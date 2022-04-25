//---------------------------------------------------------------------------

#ifndef IndexOPSH
#define IndexOPSH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include "RzRadGrp.hpp"
#include "SmrtPanel.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormIndex : public TForm
{
__published:	// IDE-managed Components
        TRichEdit *RichEdit1;
        TSmrtPanel *SmrtPanel2;
        TBitBtn *SaveButton;
        TBitBtn *CancelButton;
        TRzCheckGroup *CheckGroup;
        void __fastcall SaveButtonClick(TObject *Sender);
        void __fastcall CancelButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormIndex(TComponent* Owner);
        AnsiString ListOPS;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormIndex *FormIndex;
//---------------------------------------------------------------------------
#endif
