object InvoicesSelectFilterForm: TInvoicesSelectFilterForm
  Left = 517
  Top = 110
  Width = 345
  Height = 249
  Caption = #1054#1090#1073#1086#1088' '#1089#1095#1077#1090#1086#1074'-'#1092#1072#1082#1090#1091#1088' '#1087#1086' '#1091#1089#1083#1086#1074#1080#1102
  Color = clWindow
  Ctl3D = False
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 185
    Width = 337
    Height = 30
    Align = alBottom
    BevelOuter = bvNone
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 0
    DesignSize = (
      337
      30)
    object selectButton: TJvXPButton
      Left = 144
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
    end
    object cancelButton: TJvXPButton
      Left = 232
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
    end
  end
  object SmrtPanel1: TSmrtPanel
    Left = 0
    Top = 0
    Width = 337
    Height = 185
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
    DesignSize = (
      337
      185)
    object CustomerCheckBox: TCheckBox
      Tag = 12
      Left = 16
      Top = 128
      Width = 145
      Height = 17
      Alignment = taLeftJustify
      Caption = #1087#1086' '#1075#1088#1091#1079#1086#1087#1086#1083#1091#1095#1072#1090#1077#1083#1102
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
    end
    object UserCheckBox: TCheckBox
      Tag = 12
      Left = 16
      Top = 156
      Width = 145
      Height = 17
      Alignment = taLeftJustify
      Caption = #1087#1086' '#1087#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1102
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
    end
    object CustomerEdit: TComboEdit
      Tag = 13
      Left = 168
      Top = 126
      Width = 155
      Height = 21
      DirectInput = False
      GlyphKind = gkEllipsis
      ButtonWidth = 18
      Anchors = [akLeft, akTop, akRight]
      NumGlyphs = 1
      TabOrder = 2
      Text = 'CustomerEdit'
    end
    object UserEdit: TComboEdit
      Tag = 13
      Left = 168
      Top = 154
      Width = 155
      Height = 21
      GlyphKind = gkEllipsis
      ButtonWidth = 18
      Anchors = [akLeft, akTop, akRight]
      NumGlyphs = 1
      TabOrder = 3
      Text = 'UserEdit'
    end
    object invoiceTypeCheckBox: TCheckBox
      Tag = 12
      Left = 16
      Top = 16
      Width = 145
      Height = 17
      Alignment = taLeftJustify
      Caption = #1087#1086' '#1090#1080#1087#1091' '#1076#1086#1082#1091#1084#1077#1085#1090#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
    end
    object invoiceTypeBox: TComboBox
      Tag = 12
      Left = 168
      Top = 16
      Width = 73
      Height = 21
      BevelKind = bkFlat
      ItemHeight = 13
      ItemIndex = 1
      TabOrder = 5
      Text = #1059#1089#1083#1091#1075#1072
      Items.Strings = (
        #1058#1086#1074#1072#1088
        #1059#1089#1083#1091#1075#1072)
    end
  end
end
