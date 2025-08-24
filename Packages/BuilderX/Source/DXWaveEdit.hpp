// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DXWaveEdit.pas' rev: 5.00

#ifndef DXWaveEditHPP
#define DXWaveEditHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Graphics.hpp>	// Pascal unit
#include <Wave.hpp>	// Pascal unit
#include <DXSounds.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Dxwaveedit
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TDelphiXWaveEditForm;
class PASCALIMPLEMENTATION TDelphiXWaveEditForm : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Extctrls::TBevel* Bevel2;
	Stdctrls::TButton* OKButton;
	Stdctrls::TButton* CancelButton;
	Dialogs::TSaveDialog* SaveDialog;
	Dialogs::TOpenDialog* OpenDialog;
	Extctrls::TImage* PlayImage;
	Extctrls::TImage* StopImage;
	Extctrls::TTimer* Timer;
	Dxsounds::TDXSound* DXSound;
	Stdctrls::TButton* ClearButton;
	Stdctrls::TButton* SaveButton;
	Stdctrls::TButton* LoadButton;
	Extctrls::TPanel* Panel1;
	Comctrls::TTrackBar* TrackBar;
	Buttons::TSpeedButton* TestButton;
	Stdctrls::TLabel* LengthLabel;
	Stdctrls::TLabel* FrequencyLabel;
	Stdctrls::TLabel* TypeLabel;
	Stdctrls::TLabel* SizeLabel;
	Stdctrls::TLabel* LengthValueLabel;
	Stdctrls::TLabel* FrequencyValueLabel;
	Stdctrls::TLabel* TypeValueLabel;
	Stdctrls::TLabel* SizeValueLabel;
	void __fastcall OKButtonClick(System::TObject* Sender);
	void __fastcall CancelButtonClick(System::TObject* Sender);
	void __fastcall LoadButtonClick(System::TObject* Sender);
	void __fastcall SaveButtonClick(System::TObject* Sender);
	void __fastcall ClearButtonClick(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall DXSoundInitialize(System::TObject* Sender);
	void __fastcall DXSoundFinalize(System::TObject* Sender);
	void __fastcall TestButtonClick(System::TObject* Sender);
	void __fastcall TimerTimer(System::TObject* Sender);
	void __fastcall TrackBarChange(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	
private:
	bool FChanged;
	Dxsounds::TAudioStream* FAudio;
	bool FPlaying;
	Wave::TCustomWaveStream* FWaveStream;
	AnsiString FWaveFileName;
	bool FUpdating;
	void __fastcall UpDateData(void);
	void __fastcall SetPlaying(bool Value);
	__property bool Playing = {read=FPlaying, write=SetPlaying, nodefault};
	
public:
	Wave::TWave* Wave;
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TDelphiXWaveEditForm(Classes::TComponent* AOwner
		) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TDelphiXWaveEditForm(Classes::TComponent* AOwner
		, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TDelphiXWaveEditForm(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TDelphiXWaveEditForm(HWND ParentWindow) : Forms::TForm(
		ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TDelphiXWaveEditForm* DelphiXWaveEditForm;

}	/* namespace Dxwaveedit */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Dxwaveedit;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DXWaveEdit
