//---------------------------------------------------------------------------

#ifndef SelectFilterH
#define SelectFilterH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Placemnt.hpp"
#include <ExtCtrls.hpp>
#include "RXDBCtrl.hpp"
#include "SmrtPanel.h"
#include "ToolEdit.hpp"
#include <Mask.hpp>
#include <Buttons.hpp>
#include "FIBDatabase.hpp"
#include "FIBQuery.hpp"
#include "pFIBDatabase.hpp"
#include "pFIBQuery.hpp"
#include "JvComponent.hpp"
#include "JvExControls.hpp"
#include "JvXPButtons.hpp"
#include "JvXPCore.hpp"
#include "FIBDataSet.hpp"
#include "pFIBDataSet.hpp"
#include <DB.hpp>
//---------------------------------------------------------------------------
class TSelectFilterForm : public TForm
{
__published:	// IDE-managed Components
        TFormStorage *FormStorage1;
        TPanel *Panel1;
        TLabel *Label1;
        TSmrtPanel *SmrtPanel1;
        TCheckBox *CustomerCheckBox;
        TCheckBox *UserCheckBox;
        TpFIBQuery *RQ;
        TpFIBTransaction *RT;
        TJvXPButton *selectButton;
        TJvXPButton *cancelButton;
        TComboBox *autoNumberEdit1;
        TComboBox *autoNumberEdit;
        TpFIBDataSet *RQT;
        TComboBox *autoNumberEdit2;
        TCheckBox *PostCheckBox;
        TRadioGroup *RadioGroup1;
        TCheckBox *CheckBox1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall CustomerCheckBoxClick(TObject *Sender);
        void __fastcall UserCheckBoxClick(TObject *Sender);
        void __fastcall selectButtonClick(TObject *Sender);
        void __fastcall cancelButtonClick(TObject *Sender);
        void __fastcall autoNumberEditChange(TObject *Sender);
        void __fastcall autoNumberEdit1Change(TObject *Sender);
        void __fastcall PostCheckBoxClick(TObject *Sender);
        void __fastcall autoNumberEdit2Change(TObject *Sender);
        void __fastcall RadioGroup1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
private:	// User declarations
        TStringList *autoID;
        TStringList *autoID1;
        TStringList *autoID2;
        AnsiString Post;
        int Dost,Ops,KPost,Opl;

public:		// User declarations
        __fastcall TSelectFilterForm(TComponent* Owner);
        unsigned short parent;
        AnsiString __fastcall getPost(void);
        int __fastcall getDost(void);
        int __fastcall getOps(void);
        int __fastcall getKpost(void);
        int __fastcall getOpl(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TSelectFilterForm *SelectFilterForm;
//---------------------------------------------------------------------------
#endif
