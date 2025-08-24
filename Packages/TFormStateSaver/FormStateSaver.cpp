//---------------------------------------------------------------------------
#include <basepch.h>
#pragma hdrstop
#include "FormStateSaver.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
static inline void ValidCtrCheck(TFormStateSaver *)
{
  new TFormStateSaver(NULL);
}
//---------------------------------------------------------------------------
__fastcall TFormStateSaver::TFormStateSaver(TComponent* Owner)
  : TComponent(Owner)
{
  FWindow = dynamic_cast<TForm *> (Owner);
  FHook = NULL;
  if ( !ComponentState.Contains(csDesigning) )
  {
    FHook = new TFormStateSaverHook(this);
  }
  FFormShown = false;
}
//---------------------------------------------------------------------------
__fastcall TFormStateSaver::~TFormStateSaver()
{
}
//---------------------------------------------------------------------------
namespace Formstatesaver
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TFormStateSaver)};
     RegisterComponents("WWPTC", classes, 0);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormStateSaver::SetParentComponent(TComponent* Value)
{
  TComponent::SetParentComponent(Value);
  TWinControl * vWinControl = dynamic_cast<TWinControl *> (Value);
  if ( (!ComponentState.Contains(csDesigning)) && (vWinControl != NULL) )
  {
    FHook->Parent = (TWinControl *) Value;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormStateSaver::WMDestroy(Messages::TMessage &Message)
{
  if ( !ComponentState.Contains(csDesigning) )
  {
    Save();
  }
//  TComponent::WMDestroy(&Message);
}
//---------------------------------------------------------------------------
void __fastcall TFormStateSaver::CMShowingChanged(Messages::TMessage &Message)
{
//  TComponent::CMShowingChanged(Message);
  if ( !FFormShown )
  {
    FFormShown = true;
    if ( !ComponentState.Contains(csDesigning) )
    {
      Restore();
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormStateSaver::FSSSetWindowState(Messages::TMessage &Message)
{
  if ( (!ComponentState.Contains(csDesigning)) && (FWindow != NULL) )
  {
    switch ( TWindowState(Message.LParam) )
    {
      case wsMaximized : FWindow->WindowState = wsMaximized;
      case wsMinimized : if ( Application->MainForm == FWindow )
                         {
                           Application->Minimize();
                         }
                         else
                         {
                           FWindow->WindowState = wsMinimized;
                         }
      default          : FWindow->WindowState = wsNormal;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormStateSaver::Restore()
{
  if ( (!ComponentState.Contains(csDesigning)) && (FWindow != NULL) )
  {
    TIniFile * f = new TIniFile(ChangeFileExt(Application->ExeName, ".State.ini"));
    int Left, Top, Width, Height, State;
    //  The Components of the Window
    if ( SaveWindowComponentsState )
    {
      for ( int i = 0 ; i < Owner->ComponentCount ; i++ )
      {
        TControl * vControl = dynamic_cast<TControl *> (Owner->Components[i]);
        if ( vControl != NULL )
        {
          vControl->Left = f->ReadInteger(FWindow->Name, vControl->Name+"_Left", vControl->Left);
          vControl->Top = f->ReadInteger(FWindow->Name, vControl->Name+"_Top", vControl->Top);
          vControl->Width = f->ReadInteger(FWindow->Name, vControl->Name+"_Width", vControl->Width);
          vControl->Height = f->ReadInteger(FWindow->Name, vControl->Name+"_Height", vControl->Height);
        }
      }
    }
    //  The Default Values ...
    Left = FWindow->Left;
    Top = FWindow->Top;
    Width = FWindow->Width;
    Height = FWindow->Height;
    State = FWindow->WindowState;
    //  Loading In INI File ...
    Left = f->ReadInteger(FWindow->Name, "Left", Left);
    Top = f->ReadInteger(FWindow->Name, "Top", Top);
    Width = f->ReadInteger(FWindow->Name, "Width", Width);
    Height = f->ReadInteger(FWindow->Name, "Height", Height);
    State = f->ReadInteger(FWindow->Name, "State", State);
    //  Applying The Measurments ...
    FWindow->Position = poDesigned;
    FWindow->Left = Left;
    FWindow->Top = Top;
    FWindow->Width = Width;
    FWindow->Height = Height;
    //  Applying The State ...
    if ( SaveWindowState )
    {
      PostMessage(FHook->Handle, FSS_SET_WINDOW_STATE, 0, State);
    }
    delete f;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormStateSaver::Save()
{
  if ( (!ComponentState.Contains(csDesigning)) && (FWindow != NULL) )
  {
    TIniFile * f = new TIniFile(ChangeFileExt(Application->ExeName, ".State.ini"));
    int Left, Top, Width, Height, State;
    //  The Components of the Window
    if ( SaveWindowComponentsState )
    {
      for ( int i = 0 ; i < Owner->ComponentCount ; i++ )
      {
        TControl * vControl = dynamic_cast<TControl *> (Owner->Components[i]);
        if ( vControl != NULL )
        {
          f->WriteInteger(FWindow->Name, vControl->Name+"_Left", vControl->Left);
          f->WriteInteger(FWindow->Name, vControl->Name+"_Top", vControl->Top);
          f->WriteInteger(FWindow->Name, vControl->Name+"_Width", vControl->Width);
          f->WriteInteger(FWindow->Name, vControl->Name+"_Height", vControl->Height);
        }
      }
    }
    //  Get The Measurment ...
    Left = FWindow->Left;
    Top = FWindow->Top;
    Width = FWindow->Width;
    Height = FWindow->Height;
    //  Get The State ...
    if ( (Application->MainForm == FWindow) && (IsIconic(Application->Handle)) )
    {
      State = wsMinimized;
    }
    else
    {
      State = FWindow->WindowState;
    }
    //  Saving in INI File ...
    f->WriteInteger(FWindow->Name, "Left", Left);
    f->WriteInteger(FWindow->Name, "Top", Top);
    f->WriteInteger(FWindow->Name, "Width", Width);
    f->WriteInteger(FWindow->Name, "Height", Height);
    f->WriteInteger(FWindow->Name, "State", State);
    delete f;
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TFormStateSaverHook::TFormStateSaverHook(TComponent* Owner)
  : TWinControl(Owner)
{
}
//---------------------------------------------------------------------------
__fastcall TFormStateSaverHook::~TFormStateSaverHook()
{
}
//---------------------------------------------------------------------------
void __fastcall TFormStateSaverHook::SendMsgToOwner(Messages::TMessage Message)
{
  Owner->Dispatch(&Message);
}
//---------------------------------------------------------------------------
void __fastcall TFormStateSaverHook::WMDestroy(Messages::TMessage &Message)
{
  SendMsgToOwner(Message);
//  TWinControl::WMDestroy(&Message);
}
//---------------------------------------------------------------------------
void __fastcall TFormStateSaverHook::CMShowingChanged(Messages::TMessage &Message)
{
//  TWinControl::CMShowingChanged(Message);
  SendMsgToOwner(Message);
}
//---------------------------------------------------------------------------
void __fastcall TFormStateSaverHook::FSSSetWindowState(Messages::TMessage &Message)
{
  SendMsgToOwner(Message);
}
//---------------------------------------------------------------------------

