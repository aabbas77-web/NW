// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'RFormat.pas' rev: 6.00

#ifndef RFormatHPP
#define RFormatHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <DB.hpp>	// Pascal unit
#include <Variants.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Rformat
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS MWBufferException;
class PASCALIMPLEMENTATION MWBufferException : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall MWBufferException(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall MWBufferException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall MWBufferException(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall MWBufferException(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall MWBufferException(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall MWBufferException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall MWBufferException(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall MWBufferException(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~MWBufferException(void) { }
	#pragma option pop
	
};


typedef int *PInteger;

typedef int TPosition;

#pragma option push -b-
enum TMWFieldType { mwString, mwBlob };
#pragma option pop

class DELPHICLASS TMWBuffer;
typedef AnsiString __fastcall (*TMWBufferSortBuildKey)(TMWBuffer* MWBuffer);

class DELPHICLASS TMWBufferSortList;
class PASCALIMPLEMENTATION TMWBufferSortList : public Classes::TList 
{
	typedef Classes::TList inherited;
	
public:
	__fastcall virtual ~TMWBufferSortList(void);
	void __fastcall ClearList(void);
	void __fastcall AddKey(const AnsiString Key, const int Offset);
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TMWBufferSortList(void) : Classes::TList() { }
	#pragma option pop
	
};


#pragma pack(push, 4)
struct TMWBufferSortRec
{
	AnsiString Key;
	int Offset;
} ;
#pragma pack(pop)

typedef TMWBufferSortRec *PMWBufferSortRec;

class PASCALIMPLEMENTATION TMWBuffer : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	char *FDataBuffer;
	int FDataBufferSize;
	int FDataBufferCount;
	int FHeaderSize;
	int FFieldCount;
	int FRecordCount;
	char FFldSep;
	char FRecSep;
	char FEscSep;
	char *FRecordPointer;
	bool FHitEof;
	bool FHitBof;
	bool FHasData;
	bool FHasAllocated;
	int FAutoExpand;
	AnsiString FMetaDataLayout;
	
protected:
	void __fastcall RaiseException(const AnsiString Where);
	AnsiString __fastcall GetFields(int nIndex);
	TMWFieldType __fastcall GetFieldType(int nIndex);
	int __fastcall GetFieldCount(void);
	int __fastcall GetRecordCount(void);
	bool __fastcall GetEof(void);
	bool __fastcall GetBof(void);
	void __fastcall SetFields(int nIndex, AnsiString newValue);
	void __fastcall SetDataBufferSize(int newValue);
	void __fastcall SetDataBuffer(char * newValue);
	void __fastcall SetHasData(bool newValue);
	char * __fastcall GetFieldPtr(int nIndex);
	int __fastcall GetFieldSize(int nIndex);
	char * __fastcall GetNextFieldPtr(char * Cur);
	int __fastcall GetEscapedLength(char * Src, int Len);
	int __fastcall GetUnEscapedLength(char * p, char * q);
	void __fastcall MoveEscaped(const void *Source, void *Dest, int Count);
	AnsiString __fastcall GetMetaData(int nIndex, char Delim);
	char * __fastcall SkipMetaData(char * P, char * Q);
	
public:
	__fastcall virtual TMWBuffer(Classes::TComponent* AOwner);
	__fastcall virtual ~TMWBuffer(void);
	void __fastcall First(void);
	void __fastcall Next(void);
	void __fastcall Prior(void);
	void __fastcall Last(void);
	int __fastcall Tell(void);
	void __fastcall Seek(int nPos);
	virtual void * __fastcall GetBookmark(void);
	void __fastcall GotoBookmark(void * Bookmark);
	virtual void __fastcall FreeBookmark(void * Bookmark);
	AnsiString __fastcall RecordToString();
	int __fastcall StringToRecord(AnsiString Src, int &Start);
	void __fastcall StringToRecords(AnsiString Src);
	void __fastcall Rewrite(void);
	void __fastcall WriteRecord(const System::TVarRec * Args, const int Args_Size);
	void __fastcall WriteFields(bool NewRec, const System::TVarRec * Args, const int Args_Size);
	void __fastcall AppendFields(const System::TVarRec * Args, const int Args_Size);
	void __fastcall AppendRecord(TMWBuffer* From);
	void __fastcall WriteStreamField(bool NewRec, TMWFieldType FldType, Classes::TStream* Data);
	void __fastcall AppendStreamField(Classes::TStream* Data, TMWFieldType FldType);
	void __fastcall AppendBinaryField(void * Data, int Len, TMWFieldType FldType);
	int __fastcall GetStreamField(int FieldNb, Classes::TStream* Data, TMWFieldType &FieldType);
	void __fastcall Delete(void);
	bool __fastcall Locate(const AnsiString KeyFields, const Variant &KeyValues, Db::TLocateOptions Options);
	void __fastcall WriteRecordMarker(void);
	void __fastcall SaveToStream(Classes::TStream* Stream);
	void __fastcall LoadFromStream(Classes::TStream* Stream);
	void __fastcall SaveToFile(AnsiString FileName);
	void __fastcall LoadFromFile(AnsiString FileName);
	void __fastcall Sort(TMWBufferSortBuildKey BuildKey, bool Ascending);
	bool __fastcall IsValidFields(int nIndex);
	bool __fastcall ExpandBuffer(PInteger pSize, int Requested);
	void __fastcall WriteDataBuffer(char * Src, int Len);
	void __fastcall AppendMetaData(char Delim, char * Src, int Len);
	void __fastcall SetMetaDataLayout(const AnsiString Layout);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	__property AnsiString Fields[int nIndex] = {read=GetFields, write=SetFields};
	__property AnsiString MetaData[int nIndex][char Delim] = {read=GetMetaData};
	__property TMWFieldType FieldType[int nIndex] = {read=GetFieldType};
	__property int FieldSize[int nIndex] = {read=GetFieldSize};
	__property int FieldCount = {read=GetFieldCount, nodefault};
	__property int RecordCount = {read=GetRecordCount, nodefault};
	__property bool Eof = {read=GetEof, nodefault};
	__property bool Bof = {read=GetBof, nodefault};
	__property bool HasData = {read=FHasData, write=SetHasData, nodefault};
	__property char * DataBuffer = {read=FDataBuffer, write=SetDataBuffer};
	__property int DataBufferCount = {read=FDataBufferCount, write=FDataBufferCount, nodefault};
	
__published:
	__property int DataBufferSize = {read=FDataBufferSize, write=SetDataBufferSize, nodefault};
	__property int HeaderSize = {read=FHeaderSize, write=FHeaderSize, nodefault};
	__property int AutoExpand = {read=FAutoExpand, write=FAutoExpand, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
static const Byte MWBufferVersion = 0x83;
extern PACKAGE AnsiString CopyRight;
static const char FieldSeparator = '\x12';
static const char RecordSeparator = '\x14';
static const char EscMarker = '\x7f';
extern PACKAGE void __fastcall Register(void);
extern PACKAGE AnsiString __fastcall DateTimeToMWFormat(System::TDateTime DateTime);
extern PACKAGE System::TDateTime __fastcall DateTimeFromMWFormat(AnsiString Src);
extern PACKAGE AnsiString __fastcall TimeStampToMWFormat(const Sysutils::TTimeStamp &TimeStamp);
extern PACKAGE Sysutils::TTimeStamp __fastcall TimeStampFromMWFormat(AnsiString Src);
extern PACKAGE AnsiString __fastcall FloatToStrEx(Extended Value);

}	/* namespace Rformat */
using namespace Rformat;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// RFormat
