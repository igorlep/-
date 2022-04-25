object EditNomenclatuteForm: TEditNomenclatuteForm
  Left = 925
  Top = 462
  Width = 572
  Height = 217
  ActiveControl = EIEdit
  BorderIcons = []
  Caption = #1059#1095#1072#1089#1090#1086#1082
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object Panel2: TPanel
    Left = 0
    Top = 131
    Width = 554
    Height = 41
    Align = alBottom
    TabOrder = 0
    DesignSize = (
      554
      41)
    object SaveButton: TBitBtn
      Left = 314
      Top = 8
      Width = 117
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      TabOrder = 0
      OnClick = SaveButtonClick
      Glyph.Data = {
        F6000000424DF600000000000000760000002800000010000000100000000100
        0400000000008000000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
        8888880000000000000880330000008803088033000000880308803300000088
        0308803300000000030880333333333333088033000000003308803088888888
        0308803088888888030880308888888803088030888888880308803088888888
        0008803088888888080880000000000000088888888888888888}
    end
    object CancelButton: TBitBtn
      Left = 446
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
  object SmrtPanel1: TSmrtPanel
    Left = 0
    Top = 0
    Width = 554
    Height = 131
    Align = alClient
    TabOrder = 1
    object Label1: TLabel
      Tag = 15
      Left = 8
      Top = 24
      Width = 169
      Height = 16
      Alignment = taRightJustify
      AutoSize = False
      Caption = #1050#1086#1076
    end
    object Label2: TLabel
      Tag = 15
      Left = 8
      Top = 54
      Width = 169
      Height = 16
      Alignment = taRightJustify
      AutoSize = False
      Caption = #1053#1086#1084#1077#1088' '#1091#1095#1072#1089#1090#1082#1072
    end
    object Label3: TLabel
      Tag = 15
      Left = 10
      Top = 82
      Width = 169
      Height = 16
      Alignment = taRightJustify
      AutoSize = False
      Caption = #1060#1048#1054' '#1087#1086#1095#1090#1072#1083#1100#1086#1085#1072
    end
    object Label4: TLabel
      Tag = 15
      Left = 10
      Top = 108
      Width = 169
      Height = 16
      Alignment = taRightJustify
      AutoSize = False
      Caption = #1050#1086#1076' '#1087#1086#1095#1090#1072#1083#1100#1086#1085#1072
    end
    object EIEdit: TDBEditEh
      Tag = 15
      Left = 185
      Top = 78
      Width = 361
      Height = 24
      DataField = 'EI'
      DataSource = DSource
      EditButtons = <
        item
          Style = ebsEllipsisEh
          OnClick = DBEditEh1EditButtons0Click
        end>
      TabOrder = 0
      Visible = True
    end
    object IDEdit: TDBEditEh
      Tag = 15
      Left = 184
      Top = 20
      Width = 57
      Height = 24
      DataField = 'ID'
      DataSource = DSource
      EditButtons = <>
      Enabled = False
      ReadOnly = True
      TabOrder = 1
      Visible = True
      OnKeyPress = IDEditKeyPress
    end
    object NameEdit: TDBEditEh
      Tag = 15
      Left = 185
      Top = 50
      Width = 33
      Height = 24
      DataField = 'Description'
      DataSource = DSource
      EditButtons = <>
      TabOrder = 2
      Visible = True
      OnKeyPress = NameEditKeyPress
    end
    object CODPEdit: TDBEditEh
      Tag = 15
      Left = 185
      Top = 106
      Width = 160
      Height = 24
      DataField = 'CODP'
      DataSource = DSource
      EditButtons = <>
      ReadOnly = True
      TabOrder = 3
      Visible = True
      OnKeyPress = NameEditKeyPress
    end
  end
  object DSource: TDataSource
    DataSet = DS
    Left = 16
    Top = 16
  end
  object FormStorage1: TFormStorage
    IniFileName = '.\MySB.ini'
    IniSection = 'EditNomeclatureForm'
    StoredValues = <>
    Left = 336
    Top = 32
  end
  object DS: TpFIBDataSet
    UpdateSQL.Strings = (
      'UPDATE NOMENCLATURE'
      'SET '
      '    DESCRIPTION = :DESCRIPTION,'
      '    EI = :EI,'
      '    CODP = :CODP'
      'WHERE'
      '    ID = :OLD_ID'
      '    ')
    RefreshSQL.Strings = (
      'SELECT'
      '    ID,'
      '    FILE_ID,'
      '    REC_TYPE,'
      '    DESCRIPTION,'
      '    EI,'
      '    CODP'
      'FROM'
      '    NOMENCLATURE '
      ''
      ' WHERE '
      '        NOMENCLATURE.ID = :OLD_ID'
      '    ')
    SelectSQL.Strings = (
      'SELECT'
      '    ID,'
      '    FILE_ID,'
      '    REC_TYPE,'
      '    DESCRIPTION,'
      '    EI,'
      '    CODP,'
      '    INDEXOPS'
      'FROM'
      '    NOMENCLATURE ')
    BeforeEdit = DSBeforeEdit
    Transaction = EditTransaction
    Database = SaleBookDM.DataBase
    Left = 16
    Top = 64
    object DSID: TFIBIntegerField
      FieldName = 'ID'
    end
    object DSFILE_ID: TFIBIntegerField
      FieldName = 'FILE_ID'
    end
    object DSREC_TYPE: TFIBSmallIntField
      FieldName = 'REC_TYPE'
    end
    object DSDESCRIPTION: TFIBStringField
      FieldName = 'DESCRIPTION'
      Size = 120
      EmptyStrToNull = True
    end
    object DSEI: TFIBStringField
      FieldName = 'EI'
      Size = 50
      EmptyStrToNull = True
    end
    object DSCODP: TFIBIntegerField
      FieldName = 'CODP'
    end
    object DSINDEXOPS: TFIBIntegerField
      FieldName = 'INDEXOPS'
    end
  end
  object EditTransaction: TpFIBTransaction
    Active = True
    DefaultDatabase = SaleBookDM.DataBase
    TimeoutAction = TARollback
    Left = 64
    Top = 16
  end
end
