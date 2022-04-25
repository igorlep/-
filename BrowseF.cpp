//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BrowseF.h"
#include "DataModule.h"
#include "Main.h"
#include "SelectPeriod.h"
#include "SelectFilter.h"
#include "utils.h"
#include "AccountEdit.h"
#include "EI.h"
#include "AccauntsJournal.h"
#include "SelectPeriodBF.h"
#include "DifferentFunctions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "RXSpin"
#pragma link "SmrtPanel"
#pragma link "FIBDatabase"
#pragma link "FIBDataSet"
#pragma link "FIBQuery"
#pragma link "pFIBDatabase"
#pragma link "pFIBDataSet"
#pragma link "pFIBQuery"
#pragma link "Placemnt"
#pragma link "JvComponent"
#pragma link "JvExControls"
#pragma link "JvNavigationPane"
#pragma resource "*.dfm"
TBrowseForm *BrowseForm;
//TAccountEditForm *AccountEditForm;
//---------------------------------------------------------------------------
__fastcall TBrowseForm::TBrowseForm(TComponent* Owner)
        : TForm(Owner)
{
  iniFileName=MainForm->getIniFileName();
  FormStorage1->IniFileName=iniFileName;
  FormStorage1->IniSection="BrowserForm";
  Year->Height=21;
  if(MainForm->getFontDPI()>96)
  { DBGrid->Font->Size=10;
    DBGrid->FooterFont->Size=10;
    DBGrid->TitleFont->Size=10;
  }

  loadProperties();
  order=None;
  filter=None;
  date1=1;
  date2=31;
  Ops=0;
  Dost=0;
  Post="";
  Opl=1;
  ByNH=0;
}
//---------------------------------------------------------------------------

void __fastcall TBrowseForm::loadProperties(void)
{
TIniFile *ini=NULL;
TDateTime dt=Date();
int aGridFontSize;
TDateTime lockDate;
unsigned short yl,ml,dl;


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

  try
  {
    ini=new TIniFile(iniFileName);
    Year->Value=ini->ReadInteger("BrowserForm","Year",y);
    Month->ItemIndex=ini->ReadInteger("BrowserForm","Month",m-1);
    aGridFontSize=ini->ReadInteger("BrowserForm","aGridFontSize",DBGrid->Font->Size);
    delete ini;
  }
  catch(...)
  { if(ini!=NULL) delete ini;
    Year->Value=y;
    Month->ItemIndex=m-1;
    aGridFontSize=DBGrid->Font->Size;
  }
  DBGrid->Font->Size=aGridFontSize;
  DBGrid->FooterFont->Size=aGridFontSize;
  DBGrid->TitleFont->Size=aGridFontSize;
}

void __fastcall TBrowseForm::setMainHeader(void)
{
AnsiString s,s1;

  s="";
  s1="";

  if (flag==2 || flag==0)
  {
  s+=" ТЕКУЩАЯ Выплатная база ";
  }
  else
  {
  if ( ByNH == 0 )
  {
  MainHeader->Font->Color=clBlack;
  if(date1 == date2) s+=" ВСЕ НЕОПЛАЧЕННЫЕ кроме нет дома и до востребования платежные поручения  за число - "+IntToStr(date1);
  else s+=" ВСЕ НЕОПЛАЧЕННЫЕ платежные поручения кроме нет дома и до востребования с "+IntToStr(date1)+" по "+IntToStr(date2);
  }else
  {
  MainHeader->Font->Color=clRed;
  if(date1 == date2) s+=" ТОЛЬКО !!! НЕОПЛАЧЕННЫЕ со статусом нет дома и до востребования платежные поручения  за число - "+IntToStr(date1);
  else s+=" ТОЛЬКО !!! НЕОПЛАЧЕННЫЕ со статусом нет дома и до востребования платежные поручения с "+IntToStr(date1)+" по "+IntToStr(date2);
  }

  if(filter==ByPost) if (Post.Trim() != "") s+= " по почтальону -> " + Post.Trim();
  if(filter==ByOps)  if (Ops>0) s+= " по ОПС -> " + IntToStr(Ops);
  if(filter==ByDost) if (Dost>0) s+= " по ДО -> " + IntToStr(Dost);
  if(filter==ByPost1){
  if (Post.Trim() != "") s+= " по почтальону -> " + Post.Trim();
  if (Ops>0) s+= " по ОПС -> " + IntToStr(Ops);
  }
  if(filter==ByPost2){
  if (Post.Trim() != "") s+= " по почтальону -> " + Post.Trim();
  if (Dost>0) s+= " по ДО -> " + IntToStr(Dost);
  }
  if(filter==ByPost3){
  if (Post.Trim() != "") s+= " по почтальону -> " + Post.Trim();
  if (Dost>0 && Ops>0) s+= " по ОПС -> " + IntToStr(Ops) + " и ДО -> " + IntToStr(Dost);
  }
  if(filter==ByPost4){
  if (Ops>0) s+= " по ОПС -> " + IntToStr(Ops);
  if (Dost>0) s+= " по ДО -> " + IntToStr(Dost);
  }

  s+= " МЕСЯЦ " + namemonthOfDate(m);
  }
  MainHeader->Caption=s;

}


