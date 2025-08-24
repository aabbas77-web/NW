{*_* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Author:       François PIETTE
Description:  Application Server Component. This is the communication kernel
              for the application server in F. Piette's Middleware (MidWare).
              This component handle all the communication work for the
              application server, keeping track of user connections.
              A complete application server is made of this somponent, a
              request broker component and a set of server components.
              See project SrvTst for a sample application server program.
Creation:     March 02, 1998
Version:      1.15
EMail:        francois.piette@overbyte.be   francois.piette@rtfm.be
              http://www.overbyte.be        http://www.rtfm.be/fpiette
              francois.piette@pophost.eunet.be
Support:      Use the mailing list midware@elists.org
              Follow "support" link at http://www.overbyte.be for subscription.
Legal issues: Copyright (C) 1998-2001 by François PIETTE
              Rue de Grady 24, 4053 Embourg, Belgium. Fax: +32-4-365.74.56
              <francois.piette@overbyte.be> <francois.piette@pophost.eunet.be>

              This software is provided 'as-is', without any express or
              implied warranty.  In no event will the author be held liable
              for any  damages arising from the use of this software.

              Permission is granted to anyone to use this software and or any
              derived or altered versions for any purpose, excluding commercial
              applications. You can use this software for personal use only.
              You may distribute it freely untouched.
              The following restrictions applies:

              1. The origin of this software must not be misrepresented, you
                 must not claim that you wrote the original software.

              2. If you use this software in a product, an acknowledgment in
                 the product documentation and displayed on screen is required.
                 The text must be: "This product is based on MidWare. Freeware
                 source code is available at http://www.rtfm.be/fpiette."

              3. Altered source versions must be plainly marked as such, and
                 must not be misrepresented as being the original software.

              4. This notice may not be removed or altered from any source
                 distribution and must be added to the product documentation.

Updates:
Mar 27, 1998  V1.01 Added ClientWSocket[] indexed property to retrive the
              client TWSocket reference (helpful for example to display all
              connected client IP addresses).
Apr 10, 1998  V1.02 Accepted the client connection before triggering the
              OnClientConnected event handler.
Apr 14, 1998  V1.03 Changed LongInt to Integer parameter ProcessClientCommand
              to match function description in TClientWSocket - ApSrvCli.PAS
              (from Bruce Christensen <brucec@compusmart.ab.ca>)
              Added a Banner property.
May 18, 1998  V1.04 Implemented client timeout functions.
May 23, 1998  V1.05 Added comments to describes properties, events and methods.
Jun 01, 1998  V1.06 Removed beta status. Changed "legal stuff" to prohibe
              commercial applications whithout an agreement.
Jun 07, 1998  V1.07 Added functionnalities to support encryption and compression
Jun 19, 1998  V1.08 DisconnectAll now trigger the OnSessionClosed event for
              each client.
Jul 08, 1998  V1.09 Adapted for Delphi 4
Jul 15, 1998  V1.10 Added TAppServer.FClientClass to allow descendent class
              to use a custom class for his clients sockets.
Aug 17, 1998  V1.11 Added handling for client buffer overflow
              Added SendStringResponseToClient to correctly format error
              responses to client (Timeout and overflow)
Sep 10, 1998  V1.12 Added RequestCount and ConnectCount property and support
Dec 12, 1998  V1.13 Added background exception handling
Feb 14, 1999  V1.14 Use runtime dynamic link with winsock, using wsocket
              functionswhich are linked at runtime instead of loadtime. This
              allows programs to run without winsock installed, provided program
              doesn't try to use TWSocket or winsock function without first
              checking for winsock installation.
              Added functions AppServerWindowProc, AppServerAllocateHWnd and
              AppServerDeallocateHWnd to handle private message handling
              without using the Forms unit (help for writing services or non
              GUI applications).
              Added OnBgexception event and related logic.
Dec 07, 2000  V1.15 Added 100mS sleep right after a client connect when we
              run on Windows 2000. Thanks to Thomas Hensle <freevcs@thensle.de>.


 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
unit ApServer;

interface

{$B-}           { Enable partial boolean evaluation   }
{$T-}           { Untyped pointers                    }
{$J+}           { Allow typed constant to be modified }
{$IFDEF VER110} { C++ Builder V3.0                    }
    {$ObjExportAll On}
{$ENDIF}

uses
    WinTypes, WinProcs, Messages, SysUtils, Classes, StdCtrls, ExtCtrls,
    RBroker, RFormat, ApSrvCli, WSocket, WinSock;

const
    ApServerVersion    = 115;
    CopyRight : String = ' TAppServer (c) 98 F. Piette V1.15 ';
    WM_DESTROY_CLIENT_SOCKET = WM_USER + 1;

type
    TClientEvent         = procedure (Sender       : TObject;
                                      CliWSocket   : TClientWSocket) of object;
    TClientCommandEvent  = procedure (Sender       : TObject;
                                      CliWSocket   : TClientWSocket;
                                      CmdBuf       : PChar;
                                      CmdLen       : LongInt) of object;
    TClientTimeoutEvent  = procedure (Sender       : TObject;
                                      CliWSocket   : TClientWSocket;
                                      var CanClose : Boolean) of object;
    TClientBgException   = procedure (Sender       : TObject;
                                      CliWSocket   : TClientWSocket;
                                      E            : Exception) of object;
    TProcessRequestEvent = procedure (Sender       : TObject;
                                      CliWSocket   : TClientWSocket;
                                      var CmdBuf   : PChar;
                                      var CmdLen   : integer) of object;
    TAppServerBgExceptionEvent = procedure (Sender : TObject;
                                            E : Exception) of object;
    TAppServerOption     = (asoAutoStart,
                            asoDisplayCommands,
                            asoDisplayClientCount);
    TAppServerOptions    = set of TAppServerOption;
    TClientWSocketClass  = class of TClientWSocket;

    {:TAppServer component is responsible for client connection, communication
      and management. It is constitued of a listening TWSocket receiving client
      connections. For each connection a new TClientWSocket is instanciated.
      TAppServer work with a linked TRequestBroker which manage to execute
      client request. }
    TAppServer = class(TComponent)
    protected
        FBanner                 : String;
        FDisplayMemo            : TCustomMemo;
        FClientClass            : TClientWSocketClass;
        FClientCountLabel       : TLabel;
        FClientList             : TList;
        FRequestCount           : LongInt;
        FConnectCount           : LongInt;
        FRequestBroker          : TRequestBroker;
        FSrvWSocket             : TWSocket;
        FPort                   : String;
        FHandle                 : HWND;
        FClientTimeout          : LongInt;          { in seconds }
        FTimeoutInterval        : LongInt;          { in seconds }
        FTimer                  : TTimer;
        FSysVersionInfo         : _OSVersionInfoA;
        FOptions                : TAppServerOptions;
        FOnDisplay              : TDisplayEvent;
        FOnClientConnected      : TClientEvent;
        FOnClientClosed         : TClientEvent;
        FOnClientCommand        : TClientCommandEvent;
        FOnClientTimeout        : TClientTimeoutEvent;
        FOnClientBgException    : TClientBgException;
        FOnBeforeSendReply      : TClientEvent;
        FOnAfterSendReply       : TClientEvent;
        FOnBeforeProcessRequest : TProcessRequestEvent;
        FOnAfterProcessRequest  : TProcessRequestEvent;
        FOnServerBgException    : TAppServerBgExceptionEvent;
        procedure   WndProc(var MsgRec: TMessage); virtual;
        procedure   Notification(AComponent: TComponent; operation: TOperation); override;
        procedure   SrvWSocketSessionAvailable(Sender: TObject; Error: Word);
        procedure   CliSessionClosed(Sender: TObject; Error: Word);
        procedure   SendResponseToClient(Dest     : TObject;
                                         ORB      : TRequestBroker;
                                         Status   : Integer;
                                         Response : PChar;
                                         Len      : Integer); virtual;
        procedure   SendStringResponseToClient(
                                         Dest     : TObject;
                                         ORB      : TRequestBroker;
                                         Status   : Integer;
                                         Response : String); virtual;
        procedure   ProcessClientCommand(Sender : TObject;
                                         CmdBuf : PChar;
                                         CmdLen : Integer);
        procedure   ProcessClientBgException(Sender : TObject;
                                             E      : Exception;
                                             var CanClose : Boolean);
        procedure   ProcessClientOverflow(Sender       : TObject;
                                          var CanAbort : Boolean);
        function    GetClientCount : Integer;
        function    GetClientWSocket(nIndex : Integer) : TClientWSocket;
        procedure   SetClientTimeout(newValue : LongInt);
        procedure   SetTimeoutInterval(newValue : LongInt);
        procedure   TimerTimer(Sender : TObject);
        procedure   CliTimeout(Sender : TObject; var CanClose : Boolean); virtual;
        procedure   Loaded; override;
        procedure   InternalDisplay(Sender : TObject; Msg : String);
        procedure   TriggerBgException(E: Exception); virtual;
    public
        constructor Create(AOwner: TComponent); override;
        destructor  Destroy; override;
        {:The start procedure will start the server. The server will accept new
          client connections. }
        procedure   Start;
        {:The Stop procedure will stop the server which will no more accept
          new clients, but will not disconnect already connected clients. }
        procedure   Stop;
        {:DisconnectAll will disconnect every connected client. Do not confuse
          with the Stop procedure. }
        procedure   DisconnectAll;
        {:SrvWSocket is the underlayng TWSocket component. }
        property SrvWSocket    : TWSocket          read  FSrvWSocket;
        {:ClientCount gives the actual numlber of connected clients. }
        property ClientCount   : Integer           read  GetClientCount;
        {:ConnectCount gives the total number of connection received since
          server startup}
        property ConnectCount  : LongInt           read  FConnectCount;
        {:RequestCount gives the total number of request received since
          server startup}
        property RequestCount  : LongInt           read  FRequestCount;
        {:ClientWSocket is an indexed property whose value is the reference to
          each connected client. }
        property ClientWSocket[nIndex : Integer] : TClientWSocket
                                                   read  GetClientWSocket;
        {:The Handle property is the windows handle for the hidden window
          the component uses for internal messages. }
        property Handle        : HWND              read  FHandle;
    published
        property DisplayMemo   : TCustomMemo       read  FDisplayMemo
                                                   write FDisplayMemo;
        property ClientCountLabel : TLabel         read  FClientCountLabel
                                                   write FClientCountLabel;
        property Options       : TAppServerOptions read  FOptions
                                                   write FOptions;
        {:The banner property is the text that is sent to the client when
          the connection has been established. This banner can be anything
          because the client ignore it. }
        property Banner        : String            read  FBanner
                                                   write FBanner;
        {:The port property gives the port number used by the server to
          listen for client connection. It can be a numeric value or a
          string value which must be present in the 'services' file.
          You should not use any port number already used in your computer.
          This default value is 2106. }
        property Port          : String            read  FPort
                                                   write FPort;
        {:ClientTimeout gives the time in seconds before the server
          disconnect a client without activity. The default value is 300
          seconds. }
        property ClientTimeout : LongInt           read  FClientTimeout
                                                   write SetClientTimeout;
        {:The server periodically check for client timeout. It uses a single
          TTimer component for this check. The TimeoutInterval is this timer
          interval and efault to 30 seconds. This means that every 30", the
          server will goes thru the client list and check for timeout. A
          smaller value gives better accuracy in timeout detection, but
          produce some overhead, specially if the number of client is large. }
        property TimeoutInterval : LongInt         read  FTimeoutInterval
                                                   write SetTimeoutInterval;
        {:The server component receive client request, data parameters and
          send replies to client. But it delegate the request dispatching to
          a dedicated component: the RequestBroker component. }
        property RequestBroker : TRequestBroker    read  FRequestBroker
                                                   write FRequestBroker;

        {:Sometimes, the server can display some infos about his internal
          working. Each time the server wants to display that info, it triggers
          the OnDisplay event. There is no need to have an event handler
          connected to this event. If you ad an event handler, it is probably
          to display the messages on the server's user interface, or just to
          log it into a file. Messages to be displayed can be generate by
          the TAppServer component or any TServerObject used in the server. }
        property OnDisplay     : TDisplayEvent     read  FOnDisplay
                                                   write FOnDisplay;
        {:This event is triggered when a client connect to the server.
          It could be used to disconnect unwanted client or any other
          processing that must be done when a new client connect, such as
          updating the server user interface to show how many clients are
          connected. }
        property OnClientConnected : TClientEvent  read  FOnClientConnected
                                                   write FOnClientConnected;
        {:When a client disconnect, the OnClientClosed event is triggered.
          The event handler could be used to update the server's user interface
          or to do any other post-processing or cleaning task. }
        property OnClientClosed    : TClientEvent  read  FOnClientClosed
                                                   write FOnClientClosed;
        {:Clients connects to the server to send commands (also called requests)
          and wait for server responses. The OnClientCommand is triggered when
          such a command arrives, before it gets executed. The event handler
          can use the command for any purpose, it can even change it. }
        property OnClientCommand   : TClientCommandEvent
                                                   read  FOnClientCommand
                                                   write FOnClientCommand;
        {:When a client had no more activity during some time specified by the
          ClientTimeout property, it is automatically disconnected. If this
          occurs, the OnClientTimeout event is triggred. }
        property OnClientTimeout   : TClientTimeoutEvent
                                                   read  FOnClientTimeout
                                                   write FOnClientTimeout;
        {:When an exception is triggered in the background. }
        property OnClientBgException : TClientBgException
                                                   read  FOnClientBgException
                                                   write FOnClientBgException;

        {:The OnBeforeSendReply event is called when a reply is ready to be
          transmitted to the client. A reply is made of a header and a body
          which are accessible thru the CliWSocket properties. The event
          has the possibility to process the header and answer to encrypt or
          compress them. It can even allocate some memory for holding the
          processed header and body. Use the OnAfterSendReply to free any
          allocated memory. The processed data must *not* contains CR/LF
          pair as it is used by the client to delimit the reply. If processed
          data has CR/LF, then it must be escaped in some way. }
        property OnBeforeSendReply : TClientEvent  read  FOnBeforeSendReply
                                                   write FOnBeforeSendReply;
        {:The OnAfterSendReply event is called once the reply header and body
          has ben written to the internal buffer for sending in the background.
          It's the right place to deallocate any resource allocated in the
          OnBeforeSendReply. }
        property OnAfterSendReply  : TClientEvent  read  FOnAfterSendReply
                                                   write FOnAfterSendReply;
        {:The OnBeforeProcessRequest event is triggered just before anything is
          done with a request received from the client. This is the right place
          to add code for decryption/decompression. If needed, the event
          handler can allocate memory or resources and change the values on
          the arguments (passed by var) to fit the requirement. Allocated
          resources must be freed from the OnAfterProcessCommand. }
        property OnBeforeProcessRequest : TProcessRequestEvent
                                                   read  FOnBeforeProcessRequest
                                                   write FOnBeforeProcessRequest;
        {:The OnAfterProcessRequest is called when a request has been
          transformed to a command for execution. It main purpose is to
          cleanup resources allocated in the OnBeforeProcessRequest event. }
        property OnAfterProcessRequest  : TProcessRequestEvent
                                                   read  FOnAfterProcessRequest
                                                   write FOnAfterProcessRequest;
        {:The OnBgException event is triggered when an exception occurs in the
          background (occuring in an event handler called from the message
          pump). If not handled, those exceptions are simply ignored. }
        property OnServerBgException    : TAppServerBgExceptionEvent
                                                    read  FOnServerBgException
                                                    write FOnServerBgException;
    end;

procedure Register;

implementation

{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure Register;
begin
    RegisterComponents('FPiette', [TAppServer]);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This function is a callback function. It means that it is called by       }
{ windows. This is the very low level message handler procedure setup to    }
{ handle the message sent by windows to handle messages.                    }
function AppServerWindowProc(
    ahWnd   : HWND;
    auMsg   : Integer;
    awParam : WPARAM;
    alParam : LPARAM): Integer; stdcall;
var
    Obj    : TObject;
    MsgRec : TMessage;
begin
    { At window creation asked windows to store a pointer to our object     }
    Obj := TObject(GetWindowLong(ahWnd, 0));

    { If the pointer doesn't represent a TAppServer, just call the default  }
    { procedure                                                             }
    if not (Obj is TAppServer) then
        Result := DefWindowProc(ahWnd, auMsg, awParam, alParam)
    else begin
        { Delphi use a TMessage type to pass parameter to his own kind of   }
        { windows procedure. So we are doing the same...                    }
        MsgRec.Msg    := auMsg;
        MsgRec.wParam := awParam;
        MsgRec.lParam := alParam;
        { May be a try/except around next line is needed. Not sure ! }
        TAppServer(Obj).WndProc(MsgRec);
        Result := MsgRec.Result;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This global variable is used to store the windows class characteristic    }
{ and is needed to register the window class used by TWSocket               }
var
    AppServerWindowClass: TWndClass = (
        style         : 0;
        lpfnWndProc   : @AppServerWindowProc;
        cbClsExtra    : 0;
        cbWndExtra    : SizeOf(Pointer);
        hInstance     : 0;
        hIcon         : 0;
        hCursor       : 0;
        hbrBackground : 0;
        lpszMenuName  : nil;
        lpszClassName : 'AppServerWindowClass');


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ Allocate a window handle. This means registering a window class the first }
{ time we are called, and creating a new window each time we are called.    }
function AppServerAllocateHWnd(Obj : TObject): HWND;
var
    TempClass       : TWndClass;
    ClassRegistered : Boolean;
