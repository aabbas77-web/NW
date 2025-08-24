//---------------------------------------------------------------------------
#include <vcl.h>
#include <FileCtrl.hpp>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "nw_CopyThread.h"
#include "ClientProcess.h"    
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall nw_CopyThread::nw_CopyThread(bool CreateSuspended,bool bFromRemoteToLocal)
	: TThread(CreateSuspended)
{
	m_bFromRemoteToLocal = bFromRemoteToLocal;
    if(m_bFromRemoteToLocal)
    {
	    m_pFormCopyDialog=new TFormCopyDialog(Application);
    	m_pFormCopyDialog->Show();
	    m_pFormCopyDialog->Animate->Active=true;
    }
    else
    {
	    m_pFormCopyDialog=NULL;
    }

    m_nFilesCount=0;
    m_nDirsCount=0;
    m_nFilesSize=0;
}
//---------------------------------------------------------------------------
void __fastcall nw_CopyThread::DoFreeMemory(TObject *Sender)
{
    if(m_pFormCopyDialog)	delete m_pFormCopyDialog;
    m_pFormCopyDialog=NULL;
}
//---------------------------------------------------------------------------
void __fastcall nw_CopyThread::UpdateStatus()
{
	m_pFormCopyDialog->LabelFileName->Caption=" "+MinimizeName(m_strSourceFileName,m_pFormCopyDialog->LabelFileName->Canvas,m_pFormCopyDialog->LabelFileName->Width-10)+" ";
    m_pFormCopyDialog->LabelResult->Caption=" "+FormatFloat("Folders: 0",m_nDirsCount)+" , "+FormatFloat("Files: 0",m_nFilesCount)+" , "+FormatFloat("Total Size: 0.0 KB",m_nFilesSize/1024.0)+" ";
}
//---------------------------------------------------------------------------
void __fastcall nw_CopyThread::Execute()
{
    TSearchRec  Sr;
    m_nError=FindFirst("*.*",faAnyFile,Sr) ;
    while(!m_nError)
    {
    	if(DMClient->m_bSending)	continue;
        if(DMClient->m_bError)	continue;
    	if(m_bFromRemoteToLocal && (!m_pFormCopyDialog->Visible))	break;
        Application->ProcessMessages();
        if(Sr.Name[1] != '.')
        {
            if(!(Sr.Attr & faDirectory))
            {
				// Update Status
                m_nFilesSize+=Sr.Size;
                m_nFilesCount++;
                if(m_bFromRemoteToLocal)
                {
	                Synchronize(UpdateStatus);
                }

	            m_strCurrDirName=IncludeTrailingBackslash(m_strDestDirName+ExtractRelativePath(m_strSourceDirName,ExpandFileName(GetCurrentDir())));

                m_strSourceFileName=ExpandFileName(Sr.Name);
                m_strDestFileName=m_strCurrDirName+Sr.Name;

                // Process Files
                if(m_bFromRemoteToLocal)
	                DMClient->SendFileFromRemoteToLocal(m_strTo,m_strSourceFileName,m_strDestFileName);
                else
	                DMClient->SendFileFromLocalToRemote(m_strTo,m_strSourceFileName,m_strDestFileName);
            }
            else
            {
//	            m_strCurrDirName=IncludeTrailingBackslash(m_strDestDirName+ExtractRelativePath(m_strSourceDirName,ExpandFileName(Sr.Name)));
	            m_nDirsCount++;
                if(m_bFromRemoteToLocal)
                {
		            Synchronize(UpdateStatus);
                }

	            SetCurrentDir(Sr.Name);
	            Execute();
    	        SetCurrentDir("..") ;
            }
        }

        m_nError=FindNext(Sr) ;
    }
}
//---------------------------------------------------------------------------
