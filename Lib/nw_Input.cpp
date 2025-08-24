//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "nw_Input.h"
#include "ProtectionLib.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormnw_Input *Formnw_Input;
//---------------------------------------------------------------------------
__fastcall TFormnw_Input::TFormnw_Input(TComponent* Owner)
	: TForm(Owner)
{
	#ifdef _PROTECTED_
    pro_SoftIceCheck();
	pro_DebuggerCheck();
    pro_Scrambling();
    pro_Check();
    #endif
}
//---------------------------------------------------------------------------
