//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "DataModule.h"
#include "SelectPeriod.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Placemnt"
#pragma link "SmrtPanel"
#pragma link "ToolEdit"
#pragma link "CSPIN"
#pragma link "JvComponent"
#pragma link "JvExControls"
#pragma link "JvXPButtons"
#pragma link "JvXPCore"
#pragma link "JvComponent"
#pragma link "JvExControls"
#pragma link "JvXPButtons"
#pragma link "JvXPCore"
#pragma resource "*.dfm"
TSelectPeriodForm *SelectPeriodForm;
//---------------------------------------------------------------------------
__fastcall TSelectPeriodForm::TSelectPeriodForm(TComponent* Owner, int dt1, int dt2)
        : TForm(Owner)
{
  iniFileName=MainForm->getIniFileName();
  FormStorage->IniFileName=iniFileName;
  FormStorage->IniSection="SelectPeriodForm";
}
//---------------------------------------------------------------------------
void __fastcall TSelectPeriodForm::JXPBOKClick(TObject *Sender)
{

  date1=StrToInt(D1->Text);
  date2=StrToInt(D2->Text);
  Close();
  ModalResult=mrOk;
}
//---------------------------------------------------------------------------
int __fastcall TSelectPeriodForm::getDate1(void)
{
  return date1;
}
//---------------------------------------------------------------------------
int __fastcall TSelectPeriodForm::getDate2(void)
{
  return date2;
}
//---------------------------------------------------------------------------


void __fastcall TSelectPeriodForm::JvXPButton1Click(TObject *Sender)
{
Close();
ModalResult=mrCancel;
}
//---------------------------------------------------------------------------

