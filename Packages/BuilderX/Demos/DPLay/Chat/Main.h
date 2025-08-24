//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DXPlay.hpp"
//---------------------------------------------------------------------------
const int DXCHAT_MESSAGE = 0;
struct TDXChatMessage
{
    DWORD MessageType;
    int Len;
    char *C;
};
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo1;
	TEdit *Edit1;
	TButton *Button1;
	TDXPlay *DXPlay1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall DXPlay1AddPlayer(TObject *Sender, TDXPlayPlayer *Player);
	void __fastcall DXPlay1DeletePlayer(TObject *Sender,
          TDXPlayPlayer *Player);
	void __fastcall DXPlay1Message(TObject *Sender, TDXPlayPlayer *From,
          Pointer Data, int DataSize);
	void __fastcall DXPlay1Open(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
