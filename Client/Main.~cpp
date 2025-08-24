//---------------------------------------------------------------------------

#include <vcl.h>
#include <inifiles.hpp>
#pragma hdrstop

#include "Main.h"
#include "DataModule.h"
#include "nw_Messages.h"
#include "Input.h"
#include "ClientProcess.h"
#include "FullScreen.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ShellCtrls"
#pragma link "ShellCtrls"
#pragma link "FormTranslation"
#pragma link "ACMDialog"
#pragma link "ACMWaveIn"
#pragma link "ACMWaveOut"
#pragma link "CSPIN"
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::CreateParams(Controls::TCreateParams &Params)
{
	TCustomForm::CreateParams(Params);
	Params.Style |= WS_MINIMIZE;
    Params.ExStyle |= WS_EX_ACCEPTFILES;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::DropFiles(HDROP hDrop)
{ 
	if(TabControlMessages->Tabs->Count <= 0)
    {
    	PanelMessages->Caption = FormMessages->ValueListEditor->Values["c_strSelectClientsFirst"];
    	return;
    }
    else
    {
    	PanelMessages->Caption = FormMessages->ValueListEditor->Values["c_strMessages"];
    }

	char szPath[MAX_PATH];
	UINT nDropped;

	// Get number of files dropped
	nDropped = DragQueryFile(hDrop,0xFFFFFFFF,NULL,0);
	if(nDropped)
    {
		SetActiveWindow(WindowHandle);

		// If we wanted to, we could simulate a click at the position
		// the drop took place....
        POINT P;
        DragQueryPoint(hDrop,&P);
//        PanelHere->Left = P.x;
//        PanelHere->Top = P.y;

		for (UINT n = 0; n < nDropped; n++)
        {
			// Get the file that was dropped....
			DragQueryFile(hDrop, n, szPath, MAX_PATH);

			DMClient->SendDocument(szPath);
		}
	}
	DragFinish(hDrop); /* Delete structure alocated */
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::WndProc(Messages::TMessage &Message)
{
    switch(Message.Msg)
    {
		case WM_DROPFILES:
        {
        	HDROP hDrop = (HANDLE)Message.WParam;
     		DropFiles(hDrop);
         	break;
        }
    }
	TCustomForm::WndProc(Message);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::InitializeSoundIn()
{
	ACMWaveIn->Close();

	tWAVEFORMATEX Format;
    PWaveFormatEx pFormat;

    Format.wFormatTag = 1;
    Format.nChannels = 1;
    Format.nSamplesPerSec = 8000;
    Format.nAvgBytesPerSec = 8000;
    Format.nBlockAlign = 1;
    Format.wBitsPerSample = 8;
    Format.cbSize = 18964;

//	pFormat = (PWaveFormatEx)ACMDialog->OpenDialog();
	pFormat = &Format;

    if(pFormat == NULL)	return;
    ACMWaveIn->Open(pFormat);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FinalizeSoundIn()
{
	ACMWaveIn->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::InitializeSoundOut()
{
    ACMWaveOut->Close();

	tWAVEFORMATEX Format;
    PWaveFormatEx pFormat;

    Format.wFormatTag = 1;
    Format.nChannels = 1;
    Format.nSamplesPerSec = 8000;
    Format.nAvgBytesPerSec = 8000;
    Format.nBlockAlign = 1;
    Format.wBitsPerSample = 8;
    Format.cbSize = 18964;

//	pFormat = (PWaveFormatEx)ACMDialog->OpenDialog();
	pFormat = &Format;

    if(pFormat == NULL)	return;
    ACMWaveOut->Open(pFormat);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FinalizeSoundOut()
{
    ACMWaveOut->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ClearTabs()
{
	for(int i=0;i<c_nServicesCount;i++)
    {
     	DM->TabControls[i]->Tabs->Clear();
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
    DM->TabControls[0] = TabControlChat;
    DM->TabControls[1] = TabControlMonitoring;
    DM->TabControls[2] = TabControlFileManager;
    DM->TabControls[3] = TabControlCommandPrompt;
    DM->TabControls[4] = TabControlMaintenance;
    DM->TabControls[5] = TabControlMessages;
    DM->TabControls[6] = TabControlConference;
    DM->TabControls[7] = TabControlAutoWatch;
    ClearTabs();

	// Define ListView ImageList (System ImageList)
    SHFILEINFO FileInfo;
    int nSmallImageList;
    int nLargeImageList;
    nLargeImageList=SHGetFileInfo("",0,&FileInfo,sizeof(FileInfo),SHGFI_SYSICONINDEX | SHGFI_LARGEICON);
    nSmallImageList=SHGetFileInfo("",0,&FileInfo,sizeof(FileInfo),SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
    if(nLargeImageList)
    	SendMessage(FormMain->ListView1->Handle, LVM_SETIMAGELIST, LVSIL_NORMAL, nLargeImageList);
    if(nSmallImageList)
    	SendMessage(FormMain->ListView1->Handle, LVM_SETIMAGELIST, LVSIL_SMALL, nSmallImageList);

    try
    {
	    DM->TrayIcon->Visible = DMClient->m_bVisible;
    }
    catch(...)
    {}
    DM->TrayIcon->Minimize();

    InitializeSoundOut();
    PageControl->ActivePageIndex = 0;


//    Image->Width = 0;
//    Image->Height = 0;

	DM->TimerConnection->Enabled = !DMClient->m_bVisible;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
	FinalizeSoundOut();		
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TreeViewGroupsGetSelectedIndex(TObject *Sender,
      TTreeNode *Node)
{
 	Node->SelectedIndex = Node->ImageIndex;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MemoSendKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	switch(Key)
    {
     	case VK_RETURN:
        {
        	DMClient->SendText(FormMain->MemoSend->Text);
        	FormMain->MemoSend->Clear();
         	break;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ListView1DblClick(TObject *Sender)
{
	DM->AOpenExecute(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolButton1Click(TObject *Sender)
{
	DM->ABackExecute(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ListView1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	switch(Key)
    {
        case VK_BACK:
        {
        	DM->ABackExecute(NULL);
            break;
        }
     	case VK_F5:
        {
    		DM->ARefreshExecute(NULL);
         	break;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ListView1DragOver(TObject *Sender,
      TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
	Accept = Source->ClassNameIs("TShellListView");
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ListView1DragDrop(TObject *Sender,
      TObject *Source, int X, int Y)
{
  	if(Sender->ClassNameIs("TListView") && Source->ClassNameIs("TShellListView"))
  	{
		TShellListView *pShellListView = (TShellListView *)Source;

        if(pShellListView->Selected)
        {
			AnsiString strPath = FormMain->ShellListView1->Folders[pShellListView->Selected->Index]->PathName();
            DMClient->CopyFolders(strPath);
        }
  	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ShellListView1DragOver(TObject *Sender,
      TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
	Accept = Source->ClassNameIs("TListView");
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ShellListView1DragDrop(TObject *Sender,
      TObject *Source, int X, int Y)
{
  	if(Sender->ClassNameIs("TShellListView") && Source->ClassNameIs("TListView"))
  	{
    	TListView *pListView = (TListView *)Source;

        if(pListView->Selected)
        {
	        DMClient->SendFolderCommand("COPY",pListView->Selected->Index);
        }
  	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ImageDblClick(TObject *Sender)
{
//	if(Image->Picture->Bitmap->Width * Image->Picture->Bitmap->Height > 0)
    {
//	    FormFullScreen->Image->Visible = true;
		FormFullScreen->ShowModal();
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabSheet4Show(TObject *Sender)
{
//	DMClient->SendMaintenanceCommand(true);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabSheet4Hide(TObject *Sender)
{
//	DMClient->SendMaintenanceCommand(false);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabControlChatChanging(TObject *Sender,
      bool &AllowChange)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabControlChatChange(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabControlMonitoringChanging(TObject *Sender,
      bool &AllowChange)
{
	DM->AStopWatchingExecute(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabControlMonitoringChange(TObject *Sender)
{
	DM->AStartWatchingExecute(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabControlFileManagerChanging(TObject *Sender,
      bool &AllowChange)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabControlFileManagerChange(TObject *Sender)
{
	DMClient->SendFoldersCommand("DESKTOP",0);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabControlMaintenanceChanging(TObject *Sender,
      bool &AllowChange)
{
	DM->AStopMaintenanceExecute(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabControlMaintenanceChange(TObject *Sender)
{
	DM->AStartMaintenanceExecute(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MemoCommandPromptKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
	switch(Key)
    {
     	case VK_RETURN:
        {
			MemoCommandPrompt->Lines->Text = MemoCommandPrompt->Lines->Text.Trim();
        	if(MemoCommandPrompt->Lines->Count > 0)
            {
            	AnsiString strCommand = MemoCommandPrompt->Lines->Strings[MemoCommandPrompt->Lines->Count-1];
	        	DMClient->SendCommandPromptCommand(strCommand);
            }
            MemoCommandPrompt->Lines->Text = "";
         	break;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PageControlChanging(TObject *Sender,
      bool &AllowChange)
{
	switch(PageControl->ActivePageIndex)
    {
     	case 1:
        {
			DM->AStopSoundExecute(NULL);
         	break;
        }
     	case 2:
        {
			DM->AStopWatchingExecute(NULL);
         	break;
        }
     	case 3:
        {
         	break;
        }
     	case 4:
        {
         	break;
        }
     	case 5:
        {
			DM->AStopMaintenanceExecute(NULL);
         	break;
        }
     	case 6:
        {
         	break;
        }
     	case 7:
        {
         	break;
        }
     	case 8:
        {
			DM->AStopAutoWatchExecute(NULL);
         	break;
        }
    }

	AllowChange = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PageControlChange(TObject *Sender)
{
	switch(PageControl->ActivePageIndex)
    {
     	case 1:
        {
        	DM->ServiceType=stChatting;
         	break;
        }
     	case 2:
        {
			DM->ServiceType=stWatching;
         	break;
        }
     	case 3:
        {
			DM->ServiceType=stFileManager;
         	break;
        }
     	case 4:
        {
			DM->ServiceType=stCommandPrompt;
         	break;
        }
     	case 5:
        {
			DM->ServiceType=stMaintenance;
         	break;
        }
     	case 6:
        {
			DM->ServiceType=stMessages;
         	break;
        }
     	case 7:
        {
			DM->ServiceType=stConference;
         	break;
        }
     	case 8:
        {
			DM->ServiceType=stAutoWatch;
         	break;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ACMWaveInData(Pointer data, int size)
{
	if(FormMain->ToolButtonSound->Marked)
    {
		DMClient->SendBuffer(data,size,"SOUND","");
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabControlCommandPromptChange(TObject *Sender)
{
	DMClient->SendCommandPromptCommand("dir");
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabControlCommandPromptChanging(TObject *Sender,
      bool &AllowChange)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabControlMessagesChange(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabControlMessagesChanging(TObject *Sender,
      bool &AllowChange)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabControlConferenceChange(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabControlConferenceChanging(TObject *Sender,
      bool &AllowChange)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caNone;	
    DM->TrayIcon->Minimize();
}
//---------------------------------------------------------------------------

