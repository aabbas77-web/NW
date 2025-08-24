//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "nw_SelectClient.h"
#include "nw_Messages.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSelectClient *FormSelectClient;
//---------------------------------------------------------------------------
__fastcall TFormSelectClient::TFormSelectClient(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormSelectClient::BitBtn1Click(TObject *Sender)
{
	if(m_bAllowNoneClients)
    {
    	ModalResult = mrOk;
        return;
    }
	if(ListBoxClients->Items->Count > 0)
    {
    	ModalResult = mrOk;
        return;
    }
    MessageDlg(FormMessages->ValueListEditor->Values["c_strYouMustSelectAClientFirst"],mtInformation,TMsgDlgButtons()<<mbOK,0);
}
//---------------------------------------------------------------------------
void __fastcall TFormSelectClient::BitBtn2Click(TObject *Sender)
{
	ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TFormSelectClient::AddClient(AnsiString strClientName)
{
	if(m_bSelectMaximumOne)
    {
		if(ListBoxClients->Items->Count >= 1)	return;
    }
	int nIndex;
    nIndex = ListBoxClients->Items->IndexOf(strClientName);
    if(nIndex < 0)
    {
    	ListBoxClients->Items->Add(strClientName);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormSelectClient::RemoveClient(AnsiString strClientName)
{
	int nIndex;
    nIndex = ListBoxClients->Items->IndexOf(strClientName);
    if(nIndex >= 0)
    {
    	ListBoxClients->Items->Delete(nIndex);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormSelectClient::SpeedButton1Click(TObject *Sender)
{
	for(UINT i=0;i<TreeViewGroups->SelectionCount;i++)
    {
		if(TreeViewGroups->Selections[i]->Level != 0)
        {
        	AddClient(TreeViewGroups->Selections[i]->Text);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormSelectClient::SpeedButton2Click(TObject *Sender)
{
	for(int i=0;i<TreeViewGroups->Items->Count;i++)
    {
		if(TreeViewGroups->Items->Item[i]->Level != 0)
        {
        	AddClient(TreeViewGroups->Items->Item[i]->Text);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormSelectClient::SpeedButton3Click(TObject *Sender)
{
	TStringList *pList = new TStringList();
	for(int i=0;i<ListBoxClients->Items->Count;i++)
    {
		if(!ListBoxClients->Selected[i])
        {
			pList->Add(ListBoxClients->Items->Strings[i]);
        }
    }
    ListBoxClients->Items->Assign(pList);
    if(pList)
    {
     	delete pList;
        pList = NULL;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormSelectClient::SpeedButton4Click(TObject *Sender)
{
	ListBoxClients->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TFormSelectClient::FormCreate(TObject *Sender)
{
	m_bAllowNoneClients = false;
    m_bSelectMaximumOne = false;	
}
//---------------------------------------------------------------------------

void __fastcall TFormSelectClient::TreeViewGroupsDblClick(TObject *Sender)
{
	SpeedButton1Click(NULL);
}
//---------------------------------------------------------------------------

