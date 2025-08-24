// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'SrvObj2.pas' rev: 6.00

#ifndef SrvObj2HPP
#define SrvObj2HPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <RFormat.hpp>	// Pascal unit
#include <RBroker.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Srvobj2
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TLengthyThread;
class PASCALIMPLEMENTATION TLengthyThread : public Classes::TThread 
{
	typedef Classes::TThread inherited;
	
private:
	Rformat::TMWBuffer* FResponseBuffer;
	
protected:
	virtual void __fastcall Execute(void);
public:
	#pragma option push -w-inl
	/* TThread.Create */ inline __fastcall TLengthyThread(bool CreateSuspended) : Classes::TThread(CreateSuspended) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TThread.Destroy */ inline __fastcall virtual ~TLengthyThread(void) { }
	#pragma option pop
	
};


class DELPHICLASS TServerObjectTHREAD;
class PASCALIMPLEMENTATION TServerObjectTHREAD : public Rbroker::TServerObject 
{
	typedef Rbroker::TServerObject inherited;
	
private:
	TLengthyThread* FWorkerThread;
	void __fastcall ThreadJobDone(System::TObject* Sender);
	
public:
	virtual void __fastcall Execute(void);
protected:
	#pragma option push -w-inl
	/* TServerObject.CreateForFunctionCode */ inline __fastcall virtual TServerObjectTHREAD(Classes::TComponent* AOwner, int Dummy) : Rbroker::TServerObject(AOwner, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TServerObject.Create */ inline __fastcall virtual TServerObjectTHREAD(Classes::TComponent* AOwner) : Rbroker::TServerObject(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TServerObject.Destroy */ inline __fastcall virtual ~TServerObjectTHREAD(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Srvobj2 */
using namespace Srvobj2;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// SrvObj2
