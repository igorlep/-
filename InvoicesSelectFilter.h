//---------------------------------------------------------------------------

#ifndef InvoicesSelectFilterH
#define InvoicesSelectFilterH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "JvComponent.hpp"
#include "JvExControls.hpp"
#include "JvXPButtons.hpp"
#include "JvXPCore.hpp"
#include "SmrtPanel.h"
#include "ToolEdit.hpp"
#include <ExtCtrls.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TInvoicesSelectFilterForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TJvXPButton *selectButton;
        TJvXPButton *cancelButton;
        TSmrtPanel *SmrtPanel1;
        TCheckBox *CustomerCheckBox;
        TCheckBox *UserCheckBox;
        TComboEdit *CustomerEdit;
        TComboEdit *UserEdit;
        TCheckBox *invoiceTypeCheckBox;
        TComboBox *invoiceTypeBox;
private:	// User declarations
public:		// User declarations
        __fastcall TInvoicesSelectFilterForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInvoicesSelectFilterForm *InvoicesSelectFilterForm;
//---------------------------------------------------------------------------
#endif
