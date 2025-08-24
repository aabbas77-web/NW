// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'RBroker.pas' rev: 6.00

#ifndef RBrokerHPP
#define RBrokerHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <RFormat.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Rbroker
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS ERequestBrokerException;
class PASCALIMPLEMENTATION ERequestBrokerException : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ERequestBrokerException(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ERequestBrokerException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ERequestBrokerException(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ERequestBrokerException(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ERequestBrokerException(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ERequestBrokerException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ERequestBrokerException(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ERequestBrokerException(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ERequestBrokerException(void) { }
	#pragma option pop
	
};


typedef TMetaClass*TServerObjectClass;

#pragma option push -b-
enum TRequestBrokerOption { rboDisplayObjectCount };
#pragma option pop

typedef Set<TRequestBrokerOption, rboDisplayObjectCount, rboDisplayObjectCount>  TRequestBrokerOptions;

typedef void __fastcall (__closure *TDisplayEvent)(System::TObject* Sender, AnsiString Msg);

class DELPHICLASS TRequestBroker;
typedef void __fastcall (__closure *TSendResponseToClient)(System::TObject* Dest, TRequestBroker* ORB, int Status, char * Response, int Len);

struct TORBData
{
	TSendResponseToClient SendResp;
	System::TObject* Tag;
	int Item;
	TRequestBroker* ORB;
	System::TObject* AppServer;
} ;

typedef TORBData *PORBData;

class DELPHICLASS TServerObject;
class PASCALIMPLEMENTATION TServerObject : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
protected:
	AnsiString FFunctionCode;
	Rformat::TMWBuffer* FRequestBuffer;
	Rformat::TMWBuffer* FResponseBuffer;
	int FResponseSize;
	int FResultStatus;
	int FUserData;
	AnsiString FIniFileName;
	TORBData *FORBDataPtr;
	TRequestBroker* FRequestBroker;
	TMetaClass*FServerObjectClass;
	Classes::TNotifyEvent FOnRequestDone;
	TDisplayEvent FOnDisplay;
	virtual void __fastcall TriggerDisplay(AnsiString Msg);
	virtual void __fastcall BuildFunctionCode(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation operation);
	virtual void __fastcall CopyFromReference(TServerObject* Reference);
	__fastcall virtual TServerObject(Classes::TComponent* AOwner, int Dummy);
	
public:
	__fastcall virtual TServerObject(Classes::TComponent* AOwner);
	__fastcall virtual ~TServerObject(void);
	virtual void __fastcall GiveRequest(char * RqBuffer, int RqLength);
	virtual void __fastcall Initialize(void);
	virtual void __fastcall Execute(void);
	virtual void __fastcall Finish(void);
	__property int UserData = {read=FUserData, write=FUserData, nodefault};
	__property int ResultStatus = {read=FResultStatus, write=FResultStatus, nodefault};
	__property PORBData ORBDataPtr = {read=FORBDataPtr, write=FORBDataPtr};
	
__published:
	__property TRequestBroker* RequestBroker = {read=FRequestBroker, write=FRequestBroker};
};


class DELPHICLASS TServerObjectUNKNOWN;
class PASCALIMPLEMENTATION TServerObjectUNKNOWN : public TServerObject 
{
	typedef TServerObject inherited;
	
private:
	AnsiString FFunctionCode;
	
public:
	__fastcall virtual TServerObjectUNKNOWN(Classes::TComponent* AOwner, AnsiString FunctionCode);
	virtual void __fastcall Execute(void);
protected:
	#pragma option push -w-inl
	/* TServerObject.CreateForFunctionCode */ inline __fastcall virtual TServerObjectUNKNOWN(Classes::TComponent* AOwner, int Dummy) : TServerObject(AOwner, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TServerObject.Create */ inline __fastcall virtual TServerObjectUNKNOWN(Classes::TComponent* AOwner) : TServerObject(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TServerObject.Destroy */ inline __fastcall virtual ~TServerObjectUNKNOWN(void) { }
	#pragma option pop
	
};


#pragma pack(push, 4)
struct TDispatchObject
{
	AnsiString FunctionCode;
	bool Initialized;
	TMetaClass*ServerObject;
	TServerObject* Reference;
} ;
#pragma pack(pop)

typedef TDispatchObject *PDispatchObject;

typedef void __fastcall (__closure *TInstanciationEvent)(System::TObject* Sender, TServerObject* ServerObject);

typedef bool __fastcall (__closure *TEnumServerFunctions)(System::TObject* Sender, AnsiString FunctionCode);

class PASCALIMPLEMENTATION TRequestBroker : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
protected:
	TRequestBrokerOptions FOptions;
	Stdctrls::TCustomMemo* FDisplayMemo;
	Stdctrls::TLabel* FObjectCountLabel;
	Classes::TList* FObjectList;
	Classes::TList* FRunningList;
	int FObjectCount;
	int FUserData;
	AnsiString FIniFileName;
	TDisplayEvent FOnDisplay;
	TInstanciationEvent FOnObjCreate;
	TInstanciationEvent FOnObjDestroy;
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation operation);
	int __fastcall FindServerObject(AnsiString FunctionCode);
	int __fastcall RemoveServerObject(AnsiString FunctionCode);
	void __fastcall ServerObjectRequestDone(System::TObject* Sender);
	virtual void __fastcall CrackHeader(char * RqBuffer, int RqLength, System::TObject* Tag, AnsiString &FunctionCode, char * &ParamPtr, int &ParamLen);
	virtual void __fastcall TriggerObjCreate(TServerObject* ServerObject);
	virtual void __fastcall TriggerObjDestroy(TServerObject* ServerObject);
	void __fastcall InternalDisplay(System::TObject* Sender, AnsiString Msg);
	virtual void __fastcall Loaded(void);
	bool __fastcall RemoveRunningObject(TServerObject* ServerObject);
	
public:
	__fastcall virtual TRequestBroker(Classes::TComponent* AOwner);
	__fastcall virtual ~TRequestBroker(void);
	void __fastcall AddServerObject(TMetaClass* ServerObjectClass);
	void __fastcall AddServerObjectWithReference(TMetaClass* ServerObjectClass, TServerObject* ServerObjectInstance);
	void __fastcall EnumServerFunctions(TEnumServerFunctions CallBack);
	void __fastcall BrokeRequest(System::TObject* Sender, char * RqBuffer, int RqLength, System::TObject* Tag, TSendResponseToClient SendResp);
	__property int ObjectCount = {read=FObjectCount, nodefault};
	
__published:
	__property int UserData = {read=FUserData, write=FUserData, nodefault};
	__property AnsiString IniFileName = {read=FIniFileName, write=FIniFileName};
	__property Stdctrls::TLabel* ObjectCountLabel = {read=FObjectCountLabel, write=FObjectCountLabel};
	__property TRequestBrokerOptions Options = {read=FOptions, write=FOptions, nodefault};
	__property Stdctrls::TCustomMemo* DisplayMemo = {read=FDisplayMemo, write=FDisplayMemo};
	__property TDisplayEvent OnDisplay = {read=FOnDisplay, write=FOnDisplay};
	__property TInstanciationEvent OnObjCreate = {read=FOnObjCreate, write=FOnObjCreate};
	__property TInstanciationEvent OnObjDestroy = {read=FOnObjDestroy, write=FOnObjDestroy};
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint RBrokerVersion = 0x6e;
extern PACKAGE AnsiString CopyRight;
static const Shortint ServerObjectVersion = 0x6e;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Rbroker */
using namespace Rbroker;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// RBroker
