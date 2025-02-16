//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DataModule.h"
#include "Main.h"
#include "RestoreBase.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Placemnt"
#pragma link "IB_Services"
#pragma link "ToolEdit"
#pragma link "ZipBuilder"
#pragma link "RxRichEd"
#pragma link "JvComponent"
#pragma link "JvExControls"
#pragma link "JvNavigationPane"
#pragma link "JvWaitingGradient"
#pragma link "JvExStdCtrls"
#pragma link "JvMemo"
#pragma link "JvWaitingProgress"
#pragma link "JvWaitingProgress"
#pragma link "JvWaitingProgress"
#pragma link "JvProgressBar"
#pragma link "JvExComCtrls"
#pragma link "JvWaitingProgress"
#pragma resource "*.dfm"
//TRestoreBaseForm *RestoreBaseForm;
//---------------------------------------------------------------------------
__fastcall TRestoreBaseForm::TRestoreBaseForm(TComponent* Owner)
        : TForm(Owner)
{
  FormStorage1->IniFileName=MainForm->WorkDir+"SB_2009.ini";
  FormStorage1->IniSection="RestoreBaseForm";

  server=SaleBookDM->Server;
  dbFullName=SaleBookDM->DB_Name;

  Label2->Caption="���� ������ - "+server+dbFullName;
  TIniFile *ini = new TIniFile(MainForm->WorkDir+"SB_2009.ini");
  zipFilenameEdit->Text=ini->ReadString(server+"BackUpBaseForm","ZipFileName","");
  backupFilenameEdit->Text=ini->ReadString(server+"BackUpBaseForm","BackUpNetDirectory","")+"\\"+ChangeFileExt(SaleBookDM->Base_Name,".gbk");
  dbNetDirectoryEdit->Text=ini->ReadString(server+"RestoreBaseForm","dbNetDirectory","");
  dbCopyDirectoryEdit->Text=ini->ReadString(server+"RestoreBaseForm","dbCopyDirectory","");
  delete ini;
}
//---------------------------------------------------------------------------
void __fastcall TRestoreBaseForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  TIniFile *ini = new TIniFile(MainForm->WorkDir+"SB_2009.ini");
  ini->WriteString(server+"RestoreBaseForm","dbNetDirectory",dbNetDirectoryEdit->Text);
  ini->WriteString(server+"RestoreBaseForm","dbCopyDirectory",dbCopyDirectoryEdit->Text);
  delete ini;

  SetCurrentDir(MainForm->WorkDir);
}
//---------------------------------------------------------------------------
void __fastcall TRestoreBaseForm::ExitButtonClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TRestoreBaseForm::RestoreButtonClick(TObject *Sender)
{
  //��������� ������� ����������� � ���� ������
  AnsiString str;
  TpFIBQuery * TQ=SaleBookDM->TempQuery;
  TQ->Close();
  TQ->SQL->Clear();
  str="select USER_ID from USERS_MONITOR where USER_ID <> "+IntToStr(SaleBookDM->UserID);
  TQ->SQL->Add(str);
  try
  {
    TQ->ExecQuery();
  }
  catch(const Exception &exc)
  { MessageDlg("������ select USER_ID from USERS_MONITOR where USER_ID <> "+IntToStr(SaleBookDM->UserID)+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    TQ->Close();
    return;
  }
  if(TQ->RecordCount > 0)
  { MessageDlg("�������������� ���� ������ �������� ������ � ����������� ������.\n������� � ������� ������������� � ���������, ��� ����� ��� ����� �� ������� � �����.",mtWarning,TMsgDlgButtons() << mbOK,0);
    TQ->Close();
    return;
  }
  TQ->Close();

  if(backupFilenameEdit->Text.IsEmpty())
  { MessageDlg("�� ������� ��� BackUp �����",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }

  if(dbNetDirectoryEdit->Text.IsEmpty() || !DirectoryExists(dbNetDirectoryEdit->Text))
  { if(dbNetDirectoryEdit->Text.IsEmpty())
      MessageDlg("�� ������ ������� ���� � ���� ������",mtError,TMsgDlgButtons() << mbOK,0);
    else
      MessageDlg("������� \""+dbNetDirectoryEdit->Text+"\" �����������",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }

  if(dbCopyDirectoryEdit->Text.IsEmpty() || !DirectoryExists(dbCopyDirectoryEdit->Text))
  { if(dbCopyDirectoryEdit->Text.IsEmpty())
      MessageDlg("�� ������� ����� ��� ����� ���� ������",mtError,TMsgDlgButtons() << mbOK,0);
    else
      MessageDlg("������� \""+dbCopyDirectoryEdit->Text+"\" �����������",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }

  AnsiString backupFileName=backupFilenameEdit->Text;

  RichEdit->Lines->Clear();
  RichEdit->SetFocus();
  TColor color=RichEdit->DefAttributes->Color;
  int size=RichEdit->DefAttributes->Size;
  RichEdit->SelAttributes->Color=clRed;
  RichEdit->SelAttributes->Size=10;

  WaitingGradient->Visible=true;
  WaitingGradient->Active=true;

  //������������� �����
  if(!zipFilenameEdit->Text.IsEmpty() && FileExists(zipFilenameEdit->Text))
  {
    RichEdit->Lines->Add("���������� BackUp ����� �� ������...");
    RichEdit->Repaint();

    ZipBuilder->ZipFileName=zipFilenameEdit->Text;
    ZipBuilder->ExtrBaseDir=ExtractFileDir(backupFilenameEdit->Text);
    ZipBuilder->FSpecArgs->Clear();
    ZipBuilder->ExtrOptions.Clear();
    ZipBuilder->ExtrOptions << ExtrOverWrite;
    ZipBuilder->Extract();
    if(ZipBuilder->SuccessCnt != 1)
    { MessageDlg("������ ���������� BackUp �����",mtError,TMsgDlgButtons() << mbOK,0);
      ProgressBar->Position=0;
      return;
    }

    ProgressBar->Position=20;

    RichEdit->SelAttributes->Color=clBlue;
    RichEdit->SelAttributes->Size=10;
    RichEdit->Lines->Add("BackUp ���� ��������!");
    RichEdit->Repaint();
  }

  if(!FileExists(backupFilenameEdit->Text))
  { MessageDlg("BackUP ����� \""+backupFilenameEdit->Text+"\" �����������",mtError,TMsgDlgButtons() << mbOK,0);
    ProgressBar->Position=0;
    return;
  }

  SaleBookDM->DisConnectDataBase();

  ProgressBar->Position=30;
  ProgressBar->Refresh();

  //��������� ������ ����
  RichEdit->SelAttributes->Color=clRed;
  RichEdit->SelAttributes->Size=10;
  RichEdit->Lines->Add("��������� ������ ���� ������");
  RichEdit->Repaint();

  AnsiString oldDBFileName, dbFileName;
  dbFileName=SaleBookDM->DB_Name;
//  dbFileName=dbNetDirectoryEdit->Text+"\\"+SaleBookDM->Base_Name;
  unsigned short y,m,d;
  Date().DecodeDate(&y,&m,&d);
  oldDBFileName=dbCopyDirectoryEdit->Text+"\\"+SaleBookDM->Base_Name.SubString(0,SaleBookDM->Base_Name.Pos(".")-1)+AnsiString().sprintf("%4d%02d%02d",y,m,d)+".old";

  int hDB, hOldDB;
  hDB=FileOpen(dbFileName,fmOpenRead);
  if(hDB < 0)
  { MessageDlg("������ �������� ����� - "+dbFileName,mtError,TMsgDlgButtons() << mbOK,0);
    RichEdit->Lines->Clear();
    return;
  }
  if(FileExists(oldDBFileName)) DeleteFile(oldDBFileName);
  hOldDB=FileCreate(oldDBFileName);
  if(hOldDB < 0)
  { MessageDlg("������ �������� ����� - "+oldDBFileName,mtError,TMsgDlgButtons() << mbOK,0);
    RichEdit->Lines->Clear();
    return;
  }
  char buf[32768];
  int rb=0;
  while((rb=FileRead(hDB,buf,sizeof(buf))) > 0)
  { if(FileWrite(hOldDB,buf,rb) < 0)
    { MessageDlg("������ ����������� ����� - ",mtError,TMsgDlgButtons() << mbOK,0);
      RichEdit->Lines->Clear();
      return;
    }
  }
  FileClose(hDB);
  FileClose(hOldDB);

  //  if(FileExists(oldDBFileName)) DeleteFile(oldDBFileName);
//  RenameFile(dbFileName,oldDBFileName);
//  if(!FileExists(oldDBFileName))
//  { MessageDlg("������ ��� ���������� ������ ����",mtError,TMsgDlgButtons() << mbOK,0);
//    ProgressBar->Position=0;
//    return;
//  }

  WaitingGradient->Active=false;
  WaitingGradient->Visible=false;

  RichEdit->SelAttributes->Color=clBlue;
  RichEdit->SelAttributes->Size=10;
  RichEdit->Lines->Add("������ ���� ��������� � ����� - "+oldDBFileName);
  RichEdit->Repaint();

  //�������������� ���� �� BuckUp ����
  RichEdit->SelAttributes->Color=clRed;
  RichEdit->SelAttributes->Size=10;
  RichEdit->Lines->Add("�������������� ���� ������ �� BackUp �����...");
  RichEdit->SelAttributes->Color=color;
  RichEdit->SelAttributes->Size=size;
  RichEdit->Repaint();

  //���������� ������
  RestoreService->ServerName=server.SubString(0,server.Length()-1);
  RestoreService->LoginPrompt=false;
  RestoreService->Params->Clear();
  RestoreService->Params->Add("user_name=SYSDBA");
  RestoreService->Params->Add("password=masterkey");
  RestoreService->Protocol=TCP;
  RestoreService->Active=true;
  RestoreService->Verbose = true;
  RestoreService->PageSize=8192;
  RestoreService->BufferSize=32000;
  RestoreService->DatabaseName->Clear();
  RestoreService->DatabaseName->Add(dbFullName);
  RestoreService->BackupFile->Clear();
  RestoreService->BackupFile->Add(backupFilenameEdit->Text);

  if(CheckBox1->Checked==false)
  { ProgressBar->Visible=true;
    ProgressBar->Position=0;
  }
  try
  { AnsiString Text;
    RestoreService->ServiceStart();
    while(!RestoreService->Eof)
    { Text=RestoreService->GetNextLine();
      if(CheckBox1->Checked)
      { RichEdit->Lines->Add(Text);
        RichEdit->Repaint();
        RichEdit->SetFocus();
        RichEdit->SelStart=RichEdit->Text.Length();
        RichEdit->SelLength=0;
      }
      else
      { ProgressBar->StepIt();
        ProgressBar->Refresh();
      }
    }
  }
  catch(const Exception &exc)
  { MessageDlg("������ �������������� �� BackUp �����\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    RestoreService->Active = false;
    ProgressBar->Position=0;
    return;
  }
  RestoreService->Active = false;

  RichEdit->SelAttributes->Color=clBlue;
  RichEdit->SelAttributes->Size=10;
  RichEdit->Lines->Add("���� ������ �������������!");
  RichEdit->Repaint();

  if(ProgressBar->Visible)
  { ProgressBar->Position=0;
    ProgressBar->Visible=false;
  }

  //�������� BackUp �����
  if(!zipFilenameEdit->Text.IsEmpty() && FileExists(backupFileName))
  { RichEdit->SelAttributes->Color=clRed;
    RichEdit->SelAttributes->Size=10;
    RichEdit->Lines->Add("�������� BackUp �����...");
    RichEdit->Repaint();
    DeleteFile(backupFileName);
    RichEdit->SelAttributes->Color=clBlue;
    RichEdit->SelAttributes->Size=10;
    if(!FileExists(backupFileName))
      RichEdit->Lines->Add("���� ������!");
    else
      MessageDlg("�� ���� ������� BackUp ���� - "+backupFileName,mtError,TMsgDlgButtons() << mbOK,0);
    RichEdit->Lines->Add("\n");
    RichEdit->SelAttributes->Color=clBlue;
    RichEdit->SelAttributes->Size=10;
    RichEdit->Lines->Add("�������� ���������!");
    RichEdit->Repaint();
  }

  RichEdit->SelAttributes->Color=color;
  RichEdit->SelAttributes->Size=size;

  SaleBookDM->ConnectToDataBase();

  //�������� �������� � ������� ������� ACTIONS_JOURNAL
  str="������������� ���� ������ �� ������ - "+zipFilenameEdit->Text;
  SaleBookDM->TT->StartTransaction();
  if(SaleBookDM->AddRecordToActionsJournal(RestoreBase,str,SaleBookDM->TT)==true)
    SaleBookDM->TT->Commit();
  else SaleBookDM->TT->Rollback();
}
//---------------------------------------------------------------------------

