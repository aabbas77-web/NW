object FormFullScreen: TFormFullScreen
  Left = 739
  Top = 361
  BorderIcons = []
  BorderStyle = bsNone
  Caption = 'Full Screen'
  ClientHeight = 238
  ClientWidth = 277
  Color = 15132390
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnActivate = FormActivate
  OnClose = FormClose
  OnCreate = FormCreate
  OnDeactivate = FormDeactivate
  OnKeyDown = FormKeyDown
  OnMouseDown = FormMouseDown
  OnMouseMove = FormMouseMove
  OnMouseUp = FormMouseUp
  PixelsPerInch = 96
  TextHeight = 13
  object FormTranslation1: TFormTranslation
    Left = 96
    Top = 60
  end
  object ApplicationEvents1: TApplicationEvents
    Left = 68
    Top = 60
  end
end
