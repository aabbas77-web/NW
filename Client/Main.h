//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <DBCtrls.hpp>
//---------------------------------------------------------------------------
#include "shellctrls.h"
#include "ShellCtrls.h"
#include <ToolWin.hpp>
#include <AppEvnts.hpp>
#include "FormTranslation.h"
#include "ACMDialog.hpp"
#include "ACMWaveIn.hpp"
#include "ACMWaveOut.hpp"
#include <jpeg.hpp>
#include "FormStateSaver.h"
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBoxServices;
	TPageControl *PageControl;
	TTabSheet *TabSheetChating;
	TTabSheet *TabSheetWatching;
	TTabSheet *TabSheetFileManager;
	TGroupBox *GroupBoxChat;
	TTabControl *TabControlChat;
	TGroupBox *GroupBox4;
	TSplitter *Splitter2;
	TGroupBox *GroupBox5;
	TMemo *MemoSend;
	TGroupBox *GroupBoxMonitoring;
	TTabControl *TabControlMonitoring;
	TGroupBox *GroupBox6;
	TGroupBox *GroupBoxFileManager;
	TTabControl *TabControlFileManager;
	TGroupBox *GroupBoxFileManagerContainer;
	TGroupBox *GroupBox1;
	TSplitter *Splitter1;
	TPanel *Panel1;
	TPanel *Panel3;
	TShellTreeView *ShellTreeView1;
	TSplitter *Splitter3;
	TShellListView *ShellListView1;
	TGroupBox *GroupBox3;
	TPanel *Panel4;
	TListView *ListView1;
	TToolBar *ToolBar1;
	TToolButton *ToolButton1;
	TPanel *PanelPath;
	TGroupBox *GroupBox8;
	TSplitter *Splitter4;
	TTabSheet *TabSheetCommandPrompt;
	TGroupBox *GroupBoxCommandPrompt;
	TTabControl *TabControlCommandPrompt;
	TMemo *MemoCommandPromptResult;
	TMemo *MemoCommandPrompt;
	TPanel *PanelStatus;
	TFormTranslation *FormTranslation1;
	TACMWaveIn *ACMWaveIn;
	TACMWaveOut *ACMWaveOut;
	TACMDialog *ACMDialog;
	TToolBar *ToolBar2;
	TToolButton *ToolButtonSound;
	TToolButton *ToolButtonStopSound;
	TTabSheet *TabSheetAbout;
	TImage *ProgramIcon;
	TListBox *ListBoxMessages;
	TListBox *ListBoxPrevSend;
	TListBox *ListBoxReceive;
	TGroupBox *GroupBox2;
	TListBox *ListBoxSoundUsers;
	TSplitter *Splitter5;
	TTabSheet *TabSheetMaintenance;
	TPanel *PanelLanguage;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TToolBar *ToolBar3;
	TToolButton *ToolButton4;
	TToolButton *ToolButton5;
	TToolButton *ToolButtonStartWatching;
	TToolButton *ToolButtonStopWatching;
	TToolButton *ToolButton8;
	TScrollBox *ScrollBox1;
	TTabSheet *TabSheetConference;
	TToolButton *ToolButton9;
	TPaintBox *PaintBox;
	TTabControl *TabControlMaintenance;
	TPanel *Panel2;
	TToolBar *ToolBar4;
	TToolButton *ToolButton6;
	TToolButton *ToolButton7;
	TToolButton *ToolButtonStartMaintenance;
	TToolButton *ToolButtonStopMaintenance;
	TToolBar *ToolBar5;
	TToolButton *ToolButton10;
	TToolBar *ToolBar6;
	TToolButton *ToolButton11;
	TTabSheet *TabSheetMessages;
	TTabControl *TabControlMessages;
	TPanel *PanelMessages;
	TToolBar *ToolBar7;
	TToolButton *ToolButton12;
	TToolButton *ToolButton13;
	TToolButton *ToolButton14;
	TToolButton *ToolButton15;
	TTabControl *TabControlConference;
	TToolBar *ToolBar8;
	TToolButton *ToolButton16;
	TToolButton *ToolButton17;
	TPanel *Panel5;
	TToolButton *ToolButton18;
	TToolButton *ToolButton19;
	TCSpinEdit *CSpinEditWatchingDelay;
	TCSpinEdit *CSpinEditBlockSize;
	TTabSheet *TabSheet1;
	TGroupBox *GroupBox7;
	TTabControl *TabControlAutoWatch;
	TGroupBox *GroupBox9;
	TScrollBox *ScrollBox2;
	TPaintBox *PaintBox1;
	TToolBar *ToolBar9;
	TToolButton *ToolButton20;
	TToolButton *ToolButton21;
	TCSpinEdit *CSpinEditAutoWatchDelay;
	TCSpinEdit *CSpinEditAutoWatchBlockSize;
	TToolButton *ToolButtonStartAutoWatch;
	TToolButton *ToolButtonStopAutoWatch;
	TToolButton *ToolButton24;
	TToolButton *ToolButton25;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall TreeViewGroupsGetSelectedIndex(TObject *Sender,
          TTreeNode *Node);
	void __fastcall MemoSendKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall ListView1DblClick(TObject *Sender);
	void __fastcall ToolButton1Click(TObject *Sender);
	void __fastcall ListView1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall ListView1DragOver(TObject *Sender, TObject *Source, int X,
          int Y, TDragState State, bool &Accept);
	void __fastcall ListView1DragDrop(TObject *Sender, TObject *Source, int X,
          int Y);
	void __fastcall ShellListView1DragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept);
	void __fastcall ShellListView1DragDrop(TObject *Sender, TObject *Source,
          int X, int Y);
	void __fastcall ImageDblClick(TObject *Sender);
	void __fastcall TabControlMonitoringChange(TObject *Sender);
	void __fastcall TabControlMonitoringChanging(TObject *Sender,
          bool &AllowChange);
	void __fastcall TabSheet4Show(TObject *Sender);
	void __fastcall TabSheet4Hide(TObject *Sender);
	void __fastcall TabControlMaintenanceChange(TObject *Sender);
	void __fastcall TabControlMaintenanceChanging(TObject *Sender,
          bool &AllowChange);
	void __fastcall TabControlFileManagerChanging(TObject *Sender,
          bool &AllowChange);
	void __fastcall TabControlFileManagerChange(TObject *Sender);
	void __fastcall TabControlChatChanging(TObject *Sender,
          bool &AllowChange);
	void __fastcall TabControlChatChange(TObject *Sender);
	void __fastcall MemoCommandPromptKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall PageControlChanging(TObject *Sender, bool &AllowChange);
	void __fastcall PageControlChange(TObject *Sender);
	void __fastcall ACMWaveInData(Pointer data, int size);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall TabControlCommandPromptChange(TObject *Sender);
	void __fastcall TabControlCommandPromptChanging(TObject *Sender,
          bool &AllowChange);
	void __fastcall TabControlMessagesChange(TObject *Sender);
	void __fastcall TabControlMessagesChanging(TObject *Sender,
          bool &AllowChange);
	void __fastcall TabControlConferenceChange(TObject *Sender);
	void __fastcall TabControlConferenceChanging(TObject *Sender,
          bool &AllowChange);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
	void __fastcall CreateParams(Controls::TCreateParams &Params);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	void __fastcall DropFiles(HDROP hDrop);
public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);
	void __fastcall InitializeSoundIn();
	void __fastcall FinalizeSoundIn();
	void __fastcall InitializeSoundOut();
	void __fastcall FinalizeSoundOut();
	void __fastcall ClearTabs();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
