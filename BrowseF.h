//---------------------------------------------------------------------------

#ifndef BrowseFH
#define BrowseFH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DBGridEh.hpp"
#include "RXSpin.hpp"
#include "SmrtPanel.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "FIBDatabase.hpp"
#include "FIBDataSet.hpp"
#include "FIBQuery.hpp"
#include "pFIBDatabase.hpp"
#include "pFIBDataSet.hpp"
#include "pFIBQuery.hpp"
#include "Placemnt.hpp"
#include <DB.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include "DataModule.h"
#include "JvComponent.hpp"
#include "JvExControls.hpp"
#include "JvNavigationPane.hpp"
#include "AccountEdit.h"


//---------------------------------------------------------------------------
class TBrowseForm : public TForm
{
__published:	// IDE-managed Components
        TSmrtPanel *SmrtPanel1;
        TLabel *Label1;
        TSpeedButton *FirstButton;
        TSpeedButton *LastButton;
        TSpeedButton *PriorButton;
        TSpeedButton *NextButton;
        TSpeedButton *ExitButton;
        TSpeedButton *increaseButton;
        TSpeedButton *reduceButton;
        TEdit *Edit1;
        TComboBox *Month;
        TRxSpinEdit *Year;
        TSmrtPanel *SmrtPanel3;
        TDBGridEh *AccountsGrid;
        TSmrtPanel *SmrtPanel2;
        TDBGridEh *DBGrid;
        TFormStorage *FormStorage1;
        TpFIBDataSet *A_DS;
        TpFIBTransaction *ATransaction;
        TImageList *ImageList;
        TpFIBTransaction *WriteTransaction;
        TpFIBQuery *WQ;
        TDataSource *AccountsS;
        TTimer *searchTimer;
        TFIBStringField *A_DSLCHET1;
        TFIBFloatField *A_DSSUMMA;
        TFIBStringField *A_DSWORD;
        TFIBIntegerField *A_DSMETKA;
        TFIBIntegerField *A_DSNEOPL;
        TFIBIntegerField *A_DSPNN;
        TFIBIntegerField *A_DSLCHET;
        TFIBStringField *A_DSFAMILY;
        TFIBStringField *A_DSNAME;
        TFIBStringField *A_DSFATHER;
        TFIBIntegerField *A_DSKOD;
        TFIBDateField *A_DSC;
        TFIBDateField *A_DSDOC;
        TFIBStringField *A_DSSERIA;
        TFIBIntegerField *A_DSNOMER;
        TFIBIntegerField *A_DSDOST;
        TFIBIntegerField *A_DSD_VIPL;
        TFIBStringField *A_DSULIC;
        TFIBStringField *A_DSADRES;
        TFIBIntegerField *A_DSCHEL;
        TFIBIntegerField *A_DSMETKA1;
        TFIBIntegerField *A_DSVNOM;
        TFIBStringField *A_DSPRICH;
        TFIBIntegerField *A_DSIST;
        TFIBIntegerField *A_DSBSUMMA;
        TFIBStringField *A_DSBWORD;
        TFIBIntegerField *A_DSFAKT_CHEL;
        TFIBIntegerField *A_DSFAKT_DAT;
        TFIBIntegerField *A_DSNSP;
        TFIBStringField *A_DSKEM_VID;
        TFIBDateField *A_DSDATA_VID;
        TSpeedButton *UnSelectButton;
        TSpeedButton *SelectPer;
        TJvNavPanelHeader *MainHeader;
        TSpeedButton *SelectButton;
        TSpeedButton *CopyButton;
        TpFIBQuery *TempQuery;
        TSpeedButton *SaveButton;
        TSpeedButton *EditButton;
        TSpeedButton *CancelButton;
        TJvNavPanelHeader *MainFooter;
        TFIBSmallIntField *A_DSDOBAVL;
        TFIBIntegerField *A_DSKODPEN;
        TFIBIntegerField *A_DSFOND;
        TFIBIntegerField *A_DSM;
        TFIBIntegerField *A_DSY;
        TLabel *Label19;
        TLabel *Label2;
        TEdit *Edit2;
        TCheckBox *CheckBox1;
        TSmrtPanel *SmrtPanel4;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ExitButtonClick(TObject *Sender);
        void __fastcall increaseButtonClick(TObject *Sender);
        void __fastcall reduceButtonClick(TObject *Sender);
        void __fastcall FirstButtonClick(TObject *Sender);
        void __fastcall PriorButtonClick(TObject *Sender);
        void __fastcall NextButtonClick(TObject *Sender);
        void __fastcall LastButtonClick(TObject *Sender);
        void __fastcall searchTimerTimer(TObject *Sender);
        void __fastcall AccountsSDataChange(TObject *Sender,
          TField *Field);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall UnSelectButtonClick(TObject *Sender);
        void __fastcall SelectPerClick(TObject *Sender);
        void __fastcall SelectButtonClick(TObject *Sender);
        void __fastcall CopyButtonClick(TObject *Sender);
        void __fastcall SaveButtonClick(TObject *Sender);
        void __fastcall EditButtonClick(TObject *Sender);
        void __fastcall CancelButtonClick(TObject *Sender);
        void __fastcall A_DSD_VIPLChange(TField *Sender);
        void __fastcall A_DSBeforeEdit(TDataSet *DataSet);
        void __fastcall DBGridMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall DBGridCellClick(TColumnEh *Column);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
private:	// User declarations
  AnsiString iniFileName;
  int date1, date2;
  orders order;
  void __fastcall loadProperties(void);
  void __fastcall saveProperties(void);
public:		// User declarations
  __fastcall TBrowseForm(TComponent* Owner);
  filters filter;
  void __fastcall LoadDataSet(void);
  void __fastcall setMainHeader(void);
  void __fastcall SetButtons(void);
  void __fastcall ProvStatus(void);
  int __fastcall getDate1(void){ return date1; }
  int __fastcall getDate2(void){ return date2; }
  AnsiString Post;
  int flag;
  int post;
  int dold;
  int kolzap;
  int indexofops;
  int Dost,Ops,KPost,Opl;
  unsigned short y,m,d;
  int ByNH;
};
//---------------------------------------------------------------------------
extern PACKAGE TBrowseForm *BrowseForm;
//---------------------------------------------------------------------------
#endif
