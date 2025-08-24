// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DnsQuery.pas' rev: 6.00

#ifndef DnsQueryHPP
#define DnsQueryHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <WSocket.hpp>	// Pascal unit
#include <WinSock.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Dnsquery
{
//-- type declarations -------------------------------------------------------
typedef AnsiString TDnsAnswerNameArray[50];

typedef int TDnsAnswerTypeArray[50];

typedef int TDnsAnswerClassArray[50];

typedef int TDnsAnswerTTLArray[50];

typedef int TDnsAnswerTagArray[50];

typedef int TDnsMXPreferenceArray[50];

typedef AnsiString TDnsMXExchangeArray[50];

typedef in_addr TDnsAddressArray[50];

typedef AnsiString TDnsHostnameArray[10];

typedef void __fastcall (__closure *TDnsRequestDoneEvent)(System::TObject* Sender, Word Error);

#pragma pack(push, 1)
struct TDnsRequestHeader
{
	Word ID;
	Word Flags;
	Word QDCount;
	Word ANCount;
	Word NSCount;
	Word ARCount;
} ;
#pragma pack(pop)

typedef TDnsRequestHeader *PDnsRequestHeader;

#pragma pack(push, 1)
struct TLOCInfo
{
	Byte version;
	Byte size;
	Byte horizpre;
	Byte vertpre;
	int latitude;
	int longitude;
	int altitude;
} ;
#pragma pack(pop)

typedef TLOCInfo *PLOCInfo;

#pragma pack(push, 4)
struct TLogGeo
{
	Byte version;
	int longsize;
	int latsize;
	int horizpre;
	int vertpre;
	int lad;
	int lam;
	int las;
	int lams;
	char lahem;
	int lod;
	int lom;
	int los;
	int loms;
	char lohem;
	int altitude;
} ;
#pragma pack(pop)

class DELPHICLASS TDnsQuery;
class PASCALIMPLEMENTATION TDnsQuery : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
protected:
	Wsocket::TWSocket* FWSocket;
	AnsiString FPort;
	AnsiString FAddr;
	Word FIDCount;
	char FQueryBuf[512];
	int FQueryLen;
	char FResponseBuf[512];
	int FResponseLen;
	int FResponseID;
	int FResponseCode;
	int FResponseOpCode;
	bool FResponseAuthoritative;
	bool FResponseTruncation;
	bool FResponseRecursionAvailable;
	int FResponseQDCount;
	int FResponseANCount;
	int FResponseNSCount;
	int FResponseARCount;
	int FQuestionType;
	int FQuestionClass;
	AnsiString FQuestionName;
	AnsiString FAnswerNameArray[50];
	int FAnswerTypeArray[50];
	int FAnswerClassArray[50];
	int FAnswerTTLArray[50];
	int FAnswerTagArray[50];
	int FMXRecordCount;
	int FMXPreferenceArray[50];
	AnsiString FMXExchangeArray[50];
	int FARecordCount;
	in_addr FAddressArray[50];
	int FPTRRecordCount;
	AnsiString FHostnameArray[10];
	TDnsRequestDoneEvent FOnRequestDone;
	#pragma pack(push, 1)
	TLOCInfo fLOCInfo;
	#pragma pack(pop)
	
	int __fastcall GetMXPreference(int nIndex);
	AnsiString __fastcall GetMXExchange(int nIndex);
	AnsiString __fastcall GetAnswerName(int nIndex);
	int __fastcall GetAnswerType(int nIndex);
	int __fastcall GetAnswerClass(int nIndex);
	int __fastcall GetAnswerTTL(int nIndex);
	int __fastcall GetAnswerTag(int nIndex);
	in_addr __fastcall GetAddress(int nIndex);
	AnsiString __fastcall GetHostname(int nIndex);
	virtual void __fastcall BuildRequestHeader(PDnsRequestHeader Dst, Word ID, Byte OPCode, bool Recursion, Word QDCount, Word ANCount, Word NSCount, Word ARCount);
	virtual int __fastcall BuildQuestionSection(char * Dst, const AnsiString QName, Word QType, Word QClass);
	virtual void __fastcall WSocketDataAvailable(System::TObject* Sender, Word Error);
	virtual void __fastcall TriggerRequestDone(Word Error);
	char * __fastcall GetResponseBuf(void);
	void __fastcall SendQuery(void);
	char * __fastcall ExtractName(char * Base, char * From, AnsiString &Name);
	char * __fastcall DecodeQuestion(char * Base, char * From, AnsiString &Name, int &QType, int &QClass);
	char * __fastcall DecodeAnswer(char * Base, char * From, AnsiString &Name, int &QType, int &QClass, int &TTL, void * &RDataPtr, int &RDataLen);
	char * __fastcall DecodeMXData(char * Base, char * From, int &Preference, AnsiString &Exchange);
	char * __fastcall DecodeAData(char * Base, char * From, in_addr &Address);
	char * __fastcall DecodePTRData(char * Base, char * From, AnsiString &Hostname);
	
public:
	__fastcall virtual TDnsQuery(Classes::TComponent* AOwner);
	__fastcall virtual ~TDnsQuery(void);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation operation);
	int __fastcall MXLookup(AnsiString Domain);
	int __fastcall ALookup(AnsiString Host);
	int __fastcall PTRLookup(AnsiString IP);
	int __fastcall QueryAny(AnsiString Host, int QNumber);
	__property int ResponseID = {read=FResponseID, nodefault};
	__property int ResponseCode = {read=FResponseCode, nodefault};
	__property int ResponseOpCode = {read=FResponseOpCode, nodefault};
	__property bool ResponseAuthoritative = {read=FResponseAuthoritative, nodefault};
	__property bool ResponseTruncation = {read=FResponseTruncation, nodefault};
	__property bool ResponseRecursionAvailable = {read=FResponseRecursionAvailable, nodefault};
	__property int ResponseQDCount = {read=FResponseQDCount, nodefault};
	__property int ResponseANCount = {read=FResponseANCount, nodefault};
	__property int ResponseNSCount = {read=FResponseNSCount, nodefault};
	__property int ResponseARCount = {read=FResponseARCount, nodefault};
	__property char * ResponseBuf = {read=GetResponseBuf};
	__property int ResponseLen = {read=FResponseLen, nodefault};
	__property int QuestionType = {read=FQuestionType, nodefault};
	__property int QuestionClass = {read=FQuestionClass, nodefault};
	__property AnsiString QuestionName = {read=FQuestionName};
	__property AnsiString AnswerName[int nIndex] = {read=GetAnswerName};
	__property int AnswerType[int nIndex] = {read=GetAnswerType};
	__property int AnswerClass[int nIndex] = {read=GetAnswerClass};
	__property int AnswerTTL[int nIndex] = {read=GetAnswerTTL};
	__property int AnswerTag[int nIndex] = {read=GetAnswerTag};
	__property int MXPreference[int nIndex] = {read=GetMXPreference};
	__property AnsiString MXExchange[int nIndex] = {read=GetMXExchange};
	__property in_addr Address[int nIndex] = {read=GetAddress};
	__property AnsiString Hostname[int nIndex] = {read=GetHostname};
	__property TLOCInfo Loc = {read=fLOCInfo};
	
