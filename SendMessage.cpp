//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SendMessage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FIBDatabase"
#pragma link "FIBQuery"
#pragma link "pFIBDatabase"
#pragma link "pFIBQuery"
#pragma link "FIBDataSet"
#pragma link "pFIBDataSet"
#pragma resource "*.dfm"
TSendMessForm *SendMessForm;
//---------------------------------------------------------------------------
__fastcall TSendMessForm::TSendMessForm(TComponent* Owner,TDataSet *DS)
        : TForm(Owner)
{
UMDataSet=((TpFIBDataSet*)(DS));
}
//---------------------------------------------------------------------------
void __fastcall TSendMessForm::SaveButtonClick(TObject *Sender)
{
AnsiString sql;
// отправка сообщения пользователю
  if(OldPassword->Text.IsEmpty())
  {
    MessageDlg("Введите отправляемое сообщение !!!",mtError,TMsgDlgButtons() << mbOK,0);
    OldPassword->SetFocus();
    return;
  }

  if (!CheckBox1->Checked)
  {
  Q->Close();
  Q->SQL->Clear();
  sql="insert into SENDED_MESSAGES_TABLE (U_ID,MES_DATA) values("+IntToStr(UMDataSet->FieldByName("USER_ID")->AsInteger)+",'"+OldPassword->Text.Trim()+"')";
  Q->SQL->Add(sql);
  try
  {
   Q->ExecQuery();
  }
  catch(const Exception &exc)
  {
   MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
   return;
  }
  }
  else
  {
   if(UMDataSet->RecordCount > 0)
   {
   T->StartTransaction();
   UMDataSet->First();
   while(!UMDataSet->Eof)
   {
     Q->Close();
     Q->SQL->Clear();
     sql="insert into SENDED_MESSAGES_TABLE (U_ID,MES_DATA) values("+IntToStr(UMDataSet->FieldByName("USER_ID")->AsInteger)+",'"+OldPassword->Text.Trim()+"')";
     Q->SQL->Add(sql);
     try
     {
     Q->ExecQuery();
     }
     catch(const Exception &exc)
    {
      MessageDlg("Ошибка Q (insert...)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      T->Rollback();
      return;
    }
    UMDataSet->Next();
    T->Commit();
   }
   UMDataSet->First();
   }
  }
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TSendMessForm::CancelButtonClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