begin
    { Check if the window class is already registered                       }
    AppServerWindowClass.hInstance := HInstance;
    ClassRegistered := GetClassInfo(HInstance,
                                    AppServerWindowClass.lpszClassName,
                                    TempClass);
    if not ClassRegistered then begin
       { Not yet registered, do it right now                                }
       Result := WinProcs.RegisterClass(AppServerWindowClass);
       if Result = 0 then
           Exit;
    end;

    { Now create a new window                                               }
    Result := CreateWindowEx(WS_EX_TOOLWINDOW,
                             AppServerWindowClass.lpszClassName,
                             '',        { Window name   }
                             WS_POPUP,  { Window Style  }
                             0, 0,      { X, Y          }
                             0, 0,      { Width, Height }
                             0,         { hWndParent    }
                             0,         { hMenu         }
                             HInstance, { hInstance     }
                             nil);      { CreateParam   }

    { if successfull, the ask windows to store the object reference         }
    { into the reserved byte (see RegisterClass)                            }
    if (Result <> 0) and Assigned(Obj) then
        SetWindowLong(Result, 0, Integer(Obj));
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ Free the window handle                                                    }
procedure AppServerDeallocateHWnd(Wnd: HWND);
begin
    DestroyWindow(Wnd);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
constructor TAppServer.Create(AOwner: TComponent);
begin
    inherited Create(AOwner);
    FBanner          := 'Welcome to MidWare server';
    FHandle          := AppServerAllocateHWnd(Self); // 14/02/99 AllocateHWnd(WndProc);
    FClientClass     := TClientWSocket;
    FClientList      := TList.Create;
    FSrvWSocket      := TWSocket.Create(Self);
    FPort            := '2106';
    FClientTimeout   := 300;           { 5 minutes timeout              }
    FTimeoutInterval := 30;            { Check timeout every 30 seconds }
    FTimer           := TTimer.Create(Self);
    FTimer.Enabled   := FALSE;
    FTimer.OnTimer   := TimerTimer;
    FTimer.Interval  := FTimeoutInterval * 1000;
    FOptions         := [asoDisplayCommands, asoDisplayClientCount];
    FSysVersionInfo.dwOSVersionInfoSize := SizeOf(OSVERSIONINFO);
    GetVersionEx(FSysVersionInfo);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
