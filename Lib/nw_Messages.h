//---------------------------------------------------------------------------

#ifndef nw_MessagesH
#define nw_MessagesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include "FormTranslation.h"
//---------------------------------------------------------------------------
const AnsiString c_strWithoutGroup=
	"Without group";
const AnsiString c_strClients=
	"Clients";
//---------------------------------------------------------------------------
class TFormMessages : public TForm
{
__published:	// IDE-managed Components
	TValueListEditor *ValueListEditor;
	TFormTranslation *FormTranslation1;
private:	// User declarations
public:		// User declarations
	__fastcall TFormMessages(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMessages *FormMessages;
//---------------------------------------------------------------------------
#endif
