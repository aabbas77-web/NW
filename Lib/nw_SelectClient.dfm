object FormSelectClient: TFormSelectClient
  Left = 190
  Top = 105
  Width = 482
  Height = 350
  BorderIcons = [biSystemMenu]
  Caption = 'Select Client'
  Color = 15132390
  Font.Charset = ARABIC_CHARSET
  Font.Color = clNavy
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBoxNetwork: TGroupBox
    Left = 0
    Top = 0
    Width = 231
    Height = 282
    Align = alClient
    Caption = 'Network'
    TabOrder = 0
    object TreeViewGroups: TTreeView
      Left = 2
      Top = 15
      Width = 227
      Height = 265
      Align = alClient
      BiDiMode = bdLeftToRight
      Color = 15132390
      Ctl3D = True
      DragMode = dmAutomatic
      Images = DM.ImageList
      Indent = 19
      MultiSelect = True
      MultiSelectStyle = [msControlSelect, msShiftSelect]
      ParentBiDiMode = False
      ParentCtl3D = False
      ReadOnly = True
      RowSelect = True
      SortType = stText
      TabOrder = 0
      OnDblClick = TreeViewGroupsDblClick
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 282
    Width = 474
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    Color = 15132390
    TabOrder = 1
    DesignSize = (
      474
      41)
    object Panel2: TPanel
      Left = 152
      Top = 4
      Width = 169
      Height = 33
      Anchors = []
      BevelOuter = bvNone
      Color = 15132390
      TabOrder = 0
      object BitBtn1: TBitBtn
        Left = 7
        Top = 4
        Width = 75
        Height = 25
        Caption = 'Ok'
        Default = True
        TabOrder = 0
        OnClick = BitBtn1Click
      end
      object BitBtn2: TBitBtn
        Left = 87
        Top = 4
        Width = 75
        Height = 25
        Cancel = True
        Caption = 'Cancel'
        TabOrder = 1
        OnClick = BitBtn2Click
      end
    end
  end
  object GroupBox1: TGroupBox
    Left = 280
    Top = 0
    Width = 194
    Height = 282
    Align = alRight
    Caption = 'Clients'
    Color = 15132390
    ParentColor = False
    TabOrder = 2
    object ListBoxClients: TListBox
      Left = 2
      Top = 15
      Width = 190
      Height = 265
      Align = alClient
      Color = 15132390
      Font.Charset = ARABIC_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ItemHeight = 13
      MultiSelect = True
      ParentFont = False
      TabOrder = 0
    end
  end
  object Panel3: TPanel
    Left = 231
    Top = 0
    Width = 49
    Height = 282
    Align = alRight
    BevelInner = bvLowered
    BevelOuter = bvNone
    Color = 15132390
    TabOrder = 3
    DesignSize = (
      49
      282)
    object Panel4: TPanel
      Left = 8
      Top = 71
      Width = 33
      Height = 139
      Anchors = []
      BevelOuter = bvNone
      Color = 15132390
      TabOrder = 0
      object SpeedButton1: TSpeedButton
        Left = 5
        Top = 4
        Width = 23
        Height = 22
        Caption = '>'
        Font.Charset = ARABIC_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = SpeedButton1Click
      end
      object SpeedButton2: TSpeedButton
        Left = 5
        Top = 32
        Width = 23
        Height = 22
        Caption = '>>'
        Font.Charset = ARABIC_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = SpeedButton2Click
      end
      object SpeedButton3: TSpeedButton
        Left = 5
        Top = 84
        Width = 23
        Height = 22
        Caption = '<'
        Font.Charset = ARABIC_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = SpeedButton3Click
      end
      object SpeedButton4: TSpeedButton
        Left = 5
        Top = 112
        Width = 23
        Height = 22
        Caption = '<<'
        Font.Charset = ARABIC_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = SpeedButton4Click
      end
      object Bevel1: TBevel
        Left = -2
        Top = 68
        Width = 36
        Height = 2
        Shape = bsBottomLine
      end
    end
  end
end
