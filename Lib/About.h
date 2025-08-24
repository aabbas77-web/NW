//----------------------------------------------------------------------------
#ifndef AboutH
#define AboutH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
#include <jpeg.hpp>
#include "FormTranslation.h"
//----------------------------------------------------------------------------
class TFormAbout : public TForm
{
__published:
	TPanel *Panel1;
        TImage *ProgramIcon;
	TFormTranslation *FormTranslation1;
	void __fastcall FormClick(TObject *Sender);
private:
public:
	virtual __fastcall TFormAbout(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TFormAbout *FormAbout;
//----------------------------------------------------------------------------
#endif    
