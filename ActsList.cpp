//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ActsList.h"
#include "BrowseF.h"
#include "DataModule.h"
#include "Main.h"
#include "utils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Placemnt"
#pragma link "DBGridEh"
#pragma link "FIBDatabase"
#pragma link "FIBDataSet"
#pragma link "pFIBDatabase"
#pragma link "pFIBDataSet"
#pragma link "FIBQuery"
#pragma link "pFIBQuery"
#pragma resource "*.dfm"
TActsListForm *ActsListForm;
//---------------------------------------------------------------------------
__fastcall TActsListForm::TActsListForm(TComponent* Owner)
        : TForm(Owner)
{
AnsiString sql="";

  iniFileName=MainForm->getIniFileName();
  FormStorage->IniFileName=iniFileName;
  FormStorage->IniSection="ActsListForm";
  ADS->Close();
  ADS->SQLs->SelectSQL->Clear();
  sql="SELECT d.* FROM DOV d ";
  if(SaleBookDM->UserRole=="Администратор" || SaleBookDM->UserRole=="Руководитель" || SaleBookDM->UserRole=="Кассир")
  {
  }
  else
  {
  sql+=" where d.USER_ID = "+IntToStr(SaleBookDM->UserID);
  }
  sql+=" ORDER BY d.FAMILY,d.NAME,d.FATHER";
  ADS->SQLs->SelectSQL->Add(sql);
  try
  {
    ADS->Active=true;
  }
  catch (Exception &exc)
  {
    MessageDlg("Ошибка открытия таблицы DOV",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  ADS->First();
}
//---------------------------------------------------------------------------
void __fastcall TActsListForm::ExitButtonClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TActsListForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  ADS->Active=false;
  Action=caFree;
}
//---------------------------------------------------------------------------
void __fastcall TActsListForm::FormShow(TObject *Sender)
{

  if(SaleBookDM->UserRole=="Администратор" || SaleBookDM->UserRole=="Руководитель" || SaleBookDM->UserRole=="Кассир")
  {
  DelButton->Enabled = false;
  SaveButton->Enabled = false;
  }
  else
  {
  if (ADS->RecordCount > 0) DelButton->Enabled = true; else DelButton->Enabled = false;
  SaveButton->Enabled = true;
  }

  Grid->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TActsListForm::SaveButtonClick(TObject *Sender)
{
  if(!Application->FindComponent("BrowseForm"))
  { try
    {
      Application->CreateForm(__classid(TBrowseForm), &BrowseForm);
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка создания формы BrowseForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
  }
  BrowseForm->flag=2;
  BrowseForm->Show();
}
//---------------------------------------------------------------------------
//Удаление акта
void __fastcall TActsListForm::DelButtonClick(TObject *Sender)
{
  if(MessageDlg("Вы уверены, что хотите удалить текущую запись о востребования? ",mtConfirmation,TMsgDlgButtons() << mbOK << mbCancel,0)==mrOk)
  {
    ADS->Delete();
    updateset();
  }
}
//---------------------------------------------------------------------------

void __fastcall TActsListForm::GridCellClick(TColumnEh *Column)
{
  if(SaleBookDM->UserRole=="Администратор" || SaleBookDM->UserRole=="Руководитель" || SaleBookDM->UserRole=="Кассир")
  {
  DelButton->Enabled = false;
  SaveButton->Enabled = false;
  }
  else
  {
  if (ADS->RecordCount > 0) DelButton->Enabled = true; else DelButton->Enabled = false;
  SaveButton->Enabled = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TActsListForm::updateset(void)
{
AnsiString sql;

  ADS=((TpFIBDataSet*)(Grid->DataSource->DataSet));
  ADS->Close();
  ADS->SQLs->SelectSQL->Clear();
  sql="SELECT d.* FROM DOV d ";
  if(SaleBookDM->UserRole=="Администратор" || SaleBookDM->UserRole=="Руководитель" || SaleBookDM->UserRole=="Кассир")
  {
  }
  else
  {
  sql+=" where d.USER_ID = "+IntToStr(SaleBookDM->UserID);
  }
  sql+=" ORDER BY d.FAMILY,d.NAME,d.FATHER";
  ADS->SQLs->SelectSQL->Add(sql);
  try
  {
    ADS->Open();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка открытия таблицы ADS\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(ADS->RecordCount>0) ADS->First();
}

void __fastcall TActsListForm::FormActivate(TObject *Sender)
{
updateset();
}
//---------------------------------------------------------------------------


void __fastcall TActsListForm::Edit1Change(TObject *Sender)
{
  if(searchTimer->Enabled==true) searchTimer->Enabled=false;
  searchTimer->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TActsListForm::Edit1KeyPress(TObject *Sender, char &Key)
{
  if(Key==VK_RETURN || Key==VK_DOWN || Key==VK_UP)
  {
    Key=0;
    Grid->SetFocus();
  }
  else if(Key == VK_ESCAPE){ Key=0; Edit1->Text=""; }

}
//---------------------------------------------------------------------------

void __fastcall TActsListForm::searchTimerTimer(TObject *Sender)
{
TLocateOptions opt;
opt<<loPartialKey<<loCaseInsensitive;
AnsiString d=0;
int test=0;

  searchTimer->Enabled=false;
  if(Edit1->Text.IsEmpty()) return;
  if(Edit1->Text.Length() <= 6 && IsNum(Edit1->Text.Trim())){
  d=Edit1->Text.Trim();
  ADS->Locate("LCHET",d,opt);
  Edit1->Text="";
  }else
  {
  d=Edit1->Text.Trim();
  ADS->Locate("FAMILY",d,opt);
  Edit1->Text="";
  }
}
//---------------------------------------------------------------------------

