//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <math.h>
#include<stdio.h>
#include<time.h>
#include<DateUtils.hpp>
#include<io.h>

#include "Main.h"
#include "AccauntsJournal.h"
#include "DataModule.h"
#include "utils.h"
#include "PrntData.h"
#include "DifferentFunctions.h"
#include "Propis.h"
#include "SMTPMessage.h"
#include <ComObj.hpp>
#include <sysvari.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FIBDataSet"
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma link "pFIBDataSet"
#pragma link "Placemnt"
#pragma link "RXSpin"
#pragma link "SmrtPanel"
#pragma link "frxExportXLS"
#pragma link "FIBDatabase"
#pragma link "pFIBDatabase"
#pragma link "DBGridEh"
#pragma link "JvComponent"
#pragma link "JvExControls"
#pragma link "JvNavigationPane"
#pragma link "JvXPButtons"
#pragma link "JvXPCore"
#pragma link "kbmMemTable"
#pragma link "JvExMask"
#pragma link "JvSpin"

#pragma link "frxExportRTF"
#pragma link "FIBQuery"
#pragma link "pFIBQuery"
#pragma link "ZipBuilder"
#pragma link "CGAUGES"
#pragma link "pFIBStoredProc"
#pragma resource "*.dfm"
TPrntDataForm *PrntDataForm;
//---------------------------------------------------------------------------
__fastcall TPrntDataForm::TPrntDataForm(TComponent* Owner)
        : TForm(Owner)
{
  iniFileName=MainForm->WorkDir+"SB_2009.ini";
  if(!DirectoryExists(MainForm->WorkDir+"Send\\")) CreateDir(MainForm->WorkDir+"Send\\");

  if(AccountsJournalForm->AccountsGrid->SelectedRows->Count==0)
    AccountsJournalForm->AccountsGrid->Selection->Rows->CurrentRowSelected=true;

  MemTable1->EmptyTable();
  MemTable1->Open();
  forLeaderTable->EmptyTable();
  forLeaderTable->Open();
  forLeaderTableEditFLG=false;
  forBookTable->EmptyTable();
  forBookTable->Open();
  forBookTableEditFLG=false;
  TDateTime dt=TDateTime(int(AccountsJournalForm->Year->Value),AccountsJournalForm->MonthUpDown->Position,SaleBookDM->LastDay(int(AccountsJournalForm->Year->Value),AccountsJournalForm->MonthUpDown->Position));
  if(dt < TDateTime("01.10.2209"))
  {
    TIniFile *ini = new TIniFile(iniFileName);
    Left=ini->ReadInteger("PrintDataForm2","Left",0);
    Top=ini->ReadInteger("PrintDataForm2","Top",0);
    Height=ini->ReadInteger("PrintDataForm2","Height",250);
    Width=ini->ReadInteger("PrintDataForm2","Width",360);
    delete ini;
  }
  else
  { TIniFile *ini = new TIniFile(iniFileName);
    Left=ini->ReadInteger("PrintDataForm1","Left",0);
    Top=ini->ReadInteger("PrintDataForm1","Top",0);
    Height=ini->ReadInteger("PrintDataForm1","Height",500);
    Width=ini->ReadInteger("PrintDataForm1","Width",360);
    bool forLeader1,forLeader2,forLeader3,forLeader4,forBook1,forBook2;

    AnsiString sql;
    TpFIBDataSet *DS=SaleBookDM->TDS;
    DS->Close();
    DS->SQLs->SelectSQL->Clear();
    sql="select v.CONST_VALUE,v.CONST_DATE,c.IDENTIFIER";
    sql+=" from CONST_VALUES v";
    sql+=" left outer join CONSTANT c on c.ID=v.CONST_ID";
    sql+=" where (c.IDENTIFIER='ORDER_SIGNATURE'";
    sql+=" or c.IDENTIFIER='FOR_LEADER_WARRANT'";
    sql+=" or c.IDENTIFIER='FOR_BOOKLEADER_WARRANT')";
    sql+=" and v.ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
    sql+=" order by v.CONST_DATE";
    DS->SQLs->SelectSQL->Add(sql);
    try
    {
      DS->Open();
    }
    catch(const Exception &exc)
    { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
    DS->First();
    int id=1;
    while(!DS->Eof)
    { MemTable1->Append();
      MemTable1->FieldByName("DOC_ID")->AsInteger=id;
      if(DS->FieldByName("IDENTIFIER")->AsString=="ORDER_SIGNATURE")
        MemTable1->FieldByName("DOC_NAME")->AsString="Приказ";
      else
        MemTable1->FieldByName("DOC_NAME")->AsString="Доверенность";
      MemTable1->FieldByName("DOC_NUMBER")->AsString=DS->FieldByName("CONST_VALUE")->AsString;
      MemTable1->FieldByName("DOC_DATE")->AsString=DS->FieldByName("CONST_DATE")->AsString;
      MemTable1->FieldByName("CONST_IDENTIFIER")->AsString=DS->FieldByName("IDENTIFIER")->AsString;
      MemTable1->Post();
      DS->Next();
      id++;
    }
    DS->Close();
    TpFIBQuery *RQ=SaleBookDM->TempQuery;
    MemTable1->First();
    while(!MemTable1->Eof)
    { if(MemTable1->FieldByName("CONST_IDENTIFIER")->AsString=="ORDER_SIGNATURE")
      { forLeader1=ini->ReadBool("PrntDataForm",MemTable1->FieldByName("DOC_NUMBER")->AsString+"_forLeader1",false);
        forLeader2=ini->ReadBool("PrntDataForm",MemTable1->FieldByName("DOC_NUMBER")->AsString+"_forLeader2",false);
        forLeader3=ini->ReadBool("PrntDataForm",MemTable1->FieldByName("DOC_NUMBER")->AsString+"_forLeader3",false);
        forLeader4=ini->ReadBool("PrntDataForm",MemTable1->FieldByName("DOC_NUMBER")->AsString+"_forLeader4",false);
        forBook1=ini->ReadBool("PrntDataForm",MemTable1->FieldByName("DOC_NUMBER")->AsString+"_forBook1",false);
        forBook2=ini->ReadBool("PrntDataForm",MemTable1->FieldByName("DOC_NUMBER")->AsString+"_forBook2",false);
      }
      else
      { forLeader2=false;
        forLeader3=false;
        forLeader4=false;
        forBook2=false;
        if(MemTable1->FieldByName("CONST_IDENTIFIER")->AsString=="FOR_LEADER_WARRANT")
        { forLeader1=ini->ReadBool("PrntDataForm",MemTable1->FieldByName("DOC_NUMBER")->AsString+"_forLeader1",false);
          forBook1=false;
        }
        else
        { forBook1=ini->ReadBool("PrntDataForm",MemTable1->FieldByName("DOC_NUMBER")->AsString+"_forBook1",false);
          forLeader1=false;
        }
      }
      if(MemTable1->FieldByName("CONST_IDENTIFIER")->AsString=="ORDER_SIGNATURE")
      { forLeaderTable->Append();
        forLeaderTable->FieldByName("V_ID")->AsInteger=1;
        forLeaderTable->FieldByName("DOC_ID")->AsInteger=MemTable1->FieldByName("DOC_ID")->AsInteger;
        sql="select v.CONST_VALUE from CONST_VALUES v";
        sql+=" left outer join constant c on c.id=v.const_id";
        sql+=" where v.ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
        sql+=" and c.identifier='SIGNATURE_FOR_LEADER_1'";
        sql+=" and v.const_date='"+MemTable1->FieldByName("DOC_DATE")->AsString+"'";
        RQ->Close();
        RQ->SQL->Clear();
        RQ->SQL->Add(sql);
        try
        {
          RQ->ExecQuery();
        }
        catch(const Exception &exc)
        { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
          return;
        }
        forLeaderTable->FieldByName("FOR_LEADER")->Value=RQ->FieldByName("CONST_VALUE")->Value;
        forLeaderTable->FieldByName("LEADER_CHECK")->AsBoolean=forLeader1;
        forLeaderTable->Post();

        forLeaderTable->Append();
        forLeaderTable->FieldByName("V_ID")->AsInteger=2;
        forLeaderTable->FieldByName("DOC_ID")->AsInteger=MemTable1->FieldByName("DOC_ID")->AsInteger;
        sql="select v.CONST_VALUE from CONST_VALUES v";
        sql+=" left outer join constant c on c.id=v.const_id";
        sql+=" where v.ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
        sql+=" and c.identifier='SIGNATURE_FOR_LEADER_2'";
        sql+=" and v.const_date='"+MemTable1->FieldByName("DOC_DATE")->AsString+"'";
        RQ->Close();
        RQ->SQL->Clear();
        RQ->SQL->Add(sql);
        try
        {
          RQ->ExecQuery();
        }
        catch(const Exception &exc)
        { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
          return;
        }
        forLeaderTable->FieldByName("FOR_LEADER")->Value=RQ->FieldByName("CONST_VALUE")->Value;
        forLeaderTable->FieldByName("LEADER_CHECK")->AsBoolean=forLeader2;
        forLeaderTable->Post();

        forLeaderTable->Append();
        forLeaderTable->FieldByName("V_ID")->AsInteger=3;
        forLeaderTable->FieldByName("DOC_ID")->AsInteger=MemTable1->FieldByName("DOC_ID")->AsInteger;
        sql="select v.CONST_VALUE from CONST_VALUES v";
        sql+=" left outer join constant c on c.id=v.const_id";
        sql+=" where v.ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
        sql+=" and c.identifier='SIGNATURE_FOR_LEADER_3'";
        sql+=" and v.const_date='"+MemTable1->FieldByName("DOC_DATE")->AsString+"'";
        RQ->Close();
        RQ->SQL->Clear();
        RQ->SQL->Add(sql);
        try
        {
          RQ->ExecQuery();
        }
        catch(const Exception &exc)
        { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
          return;
        }
        forLeaderTable->FieldByName("FOR_LEADER")->Value=RQ->FieldByName("CONST_VALUE")->Value;
        forLeaderTable->FieldByName("LEADER_CHECK")->AsBoolean=forLeader3;
        forLeaderTable->Post();

        forLeaderTable->Append();
        forLeaderTable->FieldByName("V_ID")->AsInteger=4;
        forLeaderTable->FieldByName("DOC_ID")->AsInteger=MemTable1->FieldByName("DOC_ID")->AsInteger;
        sql="select v.CONST_VALUE from CONST_VALUES v";
        sql+=" left outer join constant c on c.id=v.const_id";
        sql+=" where v.ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
        sql+=" and c.identifier='SIGNATURE_FOR_LEADER_4'";
        sql+=" and v.const_date='"+MemTable1->FieldByName("DOC_DATE")->AsString+"'";
        RQ->Close();
        RQ->SQL->Clear();
        RQ->SQL->Add(sql);
        try
        {
          RQ->ExecQuery();
        }
        catch(const Exception &exc)
        { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
          return;
        }
        forLeaderTable->FieldByName("FOR_LEADER")->Value=RQ->FieldByName("CONST_VALUE")->Value;
        forLeaderTable->FieldByName("LEADER_CHECK")->AsBoolean=forLeader4;
        forLeaderTable->Post();

        forBookTable->Append();
        forBookTable->FieldByName("V_ID")->AsInteger=1;
        forBookTable->FieldByName("DOC_ID")->AsInteger=MemTable1->FieldByName("DOC_ID")->AsInteger;
        sql="select v.CONST_VALUE from CONST_VALUES v";
        sql+=" left outer join constant c on c.id=v.const_id";
        sql+=" where v.ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
        sql+=" and c.identifier='SIGNATURE_FOR_BOOK_LEADER_1'";
        sql+=" and v.const_date='"+MemTable1->FieldByName("DOC_DATE")->AsString+"'";
        RQ->Close();
        RQ->SQL->Clear();
        RQ->SQL->Add(sql);
        try
        {
          RQ->ExecQuery();
        }
        catch(const Exception &exc)
        { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
          return;
        }
        forBookTable->FieldByName("FOR_BOOK")->Value=RQ->FieldByName("CONST_VALUE")->Value;
        forBookTable->FieldByName("BOOK_CHECK")->AsBoolean=forBook1;
        forBookTable->Post();

        forBookTable->Append();
        forBookTable->FieldByName("V_ID")->AsInteger=2;
        forBookTable->FieldByName("DOC_ID")->AsInteger=MemTable1->FieldByName("DOC_ID")->AsInteger;
        sql="select v.CONST_VALUE from CONST_VALUES v";
        sql+=" left outer join constant c on c.id=v.const_id";
        sql+=" where v.ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
        sql+=" and c.identifier='SIGNATURE_FOR_BOOK_LEADER_2'";
        sql+=" and v.const_date='"+MemTable1->FieldByName("DOC_DATE")->AsString+"'";
        RQ->Close();
        RQ->SQL->Clear();
        RQ->SQL->Add(sql);
        try
        {
          RQ->ExecQuery();
        }
        catch(const Exception &exc)
        { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
          return;
        }
        forBookTable->FieldByName("FOR_BOOK")->Value=RQ->FieldByName("CONST_VALUE")->Value;
        forBookTable->FieldByName("BOOK_CHECK")->AsBoolean=forBook2;
        forBookTable->Post();
      }
      else
      { if(MemTable1->FieldByName("CONST_IDENTIFIER")->AsString=="FOR_LEADER_WARRANT")
        { forLeaderTable->Append();
          forLeaderTable->FieldByName("V_ID")->AsInteger=1;
          forLeaderTable->FieldByName("DOC_ID")->AsInteger=MemTable1->FieldByName("DOC_ID")->AsInteger;
          sql="select v.CONST_VALUE from CONST_VALUES v";
          sql+=" left outer join constant c on c.id=v.const_id";
          sql+=" where v.ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
          sql+=" and c.identifier='SIGNATURE_FOR_LW'";
          sql+=" and v.const_date='"+MemTable1->FieldByName("DOC_DATE")->AsString+"'";
          RQ->Close();
          RQ->SQL->Clear();
          RQ->SQL->Add(sql);
          try
          {
            RQ->ExecQuery();
          }
          catch(const Exception &exc)
          { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
            return;
          }
          forLeaderTable->FieldByName("FOR_LEADER")->Value=RQ->FieldByName("CONST_VALUE")->Value;
          forLeaderTable->FieldByName("LEADER_CHECK")->AsBoolean=forLeader1;
          forLeaderTable->Post();
        }
        else
        { forBookTable->Append();
          forBookTable->FieldByName("V_ID")->AsInteger=1;
          forBookTable->FieldByName("DOC_ID")->AsInteger=MemTable1->FieldByName("DOC_ID")->AsInteger;
          sql="select v.CONST_VALUE from CONST_VALUES v";
          sql+=" left outer join constant c on c.id=v.const_id";
          sql+=" where v.ORG_ID="+IntToStr(SaleBookDM->OrganizationID);
          sql+=" and c.identifier='SIGNATURE_FOR_BW'";
          sql+=" and v.const_date='"+MemTable1->FieldByName("DOC_DATE")->AsString+"'";
          RQ->Close();
          RQ->SQL->Clear();
          RQ->SQL->Add(sql);
          try
          {
            RQ->ExecQuery();
          }
          catch(const Exception &exc)
          { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
            return;
          }
          forBookTable->FieldByName("FOR_BOOK")->Value=RQ->FieldByName("CONST_VALUE")->Value;
          forBookTable->FieldByName("BOOK_CHECK")->AsBoolean=forBook1;
          forBookTable->Post();
        }
      }
      MemTable1->Next();
    }
    RQ->Close();
    delete ini;
  }
}
//---------------------------------------------------------------------------
void __fastcall TPrntDataForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
bool forLeader,forBook;
TIniFile *ini = new TIniFile(iniFileName);


  MemTable1->First();
  while(!MemTable1->Eof)
  { if(MemTable1->FieldByName("CONST_IDENTIFIER")->AsString=="ORDER_SIGNATURE")
    { int n=1;
      forLeaderTable->First();
      while(!forLeaderTable->Eof)
      { forLeader=forLeaderTable->FieldByName("LEADER_CHECK")->AsBoolean;
        ini->WriteBool("PrntDataForm",MemTable1->FieldByName("DOC_NUMBER")->AsString+"_forLeader"+IntToStr(n),forLeader);
        forLeaderTable->Next();
        n++;
      }
      n=1;
      forBookTable->First();
      while(!forBookTable->Eof)
      { forBook=forBookTable->FieldByName("BOOK_CHECK")->AsBoolean;
        ini->WriteBool("PrntDataForm",MemTable1->FieldByName("DOC_NUMBER")->AsString+"_forBook"+IntToStr(n),forBook);
        forBookTable->Next();
        n++;
      }
    }
    else
    { if(MemTable1->FieldByName("CONST_IDENTIFIER")->AsString=="FOR_LEADER_WARRANT")
      { forLeaderTable->First();
        forLeader=forLeaderTable->FieldByName("LEADER_CHECK")->AsBoolean;
        ini->WriteBool("PrntDataForm",MemTable1->FieldByName("DOC_NUMBER")->AsString+"_forLeader1",forLeader);
      }
      else
      { forLeaderTable->First();
        forBook=forBookTable->FieldByName("BOOK_CHECK")->AsBoolean;
        ini->WriteBool("PrntDataForm",MemTable1->FieldByName("DOC_NUMBER")->AsString+"_forBook1",forBook);
      }
    }
    MemTable1->Next();
  }
  delete ini;
  forLeaderTable->Close();
  forBookTable->Close();
  MemTable1->Close();

  HeadDS->Close();
  TableDS->Close();
  Action=caFree;
}
//---------------------------------------------------------------------------
void __fastcall TPrntDataForm::CloseButtonClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TPrntDataForm::CountButtonClick(TObject *Sender)
{
  Label1->Visible = false;
  Label3->Visible = false;
  CNEdit->Visible = false;
  CNEdit1->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TPrntDataForm::InvoiceButtonClick(TObject *Sender)
{
  Label1->Visible = true;
  Label3->Visible = true;
  CNEdit->Visible = true;
  CNEdit1->Visible = true;
//  CNEdit1->Value = 22;
}
//---------------------------------------------------------------------------
void __fastcall TPrntDataForm::JournalButtonClick(TObject *Sender)
{
  Label1->Visible = true;
  Label3->Visible = true;
  CNEdit->Visible = true;
  CNEdit1->Visible = true;
//  CNEdit1->Value = 22;
}
//---------------------------------------------------------------------------
void __fastcall TPrntDataForm::fillSignatures(TDateTime constDate)
{
Variant v[2];
TDateTime doc_dt;

  forLeaderSignature="";
  forBookSignature="";
  docForLeader="";
  docForBook="";
  //Пытаемся найти подписи "За руководителя" и "За главного бухгалтера" из приказа
  doc_dt=SaleBookDM->GetConstDate(OrgID,"ORDER_SIGNATURE",constDate); //дата приказа
  if(int(doc_dt) > 0)
  { v[0]=doc_dt;
    v[1]="ORDER_SIGNATURE";
    if(MemTable1->Locate("DOC_DATE;CONST_IDENTIFIER",VarArrayOf(v, 1),TLocateOptions().Clear())==true)
    { AnsiString s="Приказ на право подписи №"+MemTable1->FieldByName("DOC_NUMBER")->AsString;
      s+=" от "+MemTable1->FieldByName("DOC_DATE")->AsString;
      v[0]=MemTable1->FieldByName("DOC_ID")->AsInteger;
      v[1]=true;
      if(forLeaderTable->Locate("DOC_ID;LEADER_CHECK",VarArrayOf(v, 1),TLocateOptions().Clear())==true && !(forLeaderSignature=forLeaderTable->FieldByName("FOR_LEADER")->AsString).IsEmpty())
        docForLeader=s;
      if(forBookTable->Locate("DOC_ID;BOOK_CHECK",VarArrayOf(v, 1),TLocateOptions().Clear())==true && !(forBookSignature=forBookTable->FieldByName("FOR_BOOK")->AsString).IsEmpty())
        docForBook=s;
    }
  }
  //Пытаемся найти подпись "За руководителя" из доверенности
  if(forLeaderSignature.IsEmpty())
  { doc_dt=SaleBookDM->GetConstDate(OrgID,"FOR_LEADER_WARRANT",constDate);
    v[0]=doc_dt;
    v[1]="FOR_LEADER_WARRANT";
    if(MemTable1->Locate("DOC_DATE;CONST_IDENTIFIER",VarArrayOf(v, 1),TLocateOptions().Clear())==true)
    { v[0]=MemTable1->FieldByName("DOC_ID")->AsInteger;
      v[1]=true;
      if(forLeaderTable->Locate("DOC_ID;LEADER_CHECK",VarArrayOf(v, 1),TLocateOptions().Clear())==true && !(forLeaderSignature=forLeaderTable->FieldByName("FOR_LEADER")->AsString).IsEmpty())
      { AnsiString s="Доверенность на право подписи №"+MemTable1->FieldByName("DOC_NUMBER")->AsString;
        s+=" от "+MemTable1->FieldByName("DOC_DATE")->AsString;
        docForLeader=s;
      }
    }
  }
  //Пытаемся найти подпись "За главоного бухгалтера" из доверенности
  if(forBookSignature.IsEmpty())
  { doc_dt=SaleBookDM->GetConstDate(OrgID,"FOR_BOOKLEADER_WARRANT",constDate);
    v[0]=doc_dt;
    v[1]="FOR_BOOKLEADER_WARRANT";
    if(MemTable1->Locate("DOC_DATE;CONST_IDENTIFIER",VarArrayOf(v, 1),TLocateOptions().Clear())==true)
    { v[0]=MemTable1->FieldByName("DOC_ID")->AsInteger;
      v[1]=true;
      if(forBookTable->Locate("DOC_ID;BOOK_CHECK",VarArrayOf(v, 1),TLocateOptions().Clear())==true && !(forBookSignature=forBookTable->FieldByName("FOR_BOOK")->AsString).IsEmpty())
      { AnsiString s="Доверенность на право подписи №"+MemTable1->FieldByName("DOC_NUMBER")->AsString;
        s+=" от "+MemTable1->FieldByName("DOC_DATE")->AsString;
        docForBook=s;
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TPrntDataForm::frxReportGetValue(const AnsiString VarName,
      Variant &Value)
{
AnsiString s;
AnsiString KolPropis;
AnsiString sql;

      if(VarName=="Z1" || VarName=="Z2" || VarName=="Z3" || VarName=="Z4" || VarName=="Z5" || VarName=="Z6" || VarName=="Z7" || VarName=="Z8" || VarName=="Z9" || VarName=="Z10" || VarName=="Z11" || VarName=="Z12" || VarName=="Z13" || VarName=="Z14" || VarName=="Z15" || VarName=="D1" || VarName=="D2" || VarName=="D3" || VarName=="D4")
      {
      DSREPRES->Close();
      DSREPRES->SQLs->SelectSQL->Clear();
      sql="select g.* ";
      sql+=" from REPRES g where";
      sql+=" g.OPS="+IntToStr(DSSved->FieldByName("OPS")->AsInteger);
      DSREPRES->SQLs->SelectSQL->Add(sql);
      try
      {
        DSREPRES->Open();
      }
      catch(const Exception &exc)
      {
        MessageDlg("Ошибка DSSved->Open()\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
        return;
      }
      }

      if(VarName=="Z16" || VarName=="Z17" || VarName=="Z18" || VarName=="Z19" || VarName=="Z20" || VarName=="Z21" || VarName=="Z22")
      {
      DSREPRES->Close();
      DSREPRES->SQLs->SelectSQL->Clear();
      sql="select g.* ";
      sql+=" from REPRES g where";
      sql+=" g.OPS= 0";
      DSREPRES->SQLs->SelectSQL->Add(sql);
      try
      {
        DSREPRES->Open();
      }
      catch(const Exception &exc)
      {
        MessageDlg("Ошибка DSSved->Open()\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
        return;
      }
      }


  if(VarName=="NumCount")
  {
    Value=HeadDS->FieldByName("COUNT_DATE")->AsDateTime.DateString();
  }
  else if(VarName=="NumCount1") Value=HeadDS->FieldByName("CUSTOMER_NAME")->AsString;
  else if(VarName=="OPS") Value=IntToStr(TableDS->FieldByName("OPS")->AsInteger);

  else if(VarName=="OPS1")
  { if(!DSREPRES->FieldByName("OPS")->AsString.IsEmpty())
      Value=DSREPRES->FieldByName("OPS")->AsString;
    else Value="";
  }

  else if(VarName=="GF_NAME")
  { if(!DSSved->FieldByName("OPS")->AsString.IsEmpty())
      Value=DSSved->FieldByName("OPS")->AsString;
    else Value="";
  }

  else if(VarName=="C1")
  { if(DSREPRES->FieldByName("COUNT_TOTALI")->AsInteger!=0)
      Value=IntToStr(DSREPRES->FieldByName("COUNT_TOTALI")->AsInteger);
    else Value="0";
  }
  else if(VarName=="C2")
  { if(DSREPRES->FieldByName("COUNT_TOTAL")->AsFloat!=0)
      Value=AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_TOTAL")->AsFloat);
    else Value="0.00";
  }

  else if(VarName=="C3")
  { if(DSREPRES->FieldByName("COUNT_OPLI")->AsInteger!=0)
      Value=IntToStr(DSREPRES->FieldByName("COUNT_OPLI")->AsInteger);
    else Value="0";
  }
  else if(VarName=="C4")
  { if(DSREPRES->FieldByName("COUNT_OPL")->AsFloat!=0)
      Value=AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_OPL")->AsFloat);
    else Value="0.00";
  }

  else if(VarName=="C5")
  { if(DSREPRES->FieldByName("COUNT_NEOPLI")->AsInteger!=0)
      Value=IntToStr(DSREPRES->FieldByName("COUNT_NEOPLI")->AsInteger);
    else Value="0";
  }
  else if(VarName=="C6")
  { if(DSREPRES->FieldByName("COUNT_NEOPL")->AsFloat!=0)
      Value=AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_NEOPL")->AsFloat);
    else Value="0.00";
  }

  else if(VarName=="C7")
  { if(DSREPRES->FieldByName("COUNT_NEOPLG")->AsInteger!=0)
      Value=IntToStr(DSREPRES->FieldByName("COUNT_NEOPLG")->AsInteger);
    else Value="0";
  }
  else if(VarName=="C8")
  { if(DSREPRES->FieldByName("COUNT_NEOPLP")->AsFloat!=0)
      Value=AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_NEOPLP")->AsFloat);
    else Value="0.00";
  }

  else if(VarName=="C9")
  { if(DSREPRES->FieldByName("COUNT_OPLM")->AsInteger!=0)
      Value=IntToStr(DSREPRES->FieldByName("COUNT_OPLM")->AsInteger);
    else Value="0";
  }
  else if(VarName=="C10")
  { if(DSREPRES->FieldByName("COUNT_TEK")->AsFloat!=0)
      Value=AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_TEK")->AsFloat);
    else Value="0.00";
  }

  else if(VarName=="C11")
  { if(DSREPRES->FieldByName("COUNT_OPLT")->AsInteger!=0)
      Value=IntToStr(DSREPRES->FieldByName("COUNT_OPLT")->AsInteger);
    else Value="0";
  }
  else if(VarName=="C12")
  { if(DSREPRES->FieldByName("COUNT_PR")->AsFloat!=0)
      Value=AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_PR")->AsFloat);
    else Value="0.00";
  }

  else if(VarName=="C13")
  { if(DSREPRES->FieldByName("COUNT_OPLR")->AsInteger!=0)
      Value=IntToStr(DSREPRES->FieldByName("COUNT_OPLR")->AsInteger);
    else Value="0";
  }
  else if(VarName=="C14")
  { if(DSREPRES->FieldByName("COUNT_RAZ")->AsFloat!=0)
      Value=AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_RAZ")->AsFloat);
    else Value="0.00";
  }

  else if(VarName=="C15")
  { if(DSREPRES->FieldByName("COUNT_FI")->AsInteger!=0)
      Value=IntToStr(DSREPRES->FieldByName("COUNT_FI")->AsInteger);
    else Value="0";
  }
  else if(VarName=="C16")
  { if(DSREPRES->FieldByName("COUNT_FD")->AsFloat!=0)
      Value=AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_FD")->AsFloat);
    else Value="0.00";
  }

  else if(VarName=="OPLC")
  { if(TableDS->FieldByName("COUNT_OPL")->AsInteger!=0)
      Value=IntToStr(TableDS->FieldByName("COUNT_OPL")->AsInteger);
    else Value="0";
  }
  else if(VarName=="OPLR")
  { if(TableDS->FieldByName("OPL")->AsFloat!=0)
      Value=AnsiString().sprintf("%.2lf",TableDS->FieldByName("OPL")->AsFloat);
    else Value="0.00";
  }
  else if(VarName=="NEOPLC")
  { if(TableDS->FieldByName("COUNT_NEOPL")->AsInteger!=0)
      Value=IntToStr(TableDS->FieldByName("COUNT_NEOPL")->AsInteger);
    else Value="0";
  }
  else if(VarName=="NEOPLR")
  { if(TableDS->FieldByName("NEOPL")->AsFloat!=0)
      Value=AnsiString().sprintf("%.2lf",TableDS->FieldByName("NEOPL")->AsFloat);
    else Value="0.00";
  }



  else if(VarName=="Header"){
    s="Отчет за " +AccountsJournalForm->Month->Text + " c " + CNEdit->EditText;
    s+=" по "+ CNEdit1->EditText + " число ЕДВ Муниципальные по " + SaleBookDM->GetConstValue(OrgID,"ORG_NAME",ConstToDate);
    Value=s;
  }

  else if(VarName=="SS_Name"){
    s=" в  " +  SaleBookDM->GetConstValue(OrgID,"ORG_NAME",ConstToDate) + " г.Новосибирска ";
    Value=s;
  }
  else if(VarName=="MOL"){
    s=" за " + AccountsJournalForm->Month->Text + " " +IntToStr(int(AccountsJournalForm->Year->Value))+" г. ";;
    Value=s;
  }

  else if(VarName=="Itogo1")
  {
    s="Итого оплачено за " +AccountsJournalForm->Month->Text + " c " + CNEdit->EditText;
    s+=" по "+ CNEdit1->EditText;
   Value=s;
  }

  else if(VarName=="Itogo2"){
  TfrxMemoView *Memo;
    Memo=(TfrxMemoView *)frxReport->FindObject("Memo58");
    Value=AnsiString(f_to_str(double(Memo->Value)));
  }
  else if(VarName=="Itogo4"){
    s=SaleBookDM->GetConstValue(OrgID,"JOB_TITLE_OF_LEADER",ConstToDate) + " ____________________________ " + SaleBookDM->GetConstValue(OrgID,"LEADER",ConstToDate);
    Value=s;
  }
  else if(VarName=="Itogo3"){
    s=SaleBookDM->GetConstValue(OrgID,"JOB_TITLE_OF_LEADER_TO_BOOK",ConstToDate) + " ____________________________ " + SaleBookDM->GetConstValue(OrgID,"LEADER_TO_BOOK",ConstToDate);
    Value=s;
  }
  else if(VarName=="Z1")
  { if(DSREPRES->FieldByName("COUNT_TOTALI")->AsInteger!=0)
      Value=IntToStr(DSREPRES->FieldByName("COUNT_TOTALI")->AsInteger) + " поручений";
    else Value="0 поручений";
  }
  else if(VarName=="Z2")
  { if(DSREPRES->FieldByName("COUNT_TOTAL")->AsFloat!=0)
      Value=AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_TOTAL")->AsFloat) + " руб.";
    else Value="0.00 руб.";
  }
  else if(VarName=="Z3")
  { if(DSREPRES->FieldByName("COUNT_TOTAL")->AsFloat!=0)
    Value=AnsiString(f_to_str(DSREPRES->FieldByName("COUNT_TOTAL")->AsFloat));
    else Value=" ";
  }
  else if(VarName=="Z4")
  {
    if(DSREPRES->FieldByName("COUNT_OPLI")->AsInteger!=0)
      Value=IntToStr(DSREPRES->FieldByName("COUNT_OPLI")->AsInteger) + " поручений";
    else Value="0 поручений";
  }
  else if(VarName=="Z5")
  { if(DSREPRES->FieldByName("COUNT_OPL")->AsFloat!=0)
      Value=AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_OPL")->AsFloat) + " руб.";
    else Value="0.00 руб.";
  }
  else if(VarName=="Z6")
  { if(DSREPRES->FieldByName("COUNT_OPL")->AsFloat!=0)
    Value=AnsiString(f_to_str(DSREPRES->FieldByName("COUNT_OPL")->AsFloat));
    else Value=" ";
  }
  else if(VarName=="Z7")
  {
   if(DSREPRES->FieldByName("COUNT_FD")->AsFloat!=0)
      Value=AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_FD")->AsFloat) + " руб.";
    else Value="0.00 руб.";
  }
  else if(VarName=="Z8")
  { if((DSREPRES->FieldByName("COUNT_OPL")->AsFloat-DSREPRES->FieldByName("COUNT_FD")->AsFloat)!=0)
      Value=AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_OPL")->AsFloat-DSREPRES->FieldByName("COUNT_FD")->AsFloat) + " руб.";
    else Value="0.00 руб.";
  }
  else if(VarName=="Z9")
  {
    if(DSREPRES->FieldByName("COUNT_OPLT")->AsInteger!=0) s="кол-во " + IntToStr(DSREPRES->FieldByName("COUNT_OPLT")->AsInteger); else s=" кол-во 0 ";
    if(DSREPRES->FieldByName("COUNT_PR")->AsFloat!=0) s+=" сумма " + AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_PR")->AsFloat); else s+=" сумма 0.00 ";
    Value=s;
  }
  else if(VarName=="Z10")
  {
    if(DSREPRES->FieldByName("COUNT_NEOPLI")->AsInteger!=0)
      s="кол-во " + IntToStr(DSREPRES->FieldByName("COUNT_NEOPLI")->AsInteger);
    else s="кол-во 0 ";
    if(DSREPRES->FieldByName("COUNT_NEOPL")->AsFloat!=0)
      s+=" сумма " + AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_NEOPL")->AsFloat);
    else s+=" сумма 0.00 ";
    Value=s;
  }
  else if(VarName=="Z11")
  {
    if(DSREPRES->FieldByName("COUNT_OPLR")->AsInteger!=0)
      s="кол-во " + IntToStr(DSREPRES->FieldByName("COUNT_OPLR")->AsInteger);
    else s="кол-во 0 ";
    if(DSREPRES->FieldByName("COUNT_RAZ")->AsFloat!=0)
      s+=" сумма " + AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_RAZ")->AsFloat);
    else s+=" сумма 0.00 ";
    Value=s;
  }
  else if(VarName=="Z12")
  {
    if(DSREPRES->FieldByName("COUNT_NEOPLG")->AsInteger!=0)
      s="кол-во " + IntToStr(DSREPRES->FieldByName("COUNT_NEOPLG")->AsInteger);
    else s="кол-во 0 ";
    if(DSREPRES->FieldByName("COUNT_NEOPLP")->AsFloat!=0)
      s+=" сумма " + AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_NEOPLP")->AsFloat);
    else s+=" сумма 0.00 ";
    Value=s;
  }
  else if(VarName=="Z13")
  {
    s="кол-во 0 ";
    s+=" сумма 0.00 ";
    Value=s;
  }
  else if(VarName=="Z14")
  {
    if((DSREPRES->FieldByName("COUNT_OPLM")->AsInteger-DSREPRES->FieldByName("COUNT_OPLR")->AsInteger)!=0)
      s="кол-во " + IntToStr(DSREPRES->FieldByName("COUNT_OPLM")->AsInteger-DSREPRES->FieldByName("COUNT_OPLR")->AsInteger);
    else s="кол-во 0 ";
    if(DSREPRES->FieldByName("COUNT_TEK")->AsFloat!=0)
      s+=" сумма " + AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_TEK")->AsFloat);
    else s+=" сумма 0.00 ";
    Value=s;
  }
  else if(VarName=="Z15")
  {
    if((DSREPRES->FieldByName("COUNT_OPLM")->AsInteger-DSREPRES->FieldByName("COUNT_OPLR")->AsInteger)!=0)
      s="кол-во " + IntToStr(DSREPRES->FieldByName("COUNT_OPLM")->AsInteger-DSREPRES->FieldByName("COUNT_OPLR")->AsInteger);
    else s="кол-во 0 ";
    if(DSREPRES->FieldByName("COUNT_TEK")->AsFloat!=0)
      s+=" сумма " + AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_TEK")->AsFloat);
    else s+=" сумма 0.00 ";
    Value=s;
  }
  else if(VarName=="Z16")
  {
    if(DSREPRES->FieldByName("COUNT_OPLT")->AsInteger!=0) s="кол-во " + IntToStr(DSREPRES->FieldByName("COUNT_OPLT")->AsInteger); else s=" кол-во 0 ";
    if(DSREPRES->FieldByName("COUNT_PR")->AsFloat!=0) s+=" сумма " + AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_PR")->AsFloat); else s+=" сумма 0.00 ";
    Value=s;
  }
  else if(VarName=="Z17")
  {
    if(DSREPRES->FieldByName("COUNT_NEOPLI")->AsInteger!=0)
      s="кол-во " + IntToStr(DSREPRES->FieldByName("COUNT_NEOPLI")->AsInteger);
    else s="кол-во 0 ";
    if(DSREPRES->FieldByName("COUNT_NEOPL")->AsFloat!=0)
      s+=" сумма " + AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_NEOPL")->AsFloat);
    else s+=" сумма 0.00 ";
    Value=s;
  }
  else if(VarName=="Z18")
  {
    if(DSREPRES->FieldByName("COUNT_OPLR")->AsInteger!=0)
      s="кол-во " + IntToStr(DSREPRES->FieldByName("COUNT_OPLR")->AsInteger);
    else s="кол-во 0 ";
    if(DSREPRES->FieldByName("COUNT_RAZ")->AsFloat!=0)
      s+=" сумма " + AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_RAZ")->AsFloat);
    else s+=" сумма 0.00 ";
    Value=s;
  }
  else if(VarName=="Z19")
  {
    if(DSREPRES->FieldByName("COUNT_NEOPLG")->AsInteger!=0)
      s="кол-во " + IntToStr(DSREPRES->FieldByName("COUNT_NEOPLG")->AsInteger);
    else s="кол-во 0 ";
    if(DSREPRES->FieldByName("COUNT_NEOPLP")->AsFloat!=0)
      s+=" сумма " + AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_NEOPLP")->AsFloat);
    else s+=" сумма 0.00 ";
    Value=s;
  }
  else if(VarName=="Z20")
  {
    s="кол-во 0 ";
    s+=" сумма 0.00 ";
    Value=s;
  }
  else if(VarName=="Z21")
  {
    if(DSREPRES->FieldByName("COUNT_OPLM")->AsInteger!=0)
      s="кол-во " + IntToStr(DSREPRES->FieldByName("COUNT_OPLM")->AsInteger);
    else s="кол-во 0 ";
    if(DSREPRES->FieldByName("COUNT_TEK")->AsFloat!=0)
      s+=" сумма " + AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_TEK")->AsFloat);
    else s+=" сумма 0.00 ";
    Value=s;
  }
  else if(VarName=="Z22")
  {
    if(DSREPRES->FieldByName("COUNT_OPLM")->AsInteger !=0)
      s="кол-во " + IntToStr(DSREPRES->FieldByName("COUNT_OPLM")->AsInteger);
    else s="кол-во 0 ";
    if(DSREPRES->FieldByName("COUNT_TEK")->AsFloat!=0)
      s+=" сумма " + AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_TEK")->AsFloat);
    else s+=" сумма 0.00 ";
    Value=s;
  }
  else if(VarName=="D1")
  { if(DSREPRES->FieldByName("COUNT_TOTALI")->AsInteger!=0)
      Value=IntToStr(DSREPRES->FieldByName("COUNT_TOTALI")->AsInteger) + " поручений";
    else Value="0 поручений";
  }
  else if(VarName=="D2")
  { if(DSREPRES->FieldByName("COUNT_TOTAL")->AsFloat!=0)
      Value=" на сумму " + AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_TOTAL")->AsFloat);
    else Value=" на сумму 0.00 руб.";
  }
  else if(VarName=="D3")
  {
    if(DSREPRES->FieldByName("COUNT_OPLI")->AsInteger!=0)
      Value=IntToStr(DSREPRES->FieldByName("COUNT_OPLI")->AsInteger) + " поручений";
    else Value="0 поручений";
  }
  else if(VarName=="D4")
  { if(DSREPRES->FieldByName("COUNT_OPL")->AsFloat!=0)
      Value=" на сумму " + AnsiString().sprintf("%.2lf",DSREPRES->FieldByName("COUNT_OPL")->AsFloat);
    else Value=" на сумму  0.00 руб.";
  }

}
//---------------------------------------------------------------------------



void __fastcall TPrntDataForm::FormShow(TObject *Sender)
{
TpFIBDataSet *DSZ;
TDateTime dprn;
unsigned short dvp,yvp,mvp;
TDateTime lockDate;
unsigned short yl,ml,dl;


if(Application->FindComponent("AccountsJournalForm")) dprn=AccountsJournalForm->getDate1(); else dprn=Date();
dprn.DecodeDate(&yvp,&mvp,&dvp);

lockDate=SaleBookDM->GetConstValue(SaleBookDM->OrganizationID,"LOCK_EDIT_DATE");
lockDate.DecodeDate(&yl,&ml,&dl);


DSZ=((TpFIBDataSet*)(AccountsJournalForm->AccountsGrid->DataSource->DataSet));
if (DSZ->RecordCount==0)
{
CountButton->Enabled=false;
}
else
{
CountButton->Enabled=true;
}
if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель")
{
PrntDataForm->Caption="Вывод данных на принтер...";
OutputButton->Visible = false;
PotrButton->Visible = false;
SendButton->Visible = false;
Indicator->Visible=false;
Panel2->Height=90;
Panel1->Height=35;
}
else
{
if(SaleBookDM->UserRole=="Администратор")
{
PrntDataForm->Caption="Вывод данных на принтер и отправка данных в администрацию соцзащиты!!!";
if (mvp==ml)
{
SendButton->Visible = true;
OutputButton->Visible = true;
Indicator->Visible=true;
}else
{
SendButton->Visible = false;
OutputButton->Visible = false;
Indicator->Visible=false;
}
}
else
{
PrntDataForm->Caption="Вывод данных на принтер...";
SendButton->Visible = false;
OutputButton->Visible = false;
Indicator->Visible=false;
}
PotrButton->Visible = true;
Panel2->Height=113;
Panel1->Height=70;
}
}
//---------------------------------------------------------------------------

bool __fastcall TPrntDataForm::Filedate(AnsiString NF)
{
FILE *stream;
std::ftime ft;
TDateTime tt;
TDateTime today;
AnsiString result,resD,resM;
int yearf,monthf,dayf;
int yeart,montht,dayt;

today=Date();

if ((stream=fopen(NF.c_str(),"r")) == NULL)
{
result="notdated";
return false;
}

getftime(fileno(stream),&ft);
fclose(stream);
tt=EncodeDate(ft.ft_year+1980,ft.ft_month,ft.ft_day);
dayf=DayOf(tt);
monthf=MonthOf(tt);
yearf=YearOf(tt);
dayt=DayOf(today);
montht=MonthOf(today);
yeart=YearOf(today);


if (dayf == dayt && monthf==montht && yearf==yeart)
{
return true;
}
else
{
return false;
}

}

void __fastcall TPrntDataForm::OutputButtonClick(TObject *Sender)
{
AnsiString DirExport;
AnsiString s,sql;;
int c=0;
TSearchRec sr;
int CountFileAll=0;
unsigned short y,m,d;
Date().DecodeDate(&y,&m,&d);
char buf[10];
sprintf(buf,"%02d%02d%02d",y-2000,m,d);
AnsiString zip=MainForm->WorkDir+"Send\\"+buf+".zip";
DirExport=MainForm->WorkDir+"Send\\";
AnsiString backup=MainForm->WorkDir+"Send\\*.*";
unsigned short dvp,yvp,mvp;
int date1,date2;
int k;
AnsiString IndOps;


TDateTime dprn=AccountsJournalForm->getDate1();
dprn.DecodeDate(&yvp,&mvp,&dvp);
date1=StrToInt(CNEdit->Text);
date2=StrToInt(CNEdit1->Text);
TpFIBDataSet *DSZ;
DSZ=((TpFIBDataSet*)(AccountsJournalForm->AccountsGrid->DataSource->DataSet));



  for (int cidm=0;cidm<20;cidm++)
  {
  Massiv[cidm]=0;
  }

  sql="select * from USERS where ID="+IntToStr(SaleBookDM->UserID);
  TempQ->Close();
  TempQ->SQL->Clear();
  TempQ->SQL->Add(sql);
  try
  {
    TempQ->ExecQuery();
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  }
  IndOps=TempQ->FieldByName("U_INDEX")->AsString;

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


  // проверка папки на наличие таблиц dbf
DirExport=MainForm->WorkDir+"Send\\";

SetCurrentDir(DirExport);

if (FindFirst("*.dbf",faAnyFile , sr) == 0)
{
DeleteFile(sr.Name.Trim());
  while (FindNext(sr)==0)
  {
  DeleteFile(sr.Name.Trim());
  }
}

if (FindFirst("*.zip",faAnyFile , sr) == 0)
{
DeleteFile(sr.Name.Trim());
  while (FindNext(sr)==0)
  {
  DeleteFile(sr.Name.Trim());
  }
}


if (FindFirst("*.rtf",faAnyFile , sr) == 0)
{
CountFileAll++;

if ((sr.Name.Pos("reportof") || sr.Name.Pos("svedof"))  && Filedate(sr.Name.Trim()))
{c++;}
else
{DeleteFile(sr.Name.Trim());}

  while (FindNext(sr)==0)
  {
  if ((sr.Name.Pos("reportof") || sr.Name.Pos("svedof"))  && Filedate(sr.Name.Trim()))
  {c++;}
  else
  {DeleteFile(sr.Name.Trim());}
  CountFileAll++;
  }
}


if (c==0)
{
s="В папке для отправки " + DirExport + " НЕ обнаружены актуальные по дате файлы rtf для отправки!!! \n Сделайте экспорт отчетов в формат rtf !!! ";
MessageDlg(s,mtError,TMsgDlgButtons() << mbOK,0);
return;
}

if (c==2)
{
  sql="select MIN(EDIT_KEY) as SEK from ACCOUNTS where M="+IntToStr(mvp);
  sql+=" and Y="+IntToStr(yvp);
  SaleBookDM->TempQuery->Close();
  SaleBookDM->TempQuery->SQL->Clear();
  SaleBookDM->TempQuery->SQL->Add(sql);
  try
  {
    SaleBookDM->TempQuery->ExecQuery();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(SaleBookDM->TempQuery->FieldByName("SEK")->AsInteger==0)
  {
    MessageDlg("Задания редактируется! Для экспорта данных и отправки в соцзащиту необходимо закончить редактирования всех задания и закрыть их!!!",mtWarning,TMsgDlgButtons() << mbOK,0);
    return;
  }

    int res=exporttodbf();
    if (res==1)
    {
    if(FileExists(zip)) DeleteFile(zip);
    ZipBuilder->ZipFileName=zip;
    ZipBuilder->FSpecArgs->Clear();
    ZipBuilder->FSpecArgs->Add(backup);
    ZipBuilder->Add();
    if(ZipBuilder->ErrCode != 0)
    {
      MessageDlg("Ошибка создания архива. Код ошибки - "+IntToStr(ZipBuilder->ErrCode)+".\n"+ZipBuilder->Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }

  // удаление ненужных файлов
SetCurrentDir(DirExport);

if (FindFirst("*.dbf",faAnyFile , sr) == 0)
{
DeleteFile(sr.Name.Trim());
  while (FindNext(sr)==0)
  {
  DeleteFile(sr.Name.Trim());
  }
}

int cd=0;

if (FindFirst("*.rtf",faAnyFile , sr) == 0)
{
if (sr.Name.Pos("reportof") && Filedate(sr.Name.Trim()))
{cd++;}
else
{DeleteFile(sr.Name.Trim());}

  while (FindNext(sr)==0)
  {
  if (sr.Name.Pos("reportof") && Filedate(sr.Name.Trim()))
  {cd++;}
  else
  {DeleteFile(sr.Name.Trim());}
  }
}


    s="Архив для отправки данных создан и находится в файле - "+ zip + "\n Отправьте их пожалуйста по назначению !!! ";
    MessageDlg(s,mtInformation,TMsgDlgButtons() << mbOK,0);
    }else
    {
    if (res==0) MessageDlg("Сбой экспорта !!! (((",mtInformation,TMsgDlgButtons() << mbOK,0);
    if (res==2) MessageDlg("Необходимо создать сводный отчет и машинограмму и вновь выгрузить данные!!!",mtInformation,TMsgDlgButtons() << mbOK,0);
    if (res==4) MessageDlg("Обнаружена ошибка в БД!!! Необходимо сделать проверку БД через меню Администрирование->Проверить БД !!!",mtInformation,TMsgDlgButtons() << mbOK,0);
    if (res==3) MessageDlg("Необходимо обновить сводный отчет и машинограмму и вновь выгрузить данные!!!",mtInformation,TMsgDlgButtons() << mbOK,0);
    }
}
else
{
s="В папке для отправки "  + DirExport +  " НЕ все обнаружены актуальные по дате файлы rtf для отправки!!! \n Сделайте экспорт отчетов в формат rtf !!! ";
MessageDlg(s,mtError,TMsgDlgButtons() << mbOK,0);
return;
}
}

//---------------------------------------------------------------------------
int __fastcall TPrntDataForm::CheckDB(void)
{
AnsiString sql;
int countoplr,countople,countneoplr,countneople,countpodlr,countdouble;
unsigned short dvp,yvp,mvp;
int date1,date2;
int countzap=0;

TDateTime dprn=AccountsJournalForm->getDate1();
dprn.DecodeDate(&yvp,&mvp,&dvp);
date1=StrToInt(CNEdit->Text);
date2=StrToInt(CNEdit1->Text);


  sql="  select sum(COUNT_NEOPLI+COUNT_NEOPLG) as NEOPL , sum(COUNT_OPLT+COUNT_OPLR) as OPL , sum(COUNT_TOTALI) as PODL from REPRES ";
  TempQ->Close();
  TempQ->SQL->Clear();
  TempQ->SQL->Add(sql);
  try
  {
    TempQ->ExecQuery();
  }
  catch(const Exception &exc)
  {
  MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  return 0;
  }

  if(TempQ->FieldByName("NEOPL")->AsInteger > 0) countneoplr=TempQ->FieldByName("NEOPL")->AsInteger; else countneoplr=0;
  if(TempQ->FieldByName("OPL")->AsInteger > 0) countoplr=TempQ->FieldByName("OPL")->AsInteger; else countoplr=0;
  if(TempQ->FieldByName("PODL")->AsInteger > 0) countpodlr=TempQ->FieldByName("PODL")->AsInteger; else countpodlr=0;


  sql="select count (distinct g.lchet) as CR from SGB g where g.PRICH = ''";
  sql+=" and g.FAKT_DAT>="+IntToStr(date1);
  sql+=" and g.FAKT_DAT<="+IntToStr(date2);
  sql+=" and g.M="+IntToStr(mvp);
  sql+=" and g.Y="+IntToStr(yvp);
  sql+=" and g.METKA1 IN ("+ IndexOps + ")";
  sql+=" and g.LCHET1 NOT IN ('Прошврем','раздел 1')";


  TempQ->Close();
  TempQ->SQL->Clear();
  TempQ->SQL->Add(sql);
  try
  {
    TempQ->ExecQuery();
  }
  catch(const Exception &exc)
  {
  MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  return 0;
  }

  if(TempQ->FieldByName("CR")->AsInteger > 0) countople=TempQ->FieldByName("CR")->AsInteger; else countople=0;
  countzap=countople;


  sql="select count (distinct g.lchet) as CR from SGB g where g.PRICH NOT IN ('н/д') and g.prich <>''";
  sql+=" and g.FAKT_DAT>="+IntToStr(date1);
  sql+=" and g.FAKT_DAT<="+IntToStr(date2);
  sql+=" and g.M="+IntToStr(mvp);
  sql+=" and g.Y="+IntToStr(yvp);
  sql+=" and g.METKA1 IN ("+ IndexOps + ")";
  sql+=" and g.kassa= 0";
  sql+=" and g.LCHET1 NOT IN ('Прошврем','раздел 1')";
  TempQ->Close();
  TempQ->SQL->Clear();
  TempQ->SQL->Add(sql);
  try
  {
    TempQ->ExecQuery();
  }
  catch(const Exception &exc)
  {
  MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  return 0;
  }

  if(TempQ->FieldByName("CR")->AsInteger > 0) countneople=TempQ->FieldByName("CR")->AsInteger; else countneople=0;

      sql="select distinct count (g.lchet) as CR from NDOST g where";
      sql+=" g.lchet not in(select lchet from sgb where sgb.M=" +IntToStr(mvp) + " and sgb.Y=" +IntToStr(yvp);
      sql+=" ) and g.D_VIPL>="+IntToStr(date1);
      sql+=" and g.D_VIPL<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1 IN ("+ IndexOps + ")";
      sql+=" and g.LCHET1 NOT IN ('Прошврем','раздел 1')";

  TempQ->Close();
  TempQ->SQL->Clear();
  TempQ->SQL->Add(sql);
  try
  {
    TempQ->ExecQuery();
  }
  catch(const Exception &exc)
  {
  MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  return 0;
  }

  if(TempQ->FieldByName("CR")->AsInteger > 0) countneople=countneople+TempQ->FieldByName("CR")->AsInteger;
  countzap=countzap+countneople;

  sql="select distinct count (distinct g.lchet) as CR from SGB g where g.PRICH = 'н/д'";
  sql+=" and g.FAKT_DAT>="+IntToStr(date1);
  sql+=" and g.FAKT_DAT<="+IntToStr(date2);
  sql+=" and g.M="+IntToStr(mvp);
  sql+=" and g.Y="+IntToStr(yvp);
  sql+=" and g.METKA1 IN ("+ IndexOps + ")";
  sql+=" and g.kassa= 0";
  sql+=" and g.LCHET1 NOT IN ('Прошврем','раздел 1')";
  TempQ->Close();
  TempQ->SQL->Clear();
  TempQ->SQL->Add(sql);
  try
  {
    TempQ->ExecQuery();
  }
  catch(const Exception &exc)
  {
  MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  return 0;
  }

  if(TempQ->FieldByName("CR")->AsInteger > 0) countdouble=TempQ->FieldByName("CR")->AsInteger; else countdouble=0;
  countzap=countzap+countdouble;


  if ( countpodlr != countzap )return 1; return 2;

}
//---------------------------------------------------------------------------
int __fastcall TPrntDataForm::exporttodbf(void)
{
AnsiString DirExport;
AnsiString s,sql;
int inH, outH, fl;
char *buf;
unsigned short y,m,d;
Date().DecodeDate(&y,&m,&d);
char bufn[10];
sprintf(bufn,"%02d",m);
AnsiString FileName=MainForm->WorkDir+"Send\\sm"+bufn+".dbf";
AnsiString FileName1=MainForm->WorkDir+"Send\\neoplat.dbf";
AnsiString SourceName=MainForm->WorkDir+"SOURCE\\dbf.dsn";
AnsiString dbfFile=ExtractFileName(FileName);
AnsiString dbfFile1=ExtractFileName(FileName1);
AnsiString path;
AnsiString str;
AnsiString tempName;
int countoplr,countople,countneoplr,countneople,countpodlr;
unsigned short dvp,yvp,mvp;
TDateTime dprn=AccountsJournalForm->getDate1();
dprn.DecodeDate(&yvp,&mvp,&dvp);
double summa=0.00;
int kol=0;
int countzap=0;
int id=0;


  sql="  select sum(COUNT_NEOPLI+COUNT_NEOPLG) as NEOPL , sum(COUNT_OPLT+COUNT_OPLR) as OPL , sum(COUNT_TOTALI+COUNT_OPLI) as PODL from REPRES where OPS=0";
  TempQ->Close();
  TempQ->SQL->Clear();
  TempQ->SQL->Add(sql);
  try
  {
    TempQ->ExecQuery();
  }
  catch(const Exception &exc)
  {
  MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  return 0;
  }

  if(TempQ->FieldByName("NEOPL")->AsInteger > 0) countneoplr=TempQ->FieldByName("NEOPL")->AsInteger; else countneoplr=0;
  if(TempQ->FieldByName("OPL")->AsInteger > 0) countoplr=TempQ->FieldByName("OPL")->AsInteger; else countoplr=0;
  if(TempQ->FieldByName("PODL")->AsInteger > 0) countpodlr=TempQ->FieldByName("PODL")->AsInteger; else countpodlr=0;

  if (countneoplr==0 && countoplr==0)
  {

  sql="  select sum(COUNT_NEOPLI+COUNT_NEOPLG) as NEOPL , sum(COUNT_OPLT+COUNT_OPLR) as OPL , sum(COUNT_TOTALI+COUNT_OPLI) as PODL from REPRES ";
  TempQ->Close();
  TempQ->SQL->Clear();
  TempQ->SQL->Add(sql);
  try
  {
    TempQ->ExecQuery();
  }
  catch(const Exception &exc)
  {
  MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  return 0;
  }

  if(TempQ->FieldByName("NEOPL")->AsInteger > 0) countneoplr=TempQ->FieldByName("NEOPL")->AsInteger; else countneoplr=0;
  if(TempQ->FieldByName("OPL")->AsInteger > 0) countoplr=TempQ->FieldByName("OPL")->AsInteger; else countoplr=0;
  if(TempQ->FieldByName("PODL")->AsInteger > 0) countpodlr=TempQ->FieldByName("PODL")->AsInteger; else countpodlr=0;

    if (countneoplr==0 && countoplr==0)
    {
    return 2;
    }
  }


// экспорт в sm.dbf
  ADOConnection->Connected=false;
   //Читаем данные о структуре из файла-шаблона
    tempName=MainForm->WorkDir+"Export\\Templates\\sm.dbf";
    if(!FileExists(tempName))
    { MessageDlg("Отсутствует шаблон для файла выгрузки",mtError,TMsgDlgButtons() << mbOK,0);
      return 0;
    }
    if((inH=FileOpen(tempName,fmOpenRead)) < 0)
    { MessageDlg("Ошибка открытия файла-шаблона",mtError,TMsgDlgButtons() << mbOK,0);
      return 0;
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
      return 0;
    }
    FileRead(inH, buf, fl);
    FileClose(inH);

    //Пишем данные о структуре в выходной файл
    if(FileExists(FileName)) DeleteFile(FileName);
    if((outH=FileCreate(FileName)) < 0)
    { MessageDlg("Ошибка создания выходного файла",mtError,TMsgDlgButtons() << mbOK,0);
      delete buf;
      return 0;
    }
    FileWrite(outH,buf,fl);
    FileClose(outH);
    delete buf;

    if(!FileExists(FileName))
    { MessageDlg("Ошибка создания файла выгрузки",mtError,TMsgDlgButtons() << mbOK,0);
      return 0;
    }

    //Инициализируем ADO подключение
    path=ExtractFilePath(FileName);
    str="FILE NAME="+SourceName+";";
    ADOConnection->ConnectionString=str;
    try
    {
      ADOConnection->Connected=true;
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка инициализации ADO подключения\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return 0;
    }

      ExportDS->Close();
      ExportDS->SQLs->SelectSQL->Clear();
      sql="select distinct g.* from SGB g where g.PRICH = ''";
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      ExportDS->SQLs->SelectSQL->Add(sql);
      try
      {
        ExportDS->Open();
      }
      catch(const Exception &exc)
      { MessageDlg("Ошибка ExportDS->Open()\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
        return 0;
      }

    ExportDS->Last();
    countople=ExportDS->RecordCount;
    Indicator->Visible = true;
    Indicator->MinValue=0;
    Indicator->MaxValue=countople;
    ExportDS->First();
    id=0;
    if ( countoplr != countople )
    {
    return 4;
    }
    while(!ExportDS->Eof)
    {
        Q->Close();
        Q->SQL->Clear();
        sql="insert into "+dbfFile+" (LCHET,SUMMA,WORD,METKA,NEOPL,KODPEN,IST,FOND,PNN,\
        LCHET1,D_VIPL,DOST,SUMMA_PART,SUM_BASE,IST_BASE,SUM_INC,IST_INC,SUM_ACC,IST_ACC,\
        SUM_DOUB,IST_DOUB,SUM_DELTA,IST_DELTA,SUM_DELTA2,IST_DELTA2,PROXY) values('";
        sql+=ExportDS->FieldByName("LCHET1")->AsString.Trim()+"',";
        sql+=AnsiString().sprintf("%.02lf",ExportDS->FieldByName("SUMMA")->AsFloat)+",'";
        sql+=ExportDS->FieldByName("WORD")->AsString.Trim()+"',";
        sql+=IntToStr(ExportDS->FieldByName("METKA")->AsInteger)+",";
        sql+=IntToStr(ExportDS->FieldByName("NEOPL")->AsInteger)+",";
        sql+=IntToStr(ExportDS->FieldByName("KODPEN")->AsInteger)+",";
        sql+=IntToStr(ExportDS->FieldByName("IST")->AsInteger)+",";
        sql+=IntToStr(ExportDS->FieldByName("FOND")->AsInteger)+",";
        sql+=IntToStr(ExportDS->FieldByName("PNN")->AsInteger)+",";
        sql+=IntToStr(ExportDS->FieldByName("LCHET")->AsInteger)+",";
        sql+=IntToStr(ExportDS->FieldByName("D_VIPL")->AsInteger)+",";
        sql+=IntToStr(ExportDS->FieldByName("DOST")->AsInteger)+",";
        sql+=AnsiString().sprintf("%.02lf",summa)+",";
        sql+=AnsiString().sprintf("%.02lf",summa)+",";
        sql+=IntToStr(kol)+",";
        sql+=AnsiString().sprintf("%.02lf",summa)+",";
        sql+=IntToStr(kol)+",";
        sql+=AnsiString().sprintf("%.02lf",summa)+",";
        sql+=IntToStr(kol)+",";
        sql+=AnsiString().sprintf("%.02lf",summa)+",";
        sql+=IntToStr(kol)+",";
        sql+=AnsiString().sprintf("%.02lf",summa)+",";
        sql+=IntToStr(kol)+",";
        sql+=AnsiString().sprintf("%.02lf",summa)+",";
        sql+=IntToStr(kol)+",'')";
        Q->SQL->Add(sql);
        try
        {
          Q->ExecSQL();
        }
        catch(const Exception &exc)
        { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
          ADOConnection->Connected=false;
          return 0;
        }

      ExportDS->Next();
      id++;
      Indicator->Progress = id;
    }
    ExportDS->Close();
    ADOConnection->Connected=false;
    countzap=countzap+id;

// экспорт в neoplat.dbf

  ADOConnection->Connected=false;
   //Читаем данные о структуре из файла-шаблона
    tempName=MainForm->WorkDir+"Export\\Templates\\neoplat.dbf";
    if(!FileExists(tempName))
    { MessageDlg("Отсутствует шаблон для файла выгрузки",mtError,TMsgDlgButtons() << mbOK,0);
      return 0;
    }
    if((inH=FileOpen(tempName,fmOpenRead)) < 0)
    { MessageDlg("Ошибка открытия файла-шаблона",mtError,TMsgDlgButtons() << mbOK,0);
      return 0;
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
      return 0;
    }
    FileRead(inH, buf, fl);
    FileClose(inH);

    //Пишем данные о структуре в выходной файл
    if(FileExists(FileName1)) DeleteFile(FileName1);
    if((outH=FileCreate(FileName1)) < 0)
    { MessageDlg("Ошибка создания выходного файла",mtError,TMsgDlgButtons() << mbOK,0);
      delete buf;
      return 0;
    }
    FileWrite(outH,buf,fl);
    FileClose(outH);
    delete buf;

    if(!FileExists(FileName1))
    { MessageDlg("Ошибка создания файла выгрузки",mtError,TMsgDlgButtons() << mbOK,0);
      return 0;
    }

    //Инициализируем ADO подключение
    path=ExtractFilePath(FileName1);
    str="FILE NAME="+SourceName+";";
    ADOConnection->ConnectionString=str;
    try
    {
      ADOConnection->Connected=true;
    }
    catch (Exception &exc)
    { MessageDlg("Ошибка инициализации ADO подключения\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return 0;
    }

      ExportDS->Close();
      ExportDS->SQLs->SelectSQL->Clear();
      sql="select distinct g.LCHET,g.LCHET1,g.NEOPL,g.SUMMA,g.C,g.DOC,g.METKA,g.PNN from SGB g where g.PRICH <> ''";
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.kassa= 0";

      ExportDS->SQLs->SelectSQL->Add(sql);
      try
      {
        ExportDS->Open();
      }
      catch(const Exception &exc)
      { MessageDlg("Ошибка ExportDS->Open()\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
        return 0;
      }

    ExportDS->Last();
    countneople=ExportDS->RecordCount;
    Indicator->MaxValue=countneople;

    ExportDS->First();
    id=0;
    while(!ExportDS->Eof)
    {
        Q->Close();
        Q->SQL->Clear();
        sql="insert into "+dbfFile1+" (LCHET,R1,NEOPL,SUM,DATA,DATA_DO,ORG,\
        PNN,SUM_BASE,SUM_INC,SUM_ACC,SUM_POV,SUM_DOUB,SUM_DELTA,SUM_DELTA2,IST_BASE,IST_INC,IST_ACC,\
        IST_POV,IST_DOUB,IST_DELTA,IST_DELTA2) values(";
        sql+=IntToStr(ExportDS->FieldByName("LCHET")->AsInteger)+",";
        if (ExportDS->FieldByName("LCHET1")->AsString.Trim() == "раздел 1") sql+="1,"; else sql+="0,";
        sql+=IntToStr(ExportDS->FieldByName("NEOPL")->AsInteger)+",";
        sql+=AnsiString().sprintf("%.02lf",ExportDS->FieldByName("SUMMA")->AsFloat)+",'";
        sql+=ExportDS->FieldByName("C")->AsDateTime.DateString()+"','";
        sql+=ExportDS->FieldByName("DOC")->AsDateTime.DateString()+"',";
        sql+=IntToStr(ExportDS->FieldByName("METKA")->AsInteger)+",";
        sql+=IntToStr(ExportDS->FieldByName("PNN")->AsInteger)+",";
        sql+=AnsiString().sprintf("%.02lf",summa)+",";
        sql+=AnsiString().sprintf("%.02lf",summa)+",";
        sql+=AnsiString().sprintf("%.02lf",summa)+",";
        sql+=AnsiString().sprintf("%.02lf",summa)+",";
        sql+=AnsiString().sprintf("%.02lf",summa)+",";
        sql+=AnsiString().sprintf("%.02lf",summa)+",";
        sql+=AnsiString().sprintf("%.02lf",summa)+",";
        sql+=IntToStr(kol)+",";
        sql+=IntToStr(kol)+",";
        sql+=IntToStr(kol)+",";
        sql+=IntToStr(kol)+",";
        sql+=IntToStr(kol)+",";
        sql+=IntToStr(kol)+",";
        sql+=IntToStr(kol)+")";
        Q->SQL->Add(sql);
        try
        {
          Q->ExecSQL();
        }
        catch(const Exception &exc)
        { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
          ADOConnection->Connected=false;
          return 0;
        }

      ExportDS->Next();
      id++;
      Indicator->Progress = id;
    }
    ExportDS->Close();

// экспорт из выплатной базы

      ExportDS1->Close();
      ExportDS1->SQLs->SelectSQL->Clear();
      sql="select distinct g.* from NDOST g where";
      sql+=" g.lchet not in(select lchet from sgb )";
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);

      ExportDS1->SQLs->SelectSQL->Add(sql);
      try
      {
        ExportDS1->Open();
      }
      catch(const Exception &exc)
      {
        MessageDlg("Ошибка ExportDS->Open()\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
        return 0;
      }

    ExportDS1->Last();
    Indicator->MaxValue=ExportDS1->RecordCount;
    countneople+=ExportDS1->RecordCount;
    if ( countneoplr != countneople )
    {
    return 4;
    }
    int cz=0;
    ExportDS1->First();
    while(!ExportDS1->Eof)
    {
        Q->Close();
        Q->SQL->Clear();
        sql="insert into "+dbfFile1+" (LCHET,R1,NEOPL,SUM,DATA,DATA_DO,ORG,\
        PNN,SUM_BASE,SUM_INC,SUM_ACC,SUM_POV,SUM_DOUB,SUM_DELTA,SUM_DELTA2,IST_BASE,IST_INC,IST_ACC,\
        IST_POV,IST_DOUB,IST_DELTA,IST_DELTA2) values(";
        sql+=IntToStr(ExportDS1->FieldByName("LCHET")->AsInteger)+",";
        if (ExportDS1->FieldByName("LCHET1")->AsString.Trim() == "раздел 1") sql+="1,"; else sql+="0,";
        sql+=IntToStr(ExportDS1->FieldByName("NEOPL")->AsInteger)+",";
        sql+=AnsiString().sprintf("%.02lf",ExportDS1->FieldByName("SUMMA")->AsFloat)+",'";
        sql+=ExportDS1->FieldByName("C")->AsDateTime.DateString()+"','";
        sql+=ExportDS1->FieldByName("DOC")->AsDateTime.DateString()+"',";
        sql+=IntToStr(ExportDS1->FieldByName("METKA")->AsInteger)+",";
        sql+=IntToStr(ExportDS1->FieldByName("PNN")->AsInteger)+",";
        sql+=AnsiString().sprintf("%.02lf",summa)+",";
        sql+=AnsiString().sprintf("%.02lf",summa)+",";
        sql+=AnsiString().sprintf("%.02lf",summa)+",";
        sql+=AnsiString().sprintf("%.02lf",summa)+",";
        sql+=AnsiString().sprintf("%.02lf",summa)+",";
        sql+=AnsiString().sprintf("%.02lf",summa)+",";
        sql+=AnsiString().sprintf("%.02lf",summa)+",";
        sql+=IntToStr(kol)+",";
        sql+=IntToStr(kol)+",";
        sql+=IntToStr(kol)+",";
        sql+=IntToStr(kol)+",";
        sql+=IntToStr(kol)+",";
        sql+=IntToStr(kol)+",";
        sql+=IntToStr(kol)+")";
        Q->SQL->Add(sql);
        try
        {
          Q->ExecSQL();
        }
        catch(const Exception &exc)
        { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
          ADOConnection->Connected=false;
          return 0;
        }

      ExportDS1->Next();
      id++;
      cz++;
      Indicator->Progress = cz;
    }
    ExportDS1->Close();
    Indicator->Progress = 0;
    ADOConnection->Connected=false;
    countzap=countzap+id;

    if ( countpodlr != countzap )
    {
    return 4;
    }


// записывaем в журнал импорта экспорта запись об импорте

  TDateTime dt=Date();
  dt.DecodeDate(&y,&m,&d);
  str="Произведен экспорт данных в файлы: " + dbfFile +"," + dbfFile1 + " всего записей - "+IntToStr(countzap);
  TempQ->Close();
  TempQ->SQL->Clear();

  sql="insert into IMPORT_DOCUMENTS_TABLE (ID,ID_NUMBER,SUMZAP,ID_DATE) values(GEN_ID(GEN_IMPORT_DOCUMENTS_TABLE_ID,1),'"+str+"',"+IntToStr(countzap)+",'"+dt.DateString()+"')";
  TempQ->SQL->Add(sql);
  TempQ->Transaction->StartTransaction();
  try
  {
    TempQ->ExecQuery();
  }
  catch(const Exception &exc)
  {
  MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  TempQ->Transaction->Rollback();
  return 0;
  }
  TempQ->Transaction->Commit();

  TpFIBQuery * TQJ=SaleBookDM->TempQuery;

  TQJ->Close();
  TQJ->SQL->Clear();
  str="select GEN_ID(GEN_ACTIONS_JOURNAL_ID,1) as ID from RDB$DATABASE";
  TQJ->SQL->Add(str);
  try
  {
    TQJ->ExecQuery();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка select GEN_ID(GEN_ACTIONS_JOURNAL_ID,1) as ID from RDB$DATABASE\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return 0;
  }
  int idt=TQJ->FieldByName("ID")->AsInteger;
  TQJ->Close();
  str="Произведен экспорт данных в файлы: " + dbfFile +"," + dbfFile1 + " всего записей - "+IntToStr(countzap) + " из них оплаченных - "+IntToStr(countople)+ " из них неоплаченных - "+IntToStr(countneople);
  SaleBookDM->TT->StartTransaction();
  if(SaleBookDM->AddRecordToActionsJournal(AddExport,str,SaleBookDM->TT)==true) SaleBookDM->TT->Commit();  else SaleBookDM->TT->Rollback();

    s="Экспорт данных завершен";
    if(id > 0) s+=".\nДанные успешно выгружены в файлы "+FileName + "," +FileName1+ " всего записей - "+IntToStr(countzap) + " из них оплаченных - "+IntToStr(countople)+ " из них неоплаченных - "+IntToStr(countneople);
    MessageDlg(s,mtInformation,TMsgDlgButtons() << mbOK,0);
    return 1;
}


void __fastcall TPrntDataForm::ViewButtonClick(TObject *Sender)
{
AnsiString sql;
AnsiString IndOps;
int k=0;
int c_opl=0;
double opl=0.00;
int c_neopl=0;
double neopl=0.00;
int r1,r2,r3,r4,r5,r6,r7,r8;
double d1,d2,d3,d4,d5,d6,d7,d8;
int ir1,ir2,ir3,ir4,ir5,ir6,ir7,ir8;
double dr1,dr2,dr3,dr4,dr5,dr6,dr7,dr8;
int countoplr,countople,countneoplr,countneople,countpodlr;
unsigned short dvp,yvp,mvp;
int date1,date2;
AnsiString Folder;
AnsiString fileOut,s;
int countzap=0;
TDateTime dprn;
unsigned short dt,yt,mt;
TDateTime lockDate;
unsigned short yl,ml,dl;
TDateTime today;
double sumopltek,sumoplpro;
int kolopltek,koloplpro;


if(Application->FindComponent("AccountsJournalForm")) dprn=AccountsJournalForm->getDate1(); else dprn=Date();
dprn.DecodeDate(&yvp,&mvp,&dvp);

lockDate=SaleBookDM->GetConstValue(SaleBookDM->OrganizationID,"LOCK_EDIT_DATE");
lockDate.DecodeDate(&yl,&ml,&dl);

if (mvp==ml) today=Date(); else today=Date()+10;
today.DecodeDate(&yt,&mt,&dt);

date1=StrToInt(CNEdit->Text);
date2=StrToInt(CNEdit1->Text);


TpFIBDataSet *DSZ;
DSZ=((TpFIBDataSet*)(AccountsJournalForm->AccountsGrid->DataSource->DataSet));


    TDataSet *Count=AccountsJournalForm->AccountsGrid->DataSource->DataSet;
    ConstToDate=Count->FieldByName("COUNT_DATE")->AsDateTime;
    OrgID=Count->FieldByName("ORG_ID")->AsInteger;
    if (OrgID==0)
    {
    OrgID=1;
    ConstToDate=today;
    }

  //Печать задания
  if(CountButton->Checked)
  {
  Folder=MainForm->WorkDir+"Out\\";
  fileOut="report.rtf";
  SetCurrentDir(Folder);
  if (FileExists(fileOut)) DeleteFile(fileOut);
  RTFExport->ShowDialog = true;
  RTFExport->OpenAfterExport = true;
  RTFExport->DefaultPath=Folder;
  RTFExport->FileName=fileOut;


  // проверка что задания закрыта!!!
  //Проверяем не закрыт ли задания для редактирования
 if (DSZ->RecordCount>0)
 {
  SaleBookDM->TempQuery->Close();
  SaleBookDM->TempQuery->SQL->Clear();
  if (mvp==ml)
  {
  sql="select EDIT_KEY from ACCOUNTS where ORG_ID="+IntToStr(Count->FieldByName("ORG_ID")->AsInteger);
  sql+=" and COUNT_DATE='"+Count->FieldByName("COUNT_DATE")->AsString+"'";
  sql+=" and COUNT_NUMBER="+Count->FieldByName("COUNT_NUMBER")->AsString;
  SaleBookDM->TempQuery->SQL->Add(sql);
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
    MessageDlg("Не найдена нужная запись (select EDIT_KEY from ACCOUNTS)",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(SaleBookDM->TempQuery->FieldByName("EDIT_KEY")->AsInteger==0)
  {
    MessageDlg("Задание редактируется! Для печати данного задания необходимо закончить редактирования задания и закрыть его!!!",mtWarning,TMsgDlgButtons() << mbOK,0);
    return;
  }
  }
 }
  for (int cidm=0;cidm<20;cidm++)
  {
  Massiv[cidm]=0;
  }

  if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель") sql="select * from USERS where ID="+IntToStr(SaleBookDM->UserID); else sql="select * from USERS where ID="+IntToStr(DSZ->FieldByName("USER_ID")->AsInteger);
  TempQ->Close();
  TempQ->SQL->Clear();
  TempQ->SQL->Add(sql);
  try
  {
    TempQ->ExecQuery();
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  }
  IndOps=TempQ->FieldByName("U_INDEX")->AsString;

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

    frxReport->DataSet=frxHeadDS;
    HeadDS->Close();
    HeadDS->SQLs->SelectSQL->Clear();

      sql="select a.*,";
      sql+=" u.LOGIN";
      if (mvp==ml) sql+=" from ACCOUNTS a "; else sql+=" from ACCOUNTS_A a ";
      sql+=" left join USERS u on u.ID=a.USER_ID";
      sql+=" where";
      sql+=" a.ORG_ID="+IntToStr(OrgID);
      sql+=" and a.COUNT_DATE='"+Count->FieldByName("COUNT_DATE")->AsString+"'";
      sql+=" and a.COUNT_NUMBER="+Count->FieldByName("COUNT_NUMBER")->AsString;
      HeadDS->SQLs->SelectSQL->Add(sql);
      try
      {
        HeadDS->Open();
      }
      catch(const Exception &exc)
      { MessageDlg("Ошибка HeadDS->Open()\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
        return;
      }
      //Табличная часть задания

      TempQ->Close();
      TempQ->SQL->Clear();
      sql="delete from RESULT";
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка удаления записей из таблицы result \n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      }

      for(int r=0; r<=KolOps; r++)
      {

      c_opl=0;
      opl=0.00;
      c_neopl=0;
      neopl=0.00;

      TempQ->Close();
      TempQ->SQL->Clear();
      if (mvp==ml) sql="select count (distinct g.lchet) as CR  from SGB g where g.PRICH = ''"; else sql="select count (distinct g.lchet) as CR  from SGB_A g where g.PRICH = ''";
      sql+=" and g.ORG_ID="+Count->FieldByName("ORG_ID")->AsString;
      sql+=" and g.COUNT_DATE='"+Count->FieldByName("COUNT_DATE")->AsString+"'";
      sql+=" and g.COUNT_NUMBER="+Count->FieldByName("COUNT_NUMBER")->AsString;
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.LCHET1 NOT IN ('Прошврем','раздел 1')";
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("CR")->AsInteger > 0)  c_opl=TempQ->FieldByName("CR")->AsInteger;

      TempQ->Close();
      TempQ->SQL->Clear();
      if (mvp==ml) sql="select distinct sum (g.summa) as summav from SGB g where g.PRICH = ''"; else sql="select distinct sum (g.summa) as summav from SGB_A g where g.PRICH = ''";
      sql+=" and g.ORG_ID="+Count->FieldByName("ORG_ID")->AsString;
      sql+=" and g.COUNT_DATE='"+Count->FieldByName("COUNT_DATE")->AsString+"'";
      sql+=" and g.COUNT_NUMBER="+Count->FieldByName("COUNT_NUMBER")->AsString;
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) opl=TempQ->FieldByName("SUMMAV")->AsFloat;


      TempQ->Close();
      TempQ->SQL->Clear();
      if (mvp==ml) sql="select count (distinct g.lchet) as CR  from SGB g where g.PRICH <> ''"; else sql="select count (distinct g.lchet) as CR  from SGB_A g where g.PRICH <> ''";
      sql+=" and g.ORG_ID="+Count->FieldByName("ORG_ID")->AsString;
      sql+=" and g.COUNT_DATE='"+Count->FieldByName("COUNT_DATE")->AsString+"'";
      sql+=" and g.COUNT_NUMBER="+Count->FieldByName("COUNT_NUMBER")->AsString;
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.LCHET1 NOT IN ('Прошврем','раздел 1')";
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("CR")->AsInteger > 0)  c_neopl=TempQ->FieldByName("CR")->AsInteger;

      TempQ->Close();
      TempQ->SQL->Clear();
      if (mvp==ml) sql="select distinct sum (g.summa) as summav from SGB g where g.PRICH <> ''"; else sql="select distinct sum (g.summa) as summav from SGB_A g where g.PRICH <> ''";
      sql+=" and g.ORG_ID="+Count->FieldByName("ORG_ID")->AsString;
      sql+=" and g.COUNT_DATE='"+Count->FieldByName("COUNT_DATE")->AsString+"'";
      sql+=" and g.COUNT_NUMBER="+Count->FieldByName("COUNT_NUMBER")->AsString;
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) neopl=TempQ->FieldByName("SUMMAV")->AsFloat;

      if (c_neopl > 0 || c_opl > 0)
      {
      TempQ->Close();
      TempQ->SQL->Clear();
      sql="insert into RESULT(OPS,OPL,NEOPL,COUNT_OPL,COUNT_NEOPL) values(";
      sql+=IntToStr(Massiv[r])+",";
      sql+=AnsiString().sprintf("%.02lf",opl)+",";
      sql+=AnsiString().sprintf("%.02lf",neopl)+",";
      sql+=IntToStr(c_opl)+",";
      sql+=IntToStr(c_neopl)+")";
      TempQ->SQL->Add(sql);
      TempQ->ExecQuery();
      }

      }

      TableDS->Close();
      TableDS->SQLs->SelectSQL->Clear();
      sql="select g.* ";
      sql+=" from RESULT g";
      TableDS->SQLs->SelectSQL->Add(sql);
      try
      {
        TableDS->Open();
      }
      catch(const Exception &exc)
      { MessageDlg("Ошибка TableDS->Open()\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
        return;
      }

          frxReport1->LoadFromFile(MainForm->WorkDir+"Reports\\Count.fr3");
          frxReport1->PrepareReport(false);
          frxReport1->ShowPreparedReport();
  }

  //Печать отчета
  if(InvoiceButton->Checked)
  {
  Folder=MainForm->WorkDir+"Send\\";
  SetCurrentDir(Folder);
  s=AnsiString().sprintf("%02d-%d",mvp,yvp);
  fileOut="reportof";
  fileOut+=s+".rtf";
  if(FileExists(fileOut))
  {
   if(!Filedate(fileOut)) DeleteFile(fileOut);
  }
  RTFExport->ShowDialog = false;
  RTFExport->OpenAfterExport = false;

  RTFExport->DefaultPath=Folder;
  RTFExport->FileName=fileOut;

 if (DSZ->RecordCount>0)
 {
  if (mvp==ml){
  if(SaleBookDM->UserRole=="Администратор" || SaleBookDM->UserRole=="Руководитель")
  {
  SaleBookDM->TempQuery->Close();
  SaleBookDM->TempQuery->SQL->Clear();
  sql="select MIN(EDIT_KEY) as SEK from ACCOUNTS where M="+IntToStr(mvp);
  sql+=" and Y="+IntToStr(yvp);
  SaleBookDM->TempQuery->SQL->Add(sql);
  try
  {
    SaleBookDM->TempQuery->ExecQuery();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(SaleBookDM->TempQuery->FieldByName("SEK")->AsInteger==0)
  {
    MessageDlg("Задания редактируется! Для печати данного отчета необходимо закончить редактирования всех задания и закрыть их!!!",mtWarning,TMsgDlgButtons() << mbOK,0);
    return;
  }
  }
  }
 }
  for (int cidm=0;cidm<20;cidm++)
  {
  Massiv[cidm]=0;
  }

  sql="select * from USERS where ID="+IntToStr(SaleBookDM->UserID);
  TempQ->Close();
  TempQ->SQL->Clear();
  TempQ->SQL->Add(sql);
  try
  {
    TempQ->ExecQuery();
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  }
  IndOps=TempQ->FieldByName("U_INDEX")->AsString;

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

      TempQ->Close();
      TempQ->SQL->Clear();
      sql="delete from REPRES";
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка удаления записей из таблицы REPRES\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);\
      return;
      }


      for(int r=0; r<=KolOps; r++)
      {

      r1=0;
      d1=0.00;
      r2=0;
      d2=0.00;
      r3=0;
      d3=0.00;
      r4=0;
      d4=0.00;
      r5=0;
      d5=0.00;
      r6=0;
      d6=0.00;
      r7=0;
      d7=0.00;
      r8=0;
      d8=0.00;
      sumopltek=0.00;
      sumoplpro=0.00;
      kolopltek=0;
      koloplpro=0;


      TempQ->Close();
      TempQ->SQL->Clear();
      if (mvp==ml) sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from NDOST g where g.LCHET1 NOT IN ('Прошврем','раздел 1')"; else sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from NDOST_A g where g.LCHET1 NOT IN ('Прошврем','раздел 1')";
      sql+=" and g.D_VIPL>="+IntToStr(date1);
      sql+=" and g.D_VIPL<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("CR")->AsInteger > 0)  r1=TempQ->FieldByName("CR")->AsInteger;
      if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) d1=TempQ->FieldByName("SUMMAV")->AsFloat;

      TempQ->Close();
      TempQ->SQL->Clear();
      sql="";
      if (mvp==ml) sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from NDOST g where LCHET1 IN ('Прошврем','раздел 1')"; else sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from NDOST_A g where LCHET1 IN ('Прошврем','раздел 1')";
      sql+=" and g.D_VIPL>="+IntToStr(date1);
      sql+=" and g.D_VIPL<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("CR")->AsInteger > 0)  r2=TempQ->FieldByName("CR")->AsInteger;
      if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) d2=TempQ->FieldByName("SUMMAV")->AsFloat;

// неоплаченные из заданий

      TempQ->Close();
      TempQ->SQL->Clear();
      if (mvp==ml) sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from SGB g where LCHET1 NOT IN ('Прошврем','раздел 1') "; else sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from SGB_A g where LCHET1 NOT IN ('Прошврем','раздел 1') ";
      sql+=" and g.FAKT_DAT>="+IntToStr(date1);
      sql+=" and g.FAKT_DAT<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      sql+= " and ((UPPER(PRICH) <> UPPER('н/д')) AND (UPPER(PRICH) <> UPPER('')))";
      sql+=" and g.KASSA=0";
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("CR")->AsInteger > 0)  r3=TempQ->FieldByName("CR")->AsInteger;
      if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) d3=TempQ->FieldByName("SUMMAV")->AsFloat;

// нет дома брать из ПРОЦЕДУРЫ!!!

     ConstProc->Close();
     if (mvp==ml) ConstProc->StoredProcName="SUM_BY_NH"; else ConstProc->StoredProcName="SUM_BY_NHA";

     ConstProc->ParamByName("DATE1")->AsInteger=date1;
     ConstProc->ParamByName("DATE2")->AsInteger=date2;
     ConstProc->ParamByName("MVP")->AsInteger=mvp;
     ConstProc->ParamByName("YVP")->AsInteger=yvp;
     ConstProc->ParamByName("METKA")->AsInteger=Massiv[r];
     ConstProc->Prepare();
     try
     {
     ConstProc->ExecProc();
     }
     catch(const Exception &exc)
     {
      MessageDlg("Ошибка ConstProc->ExecProc()\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
     }
      sumopltek=ConstProc->ParamByName("SUMOPLTEK")->AsFloat;
      sumoplpro=ConstProc->ParamByName("SUMOPLPRO")->AsFloat;
      kolopltek=ConstProc->ParamByName("KOLOPLTEK")->AsInteger;
      koloplpro=ConstProc->ParamByName("KOLOPLPRO")->AsInteger;
      ConstProc->Close();
      d3=d3+sumopltek;
      r3=r3+kolopltek;

// неоплаченные из выплатной базы

      TempQ->Close();
      TempQ->SQL->Clear();
      if (mvp==ml) sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from NDOST g where LCHET1 NOT IN ('Прошврем','раздел 1') "; else sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from NDOST_A g where LCHET1 NOT IN ('Прошврем','раздел 1') ";
      if (mvp==ml) sql+=" and g.lchet not in(select lchet from sgb where sgb.M=" +IntToStr(mvp) + " and sgb.Y=" +IntToStr(yvp); else sql+=" and g.lchet not in(select lchet from sgb_a where sgb_a.M=" +IntToStr(mvp) + " and sgb_a.Y=" +IntToStr(yvp);
      sql+=" ) and g.D_VIPL>="+IntToStr(date1);
      sql+=" and g.D_VIPL<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("CR")->AsInteger > 0)  r3=r3+TempQ->FieldByName("CR")->AsInteger;
      if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) d3=d3+TempQ->FieldByName("SUMMAV")->AsFloat;

// неоплаченные из заданий

      TempQ->Close();
      TempQ->SQL->Clear();
      sql="";
      if (mvp==ml) sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from SGB g where LCHET1 IN ('Прошврем','раздел 1') "; else sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from SGB_A g where LCHET1 IN ('Прошврем','раздел 1') ";
      sql+=" and g.FAKT_DAT>="+IntToStr(date1);
      sql+=" and g.FAKT_DAT<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      sql+= " and ((UPPER(PRICH) <> UPPER('н/д')) AND (UPPER(PRICH) <> UPPER('')))";
      sql+=" and g.KASSA=0";
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("CR")->AsInteger > 0)  r4=TempQ->FieldByName("CR")->AsInteger;
      if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) d4=TempQ->FieldByName("SUMMAV")->AsFloat;


      d4=d4+sumoplpro;
      r4=r4+koloplpro;

// неоплаченные из выплатной базы


      TempQ->Close();
      TempQ->SQL->Clear();
      sql="";
      if (mvp==ml)
      {
      sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from NDOST g where LCHET1 IN ('Прошврем','раздел 1') ";
      }
      else
      {
      sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from NDOST_A g where LCHET1 IN ('Прошврем','раздел 1') ";
      }
      if (mvp==ml) sql+=" and g.lchet not in(select lchet from sgb where sgb.M=" +IntToStr(mvp) + " and sgb.Y=" +IntToStr(yvp); else sql+=" and g.lchet not in(select lchet from sgb_a where sgb_a.M=" +IntToStr(mvp) + " and sgb_a.Y=" +IntToStr(yvp);
      sql+=" ) and g.D_VIPL>="+IntToStr(date1);
      sql+=" and g.D_VIPL<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("CR")->AsInteger > 0)  r4=r4+TempQ->FieldByName("CR")->AsInteger;
      if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) d4=d4+TempQ->FieldByName("SUMMAV")->AsFloat;

// оплаченные

      TempQ->Close();
      TempQ->SQL->Clear();
      if (mvp==ml) sql="select count (distinct g.lchet) as CR from SGB g where g.PRICH = ''"; else sql="select count (distinct g.lchet) as CR from SGB_A g where g.PRICH = ''";
      sql+=" and g.FAKT_DAT>="+IntToStr(date1);
      sql+=" and g.FAKT_DAT<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("CR")->AsInteger > 0)  r5=TempQ->FieldByName("CR")->AsInteger;

      TempQ->Close();
      TempQ->SQL->Clear();
      if (mvp==ml) sql="select distinct sum (g.summa) as summav from SGB g where g.PRICH = ''"; else sql="select distinct sum (g.summa) as summav from SGB_A g where g.PRICH = ''";
      sql+=" and g.FAKT_DAT>="+IntToStr(date1);
      sql+=" and g.FAKT_DAT<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) d5=TempQ->FieldByName("SUMMAV")->AsFloat;

      TempQ->Close();
      TempQ->SQL->Clear();
      sql="";
      if (mvp==ml) sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from SGB g where LCHET1 NOT IN ('Прошврем','раздел 1') AND g.PRICH = ''"; else sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from SGB_A g where LCHET1 NOT IN ('Прошврем','раздел 1') AND g.PRICH = ''";
      sql+=" and g.FAKT_DAT>="+IntToStr(date1);
      sql+=" and g.FAKT_DAT<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("CR")->AsInteger > 0)  r6=TempQ->FieldByName("CR")->AsInteger;
      if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) d6=TempQ->FieldByName("SUMMAV")->AsFloat;

      TempQ->Close();
      TempQ->SQL->Clear();
      sql="";
      if (mvp==ml) sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from SGB g where LCHET1 IN ('Прошврем','раздел 1') AND g.PRICH = ''"; else sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from SGB_A g where LCHET1 IN ('Прошврем','раздел 1') AND g.PRICH = ''";
      sql+=" and g.FAKT_DAT>="+IntToStr(date1);
      sql+=" and g.FAKT_DAT<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("CR")->AsInteger > 0)  r7=TempQ->FieldByName("CR")->AsInteger;
      if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) d7=TempQ->FieldByName("SUMMAV")->AsFloat;

      TempQ->Close();
      TempQ->SQL->Clear();
      sql="insert into REPRES(OPS,COUNT_TOTAL,COUNT_OPL,COUNT_NEOPL,COUNT_TOTALI,COUNT_OPLI,COUNT_NEOPLI,COUNT_TEK,COUNT_PR,COUNT_RAZ,COUNT_NEOPLP,\
      COUNT_FI,COUNT_FD,COUNT_NEOPLG,COUNT_OPLM,COUNT_OPLT,COUNT_OPLR) values(";
      sql+=IntToStr(Massiv[r])+",";
      sql+=AnsiString().sprintf("%.02lf",d1)+",";
      sql+=AnsiString().sprintf("%.02lf",d2)+",";
      sql+=AnsiString().sprintf("%.02lf",d3)+",";
      sql+=IntToStr(r1)+",";
      sql+=IntToStr(r2)+",";
      sql+=IntToStr(r3)+",";
      sql+=AnsiString().sprintf("%.02lf",d5)+",";
      sql+=AnsiString().sprintf("%.02lf",d6)+",";
      sql+=AnsiString().sprintf("%.02lf",d7)+",";
      sql+=AnsiString().sprintf("%.02lf",d4)+",";
      sql+=IntToStr(r8)+",";
      sql+=AnsiString().sprintf("%.02lf",d8)+",";
      sql+=IntToStr(r4)+",";
      sql+=IntToStr(r6)+",";
      sql+=IntToStr(r6)+",";
      sql+=IntToStr(r7)+")";
       TempQ->SQL->Add(sql);
      TempQ->ExecQuery();
      }

    if (mvp==ml){
    if (date1==1 && date2>=22)
    {
// здесь необходима ПОЛНАЯ проверка БД!!!

    if ( CheckDB() == 0 ){
    MessageDlg("Сбой в компоненте TempQuery!!!",mtInformation,TMsgDlgButtons() << mbOK,0);
    return;
    }

    if ( CheckDB() == 1 ){
     if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole=="Руководитель")
      {
       MessageDlg("Обнаружена ошибка в БД!!! Необходимо сделать проверку БД пользователем с ролью Администратора или Руководителя через меню Администрирование->Проверить БД !!! Обратитесь пожалуйста к Вашему руководителю имеющую права Администратора или Руководителя в ИС Инспектор",mtInformation,TMsgDlgButtons() << mbOK,0);
      }else
      {
       MessageDlg("Обнаружена ошибка в БД!!! Необходимо сделать проверку БД через меню Администрирование->Проверить БД !!!",mtInformation,TMsgDlgButtons() << mbOK,0);
      }
      return;
    }
    }
    }
      DSREPRES->Close();
      DSREPRES->SQLs->SelectSQL->Clear();
      sql="select g.* ";
      sql+=" from REPRES g";
      DSREPRES->SQLs->SelectSQL->Add(sql);
      try
      {
        DSREPRES->Open();
      }
      catch(const Exception &exc)
      {
        MessageDlg("Ошибка TableDS->Open()\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
        return;
      }

          frxReport->LoadFromFile(MainForm->WorkDir+"Reports\\Count1.fr3");
          frxReport->PrepareReport(true);
          frxReport->ShowPreparedReport();
          if (mvp==ml){
          if (date1==1 && date2>=22)
          {
          frxReport->Export(RTFExport);
          MessageDlg("Данный отчет автоматически экспортирован в файл " + fileOut + " из папки " + Folder ,mtWarning,TMsgDlgButtons() << mbOK,0);
          }
          }
  }

    //Печать сведения
  if(JournalButton->Checked)
  {
  Folder=MainForm->WorkDir+"Send\\";
  s=AnsiString().sprintf("%02d-%d",mvp,yvp);
  fileOut="svedof";
  fileOut+=s+".rtf";
  SetCurrentDir(Folder);
  if(FileExists(fileOut))
  {
   if(!Filedate(fileOut)) DeleteFile(fileOut);
  }
  RTFExport->ShowDialog = false;
  RTFExport->OpenAfterExport = false;

  RTFExport->DefaultPath=Folder;
  RTFExport->FileName=fileOut;
 if (DSZ->RecordCount>0)
 {
  if (mvp==ml)
  {
  if(SaleBookDM->UserRole=="Администратор" || SaleBookDM->UserRole=="Руководитель")
  {
  SaleBookDM->TempQuery->Close();
  SaleBookDM->TempQuery->SQL->Clear();
  sql="select MIN(EDIT_KEY) as SEK from ACCOUNTS where M="+IntToStr(mvp);
  sql+=" and Y="+IntToStr(yvp);
  SaleBookDM->TempQuery->SQL->Add(sql);
  try
  {
    SaleBookDM->TempQuery->ExecQuery();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  if(SaleBookDM->TempQuery->FieldByName("SEK")->AsInteger==0)
  {
    MessageDlg("Задания редактируется! Для печати данного отчета необходимо закончить редактирования всех задания и закрыть их!!!",mtWarning,TMsgDlgButtons() << mbOK,0);
    return;
  }

  }
  }
 }
  for (int cidm=0;cidm<20;cidm++)
  {
  Massiv[cidm]=0;
  }

  sql="select * from USERS where ID="+IntToStr(SaleBookDM->UserID);
  TempQ->Close();
  TempQ->SQL->Clear();
  TempQ->SQL->Add(sql);
  try
  {
    TempQ->ExecQuery();
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  }
  IndOps=TempQ->FieldByName("U_INDEX")->AsString;

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


      TempQ->Close();
      TempQ->SQL->Clear();
      sql="delete from REPRES";
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка удаления записей из таблицы REPRES\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      }

      ir1=0;
      dr1=0.00;
      ir2=0;
      dr2=0.00;
      ir3=0;
      dr3=0.00;
      ir4=0;
      dr4=0.00;
      ir5=0;
      dr5=0.00;
      ir6=0;
      dr6=0.00;
      ir7=0;
      dr7=0.00;
      ir8=0;
      dr8=0.00;
      sumopltek=0.00;
      sumoplpro=0.00;
      kolopltek=0;
      koloplpro=0;

      for(int r=0; r<=KolOps; r++)
      {

      r1=0;
      d1=0.00;
      r2=0;
      d2=0.00;
      r3=0;
      d3=0.00;
      r4=0;
      d4=0.00;
      r5=0;
      d5=0.00;
      r6=0;
      d6=0.00;
      r7=0;
      d7=0.00;
      r8=0;
      d8=0.00;


      TempQ->Close();
      TempQ->SQL->Clear();
      if (mvp==ml) sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from NDOST g where g.LCHET1 NOT IN ('Прошврем','раздел 1')"; else sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from NDOST_A g where g.LCHET1 NOT IN ('Прошврем','раздел 1')";
      sql+=" and g.D_VIPL>="+IntToStr(date1);
      sql+=" and g.D_VIPL<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("CR")->AsInteger > 0)  r1=TempQ->FieldByName("CR")->AsInteger;
      if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) d1=TempQ->FieldByName("SUMMAV")->AsFloat;

      ir1+=r1;
      dr1+=d1;

      TempQ->Close();
      TempQ->SQL->Clear();
      sql="";
      if (mvp==ml) sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from NDOST g where LCHET1 IN ('Прошврем','раздел 1')"; else sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from NDOST_A g where LCHET1 IN ('Прошврем','раздел 1')";
      sql+=" and g.D_VIPL>="+IntToStr(date1);
      sql+=" and g.D_VIPL<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("CR")->AsInteger > 0)  r2=TempQ->FieldByName("CR")->AsInteger;
      if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) d2=TempQ->FieldByName("SUMMAV")->AsFloat;

      ir2+=r2;
      dr2+=d2;

// неоплаченные из заданий

      TempQ->Close();
      TempQ->SQL->Clear();
      if (mvp==ml) sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from SGB g where LCHET1 NOT IN ('Прошврем','раздел 1') "; else sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from SGB_A g where LCHET1 NOT IN ('Прошврем','раздел 1') ";
      sql+=" and g.FAKT_DAT>="+IntToStr(date1);
      sql+=" and g.FAKT_DAT<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      sql+= "and ((UPPER(PRICH) <> UPPER('н/д')) AND (UPPER(PRICH) <> UPPER('')))";
      sql+=" and g.KASSA=0";
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("CR")->AsInteger > 0)  r3=TempQ->FieldByName("CR")->AsInteger;
      if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) d3=TempQ->FieldByName("SUMMAV")->AsFloat;

