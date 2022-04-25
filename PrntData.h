//---------------------------------------------------------------------------

#ifndef PrntDataH
#define PrntDataH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "FIBDataSet.hpp"
#include "frxClass.hpp"
#include "frxDBSet.hpp"
#include "pFIBDataSet.hpp"
#include "Placemnt.hpp"
#include "RXSpin.hpp"
#include "SmrtPanel.h"
#include <Buttons.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include "frxExportXLS.hpp"
#include "FIBDatabase.hpp"
#include "pFIBDatabase.hpp"
#include "DBGridEh.hpp"
#include "JvComponent.hpp"
#include "JvExControls.hpp"
#include "JvNavigationPane.hpp"
#include "JvXPButtons.hpp"
#include "JvXPCore.hpp"
#include "kbmMemTable.hpp"
#include <Grids.hpp>
#include <DBTables.hpp>
#include "JvExMask.hpp"
#include "JvSpin.hpp"
#include <Mask.hpp>
#include "frxExportRTF.hpp"
#include "FIBQuery.hpp"
#include "pFIBQuery.hpp"
#include <ADODB.hpp>
#include "ZipBuilder.h"
#include "CGAUGES.h"
#include "pFIBStoredProc.hpp"
//---------------------------------------------------------------------------
class TPrntDataForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TpFIBDataSet *HeadDS;
        TfrxDBDataset *frxHeadDS;
        TpFIBDataSet *TableDS;
        TfrxDBDataset *frxTableDS;
        TfrxDBDataset *DSSvod;
        TpFIBTransaction *HT;
        TpFIBTransaction *TT;
        TkbmMemTable *MemTable1;
        TkbmMemTable *forLeaderTable;
        TDataSource *Source1;
        TDataSource *forLeaderSource;
        TStringField *MemTable1DOC_NUNBER;
        TDateField *MemTable1DOC_DATE;
        TSmallintField *MemTable1DOC_ID;
        TSmallintField *forLeaderTableDOC_ID;
        TStringField *forLeaderTableFOR_LEADER;
        TBooleanField *forLeaderTableLEADER_CHECK;
        TJvXPButton *CloseButton;
        TJvXPButton *ViewButton;
        TSmallintField *forLeaderTableV_ID;
        TStringField *MemTable1DOC_NAME;
        TStringField *MemTable1CONST_IDENTIFIER;
        TPanel *Panel2;
        TRadioButton *JournalButton;
        TRadioButton *InvoiceButton;
        TRadioButton *CountButton;
        TJvNavPanelHeader *JvNavPanelHeader2;
        TPanel *Panel6;
        TLabel *Label3;
        TJvSpinEdit *CNEdit;
        TkbmMemTable *forBookTable;
        TSmallintField *forBookTableV_ID;
        TSmallintField *forBookTableDOC_ID;
        TStringField *forBookTableFOR_BOOK;
        TBooleanField *forBookTableBOOK_CHECK;
        TDataSource *forBookSource;
        TfrxRTFExport *RTFExport;
        TLabel *Label1;
        TJvSpinEdit *CNEdit1;
        TpFIBQuery *TempQ;
        TpFIBTransaction *DT;
        TpFIBTransaction *AccountsT;
        TFIBSmallIntField *HeadDSORG_ID;
        TFIBDateField *HeadDSCOUNT_DATE;
        TFIBSmallIntField *HeadDSCOUNT_NUMBER;
        TFIBIntegerField *HeadDSCUSTOMER_ID;
        TFIBStringField *HeadDSCUSTOMER_NAME;
        TFIBSmallIntField *HeadDSUSER_ID;
        TFIBSmallIntField *HeadDSRS_ID;
        TFIBFloatField *HeadDSCOUNT_TOTAL;
        TFIBBooleanField *HeadDSEDIT_KEY;
        TFIBSmallIntField *HeadDSCOUNT_TYPE;
        TFIBFloatField *HeadDSCOUNT_OPL;
        TFIBFloatField *HeadDSCOUNT_NEOPL;
        TFIBIntegerField *HeadDSCOUNT_TOTALI;
        TFIBIntegerField *HeadDSCOUNT_OPLI;
        TFIBIntegerField *HeadDSCOUNT_NEOPLI;
        TFIBFloatField *HeadDSCOUNT_TEK;
        TFIBFloatField *HeadDSCOUNT_PR;
        TFIBFloatField *HeadDSCOUNT_RAZ;
        TFIBFloatField *HeadDSCOUNT_NEOPLP;
        TFIBFloatField *HeadDSCOUNT_OPLP;
        TFIBIntegerField *HeadDSM;
        TFIBIntegerField *HeadDSY;
        TFIBIntegerField *TableDSOPS;
        TFIBFloatField *TableDSOPL;
        TFIBFloatField *TableDSNEOPL;
        TFIBIntegerField *TableDSCOUNT_OPL;
        TFIBIntegerField *TableDSCOUNT_NEOPL;
        TfrxDBDataset *frxTableDS1;
        TpFIBDataSet *DSREPRES;
        TFIBIntegerField *DSREPRESOPS;
        TFIBFloatField *DSREPRESCOUNT_TOTAL;
        TFIBFloatField *DSREPRESCOUNT_OPL;
        TFIBFloatField *DSREPRESCOUNT_NEOPL;
        TFIBIntegerField *DSREPRESCOUNT_TOTALI;
        TFIBIntegerField *DSREPRESCOUNT_OPLI;
        TFIBIntegerField *DSREPRESCOUNT_NEOPLI;
        TFIBFloatField *DSREPRESCOUNT_TEK;
        TFIBFloatField *DSREPRESCOUNT_PR;
        TFIBFloatField *DSREPRESCOUNT_RAZ;
        TFIBFloatField *DSREPRESCOUNT_NEOPLP;
        TFIBIntegerField *DSREPRESCOUNT_FI;
        TFIBFloatField *DSREPRESCOUNT_FD;
        TFIBIntegerField *DSREPRESCOUNT_NEOPLG;
        TFIBIntegerField *DSREPRESCOUNT_OPLM;
        TFIBIntegerField *DSREPRESCOUNT_OPLT;
        TFIBIntegerField *DSREPRESCOUNT_OPLR;
        TpFIBDataSet *DSSved;
        TJvXPButton *OutputButton;
        TADOConnection *ADOConnection;
        TADOQuery *Q;
        TZipBuilder *ZipBuilder;
        TpFIBDataSet *ExportDS;
        TpFIBDataSet *ExportDS1;
        TFIBStringField *ExportDS1LCHET1;
        TFIBFloatField *ExportDS1SUMMA;
        TFIBStringField *ExportDS1WORD;
        TFIBIntegerField *ExportDS1METKA;
        TFIBIntegerField *ExportDS1NEOPL;
        TFIBIntegerField *ExportDS1PNN;
        TFIBIntegerField *ExportDS1LCHET;
        TFIBStringField *ExportDS1FAMILY;
        TFIBStringField *ExportDS1NAME;
        TFIBStringField *ExportDS1FATHER;
        TFIBIntegerField *ExportDS1KOD;
        TFIBDateField *ExportDS1C;
        TFIBDateField *ExportDS1DOC;
        TFIBStringField *ExportDS1SERIA;
        TFIBIntegerField *ExportDS1NOMER;
        TFIBIntegerField *ExportDS1DOST;
        TFIBIntegerField *ExportDS1D_VIPL;
        TFIBStringField *ExportDS1ULIC;
        TFIBStringField *ExportDS1ADRES;
        TFIBIntegerField *ExportDS1CHEL;
        TFIBIntegerField *ExportDS1METKA1;
        TFIBIntegerField *ExportDS1VNOM;
        TFIBStringField *ExportDS1PRICH;
        TFIBIntegerField *ExportDS1IST;
        TFIBIntegerField *ExportDS1BSUMMA;
        TFIBStringField *ExportDS1BWORD;
        TFIBIntegerField *ExportDS1FAKT_CHEL;
        TFIBIntegerField *ExportDS1FAKT_DAT;
        TFIBIntegerField *ExportDS1NSP;
        TFIBStringField *ExportDS1KEM_VID;
        TFIBDateField *ExportDS1DATA_VID;
        TFIBSmallIntField *ExportDS1DOBAVL;
        TFIBIntegerField *ExportDS1KODPEN;
        TFIBIntegerField *ExportDS1FOND;
        TFIBIntegerField *ExportDS1M;
        TFIBIntegerField *ExportDS1Y;
        TCGauge *Indicator;
        TRadioButton *PotrButton;
        TpFIBDataSet *PotrDS;
        TfrxDBDataset *frxPotrDS;
        TfrxReport *frxReport3;
        TfrxReport *frxReport;
        TJvXPButton *SendButton;
        TfrxReport *frxReport1;
        TFormStorage *FormStorage1;
        TpFIBTransaction *ConstTransaction;
        TpFIBStoredProc *ConstProc;
        TfrxReport *frxReport2;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall CountButtonClick(TObject *Sender);
        void __fastcall InvoiceButtonClick(TObject *Sender);
        void __fastcall JournalButtonClick(TObject *Sender);
        void __fastcall frxReportGetValue(const AnsiString VarName,
          Variant &Value);
        void __fastcall CloseButtonClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall OutputButtonClick(TObject *Sender);
        void __fastcall ViewButtonClick(TObject *Sender);
        void __fastcall PotrButtonClick(TObject *Sender);
        void __fastcall frxReport3GetValue(const AnsiString VarName,
          Variant &Value);
        void __fastcall SendButtonClick(TObject *Sender);
private:	// User declarations
  AnsiString iniFileName;
  bool memTable1FLG;
  bool forLeaderTableEditFLG,forBookTableEditFLG;
  AnsiString forLeaderSignature,forBookSignature,docForLeader,docForBook;
  void __fastcall fillSignatures(TDateTime constDate);
  bool __fastcall Filedate(AnsiString NF);
  int __fastcall CheckDB(void);
  int __fastcall exporttodbf(void);
public:		// User declarations
        __fastcall TPrntDataForm(TComponent* Owner);
        TDateTime ConstToDate;
        int OrgID;
        int Massiv[20];
        AnsiString IndexOps;
        int KolOps;
};
//---------------------------------------------------------------------------
extern PACKAGE TPrntDataForm *PrntDataForm;
//---------------------------------------------------------------------------
#endif
