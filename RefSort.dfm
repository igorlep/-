object RefSortForm: TRefSortForm
  Left = 286
  Top = 830
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1042#1099#1073#1086#1088' '#1089#1087#1086#1089#1086#1073#1072' '#1089#1086#1088#1090#1080#1088#1086#1074#1082#1080
  ClientHeight = 136
  ClientWidth = 308
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  OnClose = FormClose
  PixelsPerInch = 120
  TextHeight = 16
  object Panel1: TPanel
    Left = 0
    Top = 95
    Width = 308
    Height = 41
    Align = alBottom
    TabOrder = 0
    DesignSize = (
      308
      41)
    object SelectButton: TBitBtn
      Left = 65
      Top = 8
      Width = 100
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1042#1099#1073#1088#1072#1090#1100
      TabOrder = 0
      OnClick = SelectButtonClick
      Glyph.Data = {
        F6000000424DF600000000000000760000002800000010000000100000000100
        0400000000008000000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFF90FFFFFFFFFFFFF9990FFFFFFFFFFFF9990FFFF
        FFFFFFF999990FFFFFFFFF9999990FFFFFFFF7990F9990FFFFFF790FFFF990FF
        FFFFFFFFFFF9990FFFFFFFFFFFFF990FFFFFFFFFFFFFF990FFFFFFFFFFFFFF79
        0FFFFFFFFFFFFFF790FFFFFFFFFFFFFFF990FFFFFFFFFFFFFFFF}
    end
    object CancelButton: TBitBtn
      Left = 185
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
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 308
    Height = 95
    Align = alClient
    TabOrder = 1
    DesignSize = (
      308
      95)
    object RadioButton1: TRadioButton
      Left = 24
      Top = 24
      Width = 273
      Height = 17
      Anchors = [akLeft, akTop, akRight]
      Caption = #1057#1086#1088#1090#1080#1088#1086#1074#1072#1090#1100' '#1087#1086' '#1085#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1102
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      TabStop = True
    end
    object RadioButton2: TRadioButton
      Left = 24
      Top = 56
      Width = 273
      Height = 17
      Anchors = [akLeft, akTop, akRight]
      Caption = #1057#1086#1088#1090#1080#1088#1086#1074#1072#1090#1100' '#1087#1086' '#1082#1086#1076#1091
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
    end
  end
end
