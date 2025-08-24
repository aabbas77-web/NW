//---------------------------------------------------------------------------
#ifndef MLH
#define MLH
//---------------------------------------------------------------------------
#include <Forms.hpp>
#include <Classes.hpp>
#include <Dialogs.hpp>
#include <DB.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include <vector.h>
//---------------------------------------------------------------------------
// Collecting Tyes
#define		ctNone		(Byte)0
#define		ctLeft		(Byte)1
#define		ctRight		(Byte)2
//---------------------------------------------------------------------------
// Phrase Types
#define		ptPhrase		(Byte)0
#define		ptPunctuation	(Byte)1
#define		ptSpace			(Byte)2
#define		ptSeperator		(Byte)3
//---------------------------------------------------------------------------
struct ml_Phrase
{
	AnsiString 	strPhrase;
    Byte 		byType;
};
//---------------------------------------------------------------------------
typedef vector<ml_Phrase> ml_Paragraph;
//---------------------------------------------------------------------------
struct ml_TranslationRec
{
	AnsiString strFound;
    AnsiString strTranslation;
};
//---------------------------------------------------------------------------
typedef vector<ml_TranslationRec> ml_TranslationRecs;
//---------------------------------------------------------------------------
extern bool 	g_bInitialized;
extern int 		g_nSourceLanguage;
extern int 		g_nDestLanguage;
extern int 		g_nStartCode;
extern int 		g_nLanguagesCount;
extern TStringList *g_pList;
extern TStringList *g_pRecordList;
extern ml_Paragraph g_Paragraph;
extern ml_Paragraph g_PhraseWords;
extern ml_Paragraph g_PhraseSegments;
extern ml_Paragraph g_CollectedSegments;
extern int 		g_nSeperatorLength;
extern Byte		g_byCollectingType;
extern bool		g_bAddBreakPoint;
extern bool		g_bApplyConstraints;
extern int		g_nMinWordsCount;
extern int		g_nMaxWordsCount;
extern bool 	g_bJustTranslation;
extern bool 	g_bSourceIsLeftToRight;
extern bool 	g_bDestIsLeftToRight;
extern int		g_nLocateCount;
extern bool		g_bUpdateFreq;
extern TProgressBar *g_pProgressBar;
//---------------------------------------------------------------------------
void ml_Initialize();
void ml_Finalize();
void ml_Clear();
bool ml_IsSeperator(char c);
bool ml_IsSingleWord(AnsiString strPhrase);
int  ml_CalculateWordsCount(AnsiString strPhrase);
void ml_DecodePhrase(AnsiString strPhrase,AnsiString &strLeft,AnsiString &strRight);
void ml_ExtractPhraseWords(AnsiString strPhrase);
bool ml_TranslateSection(AnsiString strSection,AnsiString &strTranslation);
void ml_TranslatePhrase(AnsiString strPhrase,AnsiString &strTranslation);
void ml_TranslateParagraph(AnsiString strParagraph,AnsiString &strTranslation);
void ml_AddSectionToUserDictionary(AnsiString strSection);
void ml_GeneratePhraseSegments(AnsiString strPhrase);
int ml_CalculatePhrasesCount(AnsiString strParagraph);
void ml_DecodeParagraph(AnsiString strParagraph);
bool ml_IsPunctuation(char c);
void ml_ExtractPhraseSegments();
void ml_CollectSegments();
void ml_AddSegmentsToDictionary();
AnsiString ReplaceBy(AnsiString strPhrase,char a,char b);
int ml_GetCurrStartCode();
AnsiString ml_RemoveRepeatedSpaces(AnsiString strPhrase);
void ml_AddPhraseToDictionary(AnsiString strPhrase);
//---------------------------------------------------------------------------
#endif
