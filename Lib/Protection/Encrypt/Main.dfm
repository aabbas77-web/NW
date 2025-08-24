object FormMain: TFormMain
  Left = 189
  Top = 105
  Width = 696
  Height = 482
  Caption = 'Encrypt'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 32
    Top = 16
    Width = 21
    Height = 13
    Caption = 'Text'
  end
  object Edit1: TEdit
    Left = 32
    Top = 36
    Width = 641
    Height = 21
    TabOrder = 0
    Text = '0'
  end
  object Button1: TButton
    Left = 32
    Top = 72
    Width = 75
    Height = 25
    Caption = 'Encrypt'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Edit2: TEdit
    Left = 32
    Top = 104
    Width = 641
    Height = 21
    TabOrder = 2
  end
end
