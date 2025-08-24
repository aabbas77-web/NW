// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ApSrvCli.pas' rev: 6.00

#ifndef ApSrvCliHPP
#define ApSrvCliHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <WSocket.hpp>	// Pascal unit
#include <WinSock.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Apsrvcli
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS ClientWSocketException;
class PASCALIMPLEMENTATION ClientWSocketException : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ClientWSocketException(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ClientWSocketException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ClientWSocketException(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ClientWSocketException(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ClientWSocketException(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ClientWSocketException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ClientWSocketException(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ClientWSocketException(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ClientWSocketException(void) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TDisplayEvent)(System::TObject* Sender, AnsiString Msg);

typedef void __fastcall (__closure *TCommandEvent)(System::TObject* Sender, char * CmdBuf, int CmdLen);

typedef void __fastcall (__closure *TTimeoutEvent)(System::TObject* Sender, bool &CanClose);

typedef void __fastcall (__closure *TOverflowEvent)(System::TObject* Sender, bool &CanAbort);

class DELPHICLASS TClientWSocket;
class PASCALIMPLEMENTATION TClientWSocket : public Wsocket::TCustomWSocket 
{
	typedef Wsocket::TCustomWSocket inherited;
	
protected:
	char *FRcvBuf;
	int FRcvCnt;
	int FRcvSize;
	int FRcvSizeInc;
	int FRcvSizeMax;
	bool FBusy;
	System::TDateTime FConnectedSince;
	System::TDateTime FLastCommandTime;
	int FCommandCount;
	System::TDateTime FCommandTimeOut;
	AnsiString FBanner;
	AnsiString FPeerAddr;
	char *FReplyHeader;
	int FReplyHeaderLen;
	char *FReplyBody;
	int FReplyBodyLen;
	int FUserData;
	bool FAbortRequest;
	TDisplayEvent FOnDisplay;
	TCommandEvent FOnCommand;
	TTimeoutEvent FOnTimeout;
	TOverflowEvent FOnOverflow;
	virtual void __fastcall TriggerSessionConnected(Word Error);
	virtual bool __fastcall TriggerDataAvailable(Word Error);
	virtual void __fastcall TriggerCommand(char * CmdBuf, int CmdLen);
	virtual void __fastcall TriggerTimeout(bool &CanClose);
	virtual void __fastcall TriggerOverflow(bool &CanAbort);
	void __fastcall SetRcvSize(int newValue);
	virtual void __fastcall WndProc(Messages::TMessage &MsgRec);
	MESSAGE void __fastcall WMAbortRequest(Messages::TMessage &msg);
	
public:
	__fastcall virtual TClientWSocket(Classes::TComponent* AOwner);
	__fastcall virtual ~TClientWSocket(void);
	void __fastcall StartConnection(void);
	virtual void __fastcall CheckCommandTimeout(void);
	virtual void __fastcall SendReply(void);
	virtual void __fastcall Dup(int newHSocket);
	virtual AnsiString __fastcall GetPeerAddr();
	__property AnsiString PeerAddr = {read=GetPeerAddr};
	__property System::TDateTime ConnectedSince = {read=FConnectedSince};
	__property System::TDateTime LastCommandTime = {read=FLastCommandTime};
	__property int CommandCount = {read=FCommandCount, nodefault};
	__property System::TDateTime CommandTimeOut = {read=FCommandTimeOut, write=FCommandTimeOut};
	__property char * RcvBuf = {read=FRcvBuf};
	__property RcvdCount ;
	__property char * ReplyHeader = {read=FReplyHeader, write=FReplyHeader};
	__property int ReplyHeaderLen = {read=FReplyHeaderLen, write=FReplyHeaderLen, nodefault};
	__property char * ReplyBody = {read=FReplyBody, write=FReplyBody};
	__property int ReplyBodyLen = {read=FReplyBodyLen, write=FReplyBodyLen, nodefault};
	__property LocalPort ;
	
__published:
	__property AnsiString Banner = {read=FBanner, write=FBanner};
	__property int RcvSize = {read=FRcvSize, write=SetRcvSize, nodefault};
	__property int RcvSizeInc = {read=FRcvSizeInc, write=FRcvSizeInc, nodefault};
	__property int RcvSizeMax = {read=FRcvSizeMax, write=FRcvSizeMax, nodefault};
	__property bool Busy = {read=FBusy, write=FBusy, nodefault};
	__property int UserData = {read=FUserData, write=FUserData, nodefault};
	__property TDisplayEvent OnDisplay = {read=FOnDisplay, write=FOnDisplay};
	__property TCommandEvent OnCommand = {read=FOnCommand, write=FOnCommand};
	__property TTimeoutEvent OnTimeout = {read=FOnTimeout, write=FOnTimeout};
	__property TOverflowEvent OnOverflow = {read=FOnOverflow, write=FOnOverflow};
	__property OnSessionClosed ;
	__property OnBgException ;
	__property HSocket ;
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint ApSrvCliVersion = 0x6d;
extern PACKAGE AnsiString CopyRight;
static const Word DefaultRcvSize = 0xfc18;
static const Word DefaultRcvSizeInc = 0xfc18;
static const Shortint DefaultRcvSizeMax = 0x0;
static const Word WM_ABORT_REQUEST = 0x40a;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Apsrvcli */
using namespace Apsrvcli;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ApSrvCli
