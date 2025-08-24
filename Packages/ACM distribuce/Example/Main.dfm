object FormMain: TFormMain
  Left = 190
  Top = 105
  Width = 230
  Height = 284
  Caption = 'ACM Example'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object ButtonStart: TButton
    Left = 8
    Top = 60
    Width = 75
    Height = 25
    Caption = 'Start'
    TabOrder = 0
    OnClick = ButtonStartClick
  end
  object Edit: TEdit
    Left = 88
    Top = 28
    Width = 121
    Height = 21
    TabOrder = 1
    Text = 'amir-pc'
  end
  object ButtonStop: TButton
    Left = 88
    Top = 60
    Width = 75
    Height = 25
    Caption = 'Stop'
    Enabled = False
    TabOrder = 2
    OnClick = ButtonStopClick
  end
  object CheckBoxServer: TCheckBox
    Left = 8
    Top = 4
    Width = 57
    Height = 17
    Caption = 'Server'
    Checked = True
    State = cbChecked
    TabOrder = 3
  end
  object Button1: TButton
    Left = 8
    Top = 28
    Width = 75
    Height = 25
    Caption = 'Connect'
    TabOrder = 5
    OnClick = Button1Click
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 238
    Width = 222
    Height = 19
    Panels = <>
    SimplePanel = True
  end
  object Button2: TButton
    Left = 168
    Top = 60
    Width = 44
    Height = 25
    Caption = 'Test'
    TabOrder = 7
    OnClick = Button2Click
  end
  object Memo: TMemo
    Left = 8
    Top = 92
    Width = 205
    Height = 141
    TabOrder = 6
  end
  object ACMWaveOut: TACMWaveOut
    Left = 80
    Top = 4
    Width = 32
    Height = 32
  end
  object ACMWaveIn: TACMWaveIn
    Left = 112
    Top = 4
    Width = 32
    Height = 32
    OnData = ACMWaveInData
  end
  object ACMDialog: TACMDialog
    Left = 48
    Top = 4
  end
  object ServerSocket: TServerSocket
    Active = False
    Port = 1024
    ServerType = stNonBlocking
    OnClientConnect = ServerSocketClientConnect
    OnClientDisconnect = ServerSocketClientDisconnect
    OnClientRead = ServerSocketClientRead
    Left = 156
    Top = 4
  end
  object ClientSocket: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Port = 1024
    OnConnect = ClientSocketConnect
    OnDisconnect = ClientSocketDisconnect
    OnRead = ClientSocketRead
    Left = 184
    Top = 4
  end
end
