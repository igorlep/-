//---------------------------------------------------------------------------

#ifndef ConstHistoryEditH
#define ConstHistoryEditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Placemnt.hpp"
#include "FIBQuery.hpp"
#include "pFIBQuery.hpp"
#include "DBGridEh.hpp"
#include "FIBDataSet.hpp"
#include "pFIBDataSet.hpp"
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include "FIBDatabase.hpp"
#include "pFIBDatabase.hpp"
#include "JvComponent.hpp"
#include "JvExControls.hpp"
#include "JvNavigationPane.hpp"
//---------------------------------------------------------------------------
class TConstHistoryEditForm : public TForm
{
__published:	// IDE-managed Components
        TFormStorage *FormStorage1;
        TPanel *Panel1;
        TpFIBDataSet *ConstValDS;
        TDataSource *ConstValSource;
        TDBGridEh *ConstValGrid;
        TFIBIntegerField *ConstValDSID;
        TFIBSmallIntField *ConstValDSORG_ID;
        TFIBSmallIntField *ConstValDSCONST_ID;
        TFIBStringField *ConstValDSCONST_VALUE;
        TFIBDateField *ConstValDSCONST_DATE;
        TFIBIntegerField *ConstValDSREFERENCE;
        TSpeedButton *SpeedButton1;
        TSpeedButton *AddButton;
        TSpeedButton *SaveButton;
        TSpeedButton *CancelButton;
        TSpeedButton *DelButton;
        TSpeedButton *ExitButton;
        TpFIBTransaction *WT;
        TpFIBTransaction *RT;
        TJvNavPanelHeader *formHeader;
        TpFIBQuery *ConstQ;
        void __fastcall ConstValSourceStateChange(TObject *Sender);
        void __fastcall AddButtonClick(TObject *Sender);
        void __fastcall SaveButtonClick(TObject *Sender);
        void __fastcall CancelButtonClick(TObject *Sender);
        void __fastcall DelButtonClick(TObject *Sender);
        void __fastcall ConstValDSBeforePost(TDataSet *DataSet);
        void __fastcall ExitButtonClick(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
  int OrgID, ConstID, constType;
public:		// User declarations
  __fastcall TConstHistoryEditForm(TComponent* Owner,int Org_ID,int Const_ID);
};
//---------------------------------------------------------------------------
//extern PACKAGE TConstHistoryEditForm *ConstHistoryEditForm;
//---------------------------------------------------------------------------
#endif
