{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Author:       François PIETTE
Description:  Application Server sample for F. Piette's Middleware (MidWare)
              Work with CliTst, the corresponding client application.
Creation:     February 17, 1998
Version:      1.01
EMail:        francois.piette@pophost.eunet.be    
              francois.piette@rtfm.be             http://www.rtfm.be/fpiette
Support:      Use the mailing list midware@rtfm.be See website for details.
Legal issues: Copyright (C) 1998 by François PIETTE
              Rue de Grady 24, 4053 Embourg, Belgium. Fax: +32-4-365.74.56
              <francois.piette@pophost.eunet.be>

              This software is provided 'as-is', without any express or
              implied warranty.  In no event will the author be held liable
              for any  damages arising from the use of this software.

              Permission is granted to anyone to use this software and or any
              derived or altered versions for any purpose, excluding commercial
              applications. You can use this software for personal or internal
              use only. You may distribute it freely untouched.
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
20/03/98 V1.01 Adapted to changes made in TMWBuffer (rformat.pas)
         Added SrvObj4 to show how a TQuery could be used


 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
unit Srv1Tst1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  IniFiles, WSocket, Menus, StdCtrls, ExtCtrls,
  ApSrvCli, RFormat, RBroker, ApServer, Srv1Tst2, SrvObj1;

const
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
    RequestBroker1.IniFileName := FIniFileName;
    RequestBroker1.AddServerObject(TServerObjectUPPER);

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
procedure TServerForm.FormShow(Sender: TObject);
var
    IniFile : TIniFile;
begin
    if not FInitialized then begin
        FInitialized        := TRUE;
        Caption             := 'Starting ' + MainTitle;

        IniFile := TIniFile.Create(FIniFileName);
        Top    := IniFile.ReadInteger(SectionWindow, KeyTop,    Top);
        Left   := IniFile.ReadInteger(SectionWindow, KeyLeft,   Left);
        Width  := IniFile.ReadInteger(SectionWindow, KeyWidth,  Width);
        Height := IniFile.ReadInteger(SectionWindow, KeyHeight, Height);
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

    { Start the application server component }
    AppServer1.Port := FPort;
    AppServer1.Start;
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
    DisplayMemo.Lines.Add(StrPas(CmdBuf));
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

end.

{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}

