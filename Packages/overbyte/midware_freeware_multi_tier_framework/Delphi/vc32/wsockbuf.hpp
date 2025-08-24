// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'WSockBuf.pas' rev: 6.00

#ifndef WSockBufHPP
#define WSockBufHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Wsockbuf
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TBuffer;
class PASCALIMPLEMENTATION TBuffer : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	void *Buf;
	int FBufSize;
	int WrCount;
	int RdCount;
	__fastcall virtual TBuffer(int nSize);
	__fastcall virtual ~TBuffer(void);
	int __fastcall Write(void * Data, int Len);
	int __fastcall Read(void * Data, int Len);
	void * __fastcall Peek(int &Len);
	int __fastcall Remove(int Len);
	void __fastcall SetBufSize(int newSize);
	__property int BufSize = {read=FBufSize, write=SetBufSize, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
static const Byte WSockBufVersion = 0xc9;

}	/* namespace Wsockbuf */
using namespace Wsockbuf;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// WSockBuf
