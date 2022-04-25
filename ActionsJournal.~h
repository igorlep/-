//---------------------------------------------------------------------------

#ifndef ActionsJournalH
#define ActionsJournalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "Placemnt.hpp"
#include "DBGridEh.hpp"
#include "FIBDataSet.hpp"
#include "pFIBDataSet.hpp"
#include <DB.hpp>
#include <Grids.hpp>
#include "SelectRecords.h"
#include "FIBDatabase.hpp"
#include "pFIBDatabase.hpp"
//---------------------------------------------------------------------------
class TActionsJournalForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TSpeedButton *ExitButton;
        TFormStorage *FormStorage1;
        TpFIBDataSet *ActionsDS;
        TDBGridEh *Grid;
        TDataSource *ActionsSource;
        TSpeedButton *SelectButton;
        TSpeedButton *UnSelectButton;
        TpFIBTransaction *AT;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ExitButtonClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall SelectButtonClick(TObject *Sender);
        void __fastcall UnSelectButtonClick(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TActionsJournalForm(TComponent* Owner);
        AnsiString Filter;
        TSelectRecordsForm *SRF;
        void __fastcall SetActionsDS(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TActionsJournalForm *ActionsJournalForm;
//---------------------------------------------------------------------------
#endif
