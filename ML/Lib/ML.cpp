// strpbrk
//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include <inifiles.hpp>
#include <StrUtils.hpp>
#include "ML_DataModule.h"
#include "ML.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
bool 		g_bInitialized=false;
int 		g_nSourceLanguage=0;
int 		g_nDestLanguage=1;
int 		g_nStartCode=0;
int 		g_nLanguagesCount=1;
TStringList 	*g_pList=NULL;
TStringList 	*g_pRecordList=NULL;
ml_Paragraph g_Paragraph;
ml_Paragraph g_PhraseWords;
ml_Paragraph g_PhraseSegments;
ml_Paragraph g_CollectedSegments;
int 		g_nSeperatorLength=3;
Byte		g_byCollectingType=ctLeft;
bool		g_bAddBreakPoint=true;
bool		g_bApplyConstraints=true;
int			g_nMinWordsCount=2;
int			g_nMaxWordsCount=10;
bool 		g_bJustTranslation=false;
bool 		g_bSourceIsLeftToRight=true;
bool 		g_bDestIsLeftToRight=false;
int			g_nLocateCount=0;
bool		g_bUpdateFreq = false;
TProgressBar *g_pProgressBar = NULL;
//---------------------------------------------------------------------------
void ml_Initialize()
{
    g_pList=new TStringList();
    g_pRecordList=new TStringList();
    g_bInitialized=true;

    TIniFile *pIniFile=new TIniFile(ChangeFileExt(Application->ExeName,".ini"));

    g_nLanguagesCount=pIniFile->ReadInteger("UserDictionary","LanguagesCount",1);
    g_nSeperatorLength=pIniFile->ReadInteger("UserDictionary","SeperatorLength",3);
    g_byCollectingType=(Byte)pIniFile->ReadInteger("UserDictionary","CollectingType",0);
    g_bAddBreakPoint=pIniFile->ReadBool("UserDictionary","AddBreakPoint",true);
    g_bApplyConstraints=pIniFile->ReadBool("UserDictionary","ApplyConstraints",true);
	g_nMinWordsCount=pIniFile->ReadInteger("UserDictionary","MinWordsCount",2);
	g_nMaxWordsCount=pIniFile->ReadInteger("UserDictionary","MaxWordsCount",4);
    g_bJustTranslation=pIniFile->ReadBool("UserDictionary","JustTranslation",false);
    g_bSourceIsLeftToRight=pIniFile->ReadBool("UserDictionary","SourceIsLeftToRight",true);
    g_bDestIsLeftToRight=pIniFile->ReadBool("UserDictionary","DestIsLeftToRight",false);
    g_bUpdateFreq=pIniFile->ReadBool("UserDictionary","UpdateFreq",false);
    g_nLocateCount = 0;

    if(pIniFile)	delete pIniFile;
    pIniFile=NULL;
}
//---------------------------------------------------------------------------
void ml_Finalize()
{
    if(g_pList)	delete g_pList;
    g_pList=NULL;
    if(g_pRecordList)	delete g_pRecordList;
    g_pRecordList=NULL;

    TIniFile *pIniFile=new TIniFile(ChangeFileExt(Application->ExeName,".ini"));

    pIniFile->WriteInteger("UserDictionary","LanguagesCount",g_nLanguagesCount);
    pIniFile->WriteInteger("UserDictionary","SeperatorLength",g_nSeperatorLength);
    pIniFile->WriteInteger("UserDictionary","CollectingType",g_byCollectingType);
    pIniFile->WriteBool("UserDictionary","AddBreakPoint",g_bAddBreakPoint);
    pIniFile->WriteBool("UserDictionary","ApplyConstraints",g_bApplyConstraints);
	pIniFile->WriteInteger("UserDictionary","MinWordsCount",g_nMinWordsCount);
	pIniFile->WriteInteger("UserDictionary","MaxWordsCount",g_nMaxWordsCount);
    pIniFile->WriteBool("UserDictionary","JustTranslation",g_bJustTranslation);
    pIniFile->WriteBool("UserDictionary","SourceIsLeftToRight",g_bSourceIsLeftToRight);
    pIniFile->WriteBool("UserDictionary","DestIsLeftToRight",g_bDestIsLeftToRight);
    pIniFile->WriteBool("UserDictionary","UpdateFreq",g_bUpdateFreq);

    if(pIniFile)	delete pIniFile;
    pIniFile=NULL;
}
//---------------------------------------------------------------------------
int ml_GetCurrStartCode()
{
	int nCode;
    DM_ML->ADOQueryMaxCode->Close();
    DM_ML->ADOQueryMaxCode->Open();
    if(DM_ML->ADOQueryMaxCode->Fields->Count > 0)
    {
		if(DM_ML->ADOQueryMaxCode->Fields->Fields[0]->AsString != "")
			nCode = DM_ML->ADOQueryMaxCode->Fields->Fields[0]->Value;
	    else
        	nCode = 0;
    }
    else
    {
		nCode = 0;
    }
	return nCode;
}
//---------------------------------------------------------------------------
void ml_Clear()
{
    TIniFile *pIniFile=new TIniFile(ChangeFileExt(Application->ExeName,".ini"));
	pIniFile->WriteInteger("UserDictionary","StartCode",1);
    if(pIniFile)	delete pIniFile;
    pIniFile=NULL;
}
//---------------------------------------------------------------------------
bool ml_IsPunct(char c)
{
	bool bResult = false;
    switch(c)
    {
		case '.':
		case ',':
		case ':':
		case '{':
		case '}':
		case '"':
		case '?':
		case '!':
		case '@':
		case '#':
		case '$':
		case '%':
		case '^':
		case '&':
		case '*':
		case '(':
		case ')':
//		case '-':
		case '+':
		case '=':
		case '|':
//		case '\\':
		case '[':
		case ']':
		case ';':
		case '<':
		case '>':
        {
        	bResult = true;
         	break;
        }
    }
	return bResult;
}
//---------------------------------------------------------------------------
bool ml_IsSeperator(char c)
{
	return (ml_IsPunct(c) || isdigit(c) || iscntrl(c) || isspace(c));
}
//---------------------------------------------------------------------------
bool ml_IsPunctuation(char c)
{
	return (ml_IsPunct(c) || isdigit(c) || iscntrl(c));
}
//---------------------------------------------------------------------------
AnsiString ml_RemoveRepeatedSpaces(AnsiString strPhrase)
{
	AnsiString strResult = "";
    char c;
    char PrevChar = 'a';
	for(int i=1;i<=strPhrase.Length();i++)
    {
    	c = strPhrase[i];
		if(isspace(PrevChar) && (c == PrevChar))
        {

        }
        else
        {
			strResult += c;
        }
        PrevChar = c;
    }    
	return strResult;
}
//---------------------------------------------------------------------------
bool ml_IsSingleWord(AnsiString strPhrase)
{
	strPhrase=strPhrase.Trim();
	for(int i=1;i<=strPhrase.Length();i++)
    {
     	if(isspace(strPhrase[i]))
        {
         	return false;
        }
    }
    return true;
}
//---------------------------------------------------------------------------
int ml_CalculateWordsCount(AnsiString strPhrase)
{
	strPhrase=strPhrase.Trim();
    int nWordsCount=0;
    if(strPhrase.Length()<=0)	return nWordsCount;
	for(int i=1;i<=strPhrase.Length();i++)
    {
     	if(isspace(strPhrase[i]))
        {
         	nWordsCount++;
        }
    }
    nWordsCount++;
    return nWordsCount;
}
//---------------------------------------------------------------------------
void ml_DecodePhrase(AnsiString strPhrase,AnsiString &strLeft,AnsiString &strRight)
{
	char c;
    bool bIsSingle=true;
    strLeft=strPhrase.Trim();
	strRight="";
    if(strPhrase.Length()<=0)	return;
	for(int i=strPhrase.Length();i>=1;i--)
    {
    	c=strPhrase[i];
     	if(isspace(c))
        {
	        strLeft.Delete(strLeft.Length(),1);
            bIsSingle=false;
        	break;
        }
        strRight=AnsiString(c)+strRight;
        strLeft.Delete(strLeft.Length(),1);
    }
    if(bIsSingle)
    {
	    strLeft=strPhrase.Trim();
    	strRight="";
    }
    else
    {
	    strLeft=strLeft.Trim();
    	strRight=strRight.Trim();
    }
}
//---------------------------------------------------------------------------
bool ml_TranslateSection(AnsiString strSection,AnsiString &strTranslation)
{
	strSection=strSection.Trim();
	strTranslation="";
    if(strSection.Length()<=0)	return false;
    if(!g_bInitialized)
    {
     	MessageDlg("Multi-Language library not initialized...",mtError,TMsgDlgButtons()<<mbOK,0);
    	Application->Terminate();
    }

    AnsiString strCode;
	TLocateOptions LocateOptions;
	LocateOptions.Clear();
	Variant locvalues[2];
    bool bTranslated=false;

    // Translate if found.
    locvalues[0] = Variant(strSection);
    locvalues[1] = Variant(g_nSourceLanguage);
    if(DM_ML->TableUserDictionary->Locate("WORD_VALUE_TX;LANGUAGE_ID_I",VarArrayOf(locvalues, 1),LocateOptions))
    {
    	g_nLocateCount++;
    	if(g_bUpdateFreq)
        {
	        DM_ML->TableUserDictionary->Edit();
    	    DM_ML->TableUserDictionary->FieldByName("WORD_FREQ_N")->AsInteger++;

	        float pf=DM_ML->TableUserDictionary->FieldByName("WORD_PFREQ_N")->AsInteger;
            if(pf <= 0)	pf = 1;
	        float len=DM_ML->TableUserDictionary->FieldByName("WORD_LENG_N")->AsInteger;
            if(len <= 0)	len = 1;
	        float f=DM_ML->TableUserDictionary->FieldByName("WORD_FREQ_N")->AsInteger;
	        DM_ML->TableUserDictionary->FieldByName("WORD_FREQ_PROD_N")->Value=f*len;
	        DM_ML->TableUserDictionary->FieldByName("WORD_FREQ_DIV_N")->Value=f/len;
            DM_ML->TableUserDictionary->FieldByName("WORD_RATIO_N")->Value=f/pf;

	        DM_ML->TableUserDictionary->Post();
        }

		if(g_nLanguagesCount>1)// Translate
        {
	    	strCode=DM_ML->TableUserDictionary->FieldByName("WORD_CODE_TX")->Value;

	        locvalues[0] = Variant(strCode);
	        locvalues[1] = Variant(g_nDestLanguage);
	        if(DM_ML->TableUserDictionary->Locate("WORD_CODE_TX;LANGUAGE_ID_I",VarArrayOf(locvalues, 1),LocateOptions))
	        {
    			g_nLocateCount++;
	        	strTranslation=DM_ML->TableUserDictionary->FieldByName("WORD_VALUE_TX")->Value;

	            bTranslated=true;
	        }
	        else
	        {
				FatalAppExit(0,"Invalid Dictionary...\nField not found.");
    	    }
        }
        else
		{
			bTranslated=true;
    	    strTranslation=strSection;
        }
    }
    return bTranslated;
}
//---------------------------------------------------------------------------
void ml_AddSectionToUserDictionary(AnsiString strSection)
{
	strSection=strSection.Trim();
    if(strSection.Length()<=0)	return;

    if(g_bApplyConstraints)
    {
	    int nWordsCount=ml_CalculateWordsCount(strSection);
	    if((nWordsCount<g_nMinWordsCount) || (nWordsCount>g_nMaxWordsCount))
	    {
			return;
	    }
    }
	strSection = StringReplace(strSection,"_"," ",TReplaceFlags()<<rfReplaceAll);
//	strSection=ReplaceBy(strSection,'_',' ');

    if(strSection.Length()>0)
    {
    	if(strSection.Length()<=g_nSeperatorLength)// Logical break point
        {
        	if(!g_bAddBreakPoint)
            {
            	return;
            }
        }
    }

    if(!g_bInitialized)
    {
     	MessageDlg("Multi-Language library not initialized...",mtError,TMsgDlgButtons()<<mbOK,0);
    	return;
    }

	TLocateOptions LocateOptions;
	LocateOptions.Clear();
	Variant locvalues[2];

    locvalues[0] = Variant(strSection);
    locvalues[1] = Variant(g_nSourceLanguage);

    if(DM_ML->TableUserDictionary->Locate("WORD_VALUE_TX;LANGUAGE_ID_I",VarArrayOf(locvalues, 1),LocateOptions))
  	{
    	g_nLocateCount++;
    	if(g_bUpdateFreq)
        {
    		DM_ML->TableUserDictionary->Edit();
        	DM_ML->TableUserDictionary->FieldByName("WORD_PFREQ_N")->AsInteger++;

	        float pf=DM_ML->TableUserDictionary->FieldByName("WORD_PFREQ_N")->AsInteger;
	        if(pf <= 0)	pf = 1;
	        float len=DM_ML->TableUserDictionary->FieldByName("WORD_LENG_N")->AsInteger;
	        if(len <= 0)	len = 1;
	        float f=DM_ML->TableUserDictionary->FieldByName("WORD_FREQ_N")->AsInteger;
	        DM_ML->TableUserDictionary->FieldByName("WORD_PFREQ_PROD_N")->Value=pf*len;
	        DM_ML->TableUserDictionary->FieldByName("WORD_PFREQ_DIV_N")->Value=pf/len;
	        DM_ML->TableUserDictionary->FieldByName("WORD_RATIO_N")->Value=f/pf;

    	    DM_ML->TableUserDictionary->Post();
        }
    }
    else
    {
		for(int j=0;j<g_nLanguagesCount;j++)
		{
			DM_ML->TableUserDictionary->Append();
		    DM_ML->TableUserDictionary->FieldByName("WORD_CODE_TX")->Value=FormatFloat("0",g_nStartCode);
		    DM_ML->TableUserDictionary->FieldByName("LANGUAGE_ID_I")->Value=j;
		    DM_ML->TableUserDictionary->FieldByName("WORD_VALUE_TX")->Value=strSection;
		    DM_ML->TableUserDictionary->FieldByName("WORD_IS_NEW_B")->Value=true;
	    	if(g_bUpdateFreq)
    	    {
			    DM_ML->TableUserDictionary->FieldByName("WORD_LENG_N")->Value=strSection.Length();
			    DM_ML->TableUserDictionary->FieldByName("WORD_FREQ_N")->Value=0;
			    DM_ML->TableUserDictionary->FieldByName("WORD_FREQ_PROD_N")->Value=0;
			    DM_ML->TableUserDictionary->FieldByName("WORD_FREQ_DIV_N")->Value=0;
		        DM_ML->TableUserDictionary->FieldByName("WORD_PFREQ_N")->Value=0;
			    DM_ML->TableUserDictionary->FieldByName("WORD_PFREQ_PROD_N")->Value=0;
			    DM_ML->TableUserDictionary->FieldByName("WORD_PFREQ_DIV_N")->Value=0;
			    DM_ML->TableUserDictionary->FieldByName("WORD_RATIO_N")->Value=0;
            }
		    DM_ML->TableUserDictionary->Post();
		}
	    g_nStartCode++;
    }
}
//---------------------------------------------------------------------------
int GetIndexOf(AnsiString strSubText,AnsiString strText)
{
//	return strText.Pos(strSubText);
	bool bFound;
    int nLength = strText.Length();
    int nSubLength = strSubText.Length();
	for(int i=1;i<=nLength;i++)
    {
    	bFound = true;
     	for(int j=1;j<=nSubLength;j++)
        {
         	if((i-1+j > nLength) || (strText[i-1+j] != strSubText[j]))
            {
    			bFound = false;
                break;
            }
        }
        if(bFound)
        {
        	if(((i == 1) || (strText[i-1] == ' ')) &&
               ((i-1+nSubLength == nLength) || (strText[i-1+nSubLength+1] == ' ')))
            {
	        	return i;
            }
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
AnsiString ml_TranslatePhrase0(AnsiString strPhrase)
{
	if(strPhrase == "")
    {
        return strPhrase;
    }
    AnsiString strDicPhrase;
    AnsiString strTempPhrase = strPhrase;
    AnsiString strTemp;
    AnsiString strLeft,strRight;
    int nCode;
    int nPos;
	Variant locvalues[2];
	TLocateOptions LocateOptions;
    AnsiString strTranslation;
    ml_TranslationRecs TranslationRecs;
    ml_TranslationRec TranslationRec;
    TBookmark Bookmark;

	strTranslation=strTempPhrase;
    DM_ML->TableUserDictionary->First();
    while(!DM_ML->TableUserDictionary->Eof)
    {
    	strDicPhrase = DM_ML->TableUserDictionary->FieldByName("WORD_VALUE_TX")->AsString;
        strDicPhrase = ml_RemoveRepeatedSpaces(strDicPhrase);
        if(strDicPhrase == "")
        {
	     	DM_ML->TableUserDictionary->Next();
        	continue;
        }
//    	if(UpperCase(strTempPhrase).Pos(UpperCase(strDicPhrase)) > 0)
//    	if(AnsiPos(UpperCase(strDicPhrase),UpperCase(strTempPhrase)) > 0)
		nPos = GetIndexOf(UpperCase(strDicPhrase),UpperCase(strTempPhrase));
//    	if(GetIndexOf(UpperCase(strDicPhrase),UpperCase(strTempPhrase)) > 0)
    	if(nPos > 0)
        {
        	nCode = DM_ML->TableUserDictionary->FieldByName("WORD_CODE_TX")->AsInteger;
	        locvalues[0] = Variant(nCode);
	        locvalues[1] = Variant(g_nDestLanguage);
            Bookmark = DM_ML->TableUserDictionary->GetBookmark();
	        if(DM_ML->TableUserDictionary->Locate("WORD_CODE_TX;LANGUAGE_ID_I",VarArrayOf(locvalues, 1),LocateOptions))
	        {
            	TranslationRec.strFound = strDicPhrase;
                TranslationRec.strTranslation = DM_ML->TableUserDictionary->FieldByName("WORD_VALUE_TX")->AsString;
            	TranslationRecs.push_back(TranslationRec);
	        }
            DM_ML->TableUserDictionary->GotoBookmark(Bookmark);
            DM_ML->TableUserDictionary->FreeBookmark(Bookmark);
        }

     	DM_ML->TableUserDictionary->Next();
    }

    int nMaxLength = -MaxInt;
    int nLength;
    TranslationRec.strFound = "";
    TranslationRec.strTranslation = "";
    for(UINT i=0;i<TranslationRecs.size();i++)
    {
    	nLength = TranslationRecs[i].strFound.Length();
     	if(nLength > nMaxLength)
        {
         	nMaxLength = nLength;
            TranslationRec = TranslationRecs[i];
        }
    }

    AnsiString strLeftTranslation = "";
    AnsiString strRightTranslation = "";
//    nPos = UpperCase(strTempPhrase).Pos(UpperCase(TranslationRec.strFound));
//    nPos = AnsiPos(UpperCase(TranslationRec.strFound),UpperCase(strTempPhrase));
    nPos = GetIndexOf(UpperCase(TranslationRec.strFound),UpperCase(strTempPhrase));
    if(nPos > 0)
    {
	    strLeft = strTempPhrase.SubString(1,nPos-1);
	    strRight = strTempPhrase.SubString(nPos+TranslationRec.strFound.Length()+1,strTempPhrase.Length());
        if(strLeft != "")	strLeftTranslation = ml_TranslatePhrase0(strLeft);
        if(strRight != "")	strRightTranslation = ml_TranslatePhrase0(strRight);
        strTranslation = strLeftTranslation+" "+TranslationRec.strTranslation.Trim()+" "+strRightTranslation;

//    	ml_AddPhraseToDictionary(strLeftTranslation);
//    	ml_AddPhraseToDictionary(strRightTranslation);
    }
    else
    {
    	ml_AddPhraseToDictionary(strTempPhrase);
    }

    return strTranslation.Trim();
}
//---------------------------------------------------------------------------
void ml_AddPhraseToDictionary(AnsiString strPhrase)
{
    if(g_bJustTranslation)	return;
	ml_ExtractPhraseWords(strPhrase.Trim());
    ml_ExtractPhraseSegments();
    ml_CollectSegments();
    ml_AddSegmentsToDictionary();
}
//---------------------------------------------------------------------------
/*
AnsiString ml_TranslatePhrase0(AnsiString strPhrase)
{
	if(strPhrase == "")
    {
        return strPhrase;
    }
    AnsiString strDicPhrase;
    AnsiString strTempPhrase = strPhrase;
    AnsiString strTemp;
    AnsiString strLeft,strRight;
    int nCode;
    int nPos;
	Variant locvalues[2];
	TLocateOptions LocateOptions;
    AnsiString strTranslation;

	strTranslation=strTempPhrase;
    DM_ML->TableUserDictionary->First();
    while(!DM_ML->TableUserDictionary->Eof)
    {
    	strDicPhrase = DM_ML->TableUserDictionary->FieldByName("WORD_VALUE_TX")->AsString;
        nPos = UpperCase(strTempPhrase).Pos(UpperCase(strDicPhrase));
    	if(nPos > 0)
        {
        	nCode = DM_ML->TableUserDictionary->FieldByName("WORD_CODE_TX")->Value;
            strTemp = strTempPhrase;
	        locvalues[0] = Variant(nCode);
	        locvalues[1] = Variant(g_nDestLanguage);
	        if(DM_ML->TableUserDictionary->Locate("WORD_CODE_TX;LANGUAGE_ID_I",VarArrayOf(locvalues, 1),LocateOptions))
	        {
	        	strTemp=DM_ML->TableUserDictionary->FieldByName("WORD_VALUE_TX")->Value;
	        }

            strLeft = strTempPhrase.SubString(1,nPos-1);
            strRight = strTempPhrase.SubString(nPos+strDicPhrase.Length()+1,strTempPhrase.Length());
        	strTranslation = ml_TranslatePhrase0(strLeft)+" "+strTemp+" "+ml_TranslatePhrase0(strRight);
         	break;
        }

     	DM_ML->TableUserDictionary->Next();
    }
    return strTranslation;
}
*/
//---------------------------------------------------------------------------
void ml_TranslatePhrase(AnsiString strPhrase,AnsiString &strTranslation)
{
	AnsiString strExtension="";
    char c;
	for(int i=strPhrase.Length();i>=1;i--)
    {
    	c=strPhrase[i];
        if(!isspace(c))	break;
        strExtension=AnsiString(c)+strExtension;
    }
	strPhrase=strPhrase.Trim();
	strTranslation="";
	if(strPhrase.Length()<=0)	return;
    if(!g_bInitialized)
    {
     	MessageDlg("Multi-Language library not initialized...",mtError,TMsgDlgButtons()<<mbOK,0);
    	return;
    }

 	strTranslation = ml_TranslatePhrase0(strPhrase);
    strTranslation += strExtension;
}
//---------------------------------------------------------------------------
/*
void ml_TranslatePhrase(AnsiString strPhrase,AnsiString &strTranslation)
{
	AnsiString strExtension="";
    char c;
	for(int i=strPhrase.Length();i>=1;i--)
    {
    	c=strPhrase[i];
        if(!isspace(c))	break;
        strExtension=AnsiString(c)+strExtension;
    }
	strPhrase=strPhrase.Trim();
	strTranslation="";
	if(strPhrase.Length()<=0)	return;
    if(!g_bInitialized)
    {
     	MessageDlg("Multi-Language library not initialized...",mtError,TMsgDlgButtons()<<mbOK,0);
    	return;
    }

    AnsiString strDicPhrase;
    AnsiString strTempPhrase = strPhrase;
    AnsiString strTemp;
    AnsiString strLeft,strRight;
    int nCode;
    int nPos;
	Variant locvalues[2];
	TLocateOptions LocateOptions;

	strTranslation=strTempPhrase;
    DM_ML->TableUserDictionary->First();
    while(!DM_ML->TableUserDictionary->Eof)
    {
    	strDicPhrase = DM_ML->TableUserDictionary->FieldByName("WORD_VALUE_TX")->AsString;
        nPos = UpperCase(strTempPhrase).Pos(UpperCase(strDicPhrase));
    	if(nPos > 0)
        {
        	nCode = DM_ML->TableUserDictionary->FieldByName("WORD_CODE_TX")->Value;
            strTemp = strTempPhrase;
	        locvalues[0] = Variant(nCode);
	        locvalues[1] = Variant(g_nDestLanguage);
	        if(DM_ML->TableUserDictionary->Locate("WORD_CODE_TX;LANGUAGE_ID_I",VarArrayOf(locvalues, 1),LocateOptions))
	        {
	        	strTemp=DM_ML->TableUserDictionary->FieldByName("WORD_VALUE_TX")->Value;
	        }

            strLeft = strTempPhrase.SubString(1,nPos-1);
            strRight = strTempPhrase.SubString(nPos+strDicPhrase.Length()+1,strTempPhrase.Length());
        	strTranslation = strLeft+strTemp+strRight;
         	break;
        }

     	DM_ML->TableUserDictionary->Next();
    }

    LEnd:;
    strTranslation+=strExtension;
//    if(!g_bJustTranslation)
//        ml_AddSegmentsToDictionary();
}
*/
//---------------------------------------------------------------------------
/*
void ml_TranslatePhrase(AnsiString strPhrase,AnsiString &strTranslation)
{
	AnsiString strExtension="";
    char c;
	for(int i=strPhrase.Length();i>=1;i--)
    {
    	c=strPhrase[i];
        if(!isspace(c))	break;
        strExtension=AnsiString(c)+strExtension;
    }
	strPhrase=strPhrase.Trim();
	strTranslation="";
	if(strPhrase.Length()<=0)	return;
    if(!g_bInitialized)
    {
     	MessageDlg("Multi-Language library not initialized...",mtError,TMsgDlgButtons()<<mbOK,0);
    	return;
    }

	AnsiString strTemp,strLeft,strRight,strTotalRight;
    AnsiString strLeftTranslation;
    AnsiString strTotalRightTemp;
    strTemp=strPhrase;
    strTotalRight="";
    if(ml_TranslateSection(strTemp,strLeftTranslation))
    {
	    strTranslation+=strLeftTranslation;
    	goto LEnd;
    }
    else
    {
        if(ml_IsSingleWord(strTemp))
        {
        	strTranslation+=strTemp;
	    	goto LEnd;
        }
    }
    while(true)
    {
    	ml_DecodePhrase(strTemp,strLeft,strRight);

        strTotalRightTemp=strTotalRight;
        if(strRight.Length()>0)
        	strTotalRight=strRight;
        if(strTotalRightTemp.Length()>0)
        	strTotalRight+=" "+strTotalRightTemp;

        if(ml_IsSingleWord(strLeft))
        {
			if(ml_TranslateSection(strLeft,strLeftTranslation))
		    {
            	strTranslation+=strLeftTranslation;
                if(strTotalRight.Length()>0)
                	strTranslation+=" ";
	            strTemp=strTotalRight;
			}
            else
            {
				if(strLeft.Length()<=0)
                {
                	if(strTotalRight.Length()<=0)	break;
                }
                strTranslation+=strLeft;
                if(strTotalRight.Length()>0)
                	strTranslation+=" ";
                strTemp=strTotalRight;
            }
            strTotalRight="";
        }
        else
        {
			if(ml_TranslateSection(strLeft,strLeftTranslation))
		    {
            	strTranslation+=strLeftTranslation;
                if(strTotalRight.Length()>0)
                	strTranslation+=" ";
	            strTemp=strTotalRight;
			    strTotalRight="";
		    }
            else
            {
				if(strLeft.Length()<=0)
                {
                	if(strTotalRight.Length()<=0)	break;
                	strLeft=strTotalRight;
	                strTotalRight="";
                }
	            strTemp=strLeft;
            }
        }
    }

    LEnd:;
    strTranslation+=strExtension;
//    if(!g_bJustTranslation)
//        ml_AddSegmentsToDictionary();
}
*/
//---------------------------------------------------------------------------
void ml_GeneratePhraseSegments(AnsiString strPhrase)
{
	strPhrase=strPhrase.Trim();
	if(strPhrase.Length()<=0)	return;
    if(!g_bInitialized)
    {
     	MessageDlg("Multi-Language library not initialized...",mtError,TMsgDlgButtons()<<mbOK,0);
    	return;
    }

	AnsiString strTemp,strLeft,strRight,strTotalRight;
    AnsiString strLeftTranslation;
    AnsiString strTotalRightTemp;
    strTemp=strPhrase;
    strTotalRight="";
    g_pList->Clear();
    g_pList->Add(strTemp);
    while(true)
    {
    	ml_DecodePhrase(strTemp,strLeft,strRight);

        strTotalRightTemp=strTotalRight;
        if(strRight.Length()>0)
        	strTotalRight=strRight;
        if(strTotalRightTemp.Length()>0)
        	strTotalRight+=" "+strTotalRightTemp;

        if(ml_IsSingleWord(strLeft))
        {
        	if(strLeft.Length()<=0)
            {
            	if(strTotalRight.Length()<=0)	break;
            }
            strTemp=strTotalRight;

            if(strTemp.Length()>0)
            {
	            if(strLeft.Length()>0)
    	        {
        	    	g_pList->Add(strLeft);
            	}
            	g_pList->Add(strTemp);
            }
            strTotalRight="";
        }
        else
        {
            if(strLeft.Length()>0)
            {
            	g_pList->Add(strLeft);
            }

            if(strLeft.Length()<=0)
            {
            	if(strTotalRight.Length()<=0)	break;
                strLeft=strTotalRight;
                strTotalRight="";
            }
            strTemp=strLeft;
        }
    }

    LEnd:;
    // Add new phrases to dictionary
    for(int i=0;i<g_pList->Count;i++)
    {
    	ml_AddSectionToUserDictionary(g_pList->Strings[i]);
    }
}
//---------------------------------------------------------------------------
void ml_DecodeParagraph(AnsiString strParagraph)
{
	g_Paragraph.clear();
    if(strParagraph.Length()<=0)	return;
    int len=strParagraph.Length();
    char c;
    ml_Phrase Phrase;
    Phrase.strPhrase="";
    Phrase.byType=ptPhrase;

    ml_Phrase Punctuation;
    Punctuation.strPhrase="";
    Punctuation.byType=ptPunctuation;

    AnsiString strLeftSpace="";
    AnsiString strRightSpace="";
    for(int i=1;i<=len;)
    {
		c=strParagraph[i];
        Punctuation.strPhrase="";
        strLeftSpace="";
        strRightSpace="";
    	while(isspace(c))
		{
        	strLeftSpace+=c;
            i++;
            if(i>len)	break;
			c=strParagraph[i];
        }

    	while(ml_IsPunctuation(c))
		{
        	Punctuation.strPhrase+=c;
            i++;
            if(i>len)	break;
			c=strParagraph[i];
        }

    	while(isspace(c))
		{
        	strRightSpace+=c;
            i++;
            if(i>len)	break;
			c=strParagraph[i];
        }

        if(Punctuation.strPhrase.Length()>0)
        {
        	Punctuation.strPhrase=strLeftSpace+Punctuation.strPhrase+strRightSpace;
            if(Phrase.strPhrase.Length()>0)
	            g_Paragraph.push_back(Phrase);
            g_Paragraph.push_back(Punctuation);

			Phrase.strPhrase="";
	        Punctuation.strPhrase="";
    	    strLeftSpace="";
        	strRightSpace="";
        }
        else
        {
        	Phrase.strPhrase+=strLeftSpace+c+strRightSpace;
            i++;
        }
    }

    Punctuation.strPhrase=strLeftSpace+Punctuation.strPhrase+strRightSpace;
    if(Punctuation.strPhrase.Length()>0)
    {
        g_Paragraph.push_back(Punctuation);
    }
    if(Phrase.strPhrase.Length()>0)
    {
    	g_Paragraph.push_back(Phrase);
    }
}
//---------------------------------------------------------------------------
void ml_ExtractPhraseWords(AnsiString strPhrase)
{
	g_PhraseWords.clear();
    int len=strPhrase.Length();
    if(len<=0)	return;
    ml_Phrase Word;
    Word.strPhrase="";
    Word.byType=ptPhrase;

    ml_Phrase Space;
    Space.strPhrase="";
    Space.byType=ptSpace;

    char c;
    for(int i=1;i<=len;)
    {
		c=strPhrase[i];
	    Space.strPhrase="";
        while(isspace(c))
        {
        	Space.strPhrase+=c;
            i++;
            if(i>len)	break;
			c=strPhrase[i];
        }

        if(Space.strPhrase.Length()>0)
        {
        	if(Word.strPhrase.Length()>0)
	        	g_PhraseWords.push_back(Word);
//            g_PhraseWords.push_back(Space);
			Word.strPhrase="";
	    	Space.strPhrase="";
        }
        else
        {
        	Word.strPhrase+=c;
            i++;
        }
    }

    if(Word.strPhrase.Length()>0)
    {
    	g_PhraseWords.push_back(Word);
    }
}
//---------------------------------------------------------------------------
void ml_ExtractPhraseSegments()
{
	g_PhraseSegments.clear();
    ml_Phrase Segment;
    Segment.strPhrase="";
    Segment.byType=ptPhrase;

    ml_Phrase Seperator;
    Seperator.strPhrase="";
    Seperator.byType=ptSeperator;

    AnsiString strWord;
    UINT count=g_PhraseWords.size();
	for(UINT i=0;i<count;)
    {
    	strWord=g_PhraseWords[i].strPhrase;
        Seperator.strPhrase="";
     	while(strWord.Length()<=g_nSeperatorLength)
        {
        	Seperator.strPhrase+=strWord+" ";
			i++;
            if(i>=count)	break;
	    	strWord=g_PhraseWords[i].strPhrase;
        }

        if(Seperator.strPhrase.Trim().Length()>0)
        {
        	if(Segment.strPhrase.Trim().Length()>0)
		    {
            	Segment.strPhrase=Segment.strPhrase.Trim();
		        g_PhraseSegments.push_back(Segment);
            }
            Seperator.strPhrase=Seperator.strPhrase.Trim();
         	g_PhraseSegments.push_back(Seperator);
            Segment.strPhrase="";
	        Seperator.strPhrase="";
        }
        else
        {
	        Segment.strPhrase+=strWord+" ";
            i++;
        }
    }

    if(Segment.strPhrase.Trim().Length()>0)
    {
    	Segment.strPhrase=Segment.strPhrase.Trim();
        g_PhraseSegments.push_back(Segment);
    }
}
//---------------------------------------------------------------------------
void ml_CollectSegments()
{
	g_CollectedSegments.clear();
    switch(g_byCollectingType)
    {
    	case ctNone:
        {
		    for(UINT i=0;i<g_PhraseSegments.size();i++)
		    {
            	g_CollectedSegments.push_back(g_PhraseSegments[i]);
		    }
            break;
        }
        case ctLeft:
        {
		    ml_Phrase Segment;
		    Segment.byType=ptPhrase;
        	Segment.strPhrase="";
		    for(UINT i=0;i<g_PhraseSegments.size();i++)
		    {
            	if(g_PhraseSegments[i].byType==ptSeperator)
                {
                	Segment.strPhrase+=g_PhraseSegments[i].strPhrase;
                    if(Segment.strPhrase.Trim().Length()>0)
                    {
                    	Segment.strPhrase=Segment.strPhrase.Trim();
		            	g_CollectedSegments.push_back(Segment);
                    }
		        	Segment.strPhrase="";
                }
                else
                {
                 	Segment.strPhrase+=g_PhraseSegments[i].strPhrase+" ";
                }
		    }
            if(Segment.strPhrase.Trim().Length()>0)
            {
            	Segment.strPhrase=Segment.strPhrase.Trim();
            	g_CollectedSegments.push_back(Segment);
            }
        	break;
        }
        case ctRight:
        {
		    ml_Phrase Seperator;
		    Seperator.byType=ptPhrase;
        	Seperator.strPhrase="";
		    for(UINT i=0;i<g_PhraseSegments.size();i++)
		    {
            	if(g_PhraseSegments[i].byType==ptPhrase)
                {
                	Seperator.strPhrase+=g_PhraseSegments[i].strPhrase;
                    if(Seperator.strPhrase.Trim().Length()>0)
                    {
                    	Seperator.strPhrase=Seperator.strPhrase.Trim();
		            	g_CollectedSegments.push_back(Seperator);
                    }
		        	Seperator.strPhrase="";
                }
                else
                {
                 	Seperator.strPhrase+=g_PhraseSegments[i].strPhrase+" ";
                }
		    }
            if(Seperator.strPhrase.Trim().Length()>0)
            {
            	Seperator.strPhrase=Seperator.strPhrase.Trim();
            	g_CollectedSegments.push_back(Seperator);
            }
            break;
        }
    }
}
//---------------------------------------------------------------------------
AnsiString ReplaceBy(AnsiString strPhrase,char a,char b)
{
	AnsiString strResult="";
    char x;
    for(int i=1;i<=strPhrase.Length();i++)
    {
    	x=strPhrase[i];
    	if(x==a)
        {
			strResult+=b;
        }
        else
        {
			strResult+=x;
        }
    }
    return strResult;
}
//---------------------------------------------------------------------------
void ml_AddSegmentsToDictionary()
{
	// Left Alignment
	ml_Phrase Segment;
	Segment.byType=ptPhrase;
    Segment.strPhrase="";
	for(UINT i=0;i<g_PhraseSegments.size();i++)
	{
    	if(g_PhraseSegments[i].byType==ptSeperator)
        {
//        	Segment.strPhrase+=ReplaceBy(g_PhraseSegments[i].strPhrase,' ','_');
			Segment.strPhrase += StringReplace(g_PhraseSegments[i].strPhrase," ","_",TReplaceFlags()<<rfReplaceAll);
            if(Segment.strPhrase.Trim().Length()>0)
            {
            	Segment.strPhrase=Segment.strPhrase.Trim();
				ml_GeneratePhraseSegments(Segment.strPhrase);
            }
	    	Segment.strPhrase="";
        }
        else
        {
         	Segment.strPhrase+=g_PhraseSegments[i].strPhrase+" ";
        }
	}
    if(Segment.strPhrase.Trim().Length()>0)
    {
    	Segment.strPhrase=Segment.strPhrase.Trim();
        ml_GeneratePhraseSegments(Segment.strPhrase);
    }

	// Right Alignment
	ml_Phrase Seperator;
	Seperator.byType=ptPhrase;
    Seperator.strPhrase="";
	for(UINT i=0;i<g_PhraseSegments.size();i++)
	{
    	if(g_PhraseSegments[i].byType==ptPhrase)
        {
        	Seperator.strPhrase+=g_PhraseSegments[i].strPhrase;
            if(Seperator.strPhrase.Trim().Length()>0)
            {
            	Seperator.strPhrase=Seperator.strPhrase.Trim();
	            ml_GeneratePhraseSegments(Seperator.strPhrase);
            }
	    	Seperator.strPhrase="";
        }
        else
        {
//         	Seperator.strPhrase+=ReplaceBy(g_PhraseSegments[i].strPhrase,' ','_')+" ";
			Segment.strPhrase += StringReplace(g_PhraseSegments[i].strPhrase," ","_",TReplaceFlags()<<rfReplaceAll);
        }
	}
    if(Seperator.strPhrase.Trim().Length()>0)
    {
    	Seperator.strPhrase=Seperator.strPhrase.Trim();
		ml_GeneratePhraseSegments(Seperator.strPhrase);
    }

/*
    switch(g_byCollectingType)
    {
    	case ctNone:
        {
		    for(UINT i=0;i<g_PhraseSegments.size();i++)
		    {
				ml_GeneratePhraseSegments(g_PhraseSegments[i].strPhrase);
		    }
            break;
        }
        case ctLeft:
        {
		    ml_Phrase Segment;
		    Segment.byType=ptPhrase;
        	Segment.strPhrase="";
		    for(UINT i=0;i<g_PhraseSegments.size();i++)
		    {
            	if(g_PhraseSegments[i].byType==ptSeperator)
                {
                	Segment.strPhrase+=ReplaceBy(g_PhraseSegments[i].strPhrase,' ','_');
                    if(Segment.strPhrase.Trim().Length()>0)
                    {
                    	Segment.strPhrase=Segment.strPhrase.Trim();
						ml_GeneratePhraseSegments(Segment.strPhrase);
                    }
		        	Segment.strPhrase="";
                }
                else
                {
                 	Segment.strPhrase+=g_PhraseSegments[i].strPhrase+" ";
                }
		    }
            if(Segment.strPhrase.Trim().Length()>0)
            {
            	Segment.strPhrase=Segment.strPhrase.Trim();
                ml_GeneratePhraseSegments(Segment.strPhrase);
            }
        	break;
        }
        case ctRight:
        {
		    ml_Phrase Seperator;
		    Seperator.byType=ptPhrase;
        	Seperator.strPhrase="";
		    for(UINT i=0;i<g_PhraseSegments.size();i++)
		    {
            	if(g_PhraseSegments[i].byType==ptPhrase)
                {
                	Seperator.strPhrase+=g_PhraseSegments[i].strPhrase;
                    if(Seperator.strPhrase.Trim().Length()>0)
                    {
                    	Seperator.strPhrase=Seperator.strPhrase.Trim();
//		            	g_CollectedSegments.push_back(Seperator);
		                ml_GeneratePhraseSegments(Seperator.strPhrase);
                    }
		        	Seperator.strPhrase="";
                }
                else
                {
//                 	Seperator.strPhrase+=g_PhraseSegments[i].strPhrase+" ";
                 	Seperator.strPhrase+=ReplaceBy(g_PhraseSegments[i].strPhrase,' ','_')+" ";
                }
		    }
            if(Seperator.strPhrase.Trim().Length()>0)
            {
            	Seperator.strPhrase=Seperator.strPhrase.Trim();
//            	g_CollectedSegments.push_back(Seperator);
				ml_GeneratePhraseSegments(Seperator.strPhrase);
            }
            break;
        }
    }
*/
}
//---------------------------------------------------------------------------
void ml_TranslateParagraph(AnsiString strParagraph,AnsiString &strTranslation)
{
	strTranslation="";
    strParagraph = StringReplace(strParagraph,"\n"," ",TReplaceFlags()<<rfReplaceAll);
    strParagraph = StringReplace(strParagraph,"\r"," ",TReplaceFlags()<<rfReplaceAll);
    strParagraph = StringReplace(strParagraph,"\t"," ",TReplaceFlags()<<rfReplaceAll);
    strParagraph = ml_RemoveRepeatedSpaces(strParagraph);
	if(strParagraph.Length()<=0)	return;
    if(!g_bInitialized)
    {
     	MessageDlg("Multi-Language library not initialized...",mtError,TMsgDlgButtons()<<mbOK,0);
    	return;
    }

    AnsiString strLocalTranslation="";

    g_nStartCode = ml_GetCurrStartCode() + 1;

	ml_DecodeParagraph(strParagraph.LowerCase());

    if(g_pProgressBar)
    {
	    g_pProgressBar->Min=0;
	    g_pProgressBar->Max=g_Paragraph.size()-1;
	    g_pProgressBar->Position=0;
    }

    DM_ML->TableUserDictionary->Close();
    DM_ML->TableUserDictionary->Open();

    // For best performance we disable display controls.
    DM_ML->TableUserDictionary->DisableControls();
    try
    {
	    for(UINT i=0;i<g_Paragraph.size();i++)
	    {
        	if(g_pProgressBar)
            {
		    	g_pProgressBar->Position=i;
            }
            Application->ProcessMessages();
	    	if(g_Paragraph[i].byType==ptPhrase)
	        {
                ml_TranslatePhrase(g_Paragraph[i].strPhrase,strLocalTranslation);
                strTranslation+=strLocalTranslation+" ";
/*
				ml_ExtractPhraseWords(g_Paragraph[i].strPhrase);
	            ml_ExtractPhraseSegments();
	            ml_CollectSegments();
    			if(!g_bJustTranslation)
        			ml_AddSegmentsToDictionary();
*/                    
	        }
	        else
	        {
	        	strTranslation=strTranslation.Trim();
	        	strTranslation+=g_Paragraph[i].strPhrase;
	        }
	    }
	    strTranslation=strTranslation.Trim();
    }
    __finally
    {
	    DM_ML->TableUserDictionary->EnableControls();
        if(g_pProgressBar)
        {
	        g_pProgressBar->Position=0;
        }
    }
}
//---------------------------------------------------------------------------
/*
void ml_TranslateParagraph(AnsiString strParagraph,AnsiString &strTranslation)
{
	strTranslation="";
	if(strParagraph.Length()<=0)	return;
    if(!g_bInitialized)
    {
     	MessageDlg("Multi-Language library not initialized...",mtError,TMsgDlgButtons()<<mbOK,0);
    	return;
    }

    AnsiString strLocalTranslation="";

    g_nStartCode = ml_GetCurrStartCode() + 1;

	ml_DecodeParagraph(strParagraph.LowerCase());

    if(g_pProgressBar)
    {
	    g_pProgressBar->Min=0;
	    g_pProgressBar->Max=g_Paragraph.size()-1;
	    g_pProgressBar->Position=0;
    }

    DM_ML->TableUserDictionary->Close();
    DM_ML->TableUserDictionary->Open();

    // For best performance we disable display controls.
    DM_ML->TableUserDictionary->DisableControls();
    try
    {
	    for(UINT i=0;i<g_Paragraph.size();i++)
	    {
        	if(g_pProgressBar)
            {
		    	g_pProgressBar->Position=i;
            }
            Application->ProcessMessages();
	    	if(g_Paragraph[i].byType==ptPhrase)
	        {
				ml_ExtractPhraseWords(g_Paragraph[i].strPhrase);
	            ml_ExtractPhraseSegments();
	            ml_CollectSegments();
//                ml_AddSegmentsToDictionary();
    			if(!g_bJustTranslation)
        			ml_AddSegmentsToDictionary();

	            for(UINT j=0;j<g_CollectedSegments.size();j++)
	            {
					ml_TranslatePhrase(g_CollectedSegments[j].strPhrase,strLocalTranslation);
	                strTranslation+=strLocalTranslation+" ";
	            }
                
	        }
	        else
	        {
	        	strTranslation=strTranslation.Trim();
	        	strTranslation+=g_Paragraph[i].strPhrase;
	        }
	    }
	    strTranslation=strTranslation.Trim();
    }
    __finally
    {
	    DM_ML->TableUserDictionary->EnableControls();
        if(g_pProgressBar)
        {
	        g_pProgressBar->Position=0;
        }
    }
}
*/
//---------------------------------------------------------------------------
/*
void ml_TranslateParagraph(AnsiString strParagraph,AnsiString &strTranslation)
{
	AnsiString strPhrase="";
    char c;
    AnsiString strLocalTranslation="";
    AnsiString strCurrWord="";
    int nPhraseIndex=0;
    strTranslation="";
    if(strParagraph.Length()<=0)	return;
    if(!g_bInitialized)
    {
     	MessageDlg("Multi-Language library not initialized...",mtError,TMsgDlgButtons()<<mbOK,0);
    	return;
    }

	int nPhrasesCount=ml_CalculatePhrasesCount(strParagraph);
    FormMain->ProgressBar1->Min=1;
    FormMain->ProgressBar1->Max=nPhrasesCount;
    FormMain->ProgressBar1->Position=0;

    // For best performance we disable display controls.
    DM_ML->TableUserDictionary->DisableControls();
    try
    {

    int nLength=strParagraph.Length();
    for(int i=1;i<=nLength;)
	{
    	c=strParagraph[i];
        strCurrWord="";
    	while(!ml_IsSeperator(c))
        {
			strCurrWord+=c;
        	strPhrase+=c;

			i++;
            if(i>nLength)	break;
	    	c=strParagraph[i];
        }
        int len=strCurrWord.Length();
        if(len<=0)// Punctuation or space
        {
        	if(strPhrase.Length()>0)
            {
            	ml_TranslatePhrase(strPhrase,strLocalTranslation);
                strTranslation+=strLocalTranslation;
                nPhraseIndex++;
			    FormMain->ProgressBar1->Position=nPhraseIndex;
            }
            strTranslation+=strCurrWord+c;
            strPhrase="";
            strCurrWord="";
            i++;
        }
        else
        if((len>0) && (len<=g_nSeperatorLength))// Logical break point
        {
            switch(g_byCollectingType)
            {
             	case ctNone:
                {
					strPhrase.Delete(strPhrase.Length()-len+1,len);
                 	break;
                }
             	case ctLeft:
                {
                 	break;
                }
             	case ctRight:
                {
                	strPhrase.Delete(strPhrase.Length()-len+1,len);
                 	break;
                }
            }
        	if(strPhrase.Length()>0)
            {
            	ml_TranslatePhrase(strPhrase,strLocalTranslation);
                strTranslation+=strLocalTranslation;
                nPhraseIndex++;
			    FormMain->ProgressBar1->Position=nPhraseIndex;
            }
            switch(g_byCollectingType)
            {
             	case ctNone:
                {
                    strPhrase=strCurrWord;
                    if(strPhrase.Length()>0)
                    {
                    	ml_TranslatePhrase(strPhrase,strLocalTranslation);
                        strTranslation+=strLocalTranslation;
                        nPhraseIndex++;
                        FormMain->ProgressBar1->Position=nPhraseIndex;
                    }
                    strTranslation+=c;
                    strPhrase="";
                 	break;
                }
             	case ctLeft:
                {
		            strTranslation+=c;
		            strPhrase="";
                 	break;
                }
             	case ctRight:
                {           
                    strPhrase=strCurrWord;
                    if(isspace(c))	strPhrase+=c;
                    else
                    {
			        	if(strPhrase.Length()>0)
			            {
			            	ml_TranslatePhrase(strPhrase,strLocalTranslation);
			                strTranslation+=strLocalTranslation;
			                nPhraseIndex++;
						    FormMain->ProgressBar1->Position=nPhraseIndex;
			            }
			            strTranslation+=c;
			            strPhrase="";
                    }
                 	break;
                }
            }
            strCurrWord="";
            i++;
        }
        else
        {
        	if(isspace(c))
            {
            	strPhrase+=c;
            }
            else
            {
	        	if(strPhrase.Length()>0)
	            {
	            	ml_TranslatePhrase(strPhrase,strLocalTranslation);
	                strTranslation+=strLocalTranslation;
	                nPhraseIndex++;
				    FormMain->ProgressBar1->Position=nPhraseIndex;
	            }
	            strTranslation+=c;
	            strPhrase="";
            }
            strCurrWord="";
            i++;
        }
    }

    }
    __finally
    {
	    DM_ML->TableUserDictionary->EnableControls();
        FormMain->ProgressBar1->Position=0;
    }
}
//---------------------------------------------------------------------------
int ml_CalculatePhrasesCount(AnsiString strParagraph)
{
	AnsiString strPhrase="";
    char c;
    AnsiString strCurrWord="";
    int nPhrasesCount=0;
    if(strParagraph.Length()<=0)	return nPhrasesCount;
    if(!g_bInitialized)
    {
     	MessageDlg("Multi-Language library not initialized...",mtError,TMsgDlgButtons()<<mbOK,0);
    	return nPhrasesCount;
    }

    int nLength=strParagraph.Length();
    for(int i=1;i<=nLength;)
	{
    	c=strParagraph[i];
        strCurrWord="";
    	while(!ml_IsSeperator(c))
        {
			strCurrWord+=c;
        	strPhrase+=c;

			i++;
            if(i>nLength)	break;
	    	c=strParagraph[i];
        }
        int len=strCurrWord.Length();
        if(len<=0)// Punctuation or space
        {
        	if(strPhrase.Length()>0)
            {
                nPhrasesCount++;
            }
            strPhrase="";
            strCurrWord="";
            i++;
        }
        else
        if((len>0) && (len<=g_nSeperatorLength))// Logical break point
        {
            switch(g_byCollectingType)
            {
             	case ctNone:
                {
					strPhrase.Delete(strPhrase.Length()-len+1,len);
                 	break;
                }
             	case ctLeft:
                {
                 	break;
                }
             	case ctRight:
                {
                	strPhrase.Delete(strPhrase.Length()-len+1,len);
                 	break;
                }
            }
        	if(strPhrase.Length()>0)
            {
                nPhrasesCount++;
            }
            switch(g_byCollectingType)
            {
             	case ctNone:
                {
                    strPhrase=strCurrWord;
                    if(strPhrase.Length()>0)
                    {
                        nPhrasesCount++;
                    }
                    strPhrase="";
                 	break;
                }
             	case ctLeft:
                {
		            strPhrase="";
                 	break;
                }
             	case ctRight:
                {           
                    strPhrase=strCurrWord;
                    if(isspace(c))	strPhrase+=c;
                    else
                    {
			        	if(strPhrase.Length()>0)
			            {
			                nPhrasesCount++;
			            }
			            strPhrase="";
                    }
                 	break;
                }
            }
            strCurrWord="";
            i++;
        }
        else
        {
        	if(isspace(c))
            {
            	strPhrase+=c;
            }
            else
            {
	        	if(strPhrase.Length()>0)
	            {
	                nPhrasesCount++;
	            }
	            strPhrase="";
            }
            strCurrWord="";
            i++;
        }
    }
    return nPhrasesCount;
}
*/
//---------------------------------------------------------------------------

