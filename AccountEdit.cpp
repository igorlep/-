//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <math.h>

//#include "Contractors.h"
//#include "utils.h"
#include "Users.h"
#include "DataModule.h"
#include "Nomenclature.h"
//#include "NDS.h"
#include "Main.h"
#include "AccountEdit.h"
#include "BrowseF.h"
#include "EI.h"
#include "utils.h"
#include "AccauntsJournal.h"
#include "MoveRecords.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "SmrtPanel"
#pragma link "DBCtrlsEh"
#pragma link "DBLookupEh"
#pragma link "ToolEdit"
#pragma link "Placemnt"
#pragma link "RxCalc"
#pragma link "FIBDataSet"
#pragma link "pFIBDataSet"
#pragma link "FIBQuery"
#pragma link "pFIBQuery"
#pragma link "RXDBCtrl"
#pragma link "FIBDatabase"
#pragma link "pFIBDatabase"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
//Создание нового задания
__fastcall TAccountEditForm::TAccountEditForm(TComponent* Owner, TDateTime date, unsigned short number)
        : TForm(Owner)
{
AnsiString sql;
unsigned short d;

  FormStorage1->IniFileName=MainForm->WorkDir+"SB_2009.ini";
  FormStorage1->IniSection="AccountsEditForm";

  ErrFLG=false;
  LoadFLG=true;
  Caption="Новое задание";
  NewFLG=true;
  CountDate=date;
  Number=number;
  UserName->Caption=SaleBookDM->UserName;

  //Ищем в таблице ACCOUNTS_TEMP задание с номером Number и открываем его для редактирования
  C_DS=AccountsTempDS;
  C_DS->Close();
  C_DS->SQLs->SelectSQL->Clear();
  sql="select a.*, c.DESCRIPTION as CUSTOMER_NAME, u.LOGIN as USER_NAME";
  sql+=" from ACCOUNTS_TEMP a";
  sql+=" left outer join EI c on c.ID=a.CUSTOMER_ID";
  sql+=" left outer join USERS u on u.ID=a.USER_ID";
  sql+=" where a.ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
  sql+=" and a.COUNT_DATE='"+CountDate.DateString()+"'";
  sql+=" and a.COUNT_NUMBER="+IntToStr(Number);
  C_DS->SQLs->SelectSQL->Add(sql);
  try
  {
    C_DS->Open();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    ErrFLG=true;
    return;
  }
  if(C_DS->RecordCount == 0)
  { MessageDlg("В таблице ACCOUNTS_TEMP нет задания с номером - "+IntToStr(Number),mtError,TMsgDlgButtons() << mbOK,0);
    C_DS->Close();
    ErrFLG=true;
    return;
  }
  C_DS->Edit();
  C_DS->FieldByName("USER_ID")->AsInteger=SaleBookDM->UserID;
  C_DS->FieldByName("COUNT_TYPE")->AsInteger=0;
  C_DS->FieldByName("M")->AsInteger=Month(CountDate);

  //Убираем все записи пользователя из таблицы SOLD_GOODS_TEMP
  TempQ->Close();
  TempQ->SQL->Clear();
//  if(SaleBookDM->UserRole!="Администратор")
//  {
  sql="delete from SGBT where USER_ID="+IntToStr(SaleBookDM->UserID);
//  }
//  else
//  {
//  sql="delete from SGBT where USER_ID="+IntToStr(DS->FieldByName("USER_ID")->AsInteger);
//  }
  TempQ->SQL->Add(sql);
  TempQ->ExecQuery();

  //Подготавливаем таблице SOLD_GOODS_TEMP для работы
  SG_DST=((TpFIBDataSet*)(SoldGoodsGrid->DataSource->DataSet));
  SG_DST->Close();
  SG_DST->SQLs->SelectSQL->Clear();
  sql="select g.*";
  sql+=" from SGBT g";
//  if(SaleBookDM->UserRole!="Администратор")
//  {
  sql+=" where USER_ID="+IntToStr(SaleBookDM->UserID);
  sql+=" order by g.FAMILY,g.NAME,g.FATHER";
//  }
//  else
//  {
//  sql+=" where USER_ID=" +IntToStr(DS->FieldByName("USER_ID")->AsInteger);
//  }

//  sql+=" where USER_ID="+IntToStr(SaleBookDM->UserID);
  SG_DST->SQLs->SelectSQL->Add(sql);
  try
  {
    SG_DST->Open();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка открытия таблицы SOLD_GOODS_TEMP\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(SG_DST->RecordCount>0) SG_DST->First();
}
//---------------------------------------------------------------------------
//Редактирование существующего счета
__fastcall TAccountEditForm::TAccountEditForm(TComponent* Owner,TDataSet *DS)
        : TForm(Owner)
{
AnsiString sql;

  FormStorage1->IniFileName=MainForm->WorkDir+"SB_2009.ini";
  FormStorage1->IniSection="AccountsEditForm";

  ErrFLG=false;
  NewFLG=false;
  LoadFLG=true;

  Caption="Редактирование задания";
  CountDate=DS->FieldByName("COUNT_DATE")->AsDateTime;
  Number=DS->FieldByName("COUNT_NUMBER")->AsInteger;
  RS_ID=DS->FieldByName("RS_ID")->AsInteger;
  U_ID=DS->FieldByName("USER_ID")->AsInteger;

  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") UserName->Caption=SaleBookDM->UserName; else UserName->Caption=DS->FieldByName("Avtor")->AsString;

  //На всякий случай чистим таблицы ACCOUNTS_TEMP и SOLD_GOODS_TEMP
  TempQ->Close();
  TempQ->SQL->Clear();
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql="delete from ACCOUNTS_TEMP where USER_ID="+IntToStr(SaleBookDM->UserID); else sql="delete from ACCOUNTS_TEMP where USER_ID="+IntToStr(U_ID);

  TempQ->SQL->Add(sql);
  try
  {
    TempQ->ExecQuery();
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    ErrFLG=true;
    return;
  }
  TempQ->Close();
  TempQ->SQL->Clear();
//  if(SaleBookDM->UserRole!="Администратор") sql="delete from SGBT where USER_ID="+IntToStr(SaleBookDM->UserID); else sql="delete from SGBT ";
//  sql="delete from SGBT where USER_ID="+IntToStr(SaleBookDM->UserID);
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql="delete from SGBT where USER_ID="+IntToStr(SaleBookDM->UserID); else sql="delete from SGBT where USER_ID="+IntToStr(U_ID);

  TempQ->SQL->Add(sql);
  try
  {
    TempQ->ExecQuery();
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    ErrFLG=true;
    return;
  }

  //Копируем запись из таблицы ACCOUNTS в таблицу ACCOUNTS_TEMP
  TDateTime date;
  TempQ->Close();
  TempQ->SQL->Clear();


  sql="insert into ACCOUNTS_TEMP select ORG_ID,COUNT_DATE,COUNT_NUMBER,CUSTOMER_ID,USER_ID,COUNT_TYPE,M,Y from ACCOUNTS where";
  sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
  sql+=" and COUNT_DATE='"+CountDate.DateString()+"'";
  sql+=" and COUNT_NUMBER="+IntToStr(Number);
  TempQ->SQL->Add(sql);
  try
  {
    TempQ->ExecQuery();
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    ErrFLG=true;
    return;
  }
  TempQ->Close();

  //Настраиваем C_DS на таблицу ACCOUNTS_TEMP
  C_DS=((TpFIBDataSet*)(AccountsTempS->DataSet));
  C_DS->Close();
  C_DS->SQLs->SelectSQL->Clear();
  sql="select a.*, c.DESCRIPTION as CUSTOMER_NAME, u.LOGIN as USER_NAME";
  sql+=" from ACCOUNTS_TEMP a";
  sql+=" left outer join EI c on c.ID=a.CUSTOMER_ID";
  sql+=" left outer join USERS u on u.ID=a.USER_ID";
  sql+=" where a.ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
  sql+=" and a.COUNT_DATE='"+CountDate.DateString()+"'";
  sql+=" and a.COUNT_NUMBER="+IntToStr(Number);
  C_DS->SQLs->SelectSQL->Add(sql);
  try
  {
    C_DS->Open();
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    ErrFLG=true;
    return;
  }

  //Проверяем, есть ли записи в таблице SOLD_GOODS_BOOK для выбранного счета
  TempQ->Close();
  TempQ->SQL->Clear();
  sql="select COUNT_NUMBER from SGB where";
  sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
  sql+=" and COUNT_DATE='"+CountDate.DateString()+"'";
  sql+=" and COUNT_NUMBER="+IntToStr(Number);
  TempQ->SQL->Add(sql);
  try
  {
    TempQ->ExecQuery();
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    ErrFLG=true;
    return;
  }

  if(TempQ->RecordCount > 0)
  { //Копируем записи о поручениях в таблицу SOLD_GOODS_TEMP
    TempQ->Close();
    TempQ->SQL->Clear();
    sql="insert into SGBT";
    sql+=" select a.USER_ID, s.LCHET1, s.SUMMA, s.WORD, s.METKA, \
s.NEOPL,s.PNN,s.LCHET,s.FAMILY,s.NAME,s.FATHER,s.KOD,s.C,s.DOC,s.SERIA,s.NOMER, \
s.DOST, s.D_VIPL, s.ULIC, s.ADRES, s.CHEL, s.METKA1, s.VNOM, s.PRICH, s.IST, s.BSUMMA, s.BWORD, s.FAKT_CHEL, s.FAKT_DAT, s.NSP, s.KEM_VID, s.DATA_VID , s.KODPEN, s.FOND , s.KASSA from ACCOUNTS a";
    sql+=" left outer join SGB s on a.ORG_ID=s.ORG_ID \
and a.COUNT_DATE=s.COUNT_DATE and a.COUNT_NUMBER=s.COUNT_NUMBER";
    sql+=" where a.ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
    sql+=" and a.COUNT_DATE='"+CountDate+"'";
    sql+=" and a.COUNT_NUMBER="+IntToStr(Number);
//    sql+=" order by s.FAMILY,s.NAME,s.FATHER";
  sql+=" order by s.LCHET,s.LCHET1,s.FAMILY,s.NAME,s.FATHER";

    TempQ->SQL->Add(sql);
    try
    {
      TempQ->ExecQuery();
    }
    catch(const Exception &exc)
    { MessageDlg("Ошибка insert into SOLD_GOODS_TEMP\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      ErrFLG=true;
      return;
    }
  }
  TempQ->Close();

  //Настраиваем SG_DST и SN_DS
  SG_DST=((TpFIBDataSet*)(SoldGoodsGrid->DataSource->DataSet));
//  SG_DST->Close();
  SG_DST->SQLs->SelectSQL->Clear();
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель")
  {
  sql="select g.* from SGBT g where USER_ID="+IntToStr(SaleBookDM->UserID);
  }
  else
  {
  sql="select g.* from SGBT g where USER_ID="+IntToStr(U_ID);
  }
  sql+=" order by g.FAMILY,g.NAME,g.FATHER";
  SG_DST->SQLs->SelectSQL->Add(sql);
  try
  {
    SG_DST->Open();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка - "+SG_DST->SQLs->SelectSQL->Text+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    ErrFLG=true;
    return;
  }

}
//---------------------------------------------------------------------------
void __fastcall TAccountEditForm::FormDestroy(TObject *Sender)
{
AnsiString sql;
TpFIBDataSet *DSZ;

DSZ=((TpFIBDataSet*)(AccountsJournalForm->AccountsGrid->DataSource->DataSet));
U_ID=DSZ->FieldByName("USER_ID")->AsInteger;

  //Чистим таблицу ACCOUNTS_TEMP
  TempQ->Close();
  TempQ->SQL->Clear();
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql="delete from ACCOUNTS_TEMP where USER_ID="+IntToStr(SaleBookDM->UserID); else sql="delete from ACCOUNTS_TEMP where USER_ID="+IntToStr(U_ID);
  TempQ->SQL->Add(sql);
  try
  {
    TempQ->ExecQuery();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка удаления записей из таблицы ACCOUNTS_TEMP\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  }

  TempQ->Close();
  TempQ->SQL->Clear();
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql="delete from SGBT where USER_ID="+IntToStr(SaleBookDM->UserID); else sql="delete from SGBT where USER_ID="+IntToStr(U_ID);
  TempQ->SQL->Add(sql);
  try
  {
    TempQ->ExecQuery();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка удаления записей из таблицы ACCOUNTS_TEMP\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  }

  TempQ->Close();
  SG_DST->Close();
  C_DS->Close();
}
//---------------------------------------------------------------------------
void __fastcall TAccountEditForm::FormShow(TObject *Sender)
{
TpFIBQuery *Q=SaleBookDM->TempQuery;
AnsiString sql;
int indops;


  if(ErrFLG) Close();
  else
  {
   Label19->Caption="";
   Label19->Visible=false;
   if (SoldGoodsGrid->SelectedRows->Count==0)
   {
   AddButton->Enabled=true;
   OstButton->Enabled=false;
   }
   else
   {
   AddButton->Enabled=false;
   OstButton->Enabled=true;
   }
    if(NewFLG)
    {
    CustomerEdit->SetFocus();
    Label4->Visible=true;
    Label6->Visible=true;
    Label7->Visible=true;
    Label8->Visible=true;
    Label9->Visible=true;
    StaticText1->Visible = true;
    StaticText4->Visible = true;
    StaticText5->Visible = true;
    StaticText6->Visible = true;
    StaticText1->Caption ="0";
    StaticText4->Caption ="0.00";
    StaticText5->Caption ="0.00";
    StaticText6->Caption ="0.00";

    Label10->Visible=false;
    Label11->Visible=false;
    Label12->Visible=false;
    Label13->Visible=false;
    Label14->Visible=false;
    Label15->Visible=false;
    Label16->Visible=false;
    Label17->Visible=false;
    StaticText2->Visible = false;
    StaticText7->Visible = false;
    StaticText8->Visible = false;
    StaticText3->Visible = false;
    StaticText9->Visible = false;
    StaticText10->Visible = false;

    AddButton->Enabled = true;
    SaveButton->Enabled = false;
    EditButton->Enabled = false;
    CancelButton->Enabled = false;
    if(SG_DST->RecordCount>0)
    {
    DelButton->Enabled = true;
    }else
    {
    DelButton->Enabled = false;
    }

    SoldGoodsGrid->Columns->Items[7]->Visible = false;
    SoldGoodsGrid->Columns->Items[8]->Visible = false;
    SoldGoodsGrid->ReadOnly = true;

    CustomerEdit->Enabled=true;
    NumberEdit->Enabled=true;
    DateEdit->Enabled=true;
    MoveButton->Enabled=false;
    }
    else
    {
    SoldGoodsGrid->SetFocus();
    Label4->Visible=false;
    Label6->Visible=false;
    Label7->Visible=false;
    Label8->Visible=false;
    Label9->Visible=false;
    StaticText1->Visible = false;
    StaticText4->Visible = false;
    StaticText5->Visible = false;
    StaticText6->Visible = false;

    Label10->Visible=true;
    Label11->Visible=true;
    Label12->Visible=true;
    Label13->Visible=true;
    Label14->Visible=true;
    Label15->Visible=true;
    Label16->Visible=true;
    Label17->Visible=true;
    StaticText2->Visible = true;
    StaticText7->Visible = true;
    StaticText8->Visible = true;
    StaticText3->Visible = true;
    StaticText9->Visible = true;
    StaticText10->Visible = true;

//    StaticText2->Caption ="0";
//    StaticText3->Caption ="0";
//    StaticText7->Caption ="0.00";
//    StaticText8->Caption ="0.00";
//    StaticText9->Caption ="0.00";
//    StaticText10->Caption ="0.00";
    AddButton->Enabled = true;
    if(SG_DST->RecordCount>0)
    {
    DelButton->Enabled = true;
    SaveButton->Enabled = true;
    EditButton->Enabled = true;
    CancelButton->Enabled = true;
    }else
    {
    DelButton->Enabled = false;
    SaveButton->Enabled = false;
    EditButton->Enabled = false;
    CancelButton->Enabled = false;
    }

    SoldGoodsGrid->Columns->Items[7]->Visible = true;
    Q->Close();
    Q->SQL->Clear();
    sql="select INDEXOPS as IND from NOMENCLATURE";
    sql+=" where CODP="+IntToStr(C_DS->FieldByName("CUSTOMER_ID")->AsInteger);
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
    SoldGoodsGrid->Options.Clear();
    SoldGoodsGrid->Options << dgEditing << dgAlwaysShowEditor << dgTitles << dgIndicator << dgColumnResize << dgColLines << dgRowLines << dgTabs << dgAlwaysShowSelection << dgConfirmDelete << dgCancelOnExit;
    }
    else
    {
    SoldGoodsGrid->Columns->Items[7]->Visible = false;
    SoldGoodsGrid->Columns->Items[8]->Visible = true;
    SoldGoodsGrid->Options.Clear();
    SoldGoodsGrid->Options << dgColumnResize << dgColLines << dgTitles << dgRowLines << dgTabs << dgRowSelect << dgAlwaysShowSelection << dgConfirmDelete << dgCancelOnExit << dgMultiSelect;
    }
    }
    else
    {
//    MessageDlg("Данный почтальон не работает на участках!!! Аварийный выход из процедуры!!! - ",mtError,TMsgDlgButtons() << mbOK,0);
//    return;
    }

    SoldGoodsGrid->ReadOnly = false;

    CustomerEdit->Enabled=false;
    NumberEdit->Enabled=false;
    DateEdit->Enabled = false;
    if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель")
    {
     MoveButton->Enabled=false;
    }
    else
    {
    MoveButton->Enabled=false;
    }
    }
  }
updateset();
ras();
}
//---------------------------------------------------------------------------
//Выбор заказчика
void __fastcall TAccountEditForm::CustomerEditButtonClick(
      TObject *Sender)
{
TDateTime dt=TDateTime(DateEdit->Text);
AnsiString sql;
unsigned short dv,yv,mv;
unsigned short ytw,mtw,dtw;

dt.DecodeDate(&yv,&mv,&dv);
SaleBookDM->yvip=yv;
SaleBookDM->mvip=mv;
SaleBookDM->dvip=dv;

TDateTime dtoday=Date()+9;
dtoday.DecodeDate(&ytw,&mtw,&dtw);
TDateTime lockDate;
unsigned short yl,ml,dl;

lockDate=SaleBookDM->GetConstValue(SaleBookDM->OrganizationID,"LOCK_EDIT_DATE");
lockDate.DecodeDate(&yl,&ml,&dl);


  if(dv>=23)
  {
    MessageDlg("Дата выплаты должна быть до 22 числа текущего месяца !!!",mtWarning,TMsgDlgButtons() << mbOK,0);
    DateEdit->SetFocus();
    return;
  }

  if(mv!=ml)
  {
    MessageDlg("Дата выплаты НЕВЕРНАЯ !!!",mtWarning,TMsgDlgButtons() << mbOK,0);
    DateEdit->SetFocus();
    return;
  }

  if(yv!=yl)
  {
    MessageDlg("Дата выплаты НЕВЕРНАЯ !!!",mtWarning,TMsgDlgButtons() << mbOK,0);
    DateEdit->SetFocus();
    return;
  }


TpFIBDataSet *DSZ;
DSZ=((TpFIBDataSet*)(AccountsJournalForm->AccountsGrid->DataSource->DataSet));


  if(!Application->FindComponent("EIForm"))
  {
    try
    {
      Application->CreateForm(__classid(TEIForm), &EIForm);
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка создания формы EIForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
  }
    EIForm->LookUpRecord(C_DS->FieldByName("CUSTOMER_ID")->AsInteger);
    if(EIForm->ShowModal()==mrOk)
    {

       TempQ->Close();
       TempQ->SQL->Clear();
       if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql="delete from SGBT where USER_ID="+IntToStr(SaleBookDM->UserID); else sql="delete from SGBT where USER_ID="+IntToStr(DSZ->FieldByName("USER_ID")->AsInteger);
       TempQ->SQL->Add(sql);
       TempQ->ExecQuery();
       TempQ->Close();
       updateset();


      if(C_DS->State!=dsEdit) C_DS->Edit();
      C_DS->FieldByName("CUSTOMER_ID")->AsInteger=EIForm->DS->FieldByName("ID")->AsInteger;
      C_DS->FieldByName("CUSTOMER_NAME")->AsString=EIForm->DS->FieldByName("DESCRIPTION")->AsString;
      C_DS->FieldByName("COUNT_DATE")->AsDateTime=dt;
      C_DS->Post();
      DateEdit->Enabled=true;
      TempQ->Close();
      TempQ->SQL->Clear();
      sql="select INDEXOPS as INDOPS from NOMENCLATURE n where CODP="+IntToStr(C_DS->FieldByName("CUSTOMER_ID")->AsInteger);
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


     if (!TempQ->FieldByName("INDOPS")->IsNull)
     {
      AddButton->Enabled=true;
      if (TempQ->FieldByName("INDOPS")->AsInteger > 0)
      {
       otbor(dv,C_DS->FieldByName("CUSTOMER_ID")->AsInteger);
      }
      else
      {
//       otborforkassa(dv,C_DS->FieldByName("CUSTOMER_ID")->AsInteger);
      }
     }
     else
     {
      if(MessageDlg("ВНИМАНИЕ!!! Вы уверены, что хотите данному почтальону который не работает на данном участке создать НОВОЕ поручение ? ",mtConfirmation,TMsgDlgButtons() << mbOK << mbCancel,0)==mrOk)
      {
      AddButton->Enabled=true;
      otbor(dv,C_DS->FieldByName("CUSTOMER_ID")->AsInteger);
      }else
      {
      MessageDlg("Данный почтальон НЕ РАБОТАЕТ !!! Аварийный выход из процедуры!!! ",mtError,TMsgDlgButtons() << mbOK,0);
      AddButton->Enabled=false;
      return;
      }
    }
   } 
}

void __fastcall TAccountEditForm::ras(void)
{
AnsiString sql;
TpFIBDataSet *DSZ;
DSZ=((TpFIBDataSet*)(AccountsJournalForm->AccountsGrid->DataSource->DataSet));
TpFIBQuery *Q=SaleBookDM->TempQuery;
int indops=0;

prh=0.00;
razdh=0.00;


  TempQ->Close();
  TempQ->SQL->Clear();
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель"){
  sql="select distinct count (n.lchet) as CR from SGBT n where USER_ID="+IntToStr(SaleBookDM->UserID) + " and LCHET1 NOT IN ('Прошврем','раздел 1')";
  }
  else
  {
  sql="select distinct count (n.lchet) as CR from SGBT n where USER_ID="+IntToStr(DSZ->FieldByName("USER_ID")->AsInteger) + " and LCHET1 NOT IN ('Прошврем','раздел 1')";
  }
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

  if (TempQ->FieldByName("CR")->AsInteger > 0) StaticText1->Caption=IntToStr(TempQ->FieldByName("CR")->AsInteger); else StaticText1->Caption="0";

  TempQ->Close();
  TempQ->SQL->Clear();
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель"){
  sql="select distinct sum (n.summa) as summav from SGBT n where LCHET1 NOT IN ('Прошврем','раздел 1') and USER_ID="+IntToStr(SaleBookDM->UserID);
  }else
  {
  sql="select distinct sum (n.summa) as summav from SGBT n where LCHET1 NOT IN ('Прошврем','раздел 1') and USER_ID="+IntToStr(DSZ->FieldByName("USER_ID")->AsInteger);
  }
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

  if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) StaticText4->Caption=AnsiString().sprintf("%.2lf",TempQ->FieldByName("SUMMAV")->AsFloat); else StaticText4->Caption="0.00";

  TempQ->Close();
  TempQ->SQL->Clear();
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель"){
  sql="select distinct sum (n.summa) as summav from SGBT n where LCHET1 IN ('Прошврем') and USER_ID="+IntToStr(SaleBookDM->UserID);
  }else
  {
  sql="select distinct sum (n.summa) as summav from SGBT n where LCHET1 IN ('Прошврем') and USER_ID="+IntToStr(DSZ->FieldByName("USER_ID")->AsInteger);
  }
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

  if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) StaticText5->Caption=AnsiString().sprintf("%.2lf",TempQ->FieldByName("SUMMAV")->AsFloat); else StaticText5->Caption="0.00";

  TempQ->Close();
  TempQ->SQL->Clear();
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель"){
  sql="select distinct sum (n.summa) as summav from SGBT n where LCHET1 IN ('раздел 1') and USER_ID="+IntToStr(SaleBookDM->UserID);
  }else
  {
  sql="select distinct sum (n.summa) as summav from SGBT n where LCHET1 IN ('раздел 1') and USER_ID="+IntToStr(DSZ->FieldByName("USER_ID")->AsInteger);
  }
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

  if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) StaticText6->Caption=AnsiString().sprintf("%.2lf",TempQ->FieldByName("SUMMAV")->AsFloat); else StaticText6->Caption="0.00";

  TempQ->Close();
  TempQ->SQL->Clear();
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель"){
  sql="select count (n.lchet) as CR from SGBT n where PRICH = '' and USER_ID="+IntToStr(SaleBookDM->UserID)+ " and LCHET1 NOT IN ('Прошврем','раздел 1')";
  }else
  {
  sql="select count (n.lchet) as CR from SGBT n where PRICH = '' and USER_ID="+IntToStr(DSZ->FieldByName("USER_ID")->AsInteger)+ " and LCHET1 NOT IN ('Прошврем','раздел 1')";
  }
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

  if (TempQ->FieldByName("CR")->AsInteger > 0) StaticText2->Caption=IntToStr(TempQ->FieldByName("CR")->AsInteger); else StaticText2->Caption="0";

  TempQ->Close();
  TempQ->SQL->Clear();
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель"){
  sql="select distinct sum (n.summa) as summav from SGBT n where PRICH = '' and LCHET1 NOT IN ('раздел 1','Прошврем') and USER_ID="+IntToStr(SaleBookDM->UserID);
  }else
  {
  sql="select distinct sum (n.summa) as summav from SGBT n where PRICH = '' and LCHET1 NOT IN ('раздел 1','Прошврем') and USER_ID="+IntToStr(DSZ->FieldByName("USER_ID")->AsInteger);
  }
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

  if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) StaticText7->Caption=AnsiString().sprintf("%.2lf",TempQ->FieldByName("SUMMAV")->AsFloat); else StaticText7->Caption="0.00";

  TempQ->Close();
  TempQ->SQL->Clear();
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель"){
  sql="select distinct sum (n.summa) as summav from SGBT n where PRICH = '' and LCHET1 IN ('раздел 1','Прошврем') and USER_ID="+IntToStr(SaleBookDM->UserID);
  }else
  {
  sql="select distinct sum (n.summa) as summav from SGBT n where PRICH = '' and LCHET1 IN ('раздел 1','Прошврем') and USER_ID="+IntToStr(DSZ->FieldByName("USER_ID")->AsInteger);
  }
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

  if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) StaticText8->Caption=AnsiString().sprintf("%.2lf",TempQ->FieldByName("SUMMAV")->AsFloat); else StaticText8->Caption="0.00";


  TempQ->Close();
  TempQ->SQL->Clear();
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель"){
  sql="select count (n.lchet) as CR from SGBT n where PRICH <> '' and USER_ID="+IntToStr(SaleBookDM->UserID) + " and LCHET1 NOT IN ('Прошврем','раздел 1')";
  }else
  {
  sql="select count (n.lchet) as CR from SGBT n where PRICH <> '' and USER_ID="+IntToStr(DSZ->FieldByName("USER_ID")->AsInteger) + " and LCHET1 NOT IN ('Прошврем','раздел 1')";
  }
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

  if (TempQ->FieldByName("CR")->AsInteger > 0) StaticText3->Caption=IntToStr(TempQ->FieldByName("CR")->AsInteger); else StaticText3->Caption="0";

  TempQ->Close();
  TempQ->SQL->Clear();
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель"){
  sql="select distinct sum (n.summa) as summav from SGBT n where PRICH <> '' and LCHET1 NOT IN ('раздел 1','Прошврем') and USER_ID="+IntToStr(SaleBookDM->UserID);
  }else
  {
  sql="select distinct sum (n.summa) as summav from SGBT n where PRICH <> '' and LCHET1 NOT IN ('раздел 1','Прошврем') and USER_ID="+IntToStr(DSZ->FieldByName("USER_ID")->AsInteger);
  }
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

  if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) StaticText9->Caption=AnsiString().sprintf("%.2lf",TempQ->FieldByName("SUMMAV")->AsFloat); else StaticText9->Caption="0.00";

  TempQ->Close();
  TempQ->SQL->Clear();
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель"){
  sql="select distinct sum (n.summa) as summav from SGBT n where PRICH <> '' and LCHET1 IN ('раздел 1','Прошврем') and USER_ID="+IntToStr(SaleBookDM->UserID);
  }else
  {
  sql="select distinct sum (n.summa) as summav from SGBT n where PRICH <> '' and LCHET1 IN ('раздел 1','Прошврем') and USER_ID="+IntToStr(DSZ->FieldByName("USER_ID")->AsInteger);
  }
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

  if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) StaticText10->Caption=AnsiString().sprintf("%.2lf",TempQ->FieldByName("SUMMAV")->AsFloat); else StaticText10->Caption="0.00";


}

