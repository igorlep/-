object AccountEditForm: TAccountEditForm
  Left = 392
  Top = 179
  Width = 1389
  Height = 516
  BorderIcons = [biSystemMenu, biMinimize, biMaximize, biHelp]
  Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1077
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
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF000000
    0000000000000CCCCCCCCCCCCCC00CFFFFFFFFFFFFC00C0F000F000F00C00CFF
    FFFFFFFFFFC00C0F000F000F00C00CFFFFFFFFFFFFC00C0F000F000F00C00CFF
    FFFFFFFFFFC00C000000000000C00CF0FFF0FFF0FFC00C000000000000C00CFF
    FFFFFFFFFFC00CFFF00F0000FFC00CFFFFFFFFFFFFC00CCCCCCCCCCCCCC0C000
    0000800000008000000080000000800000008000000080000000800000008000
    000080000000800000008000000080000000800000008000000080010000}
  OldCreateOrder = False
  Scaled = False
  OnActivate = FormActivate
  OnClose = FormClose
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object SmrtPanel1: TSmrtPanel
    Left = 0
    Top = 0
    Width = 1371
    Height = 73
    Align = alTop
    TabOrder = 0
    DesignSize = (
      1371
      73)
    object Label1: TLabel
      Tag = 13
      Left = 797
      Top = 48
      Width = 104
      Height = 16
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = #1047#1072#1076#1072#1085#1080#1077' '#8470
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label2: TLabel
      Tag = 13
      Left = 1023
      Top = 48
      Width = 30
      Height = 16
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = #1086#1090
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label3: TLabel
      Tag = 13
      Left = 615
      Top = 12
      Width = 138
      Height = 16
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = #1055#1086#1095#1090#1072#1083#1100#1086#1085
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label5: TLabel
      Tag = 13
      Left = 1181
      Top = 8
      Width = 169
      Height = 16
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = #1055#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label18: TLabel
      Left = 24
      Top = 8
      Width = 149
      Height = 41
      Alignment = taCenter
      AutoSize = False
      Caption = #1055#1086#1080#1089#1082' '#1076#1077#1083#1072' '#1087#1086' '#1053#1086#1084#1077#1088#1091' '#1080#1083#1080' '#1060#1072#1084#1080#1083#1080#1102
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      WordWrap = True
    end
    object Label20: TLabel
      Left = 2
      Top = 42
      Width = 171
      Height = 24
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = #1042#1099#1073#1088#1072#1085#1086' '#1079#1072#1087#1080#1089#1077#1081
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      WordWrap = True
    end
    object DateEdit: TDBDateTimeEditEh
      Tag = 13
      Left = 1060
      Top = 44
      Width = 113
      Height = 20
      Alignment = taCenter
      Anchors = [akTop, akRight]
      Ctl3D = False
      DataField = 'COUNT_DATE'
      DataSource = AccountsTempS
      EditButtons = <>
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      Flat = True
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 1
      Visible = True
      OnChange = DateEditChange
      OnKeyDown = DateEditKeyDown
      EditFormat = 'DD.MM.YYYY'
    end
    object NumberEdit: TDBEditEh
      Tag = 13
      Left = 907
      Top = 44
      Width = 103
      Height = 20
      Alignment = taCenter
      Anchors = [akTop, akRight]
      Ctl3D = False
      DataField = 'COUNT_NUMBER'
      DataSource = AccountsTempS
      EditButtons = <>
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      Flat = True
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 0
      Visible = True
      OnKeyDown = NumberEditKeyDown
    end
    object CustomerEdit: TRxDBComboEdit
      Tag = 13
      Left = 759
      Top = 8
      Width = 381
      Height = 21
      Ctl3D = False
      DataField = 'CUSTOMER_NAME'
      DataSource = AccountsTempS
      DirectInput = False
      GlyphKind = gkEllipsis
      Anchors = [akTop, akRight]
      NumGlyphs = 1
      ParentCtl3D = False
      TabOrder = 2
      OnButtonClick = CustomerEditButtonClick
    end
    object UserName: TStaticText
      Tag = 13
      Left = 1181
      Top = 24
      Width = 161
      Height = 22
      Anchors = [akTop, akRight]
      AutoSize = False
      BevelInner = bvNone
      BevelKind = bkFlat
      BorderStyle = sbsSingle
      TabOrder = 3
    end
    object Edit1: TEdit
      Left = 184
      Top = 14
      Width = 100
      Height = 22
      Hint = #1055#1086#1080#1089#1082' '#1087#1086' '#1085#1086#1084#1077#1088#1091' '#1076#1077#1083#1072
      AutoSelect = False
      AutoSize = False
      Constraints.MaxWidth = 100
      Constraints.MinWidth = 60
      Ctl3D = False
      ParentCtl3D = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 4
      OnChange = Edit1Change
      OnKeyPress = Edit1KeyPress
    end
    object Edit2: TEdit
      Left = 185
      Top = 39
      Width = 60
      Height = 22
      Anchors = [akTop, akRight]
      AutoSelect = False
      Constraints.MaxWidth = 100
      Constraints.MinWidth = 60
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentCtl3D = False
      ParentFont = False
      ParentShowHint = False
      ReadOnly = True
      ShowHint = True
      TabOrder = 5
      Text = '0'
    end
  end
  object SmrtPanel2: TSmrtPanel
    Left = 0
    Top = 331
    Width = 1371
    Height = 140
    Align = alBottom
    TabOrder = 1
    DesignSize = (
      1371
      140)
    object Label4: TLabel
      Tag = 13
      Left = 177
      Top = 8
      Width = 104
      Height = 16
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = #1048#1090#1086#1075#1086
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label6: TLabel
      Tag = 13
      Left = 101
      Top = 32
      Width = 148
      Height = 16
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = #1050#1086#1083'-'#1074#1086' '#1087#1086#1088#1091#1095#1077#1085#1080#1081
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label7: TLabel
      Tag = 13
      Left = 147
      Top = 56
      Width = 104
      Height = 16
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = #1058#1077#1082#1091#1097#1077#1077
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label8: TLabel
      Tag = 13
      Left = 147
      Top = 80
      Width = 104
      Height = 16
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = #1055#1088#1086#1096#1083#1086#1077
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label9: TLabel
      Tag = 13
      Left = 147
      Top = 104
      Width = 104
      Height = 16
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = #1056#1072#1079#1076#1077#1083' 1'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label10: TLabel
      Tag = 13
      Left = 443
      Top = 8
      Width = 104
      Height = 16
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = #1054#1055#1051#1040#1063#1045#1053#1054
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label11: TLabel
      Tag = 13
      Left = 389
      Top = 32
      Width = 104
      Height = 16
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label12: TLabel
      Tag = 13
      Left = 389
      Top = 56
      Width = 104
      Height = 16
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = #1058#1077#1082#1091#1097#1077#1077
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label13: TLabel
      Tag = 13
      Left = 389
      Top = 80
      Width = 104
      Height = 16
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = #1055#1088#1086#1096#1083#1086#1077' + '#1056'1'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label14: TLabel
      Tag = 13
      Left = 643
      Top = 9
      Width = 141
      Height = 16
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = #1053#1045#1054#1055#1051#1040#1063#1045#1053#1054
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label15: TLabel
      Tag = 13
      Left = 621
      Top = 33
      Width = 104
      Height = 16
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label16: TLabel
      Tag = 13
      Left = 621
      Top = 57
      Width = 104
      Height = 16
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = #1058#1077#1082#1091#1097#1077#1077
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label17: TLabel
      Tag = 13
      Left = 621
      Top = 81
      Width = 104
      Height = 16
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = #1055#1088#1086#1096#1083#1086#1077' + '#1056'1'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object WriteButton: TBitBtn
      Left = 966
      Top = 40
      Width = 264
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1080' '#1079#1072#1082#1088#1099#1090#1100' '#1079#1072#1076#1072#1085#1080#1077
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnClick = WriteButtonClick
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
    object ExitButton: TBitBtn
      Left = 966
      Top = 72
      Width = 265
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1054#1090#1082#1072#1079#1072#1090#1100#1089#1103
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = ExitButtonClick
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
    object StaticText1: TStaticText
      Tag = 13
      Left = 253
      Top = 29
      Width = 83
      Height = 22
      Alignment = taCenter
      Anchors = [akTop, akRight]
      AutoSize = False
      BevelInner = bvNone
      BevelKind = bkFlat
      BorderStyle = sbsSingle
      Caption = '0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
    end
    object StaticText2: TStaticText
      Tag = 13
      Left = 503
      Top = 29
      Width = 83
      Height = 22
      Alignment = taCenter
      Anchors = [akTop, akRight]
      AutoSize = False
      BevelInner = bvNone
      BevelKind = bkFlat
      BorderStyle = sbsSingle
      Caption = '0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
    end
    object StaticText3: TStaticText
      Tag = 13
      Left = 733
      Top = 29
      Width = 83
      Height = 22
      Alignment = taCenter
      Anchors = [akTop, akRight]
      AutoSize = False
      BevelInner = bvNone
      BevelKind = bkFlat
      BorderStyle = sbsSingle
      Caption = '0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
    end
    object StaticText4: TStaticText
      Tag = 13
      Left = 253
      Top = 53
      Width = 83
      Height = 22
      Hint = '#0.00'
      Alignment = taCenter
      Anchors = [akTop, akRight]
      AutoSize = False
      BevelInner = bvNone
      BevelKind = bkFlat
      BorderStyle = sbsSingle
      Caption = '0.00'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
    end
    object StaticText5: TStaticText
      Tag = 13
      Left = 253
      Top = 77
      Width = 83
      Height = 22
      Alignment = taCenter
      Anchors = [akTop, akRight]
      AutoSize = False
      BevelInner = bvNone
      BevelKind = bkFlat
      BorderStyle = sbsSingle
      Caption = '0.00'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 6
    end
    object StaticText6: TStaticText
      Tag = 13
      Left = 253
      Top = 101
      Width = 83
      Height = 22
      Alignment = taCenter
      Anchors = [akTop, akRight]
      AutoSize = False
      BevelInner = bvNone
      BevelKind = bkFlat
      BorderStyle = sbsSingle
      Caption = '0.00'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 7
    end
    object StaticText7: TStaticText
      Tag = 13
      Left = 503
      Top = 53
      Width = 83
      Height = 22
      Alignment = taCenter
      Anchors = [akTop, akRight]
      AutoSize = False
      BevelInner = bvNone
      BevelKind = bkFlat
      BorderStyle = sbsSingle
      Caption = '0.00'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 8
    end
    object StaticText8: TStaticText
      Tag = 13
      Left = 503
      Top = 77
      Width = 83
      Height = 22
      Alignment = taCenter
      Anchors = [akTop, akRight]
      AutoSize = False
      BevelInner = bvNone
      BevelKind = bkFlat
      BorderStyle = sbsSingle
      Caption = '0.00'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 9
    end
    object StaticText9: TStaticText
      Tag = 13
      Left = 733
      Top = 53
      Width = 83
      Height = 22
      Alignment = taCenter
      Anchors = [akTop, akRight]
      AutoSize = False
      BevelInner = bvNone
      BevelKind = bkFlat
      BorderStyle = sbsSingle
      Caption = '0.00'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 10
    end
    object StaticText10: TStaticText
      Tag = 13
      Left = 733
      Top = 77
      Width = 83
      Height = 22
      Alignment = taCenter
      Anchors = [akTop, akRight]
      AutoSize = False
      BevelInner = bvNone
      BevelKind = bkFlat
      BorderStyle = sbsSingle
      Caption = '0.00'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 11
    end
  end
  object SmrtPanel3: TSmrtPanel
    Left = 0
    Top = 73
    Width = 1371
    Height = 223
    Align = alClient
    TabOrder = 2
    object SmrtPanel4: TSmrtPanel
      Left = 1
      Top = 1
      Width = 28
      Height = 221
      Align = alLeft
      TabOrder = 0
      object AddButton: TSpeedButton
        Left = 4
        Top = 8
        Width = 20
        Height = 20
        Hint = #1044#1086#1073#1072#1074#1080#1090#1100' '#1087#1086#1088#1091#1095#1077#1085#1080#1103' '#1080#1079' '#1074#1099#1087#1083#1072#1090#1085#1086#1081' '#1073#1072#1079#1099'...'
        Flat = True
        Glyph.Data = {
          F6000000424DF600000000000000760000002800000010000000100000000100
          0400000000008000000000000000000000001000000000000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFCFFFFFF
          FFFFFCCCCCCFFFFFFFFFCCCCCCCCCF999999CCCCCCCCCF999999CCCCCCCFFFFF
          FFFFCCCFFCF777777777CCCF7F7777777777CCCFFFFFFFFFFFFFCCC777777777
          7777FFF7777777777777FFFFFFFFFFFFFFFFFFF7777777777777FFF777777777
          7777FFFFFFFFFFFFFFFFFFF7777777777777FFF7777777777777}
        ParentShowHint = False
        ShowHint = True
        OnClick = AddButtonClick
      end
      object DelButton: TSpeedButton
        Left = 4
        Top = 88
        Width = 20
        Height = 20
        Hint = #1059#1076#1072#1083#1080#1090#1100' '#1090#1077#1082#1091#1097#1077#1077' '#1087#1086#1088#1091#1095#1077#1085#1080#1077
        Flat = True
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          0400000000000001000000000000000000001000000000000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFF777777777
          7777FFF7777777777777FFF7777777777777FFF7777777777777FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFF7777777777777FFF7777777777777999777999777
          77777777777777777777F999F999FFFFFFFFF777F777FFFFFFFFFF99999FFFFF
          FFFFFF77777FFFFFFFFFFFF999CCCCCCCCCCFFF7777777777777FF99999CCCCC
          CCCCFFF7777777777777F999F999FFFFFFFFF777F777FFFFFFFF999FFF999FFF
          FFFF777FFF777FFFFFFFFFF7777777777777FFF7777777777777FFF777777777
          7777FFF7777777777777FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF777777777
          7777FFF7777777777777FFF7777777777777FFF7777777777777}
        NumGlyphs = 2
        ParentShowHint = False
        ShowHint = True
        OnClick = DelButtonClick
      end
      object SaveButton: TSpeedButton
        Left = 4
        Top = 28
        Width = 20
        Height = 20
        Hint = #1047#1072#1087#1080#1089#1072#1090#1100
        Flat = True
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          0400000000000001000000000000000000001000000000000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
          8888888888888888888882882222282222888788777778777788882088888888
          888888778888888888888800008882222288887777888777778888800F008888
          888888877F77888888888880FFF0388222888887FFF73887778888880F023388
          888888887F78338888888888002223388888888877888338888888888A222233
          88888888878888338888888888A22223388888888878888338888888888A2222
          3388888888878888338888888888A22223388888888878888338888888888A22
          223888888888878888388888888888A22228888888888878887888888888888A
          2228888888888887777888888888888888888888888888888888}
        NumGlyphs = 2
        ParentShowHint = False
        ShowHint = True
        OnClick = SaveButtonClick
      end
      object CancelButton: TSpeedButton
        Left = 4
        Top = 66
        Width = 20
        Height = 20
        Hint = #1054#1090#1084#1077#1085#1080#1090#1100
        Flat = True
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          0400000000000001000000000000000000001000000000000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
          8888888888888888888889982222992222888778777777777788899988899988
          8888877788877788888888999099922222888877777777777788888999998888
          8888888777777888888888809990388222888887777738877788888999993388
          888888877777338888888899909993388888887777777338888889998A299933
          88888777878777338888899888A29923388887788878778338888888888A2222
          3388888888878888338888888888A22223388888888878888338888888888A22
          223888888888878888388888888888A22228888888888878887888888888888A
          2228888888888887777888888888888888888888888888888888}
        NumGlyphs = 2
        ParentShowHint = False
        ShowHint = True
        OnClick = CancelButtonClick
      end
      object EditButton: TSpeedButton
        Left = 3
        Top = 48
        Width = 20
        Height = 20
        Hint = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100
        Flat = True
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          0400000000000001000000000000000000001000000000000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF2FF44444444
          444FF7FF44444444444F4F20FFFFFFFFFF4F4F88FFFFFFFFFF4F4F0000FFFF00
          0F4F4F8888FFFF000F4F4FF00F00FFFFFF4F4FF88F00FFFFFF4F4FF0FFF03F00
          0F4F4FF8FFF07F000F4F4FFF0F0233FFFF4F4FFF8F0873FFFF4F4F0F00222330
          0F4F4F0F888883300F4F4FFFFA222233FF4F4FFFF7888833FF4F4F000FA22223
          3F4F4F000F7888833F4F4FFFFFFA2222334F4FFFFFF78888774F44444444A222
          233F444444447888877F4F444F444A22223F4F444F444788887F4444444444A2
          222F444444444478888FFFFFFFFFFFFA222FFFFFFFFFFFF7888F}
        NumGlyphs = 2
        ParentShowHint = False
        ShowHint = True
        OnClick = EditButtonClick
      end
      object MoveButton: TSpeedButton
        Left = 5
        Top = 135
        Width = 20
        Height = 26
        Hint = #1055#1077#1088#1077#1076#1072#1090#1100' '#1090#1077#1082#1091#1097#1077#1077' '#1079#1072#1076#1072#1085#1080#1077'...'
        Flat = True
        Glyph.Data = {
          0E070000424D0E0700000000000036040000280000001A0000001A0000000100
          080000000000D802000000000000000000000001000000000000FFFCF700F7F2
          F100FFF8ED00FFEEE600DEDEDE00DED6D600FBE1D200DBCDC900F4D2C400DCC6
          BB00F9C8B100D9B9B100E7BCA700E7C6A500D6AEA000C0A79D00E7BD9C00E7B5
          9C00E7B59400E7AD9400D9A88F00C09A8F00E7AD8C00E7A58C00D69A8700E7A5
          8400E79C8400C2958300BC8B7E00E79C7B00E7947B00DA937B00E78C7B00E78C
          7300DE8C7300D6847300D38C7200DE847200BD816F00D6846B00CE846B00CE7B
          6B00CE7B6300C67B6300BD7B6300BD735F00B1745E00C6735E00B8685000AD60
          4A00965A4A009F4F370079240A00000000000000000000000000000000000000
          00000000000000000000000000000000000000000000000000001C1A0500180C
          03001904190014191D0016221D0019141900332A2A000000CC000D000000261C
          18001C1C1C000D1913001F1C0D00190B03001C051900191C21001D1F1C001314
          190033CC990000CC99001D180F001D222200151515000B1A18001C191400190D
          0400200A19001A181800281F1F001B1C280033669900006699002B281100292D
          2D00211F2200051D1D002B242100241507002D0623002D29240024292B001D1D
          210033009900000099002D2811002124220022282B00041521002B2821002418
          060031002B0028282B002B292900191D290033CC660000CC6600191C11001C19
          14001D2113000F151900221C13001D1C1C00212221002F292900291F2100211D
          2900F7F2F100FFF8ED0018130F001A181400181D1C00191C1F001C1F18001A19
          1A001D1C1C00282824001C1D210020191C00D6AEA000E7BD9C00323232003232
          3200323232003232320032323200323232003232320032363200363632003636
          3600C2958300E79C7B0000000000000000000000000000000000343431003C3C
          3C00000A000000000E000000000000000000CE846B00CE7B6B00000000000000
          0000080A000030303500343131003C3434001707390000000E00000000000000
          00007F342000581C15000000000012000000120A0E00093B12002D3131003C34
          3400333A39000000030000000000000000000000000000000000000404000000
          00001200000039353500373B1200162A140034343100123A3A00303535000000
          000000000000D5D6D500AAB9CE0000000000010102003B3509003A3B39001207
          12003C34310039353A003A38380000000000000000005A799F008FB09D000000
          000012123000303030003B373A000730370034312A0039303000253A3A001717
          170000000E00526B8C004A668C00000000003335070039393B0038383B003B3A
          3700172A30003A3B3700301235001230370000000E0052637B004A637A000000
          0000253535003B3B3A003B3839003A383B0030333900383A3B00353735000000
          300000000000215B37001D8835000E00000012100E00383535001A1A1F1D1F1E
          1E1F21222222232727282929292B2B2C2D2D2D2E22211A181A1F1D1E1F1E2224
          23272729292A2A2A2B2B2B2B2C2D2D2D6D651A1A1A1A1A1F1E1F272A2F2D2D30
          30302E302D2D2D2F2C2C2D2D2827191A1A181A1D1F1F28303233333333323331
          333131302B2B2D2C2D231919191A1A181711141B1C1C1C1C262E313233333331
          2F2B2B2D726517171919181A130000000000000000000000041533312D2B2B2B
          0F0D17171719191A180300000301000000000000000133332D2A292B00001717
          171919181A0800000C0A080300000000000032312D2A2929000016161717181A
          241801000B0C0C080600000000002E322F2A2829000016131614191F262B0808
          342E0C0C0C080300000026332D292728000013161317171F2D2B0C113434342E
          14110C0803001C332D28272778821313161634343434343434343434342C0E0A
          030015332D272727C38213131316343434343434343434343434342E07001531
          2D27222552541212131334343434343434343434342E0B01000015332D272222
          0BFF121212131316161600003434342E0E01000000000F312F2422221D1D1112
          1212131313160000342E090000000000000015312B2222221D1B111112121213
          131601000E0000000000000309061B30282222201B1D11111112121213160000
          0000000000050E303105182B221E1E2278821010111112121211000000000000
          00182E1C08012824181E1F1E1B1D101010111112120D00000000000000090300
          01241F1F1D1F1D1F7882101010101111120800000000000000050002181F181D
          1D1A1F1D788210101010101111030000000000000101001418191A181A181D1F
          78820D1010101011100C100C1112131413131417171719191A1A1A1D78820D0D
          101010101010111212121313131616171717171919181A1878820D0D0D101010
          10101111121212131316131617171719191A1A1A78820D0D0D0D101010101011
          11121212131316161617171719191A187882}
        ParentShowHint = False
        ShowHint = True
        Visible = False
        OnClick = MoveButtonClick
      end
      object DelAllButton: TSpeedButton
        Left = 6
        Top = 112
        Width = 17
        Height = 20
        Hint = #1059#1076#1072#1083#1080#1090#1100' '#1074#1089#1077' '#1087#1086#1088#1091#1095#1077#1085#1080#1103'...'
        Flat = True
        Glyph.Data = {
          66010000424D6601000000000000760000002800000014000000140000000100
          040000000000F000000000000000000000001000000010000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
          8888888800008888888888888888889800008898888888888888898800008899
          88777777777798880000889990000000000998880000888990BFFFBFFF998888
          0000888899FCCCCCCF97888800008888999FBFFFB9978888000088888999CCC9
          990788880000888880999FB99F0788880000888880FC9999CF07888800008888
          80FF9999BF0788880000888880FC9999000788880000888880B99F099F078888
          0000888880999F099998888800008888999FBF0F089988880000889999000000
          8889988800008899988888888888898800008888888888888888889800008888
          88888888888888880000}
        ParentShowHint = False
        ShowHint = True
        OnClick = DelAllButtonClick
      end
      object OstButton: TSpeedButton
        Left = 5
        Top = 165
        Width = 20
        Height = 20
        Hint = #1054#1089#1090#1072#1074#1080#1090#1100' '#1074#1099#1073#1088#1072#1085#1085#1099#1077' '#1087#1086#1088#1091#1095#1077#1085#1080#1103' '#1074' '#1079#1072#1076#1072#1085#1080#1077'., '#1091#1076#1072#1083#1080#1074' '#1086#1089#1090#1072#1083#1100#1085#1099#1077' ...'
        Flat = True
        Glyph.Data = {
          96010000424D9601000000000000760000002800000018000000180000000100
          0400000000002001000000000000000000001000000000000000000000000000
          BF0000BF000000BFBF00BF000000BF00BF00BFBF0000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
          3333333333333333333333333333333333338888888888888883333333330000
          0000000000033333333333333333333333333333333388888888888883333333
          33330000000000000333333333333333333333333333333B3333888888888333
          3333333B3333000000000333333B3333333B333333333333C333B33333B33333
          3333333CC333333033333333333333CCC33333303333333333333CCCC3333000
          00333333333333CCC3333330333333333333333CC33333303333333333333333
          C3333333333388888888833333333B3333B30000000003333333B33B333B3333
          333333333333333B333388888888888883333333333300000000000003333333
          3333333333333333333333333333333333333333333333333333}
        ParentShowHint = False
        ShowHint = True
        Visible = False
        OnClick = OstButtonClick
      end
    end
    object SoldGoodsGrid: TDBGridEh
      Left = 29
      Top = 1
      Width = 1341
      Height = 221
      Align = alClient
      AutoFitColWidths = True
      Color = clWhite
      ColumnDefValues.AlwaysShowEditButton = True
      ColumnDefValues.AutoDropDown = True
      ColumnDefValues.DblClickNextVal = True
      ColumnDefValues.DropDownShowTitles = True
      Ctl3D = False
      DataSource = SoldGoodsS
      Flat = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      FooterColor = 16776176
      FooterFont.Charset = DEFAULT_CHARSET
      FooterFont.Color = clWindowText
      FooterFont.Height = -13
      FooterFont.Name = 'MS Sans Serif'
      FooterFont.Style = [fsBold]
      FooterRowCount = 1
      HorzScrollBar.Tracking = True
      ImeMode = imHira
      Options = [dgEditing, dgAlwaysShowEditor, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgAlwaysShowSelection]
      OptionsEh = [dghFixed3D, dghFooter3D, dghData3D, dghHighlightFocus, dghTraceColSizing, dghRowHighlight]
      ParentCtl3D = False
      ParentFont = False
      SumList.Active = True
      TabOrder = 1
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -13
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      UseMultiTitle = True
      OnCellClick = SoldGoodsGridCellClick
      OnGetCellParams = SoldGoodsGridGetCellParams
      OnKeyDown = SoldGoodsGridKeyDown
      OnMouseDown = SoldGoodsGridMouseDown
      Columns = <
        item
          EditButtons = <>
          FieldName = 'LCHET1'
          Footer.Color = clMoneyGreen
          Footer.DisplayFormat = '#0'
          Footer.FieldName = 'LCHET1'
          Footer.ValueType = fvtCount
          Footers = <>
          ReadOnly = True
          Title.Caption = #8470' '#1044#1077#1083#1072
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -13
          Title.Font.Name = 'MS Sans Serif'
          Title.Font.Style = [fsBold]
        end
        item
          Alignment = taCenter
          DisplayFormat = '#0.00'
          EditButtons = <>
          FieldName = 'SUMMA'
          Footer.Color = clMoneyGreen
          Footer.DisplayFormat = '#0.00'
          Footer.FieldName = 'SUMMA'
          Footer.ValueType = fvtSum
          Footers = <>
          ReadOnly = True
          Title.Caption = #1057#1091#1084#1084#1072
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -13
          Title.Font.Name = 'MS Sans Serif'
          Title.Font.Style = [fsBold]
        end
        item
          EditButtons = <>
          FieldName = 'WORD'
          Footers = <>
          ReadOnly = True
          Title.Caption = #1044#1072#1090#1072' '#1076#1086#1083#1075#1072
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -13
          Title.Font.Name = 'MS Sans Serif'
          Title.Font.Style = [fsBold]
        end
        item
          EditButtons = <>
          FieldName = 'FAMILY'
          Footers = <>
          ReadOnly = True
          Title.Caption = #1060#1072#1084#1080#1083#1080#1103
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -13
          Title.Font.Name = 'MS Sans Serif'
          Title.Font.Style = [fsBold]
          Width = 215
        end
        item
          EditButtons = <>
          FieldName = 'NAME'
          Footers = <>
          ReadOnly = True
          Title.Caption = #1048#1084#1103
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -13
          Title.Font.Name = 'MS Sans Serif'
          Title.Font.Style = [fsBold]
        end
        item
          EditButtons = <>
          FieldName = 'FATHER'
          Footers = <>
          ReadOnly = True
          Title.Caption = #1054#1090#1095#1077#1089#1090#1074#1086
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -13
          Title.Font.Name = 'MS Sans Serif'
          Title.Font.Style = [fsBold]
        end
        item
          Alignment = taLeftJustify
          EditButtons = <>
          FieldName = 'METKA1'
          Footers = <>
          ReadOnly = True
          Title.Caption = #1054'/'#1057
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -13
          Title.Font.Name = 'MS Sans Serif'
          Title.Font.Style = [fsBold]
        end
        item
          AlwaysShowEditButton = False
          Checkboxes = False
          DropDownBox.AutoFitColWidths = False
          DropDownBox.Options = []
          DropDownShowTitles = False
          EditButtons = <
            item
            end>
          FieldName = 'PRICH'
          Footers = <>
          PickList.Strings = (
            #1085'/'#1076
            #1091#1084#1077#1088
            #1076#1083'.'#1085'/'#1086
            #1074#1099#1073#1099#1083
            #1089#1084'.'#1072#1076#1088
            #1089#1073'/'#1082
            #1087#1088#1086#1095#1077#1077)
          Title.Caption = #1055#1088#1080#1095#1080#1085#1072
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -13
          Title.Font.Name = 'MS Sans Serif'
          Title.Font.Style = [fsBold]
          Width = 112
          OnUpdateData = SoldGoodsGridColumns7UpdateData
        end
        item
          Alignment = taLeftJustify
          AlwaysShowEditButton = False
          AutoDropDown = False
          AutoFitColWidth = False
          DblClickNextVal = False
          DropDownBox.AutoFitColWidths = False
          DropDownShowTitles = False
          EditButtons = <>
          FieldName = 'FAKT_DAT'
          Footers = <>
          Title.Caption = #1044#1072#1090#1072
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -13
          Title.Font.Name = 'MS Sans Serif'
          Title.Font.Style = [fsBold]
          Width = 60
          OnUpdateData = SoldGoodsGridColumns8UpdateData
        end>
    end
  end
  object SmrtPanel5: TSmrtPanel
    Left = 0
    Top = 296
    Width = 1371
    Height = 35
    Align = alBottom
    TabOrder = 3
    object Label19: TLabel
      Tag = 13
      Left = 1
      Top = 1
      Width = 1369
      Height = 33
      Align = alClient
      Alignment = taCenter
      AutoSize = False
      Caption = #1047#1072#1076#1072#1085#1080#1077' '#8470
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
      Visible = False
    end
  end
  object AccountsTempS: TDataSource
    DataSet = AccountsTempDS
    Left = 728
    Top = 128
  end
  object SoldGoodsS: TDataSource
    DataSet = SoldGoodsDS
    OnStateChange = SoldGoodsSStateChange
    OnDataChange = SoldGoodsSDataChange
    Left = 952
    Top = 128
  end
  object FormStorage1: TFormStorage
    StoredValues = <>
    Left = 568
    Top = 136
  end
  object AccountsTempDS: TpFIBDataSet
    UpdateSQL.Strings = (
      'UPDATE ACCOUNTS_TEMP'
      'SET '
      '    COUNT_DATE = :COUNT_DATE,'
      '    COUNT_NUMBER = :COUNT_NUMBER,'
      '    CUSTOMER_ID = :CUSTOMER_ID,'
      '    USER_ID = :USER_ID,'
      '    COUNT_TYPE = :COUNT_TYPE'
      'WHERE'
      '    ORG_ID = :OLD_ORG_ID'
      '    and COUNT_DATE = :OLD_COUNT_DATE'
      '    and COUNT_NUMBER = :OLD_COUNT_NUMBER'
      '    ')
    InsertSQL.Strings = (
      
        'insert into ACCOUNTS_TEMP(ORG_ID,COUNT_DATE,COUNT_NIMBER) valies' +
        '(:ORG_ID,:COUNT_DATE,:COUNT_NUMBER)')
    RefreshSQL.Strings = (
      'SELECT'
      '    ORG_ID,'
      '    COUNT_DATE,'
      '    COUNT_NUMBER,'
      '    CUSTOMER_ID,'
      '    USER_ID,'
      '    COUNT_TYPE'
      'FROM'
      '    ACCOUNTS_TEMP '
      ' WHERE '
      '    ACCOUNTS_TEMP.ORG_ID = :OLD_ORG_ID'
      '    and ACCOUNTS_TEMP.COUNT_DATE = :OLD_COUNT_DAYE'
      '    and ACCOUNTS_TEMP.COUNT_NUMBER = :OLD_COUNT_NUMBER'
      '    ')
    AutoUpdateOptions.UpdateTableName = 'ACCOUNTS'
    AutoUpdateOptions.AutoParamsToFields = True
    Transaction = AccountsT
    Database = SaleBookDM.DataBase
    AutoCommit = True
    Left = 728
    Top = 176
    poSQLINT64ToBCD = True
  end
  object SoldGoodsDS: TpFIBDataSet
    CachedUpdates = True
    UpdateSQL.Strings = (
      'UPDATE SGBT'
      'SET '
      '    PRICH = :PRICH,'
      '    FAKT_DAT = :FAKT_DAT'
      'WHERE'
      '    LCHET1 = :LCHET1'
      '    AND LCHET = :OLD_LCHET'
      '')
    DeleteSQL.Strings = (
      'DELETE FROM'
      '    SGBT'
      'WHERE'
      '        USER_ID = :OLD_USER_ID'
      '    ')
    InsertSQL.Strings = (
      'INSERT INTO SGBT('
      '    LCHET1,'
      '    SUMMA,'
      '    WORD,'
      '    METKA,'
      '    NEOPL,'
      '    PNN,'
      '    LCHET,'
      '    FAMILY,'
      '    NAME,'
      '    FATHER,'
      '    KOD,'
      '    C,'
      '    DOC,'
      '    SERIA,'
      '    NOMER,'
      '    DOST,'
      '    D_VIPL,'
      '    ULIC,'
      '    ADRES,'
      '    CHEL,'
      '    METKA1,'
      '    VNOM,'
      '    PRICH,'
      '    IST,'
      '    BSUMMA,'
      '    BWORD,'
      '    FAKT_CHEL,'
      '    FAKT_DAT,'
      '    NSP,'
      '    KEM_VID,'
      '    DATA_VID'
      ')'
      'VALUES('
      '    :LCHET1,'
      '    :SUMMA,'
      '    :WORD,'
      '    :METKA,'
      '    :NEOPL,'
      '    :PNN,'
      '    :LCHET,'
      '    :FAMILY,'
      '    :NAME,'
      '    :FATHER,'
      '    :KOD,'
      '    :C,'
      '    :DOC,'
      '    :SERIA,'
      '    :NOMER,'
      '    :DOST,'
      '    :D_VIPL,'
      '    :ULIC,'
      '    :ADRES,'
      '    :CHEL,'
      '    :METKA1,'
      '    :VNOM,'
      '    :PRICH,'
      '    :IST,'
      '    :BSUMMA,'
      '    :BWORD,'
      '    :FAKT_CHEL,'
      '    :FAKT_DAT,'
      '    :NSP,'
      '    :KEM_VID,'
      '    :DATA_VID'
      ')')
    RefreshSQL.Strings = (
      'SELECT *'
      'FROM'
      '    SGBT g'
      'where(  g.USER_ID=?MAS_USER_ID'
      '     ) and (     G.LCHET = :OLD_LCHET'
      '     )'
      '    '
      '  ')
    SelectSQL.Strings = (
      'SELECT *'
      'FROM'
      '    SGBT g'
      'where g.USER_ID=?MAS_USER_ID'
      '  ')
    AutoUpdateOptions.AutoReWriteSqls = True
    AutoUpdateOptions.CanChangeSQLs = True
    AutoUpdateOptions.AutoParamsToFields = True
    Transaction = SouldGoodsT
    Database = SaleBookDM.DataBase
    AutoCommit = True
    DataSource = AccountsTempS
    Left = 952
    Top = 176
    poSQLINT64ToBCD = True
    oRefreshAfterPost = False
    object SoldGoodsDSUSER_ID: TFIBSmallIntField
      FieldName = 'USER_ID'
    end
    object SoldGoodsDSLCHET1: TFIBStringField
      FieldName = 'LCHET1'
      Size = 10
      EmptyStrToNull = True
    end
    object SoldGoodsDSSUMMA: TFIBFloatField
      FieldName = 'SUMMA'
    end
    object SoldGoodsDSWORD: TFIBStringField
      FieldName = 'WORD'
      EmptyStrToNull = True
    end
    object SoldGoodsDSMETKA: TFIBIntegerField
      FieldName = 'METKA'
    end
    object SoldGoodsDSNEOPL: TFIBIntegerField
      FieldName = 'NEOPL'
    end
    object SoldGoodsDSPNN: TFIBIntegerField
      FieldName = 'PNN'
    end
    object SoldGoodsDSLCHET: TFIBIntegerField
      FieldName = 'LCHET'
    end
    object SoldGoodsDSFAMILY: TFIBStringField
      FieldName = 'FAMILY'
      EmptyStrToNull = True
    end
    object SoldGoodsDSNAME: TFIBStringField
      FieldName = 'NAME'
      EmptyStrToNull = True
    end
    object SoldGoodsDSFATHER: TFIBStringField
      FieldName = 'FATHER'
      EmptyStrToNull = True
    end
    object SoldGoodsDSKOD: TFIBIntegerField
      FieldName = 'KOD'
    end
    object SoldGoodsDSC: TFIBDateField
      FieldName = 'C'
      DisplayFormat = 'dd.mm.yyyy'
    end
    object SoldGoodsDSDOC: TFIBDateField
      FieldName = 'DOC'
      DisplayFormat = 'dd.mm.yyyy'
    end
    object SoldGoodsDSSERIA: TFIBStringField
      FieldName = 'SERIA'
      Size = 8
      EmptyStrToNull = True
    end
    object SoldGoodsDSNOMER: TFIBIntegerField
      FieldName = 'NOMER'
    end
    object SoldGoodsDSDOST: TFIBIntegerField
      FieldName = 'DOST'
    end
    object SoldGoodsDSD_VIPL: TFIBIntegerField
      FieldName = 'D_VIPL'
    end
    object SoldGoodsDSULIC: TFIBStringField
      FieldName = 'ULIC'
      EmptyStrToNull = True
    end
    object SoldGoodsDSADRES: TFIBStringField
      FieldName = 'ADRES'
      Size = 14
      EmptyStrToNull = True
    end
    object SoldGoodsDSCHEL: TFIBIntegerField
      FieldName = 'CHEL'
    end
    object SoldGoodsDSMETKA1: TFIBIntegerField
      FieldName = 'METKA1'
    end
    object SoldGoodsDSVNOM: TFIBIntegerField
      FieldName = 'VNOM'
    end
    object SoldGoodsDSPRICH: TFIBStringField
      FieldName = 'PRICH'
      OnChange = SoldGoodsDSPRICHChange
      Size = 6
      EmptyStrToNull = True
    end
    object SoldGoodsDSIST: TFIBIntegerField
      FieldName = 'IST'
    end
    object SoldGoodsDSBSUMMA: TFIBIntegerField
      FieldName = 'BSUMMA'
    end
    object SoldGoodsDSBWORD: TFIBStringField
      FieldName = 'BWORD'
      Size = 11
      EmptyStrToNull = True
    end
    object SoldGoodsDSFAKT_CHEL: TFIBIntegerField
      FieldName = 'FAKT_CHEL'
    end
    object SoldGoodsDSFAKT_DAT: TFIBIntegerField
      FieldName = 'FAKT_DAT'
    end
    object SoldGoodsDSNSP: TFIBIntegerField
      FieldName = 'NSP'
    end
    object SoldGoodsDSKEM_VID: TFIBStringField
      FieldName = 'KEM_VID'
      Size = 40
      EmptyStrToNull = True
    end
    object SoldGoodsDSDATA_VID: TFIBDateField
      FieldName = 'DATA_VID'
      DisplayFormat = 'dd.mm.yyyy'
    end
    object SoldGoodsDSKODPEN: TFIBIntegerField
      FieldName = 'KODPEN'
    end
    object SoldGoodsDSFOND: TFIBIntegerField
      FieldName = 'FOND'
    end
    object SoldGoodsDSKASSA: TFIBSmallIntField
      DefaultExpression = '0'
      FieldName = 'KASSA'
    end
  end
  object TempQ: TpFIBQuery
    Transaction = DT
    Database = SaleBookDM.DataBase
    Left = 240
    Top = 112
    qoAutoCommit = True
    qoStartTransaction = True
  end
  object TQ: TpFIBQuery
    Transaction = WT
    Database = SaleBookDM.DataBase
    ParamCheck = False
    Left = 240
    Top = 160
    qoAutoCommit = True
  end
  object WT: TpFIBTransaction
    Active = True
    DefaultDatabase = SaleBookDM.DataBase
    Timeout = 5
    TimeoutAction = TARollbackRetaining
    TPBMode = tpbDefault
    Left = 240
    Top = 208
  end
  object AccountsT: TpFIBTransaction
    Active = True
    DefaultDatabase = SaleBookDM.DataBase
    TimeoutAction = TARollback
    Left = 736
    Top = 232
  end
  object SouldGoodsT: TpFIBTransaction
    Active = True
    DefaultDatabase = SaleBookDM.DataBase
    TimeoutAction = TARollback
    Left = 960
    Top = 224
  end
  object DT: TpFIBTransaction
    Active = True
    DefaultDatabase = SaleBookDM.DataBase
    TimeoutAction = TARollback
    Left = 272
    Top = 216
  end
  object searchTimer: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = searchTimerTimer
    Left = 400
    Top = 144
  end
  object NDOST: TpFIBDataSet
    UpdateSQL.Strings = (
      'UPDATE ACCOUNTS_TEMP'
      'SET '
      '    COUNT_DATE = :COUNT_DATE,'
      '    COUNT_NUMBER = :COUNT_NUMBER,'
      '    CUSTOMER_ID = :CUSTOMER_ID,'
      '    USER_ID = :USER_ID,'
      '    COUNT_TYPE = :COUNT_TYPE'
      'WHERE'
      '    ORG_ID = :OLD_ORG_ID'
      '    and COUNT_DATE = :OLD_COUNT_DATE'
      '    and COUNT_NUMBER = :OLD_COUNT_NUMBER'
      '    ')
    InsertSQL.Strings = (
      
        'insert into ACCOUNTS_TEMP(ORG_ID,COUNT_DATE,COUNT_NIMBER) valies' +
        '(:ORG_ID,:COUNT_DATE,:COUNT_NUMBER)')
    RefreshSQL.Strings = (
      'SELECT'
      '    ORG_ID,'
      '    COUNT_DATE,'
      '    COUNT_NUMBER,'
      '    CUSTOMER_ID,'
      '    USER_ID,'
      '    COUNT_TYPE'
      'FROM'
      '    ACCOUNTS_TEMP '
      ' WHERE '
      '    ACCOUNTS_TEMP.ORG_ID = :OLD_ORG_ID'
      '    and ACCOUNTS_TEMP.COUNT_DATE = :OLD_COUNT_DAYE'
      '    and ACCOUNTS_TEMP.COUNT_NUMBER = :OLD_COUNT_NUMBER'
      '    ')
    AutoUpdateOptions.UpdateTableName = 'ACCOUNTS'
    AutoUpdateOptions.AutoParamsToFields = True
    Transaction = AccountsT
    Database = SaleBookDM.DataBase
    AutoCommit = True
    Left = 824
    Top = 136
    poSQLINT64ToBCD = True
  end
  object DB1: TpFIBDataSet
    UpdateSQL.Strings = (
      'UPDATE '
      'SET '
      'WHERE'
      '    ')
    DeleteSQL.Strings = (
      'DELETE FROM'
      '    '
      'WHERE'
      '        ')
    InsertSQL.Strings = (
      'INSERT INTO ('
      ')'
      'VALUES('
      ')')
    Transaction = ReadTransaction
    Database = SaleBookDM.DataBase
    AutoCommit = True
    Left = 56
    Top = 128
  end
  object ReadTransaction: TpFIBTransaction
    Active = True
    DefaultDatabase = SaleBookDM.DataBase
    TimeoutAction = TARollback
    Left = 144
    Top = 80
  end
end
