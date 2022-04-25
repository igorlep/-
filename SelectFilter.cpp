//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "AccauntsJournal.h"
#include "DataModule.h"
#include "SelectFilter.h"
#include "BrowseF.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Placemnt"
#pragma link "RXDBCtrl"
#pragma link "SmrtPanel"
#pragma link "ToolEdit"
#pragma link "FIBDatabase"
#pragma link "FIBQuery"
#pragma link "pFIBDatabase"
#pragma link "pFIBQuery"
#pragma link "JvComponent"
#pragma link "JvExControls"
#pragma link "JvXPButtons"
#pragma link "JvXPCore"
#pragma link "FIBDataSet"
#pragma link "pFIBDataSet"
#pragma resource "*.dfm"
TSelectFilterForm *SelectFilterForm;
//---------------------------------------------------------------------------
__fastcall TSelectFilterForm::TSelectFilterForm(TComponent* Owner)
        : TForm(Owner)
{
AnsiString sql;
AnsiString Massiv[100];
AnsiString IndOps;
AnsiString IndexOps;
int i=1;
int KolOps=0;
int k=0;


  FormStorage1->IniFileName=MainForm->WorkDir+"SB_2009.ini";
  FormStorage1->IniSection="SelectFilterForm";
  autoID=NULL;
  autoID1=NULL;

  for (int cidm=0;cidm<100;cidm++)
  {
  Massiv[cidm]="";
  }


  try
  {
    autoID=new TStringList();
  }
  catch (Exception &exc)
  {
    MessageDlg("Ошибка создания объекта TStringList\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    autoID=NULL;
    return;
  }
  autoNumberEdit->Items->Clear();

  RQT->Close();
  RQT->SQLs->SelectSQL->Clear();
  if (SaleBookDM->UserRole=="Администратор" || SaleBookDM->UserRole!="Руководитель"){
  sql="select DESCRIPTION as SD_NAME from NOMENCLATURE where ";
  sql+= " NOMENCLATURE.DESCRIPTION IN ("+SaleBookDM->UserIndexAll + ")";
  RQT->SQLs->SelectSQL->Add(sql);
  try
  {
    RQT->Open();
  }
  catch (Exception &exc)
  {
  MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  }
  int i=1;
  if (RQT->RecordCount <=0)
  {
  MessageDlg("Нет данных !!! ",mtWarning,TMsgDlgButtons() << mbOK,0);
  autoNumberEdit->Items->Clear();
  autoNumberEdit1->Items->Clear();
  autoNumberEdit1->Visible=false;
  autoNumberEdit->Visible=false;
  selectButton->Enabled=false;
  return;
  }
  RQT->First();
  while(!RQT->Eof)
  {
    AnsiString sdName=RQT->FieldByName("SD_NAME")->AsString;
    autoNumberEdit->Items->Add(sdName);
    autoID->Add(RQT->FieldByName("SD_NAME")->AsString);
    RQT->Next();
    i++;
  }
  RQT->Close();
  }else
  {
  IndOps=SaleBookDM->UserIndex.Trim();
  k=0;
  int cur=0, beg=IndOps.Pos(",");
  if (beg>0)
  {
  IndexOps="'";
  while(beg)
  {
    AnsiString S1=IndOps.SubString(cur,cur+beg-1);
    AnsiString S2="";
    if (S1.Length()==1) S2="63000"+S1.Trim();
    if (S1.Length()==2) S2="6300"+S1.Trim();
    if (S1.Length()==3) S2="630"+S1.Trim();
    IndexOps=IndexOps+S2.Trim()+"','";
    Massiv[k]=S2.Trim();

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
    IndexOps=IndexOps+S4.Trim()+"'";
    Massiv[k]= S4.Trim();
   }
  }
  KolOps=k;
  for (int cidm=0;cidm<=KolOps;cidm++)
  {
  autoNumberEdit->Items->Add(Massiv[cidm].Trim());
  autoID->Add(Massiv[cidm].Trim());
  }
  }
  else
  {
  KolOps=1;
  AnsiString S5="";
  if (IndOps.Length()==1) S5="63000"+IndOps.Trim();
  if (IndOps.Length()==2) S5="6300"+IndOps.Trim();
  if (IndOps.Length()==3) S5="630"+IndOps.Trim();
  IndexOps=IndexOps+S5.Trim()+"'";
  Massiv[0]= S5.Trim();
  autoNumberEdit->Items->Add(S5.Trim());
  autoID->Add(S5.Trim());
  }
  }


  autoNumberEdit->ItemIndex=0;

  // формирование списка участков
  try
  {
    autoID1=new TStringList();
  }
  catch (Exception &exc)
  {
    MessageDlg("Ошибка создания объекта TStringList\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    autoID1=NULL;
    return;
  }
  int index = autoNumberEdit->ItemIndex;
  autoNumberEdit1->Items->Clear();
  RQT->Close();
  RQT->SQLs->SelectSQL->Clear();
  sql="";
  AnsiString vibOPS=autoID->Strings[index];
  AnsiString iops=vibOPS.SubString(4,255);
  int ops = StrToInt(iops);

  sql="select DESCRIPTION as SD_NAME from NOMENCLATURE where REC_TYPE=1 and INDEXOPS ="+IntToStr(ops);

  RQT->SQLs->SelectSQL->Add(sql);
  try
  {
    RQT->Open();
  }
  catch (Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  i=1;
  RQT->First();
  while(!RQT->Eof)
  {
    AnsiString sdName=RQT->FieldByName("SD_NAME")->AsString;
    autoNumberEdit1->Items->Add(sdName);
    autoID1->Add(sdName);
    RQT->Next();
    i++;
  }
  RQT->Close();
  autoNumberEdit1->ItemIndex=0;
  selectButton->Enabled=true;
  Ops=ops;
  index = autoNumberEdit1->ItemIndex;
  AnsiString vibDOST=autoID1->Strings[index];
  Dost = StrToInt(vibDOST);

//  AccountsJournalForm->FilterCustomerID=ops;

  // формирование списка почтальонов
  try
  {
    autoID2=new TStringList();
  }
  catch (Exception &exc)
  {
    MessageDlg("Ошибка создания объекта TStringList\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    autoID2=NULL;
    return;
  }
  autoNumberEdit2->Items->Clear();
  RQT->Close();
  RQT->SQLs->SelectSQL->Clear();
  sql="";

  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель")
  {
    sql="select distinct CODP as IDP,EI as SD_NAME from NOMENCLATURE where REC_TYPE=1 and INDEXOPS IN ("+SaleBookDM->UserIndex + ")";
  }
  else
  {
    sql="select ID as IDP,DESCRIPTION as SD_NAME from EI where DESCRIPTION NOT STARTING WITH 'Касса' ";
  }

  RQT->SQLs->SelectSQL->Add(sql);
  try
  {
    RQT->Open();
  }
  catch (Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  i=1;
  RQT->First();
  while(!RQT->Eof)
  {
    AnsiString sdName=RQT->FieldByName("SD_NAME")->AsString;
    autoNumberEdit2->Items->Add(sdName);
    autoID2->Add(IntToStr(RQT->FieldByName("IDP")->AsInteger));
    RQT->Next();
    i++;
  }
  RQT->Close();
  autoNumberEdit2->ItemIndex=0;
  selectButton->Enabled=true;
  index = autoNumberEdit2->ItemIndex;
  AnsiString VibPost=autoID2->Strings[index];
  KPost = StrToInt(VibPost);
  Post=autoNumberEdit2->Text;

}
//---------------------------------------------------------------------------
void __fastcall TSelectFilterForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Action=caFree;
}
//---------------------------------------------------------------------------
void __fastcall TSelectFilterForm::cancelButtonClick(TObject *Sender)
{
  Close();
  ModalResult=mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TSelectFilterForm::selectButtonClick(TObject *Sender)
{
  if(CheckBox1->Checked)
  {
    BrowseForm->ByNH=1;
  }else
  {
    BrowseForm->ByNH=0;
  }
  Close();
  ModalResult=mrOk;
}
void __fastcall TSelectFilterForm::PostCheckBoxClick(TObject *Sender)
{
  if(PostCheckBox->Checked)
  {
  BrowseForm->filter=ByPost;
  if(CustomerCheckBox->Checked) BrowseForm->filter=ByPost1;
  if(UserCheckBox->Checked) BrowseForm->filter=ByPost2;
  if(UserCheckBox->Checked && CustomerCheckBox->Checked) BrowseForm->filter=ByPost3;
  }
  else
  {
  BrowseForm->filter=None;
  }

}

//---------------------------------------------------------------------------
void __fastcall TSelectFilterForm::CustomerCheckBoxClick(TObject *Sender)
{
  if(CustomerCheckBox->Checked)
  {
  BrowseForm->filter=ByOps;
  if(PostCheckBox->Checked) BrowseForm->filter=ByPost1;
  if(UserCheckBox->Checked) BrowseForm->filter=ByPost4;
  if(UserCheckBox->Checked && PostCheckBox->Checked) BrowseForm->filter=ByPost3;
  }
  else
  {
     BrowseForm->filter=None;
  }
}
//---------------------------------------------------------------------------
void __fastcall TSelectFilterForm::UserCheckBoxClick(TObject *Sender)
{

  if(UserCheckBox->Checked)
  {
  BrowseForm->filter=ByDost;
  if(PostCheckBox->Checked) BrowseForm->filter=ByPost2;
  if(CustomerCheckBox->Checked) BrowseForm->filter=ByPost4;
  if(CustomerCheckBox->Checked && PostCheckBox->Checked) BrowseForm->filter=ByPost3;
  }
  else
  {
     BrowseForm->filter=None;
  }
}
//---------------------------------------------------------------------------

void __fastcall TSelectFilterForm::autoNumberEditChange(TObject *Sender)
{
  autoID1=NULL;
  int i=1;
  AnsiString sql;
  int index = autoNumberEdit->ItemIndex;

  // формирование списка участков
  try
  {
    autoID1=new TStringList();
  }
  catch (Exception &exc)
  {
    MessageDlg("Ошибка создания объекта TStringList\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    autoID1=NULL;
    return;
  }

  autoNumberEdit1->Items->Clear();
  RQT->Close();
  RQT->SQLs->SelectSQL->Clear();
  sql="";
  AnsiString vibOPS=autoID->Strings[index];
  AnsiString iops=vibOPS.SubString(4,255);
  int ops = StrToInt(iops);

  sql="select DESCRIPTION as SD_NAME from NOMENCLATURE where REC_TYPE=1 and INDEXOPS ="+IntToStr(ops);

  RQT->SQLs->SelectSQL->Add(sql);
  try
  {
    RQT->Open();
  }
  catch (Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  i=1;
  RQT->First();
  while(!RQT->Eof)
  {
    AnsiString sdName=RQT->FieldByName("SD_NAME")->AsString;
    autoNumberEdit1->Items->Add(sdName);
    autoID1->Add(sdName);
    RQT->Next();
    i++;
  }
  RQT->Close();
  autoNumberEdit1->ItemIndex=0;
  index = autoNumberEdit1->ItemIndex;
  selectButton->Enabled=true;
  Ops=ops;
  AnsiString vibDOST=autoID1->Strings[index];
  Dost = StrToInt(vibDOST);

//  AccountsJournalForm->FilterCustomerID=ops;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TSelectFilterForm::getPost(void)
{
  return Post;
}
int __fastcall TSelectFilterForm::getDost(void)
{
  return Dost;
}

int __fastcall TSelectFilterForm::getOps(void)
{
  return Ops;
}

int __fastcall TSelectFilterForm::getKpost(void)
{
  return KPost;
}

int __fastcall TSelectFilterForm::getOpl(void)
{
  return Opl;
}

void __fastcall TSelectFilterForm::autoNumberEdit1Change(TObject *Sender)
{
  int index = autoNumberEdit->ItemIndex;
  AnsiString vibOPS=autoID->Strings[index];
  AnsiString iops=vibOPS.SubString(4,255);
  int ops = StrToInt(iops);
  Ops=ops;
  index = autoNumberEdit1->ItemIndex;
  AnsiString vibDOST=autoID1->Strings[index];
  Dost = StrToInt(vibDOST);
}
//---------------------------------------------------------------------------


void __fastcall TSelectFilterForm::autoNumberEdit2Change(TObject *Sender)
{
  int index = autoNumberEdit2->ItemIndex;
  AnsiString VibPost=autoID2->Strings[index];
  KPost = StrToInt(VibPost);
  Post=autoNumberEdit2->Text;
}
//---------------------------------------------------------------------------


void __fastcall TSelectFilterForm::RadioGroup1Click(TObject *Sender)
{

switch (RadioGroup1->ItemIndex)
{
case 0: { BrowseForm->filter=ByOpl; Opl=1;break;}
case 1: { BrowseForm->filter=ByOpl; Opl=2;break;}
case 2: { BrowseForm->filter=ByOpl; Opl=3;break;}
default: { BrowseForm->filter=None; Opl=0;}
}

}
//---------------------------------------------------------------------------

void __fastcall TSelectFilterForm::FormShow(TObject *Sender)
{
if (  BrowseForm->flag == 0 ){
RadioGroup1->Visible=true;
CheckBox1->Visible=false;
}
if (  BrowseForm->flag == 1){
RadioGroup1->Visible=false;
CheckBox1->Visible=true;
}
if (  BrowseForm->flag == 2 ){
RadioGroup1->Visible=false;
CheckBox1->Visible=false;
}

if ( BrowseForm->ByNH == 1 ) CheckBox1->Checked=true; else CheckBox1->Checked=false;
}
//---------------------------------------------------------------------------

void __fastcall TSelectFilterForm::CheckBox1Click(TObject *Sender)
{
  if(CheckBox1->Checked)
  {
    BrowseForm->ByNH=1;
  }else
  {
    BrowseForm->ByNH=0;
  }


}
//---------------------------------------------------------------------------

