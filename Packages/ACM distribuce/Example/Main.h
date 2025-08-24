//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ACMDialog.hpp"
#include "ACMWaveIn.hpp"
#include "ACMWaveOut.hpp"
#include <ScktComp.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TACMDialog *ACMDialog;
	TACMWaveOut *ACMWaveOut;
	TACMWaveIn *ACMWaveIn;
	TButton *ButtonStart;
	TEdit *Edit;
	TButton *ButtonStop;
	TServerSocket *ServerSocket;
	TCheckBox *CheckBoxServer;
	TButton *Button1;
	TClientSocket *ClientSocket;
	TStatusBar *StatusBar;
	TButton *Button2;
	TMemo *Memo;
	void __fastcall ACMWaveInData(Pointer data, int size);
	void __fastcall ButtonStartClick(TObject *Sender);
	void __fastcall ButtonStopClick(TObject *Sender);
	void __fastcall ServerSocketClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall ClientSocketRead(TObject *Sender,
          TCustomWinSocket *Socket);
	void __fastcall ServerSocketClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
	void __fastcall ServerSocketClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
	void __fastcall ClientSocketConnect(TObject *Sender,
          TCustomWinSocket *Socket);
	void __fastcall ClientSocketDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
