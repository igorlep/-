//---------------------------------------------------------------------------

#ifndef SFRegistrationH
#define SFRegistrationH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Placemnt.hpp"
#include "SmrtPanel.h"
#include "ToolEdit.hpp"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include "FIBDataSet.hpp"
#include "pFIBDataSet.hpp"
#include <DB.hpp>
#include "FIBQuery.hpp"
#include "pFIBQuery.hpp"
#include "pFIBStoredProc.hpp"
#include "FIBDatabase.hpp"
#include "pFIBDatabase.hpp"
#include <ComCtrls.hpp>
#include "JvComponent.hpp"
#include "JvExControls.hpp"
#include "JvXPButtons.hpp"
#include "JvXPCore.hpp"
#include "JvXPCheckCtrls.hpp"
#include "JvExMask.hpp"
#include "JvToolEdit.hpp"
//---------------------------------------------------------------------------
class TInvoiceEditForm : public TForm
{
__published:	// IDE-managed Components
        TFormStorage *FormStorage1;
        TSmrtPanel *SmrtPanel2;
        TSmrtPanel *SmrtPanel1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label6;
        TComboEdit *InvoiceNumberEdit;
        TLabel *PADocsLabel;
        TpFIBQuery *TQ;
        TpFIBStoredProc *AddInvoiceProc;
        TSpeedButton *SelectNumberButton;
        TpFIBQuery *UpDateQ;
        TpFIBTransaction *TempTransaction;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton1;
        TRichEdit *PADocs;
        TSpeedButton *SpeedButton3;
        TLabel *Label5;
        TComboBox *InvoiceTypeBox;
        TJvXPButton *SaveButton;
        TJvXPButton *CancelButton;
        TJvXPCheckbox *advanceCheckbox;
        TJvXPCheckbox *revisionCheckbox;
        TJvDateEdit *invoiceDateEdit;
        TJvComboEdit *buyerEdit;
        TJvComboEdit *consigneeEdit;
        void __fastcall SelectNumberButtonClick(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall InvoiceTypeBoxChange(TObject *Sender);
        void __fastcall SaveButtonClick(TObject *Sender);
        void __fastcall CancelButtonClick(TObject *Sender);
        void __fastcall invoiceDateEditChange(TObject *Sender);
        void __fastcall buyerEditButtonClick(TObject *Sender);
        void __fastcall consigneeEditButtonClick(TObject *Sender);
private:	// User declarations
  int oldINumber;
public:		// User declarations
  __fastcall TInvoiceEditForm(TComponent* Owner, TpFIBDataSet *A_DS);
  __fastcall TInvoiceEditForm(TComponent* Owner, int OrgID, int InvNum, TDateTime InvDate, int Count_Number, TDateTime Count_Date);
  TDateTime CountDate, InvDate, PrevID;
  int OrgID, InvNum;
  int CountNumber, BuyerID, ConsigneeID;
  bool NewInvoiceFLG;
};
//---------------------------------------------------------------------------
//extern PACKAGE TInvoiceEditForm *InvoiceEditForm;
//---------------------------------------------------------------------------
#endif
