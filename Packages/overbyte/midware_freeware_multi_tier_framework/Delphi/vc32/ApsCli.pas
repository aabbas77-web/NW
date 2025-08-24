{*_* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Author:       François PIETTE
Description:  Application Server Client Component
              Do not confuse TClientWSocket with TAppSrvClient which is the
              client application side. TClientWSocket is used on the server
              side to handle client connections, TAppSrvClient is used on the
              client side to connect to the application server. Both components
              are talking to each other.
Creation:     March 3, 1998
Version:      2.03
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
Mar 02, 1998  V1.01 Added a RequestDone event when DnsLookup or connection
              fails.
May 08, 1998  V1.02 Corrected a one byte error in the OnDataAvailable. Thanks
              to Miha Remec <miha.remec@k2.net> for finding the bug.
May 24, 1998  V1.03 Added comments in the source code.
Jun 01, 1998  V1.04 Removed beta status. Changed "legal stuff" to prohibe
             commercial applications whithout an agreement.
Jun 19, 1998  V1.05 Added the Connected and State properties
              Corrected Len variable in DataAvailable event handler.
Jul 08, 1998  V1.06 Adadpted for Delphi 4
Jul 09, 1998  V1.07 Added FOnBannerRcvd event, added some missing TriggerXXX
Aug 25, 1998  V1.08 Corrected a buffersize error in ProcessLine.
Nov 07, 1998  V1.09 Added var parameter in TriggerBeforeProcessReply to fix a bug
              occuring when encryption is used (CmdLen needs to be updated).
Nov 22, 1998  V2.00 Added SOCKS5 support
Apr 03, 1999  V2.01 Added AppSrvClientException. Made Request property writable.
                    Made lots of methods virtual.
Apr 16, 1999  V2.02 Added var for CmdBuf in TriggerBeforeProcessReply
Sep 15, 2001  V2.03 Added connection retry

 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
unit ApsCli;

interface

{$B-}           { Enable partial boolean evaluation   }
{$T-}           { Untyped pointers                    }
{$J+}           { Allow typed constant to be modified }
{$IFDEF VER110} { C++ Builder V3.0                    }
    {$ObjExportAll On}
{$ENDIF}

uses
    Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
    WinSock, WSocket, RFormat;

const
    AppSrvClientVersion = 203;
    CopyRight : String  = ' TAppSrvClient (c) 1998-2001 F. Piette V203 ';
    WM_REQUESTDONE      = WM_USER + 1;
    WM_RETRY            = WM_USER + 2;

type
    TErrorEvent         = procedure (Sender       : TObject;
                                     Error        : Integer;
                                     Msg          : String) of object;
    TRequestDone        = procedure (Sender       : TObject;
                                     Error        : Integer) of object;
    TProcessReplyEvent  = procedure (Sender       : TObject;
                                     var CmdBuf   : PChar;
                                     var CmdLen   : Integer) of object;
    TProcessBannerEvent = procedure (Sender       : TObject;
                                     CmdBuf       : PChar;
                                     CmdLen       : Integer;
                                     var BannerOk : Boolean) of object;
    TConnectionRetryEvent = procedure (Sender       : TObject;
                                       Error        : Integer) of object;
    TClientState = (cstReady, cstDnsLookup, cstConnecting, cstWaitingResponse);
    AppSrvClientException = class(Exception);

    TAppSrvClient = class(TComponent)
    protected
        FFunctionCode         : String;
        FWSocket              : TWSocket;
        FPort                 : String;
        FServer               : String;
        FServerIP             : String;
        FSocksServer          : String;
        FSocksPort            : String;
        FSocksUsercode        : String;
        FSocksPassword        : String;
        FSocksAuthentication  : TSocksAuthentication;
        FRequest              : TMWBuffer;
        FAnswer               : TMWBuffer;
        FAnswerStatus         : String;
        FState                : TClientState;
        FRcvBuf               : PChar;
        FRcvCnt               : LongInt;
        FRcvSize              : LongInt;
        FBannerRcvd           : Boolean;
        FHandle               : HWND;
        FRequestHeader        : PChar;
        FRequestHeaderLen     : Integer;
        FRequestBody          : PChar;
        FRequestBodyLen       : Integer;
        FRetrying             : Boolean;
        FRetryCount           : Integer;
        FMaxRetries           : Integer;
        FOnError              : TErrorEvent;
        FOnRequestDone        : TRequestDone;
        FOnSessionConnected   : TSessionConnected;
        FOnSessionClosed      : TSessionClosed;
        FOnBeforeProcessReply : TProcessReplyEvent;
        FOnAfterProcessReply  : TProcessReplyEvent;
        FOnBeforeSendRequest  : TNotifyEvent;
        FOnAfterSendRequest   : TNotifyEvent;
        FOnBannerRcvd         : TProcessBannerEvent;
        FOnSocksError         : TSocksErrorEvent;
        FOnSocksConnected     : TSessionConnected;
        FOnSocksAuthState     : TSocksAuthStateEvent;
        FOnConnectionRetry    : TConnectionRetryEvent;
        procedure WndProc(var MsgRec: TMessage);
        procedure WMRetry(var MsgRec: TMessage);
        procedure Notification(AComponent: TComponent; Operation: TOperation); override;
        procedure SessionConnected(Sender : TObject; Error : Word); virtual;
        procedure SessionClosed(Sender : TObject; Error : Word); virtual;
        procedure DnsLookupDone(Sender : TObject; Error : Word); virtual;
        procedure DataAvailable(Sender : TObject; Error : Word); virtual;
        procedure SocksConnected(Sender : TObject; Error : Word); virtual;
        procedure SocksError(Sender : TObject; Error : Integer; Msg : String); virtual;
        procedure SocksAuthState(Sender : TObject; AuthState : TSocksAuthState); virtual;
        procedure TriggerError(Error : Word; Msg : String); virtual;
        procedure TriggerRequestDone(Error : Word); virtual;
        procedure TriggerBeforeSendRequest; virtual;
        procedure TriggerAfterSendRequest; virtual;
        procedure TriggerBannerRcvd(CmdBuf : PChar;
                                    CmdLen : Integer;
                                    var BannerOk : Boolean); virtual;
        procedure TriggerBeforeProcessReply(var CmdBuf : PChar;
                                            var CmdLen : Integer); virtual;
        procedure TriggerAfterProcessReply(CmdBuf : PChar;
                                           CmdLen : Integer); virtual;
        procedure TriggerConnectionRetry(Error : Word);
        procedure ProcessLine(CmdBuf : PChar; CmdLen : Integer); virtual;
        procedure SendRequest; virtual;
        procedure CrackHeader(AnsBuffer        : PChar;
                              AnsLength        : Integer;
                              var AnswerStatus : String;
                              var ParamPtr     : PChar;
                              var ParamLen     : LongInt); virtual;
        function  GetConnected : Boolean; virtual;
        procedure SetSocksPort(newValue : String); virtual;
        procedure SetRequest(NewValue : TMWBuffer); virtual;
    public
        constructor Create(AOwner : TComponent); override;
        destructor  Destroy; override;
        {:Send a function code and request (parmeters) to the application
          server. This is the main function of the component. The communication
          with the application server is established if needed. }
        procedure   Send; virtual;
        {:Close the communication with the application server. }
        procedure   Close; virtual;
        {:Create a new Requet buffer, if required.}
        procedure   CreateRequestMWBuffer;

        {:WSocket is the reference to the underlaiying TWSocket component used
          for communication with the application server. }
        property WSocket : TWSocket                  read  FWSocket;
        {:The request property holds the parameters sent to the application
          server. The application server uses the function code to know which
          server object must be instanciated, and pass the paramters to this
          server object. Parameters can be anything and are consituted of
          records made of fields. See TMWBuffer object description for details.}
        property Request : TMWBuffer                 read  FRequest
                                                     write SetRequest;
        {:The AnswerStatus property hold the ResultStatus returned back by the
          application server. It plays the same role as the function code in
          the request. The meaning for the value is left to the application
          author. The server and client code does'nt use it. It is just passed
          from the server to the client. By default the server use numeric
          values like those used by the HTTP protocol. }
        property AnswerStatus : String               read  FAnswerStatus;
        {:The handle for the hidden window used to send and receive internal
          messages for component work. }
        property Handle  : HWND                      read  FHandle;
        {:The connected property tell if conection with the server is alive }
        property Connected            : Boolean      read  GetConnected;
        property State                : TClientState read  FState;
        property RequestHeader        : PChar        read  FRequestHeader
                                                     write FRequestHeader;
        property RequestHeaderLen     : Integer      read  FRequestHeaderLen
                                                     write FRequestHeaderLen;
        property RequestBody          : PChar        read  FRequestBody
                                                     write FRequestBody;
        property RequestBodyLen       : Integer      read  FRequestBodyLen
                                                     write FRequestBodyLen;
    published
        {:The function code is a string which is used by the application server
          to know which server object to instanciate to execute the request.
          It can be anything but default in the server to the server object
          name without the leading TServerObject. For example if you made a
          server object whose class name is TServerObjectGETCLIENT then the
          function code will be GETCLIENT. This behaviour can be overriden in
          the server object by overrinding the BuildFunctionCode procedure.
          The function code is case incensitive. }
        property FunctionCode : String               read  FFunctionCode
                                                     write FFunctionCode;
        {:This is the IP address or hostname for the application server. It
          is generaly much faster to use the IP address than the hostname
          because it avoid name resolution each time the communication is
          established. Name resolution takes time, specially if there are
          some problem with the DNS. It's better to get the IP address from
          the server host name at application startup and used the IP address
          after. }
        property Server : String                     read  FServer
                                                     write FServer;
        {:This is the port number used by the server to listen for clients.
          It defaults to 2106 but can be anything. It can even be a symbolic
          name provided that name is in the 'services' table. }
        property Port : String                       read  FPort
                                                     write FPort;
        property SocksServer : String                read  FSocksServer
                                                     write FSocksServer;
        property SocksPort : String                  read  FSocksPort
                                                     write SetSocksPort;
        property SocksUsercode : String              read  FSocksUsercode
                                                     write FSocksUsercode;
        property SocksPassword : String              read  FSocksPassword
                                                     write FSocksPassword;
        property SocksAuthentication : TSocksAuthentication
                                                     read  FSocksAuthentication
                                                     write FSocksAuthentication;
        {:The Answer property holds the answer from the application server. It
          is organized as the request: records made of fields. See TMWBuffer
          description for more details. }
        property Answer  : TMWBuffer                 read  FAnswer
                                                     write FAnswer;
        {:When connection fails, the component will retry automatically. Set
          MaxRetries to the maximum retries you wants to do. Zero means no
          retry at all. }
        property MaxRetries           : Integer      read  FMaxRetries
                                                     write FMaxRetries;
        {:When the application server sent the answer to the client, the
          OnRequestdone event is triggered. The corresponding event handler is
          the right place to test for success or failure, and to parse the
          answer to extract the returned info to update the user interface or
          do whatever needs to be done with the request's result. }
        property OnRequestDone : TRequestDone        read  FOnRequestDone
                                                     write FOnRequestDone;
        {:The event OnSessionConnected is triggered when the connection has
          been established with the application server. The event handler is
          the right place to update some status bar to let the user know he is
          connected with the server. }
        property OnSessionConnected : TSessionConnected
                                                     read  FOnSessionConnected
                                                     write FOnSessionConnected;
        property OnSocksConnected : TSessionConnected
                                                     read  FOnSocksConnected
                                                     write FOnSocksConnected;
        property OnSocksError  : TSocksErrorEvent    read  FOnSocksError
                                                     write FOnSocksError;
        property OnSocksAuthState : TSocksAuthStateEvent
                                                     read  FOnSocksAuthState
                                                     write FOnSocksAuthState;
        {:The event OnSessionConnected is triggered when the connection has
          been closed. The event handler is the right place to update some
          status bar to let the user know he is disconnected from the server. }
        property OnSessionClosed : TSessionClosed    read  FOnSessionClosed
                                                     write FOnSessionClosed;
        {:The event OnBeforeProcessReply is triggered when a reply have been
          received from the server, just before it is processed for header and
          body extraction. This event is the right place to decrypt or
          decompress data sent by the server. The event handler can allocate
          some resource or memory and change the parameters passed. To free
          resource and memory, use the OnAfterProcessReply event which will pass
          the same arguments. }
        property OnBeforeProcessReply : TProcessReplyEvent
                                                     read  FOnBeforeProcessReply
                                                     write FOnBeforeProcessReply;
        {:Use to cleanup allocated resources in the OnBeforeProcessReply event
          handler. }
        property OnAfterProcessReply  : TProcessReplyEvent
                                                     read  FOnAfterProcessReply
                                                     write FOnAfterProcessReply;
        {:The OnBeforeSendRequest event is triggered just before a request and
          his parameters are sent to the server. The event handler can process
          the header (RequestHeader, RequestHeaderLen) and the parameters
          (RequestBody, RequestBodyLen) to encrypt or compress them. If needed,
          the event handler can reallocate the data elsewhere. If needed, the
          OnAfterSendRequest event handler can be used to free allocated
          resources. }
        property OnBeforeSendRequest  : TNotifyEvent read  FOnBeforeSendRequest
                                                     write FOnBeforeSendRequest;
        {:Use to cleanup allocated resources in the OnBeforeSendRequest event
          handler. }
        property OnAfterSendRequest   : TNotifyEvent read  FOnAfterSendRequest
                                                     write FOnAfterSendRequest;
        {:This event is triggered when the banner is received from the server }
        property OnBannerRcvd         : TProcessBannerEvent
                                                     read  FOnBannerRcvd
                                                     write FOnBannerRcvd;
        {:This event is triggered each time before a retry will be started. }
        property OnConnectionRetry    : TConnectionRetryEvent
                                                     read  FOnConnectionRetry
                                                     write FOnConnectionRetry;
    end;

procedure Register;

implementation


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure Register;
begin
    RegisterComponents('FPiette', [TAppSrvClient]);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
constructor TAppSrvClient.Create(AOwner : TComponent);
begin
    inherited Create(AOwner);
    FHandle                 := AllocateHWnd(WndProc);
    FState                  := cstReady;
    FWSocket                := TWSocket.Create(Self);
    FPort                   := '2106';
    FServer                 := 'localhost';
    FRcvSize                := 2048;
    GetMem(FRcvBuf, FRcvSize);
    CreateRequestMWBuffer;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
destructor TAppSrvClient.Destroy;
begin
    // Destroy Request TMWBuffer if we own it }
    if Assigned(FRequest) and (FRequest.Owner = Self) then begin
        FRequest.Destroy;
        FRequest := nil;
    end;
    if Assigned(FWSocket) then begin
        FWSocket.Destroy;
        FWSocket := nil;
    end;
    if Assigned(FRcvBuf) then begin
        FreeMem(FRcvBuf, FRcvSize);
        FRcvBuf := nil;
    end;
    DeallocateHWnd(FHandle);
    inherited Destroy;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ Create a Request TMWBuffer, if none exists.                               }
procedure TAppSrvClient.CreateRequestMWBuffer;
begin
    if not Assigned(FRequest) then begin
        FRequest                := TMWBuffer.Create(Self);
        FRequest.DataBufferSize := 1024;
        FRequest.Rewrite;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.SetRequest(NewValue : TMWBuffer);
begin
    // Destroy existing request TMWBuffer, if we own it
    if Assigned(FRequest) and (FRequest.Owner = Self) then begin
        FRequest.Destroy;
        FRequest := nil;
    end;
    FRequest := NewValue;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.Notification(
    AComponent: TComponent;
    Operation: TOperation);
begin
    inherited Notification(AComponent, operation);
    if Operation = opRemove then begin
        if AComponent = FAnswer then
            FAnswer := nil
        else if AComponent = FRequest then
            FRequest := nil
        else if AComponent = FWSocket then
            FWSocket := nil;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.WndProc(var MsgRec: TMessage);
begin
     with MsgRec do begin
         if Msg = WM_REQUESTDONE then begin
             FState := cstReady;
             TriggerRequestDone(wParam);
         end
         else if Msg = WM_RETRY then
             WMRetry(MsgRec)
         else
             Result := DefWindowProc(Handle, Msg, wParam, lParam);
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.WMRetry(var MsgRec: TMessage);
begin
    TriggerConnectionRetry(Error);
    FWSocket.Abort;
    FRetrying      := FALSE;
    if FSocksServer <> '' then
        FWSocket.SocksServer := FServerIP
    else
        FWSocket.Addr        := FServerIP;
    FWSocket.Port  := FPort;
    FWSocket.Proto := 'tcp';
    FWSocket.Connect;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.SetSocksPort(newValue : String);
begin
    if not Assigned(FWSocket) then
        FSocksPort := newValue
    else begin
        FSocksPort := newValue;
        if FSocksPort <> FWSocket.SocksPort then
            FWSocket.SocksPort := newValue;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.TriggerConnectionRetry(Error : Word);
begin
    if Assigned(FOnConnectionRetry) then
        FOnConnectionRetry(Self, Error);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.TriggerError(Error : Word; Msg : String);
begin
    if Assigned(FOnError) then
        FOnError(Self, Error, Msg);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.TriggerRequestDone(Error : Word);
begin
    if Assigned(FOnRequestDone) then
        FOnRequestDone(Self, Error);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.TriggerBeforeSendRequest;
begin
    if Assigned(FOnBeforeSendRequest) then
        FOnBeforeSendRequest(Self);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.TriggerAfterSendRequest;
begin
    if Assigned(FOnAfterSendRequest) then
        FOnAfterSendRequest(Self);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.TriggerBannerRcvd(
    CmdBuf       : PChar;
    CmdLen       : Integer;
    var BannerOk : Boolean);
begin
    if Assigned(FOnBannerRcvd) then
        FOnBannerRcvd(Self, CmdBuf, CmdLen, BannerOk);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.TriggerBeforeProcessReply(
    var CmdBuf : PChar; var CmdLen : Integer);
begin
    if Assigned(FOnBeforeProcessReply) then
        FOnBeforeProcessReply(Self, CmdBuf, CmdLen);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.TriggerAfterProcessReply(
    CmdBuf : PChar; CmdLen : Integer);
begin
    if Assigned(FOnAfterProcessReply) then
        FOnAfterProcessReply(Self, CmdBuf, CmdLen);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.SessionConnected(Sender : TObject; Error : Word);
begin
    if (Error <> 0) and (FMaxRetries > 0) then begin
        Inc(FRetryCount);
        if FRetryCount < FMaxRetries then begin
            FRetrying := TRUE;
            PostMessage(FHandle, WM_RETRY, Error, 0);
            Exit;
        end;
    end;

    if Assigned(FOnSessionConnected) then
        FOnSessionConnected(Self, Error);
    if Error <> 0 then begin
        TriggerError(Error, 'Connection Failed');
        PostMessage(FHandle, WM_REQUESTDONE, Error, 0);
        Exit;
    end;
    { We are connected, but we need to wait for the banner from the server }
//    SendRequest;
    FWSocket.OnDataAvailable := DataAvailable;
    FWSocket.OnSessionClosed := SessionClosed;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.SocksConnected(Sender : TObject; Error : Word);
begin
    if Assigned(FOnSocksConnected) then
        FOnSocksConnected(Self, Error);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.SocksError(
    Sender : TObject; Error : Integer; Msg : String);
begin
    if Assigned(FOnSocksError) then
        FOnSocksError(Self, Error, Msg);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.SocksAuthState(
    Sender : TObject; AuthState : TSocksAuthState);
begin
    if Assigned(FOnSocksAuthState) then
        FOnSocksAuthState(Self, AuthState);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.SessionClosed(Sender : TObject; Error : Word);
begin
    if FRetrying then
        Exit;
    if Assigned(FOnSessionClosed) then
        FOnSessionClosed(Self, Error);
    if FState <> cstReady then begin
        TriggerError(WSAEINTR, 'Session closed prematurely');
        PostMessage(FHandle, WM_REQUESTDONE, WSAEINTR, 0);
    end;
    FState := cstReady;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.DnsLookupDone(Sender : TObject; Error : Word);
begin
    if Error <> 0 then begin
        TriggerError(Error, 'Dns Lookup Failed');
        PostMessage(FHandle, WM_REQUESTDONE, Error, 0);
        Exit;
    end;
    FState                       := cstConnecting;
    FServerIP                    := FWSocket.DnsResult;
    if FSocksServer <> '' then
        FWSocket.SocksServer     := FServerIP
    else
        FWSocket.Addr            := FServerIP;
    FWSocket.OnSessionConnected  := SessionConnected;
    FWSocket.OnSocksConnected    := SocksConnected;
    FWSocket.OnSocksError        := SocksError;
    FWSocket.OnSocksAuthState    := SocksAuthState;
    FWSocket.SocksUsercode       := FSocksUsercode;
    FWSocket.SocksPassword       := FSocksPassword;
    FWSocket.SocksAuthentication := FSocksAuthentication;
    FRetryCount                  := 0;
    FRetrying                    := FALSE;
    FWSocket.Connect;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ Extract the answer status and separate parameters from header             }
