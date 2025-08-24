// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FtpSrvC.pas' rev: 6.00

#ifndef FtpSrvCHPP
#define FtpSrvCHPP

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

namespace Ftpsrvc
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS EFtpCtrlSocketException;
class PASCALIMPLEMENTATION EFtpCtrlSocketException : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EFtpCtrlSocketException(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EFtpCtrlSocketException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EFtpCtrlSocketException(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EFtpCtrlSocketException(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EFtpCtrlSocketException(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EFtpCtrlSocketException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EFtpCtrlSocketException(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EFtpCtrlSocketException(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EFtpCtrlSocketException(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TFtpCtrlState { ftpcInvalid, ftpcWaitingUserCode, ftpcWaitingPassword, ftpcReady, ftpcWaitingAnswer };
#pragma option pop

typedef Byte TFtpCmdType;

#pragma option push -b-
enum TFtpOption { ftpcUNC };
#pragma option pop

typedef Set<TFtpOption, ftpcUNC, ftpcUNC>  TFtpOptions;

typedef void __fastcall (__closure *TDisplayEvent)(System::TObject* Sender, AnsiString Msg);

typedef void __fastcall (__closure *TCommandEvent)(System::TObject* Sender, char * CmdBuf, int CmdLen);

class DELPHICLASS TFtpCtrlSocket;
class PASCALIMPLEMENTATION TFtpCtrlSocket : public Wsocket::TCustomWSocket 
{
	typedef Wsocket::TCustomWSocket inherited;
	
protected:
	Wsocket::TWSocket* FDataSocket;
	char *FRcvBuf;
	int FRcvCnt;
	int FRcvSize;
	bool FBusy;
	System::TDateTime FConnectedSince;
	System::TDateTime FLastCommand;
	int FCommandCount;
	AnsiString FBanner;
	AnsiString FUserName;
	AnsiString FPassWord;
	bool FCloseRequest;
	AnsiString FHomeDir;
	AnsiString FDirectory;
	TFtpCtrlState FFtpState;
	bool FAbortingTransfer;
	int FUserData;
	AnsiString FPeerAddr;
	int FID;
	TDisplayEvent FOnDisplay;
	TCommandEvent FOnCommand;
	virtual void __fastcall TriggerSessionConnected(Word Error);
	virtual bool __fastcall TriggerDataAvailable(Word Error);
	virtual void __fastcall TriggerCommand(char * CmdBuf, int CmdLen);
	void __fastcall SetRcvSize(int newValue);
	
public:
	bool BinaryMode;
	AnsiString DataAddr;
	AnsiString DataPort;
	AnsiString FileName;
	AnsiString FilePath;
	bool DataSessionActive;
	Classes::TStream* DataStream;
	bool HasOpenedFile;
	AnsiString TransferError;
	int ByteCount;
	bool DataSent;
	Byte CurCmdType;
	int RestartPos;
	AnsiString FromFileName;
	AnsiString ToFileName;
	bool PassiveMode;
	bool PassiveStart;
	bool PassiveConnected;
	TFtpOptions Options;
	__fastcall virtual TFtpCtrlSocket(Classes::TComponent* AOwner);
	__fastcall virtual ~TFtpCtrlSocket(void);
	virtual void __fastcall Dup(int newHSocket);
	virtual void __fastcall StartConnection(void);
	void __fastcall SendAnswer(AnsiString Answer);
	void __fastcall SetDirectory(AnsiString newValue);
	void __fastcall SetAbortingTransfer(bool newValue);
	virtual AnsiString __fastcall GetPeerAddr();
	__property Wsocket::TWSocket* DataSocket = {read=FDataSocket};
	__property System::TDateTime ConnectedSince = {read=FConnectedSince};
	__property System::TDateTime LastCommand = {read=FLastCommand};
	__property int CommandCount = {read=FCommandCount, nodefault};
	__property char * RcvBuf = {read=FRcvBuf};
	__property RcvdCount ;
	__property bool CloseRequest = {read=FCloseRequest, write=FCloseRequest, nodefault};
	__property AnsiString Directory = {read=FDirectory, write=SetDirectory};
	__property AnsiString HomeDir = {read=FHomeDir, write=FHomeDir};
	__property bool AbortingTransfer = {read=FAbortingTransfer, write=SetAbortingTransfer, nodefault};
	__property int ID = {read=FID, write=FID, nodefault};
	
__published:
	__property TFtpCtrlState FtpState = {read=FFtpState, write=FFtpState, nodefault};
	__property AnsiString Banner = {read=FBanner, write=FBanner};
	__property int RcvSize = {read=FRcvSize, write=SetRcvSize, nodefault};
	__property bool Busy = {read=FBusy, write=FBusy, nodefault};
	__property AnsiString UserName = {read=FUserName, write=FUserName};
	__property AnsiString PassWord = {read=FPassWord, write=FPassWord};
	__property int UserData = {read=FUserData, write=FUserData, nodefault};
	__property TDisplayEvent OnDisplay = {read=FOnDisplay, write=FOnDisplay};
	__property TCommandEvent OnCommand = {read=FOnCommand, write=FOnCommand};
	__property OnSessionClosed ;
	__property OnDataSent ;
	__property HSocket ;
	__property AllSent ;
	__property State ;
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint FtpCtrlSocketVersion = 0x6d;
extern PACKAGE AnsiString CopyRight;
static const Word DefaultRcvSize = 0x800;
static const Shortint ftpcPORT = 0x0;
static const Shortint ftpcSTOR = 0x1;
static const Shortint ftpcRETR = 0x2;
static const Shortint ftpcCWD = 0x3;
static const Shortint ftpcXPWD = 0x4;
static const Shortint ftpcPWD = 0x5;
static const Shortint ftpcUSER = 0x6;
static const Shortint ftpcPASS = 0x7;
static const Shortint ftpcLIST = 0x8;
static const Shortint ftpcRMD = 0x9;
static const Shortint ftpcTYPE = 0xa;
static const Shortint ftpcSYST = 0xb;
static const Shortint ftpcQUIT = 0xc;
static const Shortint ftpcDELE = 0xd;
static const Shortint ftpcRNFR = 0xe;
static const Shortint ftpcMKD = 0xf;
static const Shortint ftpcRNTO = 0x10;
static const Shortint ftpcNOOP = 0x11;
static const Shortint ftpcNLST = 0x12;
static const Shortint ftpcABOR = 0x13;
static const Shortint ftpcCDUP = 0x14;
static const Shortint ftpcSIZE = 0x15;
static const Shortint ftpcREST = 0x16;
static const Shortint ftpcAPPE = 0x17;
static const Shortint ftpcSTRU = 0x18;
static const Shortint ftpcMDTM = 0x19;
static const Shortint ftpcSTOU = 0x1a;
extern PACKAGE bool __fastcall IsUNC(AnsiString S);
extern PACKAGE void __fastcall PatchIE5(AnsiString &S);

}	/* namespace Ftpsrvc */
using namespace Ftpsrvc;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FtpSrvC
