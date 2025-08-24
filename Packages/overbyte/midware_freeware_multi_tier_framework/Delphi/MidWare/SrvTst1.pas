{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Author:       François PIETTE
Description:  Application Server sample.
              Work with CliTst, the corresponding client application.
Creation:     February 17, 1998
Version:      1.09
EMail:        francois.piette@overbyte.be   francois.piette@rtfm.be
              http://www.overbyte.be        http://www.rtfm.be/fpiette
              francois.piette@pophost.eunet.be
Support:      Use the mailing list midware@elists.org
              Follow "support" link at http://www.overbyte.be for subscription.
Legal issues: Copyright (C) 1997-2001 by François PIETTE
              Rue de Grady 24, 4053 Embourg, Belgium. Fax: +32-4-365.74.56
              <francois.piette@overbyte.be> <francois.piette@pophost.eunet.be>

              This software is provided 'as-is', without any express or
              implied warranty. In no event will the author be held liable
              for any damages arising from the use of this software.

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
Mar 20, 1998 V1.01 Adapted to changes made in TMWBuffer (rformat.pas)
             Added SrvObj4 to show how a TQuery could be used
May 20, 1998 V1.02 Added Dispose(FUserData)
May 23, 1998 V1.03 Added version display on startup
Jun 07, 1998 V1.04 Implemented encryption in commands and replies.
Aug 24, 1998 V1.05 Added some comments and displayed server error message
                   in case of failure.
Dec 30, 1998 V1.06 Added SrvObj9 with SETCLIENT function code.
Mar 26, 1999 V1.07 Added code to support LZH compression. See LZH define.
Apr 04, 1999 V1.08 Corrected a bug in AppServer1AfterProcessRequest which was
                   always freeing memory, regardless of LZH compression
Apr 24, 1999 V1.09 Added CgiGate and IsaGate server objects (SrvObj10.pas)

 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
unit SrvTst1;
{$DEFINE LZH}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  IniFiles, WSocket, Menus, StdCtrls, Db, DBTables, ExtCtrls, Winsock,
  ApSrvCli, RFormat, RBroker, ApServer, SrvTst2, SrvObj1, SrvObj2,
  SrvObj3, SrvObj4, SrvObj5, {SrvObj6, SrvObj7, }Srvobj8, SrvObj9,
  SrvObj10, SObjSql,
{$IFDEF LZH}
  CipherLz;
{$ELSE}
  Cipher;
{$ENDIF}

const
  SrvTstVersion = 109;
  WM_APPSTARTUP = WM_USER + 1;

type
  TServerForm = class(TForm)
    DisplayMemo: TMemo;
    Panel1: TPanel;
    ClientCountLabel: TLabel;
    ObjectCountLabel: TLabel;
    TestButton: TButton;
    DisconnectAllButton: TButton;
    RequestBroker1: TRequestBroker;
    AppServer1: TAppServer;
    Label1: TLabel;
    Label2: TLabel;
    ClearButton: TButton;
    FunctionsButton: TButton;
    Table1: TTable;
    Query1: TQuery;
    Table2: TTable;
    procedure FormShow(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure TestButtonClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure DisconnectAllButtonClick(Sender: TObject);
    procedure AppServer1ClientConnected(Sender: TObject; CliWSocket : TClientWSocket);
    procedure AppServer1ClientClosed(Sender: TObject; CliWSocket : TClientWSocket);
    procedure AppServer1Display(Sender: TObject; Msg: String);
    procedure AppServer1ClientCommand(Sender: TObject;
      CliWSocket: TClientWSocket; CmdBuf: PChar; CmdLen: Integer);
    procedure RequestBroker1ObjCreate(Sender: TObject;
      ServerObject: TServerObject);
    procedure RequestBroker1ObjDestroy(Sender: TObject;
      ServerObject: TServerObject);
    procedure ClearButtonClick(Sender: TObject);
    procedure FunctionsButtonClick(Sender: TObject);
    procedure AppServer1ClientTimeout(Sender: TObject;
      CliWSocket: TClientWSocket; var CanClose: Boolean);
    procedure FormDestroy(Sender: TObject);
    procedure AppServer1BeforeSendReply(Sender: TObject;
      CliWSocket: TClientWSocket);
    procedure AppServer1AfterSendReply(Sender: TObject;
      CliWSocket: TClientWSocket);
    procedure AppServer1BeforeProcessRequest(Sender: TObject;
      CliWSocket: TClientWSocket; var CmdBuf: PChar; var CmdLen: Integer);
    procedure AppServer1AfterProcessRequest(Sender: TObject;
      CliWSocket: TClientWSocket; var CmdBuf: PChar; var CmdLen: Integer);
  private
    { Déclarations privées }
    FInitialized   : Boolean;
    FIniFileName   : String;
    FPort          : String;
    FRequestBuffer : TMWBuffer;
    FUserData      : PUserDataRecord;
    procedure WMAppStartup(var msg: TMessage); message WM_APPSTARTUP;
    function EnumServerFunctions(Sender: TObject;
                                 FunctionCode : String) : boolean;
  end;

var
  ServerForm: TServerForm;

implementation

{$R *.DFM}

const
    MainTitle     = 'Test Application Server';
    SectionData   = 'Data';
    KeyPort       = 'Port';
    SectionWindow = 'Window';
    KeyTop        = 'Top';
    KeyLeft       = 'Left';
    KeyWidth      = 'Width';
    KeyHeight     = 'Height';

{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerForm.FormCreate(Sender: TObject);
begin
    { Build Ini file name }
    FIniFileName := LowerCase(ExtractFileName(Application.ExeName));
    FIniFileName := Copy(FIniFileName, 1, Length(FIniFileName) - 3) + 'ini';

    { Initialize RequestBroker object }
    { There is no need to call AddServerObject when server object are }
    { installed as components and dropped on the server form. See SrvDemo }
    { sample program for such use (much simpler ! but use form's real estate }
    RequestBroker1.IniFileName := FIniFileName;
    RequestBroker1.AddServerObject(TServerObjectUPPER);
    RequestBroker1.AddServerObject(TServerObjectTHREAD);
    RequestBroker1.AddServerObject(TServerObjectGETCLIENT);
    RequestBroker1.AddServerObject(TServerObjectSETCLIENT);
    RequestBroker1.AddServerObject(TServerObjectGETCLIENTLIKE);
    RequestBroker1.AddServerObject(TServerObjectGETFILE);
    RequestBroker1.AddServerObject(TSObjSENDFILE);
    RequestBroker1.AddServerObject(TSObjCGIGATE);
    RequestBroker1.AddServerObject(TSObjISAGATE);
//    RequestBroker1.AddServerObject(TSObjGETIMAGE);
//    RequestBroker1.AddServerObject(TSObjGETIMAGELIKE);

    { It's a good place to initialize TRequestBroker.UserData with for example }
    { a pointer to a dynamically allocated record or to an object.             }
    { UserData is passed to ServerObjects instanciated by the broker. Using    }
    { it, they can gain access to some global data or procedure, such as data  }
    { base session.                                                            }

    { In this sample we use a TUserDataRecord record }
    New(FUserData);
    RequestBroker1.UserData := LongInt(FUserData);

    { Initialize user interface }
    ObjectCountLabel.Caption := '0';
    ClientCountLabel.Caption := '0';
    DisplayMemo.Clear;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerForm.FormDestroy(Sender: TObject);
begin
    if Assigned(FUserData) then begin
        Dispose(FUserData);
        FUserData := nil;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerForm.FormShow(Sender: TObject);
var
    IniFile : TIniFile;
begin
    if not FInitialized then begin
        FInitialized        := TRUE;
        Caption             := 'Starting ' + MainTitle;

        IniFile := TIniFile.Create(FIniFileName);
        Width  := IniFile.ReadInteger(SectionWindow, KeyWidth,  Width);
        Height := IniFile.ReadInteger(SectionWindow, KeyHeight, Height);
        Top    := IniFile.ReadInteger(SectionWindow, KeyTop,    (Screen.Height - Height) div 2);
        Left   := IniFile.ReadInteger(SectionWindow, KeyLeft,   (Screen.Width - Width) div 2);
        FPort  := IniFile.ReadString(SectionData,    KeyPort,   '2106');
        IniFile.Free;

        { We use a custom message to initialize things once the form }
        { is visible                                                 }
        PostMessage(Handle, WM_APPSTARTUP, 0, 0);
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerForm.FormClose(Sender: TObject;
  var Action: TCloseAction);
var
    IniFile : TIniFile;
begin
    AppServer1.Stop;
    AppServer1.DisconnectAll;
    IniFile := TIniFile.Create(FIniFileName);
    IniFile.WriteInteger(SectionWindow, KeyTop,    Top);
    IniFile.WriteInteger(SectionWindow, KeyLeft,   Left);
    IniFile.WriteInteger(SectionWindow, KeyWidth,  Width);
    IniFile.WriteInteger(SectionWindow, KeyHeight, Height);
    IniFile.WriteString(SectionData,    KeyPort,   FPort);
    IniFile.Free;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerForm.DisconnectAllButtonClick(Sender: TObject);
begin
    AppServer1.DisconnectAll;
    ClientCountLabel.Caption := IntToStr(AppServer1.ClientCount);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This message handler is triggered by the FormShow event. We comes here    }
{ only when the form is visible on screen.                                  }
procedure TServerForm.WMAppStartup(var msg: TMessage);
var
    PrvWnd  : HWND;
    Buf     : String;
    Data    : TWSAData;
begin
    { Prevent the server from running twice }
    Buf    := ClassName;
    PrvWnd := FindWindow(PChar(Buf), MainTitle);
    if PrvWnd <> 0 then begin
        Close;
        Exit;
    end;
    Caption := MainTitle;
    Update;                { It's nice to have the form completely displayed }

    { Display all pertinent info versions }
    DisplayMemo.Lines.Add(Format('SrvTst version %d.%2.2d' ,
                    [SrvTstVersion div 100, SrvTstVersion mod 100]));
    DisplayMemo.Lines.Add(Format('TAppServer version %d.%2.2d' ,
                    [ApServerVersion div 100, ApServerVersion mod 100]));
    DisplayMemo.Lines.Add(Format('TRequestBroker version %d.%2.2d' ,
                    [RBrokerVersion div 100, RBrokerVersion mod 100]));
    DisplayMemo.Lines.Add(Format('TServerObject version %d.%2.2d' ,
                    [ServerObjectVersion div 100, ServerObjectVersion mod 100]));
    DisplayMemo.Lines.Add(Format('TMWBuffer version %d.%2.2d' ,
                    [MWBufferVersion div 100, MWBufferVersion mod 100]));
    DisplayMemo.Lines.Add(Format('TWSocket version %d.%2.2d' ,
                    [WSocketVersion div 100, WSocketVersion mod 100]));
    Data := WinsockInfo;
    DisplayMemo.Lines.Add('Windows TCP/IP (Winsock) version ' +
                          IntToStr(LOBYTE(Data.wVersion)) + '.' +
                          IntToStr(HIBYTE(Data.wVersion)));
    DisplayMemo.Lines.Add(StrPas(Data.szDescription));
    DisplayMemo.Lines.Add(StrPas(Data.szSystemStatus));

    { Of the TTable and initialize UserData }
    FUserData.CliQuery  := Query1;
    Query1.DatabaseName := LowerCase(ExtractFilePath(Application.ExeName));

    FUserData.CliTable  := Table1;
    Table1.DatabaseName := LowerCase(ExtractFilePath(Application.ExeName));
    Table1.TableName    := 'clients.dbf';

//    Table1.DatabaseName := 'dbOvernet_JET';
//    Table1.TableName    := 'OrderDetails';

//    FUserData.ImgTable  := Table2;
//    Table2.DatabaseName := LowerCase(ExtractFilePath(Application.ExeName));
//    Table2.TableName    := 'album.db';
    DisplayMemo.Lines.Add('Opening ' + Table1.DatabaseName + Table1.TableName);
    try
        Table1.Open;
    except
        on E:Exception do begin
            DisplayMemo.Lines.Add(E.Message);
        end;
    end;
//    DisplayMemo.Lines.Add('Opening ' + Table2.DatabaseName + Table2.TableName);
//    try
//        Table2.Open;
//    except
//        on E:Exception do begin
//            DisplayMemo.Lines.Add(E.Message);
//        end;
//    end;

    { Start the application server component }
    AppServer1.Port := FPort;
    AppServer1.Start;
    DisplayMemo.Lines.Add('Server ready.');
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ A new client has connected, update our user interface                     }
procedure TServerForm.AppServer1ClientConnected(
    Sender     : TObject;
    CliWSocket : TClientWSocket);
begin
    ClientCountLabel.Caption := IntToStr(AppServer1.ClientCount);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ A client has disconnected, update our user interface                      }
procedure TServerForm.AppServer1ClientClosed(
    Sender     : TObject;
    CliWSocket : TClientWSocket);
begin
    ClientCountLabel.Caption := IntToStr(AppServer1.ClientCount - 1);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This event handler is called when the AppServer component has some info   }
{ to display. This info can comes from one of the server components also.   }
procedure TServerForm.AppServer1Display(Sender: TObject; Msg: String);
begin
    DisplayMemo.Lines.Add(Msg);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This event handler is called by the AppServer component when a client     }
{ request has been received. We just display it for this demo, but it is    }
{ not a good idea for performance reasons.                                  }
procedure TServerForm.AppServer1ClientCommand(Sender: TObject;
  CliWSocket: TClientWSocket; CmdBuf: PChar; CmdLen: Integer);
begin
    DisplayMemo.Lines.Add(CliWSocket.PeerAddr + ' ' + StrPas(CmdBuf));
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This event handler is called when the object request broker has just      }
{ instanciated a server object to execute a user request.                   }
procedure TServerForm.RequestBroker1ObjCreate(Sender: TObject;
  ServerObject: TServerObject);
begin
    ObjectCountLabel.Caption := IntToStr(RequestBroker1.ObjectCount);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This event handler is called just before the object request broker        }
{ destroy a server object after having executed a user request.             }
procedure TServerForm.RequestBroker1ObjDestroy(Sender: TObject;
  ServerObject: TServerObject);
