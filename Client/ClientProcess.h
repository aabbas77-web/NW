//---------------------------------------------------------------------------

#ifndef ClientProcessH
#define ClientProcessH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ApsCli.hpp"
#include "ApServer.hpp"
#include "RBroker.hpp"
#include "RFormat.hpp"
#include "nw_CaptureThread.h"
#include "FormTranslation.h"
//---------------------------------------------------------------------------
namespace ClientProcess
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
    INPUT StdInput;
};
//---------------------------------------------------------------------------
}	/* namespace ClientProcess */
//---------------------------------------------------------------------------
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace ClientProcess;
#endif
//---------------------------------------------------------------------------
class TDMClient : public TDataModule
{
__published:	// IDE-managed Components
	TMWBuffer *AnswerMWBuffer;
	TAppSrvClient *AppSrvClient;
	TRequestBroker *RequestBroker;
	TAppServer *AppServer;
	TFormTranslation *FormTranslation1;
	void __fastcall DataModuleCreate(TObject *Sender);
	void __fastcall DataModuleDestroy(TObject *Sender);
	void __fastcall AppSrvClientRequestDone(TObject *Sender, int Error);
	void __fastcall AppSrvClientSessionClosed(TObject *Sender, WORD Error);
	void __fastcall AppSrvClientSessionConnected(TObject *Sender, WORD Error);
	void __fastcall AppServerDisplay(TObject *Sender, AnsiString Msg);
	void __fastcall AppSrvClientSocksError(TObject *Sender, int Error,
          AnsiString Msg);
private:	// User declarations
public:		// User declarations
	__fastcall TDMClient(TComponent* Owner);
	void __fastcall Initialize();
	void __fastcall LoadSettings();
	void __fastcall SaveSettings();
	void __fastcall Connect();
	void __fastcall AutoConnect();
	void __fastcall DoConnect(void);
	void __fastcall LogonRequestDone(TObject *Sender,int Error);
	void __fastcall MessageToRequestDone(TObject *Sender,int Error);
	void __fastcall Display(AnsiString Msg);
	void __fastcall SendStream(TMemoryStream *Data,AnsiString strMessageType,AnsiString strMessageTitle,AnsiString strTo);
	void __fastcall SendText(AnsiString strText);
	void __fastcall StartServer(void);
	void __fastcall SendWatchCommand(AnsiString strTo,bool bStart,int nInterval,int nFrameSize);
	void __fastcall SendFoldersCommand(AnsiString strCommand,int nFolderIndex);
	void __fastcall SendFolders(AnsiString strTo);
	int __fastcall GetFileIconIndex(AnsiString strFileName);
	int __fastcall GetFolderIconIndex(AnsiString strFolderName);
	void __fastcall SendFolderCommand(AnsiString strCommand,int nFolderIndex);
	void __fastcall SendFileFromRemoteToLocal(AnsiString strTo,AnsiString strFileName,AnsiString strDestFileName);
	void __fastcall SendPathFromRemoteToLocal(AnsiString strTo,AnsiString strPath);
	void __fastcall SendFileFromLocalToRemote(AnsiString strTo,AnsiString strFileName,AnsiString strDestFileName);
	void __fastcall SendPathFromLocalToRemote(AnsiString strTo,AnsiString strPath);
	void __fastcall CopyFolders(AnsiString strPath);
	void __fastcall SendKeyboardCommand(Word wKey,Word wShift);
	void __fastcall SendMouseCommand(DWORD dwFlag,int nX,int nY);
	void __fastcall SendDesktopSettingsCommand(int nColors,int nWidth,int nHeight);
	void __fastcall SendMaintenanceCommand(bool bStart);
	void __fastcall SendWatchFeedBackCommand(AnsiString strTo);
	void __fastcall SendCommandPromptCommand(AnsiString strCommand);
	void __fastcall SendBuffer(Pointer data,int size,AnsiString strType,AnsiString strTitle);
	void __fastcall SendSoundCommand(bool bStart);
	void __fastcall SendMessage();
	void __fastcall SendDocument(AnsiString strFileName);
	void __fastcall SendConferenceCommand(bool bStart);
	void __fastcall SendWindowsMessage(UINT Msg,WPARAM wParam,LPARAM lParam);
	void __fastcall SaveAutoFrame();

    TUserData       *FUserData;
	AnsiString 	m_strServer;
	AnsiString 	m_strMe;
	AnsiString 	m_strTo;
    bool		m_bSending;
    int			m_nLanguageID;
    bool 		m_bVisible;
    AnsiString 	m_strLastMessage;
    int left,top;
    Graphics::TBitmap *m_pBitmap;
    bool		m_bError;
    TStringList *m_pFolders;

    AnsiString m_strUserName;
    AnsiString m_strComputerName;
    AnsiString m_strWindowsDir;
    int m_nFolderIconIndex;
    bool	m_bConnected;
    AnsiString m_strCurrentSoundUser;

    bool m_bDisplaySettingsChanged;
    AnsiString m_strCopyCommand;
    MSG m_Msg;
    tagPOINT CursorPos;
};
//---------------------------------------------------------------------------
extern PACKAGE TDMClient *DMClient;
//---------------------------------------------------------------------------
bool gChangeResolution(UINT w, UINT h, UINT bitdepth);
AnsiString GetUserName(AnsiString strUserName);
//---------------------------------------------------------------------------
#endif
