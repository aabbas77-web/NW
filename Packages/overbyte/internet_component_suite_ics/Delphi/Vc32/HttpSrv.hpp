// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'HttpSrv.pas' rev: 6.00

#ifndef HttpSrvHPP
#define HttpSrvHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <WSocketS.hpp>	// Pascal unit
#include <WSocket.hpp>	// Pascal unit
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

namespace Httpsrv
{
//-- type declarations -------------------------------------------------------
typedef TMetaClass*THttpConnectionClass;

#pragma option push -b-
enum THttpGetFlag { hgSendDoc, hgSendStream, hgWillSendMySelf, hg404, hgAcceptData };
#pragma option pop

#pragma option push -b-
enum THttpSendType { httpSendHead, httpSendDoc };
#pragma option pop

typedef void __fastcall (__closure *THttpGetEvent)(System::TObject* Sender, System::TObject* Client, THttpGetFlag &Flags);

typedef void __fastcall (__closure *THttpGetConnEvent)(System::TObject* Sender, THttpGetFlag &Flags);

typedef void __fastcall (__closure *THttpConnectEvent)(System::TObject* Sender, System::TObject* Client, Word Error);

typedef void __fastcall (__closure *THttpPostedDataEvent)(System::TObject* Sender, System::TObject* Client, Word Error);

#pragma option push -b-
enum THttpConnectionState { hcRequest, hcHeader, hcPostedData };
#pragma option pop

class DELPHICLASS THttpConnection;
class PASCALIMPLEMENTATION THttpConnection : public Wsockets::TWSocketClient 
{
	typedef Wsockets::TWSocketClient inherited;
	
public:
	AnsiString FRcvdLine;
	AnsiString FMethod;
	AnsiString FVersion;
	AnsiString FPath;
	AnsiString FParams;
	Classes::TStringList* FRequestHeader;
	THttpConnectionState FState;
	AnsiString FDocDir;
	AnsiString FDefaultDoc;
	AnsiString FDocument;
	Classes::TStream* FDocStream;
	char *FDocBuf;
	System::TDateTime FLastModified;
	AnsiString FAnswerContentType;
	int FRequestContentLength;
	AnsiString FRequestContentType;
	AnsiString FRequestAccept;
	AnsiString FRequestReferer;
	AnsiString FRequestAcceptLanguage;
	AnsiString FRequestAcceptEncoding;
	AnsiString FRequestUserAgent;
	AnsiString FRequestHost;
	AnsiString FRequestConnection;
	bool FAcceptPostedData;
	THttpGetConnEvent FOnGetDocument;
	THttpGetConnEvent FOnHeadDocument;
	THttpGetConnEvent FOnPostDocument;
	Wsocket::TDataAvailable FOnPostedData;
	void __fastcall ConnectionDataAvailable(System::TObject* Sender, Word Error);
	void __fastcall ConnectionDataSent(System::TObject* Sender, Word Error);
	void __fastcall ParseRequest(void);
	void __fastcall ProcessRequest(void);
	void __fastcall ProcessGet(void);
	void __fastcall ProcessHead(void);
	void __fastcall ProcessPost(void);
	void __fastcall SendDocument(THttpSendType SendType);
	void __fastcall SendStream(void);
	void __fastcall Answer404(void);
	virtual void __fastcall WndProc(Messages::TMessage &MsgRec);
	MESSAGE void __fastcall WMHttpDone(Messages::TMessage &msg);
	virtual void __fastcall TriggerGetDocument(THttpGetFlag &Flags);
	virtual void __fastcall TriggerHeadDocument(THttpGetFlag &Flags);
	virtual void __fastcall TriggerPostDocument(THttpGetFlag &Flags);
	__fastcall virtual THttpConnection(Classes::TComponent* AOwner);
	__fastcall virtual ~THttpConnection(void);
	__property AnsiString Method = {read=FMethod};
	__property AnsiString Version = {read=FVersion};
	__property Classes::TStringList* RequestHeader = {read=FRequestHeader};
	__property Classes::TStream* DocStream = {read=FDocStream, write=FDocStream};
	__property int RequestContentLength = {read=FRequestContentLength, nodefault};
	__property AnsiString RequestContentType = {read=FRequestContentType};
	__property AnsiString RequestAccept = {read=FRequestAccept};
	__property AnsiString RequestReferer = {read=FRequestReferer};
	__property AnsiString RequestAcceptLanguage = {read=FRequestAcceptLanguage};
	__property AnsiString RequestAcceptEncoding = {read=FRequestAcceptEncoding};
	__property AnsiString RequestUserAgent = {read=FRequestUserAgent};
	__property AnsiString RequestHost = {read=FRequestHost};
	__property AnsiString RequestConnection = {read=FRequestConnection};
	
__published:
	__property AnsiString DocDir = {read=FDocDir, write=FDocDir};
	__property AnsiString DefaultDoc = {read=FDefaultDoc, write=FDefaultDoc};
	__property AnsiString Document = {read=FDocument, write=FDocument};
	__property AnsiString Path = {read=FPath, write=FPath};
	__property AnsiString Params = {read=FParams, write=FParams};
	__property THttpGetConnEvent OnGetDocument = {read=FOnGetDocument, write=FOnGetDocument};
	__property THttpGetConnEvent OnHeadDocument = {read=FOnHeadDocument, write=FOnHeadDocument};
	__property THttpGetConnEvent OnPostDocument = {read=FOnPostDocument, write=FOnPostDocument};
	__property Wsocket::TDataAvailable OnPostedData = {read=FOnPostedData, write=FOnPostedData};
};


class DELPHICLASS THttpServer;
class PASCALIMPLEMENTATION THttpServer : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
protected:
	Wsockets::TWSocketServer* FWSocketServer;
	AnsiString FPort;
	AnsiString FAddr;
	TMetaClass*FClientClass;
	AnsiString FDocDir;
	AnsiString FDefaultDoc;
	Wsocket::TSocketLingerOnOff FLingerOnOff;
	int FLingerTimeout;
	Classes::TNotifyEvent FOnServerStarted;
	Classes::TNotifyEvent FOnServerStopped;
	THttpConnectEvent FOnClientConnect;
	THttpConnectEvent FOnClientDisconnect;
	THttpGetEvent FOnGetDocument;
	THttpGetEvent FOnHeadDocument;
	THttpGetEvent FOnPostDocument;
	THttpPostedDataEvent FOnPostedData;
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation operation);
	void __fastcall WSocketServerClientConnect(System::TObject* Sender, Wsockets::TWSocketClient* Client, Word Error);
	void __fastcall WSocketServerClientCreate(System::TObject* Sender, Wsockets::TWSocketClient* Client);
	void __fastcall WSocketServerClientDisconnect(System::TObject* Sender, Wsockets::TWSocketClient* Client, Word Error);
	void __fastcall WSocketServerSessionClosed(System::TObject* Sender, Word Error);
	void __fastcall WSocketServerChangeState(System::TObject* Sender, Wsocket::TSocketState OldState, Wsocket::TSocketState NewState);
	virtual void __fastcall TriggerServerStarted(void);
	virtual void __fastcall TriggerServerStopped(void);
	void __fastcall TriggerClientConnect(System::TObject* Client, Word Error);
	void __fastcall TriggerClientDisconnect(System::TObject* Client, Word Error);
	void __fastcall TriggerGetDocument(System::TObject* Sender, THttpGetFlag &Flags);
	void __fastcall TriggerHeadDocument(System::TObject* Sender, THttpGetFlag &Flags);
	virtual void __fastcall TriggerPostDocument(System::TObject* Sender, THttpGetFlag &Flags);
	virtual void __fastcall TriggerPostedData(System::TObject* Sender, Word Error);
	void __fastcall SetPortValue(AnsiString newValue);
	void __fastcall SetAddr(AnsiString newValue);
	int __fastcall GetClientCount(void);
	THttpConnection* __fastcall GetClient(int nIndex);
	
