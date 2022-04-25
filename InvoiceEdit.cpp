//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "AccauntsJournal.h"
#include "DataModule.h"
//#include "Contractors.h"
#include "SelectNumber.h"
#include "InvoiceReckonings.h"
#include "SpeedAPDoc.h"
#include "InvoiceEdit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Placemnt"
#pragma link "SmrtPanel"
#pragma link "ToolEdit"
#pragma link "FIBDataSet"
#pragma link "pFIBDataSet"
#pragma link "FIBQuery"
#pragma link "pFIBQuery"
#pragma link "pFIBStoredProc"
#pragma link "FIBDatabase"
#pragma link "pFIBDatabase"
#pragma link "JvComponent"
#pragma link "JvExControls"
#pragma link "JvXPButtons"
#pragma link "JvXPCore"
#pragma link "JvXPCheckCtrls"
#pragma link "JvExMask"
#pragma link "JvToolEdit"
#pragma resource "*.dfm"
//TInvoiceEditForm *InvoiceEditForm;
//---------------------------------------------------------------------------
//Новая счет-фактура
__fastcall TInvoiceEditForm::TInvoiceEditForm(TComponent* Owner, TpFIBDataSet *A_DS)
        : TForm(Owner)
{
AnsiString sql;
TDateTime dt, dtc;
unsigned short y,m,d;
TDateTime dt1, dt2;

  FormStorage1->IniFileName=MainForm->getIniFileName();
  FormStorage1->IniSection="InvoiceEditForm";

  InvoiceTypeBox->Height=20;

  NewInvoiceFLG=true;
  OrgID=A_DS->FieldByName("ORG_ID")->AsInteger;
  CountNumber=A_DS->FieldByName("COUNT_NUMBER")->AsInteger;
  CountDate=A_DS->FieldByName("COUNT_DATE")->AsDateTime;
  BuyerID=A_DS->FieldByName("CUSTOMER_ID")->AsInteger;

  InvoiceTypeBox->ItemIndex=1;
  advanceCheckbox->Checked=false;
  revisionCheckbox->Checked=false;
  ConsigneeID=0;

  //Устанавливаем дату счет-фактуры
  invoiceDateEdit->Date=0.0;
//  Date().DecodeDate(&y,&m,&d);
//  dt=TDateTime(y,m,SaleBookDM->LastDay(y,m));
//  if(dt > Date()) dt=Date();
//  if(CountDate >= SaleBookDM->BeginDate) dtc=CountDate;
//  else dtc=SaleBookDM->BeginDate;
  dt=dtc=CountDate;
  dt.DecodeDate(&y,&m,&d);
  do
  { TQ->Close();
    TQ->SQL->Clear();
    if(dt > TDateTime("31.12.2008"))
    { sql="select INVOICE_NUMBER, INVOICE_DATE from INVOICES where";
      sql+=" ORG_ID="+IntToStr(OrgID);
      sql+=" and INVOICE_DATE='"+dt.DateString()+"'";
      sql+=" order by INVOICE_NUMBER desc";
    }
    else
    { dt1=TDateTime(y,m,1),
      dt2=TDateTime(y,m,SaleBookDM->LastDay(y,m));
      sql="select INVOICE_NUMBER, INVOICE_DATE from INVOICES where";
      sql+=" ORG_ID="+IntToStr(OrgID);
      sql+=" and INVOICE_DATE>='"+dt1.DateString()+"'";
      sql+=" and INVOICE_DATE<='"+dt2.DateString()+"'";
      sql+=" order by INVOICE_NUMBER desc";
    }
    TQ->SQL->Add(sql);
    try
    {
      TQ->ExecQuery();
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка TQ->ExecQuery() - 1\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
    if(TQ->RecordCount > 0)
    { invoiceDateEdit->Date=TQ->FieldByName("INVOICE_DATE")->AsDateTime;
      break;
    }
    if(dt > TDateTime("31.12.2008"))
      dt--;
    else
    { m--;
      if(m==0){ y--; m=12;}
      dt1=TDateTime(y,m,1),
      dt2=TDateTime(y,m,SaleBookDM->LastDay(y,m));
    }
  }while(dt>dtc);
  if(invoiceDateEdit->Date < dtc) invoiceDateEdit->Date=dtc;
  PrevID=invoiceDateEdit->Date;
  oldINumber=StrToInt(InvoiceNumberEdit->Text);
  if(InvoiceNumberEdit->Text.IsEmpty()) InvoiceNumberEdit->Text="1";

  TQ->Close();
  TQ->SQL->Clear();
  sql="select DESCRIPTION from CONTRACTORS where";
  sql+=" ID="+IntToStr(BuyerID);
  TQ->SQL->Add(sql);
  try
  {
    TQ->ExecQuery();
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка TQ->ExecQuery() - 2\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  buyerEdit->Text=TQ->FieldByName("DESCRIPTION")->AsString;
  consigneeEdit->Text="-";
/*  if(ConsigneeID==BuyerID) ConsigneeEdit->Text=BuyerEdit->Text;
  else
  { TQ->Close();
    TQ->SQL->Clear();
    sql="select DESCRIPTION from CONTRACTORS where";
    sql+=" ID="+IntToStr(ConsigneeID);
    TQ->SQL->Add(sql);
    try
    {
      TQ->ExecQuery();
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка TQ->ExecQuery() - 2\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
    ConsigneeEdit->Text=TQ->FieldByName("DESCRIPTION")->AsString;
  }
  */
  Label6->Caption=SaleBookDM->getByCountStr(OrgID,CountNumber,CountDate);// "К счету № "+IntToStr()+" от "+.DateString();
  PADocs->Clear();
}
//--------------------------------------------------------------------------
//Редактирование счет-фактуры
__fastcall TInvoiceEditForm::TInvoiceEditForm(TComponent* Owner, int Org_ID, int Inv_Num, TDateTime Inv_Date, int Count_Number, TDateTime Count_Date)
        : TForm(Owner)
{
AnsiString sql;

  FormStorage1->IniFileName=MainForm->WorkDir+"SB_2009.ini";
  FormStorage1->IniSection="SFRegistrationForm";

  NewInvoiceFLG=false;
  OrgID=Org_ID;
  InvNum=Inv_Num;
  InvDate=Inv_Date;
  CountNumber=Count_Number;
  CountDate=Count_Date;
  invoiceDateEdit->Date=InvDate;
  InvoiceNumberEdit->Text=IntToStr(InvNum);
  if(InvDate < SaleBookDM->BeginDate)
  { invoiceDateEdit->Enabled=false;
    InvoiceNumberEdit->Enabled=false;
    SelectNumberButton->Enabled=false;
  }
  PrevID=TDateTime(invoiceDateEdit->Text);

  TQ->Close();
  TQ->SQL->Clear();
  sql="select * from INVOICES where";
  sql+=" ORG_ID="+IntToStr(OrgID);
  sql+=" and INVOICE_DATE='"+InvDate.DateString()+"'";
  sql+=" and INVOICE_NUMBER="+IntToStr(InvNum);
  TQ->SQL->Add(sql);
  try
  {
    TQ->ExecQuery();
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка TQ->ExecQuery() - 3\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  BuyerID=TQ->FieldByName("BUYER_ID")->AsInteger;
  InvoiceTypeBox->ItemIndex=TQ->FieldByName("INVOICE_TYPE")->AsInteger;
  advanceCheckbox->Checked=TQ->FieldByName("ADVANCE_FLG")->AsBoolean;
  revisionCheckbox->Checked=TQ->FieldByName("REVISION_FLG")->AsBoolean;
  if(InvoiceTypeBox->ItemIndex==0)
    ConsigneeID=TQ->FieldByName("CONSIGNEE_ID")->AsInteger;
  else ConsigneeID=0;
  PADocs->Clear();
  PADocs->Lines->Add(SaleBookDM->getPADocsString(SaleBookDM->OrganizationID,InvDate,InvNum));

  TQ->Close();
  TQ->SQL->Clear();
  sql="select DESCRIPTION from CONTRACTORS where";
  sql+=" ID="+IntToStr(BuyerID);
  TQ->SQL->Add(sql);
  try
  {
    TQ->ExecQuery();
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка TQ->ExecQuery() - 2\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  buyerEdit->Text=TQ->FieldByName("DESCRIPTION")->AsString;

  if(InvoiceTypeBox->ItemIndex==0)
  { TQ->Close();
    TQ->SQL->Clear();
    sql="select DESCRIPTION from CONTRACTORS where";
    sql+=" ID="+IntToStr(ConsigneeID);
    TQ->SQL->Add(sql);
    try
    {
      TQ->ExecQuery();
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка TQ->ExecQuery() - 2\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
    consigneeEdit->Text=TQ->FieldByName("DESCRIPTION")->AsString;
  }
  else consigneeEdit->Text="-";
  Label6->Caption="К счету № "+IntToStr(CountNumber)+" от "+CountDate.DateString();
}
//--------------------------------------------------------------------------
void __fastcall TInvoiceEditForm::CancelButtonClick(TObject *Sender)
{
  Close();
  ModalResult=mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TInvoiceEditForm::invoiceDateEditChange(TObject *Sender)
{
AnsiString sql;

  if(TDateTime(invoiceDateEdit->Text) < CountDate) invoiceDateEdit->Text=CountDate.DateString();
  if(TDateTime(invoiceDateEdit->Text) < SaleBookDM->BeginDate) invoiceDateEdit->Text=SaleBookDM->BeginDate.DateString();

  TQ->Close();
  TQ->SQL->Clear();
  if(CountDate > TDateTime("31.12.2008"))
  { sql="select max(INVOICE_NUMBER) as InvNum from INVOICES where";
    sql+=" ORG_ID="+IntToStr(OrgID);
    sql+=" and INVOICE_DATE='"+invoiceDateEdit->Date+"'";
  }
  else
  { unsigned short y,m,d;
    invoiceDateEdit->Date.DecodeDate(&y,&m,&d);
    TDateTime dt1=TDateTime(y,m,1),
              dt2=TDateTime(y,m,SaleBookDM->LastDay(y,m));
    sql="select max(INVOICE_NUMBER) as InvNum from INVOICES where";
    sql+=" ORG_ID="+IntToStr(OrgID);
    sql+=" and INVOICE_DATE>='"+dt1.DateString()+"'";
    sql+=" and INVOICE_DATE<='"+dt2.DateString()+"'";
  }
  TQ->SQL->Add(sql);
  try
  {
    TQ->ExecQuery();
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка TQ->ExecQuery()\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    InvoiceNumberEdit->Text="0";
    return;
  }
//  if(PrevID!=InvoiceDateEdit->Date) InvoiceNumberEdit->Text=IntToStr(TQ->FieldByName("InvNum")->AsInteger+1);
  InvoiceNumberEdit->Text=IntToStr(TQ->FieldByName("InvNum")->AsInteger+1);
  PrevID=invoiceDateEdit->Date;
}
//---------------------------------------------------------------------------
void __fastcall TInvoiceEditForm::buyerEditButtonClick(TObject *Sender)
{
/*  if(Application->FindComponent("ContractorsForm"))
  { ContractorsForm->LookUpRecord(BuyerID);
    if(ContractorsForm->ShowModal()==mrOk)
    { BuyerID=ContractorsForm->DataSet->FieldByName("ID")->AsInteger;
      buyerEdit->Text=ContractorsForm->DataSet->FieldByName("DESCRIPTION")->AsString;
      if(!ContractorsForm->DataSet->FieldByName("CONSIGNEE_ID")->IsNull)
      { AnsiString sql;
        TQ->Close();
        TQ->SQL->Clear();
        sql="select ID, DESCRIPTION from CONTRACTORS where";
        sql+=" ID="+IntToStr(ContractorsForm->DataSet->FieldByName("CONSIGNEE_ID")->AsInteger);
        TQ->SQL->Add(sql);
        try
        {
          TQ->ExecQuery();
        }
        catch (Exception &exc)
        { MessageDlg("Ошибка TQ->ExecQuery() - 2\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
          return;
        }
        if(TQ->RecordCount > 0)
        { ConsigneeID=TQ->FieldByName("ID")->AsInteger;
          consigneeEdit->Text=TQ->FieldByName("DESCRIPTION")->AsString;
        }
        else{ ConsigneeID=0; consigneeEdit->Text=""; }
      }
      else
      { ConsigneeID=ContractorsForm->DataSet->FieldByName("ID")->AsInteger;
        consigneeEdit->Text=ContractorsForm->DataSet->FieldByName("DESCRIPTION")->AsString;
      }
    }
  }
*/
}
//---------------------------------------------------------------------------
void __fastcall TInvoiceEditForm::consigneeEditButtonClick(TObject *Sender)
{
/*  if(Application->FindComponent("ContractorsForm"))
  { ContractorsForm->LookUpRecord(ConsigneeID);
    if(ContractorsForm->ShowModal()==mrOk)
    { ConsigneeID=ContractorsForm->DataSet->FieldByName("ID")->AsInteger;
      consigneeEdit->Text=ContractorsForm->DataSet->FieldByName("DESCRIPTION")->AsString;
    }
  }
*/  
}
//---------------------------------------------------------------------------
//Сохранение записи
void __fastcall TInvoiceEditForm::SaveButtonClick(TObject *Sender)
{
TDateTime InvoiceDate=invoiceDateEdit->Text;
unsigned short y,m,d;

  TempTransaction->StartTransaction();
  if(NewInvoiceFLG)
  { InvoiceDate.DecodeDate(&y,&m,&d);
    AddInvoiceProc->Close();
    if(CountDate > TDateTime("31.12.2008"))
    { AddInvoiceProc->StoredProcName="ADD_NEW_INVOICE";
      AddInvoiceProc->ParamByName("ORG_ID")->Value=OrgID;
    }
    else
    { AddInvoiceProc->StoredProcName="OLD_ADD_NEW_INVOICE";
      AddInvoiceProc->ParamByName("ORG_ID")->Value=OrgID;
      unsigned short y,m,d;
      invoiceDateEdit->Date.DecodeDate(&y,&m,&d);
      TDateTime dt1=TDateTime(y,m,1),
                dt2=TDateTime(y,m,SaleBookDM->LastDay(y,m));
      AddInvoiceProc->ParamByName("IDATE1")->Value=dt1;
      AddInvoiceProc->ParamByName("IDATE2")->Value=dt2;
    }
    AddInvoiceProc->ParamByName("INVOICE_DATE")->Value=invoiceDateEdit->Date;
    AddInvoiceProc->ParamByName("INVOICE_NUMBER")->Value=StrToInt(InvoiceNumberEdit->Text);
    AddInvoiceProc->ParamByName("COUNT_DATE")->Value=CountDate;
    AddInvoiceProc->ParamByName("COUNT_NUMBER")->Value=CountNumber;
    AddInvoiceProc->ParamByName("BUYER_ID")->Value=BuyerID;
    if(ConsigneeID > 0) AddInvoiceProc->ParamByName("CONSIGNEE_ID")->Value=ConsigneeID;
    AddInvoiceProc->ParamByName("INVOICE_TYPE")->Value=InvoiceTypeBox->ItemIndex;
    AddInvoiceProc->ParamByName("ADVANCE_FLG")->Value=int(advanceCheckbox->Checked);
    AddInvoiceProc->ParamByName("REVISION_FLG")->Value=int(revisionCheckbox->Checked);
    try
    {
      AddInvoiceProc->Prepare();
      AddInvoiceProc->ExecProc();
    }
    catch(const Exception &exc)
    {
      MessageDlg("Ошибка записи в журнал счет-фактур\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      TempTransaction->Rollback();
      AddInvoiceProc->Close();
      return;
    }
    if(AddInvoiceProc->ParamByName("RESULT_FLG")->AsInteger==0)
    { TempTransaction->Rollback();
      AddInvoiceProc->Close();
      MessageDlg("Счет-фактура с номером "+InvoiceNumberEdit->Text+" уже есть в базе",mtError,TMsgDlgButtons() << mbOK,0);
      invoiceDateEdit->OnChange(this);
    }
    else
    { AnsiString sql;
      if(invoiceDateEdit->Date!=PrevID || StrToInt(InvoiceNumberEdit->Text)!=oldINumber)
      { //Корректируем данные в таблице RECKONINGS_TABLE
        UpDateQ->Close();
        UpDateQ->SQL->Clear();
        sql="update RECKONINGS_TABLE set";
        sql+=" INVOICE_DATE='"+invoiceDateEdit->Date.DateString()+"'";
        sql+=",INVOICE_NUMBER="+InvoiceNumberEdit->Text;
        sql+=" where ORG_ID="+IntToStr(OrgID)+" and INVOICE_DATE='"+PrevID.DateString()+"'";
        sql+=" and INVOICE_NUMBER="+IntToStr(oldINumber);
        UpDateQ->SQL->Add(sql);
        try
        {
          UpDateQ->ExecQuery();
        }
        catch (Exception &exc)
        { MessageDlg("Ошибка записи изменений\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
          UpDateQ->Close();
          TempTransaction->Rollback();
          return;
        }
      }
      AddInvoiceProc->Close();
      //Фиксирем действие в журнале событий ACTIONS_JOURNAL
      AnsiString str="Добавлена ";
      str+="счет-фактура №"+InvoiceNumberEdit->Text+" от "+invoiceDateEdit->Text;
      str+=" "+Label6->Caption;
      if(SaleBookDM->AddRecordToActionsJournal(AddRecordToInvoicesTable,str,TempTransaction)==true)
        TempTransaction->Commit();
      else TempTransaction->Rollback();
      Close();
      ModalResult=mrOk;
    }
  }
  else
  { AnsiString sql;
    UpDateQ->Close();
    UpDateQ->SQL->Clear();
    sql="update INVOICES set";
    sql+=" INVOICE_DATE='"+invoiceDateEdit->Date.DateString()+"'";
    sql+=",INVOICE_NUMBER="+InvoiceNumberEdit->Text;
    sql+=",BUYER_ID="+IntToStr(BuyerID);
    if(ConsigneeID > 0) sql+=",CONSIGNEE_ID="+IntToStr(ConsigneeID);
    else sql+=",CONSIGNEE_ID=NULL";
    sql+=",INVOICE_TYPE="+IntToStr(InvoiceTypeBox->ItemIndex);
    sql+=",ADVANCE_FLG="+IntToStr(int(advanceCheckbox->Checked));
    sql+=",REVISION_FLG="+IntToStr(int(revisionCheckbox->Checked));
    sql+=" where ORG_ID="+IntToStr(OrgID)+" and INVOICE_DATE='"+InvDate.DateString()+"'";
    sql+=" and INVOICE_NUMBER="+IntToStr(InvNum);
    UpDateQ->SQL->Add(sql);
    try
    {
      UpDateQ->ExecQuery();
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка записи изменений\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      UpDateQ->Close();
      TempTransaction->Rollback();
      return;
    }

    if(invoiceDateEdit->Date!=InvDate || StrToInt(InvoiceNumberEdit->Text)!=InvNum)
    { //Корректируем записи в таблице RECKONINGS_TABLE
      UpDateQ->Close();
      UpDateQ->SQL->Clear();
      sql="update RECKONINGS_TABLE set";
      sql+=" INVOICE_DATE='"+invoiceDateEdit->Date.DateString()+"'";
      sql+=",INVOICE_NUMBER="+InvoiceNumberEdit->Text;
      sql+=" where ORG_ID="+IntToStr(OrgID)+" and INVOICE_DATE='"+InvDate.DateString()+"'";
      sql+=" and INVOICE_NUMBER="+IntToStr(InvNum);
      UpDateQ->SQL->Add(sql);
      try
      {
        UpDateQ->ExecQuery();
      }
      catch (Exception &exc)
      { MessageDlg("Ошибка записи изменений\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
        UpDateQ->Close();
        TempTransaction->Rollback();
        return;
      }
    }

    //Фиксирем действие в журнале событий ACTIONS_JOURNAL
    AnsiString str="Отредактирована ";
    str+="счет-фактура №"+InvoiceNumberEdit->Text+" от "+invoiceDateEdit->Text;
    str+=" "+Label6->Caption;
    if(SaleBookDM->AddRecordToActionsJournal(EditRecordFromInvoicesTable,str,TempTransaction)==true)
      TempTransaction->Commit();
    else TempTransaction->Rollback();
    UpDateQ->Close();
    Close();
    ModalResult=mrOk;
  }
}
//---------------------------------------------------------------------------
//Выбор номера счет-фактуры
void __fastcall TInvoiceEditForm::SelectNumberButtonClick(TObject *Sender)
{
TSelectNumberForm *SNF=NULL;
unsigned short y,m,d;

  TDateTime(invoiceDateEdit->Date).DecodeDate(&y,&m,&d);
  //Создаем форму для выбота номера вставляемого счета
  try
  {
    SNF=new TSelectNumberForm(this,SaleBookDM->OrganizationID,invoiceDateEdit->Date,2);
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка создания формы для выбора номера счета\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(SNF->ShowModal()==mrOk)
  {
    InvoiceNumberEdit->Text=IntToStr(SNF->getNewNumber());
  }
  delete SNF;
}
//---------------------------------------------------------------------------
//Очистка грузополучателя
void __fastcall TInvoiceEditForm::SpeedButton2Click(TObject *Sender)
{
  ConsigneeID=0;
  consigneeEdit->Text="";
}
//---------------------------------------------------------------------------
//Присединение платежно-расчетного документа
void __fastcall TInvoiceEditForm::SpeedButton1Click(TObject *Sender)
{
TInvoiceReckoningsForm *IRF;
int i_number;
unsigned short y,m,d;
int contsID[2];

  if(InvoiceNumberEdit->Text.IsEmpty())
  { MessageDlg("Не указан номер счет-фактуры",mtWarning,TMsgDlgButtons() << mbOK,0);
    return;
  }
  i_number=StrToInt(InvoiceNumberEdit->Text);
  if(int(invoiceDateEdit->Date) == 0)
  { MessageDlg("Не указана дата счет-фактуры",mtWarning,TMsgDlgButtons() << mbOK,0);
    return;
  }
  invoiceDateEdit->Date.DecodeDate(&y,&m,&d);
  if(buyerEdit->Text.IsEmpty())
  { MessageDlg("Не указан покупатель",mtWarning,TMsgDlgButtons() << mbOK,0);
    return;
  }
  contsID[0]=BuyerID;
  contsID[1]=ConsigneeID;
  unsigned short ay,am,ad;
  CountDate.DecodeDate(&ay,&am,&ad);
  try
  {
    IRF=new TInvoiceReckoningsForm(this,BuyerID, contsID, OrgID,invoiceDateEdit->Date,i_number,CountDate,CountNumber);
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка создания формы InvoiceReckoningsForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  IRF->ShowModal();
  delete IRF;
  PADocs->Clear();
  PADocs->Lines->Add(SaleBookDM->getPADocsString(OrgID,invoiceDateEdit->Date,i_number));
}
//---------------------------------------------------------------------------
//Ускоренный ввод документа
void __fastcall TInvoiceEditForm::SpeedButton3Click(TObject *Sender)
{
AnsiString sql;
TSpeedAPDocForm *SDF=NULL;
unsigned short y,m,d;
int rc_id=0, ap_id=0;
int i_number;
int contsID[2];

  if(InvoiceNumberEdit->Text.IsEmpty())
  { MessageDlg("Не указан номер счет-фактуры",mtWarning,TMsgDlgButtons() << mbOK,0);
    return;
  }
  i_number=StrToInt(InvoiceNumberEdit->Text);
  if(int(invoiceDateEdit->Date) == 0)
  { MessageDlg("Не указана дата счет-фактуры",mtWarning,TMsgDlgButtons() << mbOK,0);
    return;
  }
  invoiceDateEdit->Date.DecodeDate(&y,&m,&d);
  if(buyerEdit->Text.IsEmpty())
  { MessageDlg("Не указан покупатель",mtWarning,TMsgDlgButtons() << mbOK,0);
    return;
  }
  contsID[0]=BuyerID;
  contsID[1]=ConsigneeID;
  i_number=StrToInt(InvoiceNumberEdit->Text);

  //Определяем общую сумму платежей по счету
  double itotal=0.0;
  TQ->Close();
  TQ->SQL->Clear();
  sql="select COUNT_TOTAL from ACCOUNTS";
  sql+=" where org_id="+IntToStr(OrgID);
  sql+=" and count_date='"+CountDate.DateString()+"'";
  sql+=" and count_number="+IntToStr(CountNumber);
  TQ->SQL->Add(sql);
  try
  {
    TQ->ExecQuery();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(TQ->RecordCount > 0) itotal=TQ->FieldByName("COUNT_TOTAL")->AsFloat;

  TQ->Close();
  TQ->SQL->Clear();
  sql="select distinct a.AP_ID, r.RC_ID";
  sql+=" from RECKONINGS_TABLE r";
  sql+=" left outer join ADVANCE_PAYMENTS_TABLE a on a.AP_ID=r.AP_ID";
  sql+=" where r.ORG_ID="+IntToStr(OrgID);
  sql+=" and r.INVOICE_DATE='"+invoiceDateEdit->Date+"'";
  sql+=" and r.INVOICE_NUMBER="+IntToStr(i_number);
  TQ->SQL->Add(sql);
  try
  {
    TQ->ExecQuery();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(TQ->RecordCount > 0)
  { rc_id=TQ->FieldByName("RC_ID")->AsInteger;
    ap_id=TQ->FieldByName("AP_ID")->AsInteger;
  }
  TQ->Close();
  try
  {
    SDF=new TSpeedAPDocForm(this,rc_id,ap_id,BuyerID,contsID,OrgID,invoiceDateEdit->Date,i_number,itotal);
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка создания формы SpeedAPDoc\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  SDF->ShowModal();
  delete SDF;
  PADocs->Clear();
  PADocs->Lines->Add(SaleBookDM->getPADocsString(OrgID,invoiceDateEdit->Date,i_number));
}
//---------------------------------------------------------------------------
//При изменении типа документа
void __fastcall TInvoiceEditForm::InvoiceTypeBoxChange(TObject *Sender)
{
  if(InvoiceTypeBox->ItemIndex==0)
  { TQ->Close();
    TQ->SQL->Clear();
    AnsiString sql="select t1.CONSIGNEE_ID,t2.DESCRIPTION as CONSIGNEE_NAME from CONTRACTORS t1";
    sql+=" left outer join CONTRACTORS t2 on t2.ID=t1.CONSIGNEE_ID";
    sql+=" where t1.ID="+IntToStr(BuyerID);
    TQ->SQL->Add(sql);
    try
    {
      TQ->ExecQuery();
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
    if(TQ->RecordCount > 0)
    { if(TQ->FieldByName("CONSIGNEE_ID")->IsNull || TQ->FieldByName("CONSIGNEE_ID")->AsInteger==0)
      { ConsigneeID=BuyerID;
        consigneeEdit->Text=buyerEdit->Text;
      }
      else
      { ConsigneeID=TQ->FieldByName("CONSIGNEE_ID")->AsInteger;
        consigneeEdit->Text=TQ->FieldByName("CONSIGNEE_NAME")->AsString;
      }
    }
    else
    { ConsigneeID=BuyerID;
      consigneeEdit->Text=buyerEdit->Text;
    }
  }
  else
  { ConsigneeID=0;
    consigneeEdit->Text="-";
  }
}
//---------------------------------------------------------------------------

