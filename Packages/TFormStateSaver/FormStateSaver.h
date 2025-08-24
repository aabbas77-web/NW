//---------------------------------------------------------------------------
#ifndef FormStateSaverH
#define FormStateSaverH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <Forms.hpp>
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
#define FSS_SET_WINDOW_STATE (WM_USER)
//---------------------------------------------------------------------------
class TFormStateSaver;
//---------------------------------------------------------------------------
class TFormStateSaverHook : public TWinControl
{
private:
protected:
  void __fastcall SendMsgToOwner(Messages::TMessage Message);
  MESSAGE void __fastcall WMDestroy(Messages::TMessage &Message);
  MESSAGE void __fastcall CMShowingChanged(Messages::TMessage &Message);
  MESSAGE void __fastcall FSSSetWindowState(Messages::TMessage &Message);

  BEGIN_MESSAGE_MAP
    VCL_MESSAGE_HANDLER(WM_DESTROY, TMessage, WMDestroy)
    VCL_MESSAGE_HANDLER(CM_SHOWINGCHANGED, TMessage, CMShowingChanged)
    VCL_MESSAGE_HANDLER(FSS_SET_WINDOW_STATE, TMessage, FSSSetWindowState);
  END_MESSAGE_MAP(TWinControl)
public:
  __fastcall TFormStateSaverHook(TComponent* Owner);
  __fastcall ~TFormStateSaverHook();
};
//---------------------------------------------------------------------------
class PACKAGE TFormStateSaver : public TComponent
{
private:
  TFormStateSaverHook * FHook;
  TForm * FWindow;
  bool FFormShown;
  bool FSaveWindowState;
  bool FSaveWindowComponentsState;
protected:
	DYNAMIC void __fastcall SetParentComponent(TComponent* Value);
  MESSAGE void __fastcall WMDestroy(Messages::TMessage &Message);
  MESSAGE void __fastcall CMShowingChanged(Messages::TMessage &Message);
  MESSAGE void __fastcall FSSSetWindowState(Messages::TMessage &Message);

  BEGIN_MESSAGE_MAP
    VCL_MESSAGE_HANDLER(WM_DESTROY, TMessage, WMDestroy)
    VCL_MESSAGE_HANDLER(CM_SHOWINGCHANGED, TMessage, CMShowingChanged)
    VCL_MESSAGE_HANDLER(FSS_SET_WINDOW_STATE, TMessage, FSSSetWindowState);
  END_MESSAGE_MAP(TComponent)
public:
  __fastcall TFormStateSaver(TComponent* Owner);
  __fastcall ~TFormStateSaver();
  virtual void __fastcall Restore();
  virtual void __fastcall Save();
__published:
  __property bool SaveWindowState = { read = FSaveWindowState , write = FSaveWindowState , default = false };
  __property bool SaveWindowComponentsState = { read = FSaveWindowComponentsState , write = FSaveWindowComponentsState , default = false };
};
//---------------------------------------------------------------------------
#endif
