//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "MoveRecords.h"
#include "DataModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SmrtPanel"
#pragma link "Placemnt"
#pragma link "DBGridEh"
#pragma link "pFIBDatabase"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TMoveRecordsForm::TMoveRecordsForm(TComponent* Owner)
        : TForm(Owner)
{
  FormStorage1->IniFileName=MainForm->WorkDir+"SB_2009.ini";
  FormStorage1->IniSection="MoveRecordsForm";
  IDMove=0;
  CopyFLG=false;
  DS=SaleBookDM->EIDS;
  DataSource->DataSet=DS;
  recno=0;
}
//Консруктор формы
__fastcall TMoveRecordsForm::TMoveRecordsForm(TComponent* Owner,TDataSet *DtS,int cp)
        : TForm(Owner)
{
  FormStorage1->IniFileName=MainForm->WorkDir+"SB_2009.ini";
  FormStorage1->IniSection="MoveRecordsForm";
  IDMove=0;
  CopyFLG=false;

  DS=(TpFIBDataSet*)DtS;
  DataSource->DataSet=DS;
  recno=0;
  kod=cp;
}
//---------------------------------------------------------------------------
void __fastcall TMoveRecordsForm::LoadDataSet()
{
AnsiString sql;
TpFIBDataSet *rDS=SaleBookDM->RDS;
AnsiString Value[50];
AnsiString IndVyb="";
int k=0;


  rDS->Close();
  rDS->SQLs->SelectSQL->Clear();
  sql="select distinct  CODP as COD from NOMENCLATURE where REC_TYPE=1 and INDEXOPS=0";
  rDS->SQLs->SelectSQL->Add(sql);
  try
  {
    rDS->Open();
  }
  catch (Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  rDS->First();
  while(!rDS->Eof)
  {
    AnsiString sdName=IntToStr(rDS->FieldByName("COD")->AsInteger);
    Value[k]=sdName;
    k++;
    rDS->Next();
  }
  rDS->Close();

if (k==0)
{
    MessageDlg("Нет ни одной кассы !!! Неверная настройка ИС !!!",mtWarning,TMsgDlgButtons() << mbOK,0);
}else
{

if (k==1)
{
IndVyb=Value[0].Trim();
}else
{
for (int i=0;i<k;i++)
{
if(i==k-1)
{
IndVyb=IndVyb+Value[i].Trim();
break;
}
IndVyb=IndVyb+Value[i].Trim()+",";
}
}
}



  if(DS->Active==true) DS->Close();
  DS->SQLs->SelectSQL->Clear();

      TempQ->Close();
      TempQ->SQL->Clear();
      sql="select INDEXOPS as INDOPS from NOMENCLATURE where CODP="+IntToStr(kod);
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }


if (!TempQ->FieldByName("INDOPS")->IsNull)
{
      if (TempQ->FieldByName("INDOPS")->AsInteger > 0)
      {
      if (k==0) sql="select ID,DESCRIPTION from EI where ID <>"+ IntToStr(kod); else sql="select ID,DESCRIPTION from EI where ID NOT IN (" +IndVyb.Trim()+","+IntToStr(kod)+")";
      }
      else
      {
      if (k==0) sql="select ID,DESCRIPTION from EI where ID <>"+ IntToStr(kod); else sql="select ID,DESCRIPTION from EI where ID IN (" +IndVyb.Trim()+") AND ID <>"+IntToStr(kod);
      }
      sql+="order by DESCRIPTION";
}
else
{
MessageDlg("Данный почтальон НЕ РАБОТАЕТ !!! Аварийный выход из процедуры!!! ",mtError,TMsgDlgButtons() << mbOK,0);
return;
}


  DS->SQLs->SelectSQL->Add(sql);

  try
  {
    DS->Open();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка открытия DataSet (Поставщики доставщики)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  DS->First();
}

void __fastcall TMoveRecordsForm::RichEdit1ResizeRequest(
      TObject *Sender, TRect &Rect)
{
  RichEdit1->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TMoveRecordsForm::SaveButtonClick(TObject *Sender)
{
  IDMove=DS->FieldByName("ID")->AsInteger;
  CopyFLG=false;
  Close();
  ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TMoveRecordsForm::CancelButtonClick(TObject *Sender)
{
  Close();
  ModalResult=mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TMoveRecordsForm::CopyButtonClick(TObject *Sender)
{
  CopyFLG=true;
  Close();
  ModalResult=mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TMoveRecordsForm::FormShow(TObject *Sender)
{
  LoadDataSet();
  Visible=true;
  if (EIGrid->DataSource->DataSet->RecordCount > 0)
  {
  EIGrid->Visible=true;
  EIGrid->SetFocus();
  }
  else
  {
  EIGrid->Visible=false;
  }
}
//---------------------------------------------------------------------------

