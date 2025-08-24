object FormCopyDialog: TFormCopyDialog
  Left = 190
  Top = 105
  BiDiMode = bdLeftToRight
  BorderStyle = bsDialog
  Caption = 'Copying files'
  ClientHeight = 164
  ClientWidth = 311
  Color = 14145495
  Font.Charset = ARABIC_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  ParentBiDiMode = False
  Position = poDesktopCenter
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object BitBtn1: TBitBtn
    Left = 118
    Top = 132
    Width = 75
    Height = 25
    Caption = 'Finish'
    Default = True
    TabOrder = 0
    OnClick = BitBtn1Click
    OnKeyDown = FormKeyDown
    NumGlyphs = 2
  end
  object Panel1: TPanel
    Left = 5
    Top = 4
    Width = 300
    Height = 64
    BevelInner = bvLowered
    Color = 14145495
    TabOrder = 1
    object Animate: TAnimate
      Left = 2
      Top = 2
      Width = 296
      Height = 60
      Align = alClient
      Active = False
      CommonAVI = aviCopyFile
      StopFrame = 20
    end
  end
  object Panel2: TPanel
    Left = 5
    Top = 72
    Width = 300
    Height = 25
    BevelInner = bvLowered
    BorderWidth = 1
    Color = 14145495
    TabOrder = 2
    object LabelFileName: TLabel
      Left = 3
      Top = 3
      Width = 294
      Height = 19
      Align = alClient
      AutoSize = False
      BiDiMode = bdLeftToRight
      Caption = ' Copying...'
      ParentBiDiMode = False
      Layout = tlCenter
    end
  end
  object Panel3: TPanel
    Left = 5
    Top = 100
    Width = 300
    Height = 25
    BevelInner = bvLowered
    BorderWidth = 1
    Color = 14145495
    TabOrder = 3
    object LabelResult: TLabel
      Left = 3
      Top = 3
      Width = 294
      Height = 19
      Align = alClient
      AutoSize = False
      BiDiMode = bdLeftToRight
      Caption = ' Files: 0'
      ParentBiDiMode = False
      Layout = tlCenter
    end
  end
  object FormTranslation1: TFormTranslation
    Left = 124
    Top = 20
  end
end
