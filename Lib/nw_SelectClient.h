//---------------------------------------------------------------------------

#ifndef nw_SelectClientH
#define nw_SelectClientH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFormSelectClient : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBoxNetwork;
	TTreeView *TreeViewGroups;
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TPanel *Panel2;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TListBox *ListBoxClients;
	TPanel *Panel3;
	TPanel *Panel4;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton3;
	TSpeedButton *SpeedButton4;
	TBevel *Bevel1;
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall BitBtn2Click(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall SpeedButton3Click(TObject *Sender);
	void __fastcall SpeedButton4Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall TreeViewGroupsDblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormSelectClient(TComponent* Owner);
	void __fastcall AddClient(AnsiString strClientName);
	void __fastcall RemoveClient(AnsiString strClientName);
    bool m_bAllowNoneClients;
    bool m_bSelectMaximumOne;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSelectClient *FormSelectClient;
//---------------------------------------------------------------------------
#endif
