object PrntDataForm: TPrntDataForm
  Left = 537
  Top = 357
  Width = 801
  Height = 449
  Caption = #1042#1099#1074#1086#1076' '#1076#1072#1085#1085#1099#1093' '#1085#1072' '#1087#1088#1080#1085#1090#1077#1088'...'
  Color = clWindow
  Ctl3D = False
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object Panel1: TPanel
    Left = 0
    Top = 353
    Width = 783
    Height = 51
    Align = alBottom
    AutoSize = True
    BevelOuter = bvNone
    BorderStyle = bsSingle
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 0
    DesignSize = (
      781
      49)
    object Indicator: TCGauge
      Left = 0
      Top = 24
      Width = 781
      Height = 25
      Align = alBottom
    end
    object CloseButton: TJvXPButton
      Left = 673
      Top = 0
      Width = 89
      Caption = #1047#1072#1082#1088#1099#1090#1100
      TabOrder = 0
      Glyph.Data = {
        F6000000424DF600000000000000760000002800000010000000100000000100
        0400000000008000000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
        8888888888888888888888818888888888988899188888888888889991888888
        8988888999888888988888889918888998888888899188998888888888999998
        8888888888899988888888888899991888888888899988918888888999988889
        1888889999888888998888999888888888988888888888888888}
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      OnClick = CloseButtonClick
    end
    object ViewButton: TJvXPButton
      Left = 569
      Top = 0
      Width = 97
      Caption = #1055#1086#1082#1072#1079#1072#1090#1100
      TabOrder = 1
      Glyph.Data = {
        42010000424D4201000000000000760000002800000011000000110000000100
        040000000000CC00000000000000000000001000000010000000000000000000
        BF0000BF000000BFBF00BF000000BF00BF00BFBF0000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00777777777777
        77777000000070000000007777777000000070FFFFFFF07777700000000070F7
        7777F07777000000000070F77777F07770007000000070F77780008700077000
        000070F7700FFF0000777000000070F708FFFF0807777000000070F80E000F07
        08777000000070F0EFEFEF0770777000000070F0F0000F077077700000007000
        EFEFFF0770777000000077780000000708777000000077770077777807777000
        0000777770077700777770000000777777800087777770000000777777777777
        777770000000}
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      OnClick = ViewButtonClick
    end
    object OutputButton: TJvXPButton
      Left = 384
      Top = 0
      Width = 180
      Caption = #1042#1099#1075#1088#1091#1079#1080#1090#1100' '#1076#1072#1085#1085#1099#1077
      TabOrder = 2
      Glyph.Data = {
        F6000000424DF600000000000000760000002800000010000000100000000100
        0400000000008000000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFF0B7FFF
        FFB0FFFFFF0B7FFFFFB0FFFFFF0B7FFFFFB0FFFFFF0B7FFFFFB0000000000077
        00700FFFFFFFF00077B00FFFFFFFF00077B00000F000F00090070FFFFFFFF0F9
        99FF000000F0F099999F0FFFFFFFF99999990000F00000F999FF0FFFF0FF0FF9
        99FF0077F0FF0FF999FF0FFFF0F0FF7999FF0000000F999999FF}
      Anchors = [akTop, akRight]
      OnClick = OutputButtonClick
    end
    object SendButton: TJvXPButton
      Left = 192
      Top = 0
      Width = 180
      Caption = #1054#1090#1087#1088#1072#1074#1080#1090#1100' '#1076#1072#1085#1085#1099#1077
      TabOrder = 3
      Glyph.Data = {
        36010000424D3601000000000000760000002800000012000000100000000100
        040000000000C000000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
        FFFFFF000000FFFFFFFFFFFFFFFFFF0000000000000000000000000000000888
        888888888888F000000008FFFFFFFFFFFFFFF000000008FFFFFFCCFCCCCFF000
        000008FFFFFFFFFFFFFFF000000008FFFFFCCCFCCCFFF000000008FFFFFFFFFF
        FFFFF000000008F999F9999FFF555000000008FFFFFFFFFFFF5B500000000899
        9F9999FFFF5B500000000FFFFFFFFFFFFF555000000000000000000000000000
        0000FFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFF000000}
      Anchors = [akTop, akRight]
      ParentShowHint = False
      ShowHint = False
      OnClick = SendButtonClick
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 783
    Height = 331
    Align = alClient
    AutoSize = True
    BevelOuter = bvNone
    BorderStyle = bsSingle
    TabOrder = 1
    object JournalButton: TRadioButton
      Left = 120
      Top = 60
      Width = 313
      Height = 21
      Caption = #1057#1074#1077#1076#1077#1085#1080#1103' '#1086' '#1085#1072#1095#1080#1089#1083#1077#1085#1085#1099#1093' '#1080' '#1074#1099#1087#1083#1072#1095#1077#1085#1085#1099#1093' '#1045#1044#1042
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 0
      OnClick = JournalButtonClick
    end
    object InvoiceButton: TRadioButton
      Left = 120
      Top = 40
      Width = 193
      Height = 17
      Caption = #1057#1074#1086#1076#1085#1099#1081' '#1086#1090#1095#1077#1090
      Checked = True
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 1
      TabStop = True
      OnClick = InvoiceButtonClick
    end
    object CountButton: TRadioButton
      Left = 120
      Top = 20
      Width = 265
      Height = 17
      Caption = #1054#1090#1095#1077#1090' '#1086#1073' '#1086#1087#1083#1072#1090#1077' '#1087#1086' '#1076#1086#1089#1090#1072#1074#1097#1080#1082#1091
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 2
      OnClick = CountButtonClick
    end
    object JvNavPanelHeader2: TJvNavPanelHeader
      Left = 0
      Top = 0
      Width = 781
      Height = 18
      Align = alTop
      Alignment = taCenter
      Caption = #1054#1073#1098#1077#1082#1090' '#1087#1077#1095#1072#1090#1080
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      ColorFrom = clBtnFace
      ColorTo = clBtnShadow
      ImageIndex = 0
    end
    object PotrButton: TRadioButton
      Left = 120
      Top = 84
      Width = 313
      Height = 21
      Caption = #1055#1086#1090#1088#1077#1073#1085#1086#1089#1090#1100' '#1074' '#1044#1057
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 4
      OnClick = PotrButtonClick
    end
  end
  object Panel6: TPanel
    Left = 0
    Top = 331
    Width = 783
    Height = 22
    Align = alBottom
    AutoSize = True
    BevelOuter = bvNone
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 2
    object Label3: TLabel
      Left = 48
      Top = 4
      Width = 193
      Height = 16
      Alignment = taRightJustify
      AutoSize = False
      Caption = #1044#1085#1080' '#1079#1072#1076#1072#1085#1080#1103' '#1085#1072' '#1074#1099#1087#1083#1072#1090#1091' '#1089
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label1: TLabel
      Left = 271
      Top = 2
      Width = 42
      Height = 16
      Alignment = taRightJustify
      AutoSize = False
      Caption = #1055#1086
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object CNEdit: TJvSpinEdit
      Left = 248
      Top = 0
      Width = 41
      Height = 22
      ButtonKind = bkClassic
      MaxValue = 31
      MinValue = 1
      Value = 1
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
    end
    object CNEdit1: TJvSpinEdit
      Left = 320
      Top = 0
      Width = 41
      Height = 22
      ButtonKind = bkClassic
      MaxValue = 31
      MinValue = 1
      Value = 22
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
  end
  object HeadDS: TpFIBDataSet
    SelectSQL.Strings = (
      'SELECT * '
      'FROM'
      '    ACCOUNTS ')
    Transaction = HT
    Database = SaleBookDM.DataBase
    AutoCommit = True
    Left = 144
    Top = 248
    object HeadDSORG_ID: TFIBSmallIntField
      FieldName = 'ORG_ID'
    end
    object HeadDSCOUNT_DATE: TFIBDateField
      FieldName = 'COUNT_DATE'
      DisplayFormat = 'dd.mm.yyyy'
    end
    object HeadDSCOUNT_NUMBER: TFIBSmallIntField
      FieldName = 'COUNT_NUMBER'
    end
    object HeadDSCUSTOMER_ID: TFIBIntegerField
      FieldName = 'CUSTOMER_ID'
    end
    object HeadDSCUSTOMER_NAME: TFIBStringField
      FieldName = 'CUSTOMER_NAME'
      Size = 120
      EmptyStrToNull = True
    end
    object HeadDSUSER_ID: TFIBSmallIntField
      FieldName = 'USER_ID'
    end
    object HeadDSRS_ID: TFIBSmallIntField
      FieldName = 'RS_ID'
    end
    object HeadDSCOUNT_TOTAL: TFIBFloatField
      FieldName = 'COUNT_TOTAL'
    end
    object HeadDSEDIT_KEY: TFIBBooleanField
      DefaultExpression = '1'
      FieldName = 'EDIT_KEY'
    end
    object HeadDSCOUNT_TYPE: TFIBSmallIntField
      FieldName = 'COUNT_TYPE'
    end
    object HeadDSCOUNT_OPL: TFIBFloatField
      FieldName = 'COUNT_OPL'
    end
    object HeadDSCOUNT_NEOPL: TFIBFloatField
      FieldName = 'COUNT_NEOPL'
    end
    object HeadDSCOUNT_TOTALI: TFIBIntegerField
      FieldName = 'COUNT_TOTALI'
    end
    object HeadDSCOUNT_OPLI: TFIBIntegerField
      FieldName = 'COUNT_OPLI'
    end
    object HeadDSCOUNT_NEOPLI: TFIBIntegerField
      FieldName = 'COUNT_NEOPLI'
    end
    object HeadDSCOUNT_TEK: TFIBFloatField
      FieldName = 'COUNT_TEK'
    end
    object HeadDSCOUNT_PR: TFIBFloatField
      FieldName = 'COUNT_PR'
    end
    object HeadDSCOUNT_RAZ: TFIBFloatField
      FieldName = 'COUNT_RAZ'
    end
    object HeadDSCOUNT_NEOPLP: TFIBFloatField
      FieldName = 'COUNT_NEOPLP'
    end
    object HeadDSCOUNT_OPLP: TFIBFloatField
      FieldName = 'COUNT_OPLP'
    end
    object HeadDSM: TFIBIntegerField
      FieldName = 'M'
    end
    object HeadDSY: TFIBIntegerField
      FieldName = 'Y'
    end
  end
  object frxHeadDS: TfrxDBDataset
    UserName = 'frxHeadDS'
    CloseDataSource = False
    FieldAliases.Strings = (
      'ORG_ID=ORG_ID'
      'COUNT_DATE=COUNT_DATE'
      'COUNT_NUMBER=COUNT_NUMBER'
      'CUSTOMER_ID=CUSTOMER_ID'
      'CUSTOMER_NAME=CUSTOMER_NAME'
      'USER_ID=USER_ID'
      'RS_ID=RS_ID'
      'COUNT_TOTAL=COUNT_TOTAL'
      'EDIT_KEY=EDIT_KEY'
      'COUNT_TYPE=COUNT_TYPE'
      'COUNT_OPL=COUNT_OPL'
      'COUNT_NEOPL=COUNT_NEOPL'
      'COUNT_TOTALI=COUNT_TOTALI'
      'COUNT_OPLI=COUNT_OPLI'
      'COUNT_NEOPLI=COUNT_NEOPLI'
      'COUNT_TEK=COUNT_TEK'
      'COUNT_PR=COUNT_PR'
      'COUNT_RAZ=COUNT_RAZ'
      'COUNT_NEOPLP=COUNT_NEOPLP'
      'COUNT_OPLP=COUNT_OPLP'
      'M=M'
      'Y=Y')
    DataSet = HeadDS
    Left = 264
    Top = 360
  end
  object TableDS: TpFIBDataSet
    SelectSQL.Strings = (
      'SELECT *'
      'FROM'
      '    RESULT ')
    Transaction = TT
    Database = SaleBookDM.DataBase
    AutoCommit = True
    Left = 312
    Top = 240
    object TableDSOPS: TFIBIntegerField
      FieldName = 'OPS'
    end
    object TableDSOPL: TFIBFloatField
      FieldName = 'OPL'
    end
    object TableDSNEOPL: TFIBFloatField
      FieldName = 'NEOPL'
    end
    object TableDSCOUNT_OPL: TFIBIntegerField
      FieldName = 'COUNT_OPL'
    end
    object TableDSCOUNT_NEOPL: TFIBIntegerField
      FieldName = 'COUNT_NEOPL'
    end
  end
  object frxTableDS: TfrxDBDataset
    UserName = 'frxTableDS'
    CloseDataSource = False
    DataSet = TableDS
    Left = 320
    Top = 360
  end
  object DSSvod: TfrxDBDataset
    UserName = 'DSSvod'
    CloseDataSource = False
    DataSet = DSSved
    Left = 352
    Top = 344
  end
  object frxReport: TfrxReport
    Version = '3.24'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbZoom, pbPageSetup, pbNavigator]
    PreviewOptions.Zoom = 1
    PrintOptions.Printer = 'Default'
    ReportOptions.CreateDate = 38397.4759206713
    ReportOptions.LastChange = 43817.6987527199
    ScriptLanguage = 'C++Script'
    ScriptText.Strings = (
      '{'
      '}')
    StoreInDFM = False
    OnGetValue = frxReportGetValue
    Left = 16
    Top = 16
    Datasets = <
      item
        DataSet = frxHeadDS
        DataSetName = 'frxHeadDS'
      end
      item
        DataSet = frxTableDS
        DataSetName = 'frxTableDS'
      end
      item
        DataSet = frxTableDS1
        DataSetName = 'frxTableDS1'
      end>
    Variables = <
      item
        Name = ' MyVariables'
        Value = Null
      end
      item
        Name = 'TwoCopysOnPage'
        Value = Null
      end>
    Style = <>
  end
  object HT: TpFIBTransaction
    Active = True
    DefaultDatabase = SaleBookDM.DataBase
    TimeoutAction = TARollback
    Left = 272
    Top = 192
  end
  object TT: TpFIBTransaction
    Active = True
    DefaultDatabase = SaleBookDM.DataBase
    TimeoutAction = TARollback
    Left = 216
    Top = 168
  end
  object MemTable1: TkbmMemTable
    DesignActivation = True
    AttachedAutoRefresh = True
    AttachMaxCount = 1
    FieldDefs = <
      item
        Name = 'DOC_ID'
        DataType = ftSmallint
      end
      item
        Name = 'DOC_NAME'
        DataType = ftString
        Size = 20
      end
      item
        Name = 'DOC_NUMBER'
        DataType = ftString
        Size = 120
      end
      item
        Name = 'DOC_DATE'
        DataType = ftDate
      end
      item
        Name = 'CONST_IDENTIFIER'
        DataType = ftString
        Size = 30
      end>
    IndexFieldNames = 'DOC_ID'
    IndexName = 'MemTable1Index1'
    IndexDefs = <
      item
        Name = 'MemTable1Index1'
        Fields = 'DOC_ID'
        Options = [ixPrimary, ixUnique]
        Source = 'Source1'
      end>
    SortFields = 'DOC_ID'
    SortOptions = []
    PersistentBackup = False
    ProgressFlags = [mtpcLoad, mtpcSave, mtpcCopy]
    FilterOptions = []
    Version = '3.01'
    LanguageID = 0
    SortID = 0
    SubLanguageID = 1
    LocaleID = 1024
    Left = 64
    Top = 152
    object MemTable1DOC_ID: TSmallintField
      FieldName = 'DOC_ID'
    end
    object MemTable1DOC_NAME: TStringField
      FieldName = 'DOC_NAME'
    end
    object MemTable1DOC_NUNBER: TStringField
      FieldName = 'DOC_NUMBER'
      Size = 120
    end
    object MemTable1DOC_DATE: TDateField
      FieldName = 'DOC_DATE'
    end
    object MemTable1CONST_IDENTIFIER: TStringField
      FieldName = 'CONST_IDENTIFIER'
      Size = 30
    end
  end
  object forLeaderTable: TkbmMemTable
    DesignActivation = True
    AttachedAutoRefresh = True
    AttachMaxCount = 1
    FieldDefs = <
      item
        Name = 'V_ID'
        DataType = ftSmallint
      end
      item
        Name = 'DOC_ID'
        DataType = ftSmallint
      end
      item
        Name = 'FOR_LEADER'
        DataType = ftString
        Size = 120
      end
      item
        Name = 'FOR_BOOK'
        DataType = ftString
        Size = 120
      end
      item
        Name = 'LEADER_CHECK'
        DataType = ftBoolean
      end
      item
        Name = 'BOOK_CHECK'
        DataType = ftBoolean
      end>
    IndexFieldNames = 'DOC_ID;V_ID'
    IndexName = 'MemTable2Index1'
    IndexDefs = <
      item
        Name = 'MemTable2Index1'
        Fields = 'DOC_ID;V_ID'
      end>
    SortFields = 'V_ID'
    SortOptions = []
    PersistentBackup = False
    ProgressFlags = [mtpcLoad, mtpcSave, mtpcCopy]
    FilterOptions = []
    MasterFields = 'DOC_ID'
    MasterSource = Source1
    Version = '3.01'
    LanguageID = 0
    SortID = 1
    SubLanguageID = 1
    LocaleID = 66560
    Left = 48
    Top = 232
    object forLeaderTableV_ID: TSmallintField
      FieldName = 'V_ID'
    end
    object forLeaderTableDOC_ID: TSmallintField
      FieldName = 'DOC_ID'
    end
    object forLeaderTableFOR_LEADER: TStringField
      FieldName = 'FOR_LEADER'
      Size = 120
    end
    object forLeaderTableLEADER_CHECK: TBooleanField
      FieldName = 'LEADER_CHECK'
    end
  end
  object Source1: TDataSource
    DataSet = MemTable1
    Left = 120
    Top = 152
  end
  object forLeaderSource: TDataSource
    DataSet = forLeaderTable
    Left = 216
    Top = 248
  end
  object forBookTable: TkbmMemTable
    DesignActivation = True
    AttachedAutoRefresh = True
    AttachMaxCount = 1
    FieldDefs = <>
    IndexFieldNames = 'DOC_ID;V_ID'
    IndexName = 'MemTable2Index1'
    IndexDefs = <
      item
        Name = 'MemTable2Index1'
        Fields = 'DOC_ID;V_ID'
      end>
    SortFields = 'V_ID'
    SortOptions = []
    PersistentBackup = False
    ProgressFlags = [mtpcLoad, mtpcSave, mtpcCopy]
    FilterOptions = []
    MasterFields = 'DOC_ID'
    MasterSource = Source1
    Version = '3.01'
    LanguageID = 0
    SortID = 1
    SubLanguageID = 1
    LocaleID = 66560
    Left = 104
    Top = 368
    object forBookTableV_ID: TSmallintField
      FieldName = 'V_ID'
    end
    object forBookTableDOC_ID: TSmallintField
      FieldName = 'DOC_ID'
    end
    object forBookTableFOR_BOOK: TStringField
      FieldName = 'FOR_BOOK'
      Size = 120
    end
    object forBookTableBOOK_CHECK: TBooleanField
      FieldName = 'BOOK_CHECK'
    end
  end
  object forBookSource: TDataSource
    DataSet = forBookTable
    Left = 136
    Top = 368
  end
  object RTFExport: TfrxRTFExport
    ShowDialog = False
    UseFileCache = True
    ShowProgress = True
    Wysiwyg = True
    Creator = 'FastReport http://www.fast-report.com'
    SuppressPageHeadersFooters = False
    HeaderFooterMode = hfText
    Left = 344
    Top = 96
  end
  object TempQ: TpFIBQuery
    Transaction = DT
    Database = SaleBookDM.DataBase
    Left = 400
    Top = 104
    qoAutoCommit = True
    qoStartTransaction = True
  end
  object DT: TpFIBTransaction
    Active = True
    DefaultDatabase = SaleBookDM.DataBase
    TimeoutAction = TARollback
    Left = 832
    Top = 176
  end
  object AccountsT: TpFIBTransaction
    Active = True
    DefaultDatabase = SaleBookDM.DataBase
    TimeoutAction = TARollback
    Left = 552
    Top = 200
  end
  object frxTableDS1: TfrxDBDataset
    UserName = 'frxTableDS1'
    CloseDataSource = False
    FieldAliases.Strings = (
      'OPS=OPS'
      'COUNT_TOTAL=COUNT_TOTAL'
      'COUNT_OPL=COUNT_OPL'
      'COUNT_NEOPL=COUNT_NEOPL'
      'COUNT_TOTALI=COUNT_TOTALI'
      'COUNT_OPLI=COUNT_OPLI'
      'COUNT_NEOPLI=COUNT_NEOPLI'
      'COUNT_TEK=COUNT_TEK'
      'COUNT_PR=COUNT_PR'
      'COUNT_RAZ=COUNT_RAZ'
      'COUNT_NEOPLP=COUNT_NEOPLP'
      'COUNT_FI=COUNT_FI'
      'COUNT_FD=COUNT_FD'
      'COUNT_NEOPLG=COUNT_NEOPLG'
      'COUNT_OPLM=COUNT_OPLM'
      'COUNT_OPLT=COUNT_OPLT'
      'COUNT_OPLR=COUNT_OPLR')
    DataSet = DSREPRES
    Left = 408
    Top = 360
  end
  object DSREPRES: TpFIBDataSet
    SelectSQL.Strings = (
      'SELECT *'
      'FROM'
      '    REPRES ')
    Transaction = TT
    Database = SaleBookDM.DataBase
    AutoCommit = True
    Left = 400
    Top = 240
    object DSREPRESOPS: TFIBIntegerField
      FieldName = 'OPS'
    end
    object DSREPRESCOUNT_TOTAL: TFIBFloatField
      FieldName = 'COUNT_TOTAL'
    end
    object DSREPRESCOUNT_OPL: TFIBFloatField
      FieldName = 'COUNT_OPL'
    end
    object DSREPRESCOUNT_NEOPL: TFIBFloatField
      FieldName = 'COUNT_NEOPL'
    end
    object DSREPRESCOUNT_TOTALI: TFIBIntegerField
      FieldName = 'COUNT_TOTALI'
    end
    object DSREPRESCOUNT_OPLI: TFIBIntegerField
      FieldName = 'COUNT_OPLI'
    end
    object DSREPRESCOUNT_NEOPLI: TFIBIntegerField
      FieldName = 'COUNT_NEOPLI'
    end
    object DSREPRESCOUNT_TEK: TFIBFloatField
      FieldName = 'COUNT_TEK'
    end
    object DSREPRESCOUNT_PR: TFIBFloatField
      FieldName = 'COUNT_PR'
    end
    object DSREPRESCOUNT_RAZ: TFIBFloatField
      FieldName = 'COUNT_RAZ'
    end
    object DSREPRESCOUNT_NEOPLP: TFIBFloatField
      FieldName = 'COUNT_NEOPLP'
    end
    object DSREPRESCOUNT_FI: TFIBIntegerField
      FieldName = 'COUNT_FI'
    end
    object DSREPRESCOUNT_FD: TFIBFloatField
      FieldName = 'COUNT_FD'
    end
    object DSREPRESCOUNT_NEOPLG: TFIBIntegerField
      FieldName = 'COUNT_NEOPLG'
    end
    object DSREPRESCOUNT_OPLM: TFIBIntegerField
      FieldName = 'COUNT_OPLM'
    end
    object DSREPRESCOUNT_OPLT: TFIBIntegerField
      FieldName = 'COUNT_OPLT'
    end
    object DSREPRESCOUNT_OPLR: TFIBIntegerField
      FieldName = 'COUNT_OPLR'
    end
  end
  object DSSved: TpFIBDataSet
    SelectSQL.Strings = (
      'SELECT *'
      'FROM'
      '    SGB'
      'ORDER BY LCHET ')
    Transaction = TT
    Database = SaleBookDM.DataBase
    AutoCommit = True
    Left = 392
    Top = 168
  end
  object ADOConnection: TADOConnection
    ConnectionString = 'FILE NAME=C:\MAR\Project\SB_2009\SOURCE\dbf.dsn;'
    LoginPrompt = False
    Mode = cmReadWrite
    Provider = 'MSDASQL.1'
    Left = 344
    Top = 24
  end
  object Q: TADOQuery
    Connection = ADOConnection
    CursorType = ctStatic
    EnableBCD = False
    Parameters = <>
    Left = 408
    Top = 24
  end
  object ZipBuilder: TZipBuilder
    VersionInfo = '1.73'
    AddStoreSuffixes = [assGIF, assPNG, assZ, assZIP, assZOO, assARC, assLZH, assARJ, assTAZ, assTGZ, assLHA, assRAR, assACE, assCAB, assGZ, assGZIP, assJAR]
    SFXOptions = [SFXCheckSize]
    SFXPath = 'ZipSFX.bin'
    SFXCaption = 'Self-extracting Archive'
    Left = 72
    Top = 40
  end
  object ExportDS: TpFIBDataSet
    SelectSQL.Strings = (
      'SELECT *'
      'FROM'
      '    SGB ')
    Transaction = TT
    Database = SaleBookDM.DataBase
    AutoCommit = True
    Left = 256
    Top = 112
  end
  object ExportDS1: TpFIBDataSet
    SelectSQL.Strings = (
      'SELECT *'
      'FROM'
      '    NDOST ')
    Transaction = TT
    Database = SaleBookDM.DataBase
    AutoCommit = True
    Left = 408
    Top = 280
    object ExportDS1LCHET1: TFIBStringField
      FieldName = 'LCHET1'
      Size = 10
      EmptyStrToNull = True
    end
    object ExportDS1SUMMA: TFIBFloatField
      FieldName = 'SUMMA'
    end
    object ExportDS1WORD: TFIBStringField
      FieldName = 'WORD'
      EmptyStrToNull = True
    end
    object ExportDS1METKA: TFIBIntegerField
      FieldName = 'METKA'
    end
    object ExportDS1NEOPL: TFIBIntegerField
      FieldName = 'NEOPL'
    end
    object ExportDS1PNN: TFIBIntegerField
      FieldName = 'PNN'
    end
    object ExportDS1LCHET: TFIBIntegerField
      FieldName = 'LCHET'
    end
    object ExportDS1FAMILY: TFIBStringField
      FieldName = 'FAMILY'
      EmptyStrToNull = True
    end
    object ExportDS1NAME: TFIBStringField
      FieldName = 'NAME'
      EmptyStrToNull = True
    end
    object ExportDS1FATHER: TFIBStringField
      FieldName = 'FATHER'
      EmptyStrToNull = True
    end
    object ExportDS1KOD: TFIBIntegerField
      FieldName = 'KOD'
    end
    object ExportDS1C: TFIBDateField
      FieldName = 'C'
      DisplayFormat = 'dd.mm.yyyy'
    end
    object ExportDS1DOC: TFIBDateField
      FieldName = 'DOC'
      DisplayFormat = 'dd.mm.yyyy'
    end
    object ExportDS1SERIA: TFIBStringField
      FieldName = 'SERIA'
      Size = 8
      EmptyStrToNull = True
    end
    object ExportDS1NOMER: TFIBIntegerField
      FieldName = 'NOMER'
    end
    object ExportDS1DOST: TFIBIntegerField
      FieldName = 'DOST'
    end
    object ExportDS1D_VIPL: TFIBIntegerField
      FieldName = 'D_VIPL'
    end
    object ExportDS1ULIC: TFIBStringField
      FieldName = 'ULIC'
      EmptyStrToNull = True
    end
    object ExportDS1ADRES: TFIBStringField
      FieldName = 'ADRES'
      Size = 14
      EmptyStrToNull = True
    end
    object ExportDS1CHEL: TFIBIntegerField
      FieldName = 'CHEL'
    end
    object ExportDS1METKA1: TFIBIntegerField
      FieldName = 'METKA1'
    end
    object ExportDS1VNOM: TFIBIntegerField
      FieldName = 'VNOM'
    end
    object ExportDS1PRICH: TFIBStringField
      FieldName = 'PRICH'
      Size = 6
      EmptyStrToNull = True
    end
    object ExportDS1IST: TFIBIntegerField
      FieldName = 'IST'
    end
    object ExportDS1BSUMMA: TFIBIntegerField
      FieldName = 'BSUMMA'
    end
    object ExportDS1BWORD: TFIBStringField
      FieldName = 'BWORD'
      Size = 11
      EmptyStrToNull = True
    end
    object ExportDS1FAKT_CHEL: TFIBIntegerField
      FieldName = 'FAKT_CHEL'
    end
    object ExportDS1FAKT_DAT: TFIBIntegerField
      FieldName = 'FAKT_DAT'
    end
    object ExportDS1NSP: TFIBIntegerField
      FieldName = 'NSP'
    end
    object ExportDS1KEM_VID: TFIBStringField
      FieldName = 'KEM_VID'
      Size = 40
      EmptyStrToNull = True
    end
    object ExportDS1DATA_VID: TFIBDateField
      FieldName = 'DATA_VID'
      DisplayFormat = 'dd.mm.yyyy'
    end
    object ExportDS1DOBAVL: TFIBSmallIntField
      DefaultExpression = '0'
      FieldName = 'DOBAVL'
    end
    object ExportDS1KODPEN: TFIBIntegerField
      FieldName = 'KODPEN'
    end
    object ExportDS1FOND: TFIBIntegerField
      FieldName = 'FOND'
    end
    object ExportDS1M: TFIBIntegerField
      FieldName = 'M'
    end
    object ExportDS1Y: TFIBIntegerField
      FieldName = 'Y'
    end
  end
  object frxReport1: TfrxReport
    Version = '3.24'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbPageSetup, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1
    PrintOptions.Printer = 'Default'
    ReportOptions.CreateDate = 38397.4759206713
    ReportOptions.LastChange = 43817.6987527199
    ScriptLanguage = 'C++Script'
    ScriptText.Strings = (
      '{'
      '}')
    StoreInDFM = False
    OnGetValue = frxReportGetValue
    Left = 16
    Top = 64
    Datasets = <
      item
        DataSet = frxHeadDS
        DataSetName = 'frxHeadDS'
      end
      item
        DataSet = frxTableDS
        DataSetName = 'frxTableDS'
      end
      item
        DataSet = frxTableDS1
        DataSetName = 'frxTableDS1'
      end>
    Variables = <
      item
        Name = ' MyVariables'
        Value = Null
      end
      item
        Name = 'TwoCopysOnPage'
        Value = Null
      end>
    Style = <>
  end
  object frxReport2: TfrxReport
    Version = '3.24'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbPageSetup, pbNavigator]
    PreviewOptions.Zoom = 1
    PrintOptions.Printer = 'Default'
    ReportOptions.CreateDate = 40567.4935903125
    ReportOptions.LastChange = 43733.6270747569
    ScriptLanguage = 'C++Script'
    ScriptText.Strings = (
      ''
      '{'
      ''
      '}')
    StoreInDFM = False
    OnGetValue = frxReportGetValue
    Left = 16
    Top = 112
    Datasets = <
      item
        DataSet = DSSvod
        DataSetName = 'DSSvod'
      end>
    Variables = <>
    Style = <>
  end
  object frxReport3: TfrxReport
    Version = '3.24'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbPageSetup, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1
    PrintOptions.Printer = 'Default'
    ReportOptions.CreateDate = 38397.4759206713
    ReportOptions.LastChange = 43992.6008207407
    ScriptLanguage = 'C++Script'
    ScriptText.Strings = (
      ''
      '{'
      ''
      '}')
    StoreInDFM = False
    OnGetValue = frxReport3GetValue
    Left = 16
    Top = 168
    Datasets = <
      item
        DataSet = frxPotrDS
        DataSetName = 'frxPotrDS'
      end>
    Variables = <
      item
        Name = ' MyVariables'
        Value = Null
      end
      item
        Name = 'TwoCopysOnPage'
        Value = Null
      end>
    Style = <>
  end
  object PotrDS: TpFIBDataSet
    SelectSQL.Strings = (
      'SELECT * '
      'FROM'
      '    ACCOUNTS ')
    Transaction = HT
    Database = SaleBookDM.DataBase
    AutoCommit = True
    Left = 144
    Top = 296
  end
  object frxPotrDS: TfrxDBDataset
    UserName = 'frxPotrDS'
    CloseDataSource = False
    FieldAliases.Strings = (
      'DATEKOL=DATEKOL'
      'KOLV=KOLV'
      'SUMV=SUMV')
    DataSet = PotrDS
    Left = 264
    Top = 408
  end
  object FormStorage1: TFormStorage
    StoredValues = <>
    Left = 592
    Top = 48
  end
  object ConstTransaction: TpFIBTransaction
    DefaultDatabase = SaleBookDM.DataBase
    TimeoutAction = TARollback
    Left = 520
    Top = 96
  end
  object ConstProc: TpFIBStoredProc
    Transaction = ConstTransaction
    Database = SaleBookDM.DataBase
    Left = 504
    Top = 32
    qoAutoCommit = True
    qoStartTransaction = True
  end
end
