//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "DataModule.h"
#include "SelectRecords.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Placemnt"
#pragma link "RXCtrls"
#pragma link "SmrtPanel"
#pragma link "ToolEdit"
#pragma link "FIBDatabase"
#pragma link "FIBDataSet"
#pragma link "pFIBDatabase"
#pragma link "pFIBDataSet"
#pragma link "JvComponent"
#pragma link "JvExControls"
#pragma link "JvXPButtons"
#pragma link "JvXPCore"
#pragma resource "*.dfm"
TSelectRecordsForm *SelectRecordsForm;
//---------------------------------------------------------------------------
__fastcall TSelectRecordsForm::TSelectRecordsForm(TComponent* Owner)
        : TForm(Owner)
{
  FormStorage1->IniFileName=MainForm->WorkDir+"SB_2009.ini";
  FormStorage1->IniSection="SelectRecordsForm";
  //Заполняем UserBox
  UsersID=new TStringList();
  UsersID->Clear();
  R_DS->Close();
  R_DS->SQLs->SelectSQL->Clear();
  AnsiString sql;
  sql="select ID, LOGIN from USERS";
  R_DS->SQLs->SelectSQL->Add(sql);
  try
  {
    R_DS->Open();
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  UserBox->Clear();
  R_DS->First();
  while(!R_DS->Eof)
  { UserBox->Items->Add(R_DS->FieldByName("LOGIN")->AsString);
    UsersID->Add(R_DS->FieldByName("ID")->AsString);
    R_DS->Next();
  }
  R_DS->Close();
  StringEdit->Text="";
}
//---------------------------------------------------------------------------
void __fastcall TSelectRecordsForm::FormDestroy(TObject *Sender)
{
  delete UsersID;
}
//---------------------------------------------------------------------------
void __fastcall TSelectRecordsForm::cancelButtonClick(TObject *Sender)
{
  Close();
  ModalResult=mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TSelectRecordsForm::selectButtonClick(TObject *Sender)
{
  Close();
  ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TSelectRecordsForm::Button1Click(TObject *Sender)
{
  UserBox->Text="";        
}
//---------------------------------------------------------------------------
void __fastcall TSelectRecordsForm::StrCheckBoxClick(TObject *Sender)
{
  if(StrCheckBox->Checked) StringEdit->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TSelectRecordsForm::CheckButtonClick(TObject *Sender)
{
  for(int i=0; i<ActionsBox->Items->Count; ++i)
    ActionsBox->Checked[i]=true;
}
//---------------------------------------------------------------------------
void __fastcall TSelectRecordsForm::UnCheckButtonClick(TObject *Sender)
{
  for(int i=0; i<ActionsBox->Items->Count; ++i)
    ActionsBox->Checked[i]=false;
}
//---------------------------------------------------------------------------



