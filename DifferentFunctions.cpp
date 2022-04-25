//Набор универсальных функций
//---------------------------------------------------------------------------
#include "DBClasses.h"
#include <math.h>
#pragma hdrstop
#include "GUID.h"
#include "Propis.h"
#include "ZipBuilder.h"
#include "DifferentFunctions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
//---------------------------------------------------------------------------
//Функция определения последнего дня месяца
unsigned short __fastcall lastDayOfMonth(unsigned short y, unsigned short m)
{
unsigned short ld=31;

  if(m==4 || m==6 || m==9 || m==11) ld=30;
  else if(m==2)
  { if(y%4) ld=28;
    else ld=29;
  }
  return ld;
}
//---------------------------------------------------------------------------
//Начало месяца
TDateTime __fastcall beginOfMonth(TDateTime date)
{
unsigned short y,m,d;

  date.DecodeDate(&y,&m,&d);
  return TDateTime(y,m,1);
}
//---------------------------------------------------------------------------

unsigned short __fastcall KolOfDaysinMonth(unsigned short y,unsigned short m)
{
unsigned short ld=31;

  if(m==4 || m==6 || m==9 || m==11) ld=30;
  else if(m==2)
  { if(y%4) ld=28;
    else ld=29;
  }
  return ld;
}

//разница между датами в днях!!!
int __fastcall diffOfDays(TDateTime date1,TDateTime date2)
{
int diff=0;
int m1,m2,d1,d2,y1,y2;
int koldn=0;

m1=nummonthOfDate(date1);
m2=nummonthOfDate(date2);
d1=dayOfDate(date1);
d2=dayOfDate(date2);
y1=yearOfDate(date1);
y2=yearOfDate(date2);

if (m1-m2 > 0 )
{
for (int i=m2;i<m1+1;i++)
{
if (i==m2) koldn=KolOfDaysinMonth(y1,i)-d2;
if (i>m2) koldn=KolOfDaysinMonth(y1,i);
if (i==m1) koldn=d1;
diff=diff+koldn;
}
return diff;
}else
{
diff=d1-d2;
}

return diff;
}
//---------------------------------------------------------------------------

//Конец месяца
TDateTime __fastcall endOfMonth(TDateTime date)
{
unsigned short y,m,d;

  date.DecodeDate(&y,&m,&d);
  return TDateTime(y,m,lastDayOfMonth(y,m));
}
//---------------------------------------------------------------------------
TDateTime __fastcall endOfMonth(unsigned short y, unsigned short m)
{
  return TDateTime(y,m,lastDayOfMonth(y,m));
}
//---------------------------------------------------------------------------
//День даты
unsigned short __fastcall dayOfDate(TDateTime date)
{
unsigned short y,m,d;

  date.DecodeDate(&y,&m,&d);
  return d;
}
//---------------------------------------------------------------------------
//Месяц
AnsiString __fastcall monthOfDate(TDateTime date)
{
unsigned short y,m,d;
char *mon[12]={"января","февраля","марта","апреля","мая","июня","июля","августа","сентября","октября","ноября","декабря"};

  date.DecodeDate(&y,&m,&d);
  return AnsiString(mon[m-1]);
}

AnsiString __fastcall namemonthOfDate(int m)
{
char *mon[12]={"Январь","Февраль","Март","Апрель","Май","Июнь","Июль","Август","Сентябрь","Октябрь","Ноябрь","Декабрь"};

  return AnsiString(mon[m-1]);
}


//---------------------------------------------------------------------------
//Номер месяца
unsigned short __fastcall nummonthOfDate(TDateTime date)
{
unsigned short y,m,d;

  date.DecodeDate(&y,&m,&d);
  return m;
}
//---------------------------------------------------------------------------

//Год
unsigned short __fastcall yearOfDate(TDateTime date)
{
unsigned short y,m,d;

  date.DecodeDate(&y,&m,&d);
  return y;
}
//---------------------------------------------------------------------------

