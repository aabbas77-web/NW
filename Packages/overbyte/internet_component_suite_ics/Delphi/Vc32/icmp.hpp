// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Icmp.pas' rev: 6.00

#ifndef IcmpHPP
#define IcmpHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <WinSock.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Icmp
{
//-- type declarations -------------------------------------------------------
typedef int TIPAddr;

typedef int TIPMask;

typedef int TIPStatus;

struct TIPOptionInformation;
typedef TIPOptionInformation *PIPOptionInformation;

#pragma pack(push, 1)
struct TIPOptionInformation
{
	Byte TTL;
	Byte TOS;
	Byte Flags;
	Byte OptionsSize;
	char *OptionsData;
} ;
#pragma pack(pop)

struct TIcmpEchoReply;
typedef TIcmpEchoReply *PIcmpEchoReply;

#pragma pack(push, 1)
struct TIcmpEchoReply
{
	int Address;
	unsigned Status;
	unsigned RTT;
	Word DataSize;
	Word Reserved;
	void *Data;
	TIPOptionInformation Options;
} ;
#pragma pack(pop)

typedef unsigned __stdcall (*TIcmpCreateFile)(void);

typedef bool __stdcall (*TIcmpCloseHandle)(unsigned IcmpHandle);

typedef unsigned __stdcall (*TIcmpSendEcho)(unsigned IcmpHandle, int DestinationAddress, void * RequestData, Word RequestSize, PIPOptionInformation RequestOptions, void * ReplyBuffer, unsigned ReplySize, unsigned Timeout);

typedef void __fastcall (__closure *TICMPDisplay)(System::TObject* Sender, AnsiString Msg);

typedef void __fastcall (__closure *TICMPReply)(System::TObject* Sender, int Error);

class DELPHICLASS TICMP;
class PASCALIMPLEMENTATION TICMP : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	unsigned hICMPdll;
	TIcmpCreateFile IcmpCreateFile;
	TIcmpCloseHandle IcmpCloseHandle;
	TIcmpSendEcho IcmpSendEcho;
	unsigned hICMP;
	#pragma pack(push, 1)
	TIcmpEchoReply FReply;
	#pragma pack(pop)
	
	AnsiString FAddress;
	AnsiString FHostName;
	AnsiString FHostIP;
	int FIPAddress;
	int FSize;
	int FTimeOut;
	int FTTL;
	int FFlags;
	TICMPDisplay FOnDisplay;
	Classes::TNotifyEvent FOnEchoRequest;
	TICMPReply FOnEchoReply;
	unsigned FLastError;
	bool FAddrResolved;
	void __fastcall ResolveAddr(void);
	
public:
	__fastcall virtual TICMP(void);
	__fastcall virtual ~TICMP(void);
	int __fastcall Ping(void);
	void __fastcall SetAddress(AnsiString Value);
	AnsiString __fastcall GetErrorString();
	__property AnsiString Address = {read=FAddress, write=SetAddress};
	__property int Size = {read=FSize, write=FSize, nodefault};
	__property int Timeout = {read=FTimeOut, write=FTimeOut, nodefault};
	__property TIcmpEchoReply Reply = {read=FReply};
	__property int TTL = {read=FTTL, write=FTTL, nodefault};
	__property int Flags = {read=FFlags, write=FFlags, nodefault};
	__property unsigned ErrorCode = {read=FLastError, nodefault};
	__property AnsiString ErrorString = {read=GetErrorString};
	__property AnsiString HostName = {read=FHostName};
	__property AnsiString HostIP = {read=FHostIP};
	__property TICMPDisplay OnDisplay = {read=FOnDisplay, write=FOnDisplay};
	__property Classes::TNotifyEvent OnEchoRequest = {read=FOnEchoRequest, write=FOnEchoRequest};
	__property TICMPReply OnEchoReply = {read=FOnEchoReply, write=FOnEchoReply};
};


class DELPHICLASS TICMPException;
class PASCALIMPLEMENTATION TICMPException : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall TICMPException(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall TICMPException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall TICMPException(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall TICMPException(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall TICMPException(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall TICMPException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall TICMPException(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall TICMPException(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TICMPException(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint IcmpVersion = 0x66;
#define IcmpDLL "icmp.dll"
static const Shortint IP_SUCCESS = 0x0;
static const Word IP_STATUS_BASE = 0x2af8;
static const Word IP_BUF_TOO_SMALL = 0x2af9;
static const Word IP_DEST_NET_UNREACHABLE = 0x2afa;
static const Word IP_DEST_HOST_UNREACHABLE = 0x2afb;
static const Word IP_DEST_PROT_UNREACHABLE = 0x2afc;
static const Word IP_DEST_PORT_UNREACHABLE = 0x2afd;
static const Word IP_NO_RESOURCES = 0x2afe;
static const Word IP_BAD_OPTION = 0x2aff;
static const Word IP_HW_ERROR = 0x2b00;
static const Word IP_PACKET_TOO_BIG = 0x2b01;
static const Word IP_REQ_TIMED_OUT = 0x2b02;
static const Word IP_BAD_REQ = 0x2b03;
static const Word IP_BAD_ROUTE = 0x2b04;
static const Word IP_TTL_EXPIRED_TRANSIT = 0x2b05;
static const Word IP_TTL_EXPIRED_REASSEM = 0x2b06;
static const Word IP_PARAM_PROBLEM = 0x2b07;
static const Word IP_SOURCE_QUENCH = 0x2b08;
static const Word IP_OPTION_TOO_BIG = 0x2b09;
static const Word IP_BAD_DESTINATION = 0x2b0a;
static const Word IP_ADDR_DELETED = 0x2b0b;
static const Word IP_SPEC_MTU_CHANGE = 0x2b0c;
static const Word IP_MTU_CHANGE = 0x2b0d;
static const Word IP_GENERAL_FAILURE = 0x2b2a;
static const Word MAX_IP_STATUS = 0x2b2a;
static const Word IP_PENDING = 0x2bf7;
static const Shortint IP_FLAG_DF = 0x2;
static const Shortint IP_OPT_EOL = 0x0;
static const Shortint IP_OPT_NOP = 0x1;
static const Byte IP_OPT_SECURITY = 0x82;
static const Byte IP_OPT_LSRR = 0x83;
static const Byte IP_OPT_SSRR = 0x89;
static const Shortint IP_OPT_RR = 0x7;
static const Shortint IP_OPT_TS = 0x44;
static const Byte IP_OPT_SID = 0x88;
static const Shortint MAX_OPT_SIZE = 0x40;

}	/* namespace Icmp */
using namespace Icmp;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Icmp
