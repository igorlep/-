//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include <math.h>

#include "DataModule.h"
#include "utils.h"
#include "Nomenclature.h"
#include "Main.h"
#include "AccountEdit.h"
#include "SelectFilter.h"
//#include "Searching.h"
#include "PrntData.h"
#include "InvoiceEdit.h"
#include "ImportFrom1C.h"
#include "AccauntsJournal.h"
#include "SelectPeriodAF.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SmrtPanel"
#pragma link "Placemnt"
#pragma link "Placemnt"
#pragma link "DBGridEh"
#pragma link "RXSpin"
#pragma link "FIBDataSet"
#pragma link "pFIBDataSet"
#pragma link "FIBQuery"
#pragma link "pFIBQuery"
#pragma link "pFIBStoredProc"
#pragma link "FIBDatabase"
#pragma link "pFIBDatabase"
#pragma link "JvComponent"
#pragma link "JvExControls"
#pragma link "JvNavigationPane"
#pragma resource "*.dfm"
TAccountsJournalForm *AccountsJournalForm;
TAccountEditForm *AEF;
//---------------------------------------------------------------------------
//**********
//* public *
//**********
__fastcall TAccountsJournalForm::TAccountsJournalForm(TComponent* Owner)
        : TForm(Owner)
{
  iniFileName=MainForm->getIniFileName();
  FormStorage1->IniFileName=iniFileName;
  FormStorage1->IniSection="AccountsJournalForm";


  Year->Height=21;
  if(MainForm->getFontDPI()>96)
  { AccountsGrid->Font->Size=10;
    AccountsGrid->FooterFont->Size=10;
    AccountsGrid->TitleFont->Size=10;
  }
  setPeriod();
  loadProperties();
  order=ByDate;
//  AccountsGrid->Columns->Items[1]->Title->Color=Graphics::clMoneyGreen;
  filter=None;
  FilterCustomerID=FilterUserID=0;
  setMainHeader();
}
//---------------------------------------------------------------------------
void __fastcall TAccountsJournalForm::setMainHeader(void)
{
AnsiString s,sb;
AnsiString sql;
TpFIBQuery *Q=SaleBookDM->TempQuery;
TpFIBDataSet *Query;
AnsiString IndOps;
AnsiString fio;
int k=0;
unsigned short dvp1,yvp1,mvp1;
unsigned short dvp2,yvp2,mvp2;
TDateTime dprn1=getDate1();
TDateTime dprn2=getDate2();
dprn1.DecodeDate(&yvp1,&mvp1,&dvp1);
dprn2.DecodeDate(&yvp2,&mvp2,&dvp2);
AnsiString IndexOps;
int Massiv[20];
int KolOps;
int kol1,kol2;
int neopl=0;
int opl=0;

kol1=0;
kol2=0;
neopl=0;
opl=0;


if (date1 == date2)
{

  MainHeader->Height=30;
  MainHeader->ColorFrom=Graphics::clMoneyGreen;
  s+=" Учет поручений за "+date1.DateString();
}
else
{
  s+=" Учет поручений за период с "+date1.DateString()+" по "+date2.DateString();
  MainHeader->Height=30;
  MainHeader->ColorFrom=Graphics::clMoneyGreen;
}
  MainHeader->Caption=s;
}


