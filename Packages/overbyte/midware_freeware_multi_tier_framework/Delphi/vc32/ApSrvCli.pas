{*_* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Author:       François PIETTE
Description:  ClientWSocket component. It handle the client connection for
              the application server for F. Piette's middleware (MidWare).
              Do not confuse TClientWSocket with TAppSrvClient which is the
              client application side. TClientWSocket is used on the server
              side to handle client connections, TAppSrvClient is used on the
              client side to connect to the application server. Both components
              are talking to each other.
Creation:     February 17, 1998
Version:      1.09
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
Mar 27, 1998  V1.01 Added a ConnectedSince and LastCommand properties
              Added a Banner property, must be a single line
Apr 10, 1998  V1.01 Removed aSocket from StartConnection.
May 18, 1998  V1.03 Implemented command timeout to disconnect an inactive
              user after a period of inactivity (30 minutes by default).
              The CheckCommandTimeOut has to be called to make this feature
              work. It's the server component who do it. Using a TTimer here
              would consume too much resources.
Jun 01, 1998  V1.04 Removed beta status. Changed "legal stuff" to prohibe
              commercial applications whithout an agreement.
Jun 07, 1998  V1.05 Added ReplyHeader, ReplyHeaderLen, ReplyBody, ReplyBodyLen,
              and SendReply to allow easy encryption and compression
              implementation.
Jul 08, 1998  V1.06 Adapted for Delphi 4
Jul 13, 1998  V1.07 Corrected properties declaration order which prevented
              BCB to compile this unit, terminating on an internal error !
              Functions and procedure must be declared before any property.
              Added a register procedure to register the component.
Aug 17, 1998  V1.08 Added dynamic RcvBuf allocation, OnOverflow event and
              RcvBuf, RcvSizeInc and RcvSizeMax properties.
Dec 12, 1998  V1.09 Added background exception handling


 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
unit ApSrvCli;

interface

{$B-}           { Enable partial boolean evaluation   }
{$T-}           { Untyped pointers                    }
{$J+}           { Allow typed constant to be modified }
{$IFDEF VER110} { C++ Builder V3.0                    }
    {$ObjExportAll On}
{$ENDIF}

uses
    WinTypes, WinProcs, Messages, Classes, SysUtils, Winsock, WSocket;

const
    ApSrvCliVersion    = 109;
    CopyRight : String = ' TClientWSocket (c) 98 F. Piette V1.09 ';
    DefaultRcvSize     = 64536;
    DefaultRcvSizeInc  = 64536;
    DefaultRcvSizeMax  = 0;             { Unlimited size }
    WM_ABORT_REQUEST   = WM_USER + 10;

type
    ClientWSocketException = class(Exception);
    TDisplayEvent  = procedure (Sender : TObject; Msg : String) of object;
    TCommandEvent  = procedure (Sender : TObject; CmdBuf : PChar; CmdLen : Integer) of object;
    TTimeoutEvent  = procedure (Sender : TObject; var CanClose : Boolean) of object;
    TOverflowEvent = procedure (Sender : TObject; var CanAbort : Boolean) of object;

    {:TClientWSocket is a specialized TWSocket which handle a single client
      connected to the application server. TAppServer component instanciate a
      new TClientWSocket for each new client connecting to the server. }
    TClientWSocket = class(TCustomWSocket)
    protected
        FRcvBuf            : PChar;
        FRcvCnt            : Integer;
        FRcvSize           : Integer;
        FRcvSizeInc        : Integer;
        FRcvSizeMax        : Integer;
        FBusy              : Boolean;
        FConnectedSince    : TDateTime;
        FLastCommandTime   : TDateTime;
        FCommandCount      : LongInt;
        FCommandTimeOut    : TDateTime;
        FBanner            : String;
        FPeerAddr          : String;
        FReplyHeader       : PChar;
        FReplyHeaderLen    : Integer;
        FReplyBody         : PChar;
        FReplyBodyLen      : Integer;
        FUserData          : LongInt;
        FAbortRequest      : Boolean;
        FOnDisplay         : TDisplayEvent;
        FOnCommand         : TCommandEvent;
        FOnTimeout         : TTimeoutEvent;
        FOnOverflow        : TOverflowEvent;
        procedure TriggerSessionConnected(Error : Word); override;
        function  TriggerDataAvailable(Error : Word) : boolean; override;
        procedure TriggerCommand(CmdBuf : PChar; CmdLen : Integer); virtual;
        procedure TriggerTimeout(var CanClose : Boolean); virtual;
        procedure TriggerOverflow(var CanAbort : Boolean); virtual;
        procedure SetRcvSize(newValue : Integer);
        procedure WndProc(var MsgRec: TMessage); override;
        procedure WMAbortRequest(var msg: TMessage); message WM_ABORT_REQUEST;
    public
        constructor Create(AOwner: TComponent); override;
        destructor  Destroy; override;
        {:First method to be invoked on client connection. It initializes
          internal working and send the banner to the client. }
        procedure   StartConnection;
        {:Procedure used by TAppServer to check for inactivity timeout. }
        procedure   CheckCommandTimeout; virtual;
        procedure   SendReply; virtual;
        procedure   Dup(newHSocket : TSocket); override;
        function    GetPeerAddr: string; override;

        {:Store the client's IP address. The value is cached. }
        property    PeerAddr        : String    read  GetPeerAddr;
        {:Gives the time when the client connected. }
        property    ConnectedSince  : TDateTime read  FConnectedSince;
        {:Gives the time of the last command received. Use for timeout. }
        property    LastCommandTime : TDateTime read  FLastCommandTime;
        {:Number of commands issued by the client. }
        property    CommandCount    : LongInt   read  FCommandCount;
        {:Timeout value. If the client stay inactive for this period of
          time, the server will disconnect it. }
        property    CommandTimeOut  : TDateTime read  FCommandTimeOut
                                                write FCommandTimeout;
        {:The actual buffer used to store incomming data }
        property    RcvBuf : PChar              read  FRcvBuf;
        {:Inherited property giving the number of bytes received. }
        property    RcvdCount;
        {:ReplyHeader point to the header built by the AppServer based
          on reply status. }
        property    ReplyHeader : PChar         read  FReplyHeader
                                                write FReplyHeader;
        {:ReplyHeaderLen is the length in byte for the header. }
        property    ReplyHeaderLen : Integer    read  FReplyHeaderLen
                                                write FReplyHeaderLen;
        {:ReplyBody point to the answer to be sent to the client. }
        property    ReplyBody : PChar           read  FReplyBody
                                                write FReplyBody;
        {:ReplyBodyLen is the length in bytes for the answer. }
        property    ReplyBodyLen : Integer      read  FReplyBodyLen
                                                write FReplyBodyLen;
        property    LocalPort;
    published
        {:The banner to be sent to the client upon connection. }
        property Banner : String           read  FBanner
                                           write FBanner;
        {:Size of buffer used to receive commands (requests). }
        property RcvSize : integer         read  FRcvSize
                                           write SetRcvSize;
        {:When RcvSize is too small, the buffer will be enlarged by RcvSizeInc
          bytes automatically until RcvSizeMax is reached }
        property RcvSizeInc : Integer      read  FRcvSizeInc
                                           write FRcvSizeInc;
        {:Maximum size allowed for the RcvBuf }
        property RcvSizeMax : Integer      read  FRcvSizeMax
                                           write FRcvSizeMax;
        {:Tells if the previous request is still executing. }
        property Busy : Boolean            read  FBusy
                                           write FBusy;
        {:UserData is not user by MidWare, it is left for the application
          programmer use. }
        property UserData : LongInt        read  FUserData
                                           write FUserData;
        {:Triggered when the component wants to display something on the user
          interface. }
        property OnDisplay : TDisplayEvent read  FOnDisplay
                                           write FOnDisplay;
        {:Triggered when a client request (command) is received. }
        property OnCommand : TCommandEvent read  FOnCommand
                                           write FOnCommand;
        {:Triggered when the client timedout as is about to be disconnected
          by TAppServer. }
        property OnTimeout : TTimeoutEvent read  FOnTimeout
                                           write FOnTimeout;
        {:Triggered when the input buffer is overflowed and can't be enlarged }
        property OnOverflow : TOverflowEvent
                                           read  FOnOverflow
                                           write FOnOverflow;
        {:Inherited event triggered when the client disconnect. }
        property OnSessionClosed;
        {:Inherited event triggered when an exception occurs in the background }
        property OnBgException;
        {:Inherited property giving the winsock handle. }
        property HSocket;
    end;

procedure Register;

implementation

const
    DefaultBanner = 'Hello from MidWare Server';


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure Register;
begin
    RegisterComponents('FPiette', [TClientWSocket]);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
constructor TClientWSocket.Create(AOwner: TComponent);
begin
    inherited Create(AOwner);
    FBanner         := DefaultBanner;
    FCommandTimeOut := EncodeTime(0, 30, 0, 0);  { 30 minutes }
    FRcvSizeMax     := DefaultRcvSizeMax;
    FRcvSizeInc     := DefaultRcvSizeInc;
    if (DefaultRcvSizeMax <> 0) and (FRcvSizeMax < DefaultRcvSize) then
        SetRcvSize(DefaultRcvSizeMax)
    else
        SetRcvSize(DefaultRcvSize);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
destructor TClientWSocket.Destroy;
begin
    FRcvCnt := 0;      { Cancel received data }
    SetRcvSize(0);     { Free the buffer      }
    inherited Destroy;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TClientWSocket.WndProc(var MsgRec: TMessage);
begin
    with MsgRec do begin
        if Msg = WM_ABORT_REQUEST then begin
            try
                WMAbortRequest(MsgRec)
            except
                on E:Exception do
                    HandleBackGroundException(E);
            end;
        end
        else
            inherited WndProc(MsgRec);
   end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TClientWSocket.WMAbortRequest(var msg: TMessage);
begin
    { Verify that the socket handle is ours handle }
    if msg.wParam <> HSocket then
        Exit;
    FAbortRequest := FALSE;
    Abort;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TClientWSocket.SetRcvSize(newValue : Integer);
begin
    if FRcvSize < 0 then
        FRcvSize := 0;

    if FRcvSize = newValue then
        Exit; { No change, nothing to do }

    if (FRcvSizeMax > 0) and (newValue > FRcvSizeMax) then
        raise ClientWSocketException.Create(
            'Can''t expand receive buffer, max size (' + IntToStr(FRcvSizeMax) +
            ' bytes) has been reached');

    if newValue < FRcvCnt then
        raise ClientWSocketException.Create(
           'Can''t reduce buffer size now because data ' +
           'will not fit in new size');

    FRcvSize := newValue;
    ReallocMem(FRcvBuf, newValue);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TClientWSocket.StartConnection;
begin
    FConnectedSince  := Now;
    FLastCommandTime := Now;
    FCommandCount    := 0;
    SendStr(FBanner + #13 + #10);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TClientWSocket.GetPeerAddr: String;
begin
    Result := FPeerAddr;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TClientWSocket.Dup(newHSocket : TSocket);
begin
    inherited Dup(newHSocket);
    FPeerAddr := inherited GetPeerAddr;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TClientWSocket.TriggerSessionConnected(Error : Word);
begin
    FAbortRequest := FALSE;
    FPeerAddr     := inherited GetPeerAddr;
    inherited TriggerSessionConnected(Error);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TClientWSocket.CheckCommandTimeout;
var
    CanClose : Boolean;
begin
    if (State <> wsConnected) or (FCommandTimeOut <= 0) then
        Exit;
    if Now > (FLastCommandTime + FCommandTimeOut) then begin
        CanClose := TRUE;
        TriggerTimeout(CanClose);
        if CanClose then
            Close;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TClientWSocket.TriggerCommand(CmdBuf : PChar; CmdLen : Integer);
begin
    if Assigned(FOnCommand) then
        FOnCommand(Self, CmdBuf, CmdLen);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TClientWSocket.TriggerTimeout(var CanClose : Boolean);
begin
    if Assigned(FOnTimeout) then
        FOnTimeout(Self, CanClose);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TClientWSocket.TriggerOverflow(var CanAbort : Boolean);
begin
    if Assigned(FOnOverflow) then
        FOnOverflow(Self, CanAbort);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TClientWSocket.TriggerDataAvailable(Error : Word) : Boolean;
var
    Len        : Integer;
    I          : Integer;
    CanAbort   : Boolean;
    AllowedInc : Integer;
begin
    if FAbortRequest then begin
        Result := FALSE;
        Exit;
    end;

    Result := TRUE;                                { We read data }
    { check space in buffer }
    if (FRcvSize - FRcvCnt - 1) <= 0 then begin
        { No space left, enlarge the buffer }
        try
            if FRcvSizeMax > 0 then begin
                AllowedInc := FRcvSizeMax - FRcvSize;
                if AllowedInc <= 0 then
                    raise ClientWSocketException.Create('');
                if AllowedInc > FRcvSizeInc then
                    SetRcvSize(FRcvSize + FRcvSizeInc)
                else
                    SetRcvSize(FRcvSize + AllowedInc);
            end
            else
                SetRcvSize(FRcvSize + FRcvSizeInc);
        except
            CanAbort := TRUE;
            TriggerOverflow(CanAbort);
            if CanAbort then begin
                FAbortRequest := TRUE;
                PostMessage(Handle, WM_ABORT_REQUEST, HSocket, 0);
            end;
            { Buffer cannot be enlarged, cancel actual content }
            FRcvCnt := 0;
            Result  := FALSE;
            Exit;
        end;
    end;

    Len := Receive(@FRcvBuf[FRcvCnt], FRcvSize - FRcvCnt - 1);
    if Len <= 0 then
        Exit;

    FRcvCnt := FRcvCnt + Len;
    FRcvBuf[FRcvCnt] := #0;

    while TRUE do begin
        I := 0;
        while (I < FRcvCnt) and (FRcvBuf[I] <> #10) do
            Inc(I);
        if I >= FRcvCnt then
            Exit;
        FRcvBuf[I] := #0;
        FLastCommandTime := Now;
        Inc(FCommandCount);
        if (I > 1) and (FRcvBuf[I - 1] = #13) then begin
            FRcvBuf[I - 1] := #0;
            TriggerCommand(FRcvBuf, I - 1);
            FRcvBuf[I - 1] := #13;
        end
        else
            TriggerCommand(FRcvBuf, I);

        FRcvBuf[I] := #10;
        if I >= (FRcvCnt - 1) then begin
            FRcvCnt    := 0;
            FRcvBuf[0] := #0;
            break;
        end;
        Move(FRcvBuf[I + 1], FRcvBuf^, FRcvCnt - I);
        FRcvCnt := FRcvCnt - I - 1;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TClientWSocket.SendReply;
begin
    PutDataInSendBuffer(ReplyHeader, ReplyHeaderLen);
    PutDataInSendBuffer(ReplyBody,   ReplyBodyLen);
    PutStringInSendBuffer(#13+#10);
    Send(nil, 0);
    FBusy := FALSE;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}

end.
