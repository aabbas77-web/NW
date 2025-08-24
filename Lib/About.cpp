//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "About.h"
//--------------------------------------------------------------------- 
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormAbout *FormAbout;
//--------------------------------------------------------------------- 
__fastcall TFormAbout::TFormAbout(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------

void __fastcall TFormAbout::FormClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

