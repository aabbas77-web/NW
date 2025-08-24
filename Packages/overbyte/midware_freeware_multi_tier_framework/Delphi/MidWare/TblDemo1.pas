{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Author:       François PIETTE
Description:  Client sample.
              Work with SrvTst, the corresponding server application.
              Show how to retreive and update data.
Creation:     Dec 30, 1998
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

Updates:
Sep 15, 2001 V1.01 Removed PrmProp from uses clause to avoid missing file
             with Delphi 6 (proxies.dcu).

{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
unit TblDemo1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, Grids, DBGrids, Db, RFormat, ApsCli, MwDatSet,
  IniFiles, StdCtrls, WSocket;

const
  TblDemoVersion = 100;

type
  TTblDemoForm = class(TForm)
    ReqAppSrvClient: TAppSrvClient;
    ReqMWBuffer: TMWBuffer;
    DataSource: TDataSource;
    DBGrid: TDBGrid;
    Panel1: TPanel;
    RequestButton: TButton;
    MWTable: TMWTable;
    DebugPrmPropButton: TButton;
    EditButton: TButton;
    UpdAppSrvClient: TAppSrvClient;
    UpdMWBuffer: TMWBuffer;
    procedure RequestButtonClick(Sender: TObject);
{$IFDEF NEVER}
    procedure DebugPrmPropButtonClick(Sender: TObject);
{$ENDIF}
    procedure EditButtonClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
  private
    FInitialized   : Boolean;
    FIniFileName   : String;
    FRequestError  : integer;
    function  CreateEditForm(Table : TDataSet; Init : Boolean) : TForm;
    procedure SetClientRequestDone(Sender: TObject; Error: Integer);
  public
    { Déclarations publiques }
  end;

var
  TblDemoForm: TTblDemoForm;

implementation

{$R *.DFM}
const
    SectionWindow = 'Window';
    KeyTop        = 'Top';
    KeyLeft       = 'Left';
    KeyWidth      = 'Width';
    KeyHeight     = 'Height';


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTblDemoForm.FormCreate(Sender: TObject);
begin
    FIniFileName := LowerCase(ExtractFileName(Application.ExeName));
    FIniFileName := Copy(FIniFileName, 1, Length(FIniFileName) - 3) + 'ini';
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTblDemoForm.FormShow(Sender: TObject);
var
    IniFile : TIniFile;
begin
    if not FInitialized then begin
        FInitialized        := TRUE;
        IniFile := TIniFile.Create(FIniFileName);
        Width   := IniFile.ReadInteger(SectionWindow, KeyWidth,  Width);
        Height  := IniFile.ReadInteger(SectionWindow, KeyHeight, Height);
        Top     := IniFile.ReadInteger(SectionWindow, KeyTop,    (Screen.Height - Height) div 2);
        Left    := IniFile.ReadInteger(SectionWindow, KeyLeft,   (Screen.Width - Width) div 2);
        IniFile.Free;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTblDemoForm.FormClose(Sender: TObject;
  var Action: TCloseAction);
var
    IniFile : TIniFile;
begin
    IniFile := TIniFile.Create(FIniFileName);
    IniFile.WriteInteger(SectionWindow, KeyTop,    Top);
    IniFile.WriteInteger(SectionWindow, KeyLeft,   Left);
    IniFile.WriteInteger(SectionWindow, KeyWidth,  Width);
    IniFile.WriteInteger(SectionWindow, KeyHeight, Height);
    IniFile.Free;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTblDemoForm.RequestButtonClick(Sender: TObject);
begin
    MWTable.DesignTimeRequest;
    MWTable.Active := TRUE;
    ActiveControl  := DBGrid;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
// This handler is for debugging PrmProp property editor. You can ignore it...
{$IFDEF NEVER}
procedure TTblDemoForm.DebugPrmPropButtonClick(Sender: TObject);
var
    Form : TRequestParamsEditForm;
begin
    Form := TRequestParamsEditForm.Create(nil);
    try
        Form.ParamsText := '"abc", "def",  "ghi" ;  "123","456"';
        Caption         := Form.ParamsText;
        if Form.ShowModal = mrOk then
            Caption := Form.ParamsText;
    finally
        Form.Free;
    end;
end;
{$ENDIF}


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
// Just for fun, dynamically build a complete form with TEdit for each
// field in a table. TEdit are named 'Edit' with fieldname appended.
// There is an OK and a CANCEL button. The form is centered on screen.
// TEdit are filled with current record values if the Init argument is TRUE.
// Of course, you could use a classical form designed with Delphi.
function TTblDemoForm.CreateEditForm(Table : TDataSet; Init : Boolean) : TForm;
var
    Fld      : Integer;
    Edit     : TEdit;
    Lbl      : TLabel;
    Btn      : TButton;
    LblSize  : Integer;
    MaxWidth : Integer;
begin
    Result := TForm.Create(nil);
    try
        LblSize  := Canvas.TextWidth('ABCDEFGHIJ');
        MaxWidth := 0;
        Edit     := nil;   // Makes compiler happy about initialization
        for Fld := 0 to Table.FieldCount - 1 do begin
            Edit           := TEdit.Create(Result);
            Edit.Parent    := Result;
            Edit.Top       := 16 + Fld * (Edit.Height + 4);
            Edit.Left      := 16 + LblSize + 4;
            Edit.Width     := (Table.Fields[Fld].DisplayWidth + 1) * (LblSize div 10);
            Edit.MaxLength := Table.Fields[Fld].DisplayWidth;
            Edit.Name      := 'Edit' + Table.Fields[Fld].DisplayLabel;
            if Init then
                Edit.Text  := Table.Fields[Fld].DisplayText
            else
                Edit.Text  := '';
            if Edit.Width > MaxWidth then
                 MaxWidth := Edit.Width;
            Lbl            := TLabel.Create(Result);
            Lbl.Parent     := Result;
            Lbl.Caption    := Table.Fields[Fld].DisplayLabel;
            Lbl.Left       := Edit.Left - 4 - Canvas.TextWidth(Lbl.Caption);
            Lbl.Top        := Edit.Top + (Edit.Height - Lbl.height) div 2;
        end;
        Result.Width := Edit.Left + MaxWidth + 16 +
                        (Result.Width - Result.ClientWidth);
        // Create OK button
        Btn             := TButton.Create(Result);
        Btn.Parent      := Result;
        Btn.Caption     := '&OK';
        Btn.Default     := TRUE;
        Btn.ModalResult := mrOk;
        Btn.Left        := (Result.ClientWidth - 2 * Btn.Width - 4) div 2;
        Btn.Top         := Edit.Top + Edit.Height + 8;
        // Create CANCEL button
        Btn             := TButton.Create(Result);
        Btn.Parent      := Result;
        Btn.Caption     := '&Cancel';
        Btn.Cancel      := TRUE;
        Btn.ModalResult := mrCancel;
        Btn.Left        := ((Result.ClientWidth - 2 * Btn.Width - 4) div 2) + Btn.Width + 4;
        Btn.Top         := Edit.Top + Edit.Height + 8;
        // Set the Form height
        Result.Height := Btn.Top + Btn.Height + 16 +
                         (Result.Height - Result.ClientHeight);
        // Center the form on screen
        Result.Top := (Screen.Height - Result.Height) div 2;
        Result.Left := (Screen.Width - Result.Width) div 2;
    except
        Result.Free;
        Result := nil;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
// In this handler, we use a sperate TAppSrvClient object to send the update
// to the application server. If the application server accept our data, we
// will update our local copy. This is faster than requesting data again.
procedure TTblDemoForm.EditButtonClick(Sender: TObject);
var
    Form     : TForm;
    Edit     : TEdit;
    Key      : String;
begin
    if MWTable.FieldCount <= 0 then begin
        // No data, try to request data
        RequestButtonClick(Self);
        Exit;
    end;

    // Save the primary key for the current record (we allow to change
    // primary key)
    Key  := MWTable.FieldByName('LAST').AsString;
    // Prevent user from reentering this handler
    EditButton.Enabled := FALSE;
    // Create a TForm to edit data, fill it with current record data
    Form := CreateEditForm(MWTable, TRUE);
    try    // To protect against memory leaks
        Form.Caption := Caption + ' - Edit data';
        // Let user input data.
        if Form.ShowModal <> mrOk then
            Exit;
        // Clear the request buffer
        UpdAppSrvClient.Request.Rewrite;
        // First data field in request is primary key
        UpdAppSrvClient.Request.AppendFields([Key]);
        // Copy all field data from the Edit form to the request buffer
        Edit := Form.FindComponent('EditLast') as TEdit;
        UpdAppSrvClient.Request.AppendFields([Edit.Text]);
        Edit := Form.FindComponent('EditFirst') as TEdit;
        UpdAppSrvClient.Request.AppendFields([Edit.Text]);
        Edit := Form.FindComponent('EditStreet') as TEdit;
        UpdAppSrvClient.Request.AppendFields([Edit.Text]);
        Edit := Form.FindComponent('EditZip') as TEdit;
        UpdAppSrvClient.Request.AppendFields([Edit.Text]);
        Edit := Form.FindComponent('EditCity') as TEdit;
        UpdAppSrvClient.Request.AppendFields([Edit.Text]);
        Edit := Form.FindComponent('EditBirthday') as TEdit;
        // We need to convert date to MWFormat to be country independant
        UpdAppSrvClient.Request.AppendFields([DateTimeToMWFormat(StrToDateTime(Edit.Text))]);
        // Function code to update data at server side
        UpdAppSrvClient.FunctionCode := 'SETCLIENT';
        // Set the event handler to be executed when request done
        UpdAppSrvClient.OnrequestDone := SetClientRequestDone;
        // Send the request
        try
            UpdAppSrvClient.Send;
        except
            on E:Exception do begin
                MessageBeep(MB_OK);
                Application.MessageBox(
                    PChar('Exception occured: ' + E.ClassName + ' ' + E.Message),
                    'Warning', MB_OK);
                Exit;
            end;
        end;
        // The request is asynchonous. We must wait until it is done
        while UpdAppSrvClient.State <> cstReady do begin
             Application.ProcessMessages;
             Sleep(0);
        end;
        // Check for error during request (for example dead server)
        if FRequestError <> 0 then begin
            MessageBeep(MB_OK);
            Application.MessageBox(PChar('Request failed. Error #' +
                                         IntToStr(FRequestError)),
                                   'Warning', MB_OK);
            Exit;
        end;
        // Check if all right (answer is '200' if ok)
        if UpdAppSrvClient.AnswerStatus <> '200' then begin
            MessageBeep(MB_OK);
            Application.MessageBox(PChar('Server rejected our data. Answer was: ''' +
                                   UpdAppSrvClient.AnswerStatus + ''' (' +
                                   UpdAppSrvClient.Answer.RecordToString + ')'),
                                   'Warning', MB_OK);
            Exit;
        end;
        // Server has accepted data. Update our local copy.
        MWTable.Edit;
        Edit := Form.FindComponent('EditLast') as TEdit;
        MWTable.FieldByName('LAST').AsString := Edit.Text;
        Edit := Form.FindComponent('EditFirst') as TEdit;
        MWTable.FieldByName('FIRST').AsString := Edit.Text;
        Edit := Form.FindComponent('EditStreet') as TEdit;
        MWTable.FieldByName('STREET').AsString := Edit.Text;
        Edit := Form.FindComponent('EditZip') as TEdit;
        MWTable.FieldByName('ZIP').AsString := Edit.Text;
        Edit := Form.FindComponent('EditCity') as TEdit;
        MWTable.FieldByName('CITY').AsString := Edit.Text;
        Edit := Form.FindComponent('EditBirthday') as TEdit;
        MWTable.FieldByName('BIRTHDAY').AsString := Edit.Text;
        MWTable.Post;
    finally
        EditButton.Enabled := TRUE;
        ActiveControl      := DBGrid;
        Form.Free;
        UpdAppSrvClient.Close;   // Disconnect from app server
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTblDemoForm.SetClientRequestDone(Sender: TObject;
  Error: Integer);
begin
    FRequestError := Error;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}

end.


