//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "InvoicesJournal.h"
#include "InvoicesSelectFilter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "JvComponent"
#pragma link "JvExControls"
#pragma link "JvXPButtons"
#pragma link "JvXPCore"
#pragma link "SmrtPanel"
#pragma link "ToolEdit"
#pragma resource "*.dfm"
TInvoicesSelectFilterForm *InvoicesSelectFilterForm;
//---------------------------------------------------------------------------
__fastcall TInvoicesSelectFilterForm::TInvoicesSelectFilterForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
