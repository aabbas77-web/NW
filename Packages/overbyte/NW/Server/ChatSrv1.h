//---------------------------------------------------------------------------
#ifndef ChatSrv1H
#define ChatSrv1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ApServer.hpp"
#include "ApsCli.hpp"
#include "RBroker.hpp"
#include <ExtCtrls.hpp>
#define  WM_APPSTARTUP  (WM_USER + 1)

namespace ChatSrv1
{
typedef void __fastcall (__closure *TDisplayEvent)(System::TObject* Sender, System::AnsiString Msg);

//---------------------------------------------------------------------------
// This record is all the informations we need to hold for each client
struct TChatUser
{
	AnsiString     Name;       // The client nick name
	AnsiString     IP;         // The client IP address
	AnsiString     Port;       // The client server port number
	TClientWSocket *Client;    // The client object inside the server
};
typedef TChatUser *PChatUser;
//---------------------------------------------------------------------------
// TUserData is a shared object which hold all informations and data
// processing common to all TServerObject and the server main code
class TUserData : public TObject
{
private:
	TDisplayEvent FOnDisplay;
protected:
	void __fastcall TriggerDisplay(AnsiString Msg);
public:
    // We hold all connected client into a list. The list items are
    // TChatUser object references
	TList* UserList;
	__fastcall virtual TUserData(void);
	__fastcall virtual ~TUserData(void);
    // The LogonUser procedure will add a new user to the list
	void __fastcall LogonUser(AnsiString     UserName,
                              AnsiString     IPAddr,
                              TClientWSocket *Client,
                              AnsiString     ReplyPort);
    // Find a user into the user list, using the username as a key
    // Returns a user ID which is simply the index into UserList
	int __fastcall FindUser(AnsiString UserName);
    // Find a client into the userlist, using the client object as a key
    // Returns a user ID which is simply the index into UserList
	int __fastcall FindClient(TClientWSocket* Client);
    // Get the name for a given user ID
	AnsiString __fastcall GetName(int ID);
    // Get the IP address for a given user ID
	AnsiString __fastcall GetIP(int ID);
    // Get the client's server port number for a given user ID
	AnsiString __fastcall GetPort(int ID);
    // Remove a client from the user list
	void __fastcall RemoveClient(TClientWSocket* Client);
    // Event to display messages into the server user interface
	__property TDisplayEvent OnDisplay = {read=FOnDisplay, write=FOnDisplay};
};
//---------------------------------------------------------------------------
// The LOGON request is received at the start of the communication.
// It is used to record the user into the user list.
class TServerObjectLOGON : public TServerObject
{
public:
	virtual void __fastcall Execute(void);
public:
	__fastcall virtual TServerObjectLOGON(TComponent* AOwner) : TServerObject(AOwner) { }
	__fastcall virtual ~TServerObjectLOGON(void) { }
};
//---------------------------------------------------------------------------
// The MESSAGETO request is use to forward a message from a user to
// another user.
class TServerObjectMESSAGETO : public TServerObject
{
private:
	void __fastcall ExecuteServiceMessages(int UserID, TStream* Data);
	void __fastcall SendMessageRequestDone(TObject* Sender, int Error);
public:
	virtual void __fastcall Execute(void);
public:
	__fastcall virtual TServerObjectMESSAGETO(TComponent* AOwner) : TServerObject(AOwner) { }
	__fastcall virtual ~TServerObjectMESSAGETO(void) { }
};
}	/* namespace ChatSrv1 */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace ChatSrv1;
#endif
//---------------------------------------------------------------------------
class TChatSrvForm : public TForm
{
__published:	// IDE-managed Components
    TMemo *DisplayMemo;
    TPanel *Panel1;
    TLabel *ClientCountLabel;
    TLabel *ObjectCountLabel;
    TLabel *Label1;
    TLabel *Label2;
    TButton *DisconnectAllButton;
    TButton *ClearButton;
    TButton *FunctionsButton;
    TButton *ListClientsButton;
    TRequestBroker *RequestBroker1;
    TAppServer *AppServer1;
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
    void __fastcall ListClientsButtonClick(TObject *Sender);
protected:
    void __fastcall TChatSrvForm::WMAppStartup(TMessage &Msg);
    BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_APPSTARTUP, TMessage, WMAppStartup)
    END_MESSAGE_MAP(TForm)
private:	// User declarations
    AnsiString      FIniFileName;
    BOOL	        FInitialized;
    AnsiString      FPort;
    TUserData       *FUserData;
    bool __fastcall EnumServerFunctions(TObject *Sender, AnsiString FunctionCode);
public:		// User declarations
    __fastcall TChatSrvForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TChatSrvForm *ChatSrvForm;
//---------------------------------------------------------------------------
#endif