begin
    ObjectCountLabel.Caption := IntToStr(RequestBroker1.ObjectCount - 1);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerForm.ClearButtonClick(Sender: TObject);
begin
    DisplayMemo.Clear;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This function is called back by the request broker for each function code }
{ he knows about when we ask to enumerate functions.                        }
function TServerForm.EnumServerFunctions(
    Sender: TObject; FunctionCode : String) : boolean;
begin
    DisplayMemo.Lines.Add(FunctionCode);
    Result := TRUE;   { Continue to enumerate }
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerForm.FunctionsButtonClick(Sender: TObject);
begin
    RequestBroker1.EnumServerFunctions(EnumServerFunctions);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ The TestButton just shows how to use various TRequestBuffer methods       }
procedure TServerForm.TestButtonClick(Sender: TObject);
begin
    if Assigned(FRequestBuffer) then
        FRequestBuffer.Destroy;
    FRequestBuffer := TMWBuffer.Create(Self);
    FRequestBuffer.DataBufferSize := 200;
    FRequestBuffer.Rewrite;
    FRequestBuffer.WriteFields(TRUE,  ['abc', '123']);  { New record }
    FRequestBuffer.WriteFields(TRUE,  ['delphi']);      { New record }
    FRequestBuffer.WriteFields(FALSE, ['is the best']); { Append     }

    FRequestBuffer.First;
    DisplayMemo.Lines.Add(FRequestBuffer.RecordToString);
    FRequestBuffer.Next;
    DisplayMemo.Lines.Add(FRequestBuffer.RecordToString);

    FRequestBuffer.First;
    DisplayMemo.Lines.Add(FRequestBuffer.Fields[0]);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerForm.AppServer1ClientTimeout(Sender: TObject;
  CliWSocket: TClientWSocket; var CanClose: Boolean);
