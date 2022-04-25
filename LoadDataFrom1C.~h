//---------------------------------------------------------------------------

#ifndef LoadDataFrom1CH
#define LoadDataFrom1CH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "JvComponent.hpp"
#include "JvExControls.hpp"
#include "JvExMask.hpp"
#include "JvExStdCtrls.hpp"
#include "JvMemo.hpp"
#include "JvToolEdit.hpp"
#include "JvXPButtons.hpp"
#include "JvXPCore.hpp"
#include "Placemnt.hpp"
#include "SmrtPanel.h"
#include <ADODB.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include "FIBDatabase.hpp"
#include "pFIBDatabase.hpp"
#include "JvSpeedButton.hpp"
#include "DBF_File.h"
#include <ImgList.hpp>
#include <Buttons.hpp>
#include "FIBQuery.hpp"
#include "pFIBQuery.hpp"
//---------------------------------------------------------------------------
class TLoadDataFrom1CForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TJvXPButton *CancelButton;
        TJvXPButton *LoadButton;
        TSmrtPanel *SmrtPanel1;
        TFormStorage *FormStorage;
        TJvXPButton *PrintButton;
        TPanel *BottomPanel;
        TPanel *TopPanel;
        TLabel *Label1;
        TJvFilenameEdit *FilenameEdit;
        TPanel *RightPanel;
        TLabel *Label6;
        TRichEdit *Memo;
        TpFIBQuery *TQ;
        TpFIBTransaction *WT;
        TpFIBQuery *TempQuery;
        TpFIBTransaction *QT;
        void __fastcall CancelButtonClick(TObject *Sender);
        void __fastcall FilenameEditAfterDialog(TObject *Sender,
          AnsiString &Name, bool &Action);
        void __fastcall LoadButtonClick(TObject *Sender);
        void __fastcall PrintButtonClick(TObject *Sender);
private:	// User declarations
  AnsiString iniFileName;
  AnsiString workDir;
  AnsiString FileName;
public:		// User declarations
  __fastcall TLoadDataFrom1CForm(TComponent* Owner);
  DBF_File * dbfFile;
  int countzap;
};
//---------------------------------------------------------------------------
//extern PACKAGE TLoadDataFrom1CForm *LoadDataFrom1CForm;
//---------------------------------------------------------------------------
#endif
