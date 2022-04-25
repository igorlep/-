//---------------------------------------------------------------------------

#ifndef OrganizationsH
#define OrganizationsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Placemnt.hpp"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "DBGridEh.hpp"
#include <DB.hpp>
#include <Grids.hpp>
#include <DBCtrls.hpp>
#include "FIBDataSet.hpp"
#include "pFIBDataSet.hpp"
#include "kbmMemTable.hpp"
#include "FIBQuery.hpp"
#include "pFIBQuery.hpp"
#include "ToolEdit.hpp"
#include <Mask.hpp>
#include "FIBDatabase.hpp"
#include "pFIBDatabase.hpp"
#include "JvComponent.hpp"
#include "JvExControls.hpp"
#include "JvNavigationPane.hpp"
#include <Graphics.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TOrganizationsForm : public TForm
{
__published:	// IDE-managed Components
        TFormStorage *FormStorage1;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TSplitter *Splitter1;
        TDataSource *ConstSource;
        TPanel *bottomPanel;
        TpFIBDataSet *OrgDS;
        TDataSource *OrgSource;
        TkbmMemTable *ConstDS;
        TSmallintField *ConstDSID;
        TStringField *ConstDSConstName;
        TStringField *ConstDSConstValue;
        TpFIBDataSet *CDS;
        TpFIBQuery *ValueQ;
        TFIBSmallIntField *OrgDSID;
        TFIBStringField *OrgDSNAME;
        TFIBDateField *OrgDSBEGIN_DATE;
        TPanel *Panel3;
        TPanel *Panel7;
        TSpeedButton *SaveButton;
        TSpeedButton *AddButton;
        TSpeedButton *DelButton;
        TDBGridEh *OrgGrid;
        TPanel *Panel1;
        TSpeedButton *CancelButton;
        TSpeedButton *ExitButton;
        TSpeedButton *SpeedButton1;
        TDateField *ConstDSConstDate;
        TFIBStringField *OrgDSINN;
        TFIBStringField *OrgDSKPP;
        TFIBBooleanField *OrgDSDELETE_FLG;
        TpFIBTransaction *OrgT;
        TpFIBTransaction *RST;
        TpFIBTransaction *CT;
        TJvNavPanelHeader *bottomHeader;
        TPanel *constPanel;
        TDBGridEh *ConstGrid;
        TPanel *constDataPanel;
        TDateEdit *DateEdit;
        TPanel *hintPanel;
        TImage *Image1;
        TSmallintField *ConstDSCONST_KIND;
        TImageList *ImageList;
        TLabel *hintLabel;
        TLabel *constDateLabel;
        TStringField *ConstDSIDENTIFIER;
        void __fastcall SaveButtonClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall AddButtonClick(TObject *Sender);
        void __fastcall DelButtonClick(TObject *Sender);
        void __fastcall OrgSourceDataChange(TObject *Sender,
          TField *Field);
        void __fastcall DateEditChange(TObject *Sender);
        void __fastcall OrgSourceStateChange(TObject *Sender);
        void __fastcall CancelButtonClick(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall ExitButtonClick(TObject *Sender);
private:	// User declarations
  AnsiString iniFileName;
public:		// User declarations
        __fastcall TOrganizationsForm(TComponent* Owner);
        void __fastcall FullingConstDS(void);
        TDateTime CDate;
};
//---------------------------------------------------------------------------
extern PACKAGE TOrganizationsForm *OrganizationsForm;
//---------------------------------------------------------------------------
#endif
