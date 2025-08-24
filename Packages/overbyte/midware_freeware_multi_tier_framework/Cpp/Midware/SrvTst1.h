//---------------------------------------------------------------------------
#ifndef SrvTst1H
#define SrvTst1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "ApServer.hpp"
#include "RBroker.hpp"
#include "SrvTst2.h"
#include "cipher.h"
#include <Db.hpp>
#include <DBTables.hpp>
#include <DB.hpp>
#define WM_APPSTARTUP  (WM_USER + 1)
//---------------------------------------------------------------------------
class TServerForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TLabel *ClientCountLabel;
    TLabel *ObjectCountLabel;
    TLabel *Label1;
    TLabel *Label2;
    TButton *TestButton;
    TButton *DisconnectAllButton;
    TButton *ClearButton;
    TButton *FunctionsButton;
    TRequestBroker *RequestBroker1;
    TAppServer *AppServer1;
    TTable *Table1;
    TQuery *Query1;
    TMemo *DisplayMemo;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall DisconnectAllButtonClick(TObject *Sender);
    void __fastcall AppServer1ClientConnected(TObject *Sender,
          TClientWSocket *CliWSocket);
    void __fastcall AppServer1ClientClosed(TObject *Sender,
          TClientWSocket *CliWSocket);
    void __fastcall AppServer1Display(TObject *Sender, AnsiString Msg);
    void __fastcall AppServer1ClientCommand(TObject *Sender,
          TClientWSocket *CliWSocket, PChar CmdBuf, int CmdLen);
    void __fastcall RequestBroker1ObjCreate(TObject *Sender,
          TServerObject *ServerObject);
    void __fastcall RequestBroker1ObjDestroy(TObject *Sender,
          TServerObject *ServerObject);
    void __fastcall ClearButtonClick(TObject *Sender);
    void __fastcall FunctionsButtonClick(TObject *Sender);
    void __fastcall TestButtonClick(TObject *Sender);
    void __fastcall AppServer1ClientTimeout(TObject *Sender,
          TClientWSocket *CliWSocket, bool &CanClose);
    
    void __fastcall AppServer1BeforeSendReply(TObject *Sender,
          TClientWSocket *CliWSocket);
    void __fastcall AppServer1AfterSendReply(TObject *Sender,
          TClientWSocket *CliWSocket);
    void __fastcall AppServer1BeforeProcessRequest(TObject *Sender,
          TClientWSocket *CliWSocket, PChar &CmdBuf, int &CmdLen);
private:	// User declarations
    AnsiString      FIniFileName;
    BOOL	        FInitialized;
    AnsiString      FPort;
    PUserDataRecord FUserData;
    TMWBuffer       *FRequestBuffer;
    bool __fastcall EnumServerFunctions(TObject *Sender, AnsiString FunctionCode);
protected:
    void __fastcall TServerForm::WMAppStartup(TMessage &Msg);
    BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_APPSTARTUP, TMessage, WMAppStartup)
    END_MESSAGE_MAP(TForm)
public:		// User declarations
    __fastcall TServerForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TServerForm *ServerForm;
//---------------------------------------------------------------------------
#endif
