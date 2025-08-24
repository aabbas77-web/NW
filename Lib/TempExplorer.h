//---------------------------------------------------------------------------

#ifndef TempExplorerH
#define TempExplorerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ShellCtrls.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TFormTempExplorer : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TPanel *Panel1;
	TPanel *Panel3;
	TShellListView *ShellListView1;
	TShellTreeView *ShellTreeView1;
	TFormTranslation *FormTranslation1;
private:	// User declarations
public:		// User declarations
	__fastcall TFormTempExplorer(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormTempExplorer *FormTempExplorer;
//---------------------------------------------------------------------------
#endif
