//---------------------------------------------------------------------------
//���������� ��� ������

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "DataModule.h"
#include "RefSort.h"
#include "Main.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "Placemnt"
#pragma link "SmrtPanel"
#pragma link "FIBDataSet"
#pragma link "pFIBDataSet"
#pragma link "pFIBDataSet"
#pragma link "FIBDatabase"
#pragma link "FIBQuery"
#pragma link "pFIBQuery"
#pragma resource "*.dfm"
TEIForm *EIForm1;
//---------------------------------------------------------------------------
//���������� �����
__fastcall TEIForm1::TEIForm1(TComponent* Owner)
        : TForm(Owner)
{
  FormStorage1->IniFileName=MainForm->WorkDir+"SB_2009.ini";
  FormStorage1->IniSection="EIForm-1";

  if(SaleBookDM->UserRole=="�������������") Caption="���������� � �����";
  if(SaleBookDM->UserRole=="������������") Caption="���������� � �����";
  if(SaleBookDM->UserRole=="���������") Caption="����������";
  if(SaleBookDM->UserRole=="������") Caption="�����";
  if(SaleBookDM->UserRole=="���������-������") Caption="���������� � �����";

  if(SaleBookDM->UserRole=="�������������")
  {
  DS=SaleBookDM->EIDS;
  }else
  {
  DS=DSSved;
  }

  DataSource->DataSet=DS;
  recno=0;
  TIniFile *ini=new TIniFile(MainForm->WorkDir+"SB_2009.ini");
  sortind=ini->ReadInteger("EIForm", "sortind",1);
  delete ini;
}
//---------------------------------------------------------------------------
//���������� �����
__fastcall TEIForm1::TEIForm(TComponent* Owner,TDataSet *DtS)
        : TForm(Owner)
{
  FormStorage1->IniFileName=MainForm->WorkDir+"SB_2009.ini";
  FormStorage1->IniSection="EIForm";

  Caption="����������-����������";
  DS=(TpFIBDataSet*)DtS;
  DataSource->DataSet=DS;
  recno=0;
  TIniFile *ini=new TIniFile(MainForm->WorkDir+"SB_2009.ini");
  sortind=ini->ReadInteger("EIForm", "sortind",1);
  delete ini;
}
//---------------------------------------------------------------------------
void __fastcall TEIForm::LoadDataSet()
{
AnsiString sql;
TpFIBQuery *Q=SaleBookDM->TempQuery;
AnsiString IndOps;
AnsiString IndexOps;
int Massiv[20];
int KolOps;
int k=0;



  if(DS->Active==true) DS->Close();
  DS->SQLs->SelectSQL->Clear();

if (CheckBox1->Checked)
{

  if(SaleBookDM->UserRole=="�������������" || SaleBookDM->UserRole=="���������-������")
  {
    DS->SQLs->SelectSQL->Add("select * from EI order by DESCRIPTION");
  }

  if(SaleBookDM->UserRole=="���������")
  {
    DS->SQLs->SelectSQL->Add("select * from EI where DESCRIPTION NOT STARTING WITH '�����' order by DESCRIPTION");
  }

  if(SaleBookDM->UserRole=="������")
  {
    DS->SQLs->SelectSQL->Add("select * from EI where DESCRIPTION STARTING WITH '�����' order by DESCRIPTION");
  }
}else
{
  sql="select * from USERS where ID="+IntToStr(SaleBookDM->UserID);
  Q->Close();
  Q->SQL->Clear();
  Q->SQL->Add(sql);
  try
  {
    Q->ExecQuery();
  }
  catch(const Exception &exc)
  {
  MessageDlg("������ - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  }
  IndOps=Q->FieldByName("U_INDEX")->AsString;

  for (int cidm=0;cidm<20;cidm++)
  {
  Massiv[cidm]=0;
  }

  k=0;
  int cur=0, beg=IndOps.Pos(",");
  if (beg>0)
  {
  IndexOps="'";
  while(beg)
  {
    AnsiString S1=IndOps.SubString(cur,cur+beg-1);
    IndexOps=IndexOps+S1.Trim()+"','";
    Massiv[k]=StrToInt(S1.Trim());

    cur=beg+1;
    AnsiString S2=IndOps.SubString(cur,IndOps.Length());
    k++;
    IndOps=S2;
    cur=0;
    beg=IndOps.Pos(",");
    if (beg==0){
    IndexOps=IndexOps+S2.Trim()+"'";
    Massiv[k]= StrToInt(S2.Trim());
   }
  }
  KolOps=k;
  }
  else
  {
  IndexOps="'"+IndOps.Trim()+"'";
  KolOps=1;
  Massiv[k]=StrToInt(IndOps.Trim());
  }
  sql="select distinct ei.id,ei.description from ndost inner join ei on (ndost.chel = ei.id)";
  sql+=" where ndost.metka1 in ("+ IndexOps +")";
  sql+=" and ndost.m= " + IntToStr(SaleBookDM->mvip);
  sql+=" and ndost.y= " + IntToStr(SaleBookDM->yvip);
  sql+=" and ndost.d_vipl= " + IntToStr(SaleBookDM->dvip);
  sql+=" and ndost.lchet not in(select lchet from dov)";


  if(SaleBookDM->UserRole=="���������-������")
  {
  sql+=" union select id,description from ei where DESCRIPTION STARTING WITH '�����' order by 1";
  }
  if(SaleBookDM->UserRole=="������")
  {
  sql="";
  sql=" select id,description from ei where DESCRIPTION STARTING WITH '�����' order by 1";
  }
}

  DS->SQLs->SelectSQL->Add(sql);

  try
  {
    DS->Open();
  }
  catch(const Exception &exc)
  {
    MessageDlg("������ �������� DataSet (���������� ����������)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  DS->Last();
  DS->First();
  StaticText1->Caption="�������: "+IntToStr(DS->RecordCount);
}
//---------------------------------------------------------------------------
void __fastcall TEIForm::FormShow(TObject *Sender)
{
  if(SaleBookDM->UserRole=="�������������")
  {
  CheckBox1->Checked=true;
  CheckBox1->Visible=false;
  }else
  {
  CheckBox1->Checked=false;
  CheckBox1->Visible=true;
  }

  LoadDataSet();
  Visible=true;
  if(SaleBookDM->UserRole!="�������������")
  {
  if (EIGrid->DataSource->DataSet->RecordCount > 0){
  SelectButton->Enabled = true;
  DelButton->Enabled = false;
  SaveButton->Enabled = false;
  AddButton->Enabled = false;
  CancelButton->Enabled = false;
  }
  else
  {
  SelectButton->Enabled = false;
  DelButton->Enabled = false;
  SaveButton->Enabled = false;
  AddButton->Enabled = false;
  CancelButton->Enabled = false;
  }
  }
  else
  {
  if (EIGrid->DataSource->DataSet->RecordCount > 0){
  SelectButton->Enabled = true;
  DelButton->Enabled = true;
  SaveButton->Enabled = true;
  AddButton->Enabled = true;
  CancelButton->Enabled = true;
  }
  else
  {
  SelectButton->Enabled = false;
  DelButton->Enabled = false;
  SaveButton->Enabled = false;
  AddButton->Enabled = false;
  CancelButton->Enabled = false;
  }
  }
  EIGrid->SetFocus();
}
//---------------------------------------------------------------------------
//��� �������� �����
void __fastcall TEIForm::FormClose(TObject *Sender, TCloseAction &Action)
{
//  Action=caFree;
}
//---------------------------------------------------------------------------
void __fastcall TEIForm::FormDestroy(TObject *Sender)
{
  TIniFile *ini=new TIniFile(MainForm->WorkDir+"SB_2009.ini");
  ini->WriteInteger("EIForm", "sortind",sortind);
  delete ini;
}
//---------------------------------------------------------------------------
//����� ������
void __fastcall TEIForm::EIGridKeyPress(TObject *Sender, char &Key)
{
  if(Key==VK_RETURN && (DS->State==dsInsert || DS->State==dsEdit))
  { if(EIGrid->Col < 3) EIGrid->Col++;
    else EIGrid->Col=1;
  }
}
//---------------------------------------------------------------------------
//��� ������ ������ ������
void __fastcall TEIForm::EIGridDblClick(TObject *Sender)
{
  SelRecExecute(this);
}
//---------------------------------------------------------------------------
void __fastcall TEIForm::SelRecExecute(TObject *Sender)
{
  if(DS->State==dsEdit || DS->State==dsInsert) DS->Post();
  Close();
  ModalResult=mrOk;
}
//---------------------------------------------------------------------------
//���������� ������ ��� ������ ������
void __fastcall TEIForm::ExitButtonClick(TObject *Sender)
{
  Close();
  ModalResult=mrCancel;
}
//---------------------------------------------------------------------------
//�������� ������
void __fastcall TEIForm::DelButtonClick(TObject *Sender)
{
//  if(DS->RecordCount==0) return;
//  if(MessageDlg("�� ������������� ������ ������� ������ '"+DS->FieldByName("DESCRIPTION")->AsString+"'?",mtConfirmation,TMsgDlgButtons() << mbOK << mbCancel,0)==mrOk)
//  { DS->Delete();
//    EIGrid->SelectedRows->CurrentRowSelected=true;
//  }
}
//---------------------------------------------------------------------------
void __fastcall TEIForm::DataSourceStateChange(TObject *Sender)
{
  if(DS->State==dsEdit || DS->State==dsInsert)
  { SaveButton->Enabled=true;
    CancelButton->Enabled=true;
  }
  else
  { SaveButton->Enabled=false;
    CancelButton->Enabled=false;
  }

}
//---------------------------------------------------------------------------
void __fastcall TEIForm::SaveButtonClick(TObject *Sender)
{
  if(EIGrid->DataSource->DataSet->State==dsEdit || EIGrid->DataSource->DataSet->State==dsInsert) DS->Post();
}
//---------------------------------------------------------------------------
void __fastcall TEIForm::CancelButtonClick(TObject *Sender)
{
  if(EIGrid->DataSource->DataSet->State==dsEdit || EIGrid->DataSource->DataSet->State==dsInsert) DS->Cancel();
}
//---------------------------------------------------------------------------
void __fastcall TEIForm::AddButtonClick(TObject *Sender)
{
  DS->Append();
  EIGrid->Col=2;
}
//---------------------------------------------------------------------------
void __fastcall TEIForm::SortButtonClick(TObject *Sender)
{
/*TRefSortForm *RSF=NULL;

  try
  {
    RSF=new TRefSortForm(this);
  }
  catch(...)
  { Application->MessageBoxA("������ �������� �����","TEIForm::SortButtonClick",MB_OK);
    return;
  }
  if(RSF->ShowForm(sortind,Left,Top)==mrOk)
  { int ID=DS->FieldByName("ID")->AsInteger;
    if(RSF->RadioButton1->Checked) sortind=1;
    else sortind=2;
    LoadDataSet();
    TLocateOptions Opt; Opt.Clear();
    DS->Locate("ID",ID,Opt);
  }
  if(RSF!=NULL) delete RSF;*/
}
//---------------------------------------------------------------------------
void __fastcall TEIForm::LookUpRecord(int id)
{
  if(id==0) return;
  RQ->Close();
  RQ->SQL->Clear();
  AnsiString sql="select ID from EI where ID="+IntToStr(id);
  RQ->SQL->Add(sql);
  try
  {
    RQ->ExecQuery();
  }
  catch (Exception &exc)
  {
    MessageDlg("������ - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(RQ->RecordCount == 0)
  {
    RQ->Close();
    return;
  }
  id=RQ->FieldByName("ID")->AsInteger;
  RQ->Close();
  LoadDataSet();
  TLocateOptions lo; lo.Clear();
  DS->Locate("ID",id,lo);
}

void __fastcall TEIForm::EIGridCellClick(TColumnEh *Column)
{
  if(SaleBookDM->UserRole!="�������������")
  {
  if (EIGrid->DataSource->DataSet->RecordCount > 0){
  SelectButton->Enabled = true;
  DelButton->Enabled = false;
  SaveButton->Enabled = false;
  AddButton->Enabled = false;
  CancelButton->Enabled = false;
  }
  else
  {
  SelectButton->Enabled = false;
  DelButton->Enabled = false;
  SaveButton->Enabled = false;
  AddButton->Enabled = false;
  CancelButton->Enabled = false;
  }
  }
  else
  {
  if (EIGrid->DataSource->DataSet->RecordCount > 0){
  SelectButton->Enabled = true;
  DelButton->Enabled = true;
  SaveButton->Enabled = true;
  AddButton->Enabled = true;
  CancelButton->Enabled = true;
  }
  else
  {
  SelectButton->Enabled = false;
  DelButton->Enabled = false;
  SaveButton->Enabled = false;
  AddButton->Enabled = false;
  CancelButton->Enabled = false;
  }
  }
}
//---------------------------------------------------------------------------


void __fastcall TEIForm::CheckBox1Click(TObject *Sender)
{
  LoadDataSet();
}
//---------------------------------------------------------------------------


