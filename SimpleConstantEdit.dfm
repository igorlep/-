object SimpleConstantEditForm: TSimpleConstantEditForm
  Left = 960
  Top = 388
  Width = 250
  Height = 136
  Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1077' '#1079#1085#1072#1095#1077#1085#1080#1103
  Color = clBtnFace
  Constraints.MinWidth = 250
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  OnResize = FormResize
  PixelsPerInch = 120
  TextHeight = 13
  object buttonPanel: TPanel
    Left = 0
    Top = 55
    Width = 232
    Height = 36
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      232
      36)
    object SaveButton: TJvXPButton
      Left = 130
      Top = 4
      Width = 95
      Height = 22
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      TabOrder = 0
      Glyph.Data = {
        F6000000424DF600000000000000760000002800000010000000100000000100
        0400000000008000000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
        8888880000000000000880330000008803088033000000880308803300000088
        0308803300000000030880333333333333088033000000003308803088888888
        0308803088888888030880308888888803088030888888880308803088888888
        0008803088888888080880000000000000088888888888888888}
      Anchors = [akTop, akRight]
      OnClick = SaveButtonClick
    end
    object CancelButton: TJvXPButton
      Left = 26
      Top = 4
      Width = 95
      Height = 22
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
      OnClick = CancelButtonClick
    end
  end
  object workPanel: TSmrtPanel
    Left = 0
    Top = 0
    Width = 232
    Height = 55
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      232
      55)
    object Label: TLabel
      Tag = 12
      Left = 8
      Top = 12
      Width = 223
      Height = 13
      Alignment = taCenter
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Caption = #1047#1072#1082#1088#1099#1090#1100' '#1080#1084#1087#1086#1088#1090' '#1076#1072#1085#1085#1099#1093', '#1085#1072#1095#1080#1085#1072#1103' '#1089
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label1: TLabel
      Tag = 12
      Left = 194
      Top = 36
      Width = 28
      Height = 13
      AutoSize = False
      Caption = #1075#1086#1076#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Month: TComboBox
      Tag = 13
      Left = 24
      Top = 32
      Width = 83
      Height = 21
      BevelInner = bvNone
      BevelKind = bkFlat
      BevelOuter = bvRaised
      DropDownCount = 12
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ItemHeight = 13
      ItemIndex = 8
      ParentFont = False
      TabOrder = 0
      Text = #1089#1077#1085#1090#1103#1073#1088#1103
      OnChange = MonthChange
      Items.Strings = (
        #1103#1085#1074#1072#1088#1103
        #1092#1077#1074#1088#1072#1083#1103
        #1084#1072#1088#1090#1072
        #1072#1087#1088#1077#1083#1103
        #1084#1072#1103
        #1080#1102#1085#1103
        #1080#1102#1083#1103
        #1072#1074#1075#1091#1089#1090#1072
        #1089#1077#1085#1090#1103#1073#1088#1103
        #1086#1082#1090#1103#1073#1088#1103
        #1085#1086#1103#1073#1088#1103
        #1076#1077#1082#1072#1073#1088#1103)
    end
    object MonthUpDown: TUpDown
      Tag = 12
      Left = 110
      Top = 32
      Width = 17
      Height = 21
      Min = 0
      Max = 13
      Position = 4
      TabOrder = 1
      Wrap = False
      OnClick = MonthUpDownClick
    end
    object Year: TRxSpinEdit
      Tag = 13
      Left = 131
      Top = 32
      Width = 56
      Height = 19
      ButtonKind = bkStandard
      MaxValue = 2050
      MinValue = 2004
      Value = 2009
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 2
    end
  end
  object FormStorage: TFormStorage
    StoredValues = <>
    Left = 8
    Top = 64
  end
end
