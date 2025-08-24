// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'TnScript.pas' rev: 6.00

#ifndef TnScriptHPP
#define TnScriptHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Controls.hpp>	// Pascal unit
#include <TnEmulVT.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Tnscript
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TnScriptException;
class PASCALIMPLEMENTATION TnScriptException : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall TnScriptException(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall TnScriptException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall TnScriptException(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall TnScriptException(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall TnScriptException(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall TnScriptException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall TnScriptException(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall TnScriptException(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TnScriptException(void) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TEventHandler)(System::TObject* Sender, int ID);

#pragma option push -b-
enum TEventFlag { efIgnoreCase, efPersistent };
#pragma option pop

typedef Set<TEventFlag, efIgnoreCase, efPersistent>  TEventFlags;

typedef void __fastcall (__closure *TDisplayEvent)(System::TObject* Sender, AnsiString Msg);

typedef void __fastcall (__closure *TStringMatch)(System::TObject* Sender, int ID);

struct TEventDescriptor
{
	int ID;
	AnsiString Search;
	AnsiString ToSend;
	TEventFlags Flags;
	TEventHandler Handler;
} ;

typedef TEventDescriptor *PEventDescriptor;

class DELPHICLASS TTnScript;
class PASCALIMPLEMENTATION TTnScript : public Tnemulvt::TTnEmulVT 
{
	typedef Tnemulvt::TTnEmulVT inherited;
	
protected:
	Classes::TList* FEventList;
	char *FInputBuffer;
	int FInputBufferSize;
	int FInputBufferCount;
	int FInputBufferStart;
	TDisplayEvent FOnDisplay;
	TStringMatch FOnStringMatch;
	virtual int __fastcall SearchEvent(int ID);
	virtual void __fastcall TriggerDataAvailable(char * Buffer, int Len);
	virtual int __fastcall FindEventString(AnsiString S, TEventFlags Flags);
	virtual void __fastcall ScanEvents(void);
	virtual void __fastcall ProcessInputData(char * Buffer, int Len);
	virtual void __fastcall TriggerDisplay(AnsiString Msg);
	virtual void __fastcall TriggerStringMatch(int ID);
	virtual void __fastcall NextOne(int &N);
	virtual void __fastcall SetInputBufferSize(int newSize);
	
public:
	__fastcall virtual TTnScript(Classes::TComponent* AOwner);
	__fastcall virtual ~TTnScript(void);
	virtual void __fastcall AddEvent(int ID, AnsiString Search, AnsiString ToSend, TEventFlags Flags, TEventHandler Handler);
	virtual void __fastcall RemoveEvent(int ID);
	virtual void __fastcall RemoveAllEvents(void);
	
__published:
	__property int InputBufferSize = {read=FInputBufferSize, write=SetInputBufferSize, nodefault};
	__property TDisplayEvent OnDisplay = {read=FOnDisplay, write=FOnDisplay};
	__property TStringMatch OnStringMatch = {read=FOnStringMatch, write=FOnStringMatch};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TTnScript(HWND ParentWindow) : Tnemulvt::TTnEmulVT(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
#define TnScriptVersion  (1.030000E+00)
extern PACKAGE AnsiString CopyRight;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Tnscript */
using namespace Tnscript;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// TnScript
