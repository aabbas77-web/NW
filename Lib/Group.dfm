object FormGroup: TFormGroup
  Left = 190
  Top = 450
  BiDiMode = bdLeftToRight
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Group'
  ClientHeight = 91
  ClientWidth = 264
  Color = 15132390
  Font.Charset = ARABIC_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  ParentBiDiMode = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 54
    Width = 264
    Height = 37
    Align = alBottom
    Color = 15132390
    TabOrder = 0
    object BitBtn1: TBitBtn
      Left = 135
      Top = 6
      Width = 75
      Height = 25
      TabOrder = 0
      Kind = bkCancel
    end
    object BitBtn2: TBitBtn
      Left = 55
      Top = 6
      Width = 75
      Height = 25
      Caption = 'Ok'
      TabOrder = 1
      Kind = bkOK
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 264
    Height = 54
    Align = alClient
    Color = 15132390
    TabOrder = 1
    object Label: TLabel
      Left = 8
      Top = 8
      Width = 249
      Height = 13
      AutoSize = False
      Caption = 'Group name'
    end
    object DBLookupComboBox1: TDBLookupComboBox
      Left = 7
      Top = 26
      Width = 249
      Height = 21
      KeyField = 'Group_ID'
      ListField = 'Group_Name'
      ListSource = DM.DataSourceGroups
      TabOrder = 0
    end
  end
  object FormTranslation1: TFormTranslation
    Left = 135
    Top = 4
  end
end
