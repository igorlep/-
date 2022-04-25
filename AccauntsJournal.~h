//---------------------------------------------------------------------------

#ifndef AccauntsJournalH
#define AccauntsJournalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SmrtPanel.h"
#include "AccountEdit.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "PLACEMNT.HPP"
#include "Placemnt.hpp"
#include "DBGridEh.hpp"
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <DBCtrls.hpp>
#include "RXSpin.hpp"
#include "FIBDataSet.hpp"
#include "pFIBDataSet.hpp"
#include <ImgList.hpp>
#include "FIBQuery.hpp"
#include "pFIBQuery.hpp"
#include "pFIBStoredProc.hpp"
#include "FIBDatabase.hpp"
#include "pFIBDatabase.hpp"
#include "DataModule.h"
#include "JvComponent.hpp"
#include "JvExControls.hpp"
#include "JvNavigationPane.hpp"
//---------------------------------------------------------------------------
class TAccountsJournalForm : public TForm
{
__published:	// IDE-managed Components
        TFormStorage *FormStorage1;
        TImageList *ImageList;

        TSmrtPanel *SmrtPanel3;
        TpFIBDataSet *A_DS;
        TDataSource *AccountsS;
        TDBGridEh *AccountsGrid;
        TpFIBTransaction *ATransaction;
        TpFIBQuery *WQ;
        TpFIBTransaction *WriteTransaction;

        TSplitter *Splitter1;
        TSmrtPanel *SmrtPanel2;
        TpFIBDataSet *SG_DS;
        TDataSource *GoodsSource;
        TDBGridEh *SoldGoodsGrid;
        TpFIBTransaction *SGTransaction;

        TSmrtPanel *SmrtPanel1;
        TSpeedButton *AddButton;
        TSpeedButton *EditButton;
        TSpeedButton *DelButton;
        TSpeedButton *PrintButton;
        TSpeedButton *increaseButton;
        TSpeedButton *reduceButton;

        TRxSpinEdit *Year;
        TComboBox *Month;
        TUpDown *MonthUpDown;
        TSpeedButton *FirstButton;
        TSpeedButton *PriorButton;
        TSpeedButton *NextButton;
        TSpeedButton *LastButton;
        TSpeedButton *UpDateButton;
        TSpeedButton *ExitButton;

        TPopupMenu *Menu;
        TMenuItem *AddItem;
        TMenuItem *EditItem;
        TMenuItem *DelItem;
        TMenuItem *PrintItem;
        TFIBSmallIntField *A_DSORG_ID;
        TFIBDateField *A_DSCOUNT_DATE;
        TFIBSmallIntField *A_DSCOUNT_NUMBER;
        TFIBIntegerField *A_DSCUSTOMER_ID;
        TFIBStringField *A_DSCUSTOMER_NAME;
        TFIBSmallIntField *A_DSUSER_ID;
        TFIBSmallIntField *A_DSRS_ID;
        TFIBFloatField *A_DSCOUNT_TOTAL;
        TFIBBooleanField *A_DSEDIT_KEY;
        TFIBSmallIntField *A_DSCOUNT_TYPE;
        TFIBFloatField *A_DSCOUNT_OPL;
        TFIBFloatField *A_DSCOUNT_NEOPL;
        TFIBIntegerField *A_DSCOUNT_TOTALI;
        TFIBIntegerField *A_DSCOUNT_OPLI;
        TFIBIntegerField *A_DSCOUNT_NEOPLI;
        TFIBFloatField *A_DSCOUNT_TEK;
        TFIBFloatField *A_DSCOUNT_PR;
        TFIBFloatField *A_DSCOUNT_RAZ;
        TFIBFloatField *A_DSCOUNT_NEOPLP;
        TFIBFloatField *A_DSCOUNT_OPLP;
        TFIBIntegerField *A_DSM;
        TFIBIntegerField *A_DSY;
        TFIBSmallIntField *SG_DSORG_ID;
        TFIBDateField *SG_DSCOUNT_DATE;
        TFIBSmallIntField *SG_DSCOUNT_NUMBER;
        TFIBStringField *SG_DSLCHET1;
        TFIBFloatField *SG_DSSUMMA;
        TFIBStringField *SG_DSWORD;
        TFIBIntegerField *SG_DSMETKA;
        TFIBIntegerField *SG_DSNEOPL;
        TFIBIntegerField *SG_DSPNN;
        TFIBIntegerField *SG_DSLCHET;
        TFIBStringField *SG_DSFAMILY;
        TFIBStringField *SG_DSNAME;
        TFIBStringField *SG_DSFATHER;
        TFIBIntegerField *SG_DSKOD;
        TFIBDateField *SG_DSC;
        TFIBDateField *SG_DSDOC;
        TFIBStringField *SG_DSSERIA;
        TFIBIntegerField *SG_DSNOMER;
        TFIBIntegerField *SG_DSDOST;
        TFIBIntegerField *SG_DSD_VIPL;
        TFIBStringField *SG_DSULIC;
        TFIBStringField *SG_DSADRES;
        TFIBIntegerField *SG_DSCHEL;
        TFIBIntegerField *SG_DSMETKA1;
        TFIBIntegerField *SG_DSVNOM;
        TFIBStringField *SG_DSPRICH;
        TFIBIntegerField *SG_DSIST;
        TFIBIntegerField *SG_DSBSUMMA;
        TFIBStringField *SG_DSBWORD;
        TFIBIntegerField *SG_DSFAKT_CHEL;
        TFIBIntegerField *SG_DSFAKT_DAT;
        TFIBIntegerField *SG_DSNSP;
        TFIBStringField *SG_DSKEM_VID;
        TFIBDateField *SG_DSDATA_VID;
        TFIBStringField *A_DSAVTOR;
        TLabel *Label18;
        TEdit *Edit1;
        TTimer *searchTimer;
        TTimer *Timer1;
        TSpeedButton *SelectPer;
        TJvNavPanelHeader *MainHeader;
        TFIBIntegerField *SG_DSM;
        TFIBIntegerField *SG_DSY;
        TFIBIntegerField *SG_DSKODPEN;
        TFIBIntegerField *SG_DSFOND;
        TFIBSmallIntField *SG_DSKASSA;
        TCheckBox *CheckBox1;
        TpFIBDataSet *DB1;
        TpFIBTransaction *ReadTransaction;
        TpFIBQuery *TempQ;
        TpFIBTransaction *QT;
        TpFIBQuery *TQ;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
//  void __fastcall EditButtonClick(TObject *Sender);
  void __fastcall ExitButtonClick(TObject *Sender);

