//����� ������������� �������
//---------------------------------------------------------------------------
#ifndef DifferentFunctionsH
#define DifferentFunctionsH
//---------------------------------------------------------------------------
#include "DBClasses.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
//������� ����������� ���������� ��� ������
unsigned short __fastcall lastDayOfMonth(unsigned short y, unsigned short m);
//������ ������
TDateTime __fastcall beginOfMonth(TDateTime date);
//������� ����� ������ � ����!!!
int __fastcall diffOfDays(TDateTime date1,TDateTime date2);
//���������� ����! � ������!!
unsigned short __fastcall KolOfDaysinMonth(unsigned short y,unsigned short m);
//����� ������
TDateTime __fastcall endOfMonth(TDateTime date);
TDateTime __fastcall endOfMonth(unsigned short y, unsigned short m);
//���� ����
unsigned short __fastcall dayOfDate(TDateTime date);
//�����
AnsiString __fastcall monthOfDate(TDateTime date);
AnsiString __fastcall namemonthOfDate(int m);
//����� ������
unsigned short __fastcall nummonthOfDate(TDateTime date);
//���
unsigned short __fastcall yearOfDate(TDateTime date);
//��������� ������� ��� ������ � �����
AnsiString __fastcall getMonthYearString(TDateTime date);
TDateTime __fastcall getDateFromMonthYearString(AnsiString myStr);

//������� ���������� ��������� �� ������ � �������������
//AnsiString __fastcall getSubstring(AnsiString str, char r, int n);

//������� ��� ������ � �������� ������
// - ��������� ������ �������� ��������� ���� ��� tableName
AnsiString __fastcall getNewKeyValue(FBDatabase * fb_db, AnsiString tableName);
AnsiString __fastcall getNewKeyValue(FBQuery * fbWQ, AnsiString tableName);
void __fastcall setGenerator(FBQuery *fbWQ,AnsiString tableName,AnsiString genName,AnsiString keyName);
//������� ��������� ������� � ������� tableName ������ � ����� id
bool __fastcall checkRecord(TComponent* owner,FBDatabase *fbDB,AnsiString tableName,AnsiString id_name,AnsiString id);

// - ��������� �������� ���� fieldName ������� tableName �� �������� keyData ��������� ���� keyFieldName
//AnsiString __fastcall getDataForFieldName(FBDatabase * fbdb,AnsiString tableName,AnsiString keyFieldName,AnsiString keiData, AnsiString fieldName);

//������� ��� ������ � �������� ��������
AnsiString __fastcall getConstName(TComponent* owner,FBDatabase * fb_db,AnsiString identifer);
AnsiString __fastcall getConstTitle(TComponent* owner,FBDatabase * fb_db,AnsiString identifer);
AnsiString __fastcall getConstValue(TComponent* owner,FBDatabase * fb_db,AnsiString identifer,TDateTime date=0,AnsiString sd_id="");
int __fastcall getConstType(TComponent* owner,FBDatabase * fb_db,AnsiString identifer);
int __fastcall getConstKind(TComponent* owner,FBDatabase * fb_db,AnsiString identifer);

void  __fastcall setConstValue(FBDatabase * fb_db,AnsiString identifer, AnsiString constValue);
//������� ��� ������ � �������������� �����������
bool  __fastcall setPeriodicalConstValue(FBDatabase * fb_db,AnsiString const_id,int &value_id,AnsiString constValue,TDateTime constDate);
void  __fastcall delPeriodicalConstValue(FBDatabase * fb_db,AnsiString value_id);
AnsiString __fastcall getPeriodicalParamValue(FBDatabase * fb_db,AnsiString tableInfo,AnsiString keyID,TDateTime forDate);


//������� �������� ����������� �������������� ������ �� ���������� ���� ��� ����������� ������������
bool checkPossibileEditingData(FBDatabase * fb_db,TDateTime actualDate,int userID);

//������� �������������� ����� � ������ ��������
//������� �������������� ������������� ����� � ������������ �������� ���. � ���.
AnsiString f_to_str(double d);
AnsiString i_to_str(int i);

//�������, ������������ ���������� ������������� - GUID
AnsiString __fastcall genGUID(void);

//������� ������������ ������ ���������
AnsiString __fastcall SetHeader(AnsiString str, TDateTime date1, TDateTime date2);

//������� ��� ������ � zip ��������
// - ������� ���������� ����� �� ������
void __fastcall extactDataFromZipFile(TComponent* Owner,AnsiString zipFileName,AnsiString extactPath,TStringList *fileNames,AnsiString fn0);
// - ������� ����������� ������ ��� ���������� ������
AnsiString __fastcall zipArchFiles(TComponent *owner,TStringList *fin, AnsiString zipFileName);

//����� � RichEdit ������ ������ � ����������
void putStrToRichEdit(AnsiString str,TRichEdit *edit,TTextAttributes *attr);
void putStrToRichEdit(AnsiString titleStr,AnsiString dataStr,TRichEdit *edit);

#endif
