// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Ping.pas' rev: 6.00

#ifndef PingHPP
#define PingHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Icmp.hpp>	// Pascal unit
#include <WinSock.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Ping
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TDnsLookupDone)(System::TObject* Sender, Word Error);

typedef void __fastcall (__closure *TPingDisplay)(System::TObject* Sender, System::TObject* Icmp, AnsiString Msg);

typedef void __fastcall (__closure *TPingReply)(System::TObject* Sender, System::TObject* Icmp, int Error);

typedef void __fastcall (__closure *TPingRequest)(System::TObject* Sender, System::TObject* Icmp);

class DELPHICLASS TPing;
class PASCALIMPLEMENTATION TPing : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	Icmp::TICMP* FIcmp;
	HWND FWindowHandle;
	char FDnsLookupBuffer[1025];
	unsigned FDnsLookupHandle;
	AnsiString FDnsResult;
	TDnsLookupDone FOnDnsLookupDone;
	TPingRequest FOnEchoRequest;
	TPingReply FOnEchoReply;
	TPingDisplay FOnDisplay;
	
protected:
	void __fastcall WndProc(Messages::TMessage &MsgRec);
	MESSAGE void __fastcall WMAsyncGetHostByName(Messages::TMessage &msg);
	void __fastcall SetAddress(AnsiString Value);
	AnsiString __fastcall GetAddress();
	void __fastcall SetSize(int Value);
	int __fastcall GetSize(void);
	void __fastcall SetTimeout(int Value);
	int __fastcall GetTimeout(void);
	Icmp::TIcmpEchoReply __fastcall GetReply();
	int __fastcall GetErrorCode(void);
	AnsiString __fastcall GetErrorString();
	AnsiString __fastcall GetHostName();
	AnsiString __fastcall GetHostIP();
	void __fastcall SetTTL(int Value);
	int __fastcall GetTTL(void);
	void __fastcall Setflags(int Value);
	int __fastcall Getflags(void);
	void __fastcall IcmpEchoReply(System::TObject* Sender, int Error);
	void __fastcall IcmpEchoRequest(System::TObject* Sender);
	void __fastcall IcmpDisplay(System::TObject* Sender, AnsiString Msg);
	
public:
	__fastcall virtual TPing(Classes::TComponent* Owner);
	__fastcall virtual ~TPing(void);
	int __fastcall Ping(void);
	virtual void __fastcall DnsLookup(AnsiString HostName);
	void __fastcall CancelDnsLookup(void);
	__property Icmp::TIcmpEchoReply Reply = {read=GetReply};
	__property int ErrorCode = {read=GetErrorCode, nodefault};
	__property AnsiString ErrorString = {read=GetErrorString};
	__property AnsiString HostName = {read=GetHostName};
	__property AnsiString HostIP = {read=GetHostIP};
	__property HWND Handle = {read=FWindowHandle, nodefault};
	__property AnsiString DnsResult = {read=FDnsResult};
	
__published:
	__property AnsiString Address = {read=GetAddress, write=SetAddress};
	__property int Size = {read=GetSize, write=SetSize, nodefault};
	__property int Timeout = {read=GetTimeout, write=SetTimeout, nodefault};
	__property int TTL = {read=GetTTL, write=SetTTL, nodefault};
	__property int Flags = {read=Getflags, write=Setflags, nodefault};
	__property TPingDisplay OnDisplay = {read=FOnDisplay, write=FOnDisplay};
	__property TPingRequest OnEchoRequest = {read=FOnEchoRequest, write=FOnEchoRequest};
	__property TPingReply OnEchoReply = {read=FOnEchoReply, write=FOnEchoReply};
	__property TDnsLookupDone OnDnsLookupDone = {read=FOnDnsLookupDone, write=FOnDnsLookupDone};
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint PingVersion = 0x6f;
extern PACKAGE AnsiString CopyRight;
static const Word WM_ASYNCGETHOSTBYNAME = 0x402;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Ping */
using namespace Ping;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ping
