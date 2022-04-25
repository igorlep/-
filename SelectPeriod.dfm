object SelectPeriodForm: TSelectPeriodForm
  Left = 145
  Top = 422
  Width = 464
  Height = 178
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
    Top = 99
    Width = 448
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      448
      41)
    object JXPBOK: TJvXPButton
      Tag = 15
      Left = 331
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
    Width = 448
    Height = 99
    Align = alClient
    TabOrder = 1
    object Label1: TLabel
      Tag = 12
      Left = 56
      Top = 46
      Width = 89
      Height = 16
      Alignment = taRightJustify
      AutoSize = False
      Caption = #1055#1077#1088#1080#1086#1076' '#1089':'
    end
    object Label2: TLabel
      Tag = 12
      Left = 208
      Top = 46
      Width = 25
      Height = 16
      Alignment = taRightJustify
      AutoSize = False
      Caption = #1087#1086':'
    end
    object D1: TEdit
      Tag = 12
      Left = 152
      Top = 43
      Width = 41
      Height = 22
      TabOrder = 0
      Text = '1'
    end
    object D2: TEdit
      Tag = 12
      Left = 248
      Top = 43
      Width = 41
      Height = 22
      TabOrder = 1
      Text = '22'
    end
  end
  object FormStorage: TFormStorage
    StoredValues = <>
    Left = 392
    Top = 32
  end
end
