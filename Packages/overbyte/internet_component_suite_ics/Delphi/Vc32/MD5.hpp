// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'MD5.pas' rev: 6.00

#ifndef MD5HPP
#define MD5HPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Md5
{
//-- type declarations -------------------------------------------------------
#pragma pack(push, 4)
struct TMD5Context
{
	int State[4];
	int Count[2];
	union
	{
		struct 
		{
			int BufLong[16];
			
		};
		struct 
		{
			Byte BufChar[64];
			
		};
		
	};
} ;
#pragma pack(pop)

typedef char TMD5Digest[16];

//-- var, const, procedure ---------------------------------------------------
static const Shortint MD5Version = 0x66;
extern PACKAGE AnsiString CopyRight;
extern PACKAGE void __fastcall MD5Init(TMD5Context &MD5Context);
extern PACKAGE void __fastcall MD5Update(TMD5Context &MD5Context, const void *Data, int Len);
extern PACKAGE void __fastcall MD5Final(char * Digest, TMD5Context &MD5Context);
extern PACKAGE void __fastcall MD5Transform(int * Buf, const int Buf_Size, const int * Data, const int Data_Size);
extern PACKAGE void __fastcall MD5UpdateBuffer(TMD5Context &MD5Context, void * Buffer, int BufSize);
extern PACKAGE AnsiString __fastcall GetMD5(void * Buffer, int BufSize);
extern PACKAGE AnsiString __fastcall StrMD5(AnsiString Buffer);

}	/* namespace Md5 */
using namespace Md5;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// MD5
