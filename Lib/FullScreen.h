//---------------------------------------------------------------------------

#ifndef FullScreenH
#define FullScreenH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "FormTranslation.h"
#include <AppEvnts.hpp>
//---------------------------------------------------------------------------
class TFormFullScreen : public TForm
{
__published:	// IDE-managed Components
	TFormTranslation *FormTranslation1;
	TApplicationEvents *ApplicationEvents1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormDeactivate(TObject *Sender);
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
	void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
//	virtual void __fastcall WndProc(Messages::TMessage &Message);
public:		// User declarations
	__fastcall TFormFullScreen(TComponent* Owner);
    int nPrevX,nPrevY;
    int nRes;
    int X,Y;
    WORD wShift;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormFullScreen *FormFullScreen;
//---------------------------------------------------------------------------
#endif