begin
    DisplayMemo.Lines.Add(CliWSocket.PeerAddr + ' client timed out, disconnecting');
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{$IFDEF LZH}
procedure TServerForm.AppServer1BeforeSendReply(
    Sender: TObject;
    CliWSocket: TClientWSocket);
var
    Dst    : PChar;
    DstLen : LongInt;
begin
    { Did we received an encrypted request ? }
    if CliWSocket.UserData = 0 then
        Exit; { No, nothing to do here ! }

    Encrypt(CliWSocket.ReplyHeader, CliWSocket.ReplyHeaderLen,
            CliWSocket.ReplyBody,   CliWSocket.ReplyBodyLen,
            Dst, DstLen, 1);
    Dst[0] := #$FF;
    CliWSocket.ReplyHeader    := Dst;
    CliWSocket.ReplyHeaderLen := DstLen;
    CliWSocket.ReplyBody      := nil;
    CliWSocket.ReplyBodyLen   := 0;
end;
{$ELSE}
procedure TServerForm.AppServer1BeforeSendReply(
    Sender: TObject;
    CliWSocket: TClientWSocket);
var
    Dst    : PChar;
    DstLen : Integer;
    Key    : Integer;
begin
    { Did we received an encrypted request ? }
    if CliWSocket.UserData = 0 then
        Exit; { No, nothing to do here ! }

    Key := Ord('0');
    { Encrypt will allocate new memory for encrypted data which takes a }
    { little bit more space than original data.                         }
    { Memory will be freed in the OnAfterSendReply event handler.       }
    Encrypt(CliWSocket.ReplyHeader, CliWSocket.ReplyHeaderLen,
            Dst, DstLen, Key, 2);
    CliWSocket.ReplyHeader    := Dst;
    CliWSocket.ReplyHeaderLen := DstLen;
    Dst[0] := #3; { This will let the client know we use encrypted data }
    Dst[1] := Chr(Key);
    Encrypt(CliWSocket.ReplyBody, CliWSocket.ReplyBodyLen,
            Dst, DstLen, Key, 0);
    CliWSocket.ReplyBody    := Dst;
    CliWSocket.ReplyBodyLen := DstLen;