void __fastcall TAccountEditForm::otbor(int dayv, int kodpost)
{
AnsiString sql,dni;
TpFIBDataSet *DSZ;
DSZ=((TpFIBDataSet*)(AccountsJournalForm->AccountsGrid->DataSource->DataSet));

TDateTime dt=Date();
TDateTime lockDate;
unsigned short yl,ml,dl;
unsigned short y,m,d;



  lockDate=SaleBookDM->GetConstValue(SaleBookDM->OrganizationID,"LOCK_EDIT_DATE");
  lockDate.DecodeDate(&yl,&ml,&dl);
  dt.DecodeDate(&y,&m,&d);
  if (ml != m)
  {
   if (m==12)
   {
   m=1;
   y++;
   }else
   {
   m++;
   }
  }


      //Проверяем нет ли сдвоенных дней выплат определяем дни выплаты!!!
    TempQ->Close();
    TempQ->SQL->Clear();
    sql="select * from EID where";
    sql+=" IDAY="+IntToStr(dayv);
    TempQ->SQL->Add(sql);
    try
    {
      TempQ->ExecQuery();
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка TempQ (ACCOUNTS)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
    if(TempQ->RecordCount!=0)
    {
    dni=TempQ->FieldByName("DAYS")->AsString.Trim();
    }else
    {
    dni=IntToStr(dayv);
    }



//   Убираем все записи пользователя из таблицы SOLD_GOODS_TEMP
  TempQ->Close();
  TempQ->SQL->Clear();
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql="delete from SGBT where USER_ID="+IntToStr(SaleBookDM->UserID); else sql="delete from SGBT where USER_ID="+IntToStr(DSZ->FieldByName("USER_ID")->AsInteger);
  TempQ->SQL->Add(sql);
  TempQ->ExecQuery();
  TempQ->Close();
  updateset();

  NDOST_DS=NDOST;
  NDOST_DS->Close();
  NDOST_DS->SQLs->SelectSQL->Clear();
  sql="select distinct a.* ";
  sql+=" from NDOST a where ";
  sql+=" a.M="+IntToStr(m);
  sql+=" and a.Y="+IntToStr(y);
  sql+=" and a.lchet not in(select lchet from dov";
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql+=" where dov.METKA1 IN ("+SaleBookDM->UserIndex + "))"; else sql+=")";
  sql+=" and a.lchet not in(select lchet from sgb";
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql+=" where sgb.METKA1 IN ("+SaleBookDM->UserIndex + "))"; else sql+=")";
  sql+=" and a.D_VIPL IN ( "+ dni;
  sql+=" ) and a.CHEL="+IntToStr(kodpost);
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql+=" and a.METKA1 IN ("+SaleBookDM->UserIndex + ")";
  sql+=" order by a.FAMILY,a.NAME,a.FATHER,a.LCHET1";


  NDOST_DS->SQLs->SelectSQL->Add(sql);
  try
  {
    NDOST_DS->Open();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(NDOST_DS->RecordCount > 0)
  {
  int i=1;
  NDOST_DS->First();
  while(!NDOST_DS->Eof)
  {
      TempQ->Close();
      TempQ->SQL->Clear();
      sql="insert into SGBT(USER_ID,LCHET1,SUMMA,WORD,METKA,NEOPL,PNN,LCHET,FAMILY,NAME,\
      FATHER,KOD,C,DOC,SERIA,NOMER,DOST,D_VIPL,ULIC,ADRES,CHEL,METKA1,VNOM,PRICH,IST,BSUMMA,";
      sql+="BWORD,FAKT_CHEL,FAKT_DAT,NSP,KEM_VID,DATA_VID,KODPEN,FOND) values(";
      if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql+=IntToStr(SaleBookDM->UserID)+",'"; else sql+=IntToStr(DSZ->FieldByName("USER_ID")->AsInteger)+",'";
      sql+=NDOST_DS->FieldByName("LCHET1")->AsString.Trim()+"',";
      sql+=AnsiString().sprintf("%.02lf",NDOST_DS->FieldByName("SUMMA")->AsFloat)+",'";
      sql+=NDOST_DS->FieldByName("WORD")->AsString.Trim()+"',";
      sql+=IntToStr(NDOST_DS->FieldByName("METKA")->AsInteger)+",";
      sql+=IntToStr(NDOST_DS->FieldByName("NEOPL")->AsInteger)+",";
      sql+=IntToStr(NDOST_DS->FieldByName("PNN")->AsInteger)+",";
      sql+=IntToStr(NDOST_DS->FieldByName("LCHET")->AsInteger)+",'";
      sql+=NDOST_DS->FieldByName("FAMILY")->AsString.Trim()+"','";
      sql+=NDOST_DS->FieldByName("NAME")->AsString.Trim()+"','";
      sql+=NDOST_DS->FieldByName("FATHER")->AsString.Trim()+"',";
      sql+=IntToStr(NDOST_DS->FieldByName("KOD")->AsInteger)+",'";
      sql+=NDOST_DS->FieldByName("C")->AsDateTime.DateString()+"','";
      sql+=NDOST_DS->FieldByName("DOC")->AsDateTime.DateString()+"','";
      sql+=NDOST_DS->FieldByName("SERIA")->AsString.Trim()+"',";
      sql+=IntToStr(NDOST_DS->FieldByName("NOMER")->AsInteger)+",";
      sql+=IntToStr(NDOST_DS->FieldByName("DOST")->AsInteger)+",";
      sql+=IntToStr(NDOST_DS->FieldByName("D_VIPL")->AsInteger)+",'";
      sql+=NDOST_DS->FieldByName("ULIC")->AsString.Trim()+"','";
      sql+=NDOST_DS->FieldByName("ADRES")->AsString.Trim()+"',";
      sql+=IntToStr(NDOST_DS->FieldByName("CHEL")->AsInteger)+",";
      sql+=IntToStr(NDOST_DS->FieldByName("METKA1")->AsInteger)+",";
      sql+=IntToStr(NDOST_DS->FieldByName("VNOM")->AsInteger)+",'";
      sql+=NDOST_DS->FieldByName("PRICH")->AsString.Trim()+"',";
      sql+=IntToStr(NDOST_DS->FieldByName("IST")->AsInteger)+",";
      sql+=AnsiString().sprintf("%.02lf",NDOST_DS->FieldByName("BSUMMA")->AsFloat)+",'";
      sql+=NDOST_DS->FieldByName("BWORD")->AsString.Trim()+"',";
      sql+=IntToStr(kodpost)+",";
      sql+=IntToStr(dayv)+",";
      sql+=IntToStr(NDOST_DS->FieldByName("NSP")->AsInteger)+",'";
      sql+=NDOST_DS->FieldByName("KEM_VID")->AsString.Trim()+"','";
      sql+=NDOST_DS->FieldByName("DATA_VID")->AsDateTime.DateString()+"',";
      sql+=IntToStr(NDOST_DS->FieldByName("KODPEN")->AsInteger)+",";
      sql+=IntToStr(NDOST_DS->FieldByName("FOND")->AsInteger)+")";
      TempQ->SQL->Add(sql);
      TempQ->ExecQuery();
      i++;
    NDOST_DS->Next();
  }
  TempQ->Close();
  }
  updateset();
}


void __fastcall TAccountEditForm::otborforkassa(int dayv, int kodpost)
{
AnsiString sql,dni;
TpFIBDataSet *DSZ;
DSZ=((TpFIBDataSet*)(AccountsJournalForm->AccountsGrid->DataSource->DataSet));

TDateTime dt=Date();
TDateTime lockDate;
unsigned short yl,ml,dl;
unsigned short y,m,d;


  lockDate=SaleBookDM->GetConstValue(SaleBookDM->OrganizationID,"LOCK_EDIT_DATE");
  lockDate.DecodeDate(&yl,&ml,&dl);
  dt.DecodeDate(&y,&m,&d);
  if (ml != m)
  {
   if (m==12)
   {
   m=1;
   y++;
   }else
   {
   m++;
   }
  }

      //Проверяем нет ли сдвоенных дней выплат определяем дни выплаты!!!
    TempQ->Close();
    TempQ->SQL->Clear();
    sql="select * from EID where";
    sql+=" IDAY="+IntToStr(dayv);
    TempQ->SQL->Add(sql);
    try
    {
      TempQ->ExecQuery();
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка TempQ (ACCOUNTS)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
    if(TempQ->RecordCount!=0)
    {
    dni=TempQ->FieldByName("DAYS")->AsString.Trim();
    }else
    {
    dni=IntToStr(dayv);
    }

//   Убираем все записи пользователя из таблицы SOLD_GOODS_TEMP
  TempQ->Close();
  TempQ->SQL->Clear();
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql="delete from SGBT where USER_ID="+IntToStr(SaleBookDM->UserID); else sql="delete from SGBT where USER_ID="+IntToStr(DSZ->FieldByName("USER_ID")->AsInteger);
  TempQ->SQL->Add(sql);
  TempQ->ExecQuery();
  TempQ->Close();
  updateset();

  NDOST_DS=NDOST;
  NDOST_DS->Close();
  NDOST_DS->SQLs->SelectSQL->Clear();

  sql="select distinct a.* ";
  sql+=" from NDOST a where ";
  sql+=" a.M="+IntToStr(m);
  sql+=" and a.Y="+IntToStr(y);
  sql+=" and a.lchet in(select lchet from dov";
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql+=" where dov.METKA1 IN ("+SaleBookDM->UserIndex + "))"; else sql+=")";
  sql+=" and a.lchet not in(select lchet from sgb";
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql+=" where sgb.METKA1 IN ("+SaleBookDM->UserIndex + "))"; else sql+=")";
  sql+=" and a.D_VIPL IN ( "+dni;
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql+=" ) and a.METKA1 IN ("+SaleBookDM->UserIndex + ")"; else sql+=" ) ";
//  sql+=" and a.DOBAVL = 0 ";
  sql+=" order by a.METKA1,a.FAMILY,a.NAME,a.FATHER";
//  sql+=" order by a.FAMILY,a.NAME,a.FATHER,a.LCHET1";

  NDOST_DS->SQLs->SelectSQL->Add(sql);
  try
  {
    NDOST_DS->Open();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(NDOST_DS->RecordCount == 0)
  {
//    MessageDlg("Проверьте пожалуйста Ваш список до востребования !!! Либо он пустой , либо все получатели ЕДВ занесены в задания кассирам!!!",mtError,TMsgDlgButtons() << mbOK,0);
    NDOST_DS->Close();
    return;
  }

  int i=1;
  NDOST_DS->First();
  while(!NDOST_DS->Eof)
  {
      TempQ->Close();
      TempQ->SQL->Clear();
      sql="insert into SGBT(USER_ID,LCHET1,SUMMA,WORD,METKA,NEOPL,PNN,LCHET,FAMILY,NAME,\
      FATHER,KOD,C,DOC,SERIA,NOMER,DOST,D_VIPL,ULIC,ADRES,CHEL,METKA1,VNOM,PRICH,IST,BSUMMA,";
      sql+="BWORD,FAKT_CHEL,FAKT_DAT,NSP,KEM_VID,DATA_VID,KODPEN,FOND) values(";
      if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql+=IntToStr(SaleBookDM->UserID)+",'"; else sql+=IntToStr(DSZ->FieldByName("USER_ID")->AsInteger)+",'";
      sql+=NDOST_DS->FieldByName("LCHET1")->AsString.Trim()+"',";
      sql+=AnsiString().sprintf("%.02lf",NDOST_DS->FieldByName("SUMMA")->AsFloat)+",'";
      sql+=NDOST_DS->FieldByName("WORD")->AsString.Trim()+"',";
      sql+=IntToStr(NDOST_DS->FieldByName("METKA")->AsInteger)+",";
      sql+=IntToStr(NDOST_DS->FieldByName("NEOPL")->AsInteger)+",";
      sql+=IntToStr(NDOST_DS->FieldByName("PNN")->AsInteger)+",";
      sql+=IntToStr(NDOST_DS->FieldByName("LCHET")->AsInteger)+",'";
      sql+=NDOST_DS->FieldByName("FAMILY")->AsString.Trim()+"','";
      sql+=NDOST_DS->FieldByName("NAME")->AsString.Trim()+"','";
      sql+=NDOST_DS->FieldByName("FATHER")->AsString.Trim()+"',";
      sql+=IntToStr(NDOST_DS->FieldByName("KOD")->AsInteger)+",'";
      sql+=NDOST_DS->FieldByName("C")->AsDateTime.DateString()+"','";
      sql+=NDOST_DS->FieldByName("DOC")->AsDateTime.DateString()+"','";
      sql+=NDOST_DS->FieldByName("SERIA")->AsString.Trim()+"',";
      sql+=IntToStr(NDOST_DS->FieldByName("NOMER")->AsInteger)+",";
      sql+=IntToStr(NDOST_DS->FieldByName("DOST")->AsInteger)+",";
      sql+=IntToStr(NDOST_DS->FieldByName("D_VIPL")->AsInteger)+",'";
      sql+=NDOST_DS->FieldByName("ULIC")->AsString.Trim()+"','";
      sql+=NDOST_DS->FieldByName("ADRES")->AsString.Trim()+"',";
      sql+=IntToStr(NDOST_DS->FieldByName("CHEL")->AsInteger)+",";
      sql+=IntToStr(NDOST_DS->FieldByName("METKA1")->AsInteger)+",";
      sql+=IntToStr(NDOST_DS->FieldByName("VNOM")->AsInteger)+",'";
      sql+=NDOST_DS->FieldByName("PRICH")->AsString.Trim()+"',";
      sql+=IntToStr(NDOST_DS->FieldByName("IST")->AsInteger)+",";
      sql+=AnsiString().sprintf("%.02lf",NDOST_DS->FieldByName("BSUMMA")->AsFloat)+",'";
      sql+=NDOST_DS->FieldByName("BWORD")->AsString.Trim()+"',";
      sql+=IntToStr(kodpost)+",";
      sql+=IntToStr(dayv)+",";
      sql+=IntToStr(NDOST_DS->FieldByName("NSP")->AsInteger)+",'";
      sql+=NDOST_DS->FieldByName("KEM_VID")->AsString.Trim()+"','";
      sql+=NDOST_DS->FieldByName("DATA_VID")->AsDateTime.DateString()+"',";
      sql+=IntToStr(NDOST_DS->FieldByName("KODPEN")->AsInteger)+",";
      sql+=IntToStr(NDOST_DS->FieldByName("FOND")->AsInteger)+")";
      TempQ->SQL->Add(sql);
      TempQ->ExecQuery();
      i++;
    NDOST_DS->Next();
  }
  TempQ->Close();
  updateset();
}


//---------------------------------------------------------------------------
//Выбор плательщика
void __fastcall TAccountEditForm::NumberEditKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  if(Key==VK_RETURN) DateEdit->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TAccountEditForm::DateEditKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  if(Key==VK_RETURN) CustomerEdit->SetFocus();
}
//---------------------------------------------------------------------------

//Добавить запись в таблицу проданных товаров
void __fastcall TAccountEditForm::AddButtonClick(TObject *Sender)
{

  if(CustomerEdit->Text.IsEmpty())
  {
    MessageDlg("Не выбран \"Почтальон-Касса\"",mtWarning,TMsgDlgButtons() << mbOK,0);
    CustomerEdit->SetFocus();
    return;
  }
  else
  {
  if(!Application->FindComponent("BrowseForm"))
  { try
    {
      Application->CreateForm(__classid(TBrowseForm), &BrowseForm);
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка создания формы BrowseForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
  }
  BrowseForm->flag=1;
  BrowseForm->Show();
  }
  Edit2->Text=IntToStr(SoldGoodsGrid->SelectedRows->Count);
}
//---------------------------------------------------------------------------
//Удаление записи из таблицы SoldGoodsTemp
void __fastcall TAccountEditForm::DelButtonClick(TObject *Sender)
{
AnsiString sql="";
unsigned short dvp,yvp,mvp;
TDateTime dprn;

if(Application->FindComponent("AccountsJournalForm")) dprn=AccountsJournalForm->getDate1(); else dprn=Date();
dprn.DecodeDate(&yvp,&mvp,&dvp);


  if(MessageDlg("Вы уверены, что хотите удалить текущее поручение БЕЗВОЗВРАТНО ? ",mtConfirmation,TMsgDlgButtons() << mbOK << mbCancel,0)==mrOk)
  {
  //Стартуем транзакцию
  WT->StartTransaction();
  TQ->Close();
  TQ->SQL->Clear();
  sql="delete from SGBT where USER_ID="+IntToStr(SaleBookDM->UserID);
  sql+=" and LCHET=" + IntToStr(SoldGoodsDS->FieldByName("LCHET")->AsInteger);
  TQ->SQL->Add(sql);
  try
  {
    TQ->ExecQuery();
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка TempQ (delete from SGB)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    WT->Rollback();
    return;
  }
  WT->Commit();
  updateset();
  ras();
  }
}
//---------------------------------------------------------------------------
//Отображение кнопок SaveButton и CancelButton
void __fastcall TAccountEditForm::SoldGoodsSStateChange(TObject *Sender)
{
  if(SG_DST->State==dsEdit || SG_DST->State==dsInsert)
  { SaveButton->Enabled=true;
    CancelButton->Enabled=true;
  }
  else
  { SaveButton->Enabled=false;
    CancelButton->Enabled=false;
  }
}
//---------------------------------------------------------------------------
//Сохранение записи о товаре
void __fastcall TAccountEditForm::SaveButtonClick(TObject *Sender)
{
//  if(SG_DST->FieldByName("KASSA")->AsInteger ==1 ) return;

  if(SG_DST->State==dsEdit || SG_DST->State==dsInsert)
  {
    if(SG_DST->FieldByName("KASSA")->AsInteger ==1 )
    SG_DST->Post();
    SG_DST->CloseOpen(false);
    ras();
  }
}
//---------------------------------------------------------------------------
//Отмена результатов редактирования записи о товаре
void __fastcall TAccountEditForm::CancelButtonClick(TObject *Sender)
{
  if(SG_DST->State==dsEdit || SG_DST->State==dsInsert) SG_DST->Cancel();
}
//---------------------------------------------------------------------------
//Сохранение данных
void __fastcall TAccountEditForm::WriteButtonClick(TObject *Sender)
{
AnsiString sql="";
TDateTime NewCountDate;
unsigned short NewNumber;
unsigned short dvp,yvp,mvp;
unsigned short dvp1,yvp1,mvp1;
TpFIBQuery *Q=SaleBookDM->TempQuery;
int NumberKas=0;
int CodKas=1;
int indops=0;
int codzad=0;
bool flg;
AnsiString str;
TpFIBDataSet *DSZ;
TpFIBDataSet *TZ;
int kassa=0;


DSZ=((TpFIBDataSet*)(AccountsJournalForm->AccountsGrid->DataSource->DataSet));
TZ=((TpFIBDataSet*)(AccountsJournalForm->SoldGoodsGrid->DataSource->DataSet));


//TDateTime dprn=AccountsJournalForm->getDate1();
TDateTime dprn=C_DS->FieldByName("COUNT_DATE")->AsDateTime;
dprn.DecodeDate(&yvp,&mvp,&dvp);

count_total=0.00;
double count_opl=0.00;
double count_neopl=0.00;
count_tek=0.00;
int count_pr=0.00;
double count_raz=0.00;
double count_neoplp=0.00;
double count_oplp=0.00;
count_totali=0;
count_opli=0;
count_neopli=0;
kassa=0;
int rn;

  //Итоговая сумма
count_opl=StrToFloat(StaticText7->Caption);
count_neopl=StrToFloat(StaticText9->Caption);
count_tek=StrToFloat(StaticText4->Caption);
count_pr=StrToFloat(StaticText5->Caption);
count_raz=StrToFloat(StaticText6->Caption);
count_neoplp=StrToFloat(StaticText10->Caption);
count_oplp=StrToFloat(StaticText8->Caption);
count_total=count_raz+count_pr+count_tek;

count_totali=StrToInt(StaticText1->Caption);
count_opli=StrToInt(StaticText2->Caption);
count_neopli=StrToInt(StaticText3->Caption);


  //Сохраняем товар в таблице COLD_GOODS_TEMP
  SaveButton->Click();

    if(CustomerEdit->Text.IsEmpty())
  {
    MessageDlg("Не выбран \"Почтальон-Касса\"",mtWarning,TMsgDlgButtons() << mbOK,0);
    CustomerEdit->SetFocus();
    return;
  }


  //Новые год и месяц счета
  NewCountDate=C_DS->FieldByName("COUNT_DATE")->AsDateTime;
  NewCountDate.DecodeDate(&yvp1,&mvp1,&dvp1);
  //Новый номер счета
  NewNumber=C_DS->FieldByName("COUNT_NUMBER")->AsInteger;

  //Если изменился номер или дата счета, проверяем можно новый счет сохранить
  if(NewNumber!=Number || NewCountDate!=CountDate)
  {
    //Проверяем BeginDate
    if(NewCountDate < SaleBookDM->BeginDate)
    { MessageDlg("Дата задания не может быть меньше даты начала работы с программой - "+SaleBookDM->BeginDate.DateString(),mtError,TMsgDlgButtons() << mbOK,0);
      DateEdit->SetFocus();
      return;
    }
    //Проверяем нет ли такого счета в таблице ACCOUNTS
    TempQ->Close();
    TempQ->SQL->Clear();
    if(NewCountDate > TDateTime("31.12.2008"))
    { sql="select * from ACCOUNTS where";
      sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
      sql+=" and COUNT_DATE='"+NewCountDate.DateString()+"'";
      sql+=" and COUNT_NUMBER="+IntToStr(NewNumber);
    }
    else
    { unsigned short y,m,d;
      NewCountDate.DecodeDate(&y,&m,&d);
      TDateTime dt1=TDateTime(y,m,1),
                dt2=TDateTime(y,m,SaleBookDM->LastDay(y,m));
      sql="select * from ACCOUNTS where";
      sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
      sql+=" and COUNT_DATE>='"+dt1.DateString()+"'";
      sql+=" and COUNT_DATE<='"+dt2.DateString()+"'";
      sql+=" and COUNT_NUMBER="+IntToStr(NewNumber);
    }
    TempQ->SQL->Add(sql);
    try
    {
      TempQ->ExecQuery();
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка TempQ (ACCOUNTS)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
    if(TempQ->RecordCount!=0)
    { MessageDlg("Номер задания не уникальный",mtWarning,TMsgDlgButtons() << mbOK,0);
      NumberEdit->SetFocus();
      return;
    }
    //Проверяем нет ли такого счета в таблице AccountsTemp
    TempQ->Close();
    TempQ->SQL->Clear();
    if(NewCountDate > TDateTime("31.12.2008"))
    { sql="select * from ACCOUNTS_TEMP where";
      sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
      sql+=" and COUNT_DATE='"+NewCountDate.DateString()+"'";
      sql+=" and COUNT_NUMBER="+IntToStr(NewNumber);
      sql+=" and USER_ID<>"+IntToStr(SaleBookDM->UserID);
    }
    else
    { unsigned short y,m,d;
      NewCountDate.DecodeDate(&y,&m,&d);
      TDateTime dt1=TDateTime(y,m,1),
                dt2=TDateTime(y,m,SaleBookDM->LastDay(y,m));
      sql="select * from ACCOUNTS_TEMP where";
      sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
      sql+=" and COUNT_DATE>='"+dt1.DateString()+"'";
      sql+=" and COUNT_DATE<='"+dt2.DateString()+"'";
      sql+=" and COUNT_NUMBER<="+IntToStr(NewNumber);
      sql+=" and USER_ID<>"+IntToStr(SaleBookDM->UserID);
    }

    TempQ->SQL->Add(sql);
    try
    {
      TempQ->ExecQuery();
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка TempQ (ACCOUNTS)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
    if(TempQ->RecordCount!=0)
    { MessageDlg("С этим заданием уже работает другой пользователь",mtWarning,TMsgDlgButtons() << mbOK,0);
      NumberEdit->SetFocus();
      return;
    }
  }

  //Cохраняем задание в таблице ACCOUNTS_TEMP
  if(C_DS->State==dsEdit || C_DS->State==dsInsert)
  { try
    {
      C_DS->Post();
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка сохранения записи в таблице ACCOUNTS_TEMP\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
  }

rn=DSZ->RecNo;
  
WT->StartTransaction();
  TQ->Close();
  TQ->SQL->Clear();
  sql="delete from SGB where";
  sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
  sql+=" and COUNT_DATE='"+CountDate.DateString()+"'";
  sql+=" and COUNT_NUMBER="+IntToStr(Number);
  TQ->SQL->Add(sql);
  try
  {
    TQ->ExecQuery();
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка TempQ (delete from SGB)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    WT->Rollback();
    return;
  }
  TQ->Close();
  TQ->SQL->Clear();
  sql="delete from ACCOUNTS where";
  sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
  sql+=" and COUNT_DATE='"+CountDate.DateString()+"'";
  sql+=" and COUNT_NUMBER="+IntToStr(Number);
  TQ->SQL->Add(sql);
  try
  {
    TQ->ExecQuery();
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка TempQ (delete from ACCOUNTS)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    WT->Rollback();
    return;
  }
WT->Commit();


if(count_totali>0)
{

  //Сохраняем задание в таблице ACCOUNTS
  WT->StartTransaction();
  TQ->Close();
  TQ->SQL->Clear();
  sql="insert into ACCOUNTS ";
  sql+="(ORG_ID,COUNT_DATE,COUNT_NUMBER,CUSTOMER_ID,CUSTOMER_NAME,USER_ID,RS_ID,\
COUNT_TOTAL,EDIT_KEY,COUNT_TYPE,COUNT_OPL,COUNT_NEOPL,COUNT_TOTALI,COUNT_OPLI,COUNT_NEOPLI,\
COUNT_TEK,COUNT_PR,COUNT_RAZ,COUNT_NEOPLP,COUNT_OPLP,M,Y)";
  sql+=" values ("+IntToStr(SaleBookDM->OrganizationID);
  sql+=",'"+NewCountDate.DateString()+"'";
  sql+=","+IntToStr(NewNumber);
  sql+=","+IntToStr(C_DS->FieldByName("CUSTOMER_ID")->AsInteger);
  sql+=",'"+C_DS->FieldByName("CUSTOMER_NAME")->AsString;
  sql+="',"+IntToStr(C_DS->FieldByName("USER_ID")->AsInteger);
  sql+=","+IntToStr(0);
  sql+=","+FloatToStr(count_total)+",1";
  sql+=","+IntToStr(C_DS->FieldByName("COUNT_TYPE")->AsInteger);
  sql+=","+FloatToStr(count_opl);
  sql+=","+FloatToStr(count_neopl);
  sql+=","+IntToStr(count_totali);
  sql+=","+IntToStr(count_opli);
  sql+=","+IntToStr(count_neopli);
  sql+=","+FloatToStr(count_tek);
  sql+=","+FloatToStr(count_pr);
  sql+=","+FloatToStr(count_raz);
  sql+=","+FloatToStr(count_neoplp);
  sql+=","+FloatToStr(count_oplp);
  sql+=","+IntToStr(Month(NewCountDate));
  sql+=","+IntToStr(Year(NewCountDate))+")";
  TQ->SQL->Add(sql);
  try
  {
    TQ->ExecQuery();
  }
  catch (Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    WT->Rollback();
    return;
  }
  WT->Commit();



  // Здесь меняем флажок касса kassa и запись в таблицу поручений

unsigned short num=1;
SG_DST->First();
while(!SG_DST->Eof)
{

  //Сохраняем записи о поручениях в таблице SGB
      TQ->Close();
      TQ->SQL->Clear();
      sql="insert into SGB";
      sql+="(ORG_ID,COUNT_DATE,COUNT_NUMBER,\
      LCHET1,SUMMA,WORD,METKA,NEOPL,PNN,LCHET,FAMILY,NAME,\
      FATHER,KOD,C,DOC,SERIA,NOMER,DOST,D_VIPL,ULIC,ADRES,CHEL,METKA1,VNOM,PRICH,IST,BSUMMA,";
      sql+="BWORD,FAKT_CHEL,FAKT_DAT,NSP,KEM_VID,DATA_VID,M,Y,KODPEN,FOND,KASSA) values(";
      sql+=IntToStr(SaleBookDM->OrganizationID);
      sql+=",'"+NewCountDate.DateString()+"'";
      sql+=","+IntToStr(NewNumber)+",'";;
      sql+=SG_DST->FieldByName("LCHET1")->AsString.Trim()+"',";
      sql+=AnsiString().sprintf("%.02lf",SG_DST->FieldByName("SUMMA")->AsFloat)+",'";
      sql+=SG_DST->FieldByName("WORD")->AsString.Trim()+"',";
      sql+=IntToStr(SG_DST->FieldByName("METKA")->AsInteger)+",";
      sql+=IntToStr(SG_DST->FieldByName("NEOPL")->AsInteger)+",";
      sql+=IntToStr(SG_DST->FieldByName("PNN")->AsInteger)+",";
      sql+=IntToStr(SG_DST->FieldByName("LCHET")->AsInteger)+",'";
      sql+=SG_DST->FieldByName("FAMILY")->AsString.Trim()+"','";
      sql+=SG_DST->FieldByName("NAME")->AsString.Trim()+"','";
      sql+=SG_DST->FieldByName("FATHER")->AsString.Trim()+"',";
      sql+=IntToStr(SG_DST->FieldByName("KOD")->AsInteger)+",'";
      sql+=SG_DST->FieldByName("C")->AsDateTime.DateString()+"','";
      sql+=SG_DST->FieldByName("DOC")->AsDateTime.DateString()+"','";
      sql+=SG_DST->FieldByName("SERIA")->AsString.Trim()+"',";
      sql+=IntToStr(SG_DST->FieldByName("NOMER")->AsInteger)+",";
      sql+=IntToStr(SG_DST->FieldByName("DOST")->AsInteger)+",";
      sql+=IntToStr(SG_DST->FieldByName("D_VIPL")->AsInteger)+",'";
      sql+=SG_DST->FieldByName("ULIC")->AsString.Trim()+"','";
      sql+=SG_DST->FieldByName("ADRES")->AsString.Trim()+"',";
      sql+=IntToStr(SG_DST->FieldByName("CHEL")->AsInteger)+",";
      sql+=IntToStr(SG_DST->FieldByName("METKA1")->AsInteger)+",";
      sql+=IntToStr(SG_DST->FieldByName("VNOM")->AsInteger)+",'";
      sql+=SG_DST->FieldByName("PRICH")->AsString.Trim()+"',";
      sql+=IntToStr(SG_DST->FieldByName("IST")->AsInteger)+",";
      sql+=AnsiString().sprintf("%.02lf",SG_DST->FieldByName("BSUMMA")->AsFloat)+",'";
      sql+=SG_DST->FieldByName("BWORD")->AsString.Trim()+"',";
      sql+=IntToStr(C_DS->FieldByName("CUSTOMER_ID")->AsInteger)+",";
      sql+=IntToStr(dvp)+",";
      sql+=IntToStr(SG_DST->FieldByName("NSP")->AsInteger)+",'";
      sql+=SG_DST->FieldByName("KEM_VID")->AsString.Trim()+"','";
      sql+=SG_DST->FieldByName("DATA_VID")->AsDateTime.DateString()+"',";
      sql+=IntToStr(mvp);
      sql+=","+IntToStr(yvp)+",";
      sql+=IntToStr(SG_DST->FieldByName("KODPEN")->AsInteger)+",";
      sql+=IntToStr(SG_DST->FieldByName("FOND")->AsInteger)+",";
      sql+=IntToStr(kassa)+")";
      TQ->SQL->Add(sql);
      try
      {
        TQ->ExecQuery();
      }
      catch (Exception &exc)
      {
        MessageDlg("Ошибка TempQ (insert into SGB)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
        WT->Rollback();
        return;
      }


num++;
SG_DST->Next();
}

  WT->Commit();

  //Фиксируем действие в журнале событий ACTIONS_JOURNAL
  WT->StartTransaction();
  if(NewFLG) str="Добавлен ";
  else str="Отредактирован ";
  str+="задание №"+IntToStr(NewNumber)+" от ";
  str+=C_DS->FieldByName("COUNT_DATE")->AsString+" на сумму "+FloatToStr(count_total);
  if(NewFLG) flg=SaleBookDM->AddRecordToActionsJournal(AddRecordToAccountsTable,str,WT);
  else flg=SaleBookDM->AddRecordToActionsJournal(EditRecordFromAccountsTable,str,WT);
  //Подтверждаем результаты изменений
  if(flg==true) WT->Commit();
  else WT->Rollback();
  //
  NewFLG=false;
  provkassa();
  AccountsJournalForm->setMainHeader();
  AccountsJournalForm->LoadDataSet();
  AccountsJournalForm->A_DS->RecNo=rn;
  Close();
  ModalResult=mrOk;
}
else
{
    MessageDlg("Внимание!!!\" Новое пустое задание сохранить нельзя , а старое пустое задание удалиться АВТОМАТИЧЕСКИ !!! \"",mtWarning,TMsgDlgButtons() << mbOK,0);
    provkassa();
    AccountsJournalForm->setMainHeader();
    AccountsJournalForm->LoadDataSet();
    AccountsJournalForm->A_DS->RecNo=rn;
    Close();
    NewFLG=false;
    ModalResult=mrCancel;
    LoadFLG=false;
}
DSZ->RecNo=rn;

}
//---------------------------------------------------------------------------
void __fastcall TAccountEditForm::ExitButtonClick(TObject *Sender)
{
  //Снимаем флаг EDIT_FLG
  Close();
  NewFLG=false;
  ModalResult=mrCancel;
}
//---------------------------------------------------------------------------
//
void __fastcall TAccountEditForm::SoldGoodsGridKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  if(Key==VK_DOWN && SG_DST->RecNo==SG_DST->RecordCount) Key=0;
  else if(Key==VK_INSERT) Key=0;
  else
  { TShiftState st;
    st << ssCtrl;
    if(Shift==st && Key==VK_DELETE) Key=0;
  }
}
//---------------------------------------------------------------------------
//При изменении даты задания
void __fastcall TAccountEditForm::DateEditChange(TObject *Sender)
{
int number=0;
AnsiString sql;
unsigned short dv,yv,mv;
unsigned short y,m,d;
unsigned short ytw,mtw,dtw;

if(C_DS->State!=dsEdit && C_DS->State!=dsInsert) return;

TDateTime dt=TDateTime(DateEdit->Text);
dt.DecodeDate(&y,&m,&d);

TDateTime dtoday=Date()+9;
dtoday.DecodeDate(&ytw,&mtw,&dtw);

TDateTime lockDate;
unsigned short yl,ml,dl;

lockDate=SaleBookDM->GetConstValue(SaleBookDM->OrganizationID,"LOCK_EDIT_DATE");
lockDate.DecodeDate(&yl,&ml,&dl);


TpFIBDataSet *DSZ;
DSZ=((TpFIBDataSet*)(AccountsJournalForm->AccountsGrid->DataSource->DataSet));

  if(d>=23)
  {
    MessageDlg("Дата выплаты должна быть до 22 числа текущего месяца !!!",mtWarning,TMsgDlgButtons() << mbOK,0);
    DateEdit->SetFocus();
    return;
  }

  if(m!=ml)
  {
    MessageDlg("Дата выплаты НЕВЕРНАЯ !!!",mtWarning,TMsgDlgButtons() << mbOK,0);
    DateEdit->SetFocus();
    return;
  }

  if(y!=yl)
  {
    MessageDlg("Дата выплаты НЕВЕРНАЯ !!!",mtWarning,TMsgDlgButtons() << mbOK,0);
    DateEdit->SetFocus();
    return;
  }

  if(dt != CountDate)
  { //Ищем последний счет в таблице Accounts
    TempQ->Close();
    TempQ->SQL->Clear();
    if(CountDate > TDateTime("31.12.2008"))
    { sql="select max(COUNT_NUMBER) as MAX_COUNT_NUMBER from ACCOUNTS where";
      sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
      sql+=" and COUNT_DATE='"+dt.DateString()+"'";
    }
    else
    {
      TDateTime date1=TDateTime(y,m,1),
                date2=TDateTime(y,m,SaleBookDM->LastDay(y,m));
      sql="select max(COUNT_NUMBER) as MAX_COUNT_NUMBER from ACCOUNTS where";
      sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
      sql+=" and COUNT_DATE>='"+date1.DateString()+"'";
      sql+=" and COUNT_DATE<='"+date2.DateString()+"'";
    }
    TempQ->SQL->Add(sql);
    try
    {
      TempQ->ExecQuery();
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
    if(TempQ->RecordCount > 0) number=TempQ->FieldByName("MAX_COUNT_NUMBER")->AsInteger;
    //Ищем последний счет в таблице AccountsTemp
    TempQ->Close();
    TempQ->SQL->Clear();
    if(CountDate > TDateTime("31.12.2008"))
    { sql="select max(COUNT_NUMBER) as MAX_COUNT_NUMBER from ACCOUNTS_TEMP where";
      sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
      sql+=" and COUNT_DATE='"+dt.DateString()+"'";
    }
    else
    {
      unsigned short y,m,d;
      dt.DecodeDate(&y,&m,&d);
      TDateTime date1=TDateTime(y,m,1),
                date2=TDateTime(y,m,SaleBookDM->LastDay(y,m));
      sql="select max(COUNT_NUMBER) as MAX_COUNT_NUMBER from ACCOUNTS_TEMP where";
      sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
      sql+=" and COUNT_DATE>='"+date1.DateString()+"'";
      sql+=" and COUNT_DATE<='"+date2.DateString()+"'";
    }
    TempQ->SQL->Add(sql);
    try
    {
      TempQ->ExecQuery();
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
    if(TempQ->RecordCount > 0 && TempQ->FieldByName("MAX_COUNT_NUMBER")->AsInteger > number) number=TempQ->FieldByName("MAX_COUNT_NUMBER")->AsInteger;
    NumberEdit->Value=number+1;
    TempQ->Close();
    C_DS->FieldByName("COUNT_DATE")->AsDateTime=dt;
    dt.DecodeDate(&yv,&mv,&dv);

  }
  else
  { NumberEdit->Value=Number;
    C_DS->FieldByName("COUNT_DATE")->AsDateTime=CountDate;
    CountDate.DecodeDate(&yv,&mv,&dv);
  }

  if(CustomerEdit->Text.IsEmpty())
  {
//    MessageDlg("Не выбран \"Почтальон-Касса\"",mtWarning,TMsgDlgButtons() << mbOK,0);
    CustomerEdit->SetFocus();
    return;
  }else
  {
   TempQ->Close();
   TempQ->SQL->Clear();
   sql="select INDEXOPS as INDOPS from NOMENCLATURE n where CODP="+IntToStr(EIForm->DS->FieldByName("ID")->AsInteger);
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

   if (TempQ->FieldByName("INDOPS")->AsInteger > 0)
  {
   otbor(dv,C_DS->FieldByName("CUSTOMER_ID")->AsInteger);
  }else
  {
//   otborforkassa(dv,C_DS->FieldByName("CUSTOMER_ID")->AsInteger);
  }

 }

}
//---------------------------------------------------------------------------



void __fastcall TAccountEditForm::searchTimerTimer(TObject *Sender)
{
//int num=1;
//Variant lv[1];
TLocateOptions opt;
opt<<loPartialKey<<loCaseInsensitive;
AnsiString d=0;
int test=0;

  searchTimer->Enabled=false;
  if(Edit1->Text.IsEmpty()) return;
  if(Edit1->Text.Length() <= 6 && IsNum(Edit1->Text.Trim())){
  d=Edit1->Text.Trim();
  SoldGoodsDS->Locate("LCHET1",d,opt);
  Edit1->Text="";
  }else
  {
  d=Edit1->Text.Trim();
  SoldGoodsDS->Locate("FAMILY",d,opt);
  Edit1->Text="";
  }
}

//---------------------------------------------------------------------------

void __fastcall TAccountEditForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  NewFLG=false;
  ModalResult=mrCancel;
  Action=caFree;
}
//---------------------------------------------------------------------------

void __fastcall TAccountEditForm::SoldGoodsSDataChange(TObject *Sender,
      TField *Field)
{
  if(NewFLG)
  {
    AddButton->Enabled = true;
    SaveButton->Enabled = false;
    EditButton->Enabled = false;
    CancelButton->Enabled = false;
    if(SG_DST->RecordCount>0)
    {
    DelButton->Enabled = true;
    }else
    {
    DelButton->Enabled = false;
    }
    }
    else
    {
    AddButton->Enabled = true;
    if(SG_DST->RecordCount>0)
    {
    DelButton->Enabled = true;
    SaveButton->Enabled = true;
    EditButton->Enabled = true;
    CancelButton->Enabled = true;
    }else
    {
    DelButton->Enabled = false;
    SaveButton->Enabled = false;
    EditButton->Enabled = false;
    CancelButton->Enabled = false;
    }
  }
ras();
}
//---------------------------------------------------------------------------
void __fastcall TAccountEditForm::updateset(void)
{
AnsiString sql;
TpFIBDataSet *DSZ;
DSZ=((TpFIBDataSet*)(AccountsJournalForm->AccountsGrid->DataSource->DataSet));


  SG_DST=((TpFIBDataSet*)(SoldGoodsGrid->DataSource->DataSet));
  SG_DST->Close();
  SG_DST->SQLs->SelectSQL->Clear();
  sql="select g.*";
  sql+=" from SGBT g";
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель")
  {
  sql+=" where USER_ID="+IntToStr(SaleBookDM->UserID);
  }
  else
  {
  sql+=" where USER_ID="+IntToStr(DSZ->FieldByName("USER_ID")->AsInteger);
  }
  SG_DST->SQLs->SelectSQL->Add(sql);
  try
  {
    SG_DST->Open();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка открытия таблицы SOLD_GOODS_TEMP\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(SG_DST->RecordCount>0)
  {
  SG_DST->First();
//  SG_DST->Edit();
  }

}

void __fastcall TAccountEditForm::Edit1KeyPress(TObject *Sender, char &Key)
{
  if(Key==VK_RETURN || Key==VK_DOWN || Key==VK_UP)
  { Key=0;
    SoldGoodsGrid->SetFocus();
  }
  else if(Key == VK_ESCAPE){ Key=0; Edit1->Text=""; }

}
//---------------------------------------------------------------------------

void __fastcall TAccountEditForm::Edit1Change(TObject *Sender)
{
  if(searchTimer->Enabled==true) searchTimer->Enabled=false;
  searchTimer->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TAccountEditForm::EditButtonClick(TObject *Sender)
{
//  if(SG_DST->FieldByName("KASSA")->AsInteger ==1 ) return;
  SG_DST->Edit();
}
//---------------------------------------------------------------------------

void __fastcall TAccountEditForm::SoldGoodsGridColumns7UpdateData(
      TObject *Sender, AnsiString &Text, Variant &Value, bool &UseText,
      bool &Handled)
{
//  if(SG_DST->FieldByName("KASSA")->AsInteger ==1 )
//  {
//  MessageDlg("Нельзя менять причины невыплаты для поручений оплаченных на кассе!!!",mtError,TMsgDlgButtons() << mbOK,0);
//  SG_DST->Edit();
//  SG_DST->FieldByName("PRICH")->AsString="н/д";
//  SG_DST->Cancel();
//  SG_DST->Edit();
//  return;
//  }
//  else
//  {
  if(!Text.IsEmpty()) SG_DST->FieldByName("PRICH")->AsString=Text.Trim();
  else SG_DST->FieldByName("PRICH")->Value="";
//  }
}
//---------------------------------------------------------------------------

void __fastcall TAccountEditForm::SoldGoodsGridGetCellParams(
      TObject *Sender, TColumnEh *Column, TFont *AFont, TColor &Background,
      TGridDrawState State)
{
 if(!SG_DST->FieldByName("PRICH")->AsString.IsEmpty()){
  if(SG_DST->FieldByName("PRICH")->AsString.Trim() != "н/д")
  {
    Background=Graphics::clRed;
  }
  else
  {
  if(SG_DST->FieldByName("KASSA")->AsInteger ==1 )
  {
  Background=Graphics::clCream;
  }
  else
  {
  Background=Graphics::clYellow;
  }
  }
 }
 else
 {
 Background=Graphics::clMoneyGreen;
 }
}
//---------------------------------------------------------------------------
//Сохранение данных без закрытия формы
void __fastcall TAccountEditForm::WriteButtonClickwE(void)
{
//unsigned short NewYear,NewMonth,d;
AnsiString sql="";
TDateTime NewCountDate;
unsigned short NewNumber;
unsigned short dvp,yvp,mvp;

TDateTime dprn=AccountsJournalForm->getDate1();
dprn.DecodeDate(&yvp,&mvp,&dvp);

count_total=0.00;
count_opl=0.00;
count_neopl=0.00;
count_tek=0.00;
count_pr=0.00;
count_raz=0.00;
count_neoplp=0.00;
count_oplp=0.00;
count_totali=0;
count_opli=0;
count_neopli=0;

  //Сохраняем товар в таблице COLD_GOODS_TEMP
  SaveButton->Click();

  if(CustomerEdit->Text.IsEmpty())
  { MessageDlg("Не выбран \"Почтальон\"",mtWarning,TMsgDlgButtons() << mbOK,0);
    CustomerEdit->SetFocus();
    return;
  }


  //Новые год и месяц счета
  NewCountDate=C_DS->FieldByName("COUNT_DATE")->AsDateTime;
  //Новый номер счета
  NewNumber=C_DS->FieldByName("COUNT_NUMBER")->AsInteger;

  //Если изменился номер или дата счета, проверяем можно новый счет сохранить
  if(NewNumber!=Number || NewCountDate!=CountDate)
  {
    //Проверяем BeginDate
    if(NewCountDate < SaleBookDM->BeginDate)
    { MessageDlg("Дата задания не может быть меньше даты начала работы с программой - "+SaleBookDM->BeginDate.DateString(),mtError,TMsgDlgButtons() << mbOK,0);
      DateEdit->SetFocus();
      return;
    }
    //Проверяем нет ли такого счета в таблице ACCOUNTS
    TempQ->Close();
    TempQ->SQL->Clear();
    if(NewCountDate > TDateTime("31.12.2008"))
    { sql="select * from ACCOUNTS where";
      sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
      sql+=" and COUNT_DATE='"+NewCountDate.DateString()+"'";
      sql+=" and COUNT_NUMBER="+IntToStr(NewNumber);
    }
    else
    { unsigned short y,m,d;
      NewCountDate.DecodeDate(&y,&m,&d);
      TDateTime dt1=TDateTime(y,m,1),
                dt2=TDateTime(y,m,SaleBookDM->LastDay(y,m));
      sql="select * from ACCOUNTS where";
      sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
      sql+=" and COUNT_DATE>='"+dt1.DateString()+"'";
      sql+=" and COUNT_DATE<='"+dt2.DateString()+"'";
      sql+=" and COUNT_NUMBER="+IntToStr(NewNumber);
    }
    TempQ->SQL->Add(sql);
    try
    {
      TempQ->ExecQuery();
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка TempQ (ACCOUNTS)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
    if(TempQ->RecordCount!=0)
    { MessageDlg("Номер задания не уникальный",mtWarning,TMsgDlgButtons() << mbOK,0);
      NumberEdit->SetFocus();
      return;
    }
    //Проверяем нет ли такого счета в таблице AccountsTemp
    TempQ->Close();
    TempQ->SQL->Clear();
    if(NewCountDate > TDateTime("31.12.2008"))
    { sql="select * from ACCOUNTS_TEMP where";
      sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
      sql+=" and COUNT_DATE='"+NewCountDate.DateString()+"'";
      sql+=" and COUNT_NUMBER="+IntToStr(NewNumber);
      sql+=" and USER_ID<>"+IntToStr(SaleBookDM->UserID);
    }
    else
    { unsigned short y,m,d;
      NewCountDate.DecodeDate(&y,&m,&d);
      TDateTime dt1=TDateTime(y,m,1),
                dt2=TDateTime(y,m,SaleBookDM->LastDay(y,m));
      sql="select * from ACCOUNTS_TEMP where";
      sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
      sql+=" and COUNT_DATE>='"+dt1.DateString()+"'";
      sql+=" and COUNT_DATE<='"+dt2.DateString()+"'";
      sql+=" and COUNT_NUMBER<="+IntToStr(NewNumber);
      sql+=" and USER_ID<>"+IntToStr(SaleBookDM->UserID);
    }

    TempQ->SQL->Add(sql);
    try
    {
      TempQ->ExecQuery();
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка TempQ (ACCOUNTS)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
    if(TempQ->RecordCount!=0)
    { MessageDlg("С этим заданием уже работает другой пользователь",mtWarning,TMsgDlgButtons() << mbOK,0);
      NumberEdit->SetFocus();
      return;
    }
  }

  //Cохраняем счет в таблице ACCOUNTS_TEMP
  if(C_DS->State==dsEdit || C_DS->State==dsInsert)
  { try
    {
      C_DS->Post();
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка сохранения записи в таблице ACCOUNTS_TEMP\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
  }

  //Итоговая сумма
count_opl=StrToFloat(StaticText7->Caption);
count_neopl=StrToFloat(StaticText9->Caption);
count_tek=StrToFloat(StaticText4->Caption);
count_pr=StrToFloat(StaticText5->Caption);
count_raz=StrToFloat(StaticText6->Caption);
count_neoplp=StrToFloat(StaticText10->Caption);
count_oplp=StrToFloat(StaticText8->Caption);
count_total=count_raz+count_pr+count_tek;

count_totali=StrToInt(StaticText1->Caption);
count_opli=StrToInt(StaticText2->Caption);
count_neopli=StrToInt(StaticText3->Caption);

  //Стартуем транзакцию
  WT->StartTransaction();
  //Удаляем старые записи о поручениях из таблицы SGB
  TQ->Close();
  TQ->SQL->Clear();
  sql="delete from SGB where";
  sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
  sql+=" and COUNT_DATE='"+CountDate.DateString()+"'";
  sql+=" and COUNT_NUMBER="+IntToStr(Number);
  TQ->SQL->Add(sql);
  try
  {
    TQ->ExecQuery();
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка TempQ (delete from SGB)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    WT->Rollback();
    return;
  }
  //Удаляем старое задание из таблицы ACCOUNTS
  TQ->Close();
  TQ->SQL->Clear();
  sql="delete from ACCOUNTS where";
  sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
  sql+=" and COUNT_DATE='"+CountDate.DateString()+"'";
  sql+=" and COUNT_NUMBER="+IntToStr(Number);
  TQ->SQL->Add(sql);
  try
  {
    TQ->ExecQuery();
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка TempQ (delete from ACCOUNTS)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    WT->Rollback();
    return;
  }

  //Сохраняем задание в таблице ACCOUNTS
  TQ->Close();
  TQ->SQL->Clear();
  sql="insert into ACCOUNTS ";
  sql+="(ORG_ID,COUNT_DATE,COUNT_NUMBER,CUSTOMER_ID,CUSTOMER_NAME,USER_ID,RS_ID,\
COUNT_TOTAL,EDIT_KEY,COUNT_TYPE,COUNT_OPL,COUNT_NEOPL,COUNT_TOTALI,COUNT_OPLI,COUNT_NEOPLI,\
COUNT_TEK,COUNT_PR,COUNT_RAZ,COUNT_NEOPLP,COUNT_OPLP,M,Y)";
  sql+=" values ("+IntToStr(SaleBookDM->OrganizationID);
  sql+=",'"+NewCountDate.DateString()+"'";
  sql+=","+IntToStr(NewNumber);
  sql+=","+IntToStr(C_DS->FieldByName("CUSTOMER_ID")->AsInteger);
  sql+=",'"+C_DS->FieldByName("CUSTOMER_NAME")->AsString;
  sql+="',"+IntToStr(C_DS->FieldByName("USER_ID")->AsInteger);
  sql+=","+IntToStr(0);
  sql+=","+FloatToStr(count_total)+",1";
  sql+=","+IntToStr(C_DS->FieldByName("COUNT_TYPE")->AsInteger);
  sql+=","+FloatToStr(count_opl);
  sql+=","+FloatToStr(count_neopl);
  sql+=","+IntToStr(count_totali);
  sql+=","+IntToStr(count_opli);
  sql+=","+IntToStr(count_neopli);
  sql+=","+FloatToStr(count_tek);
  sql+=","+FloatToStr(count_pr);
  sql+=","+FloatToStr(count_raz);
  sql+=","+FloatToStr(count_neoplp);
  sql+=","+FloatToStr(count_oplp);
  sql+=","+IntToStr(Month(NewCountDate));
  sql+=","+IntToStr(Year(NewCountDate))+")";
  TQ->SQL->Add(sql);
  try
  {
    TQ->ExecQuery();
  }
  catch (Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    WT->Rollback();
    return;
  }
  WT->Commit();
  //Сохраняем записи о поручениях в таблице SGB
  WT->StartTransaction();
  unsigned short num=1;
  SG_DST->First();
  while(!SG_DST->Eof)
  {
      TQ->Close();
      TQ->SQL->Clear();
      sql="insert into SGB";
      sql+="(ORG_ID,COUNT_DATE,COUNT_NUMBER,\
      LCHET1,SUMMA,WORD,METKA,NEOPL,PNN,LCHET,FAMILY,NAME,\
      FATHER,KOD,C,DOC,SERIA,NOMER,DOST,D_VIPL,ULIC,ADRES,CHEL,METKA1,VNOM,PRICH,IST,BSUMMA,";
      sql+="BWORD,FAKT_CHEL,FAKT_DAT,NSP,KEM_VID,DATA_VID,M,Y) values(";
      sql+=IntToStr(SaleBookDM->OrganizationID);
      sql+=",'"+NewCountDate.DateString()+"'";
      sql+=","+IntToStr(NewNumber)+",'";;
      sql+=SG_DST->FieldByName("LCHET1")->AsString.Trim()+"',";
      sql+=AnsiString().sprintf("%.02lf",SG_DST->FieldByName("SUMMA")->AsFloat)+",'";
      sql+=SG_DST->FieldByName("WORD")->AsString.Trim()+"',";
      sql+=IntToStr(SG_DST->FieldByName("METKA")->AsInteger)+",";
      sql+=IntToStr(SG_DST->FieldByName("NEOPL")->AsInteger)+",";
      sql+=IntToStr(SG_DST->FieldByName("PNN")->AsInteger)+",";
      sql+=IntToStr(SG_DST->FieldByName("LCHET")->AsInteger)+",'";
      sql+=SG_DST->FieldByName("FAMILY")->AsString.Trim()+"','";
      sql+=SG_DST->FieldByName("NAME")->AsString.Trim()+"','";
      sql+=SG_DST->FieldByName("FATHER")->AsString.Trim()+"',";
      sql+=IntToStr(SG_DST->FieldByName("KOD")->AsInteger)+",'";
      sql+=SG_DST->FieldByName("C")->AsDateTime.DateString()+"','";
      sql+=SG_DST->FieldByName("DOC")->AsDateTime.DateString()+"','";
      sql+=SG_DST->FieldByName("SERIA")->AsString.Trim()+"',";
      sql+=IntToStr(SG_DST->FieldByName("NOMER")->AsInteger)+",";
      sql+=IntToStr(SG_DST->FieldByName("DOST")->AsInteger)+",";
      sql+=IntToStr(SG_DST->FieldByName("D_VIPL")->AsInteger)+",'";
      sql+=SG_DST->FieldByName("ULIC")->AsString.Trim()+"','";
      sql+=SG_DST->FieldByName("ADRES")->AsString.Trim()+"',";
      sql+=IntToStr(SG_DST->FieldByName("CHEL")->AsInteger)+",";
      sql+=IntToStr(SG_DST->FieldByName("METKA1")->AsInteger)+",";
      sql+=IntToStr(SG_DST->FieldByName("VNOM")->AsInteger)+",'";
      sql+=SG_DST->FieldByName("PRICH")->AsString.Trim()+"',";
      sql+=IntToStr(SG_DST->FieldByName("IST")->AsInteger)+",";
      sql+=AnsiString().sprintf("%.02lf",SG_DST->FieldByName("BSUMMA")->AsFloat)+",'";
      sql+=SG_DST->FieldByName("BWORD")->AsString.Trim()+"',";
      sql+=IntToStr(SG_DST->FieldByName("FAKT_CHEL")->AsInteger)+",";
      sql+=IntToStr(SG_DST->FieldByName("FAKT_DAT")->AsInteger)+",";
      sql+=IntToStr(SG_DST->FieldByName("NSP")->AsInteger)+",'";
      sql+=SG_DST->FieldByName("KEM_VID")->AsString.Trim()+"','";
      sql+=SG_DST->FieldByName("DATA_VID")->AsDateTime.DateString()+"',";
      sql+=IntToStr(mvp);
      sql+=","+IntToStr(yvp)+")";

      TQ->SQL->Add(sql);
      try
      {
        TQ->ExecQuery();
      }
      catch (Exception &exc)
      {
        MessageDlg("Ошибка TempQ (insert into SGB)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
        WT->Rollback();
        return;
      }
      num++;

    SG_DST->Next();
  }
  WT->Commit();
  NewFLG=false;
}


void __fastcall TAccountEditForm::FormActivate(TObject *Sender)
{
updateset();
}
//---------------------------------------------------------------------------


void __fastcall TAccountEditForm::MoveButtonClick(TObject *Sender)
{
TMoveRecordsForm *MRF=NULL;
AnsiString str,namep,sql,namef;
TpFIBQuery *Q=SaleBookDM->TempQuery;
TpFIBDataSet *DS;
TDateTime NewCountDate;
unsigned short NewNumber;
unsigned short dvp,yvp,mvp;
unsigned short dvp1,yvp1,mvp1;
int NumberKas=0;
int CodKas=1;
int indops=0;
int codzad=0;
int i=0;
int rn=0;
int kolzapsgb=0;
bool flg;


TDateTime dprn=AccountsJournalForm->getDate1();
dprn.DecodeDate(&yvp,&mvp,&dvp);
DS=SaleBookDM->SGBT;

count_total=0.00;
count_opl=0.00;
count_neopl=0.00;
count_tek=0.00;
count_pr=0.00;
count_raz=0.00;
count_neoplp=0.00;
count_oplp=0.00;
count_totali=0;
count_opli=0;
count_neopli=0;
count_neoplik=0;


SoldGoodsGrid->SelectedRows->SelectAll();

  try
  {
    MRF=new TMoveRecordsForm(this,SaleBookDM->EIDS,C_DS->FieldByName("CUSTOMER_ID")->AsInteger);
  }
  catch (Exception &exc)
  {
    MessageDlg("Ошибка создания формы для переноса записи\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }


  if(MRF->ShowModal()==mrOk)
  {
    int ID_To=MRF->IDMove;

    Q->Close();
    Q->SQL->Clear();
    Q->SQL->Add("select DESCRIPTION from EI where ID = "+IntToStr(ID_To));
    Q->ExecQuery();
    namep=Q->FieldByName("Description")->AsString;
    str="Вы уверены что хотите передать текущее задание ";

    Q->Close();
    Q->SQL->Clear();
    sql="select INDEXOPS as IND from NOMENCLATURE";
    sql+=" where CODP="+IntToStr(ID_To);

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
    if(!Q->FieldByName("IND")->IsNull)
    {
    indops=Q->FieldByName("IND")->AsInteger;
    if (indops>0) str+=" почтальону "; else str+=" в кассу ";
    }
    else
    {
//    MessageDlg("Данный почтальон не работает на участках!!! Аварийный выход из процедуры!!! - ",mtError,TMsgDlgButtons() << mbOK,0);
//    return;
    }
    str+=namep+"\"?";

    if(MessageDlg(str,mtConfirmation,TMsgDlgButtons() << mbOK << mbCancel,0)==mrOk)
    {
      SaveButton->Click();
     //Новые год и месяц счета
      NewCountDate=C_DS->FieldByName("COUNT_DATE")->AsDateTime;
      NewCountDate.DecodeDate(&yvp1,&mvp1,&dvp1);
     //Новый номер счета
      NewNumber=C_DS->FieldByName("COUNT_NUMBER")->AsInteger;
     //Если изменился номер или дата счета, проверяем можно новый счет сохранить
     if(NewNumber!=Number || NewCountDate!=CountDate)
      {
    //Проверяем BeginDate
      if(NewCountDate < SaleBookDM->BeginDate)
      { MessageDlg("Дата задания не может быть меньше даты начала работы с программой - "+SaleBookDM->BeginDate.DateString(),mtError,TMsgDlgButtons() << mbOK,0);
        DateEdit->SetFocus();
        return;
      }
    //Проверяем нет ли такого счета в таблице ACCOUNTS
      TempQ->Close();
      TempQ->SQL->Clear();
      if(NewCountDate > TDateTime("31.12.2008"))
      {
      sql="select * from ACCOUNTS where";
      sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
      sql+=" and COUNT_DATE='"+NewCountDate.DateString()+"'";
      sql+=" and COUNT_NUMBER="+IntToStr(NewNumber);
      }
      else
      {
      unsigned short y,m,d;
      NewCountDate.DecodeDate(&y,&m,&d);
      TDateTime dt1=TDateTime(y,m,1),
                dt2=TDateTime(y,m,SaleBookDM->LastDay(y,m));
      sql="select * from ACCOUNTS where";
      sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
      sql+=" and COUNT_DATE>='"+dt1.DateString()+"'";
      sql+=" and COUNT_DATE<='"+dt2.DateString()+"'";
      sql+=" and COUNT_NUMBER="+IntToStr(NewNumber);
      }
     TempQ->SQL->Add(sql);
     try
     {
      TempQ->ExecQuery();
     }
     catch (Exception &exc)
     { MessageDlg("Ошибка TempQ (ACCOUNTS)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
     }
     if(TempQ->RecordCount!=0)
     { MessageDlg("Номер задания не уникальный",mtWarning,TMsgDlgButtons() << mbOK,0);
      NumberEdit->SetFocus();
      return;
     }
    //Проверяем нет ли такого счета в таблице AccountsTemp
    TempQ->Close();
    TempQ->SQL->Clear();
    if(NewCountDate > TDateTime("31.12.2008"))
    { sql="select * from ACCOUNTS_TEMP where";
      sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
      sql+=" and COUNT_DATE='"+NewCountDate.DateString()+"'";
      sql+=" and COUNT_NUMBER="+IntToStr(NewNumber);
      sql+=" and USER_ID<>"+IntToStr(SaleBookDM->UserID);
    }
    else
    { unsigned short y,m,d;
      NewCountDate.DecodeDate(&y,&m,&d);
      TDateTime dt1=TDateTime(y,m,1),
                dt2=TDateTime(y,m,SaleBookDM->LastDay(y,m));
      sql="select * from ACCOUNTS_TEMP where";
      sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
      sql+=" and COUNT_DATE>='"+dt1.DateString()+"'";
      sql+=" and COUNT_DATE<='"+dt2.DateString()+"'";
      sql+=" and COUNT_NUMBER<="+IntToStr(NewNumber);
      sql+=" and USER_ID<>"+IntToStr(SaleBookDM->UserID);
    }

    TempQ->SQL->Add(sql);
    try
    {
      TempQ->ExecQuery();
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка TempQ (ACCOUNTS)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
    if(TempQ->RecordCount!=0)
    { MessageDlg("С этим заданием уже работает другой пользователь",mtWarning,TMsgDlgButtons() << mbOK,0);
      NumberEdit->SetFocus();
      return;
    }
  }

  //Cохраняем задание в таблице ACCOUNTS_TEMP
  if(C_DS->State==dsEdit || C_DS->State==dsInsert)
  { try
    {
      C_DS->Post();
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка сохранения записи в таблице ACCOUNTS_TEMP\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
  }

  // Определяем первый номер задания кассира если конечно он есть
  Q->Close();
  Q->SQL->Clear();
  sql="select COUNT_NUMBER as MIN_NUMBER from ACCOUNTS";
  sql+=" where ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
  sql+=" and COUNT_DATE='"+NewCountDate.DateString()+"'";
//  sql+=" and COUNT_DATE>='"+AccountsJournalForm->date1.DateString()+"'";
//  sql+=" and COUNT_DATE<='"+AccountsJournalForm->date2.DateString()+"'";
  sql+=" and M="+IntToStr(Month(NewCountDate));
  sql+=" and Y="+IntToStr(Year(NewCountDate));
  sql+=" and CUSTOMER_ID="+IntToStr(ID_To);
  sql+=" and USER_ID="+IntToStr(C_DS->FieldByName("USER_ID")->AsInteger);

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

 if(!Q->FieldByName("MIN_NUMBER")->IsNull)
 {
  NumberKas=Q->FieldByName("MIN_NUMBER")->AsInteger;
 }
 else
 {
  Q->Close();
  Q->SQL->Clear();
  sql="select max(COUNT_NUMBER) as MIN_NUMBER from ACCOUNTS";
  sql+=" where ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
  sql+=" and COUNT_DATE='"+NewCountDate.DateString()+"'";

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

  if(!Q->FieldByName("MIN_NUMBER")->IsNull){
  NumberKas=Q->FieldByName("MIN_NUMBER")->AsInteger+1;
  }else
  {
  NumberKas=1;
  }


  TQ->Close();
  TQ->SQL->Clear();
  sql="insert into ACCOUNTS ";
  sql+="(ORG_ID,COUNT_DATE,COUNT_NUMBER,CUSTOMER_ID,CUSTOMER_NAME,USER_ID,RS_ID,\
COUNT_TOTAL,EDIT_KEY,COUNT_TYPE,COUNT_OPL,COUNT_NEOPL,COUNT_TOTALI,COUNT_OPLI,COUNT_NEOPLI,\
COUNT_TEK,COUNT_PR,COUNT_RAZ,COUNT_NEOPLP,COUNT_OPLP,M,Y)";
  sql+=" values ("+IntToStr(SaleBookDM->OrganizationID);
  sql+=",'"+NewCountDate.DateString()+"'";
  sql+=","+IntToStr(NumberKas);
  sql+=","+IntToStr(ID_To);
  sql+=",'"+ namep.Trim();
  sql+="',"+IntToStr(C_DS->FieldByName("USER_ID")->AsInteger);
  sql+=","+IntToStr(0);
  sql+=","+FloatToStr(count_neoplk+count_neoplpk)+",1";
  sql+=","+IntToStr(C_DS->FieldByName("COUNT_TYPE")->AsInteger);
  sql+=","+FloatToStr(0.00);
  sql+=","+FloatToStr(0.00);
  sql+=","+IntToStr(0);
  sql+=","+IntToStr(0);
  sql+=","+IntToStr(0);
  sql+=","+FloatToStr(0.00);
  sql+=","+FloatToStr(0.00);
  sql+=","+FloatToStr(0.00);
  sql+=","+FloatToStr(0.00);
  sql+=","+FloatToStr(0.00);
  sql+=","+IntToStr(Month(NewCountDate));
  sql+=","+IntToStr(Year(NewCountDate))+")";
  TQ->SQL->Add(sql);
  try
  {
    TQ->ExecQuery();
  }
  catch (Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    WT->Rollback();
    return;
  }
  WT->Commit();
 }

      rn=SoldGoodsDS->RecNo;
   for(i=0; i<SoldGoodsGrid->SelectedRows->Count; ++i)
   {
      SoldGoodsDS->GotoBookmark((void *)SoldGoodsGrid->SelectedRows->Items[i].c_str());
      Q->Close();
      Q->SQL->Clear();
      sql="select count(LCHET) as CL from SGB";
      sql+=" where ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
      sql+=" and COUNT_DATE='"+NewCountDate.DateString()+"'";
      sql+=" and COUNT_NUMBER="+IntToStr(NumberKas);
      sql+=" and LCHET="+IntToStr(SoldGoodsDS->FieldByName("LCHET")->AsInteger);

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

      if(!Q->FieldByName("CL")->IsNull){
      kolzapsgb=Q->FieldByName("CL")->AsInteger;
      if (kolzapsgb>0)
      {
      WT->StartTransaction();
     //Удаляем старые записи о поручениях из таблицы SGB
      TQ->Close();
      TQ->SQL->Clear();
      sql="delete from SGB where";
      sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
      sql+=" and COUNT_DATE='"+CountDate.DateString()+"'";
      sql+=" and COUNT_NUMBER="+IntToStr(NumberKas);
      sql+=" and LCHET="+IntToStr(SoldGoodsDS->FieldByName("LCHET")->AsInteger);
      TQ->SQL->Add(sql);
      try
      {
      TQ->ExecQuery();
      }
      catch (Exception &exc)
      {
       MessageDlg("Ошибка TempQ (delete from SGB)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
       WT->Rollback();
       return;
      }
      WT->Commit();
      }
      }else
      {
      kolzapsgb=0;
      }

      DS->Close();
      DS->SQLs->SelectSQL->Clear();
      sql="select * from SGBT where LCHET = " + IntToStr(SoldGoodsDS->FieldByName("LCHET")->AsInteger);
      sql+=" and USER_ID="+IntToStr(C_DS->FieldByName("USER_ID")->AsInteger);
      DS->SQLs->SelectSQL->Add(sql);
      try
      {
      DS->Open();
      }
      catch(const Exception &exc)
      {
        MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
        return;
      }
      DS->First();
      int id=1;
      while(!DS->Eof)
      {
      count_total=0.00;
      count_opl=0.00;
      count_neopl=0.00;
      count_tek=0.00;
      count_pr=0.00;
      count_raz=0.00;
      count_neoplp=0.00;
      count_oplp=0.00;
      count_totali=0;
      count_opli=0;
      count_neopli=0;
      count_neoplik=0;

      if (DS->FieldByName("LCHET1")->AsString.Trim()=="Прошврем")
      {
      count_tek=0.00;
      count_pr=DS->FieldByName("SUMMA")->AsFloat;
      if (DS->FieldByName("PRICH")->AsString.Trim()==""){
      if (id==1) count_opli=1;
      count_oplp=DS->FieldByName("SUMMA")->AsFloat;
      }else
      {
      if (id==1) count_neopli=1;
      count_neoplp=DS->FieldByName("SUMMA")->AsFloat;
      }
      }

      if (DS->FieldByName("LCHET1")->AsString.Trim()=="раздел 1")
      {
      count_tek=0.00;
      count_raz=DS->FieldByName("SUMMA")->AsFloat;
      if (DS->FieldByName("PRICH")->AsString.Trim()==""){
      if (id==1) count_opli=1;
      count_oplp=DS->FieldByName("SUMMA")->AsFloat;
      }else
      {
      if (id==1) count_neopli=1;
      count_neoplp=DS->FieldByName("SUMMA")->AsFloat;
      }
      }

      if (DS->FieldByName("LCHET1")->AsString.Trim()!="раздел 1" && DS->FieldByName("LCHET1")->AsString.Trim()!="Прошврем")
      {
      count_tek=DS->FieldByName("SUMMA")->AsFloat;
      count_raz=0.00;
      count_pr=0.00;
      if (DS->FieldByName("PRICH")->AsString.Trim()==""){
      if (id==1) count_opli=1;
      count_opl=DS->FieldByName("SUMMA")->AsFloat;
      }else
      {
      if (id==1) count_neopli=1;
      count_neopl=DS->FieldByName("SUMMA")->AsFloat;
      }
      }

      WT->StartTransaction();
      TQ->Close();
      TQ->SQL->Clear();
      sql="insert into SGB";
      sql+="(ORG_ID,COUNT_DATE,COUNT_NUMBER,\
      LCHET1,SUMMA,WORD,METKA,NEOPL,PNN,LCHET,FAMILY,NAME,\
      FATHER,KOD,C,DOC,SERIA,NOMER,DOST,D_VIPL,ULIC,ADRES,CHEL,METKA1,VNOM,PRICH,IST,BSUMMA,";
      sql+="BWORD,FAKT_CHEL,FAKT_DAT,NSP,KEM_VID,DATA_VID,M,Y,KODPEN,FOND,KASSA) values(";
      sql+=IntToStr(SaleBookDM->OrganizationID);
      sql+=",'"+NewCountDate.DateString()+"'";
      sql+=","+IntToStr(NumberKas)+",'";;
      sql+=DS->FieldByName("LCHET1")->AsString.Trim()+"',";
      sql+=AnsiString().sprintf("%.02lf",DS->FieldByName("SUMMA")->AsFloat)+",'";
      sql+=DS->FieldByName("WORD")->AsString.Trim()+"',";
      sql+=IntToStr(DS->FieldByName("METKA")->AsInteger)+",";
      sql+=IntToStr(DS->FieldByName("NEOPL")->AsInteger)+",";
      sql+=IntToStr(DS->FieldByName("PNN")->AsInteger)+",";
      sql+=IntToStr(DS->FieldByName("LCHET")->AsInteger)+",'";
      sql+=DS->FieldByName("FAMILY")->AsString.Trim()+"','";
      sql+=DS->FieldByName("NAME")->AsString.Trim()+"','";
      sql+=DS->FieldByName("FATHER")->AsString.Trim()+"',";
      sql+=IntToStr(DS->FieldByName("KOD")->AsInteger)+",'";
      sql+=DS->FieldByName("C")->AsDateTime.DateString()+"','";
      sql+=DS->FieldByName("DOC")->AsDateTime.DateString()+"','";
      sql+=DS->FieldByName("SERIA")->AsString.Trim()+"',";
      sql+=IntToStr(DS->FieldByName("NOMER")->AsInteger)+",";
      sql+=IntToStr(DS->FieldByName("DOST")->AsInteger)+",";
      sql+=IntToStr(DS->FieldByName("D_VIPL")->AsInteger)+",'";
      sql+=DS->FieldByName("ULIC")->AsString.Trim()+"','";
      sql+=DS->FieldByName("ADRES")->AsString.Trim()+"',";
      sql+=IntToStr(DS->FieldByName("CHEL")->AsInteger)+",";
      sql+=IntToStr(DS->FieldByName("METKA1")->AsInteger)+",";
      sql+=IntToStr(DS->FieldByName("VNOM")->AsInteger)+",'";
      sql+=DS->FieldByName("PRICH")->AsString.Trim()+"',";
      sql+=IntToStr(DS->FieldByName("IST")->AsInteger)+",";
      sql+=AnsiString().sprintf("%.02lf",DS->FieldByName("BSUMMA")->AsFloat)+",'";
      sql+=DS->FieldByName("BWORD")->AsString.Trim()+"',";
      sql+=IntToStr(ID_To)+",";
      sql+=IntToStr(dvp)+",";
      sql+=IntToStr(DS->FieldByName("NSP")->AsInteger)+",'";
      sql+=DS->FieldByName("KEM_VID")->AsString.Trim()+"','";
      sql+=DS->FieldByName("DATA_VID")->AsDateTime.DateString()+"',";
      sql+=IntToStr(mvp);
      sql+=","+IntToStr(yvp)+",";
      sql+=IntToStr(DS->FieldByName("KODPEN")->AsInteger)+",";
      sql+=IntToStr(DS->FieldByName("FOND")->AsInteger)+",";
      sql+=IntToStr(DS->FieldByName("KASSA")->AsInteger)+")";
      TQ->SQL->Add(sql);
      try
      {
        TQ->ExecQuery();
      }
      catch (Exception &exc)
      {
        MessageDlg("Ошибка TempQ (insert into SGB)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
        WT->Rollback();
        return;
      }
      WT->Commit();
      str="Запись ";
      str+=DS->FieldByName("LCHET1")->AsString.Trim();
      str+=" на сумму ";
      str+=AnsiString().sprintf("%.02lf",DS->FieldByName("SUMMA")->AsFloat);
      //Фиксирем действие в журнале событий ACTIONS_JOURNAL
      WT->StartTransaction();
      flg=SaleBookDM->AddRecordToActionsJournal(EditRecordFromAccountsTable,str,WT);
      //Подтверждаем результаты изменений
      if(flg==true) WT->Commit();   else WT->Rollback();
      DS->Next();
      id++;
      }
      DS->Close();

  count_total=count_raz+count_pr+count_tek;
  WT->StartTransaction();

  Q->Close();
  Q->SQL->Clear();
  sql="select * from ACCOUNTS";
  sql+=" where ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
  sql+=" and COUNT_NUMBER="+IntToStr(NumberKas);
  sql+=" and COUNT_DATE='"+NewCountDate.DateString()+"'";
  sql+=" and M="+IntToStr(Month(NewCountDate));
  sql+=" and Y="+IntToStr(Year(NewCountDate));
  sql+=" and CUSTOMER_ID="+IntToStr(ID_To);
  sql+=" and USER_ID="+IntToStr(C_DS->FieldByName("USER_ID")->AsInteger);

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
  TQ->Close();
  TQ->SQL->Clear();
  sql="update ACCOUNTS set ";
  sql+="COUNT_TOTAL="+FloatToStr(Q->FieldByName("COUNT_TOTAL")->AsFloat+count_total)+",";
  sql+="COUNT_OPL="+FloatToStr(Q->FieldByName("COUNT_OPL")->AsFloat+count_opl)+",";
  sql+="COUNT_NEOPL="+FloatToStr(Q->FieldByName("COUNT_NEOPL")->AsFloat+count_neopl)+",";
  sql+="COUNT_TOTALI="+IntToStr(Q->FieldByName("COUNT_TOTALI")->AsInteger+1)+",";
  sql+="COUNT_NEOPLI="+IntToStr(Q->FieldByName("COUNT_NEOPLI")->AsInteger+count_neopli)+",";
  sql+="COUNT_OPLI="+IntToStr(Q->FieldByName("COUNT_OPLI")->AsInteger+count_opli)+",";
  sql+="COUNT_TEK="+FloatToStr(Q->FieldByName("COUNT_TEK")->AsFloat+count_neopl)+",";
  sql+="COUNT_PR="+FloatToStr(Q->FieldByName("COUNT_PR")->AsFloat+count_pr)+",";
  sql+="COUNT_RAZ="+FloatToStr(Q->FieldByName("COUNT_RAZ")->AsFloat+count_raz)+",";
  sql+="COUNT_NEOPLP="+FloatToStr(Q->FieldByName("COUNT_NEOPLP")->AsFloat+count_neoplp)+",";
  sql+="COUNT_OPLP="+FloatToStr(Q->FieldByName("COUNT_OPLP")->AsFloat+count_oplp);
  sql+=" where ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
  sql+=" and COUNT_NUMBER="+IntToStr(NumberKas);
  sql+=" and M="+IntToStr(Month(NewCountDate));
  sql+=" and Y="+IntToStr(Year(NewCountDate));
  sql+=" and CUSTOMER_ID="+IntToStr(ID_To);
  sql+=" and USER_ID="+IntToStr(C_DS->FieldByName("USER_ID")->AsInteger);
  TQ->SQL->Add(sql);
  try
  {
    TQ->ExecQuery();
  }
  catch (Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    WT->Rollback();
    return;
  }
  WT->Commit();

  //Стартуем транзакцию
  WT->StartTransaction();
  //Удаляем старые записи о поручениях из таблицы SGB
  TQ->Close();
  TQ->SQL->Clear();
  sql="delete from SGB where";
  sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
  sql+=" and COUNT_DATE='"+CountDate.DateString()+"'";
  sql+=" and COUNT_NUMBER="+IntToStr(Number);
  sql+=" and LCHET="+IntToStr(SoldGoodsDS->FieldByName("LCHET")->AsInteger);
  TQ->SQL->Add(sql);
  try
  {
    TQ->ExecQuery();
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка TempQ (delete from SGB)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    WT->Rollback();
    return;
  }
  WT->Commit();

  sql="delete from SGBT where USER_ID="+IntToStr(SaleBookDM->UserID);


  //Стартуем транзакцию
  WT->StartTransaction();
  //Удаляем старые записи о поручениях из таблицы SGBT
  TQ->Close();
  TQ->SQL->Clear();
  sql="delete from SGBT where";
  sql+=" USER_ID="+IntToStr(SaleBookDM->UserID);
  sql+=" and LCHET="+IntToStr(SoldGoodsDS->FieldByName("LCHET")->AsInteger);
  TQ->SQL->Add(sql);
  try
  {
    TQ->ExecQuery();
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка TempQ (delete from SGB)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    WT->Rollback();
    return;
  }
  WT->Commit();
 }
}
      updateset();
      ras();
      SoldGoodsDS->RecNo=rn;
      SoldGoodsGrid->SelectedRows->CurrentRowSelected=true;
  //Итоговая сумма
count_opl=StrToFloat(StaticText7->Caption);
count_neopl=StrToFloat(StaticText9->Caption);
count_tek=StrToFloat(StaticText4->Caption);
count_pr=StrToFloat(StaticText5->Caption);
count_raz=StrToFloat(StaticText6->Caption);
count_neoplp=StrToFloat(StaticText10->Caption);
count_oplp=StrToFloat(StaticText8->Caption);
count_total=count_raz+count_pr+count_tek;

count_totali=StrToInt(StaticText1->Caption);
count_opli=StrToInt(StaticText2->Caption);
count_neopli=StrToInt(StaticText3->Caption);

  WT->StartTransaction();
  TQ->Close();
  TQ->SQL->Clear();
  sql="update ACCOUNTS set ";
  sql+="COUNT_TOTAL="+FloatToStr(count_total)+",";
  sql+="COUNT_OPL="+FloatToStr(count_opl)+",";
  sql+="COUNT_NEOPL="+FloatToStr(count_neopl)+",";
  sql+="COUNT_TOTALI="+IntToStr(count_totali)+",";
  sql+="COUNT_NEOPLI="+IntToStr(count_neopli)+",";
  sql+="COUNT_OPLI="+IntToStr(count_opli)+",";
  sql+="COUNT_TEK="+FloatToStr(count_neopl)+",";
  sql+="COUNT_PR="+FloatToStr(count_pr)+",";
  sql+="COUNT_RAZ="+FloatToStr(count_raz)+",";
  sql+="COUNT_NEOPLP="+FloatToStr(count_neoplp)+",";
  sql+="COUNT_OPLP="+FloatToStr(count_oplp);
  sql+=" where ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
  sql+=" and COUNT_NUMBER="+IntToStr(C_DS->FieldByName("COUNT_NUMBER")->AsInteger);
  sql+=" and M="+IntToStr(Month(NewCountDate));
  sql+=" and Y="+IntToStr(Year(NewCountDate));
  sql+=" and CUSTOMER_ID="+IntToStr(C_DS->FieldByName("CUSTOMER_ID")->AsInteger);
  sql+=" and USER_ID="+IntToStr(C_DS->FieldByName("USER_ID")->AsInteger);
  TQ->SQL->Add(sql);
  try
  {
    TQ->ExecQuery();
  }
  catch (Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    WT->Rollback();
    return;
  }
  WT->Commit();


    Q->Close();
    Q->SQL->Clear();
    Q->SQL->Add("select DESCRIPTION from EI where ID = "+IntToStr(ID_To));
    Q->ExecQuery();
    namep=Q->FieldByName("Description")->AsString;

    Q->Close();
    Q->SQL->Clear();
    Q->SQL->Add("select DESCRIPTION from EI where ID = "+IntToStr(C_DS->FieldByName("CUSTOMER_ID")->AsInteger));
    Q->ExecQuery();
    namef=Q->FieldByName("Description")->AsString;

    str=" Удачно  передано текущее задание ";

    Q->Close();
    Q->SQL->Clear();
    sql="select INDEXOPS as IND from NOMENCLATURE";
    sql+=" where CODP="+IntToStr(ID_To);

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

    if(!Q->FieldByName("IND")->IsNull)
    {
    indops=Q->FieldByName("IND")->AsInteger;
    if (indops>0) str+=" почтальону "; else str+=" в кассу ";
    }
    else
    {
//    MessageDlg("Нет ни одной кассы в справочнике!!! Аварийный выход из процедуры!!!",mtError,TMsgDlgButtons() << mbOK,0);
    return;
    }

    str+=namep+" от ";
    str+=namef+"\!";
    MessageDlg(str,mtWarning,TMsgDlgButtons() << mbOK,0);


  //Фиксирем действие в журнале событий ACTIONS_JOURNAL
  WT->StartTransaction();
  flg=SaleBookDM->AddRecordToActionsJournal(EditRecordFromAccountsTable,str,WT);
  //Подтверждаем результаты изменений
  if(flg==true) WT->Commit();   else WT->Rollback();

    if(count_totali==0 && count_neoplik==0)
  {
  WT->StartTransaction();
  TQ->Close();
  TQ->SQL->Clear();
  sql="delete from ACCOUNTS where";
  sql+=" ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
  sql+=" and COUNT_DATE='"+CountDate.DateString()+"'";
  sql+=" and COUNT_NUMBER="+IntToStr(C_DS->FieldByName("COUNT_NUMBER")->AsInteger);
  TQ->SQL->Add(sql);

  try
  {
    TQ->ExecQuery();
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка TempQ (delete from ACCOUNTS)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    WT->Rollback();
    return;
  }
  WT->Commit();
  Close();
  }

  }

  if(Application->FindComponent("AccountsJournalForm"))
  {
  AccountsJournalForm->LoadDataSet();
  }

  if(MRF!=NULL){ delete MRF; MRF=NULL;}
}
//---------------------------------------------------------------------------

bool __fastcall TAccountEditForm::prov(void)
{

AnsiString prich1,prich2;

//  WT->StartTransaction();
  SG_DST->First();
  while(!SG_DST->Eof)
  {
   if (SG_DST->FieldByName("LCHET1")->AsString.Trim()=="Прошврем" || SG_DST->FieldByName("LCHET1")->AsString.Trim()=="раздел 1")
   {
     if (!SG_DST->FieldByName("PRICH")->IsNull) prich2=SG_DST->FieldByName("PRICH")->AsString.Trim(); else prich2="";
     SG_DST->Prior();
     if (!SG_DST->FieldByName("PRICH")->IsNull) prich1=SG_DST->FieldByName("PRICH")->AsString.Trim(); else prich1="";
     SG_DST->Next();
     if (prich2 != prich1)
     {
      return false;
     }
   }
    SG_DST->Next();
  }
return true;
}






void __fastcall TAccountEditForm::SoldGoodsGridMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
AnsiString sql,str,countdate,fs;
unsigned short dvp,yvp,mvp;
TDateTime dprn=AccountsJournalForm->getDate1();
dprn.DecodeDate(&yvp,&mvp,&dvp);
int countnumber;
fs="Касса";


  if(SG_DST->FieldByName("KASSA")->AsInteger ==1 )
  {
    TempQ->Close();
    TempQ->SQL->Clear();

      sql="select * from SGB where LCHET="+IntToStr(SG_DST->FieldByName("LCHET")->AsInteger);
      sql+=" and M="+IntToStr(mvp);
      sql+=" and Y="+IntToStr(yvp);
      sql+=" and KASSA=0";

    TempQ->SQL->Add(sql);
    try
    {
      TempQ->ExecQuery();
    }
    catch (Exception &exc)
    {
      MessageDlg("Ошибка TempQ (SGB)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }

    if(TempQ->RecordCount!=0)
    {
    countnumber=TempQ->FieldByName("COUNT_NUMBER")->AsInteger;
    countdate=TempQ->FieldByName("COUNT_DATE")->AsDateTime.DateString();
    TempQ->Close();
    TempQ->SQL->Clear();
    sql="select a.*, c.DESCRIPTION as CUSTOMER_NAME, u.LOGIN as USER_NAME";
    sql+=" from ACCOUNTS a";
    sql+=" left outer join EI c on c.ID=a.CUSTOMER_ID";
    sql+=" left outer join USERS u on u.ID=a.USER_ID";
    sql+=" where a.ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
    sql+=" and a.COUNT_DATE='"+countdate.Trim()+"'";
    sql+=" and a.COUNT_NUMBER="+IntToStr(countnumber);
    TempQ->SQL->Add(sql);
    try
    {
      TempQ->ExecQuery();
    }
    catch (Exception &exc)
    {
      MessageDlg("Ошибка TempQ (SGB)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }

    if(TempQ->RecordCount!=0)
    {
    str=" Оплачено по заданию № ";
    str+=IntToStr(countnumber);
    str+=" от ";
    str+=countdate.Trim();
    if(TempQ->FieldByName("CUSTOMER_NAME")->AsString.Pos(fs))
    {
    str+=" на кассе - ";
    str+=TempQ->FieldByName("CUSTOMER_NAME")->AsString.Trim();
    }else
    {
    str+=" почтальон - ";
    str+=TempQ->FieldByName("CUSTOMER_NAME")->AsString.Trim();
    }
    str+=" автор - ";
    str+=TempQ->FieldByName("USER_NAME")->AsString.Trim();
    Label19->Caption=str;
    Label19->Visible=true;
    }
    else
    {
    Label19->Caption="";
    Label19->Visible=false;
    }
    }
  }else
  {
    Label19->Caption="";
    Label19->Visible=false;
  }
}
//---------------------------------------------------------------------------


void __fastcall TAccountEditForm::SoldGoodsGridColumns8UpdateData(
      TObject *Sender, AnsiString &Text, Variant &Value, bool &UseText,
      bool &Handled)
{
  if(!Text.IsEmpty()) SG_DST->FieldByName("FAKT_DAT")->AsInteger=StrToInt(Text.Trim());
  else SG_DST->FieldByName("FAKT_DAT")->AsInteger=1;
}
//---------------------------------------------------------------------------



void __fastcall TAccountEditForm::DelAllButtonClick(TObject *Sender)
{
AnsiString sql="";
unsigned short dvp,yvp,mvp;
TDateTime dprn;
TpFIBDataSet *TZ;


if(Application->FindComponent("AccountsJournalForm")) dprn=AccountsJournalForm->getDate1(); else dprn=Date();
dprn.DecodeDate(&yvp,&mvp,&dvp);

  if(MessageDlg("Вы действительно хотите удалить все поручения из задания?",mtConfirmation,TMsgDlgButtons() << mbOK << mbCancel,0)==mrOk)
  {
  //Стартуем транзакцию
  WT->StartTransaction();
  //Удаляем старые записи о поручениях из таблицы SGB  НЕПРАВИЛЬНО ТУТ ОШИБКА!!!!!
  TQ->Close();
  TQ->SQL->Clear();
  sql="delete from SGBT where USER_ID="+IntToStr(SaleBookDM->UserID);

  TQ->SQL->Add(sql);
  try
  {
    TQ->ExecQuery();
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка TempQ (delete from SGB)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    WT->Rollback();
    return;
  }
  WT->Commit();
  updateset();
  ras();
  }
}
//---------------------------------------------------------------------------

void __fastcall TAccountEditForm::SoldGoodsDSPRICHChange(TField *Sender)
{
AnsiString prich,sql,s;
unsigned short dvp,yvp,mvp;
TDateTime CountDate;


if(SG_DST->State!=dsEdit && SG_DST->State!=dsInsert) return;

if (!NewFLG)
{
TDateTime dprn=C_DS->FieldByName("COUNT_DATE")->AsDateTime;
dprn.DecodeDate(&yvp,&mvp,&dvp);

  if(SG_DST->FieldByName("KASSA")->AsInteger ==1 )
  {
  MessageDlg("Нельзя менять причины невыплаты для текущего поручения уже оплаченных позднее !!!",mtError,TMsgDlgButtons() << mbOK,0);
  SG_DST->Cancel();
  SG_DST->Edit();
  return;
  }

  TempQ->Close();
  TempQ->SQL->Clear();
  sql="select count (LCHET) as CR from SGB where";
  sql+=" LCHET="+IntToStr(SG_DST->FieldByName("LCHET")->AsInteger);
  sql+=" and sgb.count_date>'" +dprn.DateString() + "' and sgb.prich='н/д' and sgb.kassa=0";

  TempQ->SQL->Add(sql);
   try
   {
   TempQ->ExecQuery();
   }
   catch (Exception &exc)
   {
   MessageDlg("Ошибка TempQ (SGB)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
   return;
   }
  if(TempQ->FieldByName("CR")->AsInteger > 1)
  {
  MessageDlg("Нельзя менять причины невыплаты для текущего поручения уже отмеченных как нет дома позднее !!!",mtError,TMsgDlgButtons() << mbOK,0);
  SG_DST->Cancel();
  SG_DST->Edit();
  return;
  }

      prich=SG_DST->FieldByName("PRICH")->AsString.Trim();
      if (prich.IsEmpty()) prich="";
      TempQ->Close();
      TempQ->SQL->Clear();
      sql="select count (LCHET) as CR from SGBT where";
      sql+=" LCHET="+IntToStr(SG_DST->FieldByName("LCHET")->AsInteger);
      sql+=" and USER_ID="+IntToStr(SaleBookDM->UserID);

      TempQ->SQL->Add(sql);
      try
      {
       TempQ->ExecQuery();
      }
      catch (Exception &exc)
      {
       MessageDlg("Ошибка TempQ (SGB)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
       return;
      }
      if(TempQ->FieldByName("CR")->AsInteger > 1)
      {
       int rn=SG_DST->RecNo;

       TQ->Close();
       TQ->SQL->Clear();
       sql="update SGBT set PRICH= ' " + prich.Trim() + " ' where";
       sql+=" LCHET="+IntToStr(SG_DST->FieldByName("LCHET")->AsInteger);
       sql+=" and USER_ID="+IntToStr(SaleBookDM->UserID);
       TQ->SQL->Add(sql);
       TQ->Transaction->StartTransaction();
       try
       {
        TQ->ExecQuery();
       }
       catch(const Exception &exc)
       {
        MessageDlg("Ошибка WQ (update SGBT set PRICH=)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
        TQ->Transaction->Rollback();
        return;
       }
       TQ->Transaction->Commit();
       updateset();
       ras();
       SG_DST->RecNo=rn;
       SG_DST->Edit();
      }
//SG_DST->Post();
}
}
//---------------------------------------------------------------------------



void __fastcall TAccountEditForm::SoldGoodsGridCellClick(TColumnEh *Column)
{
  Edit2->Text=IntToStr(SoldGoodsGrid->SelectedRows->Count);
   if (SoldGoodsGrid->SelectedRows->Count==0)
   {
   AddButton->Enabled=true;
   OstButton->Enabled=false;
   }
   else
   {
   AddButton->Enabled=false;
   OstButton->Enabled=true;
   }
}
//---------------------------------------------------------------------------

void __fastcall TAccountEditForm::OstButtonClick(TObject *Sender)
{
AnsiString sql="";
TDataSet *Count=SoldGoodsGrid->DataSource->DataSet;
AnsiString otbor;


if (SoldGoodsGrid->SelectedRows->Count==0)
{
    MessageDlg("Нет выбранных поручений для оставления в текущем заданий!!! ",mtWarning,TMsgDlgButtons() << mbOK,0);
    return;
}

  for(int r=0; r<SoldGoodsGrid->SelectedRows->Count; r++)
  {
    Count->GotoBookmark((void *)this->SoldGoodsGrid->SelectedRows->Items[r].c_str());
    if (SoldGoodsGrid->SelectedRows->Count==1)
    {
    otbor=IntToStr(Count->FieldByName("LCHET")->AsInteger);
    }else
    {
    otbor+=IntToStr(Count->FieldByName("LCHET")->AsInteger);
    if (r!=SoldGoodsGrid->SelectedRows->Count-1) otbor+=",";
    }
  }

  if(MessageDlg("Вы действительно хотите оставить отобранные поручения в задание , а остальные удалить?",mtConfirmation,TMsgDlgButtons() << mbOK << mbCancel,0)==mrOk)
  {
  //Стартуем транзакцию
  WT->StartTransaction();
  //Удаляем ненужные записи о поручениях из таблицы SGBT
  TQ->Close();
  TQ->SQL->Clear();
  sql="delete from SGBT where USER_ID="+IntToStr(SaleBookDM->UserID);
  sql+=" and SGBT.LCHET NOT IN ("+otbor+")";

  TQ->SQL->Add(sql);
  try
  {
    TQ->ExecQuery();
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка TempQ (delete from SGB)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    WT->Rollback();
    return;
  }
  WT->Commit();
  updateset();
  ras();
  }
  Edit2->Text=IntToStr(SoldGoodsGrid->SelectedRows->Count);
}
//---------------------------------------------------------------------------

void __fastcall TAccountEditForm::provkassa(void)
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