public:
	__fastcall virtual THttpServer(Classes::TComponent* AOwner);
	__fastcall virtual ~THttpServer(void);
	virtual void __fastcall Start(void);
	virtual void __fastcall Stop(void);
	bool __fastcall IsClient(System::TObject* SomeThing);
	__property int ClientCount = {read=GetClientCount, nodefault};
	__property THttpConnection* Client[int nIndex] = {read=GetClient};
	__property TMetaClass* ClientClass = {read=FClientClass, write=FClientClass};
	
__published:
	__property AnsiString Port = {read=FPort, write=SetPortValue};
	__property AnsiString Addr = {read=FAddr, write=SetAddr};
	__property AnsiString DocDir = {read=FDocDir, write=FDocDir};
	__property AnsiString DefaultDoc = {read=FDefaultDoc, write=FDefaultDoc};
	__property Wsocket::TSocketLingerOnOff LingerOnOff = {read=FLingerOnOff, write=FLingerOnOff, nodefault};
	__property int LingerTimeout = {read=FLingerTimeout, write=FLingerTimeout, nodefault};
	__property Classes::TNotifyEvent OnServerStarted = {read=FOnServerStarted, write=FOnServerStarted};
	__property Classes::TNotifyEvent OnServerStopped = {read=FOnServerStopped, write=FOnServerStopped};
	__property THttpConnectEvent OnClientConnect = {read=FOnClientConnect, write=FOnClientConnect};
	__property THttpConnectEvent OnClientDisconnect = {read=FOnClientDisconnect, write=FOnClientDisconnect};
	__property THttpGetEvent OnGetDocument = {read=FOnGetDocument, write=FOnGetDocument};
	__property THttpGetEvent OnHeadDocument = {read=FOnHeadDocument, write=FOnHeadDocument};
	__property THttpGetEvent OnPostDocument = {read=FOnPostDocument, write=FOnPostDocument};
	__property THttpPostedDataEvent OnPostedData = {read=FOnPostedData, write=FOnPostedData};
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint THttpServerVersion = 0x67;
extern PACKAGE AnsiString CopyRight;
static const Word WM_HTTP_DONE = 0x428;
extern PACKAGE void __fastcall Register(void);
extern PACKAGE bool __fastcall ExtractURLEncodedValue(char * Msg, AnsiString Name, AnsiString &Value);
extern PACKAGE AnsiString __fastcall UrlDecode(const AnsiString Url);

}	/* namespace Httpsrv */
using namespace Httpsrv;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// HttpSrv
