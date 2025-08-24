//---------------------------------------------------------------------------

#ifndef CopyDialogH
#define CopyDialogH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TFormCopyDialog : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *BitBtn1;
	TPanel *Panel1;
	TAnimate *Animate;
	TPanel *Panel2;
	TLabel *LabelFileName;
	TPanel *Panel3;
	TLabel *LabelResult;
	TFormTranslation *FormTranslation1;
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall TFormCopyDialog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormCopyDialog *FormCopyDialog;
//---------------------------------------------------------------------------
#endif
