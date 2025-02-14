//---------------------------------------------------------------------------
//���������� ���

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "RefSort.h"
#include "Main.h"
#include "EditNomenclature.h"
#include "DataModule.h"
#include "Nomenclature.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "Placemnt"
#pragma link "SmrtPanel"
#pragma link "FIBQuery"
#pragma link "pFIBQuery"
#pragma link "FIBDataSet"
#pragma link "pFIBDataSet"
#pragma link "FIBDatabase"
#pragma link "pFIBDatabase"
#pragma link "pFIBStoredProc"
#pragma resource "*.dfm"
TNomenclatureForm *NomenclatureForm;
//---------------------------------------------------------------------------
//���������� �����
__fastcall TNomenclatureForm::TNomenclatureForm(TComponent* Owner)
        : TForm(Owner)
{
  FormStorage1->IniFileName=MainForm->WorkDir+"SB_2009.ini";
  FormStorage1->IniSection="NomenclatureForm";

  Caption="����� ��������";
  FieldNames=new TStringList;
  FieldNames->Text="���\n��� �������\n��� ������\n����� �������\n��� ����������\n��� ����������\n������ ���";

  WriteTransaction->DefaultDatabase=SaleBookDM->DataBase;
  TempQuery->Database=SaleBookDM->DataBase;
  TempQuery1->Database=SaleBookDM->DataBase;
  SQuery->Database=SaleBookDM->DataBase;
  StoredProc->Database=SaleBookDM->DataBase;
  StoredProc->Transaction=WriteTransaction;

  TempQuery->Close();
  TempQuery->SQL->Clear();
  TempQuery->SQL->Add("select ID from NOMENCLATURE");
  try
  {
    TempQuery->ExecQuery();
  }
  catch(const Exception &exc)
  {
    MessageDlg("������ �������� ������� �������\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }

  //���� ������� NOMENCLATURE ������ �������������� �� ��� ������ ������ �� ������������
  if(TempQuery->RecordCount==0)
  { int ID;
    StoredProc->Close();
    StoredProc->StoredProcName="NOMENCLATURE_ADD";
    StoredProc->ParamByName("FILE_ID")->AsInteger=0;
    StoredProc->ParamByName("REC_TYPE")->AsInteger=0;
    StoredProc->ParamByName("DESCRIPTION")->AsString="��� ( ����� �������� )";
    StoredProc->Prepare();
    try
    {
      StoredProc->ExecProc();
    }
    catch(const Exception &exc)
    {
      MessageDlg("������ ���������� ����� ������ � ������� �������\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
    ID=StoredProc->ParamByName("ID")->AsInteger;

  }

  CreateNode(NULL,0,0);
  TreeView1->FullExpand();
  TreeView1->Selected=TreeView1->Items->Item[0];
  id=TreeView1->Selected->StateIndex;
  TIniFile *ini=new TIniFile(MainForm->WorkDir+"SB_2009.ini");
  sortind=ini->ReadInteger("NomenclatureForm", "sortind",1);
  delete ini;
  LoadDataSet();
  DBGrid->Visible=true;
  SetButtons();
  ERF=NULL;
}
//---------------------------------------------------------------------------
//��� ����������� �����
void __fastcall TNomenclatureForm::FormDestroy(TObject *Sender)
{
  TIniFile *ini=new TIniFile(MainForm->WorkDir+"SB_2009.ini");
  ini->WriteInteger("NomenclatureForm", "sortind",sortind);
  delete ini;
  if(DataSet->Active==true) DataSet->Close();
  delete FieldNames;
}
//---------------------------------------------------------------------------
void __fastcall TNomenclatureForm::FormShow(TObject *Sender)
{
  SetMemo();
  DBGrid->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TNomenclatureForm::LoadDataSet()
{
  if(DataSet->Active==true) DataSet->Close();
  DataSet->SQLs->SelectSQL->Clear();
  if(sortind==1)
    DataSet->SQLs->SelectSQL->Add("select * from NOMENCLATURE where FILE_ID="+IntToStr(id)+" and REC_TYPE <> 0 and REC_TYPE = 1 order by DESCRIPTION");
  else DataSet->SQLs->SelectSQL->Add("select * from NOMENCLATURE where FILE_ID="+IntToStr(id)+" and REC_TYPE <> 0 and REC_TYPE = 1 order by ID");

  try
  {
    DataSet->Open();
  }
  catch(const Exception &exc)
  {
    MessageDlg("������ �������� DataSet (�������������)\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  DataSet->Last();
  DataSet->First();
  StaticText1->Caption="�������: "+IntToStr(DataSet->RecordCount);
  SetMemo();
}
//---------------------------------------------------------------------------
// ��������� ������
void __fastcall TNomenclatureForm::SetButtons(void)
{
  if(TreeView1->Selected->Level==0) FSubButton->Enabled=false;
  else FSubButton->Enabled=true;

  int fileID=TreeView1->Selected->StateIndex;

  TempQuery->Close();
  TempQuery->SQL->Clear();
  TempQuery->SQL->Add("select * from NOMENCLATURE where ID="+IntToStr(fileID));
  TempQuery->ExecQuery();

  if(TempQuery->RecordCount!=0)
  { if(TempQuery->FieldByName("REC_TYPE")->AsInteger==0)
    { if(TempQuery->FieldByName("FILE_ID")->AsInteger==0)
      {
        FAddChButton->Enabled=true;
        NewButton->Enabled=false;
      }
      else
      {
       FAddChButton->Enabled=false;
       NewButton->Enabled=true;
      }
      TempQuery1->Close();
      TempQuery1->SQL->Clear();
      TempQuery1->SQL->Add("select * from NOMENCLATURE where FILE_ID="+IntToStr(fileID)+" and REC_TYPE=1");
      TempQuery1->ExecQuery();
      if(TempQuery1->RecordCount==0)
      {
        SelectButton->Enabled=false;
        EditButton->Enabled=false;
        DelButton->Enabled=false;
        SortButton->Enabled=false;
        if(TempQuery->FieldByName("FILE_ID")->AsInteger==0) NewButton->Enabled=false; else NewButton->Enabled=true; 
      }
      else
      {
        SelectButton->Enabled=true;
        EditButton->Enabled=true;
        DelButton->Enabled=true;
        NewButton->Enabled=true;
        SortButton->Enabled=true;
      }
    }
    else
    {
      FSubButton->Enabled=false;
      TempQuery->Close();
      TempQuery->SQL->Clear();
      TempQuery->SQL->Add("select * from NOMENCLATURE where FILE_ID="+IntToStr(fileID));
      TempQuery->ExecQuery();
      if(TempQuery->RecordCount==0)
      {
        SelectButton->Enabled=false;
        EditButton->Enabled=false;
        NewButton->Enabled=true;
        DelButton->Enabled=false;
        SortButton->Enabled=false;
      }
      else
      {
        SelectButton->Enabled=false;
        EditButton->Enabled=false;
        NewButton->Enabled=true;
        DelButton->Enabled=true;
        SortButton->Enabled=true;
      }
    }
  }
  else
  { MessageDlg("������ select FILE_ID (TNomenclatureForm::SetButtons)",mtError,TMsgDlgButtons() << mbOK,0);
    SelectButton->Enabled=false;
    EditButton->Enabled=false;
    NewButton->Enabled=false;
    DelButton->Enabled=false;
    SortButton->Enabled=false;
  }
}
//---------------------------------------------------------------------------
//�������� ������ �������� �����������
void __fastcall TNomenclatureForm::CreateNode(TTreeNode *Node, int FileID, int Level)
{
TpFIBDataSet *Query;

  Query=NULL;
  try
  {
    Query=new TpFIBDataSet(this);
  }
  catch(const Exception &exc)
  {
    MessageDlg("������ ������� Query\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  Query->Database=SaleBookDM->DataBase;
  Query->Transaction=SaleBookDM->ReadTransaction;
  Query->SQLs->SelectSQL->Clear();
  Query->SQLs->SelectSQL->Add("select * from NOMENCLATURE where FILE_ID="+IntToStr(FileID)+" and REC_TYPE <> 1");
  try
  {
    Query->Open();
  }
  catch(const Exception &exc)
  {
    MessageDlg("������ �������� Query\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    if(Query!=NULL) delete Query;
    return;
  }

  Query->First();
  while(!Query->Eof)
  { if(Level==0) Node=TreeView1->Items->Add(Node,Query->FieldByName("DESCRIPTION")->AsString);
    else{ Node=TreeView1->Items->AddChild(Node,Query->FieldByName("DESCRIPTION")->AsString); Level=0;}
    Node->ImageIndex=0;
    Node->SelectedIndex=1;
    Node->StateIndex=Query->FieldByName("ID")->AsInteger;
    CreateNode(Node,Query->FieldByName("ID")->AsInteger,1);
    Query->Next();
  }
  if(Query!=NULL) delete Query;
}
//---------------------------------------------------------------------------
//���������� Memo
void __fastcall TNomenclatureForm::SetMemo(void)
{
  Memo1->Clear();
  if(DBGrid->Visible==true)
  { for(int i=0; i<DataSet->FieldCount; i++)
      Memo1->Lines->Add(FieldNames->Strings[i]+" - "+DataSet->Fields->Fields[i]->AsString);
  }
}
//---------------------------------------------------------------------------
//��� ����� ��������� � ������ ������
void __fastcall TNomenclatureForm::DataSourceDataChange(TObject *Sender,
      TField *Field)
{
  SetMemo();
}
//---------------------------------------------------------------------------
//��� ����� ���������� � ������ ��������
void __fastcall TNomenclatureForm::TreeView1Change(TObject *Sender,
      TTreeNode *Node)
{
  TempQuery->Close();
  TempQuery->SQL->Clear();
  TempQuery->SQL->Add("select * from NOMENCLATURE where ID="+IntToStr(Node->StateIndex));
  TempQuery->ExecQuery();
  if(TempQuery->RecordCount!=0){ id=Node->StateIndex; LoadDataSet();}
  TempQuery->Close();
  SetButtons();
}
//---------------------------------------------------------------------------
//�������������� ������������ �������
void __fastcall TNomenclatureForm::TreeView1DblClick(TObject *Sender)
{
  TreeView1->Selected->EditText();
}
//---------------------------------------------------------------------------
//���������� �������������� ������������ �������
void __fastcall TNomenclatureForm::TreeView1Edited(TObject *Sender, TTreeNode *Node,
      AnsiString &S)
{
  TempQuery->Close();
  TempQuery->SQL->Clear();
  TempQuery->SQL->Add("update NOMENCLATURE set DESCRIPTION='"+S+"' where ID="+IntToStr(Node->StateIndex));
  try
  {
    TempQuery->ExecQuery();
  }
  catch(const Exception &exc)
  {
    MessageDlg("������ ������ ������ �����\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    TempQuery->Close();
    return;
  }
  TempQuery->Close();
  LoadDataSet();
}
//---------------------------------------------------------------------------
//���������� ����������
void __fastcall TNomenclatureForm::FAddChButtonClick(TObject *Sender)
{
TTreeNode *Node=TreeView1->Selected;
int ID=0;

  StoredProc->Close();
  StoredProc->StoredProcName="NOMENCLATURE_ADD";
  StoredProc->ParamByName("FILE_ID")->AsInteger=Node->StateIndex;
  StoredProc->ParamByName("REC_TYPE")->AsInteger=0;
  StoredProc->ParamByName("DESCRIPTION")->AsString="";
  StoredProc->Prepare();
  try
  {
    StoredProc->ExecProc();
  }
  catch(const Exception &exc)
  {
    MessageDlg("������ ���������� ����� ������ � ������� �������\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  ID=StoredProc->ParamByName("ID")->AsInteger;
  StoredProc->Close();

  Node=TreeView1->Items->AddChild(Node,"");
  Node->ImageIndex=0;
  Node->SelectedIndex=1;
  Node->StateIndex=ID;
  TreeView1->Selected=Node;
  Node->EditText();
}
//---------------------------------------------------------------------------
//�������� ������� �������
void __fastcall TNomenclatureForm::FSubButtonClick(TObject *Sender)
{
TTreeNode *Node=TreeView1->Selected;

  if(Node->Count!=0)
  { Application->MessageBoxA("������ ������� ������, ���������� ����������","�������� �������",MB_OK);
    return;
  }

  TempQuery->Close();
  TempQuery->SQL->Clear();
  TempQuery->SQL->Add("select * from NOMENCLATURE where ID="+IntToStr(Node->StateIndex));
  TempQuery->ExecQuery();
  if(TempQuery->FieldByName("REC_TYPE")->AsInteger==2 || TempQuery->FieldByName("REC_TYPE")->AsInteger==3)
  { MessageDlg("������ ������� ���� ������",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }

  TempQuery->Close();
  TempQuery->SQL->Clear();
  TempQuery->SQL->Add("select * from NOMENCLATURE where FILE_ID="+IntToStr(Node->StateIndex));
  TempQuery->ExecQuery();
  if(TempQuery->RecordCount > 0)
  { MessageDlg("������ ������� ������, ���������� ������",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }

  TempQuery->Close();
  TempQuery->SQL->Clear();
  TempQuery->SQL->Add("delete from NOMENCLATURE where ID="+IntToStr(Node->StateIndex));
  try
  {
    TempQuery->ExecQuery();
  }
  catch(const Exception &exc)
  {
    MessageDlg("������ �������� �������\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    TempQuery->Close();
    return;
  }
  TreeView1->Selected->Delete();
  TempQuery->Close();
}
//---------------------------------------------------------------------------
//����� ������
void __fastcall TNomenclatureForm::DBGridKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  TempQuery->Close();
  TempQuery->SQL->Clear();
  TempQuery->SQL->Add("select * from NOMENCLATURE where ID="+IntToStr(TreeView1->Selected->StateIndex));
  TempQuery->ExecQuery();
  if(TempQuery->RecordCount!=0 && TempQuery->FieldByName("REC_TYPE")->AsInteger==1)
  { if(Key==VK_RETURN) SelRec->Execute();
    else if(Key==VK_ESCAPE) Cancel->Execute();
  }
}
//---------------------------------------------------------------------------
//��� ������ ������ ������
void __fastcall TNomenclatureForm::DBGridDblClick(TObject *Sender)
{
  TempQuery->Close();
  TempQuery->SQL->Clear();
  TempQuery->SQL->Add("select * from NOMENCLATURE where ID="+IntToStr(TreeView1->Selected->StateIndex));
  TempQuery->ExecQuery();
  if(TempQuery->RecordCount!=0 && TempQuery->FieldByName("REC_TYPE")->AsInteger==0) SelRec->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TNomenclatureForm::SelRecExecute(TObject *Sender)
{
  Close();
  ModalResult=mrOk;
}
//---------------------------------------------------------------------------
//���������� ������ ��� ������ ������
void __fastcall TNomenclatureForm::CancelButtonClick(TObject *Sender)
{
  Close();
  ModalResult=mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TNomenclatureForm::TreeView1KeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  if(Key==VK_ESCAPE) Cancel->Execute();
}
//---------------------------------------------------------------------------
//�������� ����� �������������� ������
bool __fastcall TNomenclatureForm::CreateEditForm(void)
{
  try
  {
    ERF=new TEditNomenclatuteForm(this,DataSet->FieldByName("ID")->AsInteger);
  }
  catch (Exception &exc)
  { MessageDlg("������ �������� ����� ��� �������������� ������\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
//�������� ����� ������
void __fastcall TNomenclatureForm::NewButtonClick(TObject *Sender)
{
TTreeNode *Node=TreeView1->Selected;
int ID=0;
AnsiString indexops=Node->Text;
AnsiString iops=indexops.SubString(4,255);
int ops=0;

    if (iops.Trim() == "��")
    {
    ops=0;
    }
    else
    {
    ops = StrToInt(iops);
    }


  StoredProc->Close();
  StoredProc->StoredProcName="NOMENCLATURE_ADD";
  StoredProc->ParamByName("FILE_ID")->AsInteger=Node->StateIndex;
  StoredProc->ParamByName("REC_TYPE")->AsInteger=1;
  StoredProc->ParamByName("DESCRIPTION")->AsString="";
  StoredProc->Prepare();
  try
  {
    StoredProc->ExecProc();
  }
  catch(const Exception &exc)
  {
    MessageDlg("������ ���������� ����� ������ � ������� �������\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  ID=StoredProc->ParamByName("ID")->AsInteger;
  StoredProc->Close();

  TempQuery->Close();
  TempQuery->SQL->Clear();
  TempQuery->SQL->Add("update NOMENCLATURE set EI = '��� ������',CODP = 0,INDEXOPS = " + IntToStr(ops) +" where ID = "+IntToStr(ID));
  TempQuery->ExecQuery();
  TempQuery->Close();

  LoadDataSet();
  TLocateOptions Opt; Opt.Clear();
  if(DataSet->Locate("ID",ID,Opt))
  { if(CreateEditForm())
    { ERF->Caption="������� : �����";
      if(ERF->ShowModal()==mrOk)
      { LoadDataSet();
        DataSet->Locate("ID",ID,Opt);
        SetButtons();
      }
      else DataSet->Delete();
      delete ERF;
    }
    else DataSet->Delete();
  }
  else MessageDlg("������ Locate � ������� ��������",mtError,TMsgDlgButtons() << mbOK,0);
}
//---------------------------------------------------------------------------
//�������������� ������������ ������
void __fastcall TNomenclatureForm::EditRecExecute(TObject *Sender)
{
  if(CreateEditForm())
  { ERF->Caption="�������: "+DataSet->FieldByName("Description")->AsString;
    if(ERF->ShowModal()==mrOk)
    {
      int ID=DataSet->FieldByName("ID")->AsInteger;
      TLocateOptions Opt; Opt.Clear();
      LoadDataSet();
      DataSet->Locate("ID",ID,Opt);
    }
    delete ERF;
  }
}
//---------------------------------------------------------------------------
//�������� ������
void __fastcall TNomenclatureForm::DelButtonClick(TObject *Sender)
{
  if(MessageDlg("�� �������,��� ������ ������� ������ '"+DataSet->FieldByRelName("DESCRIPTION")->AsString+"'?\n<OK> - �������",mtConfirmation,TMsgDlgButtons() << mbOK << mbCancel,0) == mrOk)
  {

  TempQuery->Close();
  TempQuery->SQL->Clear();
  TempQuery->SQL->Add("delete from NOMENCLATURE where ID="+IntToStr(DataSet->FieldByRelName("ID")->AsInteger));
  try
  {
    TempQuery->ExecQuery();
  }
  catch(const Exception &exc)
  {
    MessageDlg("������ �������� �������\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    TempQuery->Close();
    return;
  }
    LoadDataSet();
    SetButtons();
  }
}
//---------------------------------------------------------------------------
//����� ����� ��� ���������� �������
void __fastcall TNomenclatureForm::SortButtonClick(TObject *Sender)
{
TRefSortForm *RSF=NULL;

  try
  {
    RSF=new TRefSortForm(this);
  }
  catch(const Exception &exc)
  {
    MessageDlg("������ �������� ������� RefSortForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(RSF->ShowForm(sortind,Left,Top)==mrOk)
  { int ID=DataSet->FieldByName("ID")->AsInteger;
    if(RSF->RadioButton1->Checked) sortind=1;
    else sortind=2;
    LoadDataSet();
    TLocateOptions Opt; Opt.Clear();
    DataSet->Locate("ID",ID,Opt);
  }
  if(RSF!=NULL) delete RSF;
}



