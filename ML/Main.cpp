//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "ML.h"
#include "AddNewPhrase.h"
#include "ML_DataModule.h"
#include "Dictionary.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::RichEditSourceMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
	if(!CheckBoxRealTime->Checked) return;

	MousePos.x = X;
	MousePos.y = Y;
    int nPos = SendMessage(RichEditSource->Handle,EM_CHARFROMPOS,0,(LPARAM)(&MousePos));
    AnsiString strText = RichEditSource->Text.Trim();
    int nLength = strText.Length();

    if((nPos < 0) || (nPos > nLength-1))	return;

    int nSelStart,nSelLength;
    AnsiString strSelText="";
    char c;

    nSelStart = 0;

    for(int i=nPos+1;i>=1;i--)
    {
    	c = strText[i];
    	if(ml_IsSeperator(c))
        {
    		nSelStart = i;
            break;
        }
    	strSelText = AnsiString(c) + strSelText;
    }
    for(int i=nPos+2;i<=nLength;i++)
    {
    	c = strText[i];
    	if(ml_IsSeperator(c))
        {
            break;
        }
    	strSelText += AnsiString(c);
    }

    strSelText = strSelText.Trim();
    nSelLength = strSelText.Length();
    if(nSelLength < 1)	return;

    if(strPrevSelText == strSelText)	return;
    strPrevSelText = strSelText;

    AnsiString strTranslation;
    ml_TranslateSection(strSelText,strTranslation);
    if(strTranslation == "")	strTranslation = strSelText;

    RichEditSource->SelStart = nSelStart;
    RichEditSource->SelLength = nSelLength;
    RichEditSource->Hint = strTranslation;
    RichEditSource->ShowHint = true;
    Application->HintPause = 0;
