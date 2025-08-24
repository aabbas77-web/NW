//---------------------------------------------------------------------------

#ifndef InputH
#define InputH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TFormInput : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TLabel *LabelUserName;
	TEdit *EditUserName;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TLabel *LabelServerName;
	TEdit *EditServerName;
	TLabel *Label1;
	TComboBox *ComboBoxLanguage;
	TFormTranslation *FormTranslation1;
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormInput(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormInput *FormInput;
//---------------------------------------------------------------------------
#endif