//Различные функции для работы с датой
AnsiString __fastcall getMonthYearString(TDateTime date)
{
unsigned short y,m,d;
char *mes[12]={"январь","февраль","март","апрель","май","июнь","июль","август","сентябрь","октябрь","ноябрь","декабрь"};

  if(int(date)==0) return "";
  date.DecodeDate(&y,&m,&d);
  return AnsiString(mes[m-1])+" "+IntToStr(y)+" года";
}
//---------------------------------------------------------------------------
TDateTime __fastcall getDateFromMonthYearString(AnsiString month_yearStr)
{
unsigned short y,m,d;
char *mes[12]={"январь","февраль","март","апрель","май","июнь","июль","август","сентябрь","октябрь","ноябрь","декабрь"};
int p;

  if(month_yearStr==NULL || month_yearStr.IsEmpty()) return 0;
  for(p=0; p<12; ++p) if(month_yearStr.Pos(mes[p]) != 0) break;
  if(p < 12)
  { m=p+1;
    int poz=month_yearStr.Pos(" ")+1;
    AnsiString year=month_yearStr.SubString(poz,month_yearStr.Length()-poz);
    year=year.SubString(1,year.Pos(" ")-1);
    y=StrToInt(year);
    return TDateTime(y,m,1);
  }
  else return 0;
}
//---------------------------------------------------------------------------

//Функция извлечения подстроки из строки с разделителями
//AnsiString __fastcall getSubstring(AnsiString str, char r, int n)
//str - строка с разделителями
//r - символ-разделитель подстрок
//n - номер извлекаемой подстроки
//{
//int i=1, j=1;

//  if(str.IsEmpty()) return "";
//  while(j<=str.Length() && i<n)
//  { if(str[j]==r) i++;
//    j++;
//  }
//  AnsiString s=str.SubString(j,str.Length());
//  if(s.IsEmpty()) return NULL;
//  if(s.Pos(AnsiString(r))==0) return s;
//  return s.SubString(1,s.Pos(AnsiString(r))-1);
//}
//---------------------------------------------------------------------------

//********************************
//* Функции для работы с данными *
//********************************
// - Генерация нового значения ключевого поля для tableName
AnsiString __fastcall getNewKeyValue(FBDatabase * fb_db, AnsiString tableName)
{
AnsiString sql;
FBQuery * fbWQ=fb_db->getFBQ_T2();

  sql="select GEN_ID(GEN_"+tableName+"_ID,1) as ID from RDB$DATABASE";
  if(fbWQ->execQuery("getNewRB_KeyValue:",sql)==false) return "";
  return fbWQ->getQuery()->FieldByName("ID")->AsString;
}
//---------------------------------------------------------------------------
AnsiString __fastcall getNewKeyValue(FBQuery * fbWQ, AnsiString tableName)
{
AnsiString sql;

  sql="select GEN_ID(GEN_"+tableName+"_ID,1) as ID from RDB$DATABASE";
  if(fbWQ->execQuery("getNewRB_KeyValue:",sql)==false) return "";
  return fbWQ->getQuery()->FieldByName("ID")->AsString;
}
//---------------------------------------------------------------------------
void __fastcall setGenerator(FBQuery *fbWQ,AnsiString tableName,AnsiString genName,AnsiString keyName)
{
AnsiString sql;

  //Значение генератора
  sql="select max("+keyName+") MAX_ID from "+tableName;
  if(fbWQ->execQuery("DifferentFunctions::setGenerator",sql)==true)
  { int id=fbWQ->getQuery()->FieldByName("MAX_ID")->AsInteger;
    sql="set generator "+genName+" to "+IntToStr(id);
    fbWQ->execQuery("DifferentFunctions::setGenerator",sql);
  }
}
//---------------------------------------------------------------------------
//Функция проверяет наличие в таблице tableName записи с кодом id
bool __fastcall checkRecord(TComponent* owner,FBDatabase *fbDB,AnsiString table_name,AnsiString id_name,AnsiString id)
{
AnsiString sql;
FBQuery * fbRQ=new FBQuery(owner,fbDB->getDatabase(),true);
bool rez=false;

  if(fbRQ==NULL) return rez;
  sql="select count("+id_name+") as count_record from "+table_name+" where "+id_name+"="+id;
  if(fbRQ->execQuery("",sql)==false) goto end;
  if(fbRQ->getQuery()->FieldByName("count_record")->AsInteger>0) rez=true;
end:
  delete fbRQ;
  return rez;
}
//---------------------------------------------------------------------------

// - Получение значения поля fieldName таблицы tableName по значению keyData ключевого поля keyFieldName
/*AnsiString __fastcall getDataForFieldName(FBDatabase * fb_db,AnsiString tableName,AnsiString keyFieldName,AnsiString keiData, AnsiString fieldName)
{
AnsiString fieldData="";
FBQuery *fbRQ=fb_db->getFBQ_T1();
AnsiString sql;

  sql="select "+FieldName+" from "+tableName+" where "+keyFieldName+"='"+keyData+"'";
  if(fbRQ->execQuery("",sql)==false) return fieldData;
  fieldData=fbRQ->getQuery()->FieldByName(fieldName)->AsString;
  fbRQ->getQuery()->Close();
  return fieldData;
}
//---------------------------------------------------------------------------
*/

