//---------------------------------------------------------------------------
//���� �������� ������ DBF_File ��� p����� � DBF �������

#ifndef DBF_FileH
#define DBF_FileH

#include <vcl.h>
//---------------------------------------------------------------------------
//��p����p� � ��������� ��p��� 32 ���� ��������� �����
struct DBF_FileHead
{
char FileTyp;		     //��� �����
			     //���� ���������� ���������
char Year;		       //��� ��������� ���p� ����
char Mon;		       //�����
char Day;		       //����
unsigned int RecordQuantity;	     //���������� ������� � �����
unsigned short HeadLength;   //����� ��������� � ������
unsigned short RecordLength; //����� ����� ������ � ������� (������� ���� � �p������� �������� ������)
char Rezerv_1[16];	     //��p���p��p����� ��� ����p������ �������������
char MultyIndex;	     //1-���� ��������� ��������� ���� (���� .cdx), 0-���
char Rezerv_2[3];	     //��p���p��p����� ��� ����p������ �������������
};

//��p����p� � ��������� ���� � ��������� �����
struct DBF_FieldHead
{
char Field_Name[11];	     //������������ ����
char Typ;		     //��� ������, �������� � ����
unsigned long FieldPosition; //��������� ���� ������ ������
unsigned char FieldLength;   //����� ���� � ������
unsigned char FieldDec;      //����� ���������� ���� ����� �����
char Rezerv[14]; 	     //��p���p��p����� ��� ����p������ �������������
};

class DBF_File
{
  protected:

  public:
    AnsiString DBF_FileName;	//��� ����� � �����
    DBF_FileHead FH;		//��������� �����
    int Handle;                 //���������� �����
    unsigned short FieldQuantity; //����� ����� � ������
    DBF_FieldHead **F_H; 	//��������� �����
    char *Record;		//����� ��� ������ ������
    char **Field;		//��������� �� ���� � ������
    bool SuccessFLG;            //���� ��������� �������� ������� ������
    //������� ������
    __fastcall DBF_File(AnsiString &file_name); //����������� ������
    __fastcall ~DBF_File();		        //���������� ������
    bool __fastcall RecordRead(long rec_num);	//������� ������ ������ � �����
    AnsiString __fastcall FieldToAnsiString(int field_num); //����������� ���� � �����
    bool __fastcall RecordWrite(long rec_num); //������� ������ ������ �� ����
    void __fastcall AnsiStringToField(int field_num, AnsiString &s); //����������� ������ � ����
//    void Base_view(void);	   //������� ��������� ���� ������
//    void Struct_view(void);	   //������� ��������� ��������� ������
//    void Field_write(long int,int);//������ ���� � ���� (�� ����)
//    void Record_del(long int);	   //�������� ������ (������ ���������� ��� ���������)
//    void Record_undel(long int);   //������ �������� ������ (��������� ������� ������ �� ��������)
//    void Record_add(void);	   //���������� ������
};

#endif
