//---------------------------------------------------------------------------

#ifndef RestoreBaseH
#define RestoreBaseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Placemnt.hpp"
//#include "IB_Services.hpp"
#include "ToolEdit.hpp"
#include "ZipBuilder.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include "RxRichEd.hpp"
#include "JvComponent.hpp"
#include "JvExControls.hpp"
#include "JvNavigationPane.hpp"
#include "JvWaitingGradient.hpp"
#include "JvExStdCtrls.hpp"
#include "JvMemo.hpp"
#include <ComCtrls.hpp>
#include <IBServices.hpp>
#include "JvProgressBar.hpp"
#include "JvExComCtrls.hpp"
#include "JvWaitingProgress.hpp"
//---------------------------------------------------------------------------
class TRestoreBaseForm : public TForm
{
__published:	// IDE-managed Components
        TFormStorage *FormStorage1;
        TZipBuilder *ZipBuilder;
        TJvWaitingProgress *JvWaitingProgress1;
        TPanel *Panel1;
        TLabel *Label1;
        TLabel *Label3;
        TLabel *Label5;
        TLabel *Label6;
        TFilenameEdit *zipFilenameEdit;
        TCheckBox *CheckBox1;
        TFilenameEdit *backupFilenameEdit;
        TBitBtn *RestoreButton;
        TBitBtn *ExitButton;
        TDirectoryEdit *dbNetDirectoryEdit;
        TDirectoryEdit *dbCopyDirectoryEdit;
        TRichEdit *RichEdit;
        TIBRestoreService *RestoreService;
        TJvProgressBar *ProgressBar;
        TJvWaitingGradient *WaitingGradient;
        TJvNavPanelHeader *Label2;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall RestoreButtonClick(TObject *Sender);
        void __fastcall ExitButtonClick(TObject *Sender);
private:	// User declarations
  AnsiString server, dbFullName;
public:		// User declarations
        __fastcall TRestoreBaseForm(TComponent* Owner);
//        AnsiString ZipFileName, BackUpFileName, DataBaseFileName, Server, DBNetName;
//        AnsiString BackUpFileName, ZipFileName, DBNetName;
};
//---------------------------------------------------------------------------
//extern PACKAGE TRestoreBaseForm *RestoreBaseForm;
//---------------------------------------------------------------------------
#endif
