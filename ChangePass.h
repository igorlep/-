//---------------------------------------------------------------------------

#ifndef ChangePassH
#define ChangePassH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "FIBDataSet.hpp"
#include "pFIBDataSet.hpp"
#include "FIBQuery.hpp"
#include "pFIBQuery.hpp"
#include <Buttons.hpp>
#include "FIBDatabase.hpp"
#include "pFIBDatabase.hpp"
//---------------------------------------------------------------------------
class TChangePassForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TPanel *Panel2;
        TEdit *OldPassword;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *NewPassword1;
        TEdit *NewPassword2;
        TBitBtn *SaveButton;
        TBitBtn *CancelButton;
        TpFIBQuery *Q;
        TpFIBTransaction *T;
        void __fastcall OldPasswordKeyPress(TObject *Sender, char &Key);
        void __fastcall NewPassword1KeyPress(TObject *Sender, char &Key);
        void __fastcall SaveButtonClick(TObject *Sender);
        void __fastcall CancelButtonClick(TObject *Sender);
        void __fastcall OldPasswordDblClick(TObject *Sender);
private:	// declarations
        int U_ID;
        AnsiString userPWD;
public:		// User declarations
        __fastcall TChangePassForm(TComponent* Owner, unsigned int u_id);
};
//---------------------------------------------------------------------------
//extern PACKAGE TChangePassForm *ChangePassForm;
//---------------------------------------------------------------------------
#endif