procedure TAppSrvClient.CrackHeader(
    AnsBuffer        : PChar;       { Given answer buffer        }
    AnsLength        : Integer;     { Given answer length        }
    var AnswerStatus : String;      { Returned answer status     }
    var ParamPtr     : PChar;       { Returned parameters start  }
    var ParamLen     : LongInt);    { Returned parameters length }
var
    I : LongInt;
begin
    { The first word is the object name }
    I := 0;
    while (I < AnsLength) and (AnsBuffer[I] <> ' ') do
        Inc(I);
    SetLength(AnswerStatus, I);
    Move(AnsBuffer^, AnswerStatus[1], I);

    { Skip spaces }
    while (I < AnsLength) and (AnsBuffer[I] = ' ') do
        Inc(I);

    { Parameters follows }
    ParamPtr := AnsBuffer + I;
    ParamLen := AnsLength - I;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.ProcessLine(CmdBuf : PChar; CmdLen : Integer);
var
    ParamStr : PChar;
    ParamLen : LongInt;
    BannerOk : Boolean;
begin
    if not FBannerRcvd then begin
        FBannerRcvd := TRUE;
        BannerOk    := TRUE;
        TriggerBannerRcvd(CmdBuf, CmdLen, BannerOk);
        if BannerOk then
            SendRequest
        else
            FWSocket.Abort;
        Exit;
    end;

    TriggerBeforeProcessReply(CmdBuf, CmdLen);

    CrackHeader(CmdBuf, CmdLen, FAnswerStatus, ParamStr, ParamLen);

    if Assigned(FAnswer) then begin
{$IFNDEF NODATACOPY}
        { This will allocate memory because we reseted the size before }
        FAnswer.DataBufferSize  := ParamLen + FAnswer.HeaderSize;
        { Warning: DataBufferSize may be greater than allocated value ! }
        FAnswer.DataBufferCount := ParamLen + FAnswer.HeaderSize;  // 25/08/98
        { Copy the data to the allocated memory }
        Move(ParamStr^, FAnswer.DataBuffer[FAnswer.HeaderSize], ParamLen);
{$ELSE}
        { Do not copy data, use it where it is...                       }
        { This is dangerous because data can be moved or overwritten if }
        { some communication take place before data is processed.       }
        { Use only if you know exactly what your are doing              }
        FAnswer.DataBuffer      := CmdBuf;    { This will free allocated memory }
        FAnswer.DataBufferSize  := CmdLen;
        FAnswer.DataBufferCount := CmdLen;
        FAnswer.HeaderSize      := ParamStr - CmdBuf;
{$ENDIF}
        { Those two assignations are needed to reset the record count }
        FAnswer.HasData         := FALSE;
        FAnswer.HasData         := TRUE;
        FAnswer.First;
        PostMessage(FHandle, WM_REQUESTDONE, 0, 0);
    end
    else
        PostMessage(FHandle, WM_REQUESTDONE, 0, 1);

    TriggerAfterProcessReply(CmdBuf, CmdLen);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.DataAvailable(Sender : TObject; Error : Word);
