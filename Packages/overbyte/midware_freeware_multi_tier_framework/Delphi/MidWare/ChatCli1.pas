{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Author:       François PIETTE
Description:  Chat Client using MidWare. Works with ChatSrv.
Creation:     June 19, 1998
Version:      1.01
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

How does it works ?
-------------------

ChatCli works with ChatSrv. Many ChatCli programs connect to one single ChatSrv
program which act as a central server. Each ChatCli log on ChatSrv, identifying
itself with a username (or nickname if you like most). ChatSrv maintain a list
of all connected ChatCli with their respective username and IP address. ChatSrv
serve as a dispatcher between all clients. Each message went by a client to
another client pass thru the server. In other words, a client send a message to
ChatSrv, telling him that the message is for some other client. ChatSrv will then
find the destination client and forward the message to him.

Each ChatCli program is also a small server because each ChatCli has to receive
messages sent by the others. If ChatCli was not a server, then he would poll the
main server to know if some message is arrived for him. Being also a server,
chatCli simply stand there waiting for ChatSrv to connect to send any message
from other clients.

Updates:
Jul 08, 1998 Adapted for Delphi 4


 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
unit ChatCli1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ApsCli, WSocket, WinSock,
  StdCtrls, ExtCtrls, IniFiles, RBroker, ApServer, RFormat, Buttons;

type
  TUserData = class(TObject)
  private
      FOnDisplay : TDisplayEvent;
  protected
      procedure TriggerDisplay(Msg : String);
  public
      property  OnDisplay : TDisplayEvent read FOnDisplay write FOnDisplay;
  end;

  TServerObjectMESSAGETO = class(TServerObject)
  public
      procedure Execute; override;
  end;

  TChatClientForm = class(TForm)
    Panel1: TPanel;
    MsgMemo: TMemo;
    ToEdit: TEdit;
    Label1: TLabel;
    ServerEdit: TEdit;
    Label2: TLabel;
    FromEdit: TEdit;
    Label3: TLabel;
    AppSrvClient: TAppSrvClient;
    DisplayMemo: TMemo;
    AppServer: TAppServer;
    RequestBroker: TRequestBroker;
    AnswerMWBuffer: TMWBuffer;
    SendBitBtn: TBitBtn;
    ConnectBitBtn: TBitBtn;
    procedure FormShow(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure ConnectBitBtnClick(Sender: TObject);
    procedure SendBitBtnClick(Sender: TObject);
    procedure AppSrvClientSessionConnected(Sender: TObject; Error: Word);
    procedure AppSrvClientSessionClosed(Sender: TObject; Error: Word);
    procedure AppSrvClientRequestDone(Sender: TObject; Error: Integer);
    procedure LogonRequestDone(Sender: TObject; Error: Integer);
    procedure MessageToRequestDone(Sender: TObject; Error: Integer);
    procedure FormDestroy(Sender: TObject);
  private
    FIniFileName         : String;
    FInitialized         : Boolean;
    FPort                : Integer;
    FUserData            : TUserData;
    procedure StartServer;
    procedure AppServerDisplay(Sender: TObject; Msg: String);
    procedure Display(Msg : String);
    procedure DoConnect;
  public
    { Déclarations publiques }
  end;

var
  ChatClientForm: TChatClientForm;

implementation

{$R *.DFM}
const
    SectionWindow  = 'WindowNewDoc';
    KeyTop         = 'Top';
    KeyLeft        = 'Left';
    KeyWidth       = 'Width';
    KeyHeight      = 'Height';
    SectionData    = 'Data';
    KeyFrom        = 'From';
    KeyTo          = 'To';
    KeyServer      = 'Server';


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TChatClientForm.FormCreate(Sender: TObject);
begin
    { Compute the INI filename based on the exe filename }
    FIniFileName := LowerCase(ExtractFileName(Application.ExeName));
    FIniFileName := Copy(FIniFileName, 1, Length(FIniFileName) - 3) + 'ini';
    RequestBroker.IniFileName := FIniFileName;
    DisplayMemo.Clear;
    MsgMemo.Clear;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TChatClientForm.FormDestroy(Sender: TObject);
begin
    if Assigned(FUserData) then begin
        FUserData.FRee;
        FUserData := nil;
        RequestBroker.UserData := 0;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TChatClientForm.FormShow(Sender: TObject);
var
    IniFile : TIniFile;
    Me      : String;
begin
    if not FInitialized then begin
        FInitialized := TRUE;

        IniFile         := TIniFile.Create(FIniFileName);
        { Restore window position and size from previous run }
        Top             := IniFile.ReadInteger(SectionWindow, KeyTop,
                                               (Screen.Height - Height) div 2);
        Left            := IniFile.ReadInteger(SectionWindow, KeyLeft,
                                               (Screen.Width - Width) div 2);
        Width           := IniFile.ReadInteger(SectionWindow, KeyWidth,  Width);
        Height          := IniFile.ReadInteger(SectionWindow, KeyHeight, Height);

        { Restore other parameters }
        Me := LocalHostName;
        if Pos('.', Me) > 0 then
            Me := Copy(Me, 1, Pos('.', Me) - 1);
        FromEdit.Text   := IniFile.ReadString(SectionData, KeyFrom,   Me);
        ToEdit.Text     := IniFile.ReadString(SectionData, KeyTo,     '');
        ServerEdit.Text := IniFile.ReadString(SectionData, KeyServer, 'localhost');
        IniFile.Free;

        { Start the server. The server is used to receive messages sent by }
        { other users thru the central server.                             }
        try
            StartServer;
        except
            on E:Exception do begin
                { Something failed during server startup. We cannot run    }
                { the application. Display a message and terminate.        }
                Application.ShowException(E);
                Application.Terminate;
                raise;
            end;
        end;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TChatClientForm.FormClose(Sender: TObject; var Action: TCloseAction);
var
    IniFile : TIniFile;
begin
    IniFile := TIniFile.Create(FIniFileName);
    { Save window position and size }
    IniFile.WriteInteger(SectionWindow, KeyTop,       Top);
    IniFile.WriteInteger(SectionWindow, KeyLeft,      Left);
    IniFile.WriteInteger(SectionWindow, KeyWidth,     Width);
    IniFile.WriteInteger(SectionWindow, KeyHeight,    Height);
    { Save other parameters }
    IniFile.WriteString(SectionData,    KeyServer,    ServerEdit.Text);
    IniFile.WriteString(SectionData,    KeyFrom,      FromEdit.Text);
    IniFile.WriteString(SectionData,    KeyTo,        ToEdit.Text);
    IniFile.Free;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TChatClientForm.ConnectBitBtnClick(Sender: TObject);
begin
    ServerEdit.SelectAll;
    FromEdit.SelectAll;
    ActiveControl := MsgMemo;
    { If we are already connected, then the connect button is disconnect }
    if AppSrvClient.Connected then
        AppSrvClient.Close
    else
        DoConnect;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ Connecting to the server is a little bit more than just conection setup.  }
{ We need to send the LOGON request with our name and the port we use for   }
{ our server part to receive the messages from other users.                 }
procedure TChatClientForm.DoConnect;
var
    Timeout : Integer;
begin
    { Send the LOGON request with our name and server port }
    AppSrvClient.FunctionCode := 'LOGON';
    AppSrvClient.Server       := ServerEdit.Text;
    AppSrvClient.Request.Rewrite;
    AppSrvClient.Request.WriteFields(TRUE, [FromEdit.Text, FPort]);
    AppSrvClient.OnRequestDone := LogonRequestDone;
    AppSrvClient.Send;

    { TAppSrvClient.Send is an asynchrounous function. It means that we get }
    { control back immediately while the request execute in the background. }
    { We need to wait until the request is done or some timeout elapsed.    }
    TimeOut := GetTickCount + 60000;
    while (TimeOut > Integer(GetTickCount)) and
          (AppSrvClient.State <> cstReady) do begin
        Application.ProcessMessages;
        Sleep(0);
    end;

    { Checked if we are received the answer of if we timed out           }
    { If we received the answer, we when thru the LogonRequestDone event }
    { handler and checked the answer.                                    }
    if AppSrvClient.State <> cstReady then
        AppSrvClient.Close;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This event handler is triggered when we received the answer for the LOGON }
{ request. The answer may be negative because we requested a name already   }
{ used by another user.                                                     }
procedure TChatClientForm.LogonRequestDone(
    Sender: TObject;
    Error: Integer);
