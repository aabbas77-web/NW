// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'WSocketS.pas' rev: 6.00

#ifndef WSocketSHPP
#define WSocketSHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <WinSock.hpp>	// Pascal unit
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

namespace Wsockets
{
//-- type declarations -------------------------------------------------------
typedef TMetaClass*TWSocketClientClass;

class DELPHICLASS TWSocketClient;
typedef void __fastcall (__closure *TWSocketClientCreateEvent)(System::TObject* Sender, TWSocketClient* Client);

typedef void __fastcall (__closure *TWSocketClientConnectEvent)(System::TObject* Sender, TWSocketClient* Client, Word Error);

class DELPHICLASS TCustomWSocketServer;
class PASCALIMPLEMENTATION TCustomWSocketServer : public Wsocket::TWSocket 
{
	typedef Wsocket::TWSocket inherited;
	
protected:
	AnsiString FBanner;
	AnsiString FBannerToBusy;
	TMetaClass*FClientClass;
	Classes::TList* FClientList;
	int FClientNum;
	int FMaxClients;
	TWSocketClientCreateEvent FOnClientCreate;
	TWSocketClientConnectEvent FOnClientConnect;
	TWSocketClientConnectEvent FOnClientDisconnect;
	virtual void __fastcall WndProc(Messages::TMessage &MsgRec);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation operation);
	virtual void __fastcall TriggerSessionAvailable(Word Error);
	virtual void __fastcall TriggerClientCreate(TWSocketClient* Client);
	virtual void __fastcall TriggerClientConnect(TWSocketClient* Client, Word Error);
	virtual void __fastcall TriggerClientDisconnect(TWSocketClient* Client, Word Error);
	virtual int __fastcall GetClientCount(void);
	virtual TWSocketClient* __fastcall GetClient(int nIndex);
	MESSAGE void __fastcall WMClientClosed(Messages::TMessage &msg);
	
public:
	__fastcall virtual TCustomWSocketServer(Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomWSocketServer(void);
	bool __fastcall IsClient(System::TObject* SomeThing);
	
protected:
	__property TMetaClass* ClientClass = {read=FClientClass, write=FClientClass};
	__property int ClientCount = {read=GetClientCount, nodefault};
	__property TWSocketClient* Client[int nIndex] = {read=GetClient};
	
__published:
	__property AnsiString Banner = {read=FBanner, write=FBanner};
	__property AnsiString BannerToBusy = {read=FBannerToBusy, write=FBannerToBusy};
	__property int MaxClients = {read=FMaxClients, write=FMaxClients, nodefault};
	__property TWSocketClientConnectEvent OnClientDisconnect = {read=FOnClientDisconnect, write=FOnClientDisconnect};
	__property TWSocketClientConnectEvent OnClientConnect = {read=FOnClientConnect, write=FOnClientConnect};
	__property TWSocketClientCreateEvent OnClientCreate = {read=FOnClientCreate, write=FOnClientCreate};
};


class PASCALIMPLEMENTATION TWSocketClient : public Wsocket::TWSocket 
{
	typedef Wsocket::TWSocket inherited;
	
protected:
	AnsiString FBanner;
	TCustomWSocketServer* FServer;
	AnsiString FPeerAddr;
	AnsiString FPeerPort;
	bool FSessionClosedFlag;
	
public:
	virtual void __fastcall StartConnection(void);
	virtual void __fastcall TriggerSessionClosed(Word Error);
	virtual void __fastcall Dup(int newHSocket);
	virtual AnsiString __fastcall GetPeerAddr();
	virtual AnsiString __fastcall GetPeerPort();
	__property TCustomWSocketServer* Server = {read=FServer, write=FServer};
	
__published:
	__property AnsiString Banner = {read=FBanner, write=FBanner};
public:
	#pragma option push -w-inl
	/* TCustomLineWSocket.Create */ inline __fastcall virtual TWSocketClient(Classes::TComponent* AOwner) : Wsocket::TWSocket(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomLineWSocket.Destroy */ inline __fastcall virtual ~TWSocketClient(void) { }
	#pragma option pop
	
};


class DELPHICLASS TWSocketServer;
class PASCALIMPLEMENTATION TWSocketServer : public TCustomWSocketServer 
{
	typedef TCustomWSocketServer inherited;
	
public:
	__property ClientClass ;
	__property ClientCount ;
	__property Client ;
	
__published:
	__property Banner ;
	__property BannerToBusy ;
	__property MaxClients ;
	__property OnClientDisconnect ;
	__property OnClientConnect ;
public:
	#pragma option push -w-inl
	/* TCustomWSocketServer.Create */ inline __fastcall virtual TWSocketServer(Classes::TComponent* AOwner) : TCustomWSocketServer(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomWSocketServer.Destroy */ inline __fastcall virtual ~TWSocketServer(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint WSocketServerVersion = 0x68;
extern PACKAGE AnsiString CopyRight;
static const Word WM_CLIENT_CLOSED = 0x41e;
#define DefaultBanner "Welcome to TcpSrv"
extern PACKAGE void __fastcall Register(void);

}	/* namespace Wsockets */
using namespace Wsockets;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// WSocketS
