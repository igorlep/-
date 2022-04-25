//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdio.h>

#include "DataModule.h"
#include "Main.h"
#include "utils.h"
#include "BackUpBase.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RxRichEd"
#pragma link "IB_Services"
#pragma link "Placemnt"
#pragma link "ToolEdit"
#pragma link "ZipBuilder"
#pragma link "JvComponent"
#pragma link "JvExControls"
#pragma link "JvNavigationPane"
#pragma link "JvExComCtrls"
#pragma link "JvProgressBar"
#pragma link "IB_Services"
#pragma link "JvWaitingGradient"
#pragma resource "*.dfm"
//TBackUpBaseForm *BackUpBaseForm;
//---------------------------------------------------------------------------
__fastcall TBackUpBaseForm::TBackUpBaseForm(TComponent* Owner)
        : TForm(Owner)
{
  FormStorage1->IniFileName=MainForm->WorkDir+"SB_2009.ini";
  FormStorage1->IniSection="BackUpBaseForm";

  server=SaleBookDM->Server;

  unsigned short y,m,d;
  Date().DecodeDate(&y,&m,&d);
  char buf[10];
  sprintf(buf,"%02d%02d%02d",y-2000,m,d);

  Label2->Caption="База данных - "+SaleBookDM->Server+SaleBookDM->DB_Name;
  TIniFile *ini = new TIniFile(MainForm->WorkDir+"SB_2009.ini");
  BackUpFilenameEdit->FileName=ini->ReadString(server+"BackUpBaseForm","BackUpFileName","");
  BackUpDirEdit->Text=ini->ReadString(server+"BackUpBaseForm","BackUpNetDirectory","");
  ZipFilenameEdit->FileName=ini->ReadString(server+"BackUpBaseForm","ZipFileName","");
  delete ini;
  ZipFilenameEdit->FileName=ExtractFileDir(ZipFilenameEdit->FileName)+"\\"+buf+".zip";
}
//---------------------------------------------------------------------------
void __fastcall TBackUpBaseForm::ExitButtonClick(TObject *Sender)
{
  SetCurrentDir(MainForm->WorkDir);
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TBackUpBaseForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  TIniFile *ini = new TIniFile(MainForm->WorkDir+"SB_2009.ini");
  ini->WriteString(server+"BackUpBaseForm","BackUpFileName",BackUpFilenameEdit->FileName);
  ini->WriteString(server+"BackUpBaseForm","BackUpNetDirectory",BackUpDirEdit->Text);
  ini->WriteString(server+"BackUpBaseForm","ZipFileName",ZipFilenameEdit->FileName);
  delete ini;

  SetCurrentDir(MainForm->WorkDir);
}
//---------------------------------------------------------------------------
void __fastcall TBackUpBaseForm::ArchButtonClick(TObject *Sender)
{

  ProgressBar->Visible=true;
  ProgressBar->Position=0;

  //Фиксирем действие в журнале событий ACTIONS_JOURNAL
  AnsiString str;
  TpFIBQuery * TQ=SaleBookDM->TempQuery;
  TQ->Close();
  TQ->SQL->Clear();
  str="select GEN_ID(GEN_ACTIONS_JOURNAL_ID,1) as ID from RDB$DATABASE";
  TQ->SQL->Add(str);
  try
  {
    TQ->ExecQuery();
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка select GEN_ID(GEN_ACTIONS_JOURNAL_ID,1) as ID from RDB$DATABASE\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  int id=TQ->FieldByName("ID")->AsInteger;
  TQ->Close();
  str="Создан архив базы данных. BackUp файл - "+BackUpFilenameEdit->FileName+", Архивный файл - "+ZipFilenameEdit->FileName;
  SaleBookDM->TT->StartTransaction();
  if(SaleBookDM->AddRecordToActionsJournal(BackUpBase,str,SaleBookDM->TT)==true)
    SaleBookDM->TT->Commit();
  else SaleBookDM->TT->Rollback();

  //Инициализация сервиса создания BackUp файла
  BackupService->ServerName=SaleBookDM->Server.SubString(0,SaleBookDM->Server.Length()-1);
  BackupService->LoginPrompt=false;
  BackupService->Params->Clear();
  BackupService->Params->Add("user_name=SYSDBA");
  BackupService->Params->Add("password=masterkey");
  BackupService->Protocol=TCP;
  BackupService->Active = true;
  BackupService->Verbose = true;
  BackupService->DatabaseName=SaleBookDM->DB_Name;
  BackupService->BackupFile->Clear();
  BackupService->BackupFile->Add(BackUpFilenameEdit->FileName);

  RichEdit1->Lines->Clear();
  RichEdit1->SetFocus();
  TColor color=RichEdit1->DefAttributes->Color;
  int size=RichEdit1->DefAttributes->Size;
  RichEdit1->SelAttributes->Color=clRed;
  RichEdit1->SelAttributes->Size=10;
  RichEdit1->Lines->Add("Создание Backup файла базы данных...");
  RichEdit1->SelAttributes->Color=color;
  RichEdit1->SelAttributes->Size=size;
  RichEdit1->Repaint();

  if(CheckBox1->Checked==false)
  { ProgressBar->Visible=true;
    ProgressBar->Position=0;
  }

  //Старт
  try
  { AnsiString Text;
    BackupService->ServiceStart();
    while(!BackupService->Eof)
    { Text=BackupService->GetNextLine();
      if(CheckBox1->Checked)
      { RichEdit1->Lines->Add(Text);
        RichEdit1->Repaint();
        RichEdit1->SetFocus();
        RichEdit1->SelStart=RichEdit1->Text.Length();
        RichEdit1->SelLength=0;
      }
      else
      { ProgressBar->StepIt();
        ProgressBar->Refresh();
      }
    }
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка создания BackUp файла\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    RichEdit1->Lines->Clear();
    ActionsJournalClear(id);
    return;
  }

  RichEdit1->SelAttributes->Color=clBlue;
  RichEdit1->SelAttributes->Size=10;
  RichEdit1->Lines->Add("Backup файл базы данных создан! Имя файла - "+BackUpFilenameEdit->FileName);
  RichEdit1->Repaint();
  BackupService->Active = false;

  if(ProgressBar->Visible)
  { ProgressBar->Position=0;
    ProgressBar->Visible=false;
  }
  WaitingGradient->Visible=true;
  WaitingGradient->Active=true;

  //Архивируем созданный BackUp файл
  AnsiString zip=ZipFilenameEdit->FileName;
  AnsiString bfn=BackUpFilenameEdit->FileName;
  int p=bfn.Length(), p1=p;
  while(p>1 && bfn[p]!='\\' && bfn[p]!='/') --p;
  if(bfn[p]=='\\' || bfn[p]=='/') p++;
  AnsiString backup=BackUpDirEdit->Text+"\\"+bfn.SubString(p,p1-p+1);
  if(FileExists(backup))
  { RichEdit1->SelAttributes->Color=clRed;
    RichEdit1->SelAttributes->Size=10;
    RichEdit1->Lines->Add("Архивирование Backup файла...");
    RichEdit1->Repaint();
    RichEdit1->SelAttributes->Color=clBlue;
    RichEdit1->SelAttributes->Size=10;
    if(FileExists(zip)) DeleteFile(zip);
    ZipBuilder->ZipFileName=zip;
    ZipBuilder->FSpecArgs->Clear();
    ZipBuilder->FSpecArgs->Add(backup);
    ZipBuilder->Add();
    if(ZipBuilder->ErrCode != 0)
    { MessageDlg("Ошибка создания архива. Код ошибки - "+IntToStr(ZipBuilder->ErrCode)+".\n"+ZipBuilder->Message,mtError,TMsgDlgButtons() << mbOK,0);
      ActionsJournalClear(id);
      return;
    }

    //Проверяем целостность созданного архива
    ZipBuilder->ZipFileName=zip;
    ZipBuilder->FSpecArgs->Clear();
    ZipBuilder->ExtrOptions.Clear();
    ZipBuilder->ExtrOptions << ExtrTest;
    ZipBuilder->Extract();
    if(ZipBuilder->SuccessCnt != 1)
    { MessageDlg("Ошибка тестирования созданного архива. Операцию необходимо повторить!",mtError,TMsgDlgButtons() << mbOK,0);
      RichEdit1->Lines->Clear();
      ActionsJournalClear(id);
      return;
    }

    RichEdit1->Lines->Add("Архив базы данных создан и находится в файле - "+zip);
    RichEdit1->Repaint();

    WaitingGradient->Active=false;
    WaitingGradient->Visible=false;

    //Удаление BackUp файла
    if(FileExists(backup))
    { RichEdit1->SelAttributes->Color=clRed;
      RichEdit1->SelAttributes->Size=10;
      RichEdit1->Lines->Add("Удаление BackUp файла...");
      RichEdit1->Repaint();
      DeleteFile(backup);
      RichEdit1->SelAttributes->Color=clBlue;
      RichEdit1->SelAttributes->Size=10;
      if(!FileExists(backup))
        RichEdit1->Lines->Add("Файл удален!");
      else
        MessageDlg("Не могу удалить BackUp файл - "+backup,mtError,TMsgDlgButtons() << mbOK,0);
      RichEdit1->Lines->Add("\n");
    }
  }
  RichEdit1->SelAttributes->Color=clBlue;
  RichEdit1->SelAttributes->Size=10;
  RichEdit1->Lines->Add("Операция завершена!");
  RichEdit1->Repaint();

  RichEdit1->SelAttributes->Color=color;
  RichEdit1->SelAttributes->Size=size;
}
//---------------------------------------------------------------------------
void __fastcall TBackUpBaseForm::ActionsJournalClear(unsigned int id)
{
TpFIBQuery * TQ=SaleBookDM->TempQuery;
AnsiString str;

  TQ->Close();
  TQ->SQL->Clear();
  str="delete from ACTIONS_JOURNAL where ID="+IntToStr(id);
  TQ->SQL->Add(str);
  try
  {
    TQ->ExecQuery();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка delete from ACTIONC_JOURNAL where ID="+IntToStr(id)+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  }
  TQ->Close();
}
//---------------------------------------------------------------------------



