// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ACMWaveOut.pas' rev: 6.00

#ifndef ACMWaveOutHPP
#define ACMWaveOutHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <MMSystem.hpp>	// Pascal unit
#include <MSACM.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Acmwaveout
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TACMWaveOut;
class PASCALIMPLEMENTATION TACMWaveOut : public Controls::TWinControl 
{
	typedef Controls::TWinControl inherited;
	
private:
	MESSAGE void __fastcall WaveOutCallback(Messages::TMessage &msg);
	
protected:
	MESSAGE void __fastcall TWMPaint(Messages::TWMPaint &msg);
	
public:
	__fastcall virtual TACMWaveOut(Classes::TComponent* AOwner);
	void __fastcall Open(Mmsystem::PWaveFormatEx format);
	void __fastcall PlayBack(void * data, int size);
	void __fastcall Close(void);
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TACMWaveOut(HWND ParentWindow) : Controls::TWinControl(ParentWindow) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TWinControl.Destroy */ inline __fastcall virtual ~TACMWaveOut(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE int *HWaveOut1;
extern PACKAGE bool closed;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Acmwaveout */
using namespace Acmwaveout;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ACMWaveOut
