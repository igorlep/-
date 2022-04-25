//---------------------------------------------------------------------------

#ifndef ImportDocumentsJournalH
#define ImportDocumentsJournalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Placemnt.hpp"
#include "DBGridEh.hpp"
#include "FIBDatabase.hpp"
#include "FIBDataSet.hpp"
#include "pFIBDatabase.hpp"
#include "pFIBDataSet.hpp"
#include "RXSpin.hpp"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "JvComponent.hpp"
#include "JvExControls.hpp"
#include "JvNavigationPane.hpp"
#include <ImgList.hpp>
#include "JvDialogs.hpp"
#include <Dialogs.hpp>
#include "JvBaseDlg.hpp"
#include "JvSelectDirectory.hpp"
#include <ADODB.hpp>
#include "FIBQuery.hpp"
#include "pFIBQuery.hpp"
//---------------------------------------------------------------------------
class TImportDocumentsJournalForm : public TForm
{
__published:	// IDE-managed Components
        TFormStorage *FormStorage1;
        TJvNavPanelHeader *idHeader;
        TImageList *idImageList;
        TPanel *buttonsPanel;
        TSpeedButton *ExportButton;
        TUpDown *MonthUpDown;
        TComboBox *Month;
        TRxSpinEdit *Year;
        TSpeedButton *FirstButton;
        TSpeedButton *PriorButton;
        TSpeedButton *NextButton;
        TSpeedButton *LastButton;
        TSpeedButton *UpDateButton;
        TSpeedButton *ExitButton;
        TDBGridEh *idGrid;
        TpFIBDataSet *idDS;
        TpFIBTransaction *idTransaction;
        TDataSource *idSource;
        TSplitter *bottomSplitter;
        TJvSelectDirectory *outDirectory;
        TJvOpenDialog *outFileDialog;
        TADOQuery *Q;
        TADOConnection *ADOConnection;
        TSpeedButton *AddButton;
        TpFIBQuery *WQ;
        TpFIBTransaction *WT;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall ExitButtonClick(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall YearChange(TObject *Sender);
  void __fastcall MonthChange(TObject *Sender);
  void __fastcall MonthUpDownClick(TObject *Sender,TUDBtnType Button);
  void __fastcall idSourceDataChange(TObject *Sender, TField *Field);
  void __fastcall idGridSortMarkingChanged(TObject *Sender);
  void __fastcall ExportButtonClick(TObject *Sender);
  void __fastcall AddButtonClick(TObject *Sender);
  void __fastcall UpDateButtonClick(TObject *Sender);
  void __fastcall FirstButtonClick(TObject *Sender);
  void __fastcall PriorButtonClick(TObject *Sender);
  void __fastcall NextButtonClick(TObject *Sender);
  void __fastcall LastButtonClick(TObject *Sender);
private:	// User declarations
  AnsiString iniFileName;
  TDateTime date1, date2, lockDate;
  int idID,idCol;
  AnsiString idOrder;
  void __fastcall loadProperties(void);
  void __fastcall saveProperties(void);
  void __fastcall setPeriod(void);
  void __fastcall loadDataSets(void);
  void __fastcall setButtons(void);
public:		// User declarations
   __fastcall TImportDocumentsJournalForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TImportDocumentsJournalForm *ImportDocumentsJournalForm;
//---------------------------------------------------------------------------
#endif
