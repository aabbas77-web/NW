object FormAddNewPhrase: TFormAddNewPhrase
  Left = 189
  Top = 105
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Translate Phrase'
  ClientHeight = 131
  ClientWidth = 379
  Color = 15132390
  Font.Charset = ARABIC_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 14
  object Panel1: TPanel
    Left = 0
    Top = 90
    Width = 379
    Height = 41
    Align = alBottom
    Color = 15132390
    TabOrder = 0
    object BitBtn1: TBitBtn
      Left = 114
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 0
      Kind = bkOK
    end
    object BitBtn2: TBitBtn
      Left = 190
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 1
      Kind = bkCancel
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 379
    Height = 90
    Align = alClient
    Color = 15132390
    TabOrder = 1
    object Label1: TLabel
      Left = 9
      Top = 44
      Width = 361
      Height = 14
      AutoSize = False
      Caption = 'Translation'
    end
    object EditTranslation: TEdit
      Left = 9
      Top = 60
      Width = 361
      Height = 22
      BiDiMode = bdRightToLeft
      ParentBiDiMode = False
      TabOrder = 0
    end
    object PanelPhrase: TPanel
      Left = 9
      Top = 8
      Width = 361
      Height = 25
      Alignment = taLeftJustify
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Color = 15132390
      TabOrder = 1
    end
  end
  object FormTranslation1: TFormTranslation
    Left = 288
    Top = 96
  end
end