destructor TAppServer.Destroy;
begin
    try
        if Assigned(FClientList) then begin
            FClientList.Destroy;
            FClientList := nil;
        end;
        if Assigned(FSrvWSocket) then begin
            FSrvWSocket.Destroy;
            FSrvWSocket := nil;
        end;
        if Assigned(FTimer) then begin
            FTimer.Destroy;
            FTimer := nil;
        end;
    except
        { Ignore any exception, we cannot handle them }
    end;
    AppServerDeallocateHWnd(FHandle); // 14/02/99 DeallocateHWnd(FHandle);
    inherited Destroy;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppServer.Loaded;
begin
    inherited Loaded;
    if csDesigning in ComponentState then
        Exit;
    if (asoDisplayClientCount in FOptions) and Assigned(FClientCountLabel) then
        FClientCountLabel.Caption := '0';
    if asoAutoStart in FOptions then
        Start;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ All exceptions *MUST* be handled. If an exception is not handled, the     }
{ application will be shut down !                                           }
procedure TAppServer.TriggerBgException(E: Exception);
begin
    { First call the error event handler, if any }
    if Assigned(FOnServerBgException) then begin
        try
            FOnServerBgException(Self, E);
        except
        end;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppServer.WndProc(var MsgRec: TMessage);
begin
    try  // 14/02/99
         with MsgRec do begin
             if Msg = WM_DESTROY_CLIENT_SOCKET then
                 TClientWSocket(lParam).Destroy
             else
                 Result := DefWindowProc(Handle, Msg, wParam, lParam);
        end;
    except
        on E:Exception do
            TriggerBgException(E);
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppServer.Notification(AComponent: TComponent; operation: TOperation);
begin
    inherited Notification(AComponent, operation);
    if operation = opRemove then begin
        if AComponent = FRequestBroker then
            FRequestBroker := nil
        else if AComponent = FSrvWSocket then
            FSrvWSocket := nil
        else if AComponent = FClientCountLabel then
            FClientCountLabel := nil
        else if AComponent = FDisplayMemo then
            FDisplayMemo := nil;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppServer.DisconnectAll;
