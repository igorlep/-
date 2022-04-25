object OrganizationSelectForm: TOrganizationSelectForm
  Left = 236
  Top = 138
  Width = 520
  Height = 233
  Caption = #1042#1099#1073#1086#1088' '#1086#1088#1075#1072#1085#1080#1079#1072#1094#1080#1080
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010001001010100000000000280100001600000028000000100000002000
    00000100040000000000C0000000000000000000000000000000000000000000
    000000008000008000000080800080000000800080008080000080808000C0C0
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF008778
    7777777777777778777777777777FFFFF90FFFFFFFFF77789990777777777778
    999077777777FFF999990FFFFFFFCC9999990CCCCCCCC8990C9990CCCCCC8908
    CCC990CCCCCCCCC8CCC9990CCCCCFFFFFFFF990FFFFF77787777799077777778
    777777907777FFFFFFFFFFF90FFF777877777777990777787777777777770000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  OldCreateOrder = False
  Scaled = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 16
  object Panel1: TPanel
    Left = 0
    Top = 158
    Width = 512
    Height = 41
    Align = alBottom
    TabOrder = 0
    DesignSize = (
      512
      41)
    object SelectButton: TBitBtn
      Left = 271
      Top = 8
      Width = 105
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1042#1099#1073#1088#1072#1090#1100
      TabOrder = 0
      OnClick = SelectButtonClick
      Glyph.Data = {
        F6000000424DF600000000000000760000002800000010000000100000000100
        0400000000008000000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00877877777777
        77777778777777777777FFFFF90FFFFFFFFF7778999077777777777899907777
        7777FFF999990FFFFFFFCC9999990CCCCCCCC8990C9990CCCCCC8908CCC990CC
        CCCCCCC8CCC9990CCCCCFFFFFFFF990FFFFF7778777779907777777877777790
        7777FFFFFFFFFFF90FFF77787777777799077778777777777777}
    end
    object CancelButton: TBitBtn
      Left = 395
      Top = 8
      Width = 107
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1054#1090#1082#1072#1079#1072#1090#1100#1089#1103
      TabOrder = 1
      OnClick = CancelButtonClick
      Glyph.Data = {
        F6000000424DF600000000000000760000002800000010000000100000000100
        0400000000008000000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
        8888888888888888888888818888888888988899188888888888889991888888
        8988888999888888988888889918888998888888899188998888888888999998
        8888888888899988888888888899991888888888899988918888888999988889
        1888889999888888998888999888888888988888888888888888}
    end
  end
  object OrganizationsGrid: TDBGridEh
    Left = 0
    Top = 0
    Width = 512
    Height = 158
    Align = alClient
    AutoFitColWidths = True
    DataSource = OrgSource
    FooterColor = clWindow
    FooterFont.Charset = DEFAULT_CHARSET
    FooterFont.Color = clWindowText
    FooterFont.Height = -13
    FooterFont.Name = 'MS Sans Serif'
    FooterFont.Style = []
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ReadOnly = True
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -13
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    Columns = <
      item
        Alignment = taCenter
        EditButtons = <>
        FieldName = 'ID'
        Footers = <>
        Title.Alignment = taCenter
      end
      item
        EditButtons = <>
        FieldName = 'NAME'
        Footers = <>
        Title.Alignment = taCenter
        Width = 415
      end>
  end
  object FormStorage1: TFormStorage
    StoredValues = <>
    Left = 304
    Top = 48
  end
  object OrgDS: TpFIBDataSet
    SelectSQL.Strings = (
      'SELECT'
      '    ID,'
      '    NAME'
      'FROM'
      '    ORGANIZATIONS '
      'WHERE ((DELETE_FLG IS NULL) OR (DELETE_FLG=0))')
    Transaction = OrgT
    Database = SaleBookDM.DataBase
    Left = 160
    Top = 48
  end
  object OrgT: TpFIBTransaction
    DefaultDatabase = SaleBookDM.DataBase
    TimeoutAction = TARollback
    Left = 128
    Top = 48
  end
  object OrgSource: TDataSource
    DataSet = OrgDS
    Left = 192
    Top = 48
  end
end
