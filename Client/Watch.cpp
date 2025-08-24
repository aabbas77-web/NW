//---------------------------------------------------------------------------

#include <vcl.h>
#include <JPEG.hpp>
#pragma hdrstop

#include "Watch.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormWatch *FormWatch;
//---------------------------------------------------------------------------
__fastcall TFormWatch::TFormWatch(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormWatch::BitBtn3Click(TObject *Sender)
{
	if(SaveDialog1->Execute())
    {
    	RichEdit->Lines->SaveToFile(SaveDialog1->FileName);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormWatch::BitBtn4Click(TObject *Sender)
{
	if(SavePictureDialog1->Execute())
    {
    	if(SavePictureDialog1->FileName.UpperCase().Pos(".BMP") > 0)
	    	Image->Picture->Bitmap->SaveToFile(SavePictureDialog1->FileName);
        else
    	if(SavePictureDialog1->FileName.UpperCase().Pos(".JPG") > 0)
        {
        	TJPEGImage *pJPEG = new TJPEGImage();
            pJPEG->Assign(Image->Picture->Bitmap);
	    	pJPEG->SaveToFile(SavePictureDialog1->FileName);
            if(pJPEG)	delete pJPEG;
            pJPEG = NULL;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormWatch::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	if(Key == VK_ESCAPE)
    {
     	Close();
    }
}
//---------------------------------------------------------------------------



