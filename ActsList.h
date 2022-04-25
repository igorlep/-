//---------------------------------------------------------------------------

#ifndef ActsListH
#define ActsListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "Placemnt.hpp"
#include "DBGridEh.hpp"
#include "FIBDatabase.hpp"
#include "FIBDataSet.hpp"
#include "pFIBDatabase.hpp"
#include "pFIBDataSet.hpp"
#include <DB.hpp>
#include <Grids.hpp>
#include "FIBQuery.hpp"
#include "pFIBQuery.hpp"
//---------------------------------------------------------------------------
class TActsListForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *ButtonsPanel;
        TSpeedButton *ExitButton;
        TFormStorage *FormStorage;
        TDBGridEh *Grid;
        TpFIBDataSet *ADS;
        TpFIBTransaction *AT;
        TDataSource *AS;
        TSpeedButton *SaveButton;
        TSpeedButton *DelButton;
        TpFIBQuery *Q;
        TpFIBTransaction *WT;
        TFIBIntegerField *ADSLCHET;
        TFIBStringField *ADSFAMILY;
        TFIBStringField *ADSNAME;
        TFIBStringField *ADSFATHER;
        TFIBStringField *ADSSERIA;
        TFIBIntegerField *ADSNOMER;
        TFIBIntegerField *ADSDOST;
        TFIBStringField *ADSULIC;
        TFIBStringField *ADSADRES;
        TFIBIntegerField *ADSMETKA1;
        TFIBSmallIntField *ADSUSER_ID;
        TEdit *Edit1;
        TLabel *Label1;
        TTimer *searchTimer;
        void __fastcall ExitButtonClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall SaveButtonClick(TObject *Sender);
        void __fastcall DelButtonClick(TObject *Sender);
        void __fastcall GridCellClick(TColumnEh *Column);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
        void __fastcall searchTimerTimer(TObject *Sender);
private:	// User declarations
        AnsiString iniFileName;
public:		// User declarations
        __fastcall TActsListForm(TComponent* Owner);
        void __fastcall updateset(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TActsListForm *ActsListForm;
//---------------------------------------------------------------------------
#endif
