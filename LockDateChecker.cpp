//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DataModule.h"
#include "LockDateChecker.h"
#include "FIBDatabase.hpp"
#include "pFIBDatabase.hpp"
#include "FIBQuery.hpp"
#include "pFIBQuery.hpp"
#include "pFIBErrorHandler.hpp"
#include "FIBDataSet.hpp"
#include "pFIBDataSet.hpp"
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include "pFIBStoredProc.hpp"
#include "AccountEdit.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall LockDateChecker::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall LockDateChecker::LockDateChecker(bool CreateSuspended,bool &termFLG)
        : TThread(CreateSuspended),terminateFLG(termFLG)
{

  terminateFLG=false;
  AnsiString led=SaleBookDM->GetConstValue(SaleBookDM->OrganizationID,"LOCK_WORK_DATE");
  if(!led.IsEmpty()) currentLED=StrToInt(led);
  else currentLED=0;
  try
  {
    RQ=new TpFIBQuery(NULL);
  }
  catch(const Exception &exc)
  { RQ=NULL;
    MessageDlg("LockDateChecker::LockDateChecker - Ошибка создания объекта TpFIBQuery\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  }
  RQ->Database=SaleBookDM->DataBase;
  RQ->Transaction=SaleBookDM->ReadTransaction;
  RQ->Options << qoStartTransaction << qoAutoCommit;
}
//---------------------------------------------------------------------------
void __fastcall LockDateChecker::Execute()
{
  do
  { if(!Terminated)
    { Synchronize(checkLED);
      for(int i=0; i<25; i++)
      { if(Terminated==true) break;
        Sleep(200);
      }
    }
  }while(!Terminated);
  if(RQ!=NULL) delete RQ;
  terminateFLG=true;
}
//---------------------------------------------------------------------------
void __fastcall LockDateChecker::checkLED(void)
{
AnsiString d;
AnsiString sql;
int st;


  if(RQ==NULL) return;
  sql="select CONST_VALUE from CONST_VALUES";
  sql+=" where CONST_ID=(select ID from CONSTANT where IDENTIFIER='LOCK_WORK_DATE')";
  RQ->Close();
  RQ->SQL->Clear();
  RQ->SQL->Add(sql);
  try
  {
    RQ->ExecQuery();
  }
  catch(...)
  {
    return;
  }
  if(RQ->RecordCount==0) return;
  d=RQ->FieldByName("CONST_VALUE")->AsString;
  st=d.ToInt();
  if(d!=currentLED)
  {
    currentLED=st;
  }
  if (st == 0) SaleBookDM->enableEdit=true; else SaleBookDM->enableEdit=false; 

  if (st > 0) SaleBookDM->updateSBInterface(st);
}
//---------------------------------------------------------------------------
