object FormMessage: TFormMessage
  Left = 190
  Top = 105
  Width = 399
  Height = 317
  BorderIcons = [biSystemMenu, biMaximize]
  Caption = 'Message'
  Color = 15132390
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
    Top = 249
    Width = 391
    Height = 41
    Align = alBottom
    Color = 15132390
    TabOrder = 0
    DesignSize = (
      391
      41)
    object Panel2: TPanel
      Left = 113
      Top = 5
      Width = 165
      Height = 31
      Anchors = [akTop]
      BevelOuter = bvNone
      Color = 15132390
      TabOrder = 0
      object BitBtn1: TBitBtn
        Left = 5
        Top = 3
        Width = 75
        Height = 25
        TabOrder = 0
        Kind = bkOK
      end
      object BitBtn2: TBitBtn
        Left = 85
        Top = 3
        Width = 75
        Height = 25
        TabOrder = 1
        Kind = bkCancel
      end
    end
  end
  object RichEdit: TRichEdit
    Left = 0
    Top = 0
    Width = 391
    Height = 249
    Align = alClient
    Color = 15269887
    ScrollBars = ssBoth
    TabOrder = 1
  end
  object FormTranslation1: TFormTranslation
    Left = 176
    Top = 116
  end
end
