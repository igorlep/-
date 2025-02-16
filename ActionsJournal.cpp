//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "DataModule.h"
#include "SelectRecords.h"
#include "ActionsJournal.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Placemnt"
#pragma link "DBGridEh"
#pragma link "FIBDataSet"
#pragma link "pFIBDataSet"
#pragma link "FIBDatabase"
#pragma link "pFIBDatabase"
#pragma resource "*.dfm"
TActionsJournalForm *ActionsJournalForm;
//---------------------------------------------------------------------------
__fastcall TActionsJournalForm::TActionsJournalForm(TComponent* Owner)
        : TForm(Owner)
{
TIniFile *ini;

  FormStorage1->IniFileName=MainForm->WorkDir+"SB_2009.ini";
  FormStorage1->IniSection="ActionsJournalForm";

  ini=new TIniFile(MainForm->WorkDir+"SB_2009.ini");
  Grid->Columns->Items[0]->Width=ini->ReadInteger("ActionsJournalForm","w0",60);
  Grid->Columns->Items[1]->Width=ini->ReadInteger("ActionsJournalForm","w1",60);
  Grid->Columns->Items[2]->Width=ini->ReadInteger("ActionsJournalForm","w2",60);
  Grid->Columns->Items[3]->Width=ini->ReadInteger("ActionsJournalForm","w3",60);
  Grid->Columns->Items[4]->Width=ini->ReadInteger("ActionsJournalForm","w4",60);
  delete ini;

  Filter="";
  try
  {
    SRF=new TSelectRecordsForm(this);
  }
  catch(const Exception &exc)
  {
    MessageDlg("������ �������� ����� SRF\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    SelectButton->Enabled=false;
    SRF=NULL;
  }
  UnSelectButton->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TActionsJournalForm::FormShow(TObject *Sender)
{
  if(SelectButton->Enabled) SelectButton->Click();
  SetActionsDS();
}
//---------------------------------------------------------------------------
void __fastcall TActionsJournalForm::FormDestroy(TObject *Sender)
{
TIniFile *ini;

  if(SRF!=NULL) delete SRF;
  ini=new TIniFile(MainForm->WorkDir+"SB_2009.ini");
  ini->WriteInteger("ActionsJournalForm","w0",Grid->Columns->Items[0]->Width);
  ini->WriteInteger("ActionsJournalForm","w1",Grid->Columns->Items[1]->Width);
  ini->WriteInteger("ActionsJournalForm","w2",Grid->Columns->Items[2]->Width);
  ini->WriteInteger("ActionsJournalForm","w3",Grid->Columns->Items[3]->Width);
  ini->WriteInteger("ActionsJournalForm","w4",Grid->Columns->Items[4]->Width);
  delete ini;
}
//---------------------------------------------------------------------------
void __fastcall TActionsJournalForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Action=caFree;
}
//---------------------------------------------------------------------------
void __fastcall TActionsJournalForm::ExitButtonClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TActionsJournalForm::SetActionsDS(void)
{
AnsiString sql;

  sql="select a.*, u.LOGIN as UserName, u.USER_ROLE as UserRole";
  sql+=" from ACTIONS_JOURNAL a";
  sql+=" left outer join USERS u on u.ID=a.USER_ID";
  if(!Filter.IsEmpty())sql+=" where "+Filter;
  ActionsDS->Close();
  ActionsDS->SQLs->SelectSQL->Clear();
  ActionsDS->SQLs->SelectSQL->Add(sql);
  try
  {
    ActionsDS->Open();
  }
  catch(const Exception &exc)
  {
    MessageDlg("������ - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
  }
  ActionsDS->Last();
}
//---------------------------------------------------------------------------
void __fastcall TActionsJournalForm::SelectButtonClick(TObject *Sender)
{

  if(SRF->ShowModal()==mrOk)
  { Filter="";
    //��������
    TDateTime fd, ld=Date();
    bool FLG=false;
    if(SRF->LastDayRB->Checked){ fd=Date(); FLG=true;}
    else if(SRF->LastWeekRB->Checked)
    { int d=ld.DayOfWeek();
      fd=ld;
      if(d > 1)fd-=(d-2);
      FLG=true;
    }
    else if(SRF->LastMonthRB->Checked)
    { unsigned short y,m,d;
      ld.DecodeDate(&y,&m,&d);
      fd=TDateTime(y,m,1);
      FLG=true;
    }
    else if(SRF->IntervalRB->Checked)
    { fd=TDateTime(SRF->FromDateEdit->Text);
      ld=TDateTime(SRF->ToDateEdit->Text);
      FLG=true;
    }
    if(FLG)
    { if(!Filter.IsEmpty()) Filter+=" and";
      Filter+=" (a.ACTION_DATE >= '"+fd.DateString()+"'";
      Filter+=" and a.ACTION_DATE <= '"+ld.DateString()+"')";
    }
    //���� �������
    FLG=false;
    if(SRF->ActionsBox->Checked[0]) //���� / �����
    { if(!Filter.IsEmpty()) Filter+=" and (";
      else Filter+="(";
      Filter+=" a.ACTION_TYPE="+IntToStr(InputUserToApplication);
      Filter+=" or a.ACTION_TYPE="+IntToStr(OutputUserFromApplication);
      FLG=true;
    }
    if(SRF->ActionsBox->Checked[1]) //������ �������
    { if(!Filter.IsEmpty())
      { if(!FLG) Filter+=" and (";
        else Filter+=" or";
      }
      else Filter+="(";
      Filter+=" a.ACTION_TYPE="+IntToStr(AddRecordToAccountsTable);
      Filter+=" or a.ACTION_TYPE="+IntToStr(EditRecordFromAccountsTable);
      Filter+=" or a.ACTION_TYPE="+IntToStr(DelRecordFromAccountsTable);
      FLG=true;
    }
    if(SRF->ActionsBox->Checked[2]) //����������/�������������� ����
    { if(!Filter.IsEmpty())
      { if(!FLG) Filter+=" and (";
        else Filter+=" or";
      }
      else Filter+="(";
      Filter+=" a.ACTION_TYPE="+IntToStr(BackUpBase);
      Filter+=" or a.ACTION_TYPE="+IntToStr(RestoreBase);
      FLG=true;
    }
    if(SRF->ActionsBox->Checked[3]) //������/�������
    { if(!Filter.IsEmpty())
      { if(!FLG) Filter+=" and (";
        else Filter+=" or";
      }
      else Filter+="(";
      Filter+=" a.ACTION_TYPE="+IntToStr(AddImport);
      Filter+=" or a.ACTION_TYPE="+IntToStr(AddExport);
      FLG=true;
    }
    if(SRF->ActionsBox->Checked[4]) //��������
    { if(!Filter.IsEmpty())
      { if(!FLG) Filter+=" and (";
        else Filter+=" or";
      }
      else Filter+="(";
      Filter+=" a.ACTION_TYPE="+IntToStr(SendNotice);
      Filter+=" or a.ACTION_TYPE="+IntToStr(SendLetter);
      FLG=true;
    }
    if(FLG) Filter+=")";
    //����� �� ������������
    if(!SRF->UserBox->Text.IsEmpty())
    { if(!Filter.IsEmpty()) Filter+=" and";
      Filter+=" a.USER_ID="+SRF->UsersID->Strings[SRF->UserBox->ItemIndex];
    }
    //����� �� ������
    if(SRF->StrCheckBox->Checked && !SRF->StringEdit->Text.IsEmpty())
    { if(!Filter.IsEmpty()) Filter+=" and";
      Filter+=" a.ACTION_TEXT like '%"+SRF->StringEdit->Text+"%'";
    }
    UnSelectButton->Enabled=true;
    SetActionsDS();
  }
}
//---------------------------------------------------------------------------

void __fastcall TActionsJournalForm::UnSelectButtonClick(TObject *Sender)
{
  Filter="";
  UnSelectButton->Enabled=false;
  SetActionsDS();
}
//---------------------------------------------------------------------------

