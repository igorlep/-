//---------------------------------------------------------------------------

#ifndef EIH
#define EIH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <ImgList.hpp>
#include <DBCtrls.hpp>
#include <ActnList.hpp>
//#include <DB.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "DBGridEh.hpp"
#include "Placemnt.hpp"
#include "pFIBDatabase.hpp"
#include "SmrtPanel.h"
#include "FIBDataSet.hpp"
#include "pFIBDataSet.hpp"
#include "FIBDatabase.hpp"
#include "FIBQuery.hpp"
#include "pFIBQuery.hpp"
//---------------------------------------------------------------------------
class TTEIForm1 : public TForm
{
__published:	// IDE-managed Components
        TDataSource *DataSource;
        TActionList *ActionList1;
        TAction *SelRec;
        TAction *EditRec;
        TAction *Cancel;
        TFormStorage *FormStorage1;
        TPanel *Panel1;
        TSpeedButton *ExitButton;
        TSpeedButton *SelectButton;
        TSpeedButton *DelButton;
        TSpeedButton *AddButton;
        TSpeedButton *CancelButton;
        TSpeedButton *SaveButton;
        TSpeedButton *SortButton;
        TDBGridEh *EIGrid;
        TStaticText *StaticText1;
        TpFIBTransaction *RT;
        TpFIBQuery *RQ;
        TCheckBox *CheckBox1;
        TpFIBDataSet *DSSved;
        TpFIBTransaction *TT;
        void __fastcall ExitButtonClick(TObject *Sender);
        void __fastcall DelButtonClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall EIGridDblClick(TObject *Sender);
        void __fastcall SelRecExecute(TObject *Sender);
        void __fastcall DataSourceStateChange(TObject *Sender);
        void __fastcall SaveButtonClick(TObject *Sender);
        void __fastcall CancelButtonClick(TObject *Sender);
        void __fastcall AddButtonClick(TObject *Sender);
        void __fastcall SortButtonClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall EIGridKeyPress(TObject *Sender, char &Key);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall EIGridCellClick(TColumnEh *Column);
        void __fastcall CheckBox1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TTEIForm1(TComponent* Owner);
        __fastcall TTEIForm1(TComponent* Owner,TDataSet *DS);
        void __fastcall LoadDataSet(void);
        void __fastcall LookUpRecord(int id);
        int recno,sortind;
        TpFIBDataSet *DS;
};
//---------------------------------------------------------------------------
extern PACKAGE TTEIForm1 *TEIForm1;
//---------------------------------------------------------------------------
#endif
