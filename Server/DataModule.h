//---------------------------------------------------------------------------

#ifndef DataModuleH
#define DataModuleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ActnList.hpp>
#include <ActnMan.hpp>
#include <DB.hpp>
#include <DBClient.hpp>
#include <AppEvnts.hpp>
#include <ImgList.hpp>
#include <ComCtrls.hpp>
#include "SingleInstance.h"
#include "ApServer.hpp"
#include "RBroker.hpp"
#include "trayicon.h"
#include <DBTables.hpp>
#include <ExtCtrls.hpp>
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TDM : public TDataModule
{
__published:	// IDE-managed Components
	TPopupMenu *PopupMenuGroups;
	TMenuItem *ANewGroup1;
	TDataSource *DataSourceGroups;
	TDataSource *DataSourceComputers;
	TApplicationEvents *ApplicationEvents;
	TMainMenu *MainMenu;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TImageList *ImageListTreeView;
	TMenuItem *N9;
	TMenuItem *N10;
	TMenuItem *N11;
	TPopupMenu *PopupMenuDisplay;
	TMenuItem *MenuItem1;
	TRequestBroker *RequestBroker1;
	TAppServer *AppServer1;
	TMenuItem *N5;
	TPopupMenu *PopupMenuTrayIcon;
	TMenuItem *N6;
	TMenuItem *N7;
	TMenuItem *N8;
	TTable *TableGroups;
	TTable *TableComputers;
	TStringField *TableComputersComputer_Name;
	TIntegerField *TableComputersGroup_ID;
	TBooleanField *TableComputersConnected;
	TAutoIncField *TableGroupsGroup_ID;
	TStringField *TableGroupsGroup_Name;
	TTimer *TimerPro1;
	TTimer *TimerPro2;
	TTimer *TimerPro3;
	TMenuItem *N12;
	TMenuItem *N13;
	TFormTranslation *FormTranslation1;
	TActionList *ActionList;
	TAction *AGroups;
	TAction *ANewGroup;
	TAction *ARemoveGroup;
	TAction *ARemoveAllGroups;
	TAction *AClient;
	TAction *AJoinInGroup;
	TAction *AMoveToGroup;
	TAction *AClearAll;
	TAction *ANetwork;
	TAction *AUpdateClients;
	TAction *AExit;
	TAction *ARestore;
	TAction *AClose;
	void __fastcall ANewGroupExecute(TObject *Sender);
	void __fastcall DataModuleCreate(TObject *Sender);
	void __fastcall ApplicationEventsHint(TObject *Sender);
	void __fastcall ARemoveGroupExecute(TObject *Sender);
	void __fastcall ARemoveAllGroupsExecute(TObject *Sender);
	void __fastcall AGroupsExecute(TObject *Sender);
	void __fastcall PopupMenuGroupsPopup(TObject *Sender);
	void __fastcall AJoinInGroupExecute(TObject *Sender);
	void __fastcall AMoveToGroupExecute(TObject *Sender);
	void __fastcall AClientExecute(TObject *Sender);
	void __fastcall AClearAllExecute(TObject *Sender);
	void __fastcall ANetworkExecute(TObject *Sender);
	void __fastcall AUpdateClientsExecute(TObject *Sender);
	void __fastcall AppServer1ClientClosed(TObject *Sender,
          TClientWSocket *CliWSocket);
	void __fastcall AppServer1ClientCommand(TObject *Sender,
          TClientWSocket *CliWSocket, PChar CmdBuf, int CmdLen);
	void __fastcall AppServer1ClientConnected(TObject *Sender,
          TClientWSocket *CliWSocket);
	void __fastcall AppServer1Display(TObject *Sender, AnsiString Msg);
	void __fastcall AExitExecute(TObject *Sender);
	void __fastcall TimerPro1Timer(TObject *Sender);
	void __fastcall TimerPro2Timer(TObject *Sender);
	void __fastcall TimerPro3Timer(TObject *Sender);
	void __fastcall ApplicationEventsIdle(TObject *Sender, bool &Done);
	void __fastcall ApplicationEventsActivate(TObject *Sender);
	void __fastcall ApplicationEventsDeactivate(TObject *Sender);
	void __fastcall ARestoreExecute(TObject *Sender);
	void __fastcall ACloseExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TDM(TComponent* Owner);
	void __fastcall LoadGroups();
	void __fastcall ClearAllGroups();
	void __fastcall ReBuildTreeViewGroups();

    AnsiString strAppPath;
	int m_nWithoutGroupID;
//---------------------------------------------------------------------------
};
//---------------------------------------------------------------------------
extern PACKAGE TDM *DM;
//---------------------------------------------------------------------------
#endif