void __fastcall TAccountsJournalForm::LoadDataSet(void)
{
AnsiString sql;
unsigned short dvp,yvp,mvp;
unsigned short dt,yt,mt;
TDateTime dprn=getDate1();
dprn.DecodeDate(&yvp,&mvp,&dvp);
TDateTime today=Date();
today.DecodeDate(&yt,&mt,&dt);
TDateTime lockDate;
unsigned short yl,ml,dl;

lockDate=SaleBookDM->GetConstValue(SaleBookDM->OrganizationID,"LOCK_EDIT_DATE");
lockDate.DecodeDate(&yl,&ml,&dl);


//  setPeriod();
  AccountsGrid->Visible=false;
  if(SG_DS->Active==true) SG_DS->Close();
  if(A_DS->Active==true) A_DS->Close();
  A_DS->SQLs->SelectSQL->Clear();
  sql="select t1.*, t4.LOGIN as \"Avtor\"";
  if (mvp==ml) sql+=" from ACCOUNTS t1"; else sql+=" from ACCOUNTS_A t1";
  sql+=" left outer join USERS t4 on t1.USER_ID=t4.ID";
  sql+=" where t1.ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
  sql+=" and t1.COUNT_DATE>='"+date1.DateString()+"'";
  sql+=" and t1.COUNT_DATE<='"+date2.DateString()+"'";

  if (SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель")
  {
   sql+=" and USER_ID="+IntToStr(SaleBookDM->UserID);
  }

//  if(filter==ByCustomer || filter==ByAll) sql+=" and CUSTOMER_ID="+IntToStr(FilterCustomerID);
//  if(filter==ByUser || filter==ByAll) sql+=" and USER_ID="+IntToStr(FilterUserID);
  if(order==ByDate) sql+=" order by t1.COUNT_DATE,t1.COUNT_NUMBER";
  else if(order==ByNumber) sql+=" order by t1.COUNT_NUMBER";
  else if(order==ByCustomerID) sql+=" order by t1.CUSTOMER_ID,t1.COUNT_NUMBER";
  A_DS->SQLs->SelectSQL->Add(sql);
  try
  {
    A_DS->Open();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  A_DS->Last();

  SG_DS->SQLs->SelectSQL->Clear();
  sql="select t1.* ";
  if (mvp==ml) sql+=" from SGB t1"; else sql+=" from SGB_A t1";
  sql+=" where t1.ORG_ID=?MAS_ORG_ID and t1.COUNT_DATE=?MAS_COUNT_DATE \
and t1.COUNT_NUMBER=?MAS_COUNT_NUMBER";
  sql+=" order by t1.LCHET,t1.LCHET1,t1.FAMILY,t1.NAME,t1.FATHER";
  SG_DS->SQLs->SelectSQL->Add(sql);
  try
  {
    SG_DS->Open();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка чтения таблицы SOLD_GOODS_BOOK\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  }
  AccountsGrid->Visible=true;
  SetButtons();
  try
  {
    AccountsGrid->SetFocus();
  }
  catch(...){};
}
//---------------------------------------------------------------------------
void __fastcall TAccountsJournalForm::SetButtons(void)
{
AnsiString NumLock;
int nl;
TDateTime dt=TDateTime((unsigned short)(Year->Value),(unsigned short)(Month->ItemIndex+1),1);
TDateTime today=Date();
NumLock=SaleBookDM->GetConstValue(SaleBookDM->OrganizationID,"LOCK_TASK_DATE",today);
nl=0;

if (NumLock=="")
{
MessageDlg("Дата запрета редактирования не актуальна!!! Аварийный выход из процедуры!!! - ",mtError,TMsgDlgButtons() << mbOK,0);
Close();
}
else
{
nl=StrToInt(NumLock);
}


TDateTime lockDate=SaleBookDM->GetConstValue(SaleBookDM->OrganizationID,"LOCK_EDIT_DATE");
unsigned short yl,mlock,dl;
lockDate.DecodeDate(&yl,&mlock,&dl);

unsigned short y,m,m1,d;
m1=(unsigned short)(Month->ItemIndex+1);
today.DecodeDate(&y,&m,&d);
TpFIBQuery *Q=SaleBookDM->TempQuery;
AnsiString sql;
int indops;

if (mlock==m)
{
  if(A_DS->RecordCount==0)
  {
    EditButton->Enabled=false;
    DelButton->Enabled=false;
    PrintButton->Enabled=true;

    EditItem->Enabled=false;
    DelItem->Enabled=false;
    PrintItem->Enabled=true;


    if(m1!=m)
    {
      AddButton->Enabled=false;
      AddItem->Enabled=false;
    }
    else
    {
      if (d<=nl)
      {
      if((SaleBookDM->UserRole=="Администратор" && SaleBookDM->UserRole!="Руководитель") || (SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole=="Руководитель")){
      AddButton->Enabled=false;
      AddItem->Enabled=false;
      }else
      {
      AddButton->Enabled=true;
      AddItem->Enabled=true;
      }
      }
      else
      {
      AddButton->Enabled=false;
      AddItem->Enabled=false;
      }
    }
  }
  else
  {
    PrintButton->Enabled=true;
    PrintItem->Enabled=true;

    if(m1!=m)
    {
      AddButton->Enabled=false;
      AddItem->Enabled=false;

      if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель"){
       if(A_DS->FieldByName("USER_ID")->AsInteger!=SaleBookDM->UserID || A_DS->FieldByName("EDIT_KEY")->AsInteger==0)
      {
        EditButton->Enabled=false;
        DelButton->Enabled=false;
        EditItem->Enabled=false;
        DelItem->Enabled=false;
      }
      else
      {
        if(m1!=m)
        {
        EditButton->Enabled=false;
        DelButton->Enabled=false;
        EditItem->Enabled=false;
        DelItem->Enabled=false;
        }else
        {
        if (d<=nl)
        {
        EditButton->Enabled=true;
        DelButton->Enabled=true;
        EditItem->Enabled=true;
        DelItem->Enabled=true;
        }
        else
        {
        EditButton->Enabled=false;
        DelButton->Enabled=false;
        EditItem->Enabled=false;
        DelItem->Enabled=false;
        }
        }
      }
      }else
      {
      if(A_DS->FieldByName("EDIT_KEY")->AsInteger==0)
      {
        EditButton->Enabled=false;
        DelButton->Enabled=false;
        EditItem->Enabled=false;
        DelItem->Enabled=false;
      }
      else
      {
//        if(m1!=m)
//        {
//        EditButton->Enabled=false;
//        DelButton->Enabled=false;
//        EditItem->Enabled=false;
//        DelItem->Enabled=false;
//        }else
//        {
        if (d<=23)
        {
        EditButton->Enabled=true;
        DelButton->Enabled=true;
        EditItem->Enabled=true;
        DelItem->Enabled=true;
        }
        else
        {
        EditButton->Enabled=false;
        DelButton->Enabled=false;
        EditItem->Enabled=false;
        DelItem->Enabled=false;
        }
//        }
      }
      }

    }
    else
    {
      if (d<=nl)
      {
      if((SaleBookDM->UserRole=="Администратор" && SaleBookDM->UserRole!="Руководитель") || (SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole=="Руководитель")){
      AddButton->Enabled=false;
      AddItem->Enabled=false;
      }
      else
      {
      AddButton->Enabled=true;
      AddItem->Enabled=true;
      }
      }
      else
      {
      AddButton->Enabled=false;
      AddItem->Enabled=false;
      }

      if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель"){
      if(A_DS->FieldByName("USER_ID")->AsInteger!=SaleBookDM->UserID || A_DS->FieldByName("EDIT_KEY")->AsInteger==0)
      {
        EditButton->Enabled=false;
        DelButton->Enabled=false;
        EditItem->Enabled=false;
        DelItem->Enabled=false;
      }
      else
      {
//        if(m1!=m)
//        {
//        EditButton->Enabled=false;
//        DelButton->Enabled=false;
//        EditItem->Enabled=false;
//        DelItem->Enabled=false;
//        }else
//        {
        if (d<=nl)
        {
        EditButton->Enabled=true;
        DelButton->Enabled=true;
        EditItem->Enabled=true;
        DelItem->Enabled=true;
        }
        else
        {
        EditButton->Enabled=false;
        DelButton->Enabled=false;
        EditItem->Enabled=false;
        DelItem->Enabled=false;
        }
//        }
      }
      }else
      {
      if(A_DS->FieldByName("EDIT_KEY")->AsInteger==0)
      {
        EditButton->Enabled=false;
        DelButton->Enabled=false;
        EditItem->Enabled=false;
        DelItem->Enabled=false;
      }
      else
      {
//        if(m1!=m)
//        {
//        EditButton->Enabled=false;
//        DelButton->Enabled=false;
//        EditItem->Enabled=false;
//        DelItem->Enabled=false;
//        }else
//        if (d<=14)
//        {
        EditButton->Enabled=false;
        DelButton->Enabled=false;
        EditItem->Enabled=false;
        DelItem->Enabled=false;
//        }
//        else
//        {
//        EditButton->Enabled=false;
//        DelButton->Enabled=false;
//        EditItem->Enabled=false;
//        DelItem->Enabled=false;
//        }
//        }
      }
      }
    }
  }
}
else
{
  if(A_DS->RecordCount==0)
  {
    EditButton->Enabled=false;
    DelButton->Enabled=false;
    PrintButton->Enabled=true;

    EditItem->Enabled=false;
    DelItem->Enabled=false;
    PrintItem->Enabled=true;
    AddButton->Enabled=true;
    AddItem->Enabled=true;
  }
  else
  {
    PrintButton->Enabled=true;
    PrintItem->Enabled=true;
    AddButton->Enabled=true;
    AddItem->Enabled=true;

     if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель")
     {
      if(A_DS->FieldByName("USER_ID")->AsInteger!=SaleBookDM->UserID || A_DS->FieldByName("EDIT_KEY")->AsInteger==0)
      {
        EditButton->Enabled=false;
        DelButton->Enabled=false;
        EditItem->Enabled=false;
        DelItem->Enabled=false;
      }
      else
      {
        EditButton->Enabled=true;
        DelButton->Enabled=true;
        EditItem->Enabled=true;
        DelItem->Enabled=true;
      }
     }else
     {
      if(A_DS->FieldByName("EDIT_KEY")->AsInteger==0)
      {
        EditButton->Enabled=false;
        DelButton->Enabled=false;
        EditItem->Enabled=false;
        DelItem->Enabled=false;
      }
      else
      {
        EditButton->Enabled=true;
        DelButton->Enabled=true;
        EditItem->Enabled=true;
        DelItem->Enabled=true;
      }
     }
  }
}
  if(A_DS->Eof)
  { LastButton->Enabled=false;
    NextButton->Enabled=false;
  }
  else
  { LastButton->Enabled=true;
    NextButton->Enabled=true;
  }
  if(A_DS->Bof)
  { FirstButton->Enabled=false;
    PriorButton->Enabled=false;
  }
  else
  { FirstButton->Enabled=true;
    PriorButton->Enabled=true;
  }

    if(A_DS->FieldByName("CUSTOMER_ID")->AsInteger>0)
    {
    Q->Close();
    Q->SQL->Clear();
    sql="select INDEXOPS as IND from NOMENCLATURE";
    sql+=" where CODP="+IntToStr(A_DS->FieldByName("CUSTOMER_ID")->AsInteger);
    Q->SQL->Add(sql);
    try
    {
    Q->ExecQuery();
    }
    catch(const Exception &exc)
    {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
    }

    if(!Q->FieldByName("IND")->IsNull)
    {
    indops=Q->FieldByName("IND")->AsInteger;
    if (indops>0)
    {
     SoldGoodsGrid->Columns->Items[7]->Visible = true;
     SoldGoodsGrid->Columns->Items[8]->Visible = false;
    }
      else
    {
     SoldGoodsGrid->Columns->Items[7]->Visible = false;
     SoldGoodsGrid->Columns->Items[8]->Visible = true;
    }
    }
    else
    {
//    MessageDlg("Данный почтальон не работает на участках!!! Аварийный выход из процедуры!!! - ",mtError,TMsgDlgButtons() << mbOK,0);
//    return;
    }
    }

   if((SaleBookDM->UserRole=="Администратор" && SaleBookDM->UserRole!="Руководитель") || (SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole=="Руководитель"))
   {
   AccountsGrid->Columns->Items[2]->Title->Caption="Ф.И.О почтальона / № Кассы";
   }
   else
   {
   if(SaleBookDM->UserRole=="Бухгалтер") AccountsGrid->Columns->Items[2]->Title->Caption="Ф.И.О почтальона";
   if(SaleBookDM->UserRole=="Кассир") AccountsGrid->Columns->Items[2]->Title->Caption="№ Кассы";
   if(SaleBookDM->UserRole=="Бухгалтер-кассир") AccountsGrid->Columns->Items[2]->Title->Caption="Ф.И.О почтальона / № Кассы";
   }
}
//---------------------------------------------------------------------------