//*****************************************
//* Фукции для работы с таблицей констант *
//*****************************************
//Читает наименование константы
AnsiString __fastcall getConstName(TComponent* owner,FBDatabase * fb_db,AnsiString identifier)
{
AnsiString sql;
FBQuery * fbRQ=newFBQuery(owner,"getConstName",fb_db->getDatabase(),true);
AnsiString constName="";

  if(fbRQ!=NULL)
  { sql="select CONST_NAME from CONSTANTS_TABLE where IDENTIFIER='"+identifier+"'";
    if(fbRQ->execQuery("getConstTitle",sql)==true && fbRQ->getQuery()->RecordCount > 0)
      constName=fbRQ->getQuery()->FieldByName("CONST_NAME")->AsString;
    delete fbRQ;
  }
  return constName;
}
//---------------------------------------------------------------------------
//Читает заголовок константы
AnsiString __fastcall getConstTitle(TComponent* owner,FBDatabase * fb_db,AnsiString identifier)
{
AnsiString sql;
FBQuery * fbRQ=newFBQuery(owner,"getConstTitle",fb_db->getDatabase(),true);
AnsiString constTitle="";

  if(fbRQ!=NULL)
  { sql="select CONST_TITLE from CONSTANTS_TABLE where IDENTIFIER='"+identifier+"'";
    if(fbRQ->execQuery("getConstTitle",sql)==true && fbRQ->getQuery()->RecordCount > 0)
      constTitle=fbRQ->getQuery()->FieldByName("CONST_TITLE")->AsString;
    delete fbRQ;
  }
  return constTitle;
}
//---------------------------------------------------------------------------
//Читает значение константы
AnsiString __fastcall getConstValue(TComponent* owner,FBDatabase * fb_db,AnsiString identifier,TDateTime date,AnsiString sd_id)
{
AnsiString sql;
FBQuery * fbRQ=newFBQuery(owner,"getConstValue",fb_db->getDatabase(),true);
AnsiString constValue="";
TDateTime constDT=date;

  if(fbRQ!=NULL)
  { //выясняем тип константы
    sql="select * from CONSTANTS_TABLE where IDENTIFIER='"+identifier+"'";
    if(fbRQ->execQuery("getConstTitle",sql)==true && fbRQ->getQuery()->RecordCount > 0)
    { AnsiString id=fbRQ->getQuery()->FieldByName("ID")->AsString;
      int constType=fbRQ->getQuery()->FieldByName("CONST_TYPE")->AsInteger;
//      if(int(constDT)==0) constDT=DATE();
      sql="select CONST_VALUE from GET_SIMPLE_CONST_VALUE(";
      sql+="'"+identifier+"',";
      if(int(constDT)>0)
        sql+="'"+constDT.DateString()+"',";
      else sql+="NULL,";
      if(!sd_id.IsEmpty()) sql+=sd_id+")";
      else sql+="0)";
      if(fbRQ->execQuery("getConstValue",sql)==true &&  fbRQ->getQuery()->RecordCount > 0)
      { constValue=fbRQ->getQuery()->FieldByName("CONST_VALUE")->AsString;
        if(constType==1) //константа-ссылка
        { AnsiString refTableName=fbRQ->getQuery()->FieldByName("REF_TABLE_NAME")->AsString;
          AnsiString refKeyName=fbRQ->getQuery()->FieldByName("REF_KEY_FIELD_NAME")->AsString;
          AnsiString retFieldName=fbRQ->getQuery()->FieldByName("RET_FIELD_NAME")->AsString;
          //читаем значение константы
          sql="select "+retFieldName+" from "+refTableName+" where "+refKeyName+"='"+constValue+"'";
          if(fbRQ->execQuery("getConstValue",sql)==true &&  fbRQ->getQuery()->RecordCount > 0)
            constValue=fbRQ->getQuery()->FieldByName("CONST_VALUE")->AsString;
        }
      }
    }
    delete fbRQ;
  }
  return constValue;
}
//---------------------------------------------------------------------------
//Выдает тип константы
//0 - простая константа (CONST_VALUES - содержит значение этой константы),
//1 - константа-ссылка (CONST_VALUES - содержит значение константы и ссылку на запись из другой таблицы с этим значением),
//2 - CONST_VALUES - содержит значение константы и ссылку на запись из таблицы CONST_VALUES, к которой значение относится.
int __fastcall getConstType(TComponent* owner,FBDatabase * fb_db,AnsiString identifier)
{
AnsiString sql;
FBQuery * fbRQ=newFBQuery(owner,"getConstValue",fb_db->getDatabase(),true);
int const_type;

  if(fbRQ!=NULL)
  { sql="select CONST_TYPE from CONSTANTS_TABLE where IDENTIFIER='"+identifier+"'";
    if(fbRQ->execQuery("getConstType",sql)==true && fbRQ->getQuery()->RecordCount > 0)
      const_type=fbRQ->getQuery()->FieldByName("CONST_TYPE")->AsInteger;
    else const_type=-1;
  }
  delete fbRQ;
  return const_type;
}
//---------------------------------------------------------------------------
//Выдает вид константы
//0 - непереодическая, 1 - периодическая
int __fastcall getConstKind(TComponent* owner,FBDatabase * fb_db,AnsiString identifier)
{
AnsiString sql;
FBQuery * fbRQ=newFBQuery(owner,"getConstValue",fb_db->getDatabase(),true);
int const_kind;

  if(fbRQ!=NULL)
  { sql="select CONST_KIND from CONSTANTS_TABLE where IDENTIFIER='"+identifier+"'";
    if(fbRQ->execQuery("getConstType",sql)==true && fbRQ->getQuery()->RecordCount > 0)
      const_kind=fbRQ->getQuery()->FieldByName("CONST_KIND")->AsInteger;
    else const_kind=-1;
  }
  delete fbRQ;
  return const_kind;
}
//---------------------------------------------------------------------------

