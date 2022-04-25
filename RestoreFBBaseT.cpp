//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RestoreFBBaseT.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall RestoreFBBaseThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
__fastcall RestoreFBBaseThread::RestoreFBBaseThread(bool CreateSuspended,\
AnsiString serverName,bool VerboseFLG,AnsiString baseName,AnsiString backupFileName,\
TRichEdit *richEdit,TJvProgressBar *progressBar)
        : TThread(CreateSuspended),RichEdit(richEdit),ProgressBar(progressBar),verboseFLG(VerboseFLG)
{
  try
  {
    RestoreService=new TIBRestoreService(NULL);
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка создания объекта RestoreService\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    RestoreService=NULL;
    return;
  }
  //Инициируем сервис
  RestoreService->ServerName=serverName;
  RestoreService->LoginPrompt=false;
  RestoreService->Params->Clear();
  RestoreService->Params->Add("user_name=SYSDBA");
  RestoreService->Params->Add("password=masterkey");
  RestoreService->Protocol=TCP;
  RestoreService->Active=true;
  RestoreService->Verbose=true;
  RestoreService->Options.Clear();
  RestoreService->Options << CreateNewDB;
  RestoreService->PageSize=8192;
  RestoreService->BufferSize=32000;
  RestoreService->DatabaseName->Clear();
  RestoreService->DatabaseName->Add(baseName);
  RestoreService->BackupFile->Clear();
  RestoreService->BackupFile->Add(backupFileName);
}
//---------------------------------------------------------------------------
void __fastcall RestoreFBBaseThread::Execute()
{
  ProgressBar->Position=0;
  ProgressBar->Update();
  calc=1;
  RestoreService->ServiceStart();
  while(!RestoreService->Eof)
  { ProgressBar->StepIt();
    ProgressBar->Update();
    AnsiString Text=RestoreService->GetNextLine();
    if(verboseFLG==true)
    { RichEdit->Lines->Add(Text);
      RichEdit->Repaint();
      RichEdit->SetFocus();
      RichEdit->SelStart=RichEdit->Text.Length();
      RichEdit->SelLength=0;
    }
  }
}
//---------------------------------------------------------------------------
__fastcall RestoreFBBaseThread::~RestoreFBBaseThread(void)
{
  if(RestoreService!=NULL)
  { RestoreService->Active = false;
    delete RestoreService;
  }
}
//---------------------------------------------------------------------------
void __fastcall RestoreFBBaseThread::UpdateCaption()
{
AnsiString Text=RestoreService->GetNextLine();

  if(RestoreService->Verbose==false)
  { Text="Прогресс индикатор - "+IntToStr(calc);
    RichEdit->Lines->Delete(RichEdit->Lines->Count-1);
    calc++;
  }
  RichEdit->Lines->Add(Text);
  RichEdit->Repaint();
  RichEdit->SetFocus();
  RichEdit->SelStart=RichEdit->Text.Length();
  RichEdit->SelLength=0;
}
//---------------------------------------------------------------------------

