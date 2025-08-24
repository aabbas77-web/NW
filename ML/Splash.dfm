object FormSplash: TFormSplash
  Left = 189
  Top = 105
  BorderIcons = [biSystemMenu]
  BorderStyle = bsNone
  Caption = 'Splash'
  ClientHeight = 107
  ClientWidth = 201
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 201
    Height = 107
    Align = alClient
    BevelInner = bvLowered
    BevelWidth = 5
    Caption = 'Please wait...'
    Color = 15269864
    Font.Charset = ARABIC_CHARSET
    Font.Color = clNavy
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
  end
  object FormTranslation1: TFormTranslation
    Left = 84
    Top = 40
  end
end
