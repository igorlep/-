object RestoreBaseForm: TRestoreBaseForm
  Left = 291
  Top = 118
  AutoScroll = False
  Caption = ' '#1042#1086#1089#1089#1090#1072#1085#1086#1074#1083#1077#1085#1080#1077' '#1073#1072#1079#1099' '#1076#1072#1085#1085#1099#1093' '#1080#1079' '#1072#1088#1093#1080#1074#1072
  ClientHeight = 434
  ClientWidth = 572
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PrintScale = poNone
  Scaled = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object WaitingGradient: TJvWaitingGradient
    Left = 0
    Top = 421
    Width = 572
    Height = 5
    Align = alBottom
    Color = clBtnFace
    GradientWidth = 50
    EndColor = clTeal
    ParentColor = False
    Visible = False
  end
  object JvWaitingProgress1: TJvWaitingProgress
    Left = 472
    Top = 456
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 572
    Height = 254
    Align = alTop
    BevelOuter = bvNone
    Ctl3D = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 1
    DesignSize = (
      572
      254)
    object Label1: TLabel
      Left = 20
      Top = 36
      Width = 525
      Height = 16
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Caption = #1057#1077#1090#1077#1074#1086#1077' '#1080#1084#1103' '#1092#1072#1081#1083#1072' '#1089' '#1072#1088#1093#1080#1074#1086#1084' (*.zip)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label3: TLabel
      Left = 20
      Top = 80
      Width = 533
      Height = 16
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Caption = #1057#1077#1090#1077#1074#1086#1077' '#1080#1084#1103' BackUp '#1092#1072#1083#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label5: TLabel
      Left = 20
      Top = 124
      Width = 529
      Height = 16
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Caption = #1057#1077#1090#1077#1074#1086#1077' '#1087#1091#1090#1100' '#1082' '#1073#1072#1079#1077' '#1076#1072#1085#1085#1099#1093
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label6: TLabel
      Left = 20
      Top = 172
      Width = 529
      Height = 16
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Caption = #1055#1072#1087#1082#1072' '#1076#1083#1103' '#1082#1086#1087#1080#1080' '#1073#1072#1079#1099' '#1076#1072#1085#1085#1099#1093
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object zipFilenameEdit: TFilenameEdit
      Left = 20
      Top = 52
      Width = 529
      Height = 21
      Filter = #1040#1088#1093#1080#1074#1085#1099#1081' '#1092#1072#1081#1083'  (*.zip)|*.zip'
      ButtonWidth = 17
      Anchors = [akLeft, akTop, akRight]
      NumGlyphs = 1
      TabOrder = 0
    end
    object CheckBox1: TCheckBox
      Left = 22
      Top = 227
      Width = 131
      Height = 14
      Caption = #1074#1077#1089#1090#1080' '#1087#1088#1086#1090#1086#1082#1086#1083
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
    end
    object backupFilenameEdit: TFilenameEdit
      Left = 20
      Top = 96
      Width = 529
      Height = 21
      Filter = #1060#1072#1081#1083' '#1073#1072#1079#1099' '#1076#1072#1085#1085#1099#1093'  (*.gdk)|*.gdk'
      ButtonWidth = 17
      Anchors = [akLeft, akTop, akRight]
      NumGlyphs = 1
      TabOrder = 2
    end
    object RestoreButton: TBitBtn
      Left = 360
      Top = 219
      Width = 112
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1042#1099#1087#1086#1083#1085#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      OnClick = RestoreButtonClick
      Glyph.Data = {
        F6000000424DF600000000000000760000002800000010000000100000000100
        0400000000008000000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFF0B7FFF
        FFB0FFFFFF0B7FFFFFB0FFFFFF0B7FFFFFB0FFFFFF0B7FFFFFB0000000000077
        00700FFFFFFFF00077B00FFFFFFFF00077B00000F000F00000070FFFFFFFF0FF
        99FF000000F0F9FF99FF0FFFFFF799F799FF0000F779999999FF0FFFF7999999
        99FF0077F0F9999999FF0FFFF0F799FFFFFF0000000FF9FFFFFF}
    end
    object ExitButton: TBitBtn
      Left = 480
      Top = 219
      Width = 79
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1042#1099#1093#1086#1076
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      OnClick = ExitButtonClick
      Glyph.Data = {
        F6000000424DF600000000000000760000002800000010000000100000000100
        0400000000008000000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFF00FF00F08
        0070F00FF00FF00870070000000008087700FFFFFF0880087770FFFFFF000008
        7770FFFFFF0777087770FFFFFF0777087770FF00000007080770FF0999990708
        7770F099999077087770F090990777087770F000900777087770FFF00F077770
        8770FFFFFF0777770870FFFFFF0777777080FFFFFF0000000000}
    end
    object dbNetDirectoryEdit: TDirectoryEdit
      Left = 20
      Top = 140
      Width = 529
      Height = 21
      NumGlyphs = 1
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 5
    end
    object dbCopyDirectoryEdit: TDirectoryEdit
      Left = 20
      Top = 188
      Width = 529
      Height = 21
      NumGlyphs = 1
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 6
    end
    object Label2: TJvNavPanelHeader
      Left = 0
      Top = 0
      Width = 572
      Height = 20
      Align = alTop
      Alignment = taCenter
      Caption = 'Label2'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      ColorFrom = 16776176
      ColorTo = clActiveCaption
      ImageIndex = 0
    end
  end
  object RichEdit: TRichEdit
    Left = 0
    Top = 254
    Width = 572
    Height = 167
    Align = alClient
    BevelInner = bvNone
    BevelOuter = bvRaised
    BevelKind = bkFlat
    BorderStyle = bsNone
    Ctl3D = False
    ParentCtl3D = False
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 2
  end
  object ProgressBar: TJvProgressBar
    Left = 0
    Top = 426
    Width = 572
    Height = 8
    Align = alBottom
    Min = 0
    Max = 1100
    Smooth = True
    Step = 1
    TabOrder = 3
    Visible = False
    FillColor = clTeal
  end
  object FormStorage1: TFormStorage
    IniFileName = '.\Avia'#0'ini'
    IniSection = 'RestoreBaseForm'
    StoredValues = <>
    Left = 120
    Top = 288
  end
  object ZipBuilder: TZipBuilder
    VersionInfo = '1.73'
    AddStoreSuffixes = [assGIF, assPNG, assZ, assZIP, assZOO, assARC, assLZH, assARJ, assTAZ, assTGZ, assLHA, assRAR, assACE, assCAB, assGZ, assGZIP, assJAR]
    SFXOptions = [SFXCheckSize]
    SFXPath = 'ZipSFX.bin'
    SFXCaption = 'Self-extracting Archive'
    Left = 152
    Top = 288
  end
  object RestoreService: TIBRestoreService
    Protocol = TCP
    TraceFlags = []
    Verbose = True
    PageSize = 8192
    PageBuffers = 0
    Options = [Replace]
    Left = 184
    Top = 288
  end
end
