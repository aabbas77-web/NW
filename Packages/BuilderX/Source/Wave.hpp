// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Wave.pas' rev: 5.00

#ifndef WaveHPP
#define WaveHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <MMSystem.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Wave
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS EWaveError;
class PASCALIMPLEMENTATION EWaveError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EWaveError(const AnsiString Msg) : Sysutils::Exception(Msg
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EWaveError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EWaveError(int Ident)/* overload */ : Sysutils::Exception(
		Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EWaveError(int Ident, const System::TVarRec * Args, 
		const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EWaveError(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(
		Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EWaveError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EWaveError(int Ident, int AHelpContext)/* overload */
		 : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EWaveError(System::PResStringRec ResStringRec, const 
		System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(
		ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EWaveError(void) { }
	#pragma option pop
	
};


class DELPHICLASS TWave;
class PASCALIMPLEMENTATION TWave : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	void *FData;
	tWAVEFORMATEX *FFormat;
	int FFormatSize;
	int FSize;
	void __fastcall SetFormatSize(int Value);
	void __fastcall SetSize(int Value);
	
protected:
	virtual void __fastcall DefineProperties(Classes::TFiler* Filer);
	virtual void __fastcall ReadData(Classes::TStream* Stream);
	virtual void __fastcall WriteData(Classes::TStream* Stream);
	
public:
	__fastcall virtual ~TWave(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	void __fastcall Clear(void);
	void __fastcall LoadFromFile(const AnsiString FileName);
	void __fastcall LoadFromStream(Classes::TStream* Stream);
	void __fastcall SaveToFile(const AnsiString FileName);
	void __fastcall SaveToStream(Classes::TStream* Stream);
	void __fastcall SetPCMFormat(int SamplesPerSec, int BitsPerSample, int Channels);
	__property void * Data = {read=FData};
	__property Mmsystem::PWaveFormatEx Format = {read=FFormat};
	__property int FormatSize = {read=FFormatSize, write=SetFormatSize, nodefault};
	__property int Size = {read=FSize, write=SetSize, nodefault};
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TWave(void) : Classes::TPersistent() { }
	#pragma option pop
	
};


class DELPHICLASS TCustomDXWave;
class PASCALIMPLEMENTATION TCustomDXWave : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	TWave* FWave;
	void __fastcall SetWave(TWave* Value);
	
public:
	__fastcall virtual TCustomDXWave(Classes::TComponent* AOnwer);
	__fastcall virtual ~TCustomDXWave(void);
	__property TWave* Wave = {read=FWave, write=SetWave};
};


class DELPHICLASS TDXWave;
class PASCALIMPLEMENTATION TDXWave : public TCustomDXWave 
{
	typedef TCustomDXWave inherited;
	
__published:
	__property Wave ;
public:
	#pragma option push -w-inl
	/* TCustomDXWave.Create */ inline __fastcall virtual TDXWave(Classes::TComponent* AOnwer) : TCustomDXWave(
		AOnwer) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomDXWave.Destroy */ inline __fastcall virtual ~TDXWave(void) { }
	#pragma option pop
	
};


class DELPHICLASS EWaveStreamError;
class PASCALIMPLEMENTATION EWaveStreamError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EWaveStreamError(const AnsiString Msg) : Sysutils::Exception(
		Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EWaveStreamError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EWaveStreamError(int Ident)/* overload */ : Sysutils::Exception(
		Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EWaveStreamError(int Ident, const System::TVarRec * 
		Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EWaveStreamError(const AnsiString Msg, int AHelpContext
		) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EWaveStreamError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EWaveStreamError(int Ident, int AHelpContext)/* overload */
		 : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EWaveStreamError(System::PResStringRec ResStringRec
		, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(
		ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EWaveStreamError(void) { }
	#pragma option pop
	
};


class DELPHICLASS TCustomWaveStream;
class PASCALIMPLEMENTATION TCustomWaveStream : public Classes::TStream 
{
	typedef Classes::TStream inherited;
	
private:
	int FPosition;
	
protected:
	virtual int __fastcall GetFilledSize(void);
	virtual Mmsystem::PWaveFormatEx __fastcall GetFormat(void) = 0 ;
	virtual int __fastcall GetFormatSize(void);
	HIDESBASE virtual int __fastcall GetSize(void);
	virtual int __fastcall ReadWave(void *Buffer, int Count);
	virtual void __fastcall SetFormatSize(int Value) = 0 ;
	virtual void __fastcall SetSize(int Value);
	virtual int __fastcall WriteWave(const void *Buffer, int Count);
	
public:
	virtual int __fastcall Read(void *Buffer, int Count);
	virtual int __fastcall Seek(int Offset, Word Origin);
	virtual int __fastcall Write(const void *Buffer, int Count);
	void __fastcall SetPCMFormat(int SamplesPerSec, int BitsPerSample, int Channels);
	__property int FilledSize = {read=GetFilledSize, nodefault};
	__property Mmsystem::PWaveFormatEx Format = {read=GetFormat};
	__property int FormatSize = {read=GetFormatSize, write=SetFormatSize, nodefault};
	__property int Size = {read=GetSize, write=SetSize, nodefault};
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TCustomWaveStream(void) : Classes::TStream() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TCustomWaveStream(void) { }
	#pragma option pop
	
};


class DELPHICLASS TCustomWaveStream2;
class PASCALIMPLEMENTATION TCustomWaveStream2 : public TCustomWaveStream 
{
	typedef TCustomWaveStream inherited;
	
private:
	tWAVEFORMATEX *FFormat;
	int FFormatSize;
	
protected:
	virtual Mmsystem::PWaveFormatEx __fastcall GetFormat(void);
	virtual int __fastcall GetFormatSize(void);
	virtual void __fastcall SetFormatSize(int Value);
	
public:
	__fastcall virtual ~TCustomWaveStream2(void);
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TCustomWaveStream2(void) : TCustomWaveStream() { }
	#pragma option pop
	
};


class DELPHICLASS TWaveObjectStream;
class PASCALIMPLEMENTATION TWaveObjectStream : public TCustomWaveStream 
{
	typedef TCustomWaveStream inherited;
	
private:
	TWave* FWave;
	
protected:
	virtual Mmsystem::PWaveFormatEx __fastcall GetFormat(void);
	virtual int __fastcall GetFormatSize(void);
	virtual int __fastcall GetSize(void);
	virtual int __fastcall ReadWave(void *Buffer, int Count);
	virtual void __fastcall SetFormatSize(int Value);
	virtual void __fastcall SetSize(int Value);
	virtual int __fastcall WriteWave(const void *Buffer, int Count);
	
public:
	__fastcall TWaveObjectStream(TWave* AWave);
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TWaveObjectStream(void) { }
	#pragma option pop
	
};


class DELPHICLASS TWaveStream;
class PASCALIMPLEMENTATION TWaveStream : public TCustomWaveStream2 
{
	typedef TCustomWaveStream2 inherited;
	
private:
	int FDataPosition;
	int FDataHeaderPosition;
	bool FOpened;
	int FOriPosition;
	bool FReadMode;
	int FSize;
	Classes::TStream* FStream;
	void __fastcall CloseWriteMode(void);
	void __fastcall OpenReadMode(void);
	void __fastcall OpenWriteMode(void);
	
protected:
	virtual int __fastcall GetSize(void);
	virtual int __fastcall ReadWave(void *Buffer, int Count);
	virtual int __fastcall WriteWave(const void *Buffer, int Count);
	
public:
	__fastcall TWaveStream(Classes::TStream* AStream);
	__fastcall virtual ~TWaveStream(void);
	void __fastcall Open(bool WriteMode);
};


class DELPHICLASS TWaveFileStream;
class PASCALIMPLEMENTATION TWaveFileStream : public TWaveStream 
{
	typedef TWaveStream inherited;
	
private:
	Classes::TFileStream* FFileStream;
	
public:
	__fastcall TWaveFileStream(const AnsiString FileName, int FileMode);
	__fastcall virtual ~TWaveFileStream(void);
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall MakePCMWaveFormatEx(tWAVEFORMATEX &Format, int SamplesPerSec, int BitsPerSample
	, int Channels);

}	/* namespace Wave */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Wave;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Wave
