//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ApServer.hpp"
#include "ApsCli.hpp"
#include "RBroker.hpp"
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include "singleinstance.h"
#include "SingleInstance.h"
#include <ActnList.hpp>
#include <ActnMan.hpp>
#include "trayicon.h"
#include "FormTranslation.h"
//---------------------------------------------------------------------------
namespace NW_Server
{
typedef void __fastcall (__closure *TDisplayEvent)(System::TObject* Sender, System::AnsiString Msg);
//---------------------------------------------------------------------------
// This record is all the informations we need to hold for each client
struct TChatUser
{
	AnsiString     Name;       // The client nick name
	AnsiString     IP;         // The client IP address
	AnsiString     Port;       // The client server port number
    int				LanguageID;// The language ID
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
    						  int				LanguageID,
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
    // Get the client's server language ID for a given user ID
	int __fastcall GetLanguageID(int ID);
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
}	/* namespace NW_Server */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace NW_Server;
#endif
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
private:
	void __fastcall SendMessageRequestDone(TObject* Sender, int Error);
__published:	// IDE-managed Components
    TMemo *DisplayMemo;
	TStatusBar *StatusBar;
	TGroupBox *GroupBoxNetwork;
	TTreeView *TreeViewGroups;
	TSplitter *SplitterNetwork;
	TFormTranslation *FormTranslation1;
	TTrayIcon *TrayIcon;
	TSingleAppInstance *SingleAppInstance1;
	TSplitter *Splitter1;
	TGroupBox *GroupBox1;
	TListBox *ListBoxSoundUsers;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
	void __fastcall TreeViewGroupsGetSelectedIndex(TObject *Sender,
          TTreeNode *Node);
	void __fastcall TreeViewGroupsMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall SingleAppInstance1SecondInstance(TObject *Sender,
          bool &ShutDown);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
	void __fastcall CreateParams(Controls::TCreateParams &Params);
public:		// User declarations
    __fastcall TFormMain(TComponent* Owner);
	void __fastcall LoadSettings();
	void __fastcall SaveSettings();
	void __fastcall UpdateConnectedClients();
	void __fastcall ConnectUserToTreeView(AnsiString strUserName);
	void __fastcall DisConnectUserFromTreeView(AnsiString strUserName);
	void __fastcall UpdateSoundUsers();
    TUserData       *FUserData;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
AnsiString Translate(AnsiString strBeforeTranslation);
//---------------------------------------------------------------------------
#endif