var
    CliWSocket : TClientWSocket;
begin
    if not Assigned(FClientList) then
        Exit;

    while FClientList.Count > 0 do begin
        CliWSocket := FClientList.Items[0];
        FClientList.Delete(0);
{       CliWSocket.OnSessionClosed := nil;   FP:980618}
        CliWSocket.Close;
        CliWSocket.Destroy;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppServer.Start;
begin
    if not Assigned(FSrvWSocket) then
        Exit;
    FSrvWSocket.Close;
    FSrvWSocket.Proto              := 'tcp';
    FSrvWSocket.Port               := FPort;
    FSrvWSocket.Addr               := '0.0.0.0';
    FSrvWSocket.OnSessionAvailable := SrvWSocketSessionAvailable;
    FSrvWSocket.Listen;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppServer.Stop;
begin
    if not Assigned(FSrvWSocket) then
        Exit;
    FSrvWSocket.Close;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppServer.InternalDisplay(Sender : TObject; Msg : String);
begin
    try
        if Assigned(FDisplayMemo) then
            FDisplayMemo.Lines.Add(Msg);
    except
    end;
    try
        if Assigned(FOnDisplay) then
            FOnDisplay(Sender, Msg);
    except
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppServer.SrvWSocketSessionAvailable(Sender: TObject; Error: Word);
var
    CliWSocket : TClientWSocket;
