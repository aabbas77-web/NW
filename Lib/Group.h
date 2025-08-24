//---------------------------------------------------------------------------

#ifndef GroupH
#define GroupH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <DBCtrls.hpp>
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TFormGroup : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TLabel *Label;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TDBLookupComboBox *DBLookupComboBox1;
	TFormTranslation *FormTranslation1;
private:	// User declarations
public:		// User declarations
	__fastcall TFormGroup(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormGroup *FormGroup;
//---------------------------------------------------------------------------
#endif
