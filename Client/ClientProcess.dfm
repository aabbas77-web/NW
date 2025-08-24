object DMClient: TDMClient
  OldCreateOrder = False
  OnCreate = DataModuleCreate
  OnDestroy = DataModuleDestroy
  Left = 190
  Top = 147
  Height = 298
  Width = 391
  object AnswerMWBuffer: TMWBuffer
    DataBufferSize = 256
    HeaderSize = 0
    AutoExpand = 256
    Left = 32
    Top = 44
  end
  object AppSrvClient: TAppSrvClient
    Server = 'localhost'
    Port = '2121'
    SocksAuthentication = socksNoAuthentication
    Answer = AnswerMWBuffer
    MaxRetries = 0
    OnRequestDone = AppSrvClientRequestDone
    OnSessionConnected = AppSrvClientSessionConnected
    OnSocksError = AppSrvClientSocksError
    OnSessionClosed = AppSrvClientSessionClosed
    Left = 60
    Top = 44
  end
  object RequestBroker: TRequestBroker
    UserData = 0
    Options = [rboDisplayObjectCount]
    Left = 60
    Top = 72
  end
  object AppServer: TAppServer
    Options = [asoDisplayCommands, asoDisplayClientCount]
    Banner = 'WWPTC Net-Watcher Client'
    Port = '2106'
    ClientTimeout = 300000000
    TimeoutInterval = 300000000
    RequestBroker = RequestBroker
    OnDisplay = AppServerDisplay
    Left = 32
    Top = 72
  end
  object FormTranslation1: TFormTranslation
    Left = 176
    Top = 119
  end
end
