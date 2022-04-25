object SelectFilterForm: TSelectFilterForm
  Left = 437
  Top = 389
  Width = 821
  Height = 243
  Caption = #1054#1090#1073#1086#1088' '#1087#1086' '#1091#1089#1083#1086#1074#1080#1102
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
  object Label1: TLabel
    Left = 0
    Top = 0
    Width = 803
    Height = 16
    Align = alTop
    Alignment = taCenter
    Caption = #1054#1090#1086#1073#1088#1072#1090#1100' '#1079#1072#1087#1080#1089#1080'  '#1074' '#1078#1091#1088#1085#1072#1083#1077' '#1087#1086#1088#1091#1095#1077#1085#1080#1081
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object Panel1: TPanel
    Left = 0
    Top = 168
    Width = 803
    Height = 30
    Align = alBottom
    BevelOuter = bvNone
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 0
    DesignSize = (
      803
      30)
    object selectButton: TJvXPButton
      Left = 620
      Top = 2
      Width = 81
      Caption = #1054#1090#1086#1073#1088#1072#1090#1100
      TabOrder = 0
      Glyph.Data = {
        F6000000424DF600000000000000760000002800000010000000100000000100
        0400000000008000000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
        CFFFFFFFCFFFCCCCCCFFCCCCCCFFCCCCCCCFCCCCCCCFCCCCCCCCCCCCCCFFCCCC
        CCCFFFFFCFFFCCCCCCFFFFFF9FFFFFFFCFFF999999FFFFFFFFFF9999999FFFFF
        FFFF999999FFFFFFFFFFFFFF9FFFFFFFFFFFFFFF2FFFFFFFFFFF222222FFFFFF
        FFFF2222222FFFFFFFFF222222FFFFFFFFFFFFFF2FFFFFFFFFFF}
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      OnClick = selectButtonClick
    end
    object cancelButton: TJvXPButton
      Left = 708
      Top = 2
      Width = 89
      Caption = #1054#1090#1082#1072#1079#1072#1090#1100#1089#1103
      TabOrder = 1
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
      OnClick = cancelButtonClick
    end
  end
  object SmrtPanel1: TSmrtPanel
    Left = 0
    Top = 16
    Width = 803
    Height = 152
    Align = alClient
    BevelOuter = bvNone
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 1
    object CustomerCheckBox: TCheckBox
      Tag = 12
      Left = 16
      Top = 16
      Width = 135
      Height = 17
      Alignment = taLeftJustify
      Caption = #1087#1086' '#1054#1055#1057
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnClick = CustomerCheckBoxClick
    end
    object UserCheckBox: TCheckBox
      Tag = 12
      Left = 16
      Top = 48
      Width = 135
      Height = 17
      Alignment = taLeftJustify
      Caption = #1087#1086' '#1091#1095#1072#1089#1090#1082#1091
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = UserCheckBoxClick
    end
    object autoNumberEdit1: TComboBox
      Left = 173
      Top = 45
      Width = 50
      Height = 21
      BevelKind = bkFlat
      Style = csDropDownList
      Ctl3D = False
      DropDownCount = 50
      ItemHeight = 13
      ParentCtl3D = False
      TabOrder = 2
      OnChange = autoNumberEdit1Change
    end
    object autoNumberEdit: TComboBox
      Left = 173
      Top = 13
      Width = 86
      Height = 21
      BevelKind = bkFlat
      Style = csDropDownList
      Ctl3D = False
      DropDownCount = 50
      ItemHeight = 13
      ParentCtl3D = False
      TabOrder = 3
      OnChange = autoNumberEditChange
    end
    object autoNumberEdit2: TComboBox
      Left = 173
      Top = 85
      Width = 274
      Height = 21
      BevelKind = bkFlat
      Style = csDropDownList
      Ctl3D = False
      DropDownCount = 50
      ItemHeight = 13
      ParentCtl3D = False
      TabOrder = 4
      OnChange = autoNumberEdit2Change
    end
    object PostCheckBox: TCheckBox
      Tag = 12
      Left = 16
      Top = 87
      Width = 135
      Height = 17
      Alignment = taLeftJustify
      Caption = #1087#1086' '#1087#1086#1095#1090#1072#1083#1100#1086#1085#1091
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
      OnClick = PostCheckBoxClick
    end
    object RadioGroup1: TRadioGroup
      Left = 472
      Top = 8
      Width = 281
      Height = 105
      Caption = #1054#1087#1083#1072#1090#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      Items.Strings = (
        '1.'#1054#1087#1083#1072#1095#1077#1085#1086
        '2.'#1053#1077#1086#1087#1083#1072#1095#1077#1085#1086)
      ParentFont = False
      TabOrder = 6
      OnClick = RadioGroup1Click
    end
    object CheckBox1: TCheckBox
      Left = 16
      Top = 120
      Width = 441
      Height = 17
      Caption = #1058#1086#1083#1100#1082#1086' '#1076#1086' '#1074#1086#1089#1090#1088#1077#1073#1086#1074#1072#1085#1080#1103' '#1080' '#1085#1077#1090' '#1076#1086#1084#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -17
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
      TabOrder = 7
      OnClick = CheckBox1Click
    end
  end
  object FormStorage1: TFormStorage
    StoredValues = <>
    Left = 424
    Top = 48
  end
  object RQ: TpFIBQuery
    Transaction = RT
    Database = SaleBookDM.DataBase
    GoToFirstRecordOnExecute = False
    Left = 384
    Top = 40
    qoAutoCommit = True
    qoStartTransaction = True
  end
  object RT: TpFIBTransaction
    Active = True
    DefaultDatabase = SaleBookDM.DataBase
    TimeoutAction = TARollback
    Left = 328
    Top = 40
  end
  object RQT: TpFIBDataSet
    Transaction = RT
    Database = SaleBookDM.DataBase
    Left = 280
    Top = 40
  end
end
