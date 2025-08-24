//---------------------------------------------------------------------------
#ifndef StateSaverH
#define StateSaverH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TStateSaver : public TComponent
{
private:
protected:
	virtual void __fastcall Notification(TComponent* AComponent, TOperation Operation);
  virtual void __fastcall LoadState() = 0;
  virtual void __fastcall SaveState() = 0;
public:
  __fastcall TStateSaver(TComponent* Owner);
  __fastcall ~TStateSaver();
__published:
};
//---------------------------------------------------------------------------
#endif
 