  void __fastcall AccountsGridTitleBtnClick(TObject *Sender,int ACol,TColumnEh *Column);
  void __fastcall AccountsGridDblClick(TObject *Sender);
  void __fastcall AccountsSDataChange(TObject *Sender,TField *Field);

  void __fastcall AddItemClick(TObject *Sender);
  void __fastcall AddButtonClick(TObject *Sender);
  void __fastcall EditItemClick(TObject *Sender);
  void __fastcall EditButtonClick(TObject *Sender);
  void __fastcall DelItemClick(TObject *Sender);
  void __fastcall DelButtonClick(TObject *Sender);
  void __fastcall PrintButtonClick(TObject *Sender);
  void __fastcall increaseButtonClick(TObject *Sender);
  void __fastcall reduceButtonClick(TObject *Sender);
  void __fastcall YearChange(TObject *Sender);
  void __fastcall MonthChange(TObject *Sender);
  void __fastcall MonthUpDownClick(TObject *Sender,TUDBtnType Button);
  void __fastcall FirstButtonClick(TObject *Sender);
  void __fastcall PriorButtonClick(TObject *Sender);
  void __fastcall NextButtonClick(TObject *Sender);
  void __fastcall LastButtonClick(TObject *Sender);
  void __fastcall UpDateButtonClick(TObject *Sender);
        void __fastcall SoldGoodsGridGetCellParams(TObject *Sender,
          TColumnEh *Column, TFont *AFont, TColor &Background,
          TGridDrawState State);
        void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall searchTimerTimer(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall SelectPerClick(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
private:	// User declarations
  AnsiString iniFileName;
  orders order;
  void __fastcall setPeriod(void);
  void __fastcall loadProperties(void);
  void __fastcall saveProperties(void);
public:		// User declarations
  filters filter;
  int FilterCustomerID, FilterUserID;
  TAccountEditForm *AEF;
//  TpFIBDataSet *A_DS, *SG_DS;
  __fastcall TAccountsJournalForm(TComponent* Owner);
  TDateTime date1, date2;
  TpFIBDataSet *TZ;
  void __fastcall LoadDataSet(void);
  void __fastcall setMainHeader(void);
  void __fastcall SetButtons(void);
  void __fastcall provkassa(void);
  TDateTime __fastcall getDate1(void){ return date1; }
  TDateTime __fastcall getDate2(void){ return date2; }
};
//---------------------------------------------------------------------------
extern PACKAGE TAccountsJournalForm *AccountsJournalForm;
//---------------------------------------------------------------------------
#endif
