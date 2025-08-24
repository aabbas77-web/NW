// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'SrvObj6.pas' rev: 6.00

#ifndef SrvObj6HPP
#define SrvObj6HPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <DB.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SrvTst2.hpp>	// Pascal unit
#include <RFormat.hpp>	// Pascal unit
#include <RBroker.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Srvobj6
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TSObjGETIMAGE;
class PASCALIMPLEMENTATION TSObjGETIMAGE : public Rbroker::TServerObject 
{
	typedef Rbroker::TServerObject inherited;
	
public:
	virtual void __fastcall Execute(void);
protected:
	#pragma option push -w-inl
	/* TServerObject.CreateForFunctionCode */ inline __fastcall virtual TSObjGETIMAGE(Classes::TComponent* AOwner, int Dummy) : Rbroker::TServerObject(AOwner, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TServerObject.Create */ inline __fastcall virtual TSObjGETIMAGE(Classes::TComponent* AOwner) : Rbroker::TServerObject(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TServerObject.Destroy */ inline __fastcall virtual ~TSObjGETIMAGE(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint VersionServerObjectGETIMAGE = 0x64;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Srvobj6 */
using namespace Srvobj6;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// SrvObj6
