object DM_ML: TDM_ML
  OldCreateOrder = False
  OnCreate = DataModuleCreate
  OnDestroy = DataModuleDestroy
  Left = 189
  Top = 105
  Height = 311
  Width = 386
  object TableUserDictionary: TADOTable
    Connection = ADOConnection
    CursorType = ctStatic
    TableName = 'UserDictionary'
    Left = 60
    Top = 8
  end
  object ADOQueryMaxCode: TADOQuery
    Connection = ADOConnection
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'SELECT MAX(WORD_CODE_TX) FROM UserDictionary')
    Left = 60
    Top = 56
  end
  object ADOConnection: TADOConnection
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 148
    Top = 32
  end
  object FormTranslation1: TFormTranslation
    Left = 144
    Top = 128
  end
end
