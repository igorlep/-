//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AccountEdit.h"
#include "Main.h"
#include "LockDateChecker.h"
#include "DataModule.h"
#include "AccauntsJournal.h"
//#include "SMTPMessage.h"

//#include "AccountEdit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FIBDatabase"
#pragma link "pFIBDatabase"
#pragma link "pFIBErrorHandler"
#pragma link "FIBDataSet"
#pragma link "pFIBDataSet"
#pragma link "pFIBStoredProc"
#pragma link "pFIBQuery"
#pragma link "FIBQuery"
#pragma resource "*.dfm"
TSaleBookDM *SaleBookDM;
//---------------------------------------------------------------------------
__fastcall TSaleBookDM::TSaleBookDM(TComponent* Owner)
        : TDataModule(Owner)
{
//  AttemptRest=0;
  PrgVer="5";
  DateVer="16.06.2021";
  enableEdit=true;
  TIniFile *ini=new TIniFile(MainForm->WorkDir+"SB_2009.ini");
  OrganizationID=ini->ReadInteger("EntryParams", "OrganizationID",0);
//  RS_ID=ini->ReadInteger("EntryParams", "RS_ID",0);
//  BBConnectString=ini->ReadString("EntryParams","BBConnectString","");
  delete ini;
}
//---------------------------------------------------------------------------
bool __fastcall TSaleBookDM::ConnectToDataBase(void)
{
AnsiString sql;
AnsiString IndOps;
AnsiString IndexOps;
int i=1;
int KolOps=0;
int k=0;


  DisConnectDataBase();

  if(DataBase!=NULL)
  {
  DataBase->AliasName=Alias;
  DataBase->DBName=Server+DB_Name;
  DataBase->ConnectParams->UserName=DB_Log;
  DataBase->ConnectParams->Password=DB_Pass;
  DataBase->ConnectParams->CharSet="WIN1251";
  DataBase->SQLDialect=3;
  }

  try
  {
    DataBase->Connected=true;
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка подключения к базе - "+DataBase->DBName+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return false;
  }

  //Регистрируем пользователя в таблице USERS_MONITOR, если он еще не зарегистрирован
  TempQuery->Close();
  TempQuery->SQL->Clear();
  sql="select * from USERS_MONITOR where USER_ID = "+IntToStr(UserID);
  TempQuery->SQL->Add(sql);
  try
  {
    TempQuery->ExecQuery();
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return false;
  }
  if(TempQuery->RecordCount == 0)
  {
    WQ->Close();
    WQ->SQL->Clear();
    sql="insert into USERS_MONITOR (USER_ID,USER_NAME) select ID,LOGIN from USERS where ID = "+IntToStr(UserID);
    WQ->SQL->Add(sql);
    WQ->Transaction->StartTransaction();
    try
    {
      WQ->ExecQuery();
    }
    catch(const Exception &exc)
    { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      WQ->Transaction->Rollback();
      return false;
    }
    WQ->Close();
    WQ->SQL->Clear();
    sql="update USERS_MONITOR set IN_DATE = '"+Date().DateString()+"',IN_TIME = '"+Time().TimeString()+"',";
    sql+="LAST_DATE = '"+Date().DateString()+"',LAST_TIME = '"+Time().TimeString()+"',";
    sql+="NET_NAME = '"+NetName+"'";
    sql+=" where USER_ID = "+IntToStr(UserID);
    WQ->SQL->Add(sql);
    try
    {
      WQ->ExecQuery();
    }
    catch(const Exception &exc)
    { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      WQ->Transaction->Rollback();
      return false;
    }
    WQ->Transaction->Commit();
  }

  TempQuery->Close();
  TempQuery->SQL->Clear();
  sql="select * from USERS where ID="+IntToStr(UserID);
  TempQuery->SQL->Add(sql);
  try
  {
    TempQuery->ExecQuery();
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return false;
  }
  UserName=TempQuery->FieldByName("LOGIN")->AsString;
  UserRole=TempQuery->FieldByName("USER_ROLE")->AsString;
  UserIndex=TempQuery->FieldByName("U_INDEX")->AsString;

  IndOps=UserIndex.Trim();
  k=0;
  int cur=0, beg=IndOps.Pos(",");
  IndexOps="'";
  if (beg>0)
  {
  while(beg)
  {
    AnsiString S1=IndOps.SubString(cur,cur+beg-1);
    AnsiString S2="";
    if (S1.Length()==1) S2="63000"+S1.Trim();
    if (S1.Length()==2) S2="6300"+S1.Trim();
    if (S1.Length()==3) S2="630"+S1.Trim();
    IndexOps=IndexOps+S2.Trim()+"','";

    cur=beg+1;
    AnsiString S3=IndOps.SubString(cur,IndOps.Length());
    k++;
    IndOps=S3;
    cur=0;
    beg=IndOps.Pos(",");
    if (beg==0){
    AnsiString S4="";
    if (S3.Length()==1) S4="63000"+S3.Trim();
    if (S3.Length()==2) S4="6300"+S3.Trim();
    if (S3.Length()==3) S4="630"+S3.Trim();
    IndexOps=IndexOps+S4.Trim()+"'";;
   }
  }
  }
  else
  {
  KolOps=1;
  AnsiString S5="";
  if (IndOps.Length()==1) S5="63000"+IndOps.Trim();
  if (IndOps.Length()==2) S5="6300"+IndOps.Trim();
  if (IndOps.Length()==3) S5="630"+IndOps.Trim();
  IndexOps=IndexOps+S5.Trim()+"'";;
  }

  UserIndexAll=IndexOps.Trim();

  TempQuery->Close();
  TempQuery->SQL->Clear();
  sql="select count(ID) as COUNT_ID from ORGANIZATIONS";
  TempQuery->SQL->Add(sql);
  try
  {
    TempQuery->ExecQuery();
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return false;
  }
  if(TempQuery->RecordCount==0)
  {
    MessageDlg("Внимание! Программа обнаружила, что список организаций пуст.\nСейчас в этот список будет добавлена пустая запись.\nПосле запуска программы откройте справочник организаций и отредактируйте сделанную запись.",mtWarning,TMsgDlgButtons() << mbOK,0);
    unsigned short y,m,d;
    TDateTime dt=Date();
    dt.DecodeDate(&y,&m,&d); d=1;
    dt=TDateTime(y,m,d);
    WQ->Close();
    WQ->SQL->Clear();
    sql="insert into ORGANIZATIONS (ID,NAME,BEGIN_DATE) values(GEN_ID(GEN_ORGANIZATIONS_ID,1),'Новая организация','"+dt.DateString()+"')";
    WQ->SQL->Add(sql);
    WQ->Transaction->StartTransaction();
    try
    {
      WQ->ExecQuery();
    }
    catch(const Exception &exc)
    { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      WQ->Transaction->Rollback();
      return false;
    }
    WQ->Transaction->Commit();
  }
  if(OrganizationID!=0)
  { TempQuery->Close();
    TempQuery->SQL->Clear();
    sql="select ID from ORGANIZATIONS where ID = "+IntToStr(OrganizationID);
    TempQuery->SQL->Add(sql);
    try
    {
      TempQuery->ExecQuery();
    }
    catch(const Exception &exc)
    { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return false;
    }
    if(TempQuery->RecordCount == 0) OrganizationID=0;
  }
  if(OrganizationID==0)
  { TempQuery->Close();
    TempQuery->SQL->Clear();
    sql="select ID from ORGANIZATIONS";
    TempQuery->SQL->Add(sql);
    try
    {
      TempQuery->ExecQuery();
    }
    catch(const Exception &exc)
    { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return false;
    }
    if(TempQuery->RecordCount!=0) OrganizationID=TempQuery->FieldByName("ID")->AsInteger;
  }
  //  таблица расчетных счетов организации
  if(OrganizationID!=0)
  { TempQuery->Close();
    TempQuery->SQL->Clear();
    sql="select ID from RS_TABLE where ORG_ID="+IntToStr(OrganizationID);
    TempQuery->SQL->Add(sql);
    try
    {
      TempQuery->ExecQuery();
    }
    catch(const Exception &exc)
    { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return false;
    }
    if(TempQuery->RecordCount == 0) RS_ID=0;
    if(RS_ID!=0)
    { TempQuery->Close();
      TempQuery->SQL->Clear();
      sql="select ID from RS_TABLE where ORG_ID="+IntToStr(OrganizationID);
      sql+=" and ID="+IntToStr(RS_ID);
      TempQuery->SQL->Add(sql);
      try
      {
        TempQuery->ExecQuery();
      }
      catch(const Exception &exc)
      { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
        return false;
      }
      if(TempQuery->RecordCount==0)
      { TempQuery->Close();
        TempQuery->SQL->Clear();
        sql="select ID from RS_TABLE where ORG_ID="+IntToStr(OrganizationID);
        TempQuery->SQL->Add(sql);
        try
        {
          TempQuery->ExecQuery();
        }
        catch(const Exception &exc)
        { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
          return false;
        }
        RS_ID=TempQuery->FieldByName("ID")->AsInteger;
      }
    }
  }
  else RS_ID=0;

  //Проверяем таблицу констант
  inspectConstantsTable();
  //Инициируем ConstantDS
  ConstantDS->Close();
  try
  {
    ConstantDS->Open();
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка открытия таблицы CONSTANT\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return false;
  }

  int currentLED;

  AnsiString led=GetConstValue(OrganizationID,"LOCK_WORK_DATE");
  if(!led.IsEmpty()) currentLED=StrToInt(led);
  else currentLED=0;


  //Настройка интерфейса
  //  организация
  if(OrganizationID!=0)
  {
    TempQuery->Close();
    TempQuery->SQL->Clear();
    sql="select * from ORGANIZATIONS where ID = "+IntToStr(OrganizationID);
    TempQuery->SQL->Add(sql);
    try
    {
      TempQuery->ExecQuery();
    }
    catch(const Exception &exc)
    { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return false;
    }
    if(TempQuery->RecordCount > 0)
    {

    if(currentLED==1){
    MainForm->Caption="Инспектор. Версия "+ PrgVer.Trim() + " от " + DateVer.Trim() + " г. " +  TempQuery->FieldByName("NAME")->AsString + " БД закрыта !!!";
    }
    else
    {
    MainForm->Caption="Инспектор. Версия "+ PrgVer.Trim() + " от " + DateVer.Trim() + " г. " +  TempQuery->FieldByName("NAME")->AsString + " БД открыта !!!";
    }
    BeginDate=TempQuery->FieldByName("BEGIN_DATE")->AsDateTime;
    }
  }
  //  наличие подключения
  MainForm->MainStatusBar->Panels->Items[0]->Text="Подключение к базе - есть";
  //  база данных
  MainForm->MainStatusBar->Panels->Items[1]->Text=DataBase->AliasName;
  //  пользователь
  TempQuery->Close();
  TempQuery->SQL->Clear();
  TempQuery->SQL->Add("select LOGIN,U_INDEX, USER_ROLE from USERS where ID = "+IntToStr(UserID));
  try
  {
    TempQuery->ExecQuery();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка открытия таблицы USERS\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return false;
  }
  MainForm->MainStatusBar->Panels->Items[2]->Text=TempQuery->FieldByName("USER_ROLE")->AsString + " - " +TempQuery->FieldByName("LOGIN")->AsString + " ОПС -> " + TempQuery->FieldByName("U_INDEX")->AsString;
  TempQuery->Close();
//  if (UserRole=="Администратор") MainForm->SetMainStatusBar(GetConstValue(OrganizationID,"LOCK_EDIT_DATE"));
  MainForm->SetMainStatusBar(GetConstValue(OrganizationID,"LOCK_EDIT_DATE"));

  //Запускаем таймер монитора пользователей
  UsersMonitorTimer->Enabled=true;

  if(UserRole!="Администратор")
  { //Создаем процесс, контролирующий значение параметра "Статус запрета работы"
    try
    {
      LDC=new LockDateChecker(false,terminateLDC);
    }
    catch(const Exception &exc)
    { MessageDlg("Ошибка создания объекта LockDateChecker\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      LDC=NULL;
    }
  }
  else LDC=NULL;

  return true;
}
//---------------------------------------------------------------------------
void __fastcall TSaleBookDM::DisConnectDataBase(void)
{
  UsersMonitorTimer->Enabled=false;
  MainForm->MainStatusBar->Panels->Items[0]->Text="Подключение к базе - нет";
  MainForm->MainStatusBar->Panels->Items[1]->Text="";
  if(LDC!=NULL)
  { LDC->Terminate();
    while(terminateLDC==false) Sleep(300);
    delete LDC; LDC=NULL;
  }
  if(DataBase->Connected)
  {
    TempQuery->Close();
    TempQuery->SQL->Clear();
    TempQuery->SQL->Add("delete from USERS_MONITOR where USER_ID = "+IntToStr(UserID));
    try
    {
      TempQuery->ExecQuery();
    }
    catch(const Exception &exc)
    {
      MessageDlg("Ошибка удаления записи из таблицы USERS_MONITOR\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }

    if(UserName=="Лепёшкин И.Г.")
    {
    TempQuery->Close();
    TempQuery->SQL->Clear();
    TempQuery->SQL->Add("delete from SENDED_MESSAGES_TABLE ");
    try
    {
      TempQuery->ExecQuery();
    }
    catch(const Exception &exc)
    {
      MessageDlg("Ошибка удаления записи из таблицы USERS_MONITOR\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
    }
    DataBase->Connected=false;

  }
}
//---------------------------------------------------------------------------
void __fastcall TSaleBookDM::DataModuleDestroy(TObject *Sender)
{

  if(DataBase->Connected==true)
  { //Фиксирем действие в журнале событий ACTIONS_JOURNAL
    AnsiString str;
    str="Выход пользователя из ИС";
    WriteTransaction->StartTransaction();
    if(AddRecordToActionsJournal(OutputUserFromApplication,str,SaleBookDM->WriteTransaction)==true)
      WriteTransaction->Commit();
    else
      WriteTransaction->Rollback();
  }
  DisConnectDataBase();
  TIniFile *ini=new TIniFile(MainForm->WorkDir+"SB_2009.ini");
  ini->WriteInteger("EntryParams", "OrganizationID",OrganizationID);
  ini->WriteInteger("EntryParams", "RS_ID",RS_ID);
  ini->WriteString("EntryParams","BBConnectString",BBConnectString);
  delete ini;
}
//---------------------------------------------------------------------------
void __fastcall TSaleBookDM::pFibErrorHandler1FIBErrorEvent(
      TObject *Sender, EFIBError *ErrorValue, TKindIBError KindIBError,
      bool &DoRaise)
{
  if(KindIBError == keLostConnect)
  { DoRaise=false;
    Abort();
  }
}
//---------------------------------------------------------------------------
void __fastcall TSaleBookDM::DataBaseLostConnect(TFIBDatabase *Database,
      EFIBError *E, TOnLostConnectActions &Actions)
{
  UsersMonitorTimer->Enabled=false;
  MainForm->MainStatusBar->Panels->Items[0]->Text="Подключение к базе - нет";
  MessageDlg("Внимание! Соединение с базой - "+DataBase->DBName+" потеряно.\n\
После нажатия кнопки \"Ok\" будет сделана попытка восстановления подключения",mtError,TMsgDlgButtons() << mbOK,0);
  Actions=laWaitRestore;
  RestoreCalculator=0;
}
//---------------------------------------------------------------------------
void __fastcall TSaleBookDM::UsersMonitorTimerTimer(TObject *Sender)
{
AnsiString sql;

  UsersMonitorTimer->Enabled=false;

  TempQuery->Close();
  TempQuery->SQL->Clear();
  sql="select * from USERS_MONITOR where USER_ID = "+IntToStr(UserID);
  TempQuery->SQL->Add(sql);
  TempQuery->ExecQuery();
  if(TempQuery->RecordCount == 0)
  { char nn[120];
    unsigned long size=120;
    GetUserName(nn,&size);
    AnsiString NetName=nn;
    sql="insert into USERS_MONITOR(USER_ID,USER_NAME,NET_NAME,IN_DATE,IN_TIME,LAST_DATE,\
LAST_TIME) values(";
    sql+=IntToStr(UserID)+",";
    sql+="'"+UserName+"',";
    sql+="'"+NetName+"',";
    sql+="'"+Date().DateString()+"',";
    sql+="'"+Time().TimeString()+"',";
    sql+="'"+Date().DateString()+"',";
    sql+="'"+Time().TimeString()+"')";
  }
  else sql="update USERS_MONITOR set LAST_DATE = '"+Date().DateString()+"', LAST_TIME = '"+Time().TimeString()+"' where USER_ID = "+IntToStr(UserID);
  TempQuery->Close();
  UMQuery->Close();
  UMQuery->SQL->Clear();
  UMQuery->SQL->Add(sql);
  try
  {
    UMQuery->ExecQuery();
    UsersMonitorTimer->Enabled=true;
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка обновления таблицы USERS_MONITOR\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  }
  UMQuery->Close();
}
//---------------------------------------------------------------------------
unsigned short __fastcall TSaleBookDM::LastDay(unsigned short y,unsigned short m)
{
unsigned short ld=31;

  if(m==4 || m==6 || m==9 || m==11) ld=30;
  else if(m==2)
  { if(y%4) ld=28;
    else ld=29;
  }
  return ld;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TSaleBookDM::GetConstValue(int OrgID, AnsiString Identifier, TDateTime CDate, TDateTime &ConstDate, int &Reference)
{
AnsiString ConstValue="";

  ConstProc->Close();
  ConstProc->StoredProcName="GET_CONSTANT";
  ConstProc->ParamByName("ORG_ID")->AsInteger=OrgID;
  ConstProc->ParamByName("IDENTIFIER")->AsString=Identifier;
  ConstProc->ParamByName("C_DATE")->AsDateTime=CDate.DateString();
  ConstProc->Prepare();
  try
  {
    ConstProc->ExecProc();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка ConstProc->ExecProc()\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return ConstValue;
  }
  ConstValue=ConstProc->ParamByName("CONST_VALUE")->AsString;
  ConstDate=ConstProc->ParamByName("CONST_DATE")->AsDateTime;
  Reference=ConstProc->ParamByName("REFERENCE")->AsInteger;
  ConstProc->Close();
  return ConstValue;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TSaleBookDM::GetConstValue(int OrgID, AnsiString Identifier, TDateTime CDate)
{
AnsiString ConstValue="";

  ConstProc->Close();
  ConstProc->StoredProcName="GET_CONSTANT";
  ConstProc->ParamByName("ORG_ID")->AsInteger=OrgID;
  ConstProc->ParamByName("IDENTIFIER")->AsString=Identifier;
  ConstProc->ParamByName("C_DATE")->AsDateTime=CDate.DateString();
  ConstProc->Prepare();
  try
  {
    ConstProc->ExecProc();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка ConstProc->ExecProc()\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return ConstValue;
  }
  ConstValue=ConstProc->ParamByName("CONST_VALUE")->AsString;
  ConstProc->Close();
  return ConstValue;
}
//---------------------------------------------------------------------------
TDateTime __fastcall TSaleBookDM::GetConstDate(int OrgID, AnsiString Identifier, TDateTime CDate)
{
TDateTime ConstDate=0;

  ConstProc->Close();
  ConstProc->StoredProcName="GET_CONSTANT";
  ConstProc->ParamByName("ORG_ID")->AsInteger=OrgID;
  ConstProc->ParamByName("IDENTIFIER")->AsString=Identifier;
  ConstProc->ParamByName("C_DATE")->AsDateTime=CDate.DateString();
  ConstProc->Prepare();
  try
  {
    ConstProc->ExecProc();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка ConstProc->ExecProc()\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return ConstDate;
  }
  ConstDate=ConstProc->ParamByName("CONST_DATE")->AsDateTime;
  ConstProc->Close();
  return ConstDate;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TSaleBookDM::GetConstValue(int OrgID, AnsiString Identifier)
{
AnsiString ConstValue="";

  ConstProc->Close();
  ConstProc->StoredProcName="GET_SIMPLE_CONSTANT";
  ConstProc->ParamByName("ORG_ID")->AsInteger=OrgID;
  ConstProc->ParamByName("IDENTIFIER")->AsString=Identifier;
  ConstProc->Prepare();
  try
  {
    ConstProc->ExecProc();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка ConstProc->ExecProc()\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return "";
  }
  ConstValue=ConstProc->ParamByName("CONST_VALUE")->AsString;
  ConstProc->Close();
  return ConstValue;
}
//---------------------------------------------------------------------------
int __fastcall TSaleBookDM::SetConstValue(int OrgID, AnsiString Identifier, AnsiString value)
{
int value_id=0;

  ConstProc->Close();
  ConstProc->StoredProcName="SET_SIMPLE_CONSTANT";
  ConstProc->ParamByName("ORG_ID")->AsInteger=OrgID;
  ConstProc->ParamByName("IDENTIFIER")->AsString=Identifier;
  ConstProc->ParamByName("CONST_VALUE")->AsString=value;
  ConstProc->Prepare();
  try
  {
    ConstProc->ExecProc();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка ConstProc->ExecProc()\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return value_id;
  }
  value_id=ConstProc->ParamByName("VALUE_ID")->AsInteger;
  ConstProc->Close();
  return value_id;
}
//---------------------------------------------------------------------------
/*bool __fastcall TSaleBookDM::checkPossibleEditingData(int orgID, AnsiString identifier,TDateTime actualDate)
{
AnsiString ld=GetConstValue(orgID,identifier);
TDateTime lockDate;

  if(ld.IsEmpty()) return false;
  lockDate=TDateTime(ld);
  if(actualDate > lockDate) return true;
  else return false;
}*/
//---------------------------------------------------------------------------
AnsiString __fastcall TSaleBookDM::GetConstValue(int OrgID, int ConstID, TDateTime CDate, TDateTime &ConstDate, int &Reference)
{
AnsiString ConstValue="";

  ConstProc->Close();
  ConstProc->StoredProcName="GET_CONST_BY_ID";
  ConstProc->ParamByName("ORG_ID")->AsInteger=OrgID;
  ConstProc->ParamByName("CONST_ID")->AsString=ConstID;
  ConstProc->ParamByName("C_DATE")->AsDateTime=CDate.DateString();
  ConstProc->Prepare();
  try
  {
    ConstProc->ExecProc();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка ConstProc->ExecProc()\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return ConstValue;
  }
  ConstValue=ConstProc->ParamByName("CONST_VALUE")->AsString;
  ConstDate=ConstProc->ParamByName("CONST_DATE")->AsDateTime;
  Reference=ConstProc->ParamByName("REFERENCE")->AsInteger;
  ConstProc->Close();
  return ConstValue;
}
//---------------------------------------------------------------------------
bool __fastcall TSaleBookDM::AddRecordToActionsJournal(actions ActionType, AnsiString ActionText, TFIBTransaction *Transaction)
{
AnsiString sql;

  sql="insert into ACTIONS_JOURNAL(ID,ACTION_DATE,ACTION_TIME,ACTION_TYPE,ACTION_TEXT,\
USER_ID,NET_NAME) values(GEN_ID(GEN_ACTIONS_JOURNAL_ID,1),";
  sql+="'"+Date().DateString()+"',";
  sql+="'"+Time().TimeString()+"',";
  sql+=IntToStr(ActionType)+",";
  sql+="'"+ActionText+"',";
  sql+=IntToStr(UserID)+",";
  sql+="'"+NetName+"')";
  TQ->Close();
  TQ->Transaction=Transaction;
  TQ->SQL->Clear();
  TQ->SQL->Add(sql);
  try
  {
    TQ->ExecQuery();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return false;
  }
  TQ->Close();
  return true;
}
//---------------------------------------------------------------------------
void __fastcall TSaleBookDM::DataBaseErrorRestoreConnect(
      TFIBDatabase *Database, EFIBError *E, TOnLostConnectActions &Actions)
{
  RestoreCalculator++;
  if(RestoreCalculator==1)
  {
    MessageDlg("Сделана попытка восстановления подключения к базе. Подключение не восстановлено.\nПриложение закрывается. Обратитесь к администратору локальной сети.",mtError,TMsgDlgButtons() << mbOK,0);
    Actions=laTerminateApp;
  }
}
//---------------------------------------------------------------------------
void __fastcall TSaleBookDM::DataBaseAfterRestoreConnect(
      TFIBDatabase *Database)
{
  if(ConnectToDataBase())
    MessageDlg("Соединение восстановлено",mtWarning,TMsgDlgButtons() << mbOK,0);
}
//---------------------------------------------------------------------------
//Проверка наличия константы в таблице констант
void __fastcall TSaleBookDM::inspectConstant(AnsiString identifier,AnsiString title,int type,int kind)
{
AnsiString sql;

  TempQuery->Close();
  TempQuery->SQL->Clear();
  sql="select ID from CONSTANT where IDENTIFIER='"+identifier+"'";
  TempQuery->SQL->Add(sql);
  try
  {
    TempQuery->ExecQuery();
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(TempQuery->RecordCount==0)
  { WQ->Close();
    WQ->SQL->Clear();
    sql="insert into CONSTANT(ID,IDENTIFIER,CONST_NAME,CONST_TYPE,CONST_KIND) values(";
    sql+="GEN_ID(GEN_CONSTANT_ID,1),'"+identifier+"','"+title+"',"+IntToStr(type)+","+IntToStr(kind)+")";
    WQ->SQL->Add(sql);
    WQ->Transaction->StartTransaction();
    try
    {
      WQ->ExecQuery();
    }
    catch(const Exception &exc)
    { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      WQ->Transaction->Rollback();
    }
    WQ->Transaction->Commit();
  }
}
//---------------------------------------------------------------------------
//Проверка правильности заполнения таблицы констант
void __fastcall TSaleBookDM::inspectConstantsTable(void)
{
//  inspectConstant("CODE","Префикс к номеру счет-фактуры",0,1);
  inspectConstant("ORG_NAME","Наименование организации",0,1);
//  inspectConstant("SELLER_ID","Продавец",1,1);
//  inspectConstant("CONSIGNOR_ID","Грузоотправитель",1,1);
  inspectConstant("JOB_TITLE_OF_LEADER","Должность руководителя",0,1);
  inspectConstant("LEADER","Руководитель",0,1);
  inspectConstant("JOB_TITLE_OF_LEADER_TO_BOOK","Должность руководителя бухгалтерии",0,1);
  inspectConstant("LEADER_TO_BOOK","Руководитель бухгалтерии",0,1);
//  inspectConstant("ORDER_SIGNATURE","Приказ на право подписи",0,1);
//  inspectConstant("SIGNATURE_FOR_LEADER_1","За руководителя предприятия - 1",0,1);
//  inspectConstant("SIGNATURE_FOR_LEADER_2","За руководителя предприятия - 2",0,1);
//  inspectConstant("SIGNATURE_FOR_BOOK_LEADER_1","За руководителя бухгалтерии - 1",0,1);
//  inspectConstant("SIGNATURE_FOR_BOOK_LEADER_2","За руководителя бухгалтерии - 2",0,1);
  inspectConstant("LOCK_EDIT_DATE","Дата запрета импортирования",0,0);
}

//---------------------------------------------------------------------------
void __fastcall TSaleBookDM::updateSBInterface(int status)
{
AnsiString sql;
bool flagopen;

  TempQuery->Close();
  TempQuery->SQL->Clear();
  sql="select * from ACCOUNTS_TEMP where USER_ID = "+IntToStr(UserID);
  TempQuery->SQL->Add(sql);
  TempQuery->ExecQuery();
  if(TempQuery->RecordCount == 0)
  {
  flagopen=false;
  }
  else
  {
  flagopen=true;
  }


  if (status==1)
  {
     if(Application->FindComponent("AccountsJournalForm")!=NULL)
     {
      if(flagopen)
      {
     MessageDlg("Прошу сохранить и закрыть текущее задание и выйти из ИС !!! По окончаний технических работ с БД , а также выгрузки и загрузки данных вход в ИС вновь откроется!!! Приношу извинения за доставленные неудобства!!! \n Спасибо за внимание и понимание!!!",mtError,TMsgDlgButtons() << mbOK,0);
      }else
      {
       MessageDlg("ИС Инспектор ПРИНУДИТЕЛЬНО закрывается на время проведение технических работ БД , а также выгрузки и загрузки данных с сохранением всех последних данных сеанса!!! По окончаний всех необходимых работ вход в ИС вновь откроется!!! Приношу извинения за доставленные неудобства!!! \n Спасибо за внимание и понимание!!!",mtError,TMsgDlgButtons() << mbOK,0);
       AccountsJournalForm->Close();
       MainForm->Close();
      }
     }else
     {
     MessageDlg("ИС Инспектор ПРИНУДИТЕЛЬНО закрывается на время проведение технических работ БД , а также выгрузки и загрузки данных с сохранением всех последних данных сеанса!!! По окончаний всех необходимых работ с БД вход в ИС вновь откроется!!! Приношу извинения за доставленные неудобства!!! \n Спасибо за внимание и понимание!!!",mtError,TMsgDlgButtons() << mbOK,0);
     MainForm->Close();
     }
  }

  if (status==2)
  {
    enableEdit=false;
    if(Application->FindComponent("AccountsJournalForm")!=NULL)
    {
      if(flagopen)
      {
     MessageDlg("Прошу сохранить и закрыть текущее задание !!! На время проверки БД работа с заданиями т.е ( редактирование, удаление , создание нового и прочие операций с заданиями запрещены ) !!! После завершения процедуры проверки БД Вы можете вновь как обычно работать с заданиями т.е ( редактирование, удаление , создание нового и прочие операций с заданиями будут разрешены )\n Приношу извинения за доставленные неудобства!!! \n Спасибо за внимание и понимание!!!",mtError,TMsgDlgButtons() << mbOK,0);
      }
    }
  }

}

//---------------------------------------------------------------------------


