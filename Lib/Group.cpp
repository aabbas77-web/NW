//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Group.h"
#include "DataModule.h"
#include "ProtectionLib.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormGroup *FormGroup;
//---------------------------------------------------------------------------
__fastcall TFormGroup::TFormGroup(TComponent* Owner)
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

