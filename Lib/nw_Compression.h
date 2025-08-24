//---------------------------------------------------------------------------
#ifndef nw_CompressionH
#define nw_CompressionH
//---------------------------------------------------------------------------
#include <jpeg.hpp>
//---------------------------------------------------------------------------
extern AnsiString strCompressionType;
//---------------------------------------------------------------------------
struct TCompressionHeader
{
	Word Left;
    Word Top;
};
//---------------------------------------------------------------------------
void InitializeCompression();
void FinalizeCompression();
void Compress(int left,int top,Graphics::TBitmap *pBitmap,TMemoryStream *pStream);
void DeCompress(TMemoryStream *pStream,Graphics::TBitmap *pBitmap,int &left,int &top);
void DeCompress(TMemoryStream *pStream,TCanvas *pCanvas);
//---------------------------------------------------------------------------
AnsiString Encrypt(AnsiString strText);
AnsiString Decrypt(AnsiString strText);
//---------------------------------------------------------------------------
extern TJPEGImage *g_pJPEG;
//---------------------------------------------------------------------------
#endif
