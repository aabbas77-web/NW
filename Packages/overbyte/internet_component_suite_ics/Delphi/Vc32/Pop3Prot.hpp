// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Pop3Prot.pas' rev: 6.00

#ifndef Pop3ProtHPP
#define Pop3ProtHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <MD5.hpp>	// Pascal unit
#include <WinSock.hpp>	// Pascal unit
#include <WSocket.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Pop3prot
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS Pop3Exception;
class PASCALIMPLEMENTATION Pop3Exception : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall Pop3Exception(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall Pop3Exception(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall Pop3Exception(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall Pop3Exception(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall Pop3Exception(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall Pop3Exception(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall Pop3Exception(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall Pop3Exception(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~Pop3Exception(void) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TPop3Display)(System::TObject* Sender, AnsiString Msg);

#pragma option push -b-
enum TPop3ProtocolState { pop3Disconnected, pop3WaitingUser, pop3WaitingPass, pop3Transaction };
#pragma option pop

#pragma option push -b-
enum TPop3State { pop3Ready, pop3DnsLookup, pop3Connecting, pop3Connected, pop3InternalReady, pop3WaitingBanner, pop3WaitingResponse, pop3Abort };
#pragma option pop

#pragma option push -b-
enum TPop3Request { pop3Connect, pop3User, pop3Pass, pop3RPop, pop3Quit, pop3Stat, pop3List, pop3Retr, pop3Top, pop3Dele, pop3Noop, pop3Last, pop3RSet, pop3Uidl, pop3APop, pop3Open, pop3Custom };
#pragma option pop

#pragma option push -b-
enum TPop3Fct { pop3FctNone, pop3FctConnect, pop3FctUser, pop3FctPass, pop3FctRPop, pop3FctQuit, pop3FctAPop, pop3FctStat, pop3FctList, pop3FctUidl, pop3FctRetr, pop3FctTop, pop3FctDele, pop3FctNoop, pop3FctRSet, pop3FctLast };
#pragma option pop

typedef Set<TPop3Fct, pop3FctNone, pop3FctLast>  TPop3FctSet;

typedef void __fastcall (__closure *TPop3NextProc)(void);

typedef void __fastcall (__closure *TPop3RequestDone)(System::TObject* Sender, TPop3Request RqType, Word Error);

typedef bool __fastcall (__closure *TPop3Method)(void);

class DELPHICLASS TCustomPop3Cli;
class PASCALIMPLEMENTATION TCustomPop3Cli : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	Wsocket::TWSocket* FWSocket;
	HWND FWindowHandle;
	TPop3State FState;
	TPop3ProtocolState FNextProtocolState;
	TPop3ProtocolState FProtocolState;
	bool FConnected;
	TPop3Request FRequestType;
	bool FRequestDoneFlag;
	int FReceiveLen;
	int FRequestResult;
	int FStatusCode;
	char FReceiveBuffer[4096];
	TPop3NextProc FNext;
	TPop3NextProc FWhenConnected;
	TPop3FctSet FFctSet;
	TPop3Fct FFctPrv;
	int FHighLevelResult;
	bool FHighLevelFlag;
	TPop3NextProc FNextRequest;
	AnsiString FLastResponseSave;
	int FStatusCodeSave;
	bool FRestartFlag;
	TPop3NextProc FDoneAsync;
	Classes::TNotifyEvent FMultiLineLine;
	Classes::TNotifyEvent FMultiLineEnd;
	Classes::TNotifyEvent FMultiLineProcess;
	AnsiString FHost;
	AnsiString FLocalAddr;
	AnsiString FPort;
	AnsiString FUserName;
	AnsiString FPassWord;
	AnsiString FLastResponse;
	AnsiString FErrorMessage;
	AnsiString FTimeStamp;
	int FMsgCount;
	int FMsgSize;
	int FMsgNum;
	AnsiString FMsgUidl;
	int FMsgLines;
	int FTag;
	bool FWaitingOnQuit;
	TPop3Display FOnDisplay;
	Classes::TNotifyEvent FOnMessageBegin;
	Classes::TNotifyEvent FOnMessageEnd;
	Classes::TNotifyEvent FOnMessageLine;
	Classes::TNotifyEvent FOnListBegin;
	Classes::TNotifyEvent FOnListEnd;
	Classes::TNotifyEvent FOnListLine;
	Classes::TNotifyEvent FOnUidlBegin;
	Classes::TNotifyEvent FOnUidlEnd;
	Classes::TNotifyEvent FOnUidlLine;
	Classes::TNotifyEvent FOnStateChange;
	TPop3RequestDone FOnRequestDone;
	TPop3Display FOnResponse;
	Wsocket::TSessionConnected FOnSessionConnected;
	Wsocket::TSessionClosed FOnSessionClosed;
	
protected:
	void __fastcall ExecAsync(TPop3Request RqType, AnsiString Cmd, TPop3ProtocolState NextState, TPop3NextProc DoneAsync);
	void __fastcall NextExecAsync(void);
	void __fastcall StartTransaction(AnsiString OpCode, AnsiString Params, TPop3Request RqType, TPop3ProtocolState NextState, TPop3NextProc DoneTrans);
	void __fastcall StartMultiLine(Classes::TNotifyEvent aOnBegin, Classes::TNotifyEvent aOnLine, Classes::TNotifyEvent aOnEnd, Classes::TNotifyEvent aProcess);
	void __fastcall GetALine(void);
	void __fastcall StatDone(void);
	void __fastcall ListAllDone(void);
	void __fastcall ListSingleDone(void);
	void __fastcall UidlAllDone(void);
	void __fastcall UidlSingleDone(void);
	void __fastcall RetrDone(void);
	void __fastcall LastDone(void);
	virtual void __fastcall WndProc(Messages::TMessage &MsgRec);
	MESSAGE void __fastcall WMPop3RequestDone(Messages::TMessage &msg);
	void __fastcall WSocketDnsLookupDone(System::TObject* Sender, Word Error);
	void __fastcall WSocketSessionConnected(System::TObject* Sender, Word Error);
	void __fastcall WSocketDataAvailable(System::TObject* Sender, Word Error);
	void __fastcall WSocketSessionClosed(System::TObject* Sender, Word Error);
	void __fastcall DisplayLastResponse(void);
	void __fastcall TriggerDisplay(AnsiString Msg);
	virtual void __fastcall TriggerSessionConnected(Word Error);
	void __fastcall TriggerSessionClosed(Word Error);
	virtual void __fastcall TriggerResponse(AnsiString Msg);
	virtual void __fastcall TriggerStateChange(void);
	virtual void __fastcall TriggerRequestDone(Word Error);
	bool __fastcall OkResponse(void);
	void __fastcall StateChange(TPop3State NewState);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	void __fastcall SetErrorMessage(void);
	void __fastcall Display(AnsiString Msg);
	void __fastcall SendCommand(AnsiString Cmd);
	bool __fastcall ExtractNumbers(int &N1, int &N2);
	bool __fastcall ExtractUidl(int &N1, AnsiString &N2);
	void __fastcall ProcessUidl(System::TObject* Sender);
	void __fastcall ProcessList(System::TObject* Sender);
	void __fastcall CheckReady(void);
	void __fastcall DoHighLevelAsync(void);
	
public:
	__fastcall virtual TCustomPop3Cli(Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomPop3Cli(void);
	virtual void __fastcall Connect(void);
	virtual void __fastcall Open(void);
	virtual void __fastcall User(void);
	virtual void __fastcall Pass(void);
	virtual void __fastcall RPop(void);
	virtual void __fastcall APop(void);
	virtual void __fastcall Quit(void);
	virtual void __fastcall Stat(void);
	virtual void __fastcall List(void);
	virtual void __fastcall Retr(void);
	virtual void __fastcall Top(void);
	virtual void __fastcall Dele(void);
	virtual void __fastcall Noop(void);
	virtual void __fastcall Last(void);
	virtual void __fastcall RSet(void);
	virtual void __fastcall Uidl(void);
	virtual void __fastcall Abort(void);
	void __fastcall ClearErrorMessage(void);
	void __fastcall HighLevelAsync(TPop3Request RqType, TPop3FctSet Fcts);
	__property Wsocket::TWSocket* CtrlSocket = {read=FWSocket};
	__property AnsiString Host = {read=FHost, write=FHost};
	__property AnsiString LocalAddr = {read=FLocalAddr, write=FLocalAddr};
	__property AnsiString Port = {read=FPort, write=FPort};
	__property AnsiString UserName = {read=FUserName, write=FUserName};
	__property AnsiString PassWord = {read=FPassWord, write=FPassWord};
	__property AnsiString ErrorMessage = {read=FErrorMessage};
	__property AnsiString LastResponse = {read=FLastResponse};
	__property TPop3State State = {read=FState, nodefault};
	__property bool Connected = {read=FConnected, nodefault};
	__property TPop3ProtocolState ProtocolState = {read=FProtocolState, nodefault};
	__property int MsgCount = {read=FMsgCount, nodefault};
	__property int MsgSize = {read=FMsgSize, nodefault};
	__property int MsgLines = {read=FMsgLines, write=FMsgLines, nodefault};
	__property int MsgNum = {read=FMsgNum, write=FMsgNum, nodefault};
	__property AnsiString MsgUidl = {read=FMsgUidl};
	__property int Tag = {read=FTag, write=FTag, nodefault};
	__property HWND Handle = {read=FWindowHandle, nodefault};
	__property TPop3Display OnDisplay = {read=FOnDisplay, write=FOnDisplay};
	__property Classes::TNotifyEvent OnMessageBegin = {read=FOnMessageBegin, write=FOnMessageBegin};
	__property Classes::TNotifyEvent OnMessageEnd = {read=FOnMessageEnd, write=FOnMessageEnd};
	__property Classes::TNotifyEvent OnMessageLine = {read=FOnMessageLine, write=FOnMessageLine};
	__property Classes::TNotifyEvent OnListBegin = {read=FOnListBegin, write=FOnListBegin};
	__property Classes::TNotifyEvent OnListEnd = {read=FOnListEnd, write=FOnListEnd};
	__property Classes::TNotifyEvent OnListLine = {read=FOnListLine, write=FOnListLine};
	__property Classes::TNotifyEvent OnUidlBegin = {read=FOnUidlBegin, write=FOnUidlBegin};
	__property Classes::TNotifyEvent OnUidlEnd = {read=FOnUidlEnd, write=FOnUidlEnd};
	__property Classes::TNotifyEvent OnUidlLine = {read=FOnUidlLine, write=FOnUidlLine};
	__property Classes::TNotifyEvent OnStateChange = {read=FOnStateChange, write=FOnStateChange};
	__property TPop3RequestDone OnRequestDone = {read=FOnRequestDone, write=FOnRequestDone};
	__property TPop3Display OnResponse = {read=FOnResponse, write=FOnResponse};
	__property Wsocket::TSessionConnected OnSessionConnected = {read=FOnSessionConnected, write=FOnSessionConnected};
	__property Wsocket::TSessionClosed OnSessionClosed = {read=FOnSessionClosed, write=FOnSessionClosed};
};


class DELPHICLASS TPop3Cli;
class PASCALIMPLEMENTATION TPop3Cli : public TCustomPop3Cli 
{
	typedef TCustomPop3Cli inherited;
	
__published:
	__property Host ;
	__property LocalAddr ;
	__property Port ;
	__property UserName ;
	__property PassWord ;
	__property ErrorMessage ;
	__property LastResponse ;
	__property ProtocolState ;
	__property MsgCount ;
	__property MsgSize ;
	__property MsgLines ;
	__property MsgNum ;
	__property MsgUidl ;
	__property Tag ;
	__property OnDisplay ;
	__property OnMessageBegin ;
	__property OnMessageEnd ;
	__property OnMessageLine ;
	__property OnListBegin ;
	__property OnListEnd ;
	__property OnListLine ;
	__property OnUidlBegin ;
	__property OnUidlEnd ;
	__property OnUidlLine ;
	__property OnStateChange ;
	__property OnRequestDone ;
	__property OnResponse ;
	__property OnSessionConnected ;
	__property OnSessionClosed ;
public:
	#pragma option push -w-inl
	/* TCustomPop3Cli.Create */ inline __fastcall virtual TPop3Cli(Classes::TComponent* AOwner) : TCustomPop3Cli(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomPop3Cli.Destroy */ inline __fastcall virtual ~TPop3Cli(void) { }
	#pragma option pop
	
};


class DELPHICLASS TSyncPop3Cli;
class PASCALIMPLEMENTATION TSyncPop3Cli : public TPop3Cli 
{
	typedef TPop3Cli inherited;
	
protected:
	int FTimeout;
	int FTimeStop;
	bool FMultiThreaded;
	virtual bool __fastcall WaitUntilReady(void);
	bool __fastcall Synchronize(TPop3NextProc Proc);
	virtual void __fastcall TriggerResponse(AnsiString Msg);
	
public:
	__fastcall virtual TSyncPop3Cli(Classes::TComponent* AOwner);
	virtual bool __fastcall ConnectSync(void);
	virtual bool __fastcall OpenSync(void);
	virtual bool __fastcall UserSync(void);
	virtual bool __fastcall PassSync(void);
	virtual bool __fastcall RPopSync(void);
	virtual bool __fastcall APopSync(void);
	virtual bool __fastcall QuitSync(void);
	virtual bool __fastcall StatSync(void);
	virtual bool __fastcall ListSync(void);
	virtual bool __fastcall RetrSync(void);
	virtual bool __fastcall TopSync(void);
	virtual bool __fastcall DeleSync(void);
	virtual bool __fastcall NoopSync(void);
	virtual bool __fastcall LastSync(void);
	virtual bool __fastcall RSetSync(void);
	virtual bool __fastcall UidlSync(void);
	virtual bool __fastcall AbortSync(void);
	
__published:
	__property int Timeout = {read=FTimeout, write=FTimeout, nodefault};
	__property bool MultiThreaded = {read=FMultiThreaded, write=FMultiThreaded, nodefault};
public:
	#pragma option push -w-inl
	/* TCustomPop3Cli.Destroy */ inline __fastcall virtual ~TSyncPop3Cli(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Byte Pop3CliVersion = 0xd6;
extern PACKAGE AnsiString CopyRight;
static const Word POP3_RCV_BUF_SIZE = 0x1000;
static const Word WM_POP3_REQUEST_DONE = 0x401;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Pop3prot */
using namespace Pop3prot;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Pop3Prot
