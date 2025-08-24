//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "nw_Messages.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormMessages *FormMessages;
//---------------------------------------------------------------------------
__fastcall TFormMessages::TFormMessages(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
