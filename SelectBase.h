//---------------------------------------------------------------------------

#ifndef SelectBaseH
#define SelectBaseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "JvAnimTitle.hpp"
#include "JvComponent.hpp"
#include "SmrtPanel.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "Placemnt.hpp"
#include "FIBDatabase.hpp"
#include "pFIBDatabase.hpp"
#include "AdjustConnection.h"
#include "JvExControls.hpp"
#include "JvNavigationPane.hpp"
#include "JvXPButtons.hpp"
#include "JvXPCore.hpp"
//---------------------------------------------------------------------------
class TSelectBaseForm : public TForm
{
__published:	// IDE-managed Components
        TJvAnimTitle *JvAnimTitle1;
        TPanel *Panel1;
        TPanel *Panel4;
        TImage *Image1;
        TSmrtPanel *SmrtPanel1;
        TListBox *DBNamesBox;
        TLabel *Label4;
        TFormStorage *FormStorage1;
        TpFIBDatabase *DataBase;
        TJvNavPanelHeader *Header;
        TJvNavPanelHeader *Label3;
        TJvXPButton *ConnectButton;
        TJvXPButton *AddButton;
        TJvXPButton *EditButton;
        TJvXPButton *DelButton;
        TLabel *Label1;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall DBNamesBoxClick(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall ConnectButtonClick(TObject *Sender);
        void __fastcall AddButtonClick(TObject *Sender);
        void __fastcall EditButtonClick(TObject *Sender);
        void __fastcall DelButtonClick(TObject *Sender);
private:	// User declarations
        AnsiString WorkDir;
        int DBIndex;
        bool EditFLG;
public:		// User declarations
        __fastcall TSelectBaseForm(TComponent* Owner);
        void __fastcall LoadDBNamesList(void);
        bool __fastcall SaveDBNameToList(bool AddFLG);
        TStringList *DBNames;
        TAdjustConnectionForm *ACF;
};
//---------------------------------------------------------------------------
//extern PACKAGE TSelectBaseForm *SBF;
//---------------------------------------------------------------------------
#endif
