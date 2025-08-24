//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ACMDialog"
#pragma link "ACMWaveIn"
#pragma link "ACMWaveOut"
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ACMWaveInData(Pointer data, int size)
{
	if(CheckBoxServer->Checked)
    {
		if(ServerSocket->Socket->ActiveConnections > 0)
	    {
			ServerSocket->Socket->Connections[0]->SendBuf(data,size);
	    }
    }
    else
    {
    	ClientSocket->Socket->SendBuf(data,size);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonStartClick(TObject *Sender)
{
	tWAVEFORMATEX Format;
    PWaveFormatEx pFormat;
/*
    Format.wFormatTag = 1;
    Format.nChannels = 1;
    Format.nSamplesPerSec = 8000;
    Format.nAvgBytesPerSec = 8000;
    Format.nBlockAlign = 1;
    Format.wBitsPerSample = 8;
    Format.cbSize = 18964;
*/
	pFormat = (PWaveFormatEx)ACMDialog->OpenDialog();
//	pFormat = &Format;

    Memo->Clear();
    Memo->Lines->Add(FormatFloat("wFormatTag: 0",pFormat->wFormatTag));
    Memo->Lines->Add(FormatFloat("nChannels: 0",pFormat->nChannels));
    Memo->Lines->Add(FormatFloat("nSamplesPerSec: 0",pFormat->nSamplesPerSec));
    Memo->Lines->Add(FormatFloat("nAvgBytesPerSec: 0",pFormat->nAvgBytesPerSec));
    Memo->Lines->Add(FormatFloat("nBlockAlign: 0",pFormat->nBlockAlign));
    Memo->Lines->Add(FormatFloat("wBitsPerSample: 0",pFormat->wBitsPerSample));
    Memo->Lines->Add(FormatFloat("cbSize: 0",pFormat->cbSize));

    if(pFormat == NULL)	return;
	if(CheckBoxServer->Checked)
	    ACMWaveIn->Open(pFormat);
    else
	    ACMWaveOut->Open(pFormat);

    ButtonStart->Enabled = false;
    ButtonStop->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonStopClick(TObject *Sender)
{
	if(CheckBoxServer->Checked)
		ACMWaveIn->Close();
    else
	    ACMWaveOut->Close();
    ButtonStart->Enabled = true;
    ButtonStop->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ServerSocketClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
	int nLength = Socket->ReceiveLength();
    Byte *pBuffer = new Byte[nLength];
    Socket->ReceiveBuf(pBuffer,nLength);
	ACMWaveOut->PlayBack(pBuffer,nLength);
    if(pBuffer)
    {
     	delete[] pBuffer;
        pBuffer = NULL;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Button1Click(TObject *Sender)
{
	if(CheckBoxServer->Checked)
    {
		ServerSocket->Active = true;
     	ClientSocket->Active = false;
        StatusBar->SimpleText = "Server";
    }
    else
    {
		ServerSocket->Active = false;
    	ClientSocket->Host = Edit->Text;
     	ClientSocket->Active = true;
        StatusBar->SimpleText = "Client";
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ClientSocketRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
	int nLength = Socket->ReceiveLength();
    Byte *pBuffer = new Byte[nLength];
    Socket->ReceiveBuf(pBuffer,nLength);
	ACMWaveOut->PlayBack(pBuffer,nLength);
    if(pBuffer)
    {
     	delete[] pBuffer;
        pBuffer = NULL;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ServerSocketClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
	StatusBar->SimpleText = "Connected: "+Socket->RemoteHost;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ServerSocketClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
	StatusBar->SimpleText = "DisConnected: "+Socket->RemoteHost;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ClientSocketConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
	StatusBar->SimpleText = "Connected to: "+Socket->RemoteHost;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ClientSocketDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
	StatusBar->SimpleText = "DisConnected from: "+Socket->RemoteHost;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Button2Click(TObject *Sender)
{
	int nLength = 1024;
    Byte *pBuffer = new Byte[nLength];
    for(int j=0;j<10;j++)
    {
	    for(int i=0;i<nLength;i++)
	    {
	    	pBuffer[i] = random(256);
	    }
//		ACMWaveOut->PlayBack(pBuffer,nLength);
		ACMWaveInData(pBuffer,nLength);
        Sleep(10);
    }
    if(pBuffer)
    {
     	delete[] pBuffer;
        pBuffer = NULL;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
	ButtonStopClick(NULL);
}
//---------------------------------------------------------------------------


