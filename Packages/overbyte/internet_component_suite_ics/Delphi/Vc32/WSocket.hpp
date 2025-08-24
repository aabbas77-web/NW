// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'WSocket.pas' rev: 6.00

#ifndef WSocketHPP
#define WSocketHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <WinSock.hpp>	// Pascal unit
#include <WSockBuf.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Wsocket
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TWndMethod)(Messages::TMessage &Message);

class DELPHICLASS ESocketException;
class PASCALIMPLEMENTATION ESocketException : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ESocketException(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ESocketException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ESocketException(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ESocketException(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ESocketException(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ESocketException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ESocketException(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ESocketException(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ESocketException(void) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TBgExceptionEvent)(System::TObject* Sender, Sysutils::Exception* E, bool &CanClose);

#pragma option push -b-
enum TSocketState { wsInvalidState, wsOpened, wsBound, wsConnecting, wsConnected, wsAccepting, wsListening, wsClosed };
#pragma option pop

#pragma option push -b-
enum TSocketSendFlags { wsSendNormal, wsSendUrgent };
#pragma option pop

#pragma option push -b-
enum TSocketLingerOnOff { wsLingerOff, wsLingerOn, wsLingerNoSet };
#pragma option pop

typedef sockaddr_in  TSockAddr;

typedef void __fastcall (__closure *TDataAvailable)(System::TObject* Sender, Word Error);

typedef void __fastcall (__closure *TDataSent)(System::TObject* Sender, Word Error);

typedef void __fastcall (__closure *TSendData)(System::TObject* Sender, int BytesSent);

typedef void __fastcall (__closure *TSessionClosed)(System::TObject* Sender, Word Error);

typedef void __fastcall (__closure *TSessionAvailable)(System::TObject* Sender, Word Error);

typedef void __fastcall (__closure *TSessionConnected)(System::TObject* Sender, Word Error);

typedef void __fastcall (__closure *TDnsLookupDone)(System::TObject* Sender, Word Error);

typedef void __fastcall (__closure *TChangeState)(System::TObject* Sender, TSocketState OldState, TSocketState NewState);

typedef void __fastcall (__closure *TDebugDisplay)(System::TObject* Sender, AnsiString &Msg);

typedef void __fastcall (__closure *TWSocketSyncNextProc)(void);

#pragma option push -b-
enum TWSocketOption { wsoNoReceiveLoop, wsoTcpNoDelay };
#pragma option pop

typedef Set<TWSocketOption, wsoNoReceiveLoop, wsoTcpNoDelay>  TWSocketOptions;

typedef int TSocket;

class DELPHICLASS TCustomWSocket;
class PASCALIMPLEMENTATION TCustomWSocket : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	AnsiString FDnsResult;
	Classes::TStrings* FDnsResultList;
	int FASocket;
	Classes::TList* FBufList;
	int FBufSize;
	int FSendFlags;
	int FLastError;
	HWND FWindowHandle;
	char FDnsLookupBuffer[1025];
	unsigned FDnsLookupHandle;
	bool FDnsLookupCheckMsg;
	#pragma pack(push, 1)
	Messages::TMessage FDnsLookupTempMsg;
	#pragma pack(pop)
	
	
protected:
	int FHSocket;
	AnsiString FAddrStr;
	bool FAddrResolved;
	int FAddrFormat;
	bool FAddrAssigned;
	int FProto;
	bool FProtoAssigned;
	bool FProtoResolved;
	bool FLocalPortResolved;
	AnsiString FProtoStr;
	AnsiString FPortStr;
	bool FPortAssigned;
	bool FPortResolved;
	int FPortNum;
	AnsiString FLocalPortStr;
	int FLocalPortNum;
	AnsiString FLocalAddr;
	int FType;
	TSocketLingerOnOff FLingerOnOff;
	int FLingerTimeout;
	int ReadLineCount;
	bool bAllSent;
	int FReadCount;
	bool FPaused;
	bool FCloseInvoked;
	int FFlushTimeout;
	bool FMultiThreaded;
	bool FMultiCast;
	AnsiString FMultiCastAddrStr;
	int FMultiCastIpTTL;
	bool FReuseAddr;
	TWSocketOptions FComponentOptions;
	TSocketState FState;
	bool FRcvdFlag;
	bool FTerminated;
	int FSelectEvent;
	TSessionAvailable FOnSessionAvailable;
	TSessionConnected FOnSessionConnected;
	TSessionClosed FOnSessionClosed;
	TChangeState FOnChangeState;
	TDataAvailable FOnDataAvailable;
	TDataSent FOnDataSent;
	TSendData FOnSendData;
	Classes::TNotifyEvent FOnLineTooLong;
	TDnsLookupDone FOnDnsLookupDone;
	Classes::TNotifyEvent FOnError;
	TBgExceptionEvent FOnBgException;
	TDebugDisplay FOnDisplay;
	Classes::TNotifyEvent FOnMessagePump;
	virtual void __fastcall WndProc(Messages::TMessage &MsgRec);
	virtual void __fastcall AllocateSocketHWnd(void);
	virtual void __fastcall DeallocateSocketHWnd(void);
	void __fastcall SocketError(AnsiString sockfunc);
	MESSAGE void __fastcall WMASyncSelect(Messages::TMessage &msg);
	MESSAGE void __fastcall WMAsyncGetHostByName(Messages::TMessage &msg);
	MESSAGE void __fastcall WMAsyncGetHostByAddr(Messages::TMessage &msg);
	MESSAGE void __fastcall WMCloseDelayed(Messages::TMessage &msg);
	MESSAGE void __fastcall WMRelease(Messages::TMessage &msg);
	void __fastcall ChangeState(TSocketState NewState);
	void __fastcall TryToSend(void);
	void __fastcall ASyncReceive(Word Error, TWSocketOptions MySocketOptions);
	virtual void __fastcall AssignDefaultValue(void);
	virtual void __fastcall InternalClose(bool bShut, Word Error);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation operation);
	void __fastcall SetSendFlags(TSocketSendFlags newValue);
	TSocketSendFlags __fastcall GetSendFlags(void);
	void __fastcall SetAddr(AnsiString InAddr);
	AnsiString __fastcall GetAddr();
	virtual void __fastcall SetRemotePort(AnsiString sPort);
	AnsiString __fastcall GetRemotePort();
	void __fastcall SetLocalAddr(AnsiString sLocalAddr);
	void __fastcall SetLocalPort(AnsiString sLocalPort);
	virtual void __fastcall SetProto(AnsiString sProto);
	AnsiString __fastcall GetProto();
	virtual int __fastcall GetRcvdCount(void);
	virtual void __fastcall BindSocket(void);
	void __fastcall SendText(AnsiString Str);
	virtual int __fastcall RealSend(void * Data, int Len);
	virtual void __fastcall RaiseExceptionFmt(const AnsiString Fmt, const System::TVarRec * args, const int args_Size);
	virtual void __fastcall RaiseException(const AnsiString Msg);
	virtual void __fastcall HandleBackGroundException(Sysutils::Exception* E);
	void __fastcall TriggerDisplay(AnsiString Msg);
	void __fastcall TriggerSendData(int BytesSent);
	virtual bool __fastcall TriggerDataAvailable(Word Error);
	virtual void __fastcall TriggerSessionAvailable(Word Error);
	virtual void __fastcall TriggerSessionConnected(Word Error);
	virtual void __fastcall TriggerSessionClosed(Word Error);
	virtual void __fastcall TriggerDataSent(Word Error);
	virtual void __fastcall TriggerChangeState(TSocketState OldState, TSocketState NewState);
	virtual void __fastcall TriggerDNSLookupDone(Word Error);
	virtual void __fastcall TriggerError(void);
	virtual int __fastcall DoRecv(void *Buffer, int BufferSize, int Flags);
	virtual int __fastcall DoRecvFrom(int FHSocket, void *Buffer, int BufferSize, int Flags, sockaddr_in &From, int &FromLen);
	
public:
	sockaddr_in sin;
	__fastcall virtual TCustomWSocket(Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomWSocket(void);
	virtual void __fastcall Connect(void);
	virtual void __fastcall Close(void);
	virtual void __fastcall CloseDelayed(void);
	virtual void __fastcall Release(void);
	virtual void __fastcall Abort(void);
	virtual void __fastcall Flush(void);
	virtual void __fastcall WaitForClose(void);
	virtual void __fastcall Listen(void);
	virtual int __fastcall Accept(void);
	virtual int __fastcall Receive(void * Buffer, int BufferSize);
	virtual AnsiString __fastcall ReceiveStr();
	virtual int __fastcall ReceiveFrom(void * Buffer, int BufferSize, sockaddr_in &From, int &FromLen);
	int __fastcall PeekData(void * Buffer, int BufferSize);
	virtual int __fastcall Send(void * Data, int Len);
	virtual int __fastcall SendTo(const sockaddr_in &Dest, int DestLen, void * Data, int Len);
	virtual int __fastcall SendStr(AnsiString Str);
	virtual void __fastcall DnsLookup(AnsiString HostName);
	virtual void __fastcall ReverseDnsLookup(AnsiString HostAddr);
	virtual void __fastcall CancelDnsLookup(void);
	virtual AnsiString __fastcall GetPeerAddr();
	virtual AnsiString __fastcall GetPeerPort();
	virtual int __fastcall GetPeerName(sockaddr_in &Name, int NameLen);
	virtual AnsiString __fastcall GetXPort();
	virtual AnsiString __fastcall GetXAddr();
	virtual bool __fastcall TimerIsSet(timeval &tvp);
	virtual void __fastcall TimerClear(timeval &tvp);
	virtual bool __fastcall TimerCmp(timeval &tvp, timeval &uvp, bool IsEqual);
	virtual int __fastcall GetSockName(sockaddr_in &saddr, int &saddrlen);
	void __fastcall SetLingerOption(void);
	virtual void __fastcall Dup(int NewHSocket);
	virtual void __fastcall Shutdown(int How);
	virtual void __fastcall Pause(void);
	virtual void __fastcall Resume(void);
	void __fastcall PutDataInSendBuffer(void * Data, int Len);
	void __fastcall PutStringInSendBuffer(AnsiString Str);
	void __fastcall DeleteBufferedData(void);
	void __fastcall ThreadAttach(void);
	virtual void __fastcall MessagePump(void);
	void __fastcall MessageLoop(void);
	bool __fastcall ProcessMessage(void);
	void __fastcall ProcessMessages(void);
	
protected:
	__property int PortNum = {read=FPortNum, nodefault};
	__property HWND Handle = {read=FWindowHandle, nodefault};
	__property int HSocket = {read=FHSocket, write=Dup, nodefault};
	__property AnsiString Addr = {read=GetAddr, write=SetAddr};
	__property AnsiString Port = {read=GetRemotePort, write=SetRemotePort};
	__property AnsiString LocalPort = {read=FLocalPortStr, write=SetLocalPort};
	__property AnsiString LocalAddr = {read=FLocalAddr, write=SetLocalAddr};
	__property AnsiString Proto = {read=GetProto, write=SetProto};
	__property bool MultiThreaded = {read=FMultiThreaded, write=FMultiThreaded, nodefault};
	__property bool MultiCast = {read=FMultiCast, write=FMultiCast, nodefault};
	__property AnsiString MultiCastAddrStr = {read=FMultiCastAddrStr, write=FMultiCastAddrStr};
	__property int MultiCastIpTTL = {read=FMultiCastIpTTL, write=FMultiCastIpTTL, nodefault};
	__property bool ReuseAddr = {read=FReuseAddr, write=FReuseAddr, nodefault};
	__property AnsiString PeerAddr = {read=GetPeerAddr};
	__property AnsiString PeerPort = {read=GetPeerPort};
	__property AnsiString DnsResult = {read=FDnsResult};
	__property Classes::TStrings* DnsResultList = {read=FDnsResultList};
	__property TSocketState State = {read=FState, nodefault};
	__property bool AllSent = {read=bAllSent, nodefault};
	__property int ReadCount = {read=FReadCount, nodefault};
	__property int RcvdCount = {read=GetRcvdCount, nodefault};
	__property int LastError = {read=FLastError, nodefault};
	__property TWSocketOptions ComponentOptions = {read=FComponentOptions, write=FComponentOptions, nodefault};
	__property int BufSize = {read=FBufSize, write=FBufSize, nodefault};
	__property TDataAvailable OnDataAvailable = {read=FOnDataAvailable, write=FOnDataAvailable};
	__property TDataSent OnDataSent = {read=FOnDataSent, write=FOnDataSent};
	__property TSendData OnSendData = {read=FOnSendData, write=FOnSendData};
	__property TSessionClosed OnSessionClosed = {read=FOnSessionClosed, write=FOnSessionClosed};
	__property TSessionAvailable OnSessionAvailable = {read=FOnSessionAvailable, write=FOnSessionAvailable};
	__property TSessionConnected OnSessionConnected = {read=FOnSessionConnected, write=FOnSessionConnected};
	__property TChangeState OnChangeState = {read=FOnChangeState, write=FOnChangeState};
	__property Classes::TNotifyEvent OnLineTooLong = {read=FOnLineTooLong, write=FOnLineTooLong};
	__property TDnsLookupDone OnDnsLookupDone = {read=FOnDnsLookupDone, write=FOnDnsLookupDone};
	__property Classes::TNotifyEvent OnError = {read=FOnError, write=FOnError};
	__property TBgExceptionEvent OnBgException = {read=FOnBgException, write=FOnBgException};
	__property int FlushTimeout = {read=FFlushTimeout, write=FFlushTimeout, nodefault};
	__property TSocketSendFlags SendFlags = {read=GetSendFlags, write=SetSendFlags, nodefault};
	__property AnsiString Text = {read=ReceiveStr, write=SendText};
	__property TSocketLingerOnOff LingerOnOff = {read=FLingerOnOff, write=FLingerOnOff, nodefault};
	__property int LingerTimeout = {read=FLingerTimeout, write=FLingerTimeout, nodefault};
	__property TDebugDisplay OnDisplay = {read=FOnDisplay, write=FOnDisplay};
};


#pragma option push -b-
enum TSocksState { socksData, socksNegociateMethods, socksAuthenticate, socksConnect };
#pragma option pop

#pragma option push -b-
enum TSocksAuthentication { socksNoAuthentication, socksAuthenticateUsercode };
#pragma option pop

#pragma option push -b-
enum TSocksAuthState { socksAuthStart, socksAuthSuccess, socksAuthFailure, socksAuthNotRequired };
#pragma option pop

typedef void __fastcall (__closure *TSocksAuthStateEvent)(System::TObject* Sender, TSocksAuthState AuthState);

typedef void __fastcall (__closure *TSocksErrorEvent)(System::TObject* Sender, int Error, AnsiString Msg);

class DELPHICLASS TCustomSocksWSocket;
class PASCALIMPLEMENTATION TCustomSocksWSocket : public TCustomWSocket 
{
	typedef TCustomWSocket inherited;
	
protected:
	TSocksState FSocksState;
	AnsiString FSocksServer;
	AnsiString FSocksLevel;
	AnsiString FSocksPort;
	bool FSocksPortAssigned;
	bool FSocksServerAssigned;
	AnsiString FSocksUsercode;
	AnsiString FSocksPassword;
	TSocksAuthentication FSocksAuthentication;
	char FSocksAuthNumber;
	AnsiString FBoundAddr;
	AnsiString FBoundPort;
	char FRcvBuf[128];
	int FRcvCnt;
	int FSocksRcvdCnt;
	char *FSocksRcvdPtr;
	TSocksErrorEvent FOnSocksError;
	TSessionConnected FOnSocksConnected;
	TSocksAuthStateEvent FOnSocksAuthState;
	virtual void __fastcall AssignDefaultValue(void);
	virtual void __fastcall TriggerSessionConnected(Word Error);
	virtual void __fastcall TriggerSocksConnected(Word Error);
	virtual void __fastcall TriggerSessionClosed(Word Error);
	virtual bool __fastcall TriggerDataAvailable(Word Error);
	virtual void __fastcall SetSocksPort(AnsiString sPort);
	virtual void __fastcall SetSocksServer(AnsiString sServer);
	virtual void __fastcall TriggerSocksError(int Error, AnsiString Msg);
	void __fastcall TriggerSocksAuthState(TSocksAuthState AuthState);
	virtual int __fastcall GetRcvdCount(void);
	void __fastcall SetSocksLevel(AnsiString newValue);
	virtual int __fastcall DoRecv(void *Buffer, int BufferSize, int Flags);
	void __fastcall SocksDoConnect(void);
	void __fastcall SocksDoAuthenticate(void);
	void __fastcall DataAvailableError(int ErrCode, AnsiString Msg);
	
public:
	virtual void __fastcall Connect(void);
	virtual void __fastcall Listen(void);
	
protected:
	__property AnsiString SocksServer = {read=FSocksServer, write=SetSocksServer};
	__property AnsiString SocksLevel = {read=FSocksLevel, write=SetSocksLevel};
	__property AnsiString SocksPort = {read=FSocksPort, write=SetSocksPort};
	__property AnsiString SocksUsercode = {read=FSocksUsercode, write=FSocksUsercode};
	__property AnsiString SocksPassword = {read=FSocksPassword, write=FSocksPassword};
	__property TSocksAuthentication SocksAuthentication = {read=FSocksAuthentication, write=FSocksAuthentication, nodefault};
	__property TSocksErrorEvent OnSocksError = {read=FOnSocksError, write=FOnSocksError};
	__property TSessionConnected OnSocksConnected = {read=FOnSocksConnected, write=FOnSocksConnected};
	__property TSocksAuthStateEvent OnSocksAuthState = {read=FOnSocksAuthState, write=FOnSocksAuthState};
public:
	#pragma option push -w-inl
	/* TCustomWSocket.Create */ inline __fastcall virtual TCustomSocksWSocket(Classes::TComponent* AOwner) : TCustomWSocket(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomWSocket.Destroy */ inline __fastcall virtual ~TCustomSocksWSocket(void) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TLineLimitEvent)(System::TObject* Sender, int RcvdLength, bool &ClearData);

class DELPHICLASS TCustomLineWSocket;
class PASCALIMPLEMENTATION TCustomLineWSocket : public TCustomSocksWSocket 
{
	typedef TCustomSocksWSocket inherited;
	
protected:
	char *FRcvdPtr;
	int FRcvBufSize;
	int FRcvdCnt;
	AnsiString FLineEnd;
	bool FLineMode;
	int FLineLength;
	int FLineLimit;
	bool FLineReceivedFlag;
	bool FLineClearData;
	bool FLineEcho;
	bool FLineEdit;
	int FTimeout;
	int FTimeStop;
	TLineLimitEvent FOnLineLimitExceeded;
	virtual void __fastcall WndProc(Messages::TMessage &MsgRec);
	MESSAGE void __fastcall WMTriggerDataAvailable(Messages::TMessage &msg);
	virtual bool __fastcall TriggerDataAvailable(Word Error);
	virtual void __fastcall TriggerSessionClosed(Word Error);
	virtual void __fastcall TriggerLineLimitExceeded(int Cnt, bool &ClearData);
	virtual void __fastcall SetLineMode(bool newValue);
	virtual void __fastcall EditLine(int &Len);
	virtual int __fastcall GetRcvdCount(void);
	virtual int __fastcall DoRecv(void *Buffer, int BufferSize, int Flags);
	
public:
	__fastcall virtual TCustomLineWSocket(Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomLineWSocket(void);
	__property int LineLength = {read=FLineLength, nodefault};
	
__published:
	__property bool LineMode = {read=FLineMode, write=SetLineMode, nodefault};
	__property int LineLimit = {read=FLineLimit, write=FLineLimit, nodefault};
	__property AnsiString LineEnd = {read=FLineEnd, write=FLineEnd};
	__property bool LineEcho = {read=FLineEcho, write=FLineEcho, nodefault};
	__property bool LineEdit = {read=FLineEdit, write=FLineEdit, nodefault};
	__property TLineLimitEvent OnLineLimitExceeded = {read=FOnLineLimitExceeded, write=FOnLineLimitExceeded};
};


class DELPHICLASS TCustomSyncWSocket;
class PASCALIMPLEMENTATION TCustomSyncWSocket : public TCustomLineWSocket 
{
	typedef TCustomLineWSocket inherited;
	
protected:
	AnsiString *FLinePointer;
	virtual int __fastcall Synchronize(TWSocketSyncNextProc Proc, bool &DoneFlag);
	virtual int __fastcall WaitUntilReady(bool &DoneFlag);
	void __fastcall InternalDataAvailable(System::TObject* Sender, Word Error);
	
public:
	void __fastcall ReadLine(int Timeout, AnsiString &Buffer);
public:
	#pragma option push -w-inl
	/* TCustomLineWSocket.Create */ inline __fastcall virtual TCustomSyncWSocket(Classes::TComponent* AOwner) : TCustomLineWSocket(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomLineWSocket.Destroy */ inline __fastcall virtual ~TCustomSyncWSocket(void) { }
	#pragma option pop
	
};


class DELPHICLASS TWSocket;
class PASCALIMPLEMENTATION TWSocket : public TCustomSyncWSocket 
{
	typedef TCustomSyncWSocket inherited;
	
public:
	__property PortNum ;
	__property Handle ;
	__property HSocket ;
	__property BufSize ;
	__property Text ;
	__property AllSent ;
	__property OnDisplay ;
	
__published:
	__property Addr ;
	__property Port ;
	__property Proto ;
	__property LocalAddr ;
	__property LocalPort ;
	__property PeerPort ;
	__property PeerAddr ;
	__property DnsResult ;
	__property DnsResultList ;
	__property State ;
	__property ReadCount ;
	__property RcvdCount ;
	__property LastError ;
	__property MultiThreaded ;
	__property MultiCast ;
	__property MultiCastAddrStr ;
	__property MultiCastIpTTL ;
	__property ReuseAddr ;
	__property ComponentOptions ;
	__property OnDataAvailable ;
	__property OnDataSent ;
	__property OnSendData ;
	__property OnSessionClosed ;
	__property OnSessionAvailable ;
	__property OnSessionConnected ;
	__property OnSocksConnected ;
	__property OnChangeState ;
	__property OnLineTooLong ;
	__property OnDnsLookupDone ;
	__property OnError ;
	__property OnBgException ;
	__property FlushTimeout ;
	__property SendFlags ;
	__property LingerOnOff ;
	__property LingerTimeout ;
	__property SocksLevel ;
	__property SocksServer ;
	__property SocksPort ;
	__property SocksUsercode ;
	__property SocksPassword ;
	__property SocksAuthentication ;
	__property OnSocksError ;
	__property OnSocksAuthState ;
public:
	#pragma option push -w-inl
	/* TCustomLineWSocket.Create */ inline __fastcall virtual TWSocket(Classes::TComponent* AOwner) : TCustomSyncWSocket(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomLineWSocket.Destroy */ inline __fastcall virtual ~TWSocket(void) { }
	#pragma option pop
	
};


class DELPHICLASS TSocksWSocket;
class PASCALIMPLEMENTATION TSocksWSocket : public TWSocket 
{
	typedef TWSocket inherited;
	
public:
	#pragma option push -w-inl
	/* TCustomLineWSocket.Create */ inline __fastcall virtual TSocksWSocket(Classes::TComponent* AOwner) : TWSocket(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomLineWSocket.Destroy */ inline __fastcall virtual ~TSocksWSocket(void) { }
	#pragma option pop
	
};


typedef int __stdcall (*TWSAStartup)(Word wVersionRequired, WSAData &WSData);

typedef int __stdcall (*TWSACleanup)(void);

typedef void __stdcall (*TWSASetLastError)(int iError);

typedef int __stdcall (*TWSAGetLastError)(void);

typedef int __stdcall (*TWSACancelAsyncRequest)(unsigned hAsyncTaskHandle);

typedef unsigned __stdcall (*TWSAAsyncGetHostByName)(HWND HWindow, int wMsg, char * name, char * buf, int buflen);

typedef unsigned __stdcall (*TWSAAsyncGetHostByAddr)(HWND HWindow, int wMsg, char * addr, int len, int Struct, char * buf, int buflen);

typedef int __stdcall (*TWSAAsyncSelect)(int s, HWND HWindow, int wMsg, int lEvent);

typedef Winsock::PServEnt __stdcall (*TGetServByName)(char * name, char * proto);

typedef Winsock::PProtoEnt __stdcall (*TGetProtoByName)(char * name);

typedef Winsock::PHostEnt __stdcall (*TGetHostByName)(char * name);

typedef Winsock::PHostEnt __stdcall (*TGetHostByAddr)(void * addr, int len, int Struct);

typedef int __stdcall (*TGetHostName)(char * name, int len);

typedef int __stdcall (*TOpenSocket)(int af, int Struct, int protocol);

typedef int __stdcall (*TShutdown)(int s, int how);

typedef int __stdcall (*TSetSockOpt)(int s, int level, int optname, char * optval, int optlen);

typedef int __stdcall (*TGetSockOpt)(int s, int level, int optname, char * optval, int &optlen);

typedef int __stdcall (*TSendTo)(int s, void *Buf, int len, int flags, sockaddr_in &addrto, int tolen);

typedef int __stdcall (*TSend)(int s, void *Buf, int len, int flags);

typedef int __stdcall (*TRecv)(int s, void *Buf, int len, int flags);

typedef int __stdcall (*TRecvFrom)(int s, void *Buf, int len, int flags, sockaddr_in &from, int &fromlen);

typedef Word __stdcall (*Tntohs)(Word netshort);

typedef int __stdcall (*Tntohl)(int netlong);

typedef int __stdcall (*TListen)(int s, int backlog);

typedef int __stdcall (*TIoctlSocket)(int s, unsigned cmd, int &arg);

typedef char * __stdcall (*TInet_ntoa)(in_addr inaddr);

typedef int __stdcall (*TInet_addr)(char * cp);

typedef Word __stdcall (*Thtons)(Word hostshort);

typedef int __stdcall (*Thtonl)(int hostlong);

typedef int __stdcall (*TGetSockName)(int s, sockaddr_in &name, int &namelen);

typedef int __stdcall (*TGetPeerName)(int s, sockaddr_in &name, int &namelen);

typedef int __stdcall (*TConnect)(int s, sockaddr_in &name, int namelen);

typedef int __stdcall (*TCloseSocket)(int s);

typedef int __stdcall (*TBind)(int s, sockaddr_in &addr, int namelen);

typedef int __stdcall (*TAccept)(int s, PSOCKADDR addr, System::PInteger addrlen);

//-- var, const, procedure ---------------------------------------------------
static const Word WSocketVersion = 0x1b5;
extern PACKAGE AnsiString CopyRight;
static const Word WM_ASYNCSELECT = 0x401;
static const Word WM_ASYNCGETHOSTBYNAME = 0x402;
static const Word WM_ASYNCGETHOSTBYADDR = 0x403;
static const Word WM_CLOSE_DELAYED = 0x404;
static const Word WM_WSOCKET_RELEASE = 0x405;
static const Word WM_TRIGGER_EXCEPTION = 0x406;
static const Word WM_TRIGGER_DATA_AVAILABLE = 0x414;
static const Word WSA_WSOCKET_TIMEOUT = 0x2ee1;
#define winsocket "wsock32.dll"
extern PACKAGE TWSAStartup FWSAStartup;
extern PACKAGE TWSACleanup FWSACleanup;
extern PACKAGE TWSASetLastError FWSASetLastError;
extern PACKAGE TWSAGetLastError FWSAGetLastError;
extern PACKAGE TWSACancelAsyncRequest FWSACancelAsyncRequest;
extern PACKAGE TWSAAsyncGetHostByName FWSAAsyncGetHostByName;
extern PACKAGE TWSAAsyncGetHostByAddr FWSAAsyncGetHostByAddr;
extern PACKAGE TWSAAsyncSelect FWSAAsyncSelect;
extern PACKAGE TGetServByName FGetServByName;
extern PACKAGE TGetProtoByName FGetProtoByName;
extern PACKAGE TGetHostByName FGetHostByName;
extern PACKAGE TGetHostByAddr FGetHostByAddr;
extern PACKAGE TGetHostName FGetHostName;
extern PACKAGE TOpenSocket FOpenSocket;
extern PACKAGE TShutdown FShutdown;
extern PACKAGE TSetSockOpt FSetSockOpt;
extern PACKAGE TGetSockOpt FGetSockOpt;
extern PACKAGE TSendTo FSendTo;
extern PACKAGE TSend FSend;
extern PACKAGE TRecv FRecv;
extern PACKAGE TRecvFrom FRecvFrom;
extern PACKAGE Tntohs Fntohs;
extern PACKAGE Tntohl Fntohl;
extern PACKAGE TListen FListen;
extern PACKAGE TIoctlSocket FIoctlSocket;
extern PACKAGE TInet_ntoa FInet_ntoa;
extern PACKAGE TInet_addr FInet_addr;
extern PACKAGE Thtons Fhtons;
extern PACKAGE Thtonl Fhtonl;
extern PACKAGE TGetSockName FGetSockName;
extern PACKAGE TGetPeerName FGetPeerName;
extern PACKAGE TConnect FConnect;
extern PACKAGE TCloseSocket FCloseSocket;
extern PACKAGE TBind FBind;
extern PACKAGE TAccept FAccept;
extern PACKAGE int WSocketGCount;
extern PACKAGE bool WSocketGForced;
extern PACKAGE void __fastcall Register(void);
extern PACKAGE bool __fastcall WSocketIsDottedIP(const AnsiString S);
extern PACKAGE void __fastcall WSocketForceLoadWinsock(void);
extern PACKAGE void __fastcall WSocketCancelForceLoadWinsock(void);
extern PACKAGE void __fastcall WSocketUnloadWinsock(void);
extern PACKAGE void * __fastcall WSocketGetProc(const AnsiString ProcName);
extern PACKAGE int __fastcall WSocket_WSAStartup(Word wVersionRequired, WSAData &WSData);
extern PACKAGE int __fastcall WSocket_WSACleanup(void);
extern PACKAGE void __fastcall WSocket_WSASetLastError(int iError);
extern PACKAGE int __fastcall WSocket_WSAGetLastError(void);
extern PACKAGE int __fastcall WSocket_WSACancelAsyncRequest(unsigned hAsyncTaskHandle);
extern PACKAGE unsigned __fastcall WSocket_WSAAsyncGetHostByName(HWND HWindow, int wMsg, char * name, char * buf, int buflen);
extern PACKAGE unsigned __fastcall WSocket_WSAAsyncGetHostByAddr(HWND HWindow, int wMsg, char * addr, int len, int Struct, char * buf, int buflen);
extern PACKAGE int __fastcall WSocket_WSAAsyncSelect(int s, HWND HWindow, int wMsg, int lEvent);
extern PACKAGE Winsock::PServEnt __fastcall WSocket_getservbyname(char * name, char * proto);
extern PACKAGE Winsock::PProtoEnt __fastcall WSocket_getprotobyname(char * name);
extern PACKAGE Winsock::PHostEnt __fastcall WSocket_gethostbyname(char * name);
extern PACKAGE Winsock::PHostEnt __fastcall WSocket_gethostbyaddr(void * addr, int len, int Struct);
extern PACKAGE int __fastcall WSocket_gethostname(char * name, int len);
extern PACKAGE int __fastcall WSocket_socket(int af, int Struct, int protocol);
extern PACKAGE int __fastcall WSocket_shutdown(int s, int how);
extern PACKAGE int __fastcall WSocket_setsockopt(int s, int level, int optname, char * optval, int optlen);
extern PACKAGE int __fastcall WSocket_getsockopt(int s, int level, int optname, char * optval, int &optlen);
extern PACKAGE int __fastcall WSocket_sendto(int s, void *Buf, int len, int flags, sockaddr_in &addrto, int tolen);
extern PACKAGE int __fastcall WSocket_send(int s, void *Buf, int len, int flags);
extern PACKAGE Word __fastcall WSocket_ntohs(Word netshort);
extern PACKAGE int __fastcall WSocket_ntohl(int netlong);
extern PACKAGE int __fastcall WSocket_listen(int s, int backlog);
extern PACKAGE int __fastcall WSocket_ioctlsocket(int s, unsigned cmd, int &arg);
extern PACKAGE char * __fastcall WSocket_inet_ntoa(in_addr inaddr);
extern PACKAGE int __fastcall WSocket_inet_addr(char * cp);
extern PACKAGE Word __fastcall WSocket_htons(Word hostshort);
extern PACKAGE int __fastcall WSocket_htonl(int hostlong);
extern PACKAGE int __fastcall WSocket_getsockname(int s, sockaddr_in &name, int &namelen);
extern PACKAGE int __fastcall WSocket_getpeername(int s, sockaddr_in &name, int &namelen);
extern PACKAGE int __fastcall WSocket_connect(int s, sockaddr_in &name, int namelen);
extern PACKAGE int __fastcall WSocket_closesocket(int s);
extern PACKAGE int __fastcall WSocket_bind(int s, sockaddr_in &addr, int namelen);
extern PACKAGE int __fastcall WSocket_accept(int s, PSOCKADDR addr, System::PInteger addrlen);
extern PACKAGE int __fastcall WSocket_recv(int s, void *Buf, int len, int flags);
extern PACKAGE int __fastcall WSocket_recvfrom(int s, void *Buf, int len, int flags, sockaddr_in &from, int &fromlen);
extern PACKAGE WSAData __fastcall WinsockInfo();
extern PACKAGE HWND __fastcall XSocketAllocateHWnd(System::TObject* Obj);
extern PACKAGE void __fastcall XSocketDeallocateHWnd(HWND Wnd);
extern PACKAGE HWND __fastcall AllocateHWnd(TWndMethod Method);
extern PACKAGE void __fastcall DeallocateHWnd(HWND Wnd);
extern PACKAGE in_addr __fastcall WSocketResolveHost(AnsiString InAddr);
extern PACKAGE Word __fastcall WSocketResolvePort(AnsiString Port, AnsiString Proto);
extern PACKAGE int __fastcall WSocketResolveProto(AnsiString sProto);
extern PACKAGE Winsock::PHostEnt __fastcall WSocketGetHostByAddr(AnsiString Addr);
extern PACKAGE AnsiString __fastcall WSocketResolveIp(AnsiString IpAddr);
extern PACKAGE Winsock::PHostEnt __fastcall WSocketGetHostByName(AnsiString Name);
extern PACKAGE Classes::TStrings* __fastcall LocalIPList(void);
extern PACKAGE AnsiString __fastcall LocalHostName();
extern PACKAGE AnsiString __fastcall WSocketErrorDesc(int error);

}	/* namespace Wsocket */
using namespace Wsocket;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// WSocket
