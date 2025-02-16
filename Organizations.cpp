//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "DataModule.h"
#include "ConstHistoryEdit.h"
#include "SimpleConstantEdit.h"
#include "Organizations.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Placemnt"
#pragma link "DBGridEh"
#pragma link "FIBDataSet"
#pragma link "pFIBDataSet"
#pragma link "kbmMemTable"
#pragma link "FIBQuery"
#pragma link "pFIBQuery"
#pragma link "ToolEdit"
#pragma link "FIBDatabase"
#pragma link "pFIBDatabase"
#pragma link "JvComponent"
#pragma link "JvExControls"
#pragma link "JvNavigationPane"
#pragma resource "*.dfm"
TOrganizationsForm *OrganizationsForm;
//---------------------------------------------------------------------------
__fastcall TOrganizationsForm::TOrganizationsForm(TComponent* Owner)
        : TForm(Owner)
{
  iniFileName=MainForm->WorkDir+"SB_2009.ini";
  FormStorage1->IniFileName=iniFileName;
  FormStorage1->IniSection="OrganizationsForm";

  try
  {
    OrgDS->Open();
  }
  catch(const Exception &exc)
  {
    MessageDlg("������ �������� ������� ORGANISATION\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  TLocateOptions opt; opt.Clear();
  OrgDS->Locate("ID",SaleBookDM->OrganizationID,opt);
  CDS->SQLs->SelectSQL->Clear();
  AnsiString sql="select * from CONSTANT order by CONST_KIND desc";
  CDS->SQLs->SelectSQL->Add(sql);
  try
  {
    CDS->Open();
  }
  catch(const Exception &exc)
  {
    MessageDlg("������ �������� ������� CDS\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  CDate=Date();
  DateEdit->Date=CDate;
//  FullingConstDS();
  PageControl1->ActivePage=TabSheet1;
  TIniFile *ini = new TIniFile(iniFileName);
  Panel3->Height=ini->ReadInteger("OrganizationsForm","Panel3_Height",160);
  ConstGrid->Columns->Items[0]->Width=ini->ReadInteger("OrganizationsForm","constGrid_Columns_Items[0]_Width",20);
  ConstGrid->Columns->Items[1]->Width=ini->ReadInteger("OrganizationsForm","constGrid_Columns_Items[1]_Width",50);
  ConstGrid->Columns->Items[2]->Width=ini->ReadInteger("OrganizationsForm","constGrid_Columns_Items[2]_Width",180);
  ConstGrid->Columns->Items[4]->Width=ini->ReadInteger("OrganizationsForm","constGrid_Columns_Items[4]_Width",90);
  delete ini;
}
//---------------------------------------------------------------------------
void __fastcall TOrganizationsForm::FullingConstDS(void)
{
TDateTime ConstDate;
int Reference;

  ConstDS->Active=false;
  ConstDS->EmptyTable();
  ConstDS->Active=true;
  CDS->First();
  while(!CDS->Eof)
  { AnsiString identifer=CDS->FieldByName("IDENTIFIER")->AsString;
    if(!identifer.Pos("SIGNATURE_FOR_"))
    { ConstDS->Append();
      ConstDS->FieldByName("ID")->Value=CDS->FieldByName("ID")->AsInteger;
      ConstDS->FieldByName("ConstName")->AsString=CDS->FieldByName("CONST_NAME")->AsString;
      int id=OrgDS->FieldByName("ID")->AsInteger;
      ConstDS->FieldByName("CONST_KIND")->AsInteger=CDS->FieldByName("CONST_KIND")->AsInteger;
      AnsiString value;
      if(ConstDS->FieldByName("CONST_KIND")->AsInteger==1)
      { AnsiString date=CDate.DateString();
        value=SaleBookDM->GetConstValue(id,identifer,CDate,ConstDate,Reference);
        ConstDS->FieldByName("ConstValue")->Value=value;
        ConstDS->FieldByName("ConstDate")->Value=ConstDate;
      }
      else
      { value=SaleBookDM->GetConstValue(id,identifer);
        ConstDS->FieldByName("ConstValue")->Value=value;
      }
      ConstDS->FieldByName("IDENTIFIER")->AsString=identifer;
      ConstDS->Post();
    }
    CDS->Next();
  }
  ConstDS->First();
}
//---------------------------------------------------------------------------
void __fastcall TOrganizationsForm::OrgSourceDataChange(TObject *Sender,
      TField *Field)
{
  if(ConstDS->Active) FullingConstDS();
}
//---------------------------------------------------------------------------
void __fastcall TOrganizationsForm::DateEditChange(TObject *Sender)
{
  CDate=DateEdit->Text;
  FullingConstDS();
}
//---------------------------------------------------------------------------
void __fastcall TOrganizationsForm::FormShow(TObject *Sender)
{
  OrgGrid->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TOrganizationsForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  TIniFile *ini = new TIniFile(iniFileName);
  ini->WriteInteger("OrganizationsForm","Panel3_Height",Panel3->Height);
  ini->WriteInteger("OrganizationsForm","constGrid_Columns_Items[0]_Width",ConstGrid->Columns->Items[0]->Width);
  ini->WriteInteger("OrganizationsForm","constGrid_Columns_Items[1]_Width",ConstGrid->Columns->Items[1]->Width);
  ini->WriteInteger("OrganizationsForm","constGrid_Columns_Items[2]_Width",ConstGrid->Columns->Items[2]->Width);
  ini->WriteInteger("OrganizationsForm","constGrid_Columns_Items[4]_Width",ConstGrid->Columns->Items[4]->Width);
  delete ini;
  CDS->Close();
  ConstDS->Close();
  OrgDS->Close();
  Action=caFree;
}
//---------------------------------------------------------------------------
void __fastcall TOrganizationsForm::OrgSourceStateChange(TObject *Sender)
{
  if(OrgDS->State==dsEdit || OrgDS->State==dsInsert)
  { SaveButton->Enabled=true;
    CancelButton->Enabled=true;
  }
  else
  { SaveButton->Enabled=false;
    CancelButton->Enabled=false;
  }
}
//---------------------------------------------------------------------------
//���������� �����������
void __fastcall TOrganizationsForm::AddButtonClick(TObject *Sender)
{
  if(OrgDS->State==dsEdit || OrgDS->State==dsInsert) OrgDS->Post();
  OrgDS->Append();
}
//---------------------------------------------------------------------------
//���������� ���������
void __fastcall TOrganizationsForm::SaveButtonClick(TObject *Sender)
{
  if(OrgDS->State==dsEdit || OrgDS->State==dsInsert)
  { OrgDS->Post();
    if(OrgDS->FieldByName("ID")->AsInteger==SaleBookDM->OrganizationID) SaleBookDM->BeginDate=OrgDS->FieldByName("BEGIN_DATE")->AsDateTime;
  }
}
//---------------------------------------------------------------------------
//������ ���������
void __fastcall TOrganizationsForm::CancelButtonClick(TObject *Sender)
{
  if(OrgDS->State==dsEdit || OrgDS->State==dsInsert) OrgDS->Cancel();
}
//---------------------------------------------------------------------------
//�������� �����������
void __fastcall TOrganizationsForm::DelButtonClick(TObject *Sender)
{
int id=OrgDS->FieldByName("ID")->AsInteger;

  if(OrgDS->RecordCount==0) return;

  if(MessageDlg("�� �������, ��� ������ ������� ������� ������?",mtConfirmation,TMsgDlgButtons() << mbOK << mbCancel,0)==mrCancel)
  return;

  //��������� ������� ������ �� �������� �� ��������� ������
  SaleBookDM->TempQuery->Close();
  SaleBookDM->TempQuery->SQL->Clear();
  SaleBookDM->TempQuery->SQL->Add("select * from ACCOUNTS where ORG_ID = "+IntToStr(id));
  SaleBookDM->TempQuery->ExecQuery();
  if(SaleBookDM->TempQuery->RecordCount > 0)
  {
    SaleBookDM->TempQuery->Close();
    SaleBookDM->TempQuery->SQL->Clear();
    SaleBookDM->TempQuery->SQL->Add("update ORGANIZATIONS set DELETE_FLG = 1 where ID = "+IntToStr(id));
    try
    {
      SaleBookDM->TempQuery->ExecQuery();
    }
    catch(const Exception &exc)
    {
      MessageDlg("������ �������� ������\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      SaleBookDM->TempQuery->Close();
      return;
    }
    SaleBookDM->TempQuery->Close();
  }
  else
  { try
    {
      OrgDS->Delete();
    }
    catch(const Exception &exc)
    {
      MessageDlg("������ �������� ������\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
  }
  OrgDS->Close();
  OrgDS->Open();
}
//---------------------------------------------------------------------------
//�������������� �����
void __fastcall TOrganizationsForm::SpeedButton1Click(TObject *Sender)
{
int rn=ConstDS->RecNo;

  if(ConstDS->FieldByName("IDENTIFIER")->AsString=="ORDER_SIGNATURE")
  {
  }
  else if(ConstDS->FieldByName("IDENTIFIER")->AsString=="FOR_LEADER_WARRANT" || ConstDS->FieldByName("IDENTIFIER")->AsString=="FOR_BOOKLEADER_WARRANT")
  {
  }
  else if(ConstDS->FieldByName("IDENTIFIER")->AsString=="LOCK_EDIT_DATE")
  { TSimpleConstantEditForm *SCEF;
    try
    {
      SCEF=new TSimpleConstantEditForm(this,iniFileName,OrgDS->FieldByName("ID")->AsInteger,ConstDS->FieldByName("IDENTIFIER")->AsString);
    }
    catch (Exception &exc)
    { MessageDlg("������ �������� ����� SimpleConstantEditForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
    SCEF->ShowModal();
    delete SCEF;
  }
  else
  {
    TConstHistoryEditForm *CHEF;
    try
    {
      CHEF=new TConstHistoryEditForm(this,OrgDS->FieldByName("ID")->AsInteger,ConstDS->FieldByName("ID")->AsInteger);
    }
    catch (Exception &exc)
    { MessageDlg("������ �������� ����� CHEF\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
    CHEF->ShowModal();
    delete CHEF;
  }
  FullingConstDS();
  ConstDS->RecNo=rn;
}
//---------------------------------------------------------------------------

void __fastcall TOrganizationsForm::ExitButtonClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------