var
    Len    : Integer;
    NewLen : Integer;
    I      : Integer;
    p      : PChar;
begin
    { Check if the buffer is big enough }
    NewLen := FRcvCnt + FWSocket.RcvdCount;
    if NewLen >= FRcvSize then begin
         { The buffer is too small. Allocate a new one, at least 2KB greater }
         if NewLen < (FRcvSize + 2048) then
             NewLen := FRcvSize + 2048;
         GetMem(p, NewLen);
         { Move the existing data to the new buffer }
         Move(FRcvBuf^, p^, FRcvCnt);

         { Release the old buffer }
         FreeMem(FRcvBuf, FRcvSize);

         { Makes the new buffer the effective buffer }
         FRcvBuf  := p;
         FRcvSize := NewLen;
    end;

    { Receive data from the TCP/IP low level buffers }
    Len := FWSocket.Receive(@FRcvBuf[FRcvCnt], FRcvSize - FRcvCnt - 1);
    if Len <= 0 then
        Exit;

    FRcvCnt := FRcvCnt + Len;
    FRcvBuf[FRcvCnt] := #0;

    { Parse the received data to findout complete lines (search for LF) }
    while TRUE do begin
        I := FRcvCnt - Len;
        while (I < FRcvCnt) and (FRcvBuf[I] <> #10) do
            Inc(I);
        if I >= FRcvCnt then
            Exit;
        FRcvBuf[I] := #0;
        if (I > 1) and (FRcvBuf[I - 1] = #13) then begin
            FRcvBuf[I - 1] := #0;
            ProcessLine(FRcvBuf, I - 1);
            FRcvBuf[I - 1] := #13;
        end
        else
            ProcessLine(FRcvBuf, I);

        FRcvBuf[I] := #10;
        if I >= (FRcvCnt - 1) then begin
            FRcvCnt    := 0;
            FRcvBuf[0] := #0;
            break;
        end;
        Move(FRcvBuf[I + 1], FRcvBuf^, FRcvCnt - I);
        FRcvCnt := FRcvCnt - I - 1;
        Len     := Len - I - 1;  { FP: 980619 }
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.SendRequest;
var
    Header : String;
begin
    if not Assigned(FRequest) then
        raise AppSrvClientException.Create(
                'TAppSrvClient.SendRequest: Request property not assigned');

    FState                   := cstWaitingResponse;
    FWSocket.OnDataAvailable := DataAvailable;
    FWSocket.OnSessionClosed := SessionClosed;
    Header                   := FFunctionCode + ' ';
    FRequestHeader           := @Header[1];
    FRequestHeaderLen        := Length(Header);
    FRequestBody             := FRequest.DataBuffer + FRequest.HeaderSize;
    FRequestBodyLen          := FRequest.DataBufferCount;
    TriggerBeforeSendRequest;
    FWSocket.PutDataInSendBuffer(FRequestHeader, FRequestHeaderLen);
    FWSocket.PutDataInSendBuffer(FRequestBody, FRequestBodyLen);
    FWSocket.SendStr(#13#10);
    TriggerAfterSendRequest;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.Send;
begin
    if not Assigned(FAnswer) then
        raise AppSrvClientException.Create('TAppSrvClient.Send: Answer property not assigned');

    { Empty the answer }
    FAnswer.DataBuffer      := nil;   // This will free the allocated memory
    FAnswer.DataBufferSize  := 0;
    FAnswer.DataBufferCount := 0;
    FAnswer.HasData         := FALSE;

    if FWSocket.State = wsConnected then
        SendRequest
    else begin
        { Not connected. Start the event chain until send request }
        FBannerRcvd              := FALSE;
        FWSocket.Port            := FPort;
        FWSocket.Proto           := 'tcp';
        FWSocket.OnDnsLookupDone := DnsLookupDone;
        FState                   := cstDnsLookup;
        if FSocksServer = '' then
            FWSocket.DnsLookup(FServer)
        else begin
            FWSocket.DnsLookup(FSocksServer);
            FWSocket.Addr := FServer;
        end;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TAppSrvClient.Close;
begin
    if FState = cstDnsLookup then
        FWSocket.CancelDnsLookup
    else if FWSocket.State <> wsClosed then
        FWSocket.Close
    else
        FState := cstReady;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TAppSrvClient.GetConnected : Boolean;
begin
    Result := FWSocket.State = wsConnected;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}

end.

