/*---------------------------------------------------------------------------

Author:       François PIETTE
Description:  Example of very basic server object.
              Just returns the input fields converted to uppercase.
              Part of the SrvTst sample application server.
Creation:     June 21, 1998 (from Delphi version created February 26, 1998)
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

#include "SrvObj1.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall TServerObjectUPPER::TServerObjectUPPER(TComponent* Owner)
    : TServerObject(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectUPPER::Initialize(void)
{
    // Just for demo purpose
    TriggerDisplay(FFunctionCode + " is initializing");
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectUPPER::Execute(void)
{
    int           I;
    TMemoryStream *Data;
    AnsiString    Buf;

    // The RequestBuffer is positionned on first record on startup
    while (!FRequestBuffer->Eof) {
        for (I = 0; I < FRequestBuffer->FieldCount; I++) {
            FResponseBuffer->WriteFields(I == 0,
                  ARRAYOFCONST((UpperCase(FRequestBuffer->Fields[I]))));
        }
        FRequestBuffer->Next();
    }

    // Demo for stream data field which can send anything !
    Data = new TMemoryStream;
    Buf  = "A CR/LF pair embeded here after\r\nthe CR/LF before";
    Data->WriteBuffer(Buf.c_str(), Buf.Length());
    Data->Seek(0, 0);
    FResponseBuffer->WriteStreamField(TRUE, mwString, Data);
    delete Data;

    // Write one more ordinary fields
    FResponseBuffer->WriteFields(FALSE,
         ARRAYOFCONST(("One more field", "and another")));

    FResultStatus = 200;
    Finish();
}
//---------------------------------------------------------------------------
namespace Srvobj1
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass MidWareClasses[1] = {__classid(TServerObjectUPPER)};
        RegisterComponents("fpiette", MidWareClasses, 0);
    }
}
//---------------------------------------------------------------------------