//***********
//* private *
//***********
void __fastcall TAccountsJournalForm::setPeriod(void)
{
//  date1=TDateTime((unsigned short)(Year->Value),(unsigned short)Month->ItemIndex+1,1);
//  date2=TDateTime((unsigned short)(Year->Value),(unsigned short)Month->ItemIndex+1,SaleBookDM->LastDay((unsigned short)(Year->Value),(unsigned short)Month->ItemIndex+1));
TDateTime today=Date();
TDateTime lockDate=SaleBookDM->GetConstValue(SaleBookDM->OrganizationID,"LOCK_EDIT_DATE");
unsigned short yl,ml,dl;
unsigned short y,m,d;
lockDate.DecodeDate(&yl,&ml,&dl);
today.DecodeDate(&y,&m,&d);
if (ml==m)
{
date1=Date();
date2=Date();
}else
{
  date1=TDateTime((unsigned short)yl,(unsigned short)ml,1);
  date2=TDateTime((unsigned short)yl,(unsigned short)ml,1);
}
}
//---------------------------------------------------------------------------
void __fastcall TAccountsJournalForm::loadProperties(void)
{
TIniFile *ini=NULL;
//TDateTime dt=Date();
TDateTime dt=date1;
unsigned short y,m,d;
int aGridFontSize,sGridFontSize;

  dt.DecodeDate(&y,&m,&d);
  try
  {
    ini=new TIniFile(iniFileName);
    Year->Value=y;
    Month->ItemIndex=m-1;
    MonthUpDown->Position=m;
    SmrtPanel2->Height=ini->ReadInteger("AccountsJournalForm","SmrtPanel2_Height",140);
    aGridFontSize=ini->ReadInteger("AccountsJournalForm","aGridFontSize",AccountsGrid->Font->Size);
    sGridFontSize=ini->ReadInteger("AccountsJournalForm","sGridFontSize",AccountsGrid->Font->Size);
    delete ini;
  }
  catch(...)
  {
    if(ini!=NULL) delete ini;
    Year->Value=y;
    Month->ItemIndex=m-1;
    MonthUpDown->Position=m;
    aGridFontSize=AccountsGrid->Font->Size;
    sGridFontSize=AccountsGrid->Font->Size;
  }
  AccountsGrid->Font->Size=aGridFontSize;
  AccountsGrid->FooterFont->Size=aGridFontSize;
  AccountsGrid->TitleFont->Size=aGridFontSize;
  SoldGoodsGrid->Font->Size=sGridFontSize;
  SoldGoodsGrid->FooterFont->Size=sGridFontSize;
  SoldGoodsGrid->TitleFont->Size=sGridFontSize;
}
//---------------------------------------------------------------------------
void __fastcall TAccountsJournalForm::saveProperties(void)
{
TIniFile *ini=NULL;
TDateTime dt=Date();
unsigned short y,m,d;

  dt.DecodeDate(&y,&m,&d);

  try
  { ini=new TIniFile(iniFileName);
    ini->WriteInteger("AccountsJournalForm","Year",y);
    ini->WriteInteger("AccountsJournalForm","Month",m-1);
    ini->WriteInteger("AccountsJournalForm","SmrtPanel2_Height",SmrtPanel2->Height);
    ini->WriteInteger("AccountsJournalForm","aGridFontSize",AccountsGrid->Font->Size);
    ini->WriteInteger("AccountsJournalForm","sGridFontSize",SoldGoodsGrid->Font->Size);
    delete ini;
  }
  catch(...)
  {
    if(ini!=NULL) delete ini;
  }
}
//---------------------------------------------------------------------------

