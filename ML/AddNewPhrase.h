//---------------------------------------------------------------------------

#ifndef AddNewPhraseH
#define AddNewPhraseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TFormAddNewPhrase : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TLabel *Label1;
	TEdit *EditTranslation;
	TPanel *PanelPhrase;
	TFormTranslation *FormTranslation1;
	void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormAddNewPhrase(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAddNewPhrase *FormAddNewPhrase;
//---------------------------------------------------------------------------
#endif