end;
{$ENDIF}


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerForm.AppServer1AfterSendReply(Sender: TObject;
  CliWSocket: TClientWSocket);
begin
    { Did we received an encrypted request ? }
    if CliWSocket.UserData = 0 then
        Exit; { No, nothing to do here ! }

    { Memory was allocated in the OnBeforeSendReply event handler. We have }
    { to free it to avoid memory leaks.                                    }
    if CliWSocket.ReplyHeaderLen > 0 then
        FreeMem(CliWSocket.ReplyHeader, CliWSocket.ReplyHeaderLen);
    if CliWSocket.ReplyBodyLen > 0 then
        FreeMem(CliWSocket.ReplyBody,   CliWSocket.ReplyBodyLen);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{$IFDEF LZH}
procedure TServerForm.AppServer1BeforeProcessRequest(Sender: TObject;
  CliWSocket: TClientWSocket; var CmdBuf: PChar; var CmdLen: Integer);
var
    Dst    : PChar;
    DstLen : LongInt;
begin
    { Check if we have some encrypted data }
    if (CmdLen < 3) or (CmdBuf[0] <> #$FF) then
        CliWSocket.UserData := 0
    else begin
        { We've got encrypted data. Decrypt. First byte is a flag, ignore. }
        Decrypt(CmdBuf + 1, CmdLen - 1, Dst, DstLen);
        CmdBuf := Dst;
        CmdLen := DstLen;
        { Remember we received encrypted data.     }
        { Later we will then send encrypted reply. }
        CliWSocket.UserData := 1;
    end;
end;
{$ELSE}
procedure TServerForm.AppServer1BeforeProcessRequest(Sender: TObject;
  CliWSocket: TClientWSocket; var CmdBuf: PChar; var CmdLen: Integer);
var
    Cnt : Integer;
begin
    { Check if we have some encrypted data }
    if (CmdLen < 3) or (CmdBuf[0] <> #3) then
        CliWSocket.UserData := 0
    else begin
        { We've got encrypted data. }
        Decrypt(CmdBuf, CmdLen, CmdBuf, Cnt);
        { Remember we received encrypted data.     }
        { Later we will then send encrypted reply. }
        CliWSocket.UserData := 1;
    end;
end;
{$ENDIF}


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{$IFDEF LZH}
procedure TServerForm.AppServer1AfterProcessRequest(Sender: TObject;
  CliWSocket: TClientWSocket; var CmdBuf: PChar; var CmdLen: Integer);
begin
    if CliWSocket.UserData <> 0 then
        FreeMem(CmdBuf, CmdLen);
end;
{$ELSE}
procedure TServerForm.AppServer1AfterProcessRequest(Sender: TObject;
  CliWSocket: TClientWSocket; var CmdBuf: PChar; var CmdLen: Integer);
begin
    // Nothing to do
end;
{$ENDIF}

end.