// нет дома брать из ПРОЦЕДУРЫ!!!

     ConstProc->Close();
     if (mvp==ml) ConstProc->StoredProcName="SUM_BY_NH"; else ConstProc->StoredProcName="SUM_BY_NHA";

     ConstProc->ParamByName("DATE1")->AsInteger=date1;
     ConstProc->ParamByName("DATE2")->AsInteger=date2;
     ConstProc->ParamByName("MVP")->AsInteger=mvp;
     ConstProc->ParamByName("YVP")->AsInteger=yvp;
     ConstProc->ParamByName("METKA")->AsInteger=Massiv[r];
     ConstProc->Prepare();
     try
     {
     ConstProc->ExecProc();
     }
     catch(const Exception &exc)
     {
      MessageDlg("Ошибка ConstProc->ExecProc()\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
     }
      sumopltek=ConstProc->ParamByName("SUMOPLTEK")->AsFloat;
      sumoplpro=ConstProc->ParamByName("SUMOPLPRO")->AsFloat;
      kolopltek=ConstProc->ParamByName("KOLOPLTEK")->AsInteger;
      koloplpro=ConstProc->ParamByName("KOLOPLPRO")->AsInteger;
      ConstProc->Close();
      d3=d3+sumopltek;
      r3=r3+kolopltek;

// неоплата из базы

      TempQ->Close();
      TempQ->SQL->Clear();
      if (mvp==ml) sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from NDOST g where LCHET1 NOT IN ('Прошврем','раздел 1') "; else sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from NDOST_A g where LCHET1 NOT IN ('Прошврем','раздел 1') ";
      if (mvp==ml) sql+=" and g.lchet not in(select lchet from sgb where sgb.M=" +IntToStr(mvp) + " and sgb.Y=" +IntToStr(yvp); else sql+=" and g.lchet not in(select lchet from sgb_a where sgb_a.M=" +IntToStr(mvp) + " and sgb_a.Y=" +IntToStr(yvp);
      sql+=" ) and g.D_VIPL>="+IntToStr(date1);
      sql+=" and g.D_VIPL<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("CR")->AsInteger > 0)  r3=r3+TempQ->FieldByName("CR")->AsInteger;
      if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) d3=d3+TempQ->FieldByName("SUMMAV")->AsFloat;


      ir3+=r3;
      dr3+=d3;

      // неоплата из заданий

      TempQ->Close();
      TempQ->SQL->Clear();
      sql="";
      if (mvp==ml) sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from SGB g where LCHET1 IN ('Прошврем','раздел 1') "; else sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from SGB_A g where LCHET1 IN ('Прошврем','раздел 1') ";
      sql+=" and g.FAKT_DAT>="+IntToStr(date1);
      sql+=" and g.FAKT_DAT<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      sql+= "and ((UPPER(PRICH) <> UPPER('н/д')) AND (UPPER(PRICH) <> UPPER('')))";
      sql+=" and g.KASSA=0";
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("CR")->AsInteger > 0)  r4=TempQ->FieldByName("CR")->AsInteger;
      if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) d4=TempQ->FieldByName("SUMMAV")->AsFloat;

      d4=d4+sumoplpro;
      r4=r4+koloplpro;


