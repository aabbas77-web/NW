// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DXClass.pas' rev: 5.00

#ifndef DXClassHPP
#define DXClassHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <DirectX.hpp>	// Pascal unit
#include <MMSystem.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Dxclass
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS EDirectXError;
class PASCALIMPLEMENTATION EDirectXError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EDirectXError(const AnsiString Msg) : Sysutils::Exception(
		Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EDirectXError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EDirectXError(int Ident)/* overload */ : Sysutils::Exception(
		Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EDirectXError(int Ident, const System::TVarRec * Args
		, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EDirectXError(const AnsiString Msg, int AHelpContext) : 
		Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EDirectXError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EDirectXError(int Ident, int AHelpContext)/* overload */
		 : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EDirectXError(System::PResStringRec ResStringRec
		, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(
		ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EDirectXError(void) { }
	#pragma option pop
	
};


class DELPHICLASS TDirectX;
class PASCALIMPLEMENTATION TDirectX : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	void __fastcall SetDXResult(HRESULT Value);
	
protected:
	HRESULT FDXResult;
	virtual void __fastcall Check(void);
	
public:
	__property HRESULT DXResult = {read=FDXResult, write=SetDXResult, nodefault};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TDirectX(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TDirectX(void) : Classes::TPersistent() { }
	#pragma option pop
	
};


class DELPHICLASS TDirectXDriver;
class PASCALIMPLEMENTATION TDirectXDriver : public Classes::TCollectionItem 
{
	typedef Classes::TCollectionItem inherited;
	
private:
	GUID *FGUID;
	#pragma pack(push, 1)
	GUID FGUID2;
	#pragma pack(pop)
	
	AnsiString FDescription;
	AnsiString FDriverName;
	void __fastcall SetGUID(System::PGUID Value);
	
public:
	__property System::PGUID GUID = {read=FGUID, write=SetGUID};
	__property AnsiString Description = {read=FDescription, write=FDescription};
	__property AnsiString DriverName = {read=FDriverName, write=FDriverName};
public:
	#pragma option push -w-inl
	/* TCollectionItem.Create */ inline __fastcall virtual TDirectXDriver(Classes::TCollection* Collection
		) : Classes::TCollectionItem(Collection) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TDirectXDriver(void) { }
	#pragma option pop
	
};


class DELPHICLASS TDirectXDrivers;
class PASCALIMPLEMENTATION TDirectXDrivers : public Classes::TCollection 
{
	typedef Classes::TCollection inherited;
	
private:
	TDirectXDriver* __fastcall GetDriver(int Index);
	
public:
	__fastcall TDirectXDrivers(void);
	__property TDirectXDriver* Drivers[int Index] = {read=GetDriver/*, default*/};
public:
	#pragma option push -w-inl
	/* TCollection.Destroy */ inline __fastcall virtual ~TDirectXDrivers(void) { }
	#pragma option pop
	
};


class DELPHICLASS TDXForm;
class PASCALIMPLEMENTATION TDXForm : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
private:
	bool FStoreWindow;
	#pragma pack(push, 1)
	tagWINDOWPLACEMENT FWindowPlacement;
	#pragma pack(pop)
	
	HIDESBASE MESSAGE void __fastcall WMSYSCommand(Messages::TWMSysCommand &Msg);
	
protected:
	virtual void __fastcall CreateParams(Controls::TCreateParams &Params);
	
public:
	__fastcall virtual TDXForm(Classes::TComponent* AOnwer);
	__fastcall virtual ~TDXForm(void);
	void __fastcall RestoreWindow(void);
	void __fastcall StoreWindow(void);
public:
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TDXForm(Classes::TComponent* AOwner, int Dummy
		) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TDXForm(HWND ParentWindow) : Forms::TForm(ParentWindow
		) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TDXTimerEvent)(System::TObject* Sender, int LagCount);

class DELPHICLASS TCustomDXTimer;
class PASCALIMPLEMENTATION TCustomDXTimer : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	bool FActiveOnly;
	bool FEnabled;
	int FFrameRate;
	bool FInitialized;
	unsigned FInterval;
	unsigned FInterval2;
	int FNowFrameRate;
	unsigned FOldTime;
	unsigned FOldTime2;
	Classes::TNotifyEvent FOnActivate;
	Classes::TNotifyEvent FOnDeactivate;
	TDXTimerEvent FOnTimer;
	void __fastcall AppIdle(System::TObject* Sender, bool &Done);
	bool __fastcall AppProc(Messages::TMessage &Message);
	void __fastcall Finalize(void);
	void __fastcall Initialize(void);
	void __fastcall Resume(void);
	void __fastcall SetActiveOnly(bool Value);
	void __fastcall SetEnabled(bool Value);
	void __fastcall SetInterval(unsigned Value);
	void __fastcall Suspend(void);
	
protected:
	virtual void __fastcall DoActivate(void);
	virtual void __fastcall DoDeactivate(void);
	virtual void __fastcall DoTimer(int LagCount);
	virtual void __fastcall Loaded(void);
	
public:
	__fastcall virtual TCustomDXTimer(Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomDXTimer(void);
	__property bool ActiveOnly = {read=FActiveOnly, write=SetActiveOnly, nodefault};
	__property bool Enabled = {read=FEnabled, write=SetEnabled, nodefault};
	__property int FrameRate = {read=FFrameRate, nodefault};
	__property unsigned Interval = {read=FInterval, write=SetInterval, nodefault};
	__property Classes::TNotifyEvent OnActivate = {read=FOnActivate, write=FOnActivate};
	__property Classes::TNotifyEvent OnDeactivate = {read=FOnDeactivate, write=FOnDeactivate};
	__property TDXTimerEvent OnTimer = {read=FOnTimer, write=FOnTimer};
};


class DELPHICLASS TDXTimer;
class PASCALIMPLEMENTATION TDXTimer : public TCustomDXTimer 
{
	typedef TCustomDXTimer inherited;
	
__published:
	__property ActiveOnly ;
	__property Enabled ;
	__property Interval ;
	__property OnActivate ;
	__property OnDeactivate ;
	__property OnTimer ;
public:
	#pragma option push -w-inl
	/* TCustomDXTimer.Create */ inline __fastcall virtual TDXTimer(Classes::TComponent* AOwner) : TCustomDXTimer(
		AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomDXTimer.Destroy */ inline __fastcall virtual ~TDXTimer(void) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TControlSubClassProc)(Messages::TMessage &Message, Controls::TWndMethod 
	DefWindowProc);

class DELPHICLASS TControlSubClass;
class PASCALIMPLEMENTATION TControlSubClass : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	Controls::TControl* FControl;
	Controls::TWndMethod FDefWindowProc;
	TControlSubClassProc FWindowProc;
	void __fastcall WndProc(Messages::TMessage &Message);
	
public:
	__fastcall TControlSubClass(Controls::TControl* Control, TControlSubClassProc WindowProc);
	__fastcall virtual ~TControlSubClass(void);
};


class DELPHICLASS THashCollectionItem;
class PASCALIMPLEMENTATION THashCollectionItem : public Classes::TCollectionItem 
{
	typedef Classes::TCollectionItem inherited;
	
private:
	int FHashCode;
	int FIndex;
	AnsiString FName;
	THashCollectionItem* FLeft;
	THashCollectionItem* FRight;
	void __fastcall SetName(const AnsiString Value);
	void __fastcall AddHash(void);
	void __fastcall DeleteHash(void);
	
protected:
	virtual AnsiString __fastcall GetDisplayName();
	virtual void __fastcall SetIndex(int Value);
	
public:
	__fastcall virtual THashCollectionItem(Classes::TCollection* Collection);
	__fastcall virtual ~THashCollectionItem(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	__property int Index = {read=FIndex, write=SetIndex, nodefault};
	
__published:
	__property AnsiString Name = {read=FName, write=SetName};
};


class DELPHICLASS THashCollection;
class PASCALIMPLEMENTATION THashCollection : public Classes::TCollection 
{
	typedef Classes::TCollection inherited;
	
private:
	THashCollectionItem* FHash[256];
	
public:
	int __fastcall IndexOf(const AnsiString Name);
public:
	#pragma option push -w-inl
	/* TCollection.Create */ inline __fastcall THashCollection(TMetaClass* ItemClass) : Classes::TCollection(
		ItemClass) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCollection.Destroy */ inline __fastcall virtual ~THashCollection(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE int __fastcall Max(int Val1, int Val2);
extern PACKAGE int __fastcall Min(int Val1, int Val2);
extern PACKAGE bool __fastcall PointInRect(const Windows::TPoint &Point, const Windows::TRect &Rect)
	;
extern PACKAGE bool __fastcall RectInRect(const Windows::TRect &Rect1, const Windows::TRect &Rect2);
	
extern PACKAGE bool __fastcall OverlapRect(const Windows::TRect &Rect1, const Windows::TRect &Rect2)
	;
extern PACKAGE Windows::TRect __fastcall WideRect(int ALeft, int ATop, int AWidth, int AHeight);
extern PACKAGE double __fastcall Cos256(int i);
extern PACKAGE double __fastcall Sin256(int i);
extern PACKAGE void __fastcall ReleaseCom(/* out */ void *Com);
extern PACKAGE void * __fastcall DXLoadLibrary(const AnsiString FileName, const AnsiString FuncName)
	;

}	/* namespace Dxclass */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Dxclass;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DXClass