void __fastcall TBrowseForm::LoadDataSet(void)
{
AnsiString sql,sql1,s1,sql2;
indexofops=0;
TpFIBDataSet *DSZ;
TpFIBDataSet *DSZ1;
TDateTime dt;
int codm;
int flun;

if(Application->FindComponent("AccountsJournalForm"))
{
DSZ=((TpFIBDataSet*)(AccountsJournalForm->AccountsGrid->DataSource->DataSet));
if(AccountsJournalForm->AEF!=NULL)
{
if(AccountsJournalForm->AEF->NewFLG)
{
DSZ1=AccountsJournalForm->AEF->AccountsTempDS;
  try
  {
  codm=DSZ1->FieldByName("CUSTOMER_ID")->AsInteger;
  }
  catch(const Exception &exc)
  {
  codm=DSZ->FieldByName("CUSTOMER_ID")->AsInteger;
  }
dt=DSZ1->FieldByName("COUNT_DATE")->AsDateTime;
}else
{
dt=DSZ->FieldByName("COUNT_DATE")->AsDateTime;
codm=DSZ->FieldByName("CUSTOMER_ID")->AsInteger;
}
}
else
{
dt=DSZ->FieldByName("COUNT_DATE")->AsDateTime;
codm=DSZ->FieldByName("CUSTOMER_ID")->AsInteger;
}
}


  DBGrid->Visible=false;
  if(A_DS->Active==true) A_DS->Close();
  A_DS->SQLs->SelectSQL->Clear();
  sql="";

  if (flag==0)
  {
  flun=0;
  sql="select distinct d.* ";
  sql+=" from NDOST d  ";
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql+=" where d.METKA1 IN ("+SaleBookDM->UserIndex + ")";
  }

  if (flag==1)
  {
    //Проверяем не работает с заданием текущий пользователь
  SaleBookDM->TempQuery->Close();
  SaleBookDM->TempQuery->SQL->Clear();
  sql2="select CUSTOMER_ID from ACCOUNTS_TEMP where ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
  sql2+="  and USER_ID = "+IntToStr(SaleBookDM->UserID);

  SaleBookDM->TempQuery->SQL->Add(sql2);
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
    MessageDlg("Не найдена нужная запись (CUSTOMER_ID from ACCOUNTS_TEMP)",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(SaleBookDM->TempQuery->FieldByName("CUSTOMER_ID")->AsInteger==0)
  {
    MessageDlg("Неверно выбрано почтальон или касса !!! ",mtWarning,TMsgDlgButtons() << mbOK,0);
    return;
  }

  if(ByNH==1)
  {
  flun=1;
  sql="select distinct d.* from NDOST d where d.LCHET in ( select LCHET from sgb where sgb.count_date<='" +dt.DateString()+"' and sgb.prich='н/д' and sgb.kassa=0)";
  sql+=" and d.metka1 IN ("+SaleBookDM->UserIndex + ")";
  sql+=" union select distinct d.* from NDOST d where d.LCHET in ( select LCHET from dov )";
  sql+=" and d.metka1 IN ("+SaleBookDM->UserIndex + ")";
  sql+=" and d.lchet not in(select lchet from sgb)";
  }
  else
  {
  TempQuery->Close();
  TempQuery->SQL->Clear();
  sql1="select INDEXOPS as INDOPS from NOMENCLATURE n where CODP="+IntToStr(SaleBookDM->TempQuery->FieldByName("CUSTOMER_ID")->AsInteger);
  TempQuery->SQL->Add(sql1);
  try
  {
  TempQuery->ExecQuery();
  }
  catch(const Exception &exc)
  {
  MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  return;
  }

  if (TempQuery->FieldByName("INDOPS")->AsInteger > 0)
  {
  flun=0;
  sql+=" select distinct d.* from NDOST d where d.LCHET not in ( select LCHET from sgb )";
  sql+=" and d.metka1 IN ("+SaleBookDM->UserIndex + ")";
  sql+=" and d.lchet not in(select lchet from dov)";
  post=1;
  }
  else
  {
  flun=1;
  sql="select distinct d.* from NDOST d where d.LCHET in ( select LCHET from sgb where sgb.count_date<='" +dt.DateString()+"' and sgb.prich='н/д' and sgb.kassa=0)";
  sql+=" and d.metka1 IN ("+SaleBookDM->UserIndex + ")";
  sql+=" union select distinct d.* from NDOST d where d.LCHET not in ( select LCHET from sgb )";
  sql+=" and d.metka1 IN ("+SaleBookDM->UserIndex + ")";
  post=0;
  }
  }
  sql+=" and d.lchet not in(select lchet from sgbt)";

  }

  if (flag==2)
  {
  flun=0;
  sql="select distinct d.* ";
  sql+=" from NDOST d  where ";
  sql+=" d.lchet not in(select lchet from dov";
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql+=" where dov.METKA1 IN ("+SaleBookDM->UserIndex + "))"; else sql+=")";
  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql+=" and d.METKA1 IN ("+SaleBookDM->UserIndex + ")";
  }

  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql+=" and "; else sql+=" where ";
  sql+=" d.D_VIPL>="+IntToStr(date1);
  sql+=" and d.D_VIPL<="+IntToStr(date2);

  if(filter!=None)
  {
    sql+=" and ";
  }

  if(filter==ByPost) sql+=" CHEL="+IntToStr(KPost);
  if(filter==ByOps) sql+="  METKA1="+IntToStr(Ops);
  if(filter==ByDost) sql+=" DOST="+IntToStr(Dost);
  if(filter==ByOpl)
  {
   if(flag==0)
   {
    if (Opl==1) sql+=" d.lchet in(select lchet from sgb where sgb.prich='' and sgb.kassa=0 )";
    if (Opl==2) sql+=" d.lchet not in(select lchet from sgb where sgb.prich='' and sgb.kassa=0 )";
   }
  }


  if(filter==ByPost1){
  sql+=" CHEL="+IntToStr(KPost);
  sql+=" and METKA1="+IntToStr(Ops);
  }

  if(filter==ByPost2){
  sql+=" CHEL="+IntToStr(KPost);
  sql+=" and DOST="+IntToStr(Dost);
  }

  if(filter==ByPost3){
  sql+=" CHEL="+IntToStr(KPost);
  sql+=" and METKA1="+IntToStr(Ops);
  sql+=" and DOST="+IntToStr(Dost);
  }

  if(filter==ByPost4){
  sql+=" METKA1="+IntToStr(Ops);
  sql+=" and DOST="+IntToStr(Dost);
  }

   if(flun==1)
   {
   sql+=" order by 8, 9, 10 ";
   }else
   {
   sql+=" order by FAMILY, NAME, FATHER DESC";
   }



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
  A_DS->First();
  kolzap=A_DS->RecordCount;

  if(kolzap > 0){
  if(filter==None){
   s1+=" Всего поручений "+IntToStr(kolzap);
  }else
  {
  if(filter==ByOpl){
   if (Opl==1) s1+=" Всего оплаченных поручений "+IntToStr(kolzap);
   if (Opl==2) s1+=" Всего неоплаченных поручений "+IntToStr(kolzap);
   }else
   {
   s1+=" Всего отобранных по критерию поручений "+IntToStr(kolzap);
   }
  }
  }
  else
  {
  s1+="Записей нет!!!";
  }

  MainFooter->Caption=s1;


  DBGrid->Visible=true;
  SetButtons();
  try
  {
    DBGrid->SetFocus();
  }
  catch(...){};
}

void __fastcall TBrowseForm::SetButtons(void)
{
TpFIBDataSet *DSZ;

  if(A_DS->RecordCount > 0)
  {
    LastButton->Enabled=true;
    SelectPer->Enabled=true;
    SelectButton->Enabled=true;
    if(filter==None) UnSelectButton->Enabled=false;
    else UnSelectButton->Enabled=true;
    NextButton->Enabled=true;
    FirstButton->Enabled=true;
    PriorButton->Enabled=true;
  }else
  {
    SelectButton->Enabled=true;
    if(filter==None) UnSelectButton->Enabled=false;
    else UnSelectButton->Enabled=true;
    SelectPer->Enabled=true;
    LastButton->Enabled=false;
    NextButton->Enabled=false;
    FirstButton->Enabled=false;
    PriorButton->Enabled=false;
  }

  if(A_DS->Eof)
  { LastButton->Enabled=false;
    NextButton->Enabled=false;
  }
  else
  {
    LastButton->Enabled=true;
    NextButton->Enabled=true;
  }
  if(A_DS->Bof)
  { FirstButton->Enabled=false;
    PriorButton->Enabled=false;
  }
  else
  {
    FirstButton->Enabled=true;
    PriorButton->Enabled=true;
  }
if(flag==0)
{
CopyButton->Enabled=false;
EditButton->Enabled=true;
SaveButton->Enabled=true;
CancelButton->Enabled=true;
DBGrid->Options.Clear();
DBGrid->Options << dgTitles << dgIndicator << dgColumnResize << dgColLines << dgTabs;
}else
{
CopyButton->Enabled=true;
EditButton->Enabled=false;
SaveButton->Enabled=false;
CancelButton->Enabled=false;
DBGrid->Options.Clear();
DBGrid->Options << dgTitles << dgIndicator << dgColumnResize << dgColLines << dgTabs << dgRowSelect << dgMultiSelect;
}
}
//---------------------------------------------------------------------------
void __fastcall TBrowseForm::saveProperties(void)
{
TIniFile *ini=NULL;

  try
  { ini=new TIniFile(iniFileName);
    ini->WriteInteger("BrowserForm","Year",Year->Value);
    ini->WriteInteger("BrowserForm","Month",Month->ItemIndex);
    ini->WriteInteger("BrowserForm","aGridFontSize",DBGrid->Font->Size);
    delete ini;
  }
  catch(...)
  {
    if(ini!=NULL) delete ini;
  }
}

void __fastcall TBrowseForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  saveProperties();
  Action=caFree;
}
//---------------------------------------------------------------------------

