{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Author:       François PIETTE
Description:  Client application.
              Shows how to use a DBGrid and DBNavigator.
              Using the object inspector, the following links are established:
              DataSource1.DataSet     := MWTable1;
              DBGrid1.DataSource      := DataSource1;
              DBNavigator1.DataSource := DataSource1;
              MWTable1.Data           := MWBuffer1;
              AppSrvClient1.Answer    := MWBuffer1;
Creation:     March 20, 1998
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
Jun 01, 1998 V1.01 Removed beta status. Changed "legal stuff" to prohibe
             commercial applications whithout an agreement.

 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
unit TblTst1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ApsCli, Db, MwDatSet, RFormat, StdCtrls, DBCtrls, Grids, DBGrids,
  ExtCtrls, ComCtrls, {LOProp, } Mask, DBTables;

type
  TTblTstForm = class(TForm)
    Panel1: TPanel;
    DBGrid1: TDBGrid;
    DBNavigator1: TDBNavigator;
    KeyEdit: TEdit;
    RequestButton: TButton;
    MWBuffer1: TMWBuffer;
    MWTable1: TMWTable;
    DataSource1: TDataSource;
    AppSrvClient1: TAppSrvClient;
    StatusBar1: TStatusBar;
    DBEdit1: TDBEdit;
    Panel2: TPanel;
    DBMemo1: TDBMemo;
    SaveToFileButton: TButton;
    LoadFromFileButton: TButton;
    ListBox1: TListBox;
    procedure RequestButtonClick(Sender: TObject);
    procedure AppSrvClient1RequestDone(Sender: TObject; Error: Integer);
    procedure FormShow(Sender: TObject);
    procedure AppSrvClient1SessionConnected(Sender: TObject; Error: Word);
    procedure AppSrvClient1SessionClosed(Sender: TObject; Error: Word);
    procedure SaveToFileButtonClick(Sender: TObject);
    procedure LoadFromFileButtonClick(Sender: TObject);
    procedure DataSource1DataChange(Sender: TObject; Field: TField);
  private
    { Déclarations privées }
  public
    { Déclarations publiques }
  end;

var
  TblTstForm: TTblTstForm;

implementation

{$R *.DFM}

{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTblTstForm.RequestButtonClick(Sender: TObject);
var
    Key : String;
begin
    Key := KeyEdit.Text;
    AppSrvClient1.Request.Rewrite;
    AppSrvClient1.Request.WriteFields(TRUE, [Key]);
    AppSrvClient1.Send;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTblTstForm.AppSrvClient1RequestDone(Sender: TObject; Error: Integer);
begin
    if (Error <> 0) or (AppSrvClient1.AnswerStatus <> '200') then begin
        MessageBeep(MB_OK);
        StatusBar1.Panels[2].Text := 'Failed: ' + MWBuffer1.RecordToString;
        MWBuffer1.Rewrite;
    end
    else
        StatusBar1.Panels[2].Text := IntToStr(MWBuffer1.RecordCount) +
                                     ' record(s)';
    { Refresh is not implemented, close/open does the trick }
    try
        MWTable1.Close;
        MWTable1.Open;
    except
        on E:Exception do
            Application.ShowException(E);
    end;
    ActiveControl := DBGrid1;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTblTstForm.FormShow(Sender: TObject);
begin
    StatusBar1.Panels[0].Text := AppSrvClient1.Server + ':' +
                                 AppSrvClient1.Port;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTblTstForm.AppSrvClient1SessionConnected(Sender: TObject;
  Error: Word);
begin
    if Error = 0 then
        StatusBar1.Panels[1].Text := 'Connected'
    else
        StatusBar1.Panels[1].Text := 'Can''t connect, error #' + IntToStr(Error);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTblTstForm.AppSrvClient1SessionClosed(Sender: TObject;
  Error: Word);
begin
    StatusBar1.Panels[1].Text := 'Not connected';
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This procedure is used to debug the LayoutProperty editor.                }
{$IFDEF NEVER}
procedure TTblTstForm.Button1Click(Sender: TObject);
var
    Form : TLayoutEditForm;
begin
    Form := TLayoutEditForm.Create(nil);
    try
        Form.LayoutText := 'First;C;15;Last;C;20;Zip;N;4';
        Caption         := Form.LayoutText;
        if Form.ShowModal = mrOk then
            Caption := Form.LayoutText;
    finally
        Form.Free;
    end;
end;
{$ENDIF}


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTblTstForm.SaveToFileButtonClick(Sender: TObject);
begin
    MWBuffer1.SaveToFile('TblTst.dat');
    ActiveControl := DBGrid1;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTblTstForm.LoadFromFileButtonClick(Sender: TObject);
begin
    MWTable1.Close;
    MWBuffer1.LoadFromFile('TblTst.dat');
    MWTable1.Open;
    ActiveControl := DBGrid1;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTblTstForm.DataSource1DataChange(Sender: TObject;
  Field: TField);
const
    Cnt : Integer = 0;
begin
    Inc(Cnt);
    if Field <> nil then
        ListBox1.Items.Add(Field.FieldName + ' ' + IntToStr(Cnt))
    else
        ListBox1.Items.Add('Datachange ' + IntToStr(Cnt));
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}

end.

