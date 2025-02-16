//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <math.h>

#include "DifferentFunctions.h"
#include "Main.h"
#include "LoadDataFrom1C.h"
#include "DBF_File.h"
#include "DataModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "JvComponent"
#pragma link "JvExControls"
#pragma link "JvExMask"
#pragma link "JvExStdCtrls"
#pragma link "JvMemo"
#pragma link "JvToolEdit"
#pragma link "JvXPButtons"
#pragma link "JvXPCore"
#pragma link "Placemnt"
#pragma link "SmrtPanel"
#pragma link "FIBDatabase"
#pragma link "pFIBDatabase"
#pragma link "JvSpeedButton"
#pragma link "ChTreeView"
#pragma link "FIBQuery"
#pragma link "pFIBQuery"
#pragma resource "*.dfm"
//TLoadDataFrom1CForm *LoadDataFrom1CForm;
//---------------------------------------------------------------------------
__fastcall TLoadDataFrom1CForm::TLoadDataFrom1CForm(TComponent* Owner)
        : TForm(Owner)
{

  AnsiString iniFileName=MainForm->WorkDir+"SB_2009.ini";
  FormStorage->IniFileName=iniFileName;
  FormStorage->IniSection="LoadDataFrom1CForm";
  LoadButton->Enabled=false;
  Memo->Clear();
  dbfFile=NULL;
  workDir=ExtractFilePath(iniFileName);
  TIniFile *ini = new TIniFile(iniFileName);
  delete ini;
}
//---------------------------------------------------------------------------
//
void __fastcall TLoadDataFrom1CForm::CancelButtonClick(TObject *Sender)
{
  Close();
  ModalResult=mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TLoadDataFrom1CForm::FilenameEditAfterDialog(
      TObject *Sender, AnsiString &Name, bool &Action)
{
CancelButton->Enabled=false;

  if(Action==false) return;
  FileName=ExtractFileName(Name);
  if (FileName.Trim() != "DOVOST.DBF")
  {
    MessageDlg("�� ��� ���� �����!!!\n",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }

  if(dbfFile!=NULL) delete dbfFile;
  AnsiString path=ExtractFilePath(Name);

  AnsiString nf=Name;
  dbfFile=new DBF_File(nf);
    if(dbfFile->SuccessFLG)
    {
      Memo->Lines->Add("DBF ���� dovost.dbf ������� ������!");
      Memo->Lines->Add("��� ����� - "+IntToStr(unsigned(dbfFile->FH.FileTyp)));
      Memo->Lines->Add("��� - "+IntToStr(unsigned(dbfFile->FH.Year)+2000));
      Memo->Lines->Add("����� - "+IntToStr(unsigned(dbfFile->FH.Mon)));
      Memo->Lines->Add("���� - "+IntToStr(unsigned(dbfFile->FH.Day)));
      Memo->Lines->Add("���������� ������� - "+IntToStr(dbfFile->FH.RecordQuantity));
      Memo->Lines->Add("����� ��������� - "+IntToStr(dbfFile->FH.HeadLength));
      Memo->Lines->Add("����� ������ - "+IntToStr(dbfFile->FH.RecordLength));
      LoadButton->Enabled=true;
    }
    else
    {
    Memo->Lines->Add("������ �������� DBF �����!");
    LoadButton->Enabled=false;
    }

CancelButton->Enabled=true;
}
//---------------------------------------------------------------------------

//�������� ������
void __fastcall TLoadDataFrom1CForm::LoadButtonClick(TObject *Sender)
{
AnsiString sql,str,lchet1;
int metka1=0;
countzap=0;
int countneop=0;
CancelButton->Enabled=false;
int koduser=0;
TpFIBDataSet *DS;
DS=SaleBookDM->NDOST;
int countdubl=0;

// ������ �������
  //�������� ����������
  TQ->Transaction->StartTransaction();
for(int i=1; i<=dbfFile->FH.RecordQuantity; ++i)
{
int lchet=0;
int kod=0;
koduser=0;
metka1=0;

      if(dbfFile->RecordRead(i)==true)
      {
      if (!dbfFile->FieldToAnsiString(1).IsEmpty()) kod =StrToInt(dbfFile->FieldToAnsiString(1));
      if (!dbfFile->FieldToAnsiString(2).IsEmpty()) lchet =StrToInt(dbfFile->FieldToAnsiString(2));
      }

// if (TempQuery->RecordCount>0)
// {
      DS->Close();
      DS->SQLs->SelectSQL->Clear();
      sql="select * from NDOST where LCHET = " + IntToStr(lchet);
      DS->SQLs->SelectSQL->Add(sql);
      try
      {
      DS->Open();
      }
      catch(const Exception &exc)
      {
        MessageDlg("������ - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
        return;
      }

      DS->First();
      lchet1=DS->FieldByName("LCHET1")->AsString.Trim();
      metka1=DS->FieldByName("METKA1")->AsInteger;

    if (!lchet1.IsEmpty())
    {
      TempQuery->Close();
      TempQuery->SQL->Clear();
      sql="select * from users where id <> 1 and u_index containing " +IntToStr(metka1);
      TempQuery->SQL->Add(sql);
      try
      {
       TempQuery->ExecQuery();
      }
      catch(const Exception &exc)
      {
        MessageDlg("������ - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      }

      koduser=TempQuery->FieldByName("ID")->AsInteger;

      TempQuery->Close();
      TempQuery->SQL->Clear();
      sql="select * from DOV where LCHET = " + IntToStr(lchet);
      TempQuery->SQL->Add(sql);
      try
      {
       TempQuery->ExecQuery();
      }
      catch(const Exception &exc)
      {
        MessageDlg("������ - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      }

      if (TempQuery->RecordCount == 0)
      {
      TQ->Close();
      TQ->SQL->Clear();
      sql="insert into DOV(USER_ID,LCHET,FAMILY,NAME,\
      FATHER,SERIA,NOMER,DOST,ULIC,ADRES,METKA1)";
      sql+=" values(";
      sql+=IntToStr(koduser)+",";
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
      TQ->SQL->Add(sql);
      try
      {
        TQ->ExecQuery();
      }
      catch (Exception &exc)
      {
        MessageDlg("������ - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
        TQ->Transaction->Rollback();
        return;
      }
      countzap++;
      }else
      {
      countdubl++;
      }
    }
    else
    {
      countneop++;
    }
// }else
// {
// countneop++;
// }
}

  TQ->Transaction->Commit();
  DS->Close();
  str="��������� �� dovost.dbf - " + IntToStr(dbfFile->FH.RecordQuantity) + " ������� ";
  Memo->Lines->Add(str);
  str="�� ��� ������������� ������� � ���� �� dovost.dbf - " + IntToStr(countzap) + " ������� ";
  Memo->Lines->Add(str);
  str="�� ��� ��� ���� � ������ �� ������������� - " + IntToStr(countdubl) + " ������� ";
  Memo->Lines->Add(str);
  str="�� ��� ���������� � ��������������� � ���� �� dovost.dbf - " + IntToStr(countneop) + " ������� ";
  Memo->Lines->Add(str);
  MessageDlg("�������� ���������!",mtInformation,TMsgDlgButtons() << mbOK,0);
}
//---------------------------------------------------------------------------
//������ ��������� ��������
void __fastcall TLoadDataFrom1CForm::PrintButtonClick(TObject *Sender)
{
  Memo->Print("�������� �������� ������ �� ����� - "+FilenameEdit->Text);
}
//---------------------------------------------------------------------------

