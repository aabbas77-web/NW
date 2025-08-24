// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DXReg.pas' rev: 5.00

#ifndef DXRegHPP
#define DXRegHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <DXClass.hpp>	// Pascal unit
#include <Wave.hpp>	// Pascal unit
#include <DXSounds.hpp>	// Pascal unit
#include <TypInfo.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <DsgnIntf.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Dxreg
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TWaveProperty;
class PASCALIMPLEMENTATION TWaveProperty : public Dsgnintf::TPropertyEditor 
{
	typedef Dsgnintf::TPropertyEditor inherited;
	
public:
	virtual void __fastcall Edit(void);
	virtual AnsiString __fastcall GetValue();
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TWaveProperty(const Dsgnintf::_di_IFormDesigner 
		ADesigner, int APropCount) : Dsgnintf::TPropertyEditor(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TWaveProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TDXWaveEditor;
class PASCALIMPLEMENTATION TDXWaveEditor : public Dsgnintf::TComponentEditor 
{
	typedef Dsgnintf::TComponentEditor inherited;
	
public:
	virtual void __fastcall Edit(void);
	virtual void __fastcall ExecuteVerb(int Index);
	virtual AnsiString __fastcall GetVerb(int Index);
	virtual int __fastcall GetVerbCount(void);
public:
	#pragma option push -w-inl
	/* TComponentEditor.Create */ inline __fastcall virtual TDXWaveEditor(Classes::TComponent* AComponent
		, Dsgnintf::_di_IFormDesigner ADesigner) : Dsgnintf::TComponentEditor(AComponent, ADesigner) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TDXWaveEditor(void) { }
	#pragma option pop
	
};


class DELPHICLASS TDXWaveListEditor;
class PASCALIMPLEMENTATION TDXWaveListEditor : public Dsgnintf::TComponentEditor 
{
	typedef Dsgnintf::TComponentEditor inherited;
	
public:
	virtual void __fastcall ExecuteVerb(int Index);
	virtual AnsiString __fastcall GetVerb(int Index);
	virtual int __fastcall GetVerbCount(void);
public:
	#pragma option push -w-inl
	/* TComponentEditor.Create */ inline __fastcall virtual TDXWaveListEditor(Classes::TComponent* AComponent
		, Dsgnintf::_di_IFormDesigner ADesigner) : Dsgnintf::TComponentEditor(AComponent, ADesigner) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TDXWaveListEditor(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Dxreg */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Dxreg;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DXReg
