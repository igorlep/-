// ласс - число прописью
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
// преобразование трех цифр (сотни, дес€тки, единицы) в строку,
// g- род: м-мужской, ж-женский, с-средний
AnsiString __fastcall Propis::triada(int s, int d, int e, char g)
{
char *hundreds[]  = {"сто ","двести ","триста ","четыреста ","п€тьсот ","шестьсот ","семьсот ","восемьсот ","дев€тьсот "};
char *tens[]      = {"дес€ть ","двадцать ","тридцать ","сорок ","п€тьдес€т ","шестьдес€т ","семьдес€т ","восемьдес€т ","дев€носто "};
char *units[]     = {"один ","два ","три ","четыре ","п€ть ","шесть ","семь ","восемь ","дев€ть "};
char *units_1[ ]  = {"одна ","две ","три ","четыре ","п€ть ","шесть ","семь ","восемь ","дев€ть "};
char *units_2[ ]  = {"одно ","два ","три ","четыре ","п€ть ","шесть ","семь ","восемь ","дев€ть "};
char *second_ten[]={"одиннадцать ","двенадцать ","тринадцать ","четырнадцать ","п€тнадцать ","шестнадцать ","семнадцать ","восемнадцать ","дев€тнадцать "};
AnsiString buf="";

  if(s!=0) buf=AnsiString(hundreds[s-1]);
  if(d!=1)
  { if(d!=0) buf+=AnsiString(tens[d-1]);
    if(e!=0)
    { if(g=='м') buf+=AnsiString(units[e-1]);
      else if(g=='ж') buf+=AnsiString(units_1[e-1]);
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
// преобразование длинного целого в строку
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
  //ћиллиады
  if(triads[3][0]!=0 || triads[3][1]!=0 || triads[3][2]!=0)
  { string+=triada(triads[3][2],triads[3][1],triads[3][0],'м');
    if(triads[3][0]==1)
    { if(triads[3][1]==1) string+="миллиардов ";
      else string+="миллиард ";
    }
    else if(triads[3][0]>1 && triads[3][0]<5)
    { if(triads[3][1]!=1) string+="миллиарда ";
      else string+="миллиардов ";
    }
    else string+="миллиардов ";
  }
  //ћиллионы
  if(triads[2][0]!=0 || triads[2][1]!=0 || triads[2][2]!=0)
  { string+=triada(triads[2][2],triads[2][1],triads[2][0],'м');
    if(triads[2][0]==1)
    { if(triads[2][1]==1) string+="миллионов ";
      else string+="миллион ";
    }
    else if(triads[2][0]>1 && triads[2][0]<5)
    { if(triads[2][1]!=1) string+="миллиона ";
      else string+="миллионов ";
    }
    else string+="миллионов ";
  }
  //“ыс€чи
  if(triads[1][0]!=0 || triads[1][1]!=0 || triads[1][2]!=0)
  { string+=triada(triads[1][2],triads[1][1],triads[1][0],'ж');
    if(triads[1][0]==1)
    { if(triads[1][1]==1) string+="тыс€ч ";
      else string+="тыс€ча ";
    }
    else if(triads[1][0]>1 && triads[1][0]<5)
    { if(triads[1][1]!=1) string+="тыс€чи ";
      else string+="тыс€ч ";
    }
    else string+="тыс€ч ";
  }
  //—отни
  string+=triada(triads[0][2],triads[0][1],triads[0][0],'м');
  return string;
}
//---------------------------------------------------------------------------
AnsiString __fastcall Propis::FractPropis(void)
{
  return AnsiString().sprintf("%02d",kop);
}
//---------------------------------------------------------------------------
// преобразование цисла двойной точности в строку руб.коп.
AnsiString __fastcall Propis::DoublePropis()
{
  return IntPropis()+"руб. "+FractPropis()+" коп.";
}
//---------------------------------------------------------------------------
