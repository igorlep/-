//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AdjustConnection.h"
#include "SelectBase.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "JvAnimTitle"
#pragma link "JvComponent"
#pragma link "SmrtPanel"
#pragma link "Placemnt"
#pragma link "FIBDatabase"
#pragma link "pFIBDatabase"
#pragma link "JvExControls"
#pragma link "JvNavigationPane"
#pragma link "JvXPButtons"
#pragma link "JvXPCore"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TSelectBaseForm::TSelectBaseForm(TComponent* Owner)
        : TForm(Owner)
{
  WorkDir=ExtractFilePath(Application->ExeName);
  FormStorage1->IniFileName=WorkDir+"SB_2009.ini";
  FormStorage1->IniSection="SelectBaseForm";

  DBNames=new TStringList;
  TIniFile *ini = new TIniFile(WorkDir+"SB_2009.ini");
  DBIndex=ini->ReadInteger("EntryParams","DBIndex",0);
  delete ini;
  EditFLG=false;
  ACF=NULL;
}
//---------------------------------------------------------------------------
void __fastcall TSelectBaseForm::FormShow(TObject *Sender)
{
  LoadDBNamesList();
  if(DBNamesBox->Items->Count > DBIndex) DBNamesBox->ItemIndex=DBIndex;
  else DBNamesBox->ItemIndex=0;
  DBNamesBox->OnClick(this);
  TIniFile *ini = new TIniFile(WorkDir+"SB_2009.ini");
  if(ini->SectionExists("EAR"))
  {
    AddButton->Enabled=true;
    EditButton->Enabled=true;
    DelButton->Enabled=true;
  }else
  {
    AddButton->Enabled=false;
    EditButton->Enabled=false;
    DelButton->Enabled=false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TSelectBaseForm::FormDestroy(TObject *Sender)
{
  if(DataBase->Connected) DataBase->Connected=false;
  if(EditFLG)
  { TIniFile *ini = new TIniFile(WorkDir+"SB_2009.ini");
    if(ini->SectionExists("DBAliases")) ini->EraseSection("DBAliases");
    if(DBNames->Count>0)
    { for(int i=0; i<DBNames->Count; ++i)
      { AnsiString str=DBNames->Strings[i];
        AnsiString DBAlias=str.SubString(1,str.Pos("=")-1);
        AnsiString DBName=str.SubString(str.Pos("=")+1,str.Length());
        ini->WriteString("DBAliases",DBAlias,DBName);
      }
    }
    delete ini;
  }
  delete DBNames;
}
//---------------------------------------------------------------------------
void __fastcall TSelectBaseForm::LoadDBNamesList(void)
{
  DBNamesBox->Clear();
  DBNames->Clear();
  TIniFile *ini = new TIniFile(WorkDir+"SB_2009.ini");
  ini->ReadSection("DBAliases",DBNamesBox->Items);
  ini->ReadSectionValues("DBAliases",DBNames);
  delete ini;
}
//---------------------------------------------------------------------------
void __fastcall TSelectBaseForm::DBNamesBoxClick(TObject *Sender)
{
AnsiString DBName;

  Label3->Caption="";
  if(DBNames->Count > 0)
  { DBName=DBNames->Strings[DBNamesBox->ItemIndex];
    Label3->Caption="  "+DBName.SubString(DBName.Pos("=")+1,DBName.Length());
  }
  ConnectButton->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TSelectBaseForm::EditButtonClick(TObject *Sender)
{
  try
  {
    ACF=new TAdjustConnectionForm(this);
  }
  catch(Exception &exception)
  { Application->ShowException(&exception);
    return;
  }
  AnsiString DBName=DBNames->Strings[DBNamesBox->ItemIndex];
  int p1=DBName.Pos("="),p2;
  AnsiString Alias=DBName.SubString(1,p1-1);
  AnsiString Server="";
  if(DBName.Pos("\\\\")!=0)
  { p2=DBName.Pos("\\\\");
    Server=DBName.SubString(p1+1,p2-p1-1);
    ACF->ComboBox1->ItemIndex=1;
    p2+=2;
  }
  else if(DBName.Pos("@")!=0)
  { p2=DBName.Pos("@");
    Server=DBName.SubString(p1+1,p2-p1-1);
    ACF->ComboBox1->ItemIndex=2;
    p2+=1;
  }
  else
  { p2=DBName.Pos(":");
    Server=DBName.SubString(p1+1,p2-p1-1);
    ACF->ComboBox1->ItemIndex=0;
    p2+=1;
  }
  int p3=DBName.Pos(",");
  AnsiString DBPath=DBName.SubString(p2,p3-p2);
  AnsiString DBLogPass=DBName.SubString(p3+1,DBName.Length());
  int p4=DBLogPass.Pos(",");
  AnsiString DBLog=DBLogPass.SubString(1,p4-1);
  AnsiString DBPass=DBLogPass.SubString(p4+1,DBLogPass.Length());

  if(DBName.UpperCase().Pos("LOCALHOST")!=0)
    ACF->RadioButton1->Checked=true;
  else
    ACF->RadioButton2->Checked=true;
  ACF->Edit1->Text=Server;
  ACF->Edit2->Text=DBPath;
  ACF->Edit3->Text=Alias;
  ACF->Edit4->Text=DBLog;
  ACF->Edit5->Text=DBPass;
  if(ACF->ShowModal()==mrOk) SaveDBNameToList(false);
  delete ACF;
}
//---------------------------------------------------------------------------
bool __fastcall TSelectBaseForm::SaveDBNameToList(bool AddFLG)
{
/*  if(ACF->Edit1->Text=="")
  { MessageDlg("Не указан псевдоним базы данных",mtConfirmation,TMsgDlgButtons() << mbOK,0);
    return;
  }
  AnsiString DBName=ACF->Edit3->Text+"=";
  DBName+=ACF->Edit1->Text;
  if(ACF->ComboBox1->Text=="TCP") DBName+=":";
//  else if(ACF->ComboBox1->Text=="NamedPipe") DBName+="\\\\";
//  else if(ACF->ComboBox1->Text=="SPX")  DBName+="@";
  DBName+=ACF->Edit2->Text;
  DBName+=",";
  DBName+=ACF->Edit4->Text;
  DBName+=",";
  DBName+=ACF->Edit5->Text;
  int i;
  for(i=0; i<DBNames->Count; ++i)
    if(DBName==DBNames->Strings[i]) break;
  if(i<DBNames->Count)
    MessageDlg("В списке уже имеется псевдоним с выбранными параметрами подключения",mtConfirmation,TMsgDlgButtons() << mbOK,0);
  else
  { if(!AddFLG)
    { DBNames->Delete(DBNamesBox->ItemIndex);
      DBNamesBox->Items->Delete(DBNamesBox->ItemIndex);
    }
    DBNamesBox->Items->Add(ACF->Edit3->Text);
    DBNames->Add(DBName);
    EditFLG=true;
  }
*/
  if(ACF==NULL) return false;
  if(ACF->Edit3->Text.IsEmpty())
  { MessageDlg("Не указан псевдоним базы данных",mtConfirmation,TMsgDlgButtons() << mbOK,0);
    return false;
  }
  if(ACF->Edit4->Text.IsEmpty())
  {
    MessageDlg("Не указан имя пользователя с правами администратора базы данных",mtConfirmation,TMsgDlgButtons() << mbOK,0);
    return false;
  }
  if(ACF->Edit5->Text.IsEmpty())
  {
    MessageDlg("Не указан пароль пользователя с правами администратора базы данных",mtConfirmation,TMsgDlgButtons() << mbOK,0);
    return false;
  }
  if(ACF->Edit1->Text.IsEmpty())
  { MessageDlg("Не указано сетевое имя сервера или его IP адрес",mtConfirmation,TMsgDlgButtons() << mbOK,0);
    return false;
  }
  AnsiString DBName=ACF->Edit3->Text+"=";
  DBName+=ACF->Edit1->Text;
  if(ACF->ComboBox1->Text=="TCP") DBName+=":";
  else if(ACF->ComboBox1->Text=="NamedPipe") DBName+="\\\\";
  else if(ACF->ComboBox1->Text=="SPX")  DBName+="@";
  DBName+=ACF->Edit2->Text;
  DBName+=",";
  DBName+=ACF->Edit4->Text;
  DBName+=",";
  DBName+=ACF->Edit5->Text;
  int i;
  for(i=0; i<DBNames->Count; ++i)
    if(DBName==DBNames->Strings[i]) break;
  if(i<DBNames->Count)
  { MessageDlg("В списке уже имеется псевдоним с выбранными параметрами подключения",mtConfirmation,TMsgDlgButtons() << mbOK,0);
    return false;
  }
  else
  { if(!AddFLG)
    { DBNames->Delete(DBNamesBox->ItemIndex);
      DBNamesBox->Items->Delete(DBNamesBox->ItemIndex);
    }
    DBNamesBox->Items->Add(ACF->Edit3->Text);
    DBNames->Add(DBName);
    EditFLG=true;
    return true;
  }

}
//---------------------------------------------------------------------------
void __fastcall TSelectBaseForm::AddButtonClick(TObject *Sender)
{
  try
  {
    ACF=new TAdjustConnectionForm(this);
  }
  catch(Exception &exception)
  { Application->ShowException(&exception);
    return;
  }
  ACF->RadioButton1->Checked=true;
  ACF->Edit2->Text="";
  if(ACF->ShowModal()==mrOk) SaveDBNameToList(true);
  delete ACF;
}
//---------------------------------------------------------------------------
void __fastcall TSelectBaseForm::DelButtonClick(TObject *Sender)
{
  if(MessageDlg("Вы действительно хотите удалить текущий псевдоним базы данных?",mtConfirmation,TMsgDlgButtons() << mbOK << mbCancel,0)==mrCancel)
    return;
  int i=DBNamesBox->ItemIndex;
  DBNamesBox->Items->Delete(i);
  DBNames->Delete(i);
  DBNamesBox->SetFocus();
  EditFLG=true;
}
//---------------------------------------------------------------------------
void __fastcall TSelectBaseForm::ConnectButtonClick(TObject *Sender)
{
  if(DataBase->Connected) DataBase->Connected=false;
  //Пробуем подключиться к выбранной базе
  AnsiString DBName=DBNames->Strings[DBNamesBox->ItemIndex];
  DataBase->AliasName=DBName.SubString(0,DBName.Pos("=")-1);

  int p3=DBName.Pos(",");
  int p2=DBName.Pos(":");
  int p1=DBName.Pos("=");

  AnsiString Server=DBName.SubString(p1+1,p2-p1-1);
  p2+=1;
  AnsiString DBPath=DBName.SubString(p2,p3-p2);
  AnsiString DBLogPass=DBName.SubString(p3+1,DBName.Length());
  int p4=DBLogPass.Pos(",");
  AnsiString DBLog=DBLogPass.SubString(1,p4-1);
  AnsiString DBPass=DBLogPass.SubString(p4+1,DBLogPass.Length());

  DataBase->DBName=Server+":"+DBPath;
  DataBase->ConnectParams->UserName=DBLog;
  DataBase->ConnectParams->Password=DBPass;
  DataBase->ConnectParams->CharSet="WIN1251";
  DataBase->SQLDialect=3;

  try
  {
    DataBase->Connected=true;
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка подключения к базе - "+DataBase->DBName+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  TIniFile *ini = new TIniFile(WorkDir+"SB_2009.ini");
  ini->WriteInteger("EntryParams","DBIndex",DBNamesBox->ItemIndex);
  delete ini;

  Close();
  ModalResult=mrOk;
}
//---------------------------------------------------------------------------

