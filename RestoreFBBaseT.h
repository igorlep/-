//---------------------------------------------------------------------------

#ifndef RestoreFBBaseTH
#define RestoreFBBaseTH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "JvMemo.hpp"
#include <IBServices.hpp>
#include "JvProgressBar.hpp"
//---------------------------------------------------------------------------
class RestoreFBBaseThread : public TThread
{            
private:
TIBRestoreService *RestoreService;
TRichEdit *RichEdit;
TJvProgressBar *ProgressBar;
int calc;
bool verboseFLG;
protected:
  void __fastcall Execute();
  void __fastcall UpdateCaption();
public:
  __fastcall RestoreFBBaseThread(bool CreateSuspended,AnsiString serverName,bool verboseFLG,AnsiString baseName,AnsiString backupFileName,TRichEdit *RichEdit,TJvProgressBar *ProgressBar);
  __fastcall ~RestoreFBBaseThread(void);
};
//---------------------------------------------------------------------------
#endif
