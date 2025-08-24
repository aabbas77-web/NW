//---------------------------------------------------------------------------
#ifndef FormTranslationH
#define FormTranslationH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
//---------------------------------------------------------------------------
#include <ComCtrls.hpp>
#include <DBCtrls.hpp>
#include <Buttons.hpp>
#include <MidItems.hpp>
#include <CheckLst.hpp>
#include <ValEdit.hpp>
#include <DBGrids.hpp>
#include <QRCtrls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TFormTranslation : public TComponent
{
private:
	int m_nOriginalLanguageID;
	int m_nLanguageID;
    bool m_bGenerate;
protected:
public:
	__fastcall TFormTranslation(TComponent* Owner);
	__fastcall ~TFormTranslation();
	void __fastcall GenerateTranslations(TComponent *pOwner,int nLangID);
	void __fastcall GenerateTranslations(TComponent *pOwner);
	void __fastcall FlipWindow(HWND hWnd);
	void __fastcall Translate(TComponent *pOwner);
	void __fastcall LoadSettings();
	void __fastcall SaveSettings();
	void __fastcall FlipAnchor(TControl *pControl);
__published:
};
//---------------------------------------------------------------------------
#endif
 