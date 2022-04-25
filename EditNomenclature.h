//---------------------------------------------------------------------------

#ifndef EditNomenclatureH
#define EditNomenclatureH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SmrtPanel.h"
#include <ADODB.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include "DBCtrlsEh.hpp"
#include "Placemnt.hpp"
#include <Mask.hpp>
#include "EI.h"
#include <Buttons.hpp>
#include "FIBDatabase.hpp"
#include "FIBDataSet.hpp"
#include "pFIBDatabase.hpp"
#include "pFIBDataSet.hpp"
//---------------------------------------------------------------------------
class TEditNomenclatuteForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel2;
        TDataSource *DSource;
        TSmrtPanel *SmrtPanel1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TFormStorage *FormStorage1;
        TDBEditEh *EIEdit;
        TDBEditEh *IDEdit;
        TDBEditEh *NameEdit;
        TBitBtn *SaveButton;
        TBitBtn *CancelButton;
        TpFIBDataSet *DS;
        TpFIBTransaction *EditTransaction;
        TDBEditEh *CODPEdit;
        TLabel *Label4;
        TFIBIntegerField *DSID;
        TFIBIntegerField *DSFILE_ID;
        TFIBSmallIntField *DSREC_TYPE;
        TFIBStringField *DSDESCRIPTION;
        TFIBStringField *DSEI;
        TFIBIntegerField *DSCODP;
        TFIBIntegerField *DSINDEXOPS;
        void __fastcall DBEditEh1EditButtons0Click(TObject *Sender,
          bool &Handled);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall IDEditKeyPress(TObject *Sender, char &Key);
        void __fastcall NameEditKeyPress(TObject *Sender, char &Key);
        void __fastcall SaveButtonClick(TObject *Sender);
        void __fastcall CancelButtonClick(TObject *Sender);
        void __fastcall DSBeforeEdit(TDataSet *DataSet);
private:	// User declarations
        int N_ID;
public:		// User declarations
        __fastcall TEditNomenclatuteForm(TComponent* Owner, unsigned int n_id);
        bool AddFLG;
        int codp_old;
//        TDataSet *DS;
};
//---------------------------------------------------------------------------
extern PACKAGE TEditNomenclatuteForm *EditNomenclatuteForm;
//---------------------------------------------------------------------------
#endif
