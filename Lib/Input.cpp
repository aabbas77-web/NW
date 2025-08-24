//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Input.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormInput *FormInput;
//---------------------------------------------------------------------------
__fastcall TFormInput::TFormInput(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormInput::FormCreate(TObject *Sender)
{
	ComboBoxLanguage->ItemIndex = 0;	
}
//---------------------------------------------------------------------------