// неоплата из базы

      TempQ->Close();
      TempQ->SQL->Clear();
      sql="";
      if (mvp==ml) sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from NDOST g where LCHET1 IN ('Прошврем','раздел 1') "; else sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from NDOST_A g where LCHET1 IN ('Прошврем','раздел 1') ";
      if (mvp==ml) sql+=" and g.lchet not in(select lchet from sgb where sgb.M=" +IntToStr(mvp) + " and sgb.Y=" +IntToStr(yvp); else sql+=" and g.lchet not in(select lchet from sgb_a where sgb_a.M=" +IntToStr(mvp) + " and sgb_a.Y=" +IntToStr(yvp);
      sql+=" ) and g.D_VIPL>="+IntToStr(date1);
      sql+=" and g.D_VIPL<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("CR")->AsInteger > 0)  r4=r4+TempQ->FieldByName("CR")->AsInteger;
      if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) d4=d4+TempQ->FieldByName("SUMMAV")->AsFloat;

      ir4+=r4;
      dr4+=d4;

      TempQ->Close();
      TempQ->SQL->Clear();
      if (mvp==ml) sql="select count (distinct g.lchet) as CR from SGB g where g.PRICH = ''"; else sql="select count (distinct g.lchet) as CR from SGB_A g where g.PRICH = ''";
      sql+=" and g.FAKT_DAT>="+IntToStr(date1);
      sql+=" and g.FAKT_DAT<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("CR")->AsInteger > 0)  r5=TempQ->FieldByName("CR")->AsInteger;

      TempQ->Close();
      TempQ->SQL->Clear();
      if (mvp==ml) sql="select distinct sum (g.summa) as summav from SGB g where g.PRICH = ''"; else sql="select distinct sum (g.summa) as summav from SGB_A g where g.PRICH = ''";
      sql+=" and g.FAKT_DAT>="+IntToStr(date1);
      sql+=" and g.FAKT_DAT<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) d5=TempQ->FieldByName("SUMMAV")->AsFloat;

      ir5+=r5;
      dr5+=d5;

      TempQ->Close();
      TempQ->SQL->Clear();
      sql="";
      if (mvp==ml) sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from SGB g where LCHET1 NOT IN ('Прошврем','раздел 1') AND g.PRICH = ''"; else sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from SGB_A g where LCHET1 NOT IN ('Прошврем','раздел 1') AND g.PRICH = ''";
      sql+=" and g.FAKT_DAT>="+IntToStr(date1);
      sql+=" and g.FAKT_DAT<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("CR")->AsInteger > 0)  r6=TempQ->FieldByName("CR")->AsInteger;
      if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) d6=TempQ->FieldByName("SUMMAV")->AsFloat;

      ir6+=r6;
      dr6+=d6;

      TempQ->Close();
      TempQ->SQL->Clear();
      sql="";
      if (mvp==ml) sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from SGB g where LCHET1 IN ('Прошврем','раздел 1') AND g.PRICH = ''"; else sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from SGB_A g where LCHET1 IN ('Прошврем','раздел 1') AND g.PRICH = ''";
      sql+=" and g.FAKT_DAT>="+IntToStr(date1);
      sql+=" and g.FAKT_DAT<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("CR")->AsInteger > 0)  r7=TempQ->FieldByName("CR")->AsInteger;
      if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) d7=TempQ->FieldByName("SUMMAV")->AsFloat;

      ir7+=r7;
      dr7+=d7;

      TempQ->Close();
      TempQ->SQL->Clear();
      sql="";
      if (mvp==ml) sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from SGB g where LCHET1 IN ('раздел 1')"; else sql="select count (distinct g.lchet) as CR , sum (g.summa) as summav from SGB_A g where LCHET1 IN ('раздел 1')";
      sql+=" and g.FAKT_DAT>="+IntToStr(date1);
      sql+=" and g.FAKT_DAT<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1="+IntToStr(Massiv[r]);
      sql+=" and g.PRICH<>'н/д'";
      sql+=" and g.KASSA=0";
      TempQ->SQL->Add(sql);
      try
      {
      TempQ->ExecQuery();
      }
      catch(const Exception &exc)
      {
      MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
      }

      if (TempQ->FieldByName("CR")->AsInteger > 0)  r8=TempQ->FieldByName("CR")->AsInteger;
      if (TempQ->FieldByName("SUMMAV")->AsFloat > 0) d8=TempQ->FieldByName("SUMMAV")->AsFloat;
      ir8=ir8+r8;
      dr8=dr8+d8;

      TempQ->Close();
      TempQ->SQL->Clear();
      sql="insert into REPRES(OPS,COUNT_TOTAL,COUNT_OPL,COUNT_NEOPL,COUNT_TOTALI,COUNT_OPLI,COUNT_NEOPLI,COUNT_TEK,COUNT_PR,COUNT_RAZ,COUNT_NEOPLP,\
      COUNT_FI,COUNT_FD,COUNT_NEOPLG,COUNT_OPLM,COUNT_OPLT,COUNT_OPLR) values(";
      sql+=IntToStr(Massiv[r])+",";
      sql+=AnsiString().sprintf("%.02lf",d1)+",";
      sql+=AnsiString().sprintf("%.02lf",d2)+",";
      sql+=AnsiString().sprintf("%.02lf",d3)+",";
      sql+=IntToStr(r1)+",";
      sql+=IntToStr(r2)+",";
      sql+=IntToStr(r3)+",";
      sql+=AnsiString().sprintf("%.02lf",d5)+",";
      sql+=AnsiString().sprintf("%.02lf",d6)+",";
      sql+=AnsiString().sprintf("%.02lf",d7)+",";
      sql+=AnsiString().sprintf("%.02lf",d4)+",";
      sql+=IntToStr(r8)+",";
      sql+=AnsiString().sprintf("%.02lf",d8)+",";
      sql+=IntToStr(r4)+",";
      sql+=IntToStr(r5)+",";
      sql+=IntToStr(r6)+",";
      sql+=IntToStr(r7)+")";
      TempQ->SQL->Add(sql);
      TempQ->ExecQuery();
      }
    if (mvp==ml){
    if (date1==1 && date2>=22)
    {
// здесь необходима ПОЛНАЯ проверка БД!!!

    if ( CheckDB() == 0 ){
    MessageDlg("Сбой в компоненте TempQuery!!!",mtInformation,TMsgDlgButtons() << mbOK,0);
    return;
    }

    if ( CheckDB() == 1 ){
     if(SaleBookDM->UserRole!="Администратор" && SaleBookDM->UserRole!="Руководитель")
      {
       MessageDlg("Обнаружена ошибка в БД!!! Необходимо сделать проверку БД пользователем с ролью Администратора или Руководителя через меню Администрирование->Проверить БД !!! Обратитесь пожалуйста к Вашему руководителю имеющую права Администратора или Руководителя в ИС Инспектор",mtInformation,TMsgDlgButtons() << mbOK,0);
      }else
      {
       MessageDlg("Обнаружена ошибка в БД!!! Необходимо сделать проверку БД через меню Администрирование->Проверить БД !!!",mtInformation,TMsgDlgButtons() << mbOK,0);
      }
      return;
    }
    }
    }
      TempQ->Close();
      TempQ->SQL->Clear();
      sql="insert into REPRES(OPS,COUNT_TOTAL,COUNT_OPL,COUNT_NEOPL,COUNT_TOTALI,COUNT_OPLI,COUNT_NEOPLI,COUNT_TEK,COUNT_PR,COUNT_RAZ,COUNT_NEOPLP,\
      COUNT_FI,COUNT_FD,COUNT_NEOPLG,COUNT_OPLM,COUNT_OPLT,COUNT_OPLR) values(0,";
      sql+=AnsiString().sprintf("%.02lf",dr1)+",";
      sql+=AnsiString().sprintf("%.02lf",dr2)+",";
      sql+=AnsiString().sprintf("%.02lf",dr3)+",";
      sql+=IntToStr(ir1)+",";
      sql+=IntToStr(ir2)+",";
      sql+=IntToStr(ir3)+",";
      sql+=AnsiString().sprintf("%.02lf",dr5)+",";
      sql+=AnsiString().sprintf("%.02lf",dr6)+",";
      sql+=AnsiString().sprintf("%.02lf",dr7)+",";
      sql+=AnsiString().sprintf("%.02lf",dr4)+",";
      sql+=IntToStr(ir8)+",";
      sql+=AnsiString().sprintf("%.02lf",dr8)+",";
      sql+=IntToStr(ir4)+",";
      sql+=IntToStr(ir5)+",";
      sql+=IntToStr(ir6)+",";
      sql+=IntToStr(ir7)+")";
      TempQ->SQL->Add(sql);
      TempQ->ExecQuery();


      DSSved->Close();
      DSSved->SQLs->SelectSQL->Clear();
      sql="";
      if (mvp==ml) sql="select distinct PRICH as pr , LCHET1 as lch1 , LCHET as lch, SUMMA as summad , WORD as w , METKA1 as ops from SGB g where "; else sql="select PRICH as pr , LCHET1 as lch1 , LCHET as lch, SUMMA as summad , WORD as w , METKA1 as ops from SGB_A g where ";
      sql+=" g.FAKT_DAT>="+IntToStr(date1);
      sql+=" and g.FAKT_DAT<="+IntToStr(date2);
      sql+=" and g.M="+IntToStr(mvp);
      sql+=" and g.Y="+IntToStr(yvp);
      sql+=" and g.METKA1 IN ("+ IndexOps +")";
      sql+=" and g.KASSA=0";
      sql+=" union select distinct";
      if (date1== 1 && date2 >= 22){
      sql+="  cast ('прочее' as varchar(6)) as pr, ";
      }else
      {
      sql+="  cast ('н/зад' as varchar(6)) as pr, ";
      }

      if (mvp==ml) sql+=" LCHET1 as lch1 , LCHET as lch, SUMMA as summad , WORD as w , METKA1 as ops from NDOST d where "; else sql+=" LCHET1 as lch1 , LCHET as lch, SUMMA as summad , WORD as w , METKA1 as ops from NDOST_A d where ";
      if (mvp==ml) sql+=" d.lchet not in(select lchet from sgb where sgb.M=" +IntToStr(mvp) + " and sgb.Y=" +IntToStr(yvp); else sql+=" d.lchet not in(select lchet from sgb_a where sgb_a.M=" +IntToStr(mvp) + " and sgb_a.Y=" +IntToStr(yvp);
      if (mvp==ml) sql+=" and sgb.FAKT_DAT>="+IntToStr(date1); else sql+=" and sgb_a.FAKT_DAT>="+IntToStr(date1);
      if (mvp==ml) sql+=" and sgb.FAKT_DAT<="+IntToStr(date2); else sql+=" and sgb_a.FAKT_DAT<="+IntToStr(date2);
      sql+=")";
      sql+=" and d.M="+IntToStr(mvp);
      sql+=" and d.Y="+IntToStr(yvp);
      sql+=" and d.D_VIPL>="+IntToStr(date1);
      sql+=" and d.D_VIPL<="+IntToStr(date2);
      sql+=" and d.METKA1 IN ("+ IndexOps +")";
      sql+=" order by 6,3,2";
      DSSved->SQLs->SelectSQL->Add(sql);
      try
      {
        DSSved->Open();
      }
      catch(const Exception &exc)
      {
        MessageDlg("Ошибка DSSved->Open()\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
        return;
      }

          frxReport2->LoadFromFile(MainForm->WorkDir+"Reports\\GoodsReport.fr3");
          frxReport2->PrepareReport(false);
          frxReport2->ShowPreparedReport();
          if (mvp==ml){
          if (date1==1 && date2>=22)
          {
          frxReport2->Export(RTFExport);
          MessageDlg("Данный отчет автоматически экспортирован в файл " + fileOut + " из папки " + Folder ,mtWarning,TMsgDlgButtons() << mbOK,0);
          }
          }
  }

  //Печать потребности ДС

  if(PotrButton->Checked)
  {
  Folder=MainForm->WorkDir+"Out\\";
  fileOut="potr.rtf";
  SetCurrentDir(Folder);
  if (FileExists(fileOut)) DeleteFile(fileOut);

  RTFExport->ShowDialog = true;
  RTFExport->OpenAfterExport = true;

  RTFExport->DefaultPath=Folder;
  RTFExport->FileName=fileOut;


    frxReport3->DataSet=frxPotrDS;
    PotrDS->Close();
    PotrDS->SQLs->SelectSQL->Clear();

      if (mvp==ml) sql="select kolvyp.datekol,kolvyp.kolv,sumvyp.sumv"; else sql="select kolvyp_a.datekol,kolvyp_a.kolv,sumvyp_a.sumv";
      if (mvp==ml) sql+=" from sumvyp "; else sql+=" from sumvyp_a ";
      if (mvp==ml) sql+=" inner join kolvyp on (sumvyp.mv = kolvyp.mv) and (sumvyp.yv = kolvyp.yv) and (sumvyp.datesum = kolvyp.datekol)"; else sql+=" inner join kolvyp_a on (sumvyp_a.mv = kolvyp_a.mv) and (sumvyp_a.yv = kolvyp_a.yv) and (sumvyp_a.datesum = kolvyp_a.datekol)";
      sql+=" where";
      if (mvp==ml) sql+="  kolvyp.mv="+IntToStr(mvp); else sql+="  kolvyp_a.mv="+IntToStr(mvp);
      if (mvp==ml) sql+=" and kolvyp.yv="+IntToStr(yvp); else sql+=" and kolvyp_a.yv="+IntToStr(yvp);
      PotrDS->SQLs->SelectSQL->Add(sql);
      try
      {
        PotrDS->Open();
      }
      catch(const Exception &exc)
      {
        MessageDlg("Ошибка PotrDS->Open()\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
        return;
      }

          frxReport3->LoadFromFile(MainForm->WorkDir+"Reports\\Potr.fr3");
          frxReport3->PrepareReport(false);
          frxReport3->ShowPreparedReport();
  }



}
//---------------------------------------------------------------------------

