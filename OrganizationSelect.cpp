//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//#include "DataModule.h"
#include "Main.h"
#include "OrganizationSelect.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "Placemnt"
#pragma link "FIBDatabase"
#pragma link "FIBDataSet"
#pragma link "pFIBDatabase"
#pragma link "pFIBDataSet"
#pragma resource "*.dfm"
//TOrganizationSelectForm *OrganizationSelectForm;
//---------------------------------------------------------------------------
__fastcall TOrganizationSelectForm::TOrganizationSelectForm(TComponent* Owner, unsigned int id)
        : TForm(Owner)
{
  FormStorage1->IniFileName=MainForm->WorkDir+"SB_2009.ini";
  FormStorage1->IniSection="OrganizationSelectForm";
  try
  {
    OrgDS->Open();
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка открытия OrgDS\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }

  TLocateOptions opt; opt.Clear();
  OrganizationsGrid->DataSource->DataSet->Locate("ID",id,opt);
}
//---------------------------------------------------------------------------
void __fastcall TOrganizationSelectForm::FormShow(TObject *Sender)
{
  OrganizationsGrid->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TOrganizationSelectForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Action=caFree;
}
//---------------------------------------------------------------------------
void __fastcall TOrganizationSelectForm::SelectButtonClick(
      TObject *Sender)
{
  Close();
  ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TOrganizationSelectForm::CancelButtonClick(TObject *Sender)
{
  Close();
  ModalResult=mrCancel;
}
//---------------------------------------------------------------------------

