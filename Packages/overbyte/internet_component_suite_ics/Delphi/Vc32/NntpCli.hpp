// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'NntpCli.pas' rev: 6.00

#ifndef NntpCliHPP
#define NntpCliHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <WSocket.hpp>	// Pascal unit
#include <WinSock.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Nntpcli
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TNntpDisplay)(System::TObject* Sender, char * Msg, int Len);

#pragma option push -b-
enum TNntpState { nntpNotConnected, nntpDnsLookup, nntpWaitingBanner, nntpReady, nntpWaitingResponse };
#pragma option pop

#pragma option push -b-
enum TNntpRequest { nntpGroup, nntpList, nntpConnect, nntpPost, nntpHelp, nntpNewGroups, nntpNewNews, nntpArticleByNumber, nntpArticleByID, nntpBodyByID, nntpBodyByNumber, nntpHeadByID, nntpHeadByNumber, nntpStatByID, nntpStatByNumber, nntpNext, nntpLast, nntpQuit, nntpAbort, nntpXOver, nntpListOverViewFmt, nntpDate, nntpAuthenticate, nntpModeReader, nntpXHdr };
#pragma option pop

typedef void __fastcall (__closure *TRequestDone)(System::TObject* Sender, TNntpRequest RqType, Word Error);

class DELPHICLASS NntpException;
class PASCALIMPLEMENTATION NntpException : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall NntpException(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall NntpException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall NntpException(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall NntpException(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall NntpException(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall NntpException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall NntpException(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall NntpException(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~NntpException(void) { }
	#pragma option pop
	
};


class DELPHICLASS TNntpCli;
class PASCALIMPLEMENTATION TNntpCli : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
__published:
	__fastcall virtual TNntpCli(Classes::TComponent* AOwner);
	__fastcall virtual ~TNntpCli(void);
	virtual void __fastcall Connect(void);
	virtual void __fastcall Abort(void);
	virtual void __fastcall Quit(void);
	virtual void __fastcall Group(AnsiString NewsGroupName);
	virtual void __fastcall ArticleByNumber(int Number, Classes::TStream* DestStream);
	virtual void __fastcall ArticleByID(AnsiString ID, Classes::TStream* DestStream);
	virtual void __fastcall HeadByNumber(int Number, Classes::TStream* DestStream);
	virtual void __fastcall HeadByID(AnsiString ID, Classes::TStream* DestStream);
	virtual void __fastcall BodyByNumber(int Number, Classes::TStream* DestStream);
	virtual void __fastcall BodyByID(AnsiString ID, Classes::TStream* DestStream);
	virtual void __fastcall StatByNumber(int Number);
	virtual void __fastcall StatByID(AnsiString ID);
	virtual void __fastcall Next(void);
	virtual void __fastcall Last(void);
	virtual void __fastcall List(Classes::TStream* DestStream);
	virtual void __fastcall Post(Classes::TStream* FromStream);
	virtual void __fastcall Help(Classes::TStream* DestStream);
	virtual void __fastcall Authenticate(void);
	virtual void __fastcall XOver(AnsiString Articles, Classes::TStream* DestStream);
	virtual void __fastcall ListOverViewFmt(Classes::TStream* DestStream);
	virtual void __fastcall Date(void);
	virtual void __fastcall ModeReader(void);
	virtual void __fastcall XHdr(Classes::TStream* DestStream, AnsiString Header, AnsiString Range);
	virtual void __fastcall NewGroups(System::TDateTime When, bool GMTFLag, AnsiString Distributions, Classes::TStream* DestStream);
	virtual void __fastcall NewNews(System::TDateTime When, bool GMTFLag, AnsiString NewsGroupName, AnsiString Distributions, Classes::TStream* DestStream);
	
protected:
	HWND FWindowHandle;
	AnsiString FHost;
	TNntpState FState;
	Wsocket::TWSocket* FWSocket;
	AnsiString FRequest;
	TNntpRequest FRequestType;
	bool FRequestDoneFlag;
	bool FSentFlag;
	int FStatusCode;
	char FSendBuffer[4096];
	char FReceiveBuffer[4096];
	int FReceiveLen;
	AnsiString FLastResponse;
	AnsiString FLastCmdResponse;
	AnsiString FErrorMessage;
	int FArticleEstimated;
	int FArticleFirst;
	int FArticleLast;
	int FArticleNumber;
	AnsiString FArticleID;
	System::TDateTime FServerDate;
	Classes::TStream* FDataStream;
	AnsiString FUserName;
	AnsiString FPassWord;
	void __fastcall (__closure *FNext)(void);
	bool FPostingPermited;
	Wsocket::TSessionConnected FOnSessionConnected;
	Wsocket::TSessionClosed FOnSessionClosed;
	Wsocket::TDataAvailable FOnDataAvailable;
	TRequestDone FOnRequestDone;
	TNntpDisplay FOnDisplay;
	Classes::TNotifyEvent FOnMessageBegin;
	Classes::TNotifyEvent FOnMessageEnd;
	Classes::TNotifyEvent FOnMessageLine;
	Classes::TNotifyEvent FOnXHdrBegin;
	Classes::TNotifyEvent FOnXHdrEnd;
	Classes::TNotifyEvent FOnXHdrLine;
	Classes::TNotifyEvent FOnStateChange;
	void __fastcall WndProc(Messages::TMessage &MsgRec);
	MESSAGE void __fastcall WMNntpRequestDone(Messages::TMessage &msg);
	void __fastcall WSocketDnsLookupDone(System::TObject* Sender, Word Error);
	void __fastcall WSocketSessionConnected(System::TObject* Sender, Word Error);
	void __fastcall WSocketDataAvailable(System::TObject* Sender, Word Error);
	void __fastcall WSocketSessionClosed(System::TObject* Sender, Word Error);
	void __fastcall WSocketDataSent(System::TObject* Sender, Word Error);
	virtual void __fastcall TriggerRequestDone(Word Error);
	virtual void __fastcall TriggerStateChange(void);
	virtual void __fastcall StateChange(TNntpState NewState);
	virtual void __fastcall SendRequest(void);
	virtual void __fastcall GroupNext(void);
	virtual void __fastcall QuitNext(void);
	virtual void __fastcall XHdrLineNext(void);
	virtual void __fastcall GetArticleNext(void);
	virtual void __fastcall GetArticleLineNext(void);
	virtual void __fastcall GetArticleByNumber(TNntpRequest RqType, int Number, Classes::TStream* DestStream);
	virtual void __fastcall GetArticleByID(TNntpRequest RqType, AnsiString ID, Classes::TStream* DestStream);
	virtual void __fastcall GetArticle(TNntpRequest RqType, AnsiString ID, Classes::TStream* DestStream);
	virtual void __fastcall PostNext(void);
	virtual void __fastcall PostDone(void);
	virtual void __fastcall PostBlock(void);
	virtual void __fastcall PostSendNext(void);
	virtual void __fastcall DateNext(void);
	virtual void __fastcall ModeReaderNext(void);
	virtual void __fastcall XHdrNext(void);
	virtual void __fastcall AuthenticateNext1(void);
	virtual void __fastcall AuthenticateNext2(void);
	__property HWND Handle = {read=FWindowHandle, nodefault};
	
__published:
	__property Wsocket::TWSocket* CtrlSocket = {read=FWSocket};
	__property TNntpState State = {read=FState, nodefault};
	__property AnsiString Host = {read=FHost, write=FHost};
	__property AnsiString ErrorMessage = {read=FErrorMessage};
	__property AnsiString LastResponse = {read=FLastResponse};
	__property int StatusCode = {read=FStatusCode, nodefault};
	__property bool PostingPermited = {read=FPostingPermited, nodefault};
	__property int ArticleEstimated = {read=FArticleEstimated, nodefault};
	__property int ArticleFirst = {read=FArticleFirst, nodefault};
	__property int ArticleLast = {read=FArticleLast, nodefault};
	__property int ArticleNumber = {read=FArticleNumber, nodefault};
	__property AnsiString ArticleID = {read=FArticleID};
	__property System::TDateTime ServerDate = {read=FServerDate};
	__property AnsiString UserName = {read=FUserName, write=FUserName};
	__property AnsiString PassWord = {read=FPassWord, write=FPassWord};
	__property Wsocket::TSessionConnected OnSessionConnected = {read=FOnSessionConnected, write=FOnSessionConnected};
	__property Wsocket::TSessionClosed OnSessionClosed = {read=FOnSessionClosed, write=FOnSessionClosed};
	__property Wsocket::TDataAvailable OnDataAvailable = {read=FOnDataAvailable, write=FOnDataAvailable};
	__property TRequestDone OnRequestDone = {read=FOnRequestDone, write=FOnRequestDone};
	__property TNntpDisplay OnDisplay = {read=FOnDisplay, write=FOnDisplay};
	__property Classes::TNotifyEvent OnMessageBegin = {read=FOnMessageBegin, write=FOnMessageBegin};
	__property Classes::TNotifyEvent OnMessageEnd = {read=FOnMessageEnd, write=FOnMessageEnd};
	__property Classes::TNotifyEvent OnMessageLine = {read=FOnMessageLine, write=FOnMessageLine};
	__property Classes::TNotifyEvent OnXHdrBegin = {read=FOnXHdrBegin, write=FOnXHdrBegin};
	__property Classes::TNotifyEvent OnXHdrEnd = {read=FOnXHdrEnd, write=FOnXHdrEnd};
	__property Classes::TNotifyEvent OnXHdrLine = {read=FOnXHdrLine, write=FOnXHdrLine};
	__property Classes::TNotifyEvent OnStateChange = {read=FOnStateChange, write=FOnStateChange};
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint NntpCliVersion = 0x6c;
extern PACKAGE AnsiString CopyRight;
static const Word NNTP_RCV_BUF_SIZE = 0x1000;
static const Word WM_NNTP_REQUEST_DONE = 0x401;
extern PACKAGE void __fastcall Register(void);
extern PACKAGE void __fastcall ParseListLine(const AnsiString Line, AnsiString &NewsGroupName, int &LastArticle, int &FirstArticle, char &PostingFlag);

}	/* namespace Nntpcli */
using namespace Nntpcli;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// NntpCli
