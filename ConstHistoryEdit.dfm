object ConstHistoryEditForm: TConstHistoryEditForm
  Left = 659
  Top = 228
  Width = 356
  Height = 261
  Caption = #1048#1089#1090#1086#1088#1080#1103' '#1087#1072#1088#1072#1084#1077#1090#1088#1072
  Color = clWindow
  Ctl3D = False
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object SpeedButton1: TSpeedButton
    Left = 208
    Top = 91
    Width = 19
    Height = 18
  end
  object Panel1: TPanel
    Left = 0
    Top = 18
    Width = 26
    Height = 205
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      26
      205)
    object AddButton: TSpeedButton
      Left = 3
      Top = 4
      Width = 20
      Height = 20
      Cursor = crHandPoint
      Hint = #1044#1086#1073#1072#1074#1080#1090#1100' '#1079#1072#1087#1080#1089#1100
      Flat = True
      Glyph.Data = {
        F6000000424DF600000000000000760000002800000010000000100000000100
        0400000000008000000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFCFFFFFF
        FFFFFCCCCCCFFFFFFFFFCCCCCCCCCF999999CCCCCCCCCF999999CCCCCCCFFFFF
        FFFFCCCFFCF777777777CCCF7F7777777777CCCFFFFFFFFFFFFFCCC777777777
        7777FFF7777777777777FFFFFFFFFFFFFFFFFFF7777777777777FFF777777777
        7777FFFFFFFFFFFFFFFFFFF7777777777777FFF7777777777777}
      ParentShowHint = False
      ShowHint = True
      Spacing = 3
      OnClick = AddButtonClick
    end
    object SaveButton: TSpeedButton
      Left = 3
      Top = 28
      Width = 20
      Height = 20
      Cursor = crHandPoint
      Hint = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1080#1079#1084#1077#1085#1077#1085#1080#1103
      Flat = True
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        0400000000000001000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
        8888888888888888888882882222282222888788777778777788882088888888
        888888778888888888888800008882222288887777888777778888800F008888
        888888877F77888888888880FFF0388222888887FFF73887778888880F023388
        888888887F78338888888888002223388888888877888338888888888A222233
        88888888878888338888888888A22223388888888878888338888888888A2222
        3388888888878888338888888888A22223388888888878888338888888888A22
        223888888888878888388888888888A22228888888888878887888888888888A
        2228888888888887777888888888888888888888888888888888}
      NumGlyphs = 2
      ParentShowHint = False
      ShowHint = True
      Spacing = 3
      OnClick = SaveButtonClick
    end
    object CancelButton: TSpeedButton
      Left = 3
      Top = 52
      Width = 20
      Height = 20
      Hint = #1054#1090#1084#1077#1085#1080#1090#1100' '#1080#1079#1084#1077#1085#1077#1085#1080#1103
      Flat = True
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        0400000000000001000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
        8888888888888888888889982222992222888778777777777788899988899988
        8888877788877788888888999099922222888877777777777788888999998888
        8888888777777888888888809990388222888887777738877788888999993388
        888888877777338888888899909993388888887777777338888889998A299933
        88888777878777338888899888A29923388887788878778338888888888A2222
        3388888888878888338888888888A22223388888888878888338888888888A22
        223888888888878888388888888888A22228888888888878887888888888888A
        2228888888888887777888888888888888888888888888888888}
      NumGlyphs = 2
      OnClick = CancelButtonClick
    end
    object DelButton: TSpeedButton
      Left = 3
      Top = 76
      Width = 20
      Height = 20
      Cursor = crHandPoint
      Hint = #1059#1076#1072#1083#1080#1090#1100' '#1079#1072#1087#1080#1089#1100
      Flat = True
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        0400000000000001000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFF777777777
        7777FFF7777777777777FFF7777777777777FFF7777777777777FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFF7777777777777FFF7777777777777999777999777
        77777777777777777777F999F999FFFFFFFFF777F777FFFFFFFFFF99999FFFFF
        FFFFFF77777FFFFFFFFFFFF999CCCCCCCCCCFFF7777777777777FF99999CCCCC
        CCCCFFF7777777777777F999F999FFFFFFFFF777F777FFFFFFFF999FFF999FFF
        FFFF777FFF777FFFFFFFFFF7777777777777FFF7777777777777FFF777777777
        7777FFF7777777777777FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF777777777
        7777FFF7777777777777FFF7777777777777FFF7777777777777}
      NumGlyphs = 2
      ParentShowHint = False
      ShowHint = True
      Spacing = 3
      OnClick = DelButtonClick
    end
    object ExitButton: TSpeedButton
      Left = 3
      Top = 182
      Width = 20
      Height = 20
      Hint = #1042#1099#1093#1086#1076
      Anchors = [akLeft, akBottom]
      Flat = True
      Glyph.Data = {
        F6000000424DF600000000000000760000002800000010000000100000000100
        0400000000008000000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFF00FF00F08
        0070F00FF00FF00870070000000008087700FFFFFF0880087770FFFFFF000008
        7770FFFFFF0777087770FFFFFF0777087770FF00000007080770FF0999990708
        7770F099999077087770F090990777087770F000900777087770FFF00F077770
        8770FFFFFF0777770870FFFFFF0777777080FFFFFF0000000000}
      OnClick = ExitButtonClick
    end
  end
  object ConstValGrid: TDBGridEh
    Left = 26
    Top = 18
    Width = 314
    Height = 205
    Align = alClient
    AutoFitColWidths = True
    Ctl3D = False
    DataSource = ConstValSource
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    FooterColor = clWindow
    FooterFont.Charset = DEFAULT_CHARSET
    FooterFont.Color = clWindowText
    FooterFont.Height = -11
    FooterFont.Name = 'MS Sans Serif'
    FooterFont.Style = []
    OptionsEh = [dghHighlightFocus, dghClearSelection]
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    UseMultiTitle = True
    Columns = <
      item
        AlwaysShowEditButton = True
        EditButtons = <>
        FieldName = 'CONST_VALUE'
        Footers = <>
        Width = 196
      end
      item
        AlwaysShowEditButton = True
        EditButtons = <>
        FieldName = 'CONST_DATE'
        Footers = <>
        Width = 97
      end>
  end
  object formHeader: TJvNavPanelHeader
    Left = 0
    Top = 0
    Width = 340
    Height = 18
    Align = alTop
    Alignment = taCenter
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
    ColorFrom = clWhite
    ColorTo = clGradientActiveCaption
    ImageIndex = 0
  end
  object FormStorage1: TFormStorage
    StoredValues = <>
    Left = 56
    Top = 24
  end
  object ConstValDS: TpFIBDataSet
    UpdateSQL.Strings = (
      'UPDATE CONST_VALUES'
      'SET '
      '    ORG_ID = ?ORG_ID,'
      '    CONST_ID = ?CONST_ID,'
      '    CONST_VALUE = ?CONST_VALUE,'
      '    CONST_DATE = ?CONST_DATE,'
      '    REFERENCE = ?REFERENCE'
      'WHERE'
      '    ID = ?OLD_ID'
      '    ')
    DeleteSQL.Strings = (
      'DELETE FROM'
      '    CONST_VALUES'
      'WHERE'
      '        ID = ?OLD_ID'
      '    ')
    InsertSQL.Strings = (
      'INSERT INTO CONST_VALUES('
      '    ID,'
      '    ORG_ID,'
      '    CONST_ID,'
      '    CONST_VALUE,'
      '    CONST_DATE,'
      '    REFERENCE'
      ')'
      'VALUES('
      '    ?ID,'
      '    ?ORG_ID,'
      '    ?CONST_ID,'
      '    ?CONST_VALUE,'
      '    ?CONST_DATE,'
      '    ?REFERENCE'
      ')')
    RefreshSQL.Strings = (
      'SELECT'
      '    ID,'
      '    ORG_ID,'
      '    CONST_ID,'
      '    CONST_VALUE,'
      '    CONST_DATE,'
      '    REFERENCE'
      'FROM'
      '    CONST_VALUES '
      ' WHERE '
      '        CONST_VALUES.ID = ?OLD_ID'
      '    ')
    SelectSQL.Strings = (
      'SELECT'
      '    ID,'
      '    ORG_ID,'
      '    CONST_ID,'
      '    CONST_VALUE,'
      '    CONST_DATE,'
      '    REFERENCE'
      'FROM'
      '    CONST_VALUES ')
    AutoUpdateOptions.UpdateTableName = 'CONST_VALUES'
    AutoUpdateOptions.KeyFields = 'ID'
    AutoUpdateOptions.AutoReWriteSqls = True
    AutoUpdateOptions.CanChangeSQLs = True
    AutoUpdateOptions.GeneratorName = 'GEN_CONST_VALUES_ID'
    AutoUpdateOptions.WhenGetGenID = wgOnNewRecord
    AutoUpdateOptions.AutoParamsToFields = True
    BeforePost = ConstValDSBeforePost
    Transaction = RT
    Database = SaleBookDM.DataBase
    UpdateTransaction = WT
    AutoCommit = True
    Left = 88
    Top = 64
    object ConstValDSID: TFIBIntegerField
      FieldName = 'ID'
    end
    object ConstValDSORG_ID: TFIBSmallIntField
      FieldName = 'ORG_ID'
    end
    object ConstValDSCONST_ID: TFIBSmallIntField
      FieldName = 'CONST_ID'
    end
    object ConstValDSCONST_VALUE: TFIBStringField
      DisplayLabel = #1047#1085#1072#1095#1077#1085#1080#1077
      FieldName = 'CONST_VALUE'
      Size = 70
      EmptyStrToNull = True
    end
    object ConstValDSCONST_DATE: TFIBDateField
      DisplayLabel = #1044#1072#1090#1072' '#1085#1072#1095#1072#1083#1072' '#1076#1077#1081#1089#1090#1074#1080#1103
      FieldName = 'CONST_DATE'
    end
    object ConstValDSREFERENCE: TFIBIntegerField
      FieldName = 'REFERENCE'
    end
  end
  object ConstValSource: TDataSource
    DataSet = ConstValDS
    OnStateChange = ConstValSourceStateChange
    Left = 168
    Top = 64
  end
  object WT: TpFIBTransaction
    DefaultDatabase = SaleBookDM.DataBase
    TimeoutAction = TARollback
    Left = 120
    Top = 64
  end
  object RT: TpFIBTransaction
    DefaultDatabase = SaleBookDM.DataBase
    TimeoutAction = TARollback
    Left = 88
    Top = 96
  end
  object ConstQ: TpFIBQuery
    Transaction = RT
    Database = SaleBookDM.DataBase
    Left = 56
    Top = 64
    qoAutoCommit = True
    qoStartTransaction = True
  end
end
