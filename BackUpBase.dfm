object BackUpBaseForm: TBackUpBaseForm
  Left = 754
  Top = 366
  Width = 611
  Height = 456
  Caption = #1057#1086#1079#1076#1072#1085#1080#1077' '#1072#1088#1093#1080#1074#1072' '#1073#1072#1079#1099' '#1076#1072#1085#1085#1099#1093
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 16
  object WaitingGradient: TJvWaitingGradient
    Left = 0
    Top = 405
    Width = 595
    Height = 5
    Align = alBottom
    Color = clBtnFace
    GradientWidth = 50
    EndColor = clTeal
    ParentColor = False
    Visible = False
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 595
    Height = 206
    Align = alTop
    BevelOuter = bvNone
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 0
    DesignSize = (
      595
      206)
    object Label3: TLabel
      Left = 24
      Top = 124
      Width = 558
      Height = 16
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Caption = #1057#1077#1090#1077#1074#1086#1077' '#1080#1084#1103' zip '#1072#1088#1093#1080#1074#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 24
      Top = 80
      Width = 558
      Height = 16
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Caption = #1057#1077#1090#1077#1074#1086#1077' '#1087#1091#1090#1100' '#1082' BackUp '#1092#1072#1081#1083#1091
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label5: TLabel
      Left = 24
      Top = 36
      Width = 558
      Height = 16
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Caption = #1048#1084#1103' BackUp '#1092#1072#1081#1083#1072'  '#1085#1072' '#1089#1077#1088#1074#1077#1088#1077' (*.gbk)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object CheckBox1: TCheckBox
      Left = 24
      Top = 170
      Width = 177
      Height = 17
      Caption = #1074#1077#1089#1090#1080' '#1087#1088#1086#1090#1086#1082#1086#1083
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
    end
    object ArchButton: TBitBtn
      Left = 373
      Top = 170
      Width = 113
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1042#1099#1087#1086#1083#1085#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = ArchButtonClick
      Glyph.Data = {
        F6000000424DF600000000000000760000002800000010000000100000000100
        0400000000008000000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFF0B7FFF
        FFB0FFFFFF0B7FFFFFB0FFFFFF0B7FFFFFB0FFFFFF0B7FFFFFB0000000000077
        00700FFFFFFFF00077B00FFFFFFFF00077B00000F000F00090070FFFFFFFF0F9
        99FF000000F0F099999F0FFFFFFFF99999990000F00000F999FF0FFFF0FF0FF9
        99FF0077F0FF0FF999FF0FFFF0F0FF7999FF0000000F999999FF}
    end
    object ExitButton: TBitBtn
      Left = 509
      Top = 170
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1042#1099#1093#1086#1076
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
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
    object ZipFilenameEdit: TFilenameEdit
      Left = 24
      Top = 140
      Width = 559
      Height = 21
      DefaultExt = '.zip'
      Filter = #1048#1084#1103' '#1072#1088#1093#1080#1074#1085#1086#1075#1086' '#1092#1072#1081#1083#1072'  (*.zip)|*.zip'
      Anchors = [akLeft, akTop, akRight]
      NumGlyphs = 1
      TabOrder = 3
    end
    object BackUpDirEdit: TDirectoryEdit
      Left = 24
      Top = 96
      Width = 559
      Height = 21
      NumGlyphs = 1
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 4
    end
    object Label2: TJvNavPanelHeader
      Left = 0
      Top = 0
      Width = 595
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
    object BackUpFilenameEdit: TFilenameEdit
      Left = 24
      Top = 52
      Width = 559
      Height = 21
      DefaultExt = '.zip'
      Filter = #1048#1084#1103' '#1072#1088#1093#1080#1074#1085#1086#1075#1086' '#1092#1072#1081#1083#1072'  (*.gbk)|*.gbk'
      Anchors = [akLeft, akTop, akRight]
      NumGlyphs = 1
      TabOrder = 6
    end
  end
  object RichEdit1: TRichEdit
    Left = 0
    Top = 206
    Width = 595
    Height = 199
    Align = alClient
    BevelInner = bvNone
    BevelOuter = bvRaised
    BevelKind = bkFlat
    BorderStyle = bsNone
    Ctl3D = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 1
  end
  object ProgressBar: TJvProgressBar
    Left = 0
    Top = 410
    Width = 595
    Height = 8
    Align = alBottom
    Min = 0
    Max = 1100
    Smooth = True
    Step = 1
    TabOrder = 2
    Visible = False
    FillColor = clTeal
  end
  object FormStorage1: TFormStorage
    IniFileName = '.\Avia.ini'
    IniSection = 'BackUpBaseForm'
    StoredValues = <>
    Left = 72
    Top = 256
  end
  object ZipBuilder: TZipBuilder
    VersionInfo = '1.73'
    AddStoreSuffixes = [assGIF, assPNG, assZ, assZIP, assZOO, assARC, assLZH, assARJ, assTAZ, assTGZ, assLHA, assRAR, assACE, assCAB, assGZ, assGZIP, assJAR]
    SFXOptions = [SFXCheckSize]
    SFXPath = 'ZipSFX.bin'
    SFXCaption = 'Self-extracting Archive'
    Left = 152
    Top = 256
  end
  object BackupService: TIBBackupService
    Protocol = TCP
    TraceFlags = []
    Verbose = True
    BlockingFactor = 0
    Options = []
    Left = 224
    Top = 256
  end
end
