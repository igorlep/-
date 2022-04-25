object ActionsJournalForm: TActionsJournalForm
  Left = 435
  Top = 471
  Width = 973
  Height = 590
  Caption = #1046#1091#1088#1085#1072#1083' '#1089#1086#1073#1099#1090#1080#1081
  Color = clWindow
  Ctl3D = False
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  OnClose = FormClose
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 955
    Height = 26
    Align = alTop
    BevelOuter = bvNone
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 0
    DesignSize = (
      955
      26)
    object ExitButton: TSpeedButton
      Left = 938
      Top = 3
      Width = 20
      Height = 20
      Hint = #1042#1099#1093#1086#1076
      Anchors = [akTop, akRight]
      Glyph.Data = {
        F6000000424DF600000000000000760000002800000010000000100000000100
        0400000000008000000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFF00FF00F08
        0070F00FF00FF00870070000000008087700FFFFFF0880087770FFFFFF000008
        7770FFFFFF0777087770FFFFFF0777087770FF00000007080770FF0999990708
        7770F099999077087770F090990777087770F000900777087770FFF00F077770
        8770FFFFFF0777770870FFFFFF0777777080FFFFFF0000000000}
      ParentShowHint = False
      ShowHint = True
      OnClick = ExitButtonClick
    end
    object SelectButton: TSpeedButton
      Left = 4
      Top = 3
      Width = 20
      Height = 20
      Hint = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1086#1090#1073#1086#1088' '#1079#1072#1087#1080#1089#1077#1081
      Flat = True
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        0400000000000001000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
        CFFFFFFFFFFFFFFF8FFFFFFFCFFFCCCCCCFFFFFF8FFF888888FFCCCCCCFFCCCC
        CCCF888888FF8888888FCCCCCCCFCCCCCCCC8888888F88888888CCCCCCFFCCCC
        CCCF888888FF8888888FFFFFCFFFCCCCCCFFFFFF8FFF888888FFFFFF9FFFFFFF
        CFFFFFFF8FFFFFFF8FFF999999FFFFFFFFFF888888FFFFFFFFFF9999999FFFFF
        FFFF8888888FFFFFFFFF999999FFFFFFFFFF888888FFFFFFFFFFFFFF9FFFFFFF
        FFFFFFFF8FFFFFFFFFFFFFFF2FFFFFFFFFFFFFFF8FFFFFFFFFFF222222FFFFFF
        FFFF888888FFFFFFFFFF2222222FFFFFFFFF8888888FFFFFFFFF222222FFFFFF
        FFFF888888FFFFFFFFFFFFFF2FFFFFFFFFFFFFFF8FFFFFFFFFFF}
      NumGlyphs = 2
      ParentShowHint = False
      ShowHint = True
      OnClick = SelectButtonClick
    end
    object UnSelectButton: TSpeedButton
      Left = 28
      Top = 3
      Width = 20
      Height = 20
      Hint = #1054#1090#1084#1077#1085#1080#1090#1100' '#1086#1090#1073#1086#1088' '#1079#1072#1087#1080#1089#1077#1081
      Flat = True
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        0400000000000001000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFF99FF
        CF99FFFFFFFF88FF8F88FFFFCFFFC99CCC99FFFF8FFF88888888CCCCCCFFCC99
        C99F888888FF8888888FCCCCCCCFCCC999CC8888888F88888888CCCCCCFFCCC9
        99CF888888FF8888888FFFFFCFFFCC99C99FFFFF8FFF8888888FFFFF9FFFF99F
        CF99FFFF8FFFF88F8F88999999FF99FFFF99888888FF88FFFF889999999FFFFF
        FFFF8888888FFFFFFFFF999999FFFFFFFFFF888888FFFFFFFFFFFFFF9FFFFFFF
        FFFFFFFF8FFFFFFFFFFFFFFF2FFFFFFFFFFFFFFF8FFFFFFFFFFF222222FFFFFF
        FFFF888888FFFFFFFFFF2222222FFFFFFFFF8888888FFFFFFFFF222222FFFFFF
        FFFF888888FFFFFFFFFFFFFF2FFFFFFFFFFFFFFF8FFFFFFFFFFF}
      NumGlyphs = 2
      ParentShowHint = False
      ShowHint = True
      OnClick = UnSelectButtonClick
    end
  end
  object Grid: TDBGridEh
    Left = 0
    Top = 26
    Width = 955
    Height = 519
    Align = alClient
    AutoFitColWidths = True
    Ctl3D = False
    DataSource = ActionsSource
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
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    OptionsEh = [dghHighlightFocus, dghClearSelection]
    ParentCtl3D = False
    ParentFont = False
    ReadOnly = True
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    UseMultiTitle = True
    Columns = <
      item
        Alignment = taCenter
        AutoFitColWidth = False
        EditButtons = <>
        FieldName = 'ACTION_DATE'
        Footers = <>
        Title.Caption = #1044#1072#1090#1072' '#1089#1086#1073#1099#1090#1080#1103
        Width = 62
      end
      item
        Alignment = taCenter
        AutoFitColWidth = False
        EditButtons = <>
        FieldName = 'ACTION_TIME'
        Footers = <>
        Title.Caption = #1042#1088#1077#1084#1103' '#1089#1086#1073#1099#1090#1080#1103
        Width = 60
      end
      item
        Alignment = taCenter
        AutoFitColWidth = False
        EditButtons = <>
        FieldName = 'UserName'
        Footers = <>
        Title.Caption = #1055#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1100
        Width = 97
      end
      item
        Alignment = taCenter
        AutoFitColWidth = False
        EditButtons = <>
        FieldName = 'UserRole'
        Footers = <>
        Title.Caption = #1056#1086#1083#1100' '#1087#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1103
        Width = 99
      end
      item
        Alignment = taCenter
        AutoFitColWidth = False
        EditButtons = <>
        FieldName = 'NET_NAME'
        Footers = <>
        Title.Caption = #1057#1077#1090#1077#1074#1086#1077' '#1080#1084#1103' '#1087#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1103
        Width = 101
      end
      item
        EditButtons = <>
        FieldName = 'ACTION_TEXT'
        Footers = <>
        Title.Caption = #1057#1086#1073#1099#1090#1080#1077
        Width = 211
      end>
  end
  object FormStorage1: TFormStorage
    IniSection = 'AccountsJournalForm'
    StoredValues = <>
    Left = 360
    Top = 96
  end
  object ActionsDS: TpFIBDataSet
    SelectSQL.Strings = (
      'SELECT'
      '    ID,'
      '    ACTION_DATE,'
      '    ACTION_TIME,'
      '    ACTION_TYPE,'
      '    ACTION_TEXT,'
      '    USER_ID,'
      '    USER_NAME,'
      '    USER_ROLE,'
      '    NET_NAME'
      'FROM'
      '    ACTIONS_JOURNAL ')
    Transaction = AT
    Database = SaleBookDM.DataBase
    AutoCommit = True
    Left = 112
    Top = 88
  end
  object ActionsSource: TDataSource
    DataSet = ActionsDS
    Left = 144
    Top = 88
  end
  object AT: TpFIBTransaction
    DefaultDatabase = SaleBookDM.DataBase
    TimeoutAction = TARollback
    Left = 80
    Top = 88
  end
end
