// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'SrvTst2.pas' rev: 6.00

#ifndef SrvTst2HPP
#define SrvTst2HPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <DBTables.hpp>	// Pascal unit
#include <DB.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Srvtst2
{
//-- type declarations -------------------------------------------------------
#pragma pack(push, 4)
struct TUserDataRecord
{
	Dbtables::TTable* CliTable;
	Dbtables::TQuery* CliQuery;
	Dbtables::TTable* ImgTable;
} ;
#pragma pack(pop)

typedef TUserDataRecord *PUserDataRecord;

//-- var, const, procedure ---------------------------------------------------

}	/* namespace Srvtst2 */
using namespace Srvtst2;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// SrvTst2
