//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Entry.h"
#include "DataModule.h"
#include "Nomenclature.h"
#include "EI.h"
#include "Organizations.h"
#include "HelpAbout.h"
#include "AccauntsJournal.h"
#include "OrganizationSelect.h"
#include "Users.h"
#include "UsersMonitor.h"
#include "BackUpBase.h"
#include "RestoreBase.h"
#include "ActionsJournal.h"
#include "ImportDocumentsJournal.h"
#include "Main.h"
#include "BrowseF.h"
#include "ImportFrom1C.h"
#include "ActsList.h"
#include "LoadDataFrom1C.h"
#include "UnitProv.h"
#include "LockDateChecker.h"
#include "EID.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Placemnt"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
  MainForm->Constraints->MaxWidth=Screen->Width;
//  MainForm->Left=0;
//  MainForm->Top=0;
  WorkDir=ExtractFilePath(Application->ExeName);
  iniFileName=ExtractFilePath(Application->ExeName)+"SB_2009.ini";
  MainFormStorage->IniFileName=iniFileName;
  MainFormStorage->IniSection="MainForm";

  TRegistry *Reg;
  fontDPI=96;
  try
  {
    Reg=new TRegistry(KEY_READ);
  }
  catch (Exception &exc)
  { MessageDlg("������ �������� ������� TRegistry\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  try
  { Reg->RootKey = HKEY_LOCAL_MACHINE;
    if (Reg->OpenKey("\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\FontDPI",false))
    {
      fontDPI=Reg->ReadInteger("LogPixels");
      Reg->CloseKey();
    }
  }
  __finally
  {
    delete Reg;
  }

  try
  {
    Reg=new TRegistry(KEY_WRITE);
  }
  catch (Exception &exc)
  { MessageDlg("������ �������� ������� TRegistry\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  try
  { Reg->RootKey = HKEY_CURRENT_USER;
    if (Reg->OpenKey("\\Control Panel\\International\\",true))
    { Reg->WriteString("sDecimal",".");
      Reg->CloseKey();
    }
  }
  __finally
  {
    delete Reg;
  }

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    DecimalSeparator='.';
    DateSeparator='.';
    ShortDateFormat="dd.mm.yyyy";
    ShortTimeFormat="hh:mm:ss";
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
double ff=double(fontDPI)/double(96);

  SetButtons();

  AnsiString s=MainStatusBar->Panels->Items[0]->Text;
  MainStatusBar->Panels->Items[0]->Width=s.Length()*ff*8;
  s=MainStatusBar->Panels->Items[1]->Text;
  MainStatusBar->Panels->Items[1]->Width=s.Length()*ff*15;
  s=MainStatusBar->Panels->Items[1]->Text;
  MainStatusBar->Panels->Items[2]->Width=s.Length()*ff*20;
  s=MainStatusBar->Panels->Items[2]->Text;
  if(SaleBookDM->UserRole!="�������������" && SaleBookDM->UserRole!="������������")
  {
  MainStatusBar->Panels->Items[3]->Width=0;
  }else
  {
  MainStatusBar->Panels->Items[3]->Width=s.Length()*ff*10;
  s=MainStatusBar->Panels->Items[3]->Text;
  }
  MainStatusBar->Panels->Items[4]->Width=s.Length()*ff*5;
  s=MainStatusBar->Panels->Items[4]->Text;
  int w=MainStatusBar->Panels->Items[0]->Width+MainStatusBar->Panels->Items[1]->Width+MainStatusBar->Panels->Items[2]->Width+MainStatusBar->Panels->Items[3]->Width+MainStatusBar->Panels->Items[4]->Width;
  if(SaleBookDM->UserRole!="�������������" && SaleBookDM->UserRole!="������������")
    MainForm->Constraints->MinWidth=w+s.Length()*ff*10;
  else
  {
    if(w<430) w=330;
    MainForm->Constraints->MinWidth=w;
  }
  if(fontDPI==96) MainForm->Constraints->MaxHeight=120;
  else MainForm->Constraints->MaxHeight=120;
  Height=MainForm->Constraints->MaxHeight;
  ExitButton->Left=Width-40;
  messagesTimer->Enabled=false;
  messagesTimer->Interval=1000;
  messagesTimer->Enabled=true;

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SetButtons(void)
{
  if(SaleBookDM->UserRole=="�������������")
  {
    N4->Visible=true;
    N27->Visible=true;
  }
  else
  {
    N4->Visible=false;
    if(SaleBookDM->UserRole=="������������")
    {
     N27->Visible=true;
    }
    else
    {
     N27->Visible=false;
    }
  }
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::SetMainStatusBar(AnsiString lockDate)
{
int currentLED;

  if(SaleBookDM->UserRole=="�������������")
    MainStatusBar->Panels->Items[3]->Text="���� ������� �������: "+lockDate;
  else MainStatusBar->Panels->Items[3]->Text="";

  AnsiString led=SaleBookDM->GetConstValue(SaleBookDM->OrganizationID,"LOCK_WORK_DATE");
  if(!led.IsEmpty()) currentLED=StrToInt(led);
  else currentLED=0;

  if(currentLED==1){
    MainStatusBar->Panels->Items[4]->Text="���� �������!!! ";
    MainStatusBar->Color=clRed;
    }
  else
  {
  MainStatusBar->Panels->Items[4]->Text="���� �������!!!";
  MainStatusBar->Color=clWindow;
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ExitButtonClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N7Click(TObject *Sender)
{
  if(!Application->FindComponent("NomenclatureForm"))
  { try
    {
      Application->CreateForm(__classid(TNomenclatureForm), &NomenclatureForm);
    }
    catch (Exception &exc)
    { MessageDlg("������ �������� ����� EIForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
  }
  NomenclatureForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N9Click(TObject *Sender)
{
  if(!Application->FindComponent("EIForm"))
  {
    try
    {
      Application->CreateForm(__classid(TEIForm), &EIForm);
    }
    catch (Exception &exc)
    { MessageDlg("������ �������� ����� EIForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
  }
  EIForm->Show();
}
//---------------------------------------------------------------------------
//�������� �� �����������
void __fastcall TMainForm::N19Click(TObject *Sender)
{
  if(!Application->FindComponent("OrganizationsForm"))
  { try
    {
      Application->CreateForm(__classid(TOrganizationsForm), &OrganizationsForm);
    }
    catch (Exception &exc)
    { MessageDlg("������ �������� ����� OrganizationsForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
  }
  OrganizationsForm->Show();
}
//---------------------------------------------------------------------------
//����� ������������
void __fastcall TMainForm::N18Click(TObject *Sender)
{
THelpAboutForm *HF;

  try
  {
    HF=new THelpAboutForm(this);
  }
  catch (Exception &exc)
  { MessageDlg("������ �������� ����� HelpAboutForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  HF->ShowModal();
  delete HF;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N10Click(TObject *Sender)
{
  if(!Application->FindComponent("AccountsJournalForm"))
  { try
    {
      Application->CreateForm(__classid(TAccountsJournalForm), &AccountsJournalForm);
    }
    catch (Exception &exc)
    { MessageDlg("������ �������� ����� AccountsJournalForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
  }
  AccountsJournalForm->Show();
}
//---------------------------------------------------------------------------
//����� �����������
void __fastcall TMainForm::N20Click(TObject *Sender)
{
TOrganizationSelectForm *OSF;

  try
  {
    OSF=new TOrganizationSelectForm(this, SaleBookDM->OrganizationID);
  }
  catch (Exception &exc)
  { MessageDlg("������ �������� ����� OrganizationSelectForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(OSF->ShowModal()==mrOk)
  { int orgID=OSF->OrgDS->FieldByName("ID")->AsInteger;
    SaleBookDM->DisConnectDataBase();
    TIniFile *ini=new TIniFile(MainForm->WorkDir+"SB_2009.ini");
    ini->WriteInteger("EntryParams", "OrganizationID",orgID);
    delete ini;
    SaleBookDM->OrganizationID=orgID;
    SaleBookDM->ConnectToDataBase();
  }
  delete OSF;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N15Click(TObject *Sender)
{
TUsersForm *UF;

  try
  {
    UF=new TUsersForm(this);
  }
  catch (Exception &exc)
  { MessageDlg("������ �������� ����� UsersForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  UF->ShowModal();
  delete UF;
}
//---------------------------------------------------------------------------
//������� �������������
void __fastcall TMainForm::N16Click(TObject *Sender)
{
  if(!Application->FindComponent("UsersMonitorForm"))
  { try
    {
      Application->CreateForm(__classid(TUsersMonitorForm), &UsersMonitorForm);
    }
    catch (Exception &exc)
    { MessageDlg("������ �������� ����� UsersMonitorForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
  }
  UsersMonitorForm->Show();
}
//---------------------------------------------------------------------------
//������������� ����
void __fastcall TMainForm::N21Click(TObject *Sender)
{
TBackUpBaseForm *BBF;

  try
  {
    BBF=new TBackUpBaseForm(this);
  }
  catch (Exception &exc)
  { MessageDlg("������ �������� ����� BackUpBaseForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  BBF->ShowModal();
  delete BBF;
}
//---------------------------------------------------------------------------
//�������������� ���� �� ������
void __fastcall TMainForm::N22Click(TObject *Sender)
{
TRestoreBaseForm *RBF;

  try
  {
    RBF=new TRestoreBaseForm(this);
  }
  catch (Exception &exc)
  { MessageDlg("������ �������� ����� RestoreBaseForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  RBF->ShowModal();
  delete RBF;
}
//---------------------------------------------------------------------------
//������ �������
void __fastcall TMainForm::N23Click(TObject *Sender)
{
  if(!Application->FindComponent("ActionsJournalForm"))
  { try
    {
      Application->CreateForm(__classid(TActionsJournalForm), &ActionsJournalForm);
    }
    catch (Exception &exc)
    { MessageDlg("������ �������� ����� RestoreBaseForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
  }
  ActionsJournalForm->Show();
}
//---------------------------------------------------------------------------
//���������� �����������
void __fastcall TMainForm::N24Click(TObject *Sender)
{
  SaleBookDM->ConnectToDataBase();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N110Click(TObject *Sender)
{
TImportFrom1CForm *IF=NULL;

  try
  {
    IF=new TImportFrom1CForm(this);
  }
  catch (Exception &exc)
  { MessageDlg("������ �������� ����� ImportFrom1CForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(IF->ShowModal()==mrOk)
  {
  IF->LoadButton->Enabled=false;
  }
  delete IF;
}

void __fastcall TMainForm::N14Click(TObject *Sender)
{

  if(!Application->FindComponent("BrowseForm"))
  {
    try
    {
      Application->CreateForm(__classid(TBrowseForm), &BrowseForm);
    }
    catch (Exception &exc)
    { MessageDlg("������ �������� ����� BrowseForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
  }
  BrowseForm->Show();
  BrowseForm->flag=0;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SpeedButton5Click(TObject *Sender)
{
  if(!Application->FindComponent("BrowseForm"))
  { try
    {
      Application->CreateForm(__classid(TBrowseForm), &BrowseForm);
    }
    catch (Exception &exc)
    { MessageDlg("������ �������� ����� BrowseForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
  }
  BrowseForm->Show();
  BrowseForm->flag=0;

}
//---------------------------------------------------------------------------


void __fastcall TMainForm::N17Click(TObject *Sender)
{
  if(!Application->FindComponent("ImportDocumentsJournalForm"))
  { try
    {
      Application->CreateForm(__classid(TImportDocumentsJournalForm), &ImportDocumentsJournalForm);
    }
    catch (Exception &exc)
    { MessageDlg("������ �������� ����� ImportDocumentsJournalForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
  }
  ImportDocumentsJournalForm->Show();

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SpeedButton2Click(TObject *Sender)
{
  if(!Application->FindComponent("ActsListForm"))
  { try
    {
      Application->CreateForm(__classid(TActsListForm), &ActsListForm);
    }
    catch (Exception &exc)
    { MessageDlg("������ �������� ����� ActsListForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
  }
  ActsListForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N8Click(TObject *Sender)
{
  if(!Application->FindComponent("ActsListForm"))
  { try
    {
      Application->CreateForm(__classid(TActsListForm), &ActsListForm);
    }
    catch (Exception &exc)
    { MessageDlg("������ �������� ����� ActsListForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
  }
  ActsListForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N3Click(TObject *Sender)
{
TLoadDataFrom1CForm *LDF;

  try
  {
    LDF=new TLoadDataFrom1CForm(this);
  }
  catch(const Exception &exc)
  {
    MessageDlg("������ �������� ������� TLoadDataFrom1CForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(LDF->ShowModal()==mrOk)
  {
  }
  delete LDF;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::messagesTimerTimer(TObject *Sender)
{
TpFIBQuery *Q=SaleBookDM->TempQuery;
AnsiString mes,sql;

  mes="";
  messagesTimer->Enabled=false;
  Q->Close();
  Q->SQL->Clear();
  sql="select * from SENDED_MESSAGES_TABLE";
  sql+=" where U_ID="+IntToStr(SaleBookDM->UserID);

  Q->SQL->Add(sql);
  try
  {
    Q->ExecQuery();;
  }
  catch(const Exception &exc)
  {
    MessageDlg("������ - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }

 if(!Q->FieldByName("MES_DATA")->IsNull)
 {
   if(MainForm->WindowState==wsMinimized)
   {
     ShowWindow(MainForm->Handle,SW_RESTORE);
     MainForm->Show();
   }
   mes+=Q->FieldByName("MES_DATA")->AsString.Trim();
   MessageDlg(mes,mtWarning,TMsgDlgButtons() << mbOK,0);

   Q->Close();
   Q->SQL->Clear();
   sql="delete from SENDED_MESSAGES_TABLE";
   sql+=" where U_ID="+IntToStr(SaleBookDM->UserID);

   Q->SQL->Add(sql);
   try
   {
    Q->ExecQuery();;
   }
   catch(const Exception &exc)
   {
    MessageDlg("������ - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
   }
 }

messagesTimer->Enabled=true;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N26Click(TObject *Sender)
{
TFormProv *IP=NULL;

  try
  {
    IP=new TFormProv(this);
  }
  catch (Exception &exc)
  {
    MessageDlg("������ �������� ����� FormProv\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(IP->ShowModal()==mrOk)
  {
  IP->LoadButton->Enabled=false;
  }
  delete IP;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N30Click(TObject *Sender)
{

  SaleBookDM->SetConstValue(SaleBookDM->OrganizationID,"LOCK_WORK_DATE","1");
  MessageDlg("�� �������!!!",mtError,TMsgDlgButtons() << mbOK,0);
  MainStatusBar->Panels->Items[4]->Text="���� �������!!! ";
  MainStatusBar->Color=clRed;
  SaleBookDM->ConnectToDataBase();

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N31Click(TObject *Sender)
{
  SaleBookDM->SetConstValue(SaleBookDM->OrganizationID,"LOCK_WORK_DATE","0");
  MessageDlg("�� �������!!!",mtError,TMsgDlgButtons() << mbOK,0);
  MainStatusBar->Panels->Items[4]->Text="���� �������!!! ";
  MainStatusBar->Color=clWindow;
  SaleBookDM->ConnectToDataBase();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N32Click(TObject *Sender)
{
TpFIBQuery *Q=SaleBookDM->TempQuery;
AnsiString sql;

   Q->Close();
   Q->SQL->Clear();
   sql="update ACCOUNTS set EDIT_KEY=1 where";
   sql+=" EDIT_KEY=0";

   Q->SQL->Add(sql);
   try
   {
    Q->ExecQuery();;
   }
   catch(const Exception &exc)
   {
    MessageDlg("������ - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
   }
   MessageDlg("��� ������� ��������������!!!\n",mtConfirmation,TMsgDlgButtons() << mbOK,0);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N33Click(TObject *Sender)
{
  if(!Application->FindComponent("EIDForm"))
  {
    try
    {
      Application->CreateForm(__classid(TEIDForm), &EIDForm);
    }
    catch (Exception &exc)
    { MessageDlg("������ �������� ����� EIDForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
  }
  EIDForm->Show();
}
//---------------------------------------------------------------------------

