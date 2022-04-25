//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "EI.h"
#include "DataModule.h"
#include "Main.h"
#include "EditNomenclature.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SmrtPanel"
#pragma link "DBCtrlsEh"
#pragma link "Placemnt"
#pragma link "FIBDatabase"
#pragma link "FIBDataSet"
#pragma link "pFIBDatabase"
#pragma link "pFIBDataSet"
#pragma resource "*.dfm"
TEditNomenclatuteForm *EditNomenclatuteForm;
//---------------------------------------------------------------------------
__fastcall TEditNomenclatuteForm::TEditNomenclatuteForm(TComponent* Owner, unsigned int n_id)
        : TForm(Owner)
{
  FormStorage1->IniFileName=MainForm->WorkDir+"SB_2009.ini";
  FormStorage1->IniSection="EditNomenclatuteForm";

  N_ID=n_id;
  EditTransaction->StartTransaction();
  DS->SQLs->SelectSQL->Clear();
  AnsiString sql="select * from NOMENCLATURE where ID="+IntToStr(N_ID);
  DS->SQLs->SelectSQL->Add(sql);
  try
  {
    DS->Open();
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка "+DS->SQLs->SelectSQL->Text+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  DS->First();
  DS->Edit();
}
//---------------------------------------------------------------------------
void __fastcall TEditNomenclatuteForm::DBEditEh1EditButtons0Click(
      TObject *Sender, bool &Handled)
{
TEIForm *EIF=NULL;

  try
  {
    EIF=new TEIForm(this,SaleBookDM->EIDS);
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка создания формы для редактирования записи\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(EIF->ShowModal()==mrOk)
  {
    EIEdit->Text=SaleBookDM->EIDS->FieldByRelName("DESCRIPTION")->AsString;
    CODPEdit->Text=SaleBookDM->EIDS->FieldByRelName("ID")->AsString;
  }
  if(EIF!=NULL){ delete EIF; EIF=NULL;}
}
//---------------------------------------------------------------------------
void __fastcall TEditNomenclatuteForm::FormShow(TObject *Sender)
{
  NameEdit->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TEditNomenclatuteForm::IDEditKeyPress(TObject *Sender,
      char &Key)
{
  if(Key==VK_RETURN) NameEdit->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TEditNomenclatuteForm::NameEditKeyPress(TObject *Sender,
      char &Key)
{
  if(Key==VK_RETURN) EIEdit->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TEditNomenclatuteForm::SaveButtonClick(TObject *Sender)
{
AnsiString sql="";
  try
  {
    int codp_new=DS->FieldByName("CODP")->AsInteger;
    int index_ops = DS->FieldByName("INDEXOPS")->AsInteger;
    DS->Post();
    EditTransaction->Commit();
    if (codp_new != codp_old)
    {
       SaleBookDM->TempQuery->Close();
       SaleBookDM->TempQuery->SQL->Clear();
       sql="update NDOST set CHEL = " + IntToStr(codp_new) + " where CHEL = " +IntToStr(codp_old) + " and METKA1=" + IntToStr(index_ops);
       SaleBookDM->TempQuery->SQL->Add(sql);
       try
       {
       SaleBookDM->TempQuery->ExecQuery();
       }
       catch(const Exception &exc)
       {
       MessageDlg("Ошибка обновления записи\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
       SaleBookDM->TempQuery->Close();
       return;
       }
      SaleBookDM->TempQuery->Close();
    }
  }
  catch (Exception &exc)
  { DS->Cancel();
    MessageDlg("Ошибка сохранения данных\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  }
  Close();
  ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TEditNomenclatuteForm::CancelButtonClick(TObject *Sender)
{
  Close();
  ModalResult=mrCancel;
}
//---------------------------------------------------------------------------






void __fastcall TEditNomenclatuteForm::DSBeforeEdit(TDataSet *DataSet)
{
codp_old=DS->FieldByName("CODP")->AsInteger;
}
//---------------------------------------------------------------------------

