//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CopyDialog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormCopyDialog *FormCopyDialog;
//---------------------------------------------------------------------------
__fastcall TFormCopyDialog::TFormCopyDialog(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormCopyDialog::BitBtn1Click(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------
void __fastcall TFormCopyDialog::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    switch(Key)
    {
        case VK_ESCAPE:
        {
			Close();	
            break;
        }
    }
}
//---------------------------------------------------------------------------

