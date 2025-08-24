//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "nw_RLE.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void nw_CompressRLE(Graphics::TBitmap *pBitmap,TMemoryStream *pStream)
{
	pBitmap->PixelFormat=pf24bit;
    int width=pBitmap->Width;
    int height=pBitmap->Height;
	nw_BGR *pColors;
    nw_BGR Color;
    nw_BGR BGRCount;
    Word Count;
    Word BGRSize=sizeof(nw_BGR);
    nw_RLEHeader RLEHeader;
    RLEHeader.Width=width;
    RLEHeader.Height=height;

    // Write RLE Header
    pStream->Write(&RLEHeader,sizeof(nw_RLEHeader));

    for(int y=0;y<height;y++)
    {
    	pColors=(nw_BGR *)pBitmap->ScanLine[y];
     	for(int x=0;x<width;)
        {
	    	Color=pColors[x];
	        Count=0;
	        while((x<width)&&(Color==pColors[x]))
	        {
	        	Count++;
	            x++;
	        }
	        if(Color.r==_Mark_)
	        	Color.r++;
	        if(Count==1)
	        {
	        	pStream->Write(&Color,BGRSize);
	        }
	        else
	        if(Count==2)
	        {
	        	pStream->Write(&Color,BGRSize);
	        	pStream->Write(&Color,BGRSize);
	        }
	        else
	        {
            	*((Word *)&BGRCount)=Count;
                BGRCount.r=_Mark_;
	        	pStream->Write(&BGRCount,BGRSize);
	            pStream->Write(&Color,BGRSize);
	        }
        }
    }
}
//---------------------------------------------------------------------------
void nw_DeCompressRLE(TMemoryStream *pStream,Graphics::TBitmap *pBitmap)
{                         
    nw_BGR Color;
    Word Count;
    nw_RLEHeader RLEHeader;
    Word BGRSize=sizeof(nw_BGR);

    // Read RLE Header
    pStream->Read(&RLEHeader,sizeof(nw_RLEHeader));
    pBitmap->Width=RLEHeader.Width;
    pBitmap->Height=RLEHeader.Height;
	pBitmap->PixelFormat=pf24bit;

    int x,y;
	nw_BGR *pColors;

    y=0;
    x=0;
    pColors=(nw_BGR *)pBitmap->ScanLine[y];
    while(pStream->Read(&Color,BGRSize))
    {
    	if(Color.r==_Mark_)
        {
        	Count=*((Word *)&Color);
            if(pStream->Read(&Color,BGRSize))
            {
				for(Word i=0;i<Count;i++)
                {
                	if(x<RLEHeader.Width)
                    {
	                	pColors[x]=Color;
	                    x++;
                    }
                }
            }
        }
        else
        {
        	if(x<RLEHeader.Width)
            {
            	pColors[x]=Color;
	            x++;
            }
        }
    	if((x>=RLEHeader.Width)&&(y<RLEHeader.Height-1))
        {
        	y++;
			x=0;
		    pColors=(nw_BGR *)pBitmap->ScanLine[y];
        }
    }
}
//---------------------------------------------------------------------------