begin
    { Restore the event handler to the default event handler }
    AppSrvClient.OnRequestDone := AppSrvClientRequestDone;

    { Check if any error where detected, such as server not responding }
    if Error <> 0 then begin
        Display('LOCAL> Logon failed, error #' + IntToStr(Error));
        AppSrvClient.Close;
        Exit;
    end;

    { Check the answer sent back by the server. The status is '200' if ok }
    { Any other value is an error, the result set contains the errror msg }
    if AppSrvClient.AnswerStatus <> '200' then begin
        Display('SERVER> ' + AppSrvClient.Answer.Fields[0]);
        AppSrvClient.Close;
        Exit;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This event handler is called when a message we sent is processed by the   }
{ chat server.                                                              }
procedure TChatClientForm.MessageToRequestDone(
    Sender: TObject;
    Error: Integer);
begin
    { Restore the event handler to the default event handler }
    AppSrvClient.OnRequestDone := AppSrvClientRequestDone;

    { Check if any error where detected, such as server not responding }
    if Error <> 0 then begin
        Display('LOCAL> MessageTo failed, error #' + IntToStr(Error));
        AppSrvClient.Close;
        Exit;
    end;

    { Check the answer sent back by the server. The status is '200' if ok }
    { Any other value is an error, the result set contains the errror msg }
    if AppSrvClient.AnswerStatus <> '200' then begin
        Display('SERVER> ' + AppSrvClient.Answer.Fields[0]);
        Exit;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This is the default event handler for request done. We should never go    }
{ here unless some programming or timing error occurs.                      }
procedure TChatClientForm.AppSrvClientRequestDone(
    Sender: TObject;
    Error: Integer);
