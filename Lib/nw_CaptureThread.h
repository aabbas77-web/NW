//---------------------------------------------------------------------------
#ifndef nw_CaptureThreadH
#define nw_CaptureThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
#include <vector.h>
//---------------------------------------------------------------------------
struct TReference
{
    int		x,y;
    DWORD 	Color;// For Testing
};
//---------------------------------------------------------------------------
typedef vector<TReference> vecReferences;
//---------------------------------------------------------------------------
extern bool g_bIsFirstScan;
extern int g_nCurrIndex;
//---------------------------------------------------------------------------
class TRectInfo
{
public:
	TPoint	LeftTop;
    vecReferences References;

	TRectInfo()
    {
    	LeftTop=Point(0,0);
    }
    ~TRectInfo()
    {
    }
    TRectInfo &operator =(const TRectInfo &r)
    {
    	LeftTop=r.LeftTop;
		References.clear();
		copy(r.References.begin(),r.References.end(),back_inserter(References));
        return *this;
    }
};
//---------------------------------------------------------------------------
class nw_CaptureThread
{            
private:
protected:
public:
	__fastcall nw_CaptureThread();
	__fastcall ~nw_CaptureThread();
	void __fastcall DoDestroy(TObject *Sender);
	void __fastcall Capture();
	bool __fastcall IsRectChanged();
	void __fastcall SetCaptureSettings(int nReferencesCount,int nFrameW,int nFrameH);
	void __fastcall DoTimer(TObject *Sender);

	TTimer *m_pTimer;

    TCanvas *m_pScreenCanvas;
    Graphics::TBitmap *m_pBitmap;
    TMemoryStream *m_pSendStream;
    TMemoryStream *m_pStream;
    __int64 m_nSize;

    TPoint m_LeftTop;
    DWORD m_Color;
    int m_nX,m_nY;
    TRect m_rcDest,m_rcSource;

    int m_nFrameW,m_nFrameH;

    TRectInfo vecRectInfo[1000];

    int m_nRectsCount;
    int m_nReferencesCount;

    AnsiString m_strTo;
    bool m_bConference;
};
//---------------------------------------------------------------------------
extern	nw_CaptureThread *m_pCaptureThread;
//---------------------------------------------------------------------------
#endif