//Устанавливает значение простой константы
void  __fastcall setConstValue(FBDatabase * fb_db,AnsiString identifer, AnsiString constValue)
{
AnsiString sql;
FBQuery * fbWQ=fb_db->getFBQ_T2();

  sql="update CONST_VALUES set CONST_VALUE='"+constValue+"'";
  sql+=" where CONST_ID=(select ID from CONSTANTS_TABLE where IDENTIFIER='"+identifer+"')";
  fbWQ->execQuery("setConstValue",sql);
}
//---------------------------------------------------------------------------
//Устанавливает значение периодиского параметра
bool  __fastcall setPeriodicalConstValue(FBDatabase * fb_db,AnsiString const_id,int &value_id,AnsiString constValue,TDateTime constDate)
{
AnsiString sql;
FBQuery * fbWQ=fb_db->getFBQ_T2();
bool ret=false;

  if(constValue.Length()>240) constValue.SetLength(240);
  fbWQ->getTransaction()->StartTransaction();
  if(value_id==0)  //новое значение параметра
  { AnsiString id=getNewKeyValue(fbWQ,"PERIODICAL_CONST_VALUES");
    if(id.IsEmpty())
    { MessageDlg("Ошибка генерирования ключевого поля таблицы PERIODICAL_CONST_VALUES",mtError,TMsgDlgButtons() << mbOK,0);
      fbWQ->getTransaction()->Rollback();
      return ret;
    }
    sql="insert into PERIODICAL_CONST_VALUES(ID,CONST_ID,CONST_VALUE,CONST_DATE) values(";
    sql+=id+",";
    sql+=const_id+",";
    sql+="'"+constValue+"',";
    sql+="'"+constDate.DateString()+"')";
    if(fbWQ->execQuery("setPeriodicalConstValue",sql)==false)
    { fbWQ->getTransaction()->Rollback();
      return ret;
    }
    fbWQ->getTransaction()->Commit();
    value_id=StrToInt(id);
    ret=true;
  }
  else
  { sql="update PERIODICAL_CONST_VALUES set CONST_VALUE='"+constValue+"',";
    sql+="CONST_DATE='"+constDate.DateString()+"'";
    sql+=" where ID="+IntToStr(value_id);
    if(fbWQ->execQuery("TPeriodicalConstantEditForm::SaveButtonClick",sql)==false)
    { fbWQ->getTransaction()->Rollback();
      return ret;
    }
    fbWQ->getTransaction()->Commit();
    ret=true;
  }
  return ret;
}
//---------------------------------------------------------------------------
//Удаление значения периодического параметра
void  __fastcall delPeriodicalConstValue(FBDatabase * fb_db,AnsiString value_id)
{
AnsiString sql;
FBQuery * fbWQ=fb_db->getFBQ_T2();

  sql="delete from PERIODICAL_CONST_VALUES where ID="+value_id;
  fbWQ->execQuery("delPeriodicalConstValue(",sql);
}
//---------------------------------------------------------------------------
//Получить значение периодического параметра
AnsiString __fastcall getPeriodicalParamValue(FBDatabase * fb_db,AnsiString tableInfo,AnsiString keyID,TDateTime forDate)
{
AnsiString sql;
FBQuery * fbRQ=fb_db->getFBQ_T1();
//AnsiString tableName=getSubstring(tableInfo,',',1);
//AnsiString paramIDName=getSubstring(tableInfo,',',2);
//AnsiString keyName=getSubstring(tableInfo,',',3);
//AnsiString dateName=getSubstring(tableInfo,',',4);
//AnsiString paramValueName=getSubstring(tableInfo,',',5);

//  sql="select "+paramValueName+" from "+tableName+" where "+keyName+"='"+keyID+"'";
//  sql+=" and "+dateName+"<='"+forDate.DateString()+"'";
//  sql+=" order by "+dateName+" desc";
//  if(fbRQ->execQuery("getPeriodicalParamValue",sql)==false) return "";
//  return fbRQ->getQuery()->FieldByName(paramValueName)->AsString;
}
//---------------------------------------------------------------------------

