//---------------------------------------------------------------------------

#ifndef OrganizationSelectH
#define OrganizationSelectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DBGridEh.hpp"
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "Placemnt.hpp"
#include <Buttons.hpp>
#include "FIBDatabase.hpp"
#include "FIBDataSet.hpp"
#include "pFIBDatabase.hpp"
#include "pFIBDataSet.hpp"
#include <DB.hpp>
//---------------------------------------------------------------------------
class TOrganizationSelectForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TDBGridEh *OrganizationsGrid;
        TFormStorage *FormStorage1;
        TBitBtn *SelectButton;
        TBitBtn *CancelButton;
        TpFIBDataSet *OrgDS;
        TpFIBTransaction *OrgT;
        TDataSource *OrgSource;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall SelectButtonClick(TObject *Sender);
        void __fastcall CancelButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TOrganizationSelectForm(TComponent* Owner, unsigned int id);
};
//---------------------------------------------------------------------------
//extern PACKAGE TOrganizationSelectForm *OrganizationSelectForm;
//---------------------------------------------------------------------------
#endif
