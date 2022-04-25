//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DataModule.h"
#include "Main.h"
#include "ConstHistoryEdit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Placemnt"
#pragma link "FIBQuery"
#pragma link "pFIBQuery"
#pragma link "DBGridEh"
#pragma link "FIBDataSet"
#pragma link "pFIBDataSet"
#pragma link "FIBDatabase"
#pragma link "pFIBDatabase"
#pragma link "JvComponent"
#pragma link "JvExControls"
#pragma link "JvNavigationPane"
#pragma resource "*.dfm"
//TConstHistoryEditForm *ConstHistoryEditForm;
//---------------------------------------------------------------------------
__fastcall TConstHistoryEditForm::TConstHistoryEditForm(TComponent* Owner,int Org_ID,int Const_ID)
        : TForm(Owner), OrgID(Org_ID), ConstID(Const_ID)
{
  FormStorage1->IniFileName=MainForm->WorkDir+"SB_2009.ini";
  FormStorage1->IniSection="ConstHistoryEditForm";

  ConstQ->SQL->Clear();
  AnsiString sql="select * from CONSTANT where ID="+IntToStr(ConstID);
  ConstQ->SQL->Add(sql);
  try
  {
    ConstQ->ExecQuery();
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  formHeader->Caption=ConstQ->FieldByName("CONST_NAME")->AsString;

  ConstValDS->SQLs->SelectSQL->Clear();
  ConstValDS->SQLs->SelectSQL->Add("select * from CONST_VALUES where ORG_ID="+IntToStr(OrgID)+" and CONST_ID="+IntToStr(ConstID));
  try
  {
    ConstValDS->Open();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка ConstValDS->Open()\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  constType=ConstQ->FieldByName("CONST_TYPE")->AsInteger;
  if(constType==0) ConstValGrid->Columns->Items[0]->ButtonStyle=Dbgrids::cbsNone;
  else if(constType==1) ConstValGrid->Columns->Items[0]->ButtonStyle=Dbgrids::cbsEllipsis;
}
//---------------------------------------------------------------------------
void __fastcall TConstHistoryEditForm::FormDestroy(TObject *Sender)
{
  ConstQ->Close();
  ConstValDS->Close();
}
//---------------------------------------------------------------------------
void __fastcall TConstHistoryEditForm::ExitButtonClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TConstHistoryEditForm::ConstValSourceStateChange(
      TObject *Sender)
{
  if(ConstValDS->State==dsEdit || ConstValDS->State==dsInsert)
  { SaveButton->Enabled=true;
    CancelButton->Enabled=true;
  }
  else
  { SaveButton->Enabled=false;
    CancelButton->Enabled=false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TConstHistoryEditForm::AddButtonClick(TObject *Sender)
{

  if(ConstValDS->State==dsEdit || ConstValDS->State==dsInsert) ConstValDS->Post();
  ConstValDS->Append();
}
//---------------------------------------------------------------------------
void __fastcall TConstHistoryEditForm::SaveButtonClick(TObject *Sender)
{
  if(ConstValDS->State==dsEdit || ConstValDS->State==dsInsert) ConstValDS->Post();
}
//---------------------------------------------------------------------------
void __fastcall TConstHistoryEditForm::CancelButtonClick(TObject *Sender)
{
  if(ConstValDS->State==dsEdit || ConstValDS->State==dsInsert) ConstValDS->Cancel();
}
//---------------------------------------------------------------------------
void __fastcall TConstHistoryEditForm::DelButtonClick(TObject *Sender)
{
  if(MessageDlg("Вы уверены, что хотите удалить текущую запись?",mtConfirmation,TMsgDlgButtons() << mbOK << mbCancel,0)==mrOk)
    ConstValDS->Delete();
}
//---------------------------------------------------------------------------
void __fastcall TConstHistoryEditForm::ConstValDSBeforePost(
      TDataSet *DataSet)
{
  ConstValDS->FieldByRelName("ORG_ID")->AsInteger=OrgID;
  ConstValDS->FieldByRelName("Const_ID")->AsInteger=ConstID;
}
//---------------------------------------------------------------------------

