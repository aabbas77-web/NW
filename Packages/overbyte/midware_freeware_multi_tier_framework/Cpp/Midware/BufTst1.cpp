/*---------------------------------------------------------------------------

Author:       François PIETTE
Description:  Sample to show how to use TMWBuffer
              (F. Piette's Middleware (MidWare))
Creation:     June 21, 1998 (fron Delphi version created March 14, 1998)
Version:      1.00
EMail:        francois.piette@overbyte.be   francois.piette@rtfm.be
              http://www.overbyte.be        http://www.rtfm.be/fpiette
              francois.piette@pophost.eunet.be
Support:      Use the mailing list midware@elists.org
              Follow "support" link at http://www.overbyte.be for subscription.
Legal issues: Copyright (C) 1998-2002 by François PIETTE
              Rue de Grady 24, 4053 Embourg, Belgium. Fax: +32-4-365.74.56
              <francois.piette@overbyte.be> <francois.piette@pophost.eunet.be>

              This software is provided 'as-is', without any express or
              implied warranty.  In no event will the author be held liable
              for any  damages arising from the use of this software.

              Permission is granted to anyone to use this software and or any
              derived or altered versions for any purpose, excluding commercial
              applications. You can use this software for personal or internal
              use only. You may distribute it freely untouched.
              The following restrictions applies:

              1. The origin of this software must not be misrepresented, you
                 must not claim that you wrote the original software.

              2. If you use this software in a product, an acknowledgment in
                 the product documentation and displayed on screen is required.
                 The text must be: "This product is based on MidWare. Freeware
                 source code is available at http://www.rtfm.be/fpiette."

              3. Altered source versions must be plainly marked as such, and
                 must not be misrepresented as being the original software.

              4. This notice may not be removed or altered from any source
                 distribution and must be added to the product documentation.

Updates:
May 16, 1998 Added a TMWTable on the form to make the sample program more
             realistic (the TMWTable was dynamically created).

---------------------------------------------------------------------------*/
#include <vcl.h>
#include <stdlib.h>
#pragma hdrstop

// If the symbol TABLE is defined, the program will use a TTable as data source
// else, it will use a MWBuffer. This will demonstrate the polymorphism and
// similar behaviour between a TTable and a TMWBuffer.
// To define/undefine the symbol TABLE, comment or uncomment the next line.
//#define TABLE
#include "BufTst1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MWDatSet"
#pragma link "RFormat"
#pragma link "MwDatSet"
#pragma resource "*.dfm"
TBufTstForm *BufTstForm;
//---------------------------------------------------------------------------
__fastcall TBufTstForm::TBufTstForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TBufTstForm::FormCreate(TObject *Sender)
{
    FSize = 100;
    FBuffer = (char *)malloc(FSize);
#ifdef TABLE
    FData                 = Table1;
    DataSource1->DataSet  = Table1;
#else
    FData                 = MWBuffer1;
    DataSource1->DataSet  = MWTable1;
#endif
    CreateData();
    DataSource1->DataSet->Active = TRUE;
}
//---------------------------------------------------------------------------
void __fastcall TBufTstForm::FormShow(TObject *Sender)
{
    if (!FInitialized ) {
        FInitialized = TRUE;
#ifdef TABLE
        FData->Open();
#endif
        DisplayData();
        FData->First();
        ShowCurrent();
    }
}
//---------------------------------------------------------------------------
void __fastcall TBufTstForm::FormDestroy(TObject *Sender)
{
    free(FBuffer);
}
//---------------------------------------------------------------------------
void __fastcall TBufTstForm::CreateData(void)
{
#ifndef TABLE
    FData->Rewrite();
    FData->WriteFields(TRUE, ARRAYOFCONST(("JULES",     "CAESAR")));
    FData->WriteFields(TRUE, ARRAYOFCONST(("ASTERIX",   "LE GAULOIS")));
    FData->WriteFields(TRUE, ARRAYOFCONST(("CAPITAINE", "HADDOCK")));
    FData->WriteFields(TRUE, ARRAYOFCONST(("RIC",       "HOCHET")));
    FData->First();
#endif
}
//---------------------------------------------------------------------------
AnsiString __fastcall TBufTstForm::Field(int nIndex)
{
#ifdef TABLE
    return(FData->Fields[nIndex]->AsString);
#else
    return(FData->Fields[nIndex]);
#endif
}
//---------------------------------------------------------------------------
AnsiString __fastcall TBufTstForm::Info(void)
{
#ifdef TABLE
    return("");
#else
    return(" Size="   + IntToStr(FData->DataBufferSize) +
           " Count=" + IntToStr(FData->DataBufferCount) +
           " Tell="  + IntToStr(FData->Tell()));
#endif
}
//---------------------------------------------------------------------------
void __fastcall TBufTstForm::DisplayData(void)
{
    TBookmark Bookmark;

    Memo1->Clear();
#ifdef TABLE
    Memo1->Lines->Add("Using TTable " + FData->DatabaseName + "\\" + FData->TableName);
#else
    Memo1->Lines->Add("Using TMWBuffer");
#endif
    Memo1->Lines->Add("");

    Bookmark = FData->GetBookmark();
    FData->First();
    while (!FData->Eof) {
        Memo1->Lines->Add("'" + Field(0) + "', '" + Field(1) + "'" + Info());
        FData->Next();
    }
    FData->GotoBookmark(Bookmark);
    FData->FreeBookmark(Bookmark);
}
//---------------------------------------------------------------------------
void __fastcall TBufTstForm::ShowCurrent(void)
{
    Label1->Caption = Field(0) + Info();
    EofCheckBox->Checked = FData->Eof;
    BofCheckBox->Checked = FData->Bof;
}
//---------------------------------------------------------------------------
void __fastcall TBufTstForm::PriorButtonClick(TObject *Sender)
{
    FData->Prior();
    ShowCurrent();
}
//---------------------------------------------------------------------------
void __fastcall TBufTstForm::NextButtonClick(TObject *Sender)
{
    FData->Next();
    ShowCurrent();
}
//---------------------------------------------------------------------------
void __fastcall TBufTstForm::FirstButtonClick(TObject *Sender)
{
    FData->First();
    ShowCurrent();
}
//---------------------------------------------------------------------------
void __fastcall TBufTstForm::LastButtonClick(TObject *Sender)
{
    FData->Last();
    ShowCurrent();
}
//---------------------------------------------------------------------------
void __fastcall TBufTstForm::DeleteButtonClick(TObject *Sender)
{
    FData->Delete();
    ShowCurrent();
    DisplayData();
}
//---------------------------------------------------------------------------
void __fastcall TBufTstForm::CreateButtonClick(TObject *Sender)
{
    CreateData();
    DisplayData();
    ShowCurrent();
}
//---------------------------------------------------------------------------
