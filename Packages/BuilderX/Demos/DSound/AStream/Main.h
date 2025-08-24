//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DXSounds.hpp"
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TLabel *PanLabel;
	TLabel *VolumeLabel;
	TLabel *FrequencyLabel;
	TLabel *ProgressLabel;
	TBevel *Bevel1;
	TLabel *BytesLabel;
	TButton *PlayButton;
	TTrackBar *PanTrackBar;
	TCheckBox *LoopCheckBox;
	TTrackBar *VolumeTrackBar;
	TTrackBar *FrequencyTrackBar;
	TTrackBar *ProgressTrackBar;
	TButton *StopButton;
	TButton *PauseButton;
	TDXSound *DXSound;
	TTimer *Timer;
	TMainMenu *MainMenu1;
	TMenuItem *FileMenu;
	TMenuItem *FileOpen;
	TMenuItem *FileClose;
	TMenuItem *N1;
	TMenuItem *FileEnd;
	TMenuItem *O1;
	TMenuItem *GlobalFocusItem;
	TOpenDialog *OpenDialog;
	void __fastcall DXSoundFinalize(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FileOpenClick(TObject *Sender);
	void __fastcall FileCloseClick(TObject *Sender);
	void __fastcall FileEndClick(TObject *Sender);
	void __fastcall PanTrackBarChange(TObject *Sender);
	void __fastcall VolumeTrackBarChange(TObject *Sender);
	void __fastcall FrequencyTrackBarChange(TObject *Sender);
	void __fastcall LoopCheckBoxClick(TObject *Sender);
	void __fastcall PlayButtonClick(TObject *Sender);
	void __fastcall PauseButtonClick(TObject *Sender);
	void __fastcall StopButtonClick(TObject *Sender);
	void __fastcall TimerTimer(TObject *Sender);
	void __fastcall ProgressTrackBarChange(TObject *Sender);
	void __fastcall GlobalFocusItemClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);
	void __fastcall ChangeStates();
    int FUpdating;
    TAudioFileStream *Audio;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
