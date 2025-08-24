//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DataModule.h"
#include "Main.h"
#include "nw_Input.h"
#include "nw_Messages.h"
#include "Group.h"
#include "ProtectionLib.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SingleInstance"
#pragma link "ApServer"
#pragma link "RBroker"
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

void __fastcall TDM::LoadGroups()
{
	TableGroups->Active = false;
	TableGroups->DatabaseName = strAppPath;
	TableGroups->Active = true;

	TableComputers->Active = false;
	TableComputers->DatabaseName = strAppPath;
	TableComputers->Active = true;

    // Initialize Connected Property
    TableGroups->First();
    if(TableGroups->Eof)
    {
     	ClearAllGroups();
    }

    while(!TableGroups->Eof)
    {
    	TableComputers->First();
        while(!TableComputers->Eof)
        {
        	TableComputers->Edit();
            TableComputers->FieldByName("Connected")->Value=false;
            TableComputers->Post();

            TableComputers->Next();
        }

        TableGroups->Next();
    }

    if(TableGroups->Locate("Group_Name",c_strWithoutGroup,TLocateOptions()<<loCaseInsensitive))
    {
		m_nWithoutGroupID = TableGroups->FieldByName("Group_ID")->Value;
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::ClearAllGroups()
{
    TableGroups->First();
    while(!TableGroups->Eof)
    {
        TableComputers->First();
	    while(!TableComputers->Eof)
	    {
	     	TableComputers->Delete();
	    }

     	TableGroups->Delete();
    }

    // Add Default Group
    TableGroups->Append();
	TableGroups->FieldByName("Group_Name")->Value=c_strWithoutGroup;
    TableGroups->Post();
}
//---------------------------------------------------------------------------

void __fastcall TDM::ReBuildTreeViewGroups()
{
    TTreeNode *pNode;
    TTreeNode *pPrevNode = FormMain->TreeViewGroups->Selected;
    AnsiString strGroupName;
    AnsiString strComputerName;
    int nUserID;
    AnsiString strLanguage;

    FormMain->TreeViewGroups->Items->Clear();

    TableGroups->First();
    while(!TableGroups->Eof)
    {
    	strGroupName=TableGroups->FieldByName("Group_Name")->Value;
	    pNode=FormMain->TreeViewGroups->Items->Add(NULL,strGroupName);
        pNode->ImageIndex = 0;

        TableComputers->First();
	    while(!TableComputers->Eof)
	    {
			if(TableComputers->FieldByName("Connected")->Value)
            {
		    	strComputerName=TableComputers->FieldByName("Computer_Name")->Value;
            	nUserID = FormMain->FUserData->FindUser(strComputerName);
                switch(FormMain->FUserData->GetLanguageID(nUserID))
                {
                 	case 0:
                    {
                    	strLanguage = "English";
                     	break;
                    }
                 	case 1:
                    {
                    	strLanguage = "Arabic";
                     	break;
                    }
                 	case 2:
                    {
                    	strLanguage = "Frensh";
                     	break;
                    }
                }
//                strComputerName += " <"+strLanguage+">";
			    FormMain->TreeViewGroups->Items->AddChild(pNode,strComputerName)->ImageIndex = 1;
            }

	     	TableComputers->Next();
	    }

     	TableGroups->Next();
    }
	AUpdateClientsExecute(NULL);
    FormMain->TreeViewGroups->Selected = pPrevNode;
}
//---------------------------------------------------------------------------
void __fastcall TDM::ANewGroupExecute(TObject *Sender)
{
	AnsiString strGroupName="";

    Formnw_Input->Caption=FormMessages->ValueListEditor->Values["c_strGroups"];
    Formnw_Input->Label->Caption=FormMessages->ValueListEditor->Values["c_strEnterGroupName"];
    Formnw_Input->Edit->Text=c_strWithoutGroup;
    if(Formnw_Input->ShowModal()==mrOk)
    {
    	strGroupName=Formnw_Input->Edit->Text;
    	if(!TableGroups->Locate("Group_Name",strGroupName,TLocateOptions()<<loCaseInsensitive))
        {
			TableGroups->Append();
			TableGroups->FieldByName("Group_Name")->Value=strGroupName;
            TableGroups->Post();

			ReBuildTreeViewGroups();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::DataModuleCreate(TObject *Sender)
{
	#ifdef _PROTECTED_
    pro_SoftIceCheck();
	pro_DebuggerCheck();
    pro_Scrambling();
    pro_Check();
    #endif

    #ifdef _DEMO_
    pro_SoftIceCheck();
	pro_DebuggerCheck();
    InitCheckExecutionCount();
    CheckExecutionCount();
    #endif

	strAppPath=ExtractFilePath(Application->ExeName);
    LoadGroups();
}
//---------------------------------------------------------------------------

void __fastcall TDM::ApplicationEventsHint(TObject *Sender)
{
	FormMain->StatusBar->Panels->Items[0]->Text=Application->Hint;	
}
//---------------------------------------------------------------------------

void __fastcall TDM::ARemoveGroupExecute(TObject *Sender)
{
    TTreeNode *pNode;
	pNode=FormMain->TreeViewGroups->Selected;
    if(!pNode)	return;
    AnsiString strGroupName=pNode->Text;
	if((pNode->Level==0) && (strGroupName != c_strWithoutGroup))
    {
		if(MessageDlg(FormMessages->ValueListEditor->Values["c_strRemoveGroupConfirm"]+"\n<"+strGroupName+">",mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
        {
	    	if(TableGroups->Locate("Group_Name",strGroupName,TLocateOptions()<<loCaseInsensitive))
	        {
		        TableComputers->First();
			    while(!TableComputers->Eof)
			    {
                	TableComputers->Edit();
                    TableComputers->FieldByName("Group_ID")->Value=m_nWithoutGroupID;
                	TableComputers->Post();

			     	TableComputers->Next();
			    }
                TableGroups->Delete();
				ReBuildTreeViewGroups();
	        }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::ARemoveAllGroupsExecute(TObject *Sender)
{
	if(MessageDlg(FormMessages->ValueListEditor->Values["c_strRemoveAllGroupsConfirm"],mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
    {
		ClearAllGroups();
        ReBuildTreeViewGroups();
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::AGroupsExecute(TObject *Sender)
{
	// Enable RemoveGroup Action
    if(FormMain->TreeViewGroups->Selected)
    {
		AnsiString strGroupName=FormMain->TreeViewGroups->Selected->Text;
     	DM->ARemoveGroup->Enabled=((FormMain->TreeViewGroups->Selected->Level == 0) && (strGroupName != c_strWithoutGroup));
    }
    else
	{
		DM->ARemoveGroup->Enabled=false;
    }

    // Enable RemoveAllGroups Action
    bool bEnableRemoveAllGroups=false;
    for(int i=0;i<FormMain->TreeViewGroups->Items->Count;i++)
    {
    	if(FormMain->TreeViewGroups->Items->operator [](i)->Level == 0)
        {
			if(FormMain->TreeViewGroups->Items->operator [](i)->Text != c_strWithoutGroup)
            {
            	bEnableRemoveAllGroups=true;
             	break;
            }
        }
    }
    ARemoveAllGroups->Enabled=bEnableRemoveAllGroups;
}
//---------------------------------------------------------------------------

void __fastcall TDM::PopupMenuGroupsPopup(TObject *Sender)
{
    AClient->Enabled=(FormMain->TreeViewGroups->Selected && (FormMain->TreeViewGroups->Selected->Level != 0));
}
//---------------------------------------------------------------------------

void __fastcall TDM::AJoinInGroupExecute(TObject *Sender)
{
	if(!FormMain->TreeViewGroups->Selected)	return;
	if(FormGroup->ShowModal() == mrOk)
    {
	    if(FormMain->TreeViewGroups->Selected->Parent->Text == FormGroup->DBLookupComboBox1->Text)	return;
    	AnsiString strGroupName=FormGroup->DBLookupComboBox1->Text;
        AnsiString strComputerName=FormMain->TreeViewGroups->Selected->Text;
    	if(TableGroups->Locate("Group_Name",strGroupName,TLocateOptions()<<loCaseInsensitive))
        {
        	if(!DM->TableComputers->Locate("Computer_Name",strComputerName,TLocateOptions()<<loCaseInsensitive))
            {
				TableComputers->Append();
				TableComputers->FieldByName("Computer_Name")->Value=strComputerName;
				TableComputers->FieldByName("Connected")->Value=true;
	            TableComputers->Post();
            }
            else
            {
				TableComputers->Edit();
				TableComputers->FieldByName("Connected")->Value=true;
	            TableComputers->Post();
            }
            ReBuildTreeViewGroups();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::AMoveToGroupExecute(TObject *Sender)
{
	if(!FormMain->TreeViewGroups->Selected)	return;
	if(FormGroup->ShowModal() == mrOk)
    {
	    if(FormMain->TreeViewGroups->Selected->Parent->Text == FormGroup->DBLookupComboBox1->Text)	return;
    	AnsiString strNewGroupName=FormGroup->DBLookupComboBox1->Text;
    	AnsiString strGroupName=FormMain->TreeViewGroups->Selected->Parent->Text;
        AnsiString strComputerName=FormMain->TreeViewGroups->Selected->Text;
        int nGroup_ID;
    	if(TableGroups->Locate("Group_Name",strNewGroupName,TLocateOptions()<<loCaseInsensitive))
        {
	    	nGroup_ID = TableGroups->FieldByName("Group_ID")->Value;
            if(!TableComputers->Locate("Computer_Name",strComputerName,TLocateOptions()<<loCaseInsensitive))
            {
	    		if(TableGroups->Locate("Group_Name",strGroupName,TLocateOptions()<<loCaseInsensitive))
	    	    {
	        		if(TableComputers->Locate("Computer_Name",strComputerName,TLocateOptions()<<loCaseInsensitive))
	            	{
						TableComputers->Edit();
						TableComputers->FieldByName("Group_ID")->Value=nGroup_ID;
			            TableComputers->Post();
		            }
                }
            }
            else
            {
            	TableComputers->Edit();
            	TableComputers->FieldByName("Connected")->Value=true;
                TableComputers->Post();

	    		if(TableGroups->Locate("Group_Name",strGroupName,TLocateOptions()<<loCaseInsensitive))
	    	    {
	        		if(TableComputers->Locate("Computer_Name",strComputerName,TLocateOptions()<<loCaseInsensitive))
	            	{
						TableComputers->Delete();
		            }
                }
            }
            ReBuildTreeViewGroups();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::AClientExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TDM::AClearAllExecute(TObject *Sender)
{
    FormMain->DisplayMemo->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TDM::ANetworkExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TDM::AUpdateClientsExecute(TObject *Sender)
{
	FormMain->UpdateConnectedClients();
}
//---------------------------------------------------------------------------

void __fastcall TDM::AppServer1ClientClosed(TObject *Sender,
      TClientWSocket *CliWSocket)
{
    int nClientID = FormMain->FUserData->FindClient(CliWSocket);
    AnsiString strUserName = FormMain->FUserData->GetName(nClientID);
    FormMain->DisConnectUserFromTreeView(strUserName);

    FormMain->FUserData->RemoveClient(CliWSocket);
    FormMain->StatusBar->Panels->Items[0]->Text = FormMessages->ValueListEditor->Values["c_strClients"]+FormatFloat(" 0",AppServer1->ClientCount - 1);

    FormMain->UpdateConnectedClients();
}
//---------------------------------------------------------------------------

void __fastcall TDM::AppServer1ClientCommand(TObject *Sender,
      TClientWSocket *CliWSocket, PChar CmdBuf, int CmdLen)
{
//    FormMain->DisplayMemo->Lines->Add(CmdBuf);
}
//---------------------------------------------------------------------------

void __fastcall TDM::AppServer1ClientConnected(TObject *Sender,
      TClientWSocket *CliWSocket)
{
    FormMain->StatusBar->Panels->Items[0]->Text = FormMessages->ValueListEditor->Values["c_strClients"]+FormatFloat(" 0",AppServer1->ClientCount);
}
//---------------------------------------------------------------------------

void __fastcall TDM::AppServer1Display(TObject *Sender, AnsiString Msg)
{
	FormMain->DisplayMemo->Lines->Add(Msg);
}
//---------------------------------------------------------------------------

void __fastcall TDM::AExitExecute(TObject *Sender)
{
	Application->Terminate();	
}
//---------------------------------------------------------------------------

void __fastcall TDM::TimerPro1Timer(TObject *Sender)
{
	#ifdef _PROTECTED_
    pro_SoftIceCheck();
	pro_DebuggerCheck();
    pro_Scrambling();
    pro_Check();
    #endif

    #ifdef _DEMO_
    CheckExecutionCount();
    pro_SoftIceCheck();
	pro_DebuggerCheck();
    #endif
}
//---------------------------------------------------------------------------

void __fastcall TDM::TimerPro2Timer(TObject *Sender)
{
	#ifdef _PROTECTED_
    pro_SoftIceCheck();
	pro_DebuggerCheck();
    pro_Check();
    pro_Scrambling();
    #endif

    #ifdef _DEMO_
    pro_SoftIceCheck();
    CheckExecutionCount();
	pro_DebuggerCheck();
    #endif
}
//---------------------------------------------------------------------------

void __fastcall TDM::TimerPro3Timer(TObject *Sender)
{
	#ifdef _PROTECTED_
	pro_DebuggerCheck();
    pro_SoftIceCheck();
    pro_Scrambling();
    pro_Check();
    #endif

    #ifdef _DEMO_
    pro_SoftIceCheck();
	pro_DebuggerCheck();
    CheckExecutionCount();
    #endif
}
//---------------------------------------------------------------------------

void __fastcall TDM::ApplicationEventsIdle(TObject *Sender, bool &Done)
{
	#ifdef _PROTECTED_
    pro_SoftIceCheck();
    pro_Check();
	pro_DebuggerCheck();
    pro_Scrambling();
    #endif

    #ifdef _DEMO_
    CheckExecutionCount();
    pro_SoftIceCheck();
	pro_DebuggerCheck();
    #endif

    Done = true;
}
//---------------------------------------------------------------------------

void __fastcall TDM::ApplicationEventsActivate(TObject *Sender)
{
	#ifdef _PROTECTED_
    pro_SoftIceCheck();
    pro_Check();
	pro_DebuggerCheck();
    pro_Scrambling();
    #endif

    #ifdef _DEMO_
    pro_SoftIceCheck();
	pro_DebuggerCheck();
    CheckExecutionCount();
    #endif
}
//---------------------------------------------------------------------------

void __fastcall TDM::ApplicationEventsDeactivate(TObject *Sender)
{
	#ifdef _PROTECTED_
    pro_SoftIceCheck();
    pro_Check();
	pro_DebuggerCheck();
    pro_Scrambling();
    #endif

    #ifdef _DEMO_
    CheckExecutionCount();
    pro_SoftIceCheck();
	pro_DebuggerCheck();
    #endif
}
//---------------------------------------------------------------------------

void __fastcall TDM::ARestoreExecute(TObject *Sender)
{
	FormMain->TrayIcon->Restore();	
}
//---------------------------------------------------------------------------

void __fastcall TDM::ACloseExecute(TObject *Sender)
{
	FormMain->Close();	
}
//---------------------------------------------------------------------------

