//---------------------------------------------------------------------------
#include <vcl.h>
#include <inifiles.hpp>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Main.h"
#include "nw_Messages.h"
#include "nw_Compression.h"
#include "DataModule.h"
#include "ProtectionLib.h"
#include "ML.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ApServer"
#pragma link "RBroker"
#pragma link "SingleInstance"
#pragma link "SingleInstance"
#pragma link "trayicon"
#pragma link "FormTranslation"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
#define SectionData    "Data"
#define KeyPort        "Port"
#define SectionWindow  "Window"
#define KeyTop         "Top"
#define KeyLeft        "Left"
#define KeyWidth       "Width"
#define KeyHeight      "Height"
//---------------------------------------------------------------------------
TFormMain *FormMain;
AnsiString      strIniFileName;
AnsiString      strPort;
//---------------------------------------------------------------------------
AnsiString Translate(AnsiString strBeforeTranslation)
{
    strBeforeTranslation = strBeforeTranslation.Trim();
    AnsiString strAfterTranslation="";
	ml_TranslateParagraph(strBeforeTranslation.LowerCase(),strAfterTranslation);
    return strAfterTranslation;
}
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
    : TForm(Owner)
{
	#ifdef _PROTECTED_
	pro_DebuggerCheck();
    pro_SoftIceCheck();
    pro_Check();
    pro_Scrambling();
    #endif

    #ifdef _DEMO_
    CheckExecutionCount();
    #endif
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::CreateParams(Controls::TCreateParams &Params)
{
	TCustomForm::CreateParams(Params);
	Params.Style |= WS_MINIMIZE;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::LoadSettings()
{
    TIniFile *IniFile;
    IniFile = new TIniFile(strIniFileName);
//    Top     = IniFile->ReadInteger(SectionWindow, KeyTop,
//    								(Screen->Height - Height) / 2);
//    Left    = IniFile->ReadInteger(SectionWindow, KeyLeft,
//    								(Screen->Width - Width) / 2);
//    Width   = IniFile->ReadInteger(SectionWindow, KeyWidth,  Width);
//    Height  = IniFile->ReadInteger(SectionWindow, KeyHeight, Height);
    strPort   = IniFile->ReadString(SectionData,    KeyPort,   "2121");
    delete IniFile;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SaveSettings()
{
    TIniFile *IniFile;
    IniFile = new TIniFile(strIniFileName);
//    IniFile->WriteInteger(SectionWindow, KeyTop,    Top);
//    IniFile->WriteInteger(SectionWindow, KeyLeft,   Left);
//    IniFile->WriteInteger(SectionWindow, KeyWidth,  Width);
//    IniFile->WriteInteger(SectionWindow, KeyHeight, Height);
    IniFile->WriteString(SectionData,    KeyPort,   strPort);
    delete IniFile;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
    strIniFileName = LowerCase(ChangeFileExt(Application->ExeName,".ini"));
//    Caption = c_strWWPTC+" - "+c_strNetWatcher+" <"+c_strServer+">";

    // Initialize RequestBroker object
    DM->RequestBroker1->IniFileName = strIniFileName;
    DM->RequestBroker1->AddServerObject(__classid(TServerObjectMESSAGETO));
    DM->RequestBroker1->AddServerObject(__classid(TServerObjectLOGON));

    // It's a good place to initialize TRequestBroker->UserData with for example
    // a pointer to a dynamically allocated record or to an object.
    // UserData is passed to ServerObjects instanciated by the broker. Using
    // it, they can gain access to some global data or procedure, such as data
    // base session.

    // In this sample we use a TUserData object
    FUserData = new TUserData;
	FUserData->OnDisplay = DM->AppServer1Display;
    DM->RequestBroker1->UserData = (long)FUserData;

    // Initialize user interface
    StatusBar->Panels->Items[0]->Text = c_strClients+FormatFloat(" 0",0);
    DisplayMemo->Clear();

    LoadSettings();

    // Start the application server component
    DM->AppServer1->Port = strPort;
    DM->AppServer1->Start();

	DM->ReBuildTreeViewGroups();
    TrayIcon->Minimize();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
	TrayIcon->Visible = false;

	SaveSettings();

    DM->AppServer1->Stop();
    DM->AppServer1->DisconnectAll();

    if(FUserData)
    {
    	delete FUserData;
        FUserData = NULL;
    }
}
//---------------------------------------------------------------------------
// A new client has connected, update our user interface
// A client has disconnected, update our user interface
void __fastcall TFormMain::UpdateConnectedClients()
{
    AnsiString 	ToUser;
    AnsiString 	Port;
    AnsiString 	IPAddr;
    int 		LanguageID;
    TMemoryStream *pStream=new TMemoryStream();
    pStream->Position=0;
	TreeViewGroups->SaveToStream(pStream);
    pStream->Position=0;

    for(int UserID=0;UserID<FUserData->UserList->Count;UserID++)
    {
	    ToUser   = FUserData->GetName(UserID);
	    Port     = FUserData->GetPort(UserID);
        IPAddr   = FUserData->GetIP(UserID);
//        LanguageID = FUserData->GetLanguageID(UserID);

    	TAppSrvClient *AppSrvClient;
        AppSrvClient = new TAppSrvClient(NULL);
        try
        {
            AppSrvClient->Answer = new TMWBuffer(NULL);
            try
            {
                AppSrvClient->FunctionCode = "MESSAGETO";
                AppSrvClient->Server       = IPAddr;
                AppSrvClient->Port         = Port;
                AppSrvClient->Request->WriteFields(TRUE, ARRAYOFCONST((ToUser, "SERVER", "CONNECTED_CLIENTS", "")));
                AppSrvClient->Request->AppendStreamField(pStream, mwBlob);
                AppSrvClient->OnRequestDone = SendMessageRequestDone;
                AppSrvClient->Send();
                // Sending will take place in the background. We must not
                // destroy the object if send returns ok. The object will
                // be destroyed later, when the request is done, in the
                // SendMessageRequestDone event handler that will be
                // called at that time.
            }
            catch (const Exception& E)
            {
                // We got an exception during the request building or
                // when we tried to send. We destroy the TMWBuffer  now
                // and re-raise the exception. It will be catch by the
                // outer try/except to send a negative answer to the
                // originating client.
                if(pStream)	delete pStream;
                pStream=NULL;
                delete AppSrvClient->Answer;
                throw E;
            }
        }
        catch (const Exception& E)
        {
            // We got an exception during the request building or
            // when we tried to send. We destroy the TAppSrvClient now
            // and re-raise the exception. It will be catch by the
            // outer try/except to send a negative answer to the
            // originating client.
            if(pStream)	delete pStream;
            pStream=NULL;
            delete AppSrvClient;
            throw E;
        }
    }
    if(pStream)	delete pStream;
    pStream=NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::UpdateSoundUsers()
{
    AnsiString 	ToUser;
    AnsiString 	Port;
    AnsiString 	IPAddr;
    int 		LanguageID;
    TMemoryStream *pStream=new TMemoryStream();
    pStream->Position=0;
	ListBoxSoundUsers->Items->SaveToStream(pStream);
    pStream->Position=0;

    for(int UserID=0;UserID<FUserData->UserList->Count;UserID++)
    {
	    ToUser   = FUserData->GetName(UserID);
	    Port     = FUserData->GetPort(UserID);
        IPAddr   = FUserData->GetIP(UserID);
//        LanguageID = FUserData->GetLanguageID(UserID);

    	TAppSrvClient *AppSrvClient;
        AppSrvClient = new TAppSrvClient(NULL);
        try
        {
            AppSrvClient->Answer = new TMWBuffer(NULL);
            try
            {
                AppSrvClient->FunctionCode = "MESSAGETO";
                AppSrvClient->Server       = IPAddr;
                AppSrvClient->Port         = Port;
                AppSrvClient->Request->WriteFields(TRUE, ARRAYOFCONST((ToUser, "SERVER", "SOUND_USERS", "")));
                AppSrvClient->Request->AppendStreamField(pStream, mwBlob);
                AppSrvClient->OnRequestDone = SendMessageRequestDone;
                AppSrvClient->Send();
                // Sending will take place in the background. We must not
                // destroy the object if send returns ok. The object will
                // be destroyed later, when the request is done, in the
                // SendMessageRequestDone event handler that will be
                // called at that time.
            }
            catch (const Exception& E)
            {
                // We got an exception during the request building or
                // when we tried to send. We destroy the TMWBuffer  now
                // and re-raise the exception. It will be catch by the
                // outer try/except to send a negative answer to the
                // originating client.
                if(pStream)	delete pStream;
                pStream=NULL;
                delete AppSrvClient->Answer;
                throw E;
            }
        }
        catch (const Exception& E)
        {
            // We got an exception during the request building or
            // when we tried to send. We destroy the TAppSrvClient now
            // and re-raise the exception. It will be catch by the
            // outer try/except to send a negative answer to the
            // originating client.
            if(pStream)	delete pStream;
            pStream=NULL;
            delete AppSrvClient;
            throw E;
        }
    }
    if(pStream)	delete pStream;
    pStream=NULL;
}
//---------------------------------------------------------------------------
// A client has disconnected, update our user interface
void __fastcall TFormMain::DisConnectUserFromTreeView(AnsiString strUserName)
{
	#ifdef _PROTECTED_
    pro_SoftIceCheck();
	pro_DebuggerCheck();
    pro_Scrambling();
    pro_Check();
    #endif

    #ifdef _DEMO_
    CheckExecutionCount();
    #endif

    AnsiString strComputerName=strUserName;
    DM->TableGroups->First();
    while(!DM->TableGroups->Eof)
    {
        if(DM->TableComputers->Locate("Computer_Name",strComputerName,TLocateOptions()<<loCaseInsensitive))
        {
        	DM->TableComputers->Edit();
            DM->TableComputers->FieldByName("Connected")->Value=false;
            DM->TableComputers->Post();
        }

     	DM->TableGroups->Next();
    }
    DM->ReBuildTreeViewGroups();

    int nIndex;
    nIndex = FormMain->ListBoxSoundUsers->Items->IndexOf(strUserName);
    if(nIndex >= 0)
    {
    	FormMain->ListBoxSoundUsers->Items->Delete(nIndex);
        FormMain->UpdateSoundUsers();
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SendMessageRequestDone(
    TObject *Sender, int Error)
{
    TAppSrvClient *AppSrvClient;

    AppSrvClient = (TAppSrvClient *)Sender;
    AppSrvClient->Close();
    delete AppSrvClient->Answer;
    delete AppSrvClient;
}
//---------------------------------------------------------------------------
// This event handler is called when the AppServer component has some info
// to display. This info can comes from one of the server components also.
// This event handler is called by the AppServer component when a client
// request has been received. We just display it for this demo, but it is
// not a good idea for performance reasons
// This event handler is called when the object request broker has just
// instanciated a server object to execute a user request->
// This event handler is called just before the object request broker
// destroy a server object after having executed a user request->
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
    for (I = 0; I < UserList->Count; I++)
    {
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

    for (I = 0; I < UserList->Count; I++)
    {
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
    if (ID >= 0)
    {
        User = (PChatUser)(UserList->Items[ID]);
//        TriggerDisplay(c_strLOGOFF+": " + User->Name + ", " +
//                       User->IP + ", " +
//                       IntToHex(Integer(Client), 8) + ", " +
//                       User->Port);
        TriggerDisplay(FormMessages->ValueListEditor->Values["c_strLOGOFF"]+": " + User->Name);
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
int __fastcall TUserData::GetLanguageID(int ID)
{
    return(((PChatUser)(UserList->Items[ID]))->LanguageID);
}
//---------------------------------------------------------------------------
// The LogonUser procedure will add a new user to the list provided it is
// not already in the list.
void __fastcall TUserData::LogonUser(
    AnsiString     UserName,
    AnsiString     IPAddr,
    int				LanguageID,
    TClientWSocket *Client,
    AnsiString     ReplyPort)
{
    AnsiString ErrMsg;
    PChatUser  User;
    AnsiString Name;

    Name = Trim(UpperCase(UserName));
//    TriggerDisplay(c_strLOGON+": " + UserName + ", " +
//                   IPAddr + ", " +
//                   IntToHex(Integer(Client), 8) + ", " +
//                   ReplyPort);
    TriggerDisplay(FormMessages->ValueListEditor->Values["c_strLOGON"]+": " + UserName);
    // We will check to see if username is at least 3 characters.
    // We don"t like meaningless names...
    if (Name.Length() < 3)
    {
        ErrMsg = FormMessages->ValueListEditor->Values["c_strUserName"]+" '" + UserName + "' "+FormMessages->ValueListEditor->Values["c_strAtLeast3Chars"]+".";
        TriggerDisplay(ErrMsg);
        throw Exception(ErrMsg);
    }

    // Check for reserved user name
    if (Name == "SERVER")
    {
        ErrMsg = FormMessages->ValueListEditor->Values["c_strUserName"]+" '" + UserName + "' "+FormMessages->ValueListEditor->Values["c_strReserved"]+".";
        TriggerDisplay(ErrMsg);
        throw Exception(ErrMsg);
    }

    // Check if the username already exists in the list
    if (FindUser(Name) >= 0)
    {
//        ErrMsg = FormMessages->ValueListEditor->Values["c_strUserName"]+" '" + UserName + "' "+FormMessages->ValueListEditor->Values["c_strAlreadyUsed"]+".";
//        TriggerDisplay(ErrMsg);
		ErrMsg = "UserExists";
        throw Exception(ErrMsg);
    }

    // Create a new user data record and add it to the end of the list
    User = new TChatUser;
    User->Name   = Name;
    User->Client = Client;
    User->IP     = IPAddr;
    User->Port   = ReplyPort;
    User->LanguageID = LanguageID;
    UserList->Add(User);

    FormMain->ConnectUserToTreeView(Name);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ConnectUserToTreeView(AnsiString strUserName)
{
	#ifdef _PROTECTED_
    pro_SoftIceCheck();
	pro_DebuggerCheck();
    pro_Scrambling();
    pro_Check();
    #endif

    #ifdef _DEMO_
    CheckExecutionCount();
    #endif

    AnsiString strComputerName=strUserName;
    bool bComputerFound=false;

    DM->TableGroups->First();
    while(!DM->TableGroups->Eof)
    {
        if(DM->TableComputers->Locate("Computer_Name",strComputerName,TLocateOptions()<<loCaseInsensitive))
        {
        	if(!DM->TableComputers->FieldByName("Connected")->Value)
            {
	        	DM->TableComputers->Edit();
	        	DM->TableComputers->FieldByName("Connected")->Value=true;
	            DM->TableComputers->Post();
     		}
            else
            {
            	MessageDlg(FormMessages->ValueListEditor->Values["c_strClientFound"],mtError,TMsgDlgButtons()<<mbOK,0);
//                SendCloseCommand(Socket);
            }
         	bComputerFound=true;
        }

     	DM->TableGroups->Next();
    }

    if(!bComputerFound)
    {
    	if(DM->TableGroups->Locate("Group_Name",c_strWithoutGroup,TLocateOptions()<<loCaseInsensitive))
        {
			DM->TableComputers->Append();
			DM->TableComputers->FieldByName("Computer_Name")->Value=strComputerName;
			DM->TableComputers->FieldByName("Connected")->Value=true;
            DM->TableComputers->Post();
        }
    }

    DM->ReBuildTreeViewGroups();
}
//---------------------------------------------------------------------------
void __fastcall TServerObjectLOGON::Execute(void)
{
    TUserData      *UData;
    AnsiString     UserName;
    AnsiString     ReplyPort;
    TClientWSocket *Client;
    AnsiString     IPAddr;
    int 			LanguageID;

    UData     = (TUserData *)FUserData;
    UserName  = FRequestBuffer->Fields[0];
    ReplyPort = FRequestBuffer->Fields[1];
    LanguageID = StrToInt(FRequestBuffer->Fields[2]);
    IPAddr    = ((TClientWSocket *)(FORBDataPtr->Tag))->PeerAddr;
    Client    = (TClientWSocket *)(FORBDataPtr->Tag);
    try
    {
        UData->LogonUser(UserName, IPAddr, LanguageID, Client, ReplyPort);
        FResponseBuffer->WriteFields(TRUE, ARRAYOFCONST((FormMessages->ValueListEditor->Values["c_strUserLoged"])));
        FResultStatus = 200;

	    FormMain->UpdateConnectedClients();
    }
    catch (const Exception& E)
    {
        FResponseBuffer->WriteFields(TRUE,
            ARRAYOFCONST((FormMessages->ValueListEditor->Values["c_strLogOnFailed"]+": " + E.Message)));
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
    if (Cmd == "WHOAMI")
    {
        Buf = FormMessages->ValueListEditor->Values["c_strName"]+"=" + UData->GetName(UserID) + " "+FormMessages->ValueListEditor->Values["c_strIPAddress"]+"=" + UData->GetIP(UserID);
        Data->Write(Buf.c_str(), Buf.Length());
    }
    else if (Cmd == "WHO")
    {
        for (I = 0; I < UData->UserList->Count; I++)
        {
            Buf = FormMessages->ValueListEditor->Values["c_strName"]+"=" + UData->GetName(I) +
                  " "+FormMessages->ValueListEditor->Values["c_strIPAddress"]+"=" + UData->GetIP(I) + "\r\n";
            Data->Write(Buf.c_str(), Buf.Length());
        }
    }
    else
    {
        Buf = FormMessages->ValueListEditor->Values["c_strInvalidCommand"]+" '" + Cmd + "'";
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
    int           FromUserID;
    int           ToUserID;
    TAppSrvClient *AppSrvClient;
    TMemoryStream *Data;
    TMWFieldType  FldType;
    AnsiString    IPAddr;
    AnsiString    Port;
    AnsiString strMessageType;
    AnsiString strMessageTitle;

    UData    = (TUserData *)FUserData;
    ToUser   = UpperCase(Trim(FRequestBuffer->Fields[0]));
    FromUser = UpperCase(Trim(FRequestBuffer->Fields[1]));
    strMessageType = UpperCase(Trim(FRequestBuffer->Fields[2]));
    strMessageTitle = UpperCase(Trim(FRequestBuffer->Fields[3]));

    // Verify that the sending user has logged on, to avoid fake user
    UserID = UData->FindUser(FromUser);
    if (UserID < 0)
    {
        FResultStatus = 401;
        FResponseBuffer->WriteFields(TRUE, ARRAYOFCONST(("'" + FromUser +
                                           "' "+FormMessages->ValueListEditor->Values["c_strMustFirstLogon"])));
        Finish();
        return;
    }

    // Verify that the sending user still has the same IP, to avoid fake user
    IPAddr = ((TClientWSocket *)(FORBDataPtr->Tag))->PeerAddr;
    if (IPAddr != UData->GetIP(UserID))
    {
        FResultStatus = 401;
        FResponseBuffer->WriteFields(TRUE, ARRAYOFCONST(("'" + FromUser + "' "+FormMessages->ValueListEditor->Values["c_strHasNotLoggedWithThisIPAddress"])));
        Finish();
        return;
    }

    // Search for the destination user
    if (ToUser == "SERVER")
    {
        if(SameText(strMessageType,"SOUND_COMMAND"))
        {
			if(SameText(strMessageTitle,"START"))
            {
				FormMain->ListBoxSoundUsers->Items->Add(FromUser);
                FormMain->UpdateSoundUsers();
            }
            else
			if(SameText(strMessageTitle,"STOP"))
            {
            	int nIndex;
				nIndex = FormMain->ListBoxSoundUsers->Items->IndexOf(FromUser);
                if(nIndex >= 0)
                {
					FormMain->ListBoxSoundUsers->Items->Delete(nIndex);
	                FormMain->UpdateSoundUsers();
                }
            }
            goto LEnd;
        }

        IPAddr   = UData->GetIP(UserID);
        Port     = UData->GetPort(UserID);
        FromUser = ToUser;
        UserID   = -2 - UserID;
    }
    else
    {
        UserID = UData->FindUser(ToUser);
        if (UserID < 0)
        {
            FResultStatus = 401;
            FResponseBuffer->WriteFields(TRUE, ARRAYOFCONST((FormMessages->ValueListEditor->Values["c_strUser"]+" '" + ToUser + "' "+FormMessages->ValueListEditor->Values["c_strNotFound"])));
            Finish();
        }
        IPAddr = UData->GetIP(UserID);
        Port   = UData->GetPort(UserID);
    }

    FromUserID = UData->FindUser(FromUser);
    ToUserID = UData->FindUser(ToUser);
    g_nSourceLanguage = UData->GetLanguageID(FromUserID);
    g_nDestLanguage = UData->GetLanguageID(ToUserID);

    // Now that everything is ok, we must forward the message from the sending
    // user to the destination user. We will use a dynamically created
    // TAppSrvClient to send the message in the background. Remember that each
    // client has a server part in his program.
    // We have to be very carefull here to avoid memory leaks. Each object
    // instanciation or memory allocation must be guraded by a try/finally or
    // try/except to be sure to delete the object and free memory in all cases
    // There are 3 object: a TMemoryStream, a TMWBuffer and a TAppSrvClient
    try
    {
        Data = new TMemoryStream;
        try
        {
            FRequestBuffer->GetStreamField(4, Data, FldType);
            Data->Seek(0, 0);

            // Check for service messages sent to the server
            if (UserID < -1)
                ExecuteServiceMessages(-2 - UserID, Data);

            AppSrvClient = new TAppSrvClient(NULL);
            try
            {
                AppSrvClient->Answer = new TMWBuffer(NULL);
                try
                {
                    AppSrvClient->FunctionCode = "MESSAGETO";
                    AppSrvClient->Server       = IPAddr;
                    AppSrvClient->Port         = Port;
                    AppSrvClient->Request->WriteFields(TRUE, ARRAYOFCONST((ToUser, FromUser, strMessageType, strMessageTitle)));

        			if(SameText(strMessageType,"TEXT") && SameText(strMessageTitle,"REQUEST"))
		            {
                     	TStringList *pList = new TStringList();
            			Data->Position = 0;
						pList->LoadFromStream(Data);

//                        pList->Text = UpperCase(pList->Text);
						pList->Text = Encrypt(Translate(Decrypt(pList->Text)));

                        Data->SetSize(0);
            			Data->Position = 0;
						pList->SaveToStream(Data);
            			Data->Position = 0;
                        if(pList)
                        {
                         	delete pList;
                            pList = NULL;
                        }
                    }

                    AppSrvClient->Request->AppendStreamField(Data, mwBlob);
                    AppSrvClient->OnRequestDone = SendMessageRequestDone;
                    AppSrvClient->Send();
                    // Sending will take place in the background. We must not
                    // destroy the object if send returns ok. The object will
                    // be destroyed later, when the request is done, in the
                    // SendMessageRequestDone event handler that will be
                    // called at that time.
                }
                catch (const Exception& E)
                {
                    // We got an exception during the request building or
                    // when we tried to send. We destroy the TMWBuffer  now
                    // and re-raise the exception. It will be catch by the
                    // outer try/except to send a negative answer to the
                    // originating client.
                    delete AppSrvClient->Answer;
                    throw E;
                }
            }
            catch (const Exception& E)
            {
                // We got an exception during the request building or
                // when we tried to send. We destroy the TAppSrvClient now
                // and re-raise the exception. It will be catch by the
                // outer try/except to send a negative answer to the
                // originating client.
                delete AppSrvClient;
                throw E;
            }
        }
        __finally
        {
            // We don"t need the TMemoryStream-> Destroy it now
            delete Data;
        }

        // We arrives here if we where successful in each step before. The
        // message will be sent in the background. Tell the client that it
        // is allright.
        FResultStatus = 200;
        FResponseBuffer->WriteFields(TRUE, ARRAYOFCONST((FormMessages->ValueListEditor->Values["c_strSendingMessage"])));
    }
    catch (const Exception& E)
    {
        // Something went wrong before. Use the exception message to built
        // the answer sent back to the originating client.
        FResultStatus = 401;
        FResponseBuffer->Rewrite();
        FResponseBuffer->WriteFields(TRUE,
                                     ARRAYOFCONST((FormMessages->ValueListEditor->Values["c_strErrorIn"]+" "+FormMessages->ValueListEditor->Values["c_strSendingMessage"]+" " +
                                     E.Message)));
    }
    LEnd:;
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

void __fastcall TFormMain::TreeViewGroupsGetSelectedIndex(TObject *Sender,
      TTreeNode *Node)
{
 	Node->SelectedIndex = Node->ImageIndex;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TreeViewGroupsMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
	TreeViewGroups->Selected=TreeViewGroups->GetNodeAt(X,Y);
    DM->AGroupsExecute(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::SingleAppInstance1SecondInstance(TObject *Sender,
      bool &ShutDown)
{
	MessageDlg("You can`t execute more than one instance of the server",mtError,TMsgDlgButtons()<<mbOK,0);
	ShutDown=true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caNone;
    TrayIcon->Minimize();
}
//---------------------------------------------------------------------------

