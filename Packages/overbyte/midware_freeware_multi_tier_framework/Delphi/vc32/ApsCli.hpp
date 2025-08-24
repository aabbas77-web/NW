// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ApsCli.pas' rev: 6.00

#ifndef ApsCliHPP
#define ApsCliHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <RFormat.hpp>	// Pascal unit
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

namespace Apscli
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TErrorEvent)(System::TObject* Sender, int Error, AnsiString Msg);

typedef void __fastcall (__closure *TRequestDone)(System::TObject* Sender, int Error);

typedef void __fastcall (__closure *TProcessReplyEvent)(System::TObject* Sender, char * &CmdBuf, int &CmdLen);

typedef void __fastcall (__closure *TProcessBannerEvent)(System::TObject* Sender, char * CmdBuf, int CmdLen, bool &BannerOk);

typedef void __fastcall (__closure *TConnectionRetryEvent)(System::TObject* Sender, int Error);

#pragma option push -b-
enum TClientState { cstReady, cstDnsLookup, cstConnecting, cstWaitingResponse };
#pragma option pop

class DELPHICLASS AppSrvClientException;
class PASCALIMPLEMENTATION AppSrvClientException : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall AppSrvClientException(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall AppSrvClientException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall AppSrvClientException(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall AppSrvClientException(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall AppSrvClientException(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall AppSrvClientException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall AppSrvClientException(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall AppSrvClientException(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~AppSrvClientException(void) { }
	#pragma option pop
	
};


class DELPHICLASS TAppSrvClient;
class PASCALIMPLEMENTATION TAppSrvClient : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
protected:
	AnsiString FFunctionCode;
	Wsocket::TWSocket* FWSocket;
	AnsiString FPort;
	AnsiString FServer;
	AnsiString FServerIP;
	AnsiString FSocksServer;
	AnsiString FSocksPort;
	AnsiString FSocksUsercode;
	AnsiString FSocksPassword;
	Wsocket::TSocksAuthentication FSocksAuthentication;
	Rformat::TMWBuffer* FRequest;
	Rformat::TMWBuffer* FAnswer;
	AnsiString FAnswerStatus;
	TClientState FState;
	char *FRcvBuf;
	int FRcvCnt;
	int FRcvSize;
	bool FBannerRcvd;
	HWND FHandle;
	char *FRequestHeader;
	int FRequestHeaderLen;
	char *FRequestBody;
	int FRequestBodyLen;
	bool FRetrying;
	int FRetryCount;
	int FMaxRetries;
	TErrorEvent FOnError;
	TRequestDone FOnRequestDone;
	Wsocket::TSessionConnected FOnSessionConnected;
	Wsocket::TSessionClosed FOnSessionClosed;
	TProcessReplyEvent FOnBeforeProcessReply;
	TProcessReplyEvent FOnAfterProcessReply;
	Classes::TNotifyEvent FOnBeforeSendRequest;
	Classes::TNotifyEvent FOnAfterSendRequest;
	TProcessBannerEvent FOnBannerRcvd;
	Wsocket::TSocksErrorEvent FOnSocksError;
	Wsocket::TSessionConnected FOnSocksConnected;
	Wsocket::TSocksAuthStateEvent FOnSocksAuthState;
	TConnectionRetryEvent FOnConnectionRetry;
	void __fastcall WndProc(Messages::TMessage &MsgRec);
	void __fastcall WMRetry(Messages::TMessage &MsgRec);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	virtual void __fastcall SessionConnected(System::TObject* Sender, Word Error);
	virtual void __fastcall SessionClosed(System::TObject* Sender, Word Error);
	virtual void __fastcall DnsLookupDone(System::TObject* Sender, Word Error);
	virtual void __fastcall DataAvailable(System::TObject* Sender, Word Error);
	virtual void __fastcall SocksConnected(System::TObject* Sender, Word Error);
	virtual void __fastcall SocksError(System::TObject* Sender, int Error, AnsiString Msg);
	virtual void __fastcall SocksAuthState(System::TObject* Sender, Wsocket::TSocksAuthState AuthState);
	virtual void __fastcall TriggerError(Word Error, AnsiString Msg);
	virtual void __fastcall TriggerRequestDone(Word Error);
	virtual void __fastcall TriggerBeforeSendRequest(void);
	virtual void __fastcall TriggerAfterSendRequest(void);
	virtual void __fastcall TriggerBannerRcvd(char * CmdBuf, int CmdLen, bool &BannerOk);
	virtual void __fastcall TriggerBeforeProcessReply(char * &CmdBuf, int &CmdLen);
	virtual void __fastcall TriggerAfterProcessReply(char * CmdBuf, int CmdLen);
	void __fastcall TriggerConnectionRetry(Word Error);
	virtual void __fastcall ProcessLine(char * CmdBuf, int CmdLen);
	virtual void __fastcall SendRequest(void);
	virtual void __fastcall CrackHeader(char * AnsBuffer, int AnsLength, AnsiString &AnswerStatus, char * &ParamPtr, int &ParamLen);
	virtual bool __fastcall GetConnected(void);
	virtual void __fastcall SetSocksPort(AnsiString newValue);
	virtual void __fastcall SetRequest(Rformat::TMWBuffer* NewValue);
	
public:
	__fastcall virtual TAppSrvClient(Classes::TComponent* AOwner);
	__fastcall virtual ~TAppSrvClient(void);
	virtual void __fastcall Send(void);
	virtual void __fastcall Close(void);
	void __fastcall CreateRequestMWBuffer(void);
	__property Wsocket::TWSocket* WSocket = {read=FWSocket};
	__property Rformat::TMWBuffer* Request = {read=FRequest, write=SetRequest};
	__property AnsiString AnswerStatus = {read=FAnswerStatus};
	__property HWND Handle = {read=FHandle, nodefault};
	__property bool Connected = {read=GetConnected, nodefault};
	__property TClientState State = {read=FState, nodefault};
	__property char * RequestHeader = {read=FRequestHeader, write=FRequestHeader};
	__property int RequestHeaderLen = {read=FRequestHeaderLen, write=FRequestHeaderLen, nodefault};
	__property char * RequestBody = {read=FRequestBody, write=FRequestBody};
	__property int RequestBodyLen = {read=FRequestBodyLen, write=FRequestBodyLen, nodefault};
	
__published:
	__property AnsiString FunctionCode = {read=FFunctionCode, write=FFunctionCode};
	__property AnsiString Server = {read=FServer, write=FServer};
	__property AnsiString Port = {read=FPort, write=FPort};
	__property AnsiString SocksServer = {read=FSocksServer, write=FSocksServer};
	__property AnsiString SocksPort = {read=FSocksPort, write=SetSocksPort};
	__property AnsiString SocksUsercode = {read=FSocksUsercode, write=FSocksUsercode};
	__property AnsiString SocksPassword = {read=FSocksPassword, write=FSocksPassword};
	__property Wsocket::TSocksAuthentication SocksAuthentication = {read=FSocksAuthentication, write=FSocksAuthentication, nodefault};
	__property Rformat::TMWBuffer* Answer = {read=FAnswer, write=FAnswer};
	__property int MaxRetries = {read=FMaxRetries, write=FMaxRetries, nodefault};
	__property TRequestDone OnRequestDone = {read=FOnRequestDone, write=FOnRequestDone};
	__property Wsocket::TSessionConnected OnSessionConnected = {read=FOnSessionConnected, write=FOnSessionConnected};
	__property Wsocket::TSessionConnected OnSocksConnected = {read=FOnSocksConnected, write=FOnSocksConnected};
	__property Wsocket::TSocksErrorEvent OnSocksError = {read=FOnSocksError, write=FOnSocksError};
	__property Wsocket::TSocksAuthStateEvent OnSocksAuthState = {read=FOnSocksAuthState, write=FOnSocksAuthState};
	__property Wsocket::TSessionClosed OnSessionClosed = {read=FOnSessionClosed, write=FOnSessionClosed};
	__property TProcessReplyEvent OnBeforeProcessReply = {read=FOnBeforeProcessReply, write=FOnBeforeProcessReply};
	__property TProcessReplyEvent OnAfterProcessReply = {read=FOnAfterProcessReply, write=FOnAfterProcessReply};
	__property Classes::TNotifyEvent OnBeforeSendRequest = {read=FOnBeforeSendRequest, write=FOnBeforeSendRequest};
	__property Classes::TNotifyEvent OnAfterSendRequest = {read=FOnAfterSendRequest, write=FOnAfterSendRequest};
	__property TProcessBannerEvent OnBannerRcvd = {read=FOnBannerRcvd, write=FOnBannerRcvd};
	__property TConnectionRetryEvent OnConnectionRetry = {read=FOnConnectionRetry, write=FOnConnectionRetry};
};


//-- var, const, procedure ---------------------------------------------------
static const Byte AppSrvClientVersion = 0xcb;
extern PACKAGE AnsiString CopyRight;
static const Word WM_REQUESTDONE = 0x401;
static const Word WM_RETRY = 0x402;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Apscli */
using namespace Apscli;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ApsCli
