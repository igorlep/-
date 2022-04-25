//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SMTPMessage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SmrtPanel"
#pragma resource "*.dfm"
TSMTPMessageForm *SMTPMessageForm;
//---------------------------------------------------------------------------
__fastcall TSMTPMessageForm::TSMTPMessageForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
