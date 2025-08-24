//---------------------------------------------------------------------------
#include <vcl.h>
#include <algorithm>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "nw_CaptureThread.h"
#include "Main.h"
#include "nw_Compression.h"
#include "ClientProcess.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
bool g_bStopWatching = true;
bool g_bIsFirstScan = true;
int g_nCurrIndex = 0;
nw_CaptureThread *m_pCaptureThread = NULL;
//---------------------------------------------------------------------------
__fastcall nw_CaptureThread::nw_CaptureThread()
{
	m_pTimer = new TTimer(Application);
    m_pTimer->Enabled = false;
    m_pTimer->Interval = 15;
    m_pTimer->OnTimer = DoTimer;

	InitializeCompression();

    g_bStopWatching = false;
    m_bConference = false;

    // Initialize Screen Canvas
	m_pScreenCanvas=new TCanvas();
    m_pScreenCanvas->Handle=GetWindowDC(GetDesktopWindow());

    m_pBitmap=new Graphics::TBitmap();
    m_pSendStream=new TMemoryStream();
    m_pStream = new TMemoryStream();
}
//---------------------------------------------------------------------------
__fastcall nw_CaptureThread::~nw_CaptureThread()
{
	DoDestroy(NULL);
}
//---------------------------------------------------------------------------
void __fastcall nw_CaptureThread::SetCaptureSettings(int nReferencesCount,int nFrameW,int nFrameH)
{
	int nScreenWidth,nScreenHeight;
	HDC hdc = GetWindowDC(GetDesktopWindow());
    nScreenWidth = GetDeviceCaps(hdc, HORZRES);
    nScreenHeight = GetDeviceCaps(hdc, VERTRES);

	m_nReferencesCount=nReferencesCount;
    m_nFrameW=nFrameW;
    m_nFrameH=nFrameH;
    m_rcDest=Rect(0,0,m_nFrameW,m_nFrameH);

    // Initialize Bitmap
    m_pBitmap->Width=m_rcDest.Width();
    m_pBitmap->Height=m_rcDest.Height();
//    m_pBitmap->Width=nScreenWidth;
//    m_pBitmap->Height=nScreenHeight;
    m_pBitmap->PixelFormat=pf24bit;

    // Generate Unique Random Points
    vector<TPoint> RandomPoints;
	for(int y=0;y<m_nFrameH;y++)
    {
     	for(int x=0;x<m_nFrameW;x++)
        {
			RandomPoints.push_back(Point(x,y));
        }
    }
    random_shuffle(RandomPoints.begin(),RandomPoints.end());

	m_nRectsCount=0;
	for(int y=0;y<nScreenHeight;y+=m_nFrameH)
    {
     	for(int x=0;x<nScreenWidth;x+=m_nFrameW)
        {
        	vecRectInfo[m_nRectsCount].LeftTop=Point(x,y);
            vecRectInfo[m_nRectsCount].References.clear();
            for(int i=0;i<nReferencesCount;i++)
            {
    			TReference Reference;
            	Reference.x=x+RandomPoints[i].x;
                Reference.y=y+RandomPoints[i].y;
                Reference.Color=clBlack;
                vecRectInfo[m_nRectsCount].References.push_back(Reference);
            }
            m_nRectsCount++;
        }
    }

    g_nCurrIndex=0;
}
//---------------------------------------------------------------------------
void __fastcall nw_CaptureThread::DoDestroy(TObject *Sender)
{
	FinalizeCompression();
	g_bStopWatching = true;
	if(m_pScreenCanvas)	delete m_pScreenCanvas;
    m_pScreenCanvas=NULL;
    if(m_pBitmap)	delete m_pBitmap;
    m_pBitmap=NULL;
    if(m_pSendStream)	delete m_pSendStream;
    m_pSendStream=NULL;
    if(m_pStream)	delete m_pStream;
    m_pStream = NULL;
}
//---------------------------------------------------------------------------
void __fastcall nw_CaptureThread::Capture()
{
    if(g_bStopWatching)	return;
    if(DMClient->m_bError) 	return;
    if(DMClient->m_bSending)	return;
	m_LeftTop=vecRectInfo[g_nCurrIndex].LeftTop;
	g_nCurrIndex++;
	if(g_nCurrIndex >= m_nRectsCount)
    {
    	g_bIsFirstScan = false;
		g_nCurrIndex = 0;
    }
    m_rcSource=Rect(m_LeftTop.x+0,m_LeftTop.y+0,m_LeftTop.x+m_nFrameW,m_LeftTop.y+m_nFrameH);
//  m_rcDest=m_rcSource;
    m_pBitmap->Canvas->CopyRect(m_rcDest,m_pScreenCanvas,m_rcSource);

    Compress(m_LeftTop.x,m_LeftTop.y,m_pBitmap,m_pSendStream);

//    m_nSize = m_pSendStream->Size;
//    m_pStream->Write(&m_nSize,sizeof(m_nSize));
//    m_pStream->Write(m_pSendStream->Memory,m_nSize);

	if(m_bConference)
    {
        if(FormMain->TabControlConference->TabIndex == 0)
        {
	        for(int i=1;i<FormMain->TabControlConference->Tabs->Count;i++)
	        {
	        	m_strTo = GetUserName(FormMain->TabControlConference->Tabs->Strings[i]);
		    	DMClient->SendStream(m_pSendStream,"IMAGE","",m_strTo);
	        }
        }
        else
        {
	    	m_strTo = GetUserName(FormMain->TabControlConference->Tabs->Strings[FormMain->TabControlConference->TabIndex]);
	    	DMClient->SendStream(m_pSendStream,"IMAGE","",m_strTo);
    	}
    }
    else
    {
	    DMClient->SendStream(m_pSendStream,"IMAGE","",m_strTo);
    }
}
//---------------------------------------------------------------------------
bool __fastcall nw_CaptureThread::IsRectChanged()
{
	bool bChanged=false;
    for(UINT i=0;i<vecRectInfo[g_nCurrIndex].References.size();i++)
    {
    	m_nX=vecRectInfo[g_nCurrIndex].References[i].x;
    	m_nY=vecRectInfo[g_nCurrIndex].References[i].y;
        m_Color=m_pScreenCanvas->Pixels[m_nX][m_nY];
        if(m_Color != vecRectInfo[g_nCurrIndex].References[i].Color)
        {
        	bChanged=true;
        	vecRectInfo[g_nCurrIndex].References[i].Color=m_Color;
        }
    }
	return bChanged;
}
//---------------------------------------------------------------------------
void __fastcall nw_CaptureThread::DoTimer(TObject *Sender)
{
    if(g_bStopWatching)	return;
    if(DMClient->m_bError) 	return;
    if(DMClient->m_bSending)	return;

	// Capture Desktop Image
//    if(g_nCurrIndex == 0)
//    {
//        m_pStream->Position = 0;
//    }
//    if(g_bIsFirstScan || IsRectChanged())
    {
        Capture();
    }
//	g_nCurrIndex++;
	if(g_nCurrIndex >= m_nRectsCount)
    {
    	g_bIsFirstScan = false;
		g_nCurrIndex = 0;

//	    Compress(0,0,m_pBitmap,m_pStream);
//    	DMClient->SendStream(m_pStream,"IMAGE","",m_strTo);
    }
}
//---------------------------------------------------------------------------

