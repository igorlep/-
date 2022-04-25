//Класс "Пропись"
//---------------------------------------------------------------------------
#ifndef PropisH
#define PropisH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class Propis
{
private:
  AnsiString string;
  double number, integer, fraction;
  long int rub;
  int kop;
  AnsiString __fastcall triada(int e, int d, int s, char g); //
public:
  __fastcall Propis(double num);
  AnsiString __fastcall IntPropis(void);
  AnsiString __fastcall DoublePropis(void);
  AnsiString __fastcall FractPropis(void);
};
//---------------------------------------------------------------------------

#endif
