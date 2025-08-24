/*---------------------------------------------------------------------------

Author:       François PIETTE
Description:  This program is a demonstration for graphic field use with
              MidWare. It works as a client for the SrvDemo program. A SQL
              request is sent to SrvDemo to retrieve fish info from the
              demo database BIOLIFE (from Inprise sample data). You must
              copy biolife.db, biolife.mb, biolife.px from delphi\demos\data
              to the directory where SrvDemo is (internet\midware).
Creation:     Augustus 24, 1998 (Translated from Delphi version)
Version:      1.01
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

---------------------------------------------------------------------------*/
#include <vcl.h>
#pragma hdrstop

#include "BioLife1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ApsCli"
#pragma link "MWDatSet"
#pragma link "RFormat"
#pragma link "MwDatSet"
#pragma link "MwDatSet"
#pragma resource "*.dfm"
TBioLifeForm *BioLifeForm;
//---------------------------------------------------------------------------
__fastcall TBioLifeForm::TBioLifeForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
AnsiString DoubleQuote(AnsiString Value)
{
    int I;
    AnsiString Result;

    Result = "";
    for(I = 1; I <= Value.Length(); I++) {
        if (Value[I] == '\'')
            Result = Result + "''";
        else
            Result = Result + Value[I];
    }
    return(Result);
}
//---------------------------------------------------------------------------
void __fastcall TBioLifeForm::RequestButtonClick(TObject *Sender)
{
    AnsiString Params;

    MWTable1->Close();
    Params = "select Common_Name, Notes, Graphic from biolife";
    if (Trim(WhereEdit->Text) > "")
        Params = Params + " where " + WhereEdit->Text;
    StatusBar1->Panels->Items[0]->Text = "";
    StatusBar1->Panels->Items[1]->Text = Params;
    MWTable1->Params = "'" + DoubleQuote(Params) + "'";
    MWTable1->ExecuteRequest();
    RequestButton->Enabled = FALSE;
}
//---------------------------------------------------------------------------
void __fastcall TBioLifeForm::MWTable1RequestDone(TObject *Sender,
      int Error)
{
    RequestButton->Enabled = TRUE;
    if (Error != 0) {
        StatusBar1->Panels->Items[0]->Text = IntToStr(Error);
        Application->MessageBox(("Error #"+ IntToStr(Error)).c_str(), "Warning", MB_OK);
        return;
    }

    if (MWTable1->AppSrvClient->AnswerStatus == "200") {
        // Table is automatically opened
        StatusBar1->Panels->Items[0]->Text = IntToStr(MWTable1->Data->RecordCount);
        return;
    }

    Application->MessageBox(("Unable to get data from server\n"
                             "Server report error message:\n\n" +
                             MWTable1->Data->RecordToString()).c_str(),
                            "Warning", MB_OK);
}
//---------------------------------------------------------------------------
