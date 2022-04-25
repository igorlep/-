//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DataModule.h"
#include "HelpAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//THelpAboutForm *HelpAboutForm;
//---------------------------------------------------------------------------
__fastcall THelpAboutForm::THelpAboutForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall THelpAboutForm::Timer1Timer(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall THelpAboutForm::OkButtonClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

