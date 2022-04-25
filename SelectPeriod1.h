//---------------------------------------------------------------------------

#ifndef SelectPeriodH
#define SelectPeriodH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Placemnt.hpp"
#include "SmrtPanel.h"
#include "ToolEdit.hpp"
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <ComCtrls.hpp>
#include "CSPIN.h"
#include "JvComponent.hpp"
#include "JvExControls.hpp"
#include "JvXPButtons.hpp"
#include "JvXPCore.hpp"
//---------------------------------------------------------------------------
class TSelectPeriodForm : public TForm
{
__published:	// IDE-managed Components
        TSmrtPanel *SmrtPanel2;
        TJvXPButton *JXPBOK;
        TSmrtPanel *SmrtPanel1;
        TFormStorage *FormStorage;
        TDateEdit *IntDate1;
        TDateEdit *IntDate2;
        TStaticText *PeriodText;
        TRadioButton *MonthButton;
        TRadioButton *DayButton;
        TRadioButton *IntButton;
        TLabel *Label1;
        TLabel *Label2;
        TDateEdit *Day;
        TEdit *Month;
        TCheckBox *YearCheckBox;
        TCheckBox *MonthCheckBox;
        TCSpinButton *MonthUpDown;
        TJvXPButton *JvXPButton1;
        void __fastcall JXPBOKClick(TObject *Sender);
        void __fastcall MonthButtonClick(TObject *Sender);
        void __fastcall DayButtonClick(TObject *Sender);
        void __fastcall IntButtonClick(TObject *Sender);
        void __fastcall MonthUpDownDownClick(TObject *Sender);
        void __fastcall MonthUpDownUpClick(TObject *Sender);
        void __fastcall JvXPButton1Click(TObject *Sender);
private:	// User declarations
        TDateTime &date1, &date2;
        int MonthPosition;
public:		// User declarations
        __fastcall TSelectPeriodForm(TComponent* Owner, TDateTime &date1, TDateTime &date2);
        void __fastcall setPeriodText(void);
        TDateTime __fastcall getDate1(void);
        TDateTime __fastcall getDate2(void);
};
//---------------------------------------------------------------------------
//extern PACKAGE TSelectPeriodForm *SelectPeriodForm;
//---------------------------------------------------------------------------
#endif