__published:
	__property AnsiString Port = {read=FPort, write=FPort};
	__property AnsiString Addr = {read=FAddr, write=FAddr};
	__property TDnsRequestDoneEvent OnRequestDone = {read=FOnRequestDone, write=FOnRequestDone};
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint DnsQueryVersion = 0x66;
extern PACKAGE AnsiString CopyRight;
static const Shortint MAX_ANCOUNT = 0x32;
static const Shortint MAX_MX_RECORDS = 0x32;
static const Shortint MAX_A_RECORDS = 0x32;
static const Shortint MAX_PTR_RECORDS = 0xa;
static const Shortint DnsClassIN = 0x1;
static const Shortint DnsClassCS = 0x2;
static const Shortint DnsClassCH = 0x3;
static const Shortint DnsClassHS = 0x4;
static const Byte DnsClassALL = 0xff;
static const Shortint DnsQueryA = 0x1;
static const Shortint DnsQueryNS = 0x2;
static const Shortint DnsQueryMD = 0x3;
static const Shortint DnsQueryMF = 0x4;
static const Shortint DnsQueryCNAME = 0x5;
static const Shortint DnsQuerySOA = 0x6;
static const Shortint DnsQueryMB = 0x7;
static const Shortint DnsQueryMG = 0x8;
static const Shortint DnsQueryMR = 0x9;
static const Shortint DnsQueryNULL = 0xa;
static const Shortint DnsQueryWKS = 0xb;
static const Shortint DnsQueryPTR = 0xc;
static const Shortint DnsQueryHINFO = 0xd;
static const Shortint DnsQueryMINFO = 0xe;
static const Shortint DnsQueryMX = 0xf;
static const Shortint DnsQueryTXT = 0x10;
static const Shortint DnsQueryRP = 0x11;
static const Shortint DnsQueryAFSDB = 0x12;
static const Shortint DnsQueryX25 = 0x13;
static const Shortint DnsQueryISDN = 0x14;
static const Shortint DnsQueryRT = 0x15;
static const Shortint DnsQueryNSAP = 0x16;
static const Shortint DnsQueryNSAPPTR = 0x17;
static const Shortint DnsQuerySIG = 0x18;
static const Shortint DnsQueryKEY = 0x19;
static const Shortint DnsQueryPX = 0x1a;
static const Shortint DnsQueryGPOS = 0x1b;
static const Shortint DnsQueryAAAA = 0x1c;
static const Shortint DnsQueryLOC = 0x1d;
static const Shortint DnsQueryNXT = 0x1e;
static const Shortint DnsQuerySRV = 0x21;
static const Shortint DnsQueryNAPTR = 0x23;
static const Shortint DnsQueryKX = 0x24;
static const Byte DnsQueryAXFR = 0xfc;
static const Byte DnsQueryMAILB = 0xfd;
static const Byte DnsQueryMAILA = 0xfe;
static const Byte DnsQueryALL = 0xff;
static const Shortint DnsOpCodeQUERY = 0x0;
static const Shortint DnsOpCodeIQUERY = 0x1;
static const Shortint DnsOpCodeSTATUS = 0x2;
extern PACKAGE AnsiString __fastcall ReverseIP(const AnsiString IP);
extern PACKAGE void __fastcall Register(void);
extern PACKAGE AnsiString __fastcall LongLatToDMS(int longlat, AnsiString hemis);
extern PACKAGE TLogGeo __fastcall Loc2Geo(const TLOCInfo &loc);

}	/* namespace Dnsquery */
using namespace Dnsquery;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DnsQuery
