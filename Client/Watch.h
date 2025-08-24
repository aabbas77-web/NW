//---------------------------------------------------------------------------

#ifndef WatchH
#define WatchH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TFormWatch : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TBitBtn *BitBtn2;
	TGroupBox *GroupBox1;
	TSplitter *Splitter1;
	TGroupBox *GroupBox2;
	TRichEdit *RichEdit;
	TBitBtn *BitBtn3;
	TBitBtn *BitBtn4;
	TSaveDialog *SaveDialog1;
	TSavePictureDialog *SavePictureDialog1;
	TFormTranslation *FormTranslation1;
	TScrollBox *ScrollBox1;
	TImage *Image;
	void __fastcall BitBtn3Click(TObject *Sender);
	void __fastcall BitBtn4Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall TFormWatch(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormWatch *FormWatch;
//---------------------------------------------------------------------------
#endif
