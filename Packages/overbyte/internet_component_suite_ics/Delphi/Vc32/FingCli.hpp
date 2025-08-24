// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FingCli.pas' rev: 6.00

#ifndef FingCliHPP
#define FingCliHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <WSocket.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fingcli
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TFingerCli;
class PASCALIMPLEMENTATION TFingerCli : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
__published:
	__fastcall virtual TFingerCli(Classes::TComponent* AOwner);
	__fastcall virtual ~TFingerCli(void);
	void __fastcall StartQuery(void);
	int __fastcall Receive(void * Buffer, int Len);
	void __fastcall Abort(void);
	
protected:
	Wsocket::TWSocket* FWSocket;
	AnsiString FQuery;
	bool FQueryDoneFlag;
	Wsocket::TSessionConnected FOnSessionConnected;
	Wsocket::TDataAvailable FOnDataAvailable;
	Wsocket::TSessionClosed FOnQueryDone;
	void __fastcall WSocketDnsLookupDone(System::TObject* Sender, Word Error);
	void __fastcall WSocketSessionConnected(System::TObject* Sender, Word Error);
	void __fastcall WSocketDataAvailable(System::TObject* Sender, Word Error);
	void __fastcall WSocketSessionClosed(System::TObject* Sender, Word Error);
	void __fastcall TriggerQueryDone(Word Error);
	
__published:
	__property AnsiString Query = {read=FQuery, write=FQuery};
	__property Wsocket::TSessionConnected OnSessionConnected = {read=FOnSessionConnected, write=FOnSessionConnected};
	__property Wsocket::TDataAvailable OnDataAvailable = {read=FOnDataAvailable, write=FOnDataAvailable};
	__property Wsocket::TSessionClosed OnQueryDone = {read=FOnQueryDone, write=FOnQueryDone};
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint FingCliVersion = 0x66;
extern PACKAGE AnsiString CopyRight;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Fingcli */
using namespace Fingcli;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FingCli