begin
    try
        CliWSocket := FClientClass.Create(self);
    except
        on E:Exception do begin
            { Some error occured during file creation, we cannot handle the client }
            InternalDisplay(self, 'Can''t create client socket instance: ' +
                            E.Message);
            { We need to satisfy winsock with the incomming connection }
            WSocket_closesocket(SrvWSocket.Accept);
            Exit;
        end;
    end;
    CliWSocket.OnDisplay       := InternalDisplay;
    CliWSocket.OnSessionClosed := CliSessionClosed;
    CliWSocket.OnOverflow      := ProcessClientOverflow;
    CliWSocket.OnCommand       := ProcessClientCommand;
    CliWSocket.OnBgException   := ProcessClientBgException;
    CliWSocket.OnTimeout       := CliTimeout;
    CliWSocket.Banner          := FBanner;
    CliWSocket.CommandTimeOut  := FClientTimeout / (24 * 3600);
    FClientList.Add(CliWSocket);
    CliWSocket.HSocket         := SrvWSocket.Accept;
    if Assigned(FClientCountLabel) and (asoDisplayClientCount in FOptions) then
        FClientCountLabel.Caption := IntToStr(FClientList.Count);
    if Assigned(FOnClientConnected) then begin
        if FSysVersionInfo.dwMajorVersion = 5 then
            Sleep(100);      // If OS is Windows 2000 then "sleep" for 100 ms
        FOnClientConnected(Self, CliWSocket);
    end;
    { We have a client, we need to check for timeout }
    if FTimeoutInterval > 0 then
        FTimer.Enabled  := TRUE;
    Inc(FConnectCount);
    CliWSocket.StartConnection;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppServer.CliSessionClosed(Sender: TObject; Error: Word);
