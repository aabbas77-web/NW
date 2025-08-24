//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DXSounds"
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::DXSoundFinalize(TObject *Sender)
{
	if(Audio)	delete Audio;
    Audio = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormShow(TObject *Sender)
{
//  	ChangeStates();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FileOpenClick(TObject *Sender)
{
  	tWAVEFORMATEX WaveFormat;
  	if(!OpenDialog->Execute())	return;

  	FileCloseClick(NULL);
  	try
    {
    	Caption = Application->Title + " - " + ExtractFileName(OpenDialog->FileName);

    	DXSound->Initialize();

    	Audio = new TAudioFileStream(DXSound->DSound);
    	Audio->AutoUpdate = true;
    	Audio->BufferLength = 1000;
    	Audio->FileName = OpenDialog->FileName;
    	Audio->Looped = LoopCheckBox->Checked;

    	// Setting of format of primary buffer.
    	MakePCMWaveFormatEx(WaveFormat, 44100, Audio->Format->wBitsPerSample, 2);
    	DXSound->Primary->SetFormat(WaveFormat);

    	ChangeStates();

    	PlayButton->Enabled = true;
    	PauseButton->Enabled = false;
    	StopButton->Enabled = false;

    	LoopCheckBox->Enabled = true;
    	PanTrackBar->Enabled = true;
    	VolumeTrackBar->Enabled = true;
    	FrequencyTrackBar->Enabled = true;
    	ProgressTrackBar->Enabled = true;

    	FUpdating++;
    	try
        {
      		PanTrackBar->Position = Audio->Pan;
      		VolumeTrackBar->Position = Audio->Volume;
      		FrequencyTrackBar->Position = Audio->Frequency;
      		ProgressTrackBar->Max = Audio->Size;
      		ProgressTrackBar->PageSize = ProgressTrackBar->Max / 25;
        }
    	__finally
        {
      		FUpdating--;
    	}
	}
  	catch(...)
    {
    	FileCloseClick(NULL);
    	throw;
  	}
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FileCloseClick(TObject *Sender)
{
  Timer->Enabled = false;

  DXSound->Finalize();

  Caption = Application->Title;
             
  PlayButton->Enabled = false;
  PauseButton->Enabled = false;
  StopButton->Enabled = false;

  LoopCheckBox->Enabled = false;
  PanTrackBar->Enabled = false;
  VolumeTrackBar->Enabled = false;
  FrequencyTrackBar->Enabled = false;
  ProgressTrackBar->Enabled = false;

  ChangeStates();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FileEndClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PanTrackBarChange(TObject *Sender)
{
  if(FUpdating == 0 )
  {
    Audio->Pan = PanTrackBar->Position*100;
    ChangeStates();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::VolumeTrackBarChange(TObject *Sender)
{
  if(FUpdating == 0 )
  {
    Audio->Volume = VolumeTrackBar->Position*100;
    ChangeStates();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FrequencyTrackBarChange(TObject *Sender)
{
  if(FUpdating == 0 )
  {
    Audio->Frequency = FrequencyTrackBar->Position;
    ChangeStates();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::LoopCheckBoxClick(TObject *Sender)
{
  Audio->Looped = LoopCheckBox->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PlayButtonClick(TObject *Sender)
{
  Audio->Play();

  PlayButton->Enabled = false;
  PauseButton->Enabled = true;
  StopButton->Enabled = true;
  Timer->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PauseButtonClick(TObject *Sender)
{
  Audio->Stop();

  PlayButton->Enabled = true;
  PauseButton->Enabled = false;
  StopButton->Enabled = false;
  Timer->Enabled = false;

  ChangeStates();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::StopButtonClick(TObject *Sender)
{
  Audio->Stop();
  Audio->Position = 0;

  PlayButton->Enabled = true;
  PauseButton->Enabled = false;
  StopButton->Enabled = false;
  Timer->Enabled = false;

  ChangeStates();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TimerTimer(TObject *Sender)
{
  if(Audio->Playing)
    ChangeStates();
  else
  {
    Audio->Position = 0;
    StopButtonClick(NULL);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ChangeStates()
{
  int s;

  if(Audio != NULL)
  {
    s = (Audio->Position / Audio->Format->nBlockAlign) / int(Audio->Format->nSamplesPerSec);

    PanLabel->Caption = FormatFloat("Pan: 0 dB", Audio->Pan / 100);
    VolumeLabel->Caption = FormatFloat("Volume: 0 dB", Audio->Volume / 100);
    FrequencyLabel->Caption = FormatFloat("Frequency: 0 Hz", Audio->Frequency);
    ProgressLabel->Caption = 	FormatFloat("Time: 0.00:",(s / 60) / 60)+
    							FormatFloat(" 0.00:",(s / 60) % 60)+
    							FormatFloat(" 0.00",s % 60);

    FUpdating++;
    try
    {
      ProgressTrackBar->Position = Audio->Position;
    }
    __finally
    {
      FUpdating--;
    }

    BytesLabel->Caption = FormatFloat("0 Bytes", Audio->Position);
  }
  else
  {
    PanLabel->Caption = "Pan";
    VolumeLabel->Caption = "Volume";
    FrequencyLabel->Caption = "Frequency";
    ProgressLabel->Caption = "Time";
    BytesLabel->Caption = "Bytes";
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ProgressTrackBarChange(TObject *Sender)
{
  if(FUpdating == 0 )
  {
    Audio->Position = ProgressTrackBar->Position;
    ChangeStates();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::GlobalFocusItemClick(TObject *Sender)
{
  GlobalFocusItem->Checked = ! GlobalFocusItem->Checked;

  if(GlobalFocusItem->Checked)
    DXSound->Options = TDXSoundOptions() << soGlobalFocus;
  else
    DXSound->Options = TDXSoundOptions();

  if(Audio != NULL)
  {
    //  Buffer re-making
    Audio->RecreateBuf();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
	FileCloseClick(NULL);
}
//---------------------------------------------------------------------------

