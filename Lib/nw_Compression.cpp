//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include <JPEG.hpp>
#include "nw_Compression.h"
#include "nw_RLE.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
AnsiString strCompressionType = "JPEG";
TJPEGImage *g_pJPEG = NULL;
Graphics::TBitmap *g_pBitmap = NULL;
TCompressionHeader CompressionHeader;
//---------------------------------------------------------------------------
AnsiString Encrypt(AnsiString strText)
{
/*
	strText = strText.Trim();
	AnsiString strResult = "";
    int nLength = strText.Length();
	for(int i=1;i<=nLength;i++)
    {
		strResult += char(~Byte(strText[i]));
    }
	return strResult;
*/
	return strText;
}
//---------------------------------------------------------------------------
AnsiString Decrypt(AnsiString strText)
{
/*
	AnsiString strResult = "";
    int nLength = strText.Length();
	for(int i=1;i<=nLength;i++)
    {
		strResult += char(~Byte(strText[i]));
    }
	return strResult.Trim();
*/
	return strText;
}
//---------------------------------------------------------------------------
void InitializeCompression()
{
	g_pJPEG = new TJPEGImage();
    g_pJPEG->CompressionQuality = 40;
    g_pJPEG->Performance = jpBestSpeed;
    g_pJPEG->Grayscale = false;
    g_pJPEG->PixelFormat = jf24Bit;
    g_pBitmap = new Graphics::TBitmap();
}
//---------------------------------------------------------------------------
void FinalizeCompression()
{
	if(g_pJPEG)	delete g_pJPEG;
    g_pJPEG = NULL;
    if(g_pBitmap)	delete g_pBitmap;
    g_pBitmap = NULL;
}
//---------------------------------------------------------------------------
void Compress(int left,int top,Graphics::TBitmap *pBitmap,TMemoryStream *pStream)
{
	CompressionHeader.Left=left;
    CompressionHeader.Top=top;
    pStream->SetSize(0);
    pStream->Position=0;
    pStream->Write(&CompressionHeader,sizeof(CompressionHeader));

	if(SameText(strCompressionType,"RLE"))
    {
     	nw_CompressRLE(pBitmap,pStream);
    }
    else
	if(SameText(strCompressionType,"JPEG"))
    {
        g_pJPEG->Assign(pBitmap);
    	g_pJPEG->SaveToStream(pStream);
    }
    else 
	if(SameText(strCompressionType,"BMP256"))
    {
    	pBitmap->PixelFormat = pf8bit;
    	pBitmap->SaveToStream(pStream);
    	pBitmap->PixelFormat = pf24bit;
    }
    else // no compression
    {
    	pBitmap->SaveToStream(pStream);
    }
}
//---------------------------------------------------------------------------
void DeCompress(TMemoryStream *pStream,Graphics::TBitmap *pBitmap,int &left,int &top)
{                         
	pStream->Position=0;
    pStream->Read(&CompressionHeader,sizeof(CompressionHeader));
    left=CompressionHeader.Left;
    top=CompressionHeader.Top;

	if(SameText(strCompressionType,"RLE"))
    {
     	nw_DeCompressRLE(pStream,pBitmap);
    }
    else
	if(SameText(strCompressionType,"JPEG"))
    {
    	g_pJPEG->LoadFromStream(pStream);
        pBitmap->Assign(g_pJPEG);
    }
    else
	if(SameText(strCompressionType,"BMP256"))
    {
    	pBitmap->LoadFromStream(pStream);
    	pBitmap->PixelFormat = pf24bit;
    }
    else // no compression
    {
    	pBitmap->LoadFromStream(pStream);
    }
}
//---------------------------------------------------------------------------
void DeCompress(TMemoryStream *pStream,TCanvas *pCanvas)
{                         
	pStream->Position=0;
    pStream->Read(&CompressionHeader,sizeof(CompressionHeader));

	if(SameText(strCompressionType,"RLE"))
    {
     	nw_DeCompressRLE(pStream,g_pBitmap);
        pCanvas->Draw(CompressionHeader.Left,CompressionHeader.Top,g_pBitmap);
    }
    else
	if(SameText(strCompressionType,"JPEG"))
    {
    	g_pJPEG->LoadFromStream(pStream);
        pCanvas->Draw(CompressionHeader.Left,CompressionHeader.Top,g_pJPEG);
    }
    else
	if(SameText(strCompressionType,"BMP256"))
    {
    	g_pBitmap->LoadFromStream(pStream);
        pCanvas->Draw(CompressionHeader.Left,CompressionHeader.Top,g_pBitmap);
    }
    else // no compression
    {
    	g_pBitmap->LoadFromStream(pStream);
        pCanvas->Draw(CompressionHeader.Left,CompressionHeader.Top,g_pBitmap);
    }
}
//---------------------------------------------------------------------------

