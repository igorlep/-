//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Placemnt.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *MainStatusBar;
        TMainMenu *MainMenu;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N4;
        TMenuItem *N5;
        TMenuItem *N7;
        TMenuItem *N9;
        TMenuItem *N10;
        TMenuItem *N15;
        TMenuItem *N16;
        TMenuItem *N18;
        TMenuItem *N19;
        TMenuItem *N20;
        TPanel *Panel1;
        TSpeedButton *ExitButton;
        TSpeedButton *AccountsJournalButton;
        TMenuItem *N13;
        TMenuItem *N21;
        TMenuItem *N22;
        TMenuItem *N23;
        TMenuItem *N24;
        TMenuItem *N28;
        TFormStorage *MainFormStorage;
        TMenuItem *N110;
        TSpeedButton *ImportDocumentsJournalButton;
        TMenuItem *N25;
        TMenuItem *N29;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton3;
        TSpeedButton *SpeedButton4;
        TMenuItem *N6;
        TMenuItem *N8;
        TMenuItem *N11;
        TMenuItem *N12;
        TMenuItem *N14;
        TSpeedButton *SpeedButton5;
        TMenuItem *N17;
        TMenuItem *N3;
        TTimer *messagesTimer;
        TMenuItem *N26;
        TMenuItem *N27;
        TMenuItem *N30;
        TMenuItem *N31;
        TMenuItem *N32;
        TMenuItem *N33;
        void __fastcall N7Click(TObject *Sender);
        void __fastcall N9Click(TObject *Sender);
        void __fastcall N19Click(TObject *Sender);
        void __fastcall N18Click(TObject *Sender);
        void __fastcall N10Click(TObject *Sender);
        void __fastcall N20Click(TObject *Sender);
        void __fastcall ExitButtonClick(TObject *Sender);
        void __fastcall N15Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall N16Click(TObject *Sender);
        void __fastcall N21Click(TObject *Sender);
        void __fastcall N22Click(TObject *Sender);
        void __fastcall N23Click(TObject *Sender);
        void __fastcall N24Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall N110Click(TObject *Sender);
        void __fastcall N14Click(TObject *Sender);
        void __fastcall SpeedButton5Click(TObject *Sender);
        void __fastcall N17Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall N8Click(TObject *Sender);
        void __fastcall N3Click(TObject *Sender);
        void __fastcall messagesTimerTimer(TObject *Sender);
        void __fastcall N26Click(TObject *Sender);
        void __fastcall N30Click(TObject *Sender);
        void __fastcall N31Click(TObject *Sender);
        void __fastcall N32Click(TObject *Sender);
        void __fastcall N33Click(TObject *Sender);
private:	// User declarations
  int fontDPI;
  AnsiString iniFileName;
public:		// User declarations
  AnsiString WorkDir;
  __fastcall TMainForm(TComponent* Owner);
  void __fastcall SetButtons(void);
  void __fastcall SetMainStatusBar(AnsiString lockDate);
  int __fastcall getFontDPI(void){ return fontDPI;}
  AnsiString __fastcall getIniFileName(void){ return iniFileName;}
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