var
    Item       : Integer;
    CliWSocket : TClientWSocket;
begin
    CliWSocket := Sender as TClientWSocket;

    if Assigned(FOnClientClosed) then
        FOnClientClosed(Self, CliWSocket);

    { Remove from list }
    Item := FClientList.IndexOf(CliWSocket);
    if Item < 0 then
        Exit;
    FClientList.Delete(Item);

    if (asoDisplayClientCount in FOptions) and Assigned(FClientCountLabel) then
        FClientCountLabel.Caption := IntToStr(FClientList.Count);

    { Do we still need to check for timeout ? }
    if FClientList.Count <= 0 then
        FTimer.Enabled  := FALSE;

    CliWSocket.Close;
    PostMessage(Handle, WM_DESTROY_CLIENT_SOCKET, 0, LongInt(CliWSocket));
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppServer.CliTimeout(Sender : TObject; var CanClose : Boolean);
var
    CliWSocket : TClientWSocket;
begin
    CliWSocket := Sender as TClientWSocket;

    if Assigned(FOnClientTimeout) then
        FOnClientTimeout(Self, CliWSocket, canClose);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppServer.SendResponseToClient(
    Dest     : TObject;
    ORB      : TRequestBroker;
    Status   : Integer;
    Response : PChar;
    Len      : Integer);
