//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Dictionary.h"
#include "ML_DataModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormDictionary *FormDictionary;
//---------------------------------------------------------------------------
__fastcall TFormDictionary::TFormDictionary(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormDictionary::AShowAllMessagesExecute(TObject *Sender)
{
	Q_Dictionary->Close();
	Q_Dictionary->SQL->Clear();
    Q_Dictionary->SQL->Add("SELECT * FROM UserDictionary WHERE (LANGUAGE_ID_I = :LanguageID)");
    Q_Dictionary->Parameters->ParamByName("LanguageID")->Value = ComboBoxLanguage->ItemIndex;
    Q_Dictionary->Open();
}
//---------------------------------------------------------------------------
void __fastcall TFormDictionary::AShowNewMessagesExecute(TObject *Sender)
{
	Q_Dictionary->Close();
	Q_Dictionary->SQL->Clear();
    Q_Dictionary->SQL->Add("SELECT * FROM UserDictionary WHERE ((LANGUAGE_ID_I = :LanguageID) AND (WORD_IS_NEW_B = TRUE))");
    Q_Dictionary->Parameters->ParamByName("LanguageID")->Value = ComboBoxLanguage->ItemIndex;
    Q_Dictionary->Open();
}
//---------------------------------------------------------------------------
void __fastcall TFormDictionary::Q_DictionaryAfterScroll(TDataSet *DataSet)
{
	PanelMessage->Caption = Q_Dictionary->FieldByName("WORD_VALUE_TX")->AsString;	
}
//---------------------------------------------------------------------------
void __fastcall TFormDictionary::FormCreate(TObject *Sender)
{
	ComboBoxLanguage->ItemIndex = 0;
    AShowAllMessagesExecute(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TFormDictionary::ComboBoxLanguageChange(TObject *Sender)
{
    AShowAllMessagesExecute(NULL);	
}
//---------------------------------------------------------------------------
void __fastcall TFormDictionary::Q_DictionaryBeforePost(TDataSet *DataSet)
{
	Q_Dictionary->FieldByName("WORD_IS_NEW_B")->AsBoolean = false; 	
}
//---------------------------------------------------------------------------
void __fastcall TFormDictionary::ADeleteExecute(TObject *Sender)
{
	if(MessageDlg("Are you sure you want to delete this record?",mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)!=mrYes)	return;
/*
    if(Q_Dictionary->Locate())
    {
		Q_Dictionary->Delete();
    }
*/
}
//---------------------------------------------------------------------------

