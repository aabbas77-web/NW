//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DXPlay"
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
  try
  {
    DXPlay1->Open();
  }
  catch(Exception &E)
  {
  	Application->ShowMainForm = false;
    Application->HandleException(&E);
    Application->Terminate();
  }

  Caption = DXPlay1->ProviderName +" : "+ DXPlay1->SessionName;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
  DXPlay1->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Edit1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  	if(Key == VK_RETURN)
  	{
    	Button1Click(NULL);
    	Key = 0;
  	}
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Button1Click(TObject *Sender)
{
  	Byte *Msg;
  	int MsgSize;

  	MsgSize = sizeof(TDXChatMessage)+Edit1->Text.Length();
  	Msg = new Byte[MsgSize];
  	try
    {
    	((TDXChatMessage *)Msg)->MessageType = DXCHAT_MESSAGE;
    	((TDXChatMessage *)Msg)->Len = Edit1->Text.Length();
    	CopyMemory(((TDXChatMessage *)Msg)->C, Edit1->Text.c_str(), Edit1->Text.Length());

    	//  The message is sent all.
    	DXPlay1->SendMessage(DPID_ALLPLAYERS, Msg, MsgSize);

    	//  The message is sent also to me.
    	DXPlay1->SendMessage(DXPlay1->LocalPlayer->ID, Msg, MsgSize);

    	Edit1->Text = "";
    }
  	__finally
    {
    	if(Msg) 	delete[] Msg;
        Msg = NULL;
  	}
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::DXPlay1AddPlayer(TObject *Sender,
      TDXPlayPlayer *Player)
{
   	Memo1->Lines->Add(Player->Name+" entered a room.");
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::DXPlay1DeletePlayer(TObject *Sender,
      TDXPlayPlayer *Player)
{
   	Memo1->Lines->Add(Player->Name+" left a room.");
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::DXPlay1Message(TObject *Sender,
      TDXPlayPlayer *From, Pointer Data, int DataSize)
{
  	AnsiString s;

  	switch(DXPlayMessageType(Data))
  	{
  		case DXCHAT_MESSAGE:
        {
          	if(((TDXChatMessage *)Data)->Len<=0)
            	s = "";
          	else
            {
            	s = AnsiString((char *)((TDXChatMessage *)Data)->C);
          	}

          	Memo1->Lines->Add(From->Name + "> "+s);
        }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::DXPlay1Open(TObject *Sender)
{
  	for(int i=0 ; i< DXPlay1->Players->Count;i++)
    {
    	if(DXPlay1->Players->Players[i]->RemotePlayer)
      		Memo1->Lines->Add(DXPlay1->Players->Players[i]->Name+" is entering a room.");
    }
}
//---------------------------------------------------------------------------
