//---------------------------------------------------------------------------

#ifndef BackUpBaseH
#define BackUpBaseH
//---------------------------------------------------------------------------
#include "RxRichEd.hpp"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Placemnt.hpp"
#include "ToolEdit.hpp"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <ComCtrls.hpp>
#include "ZipBuilder.h"
#include "JvComponent.hpp"
#include "JvExControls.hpp"
#include "JvNavigationPane.hpp"
#include "JvExComCtrls.hpp"
#include "JvProgressBar.hpp"
#include <IBServices.hpp>
#include "JvWaitingGradient.hpp"
//---------------------------------------------------------------------------
class TBackUpBaseForm : public TForm
{
__published:	// IDE-managed Components
        TFormStorage *FormStorage1;
        TPanel *Panel1;
        TCheckBox *CheckBox1;
        TZipBuilder *ZipBuilder;
        TBitBtn *ArchButton;
        TBitBtn *ExitButton;
        TLabel *Label3;
        TFilenameEdit *ZipFilenameEdit;
        TLabel *Label4;
        TDirectoryEdit *BackUpDirEdit;
        TJvNavPanelHeader *Label2;
        TLabel *Label5;
        TFilenameEdit *BackUpFilenameEdit;
        TRichEdit *RichEdit1;
        TJvProgressBar *ProgressBar;
        TIBBackupService *BackupService;
        TJvWaitingGradient *WaitingGradient;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ArchButtonClick(TObject *Sender);
        void __fastcall ExitButtonClick(TObject *Sender);
private:	// User declarations
        AnsiString server;
public:		// User declarations
        __fastcall TBackUpBaseForm(TComponent* Owner);
        void __fastcall ActionsJournalClear(unsigned int id);
};
//---------------------------------------------------------------------------
//extern PACKAGE TBackUpBaseForm *BackUpBaseForm;
//---------------------------------------------------------------------------
#endif
