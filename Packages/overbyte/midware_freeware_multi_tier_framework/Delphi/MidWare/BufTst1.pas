{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Author:       François PIETTE
Description:  Sample to show how to use TMWBuffer
              (F. Piette's Middleware (MidWare))
Creation:     March 14, 1998
Version:      1.00
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
May 16, 1998 Added a TMWTable on the form to make the sample program more
             realistic (the TMWTable was dynamically created).

 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
unit BufTst1;

interface

uses
  WinTypes, WinProcs, Messages, SysUtils, Classes, Graphics, Controls, Forms,
  Dialogs, RFormat, StdCtrls, ExtCtrls, Db, DBTables, Grids, DBGrids,
  MwDatSet, DBCtrls;

{ If the symbol TABLE is defined, the program will use a TTable as data source }
{ else, it will use a MWBuffer. This will demonstrate the polymorphism and     }
{ similar behaviour between a TTable and a TMWBuffer.                          }
{ To define/undefine the symbol TABLE, add or remove the '$' sign after the    }
{ open brace on the next line                                                  }
{DEFINE TABLE}

type
  TBufTstForm = class(TForm)
    Panel1: TPanel;
    Memo1: TMemo;
    PriorButton: TButton;
    Label1: TLabel;
    NextButton: TButton;
    EofCheckBox: TCheckBox;
    BofCheckBox: TCheckBox;
    FirstButton: TButton;
    LastButton: TButton;
    DeleteButton: TButton;
    CreateButton: TButton;
    Table1: TTable;
    DBGrid1: TDBGrid;
    MWBuffer1: TMWBuffer;
    DataSource1: TDataSource;
    MWTable1: TMWTable;
    DBNavigator1: TDBNavigator;
    Button1: TButton;
    Button2: TButton;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure PriorButtonClick(Sender: TObject);
    procedure NextButtonClick(Sender: TObject);
    procedure FirstButtonClick(Sender: TObject);
    procedure LastButtonClick(Sender: TObject);
    procedure DeleteButtonClick(Sender: TObject);
    procedure CreateButtonClick(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    FInitialized : Boolean;
{$IFDEF TABLE}
    FData        : TTable;
{$ELSE}
    FData        : TMWBuffer;
{$ENDIF}
    FSize        : Integer;
    FBuffer      : PChar;
    procedure CreateData;
    procedure DisplayData;
    procedure ShowCurrent;
    function  Field(nIndex : Integer) : String;
    function  Info : String;
  public
    { Déclarations publiques }
  end;

var
  BufTstForm: TBufTstForm;

implementation

{$R *.DFM}


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TBufTstForm.FormCreate(Sender: TObject);
begin
    FSize := 100;
    GetMem(FBuffer, FSize);
{$IFDEF TABLE}
    FData                 := Table1;
    DataSource1.DataSet   := Table1;
{$ELSE}
    FData                 := MWBuffer1;
    DataSource1.DataSet   := MWTable1;
{$ENDIF}
    CreateData;
    DataSource1.DataSet.Active := TRUE;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TBufTstForm.FormShow(Sender: TObject);
begin
    if not FInitialized then begin
        FInitialized := TRUE;
{$IFDEF TABLE}
        FData.Open;
{$ENDIF}
        DisplayData;
        FData.First;
        ShowCurrent;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TBufTstForm.FormDestroy(Sender: TObject);
begin
    FreeMem(FBuffer, FSize);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TBufTstForm.CreateData;
var
    Test : String[20];
begin
{$IFNDEF TABLE}
    FData.Rewrite;
    Test := 'JULES';
    FData.WriteFields(TRUE, [Test,        'CAESAR']);
    FData.WriteFields(TRUE, ['ASTERIX',   'LE GAULOIS']);
    FData.WriteFields(TRUE, ['CAPITAINE', 'HADDOCK']);
    FData.WriteFields(TRUE, ['RIC',       'HOCHET']);
    FData.First;
{$ENDIF}
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TBufTstForm.Field(nIndex : Integer) : String;
begin
{$IFDEF TABLE}
    Result := FData.Fields[nIndex].AsString;
{$ELSE}
    Result := FData.Fields[nIndex];
{$ENDIF}
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TBufTstForm.Info : String;
begin
{$IFDEF TABLE}
    Result := '';
{$ELSE}
    Result := ' Size=' + IntToStr(FData.DataBufferSize) +
              ' Count=' + IntToStr(FData.DataBufferCount) +
              ' Tell=' + IntToStr(FData.Tell);
{$ENDIF}
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TBufTstForm.DisplayData;
var
    Bookmark : TBookmark;
begin
    Memo1.Clear;
{$IFDEF TABLE}
    Memo1.Lines.Add('Using TTable ' + FData.DataBaseName + '\' + FData.TableName);
{$ELSE}
    Memo1.Lines.Add('Using TMWBuffer');
{$ENDIF}
    Memo1.Lines.Add('');

    Bookmark := FData.GetBookmark;
    FData.First;
    while not FData.EOF do begin
        Memo1.Lines.Add('''' + Field(0) + ''', ''' + Field(1) + '''' + Info);
        FData.Next;
    end;
    FData.GotoBookmark(Bookmark);
    FData.FreeBookmark(Bookmark);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TBufTstForm.ShowCurrent;
begin
    Label1.Caption := Field(0) + Info;
    EofCheckBox.Checked := FData.EOF;
    BofCheckBox.Checked := FData.BOF;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TBufTstForm.PriorButtonClick(Sender: TObject);
begin
    FData.Prior;
    ShowCurrent;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TBufTstForm.NextButtonClick(Sender: TObject);
begin
    FData.Next;
    ShowCurrent;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TBufTstForm.FirstButtonClick(Sender: TObject);
begin
    FData.First;
    ShowCurrent;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TBufTstForm.LastButtonClick(Sender: TObject);
begin
    FData.Last;
    ShowCurrent;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TBufTstForm.DeleteButtonClick(Sender: TObject);
begin
    FData.Delete;
    ShowCurrent;
    DisplayData;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TBufTstForm.CreateButtonClick(Sender: TObject);
begin
    CreateData;
    DisplayData;
    ShowCurrent;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}

procedure TBufTstForm.Button1Click(Sender: TObject);
begin
    MWTable1.Append;
    MWTable1.FieldByName('FIRST').AsString := 'Toto';
    MWTable1.Post;
    DisplayData;
end;

procedure TBufTstForm.Button2Click(Sender: TObject);
begin
    DisplayData;
end;

end.