//Функции преобразования чисел в строку прописью
// - функция преобразования вещественного числа в числительное прописью руб. и коп.
AnsiString f_to_str(double d)
{
  return Propis(d).DoublePropis();
}
//---------------------------------------------------------------------------
// - функция преобразования целого в числительное прописью
AnsiString i_to_str(int i)
{
  return Propis(double(i)).IntPropis();
}
//---------------------------------------------------------------------------

//Функция, генерирующая уникальный идентификатор - GUID длиной 32 байта
AnsiString __fastcall genGUID(void)
{
  return guid().genGUID();
}
//---------------------------------------------------------------------------

//Функция формирования строки заголовка
AnsiString __fastcall SetHeader(AnsiString str, TDateTime date1, TDateTime date2)
{
unsigned short y1,m1,d1,y2,m2,d2;

  str+=" за ";
  if(date1==date2) str+=date1.DateString();
  else
  { date1.DecodeDate(&y1,&m1,&d1);
    date2.DecodeDate(&y2,&m2,&d2);
    if(y1==y2)
    { if(m1==m2)
      { if(d1==1 && d2==lastDayOfMonth(y2,m2))
        { char *mn[12]={"январь","февраль","март","апрель","май","июнь","июль","август","сентябрь","октябрь","ноябрь","декабрь"};
          str+=AnsiString(mn[m1-1])+" "+IntToStr(y1)+" года";
        }
        else str+="период с "+date1.DateString()+" по "+date2.DateString();
      }
      else if(m1==1 && m2==3)
      { if(d1==1 && d2==lastDayOfMonth(y2,m2)) str+="первый квартал "+IntToStr(y1)+" года";
        else str+="период с "+date1.DateString()+" по "+date2.DateString();
      }
      else if(m1==1 && m2==6)
      { if(d1==1 && d2==lastDayOfMonth(y2,m2)) str+="первое полугодие "+IntToStr(y1)+" года";
        else str+="период с "+date1.DateString()+" по "+date2.DateString();
      }
      else if(m1==4 && m2==6)
      { if(d1==1 && d2==lastDayOfMonth(y2,m2)) str+="второй квартал "+IntToStr(y1)+" года";
        else str+="период с "+date1.DateString()+" по "+date2.DateString();
      }
      else if(m1==7 && m2==9)
      { if(d1==1 && d2==lastDayOfMonth(y2,m2)) str+="третий квартал "+IntToStr(y1)+" года";
        else str+="период с "+date1.DateString()+" по "+date2.DateString();
      }
      else if(m1==10 && m2==12)
      { if(d1==1 && d2==lastDayOfMonth(y2,m2)) str+="четвертый квартал "+IntToStr(y1)+" года";
        else str+="период с "+date1.DateString()+" по "+date2.DateString();
      }
      else if(m1==7 && m2==12)
      { if(d1==1 && d2==lastDayOfMonth(y2,m2)) str+="второе полугодие "+IntToStr(y1)+" года";
        else str+="период с "+date1.DateString()+" по "+date2.DateString();
      }
      else if(m1==1 && m2==12)
      { if(d1==1 && d2==lastDayOfMonth(y2,m2)) str+=IntToStr(y1)+" год";
        else str+="период с "+date1.DateString()+" по "+date2.DateString();
      }
      else str+="период с "+date1.DateString()+" по "+date2.DateString();
    }
    else str+="период с "+date1.DateString()+" по "+date2.DateString();
  }
  return str;
}
//---------------------------------------------------------------------------