begin
    if Error <> 0 then
        Display('Request ' + AppSrvClient.FunctionCode + ' error #' + IntToStr(Error))
    else
        Display('Request ' + AppSrvClient.FunctionCode + ' done.');
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TChatClientForm.Display(Msg : String);
begin
    { We should check memo overflow ! }
    DisplayMemo.Lines.Add(Msg);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TChatClientForm.AppServerDisplay(Sender: TObject; Msg: String);
begin
    Display(Msg);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TChatClientForm.SendBitBtnClick(Sender: TObject);
var
    Data : TMemoryStream;
    I    : Integer;
begin
    { Return focus to the message memo }
    ActiveControl := MsgMemo;

    { Send only if memo is not empty }
    if MsgMemo.Lines.Count <= 0 then begin
        MessageBeep(MB_OK);
        Exit;
    end;

    { First we need to be connected to the server }
    if not AppSrvClient.Connected then begin
        DoConnect;
        if not AppSrvClient.Connected then
            Exit;
    end;

    { Display the message locally }
    for I := 0 to MsgMemo.Lines.Count - 1 do
        Display(FromEdit.Text + '> ' + MsgMemo.Lines.Strings[I]);

    { Send the message to the remote }
    Data := TMemoryStream.Create;
    try
        MsgMemo.Lines.SaveToStream(Data);
        Data.Seek(0, 0);
        ToEdit.SelectAll;
        FromEdit.SelectAll;
        ActiveControl := MsgMemo;
        AppSrvClient.FunctionCode := 'MESSAGETO';
        AppSrvClient.Server       := ServerEdit.Text;
        AppSrvClient.Request.Rewrite;
        AppSrvClient.Request.WriteFields(TRUE, [ToEdit.Text, FromEdit.Text]);
        AppSrvClient.Request.AppendStreamField(Data, mwString);
        AppSrvClient.OnRequestDone := MessageToRequestDone;
        AppSrvClient.Send;
        MsgMemo.Clear;
    finally
        Data.Free;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This event handler is triggered when the connection is established with   }
{ the chat server. This result from the LOGON request in our case.          }
procedure TChatClientForm.AppSrvClientSessionConnected(
   Sender: TObject;
   Error: Word);
