object ActsListForm: TActsListForm
  Left = 493
  Top = 222
  Width = 1024
  Height = 653
  Caption = #1057#1087#1080#1089#1086#1082' '#1076#1086' '#1074#1086#1089#1090#1088#1077#1073#1086#1074#1072#1085#1080#1103
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  OnActivate = FormActivate
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object ButtonsPanel: TPanel
    Left = 0
    Top = 0
    Width = 1006
    Height = 32
    Align = alTop
    TabOrder = 0
    DesignSize = (
      1006
      32)
    object ExitButton: TSpeedButton
      Left = 980
      Top = 6
      Width = 20
      Height = 20
      Hint = #1055#1077#1095#1072#1090#1100' '#1072#1082#1090#1072
      Anchors = [akTop, akRight]
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
      ParentShowHint = False
      ShowHint = True
      OnClick = ExitButtonClick
    end
    object SaveButton: TSpeedButton
      Left = 11
      Top = 6
      Width = 20
      Height = 20
      Hint = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1079#1072#1087#1080#1089#1100
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
      OnClick = SaveButtonClick
    end
    object DelButton: TSpeedButton
      Left = 35
      Top = 6
      Width = 20
      Height = 20
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
      OnClick = DelButtonClick
    end
    object Label1: TLabel
      Left = 472
      Top = 0
      Width = 141
      Height = 30
      Alignment = taCenter
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = #1055#1086#1080#1089#1082' '#1076#1077#1083#1072' '#1087#1086' '#1085#1086#1084#1077#1088#1091' '#1080#1083#1080' '#1060#1072#1084#1080#1083#1080#1102
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      WordWrap = True
    end
    object Edit1: TEdit
      Left = 623
      Top = 6
      Width = 100
      Height = 22
      Hint = #1055#1086#1080#1089#1082' '#1087#1086' '#1085#1086#1084#1077#1088#1091' '#1089#1095#1077#1090#1072
      Anchors = [akTop, akRight]
      Constraints.MaxWidth = 100
      Constraints.MinWidth = 60
      Ctl3D = False
      ParentCtl3D = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      OnChange = Edit1Change
      OnKeyPress = Edit1KeyPress
    end
  end
  object Grid: TDBGridEh
    Left = 0
    Top = 32
    Width = 1006
    Height = 576
    Align = alClient
    AllowedOperations = [alopDeleteEh, alopAppendEh]
    Color = clWhite
    Ctl3D = False
    DataSource = AS
    Flat = True
    FooterColor = clMoneyGreen
    FooterFont.Charset = DEFAULT_CHARSET
    FooterFont.Color = clWindowText
    FooterFont.Height = -13
    FooterFont.Name = 'MS Sans Serif'
    FooterFont.Style = []
    FooterRowCount = 1
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit]
    OptionsEh = [dghFooter3D, dghHighlightFocus, dghClearSelection, dghRowHighlight]
    ParentCtl3D = False
    ParentShowHint = False
    ShowHint = False
    SumList.Active = True
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -13
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    UseMultiTitle = True
    OnCellClick = GridCellClick
    Columns = <
      item
        Alignment = taCenter
        EditButtons = <>
        FieldName = 'LCHET'
        Footer.Alignment = taCenter
        Footer.DisplayFormat = '#0'
        Footer.FieldName = 'LCHET'
        Footer.Font.Charset = DEFAULT_CHARSET
        Footer.Font.Color = clRed
        Footer.Font.Height = -13
        Footer.Font.Name = 'MS Sans Serif'
        Footer.Font.Style = [fsBold]
        Footer.ValueType = fvtCount
        Footers = <>
        MaxWidth = 80
        MinWidth = 60
        Title.Caption = #8470' '#1076#1077#1083#1072
      end
      item
        EditButtons = <>
        FieldName = 'FAMILY'
        Footers = <>
        MaxWidth = 120
        MinWidth = 60
        Title.Caption = #1060#1072#1084#1080#1083#1080#1103
        Width = 120
      end
      item
        EditButtons = <>
        FieldName = 'NAME'
        Footers = <>
        MaxWidth = 120
        MinWidth = 60
        Title.Caption = #1048#1084#1103
        Width = 120
      end
      item
        EditButtons = <>
        FieldName = 'FATHER'
        Footers = <>
        MaxWidth = 120
        MinWidth = 60
        Title.Caption = #1054#1090#1095#1077#1089#1090#1074#1086
        Width = 120
      end
      item
        EditButtons = <>
        FieldName = 'SERIA'
        Footers = <>
        MaxWidth = 100
        MinWidth = 50
        Title.Caption = #1057#1077#1088#1080#1103
      end
      item
        Alignment = taLeftJustify
        EditButtons = <>
        FieldName = 'NOMER'
        Footers = <>
        MaxWidth = 100
        MinWidth = 50
        Title.Caption = #1053#1086#1084#1077#1088
      end
      item
        Alignment = taLeftJustify
        EditButtons = <>
        FieldName = 'METKA1'
        Footers = <>
        MaxWidth = 60
        MinWidth = 30
        Title.Caption = #8470' '#1054#1055#1057
        Width = 60
      end
      item
        Alignment = taLeftJustify
        EditButtons = <>
        FieldName = 'DOST'
        Footers = <>
        MaxWidth = 40
        MinWidth = 20
        Title.Caption = #8470' '#1091#1095#1072#1089#1090#1082#1072
        Width = 40
      end
      item
        EditButtons = <>
        FieldName = 'ULIC'
        Footers = <>
        MaxWidth = 200
        MinWidth = 80
        Title.Caption = #1059#1083#1080#1094#1072
        Width = 200
      end
      item
        EditButtons = <>
        FieldName = 'ADRES'
        Footers = <>
        MaxWidth = 80
        MinWidth = 40
        Title.Caption = #1040#1076#1088#1077#1089
        Width = 80
      end
      item
        EditButtons = <>
        FieldName = 'USER_ID'
        Footers = <>
        Visible = False
      end>
  end
  object FormStorage: TFormStorage
    StoredValues = <>
    Left = 560
    Top = 104
  end
  object ADS: TpFIBDataSet
    CachedUpdates = True
    UpdateSQL.Strings = (
      '    ')
    DeleteSQL.Strings = (
      'DELETE FROM'
      '    DOV'
      'WHERE'
      '        LCHET = :OLD_LCHET'
      '    ')
    RefreshSQL.Strings = (
      ''
      '    ')
    SelectSQL.Strings = (
      'SELECT *'
      'FROM DOV'
      'ORDER BY FAMILY')
    Transaction = AT
    Database = SaleBookDM.DataBase
    AutoCommit = True
    Left = 56
    Top = 96
    oRefreshDeletedRecord = True
    object ADSUSER_ID: TFIBSmallIntField
      FieldName = 'USER_ID'
    end
    object ADSLCHET: TFIBIntegerField
      FieldName = 'LCHET'
    end
    object ADSFAMILY: TFIBStringField
      FieldName = 'FAMILY'
      EmptyStrToNull = True
    end
    object ADSNAME: TFIBStringField
      FieldName = 'NAME'
      EmptyStrToNull = True
    end
    object ADSFATHER: TFIBStringField
      FieldName = 'FATHER'
      EmptyStrToNull = True
    end
    object ADSSERIA: TFIBStringField
      FieldName = 'SERIA'
      Size = 8
      EmptyStrToNull = True
    end
    object ADSNOMER: TFIBIntegerField
      FieldName = 'NOMER'
    end
    object ADSDOST: TFIBIntegerField
      FieldName = 'DOST'
    end
    object ADSULIC: TFIBStringField
      FieldName = 'ULIC'
      EmptyStrToNull = True
    end
    object ADSADRES: TFIBStringField
      FieldName = 'ADRES'
      Size = 14
      EmptyStrToNull = True
    end
    object ADSMETKA1: TFIBIntegerField
      FieldName = 'METKA1'
    end
  end
  object AT: TpFIBTransaction
    Active = True
    DefaultDatabase = SaleBookDM.DataBase
    TimeoutAction = TARollback
    Left = 88
    Top = 96
  end
  object AS: TDataSource
    DataSet = ADS
    Left = 120
    Top = 96
  end
  object Q: TpFIBQuery
    Transaction = WT
    Database = SaleBookDM.DataBase
    Left = 56
    Top = 152
  end
  object WT: TpFIBTransaction
    Active = True
    DefaultDatabase = SaleBookDM.DataBase
    TimeoutAction = TARollback
    Left = 88
    Top = 152
  end
  object searchTimer: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = searchTimerTimer
    Left = 216
    Top = 128
  end
end
