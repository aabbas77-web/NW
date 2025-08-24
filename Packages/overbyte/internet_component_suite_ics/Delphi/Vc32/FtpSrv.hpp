// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FtpSrv.pas' rev: 6.00

#ifndef FtpSrvHPP
#define FtpSrvHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <FtpSrvT.hpp>	// Pascal unit
#include <FtpSrvC.hpp>	// Pascal unit
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

namespace Ftpsrv
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS FtpServerException;
class PASCALIMPLEMENTATION FtpServerException : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall FtpServerException(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall FtpServerException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall FtpServerException(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall FtpServerException(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall FtpServerException(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall FtpServerException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall FtpServerException(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall FtpServerException(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~FtpServerException(void) { }
	#pragma option pop
	
};


typedef SmallString<255>  TFtpString;

typedef TMetaClass*TFtpCtrlSocketClass;

typedef void __fastcall (__closure *TFtpSrvAuthenticateEvent)(System::TObject* Sender, Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &UserName,  TFtpString &Password, bool &Authenticated);

typedef void __fastcall (__closure *TFtpSrvChangeDirectoryEvent)(System::TObject* Sender, Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Directory, bool &Allowed);

typedef void __fastcall (__closure *TFtpSrvBuildDirectoryEvent)(System::TObject* Sender, Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Directory, bool Detailed);

typedef void __fastcall (__closure *TFtpSrvClientConnectEvent)(System::TObject* Sender, Ftpsrvc::TFtpCtrlSocket* Client, Word AError);

typedef void __fastcall (__closure *TFtpSrvDataSessionConnectedEvent)(System::TObject* Sender, Ftpsrvc::TFtpCtrlSocket* Client, Wsocket::TWSocket* Data, Word AError);

typedef void __fastcall (__closure *TFtpSrvClientCommandEvent)(System::TObject* Sender, Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);

typedef void __fastcall (__closure *TFtpSrvAnswerToClientEvent)(System::TObject* Sender, Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Answer);

typedef void __fastcall (__closure *TFtpSrvValidateXferEvent)(System::TObject* Sender, Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &FilePath, bool &Allowed);

typedef void __fastcall (__closure *TFtpSrvDataAvailableEvent)(System::TObject* Sender, Ftpsrvc::TFtpCtrlSocket* Client, Wsocket::TWSocket* Data, char * Buf, int Len, Word AError);

typedef void __fastcall (__closure *TFtpSrvRetrDataSentEvent)(System::TObject* Sender, Ftpsrvc::TFtpCtrlSocket* Client, Wsocket::TWSocket* Data, Word AError);

typedef void __fastcall (__closure *TFtpSrvGetUniqueFileNameEvent)(System::TObject* Sender, Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &FileName);

typedef void __fastcall (__closure *TFtpSrvCommandProc)(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);

struct TFtpSrvCommandTableItem
{
	AnsiString KeyWord;
	TFtpSrvCommandProc Proc;
} ;

typedef TFtpSrvCommandTableItem FtpSrv__3[32];

class DELPHICLASS TFtpServer;
class PASCALIMPLEMENTATION TFtpServer : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
protected:
	AnsiString FAddr;
	AnsiString FPort;
	AnsiString FBanner;
	Wsocket::TWSocket* FServSocket;
	HWND FWindowHandle;
	TMetaClass*FClientClass;
	Classes::TList* FClientList;
	int FClientNum;
	int FMaxClients;
	TFtpSrvCommandTableItem FCmdTable[32];
	int FLastCmd;
	int FUserData;
	Classes::TNotifyEvent FOnStart;
	Classes::TNotifyEvent FOnStop;
	TFtpSrvAuthenticateEvent FOnAuthenticate;
	TFtpSrvClientConnectEvent FOnClientConnect;
	TFtpSrvClientConnectEvent FOnClientDisconnect;
	TFtpSrvClientCommandEvent FOnClientCommand;
	TFtpSrvAnswerToClientEvent FOnAnswerToClient;
	TFtpSrvChangeDirectoryEvent FOnChangeDirectory;
	TFtpSrvChangeDirectoryEvent FOnMakeDirectory;
	TFtpSrvBuildDirectoryEvent FOnBuildDirectory;
	TFtpSrvBuildDirectoryEvent FOnAlterDirectory;
	TFtpSrvValidateXferEvent FOnValidatePut;
	TFtpSrvValidateXferEvent FOnValidateDele;
	TFtpSrvValidateXferEvent FOnValidateRmd;
	TFtpSrvValidateXferEvent FOnValidateRnFr;
	TFtpSrvValidateXferEvent FOnValidateRnTo;
	TFtpSrvDataSessionConnectedEvent FOnStorSessionConnected;
	TFtpSrvDataSessionConnectedEvent FOnStorSessionClosed;
	TFtpSrvDataAvailableEvent FOnStorDataAvailable;
	TFtpSrvValidateXferEvent FOnValidateGet;
	TFtpSrvDataSessionConnectedEvent FOnRetrSessionConnected;
	TFtpSrvDataSessionConnectedEvent FOnRetrSessionClosed;
	TFtpSrvRetrDataSentEvent FOnRetrDataSent;
	TFtpSrvGetUniqueFileNameEvent FOnGetUniqueFileName;
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation operation);
	void __fastcall ServSocketSessionAvailable(System::TObject* Sender, Word AError);
	void __fastcall ServSocketStateChange(System::TObject* Sender, Wsocket::TSocketState OldState, Wsocket::TSocketState NewState);
	void __fastcall ClientSessionClosed(System::TObject* Sender, Word AError);
	void __fastcall ClientDataSent(System::TObject* Sender, Word AError);
	void __fastcall ClientCommand(System::TObject* Sender, char * CmdBuf, int CmdLen);
	void __fastcall ClientPassiveSessionAvailable(System::TObject* Sender, Word AError);
	void __fastcall ClientStorSessionConnected(System::TObject* Sender, Word AError);
	void __fastcall ClientStorSessionClosed(System::TObject* Sender, Word AError);
	void __fastcall ClientStorDataAvailable(System::TObject* Sender, Word AError);
	void __fastcall ClientRetrSessionConnected(System::TObject* Sender, Word AError);
	void __fastcall ClientRetrSessionClosed(System::TObject* Sender, Word AError);
	void __fastcall ClientRetrDataSent(System::TObject* Sender, Word AError);
	void __fastcall SendAnswer(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Answer);
	void __fastcall SendNextDataChunk(Ftpsrvc::TFtpCtrlSocket* Client, Wsocket::TWSocket* Data);
	void __fastcall StartSendData(Ftpsrvc::TFtpCtrlSocket* Client);
	void __fastcall BuildDirectory(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Params, Classes::TStream* Stream, bool Detailed);
	virtual void __fastcall TriggerServerStart(void);
	virtual void __fastcall TriggerServerStop(void);
	virtual void __fastcall TriggerAuthenticate(Ftpsrvc::TFtpCtrlSocket* Client, AnsiString UserName, AnsiString PassWord, bool &Authenticated);
	virtual void __fastcall TriggerChangeDirectory(Ftpsrvc::TFtpCtrlSocket* Client, AnsiString Directory, bool &Allowed);
	virtual void __fastcall TriggerMakeDirectory(Ftpsrvc::TFtpCtrlSocket* Client, AnsiString Directory, bool &Allowed);
	void __fastcall TriggerBuildDirectory(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Params, bool Detailed);
	void __fastcall TriggerAlterDirectory(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Params, bool Detailed);
	virtual void __fastcall TriggerSendAnswer(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Answer);
	virtual void __fastcall TriggerClientConnect(Ftpsrvc::TFtpCtrlSocket* Client, Word AError);
	virtual void __fastcall TriggerClientDisconnect(Ftpsrvc::TFtpCtrlSocket* Client, Word AError);
	virtual void __fastcall TriggerClientCommand(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall TriggerStorSessionConnected(Ftpsrvc::TFtpCtrlSocket* Client, Wsocket::TWSocket* Data, Word AError);
	virtual void __fastcall TriggerStorSessionClosed(Ftpsrvc::TFtpCtrlSocket* Client, Wsocket::TWSocket* Data, Word AError);
	virtual void __fastcall TriggerValidatePut(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &FilePath, bool &Allowed);
	virtual void __fastcall TriggerValidateDele(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &FilePath, bool &Allowed);
	virtual void __fastcall TriggerValidateRmd(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &FilePath, bool &Allowed);
	virtual void __fastcall TriggerValidateRnFr(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &FilePath, bool &Allowed);
	virtual void __fastcall TriggerValidateRnTo(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &FilePath, bool &Allowed);
	virtual void __fastcall TriggerRetrSessionConnected(Ftpsrvc::TFtpCtrlSocket* Client, Wsocket::TWSocket* Data, Word AError);
	virtual void __fastcall TriggerRetrSessionClosed(Ftpsrvc::TFtpCtrlSocket* Client, Wsocket::TWSocket* Data, Word AError);
	virtual void __fastcall TriggerValidateGet(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &FilePath, bool &Allowed);
	virtual void __fastcall TriggerStorDataAvailable(Ftpsrvc::TFtpCtrlSocket* Client, Wsocket::TWSocket* Data, char * Buf, int Len, Word AError);
	virtual void __fastcall TriggerRetrDataSent(Ftpsrvc::TFtpCtrlSocket* Client, Wsocket::TWSocket* Data, Word AError);
	virtual void __fastcall TriggerGetUniqueFileName(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &FileName);
	virtual int __fastcall GetClientCount(void);
	virtual Ftpsrvc::TFtpCtrlSocket* __fastcall GetClient(int nIndex);
	bool __fastcall GetActive(void);
	void __fastcall SetActive(bool newValue);
	virtual void __fastcall AddCommand(const AnsiString Keyword, const TFtpSrvCommandProc Proc);
	MESSAGE void __fastcall WMFtpSrvCloseRequest(Messages::TMessage &msg);
	MESSAGE void __fastcall WMFtpSrvClientClosed(Messages::TMessage &msg);
	MESSAGE void __fastcall WMFtpSrvAbortTransfer(Messages::TMessage &msg);
	MESSAGE void __fastcall WMFtpSrvCloseData(Messages::TMessage &msg);
	void __fastcall CommandDirectory(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer, bool Detailed);
	virtual void __fastcall CommandUSER(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandPASS(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandQUIT(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandNOOP(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandLIST(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandNLST(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandDELE(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandSIZE(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandREST(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandRNFR(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandRNTO(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandPORT(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandSTOR(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandRETR(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandTYPE(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandCWD(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandChangeDir(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandMKD(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandRMD(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandCDUP(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandXPWD(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandPWD(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandSYST(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandABOR(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandPASV(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandAPPE(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandSTRU(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandMDTM(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandMODE(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandOverflow(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	virtual void __fastcall CommandSTOU(Ftpsrvc::TFtpCtrlSocket* Client,  TFtpString &Keyword,  TFtpString &Params,  TFtpString &Answer);
	
public:
	__fastcall virtual TFtpServer(Classes::TComponent* AOwner);
	__fastcall virtual ~TFtpServer(void);
	void __fastcall Start(void);
	void __fastcall Stop(void);
	void __fastcall Disconnect(Ftpsrvc::TFtpCtrlSocket* Client);
	void __fastcall DisconnectAll(void);
	void __fastcall WndProc(Messages::TMessage &MsgRec);
	bool __fastcall IsClient(System::TObject* SomeThing);
	__property Wsocket::TWSocket* ServSocket = {read=FServSocket};
	__property HWND Handle = {read=FWindowHandle, nodefault};
	__property int ClientCount = {read=GetClientCount, nodefault};
	__property bool Active = {read=GetActive, write=SetActive, nodefault};
	__property TMetaClass* ClientClass = {read=FClientClass, write=FClientClass};
	__property Ftpsrvc::TFtpCtrlSocket* Client[int nIndex] = {read=GetClient};
	
__published:
	__property AnsiString Addr = {read=FAddr, write=FAddr};
	__property AnsiString Port = {read=FPort, write=FPort};
	__property AnsiString Banner = {read=FBanner, write=FBanner};
	__property int UserData = {read=FUserData, write=FUserData, nodefault};
	__property int MaxClients = {read=FMaxClients, write=FMaxClients, nodefault};
	__property Classes::TNotifyEvent OnStart = {read=FOnStart, write=FOnStart};
	__property Classes::TNotifyEvent OnStop = {read=FOnStop, write=FOnStop};
	__property TFtpSrvAuthenticateEvent OnAuthenticate = {read=FOnAuthenticate, write=FOnAuthenticate};
	__property TFtpSrvClientConnectEvent OnClientDisconnect = {read=FOnClientDisconnect, write=FOnClientDisconnect};
	__property TFtpSrvClientConnectEvent OnClientConnect = {read=FOnClientConnect, write=FOnClientConnect};
	__property TFtpSrvClientCommandEvent OnClientCommand = {read=FOnClientCommand, write=FOnClientCommand};
	__property TFtpSrvAnswerToClientEvent OnAnswerToClient = {read=FOnAnswerToClient, write=FOnAnswerToClient};
	__property TFtpSrvChangeDirectoryEvent OnChangeDirectory = {read=FOnChangeDirectory, write=FOnChangeDirectory};
	__property TFtpSrvChangeDirectoryEvent OnMakeDirectory = {read=FOnMakeDirectory, write=FOnMakeDirectory};
	__property TFtpSrvBuildDirectoryEvent OnBuildDirectory = {read=FOnBuildDirectory, write=FOnBuildDirectory};
	__property TFtpSrvBuildDirectoryEvent OnAlterDirectory = {read=FOnAlterDirectory, write=FOnAlterDirectory};
	__property TFtpSrvDataSessionConnectedEvent OnStorSessionConnected = {read=FOnStorSessionConnected, write=FOnStorSessionConnected};
	__property TFtpSrvDataSessionConnectedEvent OnRetrSessionConnected = {read=FOnRetrSessionConnected, write=FOnRetrSessionConnected};
	__property TFtpSrvDataSessionConnectedEvent OnStorSessionClosed = {read=FOnStorSessionClosed, write=FOnStorSessionClosed};
	__property TFtpSrvDataSessionConnectedEvent OnRetrSessionClosed = {read=FOnRetrSessionClosed, write=FOnRetrSessionClosed};
	__property TFtpSrvRetrDataSentEvent OnRetrDataSent = {read=FOnRetrDataSent, write=FOnRetrDataSent};
	__property TFtpSrvValidateXferEvent OnValidatePut = {read=FOnValidatePut, write=FOnValidatePut};
	__property TFtpSrvValidateXferEvent OnValidateDele = {read=FOnValidateDele, write=FOnValidateDele};
	__property TFtpSrvValidateXferEvent OnValidateRmd = {read=FOnValidateRmd, write=FOnValidateRmd};
	__property TFtpSrvValidateXferEvent OnValidateRnFr = {read=FOnValidateRnFr, write=FOnValidateRnFr};
	__property TFtpSrvValidateXferEvent OnValidateRnTo = {read=FOnValidateRnTo, write=FOnValidateRnTo};
	__property TFtpSrvValidateXferEvent OnValidateGet = {read=FOnValidateGet, write=FOnValidateGet};
	__property TFtpSrvDataAvailableEvent OnStorDataAvailable = {read=FOnStorDataAvailable, write=FOnStorDataAvailable};
	__property TFtpSrvGetUniqueFileNameEvent OnGetUniqueFileName = {read=FOnGetUniqueFileName, write=FOnGetUniqueFileName};
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint FtpServerVersion = 0x75;
extern PACKAGE AnsiString CopyRight;
static const Word WM_FTPSRV_CLOSE_REQUEST = 0x401;
static const Word WM_FTPSRV_CLIENT_CLOSED = 0x402;
static const Word WM_FTPSRV_ABORT_TRANSFER = 0x403;
static const Word WM_FTPSRV_CLOSE_DATA = 0x404;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Ftpsrv */
using namespace Ftpsrv;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FtpSrv
