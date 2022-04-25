object ChangePassForm: TChangePassForm
  Left = 219
  Top = 613
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1057#1084#1077#1085#1072' '#1087#1072#1088#1086#1083#1103' '#1087#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1103
  ClientHeight = 190
  ClientWidth = 318
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  Scaled = False
  PixelsPerInch = 96
  TextHeight = 16
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 318
    Height = 150
    Align = alClient
    BevelOuter = bvNone
    BorderStyle = bsSingle
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 26
      Width = 127
      Height = 16
      Alignment = taRightJustify
      AutoSize = False
      Caption = #1057#1090#1072#1088#1099#1081' '#1087#1072#1088#1086#1083#1100
    end
    object Label2: TLabel
      Left = 16
      Top = 76
      Width = 127
      Height = 16
      Alignment = taRightJustify
      AutoSize = False
      Caption = #1053#1086#1074#1099#1081' '#1087#1072#1088#1086#1083#1100
    end
    object Label3: TLabel
      Left = 8
      Top = 105
      Width = 135
      Height = 16
      Alignment = taRightJustify
      AutoSize = False
      Caption = #1055#1086#1074#1090#1086#1088#1080#1090#1077' '#1087#1072#1088#1086#1083#1100
    end
    object OldPassword: TEdit
      Left = 151
      Top = 22
      Width = 149
      Height = 22
      PasswordChar = '*'
      TabOrder = 0
      OnDblClick = OldPasswordDblClick
      OnKeyPress = OldPasswordKeyPress
    end
    object NewPassword1: TEdit
      Left = 151
      Top = 71
      Width = 149
      Height = 22
      PasswordChar = '*'
      TabOrder = 1
      OnKeyPress = NewPassword1KeyPress
    end
    object NewPassword2: TEdit
      Left = 151
      Top = 100
      Width = 149
      Height = 22
      PasswordChar = '*'
      TabOrder = 2
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 150
    Width = 318
    Height = 40
    Align = alBottom
    TabOrder = 1
    DesignSize = (
      318
      40)
    object SaveButton: TBitBtn
      Left = 65
      Top = 8
      Width = 117
      Height = 24
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
      Left = 195
      Top = 8
      Width = 107
      Height = 24
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
    Left = 32
    Top = 32
    qoAutoCommit = True
    qoStartTransaction = True
  end
  object T: TpFIBTransaction
    DefaultDatabase = SaleBookDM.DataBase
    TimeoutAction = TARollback
    Left = 64
    Top = 32
  end
end
