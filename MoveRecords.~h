//---------------------------------------------------------------------------

#ifndef MoveRecordsH
#define MoveRecordsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "SmrtPanel.h"
#include <ADODB.hpp>
#include <DB.hpp>
#include "Placemnt.hpp"
#include <Buttons.hpp>
#include "DBGridEh.hpp"
#include <Grids.hpp>
#include "FIBDataSet.hpp"
#include "pFIBDataSet.hpp"
#include "FIBDatabase.hpp"
#include "FIBQuery.hpp"
#include "pFIBQuery.hpp"
#include "pFIBDatabase.hpp"

//---------------------------------------------------------------------------
class TMoveRecordsForm : public TForm
{
__published:	// IDE-managed Components
        TRichEdit *RichEdit1;
        TSmrtPanel *SmrtPanel2;
        TFormStorage *FormStorage1;
        TBitBtn *SaveButton;
        TBitBtn *CancelButton;
        TBitBtn *CopyButton;
        TDBGridEh *EIGrid;
        TDataSource *DataSource;
        TpFIBQuery *TempQ;
        TpFIBTransaction *DT;
        void __fastcall RichEdit1ResizeRequest(TObject *Sender,
          TRect &Rect);
        void __fastcall SaveButtonClick(TObject *Sender);
        void __fastcall CancelButtonClick(TObject *Sender);
        void __fastcall CopyButtonClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMoveRecordsForm(TComponent* Owner);
        __fastcall TMoveRecordsForm(TComponent* Owner,TDataSet *DS, int cp);
        void __fastcall LoadDataSet(void);
        int IDMove;
        bool CopyFLG;
        int recno,kod;
        TpFIBDataSet *DS;
        
};
//---------------------------------------------------------------------------
extern PACKAGE TMoveRecordsForm *MoveRecordsForm;
//---------------------------------------------------------------------------
#endif
