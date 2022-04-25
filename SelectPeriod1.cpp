//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "DataModule.h"
#include "SelectPeriod.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Placemnt"
#pragma link "SmrtPanel"
#pragma link "ToolEdit"
#pragma link "CSPIN"
#pragma link "JvComponent"
#pragma link "JvExControls"
#pragma link "JvXPButtons"
#pragma link "JvXPCore"
#pragma link "JvComponent"
#pragma link "JvExControls"
#pragma link "JvXPButtons"
#pragma link "JvXPCore"
#pragma resource "*.dfm"
//TSelectPeriodForm *SelectPeriodForm;
//---------------------------------------------------------------------------
__fastcall TSelectPeriodForm::TSelectPeriodForm(TComponent* Owner, TDateTime &dt1, TDateTime &dt2)
        : TForm(Owner), date1(dt1), date2(dt2)
{
  FormStorage->IniFileName=MainForm->getWorkDir()+"AccountGSM.ini";
  FormStorage->IniSection="SelectPeriodForm";
  PeriodText->Caption="¬ыбран период с "+date1.DateString()+" по "+date2.DateString();
  setPeriodText();
  Month->Text="";
  if(date1==date2)
  { DayButton->Checked=true;
    Day->Date=date1;
    MonthCheckBox->Checked=false;
  }
  else
  { unsigned short y1,m1,d1, y2,m2,d2;
    char *mn[12]={"€нварь","февраль","март","апрель","май","июнь","июль","август","сент€брь","окт€брь","но€брь","декабрь"};
    date1.DecodeDate(&y1,&m1,&d1);
    date2.DecodeDate(&y2,&m2,&d2);
    if(y1==y2)
    { if(m1==m2)
      { if(d1==d2)
        { DayButton->Checked=true;
          Day->Date=date2;
          MonthCheckBox->Checked=false;
        }
        else if(d1==1 && d2==GSM_DM->GetLastDay(y2,m2))
        { MonthButton->Checked=true;
          Month->Text=AnsiString(mn[m1-1])+" "+IntToStr(y1);
          MonthPosition=m1;
          YearCheckBox->Checked=false;
        }
        else
        { DayButton->Checked=true;
          Day->Date=date2;
          MonthCheckBox->Checked=true;
        }
      }
      else
      { if(date1==TDateTime(y1,1,1) && date2==TDateTime(y2,m2,GSM_DM->GetLastDay(y2,m2)))
        { MonthButton->Checked=true;
          YearCheckBox->Checked=true;
          Month->Text=AnsiString(mn[m2-1])+" "+IntToStr(y2);
          MonthPosition=m2;
        }
        else
        { IntButton->Checked=true;
          IntDate1->Date=date1;
          IntDate2->Date=date2;
        }
      }
    }
    else
    { IntButton->Checked=true;
      IntDate1->Date=date1;
      IntDate2->Date=date2;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSelectPeriodForm::setPeriodText(void)
{
  PeriodText->Caption="¬ыбран период с "+date1.DateString()+" по "+date2.DateString();
}
//---------------------------------------------------------------------------
void __fastcall TSelectPeriodForm::MonthButtonClick(TObject *Sender)
{
  if(MonthButton->Checked==true && Month->Text.IsEmpty())
  { unsigned short y,m,d;
    char *mn[12]={"€нварь","февраль","март","апрель","май","июнь","июль","август","сент€брь","окт€брь","но€брь","декабрь"};
    date2.DecodeDate(&y,&m,&d);
    Month->Text=AnsiString(mn[m-1])+" "+IntToStr(y);
    MonthPosition=m;
  }
}
//---------------------------------------------------------------------------
void __fastcall TSelectPeriodForm::DayButtonClick(TObject *Sender)
{
  if(DayButton->Checked==true && int(Day->Date)==0)
  {
    Day->Date=date2;
  }
}
//---------------------------------------------------------------------------
void __fastcall TSelectPeriodForm::IntButtonClick(TObject *Sender)
{
  if(IntButton->Checked==true && (int(IntDate1->Date)==0 || int(IntDate1->Date)==0))
  { IntDate1->Date=date1;
    IntDate2->Date=date2;
  }
}
//---------------------------------------------------------------------------
void __fastcall TSelectPeriodForm::MonthUpDownDownClick(TObject *Sender)
{
unsigned short y,m,d;
char *mn[12]={"€нварь","февраль","март","апрель","май","июнь","июль","август","сент€брь","окт€брь","но€брь","декабрь"};
date2.DecodeDate(&y,&m,&d);

  m--;
  if(m==0){ m=12; y--;}
  Month->Text=AnsiString(mn[m-1])+" "+IntToStr(y);
  MonthPosition=m;
  date1=TDateTime(y,m,1);
  date2=TDateTime(y,m,GSM_DM->GetLastDay(y,m));
}
//---------------------------------------------------------------------------
void __fastcall TSelectPeriodForm::MonthUpDownUpClick(TObject *Sender)
{
unsigned short y,m,d;
char *mn[12]={"€нварь","февраль","март","апрель","май","июнь","июль","август","сент€брь","окт€брь","но€брь","декабрь"};
date2.DecodeDate(&y,&m,&d);

  m++;
  if(m > 12){ m=1; y++;}
  Month->Text=AnsiString(mn[m-1])+" "+IntToStr(y);
  MonthPosition=m;
  date1=TDateTime(y,m,1);
  date2=TDateTime(y,m,GSM_DM->GetLastDay(y,m));
}
//---------------------------------------------------------------------------
void __fastcall TSelectPeriodForm::JXPBOKClick(TObject *Sender)
{
  if(MonthButton->Checked==true)
  { unsigned short y1,m1,d1=1, y2,m2,d2;
    m2=MonthPosition;
    AnsiString year=Month->Text.SubString(Month->Text.Pos(" ")+1,4);
    y1=y2=StrToInt(year);
    if(YearCheckBox->Checked==true) m1=1;
    else m1=m2;
    d2=GSM_DM->GetLastDay(y2,m2);
    date1=TDateTime(y1,m1,d1);
    date2=TDateTime(y2,m2,d2);
  }
  else if(DayButton->Checked==true)
  { date2=Day->Date;
    if(MonthCheckBox->Checked==true)
    { unsigned short y,m,d;
      date2.DecodeDate(&y,&m,&d);
      date1=TDateTime(y,m,1);
    }
    else date1=date2;
  }
  else
  { date1=IntDate1->Date;
    date2=IntDate2->Date;
  }
  Close();
  ModalResult=mrOk;
}
//---------------------------------------------------------------------------
TDateTime __fastcall TSelectPeriodForm::getDate1(void)
{
  return date1;
}
//---------------------------------------------------------------------------
TDateTime __fastcall TSelectPeriodForm::getDate2(void)
{
  return date2;
}
//---------------------------------------------------------------------------

void __fastcall TSelectPeriodForm::JvXPButton1Click(TObject *Sender)
{
Close();
ModalResult=mrCancel;
}
//---------------------------------------------------------------------------

