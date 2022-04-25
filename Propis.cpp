//����� - ����� ��������
//---------------------------------------------------------------------------
#include "math.h"
#pragma hdrstop

#include "Propis.h"
//---------------------------------------------------------------------------
__fastcall Propis::Propis(double num)
{
  number=num;
  fraction=modf(number, &integer);
  rub=(long int)integer;
  kop=int(floor(fraction*100+0.5));
  string="";
  if(rub < 0){ string+="-"; rub=-rub;}
}
//---------------------------------------------------------------------------
// �������������� ���� ���� (�����, �������, �������) � ������,
// g- ���: �-�������, �-�������, �-�������
AnsiString __fastcall Propis::triada(int s, int d, int e, char g)
{
char *hundreds[]  = {"��� ","������ ","������ ","��������� ","������� ","�������� ","������� ","��������� ","��������� "};
char *tens[]      = {"������ ","�������� ","�������� ","����� ","��������� ","���������� ","��������� ","����������� ","��������� "};
char *units[]     = {"���� ","��� ","��� ","������ ","���� ","����� ","���� ","������ ","������ "};
char *units_1[ ]  = {"���� ","��� ","��� ","������ ","���� ","����� ","���� ","������ ","������ "};
char *units_2[ ]  = {"���� ","��� ","��� ","������ ","���� ","����� ","���� ","������ ","������ "};
char *second_ten[]={"����������� ","���������� ","���������� ","������������ ","���������� ","����������� ","���������� ","������������ ","������������ "};
AnsiString buf="";

  if(s!=0) buf=AnsiString(hundreds[s-1]);
  if(d!=1)
  { if(d!=0) buf+=AnsiString(tens[d-1]);
    if(e!=0)
    { if(g=='�') buf+=AnsiString(units[e-1]);
      else if(g=='�') buf+=AnsiString(units_1[e-1]);
      else buf+=AnsiString(units_2[e-1]);
    }
  }
  else
  { if(e==0) buf+=AnsiString(tens[0]);
    else buf+=AnsiString(second_ten[e-1]);
  }
  return buf;
}
//---------------------------------------------------------------------------
// �������������� �������� ������ � ������
AnsiString __fastcall Propis::IntPropis(void)
{
int triads[4][3];
int t,e;

  for(t=0; t<4; ++t) for(e=0; e<3; ++e) triads[t][e]=0l;
  t=0;
  do
  {
    for(e=0; e<3; ++e){ triads[t][e]=rub%10; rub/=10;}
    ++t;
  }while(rub!=0 && t<4);
  //��������
  if(triads[3][0]!=0 || triads[3][1]!=0 || triads[3][2]!=0)
  { string+=triada(triads[3][2],triads[3][1],triads[3][0],'�');
    if(triads[3][0]==1)
    { if(triads[3][1]==1) string+="���������� ";
      else string+="�������� ";
    }
    else if(triads[3][0]>1 && triads[3][0]<5)
    { if(triads[3][1]!=1) string+="��������� ";
      else string+="���������� ";
    }
    else string+="���������� ";
  }
  //��������
  if(triads[2][0]!=0 || triads[2][1]!=0 || triads[2][2]!=0)
  { string+=triada(triads[2][2],triads[2][1],triads[2][0],'�');
    if(triads[2][0]==1)
    { if(triads[2][1]==1) string+="��������� ";
      else string+="������� ";
    }
    else if(triads[2][0]>1 && triads[2][0]<5)
    { if(triads[2][1]!=1) string+="�������� ";
      else string+="��������� ";
    }
    else string+="��������� ";
  }
  //������
  if(triads[1][0]!=0 || triads[1][1]!=0 || triads[1][2]!=0)
  { string+=triada(triads[1][2],triads[1][1],triads[1][0],'�');
    if(triads[1][0]==1)
    { if(triads[1][1]==1) string+="����� ";
      else string+="������ ";
    }
    else if(triads[1][0]>1 && triads[1][0]<5)
    { if(triads[1][1]!=1) string+="������ ";
      else string+="����� ";
    }
    else string+="����� ";
  }
  //�����
  string+=triada(triads[0][2],triads[0][1],triads[0][0],'�');
  return string;
}
//---------------------------------------------------------------------------
AnsiString __fastcall Propis::FractPropis(void)
{
  return AnsiString().sprintf("%02d",kop);
}
//---------------------------------------------------------------------------
// �������������� ����� ������� �������� � ������ ���.���.
AnsiString __fastcall Propis::DoublePropis()
{
  return IntPropis()+"���. "+FractPropis()+" ���.";
}
//---------------------------------------------------------------------------
