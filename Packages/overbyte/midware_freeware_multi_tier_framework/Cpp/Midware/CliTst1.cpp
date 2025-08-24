/*---------------------------------------------------------------------------

Author:       François PIETTE
Description:  Sample client for the sample application server using
              F. Piette's Middleware (MidWare).
Creation:     June 21, 1998 (from Delphi version created March 3, 1998)
Version:      1.06
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
Aug 16, 1999  V1.06 Adapted for BCB4

---------------------------------------------------------------------------*/
#include <stdlib.h>
#include <vcl.h>
#include <vcl\inifiles.hpp>
#pragma hdrstop

#include "CliTst1.h"
#include "cipher.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ApsCli"
#pragma link "RFormat"
#pragma resource "*.dfm"

#define CliTstVersion  106
#define SectionData    "Data"
#define KeyPort        "Port"
#define KeyServer      "Server"
#define SectionWindow  "Window"
#define KeyTop         "Top"
#define KeyLeft        "Left"
#define KeyWidth       "Width"
#define KeyHeight      "Height"
#define KeyData        "Data"
#define KeyFunction    "Function"
#define KeyEncrypt     "Encrypt"

TTestClientForm *TestClientForm;
//---------------------------------------------------------------------------
__fastcall TTestClientForm::TTestClientForm(TComponent* Owner)
    : TForm(Owner)
{
    FIniFileName = LowerCase(ExtractFileName(Application->ExeName));
    FIniFileName = FIniFileName.SubString(1, FIniFileName.Length() - 3) + "ini";
}
//---------------------------------------------------------------------------
void __fastcall TTestClientForm::FormCreate(TObject *Sender)
{
    Memo1->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TTestClientForm::FormShow(TObject *Sender)
{
    TIniFile *IniFile;
    TWSAData Data;

    if (!FInitialized) {
        FInitialized = TRUE;
        IniFile      = new TIniFile(FIniFileName);
        Top          = IniFile->ReadInteger(SectionWindow, KeyTop,    Top);
        Left         = IniFile->ReadInteger(SectionWindow, KeyLeft,   Left);
        Width        = IniFile->ReadInteger(SectionWindow, KeyWidth,  Width);
        Height       = IniFile->ReadInteger(SectionWindow, KeyHeight, Height);
        FPort        = IniFile->ReadString(SectionData,    KeyPort,   "2106");
        FServer      = IniFile->ReadString(SectionData,    KeyServer, "localhost");

        DataEdit->Text     = IniFile->ReadString(SectionData,
                                                 KeyData, "Piette");
        FunctionEdit->Text = IniFile->ReadString(SectionData,
                                                 KeyFunction, "GETCLIENT");
        EncryptCheckBox->Checked = (IniFile->ReadInteger(SectionData,
                                                         KeyEncrypt, 0) != 0);
        delete IniFile;

        PortEdit->Text   = FPort;
        ServerEdit->Text = FServer;

        // Display all pertinent info versions
        Memo1->Lines->Add(Format("Program version %d.%2.2d" ,
                          ARRAYOFCONST((CliTstVersion / 100, CliTstVersion % 100))));
        Memo1->Lines->Add(Format("MidWare client version %d.%2.2d" ,
                          ARRAYOFCONST((AppSrvClientVersion / 100, AppSrvClientVersion % 100))));
        Memo1->Lines->Add(Format("MWBuffer version %d.%2.2d" ,
                          ARRAYOFCONST((MWBufferVersion / 100, MWBufferVersion % 100))));
        Memo1->Lines->Add(Format("TWSocket version %d.%2.2d" ,
                          ARRAYOFCONST((WSocketVersion / 100, WSocketVersion % 100))));
        Data = WinsockInfo();
        Memo1->Lines->Add("Winsock verion " +
                          IntToStr(LOBYTE(Data.wVersion)) + "->" +
                          IntToStr(HIBYTE(Data.wVersion)));
        Memo1->Lines->Add(StrPas(Data.szDescription));
        Memo1->Lines->Add(StrPas(Data.szSystemStatus));
    }
}
//---------------------------------------------------------------------------
void __fastcall TTestClientForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    TIniFile *IniFile;

    IniFile = new TIniFile(FIniFileName);
    IniFile->WriteInteger(SectionWindow, KeyTop,      Top);
    IniFile->WriteInteger(SectionWindow, KeyLeft,     Left);
    IniFile->WriteInteger(SectionWindow, KeyWidth,    Width);
    IniFile->WriteInteger(SectionWindow, KeyHeight,   Height);
    IniFile->WriteInteger(SectionData,   KeyEncrypt,  EncryptCheckBox->Checked);
    IniFile->WriteString(SectionData,    KeyPort,     PortEdit->Text);
    IniFile->WriteString(SectionData,    KeyServer,   ServerEdit->Text);
    IniFile->WriteString(SectionData,    KeyData,     DataEdit->Text);
    IniFile->WriteString(SectionData,    KeyFunction, FunctionEdit->Text);
    delete IniFile;
}
//---------------------------------------------------------------------------
void __fastcall TTestClientForm::DisconnectButtonClick(TObject *Sender)
{
    AppSrvClient1->Close();
}
//---------------------------------------------------------------------------
void __fastcall TTestClientForm::ClearButtonClick(TObject *Sender)
{
    Memo1->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TTestClientForm::SendButtonClick(TObject *Sender)
{
    DisconnectButton->Enabled   = TRUE;
    AppSrvClient1->FunctionCode = Trim(FunctionEdit->Text);
    AppSrvClient1->Request->Rewrite();
    AppSrvClient1->Request->WriteFields(TRUE, ARRAYOFCONST((DataEdit->Text, "abc'def", "123")));
    AppSrvClient1->Request->WriteFields(TRUE, ARRAYOFCONST(("delphi")));
    AppSrvClient1->Port   = PortEdit->Text;
    AppSrvClient1->Server = ServerEdit->Text;
    AppSrvClient1->Send();
}
//---------------------------------------------------------------------------
void __fastcall TTestClientForm::ImageFormClose(TObject *Sender,
      TCloseAction &Action)
{
    Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TTestClientForm::DisplayBmpFile(void)
{
    TForm        *Form;
    TImage       *Image;
    TFileStream  *Data;
    TMWFieldType FieldType;
    AnsiString   FileName;

    FileName = ExtractFileName(AppSrvClient1->Answer->Fields[0]);
    Memo1->Lines->Add("Displaying image " + FileName);
    Data = new TFileStream(FileName, fmCreate);
    AppSrvClient1->Answer->GetStreamField(1, Data, FieldType);
    delete Data;

    // Just for fun, I create a TForm on the fly with a TImage component
    Form           = new TForm((void *)NULL);
    Form->Position = poDefaultPosOnly;
    Form->Width    = Screen->Width / 2;
    Form->Height   = Screen->Height / 2;
    Form->Caption  = FileName;
    Form->OnClose  = ImageFormClose;
    Image          = new TImage(Form);
    Image->Parent  = Form;
    Image->Align   = alClient;
    Image->Picture->LoadFromFile(FileName);
    Form->Width    = Image->Picture->Width + Form->Width - Form->ClientWidth;
    Form->Height   = Image->Picture->Height + Form->Height - Form->ClientHeight;
    Form->BorderIcons = (TBorderIcons()<< biSystemMenu << biMinimize << biMaximize);

    Form->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTestClientForm::AppSrvClient1RequestDone(TObject *Sender,
      int Error)
{
    int nRec;

    if (Error == 0) {
        if ((FunctionEdit->Text == "GETFILE") &&
            (AppSrvClient1->AnswerStatus == "200") &&
            (ExtractFileExt(UpperCase(Trim(DataEdit->Text))) == ".BMP"))
            DisplayBmpFile();
        else {
            Memo1->Lines->Add("Answer status = " + AppSrvClient1->AnswerStatus);
            nRec = 0;
            AppSrvClient1->Answer->First();
            while (!AppSrvClient1->Answer->Eof) {
                nRec++;
                Memo1->Lines->Add(IntToStr(nRec) + ": " +
                                  AppSrvClient1->Answer->RecordToString());
                AppSrvClient1->Answer->Next();
            }
        }
    }
    else
        Memo1->Lines->Add("Error #" + IntToStr(Error));
}
//---------------------------------------------------------------------------
void __fastcall TTestClientForm::AppSrvClient1SessionClosed(
      TObject *Sender, WORD Error)
{
    DisconnectButton->Enabled = FALSE;
}
//---------------------------------------------------------------------------
void __fastcall TTestClientForm::AppSrvClient1BeforeProcessReply(
      TObject *Sender, PChar &CmdBuf, int &CmdLen)
{
    int Cnt;

    // Check if we have some encrypted data
    if ((CmdLen < 3) || (CmdBuf[0] != 3))
        return;

    // We've got encrypted data. Decrypt on same place
    Decrypt(CmdBuf, CmdLen, CmdBuf, &Cnt);
}
//---------------------------------------------------------------------------
void __fastcall TTestClientForm::AppSrvClient1BeforeSendRequest(
      TObject *Sender)
{
    char *Dst;
    int  DstLen;
    int  Key;

    if (!EncryptCheckBox->Checked)
        return;

    Key = '0';
    // Encrypt will allocate new memory for encrypted data which takes a
    // little bit more space than original data.
    // Memory will be freed in the OnAfterSendRequest event handler.
    Encrypt(AppSrvClient1->RequestHeader, AppSrvClient1->RequestHeaderLen,
            &Dst, &DstLen, Key, 2);
    AppSrvClient1->RequestHeader    = Dst;
    AppSrvClient1->RequestHeaderLen = DstLen;
    Dst[0] = 3;     // This will let the server know we use encrypted data
    Dst[1] = (char)Key;
    Encrypt(AppSrvClient1->RequestBody, AppSrvClient1->RequestBodyLen,
            &Dst, &DstLen, Key, 0);
    AppSrvClient1->RequestBody    = Dst;
    AppSrvClient1->RequestBodyLen = DstLen;
}
//---------------------------------------------------------------------------
void __fastcall TTestClientForm::AppSrvClient1AfterSendRequest(
      TObject *Sender)
{
    if (!EncryptCheckBox->Checked)
        return;

    // Memory was allocated in the OnBeforeSendRequest event handler. We have
    // to free it to avoid memory leaks.
    free(AppSrvClient1->RequestHeader);
    free(AppSrvClient1->RequestBody);
}
//---------------------------------------------------------------------------

