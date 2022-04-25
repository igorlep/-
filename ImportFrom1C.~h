//---------------------------------------------------------------------------

#ifndef ImportFrom1CH
#define ImportFrom1CH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "Placemnt.hpp"
#include "JvExMask.hpp"
#include "JvToolEdit.hpp"
#include "SmrtPanel.h"
#include <Mask.hpp>
#include "JvExStdCtrls.hpp"
#include "JvMemo.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "FIBQuery.hpp"
#include "pFIBQuery.hpp"
#include "RXSpin.hpp"
#include "FIBDatabase.hpp"
#include "pFIBDatabase.hpp"
#include "ToolEdit.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "DBF_File.h"
#include "FIBDataSet.hpp"
#include "pFIBDataSet.hpp"
#include "ZipBuilder.h"
#include "CGAUGES.h"
#include "JvBitBtn.hpp"
#include "JvExButtons.hpp"
#include "JvComponent.hpp"
#include "JvExControls.hpp"
#include "JvXPButtons.hpp"
#include "JvXPCore.hpp"

//---------------------------------------------------------------------------
class TImportFrom1CForm : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel1;
  TBitBtn *LoadButton;
  TBitBtn *CloseButton;
  TFormStorage *FormStorage1;
  TSmrtPanel *SmrtPanel1;
  TJvMemo *Memo;
  TpFIBQuery *TQ;
        TpFIBTransaction *WT;
        TpFIBTransaction *ReadTransaction;
        TpFIBQuery *TempQuery;
        TpFIBDataSet *DB1;
        TpFIBTransaction *QT;
        TZipBuilder *ZipBuilder;
        TCGauge *Indicator;
        TJvBitBtn *UndoButton;
        TpFIBQuery *TempQ;
        TJvXPButton *SendButton;
  void __fastcall CloseButtonClick(TObject *Sender);
  void __fastcall LoadButtonClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall UndoButtonClick(TObject *Sender);
        void __fastcall SendButtonClick(TObject *Sender);
private:	// User declarations
  AnsiString FileName;
  TDateTime lockDate,tekDate;
  int org_id;
  int rs_id;
  int user_id;
  int type_doc;
  int docs_count;
  bool __fastcall Filedate(AnsiString NF);
public:		// User declarations
  __fastcall TImportFrom1CForm(TComponent* Owner);
  DBF_File * dbfFile;
  int countzap;
  void __fastcall dat(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TImportFrom1CForm *ImportFrom1CForm;
//---------------------------------------------------------------------------
#endif