//*************
//* published *
//*************
void __fastcall TAccountsJournalForm::FormShow(TObject *Sender)
{
  CheckBox1->Checked=false;
  LoadDataSet();
}
//---------------------------------------------------------------------------
void __fastcall TAccountsJournalForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  saveProperties();
  Action=caFree;
}
//---------------------------------------------------------------------------
void __fastcall TAccountsJournalForm::ExitButtonClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TAccountsJournalForm::AccountsGridTitleBtnClick(TObject *Sender,int ACol,TColumnEh *Column)
{
  for(int i=0; i<AccountsGrid->Columns->Count; ++i) AccountsGrid->Columns->Items[i]->Title->Color=clBtnFace;
  if(Column->FieldName=="COUNT_DATE") order=ByDate;
  else if(Column->FieldName=="COUNT_NUMBER") order=ByNumber;
  else if(Column->FieldName=="CUSTOMER_NAME") order=ByCustomerID;
  else order=ByNone;
  if(order!=ByNone) Column->Title->Color=Graphics::clMoneyGreen;
  UpDateButton->OnClick(this);
}
//---------------------------------------------------------------------------
void __fastcall TAccountsJournalForm::AccountsGridDblClick(TObject *Sender)
{
  if(EditButton->Enabled) EditButton->Click();
}
//---------------------------------------------------------------------------
void __fastcall TAccountsJournalForm::AccountsSDataChange(TObject *Sender,
      TField *Field)
{
  if(AccountsGrid->Visible==true && Showing) SetButtons();
}
//---------------------------------------------------------------------------

