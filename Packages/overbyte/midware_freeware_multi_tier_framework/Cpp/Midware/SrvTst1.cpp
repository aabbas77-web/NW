/*---------------------------------------------------------------------------

Author:       François PIETTE
Description:  Application Server sample for F. Piette's Middleware (MidWare)
              Work with CliTst, the corresponding client application.
Creation:     June 21, 1998 (from Delphi version created February 17, 1998)
Version:      1.05
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
Mar 20, 1998 V1.01 Adapted to changes made in TMWBuffer (rformat.pas)
             Added SrvObj4 to show how a TQuery could be used
May 20, 1998 V1.02 Added Dispose(FUserData)
May 23, 1998 V1.03 Added version display on startup
Jun 07, 1998 V1.04 Implemented encryption in commands and replies.
Aug 16, 1999 V1.05 Adapted for BCB4

---------------------------------------------------------------------------*/
#include <stdlib.h>
#include <vcl.h>
#include <vcl\inifiles.hpp>
#pragma hdrstop

#include "SrvTst1.h"
#include "SrvObj1.h"
#include "SrvObj2.h"
#include "SrvObj3.h"
#include "SrvObj4.h"
#include "SrvObj5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ApServer"
#pragma link "RBroker"
#pragma resource "*.dfm"

#define SrvTstVersion  105
#define MainTitle      "MidWare Test Server"
#define SectionData    "Data"
#define KeyPort        "Port"
#define SectionWindow  "Window"
#define KeyTop         "Top"
#define KeyLeft        "Left"
#define KeyWidth       "Width"
#define KeyHeight      "Height"

