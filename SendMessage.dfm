object SendMessForm: TSendMessForm
  Left = 784
  Top = 364
  Width = 816
  Height = 225
  Caption = #1054#1090#1087#1088#1072#1074#1082#1072' '#1089#1086#1086#1073#1097#1077#1085#1080#1103
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 798
    Height = 130
    Align = alClient
    BevelOuter = bvNone
    BorderStyle = bsSingle
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 0
    object Label1: TLabel
      Left = 20
      Top = 32
      Width = 119
      Height = 20
      Alignment = taRightJustify
      AutoSize = False
      Caption = #1057#1086#1086#1073#1097#1077#1085#1080#1077
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -17
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object OldPassword: TEdit
      Left = 146
      Top = 30
      Width = 633
      Height = 22
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -17
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
    end
    object CheckBox1: TCheckBox
      Left = 337
      Top = 62
      Width = 285
      Height = 20
      Caption = #1042#1089#1077#1084' '#1072#1082#1090#1080#1074#1085#1099#1084' '#1087#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1103#1084
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 130
    Width = 798
    Height = 50
    Align = alBottom
    TabOrder = 1
    DesignSize = (
      798
      50)
    object SaveButton: TBitBtn
      Left = 639
      Top = 10
      Width = 144
      Height = 29
      Anchors = [akTop, akRight]
      Caption = #1054#1090#1087#1088#1072#1074#1080#1090#1100
      TabOrder = 0
      OnClick = SaveButtonClick
      Glyph.Data = {
        F6000000424DF600000000000000760000002800000010000000100000000100
        0400000000008000000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FF000FFFFFF0
        00FFFF0F0FF00FF0F0FFF0000000000000FFFF0000000000000FF000000000CC
        CC0F0111111100CCC00F0111111100CEEFFF099999990000FFFF0EEEEEE10FFF
        FFFF0CCCCC110FFFFFFF011111110FFFFFFF011111110FFFFFFFF0000000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
    end
    object CancelButton: TBitBtn
      Left = 799
      Top = 10
      Width = 132
      Height = 29
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
  object Q: TpFIBQuery
    Transaction = T
    Database = SaleBookDM.DataBase
    Left = 96
    Top = 64
    qoAutoCommit = True
    qoStartTransaction = True
  end
  object T: TpFIBTransaction
    Active = True
    DefaultDatabase = SaleBookDM.DataBase
    TimeoutAction = TARollback
    Left = 128
    Top = 64
  end
  object UMDataSet: TpFIBDataSet
    Left = 192
    Top = 64
  end
end