//    Application->HintHidePause = 60000;
//    Application->ActivateHint(RichEditSource->ClientToScreen(Point(X,Y)));
    Application->ActivateHint(Mouse->CursorPos);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormCreate(TObject *Sender)
{
    ComboBoxSource->ItemIndex = 0;
    ComboBoxDest->ItemIndex = 0;
    g_pProgressBar = ProgressBar1;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::CheckBoxRealTimeClick(TObject *Sender)
{
	RichEditSource->SetFocus();
	if(CheckBoxRealTime->Checked)
    {
		RichEditSource->Cursor = crHandPoint;
    	RichEditSource->ShowHint = true;
    }
    else
    {
		RichEditSource->Cursor = crDefault;
    	RichEditSource->ShowHint = false;
    }
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::RichEditSourceMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
	AAddToDictionary->Enabled = false;
    ATranslate->Enabled = false;
	if(Button == mbRight)
    {
    	if(RichEditSource->Text.Length() > 0)
        {
		    ATranslate->Enabled = true;
        }
    	if(RichEditSource->SelText.Length() > 0)
        {
	    	TPoint P = RichEditSource->ClientToScreen(Point(X,Y));
			AAddToDictionary->Enabled = true;
			PopupMenu->Popup(P.x,P.y);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AAddToDictionaryExecute(TObject *Sender)
{
    AnsiString strSourcePhrase = RichEditSource->SelText;
    strSourcePhrase = strSourcePhrase.Trim();
	FormAddNewPhrase->PanelPhrase->Caption = strSourcePhrase;
    for(int i=1;i<=strSourcePhrase.Length();i++)
    {
     	if(ml_IsPunctuation(strSourcePhrase[i]))
        {
        	MessageDlg("Invalid Selection, may be has a punctuation...!",mtError,TMsgDlgButtons()<<mbOK,0);
            return;
        }
    }
	if(FormAddNewPhrase->ShowModal() != mrOk)	return;
    if(FormAddNewPhrase->EditTranslation->Text == "")	return;

    AnsiString strDestPhrase = FormAddNewPhrase->EditTranslation->Text;
    int nSourceLanguage = 0;
    int nDestLanguage = 1;
	Variant locvalues[2];
    AnsiString strCode;

    // Translate if found.
    locvalues[0] = Variant(strSourcePhrase);
    locvalues[1] = Variant(nSourceLanguage);
    if(DM_ML->TableUserDictionary->Locate("WORD_VALUE_TX;LANGUAGE_ID_I",VarArrayOf(locvalues, 1),TLocateOptions()))
    {
    	strCode = DM_ML->TableUserDictionary->FieldByName("WORD_CODE_TX")->Value;

    	locvalues[0] = Variant(strCode);
	    locvalues[1] = Variant(nDestLanguage);
	    if(DM_ML->TableUserDictionary->Locate("WORD_CODE_TX;LANGUAGE_ID_I",VarArrayOf(locvalues, 1),TLocateOptions()))
	    {
        	DM_ML->TableUserDictionary->Edit();
	    	DM_ML->TableUserDictionary->FieldByName("WORD_VALUE_TX")->Value = FormAddNewPhrase->EditTranslation->Text;
        	DM_ML->TableUserDictionary->Post();
		}
        else
        {
			DM_ML->TableUserDictionary->Append();
    		DM_ML->TableUserDictionary->FieldByName("WORD_CODE_TX")->Value = strCode;
	    	DM_ML->TableUserDictionary->FieldByName("WORD_VALUE_TX")->Value = FormAddNewPhrase->EditTranslation->Text;
            DM_ML->TableUserDictionary->Post();
        }
	}
    else
    {
	    int nCode;
        nCode = ml_GetCurrStartCode() + 1;;
        strCode = FormatFloat("0",nCode);

    	DM_ML->TableUserDictionary->Append();
	    DM_ML->TableUserDictionary->FieldByName("LANGUAGE_ID_I")->Value = g_nSourceLanguage;
        DM_ML->TableUserDictionary->FieldByName("WORD_CODE_TX")->Value = strCode;
        DM_ML->TableUserDictionary->FieldByName("WORD_VALUE_TX")->Value = strSourcePhrase;
        DM_ML->TableUserDictionary->Post();

	    DM_ML->TableUserDictionary->Append();
	    DM_ML->TableUserDictionary->FieldByName("LANGUAGE_ID_I")->Value = g_nDestLanguage;
        DM_ML->TableUserDictionary->FieldByName("WORD_CODE_TX")->Value = strCode;
        DM_ML->TableUserDictionary->FieldByName("WORD_VALUE_TX")->Value = strDestPhrase;
	    DM_ML->TableUserDictionary->Post();
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::RichEditSourceMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(RichEditSource->SelText.Length() > 0)
    {
    	AAddToDictionary->Enabled = true;
    }
    if(RichEditSource->Text.Length() > 0)
    {
    	ATranslate->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ATranslateExecute(TObject *Sender)
{
    AnsiString strBeforeTranslation;
	if(RichEditSource->SelText.Length() > 0)
    {
    	strBeforeTranslation=RichEditSource->SelText;
    }
    else
    {
    	strBeforeTranslation=RichEditSource->Text;
    }
    strBeforeTranslation = strBeforeTranslation.Trim();
    AnsiString strAfterTranslation="";

    RichEditSource->BiDiMode=(g_bSourceIsLeftToRight?bdLeftToRight:bdRightToLeft);
    RichEditDest->BiDiMode=(g_bDestIsLeftToRight?bdLeftToRight:bdRightToLeft);

    Application->ProcessMessages();

	ml_TranslateParagraph(strBeforeTranslation.LowerCase(),strAfterTranslation);
    RichEditDest->Text=strAfterTranslation;

//    Caption = FormatFloat("",g_nLocateCount);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADictionaryExecute(TObject *Sender)
{
	FormDictionary->ShowModal();	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::RichEditSourceChange(TObject *Sender)
{
    ATranslate->Enabled = false;
    if(RichEditSource->Text.Length() > 0)
    {
    	ATranslate->Enabled = true;
    }
}
//---------------------------------------------------------------------------

