{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Author:       François PIETTE
Description:  Simple server demo.
Creation:     July 19, 1998
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
Aug 29, 1998 V1.01 Assigned current dir for databsename if missing


 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
unit SrvDemo1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  RBroker, ApServer, StdCtrls, ExtCtrls, SrvObj1, Db, DBTables, SObjSql,
  SObjThrd, Grids, DBGrids;

type
  TSrvDemoForm = class(TForm)
    ToolsPanel: TPanel;
    DisplayMemo: TMemo;
    AppServer1: TAppServer;
    RequestBroker1: TRequestBroker;
    ServerObjectUPPER1: TServerObjectUPPER;
    ClientCountLabel: TLabel;
    ObjectCountLabel: TLabel;
    Label1: TLabel;
    Label2: TLabel;
    ServerObjectSQL1: TServerObjectSQL;
    ServerObjectSQLTHREAD1: TServerObjectSQLTHREAD;
    FunctionsButton: TButton;
    procedure FormCreate(Sender: TObject);
    procedure RequestBroker1Display(Sender: TObject; Msg: String);
    procedure FunctionsButtonClick(Sender: TObject);
  private
    function EnumServerFunctions(Sender: TObject;
                                 FunctionCode : String) : Boolean;
  public
    { Déclarations publiques }
  end;

var
  SrvDemoForm: TSrvDemoForm;

implementation

{$R *.DFM}


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TSrvDemoForm.FormCreate(Sender: TObject);
var
    Buffer : String;
    Len    : Integer;
begin
    SetLength(Buffer, 256);
    Len := GetEnvironmentVariable('TEMP', PChar(Buffer), Length(Buffer));
    if Len <= 0 then begin
        Len := GetEnvironmentVariable('TMP', PChar(Buffer), Length(Buffer));
        if Len <= 0 then begin
            Buffer := 'C:\TEMP';
            Len    := Length(Buffer);
        end;
    end;
    SetLength(Buffer, Len);

    ServerObjectSQLTHREAD1.NetFileDir := Buffer;
    ServerObjectSQLTHREAD1.PrivateDir := Buffer;
    if ServerObjectSQLTHREAD1.DatabaseName = '' then
        ServerObjectSQLTHREAD1.DatabaseName := ExtractFilePath(Application.ExeName);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TSrvDemoForm.RequestBroker1Display(Sender: TObject; Msg: String);
begin
    // Prevent TMemo overflow
    if DisplayMemo.Lines.Count > 200 then
        DisplayMemo.Clear;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This function is called back by the request broker for each function code }
{ he knows about when we ask to enumerate functions.                        }
function TSrvDemoForm.EnumServerFunctions(
    Sender: TObject; FunctionCode : String) : boolean;
begin
    DisplayMemo.Lines.Add(FunctionCode);
    Result := TRUE;   { Continue to enumerate }
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TSrvDemoForm.FunctionsButtonClick(Sender: TObject);
begin
    RequestBroker1.EnumServerFunctions(EnumServerFunctions);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}

end.