begin
    if Error = 0 then begin
        Display('You are connected to the chat server.');
        ConnectBitBtn.Caption := '&Disconnect';
    end
    else begin
        Display('Connection with the chat server failed, error #' +
                IntToStr(Error));
        ConnectBitBtn.Caption := '&Connect';
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This event handler is called when the session with the chat server is     }
{ closed either because we closed it, or the server closed it.              }
procedure TChatClientForm.AppSrvClientSessionClosed(
    Sender: TObject;
    Error: Word);
begin
    Display('You have been disconnected from the chat server.');
    ConnectBitBtn.Caption := '&Connect';
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This procedure will start our server part. The chat client must have a    }
{ server part because he needs to receive messages from the others. If we   }
{ don't setup a server, we should poll the chat server to know if we        }
{ received any message. This is not possible with many user ! Using our own }
{ server in the chat client, we can receive messages from the others        }
{ without doing anything special.                                           }
{ The problem here is that we wants to be able to run several instances of  }
{ chat client on the same computer. Each instance will have his own server  }
{ Therefore we cannot use a fixed port for the server. We will try ports    }
{ in sequence until we find some unused one.                                }
procedure TChatClientForm.StartServer;
var
    Ok  : Boolean;
    Cnt : Integer;
begin
    FPort := 2122;           { We will start scanning port with this value  }
    Cnt   := 0;              { We will count to be sure to not loop forever }
    Ok    := FALSE;
    { We will loop until we are successful or get any error other than      }
    { "address already in use". We also stop after 100 ports.               }
    while not Ok do begin
        try
            Inc(Cnt);
            AppServer.Port := IntToStr(FPort);
            AppServer.Start;
            Ok := TRUE;
        except
            on E:ESocketException do begin
                if Cnt > 100 then
                    raise Exception.Create('Can''t start server: ' + E.Message);
                if WSAGetLastError <> WSAEADDRINUSE then
                    raise;
                Inc(FPort);
            end;
        end;
    end;

    { Initialize RequestBroker object }
    RequestBroker.IniFileName := FIniFileName;
    RequestBroker.AddServerObject(TServerObjectMESSAGETO);

    { Create the user data and pass it to the RequestBroker }
    FUserData              := TUserData.Create;
    FUserData.OnDisplay    := AppServerDisplay;
    RequestBroker.UserData := LongInt(FUserData);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TUserData.TriggerDisplay(Msg : String);
begin
    if Assigned(FOnDisplay) then
        FOnDisplay(Self, Msg);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This is a TServerObject for our server part. It is intened to receive a   }
{ single message from another user and to display it.                       }
procedure TServerObjectMESSAGETO.Execute;
var
    UData      : TUserData;
    FromName   : String;
    ToName     : String;
    Data       : TMemoryStream;
    FldType    : TMWFieldType;
    DataBuffer : TStringList;
    I          : Integer;
begin
    try
        { First field is the destination user name, it should be our name }
        ToName     := FRequestBuffer.Fields[0];
        { The second field is the sender username }
        FromName   := FRequestBuffer.Fields[1];

        { The third field is the message body as a blob. The blob was made }
        { by write a TStrings into a TSream and sending the TSream as a    }
        { single blob field. We reverse this process here. We will create  }
        { a TStrings (TStringList) and a TStream (TMemoryStream), fill the }
        { stream with the blob field and fill the TStrings with the stream }
        { We use try/finally and try/except to be sure to free the object  }
        { in the case something goes wrong to avoid memory leaks.          }
        DataBuffer := TStringList.Create;
        try
            Data := TMemoryStream.Create;
            try
                FRequestBuffer.GetStreamField(2, Data, FldType);
                Data.Seek(0,0);
                DataBuffer.LoadFromStream(Data);
            finally
                Data.Free;
            end;

            { Call the display procedure in UserData for each line }
            UData := TUserData(FUserData);
            for I := 0 to DataBuffer.Count - 1 do
                UData.TriggerDisplay(FromName + '> ' + DataBuffer.Strings[I]);

            { Send an ok response to the sender }
            FResponseBuffer.WriteFields(TRUE, ['Ok']);
            FResultStatus := 200;
        finally
            DataBuffer.Free;
        end;
    except
        on E:Exception do begin
            FResponseBuffer.WriteFields(TRUE, [E.Message]);
            FResultStatus := 401;
        end;
    end;
    Finish;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}

end.