//Функции для работы с zip архивами
// - Функция извлечения файла из архива
void __fastcall extactDataFromZipFile(TComponent* Owner,AnsiString zipFileName,AnsiString extactPath,TStringList *fileNames,AnsiString fn0)
{
TZipBuilder *zipBuilder;
TList *list;
  try
  {
    zipBuilder=new TZipBuilder(Owner);
  }
  catch (Exception &exc)
  { MessageDlg("Message::Message:Ошибка создания объекта zipBuilder\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  zipBuilder->ZipFileName=zipFileName;
  zipBuilder->ExtrBaseDir=extactPath;
  zipBuilder->List();
  list=zipBuilder->ZipContents;
  fileNames->Clear();
  if((static_cast<ZipDirEntry*>(list->Items[0]))->FileName.Pos(fn0)==0) return;
  for(int i=0; i<list->Count; i++)
  { AnsiString fileName=(static_cast<ZipDirEntry*>(list->Items[i]))->FileName;
    fileNames->Add(fileName);
    fileName=extactPath+fileName;
    if(FileExists(fileName)) DeleteFile(fileName);
  }
  zipBuilder->Extract();
  delete zipBuilder;
  return;
}
//---------------------------------------------------------------------------
// - Функция ахивироания одного или нескольких файлов
AnsiString __fastcall zipArchFiles(TComponent *owner,TStringList *fin, AnsiString zipFileName)
{
TZipBuilder *zipBuilder;

  try
  {
    zipBuilder=new TZipBuilder(owner);
  }
  catch (Exception &exc)
  { MessageDlg("Message::Message:Ошибка создания объекта zipBuilder\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return "";
  }
  zipBuilder->ZipFileName=zipFileName;
  zipBuilder->FSpecArgs->Clear();
  zipBuilder->FSpecArgs->AddStrings(fin);
  zipBuilder->Add();
  if(zipBuilder->ErrCode != 0)
  { MessageDlg("Ошибка создания архива - "+zipFileName+".\n Код ошибки - "+IntToStr(zipBuilder->ErrCode)+".\n"+zipBuilder->Message,mtError,TMsgDlgButtons() << mbOK,0);
    zipFileName="";
  }
  delete zipBuilder;
  return zipFileName;
}
//---------------------------------------------------------------------------
//Вывод в RichEdit строки текста с атрибутами
void putStrToRichEdit(AnsiString str,TRichEdit *edit,TTextAttributes *attr)
{
  edit->SetFocus();
  edit->SelStart=edit->Text.Length();
  edit->SelAttributes->Assign(attr);
  edit->Lines->Add(str);
  edit->SelLength=str.Length();
  edit->SelStart=edit->Text.Length();
  edit->SelLength=0;
  edit->Refresh();
}
//---------------------------------------------------------------------------
void putStrToRichEdit(AnsiString titleStr,AnsiString dataStr,TRichEdit *edit)
{
AnsiString str=titleStr+" - "+dataStr;
int poz=edit->Text.Length();
TTextAttributes *attr=edit->SelAttributes;

//  edit->SetFocus();
  edit->Lines->Add(str);
  edit->SelStart=poz;
  edit->SelLength=titleStr.Length()+3;
  attr->Style=attr->Style << fsBold;
  edit->SelStart=poz+titleStr.Length()+3;
  edit->SelLength=dataStr.Length();
  attr->Style=attr->Style >> fsBold;

  edit->SelStart=edit->Text.Length();
  edit->SelLength=0;
  edit->Refresh();
}
//---------------------------------------------------------------------------

/*using namespace std;

int Date( int D, int M, int Y )
{
    int a, y, m, R;
    a = ( 14 - M ) / 12;
    y = Y - a;
    m = M + 12 * a - 2;
    R = 7000 + ( D + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12 );
    return R % 7;
}

int main()
{
    int D, M, Y;
    char C;
    string S[7] = { "SUN", "MON", "TUS", "WED", "THU", "FRI", "SAT" };
    cin >> D >> C >> M >> C >> Y;
    cout << S[ Date( D, M, Y ) ] << endl;

    system("pause");
    return 0;
}
*/

