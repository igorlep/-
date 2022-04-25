//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "AccauntsJournal.h"
#include "DataModule.h"
#include "InsertAccount.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Placemnt"
#pragma link "RXSpin"
#pragma link "SmrtPanel"
#pragma resource "*.dfm"
TInsertAccountForm *InsertAccountForm;
//---------------------------------------------------------------------------
__fastcall TInsertAccountForm::TInsertAccountForm(TComponent* Owner)
        : TForm(Owner)
{
  FormStorage1->IniFileName=MainForm->WorkDir+"SaleBook.ini";
  FormStorage1->IniSection="InsertAccountsForm";
}
//---------------------------------------------------------------------------
void __fastcall TInsertAccountForm::BitBtn1Click(TObject *Sender)
{
  if(ListBox->ItemIndex < 0)
  { MessageDlg("”кажите строку с нужным номером",mtInformation,TMsgDlgButtons() << mbOK,0);
    return;
  }

  AnsiString s=ListBox->Items->Strings[ListBox->ItemIndex];
  if(s.Pos("є")==3)
  { try
    { CountNumber=StrToInt(s.SubString(4,4));
      CountDate=StrToDateTime(s.SubString(12,10));
      Close();
      ModalResult=mrOk;
    }
    catch(const Exception &exc)
    {
      MessageDlg("ќшибка\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TInsertAccountForm::BitBtn2Click(TObject *Sender)
{
  Close();
  ModalResult=mrCancel;
}
//---------------------------------------------------------------------------