var
    CliWSocket : TClientWSocket;
    Header     : String;
begin
    { Verify that the Dest is still in our client list }
    { It is removed if the client disconnected         }
    if FClientList.IndexOf(Dest) < 0 then
        Exit;

    { The client is still there, send the result }
    CliWSocket := Dest as TClientWSocket;
    Header     := IntToStr(Status) + ' ';
    CliWSocket.ReplyHeader    := PChar(Header);
    CliWSocket.ReplyHeaderLen := Length(Header);
    CliWSocket.ReplyBody      := Response;
    CliWSocket.ReplyBodyLen   := Len;
    if Assigned(FOnBeforeSendReply) then
        FOnBeforeSendReply(self, CliWSocket);
    CliWSocket.SendReply;
    if Assigned(FOnAfterSendReply) then
        FOnAfterSendReply(self, CliWSocket);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppServer.SendStringResponseToClient(
    Dest     : TObject;
    ORB      : TRequestBroker;
    Status   : Integer;
    Response : String);
var
    Buffer     : TMWBuffer;
begin
    Buffer := TMWBuffer.Create(nil);
    try
        Buffer.DataBufferSize := 256; { Remember, there is AutoExpand }
        Buffer.WriteFields(TRUE, [Response]);
        SendResponseToClient(Dest, ORB, Status,
                             Buffer.DataBuffer, Buffer.DataBufferCount);
    finally
        Buffer.Destroy;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppServer.ProcessClientOverflow(
    Sender : TObject;
    var CanAbort : Boolean);
var
    CliWSocket : TClientWSocket;
