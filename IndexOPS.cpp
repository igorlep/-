//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "IndexOPS.h"
#include "DataModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzRadGrp"
#pragma link "SmrtPanel"
#pragma resource "*.dfm"
TFormIndex *FormIndex;
//---------------------------------------------------------------------------
__fastcall TFormIndex::TFormIndex(TComponent* Owner)
        : TForm(Owner)
{
AnsiString sql;
TpFIBDataSet *rDS=SaleBookDM->RDS;

  rDS->Close();
  rDS->SQLs->SelectSQL->Clear();
  sql="select distinct DESCRIPTION as SD_NAME from NOMENCLATURE where REC_TYPE=0 and FILE_ID >0 and DESCRIPTION <>'Кассы'";
  rDS->SQLs->SelectSQL->Add(sql);
  try
  {
    rDS->Open();
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  CheckGroup->Items->Clear();
  rDS->First();
  while(!rDS->Eof)
  {
    AnsiString sdName=rDS->FieldByName("SD_NAME")->AsString;
    CheckGroup->Items->Add(sdName);
    rDS->Next();
  }
  rDS->Close();

int cls=CheckGroup->Items->Count;

for (int i=0;i<cls;i++)
{
CheckGroup->ItemChecked[i]=false;
}

}
//---------------------------------------------------------------------------
void __fastcall TFormIndex::SaveButtonClick(TObject *Sender)
{
int k=0;
AnsiString Value[50];
AnsiString IndVyb="";
AnsiString iops="";
int ops=0;



for (int i=0;i<50;i++)
{
Value[i]="";
}

int cl=CheckGroup->Items->Count;

for (int i=0;i<cl;i++)
{
if (CheckGroup->ItemChecked[i])
{
Value[k]=CheckGroup->Items->Strings[i];
k++;
}
}

if (k==0)
{
    MessageDlg("Выберите хотя бы один нужный Вам ОПС из списка !!! ",mtWarning,TMsgDlgButtons() << mbOK,0);
    CheckGroup->SetFocus();
    return;
}else
{

if (k==1)
{
IndVyb=Value[0].Trim();
iops=Value[0].SubString(4,255);
ops = StrToInt(iops);
ListOPS=IntToStr(ops);
}else
{
for (int i=0;i<k;i++)
{
if(i==k-1)
{
IndVyb=IndVyb+Value[i].Trim();
iops=Value[i].SubString(4,255);
ops = StrToInt(iops);
ListOPS=ListOPS+IntToStr(ops);
break;
}
IndVyb=IndVyb+Value[i].Trim()+",";
iops=Value[i].SubString(4,255);
ops = StrToInt(iops);
ListOPS=ListOPS+IntToStr(ops)+",";
}
}
}
  Close();
  ModalResult=mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TFormIndex::CancelButtonClick(TObject *Sender)
{
  Close();
  ModalResult=mrCancel;
}
//---------------------------------------------------------------------------

