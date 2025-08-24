/*---------------------------------------------------------------------------

Author:       François PIETTE
Description:  Example of multi-threaded server object for F. Piette's
              middleware (MidWare). Execute SQL request in a thread.
Creation:     Aug 29, 1998 (Translated from Delphi)
Version:      1.04
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
Aug 16, 1999  V1.04 Adapted for BCB4
                    Suppressed intermediate TVarRec

---------------------------------------------------------------------------*/
#include <vcl.h>
#pragma hdrstop
#pragma package(smart_init)

#include <FileCtrl.hpp>
#include "SObjThrd.h"

//---------------------------------------------------------------------------
static long UniqueNumber;
//---------------------------------------------------------------------------
__fastcall TQueryThread::TQueryThread(BOOL CreateSuspended)
    : TThread(Suspended)
{
}
//---------------------------------------------------------------------------
void __fastcall TQueryThread::DisplayMessage(void)
{
     TriggerDisplay(MessageText);
}
//---------------------------------------------------------------------------
void __fastcall TQueryThread::Display(AnsiString Msg)
{
    if (!Terminated && TriggerDisplay) {
        MessageText = Msg;
        Synchronize(DisplayMessage);
    }
}
//---------------------------------------------------------------------------
void __fastcall TQueryThread::Execute(void)
{
    int        Fld;
    AnsiString PrivDir;
    AnsiString SessName;

    try {
        // Thread safe incrementation
        InterlockedIncrement(&UniqueNumber);
        // Generate unique session name and private directory
        SessName = "MWSession" + IntToStr((int)UniqueNumber);
        PrivDir  = PrivateDir + "Private\\"+ SessName;
        ForceDirectories(PrivDir);

        try {
            ThSession = new TSession (NULL);
            try {
                ThSession->SessionName     = SessName;
                ThSession->NetFileDir      = NetFileDir;
                ThSession->PrivateDir      = PrivDir;

                ThDatabase = new TDatabase (ThSession);
                try {
                    ThDatabase->SessionName      = ThSession->SessionName;
                    ThDatabase->LoginPrompt      = FALSE;
                    ThDatabase->KeepConnection   = ThSession->KeepConnections;
                    if (DatabaseName != "") {
                        ThDatabase->DatabaseName = DatabaseName;
                        ThDatabase->DriverName   = DriverName;
                    }
                    else if (AliasName != "") {
                        ThDatabase->AliasName    = AliasName;
                        ThDatabase->DatabaseName = "MidWareDb" + IntToStr((int)UniqueNumber);
                    }

                    if (Params != NULL)
                        ThDatabase->Params       = Params;
                    Display(IntToHex((int)ThreadID, 8) + " Open Database");
                    ThDatabase->Open();

                    ThQuery = new TQuery (NULL);
                    try {
                        ThQuery->SessionName   = ThSession->SessionName;
                        ThQuery->DatabaseName  = ThDatabase->DatabaseName;
                        ThQuery->SQL->Clear();
                        ThQuery->SQL->Add(SQLStatement);

                        // Open the query
                        Display(IntToHex((int)ThreadID, 8) + " Query Open");
                        ThQuery->Open();
                        Display(IntToHex((int)ThreadID, 8) + " Query Opened");
                        // Data found
                        *ResultStatus = 200;
                        // Copy all records from the result set to the response
                        while (!Terminated && !ThQuery->Eof) {
                            // Copy all fields from the record to the response
                            for (Fld = 0; Fld < ThQuery->FieldCount; Fld++) {
#if __BORLANDC__ == 0x530
                                ResponseBuffer->WriteFields(
                                    Fld == 0,
                                    ARRAYOFCONST((*ThQuery->Fields[Fld])));
#else
                                ResponseBuffer->WriteFields(
                                    Fld == 0,
                                    ARRAYOFCONST((*ThQuery->Fields->Fields[Fld])));
#endif
                            }
                            ThQuery->Next();
                        }
                        ThQuery->Close();
                        ThDatabase->Close();
                        ThSession->Close();
                        if (Terminated) {
                            *ResultStatus = 401;
                            ResponseBuffer->WriteFields(FALSE,
                                 ARRAYOFCONST(("Thread has been terminated")));
                            return;
                        }
                    }
                    __finally {
                        delete ThQuery;
                        ThQuery = NULL;
                    }
                }
                __finally {
                    delete ThDatabase;
                    ThDatabase = NULL;
                }
            }
            __finally {
                delete ThSession;
                ThSession = NULL;
            }
        }
        __finally {
            RemoveDir(PrivDir);
        }
    }
    catch (Exception &E) {
        *ResultStatus = 400;
        ResponseBuffer->WriteFields(FALSE,
                  ARRAYOFCONST((E.ClassName(), E.Message, SQLStatement)));
    }
    PostMessage(OwnerHandle, WM_FINISH, 0, 0);
}
//---------------------------------------------------------------------------
__fastcall TServerObjectSQLTHREAD::TServerObjectSQLTHREAD(TComponent* Owner)
    : TServerObject(Owner)
{
    FParams       = new TStringList;
    FWindowHandle = AllocateHWnd(WndProc);
}
//---------------------------------------------------------------------------
__fastcall TServerObjectSQLTHREAD::~TServerObjectSQLTHREAD()
{
    if (FParams) {
        delete FParams;
        FParams = NULL;
    }
    if (FWindowHandle) {
        DeallocateHWnd(FWindowHandle);
        FWindowHandle = 0;
    }
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectSQLTHREAD::CopyFromReference(TServerObject *Reference)
{
    TServerObject::CopyFromReference(Reference);
    FDatabaseName = ((TServerObjectSQLTHREAD *)Reference)->DatabaseName;
    FDriverName   = ((TServerObjectSQLTHREAD *)Reference)->DriverName;
    FAliasName    = ((TServerObjectSQLTHREAD *)Reference)->AliasName;
    FNetFileDir   = ((TServerObjectSQLTHREAD *)Reference)->NetFileDir;
    FPrivateDir   = ((TServerObjectSQLTHREAD *)Reference)->PrivateDir;
    FParams->Assign(((TServerObjectSQLTHREAD *)Reference)->Params);
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectSQLTHREAD::SetAliasName(AnsiString newValue)
{
    FAliasName    = newValue;
    FDriverName   = "";
    FDatabaseName = "";
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectSQLTHREAD::SetDriverName(AnsiString newValue)
{
    FDriverName = newValue;
    FAliasName  = "";
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectSQLTHREAD::SetPrivateDir(AnsiString newValue)
{
    FPrivateDir = newValue;
    if ((FPrivateDir.Length() > 0) &&
        (FPrivateDir[FPrivateDir.Length()] != '\\'))
            FPrivateDir = FPrivateDir + '\\';
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectSQLTHREAD::SetDatabaseName(AnsiString newValue)
{
    FDatabaseName = newValue;
    FAliasName    = "";
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectSQLTHREAD::SetParams(TStrings *newValue)
{
    FParams->Assign(newValue);
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectSQLTHREAD::Execute(void)
{
    FWorkerThread                  = new TQueryThread (TRUE);
    FWorkerThread->TriggerDisplay  = TriggerDisplay;
    FWorkerThread->ResponseBuffer  = FResponseBuffer;
    FWorkerThread->ResultStatus    = &FResultStatus;
    FWorkerThread->AliasName       = FAliasName;
    FWorkerThread->DatabaseName    = FDatabaseName;
    FWorkerThread->DriverName      = FDriverName;
    FWorkerThread->Params          = FParams;
    FWorkerThread->NetFileDir      = FNetFileDir;
    FWorkerThread->PrivateDir      = FPrivateDir;
    FWorkerThread->SQLStatement    = FRequestBuffer->Fields[0];
    FWorkerThread->OwnerHandle     = FWindowHandle;
    FWorkerThread->FreeOnTerminate = TRUE;
    FWorkerThread->Resume();
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectSQLTHREAD::WMFinish(TMessage &Message)
{
    Finish();
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectSQLTHREAD::WndProc(Messages::TMessage &MsgRec)
{
     if (MsgRec.Msg == WM_FINISH)
         WMFinish(MsgRec);
     else
         MsgRec.Result = DefWindowProc(FWindowHandle, MsgRec.Msg,
                                       MsgRec.WParam, MsgRec.LParam);
}
//---------------------------------------------------------------------------
namespace Sobjthrd
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass MidWareClasses[1] = {__classid(TServerObjectSQLTHREAD)};
        RegisterComponents("fpiette", MidWareClasses, 0);
    }
}
//---------------------------------------------------------------------------

