/*---------------------------------------------------------------------------

Author:       François PIETTE
Description:  Simple Chat Server using MidWare. Works with ChatCli.
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

ChatSrv support a special username: 'SERVER'. It takes all messages sent to
this user for himself, executing special requests such as 'WHOAMI' and 'WHO'
and replies to the requesting user.

Updates:
Aug 16, 1999  V1.01 Adapted for BCB4

---------------------------------------------------------------------------*/
#include <vcl.h>
#include <vcl\inifiles.hpp>
#pragma hdrstop

#include "ChatSrv1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ApServer"
#pragma link "RBroker"
#pragma resource "*.dfm"
#define MainTitle      "MidWare Chat Server - http://www.rtfm.be/fpiette"
#define SectionData    "Data"
#define KeyPort        "Port"
#define SectionWindow  "Window"
#define KeyTop         "Top"
#define KeyLeft        "Left"
#define KeyWidth       "Width"
#define KeyHeight      "Height"
TChatSrvForm *ChatSrvForm;
//---------------------------------------------------------------------------
__fastcall TChatSrvForm::TChatSrvForm(TComponent* Owner)
    : TForm(Owner)
{
    // Build Ini file name
    FIniFileName = LowerCase(ExtractFileName(Application->ExeName));
    FIniFileName = FIniFileName.SubString(1, FIniFileName.Length() - 3) + "ini";
}
//---------------------------------------------------------------------------
void __fastcall TChatSrvForm::FormCreate(TObject *Sender)
{
    // Initialize RequestBroker object
    RequestBroker1->IniFileName = FIniFileName;
    RequestBroker1->AddServerObject(__classid(TServerObjectMESSAGETO));
    RequestBroker1->AddServerObject(__classid(TServerObjectLOGON));

    // It's a good place to initialize TRequestBroker->UserData with for example
    // a pointer to a dynamically allocated record or to an object.
    // UserData is passed to ServerObjects instanciated by the broker. Using
    // it, they can gain access to some global data or procedure, such as data
    // base session.

    // In this sample we use a TUserData object
    FUserData = new TUserData;
    FUserData->OnDisplay = AppServer1Display;
    RequestBroker1->UserData = (long)FUserData;

    // Initialize user interface
    ObjectCountLabel->Caption = "0";
    ClientCountLabel->Caption = "0";
    DisplayMemo->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TChatSrvForm::FormDestroy(TObject *Sender)
{
    if (FUserData) {
        delete FUserData;
        FUserData = NULL;
    }
}
//---------------------------------------------------------------------------
void __fastcall TChatSrvForm::FormShow(TObject *Sender)
{
    TIniFile *IniFile;

    if (!FInitialized) {
        FInitialized        = TRUE;
        Caption             = "Starting "  MainTitle;

        IniFile = new TIniFile(FIniFileName);
        Top     = IniFile->ReadInteger(SectionWindow, KeyTop,
                                       (Screen->Height - Height) / 2);
        Left    = IniFile->ReadInteger(SectionWindow, KeyLeft,
                                       (Screen->Width - Width) / 2);
        Width   = IniFile->ReadInteger(SectionWindow, KeyWidth,  Width);
        Height  = IniFile->ReadInteger(SectionWindow, KeyHeight, Height);
        FPort   = IniFile->ReadString(SectionData,    KeyPort,   "2121");
        delete IniFile;

        // We use a custom message to initialize things once the form
        // is visible
        PostMessage(Handle, WM_APPSTARTUP, 0, 0);
    }
}
//---------------------------------------------------------------------------
void __fastcall TChatSrvForm::FormClose(TObject *Sender, TCloseAction &Action)
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
void __fastcall TChatSrvForm::DisconnectAllButtonClick(TObject *Sender)
{
    AppServer1->DisconnectAll();
    ClientCountLabel->Caption = IntToStr(AppServer1->ClientCount);
}
//---------------------------------------------------------------------------
// This message handler is triggered by the FormShow event. We comes here
// only when the form is visible on screen.
void __fastcall TChatSrvForm::WMAppStartup(TMessage &Msg)
{
    HWND PrvWnd;

    // Prevent the server from running twice
    PrvWnd = FindWindow(String(ClassName()).c_str(), MainTitle);
    if (PrvWnd != 0) {
        Close();
        return;
    }
    Caption = MainTitle;
    Update();             // It's nice to have the form completely displayed

    // Start the application server component
    AppServer1->Port = FPort;
    AppServer1->Start();
}
//---------------------------------------------------------------------------
// A new client has connected, update our user interface
void __fastcall TChatSrvForm::AppServer1ClientConnected(TObject *Sender,
      TClientWSocket *CliWSocket)
{
    ClientCountLabel->Caption = IntToStr(AppServer1->ClientCount);
}
//---------------------------------------------------------------------------
// A client has disconnected, update our user interface
void __fastcall TChatSrvForm::AppServer1ClientClosed(TObject *Sender,
      TClientWSocket *CliWSocket)
{
    FUserData->RemoveClient(CliWSocket);
    ClientCountLabel->Caption = IntToStr(AppServer1->ClientCount - 1);
}
//---------------------------------------------------------------------------
// This event handler is called when the AppServer component has some info
// to display. This info can comes from one of the server components also.
void __fastcall TChatSrvForm::AppServer1Display(TObject *Sender, AnsiString Msg)
{
    DisplayMemo->Lines->Add(Msg);
}
//---------------------------------------------------------------------------
// This event handler is called by the AppServer component when a client
// request has been received. We just display it for this demo, but it is
// not a good idea for performance reasons
void __fastcall TChatSrvForm::AppServer1ClientCommand(TObject *Sender,
      TClientWSocket *CliWSocket, PChar CmdBuf, int CmdLen)
{
    DisplayMemo->Lines->Add(CmdBuf);
}
//---------------------------------------------------------------------------
// This event handler is called when the object request broker has just
// instanciated a server object to execute a user request->
void __fastcall TChatSrvForm::RequestBroker1ObjCreate(TObject *Sender,
      TServerObject *ServerObject)
{
    ObjectCountLabel->Caption = IntToStr(RequestBroker1->ObjectCount);
}
//---------------------------------------------------------------------------
// This event handler is called just before the object request broker
// destroy a server object after having executed a user request->
void __fastcall TChatSrvForm::RequestBroker1ObjDestroy(TObject *Sender,
      TServerObject *ServerObject)
{
    ObjectCountLabel->Caption = IntToStr(RequestBroker1->ObjectCount - 1);
}
//---------------------------------------------------------------------------
void __fastcall TChatSrvForm::ClearButtonClick(TObject *Sender)
{
    DisplayMemo->Clear();
}
//---------------------------------------------------------------------------
// This function is called back by the request broker for each function code
// he knows about when we ask to enumerate functions->
bool __fastcall TChatSrvForm::EnumServerFunctions(
    TObject *Sender, AnsiString FunctionCode)
{
    DisplayMemo->Lines->Add(FunctionCode);
    return(TRUE);   // Continue to enumerate
}
//---------------------------------------------------------------------------
void __fastcall TChatSrvForm::FunctionsButtonClick(TObject *Sender)
{
    RequestBroker1->EnumServerFunctions(EnumServerFunctions);
}
//---------------------------------------------------------------------------
void __fastcall TChatSrvForm::ListClientsButtonClick(TObject *Sender)
{
    int UserID;

    if (FUserData->UserList->Count <= 0) {
        AppServer1Display(this, "No connected client");
        return;
    }

    for (UserID = 0; UserID < FUserData->UserList->Count; UserID++) {
        AppServer1Display(this,
                          "Name="  + FUserData->GetName(UserID) +
                          " IP="   + FUserData->GetIP(UserID) +
                          " Port=" + FUserData->GetPort(UserID));
    }
}
//---------------------------------------------------------------------------
__fastcall TUserData::TUserData(void)
{
    UserList = new TList;
}
//---------------------------------------------------------------------------
__fastcall TUserData::~TUserData(void)
{
   if (UserList) {
       delete UserList;
       UserList = NULL;
   }
}
//---------------------------------------------------------------------------
void __fastcall TUserData::TriggerDisplay(AnsiString Msg)
{
    if (FOnDisplay)
        FOnDisplay(this, Msg);
}
//---------------------------------------------------------------------------
// Find a user into the user list, using the username as a key
// Returns a user ID which is simply the index into UserList
int __fastcall TUserData::FindUser(AnsiString UserName)
{
    int        I;
    PChatUser  User;
    AnsiString Name;

    Name = Trim(UpperCase(UserName));
    for (I = 0; I < UserList->Count; I++) {
        User = (PChatUser)(UserList->Items[I]);
        if (User->Name == Name)
            return(I);
    }
    return(-1);
}
//---------------------------------------------------------------------------
// Find a client into the userlist, using the client object as a key
// Returns a user ID which is simply the index into UserList
int __fastcall TUserData::FindClient(TClientWSocket* Client)
{
    int I;

    for (I = 0; I < UserList->Count; I++) {
        if (Client == ((PChatUser)(UserList->Items[I]))->Client)
            return(I);
    }
    return(-1);
}
//---------------------------------------------------------------------------
// Remove a client from the user list
void __fastcall TUserData::RemoveClient(TClientWSocket* Client)
{
    PChatUser User;
    int       ID;

    ID = FindClient(Client);
    if (ID >= 0) {
        User = (PChatUser)(UserList->Items[ID]);
        TriggerDisplay("LOGOFF: " + User->Name + ", " +
                       User->IP + ", " +
                       IntToHex(Integer(Client), 8) + ", " +
                       User->Port);
        UserList->Delete(ID);
        delete User;
    }
}
//---------------------------------------------------------------------------
AnsiString __fastcall TUserData::GetName(int ID)
{
    return(((PChatUser)(UserList->Items[ID]))->Name);
}
//---------------------------------------------------------------------------
AnsiString __fastcall TUserData::GetIP(int ID)
{
    return(((PChatUser)(UserList->Items[ID]))->IP);
}
//---------------------------------------------------------------------------
AnsiString __fastcall TUserData::GetPort(int ID)
{
    return(((PChatUser)(UserList->Items[ID]))->Port);
}
//---------------------------------------------------------------------------
// The LogonUser procedure will add a new user to the list provided it is
// not already in the list.
void __fastcall TUserData::LogonUser(
    AnsiString     UserName,
    AnsiString     IPAddr,
    TClientWSocket *Client,
    AnsiString     ReplyPort)
{
    AnsiString ErrMsg;
    PChatUser  User;
    AnsiString Name;

    Name = Trim(UpperCase(UserName));
    TriggerDisplay("LOGON: " + UserName + ", " +
                   IPAddr + ", " +
                   IntToHex(Integer(Client), 8) + ", " +
                   ReplyPort);
    // We will check to see if username is at least 4 characters.
    // We don"t like meaningless names...
    if (Name.Length() < 4) {
        ErrMsg = "Username '" + UserName + "' must be at least 4 characters.";
        TriggerDisplay(ErrMsg);
        throw Exception(ErrMsg);
    }

    // Check for reserved user name
    if (Name == "SERVER") {
        ErrMsg = "Username '" + UserName + "' is reserved.";
        TriggerDisplay(ErrMsg);
        throw Exception(ErrMsg);
    }

    // Check if the username already exists in the list
    if (FindUser(Name) >= 0) {
        ErrMsg = "Username '" + UserName + "' already used.";
        TriggerDisplay(ErrMsg);
        throw Exception(ErrMsg);
    }

    // Create a new user data record and add it to the end of the list
    User = new TChatUser;
    User->Name   = Name;
    User->Client = Client;
    User->IP     = IPAddr;
    User->Port   = ReplyPort;
    UserList->Add(User);
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectLOGON::Execute(void)
{
    TUserData      *UData;
    AnsiString     UserName;
    AnsiString     ReplyPort;
    TClientWSocket *Client;
    AnsiString     IPAddr;

    UData     = (TUserData *)FUserData;
    UserName  = FRequestBuffer->Fields[0];
    ReplyPort = FRequestBuffer->Fields[1];
    IPAddr    = ((TClientWSocket *)(FORBDataPtr->Tag))->PeerAddr;
    Client    = (TClientWSocket *)(FORBDataPtr->Tag);
    try {
        UData->LogonUser(UserName, IPAddr, Client, ReplyPort);
        FResponseBuffer->WriteFields(TRUE, ARRAYOFCONST(("User logged")));
        FResultStatus = 200;
    }
    catch (const Exception& E) {
        FResponseBuffer->WriteFields(TRUE,
            ARRAYOFCONST(("Logon failed: " + E.Message)));
        FResultStatus = 401;
    }
    Finish();
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectMESSAGETO::ExecuteServiceMessages(
    int     UserID,
    TStream *Data)
{
    TUserData   *UData;
    AnsiString  Cmd;
    int         I;
    AnsiString  Buf;

    UData = (TUserData *)FUserData;
    Cmd.SetLength(Data->Size);
    Data->Read(Cmd.c_str(), Cmd.Length());
    Cmd = Trim(UpperCase(Cmd));

    // Truncate at the first line
    I = Cmd.Pos("\r");
    if (I > 0)
        Cmd.SetLength(I - 1);

    Data->Size = 0;             // Delete the actual content
    if (Cmd == "WHOAMI") {
        Buf = "Name=" + UData->GetName(UserID) + " IP=" + UData->GetIP(UserID);
        Data->Write(Buf.c_str(), Buf.Length());
    }
    else if (Cmd == "WHO") {
        for (I = 0; I < UData->UserList->Count; I++) {
            Buf = "Name=" + UData->GetName(I) +
                  " IP=" + UData->GetIP(I) + "\r\n";
            Data->Write(Buf.c_str(), Buf.Length());
        }
    }
    else {
        Buf = "Unknown request '" + Cmd + "'";
        Data->Write(Buf.c_str(), Buf.Length());
    }

    Data->Seek(0, 0);
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectMESSAGETO::Execute(void)
{
    TUserData     *UData;
    AnsiString    FromUser;
    AnsiString    ToUser;
    int           UserID;
    TAppSrvClient *AppSrvClient;
    TMemoryStream *Data;
    TMWFieldType  FldType;
    AnsiString    IPAddr;
    AnsiString    Port;

    UData    = (TUserData *)FUserData;
    ToUser   = UpperCase(Trim(FRequestBuffer->Fields[0]));
    FromUser = UpperCase(Trim(FRequestBuffer->Fields[1]));

    // Verify that the sending user has logged on, to avoid fake user
    UserID = UData->FindUser(FromUser);
    if (UserID < 0) {
        FResultStatus = 401;
        FResponseBuffer->WriteFields(TRUE, ARRAYOFCONST(("'" + FromUser +
                                           "' must first logon")));
        Finish();
        return;
    }

    // Verify that the sending user still has the same IP, to avoid fake user
    IPAddr = ((TClientWSocket *)(FORBDataPtr->Tag))->PeerAddr;
    if (IPAddr != UData->GetIP(UserID)) {
        FResultStatus = 401;
        FResponseBuffer->WriteFields(TRUE, ARRAYOFCONST(("'" + FromUser + "' has not " +
                                           "logged with this IP address")));
        Finish();
        return;
    }

    // Search for the destination user
    if (ToUser == "SERVER") {
        IPAddr   = UData->GetIP(UserID);
        Port     = UData->GetPort(UserID);
        FromUser = ToUser;
        UserID   = -2 - UserID;
    }
    else {
        UserID = UData->FindUser(ToUser);
        if (UserID < 0) {
            FResultStatus = 401;
            FResponseBuffer->WriteFields(TRUE, ARRAYOFCONST(("User '" + ToUser + "' not found")));
            Finish();
        }
        IPAddr = UData->GetIP(UserID);
        Port   = UData->GetPort(UserID);
    }

    // Now that everything is ok, we must forward the message from the sending
    // user to the destination user. We will use a dynamically created
    // TAppSrvClient to send the message in the background. Remember that each
    // client has a server part in his program.
    // We have to be very carefull here to avoid memory leaks. Each object
    // instanciation or memory allocation must be guraded by a try/finally or
    // try/except to be sure to delete the object and free memory in all cases
    // There are 3 object: a TMemoryStream, a TMWBuffer and a TAppSrvClient
    try {
        Data = new TMemoryStream;
        try {
            FRequestBuffer->GetStreamField(2, Data, FldType);
            Data->Seek(0, 0);

            // Check for service messages sent to the server
            if (UserID < -1)
                ExecuteServiceMessages(-2 - UserID, Data);

            AppSrvClient = new TAppSrvClient(NULL);
            try {
                AppSrvClient->Answer = new TMWBuffer(NULL);
                try {
                    AppSrvClient->FunctionCode = "MESSAGETO";
                    AppSrvClient->Server       = IPAddr;
                    AppSrvClient->Port         = Port;
                    AppSrvClient->Request->WriteFields(TRUE, ARRAYOFCONST((ToUser, FromUser)));
                    AppSrvClient->Request->AppendStreamField(Data, mwBlob);
                    AppSrvClient->OnRequestDone = SendMessageRequestDone;
                    AppSrvClient->Send();
                    // Sending will take place in the background. We must not
                    // destroy the object if send returns ok. The object will
                    // be destroyed later, when the request is done, in the
                    // SendMessageRequestDone event handler that will be
                    // called at that time.
                }
                catch (const Exception& E) {
                    // We got an exception during the request building or
                    // when we tried to send. We destroy the TMWBuffer  now
                    // and re-raise the exception. It will be catch by the
                    // outer try/except to send a negative answer to the
                    // originating client.
                    delete AppSrvClient->Answer;
                    throw E;
                }
            }
            catch (const Exception& E) {
                // We got an exception during the request building or
                // when we tried to send. We destroy the TAppSrvClient now
                // and re-raise the exception. It will be catch by the
                // outer try/except to send a negative answer to the
                // originating client.
                delete AppSrvClient;
                throw E;
            }
        }
        __finally {
            // We don"t need the TMemoryStream-> Destroy it now
            delete Data;
        }

        // We arrives here if we where successful in each step before. The
        // message will be sent in the background. Tell the client that it
        // is allright.
        FResultStatus = 200;
        FResponseBuffer->WriteFields(TRUE, ARRAYOFCONST(("Sending message")));
    }
    catch (const Exception& E) {
        // Something went wrong before. Use the exception message to built
        // the answer sent back to the originating client.
        FResultStatus = 401;
        FResponseBuffer->Rewrite();
        FResponseBuffer->WriteFields(TRUE,
                                     ARRAYOFCONST(("Error sending message " +
                                     E.Message)));
    }

    Finish();
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectMESSAGETO::SendMessageRequestDone(
    TObject *Sender, int Error)
{
    TAppSrvClient *AppSrvClient;

    AppSrvClient = (TAppSrvClient *)Sender;
    AppSrvClient->Close();
    delete AppSrvClient->Answer;
    delete AppSrvClient;
}
//---------------------------------------------------------------------------

