//---------------------------------------------------------------------------

#ifndef DictionaryH
#define DictionaryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ActnList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TFormDictionary : public TForm
{
__published:	// IDE-managed Components
	TToolBar *ToolBar1;
	TActionList *ActionList1;
	TDBGrid *DBGrid1;
	TAction *AShowAllMessages;
	TAction *AShowNewMessages;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TADOQuery *Q_Dictionary;
	TDataSource *DS_Dictionary;
	TIntegerField *Q_DictionaryWORD_CODE_TX;
	TIntegerField *Q_DictionaryLANGUAGE_ID_I;
	TWideStringField *Q_DictionaryWORD_VALUE_TX;
	TFloatField *Q_DictionaryWORD_FREQ_N;
	TFloatField *Q_DictionaryWORD_LENG_N;
	TFloatField *Q_DictionaryWORD_FREQ_PROD_N;
	TFloatField *Q_DictionaryWORD_FREQ_DIV_N;
	TFloatField *Q_DictionaryWORD_PFREQ_N;
	TFloatField *Q_DictionaryWORD_PFREQ_PROD_N;
	TFloatField *Q_DictionaryWORD_PFREQ_DIV_N;
	TFloatField *Q_DictionaryWORD_RATIO_N;
	TComboBox *ComboBoxLanguage;
	TPanel *PanelMessage;
	TBooleanField *Q_DictionaryWORD_IS_NEW_B;
	TFormTranslation *FormTranslation1;
	TToolButton *ToolButton3;
	TAction *ADelete;
	void __fastcall AShowAllMessagesExecute(TObject *Sender);
	void __fastcall AShowNewMessagesExecute(TObject *Sender);
	void __fastcall Q_DictionaryAfterScroll(TDataSet *DataSet);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ComboBoxLanguageChange(TObject *Sender);
	void __fastcall Q_DictionaryBeforePost(TDataSet *DataSet);
	void __fastcall ADeleteExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormDictionary(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDictionary *FormDictionary;
//---------------------------------------------------------------------------
#endif
