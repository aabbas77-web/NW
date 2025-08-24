// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ApServer.pas' rev: 6.00

#ifndef ApServerHPP
#define ApServerHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <WinSock.hpp>	// Pascal unit
#include <WSocket.hpp>	// Pascal unit
#include <ApSrvCli.hpp>	// Pascal unit
#include <RFormat.hpp>	// Pascal unit
#include <RBroker.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Apserver
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TClientEvent)(System::TObject* Sender, Apsrvcli::TClientWSocket* CliWSocket);

typedef void __fastcall (__closure *TClientCommandEvent)(System::TObject* Sender, Apsrvcli::TClientWSocket* CliWSocket, char * CmdBuf, int CmdLen);

typedef void __fastcall (__closure *TClientTimeoutEvent)(System::TObject* Sender, Apsrvcli::TClientWSocket* CliWSocket, bool &CanClose);

typedef void __fastcall (__closure *TClientBgException)(System::TObject* Sender, Apsrvcli::TClientWSocket* CliWSocket, Sysutils::Exception* E);

typedef void __fastcall (__closure *TProcessRequestEvent)(System::TObject* Sender, Apsrvcli::TClientWSocket* CliWSocket, char * &CmdBuf, int &CmdLen);

typedef void __fastcall (__closure *TAppServerBgExceptionEvent)(System::TObject* Sender, Sysutils::Exception* E);

#pragma option push -b-
enum TAppServerOption { asoAutoStart, asoDisplayCommands, asoDisplayClientCount };
#pragma option pop

typedef Set<TAppServerOption, asoAutoStart, asoDisplayClientCount>  TAppServerOptions;

typedef TMetaClass*TClientWSocketClass;

class DELPHICLASS TAppServer;
class PASCALIMPLEMENTATION TAppServer : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
protected:
	AnsiString FBanner;
	Stdctrls::TCustomMemo* FDisplayMemo;
	TMetaClass*FClientClass;
	Stdctrls::TLabel* FClientCountLabel;
	Classes::TList* FClientList;
	int FRequestCount;
	int FConnectCount;
	Rbroker::TRequestBroker* FRequestBroker;
	Wsocket::TWSocket* FSrvWSocket;
	AnsiString FPort;
	HWND FHandle;
	int FClientTimeout;
	int FTimeoutInterval;
	Extctrls::TTimer* FTimer;
	_OSVERSIONINFOA FSysVersionInfo;
	TAppServerOptions FOptions;
	Apsrvcli::TDisplayEvent FOnDisplay;
	TClientEvent FOnClientConnected;
	TClientEvent FOnClientClosed;
	TClientCommandEvent FOnClientCommand;
	TClientTimeoutEvent FOnClientTimeout;
	TClientBgException FOnClientBgException;
	TClientEvent FOnBeforeSendReply;
	TClientEvent FOnAfterSendReply;
	TProcessRequestEvent FOnBeforeProcessRequest;
	TProcessRequestEvent FOnAfterProcessRequest;
	TAppServerBgExceptionEvent FOnServerBgException;
	virtual void __fastcall WndProc(Messages::TMessage &MsgRec);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation operation);
	void __fastcall SrvWSocketSessionAvailable(System::TObject* Sender, Word Error);
	void __fastcall CliSessionClosed(System::TObject* Sender, Word Error);
	virtual void __fastcall SendResponseToClient(System::TObject* Dest, Rbroker::TRequestBroker* ORB, int Status, char * Response, int Len);
	virtual void __fastcall SendStringResponseToClient(System::TObject* Dest, Rbroker::TRequestBroker* ORB, int Status, AnsiString Response);
	void __fastcall ProcessClientCommand(System::TObject* Sender, char * CmdBuf, int CmdLen);
	void __fastcall ProcessClientBgException(System::TObject* Sender, Sysutils::Exception* E, bool &CanClose);
	void __fastcall ProcessClientOverflow(System::TObject* Sender, bool &CanAbort);
	int __fastcall GetClientCount(void);
	Apsrvcli::TClientWSocket* __fastcall GetClientWSocket(int nIndex);
	void __fastcall SetClientTimeout(int newValue);
	void __fastcall SetTimeoutInterval(int newValue);
	void __fastcall TimerTimer(System::TObject* Sender);
	virtual void __fastcall CliTimeout(System::TObject* Sender, bool &CanClose);
	virtual void __fastcall Loaded(void);
	void __fastcall InternalDisplay(System::TObject* Sender, AnsiString Msg);
	virtual void __fastcall TriggerBgException(Sysutils::Exception* E);
	
public:
	__fastcall virtual TAppServer(Classes::TComponent* AOwner);
	__fastcall virtual ~TAppServer(void);
	void __fastcall Start(void);
	void __fastcall Stop(void);
	void __fastcall DisconnectAll(void);
	__property Wsocket::TWSocket* SrvWSocket = {read=FSrvWSocket};
	__property int ClientCount = {read=GetClientCount, nodefault};
	__property int ConnectCount = {read=FConnectCount, nodefault};
	__property int RequestCount = {read=FRequestCount, nodefault};
	__property Apsrvcli::TClientWSocket* ClientWSocket[int nIndex] = {read=GetClientWSocket};
	__property HWND Handle = {read=FHandle, nodefault};
	
__published:
	__property Stdctrls::TCustomMemo* DisplayMemo = {read=FDisplayMemo, write=FDisplayMemo};
	__property Stdctrls::TLabel* ClientCountLabel = {read=FClientCountLabel, write=FClientCountLabel};
	__property TAppServerOptions Options = {read=FOptions, write=FOptions, nodefault};
	__property AnsiString Banner = {read=FBanner, write=FBanner};
	__property AnsiString Port = {read=FPort, write=FPort};
	__property int ClientTimeout = {read=FClientTimeout, write=SetClientTimeout, nodefault};
	__property int TimeoutInterval = {read=FTimeoutInterval, write=SetTimeoutInterval, nodefault};
	__property Rbroker::TRequestBroker* RequestBroker = {read=FRequestBroker, write=FRequestBroker};
	__property Apsrvcli::TDisplayEvent OnDisplay = {read=FOnDisplay, write=FOnDisplay};
	__property TClientEvent OnClientConnected = {read=FOnClientConnected, write=FOnClientConnected};
	__property TClientEvent OnClientClosed = {read=FOnClientClosed, write=FOnClientClosed};
	__property TClientCommandEvent OnClientCommand = {read=FOnClientCommand, write=FOnClientCommand};
	__property TClientTimeoutEvent OnClientTimeout = {read=FOnClientTimeout, write=FOnClientTimeout};
	__property TClientBgException OnClientBgException = {read=FOnClientBgException, write=FOnClientBgException};
	__property TClientEvent OnBeforeSendReply = {read=FOnBeforeSendReply, write=FOnBeforeSendReply};
	__property TClientEvent OnAfterSendReply = {read=FOnAfterSendReply, write=FOnAfterSendReply};
	__property TProcessRequestEvent OnBeforeProcessRequest = {read=FOnBeforeProcessRequest, write=FOnBeforeProcessRequest};
	__property TProcessRequestEvent OnAfterProcessRequest = {read=FOnAfterProcessRequest, write=FOnAfterProcessRequest};
	__property TAppServerBgExceptionEvent OnServerBgException = {read=FOnServerBgException, write=FOnServerBgException};
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint ApServerVersion = 0x73;
extern PACKAGE AnsiString CopyRight;
static const Word WM_DESTROY_CLIENT_SOCKET = 0x401;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Apserver */
using namespace Apserver;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ApServer
