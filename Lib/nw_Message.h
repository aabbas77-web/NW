//---------------------------------------------------------------------------

#ifndef nw_MessageH
#define nw_MessageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include "FormTranslation.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormMessage : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TFormTranslation *FormTranslation1;
	TRichEdit *RichEdit;
	TPanel *Panel2;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
private:	// User declarations
public:		// User declarations
	__fastcall TFormMessage(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMessage *FormMessage;
//---------------------------------------------------------------------------
#endif
