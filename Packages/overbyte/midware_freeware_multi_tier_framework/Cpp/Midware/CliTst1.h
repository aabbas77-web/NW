//---------------------------------------------------------------------------
#ifndef CliTst1H
#define CliTst1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ApsCli.hpp"
#include "RFormat.hpp"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TTestClientForm : public TForm
{
__published:	// IDE-managed Components
    TMemo *Memo1;
    TPanel *Panel1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TButton *SendButton;
    TButton *DisconnectButton;
    TEdit *DataEdit;
    TEdit *FunctionEdit;
    TButton *ClearButton;
    TEdit *ServerEdit;
    TEdit *PortEdit;
    TCheckBox *EncryptCheckBox;
    TAppSrvClient *AppSrvClient1;
    TMWBuffer *MWBuffer1;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall DisconnectButtonClick(TObject *Sender);
    void __fastcall ClearButtonClick(TObject *Sender);
    void __fastcall SendButtonClick(TObject *Sender);
    void __fastcall AppSrvClient1RequestDone(TObject *Sender, int Error);
    void __fastcall AppSrvClient1SessionClosed(TObject *Sender,
          WORD Error);
    void __fastcall AppSrvClient1BeforeProcessReply(TObject *Sender,
          PChar &CmdBuf, int &CmdLen);
    void __fastcall AppSrvClient1BeforeSendRequest(TObject *Sender);
    void __fastcall AppSrvClient1AfterSendRequest(TObject *Sender);
private:	// User declarations
    AnsiString FIniFileName;
    BOOL	   FInitialized;
    AnsiString FPort;
    AnsiString FServer;
    void __fastcall ImageFormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall DisplayBmpFile(void);
public:		// User declarations
    __fastcall TTestClientForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTestClientForm *TestClientForm;
//---------------------------------------------------------------------------
#endif
