/*---------------------------------------------------------------------------

Author:       François PIETTE
Description:  Chat Client using MidWare. Works with ChatSrv.
Creation:     June 21, 1998 (from Delphi version created June 19, 1998)
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

How does it works ?
-------------------

ChatCli works with ChatSrv. Many ChatCli programs connect to one single ChatSrv
program which act as a central server. Each ChatCli log on ChatSrv, identifying
itself with a username (or nickname if you like most). ChatSrv maintain a list
of all connected ChatCli with their respective username and IP address. ChatSrv
serve as a dispatcher between all clients. Each message went by a client to
another client pass thru the server. In other words, a client send a message to
ChatSrv, telling him that the mesage is for some other client. ChatSrv will then
find the destination client and forward the message to him.

Each ChatCli program is also a small server because each ChatCli has to receive
messages sent by the others. If ChatCli was not a server, then he would poll the
main server to know if some message is arrived for him. Being also a server,
chatCli simply stand there waiting for ChatSrv to connect to send any message
from other clients.

Updates:
Aug 16, 1999 V1.01 Adapted for BCB4

---------------------------------------------------------------------------*/
#include <vcl.h>
#include <vcl\inifiles.hpp>
#pragma hdrstop

#include "ChatCli1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ApsCli"
#pragma link "ApServer"
#pragma link "RBroker"
#pragma link "RFormat"
#pragma resource "*.dfm"
#define SectionWindow   "WindowNewDoc"
#define KeyTop          "Top"
#define KeyLeft         "Left"
#define KeyWidth        "Width"
#define KeyHeight       "Height"
#define SectionData     "Data"
#define KeyFrom         "From"
#define KeyTo           "To"
#define KeyServer       "Server"
TChatClientForm *ChatClientForm;
//---------------------------------------------------------------------------
__fastcall TChatClientForm::TChatClientForm(TComponent* Owner)
    : TForm(Owner)
{
    // Compute the INI filename based on the exe filename
    FIniFileName = LowerCase(ExtractFileName(Application->ExeName));
    FIniFileName = FIniFileName.SubString(1, FIniFileName.Length() - 3) + "ini";
    RequestBroker->IniFileName = FIniFileName;
}
//---------------------------------------------------------------------------
void __fastcall TChatClientForm::FormCreate(TObject *Sender)
{
    DisplayMemo->Clear();
    MsgMemo->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TChatClientForm::FormDestroy(TObject *Sender)
{
    if (FUserData) {
        delete FUserData;
        FUserData = NULL;
        RequestBroker->UserData = 0;
    }
}
//---------------------------------------------------------------------------
void __fastcall TChatClientForm::FormShow(TObject *Sender)
{
    TIniFile   *IniFile;
    AnsiString Me;

    if (!FInitialized) {
        FInitialized = TRUE;

        IniFile         = new TIniFile(FIniFileName);
        // Restore window position and size from previous run
        Top             = IniFile->ReadInteger(SectionWindow, KeyTop,
                                               (Screen->Height - Height) / 2);
        Left            = IniFile->ReadInteger(SectionWindow, KeyLeft,
                                               (Screen->Width - Width) / 2);
        Width           = IniFile->ReadInteger(SectionWindow, KeyWidth,  Width);
        Height          = IniFile->ReadInteger(SectionWindow, KeyHeight, Height);

        // Restore other parameters
        Me = LocalHostName();
        if (Me.Pos("->") > 0)
            Me = Me.SubString(1, Me.Pos("->") - 1);
        FromEdit->Text   = IniFile->ReadString(SectionData, KeyFrom,   Me);
//    	FromEdit->Text=IntToStr((DWORD)Application->Handle);
        ToEdit->Text     = IniFile->ReadString(SectionData, KeyTo,     "");
        ServerEdit->Text = IniFile->ReadString(SectionData, KeyServer, "localhost");
        delete IniFile;

        // Start the server. The server is used to receive messages sent by
        // other users thru the central server
        try {
            StartServer();
        }
        catch (Exception& E) {
            // Something failed during server startup. We cannot run
            // the application. Display a message and terminate.
            Application->ShowException(&E);
            Application->Terminate();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TChatClientForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    TIniFile *IniFile;

    IniFile = new TIniFile(FIniFileName);
    // Save window position and size
    IniFile->WriteInteger(SectionWindow, KeyTop,       Top);
    IniFile->WriteInteger(SectionWindow, KeyLeft,      Left);
    IniFile->WriteInteger(SectionWindow, KeyWidth,     Width);
    IniFile->WriteInteger(SectionWindow, KeyHeight,    Height);
    // Save other parameters
    IniFile->WriteString(SectionData,    KeyServer,    ServerEdit->Text);
    IniFile->WriteString(SectionData,    KeyFrom,      FromEdit->Text);
    IniFile->WriteString(SectionData,    KeyTo,        ToEdit->Text);
    delete IniFile;
}
//---------------------------------------------------------------------------
void __fastcall TChatClientForm::ConnectBitBtnClick(TObject *Sender)
{
    ServerEdit->SelectAll();
    FromEdit->SelectAll();
    ActiveControl = MsgMemo;
    // If we are already connected, then the connect button is disconnect
    if (AppSrvClient->Connected)
        AppSrvClient->Close();
    else
        DoConnect();
}
//---------------------------------------------------------------------------
// Connecting to the server is a little bit more than just conection setup.
// We need to send the LOGON request with our name and the port we use for
// our server part to receive the messages from other users.
void __fastcall TChatClientForm::DoConnect(void)
{
    DWORD TimeOut;

    // Send the LOGON request with our name and server port
    AppSrvClient->FunctionCode = "LOGON";
    AppSrvClient->Server       = ServerEdit->Text;
    AppSrvClient->Request->Rewrite();
    AppSrvClient->Request->WriteFields(TRUE,
        ARRAYOFCONST((FromEdit->Text, FPort)));
    AppSrvClient->OnRequestDone = LogonRequestDone;
    AppSrvClient->Send();

    // TAppSrvClient->Send is an asynchrounous function. It means that we get
    // control back immediately while the request execute in the background.
    // We need to wait until the request is done or some timeout elapsed.
    TimeOut = GetTickCount() + 60000;
    while ((TimeOut > GetTickCount()) &&
           (AppSrvClient->State != cstReady)) {
        Application->ProcessMessages();
        Sleep(0);
    }

    // Checked if we are received the answer of if we timed out
    // If we received the answer, we when thru the LogonRequestDone event
    // handler and checked the answer.
    if (AppSrvClient->State != cstReady)
        AppSrvClient->Close();
}
//---------------------------------------------------------------------------
// This event handler is triggered when we received the answer for the LOGON
// request. The answer may be negative because we requested a name already
// used by another user.
void __fastcall TChatClientForm::LogonRequestDone(
    TObject *Sender,
    int     Error)
{
    // Restore the event handler to the default event handler
    AppSrvClient->OnRequestDone = AppSrvClientRequestDone;

    // Check if any error where detected, such as server not responding
    if (Error) {
        Display("LOCAL> Logon failed, error #" + IntToStr(Error));
        AppSrvClient->Close();
        return;
    }

    // Check the answer sent back by the server. The status is '200' if ok
    // Any other value is an error, the result set contains the errror msg
    if (AppSrvClient->AnswerStatus != "200") {
        Display("SERVER> " + AppSrvClient->Answer->Fields[0]);
        AppSrvClient->Close();
        return;
    }
}
//---------------------------------------------------------------------------
// This event handler is called when a message we sent is processed by the
// chat server.
void __fastcall TChatClientForm::MessageToRequestDone(
    TObject *Sender,
    int     Error)
{
    // Restore the event handler to the default event handler
    AppSrvClient->OnRequestDone = AppSrvClientRequestDone;

    // Check if any error where detected, such as server not responding
    if (Error) {
        Display("LOCAL> MessageTo failed, error #" + IntToStr(Error));
        AppSrvClient->Close();
        return;
    }

    // Check the answer sent back by the server. The status is '200' if ok
    // Any other value is an error, the result set contains the errror msg
    if (AppSrvClient->AnswerStatus != "200") {
        Display("SERVER> " + AppSrvClient->Answer->Fields[0]);
        return;
    }
}
//---------------------------------------------------------------------------
// This is the default event handler for request done. We should never go
// here unless some programming or timing error occurs.
void __fastcall TChatClientForm::AppSrvClientRequestDone(
    TObject *Sender,
    int     Error)
{
    if (Error)
        Display("Request " + AppSrvClient->FunctionCode +
                " error #" + IntToStr(Error));
    else
        Display("Request " + AppSrvClient->FunctionCode + " done.");
}
//---------------------------------------------------------------------------
void __fastcall TChatClientForm::Display(AnsiString Msg)
{
    // We should check memo overflow !
    DisplayMemo->Lines->Add(Msg);
}
//---------------------------------------------------------------------------
void __fastcall TChatClientForm::AppServerDisplay(
    TObject    *Sender,
    AnsiString Msg)
{
    Display(Msg);
}
//---------------------------------------------------------------------------
void __fastcall TChatClientForm::SendBitBtnClick(TObject *Sender)
{
    TMemoryStream *Data;
    int           I;

    // Return focus to the message memo
    ActiveControl = MsgMemo;

    // Send only if memo is not empty
    if (MsgMemo->Lines->Count <= 0) {
        MessageBeep(MB_OK);
        return;
    }

    // First we need to be connected to the server
    if (!AppSrvClient->Connected) {
        DoConnect();
        if (!AppSrvClient->Connected)
            return;
    }

    // Display the message locally
    for (I = 0; I < MsgMemo->Lines->Count; I++)
        Display(FromEdit->Text + "> " + MsgMemo->Lines->Strings[I]);

    // Send the message to the remote
    Data = new TMemoryStream;
    try {
        MsgMemo->Lines->SaveToStream(Data);
        Data->Seek(0, 0);
        ToEdit->SelectAll();
        FromEdit->SelectAll();
        ActiveControl = MsgMemo;
        AppSrvClient->FunctionCode = "MESSAGETO";
        AppSrvClient->Server       = ServerEdit->Text;
        AppSrvClient->Request->Rewrite();
        AppSrvClient->Request->WriteFields(TRUE,
            ARRAYOFCONST((ToEdit->Text, FromEdit->Text)));
        AppSrvClient->Request->AppendStreamField(Data, mwString);
        AppSrvClient->OnRequestDone = MessageToRequestDone;
        AppSrvClient->Send();
        MsgMemo->Clear();
    }
    __finally {
        delete Data;
    }
}
//---------------------------------------------------------------------------
// This event handler is triggered when the connection is established with
// the chat server. This result from the LOGON request in our case.
void __fastcall TChatClientForm::AppSrvClientSessionConnected(
      TObject *Sender, WORD Error)
{
    if (Error == 0) {
        Display("You are connected to the chat server.");
        ConnectBitBtn->Caption = "&Disconnect";
    }
    else {
        Display("Connection with the chat server failed, error #" +
                IntToStr(Error));
        ConnectBitBtn->Caption = "&Connect";
    }
}
//---------------------------------------------------------------------------
// This event handler is called when the session with the chat server is
// closed either because we closed it, or the server closed it.
void __fastcall TChatClientForm::AppSrvClientSessionClosed(
    TObject *Sender,
    WORD    Error)
{
    Display("You have been disconnected from the chat server.");
    ConnectBitBtn->Caption = "&Connect";
}
//---------------------------------------------------------------------------
// This procedure will start our server part. The chat client must have a
// server part because he needs to receive messages from the others. If we
// don't setup a server, we should poll the chat server to know if we
// received any message. This is not possible with many user ! Using our own
// server in the chat client, we can receive messages from the others
// without doing anything special.
// The problem here is that we wants to be able to run several instances of
// chat client on the same computer. Each instance will have his own server
// Therefore we cannot use a fixed port for the server. We will try ports
// in sequence until we find some unused one.
void __fastcall TChatClientForm::StartServer(void)
{
    bool Ok;
    int  Cnt;

    FPort = 2122;           // We will start scanning port with this value
    Cnt   = 0;              // We will count to be sure to not loop forever
    Ok    = FALSE;
    // We will loop until we are successful or get any error other than
    // "address already in use". We also stop after 100 ports.
    while (!Ok) {
        try {
            Cnt++;
            AppServer->Port = IntToStr(FPort);
            AppServer->Start();
            Ok = TRUE;
        }
        catch (const Exception& E) {
            if (Cnt > 100)
                throw Exception("Can't start server: " + E.Message);
            if (WSAGetLastError() != WSAEADDRINUSE)
                throw E;
            FPort++;
        }
    }

    // Initialize RequestBroker object 
    RequestBroker->IniFileName = FIniFileName;
    RequestBroker->AddServerObject(__classid(TServerObjectMESSAGETO));

    // Create the user data and pass it to the RequestBroker
    FUserData               = new TUserData;
    FUserData->OnDisplay    = AppServerDisplay;
    RequestBroker->UserData = (long)FUserData;
}
//---------------------------------------------------------------------------
void __fastcall TUserData::TriggerDisplay(AnsiString Msg)
{
    if (FOnDisplay)
        FOnDisplay(this, Msg);
}
//---------------------------------------------------------------------------
// This is a TServerObject for our server part. It is intened to receive a
// single message from another user and to display it.
void __fastcall TServerObjectMESSAGETO::Execute(void)
{
    TUserData     *UData;
    AnsiString    FromName;
    AnsiString    ToName;
    TMemoryStream *Data;
    TMWFieldType  FldType;
    TStringList   *DataBuffer;
    int           I;

    try {
        // First field is the destination user name, it should be our name
        ToName     = FRequestBuffer->Fields[0];
        // The second field is the sender username
        FromName   = FRequestBuffer->Fields[1];

        // The third field is the message body as a blob. The blob was made
        // by write a TStrings into a TSream and sending the TSream as a
        // single blob field. We reverse this process here. We will create
        // a TStrings (TStringList) and a TStream (TMemoryStream), fill the
        // stream with the blob field and fill the TStrings with the stream
        // We use try/finally and try/except to be sure to free the object
        // in the case something goes wrong to avoid memory leaks.
        DataBuffer = new TStringList;
        try {
            Data = new TMemoryStream;
            try {
                FRequestBuffer->GetStreamField(2, Data, FldType);
                Data->Seek(0,0);
                DataBuffer->LoadFromStream(Data);
            }
            __finally {
                delete Data;
            }

            // Call the display procedure in UserData for each line
            UData = (TUserData *)FUserData;
            for (I = 0; I < DataBuffer->Count; I++)
                UData->TriggerDisplay(FromName + "> " + DataBuffer->Strings[I]);

            // Send an ok response to the sender
            FResponseBuffer->WriteFields(TRUE, ARRAYOFCONST(("Ok")));
            FResultStatus = 200;
        }
        __finally {
            delete DataBuffer;
        }
    }
    catch (const Exception& E) {
        FResponseBuffer->WriteFields(TRUE, ARRAYOFCONST((E.Message)));
        FResultStatus = 401;
    }
    Finish();
}
//---------------------------------------------------------------------------