begin
    try
        CliWSocket := Sender as TClientWSocket;
        if Assigned(FDisplayMemo) then
            FDisplayMemo.Lines.Add(CliWSocket.PeerAddr + ' Input buffer overflow');

        SendStringResponseToClient(CliWSocket, FRequestBroker, 406,
                                   'Input buffer at server overflowed');
    except
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppServer.ProcessClientBgException(
    Sender : TObject;
    E      : Exception;
    var CanClose : Boolean);
var
    CliWSocket : TClientWSocket;
begin
    CliWSocket := Sender as TClientWSocket;
    if Assigned(FOnClientBgException) then
        FOnClientBgException(Self, CliWSocket, E);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppServer.ProcessClientCommand(
    Sender : TObject;
    CmdBuf : PChar;
    CmdLen : Integer);
var
    CliWSocket : TClientWSocket;
    Buffer     : String;
    I          : Integer;
begin
    CliWSocket := Sender as TClientWSocket;

    if Assigned(FOnBeforeProcessRequest) then
        FOnBeforeProcessRequest(Self, CliWSocket, CmdBuf, CmdLen);

    try
        try
            if (asoDisplayCommands in FOptions) and Assigned(FDisplayMemo) then
                FDisplayMemo.Lines.Add(CliWSocket.PeerAddr + ' ' + StrPas(CmdBuf));
        except
        end;
        if Assigned(FOnClientCommand) then
            FOnClientCommand(Self, CliWSocket, CmdBuf, CmdLen);

        if CliWSocket.Busy then begin
            SendStringResponseToClient(CliWSocket, FRequestBroker, 405,
                                       'Server object is busy');
            CliWSocket.Busy := TRUE;   { We are still busy }
        end
        else begin
            CliWSocket.Busy := TRUE;
            try
                Inc(FRequestCount);
                FRequestBroker.BrokeRequest(Self, CmdBuf, CmdLen, CliWSocket,
                                            SendResponseToClient);
            except
                on E:Exception do begin
                   Buffer := 'ServerObject crashed: ' + E.Message;
                   { Replace all CR or LF by spaces }
                   for I := 1 to Length(Buffer) do
                       if Buffer[I] in [#13, #10] then
                           Buffer[I] := ' ';
                   SendStringResponseToClient(CliWSocket, FRequestBroker, 404,
                                              Buffer);
                end;
            end;
        end;
    finally
        if Assigned(FOnAfterProcessRequest) then
            FOnAfterProcessRequest(Self, CliWSocket, CmdBuf, CmdLen);
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TAppServer.GetClientCount : Integer;
begin
    if Assigned(FClientList) then
        Result := FClientList.Count
    else
        Result := 0;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TAppServer.GetClientWSocket(nIndex : Integer) : TClientWSocket;
begin
    if Assigned(FClientList) and
       (nIndex >= 0) and
       (nIndex < FClientList.Count) then
        Result := FClientList.Items[nIndex]
    else
        Result := nil;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppServer.SetTimeoutInterval(newValue : LongInt);
begin
    if newValue <= 0 then
        newValue := 0;
    if FTimeoutInterval = newValue then
        Exit;
    FTimeoutInterval := newValue;
    if FTimeoutInterval > 0 then
        FTimer.Interval := FTimeoutInterval * 1000
    else
        FTimer.Enabled  := FALSE;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppServer.SetClientTimeout(newValue : LongInt);
var
    I : Integer;
begin
    if newValue < 0 then
        newValue := 0;
    if FClientTimeout = newValue then
        Exit;
    FClientTimeout := newValue;
    if not Assigned(FClientList) then
        Exit;
    for I := FClientList.Count - 1 downto 0 do begin
         TClientWSocket(FClientList.Items[I]).CommandTimeout :=
                 FClientTimeout / (24 * 3600);
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppServer.TimerTimer(Sender : TObject);
var
    I : Integer;
begin
    if FTimeoutInterval > 0 then
        FTimer.Enabled := TRUE;
    if not Assigned(FClientList) then
        Exit;
    for I := FClientList.Count - 1 downto 0 do
         TClientWSocket(FClientList.Items[I]).CheckCommandTimeout;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}

end.

