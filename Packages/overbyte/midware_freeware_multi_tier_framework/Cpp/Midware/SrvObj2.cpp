/*---------------------------------------------------------------------------

Author:       François PIETTE
Description:  Example of multi-threaded server object for F. Piette's
              middleware (MidWare).
              Part of the SrvTst sample application server.
              Does nothing except wait for 5 seconds and then returns
              some funny message.
Creation:     June 22, 1998 (from Delphi version created February 27, 1998)
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

#include "SrvObj2.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
// Worker thread code
//---------------------------------------------------------------------------
__fastcall TLengthyThread::TLengthyThread(bool CreateSuspended)
    : TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall TLengthyThread::Execute(void)
{
    Sleep(5000);                 // Wait for 5 secs
    FResponseBuffer->WriteFields(FALSE,
        ARRAYOFCONST(("Thread job is done (5 seconds sleep)")));
}
//---------------------------------------------------------------------------
// TServerObject code
//---------------------------------------------------------------------------
__fastcall TServerObjectTHREAD::TServerObjectTHREAD(TComponent* Owner)
    : TServerObject(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectTHREAD::Execute(void)
{
    FWorkerThread                  = new TLengthyThread(TRUE);
    FWorkerThread->FResponseBuffer = FResponseBuffer;
    FWorkerThread->OnTerminate     = ThreadJobDone;
    FWorkerThread->FreeOnTerminate = TRUE;
    FWorkerThread->Resume();
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectTHREAD::ThreadJobDone(TObject *Sender)
{
    FResponseBuffer->WriteFields(TRUE,
                                 ARRAYOFCONST(("Worker Thread terminated")));
    FResultStatus = 200;
    TriggerDisplay("THREAD terminated");
    Finish();
}
//---------------------------------------------------------------------------

