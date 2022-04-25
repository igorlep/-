//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "DataModule.h"
#include "SelectPeriodBF.h"
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
TSelectPeriodBrowseForm *SelectPeriodBrowseForm;
//---------------------------------------------------------------------------
__fastcall TSelectPeriodBrowseForm::TSelectPeriodBrowseForm(TComponent* Owner, int dt1, int dt2)
        : TForm(Owner)
{
  iniFileName=MainForm->getIniFileName();
  FormStorage->IniFileName=iniFileName;
  FormStorage->IniSection="SelectPeriodBrowseForm";
}
//---------------------------------------------------------------------------
void __fastcall TSelectPeriodBrowseForm::JXPBOKClick(TObject *Sender)
{

  date1=StrToInt(D1->Text);
  date2=StrToInt(D2->Text);
  Close();
  ModalResult=mrOk;
}
//---------------------------------------------------------------------------
int __fastcall TSelectPeriodBrowseForm::getDate1(void)
{
  return date1;
}
//---------------------------------------------------------------------------
int __fastcall TSelectPeriodBrowseForm::getDate2(void)
{
  return date2;
}
//---------------------------------------------------------------------------


void __fastcall TSelectPeriodBrowseForm::JvXPButton1Click(TObject *Sender)
{
Close();
ModalResult=mrCancel;
}
//---------------------------------------------------------------------------

