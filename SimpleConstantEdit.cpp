//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DataModule.h"
#include "SimpleConstantEdit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "JvComponent"
#pragma link "JvExControls"
#pragma link "JvXPButtons"
#pragma link "JvXPCore"
#pragma link "JvExMask"
#pragma link "JvToolEdit"
#pragma link "Placemnt"
#pragma link "RXSpin"
#pragma link "SmrtPanel"
#pragma resource "*.dfm"
//TSimpleConstantEditForm *SimpleConstantEditForm;
//---------------------------------------------------------------------------
__fastcall TSimpleConstantEditForm::TSimpleConstantEditForm(TComponent* Owner,AnsiString iniFN,int org_id,AnsiString Identifier)
        : TForm(Owner),iniFileName(iniFN),orgID(org_id),identifier(Identifier)
{
  FormStorage->IniFileName=iniFileName;
  FormStorage->IniSection="SimpleConstantEditForm";

  Year->Height=21;

  unsigned short y,m,d;
  StrToDateTime(SaleBookDM->GetConstValue(orgID,identifier)).DecodeDate(&y,&m,&d);
  Year->Value=y;
  Month->ItemIndex=m-1;
  MonthUpDown->Position=m;
}
//---------------------------------------------------------------------------
void __fastcall TSimpleConstantEditForm::CancelButtonClick(TObject *Sender)
{
  Close();
  ModalResult=mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TSimpleConstantEditForm::SaveButtonClick(TObject *Sender)
{
//TDateTime dt=TDateTime((unsigned short)Year->Value,MonthUpDown->Position,SaleBookDM->LastDay((unsigned short)Year->Value,MonthUpDown->Position));
TDateTime dt=TDateTime((unsigned short)Year->Value,MonthUpDown->Position,23);

  SaleBookDM->SetConstValue(orgID,identifier,dt.DateString());
  Close();
  ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TSimpleConstantEditForm::FormResize(TObject *Sender)
{
  Year->Height=21;
}
//---------------------------------------------------------------------------
void __fastcall TSimpleConstantEditForm::MonthUpDownClick(TObject *Sender,
      TUDBtnType Button)
{
  if(MonthUpDown->Position > 12 && Button==btNext)
  { MonthUpDown->Position=1;
    Month->ItemIndex=0;
    Year->Value++;
  }
  else if(MonthUpDown->Position < 1 && Button==btPrev)
  { MonthUpDown->Position=12;
    Month->ItemIndex=11;
    Year->Value--;
  }
  else Month->ItemIndex=MonthUpDown->Position-1;
}
//---------------------------------------------------------------------------
void __fastcall TSimpleConstantEditForm::MonthChange(TObject *Sender)
{
  MonthUpDown->Position=Month->ItemIndex+1;
}
//---------------------------------------------------------------------------