void __fastcall TPrntDataForm::PotrButtonClick(TObject *Sender)
{
  Label1->Visible = false;
  Label3->Visible = false;
  CNEdit->Visible = false;
  CNEdit1->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TPrntDataForm::frxReport3GetValue(const AnsiString VarName,
      Variant &Value)
{
AnsiString s;

    if(VarName=="M"){
    s=" Заявка на денежные средства на  " + AccountsJournalForm->Month->Text + " " +IntToStr(int(AccountsJournalForm->Year->Value))+" г. ";;
    Value=s;
  }

}
//---------------------------------------------------------------------------

void __fastcall TPrntDataForm::SendButtonClick(TObject *Sender)
{
AnsiString sql,namefr,namefz;
AnsiString str;
TpFIBQuery * TQJ=SaleBookDM->TempQuery;
AnsiString DirExport;
AnsiString s;
int cr=0;
int cz=0;
TSearchRec sr;
const int olMailItem = 0;
Variant MSOApp;
Variant myItem;
Variant myAttachments;
Variant myAttachments1;
int id;

DirExport=MainForm->WorkDir+"Send\\";
SetCurrentDir(DirExport);

if (FindFirst("*.rtf",faAnyFile , sr) == 0)
{
if (sr.Name.Pos("reportof") && Filedate(sr.Name.Trim())) cr++; namefr=sr.Name.Trim();
  while (FindNext(sr)==0)
  {
  if (sr.Name.Pos("reportof") && Filedate(sr.Name.Trim())) cr++; namefr=sr.Name.Trim();
  }
}

if (FindFirst("*.zip",faAnyFile , sr) == 0)
{
if (Filedate(sr.Name.Trim())) cz++; namefz=sr.Name.Trim();
  while (FindNext(sr)==0)
  {
  if (Filedate(sr.Name.Trim())) cz++; namefz=sr.Name.Trim();
  }
}
namefr=DirExport+namefr;
namefz=DirExport+namefz;

if (cr==0)
{
s="В папке для отправки " + DirExport + " НЕ обнаружены актуальные по дате файл со сводным отчетом в формате rtf для отправки!!! \n Сделайте экспорт сводного отчета в формат rtf для отправки!!! ";
MessageDlg(s,mtError,TMsgDlgButtons() << mbOK,0);
return;
}

if (cz==0)
{
s="В папке для отправки " + DirExport + " НЕ обнаружены актуальные по дате архивный файл с данными для отправки!!! \n Сделайте выгрузку данных в архив zip для отправки!!! ";
MessageDlg(s,mtError,TMsgDlgButtons() << mbOK,0);
return;
}

  if(SaleBookDM->MF==NULL)
  {
    try
    {
      SaleBookDM->MF=new TSMTPMessageForm(this);
    }
    catch(const Exception &exc)
    {
      MessageDlg("Ошибка создания формы TSMTPMessageForm"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
    if(SaleBookDM->MF!=NULL)
    {
    SaleBookDM->MF->Show();
    SaleBookDM->MF->StatusBar->SimpleText="Соединение с сервером";
    try {
        MSOApp = CreateOleObject("Outlook.Application");
        SaleBookDM->MF->StatusBar->SimpleText="Создание первого сообщения в администрацию соцзащиты !!!";
        myItem = MSOApp.OleFunction("CreateItem", (Variant)olMailItem);
        myItem.OlePropertySet("Subject", "Отчет и данные за текущий месяц ");
        myItem.OlePropertyGet("Recipients").OleFunction("Add",
            WideString(SaleBookDM->GetConstValue(SaleBookDM->OrganizationID,"ADRESS_ADMIN",Date())));
        myItem.OlePropertySet("Body", WideString( " Здравствуйте!!! Примите пожалуйста в дело отчет по муниципальным ЕДВ за отчетный месяц текущего года.\
Пожалуйста просим, как можно скорее по возможности обработать эти данные за отчетный месяц и новую выплатную базу  выслать по электронной почте на адрес Igor.Lepeshkin@russianpost.ru.\
 После обработки, полученной от Вас новой выплатной базы Вы получите от нас АВТОМАТИЧЕСКОЕ уведомление о ходе и результате нашей обработки Ваших данных.\
 Данное уведомление сформировано автоматически и не требует ответа.\
 Спасибо за внимание и понимание.\
 Берегите себя и близких.\
Удачи!!!"));
        myAttachments = myItem.OlePropertyGet("Attachments");
        myAttachments.OleFunction("Add", WideString(namefr));
        myAttachments1 = myItem.OlePropertyGet("Attachments");
        myAttachments1.OleFunction("Add", WideString(namefz));
        myItem.OleProcedure("Send");
        SaleBookDM->MF->StatusBar->SimpleText="Первое сообщения в администрацию соцзащиты ОТПРАВЛЕНО !!!";
//        MSOApp = CreateOleObject("Outlook.Application");
        SaleBookDM->MF->StatusBar->SimpleText="Создание второго сообщения в администрацию Почты России !!!";
        myItem = MSOApp.OleFunction("CreateItem", (Variant)olMailItem);
        myItem.OlePropertySet("Subject", "Отчет за текущий месяц ");
        myItem.OlePropertyGet("Recipients").OleFunction("Add",
            WideString(SaleBookDM->GetConstValue(SaleBookDM->OrganizationID,"ADRESS_UFPS1",Date())));
        myItem.OlePropertySet("Body", WideString( " Добрый день!!! Примите пожалуйста в дело отчет по муниципальным ЕДВ за отчетный месяц текущего года. Берегите себя и близких. Удачи!!! "));
        myAttachments = myItem.OlePropertyGet("Attachments");
        myAttachments.OleFunction("Add", WideString(namefr));
        myItem.OleProcedure("Send");
        SaleBookDM->MF->StatusBar->SimpleText="Создание УВЕДОМЛЕНИЯ руководителю ОДПП !!!";
        myItem = MSOApp.OleFunction("CreateItem", (Variant)olMailItem);
        myItem.OlePropertySet("Subject", "АВТОМАТИЧЕСКОЕ УВЕДОМЛЕНИЕ!!! ");
        myItem.OlePropertyGet("Recipients").OleFunction("Add",
            WideString(SaleBookDM->GetConstValue(SaleBookDM->OrganizationID,"ADRESS_UFPS3",Date())));
        myItem.OlePropertySet("Body", WideString( " Здравствуйте!!! \
Сводный отчет за текущий месяц получен от Вас и успешно обработан в НОВЕЙШЕЙ АИС Инспектор и отправлен всем по назначению. Ошибок и замечаний нет.\
Данное уведомление сформировано АВТОМАТИЧЕСКИ и не требует ответа.\
Спасибо!!!\
Берегите себя и близких!!!\
Удачи!!!"));
        myItem.OleProcedure("Send");
        SaleBookDM->MF->StatusBar->SimpleText="Уведомление руководителю ОДПП ОТПРАВЛЕНО успешно!!!";
        SaleBookDM->MF->StatusBar->SimpleText="Второе сообщения в администрацию Почты России ОТПРАВЛЕНО !!!";
//        MSOApp = CreateOleObject("Outlook.Application");
        SaleBookDM->MF->StatusBar->SimpleText="Создание третьего сообщения в администрацию Почты России !!!";
        myItem = MSOApp.OleFunction("CreateItem", (Variant)olMailItem);
        myItem.OlePropertySet("Subject", "Отчет за текущий месяц ");
        myItem.OlePropertyGet("Recipients").OleFunction("Add",
            WideString(SaleBookDM->GetConstValue(SaleBookDM->OrganizationID,"ADRESS_UFPS2",Date())));
        myItem.OlePropertySet("Body", WideString( " Добрый день!!! Примите пожалуйста в дело отчет по муниципальным ЕДВ за отчетный месяц текущего года. Берегите себя и близких. Удачи!!! "));
        myAttachments = myItem.OlePropertyGet("Attachments");
        myAttachments.OleFunction("Add", WideString(namefr));
        myItem.OleProcedure("Send");
        SaleBookDM->MF->StatusBar->SimpleText="Третье сообщения в администрацию Почты России ОТПРАВЛЕНО !!!";
        MSOApp.OleFunction("Quit");
        SaleBookDM->MF->Close();
    }
    catch (EOleSysError& E) {
        ShowMessage(E.Message + " Ошибка отправки!!!");
        SaleBookDM->MF->Close();
    }
    }
  }

  if(SaleBookDM->MF!=NULL) SaleBookDM->MF->Close();

  TQJ->Close();
  TQJ->SQL->Clear();
  str="select GEN_ID(GEN_ACTIONS_JOURNAL_ID,1) as ID from RDB$DATABASE";
  TQJ->SQL->Add(str);
  try
  {
    TQJ->ExecQuery();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка select GEN_ID(GEN_ACTIONS_JOURNAL_ID,1) as ID from RDB$DATABASE\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }

  id=TQJ->FieldByName("ID")->AsInteger;
  TQJ->Close();
  str="Отправлено письма в УФПС и администрацию соцзащиты ";
  SaleBookDM->TT->StartTransaction();
  if(SaleBookDM->AddRecordToActionsJournal(SendLetter,str,SaleBookDM->TT)==true) SaleBookDM->TT->Commit(); else SaleBookDM->TT->Rollback();
  DeleteFile(namefr);
  DeleteFile(namefz);

  TQJ->Close();
  TQJ->SQL->Clear();
  str="select GEN_ID(GEN_ACTIONS_JOURNAL_ID,1) as ID from RDB$DATABASE";
  TQJ->SQL->Add(str);
  try
  {
    TQJ->ExecQuery();
  }
  catch(const Exception &exc)
  {
    MessageDlg("Ошибка select GEN_ID(GEN_ACTIONS_JOURNAL_ID,1) as ID from RDB$DATABASE\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }

  id=TQJ->FieldByName("ID")->AsInteger;
  TQJ->Close();
  str="Отправлено уведомление руководителю ОДПП ";
  SaleBookDM->TT->StartTransaction();
  if(SaleBookDM->AddRecordToActionsJournal(SendNotice,str,SaleBookDM->TT)==true) SaleBookDM->TT->Commit(); else SaleBookDM->TT->Rollback();

  MessageDlg("Сообщении успешно отправлены !!! ",mtWarning,TMsgDlgButtons() << mbOK,0);
}
//---------------------------------------------------------------------------

