//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Users.h"
#include "DataModule.h"
#include "ChangePass.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FIBDatabase"
#pragma link "pFIBDatabase"
#pragma resource "*.dfm"
//TChangePassForm *ChangePassForm;
//---------------------------------------------------------------------------
__fastcall TChangePassForm::TChangePassForm(TComponent* Owner, unsigned int u_id)
        : TForm(Owner)
{
AnsiString sql;

  U_ID=u_id;
  Q->Close();
  Q->SQL->Clear();
  sql="select USER_PASSWORD from USERS where ID="+IntToStr(U_ID);
  Q->SQL->Add(sql);
  try
  {
    Q->ExecQuery();
  }
  catch(const Exception &exc)
  { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
    return;
  }
  userPWD=Q->FieldByName("USER_PASSWORD")->AsString;
}
//---------------------------------------------------------------------------
void __fastcall TChangePassForm::OldPasswordKeyPress(TObject *Sender,
      char &Key)
{
  if(Key==VK_RETURN) NewPassword1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TChangePassForm::NewPassword1KeyPress(TObject *Sender,
      char &Key)
{
  if(Key==VK_RETURN) NewPassword2->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TChangePassForm::SaveButtonClick(TObject *Sender)
{
  if(userPWD!=OldPassword->Text)
  { MessageDlg("Направильный старый пароль",mtError,TMsgDlgButtons() << mbOK,0);
    OldPassword->Text="";
    OldPassword->SetFocus();
    return;
  }
  else if(NewPassword1->Text!=NewPassword2->Text)
  { MessageDlg("Ошибка при вводе нового пароля",mtError,TMsgDlgButtons() << mbOK,0);
    NewPassword1->Text=""; NewPassword2->Text="";
    NewPassword1->SetFocus();
    return;
  }
  else if(NewPassword1->Text.IsEmpty())
  { MessageDlg("Пароль не может быть пустым",mtError,TMsgDlgButtons() << mbOK,0);
    NewPassword1->SetFocus();
    return;
  }
  else
  { Q->Close();
    Q->SQL->Clear();
    AnsiString sql="update USERS set USER_PASSWORD='"+NewPassword1->Text+"' where ID="+IntToStr(U_ID);
    Q->SQL->Add(sql);
    try
    {
      Q->ExecQuery();
    }
    catch(const Exception &exc)
    { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
  }
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TChangePassForm::CancelButtonClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TChangePassForm::OldPasswordDblClick(TObject *Sender)
{
  if(SaleBookDM->UserRole == "Администратор")
  { OldPassword->PasswordChar=NULL;
    Q->Close();
    Q->SQL->Clear();
    AnsiString sql="select USER_PASSWORD from USERS where ID="+IntToStr(U_ID);
    Q->SQL->Add(sql);
    try
    {
      Q->ExecQuery();
    }
    catch(const Exception &exc)
    { MessageDlg("Ошибка - "+sql+"\n"+exc.Message,mtError,TMsgDlgButtons() << mbOK,0);
      return;
    }
    OldPassword->Text=Q->FieldByName("USER_PASSWORD")->AsString;
  }
}
//---------------------------------------------------------------------------

