object FormTempExplorer: TFormTempExplorer
  Left = 800
  Top = 105
  Width = 224
  Height = 289
  Caption = 'Temp Explorer'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 216
    Height = 262
    Align = alClient
    Caption = 'Temporary'
    TabOrder = 0
    object Panel1: TPanel
      Left = 2
      Top = 15
      Width = 212
      Height = 245
      Align = alClient
      BiDiMode = bdLeftToRight
      Color = 12175550
      ParentBiDiMode = False
      TabOrder = 0
      object Panel3: TPanel
        Left = 1
        Top = 1
        Width = 210
        Height = 243
        Align = alClient
        Color = 12175550
        TabOrder = 0
        object ShellListView1: TShellListView
          Left = 1
          Top = 98
          Width = 208
          Height = 144
          ObjectTypes = [otFolders, otNonFolders]
          Root = 'rfDesktop'
          ShellTreeView = ShellTreeView1
          Sorted = True
          Align = alClient
          HideSelection = False
          ParentColor = False
          TabOrder = 0
          TabStop = True
        end
        object ShellTreeView1: TShellTreeView
          Left = 1
          Top = 1
          Width = 208
          Height = 97
          ObjectTypes = [otFolders]
          Root = 'rfDesktop'
          ShellListView = ShellListView1
          UseShellImages = True
          Align = alTop
          Indent = 19
          ParentColor = False
          RightClickSelect = True
          ShowRoot = False
          TabOrder = 1
          TabStop = True
        end
      end
    end
  end
  object FormTranslation1: TFormTranslation
    Left = 68
    Top = 40
  end
end
