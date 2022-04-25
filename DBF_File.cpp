//---------------------------------------------------------------------------

#include <stdio.h>
#pragma hdrstop
#include <string.h>

#include "DBF_File.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//Конструктор класса
__fastcall DBF_File::DBF_File(AnsiString &file_name)
{
  SuccessFLG=false;
  Handle=-1;
  DBF_FileName=file_name;
  if(!FileExists(DBF_FileName))
  { MessageDlg("Файл - "+DBF_FileName+" отсутствует",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  //Открываем файл с базой данных
  if((Handle=FileOpen(DBF_FileName,fmOpenReadWrite))<0)
  { MessageDlg("Ошибка открытия Файла - "+DBF_FileName,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  //Читаем первые 32 байта заголовка и определяем число полей в записи
  if(FileRead(Handle,(char*)&FH,sizeof(FH)) != sizeof(FH))
  { MessageDlg("Ошибка чтения заголовка файла - "+DBF_FileName,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  //Количество полей
  FieldQuantity=(FH.HeadLength-1)/32-1;
//  FieldQuantity=(float(FH.HeadLength)/32)-9.25;
  if(FieldQuantity == 0 || FieldQuantity > 255)
  { MessageDlg("Ошибка количества полей в записи - "+IntToStr(FieldQuantity),mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  //Инициируем массив структур с описанием полей и заполняем этот массив данными из заголовка файла
  F_H=NULL;
  if((F_H=new DBF_FieldHead*[FieldQuantity])==NULL)
  { MessageDlg("Ошибка создания F_H",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  for(int i=0; i<FieldQuantity; ++i)
  { F_H[i]=NULL;
    if((F_H[i]=new DBF_FieldHead)==NULL)
    { MessageDlg("Ошибка создания F_H["+IntToStr(i)+"]",mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
    FileRead(Handle,(char*)F_H[i],sizeof(DBF_FieldHead));
    if(i==0) F_H[i]->FieldPosition=1;
    else F_H[i]->FieldPosition=F_H[i-1]->FieldPosition+F_H[i-1]->FieldLength;
  }
  //Инициируем буфер для чтения записи
  Record=NULL;
  if((Record=new char[FH.RecordLength])==NULL)
  { MessageDlg("Ошибка создания буфера для чтения записи",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  //Инициируем массив указателей на поля записи
  Field=NULL;
  if((Field=new char*[FieldQuantity])==NULL)
  { MessageDlg("Ошибка создания массива указателей на поля записи",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  for(int i=0; i<FieldQuantity; ++i) Field[i]=Record+F_H[i]->FieldPosition;
  SuccessFLG=true;
}
//..................... end of DBF_File::DBF_File .................
//---------------------------------------------------------------------------
//Деструктор класса
__fastcall DBF_File::~DBF_File()
{
  if(Handle >= 0) FileClose(Handle);
  if(F_H!=NULL)
  { for(int i=0; i<FieldQuantity; ++i) if(F_H[i]!=NULL){ delete F_H[i]; F_H[i]=NULL;}
    delete[] F_H; F_H=NULL;
  }
  if(Record!=NULL){ delete[] Record; Record=NULL;}
  if(Field!=NULL) { delete[] Field;  Field=NULL;}
}
//..................... end of DBF_File::~DBF_File .................
//---------------------------------------------------------------------------
//Функция чтения записи
bool __fastcall DBF_File::RecordRead(long rec_num)
{
int poz;

  if(rec_num > FH.RecordQuantity)
  { MessageDlg("DBF_File::RecordRead - Номер записи больше количества записей",mtError,TMsgDlgButtons() << mbOK,0);
    return false;
  }

  poz=FH.HeadLength+FH.RecordLength*(rec_num-1);

  FileSeek(Handle,poz,0);
  int rb=FileRead(Handle,Record,FH.RecordLength);
  if(rb != FH.RecordLength)
  { MessageDlg("DBF_File::RecordRead - Прочитано "+IntToStr(rb)+" байт, надо - "+IntToStr(FH.RecordLength),mtError,TMsgDlgButtons() << mbOK,0);
    return false;
  }
  return true;
}
//..................... end of DBF_File::RecordRead ................
//---------------------------------------------------------------------------
//Функция записи
bool __fastcall DBF_File::RecordWrite(long rec_num)
{ //если rec_num = 0, то запись добавляется
int poz;
bool AddFLG=false;

  if(rec_num > FH.RecordQuantity)
  { MessageDlg("DBF_File::RecordWrite - номер записи больше количества записей",mtError,TMsgDlgButtons() << mbOK,0);
    return false;
  }

  if(rec_num==0)
  { FH.RecordQuantity++;
    FileSeek(Handle,4,0);
    FileWrite(Handle,(char*)(&FH.RecordQuantity),sizeof(FH.RecordQuantity));
    rec_num=FH.RecordQuantity;
    AddFLG=true;
  }
  poz=FH.HeadLength+FH.RecordLength*(rec_num-1);
  FileSeek(Handle,poz,0);

  int rb=FileWrite(Handle,Record,FH.RecordLength);
  if(rb != FH.RecordLength)
  { MessageDlg("DBF_File::RecordWrite - Записано "+IntToStr(rb)+" байт, надо было - "+IntToStr(FH.RecordLength),mtError,TMsgDlgButtons() << mbOK,0);
    return false;
  }
  if(AddFLG)
  { FileSeek(Handle,0,2);
    FileWrite(Handle,"\x1A",1);
  }

  return true;
}
//.................... end of DBF_File::RecordWrite ................
//---------------------------------------------------------------------------
//Копирование поля в строку
AnsiString __fastcall DBF_File::FieldToAnsiString(int field_num)
{
AnsiString s=Record, buf="";

  buf=s.SubString(F_H[field_num-1]->FieldPosition+1,F_H[field_num-1]->FieldLength);
  return buf.TrimRight();
}
//.................... end of DBF_File::FieldToAnsiString ..........
//---------------------------------------------------------------------------
//Копирование строки в поле
void __fastcall DBF_File::AnsiStringToField(int field_num, AnsiString &buf)
{
AnsiString r=Record, s;
int p=buf.Length();

  while(p < F_H[field_num-1]->FieldLength){ buf+=' '; ++p;}
  p=F_H[field_num-1]->FieldPosition;
  for(int i=0; i<F_H[field_num-1]->FieldLength; ++i){ Record[p]=(buf.c_str())[i]; ++p;}
}
//.................... end of DBF_File::AnsiStringToField ..........
//---------------------------------------------------------------------------

