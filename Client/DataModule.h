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
#include "trayicon.h"
#include "FormTranslation.h"
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <JPEG.hpp>
//---------------------------------------------------------------------------
typedef enum {stChatting,stWatching,stAutoWatch,stFileManager,stMaintenance,stCommandPrompt,stMessages,stConference} TServiceType; 
//---------------------------------------------------------------------------
const int c_nServicesCount = 8;
//---------------------------------------------------------------------------
class TDM : public TDataModule
{
__published:	// IDE-managed Components
	TApplicationEvents *ApplicationEvents;
	TMainMenu *MainMenu;
	TImageList *ImageList;
	TMenuItem *N12;
	TMenuItem *N13;
	TPopupMenu *PopupMenuFileManager;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N9;
	TImageList *ImageList1;
	TMenuItem *N11;
	TMenuItem *N14;
	TTrayIcon *TrayIcon;
	TPopupMenu *PopupMenuTrayIcon;
	TMenuItem *MenuItem1;
	TMenuItem *N18;
	TMenuItem *N19;
	TMenuItem *N22;
	TMenuItem *N23;
	TFormTranslation *FormTranslation1;
	TActionList *ActionList;
	TAction *AConnection;
	TAction *AConnect;
	TAction *ABack;
	TAction *ARefresh;
	TAction *AExit;
	TAction *AHelp;
	TAction *AAbout;
	TAction *AWatchingReport;
	TAction *ARestore;
	TAction *AStopWatching;
	TAction *AContents;
	TAction *AOptions;
	TAction *ASound;
	TAction *AStopSound;
	TAction *ACopy;
	TMenuItem *N24;
	TAction *APaste;
	TAction *ASendMessage;
	TAction *ASelectChatingClients;
	TAction *ASelectWatchingClients;
	TAction *AStartWatching;
	TAction *ASelectMaintenanceClients;
	TAction *AStartMaintenance;
	TAction *AStopMaintenance;
	TAction *ASelectFileManagerClients;
	TAction *ASelectCommandPromptClients;
	TAction *ASelectMessagesClients;
	TAction *ASendDocument;
	TOpenDialog *OpenDialogDocument;
	TAction *ASelectConferenceClients;
	TAction *AStartConference;
	TAction *AStopConference;
	TAction *AChating;
	TAction *ACommandPrompt;
	TAction *AConference;
	TAction *AFileManager;
	TAction *AMaintenance;
	TAction *AMessages;
	TAction *AWatching;
	TAction *AServices;
	TMenuItem *Services1;
	TMenuItem *Chating1;
	TMenuItem *Watching1;
	TMenuItem *Filemanager1;
	TMenuItem *Commandprompt1;
	TMenuItem *Maintenance1;
	TMenuItem *Messages1;
	TMenuItem *Conference1;
	TAction *AClose;
	TAction *ADelete;
	TMenuItem *Delete1;
	TAction *AOpen;
	TMenuItem *Open1;
	TMenuItem *N5;
	TTimer *TimerConnection;
	TAction *AStartAutoWatch;
	TAction *AStopAutoWatch;
	TAction *AAutoWatchReport;
	TAction *ASelectAutoWatchClients;
	TTimer *TimerAutoWatch;
	void __fastcall DataModuleCreate(TObject *Sender);
	void __fastcall ApplicationEventsHint(TObject *Sender);
	void __fastcall DataModuleDestroy(TObject *Sender);
	void __fastcall AConnectExecute(TObject *Sender);
	void __fastcall AConnectionExecute(TObject *Sender);
	void __fastcall ABackExecute(TObject *Sender);
	void __fastcall ARefreshExecute(TObject *Sender);
	void __fastcall ApplicationEventsShortCut(TWMKey &Msg, bool &Handled);
	void __fastcall AExitExecute(TObject *Sender);
	void __fastcall AHelpExecute(TObject *Sender);
	void __fastcall AAboutExecute(TObject *Sender);
	void __fastcall AWatchingReportExecute(TObject *Sender);
	void __fastcall ARestoreExecute(TObject *Sender);
	void __fastcall AStopWatchingExecute(TObject *Sender);
	void __fastcall AContentsExecute(TObject *Sender);
	void __fastcall AOptionsExecute(TObject *Sender);
	void __fastcall ASoundExecute(TObject *Sender);
	void __fastcall AStopSoundExecute(TObject *Sender);
	void __fastcall ACopyExecute(TObject *Sender);
	void __fastcall APasteExecute(TObject *Sender);
	void __fastcall ASendMessageExecute(TObject *Sender);
	void __fastcall ASelectChatingClientsExecute(TObject *Sender);
	void __fastcall ASelectWatchingClientsExecute(TObject *Sender);
	void __fastcall AStartWatchingExecute(TObject *Sender);
	void __fastcall ASelectMaintenanceClientsExecute(TObject *Sender);
	void __fastcall AStartMaintenanceExecute(TObject *Sender);
	void __fastcall AStopMaintenanceExecute(TObject *Sender);
	void __fastcall ASelectFileManagerClientsExecute(TObject *Sender);
	void __fastcall ASelectCommandPromptClientsExecute(TObject *Sender);
	void __fastcall ASelectMessagesClientsExecute(TObject *Sender);
	void __fastcall ASendDocumentExecute(TObject *Sender);
	void __fastcall ASelectConferenceClientsExecute(TObject *Sender);
	void __fastcall AStartConferenceExecute(TObject *Sender);
	void __fastcall AStopConferenceExecute(TObject *Sender);
	void __fastcall AChatingExecute(TObject *Sender);
	void __fastcall ACommandPromptExecute(TObject *Sender);
	void __fastcall AConferenceExecute(TObject *Sender);
	void __fastcall AFileManagerExecute(TObject *Sender);
	void __fastcall AMaintenanceExecute(TObject *Sender);
	void __fastcall AMessagesExecute(TObject *Sender);
	void __fastcall AWatchingExecute(TObject *Sender);
	void __fastcall AServicesExecute(TObject *Sender);
	void __fastcall ACloseExecute(TObject *Sender);
	void __fastcall ADeleteExecute(TObject *Sender);
	void __fastcall AOpenExecute(TObject *Sender);
	void __fastcall TimerConnectionTimer(TObject *Sender);
	void __fastcall AStartAutoWatchExecute(TObject *Sender);
	void __fastcall AStopAutoWatchExecute(TObject *Sender);
	void __fastcall AAutoWatchReportExecute(TObject *Sender);
	void __fastcall ASelectAutoWatchClientsExecute(TObject *Sender);
	void __fastcall TimerAutoWatchTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TDM(TComponent* Owner);
	void __fastcall TreeViewGroupsClick(TObject *Sender);
	void __fastcall ClearTabs();
	void __fastcall FinishPreviousService();

    TServiceType ServiceType;
    AnsiString strAppPath;
    bool m_bConnected;
    bool m_bSound;
    Graphics::TBitmap *m_pBitmap;
    TJPEGImage *m_pJPEG;

    TTabControl *TabControls[c_nServicesCount];
    int m_nCurrentAutoWatchClientIndex;
    int m_nCurrentAutoWatchIndex;
    int m_nCurrentFrameIndex;
    int m_nFrameCount;
};
//---------------------------------------------------------------------------
extern PACKAGE TDM *DM;
//---------------------------------------------------------------------------
#endif
