//---------------------------------------------------------------------------

#include <vcl.h>
#include "Main.h"
#include "DataModule.h"
#include "ImportFrom1C.h"
#pragma hdrstop

#include "ImportDocumentsJournal.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Placemnt"
#pragma link "DBGridEh"
#pragma link "FIBDatabase"
#pragma link "FIBDataSet"
#pragma link "pFIBDatabase"
#pragma link "pFIBDataSet"
#pragma link "RXSpin"
#pragma link "JvComponent"
#pragma link "JvExControls"
#pragma link "JvNavigationPane"
#pragma link "JvDialogs"
#pragma link "JvBaseDlg"
#pragma link "JvSelectDirectory"
#pragma link "FIBQuery"
#pragma link "pFIBQuery"
#pragma resource "*.dfm"
TImportDocumentsJournalForm *ImportDocumentsJournalForm;
//---------------------------------------------------------------------------
//**********
//* public *
//**********
__fastcall TImportDocumentsJournalForm::TImportDocumentsJournalForm(TComponent* Owner)
        : TForm(Owner)
{
  iniFileName=MainForm->getIniFileName();
  FormStorage1->IniFileName=iniFileName;
  FormStorage1->IniSection="ImportDocumentsJournalForm";

  loadProperties();
//  setButtons();
}
//---------------------------------------------------------------------------
void __fastcall TImportDocumentsJournalForm::loadProperties(void)
{
TIniFile *ini=NULL;
TDateTime dt=Date();
unsigned short y,m,d;

  dt.DecodeDate(&y,&m,&d);
  try
  { ini=new TIniFile(iniFileName);
    Year->Value=ini->ReadInteger("ImportDocumentsJournalForm","Year",y);
    Month->ItemIndex=ini->ReadInteger("ImportDocumentsJournalForm","Month",m-1);
    MonthUpDown->Position=Month->ItemIndex+1;
    idOrder=ini->ReadString("ImportDocumentsJournalForm","idOrder","");
    idID=ini->ReadInteger("ImportDocumentsJournalForm","id",1);
    idCol=ini->ReadInteger("ImportDocumentsJournalForm","idCol",1);
    idGrid->Columns->Items[0]->Width=ini->ReadInteger("ImportDocumentsJournalForm","ID_COL0",20);
    idGrid->Columns->Items[1]->Width=ini->ReadInteger("ImportDocumentsJournalForm","ID_COL1",30);
    idGrid->Columns->Items[2]->Width=ini->ReadInteger("ImportDocumentsJournalForm","ID_COL2",300);
    idGrid->Columns->Items[3]->Width=ini->ReadInteger("ImportDocumentsJournalForm","ID_COL3",60);
    delete ini;
  }
  catch(...)
  { if(ini!=NULL) delete ini;
    Year->Value=y;
    Month->ItemIndex=m-1;
    MonthUpDown->Position=m;
  }
  //Восстановление порядка сортировки
  idGrid->SortMarkedColumns->Clear();
  for(int i=0; i<4; i++)
  { if(idGrid->Columns->Items[i]->Title->TitleButton==true)
    { if(idOrder.Pos(idGrid->Columns->Items[i]->FieldName) > 0)
      { int k=idGrid->SortMarkedColumns->Add(idGrid->Columns->Items[i]);
        idGrid->SortMarkedColumns->Items[k]->Title->SortMarker=smUpEh;
      }
    }
  }
  idGrid->Col=idCol;
  lockDate=SaleBookDM->GetConstValue(SaleBookDM->OrganizationID,"LOCK_EDIT_DATE");
}
//---------------------------------------------------------------------------
void __fastcall TImportDocumentsJournalForm::saveProperties(void)
{
TIniFile *ini=NULL;

  try
  { ini=new TIniFile(iniFileName);
    ini->WriteInteger("ImportDocumentsJournalForm","Year",Year->Value);
    ini->WriteInteger("ImportDocumentsJournalForm","Month",Month->ItemIndex);
    ini->WriteString("ImportDocumentsJournalForm","idOrder",idOrder);
    ini->WriteInteger("ImportDocumentsJournalForm","id",idDS->FieldByName("ID")->AsInteger);
    ini->WriteInteger("ImportDocumentsJournalForm","idCol",idGrid->Col);
    ini->WriteInteger("ImportDocumentsJournalForm","ID_COL0",idGrid->Columns->Items[0]->Width);
    ini->WriteInteger("ImportDocumentsJournalForm","ID_COL1",idGrid->Columns->Items[1]->Width);
    ini->WriteInteger("ImportDocumentsJournalForm","ID_COL2",idGrid->Columns->Items[2]->Width);
    ini->WriteInteger("ImportDocumentsJournalForm","ID_COL3",idGrid->Columns->Items[3]->Width);
    delete ini;
  }
  catch(...)
  {
    if(ini!=NULL) delete ini;
  }

}
//---------------------------------------------------------------------------
void __fastcall TImportDocumentsJournalForm::setPeriod(void)
{
  date1=TDateTime((unsigned short)(Year->Value),(unsigned short)Month->ItemIndex+1,1);
  date2=TDateTime((unsigned short)(Year->Value),(unsigned short)Month->ItemIndex+1,SaleBookDM->LastDay((unsigned short)(Year->Value),(unsigned short)Month->ItemIndex+1));
}
//---------------------------------------------------------------------------
void __fastcall TImportDocumentsJournalForm::loadDataSets(void)
{
AnsiString sql;

  sql="select i.* from IMPORT_DOCUMENTS_TABLE i where";
  sql+=" i.ID_DATE >= '"+date1.DateString()+"'";
  sql+=" and i.ID_DATE <= '"+date2.DateString()+"'";
  sql+=idOrder;
  idDS->Close();
  idDS->SQLs->SelectSQL->Clear();
  idDS->SQLs->SelectSQL->Add(sql);
  try
  {
    idDS->Open();
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  idDS->Last();
}
//---------------------------------------------------------------------------
void __fastcall TImportDocumentsJournalForm::setButtons(void)
{
TDateTime dt=TDateTime((unsigned short)(Year->Value),(unsigned short)(Month->ItemIndex+1),1);

  if(dt < lockDate) { AddButton->Enabled=false;ExportButton->Enabled=false;}
  else { AddButton->Enabled=true;ExportButton->Enabled=true; }
  if(idDS->RecordCount==0)
  {
    FirstButton->Enabled=false;
    PriorButton->Enabled=false;
    NextButton->Enabled=false;
    LastButton->Enabled=false;
  }
  else
  {
    FirstButton->Enabled=true;
    PriorButton->Enabled=true;
    NextButton->Enabled=true;
    LastButton->Enabled=true;
  }

}
//---------------------------------------------------------------------------
//*************
//* published *
//*************
void __fastcall TImportDocumentsJournalForm::FormShow(TObject *Sender)
{
  setPeriod();
  loadDataSets();
  idGrid->Visible=true;
  idDS->Locate("ID",idID,TLocateOptions().Clear());
  idGrid->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TImportDocumentsJournalForm::ExitButtonClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TImportDocumentsJournalForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  saveProperties();
  Action=caFree;
}
//---------------------------------------------------------------------------
void __fastcall TImportDocumentsJournalForm::YearChange(TObject *Sender)
{
  setPeriod();
  if(this->Showing==true) loadDataSets();
}
//---------------------------------------------------------------------------
void __fastcall TImportDocumentsJournalForm::MonthChange(TObject *Sender)
{
  MonthUpDown->Position=Month->ItemIndex+1;
  setPeriod();
  if(this->Showing) loadDataSets();
}
//---------------------------------------------------------------------------
void __fastcall TImportDocumentsJournalForm::MonthUpDownClick(
      TObject *Sender, TUDBtnType Button)
{
  if(MonthUpDown->Position > 12 && Button==btNext)
  { Month->ItemIndex=0;
    Year->Value++;
    MonthUpDown->Position=1;
  }
  else if(MonthUpDown->Position < 1 && Button==btPrev)
  { Month->ItemIndex=11;
    Year->Value--;
    MonthUpDown->Position=12;
  }
  else Month->ItemIndex=MonthUpDown->Position-1;
  Month->OnChange(this);
}
//---------------------------------------------------------------------------
void __fastcall TImportDocumentsJournalForm::idSourceDataChange(
      TObject *Sender, TField *Field)
{
  if(this->Showing && idGrid->Visible==true) setButtons();
}
//---------------------------------------------------------------------------
void __fastcall TImportDocumentsJournalForm::idGridSortMarkingChanged(TObject *Sender)
{
int id=idGrid->DataSource->DataSet->FieldByName("ID")->AsInteger;
TLocateOptions lo=TLocateOptions().Clear();
bool firstItem=true;

  idOrder="";
  for(int i=0; i<idGrid->SortMarkedColumns->Count; ++i)
  { for(int j=0; j<7; j++)
    { if(idGrid->Columns->Items[j]->Title->TitleButton==true)
      { if(idGrid->SortMarkedColumns->Items[i]->FieldName==idGrid->Columns->Items[j]->FieldName)
        { if(firstItem==true){ idOrder=" order by "; firstItem=false; }
          else idOrder+=", ";
          if(j==2) idOrder+="t.";
          else if(j==6) idOrder+="u.";
          else idOrder+="i.";
          idOrder+=idGrid->Columns->Items[j]->FieldName;
          idGrid->SortMarkedColumns->Items[i]->Title->SortMarker=smUpEh;
          break;
        }
      }
    }
  }
  loadDataSets();
  idDS->Locate("ID",id,lo);
}
//---------------------------------------------------------------------------
//Выгрузка в файл номеров счет-фактур
void __fastcall TImportDocumentsJournalForm::ExportButtonClick(TObject *Sender)
{
/*AnsiString inFileName=ExtractFileDir(iniFileName)+"\\Export\\Templates\\SFNumber.dbf";
AnsiString outFileName="sf"+idDS->FieldByName("ID_NUMBER")->AsString.Trim()+".dbf";
int inH, outH, fl;
char *buf;

  outFileDialog->FileName=outFileName;
  outFileDialog->InitialDir=ExtractFileDir(iniFileName)+"\\Export\\";
  if(outFileDialog->Execute()==false) return;
  outFileName=outFileDialog->FileName;
  if(outFileName.IsEmpty()) return;
  if(FileExists(outFileName)) DeleteFile(outFileName);
  //Читаем данные о структуре из файла-шаблона
  if(!FileExists(inFileName))
  { MessageDlg("Отсутствует шаблон для файла выгрузки",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if((inH=FileOpen(inFileName,fmOpenRead)) < 0)
  { MessageDlg("Ошибка открытия файла-шаблона",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  fl=FileSeek(inH,0,2);
  FileSeek(inH,0,0);

  //Создаем вспомогательный буфер
  try
  {
    buf=new char[fl+1];
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка создания вспомогательного буфера",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  FileRead(inH, buf, fl);
  FileClose(inH);

  //Пишем данные о структуре в выходной файл
  if((outH=FileCreate(outFileName)) < 0)
  { MessageDlg("Ошибка создания выходного файла",mtError,TMsgDlgButtons() << mbOK,0);
    delete buf;
    return;
  }
  FileWrite(outH,buf,fl);
  FileClose(outH);
  delete buf;

  if(!FileExists(outFileName))
  { MessageDlg("Ошибка создания файла выгрузки",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  //Инициализируем ADO подключение
  AnsiString path=ExtractFilePath(outFileName);
  AnsiString str;
  str="Provider=MSDASQL.1;";
  str+="Persist Security Info=False;";
  str+="Data Source=Файлы dBase;";
  str+="Mode=ReadWrite;";
  str+="Extended Properties=\"DSN=Файлы dBase;";
  str+="DBQ="+path+";";
  str+="DefaultDir="+ExtractFileDir(iniFileName)+";";
  str+="DriverId=533;FIL=dBase 5.0;MaxBufferSize=2048;PageTimeout=5;\";";
  str+="Initial Catalog="+path;
  ADOConnection->ConnectionString=str;
  try
  {
    ADOConnection->Connected=true;
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка инициализации ADO подключения\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  //Переносим данные в dbf файл
  AnsiString dbfFile=ExtractFileName(outFileName);
  int docType=idDS->FieldByName("ID_TYPE")->AsInteger;
  TDateTime docDate=idDS->FieldByName("ID_DATE")->AsDateTime;
  AnsiString docNumber=idDS->FieldByName("ID_NUMBER")->AsString;
  accountsDS->First();
  while(!accountsDS->Eof)
  { if(!accountsDS->FieldByName("INVOICE_NUMBER")->IsNull)
    { int strNumber=accountsDS->FieldByName("IMPORT_DOC_STR_NUMBER")->AsInteger;
      int sfNumber=accountsDS->FieldByName("INVOICE_NUMBER")->AsInteger;
      TDateTime sfDate=accountsDS->FieldByName("INVOICE_DATE")->AsDateTime;
      unsigned short y,m,d;
      sfDate.DecodeDate(&y,&m,&d);
      AnsiString contractor=accountsDS->FieldByName("CUSTOMER")->AsString;
      double summa=accountsDS->FieldByName("COUNT_TOTAL")->AsFloat;
      AnsiString outStr;
      if(sfDate > TDateTime("31.12.2008")) outStr=AnsiString().sprintf("%02d %02d %04d %04d",m,d,sfNumber,y);
      else outStr=AnsiString().sprintf("%02d %04d %04d",m,sfNumber,y);
      Q->Close();
      Q->SQL->Clear();
      AnsiString sql="insert into "+dbfFile+" (DOCTYPE,DOCNUMBER,DOCDATE,STRNUMBER,CONTRACTOR,SUMMA,SFNUMBER) values(";
      sql+=IntToStr(docType)+",";
      sql+="'"+docNumber+"',";
      sql+="'"+docDate.DateString()+"',";
      sql+=IntToStr(strNumber)+",";
      sql+="'"+contractor+"',";
      sql+=AnsiString().sprintf("%.02lf",summa)+",";
      sql+="'"+outStr+"')";
      Q->SQL->Add(sql);
      try
      {
        Q->ExecSQL();
      }
      catch(const Exception &exc)
      { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
        ADOConnection->Connected=false;
        return;
      }
    }
    accountsDS->Next();
  }
  ADOConnection->Connected=false;
  MessageDlg("Операция успешно завершена.\nДанные выгружены в файл \""+outFileName+"\"",mtInformation,TMsgDlgButtons() << mbOK,0);*/
}
//---------------------------------------------------------------------------
//Импорт нового документа из 1С
void __fastcall TImportDocumentsJournalForm::AddButtonClick(
      TObject *Sender)
{
/*TImportFrom1CForm *IF=NULL;

  try
  {
    IF=new TImportFrom1CForm(this);
  }
  catch (Exception &exc)
  { MessageDlg("Ошибка создания формы ImportFrom1CForm\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(IF->ShowModal()==mrOk)
  {
    MessageDlg("Импорт данных успешно завершен",mtInformation,TMsgDlgButtons() << mbOK,0);
    UpDateButton->Click();
  }
  delete IF; */
}
//---------------------------------------------------------------------------
//Обновление данных
void __fastcall TImportDocumentsJournalForm::UpDateButtonClick(TObject *Sender)
{
int id=idDS->FieldByName("ID")->AsInteger;

  loadDataSets();
  idDS->Locate("ID",id,TLocateOptions().Clear());
}
//---------------------------------------------------------------------------
//На первую запись
void __fastcall TImportDocumentsJournalForm::FirstButtonClick(
      TObject *Sender)
{
  idDS->First();
}
//---------------------------------------------------------------------------
//На предыдущую запись
void __fastcall TImportDocumentsJournalForm::PriorButtonClick(
      TObject *Sender)
{
  idDS->Prior();
}
//---------------------------------------------------------------------------
//На следующую запись
void __fastcall TImportDocumentsJournalForm::NextButtonClick(
      TObject *Sender)
{
  idDS->Next();
}
//---------------------------------------------------------------------------
//На последнюю запись
void __fastcall TImportDocumentsJournalForm::LastButtonClick(
      TObject *Sender)
{
  idDS->Last();
}
//---------------------------------------------------------------------------





