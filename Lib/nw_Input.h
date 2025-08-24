//---------------------------------------------------------------------------

#ifndef nw_InputH
#define nw_InputH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TFormnw_Input : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TLabel *Label;
	TEdit *Edit;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TFormTranslation *FormTranslation1;
private:	// User declarations
public:		// User declarations
	__fastcall TFormnw_Input(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormnw_Input *Formnw_Input;
//---------------------------------------------------------------------------
#endif
