object FormWatch: TFormWatch
  Left = 190
  Top = 148
  BiDiMode = bdLeftToRight
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Watching report'
  ClientHeight = 315
  ClientWidth = 392
  Color = 15132390
  Font.Charset = ARABIC_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  ParentBiDiMode = False
  Position = poScreenCenter
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 274
    Width = 392
    Height = 41
    Align = alBottom
    Color = 15132390
    TabOrder = 0
    object BitBtn2: TBitBtn
      Left = 159
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Close'
      TabOrder = 0
      OnKeyDown = FormKeyDown
      Kind = bkClose
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 392
    Height = 274
    Align = alClient
    Color = 15132390
    TabOrder = 1
    object Splitter1: TSplitter
      Left = 1
      Top = 135
      Width = 390
      Height = 3
      Cursor = crVSplit
      Align = alTop
      Color = clNavy
      ParentColor = False
    end
    object GroupBox1: TGroupBox
      Left = 1
      Top = 1
      Width = 390
      Height = 134
      Align = alTop
      Caption = 'Text'
      TabOrder = 0
      object RichEdit: TRichEdit
        Left = 2
        Top = 15
        Width = 386
        Height = 117
        Align = alClient
        Color = 16770764
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
        OnKeyDown = FormKeyDown
      end
      object BitBtn3: TBitBtn
        Left = 296
        Top = 92
        Width = 75
        Height = 25
        Caption = 'Save'
        TabOrder = 1
        OnClick = BitBtn3Click
        OnKeyDown = FormKeyDown
      end
    end
    object GroupBox2: TGroupBox
      Left = 1
      Top = 138
      Width = 390
      Height = 135
      Align = alClient
      Caption = 'Image'
      TabOrder = 1
      object ScrollBox1: TScrollBox
        Left = 2
        Top = 15
        Width = 386
        Height = 118
        HorzScrollBar.Tracking = True
        VertScrollBar.Tracking = True
        Align = alClient
        TabOrder = 1
        object Image: TImage
          Left = 0
          Top = 0
          Width = 1024
          Height = 768
        end
      end
      object BitBtn4: TBitBtn
        Left = 292
        Top = 88
        Width = 75
        Height = 25
        Caption = 'Save'
        TabOrder = 0
        OnClick = BitBtn4Click
        OnKeyDown = FormKeyDown
      end
    end
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'rtf'
    Filter = 'Rich Text Format (*.rtf)|*.rtf|All Files (*.*)|*.*'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 156
    Top = 68
  end
  object SavePictureDialog1: TSavePictureDialog
    DefaultExt = 'jpg'
    Filter = 
      'All (*.jpg;*.bmp)|*.jpg;*.bmp|JPEG Image File (*.jpg)|*.jpg|Bitm' +
      'aps (*.bmp)|*.bmp'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 152
    Top = 200
  end
  object FormTranslation1: TFormTranslation
    Left = 96
    Top = 64
  end
end
