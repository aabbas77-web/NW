//---------------------------------------------------------------------------

#ifndef OptionsH
#define OptionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "CSPIN.h"
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TFormOptions : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TPanel *Panel2;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TComboBox *ComboBox1;
	TLabel *Label2;
	TCSpinEdit *CSpinEdit1;
	TCheckBox *CheckBox1;
	TFormTranslation *FormTranslation1;
private:	// User declarations
public:		// User declarations
	__fastcall TFormOptions(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormOptions *FormOptions;
//---------------------------------------------------------------------------
#endif
