//---------------------------------------------------------------------------

#ifndef SimpleConstantEditH
#define SimpleConstantEditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "JvComponent.hpp"
#include "JvExControls.hpp"
#include "JvXPButtons.hpp"
#include "JvXPCore.hpp"
#include <ExtCtrls.hpp>
#include "JvExMask.hpp"
#include "JvToolEdit.hpp"
#include <Mask.hpp>
#include "Placemnt.hpp"
#include "RXSpin.hpp"
#include <ComCtrls.hpp>
#include "SmrtPanel.h"
//---------------------------------------------------------------------------
class TSimpleConstantEditForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *buttonPanel;
        TJvXPButton *SaveButton;
        TJvXPButton *CancelButton;
        TFormStorage *FormStorage;
        TSmrtPanel *workPanel;
        TLabel *Label;
        TComboBox *Month;
        TUpDown *MonthUpDown;
        TRxSpinEdit *Year;
        TLabel *Label1;
        void __fastcall CancelButtonClick(TObject *Sender);
        void __fastcall SaveButtonClick(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall MonthUpDownClick(TObject *Sender,
          TUDBtnType Button);
        void __fastcall MonthChange(TObject *Sender);
private:	// User declarations
  AnsiString iniFileName;
  int orgID;
  AnsiString identifier;
public:		// User declarations
        __fastcall TSimpleConstantEditForm(TComponent* Owner,AnsiString iniFN,int org_id,AnsiString Identifier);
};
//---------------------------------------------------------------------------
//extern PACKAGE TSimpleConstantEditForm *SimpleConstantEditForm;
//---------------------------------------------------------------------------
#endif
