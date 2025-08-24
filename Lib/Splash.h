//---------------------------------------------------------------------------

#ifndef SplashH
#define SplashH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TFormSplash : public TForm
{
__published:	// IDE-managed Components
	TFormTranslation *FormTranslation1;
	TPanel *Panel1;
	TImage *Image;
private:	// User declarations
public:		// User declarations
        __fastcall TFormSplash(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSplash *FormSplash;
//---------------------------------------------------------------------------
#endif
