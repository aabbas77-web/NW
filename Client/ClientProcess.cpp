//---------------------------------------------------------------------------
#include <vcl.h>
#include <inifiles.hpp>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "ClientProcess.h"
#include "Main.h"
#include "DataModule.h"
#include "nw_Messages.h"
#include "Input.h"
#include "nw_Compression.h"
#include "TempExplorer.h"
#include "nw_CopyThread.h"
#include "FullScreen.h"
#include "Watch.h"
#include "nw_Messages.h"
#include "nw_Message.h"
#include "nw_SelectClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ApsCli"
#pragma link "ApServer"
#pragma link "RBroker"
#pragma link "RFormat"
#pragma link "FormTranslation"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
#define SectionWindow   "WindowNewDoc"
#define KeyTop          "Top"
#define KeyLeft         "Left"
#define KeyWidth        "Width"
#define KeyHeight       "Height"
#define SectionData     "Data"
#define KeyFrom         "From"
#define KeyServer       "Server"
//---------------------------------------------------------------------------
TDMClient *DMClient;
AnsiString strIniFileName;
int             nPort;
static nPrevWidth,nPrevHeight,nPrevColors;
//---------------------------------------------------------------------------
__fastcall TDMClient::TDMClient(TComponent* Owner)
	: TDataModule(Owner)
{
}
//---------------------------------------------------------------------------
AnsiString GetUserName(AnsiString strUserName)
{
	int nPos = UpperCase(strUserName).Pos('<');
    if(nPos > 0)
    {
    	strUserName.Delete(nPos,strUserName.Length());
    }
    return strUserName.Trim();
}
//---------------------------------------------------------------------------
void __fastcall Wait(HANDLE h)
{
	if (h==NULL || h==INVALID_HANDLE_VALUE) return;
  	// In this wait procedure, we set the cursor to the hourglass
  	// and disable the form. Then we repeat a loop:
  	//  1. wait for the next 50ms to see if the other application quits
  	//  2. process waiting messages (eg. to repaint the form)
  	//  3. continue until other application quits
  	// Then restore the form and cursor.
  	TCursor oldcursor=Screen->Cursor;
  	Screen->Cursor=crHourGlass;
  	bool done=false;
  	while (!done)
  	{
    	DWORD res=WaitForSingleObject(h,50);
    	if (res==WAIT_TIMEOUT) Application->ProcessMessages(); else done=true;
  	}
  	CloseHandle(h);
  	Screen->Cursor=oldcursor;
}
//---------------------------------------------------------------------------
HANDLE ExecuteProg(HWND hwnd,AnsiString strFileName,AnsiString strArgs,AnsiString strDir,int nShow)
{
  	SHELLEXECUTEINFO sei;
    ZeroMemory(&sei,sizeof(sei));
  	sei.cbSize=sizeof(sei);
  	sei.fMask=SEE_MASK_NOCLOSEPROCESS;
  	sei.hwnd=hwnd;
  	sei.lpVerb="open";
  	sei.lpFile=strFileName.c_str();
  	sei.lpParameters=strArgs.c_str();
  	sei.lpDirectory=strDir.c_str();
  	sei.nShow=nShow;
  	bool res=ShellExecuteEx(&sei);
  	HINSTANCE hInstApp=sei.hInstApp;
  	if ((int)hInstApp>32 && res) return sei.hProcess;
  	return NULL;
}
//---------------------------------------------------------------------------
bool gChangeResolution(UINT w, UINT h, UINT bitdepth)
{
	DEVMODE devMode;
	INT32   modeExist;
	INT32   modeSwitch;
	INT32   closeMode = 0;
	INT32   i;
	BYTE    buf[256];

	for (i=0; ;i++) {
		modeExist = EnumDisplaySettings(NULL, i, &devMode);

		/* Check if we ran out of modes */
		if (!modeExist) {
			//      ListDisplaySettings();
			/* Pony up an error message */
			//    sprintf(buf, "No matching mode to %ldx%ldx%ld-bit color available\n", w, h, bitdepth);
			//Log(LOG_BOOT, buf);
			break;
		}

		/* Check for a matching mode */
		if ( (devMode.dmBitsPerPel == bitdepth)
			&&(devMode.dmPelsWidth == w)
			&&(devMode.dmPelsHeight == h) )
		{
			//      sprintf(buf, "Trying %ldx%ldx%ld-bit color (%ld hertz)\n", devMode.dmPelsWidth, devMode.dmPelsHeight, devMode.dmBitsPerPel, devMode.dmDisplayFrequency);
			//      Log(LOG_BOOT, buf);
			modeSwitch = ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
			if (modeSwitch==DISP_CHANGE_SUCCESSFUL) return 0;
			//      Log(LOG_BOOT, "Nope, didnt work\n");
			if (!closeMode) closeMode = i;
		}
	}

	//Might be running in Windows95, let's try without the hertz change
	EnumDisplaySettings(NULL, closeMode, &devMode);
	devMode.dmBitsPerPel = bitdepth;
	devMode.dmPelsWidth  = w;
	devMode.dmPelsHeight = h;
	devMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	//  sprintf(buf, "Trying %ldx%ldx%ld-bit color (Win95 Hack)\n", devMode.dmPelsWidth, devMode.dmPelsHeight, devMode.dmBitsPerPel);
	//  Log(LOG_BOOT, buf);
	modeSwitch = ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
	if(modeSwitch == DISP_CHANGE_SUCCESSFUL) return 0;
	//  Log(LOG_BOOT, "Nope, didnt work\n");

	/* try with separate changes to bitdepth and resolution */
	devMode.dmFields = DM_BITSPERPEL;
	//  sprintf(buf, "Trying %ldx%ldx%ld-bit color (Separate BPP switch)\n", devMode.dmPelsWidth, devMode.dmPelsHeight, devMode.dmBitsPerPel);
	//  Log(LOG_BOOT, buf);
	modeSwitch = ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
	if(modeSwitch == DISP_CHANGE_SUCCESSFUL) {
		devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
		//sprintf(buf, "Trying %ldx%ldx%ld-bit color (Separate resolution switch)\n", devMode.dmPelsWidth, devMode.dmPelsHeight, devMode.dmBitsPerPel);
		//Log(LOG_BOOT, buf);
		modeSwitch = ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
		if(modeSwitch == DISP_CHANGE_SUCCESSFUL) return 0;
		ChangeDisplaySettings(NULL, 0);
	}
	//Log(LOG_BOOT, "Nope, didnt work\n");

	/* Well nothing works now does it */
	if(modeSwitch == DISP_CHANGE_RESTART) {
		//sprintf(buf, "You must change your video mode to %ldx%ldx%ld-bit color and then restart\n", w, h, bitdepth);
		//Log(LOG_BOOT, buf);
	} else if(modeSwitch == DISP_CHANGE_BADMODE) {
		//sprintf(buf, "The video mode %ldx%ldx%ld-bit color is not supported\n", w, h, bitdepth);
		//Log(LOG_BOOT, buf);
	} else if(modeSwitch == DISP_CHANGE_FAILED) {
		//sprintf(buf, "Hardware failed to change to %ldx%ldx%ld-bit color\n", w, h, bitdepth);
		//Log(LOG_BOOT, buf);
	} else {
		//sprintf(buf, "Failed to change to %ldx%ldx%ld-bit color - unknown reason\n", w, h, bitdepth);
		//Log(LOG_BOOT, buf);
	}
	return 1;
}
//---------------------------------------------------------------------------
bool File_DirOperations(
  AnsiString Action,  //COPY, DELETE, MOVE, RENAME
  bool RenameOnCollision, //Renames if directory exists
  bool NoConfirmation, //Responds "Yes to All" to any dialogs
  bool Silent, //No progress dialog is shown
  bool ShowProgress, //displays progress dialog but no file names
  AnsiString FromDir,  //From directory
  AnsiString ToDir   //To directory
  )
{
  TSHFileOpStruct SHFileOpStruct;

  try
  {
    if(!DirectoryExists(FromDir))
    {
      return false;
    }
    ZeroMemory(&SHFileOpStruct, sizeof(SHFileOpStruct));
    SHFileOpStruct.hwnd    = 0;
    if(UpperCase(Action) == "COPY")   SHFileOpStruct.wFunc = FO_COPY;
    if(UpperCase(Action) == "DELETE") SHFileOpStruct.wFunc = FO_DELETE;
    if(UpperCase(Action) == "MOVE")   SHFileOpStruct.wFunc = FO_MOVE;
    if( UpperCase(Action) == "RENAME") SHFileOpStruct.wFunc = FO_RENAME;
    SHFileOpStruct.pFrom  = FromDir.c_str();
    SHFileOpStruct.pTo    = ToDir.c_str();
    SHFileOpStruct.fFlags = FOF_ALLOWUNDO;
    if(RenameOnCollision) SHFileOpStruct.fFlags = SHFileOpStruct.fFlags | FOF_RENAMEONCOLLISION;
    if(NoConfirmation)    SHFileOpStruct.fFlags = SHFileOpStruct.fFlags | FOF_NOCONFIRMATION;
    if(Silent)            SHFileOpStruct.fFlags = SHFileOpStruct.fFlags | FOF_SILENT;
    if(ShowProgress)      SHFileOpStruct.fFlags = SHFileOpStruct.fFlags | FOF_SIMPLEPROGRESS;

    return (SHFileOperation(&SHFileOpStruct) == 0);
  }
  catch(...)
  {
    return false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::Initialize()
{
	char pName[255];
    DWORD nSize;
    nSize=255;
    GetUserName(pName,&nSize);
	m_strUserName=AnsiString(pName);

    nSize=255;
    GetComputerName(pName,&nSize);
	m_strComputerName=AnsiString(pName);

    nSize=255;
    GetWindowsDirectory(pName,nSize);
	m_strWindowsDir=AnsiString(pName);

    m_nFolderIconIndex = GetFolderIconIndex(m_strWindowsDir);
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::LoadSettings()
{
    TIniFile   *IniFile;

	IniFile         = new TIniFile(strIniFileName);
    // Restore window position and size from previous run
//    FormMain->Top             = IniFile->ReadInteger(SectionWindow, KeyTop,
//    										(Screen->Height - FormMain->Height) / 2);
//    FormMain->Left            = IniFile->ReadInteger(SectionWindow, KeyLeft,
//    										(Screen->Width - FormMain->Width) / 2);
//    FormMain->Width           = IniFile->ReadInteger(SectionWindow, KeyWidth,  FormMain->Width);
//    FormMain->Height          = IniFile->ReadInteger(SectionWindow, KeyHeight, FormMain->Height);

    // Restore other parameters
    m_strMe = LocalHostName();
    if (m_strMe.Pos("->") > 0)
    	m_strMe = m_strMe.SubString(1, m_strMe.Pos("->") - 1);
    m_strMe   = IniFile->ReadString(SectionData, KeyFrom,   m_strMe);
    m_strServer = IniFile->ReadString(SectionData, KeyServer, "localhost");
    m_nLanguageID = IniFile->ReadInteger(SectionData, "LanguageID", 0);
    m_bVisible = IniFile->ReadInteger(SectionData, "Visible", false);
    delete IniFile;
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SaveSettings()
{
    TIniFile *IniFile;

    IniFile = new TIniFile(strIniFileName);
    // Save window position and size
//    IniFile->WriteInteger(SectionWindow, KeyTop,       FormMain->Top);
//    IniFile->WriteInteger(SectionWindow, KeyLeft,      FormMain->Left);
//    IniFile->WriteInteger(SectionWindow, KeyWidth,     FormMain->Width);
//    IniFile->WriteInteger(SectionWindow, KeyHeight,    FormMain->Height);
    // Save other parameters
    IniFile->WriteString(SectionData,    KeyFrom,      m_strMe);
    IniFile->WriteString(SectionData,    KeyServer,    m_strServer);
    IniFile->WriteInteger(SectionData, "LanguageID", m_nLanguageID);
    IniFile->WriteInteger(SectionData, "Visible", m_bVisible);
    delete IniFile;
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::DataModuleCreate(TObject *Sender)
{
	m_bConnected = false;
//	InitializeCompression();
    strIniFileName = LowerCase(ChangeFileExt(Application->ExeName,".ini"));
    RequestBroker->IniFileName = strIniFileName;
    Initialize();
	LoadSettings();

    // Start the server. The server is used to receive messages sent by
    // other users thru the central server
    try
    {
    	StartServer();
    }
    catch (Exception& E)
    {
    	// Something failed during server startup. We cannot run
        // the application. Display a message and terminate.
        Application->ShowException(&E);
        Application->Terminate();
    }

    m_pBitmap=new Graphics::TBitmap();
    m_pFolders = new TStringList();
    m_pCaptureThread=new nw_CaptureThread();
    DMClient->m_bDisplaySettingsChanged = false;

    m_bSending = false;
    m_bError = false;
    m_strCurrentSoundUser = "";
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::DataModuleDestroy(TObject *Sender)
{
//	FinalizeCompression();
	SaveSettings();
    
    if (FUserData)
    {
        delete FUserData;
        FUserData = NULL;
        RequestBroker->UserData = 0;
    }
    if(m_pBitmap)	delete m_pBitmap;
    m_pBitmap=NULL;
    if(m_pFolders)	delete m_pFolders;
    m_pFolders = NULL;
    if(m_pCaptureThread)	delete m_pCaptureThread;
    m_pCaptureThread = NULL;

    if(m_bDisplaySettingsChanged)
    {
    	gChangeResolution(nPrevWidth, nPrevHeight, nPrevColors);
    }
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::Connect()
{
    // If we are already connected, then the connect button is disconnect
    if (AppSrvClient->Connected)
        AppSrvClient->Close();
    else
    {
	    FormInput->Caption=FormMessages->ValueListEditor->Values["c_strConnection"];
	    FormInput->LabelUserName->Caption=FormMessages->ValueListEditor->Values["c_strName"];
	    FormInput->EditUserName->Text=m_strMe;
	    FormInput->LabelServerName->Caption=FormMessages->ValueListEditor->Values["c_strServerName"];
	    FormInput->EditServerName->Text=m_strServer;
        FormInput->ComboBoxLanguage->ItemIndex = m_nLanguageID;
	    if(FormInput->ShowModal()==mrOk)
	    {
		    m_strMe = FormInput->EditUserName->Text;
            m_strServer = FormInput->EditServerName->Text;
        	m_nLanguageID = FormInput->ComboBoxLanguage->ItemIndex;
			SaveSettings();
            FormMain->Caption=FormMessages->ValueListEditor->Values["c_strWWPTC"]+" - "+FormMessages->ValueListEditor->Values["c_strNetWatcher"]+" <"+FormMessages->ValueListEditor->Values["c_strClient"]+"> ["+m_strMe+"]";
            FormMain->PanelLanguage->Caption = FormInput->ComboBoxLanguage->Text; 
	        DoConnect();
		}
    }
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::AutoConnect()
{
	FormMain->Caption=FormMessages->ValueListEditor->Values["c_strWWPTC"]+" - "+FormMessages->ValueListEditor->Values["c_strNetWatcher"]+" <"+FormMessages->ValueListEditor->Values["c_strClient"]+"> ["+m_strMe+"]";
    FormInput->ComboBoxLanguage->ItemIndex = m_nLanguageID;
    FormMain->PanelLanguage->Caption = FormInput->ComboBoxLanguage->Text;
    DoConnect();
}
//---------------------------------------------------------------------------
// Connecting to the server is a little bit more than just conection setup.
// We need to send the LOGON request with our name and the port we use for
// our server part to receive the messages from other users.
void __fastcall TDMClient::DoConnect(void)
{
    DWORD TimeOut;

    // Send the LOGON request with our name and server port
    AppSrvClient->FunctionCode = "LOGON";
    AppSrvClient->Server       = m_strServer;
    AppSrvClient->Request->Rewrite();
    AppSrvClient->Request->WriteFields(TRUE,
        ARRAYOFCONST((m_strMe, nPort, m_nLanguageID)));
    AppSrvClient->OnRequestDone = LogonRequestDone;
    AppSrvClient->Send();

    // TAppSrvClient->Send is an asynchrounous function. It means that we get
    // control back immediately while the request execute in the background.
    // We need to wait until the request is done or some timeout elapsed.
    TimeOut = GetTickCount() + 60000;
    while ((TimeOut > GetTickCount()) && (AppSrvClient->State != cstReady))
    {
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
void __fastcall TDMClient::LogonRequestDone(TObject *Sender,int Error)
{
    // Restore the event handler to the default event handler
    AppSrvClient->OnRequestDone = AppSrvClientRequestDone;

    // Check if any error where detected, such as server not responding
    if (Error)
    {
        Display(FormMessages->ValueListEditor->Values["c_strLOCAL"]+"> "+FormMessages->ValueListEditor->Values["c_strLogOnFailed"]+", "+FormMessages->ValueListEditor->Values["c_strErrorNo"]+": "+ IntToStr(Error));
        AppSrvClient->Close();
        m_bError = true;
        return;
    }

    // Check the answer sent back by the server. The status is '200' if ok
    // Any other value is an error, the result set contains the errror msg
    if (AppSrvClient->AnswerStatus != "200")
    {
        Display(FormMessages->ValueListEditor->Values["c_strSERVER"]+"> " + AppSrvClient->Answer->Fields[0]);
        AppSrvClient->Close();
        m_bError = true;
        return;
    }
}
//---------------------------------------------------------------------------
// This event handler is called when a message we sent is processed by the
// chat server.
void __fastcall TDMClient::MessageToRequestDone(TObject *Sender,int Error)
{
    m_bSending = false;

    // Restore the event handler to the default event handler
    AppSrvClient->OnRequestDone = AppSrvClientRequestDone;

    // Check if any error where detected, such as server not responding
    if (Error)
    {
        Display(FormMessages->ValueListEditor->Values["c_strLOCAL"]+"> "+FormMessages->ValueListEditor->Values["c_strMessageToFailed"]+", "+FormMessages->ValueListEditor->Values["c_strErrorNo"]+": " + IntToStr(Error));
        AppSrvClient->Close();
        m_bError = true;
        return;
    }

    // Check the answer sent back by the server. The status is '200' if ok
    // Any other value is an error, the result set contains the errror msg
    if (AppSrvClient->AnswerStatus != "200")
    {
        Display(FormMessages->ValueListEditor->Values["c_strSERVER"]+"> " + AppSrvClient->Answer->Fields[0]);
        m_bError = true;
        return;
    }
}
//---------------------------------------------------------------------------
// This is the default event handler for request done. We should never go
// here unless some programming or timing error occurs.
void __fastcall TDMClient::AppSrvClientRequestDone(TObject *Sender,int Error)
{
    if (Error)
    {
        Display(FormMessages->ValueListEditor->Values["c_strRequest"]+" " + AppSrvClient->FunctionCode +
                " "+FormMessages->ValueListEditor->Values["c_strErrorNo"] +": "+ IntToStr(Error));
        m_bError = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::Display(AnsiString Msg)
{
    // We should check memo overflow !
    if(Msg.Pos("UserExists") > 0)
    {
		if(!DMClient->m_bVisible)
        {
	    	Application->Terminate();
        }
    }
    FormMain->ListBoxMessages->Items->Add(Msg);
    FormMain->ListBoxMessages->ItemIndex = FormMain->ListBoxMessages->Items->Count - 1;
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::AppServerDisplay(TObject *Sender,AnsiString Msg)
{
    Display(Msg);
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SendStream(TMemoryStream *Data,AnsiString strMessageType,AnsiString strMessageTitle,AnsiString strTo)
{
	// Send the message to the remote
    while(m_bSending && (! m_bError))
    {
     	Application->ProcessMessages();
    }

    m_bError = false;
    m_bSending = true;

    AppSrvClient->FunctionCode = "MESSAGETO";
    AppSrvClient->Server       = m_strServer;
    AppSrvClient->Request->Rewrite();
    AppSrvClient->Request->WriteFields(TRUE,
    	ARRAYOFCONST((strTo, m_strMe, strMessageType, strMessageTitle)));
    if(Data)
    {
	    Data->Seek(0, 0);
	    AppSrvClient->Request->AppendStreamField(Data, mwString);
    }
    AppSrvClient->OnRequestDone = MessageToRequestDone;
    AppSrvClient->Send();

    while(m_bSending && (! m_bError))
    {
     	Application->ProcessMessages();
    }
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SendText(AnsiString strText)
{
    if(FormMain->TabControlChat->TabIndex < 0)	return;

    TMemoryStream *Data;
    int           I;

    // Send only if memo is not empty
    strText = strText.Trim();
    m_strLastMessage = strText;
    if(strText == "")	return;

    // Send the message to the remote
    Data = new TMemoryStream;
    try
    {
    	TStringList *pList = new TStringList();
        pList->Text = Encrypt(strText);

//        FormMain->MemoSend->Lines->SaveToStream(Data);
        pList->SaveToStream(Data);
        if(FormMain->TabControlChat->TabIndex == 0)
        {
	        for(int i=1;i<FormMain->TabControlChat->Tabs->Count;i++)
	        {
	        	m_strTo = GetUserName(FormMain->TabControlChat->Tabs->Strings[i]);
	        	SendStream(Data,"TEXT","REQUEST",m_strTo);
	        }
        }
        else
        {
	    	m_strTo = GetUserName(FormMain->TabControlChat->Tabs->Strings[FormMain->TabControlChat->TabIndex]);
            SendStream(Data,"TEXT","REQUEST",m_strTo);
    	}
        if(pList)
        {
         	delete pList;
            pList = NULL;
        }
    }
    __finally
    {
        delete Data;
    }
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SendMessage()
{
	if(FormMain->TabControlMessages->Tabs->Count <= 0)	return;

    TMemoryStream *Data;
    int           I;

    // Send only if memo is not empty
    if(FormMessage->RichEdit->Text == "")	return;

    // Send the message to the remote
    Data = new TMemoryStream;
    try
    {
    	FormMessage->RichEdit->Lines->SaveToStream(Data);
        if(FormMain->TabControlMessages->TabIndex == 0)
        {
	        for(int i=1;i<FormMain->TabControlMessages->Tabs->Count;i++)
	        {
	        	m_strTo = GetUserName(FormMain->TabControlMessages->Tabs->Strings[i]);
	            SendStream(Data,"MESSAGE","REQUEST",m_strTo);
	        }
        }
        else
        {
	    	m_strTo = GetUserName(FormMain->TabControlMessages->Tabs->Strings[FormMain->TabControlMessages->TabIndex]);
            SendStream(Data,"MESSAGE","REQUEST",m_strTo);
    	}
    }
    __finally
    {
        delete Data;
    }
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SendBuffer(Pointer data,int size,AnsiString strType,AnsiString strTitle)
{
    if(FormMain->TabControlChat->TabIndex < 0)	return;

    TMemoryStream *Data;

    // Send the message to the remote
    Data = new TMemoryStream;
    try
    {
    	Data->SetSize(size);
        Data->Position = 0;
        Data->Write(data,size);
        if(FormMain->TabControlChat->TabIndex == 0)
        {
	        for(int i=1;i<FormMain->TabControlChat->Tabs->Count;i++)
	        {
	        	m_strTo = GetUserName(FormMain->TabControlChat->Tabs->Strings[i]);
		        Data->Position = 0;
	        	SendStream(Data,strType,strTitle,m_strTo);
	        }
        }
        else
        {
	    	m_strTo = GetUserName(FormMain->TabControlChat->Tabs->Strings[FormMain->TabControlChat->TabIndex]);
	        Data->Position = 0;
            SendStream(Data,strType,strTitle,m_strTo);
    	}
    }
    __finally
    {
        delete Data;
    }
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SendFileFromRemoteToLocal(AnsiString strTo,AnsiString strFileName,AnsiString strDestFileName)
{
    TMemoryStream *Data;
    // Send the message to the remote
    Data = new TMemoryStream;
    try
    {
    	Data->LoadFromFile(strFileName);
        SendStream(Data,"FILE_FROM_REMOTE",strDestFileName,strTo);
    }
    __finally
    {
        delete Data;
    }
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SendPathFromRemoteToLocal(AnsiString strTo,AnsiString strPath)
{
    TMemoryStream *Data;
    // Send the message to the remote
    Data = new TMemoryStream;
    try
    {
    	if(DirectoryExists(strPath))
        {
			nw_CopyThread *pCopyThread=new nw_CopyThread(true,true);
		    pCopyThread->FreeOnTerminate=true;
		    pCopyThread->OnTerminate=pCopyThread->DoFreeMemory;

		    pCopyThread->m_strSourceDirName=strPath;
            pCopyThread->m_strDestDirName="";
            pCopyThread->m_strCurrDirName=pCopyThread->m_strDestDirName;
		    SetCurrentDir(pCopyThread->m_strSourceDirName);

            pCopyThread->m_strTo = strTo;
		    pCopyThread->Resume();
        }
        else
        if(FileExists(strPath))
        {
        	SendFileFromRemoteToLocal(strTo,strPath,ExtractFileName(strPath));
        }
        else
        {
         	MessageDlg("Invalid Path",mtError,TMsgDlgButtons()<<mbOK,0);
        }
    }
    __finally
    {
        delete Data;
    }
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SendFileFromLocalToRemote(AnsiString strTo,AnsiString strFileName,AnsiString strDestFileName)
{
    TMemoryStream *Data;
    // Send the message to the remote
    Data = new TMemoryStream;
    try
    {
        Data->LoadFromFile(strFileName);
        SendStream(Data,"FILE_FROM_LOCAL",strDestFileName,strTo);
    }
    __finally
    {
        delete Data;
    }
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SendDocument(AnsiString strFileName)
{
	if(FormMain->TabControlMessages->Tabs->Count <= 0)	return;

    AnsiString strPath = "c:\\nw\\";
    AnsiString strDestFileName = strPath+ExtractFileName(strFileName);
    TMemoryStream *Data;
    // Send the message to the remote
    Data = new TMemoryStream;
    try
    {
        Data->LoadFromFile(strFileName);
        if(FormMain->TabControlMessages->TabIndex == 0)
        {
	        for(int i=1;i<FormMain->TabControlMessages->Tabs->Count;i++)
	        {
	        	m_strTo = GetUserName(FormMain->TabControlMessages->Tabs->Strings[i]);
		        SendStream(Data,"DOCUMENT",strDestFileName,m_strTo);
	        }
        }
        else
        {
	    	m_strTo = GetUserName(FormMain->TabControlMessages->Tabs->Strings[FormMain->TabControlMessages->TabIndex]);
	        SendStream(Data,"DOCUMENT",strDestFileName,m_strTo);
    	}
    }
    __finally
    {
        delete Data;
    }
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SendPathFromLocalToRemote(AnsiString strTo,AnsiString strPath)
{
    TMemoryStream *Data;
    // Send the message to the remote
    Data = new TMemoryStream;
    try
    {
    	if(DirectoryExists(strPath))
        {
			nw_CopyThread *pCopyThread=new nw_CopyThread(true,false);
		    pCopyThread->FreeOnTerminate=true;
		    pCopyThread->OnTerminate=pCopyThread->DoFreeMemory;

		    pCopyThread->m_strSourceDirName=strPath;
            pCopyThread->m_strDestDirName="";
            pCopyThread->m_strCurrDirName=pCopyThread->m_strDestDirName;
		    SetCurrentDir(pCopyThread->m_strSourceDirName);

            pCopyThread->m_strTo = strTo;
		    pCopyThread->Resume();
        }
        else
        if(FileExists(strPath))
        {
        	SendFileFromLocalToRemote(strTo,strPath,ExtractFileName(strPath));
        }
        else
        {
         	MessageDlg("Invalid Path",mtError,TMsgDlgButtons()<<mbOK,0);
        }
    }
    __finally
    {
        delete Data;
    }
}
//---------------------------------------------------------------------------
// This event handler is triggered when the connection is established with
// the chat server. This result from the LOGON request in our case.
void __fastcall TDMClient::AppSrvClientSessionConnected(TObject *Sender,WORD Error)
{
    if (Error == 0)
    {
        Display(FormMessages->ValueListEditor->Values["c_strYouAreConnectedToTheServer"]+".");
        DM->AConnect->Caption = FormMessages->ValueListEditor->Values["c_strDisConnect"];
        DM->AConnect->Hint = FormMessages->ValueListEditor->Values["c_strDisConnectHint"];
//        m_bError = true;
		m_bConnected = true;
    }
    else
    {
        Display(FormMessages->ValueListEditor->Values["c_strConnectionWithTheServerFailedErrorNo"] +
                IntToStr(Error));
        DM->AConnect->Caption = FormMessages->ValueListEditor->Values["c_strConnect"];
        DM->AConnect->Hint = FormMessages->ValueListEditor->Values["c_strConnectHint"];
	    m_bError = true;
		m_bConnected = false;
    }
}
//---------------------------------------------------------------------------
// This event handler is called when the session with the chat server is
// closed either because we closed it, or the server closed it.
void __fastcall TDMClient::AppSrvClientSessionClosed(TObject *Sender,WORD Error)
{
    Display(FormMessages->ValueListEditor->Values["c_strYouHaveBeenDisconnectedFromTheServer"]+".");
    DM->AConnect->Caption = FormMessages->ValueListEditor->Values["c_strConnect"];
    DM->AConnect->Hint = FormMessages->ValueListEditor->Values["c_strConnectHint"];
    for(int i = 0; i < c_nServicesCount; i++)
    {
	    DM->TabControls[i]->Tabs->Clear();
    }
    FormMain->PageControl->ActivePageIndex = 0;
    FormSelectClient->TreeViewGroups->Items->Clear();
    FormMain->ListBoxSoundUsers->Items->Clear();
	m_bConnected = false;
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
void __fastcall TDMClient::StartServer(void)
{
    bool Ok;
    int  Cnt;

    nPort = 2122;           // We will start scanning port with this value
    Cnt   = 0;              // We will count to be sure to not loop forever
    Ok    = FALSE;
    // We will loop until we are successful or get any error other than
    // "address already in use". We also stop after 100 ports.
    while (!Ok)
    {
        try
        {
            Cnt++;
            AppServer->Port = IntToStr(nPort);
            AppServer->Start();
            Ok = TRUE;
        }
        catch (const Exception& E)
        {
            if (Cnt > 100)
                throw Exception(FormMessages->ValueListEditor->Values["c_strCantStartServer"]+": " + E.Message);
            if (WSAGetLastError() != WSAEADDRINUSE)
                throw E;
            nPort++;
        }
    }

    // Initialize RequestBroker object 
    RequestBroker->IniFileName = strIniFileName;
    RequestBroker->AddServerObject(__classid(TServerObjectMESSAGETO));

    // Create the user data and pass it to the RequestBroker
    FUserData               = new TUserData;
    FUserData->OnDisplay    = AppServerDisplay;
    RequestBroker->UserData = (long)FUserData;
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SaveAutoFrame()
{
	AnsiString strPath;
    AnsiString strFileName;
    DM->m_pJPEG->Assign(DM->m_pBitmap);
    strPath = "c:\\NW\\AutoWatch\\";
    ForceDirectories(strPath);
    strFileName = strPath+FormatFloat("0000",DM->m_nCurrentAutoWatchClientIndex)+"_"+FormatFloat("0000",DM->m_nCurrentAutoWatchIndex)+".jpg";
    DM->m_pJPEG->SaveToFile(strFileName);

    strFileName = strPath+FormatFloat("0000",DM->m_nCurrentAutoWatchClientIndex)+"_"+FormatFloat("0000",DM->m_nCurrentAutoWatchIndex)+".rtf";
    FormWatch->RichEdit->Lines->SaveToFile(strFileName);
    DM->m_nCurrentFrameIndex = 0;
    DM->m_nCurrentAutoWatchIndex++;
    DMClient->SendWatchCommand(FormMain->TabControlAutoWatch->Tabs->Strings[DM->m_nCurrentAutoWatchClientIndex],false,FormMain->CSpinEditAutoWatchDelay->Value,FormMain->CSpinEditAutoWatchBlockSize->Value);
	DM->m_nCurrentAutoWatchClientIndex++;
	if(DM->m_nCurrentAutoWatchClientIndex >= FormMain->TabControlAutoWatch->Tabs->Count)
    {
	    DM->m_nCurrentAutoWatchClientIndex = 0;
    }
    DM->m_nCurrentFrameIndex = 0;
    DMClient->SendWatchCommand(FormMain->TabControlAutoWatch->Tabs->Strings[DM->m_nCurrentAutoWatchClientIndex],true,FormMain->CSpinEditAutoWatchDelay->Value,FormMain->CSpinEditAutoWatchBlockSize->Value);
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
    AnsiString    FromName;
    AnsiString    ToName;
    TMemoryStream *Data;
    TMWFieldType  FldType;
    AnsiString strMessageType;
    AnsiString strMessageTitle;
    int           I;

    try
    {
        // First field is the destination user name, it should be our name
        ToName     = FRequestBuffer->Fields[0];
        // The second field is the sender username
        FromName   = FRequestBuffer->Fields[1];

        strMessageType = FRequestBuffer->Fields[2];
        strMessageTitle = FRequestBuffer->Fields[3];

        // The third field is the message body as a blob. The blob was made
        // by write a TStrings into a TSream and sending the TSream as a
        // single blob field. We reverse this process here. We will create
        // a TStrings (TStringList) and a TStream (TMemoryStream), fill the
        // stream with the blob field and fill the TStrings with the stream
        // We use try/finally and try/except to be sure to free the object
        // in the case something goes wrong to avoid memory leaks.
        Data = new TMemoryStream;
        try
        {
        	FRequestBuffer->GetStreamField(4, Data, FldType);
            Data->Seek(0,0);
        	if(SameText(strMessageType,"TEXT"))
            {
            	TStringList   *DataBuffer;
	            try
                {
			        DataBuffer = new TStringList;
	                DataBuffer->LoadFromStream(Data);

                    if(SameText(strMessageTitle,"REQUEST"))
                    {
			            // Call the display procedure in UserData for each line
                        AnsiString strText = Decrypt(DataBuffer->Text);
                        FormMain->ListBoxReceive->Items->Add(FromName + " > " + strText);
                        FormMain->ListBoxReceive->ItemIndex = FormMain->ListBoxReceive->Items->Count - 1;

        				DMClient->SendStream(Data,"TEXT","RESPOND",FromName);

                        DM->AChatingExecute(NULL);
                        DM->TrayIcon->Restore();
                    }
                    else
                    if(SameText(strMessageTitle,"RESPOND"))
                    {
					    // Display the message locally
                        FormMain->ListBoxPrevSend->Items->Add(FromName + " < " + DMClient->m_strLastMessage);
                        FormMain->ListBoxPrevSend->ItemIndex = FormMain->ListBoxPrevSend->Items->Count - 1;
                    }
    	        }
	            __finally
                {
		            delete DataBuffer;
	            }
            }
            else
        	if(SameText(strMessageType,"MESSAGE"))
            {
	            try
                {
                    if(SameText(strMessageTitle,"REQUEST"))
                    {
			            // Call the display procedure in UserData for each line
                        FormMessage->RichEdit->Lines->LoadFromStream(Data);
						FormMessage->ShowModal();

//        				DMClient->SendStream(Data,"MESSAGE","RESPOND",FromName);
                    }
                    else
                    if(SameText(strMessageTitle,"RESPOND"))
                    {
					    // Display the message locally
//                        FormMain->ListBoxPrevSend->Items->Add(FromName + "> " + DMClient->m_strLastMessage);
//                        FormMain->ListBoxPrevSend->ItemIndex = FormMain->ListBoxPrevSend->Items->Count - 1;
                    }
    	        }
	            __finally
                {
	            }
            }
            else
        	if(SameText(strMessageType,"SOUND"))
            {
				if(!FormMain->ToolButtonSound->Marked)
                {
	            	FormMain->ACMWaveOut->PlayBack(Data->Memory,Data->Size);
                }
            }
            else
        	if(SameText(strMessageType,"FILE_FROM_REMOTE"))
            {
                AnsiString strPath = IncludeTrailingBackslash(FormMain->ShellTreeView1->Path);
                AnsiString strFileName = strPath + strMessageTitle;
                ForceDirectories(ExtractFilePath(strFileName));
                Data->SaveToFile(strFileName);
            }
            else
        	if(SameText(strMessageType,"FILE_FROM_LOCAL"))
            {
                AnsiString strPath = IncludeTrailingBackslash(FormTempExplorer->ShellTreeView1->Path);
                AnsiString strFileName = strPath + strMessageTitle;
                ForceDirectories(ExtractFilePath(strFileName));
                Data->SaveToFile(strFileName);
            }
            else
        	if(SameText(strMessageType,"DOCUMENT"))
            {
                AnsiString strFileName = strMessageTitle;
                AnsiString strFilePath = ExtractFilePath(strFileName);
                ForceDirectories(strFilePath);
                Data->SaveToFile(strFileName);
                ExecuteProg(FormMain->Handle,strFileName,"",strFilePath,true);
            }
            else
        	if(SameText(strMessageType,"FOLDERS_COMMAND"))
            {
            	AnsiString strCommand;
                int nFolderIndex;
                int nPos;
                nPos = strMessageTitle.Pos(";");
                if(nPos > 0)
                {
                 	strCommand = strMessageTitle.SubString(1,nPos-1);
                    strMessageTitle.Delete(1,nPos);
                    nFolderIndex = StrToInt(strMessageTitle);
                }
                else
                {
                 	strCommand = strMessageTitle;
                    nFolderIndex = 0;
                }

	        	if(SameText(strCommand,"DESKTOP"))
    	        {
	            	FormTempExplorer->ShellListView1->Root = "rfDesktop";
                }
                else
	        	if(SameText(strCommand,"BACK"))
    	        {
                	FormTempExplorer->ShellListView1->Back();
                }
                else
	        	if(SameText(strCommand,"REFRESH"))
    	        {
                	FormTempExplorer->ShellListView1->Refresh();
                }
                else
	        	if(SameText(strCommand,"OPEN"))
                {
                    if(FormTempExplorer->ShellListView1->Folders[nFolderIndex]->IsFolder())
                    {
                    	FormTempExplorer->ShellListView1->TreeUpdate(FormTempExplorer->ShellListView1->Folders[nFolderIndex]->AbsoluteID);
                    }
                    else
                    {
                    	AnsiString strPath = FormTempExplorer->ShellListView1->Folders[nFolderIndex]->PathName();
            			ShellExecute(FormTempExplorer->ShellListView1->Handle, NULL, strPath.c_str(), NULL, ExtractFilePath(strPath).c_str(), SW_SHOW);
                    }

                }
                else
	        	if(SameText(strCommand,"DELETE"))
                {
                	AnsiString strPath = FormTempExplorer->ShellListView1->Folders[nFolderIndex]->PathName();
                    if(FormTempExplorer->ShellListView1->Folders[nFolderIndex]->IsFolder())
                    {
	                	File_DirOperations("DELETE",true,true,true,false,strPath,"");
	                	File_DirOperations("DELETE",true,true,true,false,strPath,"");
                    }
                    else
                    {
						DeleteFile(strPath);
                    }
                }
                FormTempExplorer->ShellListView1->Refresh();
                DMClient->SendFolders(FromName);
            }
            else
        	if(SameText(strMessageType,"FOLDER_COMMAND"))
            {
            	AnsiString strCommand;
                int nFolderIndex;
                int nPos;
                nPos = strMessageTitle.Pos(";");
                if(nPos > 0)
                {
                 	strCommand = strMessageTitle.SubString(1,nPos-1);
                    strMessageTitle.Delete(1,nPos);
                    nFolderIndex = StrToInt(strMessageTitle);
                }
                else
                {
                	throw Exception("Invalid Command <Folder Command>.");
                }

	        	if(SameText(strCommand,"COPY"))
    	        {
    				AnsiString strPath = FormTempExplorer->ShellListView1->Folders[nFolderIndex]->PathName();
                	DMClient->SendPathFromRemoteToLocal(FromName,strPath);
                }
            }
            else
        	if(SameText(strMessageType,"FOLDERS"))
            {
                TListItem *pListItem;
                AnsiString strFolder;
                int nLength;
                bool bIsFolder;
                DMClient->m_pFolders->LoadFromStream(Data);
                FormMain->ListView1->Clear();
                for(int i = 0; i < DMClient->m_pFolders->Count; i++)
                {
	            	pListItem = FormMain->ListView1->Items->Add();
                    strFolder = DMClient->m_pFolders->Strings[i];
                    nLength = strFolder.Length();
                    if(strFolder[nLength] == '1')
                    	bIsFolder = true;
                    else
                    	bIsFolder = false;
                    strFolder.Delete(nLength,1);
                    if(bIsFolder)
	                    pListItem->ImageIndex = DMClient->m_nFolderIconIndex;
                    else
	                    pListItem->ImageIndex = DMClient->GetFileIconIndex(strFolder);
                    pListItem->Caption = strFolder;
                }
                FormMain->PanelPath->Caption = strMessageTitle;
                Application->BringToFront();
            }
            else
        	if(SameText(strMessageType,"WATCH_FEEDBACK"))
            {
            	FormWatch->RichEdit->Lines->LoadFromStream(Data);
            }
            else
        	if(SameText(strMessageType,"WATCH"))
            {
            	if(UpperCase(strMessageTitle).Pos("START") > 0)
                {
                	int nPos = strMessageTitle.Pos(";");
                    strMessageTitle.Delete(1,nPos);
                	nPos = strMessageTitle.Pos(";");
                    int Interval = StrToInt(strMessageTitle.SubString(1,nPos-1));
                    strMessageTitle.Delete(1,nPos);
                    int FrameSize = StrToInt(strMessageTitle);

                	DMClient->SendWatchFeedBackCommand(FromName);

                    g_bIsFirstScan = true;
                    g_nCurrIndex = 0;

    				int nFrameW,nFrameH;
					//    nFrameH=24;
					//    nFrameH=32;
					//    nFrameH=48;
					//    nFrameH=64;
//					nFrameH=96;
//				    nFrameH=128;
					//    nFrameH=192;
//					    nFrameH=256;
//					    nFrameH=384;
//					    nFrameH=512;
					//    nFrameW=nFrameH*Ratio;
                    nFrameH = FrameSize;
				    nFrameW=nFrameH;
                    m_pCaptureThread->SetCaptureSettings(nFrameW+nFrameH,nFrameW,nFrameH);
                    m_pCaptureThread->m_pBitmap->PixelFormat = pf24bit;
                    g_pJPEG->PixelFormat = jf24Bit;
                    m_pCaptureThread->m_bConference = false;
                    m_pCaptureThread->m_strTo=FromName;
                    m_pCaptureThread->m_pTimer->Interval = Interval;
				    m_pCaptureThread->m_pTimer->Enabled = true;
				}
                else
            	if(SameText(strMessageTitle,"STOP"))
                {
				    m_pCaptureThread->m_pTimer->Enabled = false;
				}
            }
            else
        	if(SameText(strMessageType,"MAINTENANCE"))
            {
            	if(SameText(strMessageTitle,"START"))
                {

                    HDC hdc = GetWindowDC(GetDesktopWindow());
                    nPrevWidth = GetDeviceCaps(hdc, HORZRES);
                    nPrevHeight = GetDeviceCaps(hdc, VERTRES);
                    nPrevColors = GetDeviceCaps(hdc, BITSPIXEL);
					gChangeResolution(800, 600, 16);
                    DMClient->m_bDisplaySettingsChanged = true;

                    g_bIsFirstScan = true;
                    g_nCurrIndex = 0;

    				int nFrameW,nFrameH;
					//    nFrameH=24;
					//    nFrameH=32;
					//    nFrameH=48;
//					nFrameH=64;
//                    nFrameH=96;
//				    nFrameH=128;
					//nFrameH=192;
//					nFrameH=256;
					    nFrameH=384;
					//    nFrameH=512;
					//    nFrameW=nFrameH*Ratio;
				    nFrameW=nFrameH;
                    m_pCaptureThread->SetCaptureSettings(nFrameW+nFrameH,nFrameW,nFrameH);
                    m_pCaptureThread->m_pBitmap->PixelFormat = pf8bit;
                    g_pJPEG->PixelFormat = jf8Bit;
                    m_pCaptureThread->m_bConference = false;
                    m_pCaptureThread->m_strTo=FromName;
                    m_pCaptureThread->m_pTimer->Interval = 1;
				    m_pCaptureThread->m_pTimer->Enabled = true;
				}
                else
                {
				    m_pCaptureThread->m_pTimer->Enabled = false;
					gChangeResolution(nPrevWidth, nPrevHeight, nPrevColors);
                    DMClient->m_bDisplaySettingsChanged = false;
				}
            }
            else
            if(SameText(strMessageType,"CONFERENCE"))
            {
            	if(SameText(strMessageTitle,"START"))
                {
            		FormFullScreen->Show();
                }
                else
                {
            		FormFullScreen->Close();
                }
            }
            else
        	if(SameText(strMessageType,"IMAGE"))
            {
/*
    			TMemoryStream *pStream = new TMemoryStream();
                __int64 nSize;
                int nBytesRead;
                while(true)
                {
                 	nBytesRead = Data->Read(&nSize,sizeof(nSize));
                    if(nBytesRead <= 0)	break;
                    pStream->Position = 0;
                    pStream->CopyFrom(Data,nSize);

	                if(FormFullScreen->Visible)
                    	DeCompress(pStream,FormFullScreen->Canvas);
	                else
                    	DeCompress(pStream,FormMain->PaintBox->Canvas);
                }
                if(pStream)	delete pStream;
                pStream = NULL;
*/

			    if(DM->ServiceType == stAutoWatch)
			    {
                	DeCompress(Data,DM->m_pBitmap->Canvas);
                	DM->m_nCurrentFrameIndex++;
                    if(DM->m_nCurrentFrameIndex >= DM->m_nFrameCount)
                    {
                    	DMClient->SaveAutoFrame();
                    }
                }
                else
                {
	                if(FormFullScreen->Visible)
	                {
//   	             	if(FormFullScreen->Image->Visible)
//	    	            	DeCompress(Data,FormFullScreen->Image->Canvas);
//          	          else
	            	        DeCompress(Data,DM->m_pBitmap->Canvas);
	                		DeCompress(Data,FormFullScreen->Canvas);
	                }
    	            else
        	        {
//          	          DeCompress(Data,FormFullScreen->Image->Canvas);
//              	      DeCompress(Data,FormMain->Image->Canvas);
                    	DeCompress(Data,DM->m_pBitmap->Canvas);
	                    DeCompress(Data,FormMain->PaintBox->Canvas);
//  	            		FormMain->Image->Picture->Bitmap->Assign(FormFullScreen->Image->Picture->Bitmap);
        	        }
				}
            }
            else
        	if(SameText(strMessageType,"KEYBOARD_COMMAND"))
            {
                int nPos;
                WORD wKey;
                WORD wShift;

				// Key
                nPos = strMessageTitle.Pos(";");
                wKey = StrToInt(strMessageTitle.SubString(1,nPos-1));
                strMessageTitle.Delete(1,nPos);

				// Shift
                wShift = StrToInt(strMessageTitle);

/*
				// Key
                wKey = StrToInt(strMessageTitle);
                strMessageTitle.Delete(1,nPos);

				StdInput.type = INPUT_KEYBOARD;
    			StdInput.ki.wVk = wKey;
    			StdInput.ki.wScan = 0;
    			StdInput.ki.dwFlags = 0;
    			StdInput.ki.time = 0;
    			StdInput.ki.dwExtraInfo = 0;
    			SendInput(1,&StdInput,sizeof(StdInput));
*/
	
				keybd_event(wKey,wShift,0,0);
            }
            else
        	if(SameText(strMessageType,"MOUSE_COMMAND"))
            {
                int nPos;
                DWORD dwFlag;
                int nX,nY;

				// Flag
                nPos = strMessageTitle.Pos(";");
                dwFlag = StrToInt(strMessageTitle.SubString(1,nPos-1));
                strMessageTitle.Delete(1,nPos);

				// X
                nPos = strMessageTitle.Pos(";");
                nX = StrToInt(strMessageTitle.SubString(1,nPos-1));
                strMessageTitle.Delete(1,nPos);

				// Y
                nY = StrToInt(strMessageTitle);

//                SendMessage(GetActiveWindow(),
                if(dwFlag == MOUSEEVENTF_MOVE)
                {
                 	SetCursorPos(nX,nY);
                }
                else
                {
	                StdInput.type = INPUT_MOUSE;
	                StdInput.mi.dwFlags = dwFlag;
	                StdInput.mi.dx = nX;
	                StdInput.mi.dy = nY;
	                StdInput.mi.mouseData = 0;
	                StdInput.mi.time = 0;
	                StdInput.mi.dwExtraInfo = 0;
    	            SendInput(1,&StdInput,sizeof(StdInput));
                }
            }
            else
        	if(SameText(strMessageType,"WINDOWS_MESSAGE"))
            {
			    UINT Msg;	// message to send
			    WPARAM wParam;	// first message parameter
			    LPARAM lParam; 	// second message parameter
                int nPos;

				// Msg
                nPos = strMessageTitle.Pos(";");
                Msg = StrToInt(strMessageTitle.SubString(1,nPos-1));
                strMessageTitle.Delete(1,nPos);

				// wParam
                nPos = strMessageTitle.Pos(";");
                wParam = StrToInt(strMessageTitle.SubString(1,nPos-1));
                strMessageTitle.Delete(1,nPos);

				// lParam
                lParam = StrToInt(strMessageTitle);

//                PostMessage(GetActiveWindow(),Msg,wParam,lParam);

				DMClient->m_Msg.hwnd = GetActiveWindow();
                DMClient->m_Msg.message = Msg;
                DMClient->m_Msg.wParam = wParam;
                DMClient->m_Msg.lParam = lParam;
                DMClient->m_Msg.time = GetTickCount();
                GetCursorPos(&DMClient->CursorPos);
                DMClient->m_Msg.pt.x = DMClient->CursorPos.x;
                DMClient->m_Msg.pt.y = DMClient->CursorPos.y;
				TranslateMessage(&DMClient->m_Msg);
            }
            else
        	if(SameText(strMessageType,"DESKTOP_SETTINGS_COMMAND"))
            {
                int nPos;
                int nColors,nWidth,nHeight;

				// Colors
                nPos = strMessageTitle.Pos(";");
                nColors = StrToInt(strMessageTitle.SubString(1,nPos-1));
                strMessageTitle.Delete(1,nPos);

				// Width
                nPos = strMessageTitle.Pos(";");
                nWidth = StrToInt(strMessageTitle.SubString(1,nPos-1));
                strMessageTitle.Delete(1,nPos);

				// Height
                nHeight = StrToInt(strMessageTitle);

                gChangeResolution(nWidth, nHeight, nColors);
            }
            else
        	if(SameText(strMessageType,"COMMAND_PROMPT"))
            {
				TStringList *pList = new TStringList();
                AnsiString strPath = IncludeTrailingBackslash(ExtractShortPathName(GetCurrentDir()));
                AnsiString strExeName = strPath+"execute.bat";
                AnsiString strResName = strPath+"result.txt";
				pList->Add("REM CommandInterpreter: $(COMSPEC)");
				pList->Add(strMessageTitle+" > "+strResName);
                pList->SaveToFile(strExeName);

                Wait(ExecuteProg(0,strExeName,"",ExtractFilePath(strExeName),SW_HIDE));
                
                if(FileExists(strResName))
                {
	                pList->LoadFromFile(strResName);
                	pList->Add(strPath+">");

	                TMemoryStream *pStream = new TMemoryStream();
    	            pList->SaveToStream(pStream);
    				DMClient->SendStream(pStream,"COMMAND_PROMPT_RESULT","",FromName);

            	    if(pStream)	delete pStream;
                	pStream = NULL;
                }

                if(FileExists(strExeName))	DeleteFile(strExeName);
                if(FileExists(strResName))	DeleteFile(strResName);
				if(pList)	delete pList;
                pList = NULL;
            }
            else
        	if(SameText(strMessageType,"COMMAND_PROMPT_RESULT"))
            {
				TStringList *pList = new TStringList();
                pList->LoadFromStream(Data);
                pList->Text = pList->Text.Trim();
                for(int i = 0; i < pList->Count; i++)
                {
	                FormMain->MemoCommandPromptResult->Lines->Add(pList->Strings[i]);
                }
//                FormMain->MemoCommandPromptResult->Lines->Text = FormMain->MemoCommandPrompt->Lines->Text.Trim();
//                SendMessage(FormMain->MemoCommandPromptResult->Handle,EM_LINESCROLL,FormMain->MemoCommandPrompt->Lines->Count,FormMain->MemoCommandPrompt->Lines->Count);
//                SendMessage(FormMain->MemoCommandPromptResult->Handle,EM_SCROLLCARET,FormMain->MemoCommandPrompt->Lines->Count,FormMain->MemoCommandPrompt->Lines->Count);
				if(pList)	delete pList;
                pList = NULL;
            }
            else
        	if(SameText(strMessageType,"CONNECTED_CLIENTS"))
            {
            	if(DMClient->m_bConnected)
                {
    	            // Update TreeView
                	FormSelectClient->TreeViewGroups->LoadFromStream(Data);
                    for(int i=0;i<FormSelectClient->TreeViewGroups->Items->Count;i++)
                    {
    					if(SameText(FormSelectClient->TreeViewGroups->Items->Item[i]->Text,ToName))
	                    {
    						FormSelectClient->TreeViewGroups->Items->Delete(FormSelectClient->TreeViewGroups->Items->Item[i]);
	                    }
                    }

        	        // Update Tabs
                    int nTabIndex;
                    AnsiString strTabTitle;
                    bool bFound;
                    for(int i=0;i<c_nServicesCount;i++)
                    {
    	                for(int j=0;j<DM->TabControls[i]->Tabs->Count;j++)
	                    {
	    	             	strTabTitle=DM->TabControls[i]->Tabs->Strings[j];
		                    bFound=false;
	    		            for(int k=0;k<FormSelectClient->TreeViewGroups->Items->Count;k++)
		        		    {
	    						if(SameText(strTabTitle,FormMessages->ValueListEditor->Values["c_strAll"]))
				                {
		                            bFound=true;
	                                break;
	            		        }
	                            else
	    						if(SameText(FormSelectClient->TreeViewGroups->Items->Item[k]->Text,strTabTitle))
				                {
		                            bFound=true;
	                                break;
	            		        }
	                    	}
	                        if(!bFound)
	                        {
	                        	DM->TabControls[i]->Tabs->Delete(j);
	                        }
                        }

                    	if(DM->TabControls[i]->Tabs->Count == 1)
                        {
	    	                strTabTitle=DM->TabControls[i]->Tabs->Strings[0];
                            if(SameText(strTabTitle,FormMessages->ValueListEditor->Values["c_strAll"]))
                            {
	                        	DM->TabControls[i]->Tabs->Delete(0);
                            }
                        }
                    }
                }
            }
            else
        	if(SameText(strMessageType,"SOUND_USERS"))
            {
            	if(DMClient->m_bConnected)
                {
    	            // Update ListBox Sound Users
                	FormMain->ListBoxSoundUsers->Items->LoadFromStream(Data);
                    if(FormMain->ListBoxSoundUsers->Items->Count > 0)
                    {
                    	if(SameText(FormMain->ListBoxSoundUsers->Items->Strings[0] ,DMClient->m_strMe))
                        {
		                    if(FormMain->ListBoxSoundUsers->Items->Count == 1)
        		            {
    					 		FormMain->InitializeSoundIn();
								FormMain->ToolButtonSound->Marked = true;
                            }
                            else
	                    	if(!SameText(DMClient->m_strMe ,DMClient->m_strCurrentSoundUser))
    	                    {
    					 		FormMain->InitializeSoundIn();
								FormMain->ToolButtonSound->Marked = true;
        	                }
						}
                        else
                        {
	                    	if(SameText(DMClient->m_strMe ,DMClient->m_strCurrentSoundUser))
    	                    {
    							FormMain->FinalizeSoundIn();
        	                    FormMain->ToolButtonSound->Marked = false;
        	                }
                        }
                        DMClient->m_strCurrentSoundUser = FormMain->ListBoxSoundUsers->Items->Strings[0];
                    }
                    else
                    {
                    	if(SameText(DMClient->m_strMe ,DMClient->m_strCurrentSoundUser))
                        {
                        	FormMain->FinalizeSoundIn();
                            FormMain->ToolButtonSound->Marked = false;
                        }
                    }
                }
            }

            // Send an ok response to the sender
            FResponseBuffer->WriteFields(TRUE, ARRAYOFCONST(("Ok")));
            FResultStatus = 200;
        }
        __finally
        {
        	delete Data;
        }
    }
    catch (const Exception& E)
    {
        FResponseBuffer->WriteFields(TRUE, ARRAYOFCONST((E.Message)));
        FResultStatus = 401;
    }
    Finish();
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SendWatchCommand(AnsiString strTo,bool bStart,int nInterval,int nFrameSize)
{
	if(strTo == "")
    {
		if(FormMain->TabControlMonitoring->TabIndex < 0)	return;
		m_strTo = GetUserName(FormMain->TabControlMonitoring->Tabs->Strings[FormMain->TabControlMonitoring->TabIndex]);
    }
    else
    {
		m_strTo = strTo;
    }
    if(bStart)
    {
    	SendStream(NULL,"WATCH","START;"+IntToStr(nInterval)+";"+IntToStr(nFrameSize),m_strTo);
    }
    else
    {
    	SendStream(NULL,"WATCH","STOP",m_strTo);
    }
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SendWatchFeedBackCommand(AnsiString strTo)
{
	TStringList *pList = new TStringList();
    pList->Add(FormMessages->ValueListEditor->Values["c_strComputerName"]+": "+m_strComputerName);
    pList->Add(FormMessages->ValueListEditor->Values["c_strUserName"]+": "+m_strUserName);
    pList->Add(FormMessages->ValueListEditor->Values["c_strConnectionName"]+": "+m_strMe);
    pList->Add(FormMessages->ValueListEditor->Values["c_strDate"]+": "+DateToStr(Date()));
    pList->Add(FormMessages->ValueListEditor->Values["c_strTime"]+": "+TimeToStr(Now()));

    TMemoryStream *pStream = new TMemoryStream();

    pList->SaveToStream(pStream);
	SendStream(pStream,"WATCH_FEEDBACK","",strTo);

    if(pStream)	delete pStream;
    pStream = NULL;
    if(pList)	delete pList;
    pList = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SendMaintenanceCommand(bool bStart)
{
	if(FormMain->TabControlMaintenance->Tabs->Count <= 0)	return;
	m_strTo = GetUserName(FormMain->TabControlMaintenance->Tabs->Strings[0]);
    if(bStart)
    {
    	SendStream(NULL,"MAINTENANCE","START",m_strTo);
    }
    else
    {
    	SendStream(NULL,"MAINTENANCE","STOP",m_strTo);
    }
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SendFoldersCommand(AnsiString strCommand,int nFolderIndex)
{
	if(FormMain->TabControlFileManager->TabIndex < 0)	return;
	AnsiString strFolderIndex = IntToStr(nFolderIndex);
    m_strTo = GetUserName(FormMain->TabControlFileManager->Tabs->Strings[FormMain->TabControlFileManager->TabIndex]);
    SendStream(NULL,"FOLDERS_COMMAND",strCommand+";"+strFolderIndex,m_strTo);
}
//---------------------------------------------------------------------------
int __fastcall TDMClient::GetFileIconIndex(AnsiString strFileName)
{
    SHFILEINFO FileInfo;
	SHGetFileInfo(strFileName.c_str(), FILE_ATTRIBUTE_NORMAL, &FileInfo,sizeof(FileInfo),SHGFI_USEFILEATTRIBUTES|SHGFI_ICON);
	return FileInfo.iIcon;
}
//---------------------------------------------------------------------------
int __fastcall TDMClient::GetFolderIconIndex(AnsiString strFolderName)
{
    SHFILEINFO FileInfo;
	SHGetFileInfo(strFolderName.c_str(), 0, &FileInfo,sizeof(FileInfo),SHGFI_SYSICONINDEX | SHGFI_LARGEICON);
	return FileInfo.iIcon;
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SendFolders(AnsiString strTo)
{
    TMemoryStream *Data;

    // Send the message to the remote
    Data = new TMemoryStream;
    try
    {
        TStringList *pList = new TStringList();
		AnsiString strFolder;
        AnsiString strPath;
        int nIconIndex;
        for(int i = 0; i < FormTempExplorer->ShellListView1->Items->Count; i++)
        {      
        	strFolder = FormTempExplorer->ShellListView1->Items->Item[i]->Caption;
            if(FormTempExplorer->ShellListView1->Folders[i]->IsFolder())
	            strFolder+="1";
            else
	            strFolder+="0";
	        pList->Add(strFolder);
        }

    	pList->SaveToStream(Data);
        strPath = FormTempExplorer->ShellTreeView1->Path;
        SendStream(Data,"FOLDERS",strPath,strTo);

        if(pList)	delete pList;
        pList = NULL;
    }
    __finally
    {
        delete Data;
    }
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SendFolderCommand(AnsiString strCommand,int nFolderIndex)
{
	if(FormMain->TabControlFileManager->TabIndex < 0)	return;
	AnsiString strFolderIndex = IntToStr(nFolderIndex);
    m_strTo = GetUserName(FormMain->TabControlFileManager->Tabs->Strings[FormMain->TabControlFileManager->TabIndex]);
    SendStream(NULL,"FOLDER_COMMAND",strCommand+";"+strFolderIndex,m_strTo);
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::CopyFolders(AnsiString strPath)
{
	if(FormMain->TabControlFileManager->TabIndex < 0)	return;
    m_strTo = GetUserName(FormMain->TabControlFileManager->Tabs->Strings[FormMain->TabControlFileManager->TabIndex]);
    DMClient->SendPathFromLocalToRemote(m_strTo,strPath);
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SendKeyboardCommand(Word wKey,Word wShift)
{
	if(FormMain->TabControlMaintenance->Tabs->Count <= 0)	return;
	m_strTo = GetUserName(FormMain->TabControlMaintenance->Tabs->Strings[0]);
    SendStream(NULL,"KEYBOARD_COMMAND",IntToStr(wKey)+";"+IntToStr(wShift),m_strTo);
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SendMouseCommand(DWORD dwFlag,int nX,int nY)
{
	if(FormMain->TabControlMaintenance->Tabs->Count <= 0)	return;
	m_strTo = GetUserName(FormMain->TabControlMaintenance->Tabs->Strings[0]);
    SendStream(NULL,"MOUSE_COMMAND",IntToStr(dwFlag)+";"+IntToStr(nX)+";"+IntToStr(nY),m_strTo);
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SendWindowsMessage(UINT Msg,WPARAM wParam,LPARAM lParam)
{
	if(FormMain->TabControlMaintenance->Tabs->Count <= 0)	return;
	m_strTo = GetUserName(FormMain->TabControlMaintenance->Tabs->Strings[0]);
    SendStream(NULL,"WINDOWS_MESSAGE",IntToStr(Msg)+";"+IntToStr(wParam)+";"+IntToStr(lParam),m_strTo);
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SendDesktopSettingsCommand(int nColors,int nWidth,int nHeight)
{
	if(FormMain->TabControlMaintenance->Tabs->Count <= 0)	return;
	m_strTo = GetUserName(FormMain->TabControlMaintenance->Tabs->Strings[0]);
    SendStream(NULL,"DESKTOP_SETTINGS_COMMAND",IntToStr(nColors)+";"+IntToStr(nWidth)+";"+IntToStr(nHeight),m_strTo);
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::AppSrvClientSocksError(TObject *Sender,
      int Error, AnsiString Msg)
{
	m_bError = true;
    Display(Msg);
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SendCommandPromptCommand(AnsiString strCommand)
{
	if(FormMain->TabControlCommandPrompt->TabIndex < 0)	return;
    m_strTo = GetUserName(FormMain->TabControlCommandPrompt->Tabs->Strings[FormMain->TabControlCommandPrompt->TabIndex]);
    SendStream(NULL,"COMMAND_PROMPT",strCommand,m_strTo);
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SendSoundCommand(bool bStart)
{
	m_strTo = "SERVER";
    if(bStart)
    {
    	SendStream(NULL,"SOUND_COMMAND","START",m_strTo);
    }
    else
    {
    	SendStream(NULL,"SOUND_COMMAND","STOP",m_strTo);
    }
}
//---------------------------------------------------------------------------
void __fastcall TDMClient::SendConferenceCommand(bool bStart)
{
	AnsiString strTo;
    if(FormMain->TabControlConference->TabIndex == 0)
    {
	    for(int i=1;i<FormMain->TabControlConference->Tabs->Count;i++)
	    {
	    	m_strTo = GetUserName(FormMain->TabControlConference->Tabs->Strings[i]);
		    if(bStart)
		    {
				DMClient->SendStream(NULL,"CONFERENCE","START",m_strTo);
		    }
		    else
		    {
				DMClient->SendStream(NULL,"CONFERENCE","STOP",m_strTo);
		    }
	    }
    }
    else
    {
		m_strTo = GetUserName(FormMain->TabControlConference->Tabs->Strings[FormMain->TabControlConference->TabIndex]);
	    if(bStart)
	    {
			DMClient->SendStream(NULL,"CONFERENCE","START",m_strTo);
	    }
	    else
	    {
			DMClient->SendStream(NULL,"CONFERENCE","STOP",m_strTo);
	    }
    }
}
//---------------------------------------------------------------------------

