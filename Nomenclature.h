//---------------------------------------------------------------------------

#ifndef NomenclatureH
#define NomenclatureH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <ImgList.hpp>
#include <DBCtrls.hpp>
#include <ActnList.hpp>
//#include <DB.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "DBGridEh.hpp"
#include "Placemnt.hpp"
#include "SmrtPanel.h"
#include "FIBQuery.hpp"
#include "pFIBQuery.hpp"
#include "FIBDataSet.hpp"
#include "pFIBDataSet.hpp"
#include "FIBDatabase.hpp"
#include "pFIBDatabase.hpp"
#include "pFIBStoredProc.hpp"
#include "EditNomenclature.h"
//---------------------------------------------------------------------------
class TNomenclatureForm : public TForm
{
__published:	// IDE-managed Components
        TSplitter *Splitter2;
        TDataSource *DataSource;
        TMemo *Memo1;
        TActionList *ActionList1;
        TAction *SelRec;
        TImageList *ImageList2;
        TAction *EditRec;
        TSplitter *Splitter1;
        TAction *Cancel;
        TFormStorage *FormStorage1;
        TSmrtPanel *SmrtPanel1;
        TSmrtPanel *SmrtPanel2;
        TSpeedButton *FAddChButton;
        TSpeedButton *FSubButton;
        TTreeView *TreeView1;
        TSmrtPanel *SmrtPanel3;
        TPanel *Panel1;
        TSpeedButton *CancelButton;
        TSpeedButton *SelectButton;
        TSpeedButton *NewButton;
        TSpeedButton *DelButton;
        TSpeedButton *EditButton;
        TSpeedButton *SortButton;
        TDBGridEh *DBGrid;
        TpFIBQuery *TempQuery;
        TpFIBTransaction *WriteTransaction;
        TpFIBStoredProc *StoredProc;
        TpFIBTransaction *ReadTransaction;
        TpFIBDataSet *SQuery;
        TStaticText *StaticText1;
        TpFIBDataSet *DataSet;
        TpFIBTransaction *RT;
        TpFIBQuery *TempQuery1;
        TFIBIntegerField *DataSetID;
        TFIBIntegerField *DataSetFILE_ID;
        TFIBSmallIntField *DataSetREC_TYPE;
        TFIBStringField *DataSetDESCRIPTION;
        TFIBStringField *DataSetEI;
        TFIBIntegerField *DataSetCODP;
        TFIBIntegerField *DataSetINDEXOPS;
        void __fastcall DataSourceDataChange(TObject *Sender,
          TField *Field);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall TreeView1DblClick(TObject *Sender);
        void __fastcall TreeView1Edited(TObject *Sender, TTreeNode *Node,
          AnsiString &S);
//        void __fastcall FAddButtonClick(TObject *Sender);
        void __fastcall FSubButtonClick(TObject *Sender);
        void __fastcall CancelButtonClick(TObject *Sender);
        void __fastcall NewButtonClick(TObject *Sender);
        void __fastcall EditRecExecute(TObject *Sender);
        void __fastcall DelButtonClick(TObject *Sender);
        void __fastcall TreeView1Change(TObject *Sender, TTreeNode *Node);
        void __fastcall FAddChButtonClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall TreeView1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall SortButtonClick(TObject *Sender);
        void __fastcall DBGridDblClick(TObject *Sender);
        void __fastcall DBGridKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall SelRecExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
        TStringList *FieldNames;
        AnsiString RefEditCaption;
        __fastcall TNomenclatureForm(TComponent* Owner);
        bool __fastcall CreateEditForm(void);
        void __fastcall CreateNode(TTreeNode *Node, int FileID, int Level);
        void __fastcall SetButtons(void);
        void __fastcall SetMemo(void);
        void __fastcall LoadDataSet(void);
//        bool RenFLG;
//        int recno,
        int id,sortind;
//        TpFIBDataSet *DataSet;
        TEditNomenclatuteForm *ERF;
};
//---------------------------------------------------------------------------
extern PACKAGE TNomenclatureForm *NomenclatureForm;
//---------------------------------------------------------------------------
#endif
