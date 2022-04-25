//---------------------------------------------------------------------------

#ifndef SendMessageH
#define SendMessageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "FIBDatabase.hpp"
#include "FIBQuery.hpp"
#include "pFIBDatabase.hpp"
#include "pFIBQuery.hpp"
#include "FIBDataSet.hpp"
#include "pFIBDataSet.hpp"
#include <DB.hpp>
//---------------------------------------------------------------------------
class TSendMessForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TLabel *Label1;
        TEdit *OldPassword;
        TPanel *Panel2;
        TBitBtn *SaveButton;
        TBitBtn *CancelButton;
        TCheckBox *CheckBox1;
        TpFIBQuery *Q;
        TpFIBTransaction *T;
        TpFIBDataSet *UMDataSet;
        void __fastcall SaveButtonClick(TObject *Sender);
        void __fastcall CancelButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TSendMessForm(TComponent* Owner,TDataSet *DS);
};
//---------------------------------------------------------------------------
extern PACKAGE TSendMessForm *SendMessForm;
//---------------------------------------------------------------------------
#endif
