//---------------------------------------------------------------------------

#ifndef SelectRecordsH
#define SelectRecordsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Placemnt.hpp"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "RXCtrls.hpp"
#include "SmrtPanel.h"
#include "ToolEdit.hpp"
#include <Mask.hpp>
#include "FIBDatabase.hpp"
#include "FIBDataSet.hpp"
#include "pFIBDatabase.hpp"
#include "pFIBDataSet.hpp"
#include <DB.hpp>
#include "JvComponent.hpp"
#include "JvExControls.hpp"
#include "JvXPButtons.hpp"
#include "JvXPCore.hpp"
//---------------------------------------------------------------------------
class TSelectRecordsForm : public TForm
{
__published:	// IDE-managed Components
        TFormStorage *FormStorage1;
        TPanel *Panel1;
        TSmrtPanel *SmrtPanel1;
        TRxCheckListBox *ActionsBox;
        TLabel *Label1;
        TLabel *Label2;
        TComboBox *UserBox;
        TEdit *StringEdit;
        TButton *Button1;
        TCheckBox *StrCheckBox;
        TSmrtPanel *SmrtPanel2;
        TRadioButton *LastDayRB;
        TRadioButton *LastWeekRB;
        TRadioButton *LastMonthRB;
        TRadioButton *AllRB;
        TRadioButton *IntervalRB;
        TDateEdit *FromDateEdit;
        TDateEdit *ToDateEdit;
        TLabel *Label3;
        TLabel *Label4;
        TSpeedButton *CheckButton;
        TSpeedButton *UnCheckButton;
        TpFIBDataSet *R_DS;
        TpFIBTransaction *RT;
        TJvXPButton *selectButton;
        TJvXPButton *cancelButton;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall StrCheckBoxClick(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall CheckButtonClick(TObject *Sender);
        void __fastcall UnCheckButtonClick(TObject *Sender);
        void __fastcall selectButtonClick(TObject *Sender);
        void __fastcall cancelButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TSelectRecordsForm(TComponent* Owner);
        TStringList *UsersID;
};
//---------------------------------------------------------------------------
extern PACKAGE TSelectRecordsForm *SelectRecordsForm;
//---------------------------------------------------------------------------
#endif
