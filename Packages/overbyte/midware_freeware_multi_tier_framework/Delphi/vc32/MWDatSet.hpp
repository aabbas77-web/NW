// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'MwDatSet.pas' rev: 6.00

#ifndef MwDatSetHPP
#define MwDatSetHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ApsCli.hpp>	// Pascal unit
#include <RFormat.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <DBConsts.hpp>	// Pascal unit
#include <DB.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Mwdatset
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS EMWDataSetException;
class PASCALIMPLEMENTATION EMWDataSetException : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EMWDataSetException(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EMWDataSetException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EMWDataSetException(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EMWDataSetException(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EMWDataSetException(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EMWDataSetException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EMWDataSetException(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EMWDataSetException(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EMWDataSetException(void) { }
	#pragma option pop
	
};


typedef int TPosition;

typedef AnsiString TFieldLayout;

typedef AnsiString TRequestParams;

#pragma pack(push, 4)
struct TFieldData
{
	int FldOffset;
	AnsiString FldName;
	Db::TFieldType FldType;
	int FldLen;
	int FldSize;
} ;
#pragma pack(pop)

typedef TFieldData *PFieldData;

typedef int TBookmarkInfo;

struct TExtraRecInfo;
typedef TExtraRecInfo *PExtraRecInfo;

#pragma pack(push, 1)
struct TExtraRecInfo
{
	Db::TBookmarkFlag BookmarkFlag;
} ;
#pragma pack(pop)

typedef void __fastcall (__closure *TDisplayInfo)(System::TObject* Sender, const AnsiString Msg);

class DELPHICLASS TMWDataSet;
class PASCALIMPLEMENTATION TMWDataSet : public Db::TDataSet 
{
	typedef Db::TDataSet inherited;
	
private:
	int FBookmarkOffset;
	Word FCalcFieldsOffset;
	Word FExtraRecInfoOffset;
	bool FCursorOpen;
	int FInternalCurrent;
	Word FRecSize;
	Word FRecBufSize;
	Rformat::TMWBuffer* FData;
	AnsiString FFieldLayout;
	Classes::TList* FFieldData;
	int FMWBufferFieldCount;
	TDisplayInfo FOnDisplayInfo;
	
protected:
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	virtual char * __fastcall AllocRecordBuffer(void);
	virtual void __fastcall FreeRecordBuffer(char * &Buffer);
	virtual Db::TGetResult __fastcall GetRecord(char * Buffer, Db::TGetMode GetMode, bool DoCheck);
	virtual Word __fastcall GetRecordSize(void);
	virtual void __fastcall InternalClose(void);
	virtual void __fastcall InternalFirst(void);
	virtual void __fastcall InternalLast(void);
	virtual void __fastcall InternalOpen(void);
	virtual void __fastcall InternalRefresh(void);
	virtual bool __fastcall IsCursorOpen(void);
	virtual void __fastcall GetBookmarkData(char * Buffer, void * Data);
	virtual Db::TBookmarkFlag __fastcall GetBookmarkFlag(char * Buffer);
	virtual void __fastcall SetBookmarkData(char * Buffer, void * Data);
	virtual void __fastcall SetBookmarkFlag(char * Buffer, Db::TBookmarkFlag Value);
	virtual void __fastcall InternalGotoBookmark(void * Bookmark);
	virtual void __fastcall InternalSetToRecord(char * Buffer);
	virtual void __fastcall InternalInitRecord(char * Buffer);
	virtual void __fastcall InternalEdit(void);
	virtual void __fastcall InternalDelete(void);
	virtual void __fastcall InternalPost(void);
	virtual void __fastcall InternalInitFieldDefs(void);
	virtual void __fastcall SetFieldData(Db::TField* Field, void * Buffer)/* overload */;
	virtual void __fastcall InternalAddRecord(void * Buffer, bool Append);
	virtual void __fastcall ClearCalcFields(char * Buffer);
	virtual bool __fastcall FindRecord(bool Restart, bool GoForward);
	virtual int __fastcall GetRecordCount(void);
	virtual int __fastcall GetRecNo(void);
	virtual void __fastcall SetRecNo(int Value);
	void __fastcall CopyFromCurrentRecord(char * Dst);
	void __fastcall CopyToCurrentRecord(char * Src);
	void __fastcall AppendData(char * Src);
	AnsiString __fastcall TellText();
	virtual void __fastcall CloseBlob(Db::TField* Field);
	void __fastcall FreeBlobBuffer(char * Buffer);
	
public:
	virtual bool __fastcall IsSequenced(void);
	virtual bool __fastcall GetCurrentRecord(char * Buffer);
	virtual Classes::TStream* __fastcall CreateBlobStream(Db::TField* Field, Db::TBlobStreamMode Mode);
	virtual bool __fastcall BookmarkValid(void * Bookmark);
	virtual int __fastcall CompareBookmarks(void * Bookmark1, void * Bookmark2);
	virtual bool __fastcall GetFieldData(Db::TField* Field, void * Buffer)/* overload */;
	virtual bool __fastcall Locate(const AnsiString KeyFields, const Variant &KeyValues, Db::TLocateOptions Options);
	virtual Variant __fastcall Lookup(const AnsiString KeyFields, const Variant &KeyValues, const AnsiString ResultFields);
	
protected:
	char *FBufferFromInternalSetToRecord;
	int __fastcall GetFieldOffset(int FieldNo);
	int __fastcall GetFieldLen(int FieldNo);
	Db::TFieldType __fastcall GetFieldType(int FieldNo);
	virtual void __fastcall TriggerDisplayInfo(const AnsiString Msg);
	void __fastcall SetFieldLayout(AnsiString newValue);
	
public:
	__fastcall virtual TMWDataSet(Classes::TComponent* AOwner);
	__fastcall virtual ~TMWDataSet(void);
	__property Rformat::TMWBuffer* Data = {read=FData, write=FData};
	__property AnsiString FieldLayout = {read=FFieldLayout, write=SetFieldLayout};
	__property int MWBufferFieldCount = {read=FMWBufferFieldCount, nodefault};
	__property Word RecordSize = {read=GetRecordSize, nodefault};
	__property TDisplayInfo OnDisplayInfo = {read=FOnDisplayInfo, write=FOnDisplayInfo};
	
/* Hoisted overloads: */
	
protected:
	inline void __fastcall  SetFieldData(Db::TField* Field, void * Buffer, bool NativeFormat){ TDataSet::SetFieldData(Field, Buffer, NativeFormat); }
	
public:
	inline bool __fastcall  GetFieldData(int FieldNo, void * Buffer){ return TDataSet::GetFieldData(FieldNo, Buffer); }
	inline bool __fastcall  GetFieldData(Db::TField* Field, void * Buffer, bool NativeFormat){ return TDataSet::GetFieldData(Field, Buffer, NativeFormat); }
	
};


class DELPHICLASS TMWCustomTable;
class PASCALIMPLEMENTATION TMWCustomTable : public TMWDataSet 
{
	typedef TMWDataSet inherited;
	
private:
	bool FReadOnly;
	AnsiString FParams;
	AnsiString FFunctionCode;
	Apscli::TAppSrvClient* FAppSrvClient;
	bool FRequestDoneFlag;
	int FRequestError;
	int FTimeout;
	bool FBusy;
	Apscli::TRequestDone FOnRequestDone;
	
protected:
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	virtual bool __fastcall GetCanModify(void);
	virtual void __fastcall InternalOpen(void);
	virtual void __fastcall AppSrvClientRequestDone(System::TObject* Sender, int Error);
	virtual void __fastcall AppSrvClientExecuteRequestDone(System::TObject* Sender, int Error);
	void __fastcall SetFunctionCode(AnsiString newValue);
	void __fastcall SetParams(AnsiString newValue);
	void __fastcall SetAppSrvClient(Apscli::TAppSrvClient* newValue);
	void __fastcall SetTimeout(int newValue);
	virtual void __fastcall SendRequest(void);
	virtual void __fastcall TriggerRequestDone(int Error);
	
public:
	__fastcall virtual TMWCustomTable(Classes::TComponent* AOwner);
	virtual void __fastcall DesignTimeRequest(void);
	virtual void __fastcall ExecuteRequest(void);
	__property bool CanModify = {read=GetCanModify, nodefault};
	__property Apscli::TRequestDone OnRequestDone = {read=FOnRequestDone, write=FOnRequestDone};
	__property Data ;
	__property FieldLayout ;
	__property bool ReadOnly = {read=FReadOnly, write=FReadOnly, nodefault};
	__property AnsiString FunctionCode = {read=FFunctionCode, write=SetFunctionCode};
	__property AnsiString Params = {read=FParams, write=SetParams};
	__property Apscli::TAppSrvClient* AppSrvClient = {read=FAppSrvClient, write=SetAppSrvClient};
	__property int Timeout = {read=FTimeout, write=SetTimeout, nodefault};
public:
	#pragma option push -w-inl
	/* TMWDataSet.Destroy */ inline __fastcall virtual ~TMWCustomTable(void) { }
	#pragma option pop
	
};


class DELPHICLASS TMWTable;
class PASCALIMPLEMENTATION TMWTable : public TMWCustomTable 
{
	typedef TMWCustomTable inherited;
	
__published:
	__property Active  = {default=0};
	__property AutoCalcFields  = {default=1};
	__property BeforeOpen ;
	__property AfterOpen ;
	__property BeforeClose ;
	__property AfterClose ;
	__property BeforeInsert ;
	__property AfterInsert ;
	__property BeforeEdit ;
	__property AfterEdit ;
	__property BeforePost ;
	__property AfterPost ;
	__property BeforeCancel ;
	__property AfterCancel ;
	__property BeforeDelete ;
	__property AfterDelete ;
	__property BeforeScroll ;
	__property AfterScroll ;
	__property OnCalcFields ;
	__property OnDeleteError ;
	__property OnEditError ;
	__property OnNewRecord ;
	__property OnPostError ;
	__property OnDisplayInfo ;
	__property OnRequestDone ;
	__property Data ;
	__property FieldLayout ;
	__property ReadOnly ;
	__property FunctionCode ;
	__property Params ;
	__property AppSrvClient ;
	__property Timeout ;
public:
	#pragma option push -w-inl
	/* TMWCustomTable.Create */ inline __fastcall virtual TMWTable(Classes::TComponent* AOwner) : TMWCustomTable(AOwner) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TMWDataSet.Destroy */ inline __fastcall virtual ~TMWTable(void) { }
	#pragma option pop
	
};


class DELPHICLASS TMWBlobStream;
class PASCALIMPLEMENTATION TMWBlobStream : public Classes::TStream 
{
	typedef Classes::TStream inherited;
	
public:
	Db::TField* Field;
	TFieldData *pFldData;
	Db::TBlobStreamMode Mode;
	char *Buffer;
	__int64 FSize;
	int FCurPos;
	TMWDataSet* FData;
	bool FModified;
	__fastcall virtual ~TMWBlobStream(void);
	virtual int __fastcall Write(const void *Value, int Count);
	virtual int __fastcall Read(void *Value, int Count);
	virtual void __fastcall SetSize(int NewSize)/* overload */;
	HIDESBASE void __fastcall SetSize64(__int64 NewSize);
	HIDESBASE __int64 __fastcall GetSize(void);
	virtual int __fastcall Seek(int Offset, Word Origin)/* overload */;
	__property Size  = {read=GetSize, write=SetSize64};
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TMWBlobStream(void) : Classes::TStream() { }
	#pragma option pop
	
	
/* Hoisted overloads: */
	
protected:
	inline void __fastcall  SetSize(const __int64 NewSize){ TStream::SetSize(NewSize); }
	
public:
	inline __int64 __fastcall  Seek(const __int64 Offset, Classes::TSeekOrigin Origin){ return TStream::Seek(Offset, Origin); }
	
};


typedef AnsiString MwDatSet__6[13];

//-- var, const, procedure ---------------------------------------------------
static const Byte MWDataSetVersion = 0x82;
extern PACKAGE AnsiString CopyRight;
extern PACKAGE Db::TFieldType FieldTypesOrdinals[13];
extern PACKAGE AnsiString FieldTypesNames[13];
extern PACKAGE void __fastcall ClearFieldData(Classes::TList* FieldData);
extern PACKAGE AnsiString __fastcall FieldTypeToString(Db::TFieldType FieldType);
extern PACKAGE Db::TFieldType __fastcall StringToFieldType(AnsiString Token);
extern PACKAGE int __fastcall DecodeLayout(AnsiString Layout, Classes::TList* FieldData);
extern PACKAGE void __fastcall Register(void);

}	/* namespace Mwdatset */
using namespace Mwdatset;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// MwDatSet
