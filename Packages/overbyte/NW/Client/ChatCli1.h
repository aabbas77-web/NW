//---------------------------------------------------------------------------
#ifndef ChatCli1H
#define ChatCli1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ApsCli.hpp"
#include "ApServer.hpp"
#include "RBroker.hpp"
#include "RFormat.hpp"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
namespace ChatCli1
{
//---------------------------------------------------------------------------
typedef void __fastcall (__closure *TDisplayEvent)(System::TObject* Sender, System::AnsiString Msg);
//---------------------------------------------------------------------------
class TUserData : public TObject
{
private:
	TDisplayEvent FOnDisplay;
public:
	__fastcall TUserData(void) { }
	__fastcall virtual ~TUserData(void) { }
	void __fastcall TriggerDisplay(AnsiString Msg);
	__property TDisplayEvent OnDisplay = {read=FOnDisplay, write=FOnDisplay};
};
//---------------------------------------------------------------------------
class TServerObjectMESSAGETO : public TServerObject
{
public:
	virtual void __fastcall Execute(void);
public:
	__fastcall virtual TServerObjectMESSAGETO(TComponent* AOwner) : TServerObject(AOwner) { }
	__fastcall virtual ~TServerObjectMESSAGETO(void) { }
};
//---------------------------------------------------------------------------
}	/* namespace ChatCli1 */
//---------------------------------------------------------------------------
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace ChatCli1;
#endif
//---------------------------------------------------------------------------
class TChatClientForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TEdit *ToEdit;
    TEdit *ServerEdit;
    TEdit *FromEdit;
    TBitBtn *SendBitBtn;
    TBitBtn *ConnectBitBtn;
    TMemo *MsgMemo;
    TMemo *DisplayMemo;
    TAppSrvClient *AppSrvClient;
    TAppServer *AppServer;
    TRequestBroker *RequestBroker;
    TMWBuffer *AnswerMWBuffer;
	TButton *Button1;
	TOpenDialog *OpenDialog1;
	TSaveDialog *SaveDialog1;
	TListBox *ListBox;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall ConnectBitBtnClick(TObject *Sender);
    void __fastcall AppSrvClientRequestDone(TObject *Sender, int Error);
    void __fastcall AppServerDisplay(TObject *Sender, AnsiString Msg);
    void __fastcall SendBitBtnClick(TObject *Sender);
    void __fastcall AppSrvClientSessionConnected(TObject *Sender,
          WORD Error);
    void __fastcall AppSrvClientSessionClosed(TObject *Sender, WORD Error);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall MsgMemoKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall ListBoxClick(TObject *Sender);
private:	// User declarations
    TUserData       *FUserData;
    void __fastcall StartServer(void);
    void __fastcall DoConnect(void);
    void __fastcall LogonRequestDone(TObject *Sender, int Error);
    void __fastcall MessageToRequestDone(TObject *Sender, int Error);
    void __fastcall Display(AnsiString Msg);
public:		// User declarations
    __fastcall TChatClientForm(TComponent* Owner);
	void __fastcall LoadSettings();
	void __fastcall SaveSettings();
	void __fastcall SendStream(TMemoryStream *Data,AnsiString strMessageType,AnsiString strMessageTitle,AnsiString strTo);

	AnsiString m_strServer;    
	AnsiString m_strMe;
};
//---------------------------------------------------------------------------
extern PACKAGE TChatClientForm *ChatClientForm;
//---------------------------------------------------------------------------
#endif
