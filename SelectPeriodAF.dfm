object SelectPeriodForm: TSelectPeriodForm
  Left = 224
  Top = 302
  Width = 461
  Height = 244
  BorderIcons = [biSystemMenu]
  Caption = #1042#1099#1073#1086#1088' '#1087#1077#1088#1080#1086#1076#1072
  Color = clWindow
  Ctl3D = False
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  PixelsPerInch = 96
  TextHeight = 16
  object SmrtPanel2: TSmrtPanel
    Left = 0
    Top = 165
    Width = 445
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      445
      41)
    object JXPBOK: TJvXPButton
      Tag = 15
      Left = 328
      Top = 8
      Width = 105
      Height = 26
      Caption = #1042#1099#1073#1088#1072#1090#1100
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
      OnClick = JXPBOKClick
    end
    object JvXPButton1: TJvXPButton
      Left = 216
      Top = 8
      Width = 105
      Height = 26
      Caption = #1054#1090#1084#1077#1085#1072
      TabOrder = 1
      OnClick = JvXPButton1Click
    end
  end
  object SmrtPanel1: TSmrtPanel
    Left = 0
    Top = 0
    Width = 445
    Height = 165
    Align = alClient
    TabOrder = 1
    DesignSize = (
      445
      165)
    object Label1: TLabel
      Tag = 12
      Left = 120
      Top = 121
      Width = 25
      Height = 16
      Alignment = taRightJustify
      AutoSize = False
      Caption = #1089':'
    end
    object Label2: TLabel
      Tag = 12
      Left = 256
      Top = 121
      Width = 25
      Height = 16
      Alignment = taRightJustify
      AutoSize = False
      Caption = #1087#1086':'
    end
    object IntDate1: TDateEdit
      Tag = 12
      Left = 152
      Top = 120
      Width = 97
      Height = 21
      NumGlyphs = 2
      TabOrder = 0
    end
    object IntDate2: TDateEdit
      Tag = 12
      Left = 288
      Top = 120
      Width = 97
      Height = 21
      NumGlyphs = 2
      TabOrder = 1
    end
    object PeriodText: TStaticText
      Left = 24
      Top = 16
      Width = 409
      Height = 20
      Alignment = taCenter
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      BorderStyle = sbsSingle
      Caption = 'PeriodText'
      TabOrder = 2
    end
    object MonthButton: TRadioButton
      Tag = 12
      Left = 24
      Top = 56
      Width = 97
      Height = 17
      Caption = #1052#1077#1089#1103#1094
      TabOrder = 3
      OnClick = MonthButtonClick
    end
    object DayButton: TRadioButton
      Tag = 12
      Left = 24
      Top = 88
      Width = 97
      Height = 17
      Caption = #1044#1077#1085#1100
      TabOrder = 4
      OnClick = DayButtonClick
    end
    object IntButton: TRadioButton
      Tag = 12
      Left = 24
      Top = 120
      Width = 97
      Height = 17
      Caption = #1048#1085#1090#1077#1088#1074#1072#1083
      TabOrder = 5
      OnClick = IntButtonClick
    end
    object Day: TDateEdit
      Tag = 12
      Left = 152
      Top = 88
      Width = 97
      Height = 21
      NumGlyphs = 2
      TabOrder = 6
    end
    object Month: TEdit
      Tag = 12
      Left = 152
      Top = 56
      Width = 121
      Height = 22
      TabOrder = 7
      Text = 'Month'
    end
    object YearCheckBox: TCheckBox
      Tag = 12
      Left = 296
      Top = 60
      Width = 129
      Height = 17
      Caption = #1089' '#1085#1072#1095#1072#1083#1072' '#1075#1086#1076#1072
      TabOrder = 8
    end
    object MonthCheckBox: TCheckBox
      Tag = 12
      Left = 296
      Top = 92
      Width = 153
      Height = 17
      Caption = #1089' '#1085#1072#1095#1072#1083#1072' '#1084#1077#1089#1103#1094#1072
      TabOrder = 9
    end
    object MonthUpDown: TCSpinButton
      Tag = 12
      Left = 272
      Top = 56
      Width = 20
      Height = 23
      DownGlyph.Data = {
        0E010000424D0E01000000000000360000002800000009000000060000000100
        200000000000D800000000000000000000000000000000000000008080000080
        8000008080000080800000808000008080000080800000808000008080000080
        8000008080000080800000808000000000000080800000808000008080000080
        8000008080000080800000808000000000000000000000000000008080000080
        8000008080000080800000808000000000000000000000000000000000000000
        0000008080000080800000808000000000000000000000000000000000000000
        0000000000000000000000808000008080000080800000808000008080000080
        800000808000008080000080800000808000}
      TabOrder = 10
      UpGlyph.Data = {
        0E010000424D0E01000000000000360000002800000009000000060000000100
        200000000000D800000000000000000000000000000000000000008080000080
        8000008080000080800000808000008080000080800000808000008080000080
        8000000000000000000000000000000000000000000000000000000000000080
        8000008080000080800000000000000000000000000000000000000000000080
        8000008080000080800000808000008080000000000000000000000000000080
        8000008080000080800000808000008080000080800000808000000000000080
        8000008080000080800000808000008080000080800000808000008080000080
        800000808000008080000080800000808000}
      OnDownClick = MonthUpDownDownClick
      OnUpClick = MonthUpDownUpClick
    end
  end
  object FormStorage: TFormStorage
    StoredValues = <>
    Left = 392
    Top = 32
  end
end
