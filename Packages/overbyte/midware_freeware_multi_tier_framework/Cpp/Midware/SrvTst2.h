#ifndef SrvTst2H
#define SrvTst2H
#include <DBTables.hpp>
#include <Db.hpp>
#include <Windows.hpp>
#include <SysInit.hpp>
#include <System.hpp>

struct TUserDataRecord
{
	Dbtables::TTable* CliTable;
	Dbtables::TQuery* CliQuery;
} ;

typedef TUserDataRecord *PUserDataRecord;

#endif	// SrvTst2
