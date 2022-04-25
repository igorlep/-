//---------------------------------------------------------------------------

#ifndef RefSortH
#define RefSortH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TRefSortForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TPanel *Panel2;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TBitBtn *SelectButton;
        TBitBtn *CancelButton;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall SelectButtonClick(TObject *Sender);
        void __fastcall CancelButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TRefSortForm(TComponent* Owner);
        int __fastcall ShowForm(short ts, short l, short t);
};
//---------------------------------------------------------------------------
extern PACKAGE TRefSortForm *RefSortForm;
//---------------------------------------------------------------------------
#endif
