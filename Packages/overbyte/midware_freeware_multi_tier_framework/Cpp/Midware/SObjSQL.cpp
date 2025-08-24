/*---------------------------------------------------------------------------

Author:       François PIETTE
Description:  Server Object sample for F. Piette's Middleware (MidWare)
              Show how to use a TQuery and returns the result set.
Creation:     Aug 26, 1998 (translated from Delphi)
Version:      1.01
EMail:        francois.piette@overbyte.be   francois.piette@rtfm.be
              http://www.overbyte.be        http://www.rtfm.be/fpiette
              francois.piette@pophost.eunet.be
Support:      Use the mailing list midware@elists.org
              Follow "support" link at http://www.overbyte.be for subscription.
Legal issues: Copyright (C) 1998-2002 by François PIETTE
              Rue de Grady 24, 4053 Embourg, Belgium. Fax: +32-4-365.74.56
              <francois.piette@overbyte.be> <francois.piette@pophost.eunet.be>

              This software is provided 'as-is', without any express or
              implied warranty.  In no event will the author be held liable
              for any  damages arising from the use of this software.

              Permission is granted to anyone to use this software and or any
              derived or altered versions for any purpose, excluding commercial
              applications. You can use this software for personal or internal
              use only. You may distribute it freely untouched.
              The following restrictions applies:

              1. The origin of this software must not be misrepresented, you
                 must not claim that you wrote the original software.

              2. If you use this software in a product, an acknowledgment in
                 the product documentation and displayed on screen is required.
                 The text must be: "This product is based on MidWare. Freeware
                 source code is available at http://www.rtfm.be/fpiette."

              3. Altered source versions must be plainly marked as such, and
                 must not be misrepresented as being the original software.

              4. This notice may not be removed or altered from any source
                 distribution and must be added to the product documentation.

Updates:
Aug 16, 1999  V1.01 Adapted for BCB4
                    Suppressed intermediate TVarRec

---------------------------------------------------------------------------*/
#include <vcl.h>
#pragma hdrstop

#include "SObjSQL.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall TServerObjectSQL::TServerObjectSQL(TComponent* Owner)
    : TServerObject(Owner)
{
    FQuery = new TQuery(this);
}
//---------------------------------------------------------------------------
__fastcall TServerObjectSQL::~TServerObjectSQL()
{
    if (FQuery) {
        delete FQuery;
        FQuery = NULL;
    }
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectSQL::Execute(void)
{
    int        Fld;
    AnsiString SQLStatement;

    if (!FQuery) {
        FResultStatus = 400;
        FResponseBuffer->Rewrite();
        FResponseBuffer->WriteFields(FALSE,
                  ARRAYOFCONST(("No query object at server side")));
        Finish();
        return;
    }

    try {
        SQLStatement = FRequestBuffer->Fields[0];
        FQuery->Close();
        FQuery->SQL->Clear();
        FQuery->SQL->Add(SQLStatement);
        FQuery->UniDirectional = TRUE;
        FQuery->Open();
        // Data found
        FResultStatus = 200;
        // Copy all records from the result set to the response
        while (!FQuery->Eof) {
            // Copy all fields from the record to the response
            for (Fld = 0; Fld < FQuery->FieldCount; Fld++) {
#if __BORLANDC__ == 0x530
                FResponseBuffer->WriteFields(
                    Fld == 0,
                    ARRAYOFCONST((*FQuery->Fields[Fld])));
#else
                FResponseBuffer->WriteFields(
                    Fld == 0,
                    ARRAYOFCONST((*FQuery->Fields->Fields[Fld])));
#endif
            }
            FQuery->Next();
        }
        FQuery->Close();
    }
    catch (Exception &E) {
        FResultStatus = 400;
        FResponseBuffer->Rewrite();
        FResponseBuffer->WriteFields(FALSE,
                  ARRAYOFCONST((E.Message, SQLStatement)));
    }

    Finish();
}
//---------------------------------------------------------------------------
AnsiString __fastcall TServerObjectSQL::GetDatabaseName(void)
{
    if (FQuery)
        return(FQuery->DatabaseName);
    else
        return("");
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectSQL::SetDatabaseName(AnsiString newValue)
{
    if (FQuery)
        FQuery->DatabaseName = Trim(newValue);
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectSQL::CopyFromReference(TServerObject *Reference)
{
    TServerObject::CopyFromReference(Reference);
    DatabaseName = ((TServerObjectSQL *)Reference)->DatabaseName;
}
//---------------------------------------------------------------------------
namespace Sobjsql
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass MidWareClasses[1] = {__classid(TServerObjectSQL)};
        RegisterComponents("fpiette", MidWareClasses, 0);
    }
}
//---------------------------------------------------------------------------

