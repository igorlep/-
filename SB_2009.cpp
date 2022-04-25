//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SelectBase.h"
#include "Entry.h"
#include "DataModule.h"
#include "Nomenclature.h"

#define MUTEX_NAME "SB_2009"
//---------------------------------------------------------------------------
USEFORM("Main.cpp", MainForm);
USEFORM("SelectBase.cpp", SelectBaseForm);
USEFORM("AdjustConnection.cpp", AdjustConnectionForm);
USEFORM("Entry.cpp", EntryForm);
USEFORM("DataModule.cpp", SaleBookDM); /* TDataModule: File Type */
USEFORM("Nomenclature.cpp", NomenclatureForm);
USEFORM("RefSort.cpp", RefSortForm);
USEFORM("EditNomenclature.cpp", EditNomenclatuteForm);
USEFORM("EI.cpp", EIForm);
USEFORM("Organizations.cpp", OrganizationsForm);
USEFORM("OrganizationSelect.cpp", OrganizationSelectForm);
USEFORM("Users.cpp", UsersForm);
USEFORM("ChangePass.cpp", ChangePassForm);
USEFORM("ActionsJournal.cpp", ActionsJournalForm);
USEFORM("AccauntsJournal.cpp", AccountsJournalForm);
USEFORM("AccountEdit.cpp", AccountEditForm);
USEFORM("SelectFilter.cpp", SelectFilterForm);
USEFORM("PrntData.cpp", PrntDataForm);
USEFORM("ImportFrom1C.cpp", ImportFrom1CForm);
USEFORM("SelectRecords.cpp", SelectRecordsForm);
USEFORM("ExportTo1C.cpp", ExportTo1CForm);
USEFORM("UsersMonitor.cpp", UsersMonitorForm);
USEFORM("BackUpBase.cpp", BackUpBaseForm);
USEFORM("HelpAbout.cpp", HelpAboutForm);
USEFORM("RestoreBase.cpp", RestoreBaseForm);
USEFORM("SimpleConstantEdit.cpp", SimpleConstantEditForm);
USEFORM("ImportDocumentsJournal.cpp", ImportDocumentsJournalForm);
USEFORM("ConstHistoryEdit.cpp", ConstHistoryEditForm);
USEFORM("BrowseF.cpp", BrowseForm);
USEFORM("ActsList.cpp", ActsListForm);
USEFORM("LoadDataFrom1C.cpp", LoadDataFrom1CForm);
USEFORM("SelectPeriodAF.cpp", SelectPeriodForm);
USEFORM("SendMessage.cpp", SendMessForm);
USEFORM("MoveRecords.cpp", MoveRecordsForm);
USEFORM("IndexOPS.cpp", FormIndex);
USEFORM("UnitProv.cpp", FormProv);
USEFORM("SelectPeriodBF.cpp", SelectPeriodBrowseForm);
USEFORM("SMTPMessage.cpp", SMTPMessageForm);
USEFORM("EID.cpp", EIDForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
TStringList *DBN;
int DBI;
AnsiString WD;
AnsiString InitString;

  WD=ExtractFilePath(Application->ExeName);
  DBN=new TStringList;
  TIniFile *ini = new TIniFile(WD+"SB_2009.ini");
  DBI=ini->ReadInteger("EntryParams","DBIndex",0);
  DBN->Clear();
  ini->ReadSectionValues("DBAliases",DBN);
  delete ini;


  HANDLE hMutex=0;
  try
  { //Проверяем, не запущено ли уже приложение?
    hMutex = OpenMutex( MUTEX_ALL_ACCESS, FALSE, MUTEX_NAME);
    if(hMutex)
    { MessageDlg("Программа \"Инспектор\" уже запущена",mtWarning,TMsgDlgButtons() << mbOK,0);
      return 0;
    }
    hMutex = CreateMutex(NULL, false, "SB_2009");

    Application->Initialize();
    Application->Title = "\"Инспектор ver 4 от 20 мая 2021 г.\"";
    //Выбор базы данных
  if(DBN->Count > 1)
  {
    TSelectBaseForm *SBF;
    try
    {
      SBF=new TSelectBaseForm(static_cast<void*>(NULL));
    }
    catch(const Exception &exc)
    { MessageDlg("Ошибка создания формы SBF\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      if(hMutex)
      { ReleaseMutex(hMutex);
        CloseHandle(hMutex);
      }
      return 0;
    }

    if(SBF->ShowModal()!=mrOk)
    { delete SBF;
      if(hMutex)
      { ReleaseMutex(hMutex);
        CloseHandle(hMutex);
      }
      return 0;
    }
    InitString=SBF->DBNames->Strings[SBF->DBNamesBox->ItemIndex];
    delete SBF;
  }
  else
  {
    InitString=DBN->Strings[0];
  }

    TEntryForm *Entry;
    try
    {
      Entry=new TEntryForm(static_cast<void*>(NULL),InitString);
    }
    catch(const Exception &exc)
    {
      MessageDlg("Ошибка создания формы Enrty\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return 0;
    }
    if(Entry->ShowModal()==mrOk)
    {
    Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TSaleBookDM), &SaleBookDM);
                 AnsiString str;
      str="Вход пользователя в ИС Инспектор";
      SaleBookDM->InitString=InitString;

      SaleBookDM->Alias=InitString.SubString(0,InitString.Pos("=")-1);
      SaleBookDM->Server=InitString.SubString(InitString.Pos("=")+1,InitString.Pos(":")-InitString.Pos("="));
      SaleBookDM->DB_Name=InitString.SubString(InitString.Pos(":")+1,InitString.Pos(",")-InitString.Pos(":")-1);
      int p=InitString.Length(), p1=p;
      while(p>1 && InitString[p]!='\\' && InitString[p]!='/') --p;
      if(InitString[p]=='\\' || InitString[p]=='/') p++;
      SaleBookDM->Base_Name=InitString.SubString(p,p1-p+1);
      SaleBookDM->UserID=StrToInt(Entry->UsersID->Strings[Entry->UsersBox->ItemIndex]);
      int p3=InitString.Pos(",");

     AnsiString DBLogPass=InitString.SubString(p3+1,InitString.Length());
     int p4=DBLogPass.Pos(",");
     SaleBookDM->DB_Log=DBLogPass.SubString(1,p4-1);
     SaleBookDM->DB_Pass=DBLogPass.SubString(p4+1,DBLogPass.Length());

      SaleBookDM->UserRole=Entry->UsersRoles->Strings[Entry->UsersBox->ItemIndex];
      SaleBookDM->NetName=Entry->NetName;
      delete Entry;
      if(!SaleBookDM->ConnectToDataBase())
      { if(hMutex)
        { ReleaseMutex(hMutex);
          CloseHandle(hMutex);
        }
        return 0;
      }

      SaleBookDM->WriteTransaction->StartTransaction();
      SaleBookDM->AddRecordToActionsJournal(InputUserToApplication,str,SaleBookDM->WriteTransaction);
      SaleBookDM->WriteTransaction->Commit();

      Application->Run();
    }
    else
    { delete Entry;
      if(hMutex)
      { ReleaseMutex(hMutex);
        CloseHandle(hMutex);
      }
      return 0;
    }
  }
  catch (Exception &exception)
  {
    Application->ShowException(&exception);
  }
  catch (...)
  {
    try
    {
      throw Exception("");
    }
    catch (Exception &exception)
    {
      Application->ShowException(&exception);
    }
  }
  if(hMutex)
  { ReleaseMutex(hMutex);
    CloseHandle(hMutex);
  }
  return 0;
}
//---------------------------------------------------------------------------
/*
  HANDLE hMutex=0;
  try
  { //Проверяем, не запущено ли уже приложение?
    hMutex = OpenMutex( MUTEX_ALL_ACCESS, FALSE, MUTEX_NAME);
    if(hMutex)
    { MessageDlg("Программа \"Книга продаж\" уже запущенна",mtWarning,TMsgDlgButtons() << mbOK,0);
      return 0;
    }
    hMutex = CreateMutex(NULL, false, "SB_2009");

    Application->Initialize();
    Application->Title = "\"Книга продаж 2009\"";
    //Выбор базы данных
    TSelectBaseForm *SBF;
    try
    {
      SBF=new TSelectBaseForm(static_cast<void*>(NULL));
    }
    catch(const Exception &exc)
    { MessageDlg("Ошибка создания формы SBF\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      if(hMutex)
      { ReleaseMutex(hMutex);
        CloseHandle(hMutex);
      }
      return 0;
    }

    if(SBF->ShowModal()!=mrOk)
    { delete SBF;
      if(hMutex)
      { ReleaseMutex(hMutex);
        CloseHandle(hMutex);
      }
      return 0;
    }
    AnsiString InitString=SBF->DBNames->Strings[SBF->DBNamesBox->ItemIndex];
    delete SBF;
    TEntryForm *Entry;
    try
    {
      Entry=new TEntryForm(static_cast<void*>(NULL),InitString);
    }
    catch(const Exception &exc)
    {
      MessageDlg("Ошибка создания формы Enrty\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return 0;
    }
    if(Entry->ShowModal()==mrOk)
    { Application->CreateForm(__classid(TMainForm), &MainForm);
      Application->CreateForm(__classid(TSaleBookDM), &SaleBookDM);

      SaleBookDM->InitString=InitString;
      SaleBookDM->Alias=InitString.SubString(0,InitString.Pos("=")-1);
      SaleBookDM->Server=InitString.SubString(InitString.Pos("=")+1,InitString.Pos(":")-InitString.Pos("="));
      SaleBookDM->DB_Name=InitString.SubString(InitString.Pos(":")+1,InitString.Length());
      int p=InitString.Length(), p1=p;
      while(p>1 && InitString[p]!='\\' && InitString[p]!='/') --p;
      if(InitString[p]=='\\' || InitString[p]=='/') p++;
      SaleBookDM->Base_Name=InitString.SubString(p,p1-p+1);

      SaleBookDM->UserID=StrToInt(Entry->UsersID->Strings[Entry->UsersBox->ItemIndex]);
      SaleBookDM->UserRole=Entry->UsersRoles->Strings[Entry->UsersBox->ItemIndex];
      SaleBookDM->NetName=Entry->NetName;
      delete Entry;
      if(!SaleBookDM->ConnectToDataBase())
      { if(hMutex)
        { ReleaseMutex(hMutex);
          CloseHandle(hMutex);
        }
        return 0;
      }
      //Инициируем справочники
      Application->CreateForm(__classid(TContractorsForm), &ContractorsForm);
      ContractorsForm->LoadDataSet();
      Application->CreateForm(__classid(TNomenclatureForm), &NomenclatureForm);
      NomenclatureForm->LoadDataSet();
      Application->CreateForm(__classid(TNDSForm), &NDSForm);
      NDSForm->LoadDataSet();
      //Фиксирем действие в журнале событий ACTIONS_JOURNAL
      AnsiString str;
      str="Вход пользователя в программу";
      SaleBookDM->WriteTransaction->StartTransaction();
      SaleBookDM->AddRecordToActionsJournal(InputUserToApplication,str,SaleBookDM->WriteTransaction);
      SaleBookDM->WriteTransaction->Commit();
      Application->Run();
    }
    else
    { delete Entry;
      if(hMutex)
      { ReleaseMutex(hMutex);
        CloseHandle(hMutex);
      }
      return 0;
    }
  }
  catch (Exception &exception)
  {
    Application->ShowException(&exception);
  }
  catch (...)
  {
    try
    {
      throw Exception("");
    }
    catch (Exception &exception)
    {
      Application->ShowException(&exception);
    }
  }
  if(hMutex)
  { ReleaseMutex(hMutex);
    CloseHandle(hMutex);
  }
  return 0;
*/
