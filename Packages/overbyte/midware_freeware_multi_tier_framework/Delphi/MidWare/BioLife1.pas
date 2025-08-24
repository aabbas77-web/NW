{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Author:       François PIETTE
Description:  This program is a demonstration for graphic field use with
              MidWare. It works as a client for the SrvDemo program. A SQL
              request is sent to SrvDemo to retrieve fish info from the
              demo database BIOLIFE (from Inprise sample data). You must
              copy biolife.db, biolife.mb, biolife.px from delphi\demos\data
              to the directory where SrvDemo is (internet\midware).
EMail:        francois.piette@overbyte.be   francois.piette@rtfm.be
              http://www.overbyte.be        http://www.rtfm.be/fpiette
              francois.piette@pophost.eunet.be
Creation:     Augustus 19, 1998
Version:      1.02
Support:      Use the mailing list midware@elists.org
              Follow "support" link at http://www.overbyte.be for subscription.
Legal issues: Copyright (C) 1997-2001 by François PIETTE
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
Aug 24, 1998 V1.01 Added a TMemo with field NOTES, a splitter bar and a status
             bar. Added an edit box to enter the where clause
Sep 15, 2001 V1.02 Removed PrmProp from uses clause because it causes missing
             file with Delphi 6 (proxies.dcu).


* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
unit BioLife1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  DBCtrls, Db, ExtCtrls, RFormat, MwDatSet, ApsCli, StdCtrls,
  ComCtrls, Mask;

const
  ProgVersion = 102;
  CopyRight   = ' BioLife MidWare sample. (c)1998-2001 by François PIETTE. V1.02 ';

type
  TBioLifeForm = class(TForm)
    AppSrvClient1: TAppSrvClient;
    MWTable1: TMWTable;
    MWBuffer1: TMWBuffer;
    Panel1: TPanel;
    DBNavigator1: TDBNavigator;
    DataSource1: TDataSource;
    LeftPanel: TPanel;
    RightPanel: TPanel;
    DBImage1: TDBImage;
    RequestButton: TButton;
    MWTable1GRAPHIC: TGraphicField;
    MWTable1COMMONNAME: TStringField;
    MWTable1NOTES: TMemoField;
    DBMemo1: TDBMemo;
    Panel4: TPanel;
    DBText1: TDBText;
    Splitter1: TSplitter;
    Panel2: TPanel;
    Label1: TLabel;
    WhereEdit: TEdit;
    StatusBar1: TStatusBar;
    Button1: TButton;
    Image1: TImage;
    DBEdit1: TDBEdit;
    MWTable1LENGTH_IN: TFloatField;
    procedure RequestButtonClick(Sender: TObject);
    procedure MWTable1RequestDone(Sender: TObject; Error: Integer);
    procedure Button1Click(Sender: TObject);
  end;

var
  BioLifeForm: TBioLifeForm;

implementation

{$R *.DFM}

{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function DoubleQuote(Value : String) : String;
var
    I : Integer;
begin
    Result := '';
    for I := 1 to Length(Value) do begin
        if Value[I] = '''' then
            Result := Result + ''''''
        else
            Result := Result + Value[I];
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TBioLifeForm.RequestButtonClick(Sender: TObject);
var
    Params : String;
begin
    MWTable1.Close;
    Params := 'select Common_Name, Notes, Graphic, Length_in from biolife';
    if Trim(WhereEdit.Text) > '' then
        Params := Params + ' where ' + WhereEdit.Text;
    StatusBar1.Panels[0].Text := '';
    StatusBar1.Panels[1].Text := Params;
    MWTable1.Params := '''' + DoubleQuote(Params) + '''';
    MWTable1.ExecuteRequest;
    RequestButton.Enabled := FALSE;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TBioLifeForm.MWTable1RequestDone(Sender: TObject; Error: Integer);
begin
    RequestButton.Enabled := TRUE;
    if Error <> 0 then begin
        StatusBar1.Panels[0].Text := IntToStr(Error);
        Application.MessageBox(PChar('Error #'+ IntToStr(Error)), 'Warning', MB_OK);
        Exit;
    end;

    if MWTable1.AppSrvClient.AnswerStatus = '200' then begin
        // Table is automatically opened
        StatusBar1.Panels[0].Text := IntToStr(MWTable1.Data.RecordCount);
        Exit;
    end;

    Application.MessageBox(PChar('Unable to get data from server'+ #10 +
                                 'Server report error message:' + #10#10+
                                 MWTable1.Data.RecordToString), 'Warning', MB_OK);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TBioLifeForm.Button1Click(Sender: TObject);
var
    BlobField : TBlobField;
begin
    MWTable1.Active := TRUE;
    MWTable1.Edit;
    BlobField := MWTable1.FieldByName('GRAPHIC') as TBlobField;
    // WriteLn('Assign');
    BlobField.Assign(Image1.Picture);
    // WriteLn('Post');
    MWTable1.Post;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}

end.
