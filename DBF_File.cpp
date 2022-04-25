//---------------------------------------------------------------------------

#include <stdio.h>
#pragma hdrstop
#include <string.h>

#include "DBF_File.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//����������� ������
__fastcall DBF_File::DBF_File(AnsiString &file_name)
{
  SuccessFLG=false;
  Handle=-1;
  DBF_FileName=file_name;
  if(!FileExists(DBF_FileName))
  { MessageDlg("���� - "+DBF_FileName+" �����������",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  //��������� ���� � ����� ������
  if((Handle=FileOpen(DBF_FileName,fmOpenReadWrite))<0)
  { MessageDlg("������ �������� ����� - "+DBF_FileName,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  //������ ������ 32 ����� ��������� � ���������� ����� ����� � ������
  if(FileRead(Handle,(char*)&FH,sizeof(FH)) != sizeof(FH))
  { MessageDlg("������ ������ ��������� ����� - "+DBF_FileName,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  //���������� �����
  FieldQuantity=(FH.HeadLength-1)/32-1;
//  FieldQuantity=(float(FH.HeadLength)/32)-9.25;
  if(FieldQuantity == 0 || FieldQuantity > 255)
  { MessageDlg("������ ���������� ����� � ������ - "+IntToStr(FieldQuantity),mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  //���������� ������ �������� � ��������� ����� � ��������� ���� ������ ������� �� ��������� �����
  F_H=NULL;
  if((F_H=new DBF_FieldHead*[FieldQuantity])==NULL)
  { MessageDlg("������ �������� F_H",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  for(int i=0; i<FieldQuantity; ++i)
  { F_H[i]=NULL;
    if((F_H[i]=new DBF_FieldHead)==NULL)
    { MessageDlg("������ �������� F_H["+IntToStr(i)+"]",mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
    FileRead(Handle,(char*)F_H[i],sizeof(DBF_FieldHead));
    if(i==0) F_H[i]->FieldPosition=1;
    else F_H[i]->FieldPosition=F_H[i-1]->FieldPosition+F_H[i-1]->FieldLength;
  }
  //���������� ����� ��� ������ ������
  Record=NULL;
  if((Record=new char[FH.RecordLength])==NULL)
  { MessageDlg("������ �������� ������ ��� ������ ������",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  //���������� ������ ���������� �� ���� ������
  Field=NULL;
  if((Field=new char*[FieldQuantity])==NULL)
  { MessageDlg("������ �������� ������� ���������� �� ���� ������",mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  for(int i=0; i<FieldQuantity; ++i) Field[i]=Record+F_H[i]->FieldPosition;
  SuccessFLG=true;
}
//..................... end of DBF_File::DBF_File .................
//---------------------------------------------------------------------------
//���������� ������
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
//������� ������ ������
bool __fastcall DBF_File::RecordRead(long rec_num)
{
int poz;

  if(rec_num > FH.RecordQuantity)
  { MessageDlg("DBF_File::RecordRead - ����� ������ ������ ���������� �������",mtError,TMsgDlgButtons() << mbOK,0);
    return false;
  }

  poz=FH.HeadLength+FH.RecordLength*(rec_num-1);

  FileSeek(Handle,poz,0);
  int rb=FileRead(Handle,Record,FH.RecordLength);
  if(rb != FH.RecordLength)
  { MessageDlg("DBF_File::RecordRead - ��������� "+IntToStr(rb)+" ����, ���� - "+IntToStr(FH.RecordLength),mtError,TMsgDlgButtons() << mbOK,0);
    return false;
  }
  return true;
}
//..................... end of DBF_File::RecordRead ................
//---------------------------------------------------------------------------
//������� ������
bool __fastcall DBF_File::RecordWrite(long rec_num)
{ //���� rec_num = 0, �� ������ �����������
int poz;
bool AddFLG=false;

  if(rec_num > FH.RecordQuantity)
  { MessageDlg("DBF_File::RecordWrite - ����� ������ ������ ���������� �������",mtError,TMsgDlgButtons() << mbOK,0);
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
  { MessageDlg("DBF_File::RecordWrite - �������� "+IntToStr(rb)+" ����, ���� ���� - "+IntToStr(FH.RecordLength),mtError,TMsgDlgButtons() << mbOK,0);
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
//����������� ���� � ������
AnsiString __fastcall DBF_File::FieldToAnsiString(int field_num)
{
AnsiString s=Record, buf="";

  buf=s.SubString(F_H[field_num-1]->FieldPosition+1,F_H[field_num-1]->FieldLength);
  return buf.TrimRight();
}
//.................... end of DBF_File::FieldToAnsiString ..........
//---------------------------------------------------------------------------
//����������� ������ � ����
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

