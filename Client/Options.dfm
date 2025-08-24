object FormOptions: TFormOptions
  Left = 189
  Top = 105
  BiDiMode = bdLeftToRight
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Options'
  ClientHeight = 192
  ClientWidth = 420
  Color = 15132390
  Font.Charset = ARABIC_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  ParentBiDiMode = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 156
    Width = 420
    Height = 36
    Align = alBottom
    Color = 15132390
    TabOrder = 0
    object BitBtn1: TBitBtn
      Left = 213
      Top = 5
      Width = 75
      Height = 25
      Cancel = True
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 0
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        333333333333333333333333000033338833333333333333333F333333333333
        0000333911833333983333333388F333333F3333000033391118333911833333
        38F38F333F88F33300003339111183911118333338F338F3F8338F3300003333
        911118111118333338F3338F833338F3000033333911111111833333338F3338
        3333F8330000333333911111183333333338F333333F83330000333333311111
        8333333333338F3333383333000033333339111183333333333338F333833333
        00003333339111118333333333333833338F3333000033333911181118333333
        33338333338F333300003333911183911183333333383338F338F33300003333
        9118333911183333338F33838F338F33000033333913333391113333338FF833
        38F338F300003333333333333919333333388333338FFF830000333333333333
        3333333333333333333888330000333333333333333333333333333333333333
        0000}
      NumGlyphs = 2
    end
    object BitBtn2: TBitBtn
      Left = 133
      Top = 5
      Width = 75
      Height = 25
      Caption = 'Ok'
      Default = True
      ModalResult = 1
      TabOrder = 1
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        3333333333333333333333330000333333333333333333333333F33333333333
        00003333344333333333333333388F3333333333000033334224333333333333
        338338F3333333330000333422224333333333333833338F3333333300003342
        222224333333333383333338F3333333000034222A22224333333338F338F333
        8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
        33333338F83338F338F33333000033A33333A222433333338333338F338F3333
        0000333333333A222433333333333338F338F33300003333333333A222433333
        333333338F338F33000033333333333A222433333333333338F338F300003333
        33333333A222433333333333338F338F00003333333333333A22433333333333
        3338F38F000033333333333333A223333333333333338F830000333333333333
        333A333333333333333338330000333333333333333333333333333333333333
        0000}
      NumGlyphs = 2
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 420
    Height = 156
    Align = alClient
    BiDiMode = bdLeftToRight
    Color = 15132390
    ParentBiDiMode = False
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 26
      Top = 8
      Width = 369
      Height = 141
      BiDiMode = bdLeftToRight
      Caption = 'Watching and repairing'
      ParentBiDiMode = False
      TabOrder = 0
      object Label1: TLabel
        Left = 112
        Top = 24
        Width = 145
        Height = 13
        AutoSize = False
        Caption = 'Compression type'
      end
      object Label2: TLabel
        Left = 112
        Top = 72
        Width = 145
        Height = 13
        AutoSize = False
        Caption = 'Compression quality'
      end
      object ComboBox1: TComboBox
        Left = 112
        Top = 44
        Width = 145
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 0
        Items.Strings = (
          'JPEG'
          'RLE'
          'Bitmap256'
          'None')
      end
      object CSpinEdit1: TCSpinEdit
        Left = 112
        Top = 88
        Width = 145
        Height = 22
        MaxValue = 100
        MinValue = 20
        TabOrder = 1
        Value = 40
      end
      object CheckBox1: TCheckBox
        Left = 112
        Top = 116
        Width = 145
        Height = 17
        Caption = 'Gray'
        TabOrder = 2
      end
    end
  end
  object FormTranslation1: TFormTranslation
    Left = 287
    Top = 72
  end
end
