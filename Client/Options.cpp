//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Options.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormOptions *FormOptions;
//---------------------------------------------------------------------------
__fastcall TFormOptions::TFormOptions(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
