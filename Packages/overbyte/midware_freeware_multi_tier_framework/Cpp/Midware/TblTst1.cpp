/*---------------------------------------------------------------------------

Author:       François PIETTE
Description:  Client application using MidWare (Middleware by F. Piette).
              Shows how to use a DBGrid and DBNavigator.
              Using the object inspector, the following links are established:
              DataSource1.DataSet     := MWTable1;
              DBGrid1.DataSource      := DataSource1;
              DBNavigator1.DataSource := DataSource1;
              MWTable1.Data           := MWBuffer1;
              AppSrvClient1.Answer    := MWBuffer1;
Creation:     June 21, 1998 (from Delphi version created March 20, 1998)
Version:      1.01
EMail:        francois.piette@pophost.eunet.be    
              francois.piette@rtfm.be             http://www.rtfm.be/fpiette
Support:      Use the mailing list midware@rtfm.be See website for details.
Legal issues: Copyright (C) 1998 by François PIETTE
              Rue de Grady 24, 4053 Embourg, Belgium. Fax: +32-4-365.74.56
              <francois.piette@pophost.eunet.be>

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
Jun 01, 1998 V1.01 Removed beta status. Changed "legal stuff" to prohibe
             commercial applications whithout an agreement.

---------------------------------------------------------------------------*/
#include <vcl.h>
#pragma hdrstop

#include "TblTst1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ApsCli"
#pragma link "MWDatSet"
#pragma link "RFormat"
#pragma link "MwDatSet"
#pragma resource "*.dfm"
TTblTstForm *TblTstForm;
//---------------------------------------------------------------------------
__fastcall TTblTstForm::TTblTstForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TTblTstForm::RequestButtonClick(TObject *Sender)
{
//    AnsiString Key;
//
//    Key = KeyEdit->Text;
//    Key = "ABCDEFGH";
//    Key[5] = 0;
    AppSrvClient1->Request->Rewrite();
    AppSrvClient1->Request->WriteFields(TRUE, ARRAYOFCONST((KeyEdit->Text)));
    AppSrvClient1->Send();
}
//---------------------------------------------------------------------------
void __fastcall TTblTstForm::AppSrvClient1RequestDone(TObject *Sender,
      int Error)
{
    if ((Error != 0) || (AppSrvClient1->AnswerStatus != "200")) {
        StatusBar1->Panels->Items[2]->Text = "Failed";
        MWBuffer1->Rewrite();
    }
    else {
        StatusBar1->Panels->Items[2]->Text = IntToStr(MWBuffer1->RecordCount) +
                                             " record(s)";
    }
    // Refresh is not implemented, close/open does the trick
    MWTable1->Close();
    MWTable1->Open();
    ActiveControl = DBGrid1;
}
//---------------------------------------------------------------------------
void __fastcall TTblTstForm::FormShow(TObject *Sender)
{
    StatusBar1->Panels->Items[0]->Text = AppSrvClient1->Server + ':' +
                                         AppSrvClient1->Port;
}
//---------------------------------------------------------------------------
void __fastcall TTblTstForm::AppSrvClient1SessionConnected(TObject *Sender,
      WORD Error)
{
    if (Error == 0)
        StatusBar1->Panels->Items[1]->Text = "Connected";
    else
        StatusBar1->Panels->Items[1]->Text = "Can't connect, error #" +
                                             IntToStr(Error);
}
//---------------------------------------------------------------------------
void __fastcall TTblTstForm::AppSrvClient1SessionClosed(TObject *Sender,
      WORD Error)
{
    StatusBar1->Panels->Items[1]->Text = "Not connected";
}
//---------------------------------------------------------------------------
