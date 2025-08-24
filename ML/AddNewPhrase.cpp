//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AddNewPhrase.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormAddNewPhrase *FormAddNewPhrase;
//---------------------------------------------------------------------------
__fastcall TFormAddNewPhrase::TFormAddNewPhrase(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormAddNewPhrase::FormActivate(TObject *Sender)
{
	ActivateKeyboardLayout((HKL)HKL_NEXT,KLF_REORDER);
    EditTranslation->SetFocus();
}
//---------------------------------------------------------------------------

