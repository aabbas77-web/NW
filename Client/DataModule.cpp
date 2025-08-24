//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DataModule.h"
#include "Main.h"
#include "Input.h"
#include "nw_Messages.h"
#include "Group.h"
#include "ClientProcess.h"
#include "FullScreen.h"
#include "About.h"
#include "Watch.h"
#include "Options.h"
#include "nw_Messages.h"
#include "nw_Message.h"
#include "nw_SelectClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TDM *DM;
//---------------------------------------------------------------------------
__fastcall TDM::TDM(TComponent* Owner)
	: TDataModule(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TDM::DataModuleCreate(TObject *Sender)
{
	strAppPath=ExtractFilePath(Application->ExeName);
	ServiceType=stChatting;
    m_bSound = false;

    m_pBitmap = new Graphics::TBitmap();
    m_pBitmap->Width = 1024;
    m_pBitmap->Height = 768;
    m_pBitmap->PixelFormat = pf24bit;

    m_nCurrentAutoWatchClientIndex = 0;
    m_nCurrentAutoWatchIndex  = 0;

    m_pJPEG = new TJPEGImage();
}
//---------------------------------------------------------------------------

void __fastcall TDM::DataModuleDestroy(TObject *Sender)
{
	if(m_pBitmap)
    {
     	delete m_pBitmap;
        m_pBitmap = NULL;
    }
    if(m_pJPEG)
    {
     	delete m_pJPEG;
        m_pJPEG = NULL;
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::ApplicationEventsHint(TObject *Sender)
{
	FormMain->PanelStatus->Caption = Application->Hint;	
}
//---------------------------------------------------------------------------

void __fastcall TDM::ClearTabs()
{
	TTabControl *pTabControl;
    switch(ServiceType)
    {
     	case stChatting:
        {
			pTabControl=FormMain->TabControlChat;
    		pTabControl->Tabs->Clear();
         	break;
        }
     	case stWatching:
        {
			pTabControl=FormMain->TabControlMonitoring;
    		pTabControl->Tabs->Clear();
        	break;
        }
     	case stFileManager:
        {
			pTabControl=FormMain->TabControlFileManager;
    		pTabControl->Tabs->Clear();
         	break;
        }
     	case stCommandPrompt:
        {
			pTabControl=FormMain->TabControlCommandPrompt;
    		pTabControl->Tabs->Clear();
         	break;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::TreeViewGroupsClick(TObject *Sender)
{
/* WWPTC 04.03.2004
    bool bValidService=false;
	TGroupBox *pGroupBox;
	TTabControl *pTabControl;
    int nActivePageIndex = 0;

    switch(ServiceType)
    {
     	case stChatting:
        {
			pGroupBox=FormMain->GroupBoxChat;
			pTabControl=FormMain->TabControlChat;
            nActivePageIndex = 1;
         	break;
        }
     	case stWatching:
        {
			pGroupBox=FormMain->GroupBoxMonitoring;
			pTabControl=FormMain->TabControlMonitoring;
            nActivePageIndex = 2;
         	break;
        }
     	case stFileManager:
        {
			pGroupBox=FormMain->GroupBoxFileManager;
			pTabControl=FormMain->TabControlFileManager;
            nActivePageIndex = 3;
         	break;
        }
     	case stCommandPrompt:
        {
			pGroupBox=FormMain->GroupBoxCommandPrompt;
			pTabControl=FormMain->TabControlCommandPrompt;
            nActivePageIndex = 4;
         	break;
        }
    }

    pTabControl->Tabs->Clear();
    if(nActivePageIndex == 1)
    {
	    pTabControl->Tabs->Add(FormMessages->ValueListEditor->Values["c_strAll"]);
    }

	if(FormMain->TreeViewGroups->SelectionCount < 1)
    {
	    pGroupBox->Enabled=false;
    	FormMain->PageControl->ActivePageIndex = nActivePageIndex;
    }

	if(FormMain->TreeViewGroups->SelectionCount == 1)
    {
		TTreeNode *pNode=FormMain->TreeViewGroups->Selected;
		if(pNode->Level == 0)
	    {
        	pGroupBox->Caption=pNode->Text;

            AnsiString strComputerName;
        	for(int i=0;i<pNode->Count;i++)
            {
	        	strComputerName = pNode->Item[i]->Text;
                if(pTabControl->Tabs->IndexOf(strComputerName) == -1)
                {
                	pTabControl->Tabs->Add(strComputerName);
                }
                bValidService=true;
            }
	    }
	    else
	    {
        	pGroupBox->Caption=pNode->Parent->Text;
            if(pTabControl->Tabs->IndexOf(pNode->Text) == -1)
            {
            	pTabControl->Tabs->Add(pNode->Text);
            }
            bValidService=true;
	    }
    }
    else
	if(FormMain->TreeViewGroups->SelectionCount > 1)
    {
		pGroupBox->Caption=FormMessages->ValueListEditor->Values["c_strSelection"];
		for(UINT i=0;i<FormMain->TreeViewGroups->SelectionCount;i++)
	    {
	    	if(FormMain->TreeViewGroups->Selections[i]->Level != 0)
            {
            	if(pTabControl->Tabs->IndexOf(FormMain->TreeViewGroups->Selections[i]->Text) == -1)
                {
			        pTabControl->Tabs->Add(FormMain->TreeViewGroups->Selections[i]->Text);
                }
                bValidService=true;
            }
	    }
    }
    pGroupBox->Enabled=bValidService;
    FormMain->PageControl->ActivePageIndex = nActivePageIndex;
*/
}
//---------------------------------------------------------------------------

void __fastcall TDM::FinishPreviousService()
{
    switch(ServiceType)
    {
     	case stChatting:
        {
         	break;
        }
     	case stWatching:
        {
			DMClient->SendWatchCommand("",false,FormMain->CSpinEditWatchingDelay->Value,FormMain->CSpinEditBlockSize->Value);
        	break;
        }
     	case stFileManager:
        {
         	break;
        }
     	case stMaintenance:
        {
			DMClient->SendMaintenanceCommand(false);
         	break;
        }
     	case stCommandPrompt:
        {
         	break;
        }
     	case stConference:
        {
         	break;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::AConnectExecute(TObject *Sender)
{
	DMClient->Connect();
}
//---------------------------------------------------------------------------

void __fastcall TDM::AConnectionExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TDM::ABackExecute(TObject *Sender)
{
//	if(!FormMain->ListView1->IsEditing())
    {
    	DMClient->SendFoldersCommand("BACK",0);
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::ARefreshExecute(TObject *Sender)
{
//	if(!FormMain->ListView1->IsEditing())
    {
    	DMClient->SendFoldersCommand("REFRESH",0);
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::ApplicationEventsShortCut(TWMKey &Msg, bool &Handled)
{
    Handled = false;
	switch(Msg.CharCode)
    {
     	case VK_F5:
        {
        	if(FormFullScreen->Visible || (FormMain->PageControl->ActivePageIndex == 1))
            {
				DMClient->SendWatchCommand("",true,FormMain->CSpinEditWatchingDelay->Value,FormMain->CSpinEditBlockSize->Value);
	            Handled = true;
            }
         	break;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::AExitExecute(TObject *Sender)
{
	Application->Terminate();	
}
//---------------------------------------------------------------------------

void __fastcall TDM::AHelpExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TDM::AAboutExecute(TObject *Sender)
{
	FormAbout->ShowModal();	
}
//---------------------------------------------------------------------------

void __fastcall TDM::AWatchingReportExecute(TObject *Sender)
{
//	FormWatch->Image->Picture->Assign(FormFullScreen->Image->Picture);
	FormWatch->Image->Picture->Assign(m_pBitmap);
/*
	TRect Source,Dest;
    Source = Rect(0,0,FormFullScreen->Width,FormFullScreen->Height);
    Dest = Source;
	FormWatch->Image->Canvas->CopyRect(Dest,FormFullScreen->Canvas,Source);
*/
	FormWatch->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TDM::ARestoreExecute(TObject *Sender)
{
	TrayIcon->Restore();	
}
//---------------------------------------------------------------------------

void __fastcall TDM::AStartWatchingExecute(TObject *Sender)
{
	DMClient->SendWatchCommand("",true,FormMain->CSpinEditWatchingDelay->Value,FormMain->CSpinEditBlockSize->Value);
    FormMain->ToolButtonStartWatching->Down = true;
    FormMain->ToolButtonStopWatching->Down = false;
}
//---------------------------------------------------------------------------

void __fastcall TDM::AStopWatchingExecute(TObject *Sender)
{
	DMClient->SendWatchCommand("",false,FormMain->CSpinEditWatchingDelay->Value,FormMain->CSpinEditBlockSize->Value);
    FormMain->ToolButtonStartWatching->Down = false;
    FormMain->ToolButtonStopWatching->Down = true;
}
//---------------------------------------------------------------------------

void __fastcall TDM::AContentsExecute(TObject *Sender)
{
	Application->HelpFile = ExtractFilePath(Application->ExeName)+"\\NW.HLP";
    Application->HelpCommand(HELP_CONTENTS,0);
}
//---------------------------------------------------------------------------

void __fastcall TDM::AOptionsExecute(TObject *Sender)
{
	if(FormOptions->ShowModal() != mrOk)	return;	
}
//---------------------------------------------------------------------------

void __fastcall TDM::ASoundExecute(TObject *Sender)
{
	if(m_bSound)	return;
    m_bSound = true;
	DMClient->SendSoundCommand(true);
}
//---------------------------------------------------------------------------

void __fastcall TDM::AStopSoundExecute(TObject *Sender)
{
	if(!m_bSound)	return;
    m_bSound = false;
	DMClient->SendSoundCommand(false);
}
//---------------------------------------------------------------------------

void __fastcall TDM::ACopyExecute(TObject *Sender)
{
/*
	if(FormMain->pShellListView->Selected)
    {
    	AnsiString strPath = FormMain->ShellListView1->Folders[FormMain->pShellListView->Selected->Index]->PathName();
        DMClient->CopyFolders(strPath);
    }
*/    
}
//---------------------------------------------------------------------------

void __fastcall TDM::APasteExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TDM::ASendMessageExecute(TObject *Sender)
{
	if(FormMessage->ShowModal() != mrOk)	return;
	DMClient->SendMessage();
}
//---------------------------------------------------------------------------

void __fastcall TDM::ASelectChatingClientsExecute(TObject *Sender)
{
	FormSelectClient->ListBoxClients->Clear();
    for(int i=0;i<FormMain->TabControlChat->Tabs->Count;i++)
    {
    	if(!SameText(FormMain->TabControlChat->Tabs->Strings[i],FormMessages->ValueListEditor->Values["c_strAll"]))
        {
			FormSelectClient->ListBoxClients->Items->Add(FormMain->TabControlChat->Tabs->Strings[i]);
        }
    }

    FormSelectClient->m_bAllowNoneClients = true;
    FormSelectClient->m_bSelectMaximumOne = false;
	if(FormSelectClient->ShowModal() != mrOk)	return;

	FormMain->TabControlChat->Tabs->Clear();
    if(FormSelectClient->ListBoxClients->Items->Count > 0)
    {
	    FormMain->TabControlChat->Tabs->Add(FormMessages->ValueListEditor->Values["c_strAll"]);
    }
    for(int i=0;i<FormSelectClient->ListBoxClients->Items->Count;i++)
    {
		FormMain->TabControlChat->Tabs->Add(FormSelectClient->ListBoxClients->Items->Strings[i]);
    }

    if(FormMain->TabControlChat->Tabs->Count > 0)
    {
	    FormMain->MemoSend->ReadOnly = false;
    	FormMain->MemoSend->Color = clWindow;

		ASound->Enabled = true;
		AStopSound->Enabled = true;
    }
    else
    {
	    FormMain->MemoSend->ReadOnly = true;
    	FormMain->MemoSend->Color = clBtnFace;

		ASound->Enabled = false;
		AStopSound->Enabled = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::ASelectWatchingClientsExecute(TObject *Sender)
{
	AStopWatchingExecute(NULL);

	FormSelectClient->ListBoxClients->Clear();
    for(int i=0;i<FormMain->TabControlMonitoring->Tabs->Count;i++)
    {
    	if(!SameText(FormMain->TabControlMonitoring->Tabs->Strings[i],FormMessages->ValueListEditor->Values["c_strAll"]))
        {
			FormSelectClient->ListBoxClients->Items->Add(FormMain->TabControlMonitoring->Tabs->Strings[i]);
        }
    }

    FormSelectClient->m_bAllowNoneClients = true;
    FormSelectClient->m_bSelectMaximumOne = false;
	if(FormSelectClient->ShowModal() != mrOk)	return;

	FormMain->TabControlMonitoring->Tabs->Clear();
    for(int i=0;i<FormSelectClient->ListBoxClients->Items->Count;i++)
    {
		FormMain->TabControlMonitoring->Tabs->Add(FormSelectClient->ListBoxClients->Items->Strings[i]);
    }

    if(FormMain->TabControlMonitoring->Tabs->Count > 0)
    {
		AStartWatching->Enabled = true;
		AStopWatching->Enabled = true;
        AWatchingReport->Enabled = true;
        FormMain->CSpinEditWatchingDelay->Enabled = true;
        FormMain->CSpinEditBlockSize->Enabled = true;

		AStartWatchingExecute(NULL);
    }
    else
    {
		AStartWatching->Enabled = false;
		AStopWatching->Enabled = false;
        AWatchingReport->Enabled = false;
        FormMain->CSpinEditWatchingDelay->Enabled = false;
        FormMain->CSpinEditBlockSize->Enabled = false;

//        FormMain->Image->Picture->Bitmap->Width = 0;
//        FormMain->Image->Picture->Bitmap->Height = 0;

//        FormMain->Image->Width = 0;
//        FormMain->Image->Height = 0;
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::ASelectMaintenanceClientsExecute(TObject *Sender)
{
	FormSelectClient->ListBoxClients->Clear();
    for(int i=0;i<FormMain->TabControlMaintenance->Tabs->Count;i++)
    {
    	if(!SameText(FormMain->TabControlMaintenance->Tabs->Strings[i],FormMessages->ValueListEditor->Values["c_strAll"]))
        {
			FormSelectClient->ListBoxClients->Items->Add(FormMain->TabControlMaintenance->Tabs->Strings[i]);
        }
    }

    FormSelectClient->m_bAllowNoneClients = true;
    FormSelectClient->m_bSelectMaximumOne = true;
	if(FormSelectClient->ShowModal() != mrOk)	return;

	FormMain->TabControlMaintenance->Tabs->Clear();
    for(int i=0;i<FormSelectClient->ListBoxClients->Items->Count;i++)
    {
		FormMain->TabControlMaintenance->Tabs->Add(FormSelectClient->ListBoxClients->Items->Strings[i]);
        break;
    }

    if(FormMain->TabControlMaintenance->Tabs->Count > 0)
    {
		AStartMaintenance->Enabled = true;
		AStopMaintenance->Enabled = true;
    }
    else
    {
		AStartMaintenance->Enabled = false;
		AStopMaintenance->Enabled = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::AStartMaintenanceExecute(TObject *Sender)
{
	FormMain->ToolButtonStartMaintenance->Down = true;
	FormMain->ToolButtonStopMaintenance->Down = false;

    static nPrevWidth,nPrevHeight,nPrevColors;
    HDC hdc = GetWindowDC(GetDesktopWindow());
    nPrevWidth = GetDeviceCaps(hdc, HORZRES);
    nPrevHeight = GetDeviceCaps(hdc, VERTRES);
    nPrevColors = GetDeviceCaps(hdc, BITSPIXEL);
    gChangeResolution(800, 600, 16);

	DMClient->SendMaintenanceCommand(true);

	FormFullScreen->ShowModal();

    AStopMaintenanceExecute(NULL);
    gChangeResolution(nPrevWidth, nPrevHeight, nPrevColors);
}
//---------------------------------------------------------------------------

void __fastcall TDM::AStopMaintenanceExecute(TObject *Sender)
{
	FormMain->ToolButtonStartMaintenance->Down = false;
	FormMain->ToolButtonStopMaintenance->Down = true;

	DMClient->SendMaintenanceCommand(false);
}
//---------------------------------------------------------------------------

void __fastcall TDM::ASelectFileManagerClientsExecute(TObject *Sender)
{
	FormSelectClient->ListBoxClients->Clear();
    for(int i=0;i<FormMain->TabControlFileManager->Tabs->Count;i++)
    {
    	if(!SameText(FormMain->TabControlFileManager->Tabs->Strings[i],FormMessages->ValueListEditor->Values["c_strAll"]))
        {
			FormSelectClient->ListBoxClients->Items->Add(FormMain->TabControlFileManager->Tabs->Strings[i]);
        }
    }

    FormSelectClient->m_bAllowNoneClients = true;
    FormSelectClient->m_bSelectMaximumOne = false;
	if(FormSelectClient->ShowModal() != mrOk)	return;

	FormMain->TabControlFileManager->Tabs->Clear();
    for(int i=0;i<FormSelectClient->ListBoxClients->Items->Count;i++)
    {
		FormMain->TabControlFileManager->Tabs->Add(FormSelectClient->ListBoxClients->Items->Strings[i]);
    }

    if(FormMain->TabControlFileManager->Tabs->Count > 0)
    {
        FormMain->ListView1->Color = clWindow;
        FormMain->ListView1->Enabled = true;
        DMClient->SendFoldersCommand("DESKTOP",0);
    }
    else
    {
        FormMain->ListView1->Color = TColor(0x00E6E6E6);
        FormMain->ListView1->Clear();
        FormMain->PanelPath->Caption = "";
        FormMain->ListView1->Enabled = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::ASelectCommandPromptClientsExecute(TObject *Sender)
{
	FormSelectClient->ListBoxClients->Clear();
    for(int i=0;i<FormMain->TabControlCommandPrompt->Tabs->Count;i++)
    {
    	if(!SameText(FormMain->TabControlCommandPrompt->Tabs->Strings[i],FormMessages->ValueListEditor->Values["c_strAll"]))
        {
			FormSelectClient->ListBoxClients->Items->Add(FormMain->TabControlCommandPrompt->Tabs->Strings[i]);
        }
    }

    FormSelectClient->m_bAllowNoneClients = true;
    FormSelectClient->m_bSelectMaximumOne = false;
	if(FormSelectClient->ShowModal() != mrOk)	return;

	FormMain->TabControlCommandPrompt->Tabs->Clear();
    for(int i=0;i<FormSelectClient->ListBoxClients->Items->Count;i++)
    {
		FormMain->TabControlCommandPrompt->Tabs->Add(FormSelectClient->ListBoxClients->Items->Strings[i]);
    }

    if(FormMain->TabControlCommandPrompt->Tabs->Count > 0)
    {
        FormMain->MemoCommandPrompt->Color = TColor(0x00FFF0E1);
	    FormMain->MemoCommandPromptResult->Enabled = true;
        FormMain->MemoCommandPrompt->Enabled = true;
		DMClient->SendCommandPromptCommand("dir");
    }
    else
    {
        FormMain->MemoCommandPrompt->Color = clBtnFace;
        FormMain->MemoCommandPromptResult->Clear();
	    FormMain->MemoCommandPromptResult->Enabled = false;
        FormMain->MemoCommandPrompt->Enabled = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::ASelectMessagesClientsExecute(TObject *Sender)
{
	FormSelectClient->ListBoxClients->Clear();
    for(int i=0;i<FormMain->TabControlMessages->Tabs->Count;i++)
    {
    	if(!SameText(FormMain->TabControlMessages->Tabs->Strings[i],FormMessages->ValueListEditor->Values["c_strAll"]))
        {
			FormSelectClient->ListBoxClients->Items->Add(FormMain->TabControlMessages->Tabs->Strings[i]);
        }
    }

    FormSelectClient->m_bAllowNoneClients = true;
    FormSelectClient->m_bSelectMaximumOne = false;
	if(FormSelectClient->ShowModal() != mrOk)	return;

	FormMain->TabControlMessages->Tabs->Clear();
    if(FormSelectClient->ListBoxClients->Items->Count > 0)
    {
	    FormMain->TabControlMessages->Tabs->Add(FormMessages->ValueListEditor->Values["c_strAll"]);
    }
    for(int i=0;i<FormSelectClient->ListBoxClients->Items->Count;i++)
    {
		FormMain->TabControlMessages->Tabs->Add(FormSelectClient->ListBoxClients->Items->Strings[i]);
    }

    if(FormMain->TabControlMessages->Tabs->Count > 0)
    {
		ASendMessage->Enabled = true;
        ASendDocument->Enabled = true;
    }
    else
    {
		ASendMessage->Enabled = false;
        ASendDocument->Enabled = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::ASendDocumentExecute(TObject *Sender)
{
	if(OpenDialogDocument->Execute())
    {
		DMClient->SendDocument(OpenDialogDocument->FileName);
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::ASelectConferenceClientsExecute(TObject *Sender)
{
	FormSelectClient->ListBoxClients->Clear();
    for(int i=0;i<FormMain->TabControlConference->Tabs->Count;i++)
    {
    	if(!SameText(FormMain->TabControlConference->Tabs->Strings[i],FormMessages->ValueListEditor->Values["c_strAll"]))
        {
			FormSelectClient->ListBoxClients->Items->Add(FormMain->TabControlConference->Tabs->Strings[i]);
        }
    }

    FormSelectClient->m_bAllowNoneClients = true;
    FormSelectClient->m_bSelectMaximumOne = false;
	if(FormSelectClient->ShowModal() != mrOk)	return;

	FormMain->TabControlConference->Tabs->Clear();
    if(FormSelectClient->ListBoxClients->Items->Count > 0)
    {
	    FormMain->TabControlConference->Tabs->Add(FormMessages->ValueListEditor->Values["c_strAll"]);
    }
    for(int i=0;i<FormSelectClient->ListBoxClients->Items->Count;i++)
    {
		FormMain->TabControlConference->Tabs->Add(FormSelectClient->ListBoxClients->Items->Strings[i]);
    }

    if(FormMain->TabControlConference->Tabs->Count > 0)
    {
		AStartConference->Enabled = true;
		AStopConference->Enabled = true;
    }
    else
    {
		AStartConference->Enabled = false;
		AStopConference->Enabled = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::AStartConferenceExecute(TObject *Sender)
{
	DMClient->SendConferenceCommand(true);

    g_bIsFirstScan = true;
    g_nCurrIndex = 0;

    int nFrameW,nFrameH;
					//    nFrameH=24;
					//    nFrameH=32;
					//    nFrameH=48;
					//    nFrameH=64;
//					nFrameH=96;
				    nFrameH=128;
//	nFrameH=192;
//					    nFrameH=256;
//	nFrameH=384;
//					    nFrameH=512;
					//    nFrameW=nFrameH*Ratio;
	nFrameW=nFrameH;
    m_pCaptureThread->SetCaptureSettings(nFrameW+nFrameH,nFrameW,nFrameH);
    m_pCaptureThread->m_bConference = true;
    m_pCaptureThread->m_strTo="";
    m_pCaptureThread->m_pTimer->Interval = 40;
    m_pCaptureThread->m_pTimer->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TDM::AStopConferenceExecute(TObject *Sender)
{
	m_pCaptureThread->m_pTimer->Enabled = false;
	DMClient->SendConferenceCommand(false);
}
//---------------------------------------------------------------------------

void __fastcall TDM::AServicesExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TDM::AChatingExecute(TObject *Sender)
{
	FormMain->PageControl->ActivePageIndex = 1;
}
//---------------------------------------------------------------------------

void __fastcall TDM::AWatchingExecute(TObject *Sender)
{
	FormMain->PageControl->ActivePageIndex = 2;
}
//---------------------------------------------------------------------------

void __fastcall TDM::AFileManagerExecute(TObject *Sender)
{
	FormMain->PageControl->ActivePageIndex = 3;
}
//---------------------------------------------------------------------------

void __fastcall TDM::ACommandPromptExecute(TObject *Sender)
{
	FormMain->PageControl->ActivePageIndex = 4;
}
//---------------------------------------------------------------------------

void __fastcall TDM::AMaintenanceExecute(TObject *Sender)
{
	FormMain->PageControl->ActivePageIndex = 5;
}
//---------------------------------------------------------------------------

void __fastcall TDM::AMessagesExecute(TObject *Sender)
{
	FormMain->PageControl->ActivePageIndex = 6;
}
//---------------------------------------------------------------------------

void __fastcall TDM::AConferenceExecute(TObject *Sender)
{
	FormMain->PageControl->ActivePageIndex = 7;
}
//---------------------------------------------------------------------------

void __fastcall TDM::ACloseExecute(TObject *Sender)
{
	FormMain->Close();	
}
//---------------------------------------------------------------------------

void __fastcall TDM::ADeleteExecute(TObject *Sender)
{
	if(!FormMain->ListView1->Selected)	return;
//	if(!FormMain->ListView1->IsEditing())
    {
		if(FormMain->TabControlFileManager->TabIndex < 0)	return;
	    AnsiString strTo = GetUserName(FormMain->TabControlFileManager->Tabs->Strings[FormMain->TabControlFileManager->TabIndex]);
    	AnsiString strPath = strTo +" > "+ IncludeTrailingBackslash(FormMain->PanelPath->Caption)+FormMain->ListView1->Selected->Caption;
		if(MessageDlg(FormMessages->ValueListEditor->Values["c_strAreYouSureYouWantToDeleteThisFile"]+"\n"+strPath,mtWarning,TMsgDlgButtons()<<mbYes<<mbNo,0) == IDYES)
        {
			DMClient->SendFoldersCommand("DELETE",FormMain->ListView1->Selected->Index);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::AOpenExecute(TObject *Sender)
{
	if(!FormMain->ListView1->Selected)	return;
	DMClient->SendFoldersCommand("OPEN",FormMain->ListView1->Selected->Index);
}
//---------------------------------------------------------------------------

void __fastcall TDM::TimerConnectionTimer(TObject *Sender)
{
	if(!DMClient->m_bConnected)
    {
		DMClient->AutoConnect();
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::AStartAutoWatchExecute(TObject *Sender)
{
	TimerAutoWatch->Interval = 60000*FormMain->TabControlAutoWatch->Tabs->Count;
	TimerAutoWatch->Enabled = true;	
    FormMain->ToolButtonStartAutoWatch->Down = true;
    FormMain->ToolButtonStopAutoWatch->Down = false;
    m_nCurrentAutoWatchClientIndex  = 0;
    m_nCurrentAutoWatchIndex  = 0;
    if(FormMain->CSpinEditAutoWatchBlockSize->Value <= 0)	return;
    m_nFrameCount = (1024.0/FormMain->CSpinEditAutoWatchBlockSize->Value+1)*(768.0/FormMain->CSpinEditAutoWatchBlockSize->Value+1);
    m_nCurrentFrameIndex = 0;
    TimerAutoWatchTimer(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TDM::AStopAutoWatchExecute(TObject *Sender)
{
	TimerAutoWatch->Enabled = false;	
    FormMain->ToolButtonStartAutoWatch->Down = false;
    FormMain->ToolButtonStopAutoWatch->Down = true;
    for(int i=0;i<FormMain->TabControlAutoWatch->Tabs->Count;i++)
    {
		DMClient->SendWatchCommand(FormMain->TabControlAutoWatch->Tabs->Strings[i],false,FormMain->CSpinEditAutoWatchDelay->Value,FormMain->CSpinEditAutoWatchBlockSize->Value);
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::AAutoWatchReportExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TDM::ASelectAutoWatchClientsExecute(TObject *Sender)
{
	AStopAutoWatchExecute(NULL);

	FormSelectClient->ListBoxClients->Clear();
    for(int i=0;i<FormMain->TabControlAutoWatch->Tabs->Count;i++)
    {
    	if(!SameText(FormMain->TabControlAutoWatch->Tabs->Strings[i],FormMessages->ValueListEditor->Values["c_strAll"]))
        {
			FormSelectClient->ListBoxClients->Items->Add(FormMain->TabControlAutoWatch->Tabs->Strings[i]);
        }
    }

    FormSelectClient->m_bAllowNoneClients = true;
    FormSelectClient->m_bSelectMaximumOne = false;
	if(FormSelectClient->ShowModal() != mrOk)	return;

	FormMain->TabControlAutoWatch->Tabs->Clear();
    for(int i=0;i<FormSelectClient->ListBoxClients->Items->Count;i++)
    {
		FormMain->TabControlAutoWatch->Tabs->Add(FormSelectClient->ListBoxClients->Items->Strings[i]);
    }

    if(FormMain->TabControlAutoWatch->Tabs->Count > 0)
    {
		AStartAutoWatch->Enabled = true;
		AStopAutoWatch->Enabled = true;
        AAutoWatchReport->Enabled = true;
        FormMain->CSpinEditAutoWatchDelay->Enabled = true;
        FormMain->CSpinEditAutoWatchBlockSize->Enabled = true;

		AStartAutoWatchExecute(NULL);
    }
    else
    {
		AStartAutoWatch->Enabled = false;
		AStopAutoWatch->Enabled = false;
        AAutoWatchReport->Enabled = false;
        FormMain->CSpinEditAutoWatchDelay->Enabled = false;
        FormMain->CSpinEditAutoWatchBlockSize->Enabled = false;

//        FormMain->Image->Picture->Bitmap->Width = 0;
//        FormMain->Image->Picture->Bitmap->Height = 0;

//        FormMain->Image->Width = 0;
//        FormMain->Image->Height = 0;
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::TimerAutoWatchTimer(TObject *Sender)
{
	if(m_nCurrentAutoWatchClientIndex < FormMain->TabControlAutoWatch->Tabs->Count)
    {
    	m_nCurrentFrameIndex = 0;
//        DMClient->SaveAutoFrame();
		DMClient->SendWatchCommand(FormMain->TabControlAutoWatch->Tabs->Strings[m_nCurrentAutoWatchClientIndex],true,FormMain->CSpinEditAutoWatchDelay->Value,FormMain->CSpinEditAutoWatchBlockSize->Value);
//	    m_nCurrentAutoWatchClientIndex++;
    }
    else
    {
//		m_nCurrentAutoWatchClientIndex = 0;
//    	m_nCurrentFrameIndex = 0;
//        DMClient->SaveAutoFrame();
//		DMClient->SendWatchCommand(FormMain->TabControlAutoWatch->Tabs->Strings[m_nCurrentAutoWatchClientIndex],true,FormMain->CSpinEditAutoWatchDelay->Value,FormMain->CSpinEditAutoWatchBlockSize->Value);
    }
}
//---------------------------------------------------------------------------

