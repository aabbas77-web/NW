/*---------------------------------------------------------------------------

Author:       François PIETTE
Description:  Simple server demo for F. Piette's middleware (MidWare).
Creation:     Aug 24, 1998 (From Delphi Version)
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
Aug 18, 1999  V1.01 Adapted for BCB4

----------------------------------------------------------------------------*/
#include <vcl.h>
#pragma hdrstop

#include "SrvDemo1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ApServer"
#pragma link "RBroker"
#pragma link "SObjSQL"
#pragma link "SrvObj1"
#pragma link "SObjThrd"
#pragma link "ApServer"
#pragma link "RBroker"
#pragma link "SObjSQL"
#pragma link "SObjThrd"
#pragma link "SrvObj1"
#pragma resource "*.dfm"
TSrvDemoForm *SrvDemoForm;
//---------------------------------------------------------------------------
__fastcall TSrvDemoForm::TSrvDemoForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSrvDemoForm::FormCreate(TObject *Sender)
{
    AnsiString Buffer;
    int        Len;

    Buffer.SetLength(256);
    Len = GetEnvironmentVariable("TEMP", Buffer.c_str(), Buffer.Length());
    if (Len <= 0) {
        Len = GetEnvironmentVariable("TMP", Buffer.c_str(), Buffer.Length());
        if (Len <= 0) {
            Buffer = "C:\TEMP";
            Len    = Buffer.Length();
        }
    }
    Buffer.SetLength(Len);

    ServerObjectSQLTHREAD1->NetFileDir = Buffer;
    ServerObjectSQLTHREAD1->PrivateDir = Buffer;
    if (ServerObjectSQLTHREAD1->DatabaseName == "")
        ServerObjectSQLTHREAD1->DatabaseName = ExtractFilePath(Application->ExeName);
}
//---------------------------------------------------------------------------
void __fastcall TSrvDemoForm::RequestBroker1Display(TObject *Sender,
      AnsiString Msg)
{
    // Prevent TMemo overflow
    if (DisplayMemo->Lines->Count > 200)
        DisplayMemo->Clear();
}
//---------------------------------------------------------------------------