TServerForm *ServerForm;
//---------------------------------------------------------------------------
__fastcall TServerForm::TServerForm(TComponent* Owner)
    : TForm(Owner)
{
    // Build Ini file name
    FIniFileName = LowerCase(ExtractFileName(Application->ExeName));
    FIniFileName = FIniFileName.SubString(1, FIniFileName.Length() - 3) + "ini";
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::FormCreate(TObject *Sender)
{
    // Initialize RequestBroker object
    RequestBroker1->IniFileName = FIniFileName;
    RequestBroker1->AddServerObject(__classid(TServerObjectUPPER));
    RequestBroker1->AddServerObject(__classid(TServerObjectTHREAD));
    RequestBroker1->AddServerObject(__classid(TServerObjectGETCLIENT));
    RequestBroker1->AddServerObject(__classid(TServerObjectGETCLIENTLIKE));
    RequestBroker1->AddServerObject(__classid(TServerObjectGETFILE));

    // It's a good place to initialize TRequestBroker.UserData with for example
    // a pointer to a dynamically allocated record or to an object.
    // UserData is passed to ServerObjects instanciated by the broker. Using
    // it, they can gain access to some global data or procedure, such as data
    // base session.

    // In this sample we use a TUserDataRecord record
    FUserData = new TUserDataRecord;
    RequestBroker1->UserData = (long)FUserData;

    // Initialize user interface
    ObjectCountLabel->Caption = "0";
    ClientCountLabel->Caption = "0";
    DisplayMemo->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::FormDestroy(TObject *Sender)
{
    if (FUserData) {
        delete FUserData;
        FUserData = NULL;
    }
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::FormShow(TObject *Sender)
{
    TIniFile *IniFile;
DisplayMemo->Lines->Add("FormShow");

    if (!FInitialized ) {
        FInitialized = TRUE;
        Caption      = "Starting " MainTitle;

        IniFile = new TIniFile(FIniFileName);
        Top     = IniFile->ReadInteger(SectionWindow, KeyTop,    Top);
        Left    = IniFile->ReadInteger(SectionWindow, KeyLeft,   Left);
        Width   = IniFile->ReadInteger(SectionWindow, KeyWidth,  Width);
        Height  = IniFile->ReadInteger(SectionWindow, KeyHeight, Height);
        FPort   = IniFile->ReadString(SectionData,    KeyPort,   "2106");
        delete IniFile;

        DisplayMemo->Lines->Add("Starting");
        // We use a custom message to initialize things once the form
        // is visible
        PostMessage(Handle, WM_APPSTARTUP, 0, 0);
    }
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    TIniFile *IniFile;

    AppServer1->Stop();
    AppServer1->DisconnectAll();
    IniFile = new TIniFile(FIniFileName);
    IniFile->WriteInteger(SectionWindow, KeyTop,    Top);
    IniFile->WriteInteger(SectionWindow, KeyLeft,   Left);
    IniFile->WriteInteger(SectionWindow, KeyWidth,  Width);
    IniFile->WriteInteger(SectionWindow, KeyHeight, Height);
    IniFile->WriteString(SectionData,    KeyPort,   FPort);
    delete IniFile;
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::DisconnectAllButtonClick(TObject *Sender)
{
    AppServer1->DisconnectAll();
    ClientCountLabel->Caption = IntToStr(AppServer1->ClientCount);
}
//---------------------------------------------------------------------------
// This message handler is triggered by the FormShow event. We comes here
// only when the form is visible on screen.
void __fastcall TServerForm::WMAppStartup(TMessage &Msg)
{
    HWND       PrvWnd;
    TWSAData   Data;

    // Prevent the server from running twice
    PrvWnd = FindWindow(String(ClassName()).c_str(), MainTitle);
    if (PrvWnd != 0) {
        Close();
        return;
    }
    Caption = MainTitle;
    Update();             // It's nice to have the form completely displayed

    // Display all pertinent info versions
    DisplayMemo->Lines->Add(Format("Midware SrvTst version %d.%2.2d" ,
                    ARRAYOFCONST((SrvTstVersion / 100, SrvTstVersion % 100))));
    DisplayMemo->Lines->Add(Format("MidWare TAppServer version %d.%2.2d" ,
                    ARRAYOFCONST((ApServerVersion / 100, ApServerVersion % 100))));
    DisplayMemo->Lines->Add(Format("MidWare TRequestBroker version %d.%2.2d" ,
                    ARRAYOFCONST((RBrokerVersion / 100, RBrokerVersion % 100))));
    DisplayMemo->Lines->Add(Format("MidWare TServerObject version %d.%2.2d" ,
                    ARRAYOFCONST((ServerObjectVersion / 100, ServerObjectVersion % 100))));
    DisplayMemo->Lines->Add(Format("MidWare TMWBuffer version %d.%2.2d" ,
                    ARRAYOFCONST((MWBufferVersion / 100, MWBufferVersion % 100))));
    DisplayMemo->Lines->Add(Format("ICS TWSocket version %d.%2.2d" ,
                    ARRAYOFCONST((WSocketVersion / 100, WSocketVersion % 100))));
    Data = WinsockInfo();
    DisplayMemo->Lines->Add("Windows TCP/IP (Winsock) version " +
                          IntToStr(LOBYTE(Data.wVersion)) + "." +
                          IntToStr(HIBYTE(Data.wVersion)));
    DisplayMemo->Lines->Add(StrPas(Data.szDescription));
    DisplayMemo->Lines->Add(StrPas(Data.szSystemStatus));

    // Of the TTable and initialize UserData
    FUserData->CliQuery  = Query1;
    Query1->DatabaseName = LowerCase(ExtractFilePath(Application->ExeName));

    FUserData->CliTable  = Table1;
    Table1->DatabaseName = LowerCase(ExtractFilePath(Application->ExeName));
    Table1->TableName    = "clients.dbf";
    DisplayMemo->Lines->Add("Opening " + Table1->DatabaseName + Table1->TableName);
    try {
        Table1->Open();
    }
    catch (const Exception& E) {
            DisplayMemo->Lines->Add(E.Message);
    }

    // Start the application server component
    AppServer1->Port = FPort;
    AppServer1->Start();
    DisplayMemo->Lines->Add("Server ready.");
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::AppServer1ClientConnected(TObject *Sender,
      TClientWSocket *CliWSocket)
{
    ClientCountLabel->Caption = IntToStr(AppServer1->ClientCount);
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::AppServer1ClientClosed(TObject *Sender,
      TClientWSocket *CliWSocket)
{
    ClientCountLabel->Caption = IntToStr(AppServer1->ClientCount - 1);
}
//---------------------------------------------------------------------------
// This event handler is called when the AppServer component has some info
// to display-> This info can comes from one of the server components also->
void __fastcall TServerForm::AppServer1Display(TObject *Sender,
      AnsiString Msg)
{
    DisplayMemo->Lines->Add(Msg);
}
//---------------------------------------------------------------------------
// This event handler is called by the AppServer component when a client
// request has been received-> We just display it for this demo, but it is
// not a good idea for performance reasons->
void __fastcall TServerForm::AppServer1ClientCommand(TObject *Sender,
      TClientWSocket *CliWSocket, PChar CmdBuf, int CmdLen)
{
    ClientCountLabel->Caption = IntToStr(AppServer1->ClientCount - 1);
}
//---------------------------------------------------------------------------
// This event handler is called when the object request broker has just
// instanciated a server object to execute a user request->
void __fastcall TServerForm::RequestBroker1ObjCreate(TObject *Sender,
      TServerObject *ServerObject)
{
    ObjectCountLabel->Caption = IntToStr(RequestBroker1->ObjectCount);
}
//---------------------------------------------------------------------------
// This event handler is called just before the object request broker
// destroy a server object after having executed a user request->
void __fastcall TServerForm::RequestBroker1ObjDestroy(TObject *Sender,
      TServerObject *ServerObject)
{
    ObjectCountLabel->Caption = IntToStr(RequestBroker1->ObjectCount - 1);
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::ClearButtonClick(TObject *Sender)
{
    DisplayMemo->Clear();
}
//---------------------------------------------------------------------------
// This function is called back by the request broker for each function code
// he knows about when we ask to enumerate functions->
bool __fastcall TServerForm::EnumServerFunctions(
    TObject *Sender, AnsiString FunctionCode)
{
    DisplayMemo->Lines->Add(FunctionCode);
    return(TRUE);   // Continue to enumerate
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::FunctionsButtonClick(TObject *Sender)
{
    RequestBroker1->EnumServerFunctions(EnumServerFunctions);
}
//---------------------------------------------------------------------------
// The TestButton just shows how to use various TRequestBuffer methods
void __fastcall TServerForm::TestButtonClick(TObject *Sender)
{
    if (FRequestBuffer)
        delete FRequestBuffer;
    FRequestBuffer = new TMWBuffer(this);
    FRequestBuffer->DataBufferSize = 200;
    FRequestBuffer->Rewrite();
    FRequestBuffer->WriteFields(TRUE,  ARRAYOFCONST(("abc", "123")));  // New record 
    FRequestBuffer->WriteFields(TRUE,  ARRAYOFCONST(("delphi")));      // New record
    FRequestBuffer->WriteFields(FALSE, ARRAYOFCONST(("is the best"))); // Append

    FRequestBuffer->First();
    DisplayMemo->Lines->Add(FRequestBuffer->RecordToString());
    FRequestBuffer->Next();
    DisplayMemo->Lines->Add(FRequestBuffer->RecordToString());

    FRequestBuffer->First();
    DisplayMemo->Lines->Add(FRequestBuffer->Fields[0]);
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::AppServer1ClientTimeout(TObject *Sender,
      TClientWSocket *CliWSocket, bool &CanClose)
{
    DisplayMemo->Lines->Add(CliWSocket->PeerAddr +
                            " client timed out, disconnecting");
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::AppServer1BeforeSendReply(TObject *Sender,
      TClientWSocket *CliWSocket)
{
    char *Dst;
    int  DstLen;
    int  Key;

    // Did we received an encrypted request ?
    if (CliWSocket->UserData == 0)
        return; // No, nothing to do here !

    Key = '0';
    // Encrypt will allocate new memory for encrypted data which takes a
    // little bit more space than original data.
    // Memory will be freed in the OnAfterSendReply event handler.
    Encrypt(CliWSocket->ReplyHeader, CliWSocket->ReplyHeaderLen,
            &Dst, &DstLen, Key, 2);
    CliWSocket->ReplyHeader    = Dst;
    CliWSocket->ReplyHeaderLen = DstLen;
    Dst[0] = 3; // This will let the client know we use encrypted data
    Dst[1] = (char)Key;
    Encrypt(CliWSocket->ReplyBody, CliWSocket->ReplyBodyLen,
            &Dst, &DstLen, Key, 0);
    CliWSocket->ReplyBody    = Dst;
    CliWSocket->ReplyBodyLen = DstLen;
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::AppServer1AfterSendReply(TObject *Sender,
      TClientWSocket *CliWSocket)
{
    // Did we received an encrypted request ?
    if (CliWSocket->UserData == 0)
        return; // No, nothing to do here !

    // Memory was allocated in the OnBeforeSendReply event handler. We have
    // to free it to avoid memory leaks.
    free(CliWSocket->ReplyHeader);
    free(CliWSocket->ReplyBody);
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::AppServer1BeforeProcessRequest(
      TObject *Sender, TClientWSocket *CliWSocket, PChar &CmdBuf,
      int &CmdLen)
{
    int Cnt;

    // Check if we have some encrypted data
    if ((CmdLen < 3) || (CmdBuf[0] != 3))
        CliWSocket->UserData = 0;
    else {
        // We've got encrypted data. Decrypt on same place.
        Decrypt(CmdBuf, CmdLen, CmdBuf, &Cnt);
        // Remember we received encrypted data.
        // Later we will then send encrypted reply.
        CliWSocket->UserData = 1;
    }
}
//---------------------------------------------------------------------------

