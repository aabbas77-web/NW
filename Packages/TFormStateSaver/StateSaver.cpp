//---------------------------------------------------------------------------
#include <basepch.h>
#pragma hdrstop
#include "StateSaver.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TStateSaver::TStateSaver(TComponent* Owner)
  : TComponent(Owner)
{
  if ( ComponentState.Contains(csDesigning) )
  {
    return;
  }
  if ( Owner != NULL )
  {
    Owner->FreeNotification(this);
    LoadState();
  }
}
//---------------------------------------------------------------------------
__fastcall TStateSaver::~TStateSaver()
{
  if ( ComponentState.Contains(csDesigning) )
  {
    return;
  }
  if ( Owner != NULL )
  {
    Owner->RemoveFreeNotification(this);
    SaveState();
  }
}
//---------------------------------------------------------------------------
void __fastcall TStateSaver::Notification( TComponent * AComponent , TOperation Operation )
{
  if ( ComponentState.Contains(csDesigning) )
  {
    return;
  }
  if ( (AComponent == Owner) && (Owner != NULL) && (Operation == opRemove) )
  {
    Owner->RemoveFreeNotification(this);
    SaveState();
  }
}
//---------------------------------------------------------------------------

