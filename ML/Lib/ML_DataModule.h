//---------------------------------------------------------------------------

#ifndef ML_DataModuleH
#define ML_DataModuleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
#include <ADODB.hpp>
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TDM_ML : public TDataModule
{
__published:	// IDE-managed Components
	TADOTable *TableUserDictionary;
	TADOQuery *ADOQueryMaxCode;
	TADOConnection *ADOConnection;
	TFormTranslation *FormTranslation1;
	void __fastcall DataModuleCreate(TObject *Sender);
	void __fastcall DataModuleDestroy(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TDM_ML(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDM_ML *DM_ML;
//---------------------------------------------------------------------------
#endif
