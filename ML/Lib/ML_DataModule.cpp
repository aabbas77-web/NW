//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ML_DataModule.h"
#include "ML.h"
#include "Splash.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TDM_ML *DM_ML;
//---------------------------------------------------------------------------
__fastcall TDM_ML::TDM_ML(TComponent* Owner)
	: TDataModule(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDM_ML::DataModuleCreate(TObject *Sender)
{
	AnsiString strAppPath=ExtractFilePath(Application->ExeName);

    ADOConnection->Connected = false;
    ADOConnection->ConnectionString =
    "Provider=Microsoft.Jet.OLEDB.4.0;Data Source="+strAppPath+"UserDictionary.mdb;Persist Security Info=False";
    ADOConnection->Connected = true;

//	TableUserDictionary->Active=false;
//    TableUserDictionary->ConnectionString=
//    "Provider=Microsoft.Jet.OLEDB.4.0;Data Source="+strAppPath+"UserDictionary.mdb;Persist Security Info=False";
	TableUserDictionary->Active=true;

/*
    AnsiString strCode;
	TableUserDictionary->First();
    while(!TableUserDictionary->Eof)
    {
    	TableUserDictionary->Edit();
		strCode = TableUserDictionary->FieldByName("WORD_CODE_TX")->Value;
        strCode.Delete(strCode.Length(),1);
        strCode.Delete(1,1);
        TableUserDictionary->FieldByName("WORD_CODE_TX")->Value = strCode;
        TableUserDictionary->Post();

     	TableUserDictionary->Next();
    }
*/

	FormSplash = new TFormSplash(Application);
    FormSplash->Show();
    FormSplash->Update();

    AnsiString strTranslation;
    ml_Initialize();
    g_nSourceLanguage = 0;
    g_nDestLanguage = 1;
    g_pProgressBar = NULL;
    ml_TranslateSection("Start",strTranslation);

    if(FormSplash)
    {
    	FormSplash->Close();
    	delete FormSplash;
	    FormSplash = NULL;
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM_ML::DataModuleDestroy(TObject *Sender)
{
    ml_Finalize();
}
//---------------------------------------------------------------------------

