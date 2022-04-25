//---------------------------------------------------------------------------

#ifndef DataModuleH
#define DataModuleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "FIBDatabase.hpp"
#include "pFIBDatabase.hpp"
#include "pFIBErrorHandler.hpp"
#include "FIBDataSet.hpp"
#include "pFIBDataSet.hpp"
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include "pFIBStoredProc.hpp"
#include "FIBQuery.hpp"
#include "pFIBQuery.hpp"
#include <NMsmtp.hpp>
#include <Psock.hpp>
#include "SMTPMessage.h"
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdMessageClient.hpp>
#include <IdSMTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdMessage.hpp>

//---------------------------------------------------------------------------
enum orders { ByDate, ByNumber, ByCustomerID, ByNone};
enum filters { ByNum, ByCustomer, ByUser, ByNumCust, ByNumUser, ByCustUser, ByAll, ByOps, ByDost, ByPost, ByPost1, ByPost2, ByPost3, ByPost4, ByOpl, None};
enum actions {AddRecordToAccountsTable,EditRecordFromAccountsTable,DelRecordFromAccountsTable,
              AddRecordToInvoicesTable,EditRecordFromInvoicesTable,DelRecordFromInvoicesTable,
              AddRecordToSaleBook,EditRecordFromSaleBook,DelRecordFromSaleBook,
              BackUpBase, RestoreBase,
              InputUserToApplication, OutputUserFromApplication,
              MoveCountFromOldApplication, MoveInvoiceFromOldApplication, MoveSBRecordFromOldApplication,AddImport,AddExport,SendNotice,SendLetter
             };
//---------------------------------------------------------------------------
class TSaleBookDM : public TDataModule
{
__published:	// IDE-managed Components
        TpFIBDatabase *DataBase;
        TpFIBTransaction *ReadTransaction;
        TpFIBTransaction *WriteTransaction;
        TpFIBQuery *TempQuery;
        TpFibErrorHandler *pFibErrorHandler1;
        TpFIBDataSet *EIDS;
        TTimer *UsersMonitorTimer;
        TpFIBQuery *UMQuery;
        TpFIBDataSet *ConstantDS;
        TpFIBStoredProc *ConstProc;
        TpFIBTransaction *ConstTransaction;
        TpFIBQuery *TQ;
        TpFIBTransaction *TT;
        TpFIBQuery *WQ;
        TpFIBTransaction *UMT;
        TpFIBTransaction *EIRT;
        TpFIBTransaction *EIWT;
        TpFIBDataSet *NDOST;
        TpFIBDataSet *NOMDS;
        TFIBIntegerField *NOMDSCODP;
        TFIBStringField *NOMDSEI;
        TpFIBDataSet *SGBT;
        TpFIBDataSet *RDS;
        TpFIBDataSet *TDS;
        TFIBSmallIntField *EIDSID;
        TFIBStringField *EIDSDESCRIPTION;
        TpFIBDataSet *DNI;
        TFIBSmallIntField *DNIIDAY;
        TFIBStringField *DNIDAYS;
        void __fastcall DataModuleDestroy(TObject *Sender);
        void __fastcall pFibErrorHandler1FIBErrorEvent(TObject *Sender,
          EFIBError *ErrorValue, TKindIBError KindIBError, bool &DoRaise);
        void __fastcall DataBaseLostConnect(TFIBDatabase *Database,
          EFIBError *E, TOnLostConnectActions &Actions);
        void __fastcall UsersMonitorTimerTimer(TObject *Sender);
        void __fastcall DataBaseErrorRestoreConnect(TFIBDatabase *Database,
          EFIBError *E, TOnLostConnectActions &Actions);
        void __fastcall DataBaseAfterRestoreConnect(
          TFIBDatabase *Database);
private:	// User declarations
  AnsiString BBConnectString;
  class LockDateChecker *LDC;   //процесс, контролирующий значение параметра "Статус запрета работы"
  bool __fastcall terminateLDC; //флаг завершения процесса LDC
  void __fastcall inspectConstantsTable(void);
  void __fastcall inspectConstant(AnsiString identifier,AnsiString title,int type,int kind);
public:		// User declarations
        __fastcall TSaleBookDM(TComponent* Owner);
        AnsiString InitString, Alias, Server, DB_Name, Base_Name,DB_Log,DB_Pass;
        unsigned short UserID;
        AnsiString UserName, UserRole, NetName, UserIndex , UserIndexAll;
        bool __fastcall ConnectToDataBase(void);
        void __fastcall DisConnectDataBase(void);
        void __fastcall updateSBInterface(int status);
        TSMTPMessageForm *MF;
        int AttemptRest;
        int OrganizationID, RS_ID;
        TDateTime BeginDate;
        AnsiString PrgVer,DateVer;
        unsigned short dvip,yvip,mvip;
        unsigned short __fastcall LastDay(unsigned short y, unsigned short m);
        AnsiString __fastcall GetConstValue(int OrgID, AnsiString Identifier, TDateTime CDate, TDateTime &Constdate, int &Reference);
        AnsiString __fastcall GetConstValue(int OrgID, AnsiString Identifier, TDateTime CDate);
        TDateTime __fastcall GetConstDate(int OrgID, AnsiString Identifier, TDateTime CDate);
        AnsiString __fastcall GetConstValue(int OrgID, AnsiString Identifier);
        int __fastcall SetConstValue(int OrgID, AnsiString Identifier, AnsiString value);
        AnsiString __fastcall GetConstValue(int OrgID, int ConstID, TDateTime CDate, TDateTime &Constdate, int &Reference);
        bool __fastcall AddRecordToActionsJournal(actions ActionType, AnsiString ActionText, TFIBTransaction *Transaction);
        unsigned short RestoreCalculator;
        bool enableEdit;
};
//---------------------------------------------------------------------------
extern PACKAGE TSaleBookDM *SaleBookDM;
//---------------------------------------------------------------------------
#endif
