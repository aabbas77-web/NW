/*---------------------------------------------------------------------------

Author:       François PIETTE
Description:  Example of a server object which returns complete file
              as blob field.
              Part of the SrvTst sample application server.
Creation:     June 21, 1998 (from Delphi version created April 24, 1998)
Version:      1.00
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

---------------------------------------------------------------------------*/
#include <vcl.h>
#pragma hdrstop

#include "SrvObj5.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TServerObjectGETFILE::TServerObjectGETFILE(TComponent* Owner)
    : TServerObject(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectGETFILE::Execute(void)
{
    TFileStream *Data;
    AnsiString  FileName;

    // The RequestBuffer is positionned on first record on startup
    FileName = Trim(FRequestBuffer->Fields[0]);

    if (FileName.Length() == 0) {
        FResponseBuffer->WriteFields(TRUE, ARRAYOFCONST(("Missing file name")));
        FResultStatus = 400;
        Finish();
    }

    try {
        Data = new TFileStream(FileName, fmOpenRead | fmShareDenyNone);
        Data->Seek(0, 0);
        FResponseBuffer->WriteFields(TRUE, ARRAYOFCONST((FileName)));
        FResponseBuffer->WriteStreamField(FALSE, mwString, Data);
        delete Data;
        FResultStatus = 200;
    }
    catch (const Exception& E) {
        FResponseBuffer->WriteFields(TRUE,
                                     ARRAYOFCONST(("Error", E.Message)));
        FResultStatus = 400;
    }
    Finish();
}
//---------------------------------------------------------------------------
