/*---------------------------------------------------------------------------

Author:       François PIETTE
Description:  Server Object sample for F. Piette's Middleware (MidWare)
              Show how to use a TQuery and returns the result set.
Creation:     June 21, 1998 (from Delphi version created March 20, 1998)
Version:      1.02
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
May 23, 1998  V1.01 Changed table layout to use english names for columns.
Aug 16, 1999  V1.02 Passed TField to WriteFields
                    Adapted for BCB4


---------------------------------------------------------------------------*/
#include <vcl.h>
#pragma hdrstop

#include "SrvObj4.h"
#include "SrvTst2.h"
#define  VersionServerObjectGETCLIENTLIKE 102
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TServerObjectGETCLIENTLIKE::TServerObjectGETCLIENTLIKE(TComponent* Owner)
    : TServerObject(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectGETCLIENTLIKE::Execute(void)
{
    PUserDataRecord UData;
    int             Fld;
    AnsiString      Key;
    AnsiString      Value;

    try {
        UData = (PUserDataRecord)FUserData;
        Key   = UpperCase(FRequestBuffer->Fields[0]);
        UData->CliQuery->Close();
        UData->CliQuery->SQL->Clear();
        UData->CliQuery->SQL->Add("SELECT * FROM CLIENTS"
                                  " WHERE LAST LIKE '" + Key + "%'"
                                  " ORDER BY LAST");
        UData->CliQuery->Open();
        // Data found
        FResultStatus = 200;
        // Copy all records from the result set to the response
        while (!UData->CliQuery->Eof) {
            // Copy all fields from the record to the response
            for (Fld = 0; Fld < UData->CliQuery->FieldCount; Fld++) {
#if __BORLANDC__ == 0x530
                FResponseBuffer->WriteFields(FALSE,
                    ARRAYOFCONST((*UData->CliQuery->Fields[Fld])));
#else
                FResponseBuffer->WriteFields(FALSE,
                    ARRAYOFCONST((*UData->CliQuery->Fields->Fields[Fld])));
#endif
            }
            UData->CliQuery->Next();
        }
        UData->CliQuery->Close();
    }
    catch (const Exception& E) {
        // Data not found
        FResultStatus = 400;
        FResponseBuffer->WriteFields(FALSE, ARRAYOFCONST((Key, "not found")));
    }

    Finish();
}
//---------------------------------------------------------------------------

