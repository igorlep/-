//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RefSort.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TRefSortForm::TRefSortForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TRefSortForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Action=caFree;
}
//---------------------------------------------------------------------------
int __fastcall TRefSortForm::ShowForm(short ts, short l, short t)
{
  if(ts==1) RadioButton1->Checked=true;
  else RadioButton2->Checked=true;
  Left=l+40; Top=t+80;
  return ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TRefSortForm::SelectButtonClick(TObject *Sender)
{
  Close();
  ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TRefSortForm::CancelButtonClick(TObject *Sender)
{
  Close();
  ModalResult=mrCancel;
}
//---------------------------------------------------------------------------