void __fastcall TBrowseForm::FormShow(TObject *Sender)
{
  setMainHeader();
  LoadDataSet();
  if (flag==0)
  {
  Edit2->Visible=false;
  Label2->Visible=false;
  CheckBox1->Visible=false;
  }else
  {
  Edit2->Visible=true;
  CheckBox1->Visible=true;
  Label2->Visible=true;
  }
Edit1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TBrowseForm::ExitButtonClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------

void __fastcall TBrowseForm::increaseButtonClick(TObject *Sender)
{
int fontDPI;
TDBGridEh *grid=NULL;

  if(DBGrid->Focused()==true) grid=DBGrid;
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

void __fastcall TBrowseForm::reduceButtonClick(TObject *Sender)
{
int fontDPI;
TDBGridEh *grid=NULL;

  if(DBGrid->Focused()==true) grid=DBGrid;
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

void __fastcall TBrowseForm::FirstButtonClick(TObject *Sender)
{
  A_DS->First();
        
}
//---------------------------------------------------------------------------

void __fastcall TBrowseForm::PriorButtonClick(TObject *Sender)
{
  A_DS->Prior();
}
//---------------------------------------------------------------------------

void __fastcall TBrowseForm::NextButtonClick(TObject *Sender)
{
  A_DS->Next();

}
//---------------------------------------------------------------------------

void __fastcall TBrowseForm::LastButtonClick(TObject *Sender)
{
  A_DS->Last();
}
//---------------------------------------------------------------------------

void __fastcall TBrowseForm::searchTimerTimer(TObject *Sender)
{
//int num=1;
//Variant lv[1];
TLocateOptions opt;
opt<<loPartialKey<<loCaseInsensitive;
AnsiString d=0;
int test=0;
int rn=0;

  searchTimer->Enabled=false;
  if(Edit1->Text.IsEmpty()) return;
  if(Edit1->Text.Length() == 6 && IsNum(Edit1->Text.Trim())){
  d=Edit1->Text.Trim();
  A_DS->Locate("LCHET1",d,opt);
  rn=A_DS->RecNo;
  A_DS->RecNo=rn;
  DBGrid->SelectedRows->CurrentRowSelected=true;
  Edit2->Text=IntToStr(BrowseForm->DBGrid->SelectedRows->Count);
  Edit1->Text="";
  Edit1->SetFocus();
  if (rn>1) ProvStatus(); else if(flag==0) MessageDlg("Поручение не найдено в базе!!!",mtWarning,TMsgDlgButtons() << mbOK,0); else MessageDlg("Поручение возможно находиться в заданий !!!",mtWarning,TMsgDlgButtons() << mbOK,0); 
  }else
  {
  d=Edit1->Text.Trim();
  A_DS->Locate("FAMILY",d,opt);
  rn=A_DS->RecNo;
  A_DS->RecNo=rn;
  DBGrid->SelectedRows->CurrentRowSelected=true;
  Edit2->Text=IntToStr(BrowseForm->DBGrid->SelectedRows->Count);
  Edit1->Text="";
  Edit1->SetFocus();
  if (rn>1) ProvStatus(); else if(flag==0) MessageDlg("Поручение не найдено в базе!!!",mtWarning,TMsgDlgButtons() << mbOK,0); else MessageDlg("Поручение возможно находиться в заданий !!!",mtWarning,TMsgDlgButtons() << mbOK,0);
  }
}
//---------------------------------------------------------------------------



void __fastcall TBrowseForm::AccountsSDataChange(TObject *Sender,
      TField *Field)
{
  if(DBGrid->Visible==true && Showing) SetButtons();

}
//---------------------------------------------------------------------------

void __fastcall TBrowseForm::Edit1Change(TObject *Sender)
{
  if(searchTimer->Enabled==true) searchTimer->Enabled=false;
  searchTimer->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TBrowseForm::Edit1KeyPress(TObject *Sender, char &Key)
{
  if(Key==VK_RETURN || Key==VK_DOWN || Key==VK_UP)
  { Key=0;
    DBGrid->SetFocus();
  }
  else if(Key == VK_ESCAPE){ Key=0; Edit1->Text=""; }
}
//---------------------------------------------------------------------------

void __fastcall TBrowseForm::FormDestroy(TObject *Sender)
{
  saveProperties();

}
//---------------------------------------------------------------------------

void __fastcall TBrowseForm::UnSelectButtonClick(TObject *Sender)
{
  filter=None;
  Ops=0;
  Dost=0;
  Post="";
  Opl=1;
//  ByNH=0;
  setMainHeader();
  LoadDataSet();
}
//---------------------------------------------------------------------------


void __fastcall TBrowseForm::SelectPerClick(TObject *Sender)
{
TSelectPeriodBrowseForm *SPF;

  try
  {
    SPF=new TSelectPeriodBrowseForm(this,date1,date2);
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка создания формы SelectPeriodBrowseForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(SPF->ShowModal()==mrOk)
  {
    date1=SPF->getDate1();
    date2=SPF->getDate2();
    Ops=0;
    Dost=0;
    Opl=1;
    Post="";
    setMainHeader();
    filter=None;
    LoadDataSet();
  }
  if(SPF!=NULL) delete SPF;
}
//---------------------------------------------------------------------------


void __fastcall TBrowseForm::SelectButtonClick(TObject *Sender)
{
TSelectFilterForm *SFF=NULL;

  try
  {
    SFF=new TSelectFilterForm(this);
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка создания формы SelectFilterForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(SFF->ShowModal()==mrOk)
  {
    Dost=SFF->getDost();
    Ops=SFF->getOps();
    Post=SFF->getPost();
    KPost=SFF->getKpost();
    Opl=SFF->getOpl();
    setMainHeader();
    LoadDataSet();
  }
  if(SFF!=NULL) delete SFF;

}
//---------------------------------------------------------------------------

void __fastcall TBrowseForm::CopyButtonClick(TObject *Sender)
{
// копирование отобранных записей в задание
TDataSet *Count=BrowseForm->DBGrid->DataSource->DataSet;

TpFIBDataSet *DSZ;
TpFIBDataSet *DSZ1;
TpFIBDataSet *DS;
TDateTime dt;
int codm;
AnsiString sql;
unsigned short dv,yv,mv;
int teklchet;


TDateTime dtt=Date();
TDateTime lockDate;
unsigned short yl,ml,dl;


  lockDate=SaleBookDM->GetConstValue(SaleBookDM->OrganizationID,"LOCK_EDIT_DATE");
  lockDate.DecodeDate(&yl,&ml,&dl);
  dtt.DecodeDate(&y,&m,&d);
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


if(Application->FindComponent("AccountsJournalForm"))
{
DSZ=((TpFIBDataSet*)(AccountsJournalForm->AccountsGrid->DataSource->DataSet));
if(AccountsJournalForm->AEF!=NULL)
{
if(AccountsJournalForm->AEF->NewFLG)
{
//dt=TDateTime(AccountsJournalForm->AEF->DateEdit->Text);
DSZ1=AccountsJournalForm->AEF->AccountsTempDS;
  try
  {
  codm=DSZ1->FieldByName("CUSTOMER_ID")->AsInteger;
  }
  catch(const Exception &exc)
  {
//  MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  codm=DSZ->FieldByName("CUSTOMER_ID")->AsInteger;
  }
dt=DSZ1->FieldByName("COUNT_DATE")->AsDateTime;
}else
{
dt=DSZ->FieldByName("COUNT_DATE")->AsDateTime;
codm=DSZ->FieldByName("CUSTOMER_ID")->AsInteger;
}
}
else
{
dt=DSZ->FieldByName("COUNT_DATE")->AsDateTime;
codm=DSZ->FieldByName("CUSTOMER_ID")->AsInteger;
}

dt.DecodeDate(&yv,&mv,&dv);

if (BrowseForm->DBGrid->SelectedRows->Count==0)
{
    MessageDlg("Нет выбранных поручений !!! ",mtWarning,TMsgDlgButtons() << mbOK,0);
    return;
}
  CopyButton->Enabled=false;
  teklchet=0;
  for(int r=0; r<BrowseForm->DBGrid->SelectedRows->Count; r++)
  {
    Count->GotoBookmark((void *)BrowseForm->DBGrid->SelectedRows->Items[r].c_str());

      if (teklchet==Count->FieldByName("LCHET")->AsInteger) continue;

      DS=SaleBookDM->NDOST;
      DS->Close();
      DS->SQLs->SelectSQL->Clear();
      sql="select * from NDOST where LCHET = " + IntToStr(Count->FieldByName("LCHET")->AsInteger);

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
      WriteTransaction->StartTransaction();
      WQ->Close();
      WQ->SQL->Clear();
      sql="insert into SGBT(USER_ID,LCHET1,SUMMA,WORD,METKA,NEOPL,PNN,LCHET,FAMILY,NAME,\
      FATHER,KOD,C,DOC,SERIA,NOMER,DOST,D_VIPL,ULIC,ADRES,CHEL,METKA1,VNOM,PRICH,IST,BSUMMA,";
      sql+="BWORD,FAKT_CHEL,FAKT_DAT,NSP,KEM_VID,DATA_VID,KODPEN,FOND) values(";
      if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql+=IntToStr(SaleBookDM->UserID)+",'"; else sql+=IntToStr(DSZ->FieldByName("USER_ID")->AsInteger)+",'";
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
      sql+=IntToStr(codm)+",";
      sql+=IntToStr(dv)+",";
      sql+=IntToStr(DS->FieldByName("NSP")->AsInteger)+",'";
      sql+=DS->FieldByName("KEM_VID")->AsString.Trim()+"','";
      sql+=DS->FieldByName("DATA_VID")->AsDateTime.DateString()+"',";
      sql+=IntToStr(DS->FieldByName("KODPEN")->AsInteger)+",";
      sql+=IntToStr(DS->FieldByName("FOND")->AsInteger)+")";
      WQ->SQL->Add(sql);
      try
      {
      WQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      WriteTransaction->Rollback();
      return;
      }
      WriteTransaction->Commit();

      DS->Next();
      id++;
      }
      DS->Close();
      teklchet=Count->FieldByName("LCHET")->AsInteger;
      }
  }


if(Application->FindComponent("ActsListForm"))
{

  for(int r=0; r<BrowseForm->DBGrid->SelectedRows->Count; r++)
  {
    Count->GotoBookmark((void *)BrowseForm->DBGrid->SelectedRows->Items[r].c_str());

      DS=SaleBookDM->NDOST;
      DS->Close();
      DS->SQLs->SelectSQL->Clear();
      sql="select * from NDOST where LCHET = " + IntToStr(Count->FieldByName("LCHET")->AsInteger);
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
      WriteTransaction->StartTransaction();
      WQ->Close();
      WQ->SQL->Clear();
      sql="insert into DOV(USER_ID,LCHET,FAMILY,NAME,\
      FATHER,SERIA,NOMER,DOST,ULIC,ADRES,METKA1)";
      sql+=" values(";
      if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql+=IntToStr(SaleBookDM->UserID)+","; else sql+="0,";
      sql+=IntToStr(DS->FieldByName("LCHET")->AsInteger)+",'";
      sql+=DS->FieldByName("FAMILY")->AsString.Trim()+"','";
      sql+=DS->FieldByName("NAME")->AsString.Trim()+"','";
      sql+=DS->FieldByName("FATHER")->AsString.Trim()+"','";
      sql+=DS->FieldByName("SERIA")->AsString.Trim()+"',";
      sql+=IntToStr(DS->FieldByName("NOMER")->AsInteger)+",";
      sql+=IntToStr(DS->FieldByName("DOST")->AsInteger)+",'";
      sql+=DS->FieldByName("ULIC")->AsString.Trim()+"','";
      sql+=DS->FieldByName("ADRES")->AsString.Trim()+"',";
      sql+=IntToStr(DS->FieldByName("METKA1")->AsInteger)+")";
      WQ->SQL->Add(sql);
      try
      {
      WQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      WriteTransaction->Rollback();
      return;
      }
      WriteTransaction->Commit();
      DS->Close();
  }
}
  CopyButton->Enabled=true;
  if (flag==1)
  {
  if (post==1)
  {
  MessageDlg("Добавление избранных Вами поручений в задание почтальону прошло успешно!!!",mtWarning,TMsgDlgButtons() << mbOK,0);
  }else
  {
  MessageDlg("Добавление избранных Вами поручений на кассу/почтальону прошло успешно!!!",mtWarning,TMsgDlgButtons() << mbOK,0);
  }
  }else
  {
  MessageDlg("Добавление избранных Вами лиц в список до востребования прошло успешно!!!",mtWarning,TMsgDlgButtons() << mbOK,0);
  }
Close();
}
//---------------------------------------------------------------------------

void __fastcall TBrowseForm::SaveButtonClick(TObject *Sender)
{
  if(A_DS->State==dsEdit || A_DS->State==dsInsert)
  {
    A_DS->Post();
    A_DS->CloseOpen(false);
  }

}
//---------------------------------------------------------------------------

void __fastcall TBrowseForm::EditButtonClick(TObject *Sender)
{
A_DS->Edit();
}
//---------------------------------------------------------------------------

void __fastcall TBrowseForm::CancelButtonClick(TObject *Sender)
{
  if(A_DS->State==dsEdit || A_DS->State==dsInsert) A_DS->Cancel();
}
//---------------------------------------------------------------------------

void __fastcall TBrowseForm::A_DSD_VIPLChange(TField *Sender)
{
AnsiString d;
AnsiString sql;
AnsiString s;
TpFIBQuery *Q=SaleBookDM->TempQuery;


  d=IntToStr(A_DS->FieldByName("LCHET")->AsInteger);
  Q->Close();
  Q->SQL->Clear();
  sql="select ORG_ID,COUNT_DATE,COUNT_NUMBER from SGB";
  sql+=" where LCHET="+d+"";
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
  MessageDlg("Задание с делом за номером  - "+ d + " уже есть !!! МЕНЯТЬ ДАТУ НЕЛЬЗЯ!!! ",mtWarning,TMsgDlgButtons() << mbOK,0);
  A_DS->Cancel();
  return;
  }
  else
  {
  A_DS->Post();
  s="Дата выплаты текущей записи исправлена!!! Вы хотите поменять дату выплаты с "+ IntToStr(dold);
  s+=" на "+IntToStr(A_DS->FieldByName("D_VIPL")->AsInteger) +" во всех остальных записях данного набора данных?";
  if(MessageDlg(s,mtConfirmation,TMsgDlgButtons() << mbOK << mbCancel,0) == mrOk)
  {
      WriteTransaction->StartTransaction();
      WQ->Close();
      WQ->SQL->Clear();
      sql="update NDOST set D_VIPL= " + IntToStr(A_DS->FieldByName("D_VIPL")->AsInteger);
      sql+=" where D_VIPL="+IntToStr(dold);
      sql+=" and ndost.lchet not in(select lchet from sgb where sgb.m= " +IntToStr(m) + " and sgb.y = " +IntToStr(y)+" ) ";
      sql+=" and ndost.D_VIPL>="+IntToStr(date1);
      sql+=" and ndost.D_VIPL<="+IntToStr(date2);
      if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql+=" and ndost.METKA1 IN ("+SaleBookDM->UserIndex + ")";
      sql+=" and ndost.DOBAVL = 0 ";
      if(filter==ByPost) sql+=" and ndost.CHEL="+IntToStr(KPost);
      if(filter==ByOps) sql+=" and ndost.METKA1="+IntToStr(Ops);
      if(filter==ByDost) sql+=" and ndost.DOST="+IntToStr(Dost);
      if(filter==ByPost1){
      sql+=" and ndost.CHEL="+IntToStr(KPost);
      sql+=" and ndost.METKA1="+IntToStr(Ops);
      }
      if(filter==ByPost2){
      sql+=" and ndost.CHEL="+IntToStr(KPost);
      sql+=" and ndost.DOST="+IntToStr(Dost);
      }
      if(filter==ByPost3){
      sql+=" and ndost.CHEL="+IntToStr(KPost);
      sql+=" and ndost.METKA1="+IntToStr(Ops);
      sql+=" and ndost.DOST="+IntToStr(Dost);
      }
      if(filter==ByPost4){
      sql+=" and ndost.METKA1="+IntToStr(Ops);
      sql+=" and ndost.DOST="+IntToStr(Dost);
      }
      WQ->SQL->Add(sql);
      try
      {
      WQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      WriteTransaction->Rollback();
      return;
      }
      WriteTransaction->Commit();
  }
  LoadDataSet();
  }
}
//---------------------------------------------------------------------------


void __fastcall TBrowseForm::A_DSBeforeEdit(TDataSet *DataSet)
{
  dold=A_DS->FieldByName("D_VIPL")->AsInteger;
}
//---------------------------------------------------------------------------


void __fastcall TBrowseForm::DBGridMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
ProvStatus();
}
//---------------------------------------------------------------------------


void __fastcall TBrowseForm::DBGridCellClick(TColumnEh *Column)
{
  Edit2->Text=IntToStr(BrowseForm->DBGrid->SelectedRows->Count);
}
//---------------------------------------------------------------------------

void __fastcall TBrowseForm::CheckBox1Click(TObject *Sender)
{
if (CheckBox1->Checked)
{
BrowseForm->DBGrid->SelectedRows->SelectAll();
}else
{
BrowseForm->DBGrid->SelectedRows->Clear();
}
Edit2->Text=IntToStr(BrowseForm->DBGrid->SelectedRows->Count);
}
//---------------------------------------------------------------------------

void __fastcall TBrowseForm::CheckBox2Click(TObject *Sender)
{
  LoadDataSet();
}
//---------------------------------------------------------------------------
void __fastcall TBrowseForm::ProvStatus(void)
{
AnsiString sql,str,countdate,fs,prich;
int countnumber;
fs="Касса";
unsigned short dvp,yvp,mvp;
unsigned short di,yi,mi;
unsigned short dt,yt,mt;
unsigned short dl,yl,ml;
TDateTime dprn;
TDateTime lockDate=SaleBookDM->GetConstValue(SaleBookDM->OrganizationID,"LOCK_EDIT_DATE");
TDateTime tekDate=Date();
lockDate.DecodeDate(&yl,&ml,&dl);
tekDate.DecodeDate(&yt,&mt,&dt);
TpFIBQuery *Q=SaleBookDM->TempQuery;
int dov;
Label19->Height=23;

if (flag==0 || flag==1)
{
if (AccountsJournalForm!=NULL)
{
 try
 {
 dprn=AccountsJournalForm->getDate1();
 }
 catch (Exception &exc)
 {
 dprn=tekDate;
 }
 dprn.DecodeDate(&yvp,&mvp,&dvp);
 if (yvp!=yl)
 {
 dprn=tekDate;
 dprn.DecodeDate(&yvp,&mvp,&dvp);
 }
}
else
{
dprn=tekDate;
dprn.DecodeDate(&yvp,&mvp,&dvp);
}

 if (ml!=mvp)
 {
  if (ml==1)
  {
  mvp=1;
  yvp++;
  }else
  {
  mvp++;
  }
 }

  Q->Close();
  Q->SQL->Clear();
  sql="select t1.* ";
  sql+=" from DOV t1";
  sql+=" where t1.LCHET='"+A_DS->FieldByName("LCHET")->AsString+"'";
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

  if(Q->RecordCount!=0) dov=1; else dov=0;


    TempQuery->Close();
    TempQuery->SQL->Clear();

      sql="select * from SGB where LCHET="+IntToStr(A_DS->FieldByName("LCHET")->AsInteger);
      sql+=" and KASSA=0";

    TempQuery->SQL->Add(sql);
    try
    {
      TempQuery->ExecQuery();
    }
    catch (Exception &exc)
    {
      MessageDlg("Ошибка TempQuery (SGB)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }

    if(TempQuery->RecordCount>0)
    {
    countnumber=TempQuery->FieldByName("COUNT_NUMBER")->AsInteger;
    countdate=TempQuery->FieldByName("COUNT_DATE")->AsDateTime.DateString();
    prich=TempQuery->FieldByName("PRICH")->AsString.Trim();
    TempQuery->Close();
    TempQuery->SQL->Clear();
    sql="select a.*, c.DESCRIPTION as CUSTOMER_NAME, u.LOGIN as USER_NAME";
    sql+=" from ACCOUNTS a";
    sql+=" left outer join EI c on c.ID=a.CUSTOMER_ID";
    sql+=" left outer join USERS u on u.ID=a.USER_ID";
    sql+=" where a.ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
    sql+=" and a.COUNT_DATE='"+countdate.Trim()+"'";
    sql+=" and a.COUNT_NUMBER="+IntToStr(countnumber);
    TempQuery->SQL->Add(sql);
    try
    {
      TempQuery->ExecQuery();
    }
    catch (Exception &exc)
    {
      MessageDlg("Ошибка TempQuery (SGB)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }

    if(TempQuery->RecordCount!=0)
    {
    if (prich=="")
    {
    str=" Оплачено по заданию № ";
    Label19->Font->Color=clBlack;
    }
    else
    {
    if (prich=="н/д")  str=" Не оплачено по причине нет дома по заданию № "; else str=" Не оплачено по заданию № ";
    Label19->Font->Color=clRed;
    }
    str+=IntToStr(countnumber);
    str+=" от ";
    str+=countdate.Trim();
    if(TempQuery->FieldByName("CUSTOMER_NAME")->AsString.Pos(fs))
    {
    str+=" на кассе - ";
    str+=TempQuery->FieldByName("CUSTOMER_NAME")->AsString.Trim();
    }else
    {
    str+=" почтальон - ";
    str+=TempQuery->FieldByName("CUSTOMER_NAME")->AsString.Trim();
    }
    str+=" автор - ";
    str+=TempQuery->FieldByName("USER_NAME")->AsString.Trim();
    if (prich!="") str+=" причина " + prich;
    if (dov==1) str+=" до востребования по доверенности ";

    Label19->Caption=str;
    Label19->Visible=true;
    }
    else
    {
    Label19->Caption="";
    Label19->Visible=false;
    }
    }
    else
    {
    str="НЕ ДОБАВЛЕНО!!!";
    if (dov==1) str+=" Это поручение до востребования по доверенности !!! ";

    if (dt>A_DS->FieldByName("D_VIPL")->AsInteger)
    {
    str+=" ВНИМАНИЕ!!! Данное поручение НЕ БЫЛО добавлено в задание по графику в день " + IntToStr(A_DS->FieldByName("D_VIPL")->AsInteger);
    Label19->Font->Color=clRed;
    }
    else
    {
    str+=" ВНИМАНИЕ!!! Данное поручение НЕОБХОДИМО добавить в задание по графику в день " + IntToStr(A_DS->FieldByName("D_VIPL")->AsInteger);
    Label19->Font->Color=clBlack;
    }
    Label19->Caption=str;
    Label19->Height=23;
    Label19->Visible=true;
    }
}
}



