// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ACMWaveIn.pas' rev: 6.00

#ifndef ACMWaveInHPP
#define ACMWaveInHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <MMSystem.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <MSACM.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Acmwavein
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TOnData)(void * data, int size);

class DELPHICLASS TACMWaveIn;
class PASCALIMPLEMENTATION TACMWaveIn : public Controls::TWinControl 
{
	typedef Controls::TWinControl inherited;
	
private:
	TOnData FOnData;
	MESSAGE void __fastcall WaveInCallback(Messages::TMessage &msg);
	
protected:
	MESSAGE void __fastcall TWMPaint(Messages::TWMPaint &msg);
	
public:
	__fastcall virtual TACMWaveIn(Classes::TComponent* AOwner);
	void __fastcall Open(Mmsystem::PWaveFormatEx format);
	void __fastcall Close(void);
	
__published:
	__property TOnData OnData = {read=FOnData, write=FOnData};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TACMWaveIn(HWND ParentWindow) : Controls::TWinControl(ParentWindow) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TWinControl.Destroy */ inline __fastcall virtual ~TACMWaveIn(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE bool closed;
extern PACKAGE int sizebuf;
extern PACKAGE int *HWaveIn1;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Acmwavein */
using namespace Acmwavein;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ACMWaveIn