//Добавление нового счета
void __fastcall TAccountsJournalForm::AddItemClick(TObject *Sender)
{
  AddButton->Click();
}
//---------------------------------------------------------------------------
void __fastcall TAccountsJournalForm::AddButtonClick(TObject *Sender)
{
int CountNumber;
TDateTime CountDate;
AnsiString sql;
TpFIBQuery *Q=SaleBookDM->TempQuery;

  if (!SaleBookDM->enableEdit)
  {
   MessageDlg("На время проверки БД работа с заданиями т.е ( редактирование, удаление , создание нового и прочие операций с заданиями запрещены ) !!! После завершения процедуры проверки БД Вы можете вновь как обычно работать с заданиями т.е ( редактирование, удаление , создание нового и прочие операций с заданиями будут разрешены )\n Приношу извинения за доставленные неудобства!!! \n Спасибо за внимание и понимание!!!",mtError,TMsgDlgButtons() << mbOK,0);
   return;
  }

  Q->Close();
  Q->SQL->Clear();
  sql="select max(COUNT_DATE) as MAX_COUNT_DATE from ACCOUNTS";
  sql+=" where ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
  sql+=" and COUNT_DATE>='"+date1.DateString()+"'";
  sql+=" and COUNT_DATE<='"+date2.DateString()+"'";
  Q->SQL->Add(sql);
  try
  {
    Q->ExecQuery();;
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(!Q->FieldByName("MAX_COUNT_DATE")->IsNull) CountDate=Q->FieldByName("MAX_COUNT_DATE")->AsDateTime;
  else CountDate=date1;

  WQ->Close();
  WQ->SQL->Clear();
  if(CountDate > TDateTime("31.12.2008"))
  { sql="select COUNT_NUMBER from GET_NEW_COUNT("+IntToStr(SaleBookDM->OrganizationID)+",";
    sql+="'"+CountDate.DateString()+"',";
    sql+=IntToStr(SaleBookDM->UserID)+")";
  }
  else
  { unsigned short y,m,d;
    CountDate.DecodeDate(&y,&m,&d);
    TDateTime dt1=TDateTime(y,m,1),
              dt2=TDateTime(y,m,SaleBookDM->LastDay(y,m));
    sql="select COUNT_NUMBER,COUNT_DATE from OLD_GET_NEW_COUNT("+IntToStr(SaleBookDM->OrganizationID)+",";
    sql+="'"+dt1.DateString()+"',";
    sql+="'"+dt2.DateString()+"',";
    sql+=IntToStr(SaleBookDM->UserID)+")";
  }
  WQ->SQL->Add(sql);
  WQ->Transaction->StartTransaction();
  try
  {
    WQ->ExecQuery();
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    WQ->Transaction->Rollback();
    return;
  }
  if(CountDate > TDateTime("31.12.2008"))
    CountNumber=WQ->FieldByName("COUNT_NUMBER")->AsInteger;
  else
  { CountNumber=WQ->FieldByName("COUNT_NUMBER")->AsInteger;
    CountDate=WQ->FieldByName("COUNT_DATE")->AsDateTime;
  }
  WQ->Transaction->Commit();

  if(CountNumber!=0)
  {
    AEF=NULL;
    try
    {
      AEF=new TAccountEditForm(this,CountDate,CountNumber);
    }
    catch(const Exception &exc)
    {
      MessageDlg("Ошибка создания формы для редактирования задания\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      WQ->Close();
      WQ->SQL->Clear();
      AnsiString sql="delete from ACCOUNTS_TEMP where ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
      sql+=" and COUNT_DATE='"+CountDate.DateString()+"'";
      sql+=" and COUNT_NUMBER="+IntToStr(CountNumber);
      WQ->SQL->Add(sql);
      WQ->Transaction->StartTransaction();
      try
      {
        Q->ExecQuery();
      }
      catch(const Exception &exc)
      { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
        WQ->Transaction->Rollback();
        if(AEF!=NULL) delete AEF;
        return;
      }
      WQ->Transaction->Commit();
      if(AEF!=NULL) delete AEF;
      return;
    }
    if(AEF->ShowModal()==mrOk)
    {
      unsigned short year,month,day;
      AEF->C_DS->FieldByName("COUNT_DATE")->AsDateTime.DecodeDate(&year,&month,&day);
      Year->Value=year;
      Month->ItemIndex=month-1;
      setMainHeader();
      LoadDataSet();
      TLocateOptions Opt; Opt.Clear();
      Variant lv[3];
      lv[0] = AEF->C_DS->FieldByName("ORG_ID")->AsInteger;
      lv[1] = AEF->C_DS->FieldByName("COUNT_DATE")->AsDateTime;
      lv[2] = AEF->C_DS->FieldByName("COUNT_NUMBER")->AsInteger;
      A_DS->Locate("ORG_ID;COUNT_DATE;COUNT_NUMBER",VarArrayOf(lv,2),Opt);
    }
//    if(AEF!=NULL) delete AEF;
  }
  if(AEF!=NULL) delete AEF;
}
//---------------------------------------------------------------------------
//Редактирование существующего счета
void __fastcall TAccountsJournalForm::EditItemClick(TObject *Sender)
{
  EditButton->Click();
}
void __fastcall TAccountsJournalForm::EditButtonClick(TObject *Sender)
{
AnsiString sql;

  if (!SaleBookDM->enableEdit)
  {
   MessageDlg("На время проверки БД работа с заданиями т.е ( редактирование, удаление , создание нового и прочие операций с заданиями запрещены ) !!! После завершения процедуры проверки БД Вы можете вновь как обычно работать с заданиями т.е ( редактирование, удаление , создание нового и прочие операций с заданиями будут разрешены )\n Приношу извинения за доставленные неудобства!!! \n Спасибо за внимание и понимание!!!",mtError,TMsgDlgButtons() << mbOK,0);
   return;
  }

  //Проверяем не закрыт ли задания для редактирования
  SaleBookDM->TempQuery->Close();
  SaleBookDM->TempQuery->SQL->Clear();
  sql="select EDIT_KEY from ACCOUNTS where ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
  sql+=" and COUNT_DATE='"+A_DS->FieldByName("COUNT_DATE")->AsString+"'";
  sql+=" and COUNT_NUMBER="+A_DS->FieldByName("COUNT_NUMBER")->AsString;
  SaleBookDM->TempQuery->SQL->Add(sql);
  try
  {
    SaleBookDM->TempQuery->ExecQuery();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(SaleBookDM->TempQuery->RecordCount==0)
  {
    MessageDlg("Не найдена нужная запись (select EDIT_KEY from ACCOUNTS)",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(SaleBookDM->TempQuery->FieldByName("EDIT_KEY")->AsInteger==0)
  {
    MessageDlg("Запись закрыта для редактирования!",mtWarning,TMsgDlgButtons() << mbOK,0);
    return;
  }

  if(A_DS->RecordCount > 0)
  { TAccountEditForm *AEF=NULL;
    try
    {
      AEF=new TAccountEditForm(this,A_DS);
    }
    catch(const Exception &exc)
    {
      MessageDlg("Ошибка создания формы для редактирования задания\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }

    if(AEF->ShowModal()==mrOk)
    { Variant lv[3];
      TLocateOptions Opt; Opt.Clear();
      lv[0] = AEF->C_DS->FieldByName("ORG_ID")->AsInteger;
      lv[1] = AEF->C_DS->FieldByName("COUNT_DATE")->AsDateTime;
      lv[2] = AEF->C_DS->FieldByName("COUNT_NUMBER")->AsFloat;
      setMainHeader();
      LoadDataSet();
      A_DS->Locate("ORG_ID;COUNT_DATE;COUNT_NUMBER",VarArrayOf(lv,2),Opt);
    }
    if(AEF!=NULL) delete AEF;
  }
//    if(AEF!=NULL) delete AEF;
}
//---------------------------------------------------------------------------
//Удаление счета
void __fastcall TAccountsJournalForm::DelItemClick(TObject *Sender)
{
  DelButton->Click();
}
//---------------------------------------------------------------------------
void __fastcall TAccountsJournalForm::DelButtonClick(TObject *Sender)
{
  AnsiString sql;
  TpFIBQuery *TempQ=SaleBookDM->TempQuery;
  unsigned short dvp,yvp,mvp;
  TDateTime dprn=getDate1();
  dprn.DecodeDate(&yvp,&mvp,&dvp);
  int kassa;

  if (!SaleBookDM->enableEdit)
  {
   MessageDlg("На время проверки БД работа с заданиями т.е ( редактирование, удаление , создание нового и прочие операций с заданиями запрещены ) !!! После завершения процедуры проверки БД Вы можете вновь как обычно работать с заданиями т.е ( редактирование, удаление , создание нового и прочие операций с заданиями будут разрешены )\n Приношу извинения за доставленные неудобства!!! \n Спасибо за внимание и понимание!!!",mtError,TMsgDlgButtons() << mbOK,0);
   return;
  }

  AnsiString s="Вы уверены, что хотите БЕЗВОЗВРАТНО!!! удалить задание №"+A_DS->FieldByName("COUNT_NUMBER")->AsString;
  s+=" от "+A_DS->FieldByName("COUNT_DATE")->AsString+" из журнала заданий?";
  if(MessageDlg(s,mtConfirmation,TMsgDlgButtons() << mbOK << mbCancel,0) == mrOk)
  {

    WQ->Close();
    //Удаляем записи о поручениях, принадлежащие удаляемому заданий
    WQ->SQL->Clear();
    sql="delete from SGB where";
    sql+=" ORG_ID="+A_DS->FieldByName("ORG_ID")->AsString;
    sql+=" and COUNT_DATE='"+A_DS->FieldByName("COUNT_DATE")->AsString+"'";
    sql+=" and COUNT_NUMBER="+A_DS->FieldByName("COUNT_NUMBER")->AsString;
    WQ->SQL->Add(sql);
    WQ->Transaction->StartTransaction();
    try
    {
      WQ->ExecQuery();
    }
    catch(Exception &exc)
    { MessageDlg("Ошибка удаления записей о поручениях\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      WQ->Transaction->RollbackRetaining();
      return;
    }
    WQ->Transaction->CommitRetaining();
    //Удаляем задание
    int rn=A_DS->RecNo;
    WQ->Close();
    WQ->SQL->Clear();
    sql="delete from ACCOUNTS where";
    sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
    sql+=" and COUNT_DATE='"+A_DS->FieldByName("COUNT_DATE")->AsString+"'";
    sql+=" and COUNT_NUMBER="+A_DS->FieldByName("COUNT_NUMBER")->AsString;
    WQ->SQL->Add(sql);
    WQ->Transaction->StartTransaction();
    try
    {
      WQ->ExecQuery();
    }
    catch(Exception &exc)
    {
      MessageDlg("Ошибка удаления записи о заданий\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      WQ->Transaction->RollbackRetaining();
      return;

    }
    WQ->Transaction->CommitRetaining();

    //Фиксирем действие в журнале событий ACTIONS_JOURNAL
    WQ->Transaction->StartTransaction();
    AnsiString str;
    str="Удалено задание  №"+A_DS->FieldByName("COUNT_NUMBER")->AsString+" от ";
    str+=A_DS->FieldByName("COUNT_DATE")->AsString+" на сумму "+FloatToStr(A_DS->FieldByName("COUNT_TOTAL")->AsFloat);
    SaleBookDM->AddRecordToActionsJournal(DelRecordFromAccountsTable,str,WriteTransaction);

    WQ->Transaction->CommitRetaining();
    A_DS->RecNo=rn;

  provkassa();
  LoadDataSet();
  setMainHeader();
  }
}
//---------------------------------------------------------------------------
//Вывод данных на печать
void __fastcall TAccountsJournalForm::PrintButtonClick(TObject *Sender)
{
  if(AccountsGrid->SelectedRows->Count==0) AccountsGrid->Selection->Rows->CurrentRowSelected=true;
  if(!Application->FindComponent("PrntDataForm"))
  { try
    {
      Application->CreateForm(__classid(TPrntDataForm), &PrntDataForm);
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка создания формы PrntDataForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
  }
  PrntDataForm->ShowModal();
}
//Увеличение размера шрифта в Grid-е
void __fastcall TAccountsJournalForm::increaseButtonClick(TObject *Sender)
{
int fontDPI;
TDBGridEh *grid=NULL;

  if(AccountsGrid->Focused()==true) grid=AccountsGrid;
  else if(SoldGoodsGrid->Focused()==true) grid=SoldGoodsGrid;
  if(grid!=NULL)
  { fontDPI=grid->Font->Size;
    if(fontDPI < 14)
    { fontDPI+=2;
      grid->Font->Size=fontDPI;
      grid->FooterFont->Size=fontDPI;
      grid->TitleFont->Size=fontDPI;
      grid->Repaint();
    }
  }
}
//---------------------------------------------------------------------------
//Уменьшение размера шрифта в Grid-е
void __fastcall TAccountsJournalForm::reduceButtonClick(TObject *Sender)
{
int fontDPI;
TDBGridEh *grid=NULL;

  if(AccountsGrid->Focused()==true) grid=AccountsGrid;
  else if(SoldGoodsGrid->Focused()==true) grid=SoldGoodsGrid;
  if(grid!=NULL)
  { fontDPI=grid->Font->Size;
    if(fontDPI > 8)
    { fontDPI-=2;
      grid->Font->Size=fontDPI;
      grid->FooterFont->Size=fontDPI;
      grid->TitleFont->Size=fontDPI;
      grid->Repaint();
    }
  }
}
//---------------------------------------------------------------------------
//Деблокирование записи
void __fastcall TAccountsJournalForm::YearChange(TObject *Sender)
{
  if(this->Showing==true) LoadDataSet();
}
//---------------------------------------------------------------------------
void __fastcall TAccountsJournalForm::MonthChange(TObject *Sender)
{
  MonthUpDown->Position=Month->ItemIndex+1;
  if(this->Showing) LoadDataSet();
}
//---------------------------------------------------------------------------
void __fastcall TAccountsJournalForm::MonthUpDownClick(TObject *Sender,
      TUDBtnType Button)
{
  if(MonthUpDown->Position > 12 && Button==btNext)
  { Month->ItemIndex=0;
    Year->Value++;
    MonthUpDown->Position=1;
  }
  else if(MonthUpDown->Position < 1 && Button==btPrev)
  { Month->ItemIndex=11;
    Year->Value--;
    MonthUpDown->Position=12;
  }
  else Month->ItemIndex=MonthUpDown->Position-1;
  Month->OnChange(this);
}
//---------------------------------------------------------------------------
void __fastcall TAccountsJournalForm::FirstButtonClick(TObject *Sender)
{
  A_DS->First();
}
//---------------------------------------------------------------------------
void __fastcall TAccountsJournalForm::PriorButtonClick(TObject *Sender)
{
  A_DS->Prior();
}
//---------------------------------------------------------------------------
void __fastcall TAccountsJournalForm::NextButtonClick(TObject *Sender)
{
  A_DS->Next();
}
//---------------------------------------------------------------------------
void __fastcall TAccountsJournalForm::LastButtonClick(TObject *Sender)
{
  A_DS->Last();
}
//---------------------------------------------------------------------------
void __fastcall TAccountsJournalForm::UpDateButtonClick(TObject *Sender)
{
//Variant lv[3];
//TLocateOptions opt;

//  if(A_DS->RecordCount > 0)
//  { lv[0]=A_DS->FieldByName("ORG_ID")->AsInteger;
//    lv[1]=A_DS->FieldByName("COUNT_DATE")->AsDateTime;
//    lv[2]=A_DS->FieldByName("COUNT_NUMBER")->AsInteger;
//  }
//  else{ lv[0]=0; lv[1]=Date(); lv[2]=0;}
  LoadDataSet();
//  opt.Clear();
//  A_DS->Locate("ORG_ID;COUNT_DATE;COUNT_NUMBER",VarArrayOf(lv,2),opt);
}
//---------------------------------------------------------------------------



void __fastcall TAccountsJournalForm::SoldGoodsGridGetCellParams(
      TObject *Sender, TColumnEh *Column, TFont *AFont, TColor &Background,
      TGridDrawState State)
{

 if(!SG_DS->FieldByName("PRICH")->AsString.IsEmpty()){
  if(SG_DS->FieldByName("PRICH")->AsString.Trim() != "н/д")
  {
    Background=Graphics::clRed;
  }
  else
  {
  if(SG_DS->FieldByName("KASSA")->AsInteger ==1 ) Background=Graphics::clCream; else Background=Graphics::clYellow;
  }
 }
 else
 {
 Background=Graphics::clMoneyGreen;
 }

}
//---------------------------------------------------------------------------

void __fastcall TAccountsJournalForm::Edit1KeyPress(TObject *Sender,
      char &Key)
{
  if(Key==VK_RETURN || Key==VK_DOWN || Key==VK_UP)
  { Key=0;
    SoldGoodsGrid->SetFocus();
  }
  else if(Key == VK_ESCAPE){ Key=0; Edit1->Text=""; }
}
//---------------------------------------------------------------------------

void __fastcall TAccountsJournalForm::Edit1Change(TObject *Sender)
{
  if(searchTimer->Enabled==true) searchTimer->Enabled=false;
  searchTimer->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TAccountsJournalForm::searchTimerTimer(TObject *Sender)
{
unsigned short y,m,d1;
Variant lv[3];
TLocateOptions opt;
opt<<loPartialKey<<loCaseInsensitive;
AnsiString d=0;
AnsiString sql;
TpFIBQuery *Q=SaleBookDM->TempQuery;
date1.DecodeDate(&y,&m,&d1);

unsigned short dvp,yvp,mvp;
unsigned short dt,yt,mt;
TDateTime dprn=getDate1();
dprn.DecodeDate(&yvp,&mvp,&dvp);
TDateTime today=Date();
today.DecodeDate(&yt,&mt,&dt);


  searchTimer->Enabled=false;
  if(Edit1->Text.IsEmpty()) return;
 if(Edit1->Text.Length() <= 6 && IsNum(Edit1->Text.Trim()))
 {
  d=Edit1->Text.Trim();
  Q->Close();
  Q->SQL->Clear();
  if (mvp==mt) sql="select LCHET from NDOST"; else sql="select LCHET from NDOST_A";
  sql+=" where LCHET1='"+d+"'";
  sql+=" and M= " +IntToStr(m) + " and Y = " +IntToStr(y);
  Q->SQL->Add(sql);
  try
  {
    Q->ExecQuery();;
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
   if(!Q->FieldByName("LCHET")->IsNull)
   {
    sql="";
    Q->Close();
    Q->SQL->Clear();
    if (mvp==mt) sql="select ORG_ID,COUNT_DATE,COUNT_NUMBER from SGB"; else sql="select ORG_ID,COUNT_DATE,COUNT_NUMBER from SGB_A";
    sql+=" where LCHET1='"+d+"'";
    sql+=" and M= " +IntToStr(m) + " and Y = " +IntToStr(y);
    Q->SQL->Add(sql);
    try
    {
     Q->ExecQuery();;
    }
    catch(const Exception &exc)
    {
     MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
     return;
    }
     if(!Q->FieldByName("ORG_ID")->IsNull)
     {
      lv[0]=Q->FieldByName("ORG_ID")->AsInteger;
      lv[1]=Q->FieldByName("COUNT_DATE")->AsDateTime;
      lv[2]=Q->FieldByName("COUNT_NUMBER")->AsInteger;
      opt.Clear();
      if (!A_DS->Locate("ORG_ID;COUNT_DATE;COUNT_NUMBER",VarArrayOf(lv,2),opt))
      {
       if (SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель")
       {
        MessageDlg("Задание с делом за номером - "+ d + " к сожалению не найдено !!! Поищите задание пожалуйста на другом участке или за другой день или временной интервал!!! ",mtWarning,TMsgDlgButtons() << mbOK,0);
       }else
       {
        MessageDlg("Задание с делом за номером - "+ d + " к сожалению не найдено !!! Поищите задание пожалуйста за другой день или временной интервал!!! ",mtWarning,TMsgDlgButtons() << mbOK,0);
       }
       Edit1->Text="";
       return;
      }
     }
     else
     {
     MessageDlg("Задание с делом за номером - "+ d + " к сожалению не создано!!! Заведите задание пожалуйста !!! ",mtWarning,TMsgDlgButtons() << mbOK,0);
     Edit1->Text="";
     return;
     }
   }else
   {
     MessageDlg("Задание с делом за номером - "+ d + " к сожалению отстутвует в текущей выплатной базе!!! Обратитесь в администрацию Вашего района пожалуйста !!! ",mtWarning,TMsgDlgButtons() << mbOK,0);
     Edit1->Text="";
     return;
   }
  if(Timer1->Enabled==true) Timer1->Enabled=false;
  Timer1->Enabled=true;
  }
  else
  {
   MessageDlg("Неправильно набран номер!!!.\n Поиск невозможен!!!\n Введите правильный номер например 756211. Удачи!!!",mtWarning,TMsgDlgButtons() << mbOK,0);
   Edit1->Text="";
  }
}
//---------------------------------------------------------------------------

void __fastcall TAccountsJournalForm::Timer1Timer(TObject *Sender)
{
TLocateOptions opt;
opt<<loPartialKey<<loCaseInsensitive;
AnsiString d=0;

  Timer1->Enabled=false;
  if(Edit1->Text.IsEmpty()) return;
  if(IsNum(Edit1->Text.Trim()))
  {

  if(Edit1->Text.Length() <= 6 && IsNum(Edit1->Text.Trim())){
  d=Edit1->Text.Trim();
  SG_DS->Locate("LCHET1",d,opt);
  Edit1->Text="";
  }else
  {
   MessageDlg("Неправильно набран номер!!!.\n Поиск невозможен!!!\n Введите правильный номер например 756211. Удачи!!!",mtWarning,TMsgDlgButtons() << mbOK,0);
   Edit1->Text="";
  }

  }
  else
  {
   MessageDlg("Неправильно набран номер!!!.\n Поиск невозможен!!!\n Введите правильный номер например 756211. Удачи!!!",mtWarning,TMsgDlgButtons() << mbOK,0);
   Edit1->Text="";
  }

}
//---------------------------------------------------------------------------



void __fastcall TAccountsJournalForm::SelectPerClick(TObject *Sender)
{
TSelectPeriodForm *SPFAF;

  try
  {
    SPFAF=new TSelectPeriodForm(this,date1,date2);
  }
  catch (Exception &exc)
  {
    MessageDlg("Ошибка создания формы SelectPeriodForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(SPFAF->ShowModal()==mrOk)
  {
    date1=SPFAF->getDate1();
    date2=SPFAF->getDate2();
    filter=None;
    FilterCustomerID=FilterUserID=0;
    setMainHeader();
    loadProperties();
    LoadDataSet();
  }
  if(SPFAF!=NULL) delete SPFAF;

}
//---------------------------------------------------------------------------

void __fastcall TAccountsJournalForm::CheckBox1Click(TObject *Sender)
{
      LoadDataSet();
      setMainHeader();
}
//---------------------------------------------------------------------------
void __fastcall TAccountsJournalForm::provkassa(void)
{
AnsiString sql;
int lchet;
int nsk=0;
int ns=0;
int pr1=0;
int pr2=0;

  DB1->Close();
  DB1->SQLs->SelectSQL->Clear();
  sql="select * from SGB";
  sql+=" where PRICH='н/д'";
  sql+=" and LCHET1 NOT IN ('Прошврем','раздел 1')";
  sql+=" and METKA1 IN ("+SaleBookDM->UserIndex + ")";

  DB1->SQLs->SelectSQL->Add(sql);
  try
  {
    DB1->Open();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  }
  DB1->Last();

  DB1->First();
  nsk=0;
  ns=0;
  while(!DB1->Eof)
  {
      lchet=DB1->FieldByName("LCHET")->AsInteger;
      pr1=0;
      pr2=0;

      sql="select count (distinct g.lchet) as CR  from SGB g where LCHET = "+IntToStr(lchet);
      sql+=" and PRICH=''";
      sql+=" and LCHET1 NOT IN ('Прошврем','раздел 1')";

      TempQ->Close();
      TempQ->SQL->Clear();
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }
      if (TempQ->FieldByName("CR")->AsInteger >=0 ) pr1=TempQ->FieldByName("CR")->AsInteger;

      sql="select count (distinct g.lchet) as CR  from SGB g where LCHET = "+IntToStr(lchet);
      sql+=" and PRICH<>'н/д'";
      sql+=" and LCHET1 NOT IN ('Прошврем','раздел 1')";
      TempQ->Close();
      TempQ->SQL->Clear();
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }
      if (TempQ->FieldByName("CR")->AsInteger >=0 ) pr2=TempQ->FieldByName("CR")->AsInteger;

      TQ->Transaction->StartTransaction();
      TQ->Close();
      TQ->SQL->Clear();
      sql="update SGB set";
      if ( pr1+pr2 >0 ) sql+=" KASSA=1"; else sql+=" KASSA=0";
      sql+=" where LCHET="+IntToStr(lchet);
      sql+=" and PRICH='н/д'";
      TQ->SQL->Add(sql);
      try
      {
        TQ->ExecQuery();
        nsk++;
      }
      catch (Exception &exc)
      {
        MessageDlg("ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
        TQ->Transaction->Rollback();
      }
      TQ->Transaction->Commit();

      DB1->Next();
      ns++;
    }

DB1->Close();
}

