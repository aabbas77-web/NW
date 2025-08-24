object FormDictionary: TFormDictionary
  Left = 190
  Top = 126
  Width = 609
  Height = 454
  BorderIcons = [biSystemMenu, biMaximize]
  Caption = 'Dictionary'
  Color = 15132390
  Font.Charset = ARABIC_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 601
    Height = 25
    AutoSize = True
    ButtonHeight = 21
    ButtonWidth = 107
    Caption = 'ToolBar1'
    EdgeBorders = [ebLeft, ebTop, ebRight, ebBottom]
    Flat = True
    ShowCaptions = True
    TabOrder = 0
    object ComboBoxLanguage: TComboBox
      Left = 0
      Top = 0
      Width = 120
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
      OnChange = ComboBoxLanguageChange
      Items.Strings = (
        'English'
        'Arabic')
    end
    object ToolButton1: TToolButton
      Left = 120
      Top = 0
      Action = AShowAllMessages
    end
    object ToolButton2: TToolButton
      Left = 227
      Top = 0
      Action = AShowNewMessages
    end
    object ToolButton3: TToolButton
      Left = 334
      Top = 0
      Action = ADelete
    end
  end
  object DBGrid1: TDBGrid
    Left = 0
    Top = 66
    Width = 601
    Height = 361
    Align = alClient
    DataSource = DS_Dictionary
    ParentShowHint = False
    ShowHint = False
    TabOrder = 1
    TitleFont.Charset = ARABIC_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    Columns = <
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'WORD_VALUE_TX'
        Title.Alignment = taCenter
        Title.Caption = 'Message'
        Width = 565
        Visible = True
      end>
  end
  object PanelMessage: TPanel
    Left = 0
    Top = 25
    Width = 601
    Height = 41
    Align = alTop
    BevelInner = bvLowered
    Color = 16244940
    Font.Charset = ARABIC_CHARSET
    Font.Color = clNavy
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
  end
  object ActionList1: TActionList
    Left = 172
    Top = 162
    object AShowAllMessages: TAction
      Caption = 'Show All Messages'
      OnExecute = AShowAllMessagesExecute
    end
    object AShowNewMessages: TAction
      Caption = 'Show New Messages'
      OnExecute = AShowNewMessagesExecute
    end
    object ADelete: TAction
      Caption = 'Delete'
      Hint = 'Delete current record'
      OnExecute = ADeleteExecute
    end
  end
  object Q_Dictionary: TADOQuery
    Connection = DM_ML.ADOConnection
    CursorType = ctStatic
    BeforePost = Q_DictionaryBeforePost
    AfterScroll = Q_DictionaryAfterScroll
    Parameters = <
      item
        Name = 'LanguageID'
        Attributes = [paNullable]
        DataType = ftFixedChar
        NumericScale = 255
        Precision = 255
        Size = 510
        Value = '0'
      end>
    SQL.Strings = (
      
        'SELECT * FROM UserDictionary WHERE ((LANGUAGE_ID_I = :LanguageID' +
        ') AND (WORD_IS_NEW_B = TRUE))')
    Left = 172
    Top = 134
    object Q_DictionaryWORD_CODE_TX: TIntegerField
      FieldName = 'WORD_CODE_TX'
    end
    object Q_DictionaryLANGUAGE_ID_I: TIntegerField
      FieldName = 'LANGUAGE_ID_I'
    end
    object Q_DictionaryWORD_VALUE_TX: TWideStringField
      FieldName = 'WORD_VALUE_TX'
      Size = 255
    end
    object Q_DictionaryWORD_IS_NEW_B: TBooleanField
      FieldName = 'WORD_IS_NEW_B'
    end
    object Q_DictionaryWORD_FREQ_N: TFloatField
      FieldName = 'WORD_FREQ_N'
    end
    object Q_DictionaryWORD_LENG_N: TFloatField
      FieldName = 'WORD_LENG_N'
    end
    object Q_DictionaryWORD_FREQ_PROD_N: TFloatField
      FieldName = 'WORD_FREQ_PROD_N'
    end
    object Q_DictionaryWORD_FREQ_DIV_N: TFloatField
      FieldName = 'WORD_FREQ_DIV_N'
    end
    object Q_DictionaryWORD_PFREQ_N: TFloatField
      FieldName = 'WORD_PFREQ_N'
    end
    object Q_DictionaryWORD_PFREQ_PROD_N: TFloatField
      FieldName = 'WORD_PFREQ_PROD_N'
    end
    object Q_DictionaryWORD_PFREQ_DIV_N: TFloatField
      FieldName = 'WORD_PFREQ_DIV_N'
    end
    object Q_DictionaryWORD_RATIO_N: TFloatField
      FieldName = 'WORD_RATIO_N'
    end
  end
  object DS_Dictionary: TDataSource
    DataSet = Q_Dictionary
    Left = 200
    Top = 134
  end
  object FormTranslation1: TFormTranslation
    Left = 288
    Top = 204
  end
end
