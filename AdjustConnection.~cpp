//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AdjustConnection.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Placemnt"
#pragma link "Placemnt"
#pragma link "SmrtPanel"
#pragma link "SmrtPanel"
#pragma link "SmrtPanel"
#pragma resource "*.dfm"
TAdjustConnectionForm *AdjustConnectionForm;
//---------------------------------------------------------------------------
__fastcall TAdjustConnectionForm::TAdjustConnectionForm(TComponent* Owner)
        : TForm(Owner)
{
  FormStorage1->IniFileName=WorkDir+"SB_2009.ini";
  FormStorage1->IniSection="AdjustConnectionForm";

  if(FileExists(WorkDir+"Edit1.ini")) Edit1->Items->LoadFromFile(WorkDir+"Edit1.ini");
  if(FileExists(WorkDir+"Edit2.ini")) Edit2->Items->LoadFromFile(WorkDir+"Edit2.ini");
  if(RadioButton1->Checked)
  { Edit1->Text="LOCALHOST";
    Edit1->Enabled=false;
    ComboBox1->Enabled=false;
    Button3->Enabled=true;
  }
  else
  { Edit1->Enabled=true;
    ComboBox1->Enabled=true;
    Button3->Enabled=false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TAdjustConnectionForm::FormShow(TObject *Sender)
{
  Edit3->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TAdjustConnectionForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Edit1->Items->SaveToFile(WorkDir+"Edit1.ini");
  Edit2->Items->SaveToFile(WorkDir+"Edit2.ini");
  Action=caFree;
}
//---------------------------------------------------------------------------
void __fastcall TAdjustConnectionForm::RadioButton1Click(TObject *Sender)
{
  if(RadioButton1->Checked)
  { Edit1->Text="127.0.0.1";
    Edit1->Enabled=false;
    ComboBox1->Enabled=false;
    Button3->Enabled=true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TAdjustConnectionForm::RadioButton2Click(TObject *Sender)
{
  if(RadioButton2->Checked)
  { Edit1->Enabled=true;
    Edit1->Text="";
    ComboBox1->Enabled=true;
    Button3->Enabled=false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TAdjustConnectionForm::Button3Click(TObject *Sender)
{
  OpenDialog1->InitialDir=Edit1->Text;
  if(OpenDialog1->Execute())
    Edit2->Text=OpenDialog1->FileName;
}
//---------------------------------------------------------------------------
void __fastcall TAdjustConnectionForm::ConnectButtonClick(TObject *Sender)
{
  if(Edit3->Text.IsEmpty())
  { MessageDlg("Поле \"Псевдоним\" должно быть заполнено",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(Edit4->Text.IsEmpty())
  { MessageDlg("Поле \"Имя пользователя\" должно быть заполнено",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(Edit5->Text.IsEmpty())
  { MessageDlg("Поле \"Пароль пользователя\" должно быть заполнено",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(Edit1->Items->Text.Pos(Edit1->Text)==0) Edit1->Items->Add(Edit1->Text);
  if(Edit2->Items->Text.Pos(Edit2->Text)==0) Edit2->Items->Add(Edit2->Text);
  Close();
  ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TAdjustConnectionForm::CancelButtonClick(TObject *Sender)
{
  Close();
  ModalResult=mrCancel;
}
//---------------------------------------------------------------------------

