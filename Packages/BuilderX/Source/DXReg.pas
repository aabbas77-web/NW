unit DXReg;

interface

uses
  Windows, SysUtils, Classes, DsgnIntf, Forms, Dialogs, Graphics, TypInfo,
  DXSounds, Wave, DXClass;

type

  {  TWaveProperty  }

  TWaveProperty = class(TPropertyEditor)
  public
    procedure Edit; override;
    function GetValue: string; override;
    function GetAttributes: TPropertyAttributes; override;
  end;

  {  TDXWaveEditor  }

  TDXWaveEditor = class(TComponentEditor)
  public
    procedure Edit; override;
    procedure ExecuteVerb(Index: Integer); override;
    function GetVerb(Index: Integer): string; override;
    function GetVerbCount: Integer; override;
  end;

  {  TDXWaveListEditor  }

  TDXWaveListEditor = class(TComponentEditor)
  public
    procedure ExecuteVerb(Index: Integer); override;
    function GetVerb(Index: Integer): string; override;
    function GetVerbCount: Integer; override;
  end;

procedure Register;

implementation

uses DXWaveEdit;

const
  SNone = '(None)';

  SSettingImage = '&Image...';
  SSettingWave = '&Wave...';
  SDXGFileFilter = 'DXG file(*.dxg)|*.dxg|All files(*.*)|*.*';
  SDXGOpenFileFilter = 'DXG file(*.dxg)|*.dxg|Bitmap file(*.bmp)|*.bmp|All files(*.*)|*.*';
  SDXWFileFilter = 'DXW file(*.dxw)|*.dxg|All files(*.*)|*.*';
  SDXWOpenFileFilter = 'DXW file(*.dxw)|*.dxw|Wave file(*.wav)|*.wav|All files(*.*)|*.*';
  SSinglePlayer = '&Single player';
  SMultiPlayer1 = 'Multi player &1';
  SMultiPlayer2 = 'Multi player &2';

  SOpen = '&Open...';
  SSave = '&Save..';

procedure Register;
begin
  RegisterPropertyEditor(TypeInfo(TWave), nil, '', TWaveProperty);
  RegisterComponentEditor(TCustomDXWave, TDXWaveEditor);

  RegisterComponentEditor(TCustomDXWaveList, TDXWaveListEditor);

  RegisterComponents('BuilderX',
    [TDXSound,
    TDXWave,
    TDXWaveList,
    TDXTimer]);
end;

{  TWaveProperty  }

procedure TWaveProperty.Edit;
var
  Form: TDelphiXWaveEditForm;
begin
  Form := TDelphiXWaveEditForm.Create(nil);
  try
    Form.Wave := TWave(GetOrdValue);
    Form.ShowModal;
    if Form.Tag<>0 then
    begin
      SetOrdValue(Integer(Form.Wave));
      Designer.Modified;
    end;
  finally
    Form.Free;
  end;
end;

function TWaveProperty.GetAttributes: TPropertyAttributes;
begin
  Result := [paDialog, paReadOnly];
end;

function TWaveProperty.GetValue: string;
begin
  if TWave(GetOrdValue).Size=0 then
    Result := SNone
  else
    Result := Format('(%s)', [TObject(GetOrdValue).ClassName]);
end;

{  TDXWaveEditor  }

procedure TDXWaveEditor.Edit;
var
  Form: TDelphiXWaveEditForm;
begin
  Form := TDelphiXWaveEditForm.Create(nil);
  try
    Form.Wave := TCustomDXWave(Component).Wave;
    Form.ShowModal;
    if Form.Tag<>0 then
    begin
      TCustomDXWave(Component).Wave := Form.Wave;
      Designer.Modified;
    end;
  finally
    Form.Free;
  end;
end;

procedure TDXWaveEditor.ExecuteVerb(Index: Integer);
begin
  case Index of
    0: Edit;
  end;
end;

function TDXWaveEditor.GetVerb(Index: Integer): string;
begin
  case Index of
    0: Result := SSettingWave;
  end;
end;

function TDXWaveEditor.GetVerbCount: Integer;
begin
  Result := 1;
end;

{  TDXWaveListEditor  }

procedure TDXWaveListEditor.ExecuteVerb(Index: Integer);
var
  OpenDialog: TOpenDialog;
  SaveDialog: TSaveDialog;
  i: Integer;
begin
  case Index of
    0: begin
         OpenDialog := TOpenDialog.Create(nil);
         try
           OpenDialog.DefaultExt := 'dxw';
           OpenDialog.Filter := SDXWOpenFileFilter;
           OpenDialog.Options := [ofPathMustExist, ofFileMustExist, ofAllowMultiSelect];
           if OpenDialog.Execute then
           begin
             if OpenDialog.FilterIndex=2 then
             begin
               for i:=0 to OpenDialog.Files.Count-1 do
                 with TWaveCollectionItem.Create(TCustomDXWaveList(Component).Items) do
                 begin
                   try
                     Wave.LoadFromFile(OpenDialog.Files[i]);
                     Name := ExtractFileName(OpenDialog.Files[i]);
                   except
                     Free;
                     raise;
                   end;
                 end;
             end else
               TCustomDXWaveList(Component).Items.LoadFromFile(OpenDialog.FileName);
             Designer.Modified;
           end;
         finally
           OpenDialog.Free;
         end;
       end;
    1: begin
         SaveDialog := TSaveDialog.Create(nil);
         try
           SaveDialog.DefaultExt := 'dxw';
           SaveDialog.Filter := SDXWFileFilter;
           SaveDialog.Options := [ofOverwritePrompt, ofPathMustExist];
           if SaveDialog.Execute then
             TCustomDXWaveList(Component).Items.SaveToFile(SaveDialog.FileName);
         finally
           SaveDialog.Free;
         end;
       end;
  end;
end;

function TDXWaveListEditor.GetVerb(Index: Integer): string;
begin
  case Index of
    0: Result := SOpen;
    1: Result := SSave;
  end;
end;

function TDXWaveListEditor.GetVerbCount: Integer;
begin
  Result := 2;
end;

end.
