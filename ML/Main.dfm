object FormMain: TFormMain
  Left = 190
  Top = 105
  Width = 834
  Height = 477
  Caption = 'Multi-Language'
  Color = 15132390
  Font.Charset = ARABIC_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 14
  object Panel1: TPanel
    Left = 0
    Top = 46
    Width = 826
    Height = 385
    Align = alClient
    TabOrder = 0
    object Splitter1: TSplitter
      Left = 1
      Top = 181
      Width = 824
      Height = 3
      Cursor = crVSplit
      Align = alTop
      Color = clNavy
      ParentColor = False
    end
    object RichEditSource: TRichEdit
      Left = 1
      Top = 1
      Width = 824
      Height = 180
      Align = alTop
      Font.Charset = ARABIC_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ScrollBars = ssBoth
      ShowHint = False
      TabOrder = 0
      OnChange = RichEditSourceChange
      OnMouseDown = RichEditSourceMouseDown
      OnMouseMove = RichEditSourceMouseMove
      OnMouseUp = RichEditSourceMouseUp
    end
    object RichEditDest: TRichEdit
      Left = 1
      Top = 184
      Width = 824
      Height = 200
      Align = alClient
      Font.Charset = ARABIC_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ScrollBars = ssBoth
      TabOrder = 1
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 28
    Width = 826
    Height = 18
    Align = alTop
    TabOrder = 1
    object ProgressBar1: TProgressBar
      Left = 1
      Top = 1
      Width = 824
      Height = 16
      Align = alTop
      Min = 0
      Max = 100
      TabOrder = 0
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 431
    Width = 826
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object Panel3: TPanel
    Left = 0
    Top = 0
    Width = 826
    Height = 28
    Align = alTop
    TabOrder = 3
    object ToolBar1: TToolBar
      Left = 1
      Top = 1
      Width = 824
      Height = 26
      AutoSize = True
      ButtonWidth = 109
      Caption = 'ToolBar1'
      Color = 15132390
      EdgeBorders = [ebLeft, ebTop, ebRight, ebBottom]
      Flat = True
      ParentColor = False
      ShowCaptions = True
      TabOrder = 0
      object ToolButton2: TToolButton
        Left = 0
        Top = 0
        Action = AAddToDictionary
      end
      object ToolButton1: TToolButton
        Left = 109
        Top = 0
        Action = ATranslate
      end
      object ToolButton3: TToolButton
        Left = 218
        Top = 0
        Action = ADictionary
      end
      object Panel4: TPanel
        Left = 327
        Top = 0
        Width = 45
        Height = 22
        BevelOuter = bvLowered
        Caption = 'From'
        Color = 15132390
        TabOrder = 2
      end
      object ComboBoxSource: TComboBox
        Left = 372
        Top = 0
        Width = 100
        Height = 22
        Style = csDropDownList
        ItemHeight = 14
        TabOrder = 0
        Items.Strings = (
          'English')
      end
      object Panel5: TPanel
        Left = 472
        Top = 0
        Width = 45
        Height = 22
        BevelOuter = bvLowered
        Caption = 'To'
        Color = 15132390
        TabOrder = 3
      end
      object ComboBoxDest: TComboBox
        Left = 517
        Top = 0
        Width = 100
        Height = 22
        Style = csDropDownList
        ItemHeight = 14
        TabOrder = 1
        Items.Strings = (
          'Arabic')
      end
      object CheckBoxRealTime: TCheckBox
        Left = 617
        Top = 0
        Width = 73
        Height = 22
        Caption = 'Real time'
        TabOrder = 4
        OnClick = CheckBoxRealTimeClick
      end
    end
  end
  object PopupMenu: TPopupMenu
    Left = 304
    Top = 320
    object Addtodictionary1: TMenuItem
      Action = AAddToDictionary
    end
  end
  object ActionList1: TActionList
    Left = 332
    Top = 320
    object AAddToDictionary: TAction
      Caption = '&Add to dictionary'
      Enabled = False
      OnExecute = AAddToDictionaryExecute
    end
    object ATranslate: TAction
      Caption = 'Translate'
      Enabled = False
      Hint = 'Translate Selected Text'
      OnExecute = ATranslateExecute
    end
    object ADictionary: TAction
      Caption = 'Dictionary'
      Hint = 'Show Dictionary Window'
      OnExecute = ADictionaryExecute
    end
  end
  object FormTranslation1: TFormTranslation
    Left = 360
    Top = 320
  end
end
