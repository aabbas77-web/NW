// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DXSounds.pas' rev: 5.00

#ifndef DXSoundsHPP
#define DXSoundsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Wave.hpp>	// Pascal unit
#include <DXClass.hpp>	// Pascal unit
#include <DirectX.hpp>	// Pascal unit
#include <MMSystem.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Dxsounds
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS EDirectSoundError;
class PASCALIMPLEMENTATION EDirectSoundError : public Dxclass::EDirectXError 
{
	typedef Dxclass::EDirectXError inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EDirectSoundError(const AnsiString Msg) : Dxclass::EDirectXError(
		Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EDirectSoundError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size) : Dxclass::EDirectXError(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EDirectSoundError(int Ident)/* overload */ : Dxclass::EDirectXError(
		Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EDirectSoundError(int Ident, const System::TVarRec * 
		Args, const int Args_Size)/* overload */ : Dxclass::EDirectXError(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EDirectSoundError(const AnsiString Msg, int AHelpContext
		) : Dxclass::EDirectXError(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EDirectSoundError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Dxclass::EDirectXError(Msg, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EDirectSoundError(int Ident, int AHelpContext)/* overload */
		 : Dxclass::EDirectXError(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EDirectSoundError(System::PResStringRec ResStringRec
		, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Dxclass::EDirectXError(
		ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EDirectSoundError(void) { }
	#pragma option pop
	
};


class DELPHICLASS EDirectSoundBufferError;
class PASCALIMPLEMENTATION EDirectSoundBufferError : public EDirectSoundError 
{
	typedef EDirectSoundError inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EDirectSoundBufferError(const AnsiString Msg) : EDirectSoundError(
		Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EDirectSoundBufferError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size) : EDirectSoundError(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EDirectSoundBufferError(int Ident)/* overload */ : EDirectSoundError(
		Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EDirectSoundBufferError(int Ident, const System::TVarRec 
		* Args, const int Args_Size)/* overload */ : EDirectSoundError(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EDirectSoundBufferError(const AnsiString Msg, int AHelpContext
		) : EDirectSoundError(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EDirectSoundBufferError(const AnsiString Msg, const 
		System::TVarRec * Args, const int Args_Size, int AHelpContext) : EDirectSoundError(Msg, Args, Args_Size
		, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EDirectSoundBufferError(int Ident, int AHelpContext
		)/* overload */ : EDirectSoundError(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EDirectSoundBufferError(System::PResStringRec ResStringRec
		, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EDirectSoundError(
		ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EDirectSoundBufferError(void) { }
	#pragma option pop
	
};


class DELPHICLASS TDirectSound;
class DELPHICLASS TDirectSoundBuffer;
class PASCALIMPLEMENTATION TDirectSound : public Dxclass::TDirectX 
{
	typedef Dxclass::TDirectX inherited;
	
private:
	Classes::TList* FBufferList;
	bool FGlobalFocus;
	Directx::_di_IDirectSound FIDSound;
	bool FInRestoreBuffer;
	bool FStickyFocus;
	TDirectSoundBuffer* __fastcall GetBuffer(int Index);
	int __fastcall GetBufferCount(void);
	Directx::_di_IDirectSound __fastcall GetIDSound();
	Directx::_di_IDirectSound __fastcall GetISound();
	
protected:
	void __fastcall CheckBuffer(TDirectSoundBuffer* Buffer);
	virtual void __fastcall DoRestoreBuffer(void);
	
public:
	__fastcall TDirectSound(System::PGUID GUID);
	__fastcall virtual ~TDirectSound(void);
	/*         class method */ static Dxclass::TDirectXDrivers* __fastcall Drivers(TMetaClass* vmt);
	__property int BufferCount = {read=GetBufferCount, nodefault};
	__property TDirectSoundBuffer* Buffers[int Index] = {read=GetBuffer};
	__property Directx::_di_IDirectSound IDSound = {read=GetIDSound};
	__property Directx::_di_IDirectSound ISound = {read=GetISound};
};


class PASCALIMPLEMENTATION TDirectSoundBuffer : public Dxclass::TDirectX 
{
	typedef Dxclass::TDirectX inherited;
	
private:
	TDirectSound* FDSound;
	Directx::_di_IDirectSoundBuffer FIDSBuffer;
	Directx::TDSBCaps FCaps;
	tWAVEFORMATEX *FFormat;
	int FFormatSize;
	void *FLockAudioPtr1[1];
	void *FLockAudioPtr2[1];
	unsigned FLockAudioSize1[1];
	unsigned FLockAudioSize2[1];
	int FLockCount;
	int __fastcall GetBitCount(void);
	Mmsystem::PWaveFormatEx __fastcall GetFormat(void);
	int __fastcall GetFrequency(void);
	Directx::_di_IDirectSoundBuffer __fastcall GetIDSBuffer();
	Directx::_di_IDirectSoundBuffer __fastcall GetIBuffer();
	bool __fastcall GetPlaying(void);
	int __fastcall GetPan(void);
	int __fastcall GetPosition(void);
	int __fastcall GetSize(void);
	int __fastcall GetStatus(void);
	int __fastcall GetVolume(void);
	void __fastcall SetFrequency(int Value);
	void __fastcall SetIDSBuffer(Directx::_di_IDirectSoundBuffer Value);
	void __fastcall SetPan(int Value);
	void __fastcall SetPosition(int Value);
	void __fastcall SetVolume(int Value);
	
protected:
	virtual void __fastcall Check(void);
	
public:
	__fastcall TDirectSoundBuffer(TDirectSound* ADirectSound);
	__fastcall virtual ~TDirectSoundBuffer(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	bool __fastcall CreateBuffer(const Directx::TDSBufferDesc &BufferDesc);
	void __fastcall LoadFromFile(const AnsiString FileName);
	void __fastcall LoadFromMemory(const tWAVEFORMATEX &Format, void * Data, int Size);
	void __fastcall LoadFromStream(Classes::TStream* Stream);
	void __fastcall LoadFromWave(Wave::TWave* Wave);
	bool __fastcall Lock(int LockPosition, int LockSize, void * &AudioPtr1, int &AudioSize1, void * &AudioPtr2
		, int &AudioSize2);
	bool __fastcall Play(bool Loop);
	bool __fastcall Restore(void);
	bool __fastcall SetFormat(const tWAVEFORMATEX &Format);
	void __fastcall SetSize(const tWAVEFORMATEX &Format, int Size);
	void __fastcall Stop(void);
	void __fastcall UnLock(void);
	__property int BitCount = {read=GetBitCount, nodefault};
	__property TDirectSound* DSound = {read=FDSound};
	__property Mmsystem::PWaveFormatEx Format = {read=GetFormat};
	__property int FormatSize = {read=FFormatSize, nodefault};
	__property int Frequency = {read=GetFrequency, write=SetFrequency, nodefault};
	__property Directx::_di_IDirectSoundBuffer IBuffer = {read=GetIBuffer};
	__property Directx::_di_IDirectSoundBuffer IDSBuffer = {read=GetIDSBuffer, write=SetIDSBuffer};
	__property bool Playing = {read=GetPlaying, nodefault};
	__property int Pan = {read=GetPan, write=SetPan, nodefault};
	__property int Position = {read=GetPosition, write=SetPosition, nodefault};
	__property int Size = {read=GetSize, nodefault};
	__property int Volume = {read=GetVolume, write=SetVolume, nodefault};
};


class DELPHICLASS EAudioStreamError;
class PASCALIMPLEMENTATION EAudioStreamError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EAudioStreamError(const AnsiString Msg) : Sysutils::Exception(
		Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EAudioStreamError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EAudioStreamError(int Ident)/* overload */ : Sysutils::Exception(
		Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EAudioStreamError(int Ident, const System::TVarRec * 
		Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EAudioStreamError(const AnsiString Msg, int AHelpContext
		) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EAudioStreamError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EAudioStreamError(int Ident, int AHelpContext)/* overload */
		 : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EAudioStreamError(System::PResStringRec ResStringRec
		, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(
		ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EAudioStreamError(void) { }
	#pragma option pop
	
};


class DELPHICLASS TAudioStream;
class PASCALIMPLEMENTATION TAudioStream : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	bool FAutoUpdate;
	TDirectSoundBuffer* FBuffer;
	int FBufferLength;
	unsigned FBufferPos;
	unsigned FPlayBufferPos;
	unsigned FBufferSize;
	TDirectSound* FDSound;
	bool FLooped;
	int FPlayedSize;
	bool FPlaying;
	int FPosition;
	Wave::TCustomWaveStream* FWaveStream;
	int FWritePosition;
	unsigned FNotifyEvent;
	Classes::TThread* FNotifyThread;
	bool FInThread;
	Mmsystem::PWaveFormatEx __fastcall GetFormat(void);
	int __fastcall GetFormatSize(void);
	int __fastcall GetFrequency(void);
	int __fastcall GetPan(void);
	int __fastcall GetPlayedSize(void);
	int __fastcall GetSize(void);
	int __fastcall GetVolume(void);
	int __fastcall GetWriteSize(void);
	void __fastcall SetAutoUpdate(bool Value);
	void __fastcall SetBufferLength(int Value);
	void __fastcall SetFrequency(int Value);
	void __fastcall SetLooped(bool Value);
	void __fastcall SetPan(int Value);
	void __fastcall SetPlayedSize(int Value);
	void __fastcall SetPosition(int Value);
	void __fastcall SetVolume(int Value);
	void __fastcall SetWaveStream(Wave::TCustomWaveStream* Value);
	void __fastcall UpdatePlayedSize(void);
	int __fastcall WriteWave(int WriteSize);
	
public:
	__fastcall TAudioStream(TDirectSound* ADirectSound);
	__fastcall virtual ~TAudioStream(void);
	void __fastcall Play(void);
	void __fastcall RecreateBuf(void);
	void __fastcall Stop(void);
	void __fastcall Update(void);
	__property bool AutoUpdate = {read=FAutoUpdate, write=SetAutoUpdate, nodefault};
	__property int BufferLength = {read=FBufferLength, write=SetBufferLength, nodefault};
	__property Mmsystem::PWaveFormatEx Format = {read=GetFormat};
	__property int FormatSize = {read=GetFormatSize, nodefault};
	__property int Frequency = {read=GetFrequency, write=SetFrequency, nodefault};
	__property int Pan = {read=GetPan, write=SetPan, nodefault};
	__property int PlayedSize = {read=GetPlayedSize, write=SetPlayedSize, nodefault};
	__property bool Playing = {read=FPlaying, nodefault};
	__property int Position = {read=FPosition, write=SetPosition, nodefault};
	__property bool Looped = {read=FLooped, write=SetLooped, nodefault};
	__property int Size = {read=GetSize, nodefault};
	__property int Volume = {read=GetVolume, write=SetVolume, nodefault};
	__property Wave::TCustomWaveStream* WaveStream = {read=FWaveStream, write=SetWaveStream};
};


class DELPHICLASS TAudioFileStream;
class PASCALIMPLEMENTATION TAudioFileStream : public TAudioStream 
{
	typedef TAudioStream inherited;
	
private:
	AnsiString FFileName;
	Wave::TWaveFileStream* FWaveFileStream;
	void __fastcall SetFileName(const AnsiString Value);
	
public:
	__fastcall virtual ~TAudioFileStream(void);
	__property AnsiString FileName = {read=FFileName, write=SetFileName};
public:
	#pragma option push -w-inl
	/* TAudioStream.Create */ inline __fastcall TAudioFileStream(TDirectSound* ADirectSound) : TAudioStream(
		ADirectSound) { }
	#pragma option pop
	
};


class DELPHICLASS TSoundCaptureFormat;
class PASCALIMPLEMENTATION TSoundCaptureFormat : public Classes::TCollectionItem 
{
	typedef Classes::TCollectionItem inherited;
	
private:
	int FBitsPerSample;
	int FChannels;
	int FSamplesPerSec;
	
public:
	__property int BitsPerSample = {read=FBitsPerSample, nodefault};
	__property int Channels = {read=FChannels, nodefault};
	__property int SamplesPerSec = {read=FSamplesPerSec, nodefault};
public:
	#pragma option push -w-inl
	/* TCollectionItem.Create */ inline __fastcall virtual TSoundCaptureFormat(Classes::TCollection* Collection
		) : Classes::TCollectionItem(Collection) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TSoundCaptureFormat(void) { }
	#pragma option pop
	
};


class DELPHICLASS TSoundCaptureFormats;
class PASCALIMPLEMENTATION TSoundCaptureFormats : public Classes::TCollection 
{
	typedef Classes::TCollection inherited;
	
private:
	HIDESBASE TSoundCaptureFormat* __fastcall GetItem(int Index);
	
public:
	__fastcall TSoundCaptureFormats(void);
	int __fastcall IndexOf(int ASamplesPerSec, int ABitsPerSample, int AChannels);
	__property TSoundCaptureFormat* Items[int Index] = {read=GetItem/*, default*/};
public:
	#pragma option push -w-inl
	/* TCollection.Destroy */ inline __fastcall virtual ~TSoundCaptureFormats(void) { }
	#pragma option pop
	
};


class DELPHICLASS ESoundCaptureStreamError;
class PASCALIMPLEMENTATION ESoundCaptureStreamError : public Wave::EWaveStreamError 
{
	typedef Wave::EWaveStreamError inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ESoundCaptureStreamError(const AnsiString Msg) : Wave::EWaveStreamError(
		Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ESoundCaptureStreamError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size) : Wave::EWaveStreamError(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ESoundCaptureStreamError(int Ident)/* overload */ : Wave::EWaveStreamError(
		Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ESoundCaptureStreamError(int Ident, const System::TVarRec 
		* Args, const int Args_Size)/* overload */ : Wave::EWaveStreamError(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ESoundCaptureStreamError(const AnsiString Msg, int AHelpContext
		) : Wave::EWaveStreamError(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ESoundCaptureStreamError(const AnsiString Msg, const 
		System::TVarRec * Args, const int Args_Size, int AHelpContext) : Wave::EWaveStreamError(Msg, Args, 
		Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ESoundCaptureStreamError(int Ident, int AHelpContext
		)/* overload */ : Wave::EWaveStreamError(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ESoundCaptureStreamError(System::PResStringRec ResStringRec
		, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Wave::EWaveStreamError(
		ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ESoundCaptureStreamError(void) { }
	#pragma option pop
	
};


class DELPHICLASS TSoundCaptureStream;
class PASCALIMPLEMENTATION TSoundCaptureStream : public Wave::TCustomWaveStream2 
{
	typedef Wave::TCustomWaveStream2 inherited;
	
private:
	Directx::_di_IDirectSoundCaptureBuffer FBuffer;
	int FBufferLength;
	unsigned FBufferPos;
	unsigned FBufferSize;
	Directx::_di_IDirectSoundCapture FCapture;
	int FCaptureFormat;
	bool FCapturing;
	unsigned FNotifyEvent;
	Classes::TThread* FNotifyThread;
	Classes::TNotifyEvent FOnFilledBuffer;
	TSoundCaptureFormats* FSupportedFormats;
	int __fastcall GetReadSize(void);
	void __fastcall SetBufferLength(int Value);
	void __fastcall SetOnFilledBuffer(Classes::TNotifyEvent Value);
	
protected:
	virtual void __fastcall DoFilledBuffer(void);
	virtual int __fastcall GetFilledSize(void);
	virtual int __fastcall ReadWave(void *Buffer, int Count);
	
public:
	__fastcall TSoundCaptureStream(System::PGUID GUID);
	__fastcall virtual ~TSoundCaptureStream(void);
	/*         class method */ static Dxclass::TDirectXDrivers* __fastcall Drivers(TMetaClass* vmt);
	void __fastcall Start(void);
	void __fastcall Stop(void);
	__property int BufferLength = {read=FBufferLength, write=SetBufferLength, nodefault};
	__property int CaptureFormat = {read=FCaptureFormat, write=FCaptureFormat, nodefault};
	__property bool Capturing = {read=FCapturing, nodefault};
	__property Classes::TNotifyEvent OnFilledBuffer = {read=FOnFilledBuffer, write=SetOnFilledBuffer};
	__property TSoundCaptureFormats* SupportedFormats = {read=FSupportedFormats};
};


class DELPHICLASS TSoundEngine;
class PASCALIMPLEMENTATION TSoundEngine : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	TDirectSound* FDSound;
	Classes::TList* FEffectList;
	bool FEnabled;
	Extctrls::TTimer* FTimer;
	TDirectSoundBuffer* __fastcall GetEffect(int Index);
	int __fastcall GetEffectCount(void);
	void __fastcall SetEnabled(bool Value);
	void __fastcall TimerEvent(System::TObject* Sender);
	
public:
	__fastcall TSoundEngine(TDirectSound* ADSound);
	__fastcall virtual ~TSoundEngine(void);
	void __fastcall Clear(void);
	void __fastcall EffectFile(const AnsiString Filename, bool Loop, bool Wait);
	void __fastcall EffectStream(Classes::TStream* Stream, bool Loop, bool Wait);
	void __fastcall EffectWave(Wave::TWave* Wave, bool Loop, bool Wait);
	__property int EffectCount = {read=GetEffectCount, nodefault};
	__property TDirectSoundBuffer* Effects[int Index] = {read=GetEffect};
	__property bool Enabled = {read=FEnabled, write=SetEnabled, nodefault};
};


class DELPHICLASS EDXSoundError;
class PASCALIMPLEMENTATION EDXSoundError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EDXSoundError(const AnsiString Msg) : Sysutils::Exception(
		Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EDXSoundError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EDXSoundError(int Ident)/* overload */ : Sysutils::Exception(
		Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EDXSoundError(int Ident, const System::TVarRec * Args
		, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EDXSoundError(const AnsiString Msg, int AHelpContext) : 
		Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EDXSoundError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EDXSoundError(int Ident, int AHelpContext)/* overload */
		 : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EDXSoundError(System::PResStringRec ResStringRec
		, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(
		ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EDXSoundError(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TDXSoundOption { soGlobalFocus, soStickyFocus, soExclusive };
#pragma option pop

typedef Set<TDXSoundOption, soGlobalFocus, soExclusive>  TDXSoundOptions;

#pragma option push -b-
enum TDXSoundNotifyType { dsntDestroying, dsntInitializing, dsntInitialize, dsntFinalize, dsntRestore 
	};
#pragma option pop

class DELPHICLASS TCustomDXSound;
typedef void __fastcall (__closure *TDXSoundNotifyEvent)(TCustomDXSound* Sender, TDXSoundNotifyType 
	NotifyType);

class PASCALIMPLEMENTATION TCustomDXSound : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	bool FAutoInitialize;
	bool FCalledDoInitialize;
	GUID *FDriver;
	#pragma pack(push, 1)
	GUID FDriverGUID;
	#pragma pack(pop)
	
	TDirectSound* FDSound;
	Forms::TCustomForm* FForm;
	bool FInitialized;
	bool FInternalInitialized;
	Classes::TList* FNotifyEventList;
	TDXSoundOptions FNowOptions;
	Classes::TNotifyEvent FOnFinalize;
	Classes::TNotifyEvent FOnInitialize;
	Classes::TNotifyEvent FOnInitializing;
	Classes::TNotifyEvent FOnRestore;
	TDXSoundOptions FOptions;
	TDirectSoundBuffer* FPrimary;
	Dxclass::TControlSubClass* FSubClass;
	void __fastcall FormWndProc(Messages::TMessage &Message, Controls::TWndMethod DefWindowProc);
	void __fastcall NotifyEventList(TDXSoundNotifyType NotifyType);
	void __fastcall SetDriver(System::PGUID Value);
	void __fastcall SetForm(Forms::TCustomForm* Value);
	void __fastcall SetOptions(TDXSoundOptions Value);
	
protected:
	virtual void __fastcall DoFinalize(void);
	virtual void __fastcall DoInitialize(void);
	virtual void __fastcall DoInitializing(void);
	virtual void __fastcall DoRestore(void);
	virtual void __fastcall Loaded(void);
	
public:
	__fastcall virtual TCustomDXSound(Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomDXSound(void);
	/*         class method */ static Dxclass::TDirectXDrivers* __fastcall Drivers(TMetaClass* vmt);
	void __fastcall Finalize(void);
	void __fastcall Initialize(void);
	void __fastcall Restore(void);
	void __fastcall RegisterNotifyEvent(TDXSoundNotifyEvent NotifyEvent);
	void __fastcall UnRegisterNotifyEvent(TDXSoundNotifyEvent NotifyEvent);
	__property bool AutoInitialize = {read=FAutoInitialize, write=FAutoInitialize, nodefault};
	__property System::PGUID Driver = {read=FDriver, write=SetDriver};
	__property TDirectSound* DSound = {read=FDSound};
	__property bool Initialized = {read=FInitialized, nodefault};
	__property TDXSoundOptions NowOptions = {read=FNowOptions, nodefault};
	__property TDirectSoundBuffer* Primary = {read=FPrimary};
	__property Classes::TNotifyEvent OnFinalize = {read=FOnFinalize, write=FOnFinalize};
	__property Classes::TNotifyEvent OnInitialize = {read=FOnInitialize, write=FOnInitialize};
	__property Classes::TNotifyEvent OnInitializing = {read=FOnInitializing, write=FOnInitializing};
	__property Classes::TNotifyEvent OnRestore = {read=FOnRestore, write=FOnRestore};
	__property TDXSoundOptions Options = {read=FOptions, write=SetOptions, nodefault};
};


class DELPHICLASS TDXSound;
class PASCALIMPLEMENTATION TDXSound : public TCustomDXSound 
{
	typedef TCustomDXSound inherited;
	
__published:
	__property AutoInitialize ;
	__property Options ;
	__property OnFinalize ;
	__property OnInitialize ;
	__property OnInitializing ;
	__property OnRestore ;
public:
	#pragma option push -w-inl
	/* TCustomDXSound.Create */ inline __fastcall virtual TDXSound(Classes::TComponent* AOwner) : TCustomDXSound(
		AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomDXSound.Destroy */ inline __fastcall virtual ~TDXSound(void) { }
	#pragma option pop
	
};


class DELPHICLASS EWaveCollectionError;
class PASCALIMPLEMENTATION EWaveCollectionError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EWaveCollectionError(const AnsiString Msg) : Sysutils::Exception(
		Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EWaveCollectionError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EWaveCollectionError(int Ident)/* overload */ : Sysutils::Exception(
		Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EWaveCollectionError(int Ident, const System::TVarRec 
		* Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EWaveCollectionError(const AnsiString Msg, int AHelpContext
		) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EWaveCollectionError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EWaveCollectionError(int Ident, int AHelpContext)/* overload */
		 : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EWaveCollectionError(System::PResStringRec ResStringRec
		, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(
		ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EWaveCollectionError(void) { }
	#pragma option pop
	
};


class DELPHICLASS TWaveCollectionItem;
class DELPHICLASS TWaveCollection;
class PASCALIMPLEMENTATION TWaveCollectionItem : public Dxclass::THashCollectionItem 
{
	typedef Dxclass::THashCollectionItem inherited;
	
private:
	TDirectSoundBuffer* FBuffer;
	Classes::TList* FBufferList;
	int FFrequency;
	bool FInitialized;
	bool FLooped;
	int FMaxPlayingCount;
	int FPan;
	int FVolume;
	Wave::TWave* FWave;
	TDirectSoundBuffer* __fastcall CreateBuffer(void);
	void __fastcall Finalize(void);
	void __fastcall Initialize(void);
	TDirectSoundBuffer* __fastcall GetBuffer(void);
	TWaveCollection* __fastcall GetWaveCollection(void);
	void __fastcall SetFrequency(int Value);
	void __fastcall SetLooped(bool Value);
	void __fastcall SetMaxPlayingCount(int Value);
	void __fastcall SetPan(int Value);
	void __fastcall SetVolume(int Value);
	void __fastcall SetWave(Wave::TWave* Value);
	
public:
	__fastcall virtual TWaveCollectionItem(Classes::TCollection* Collection);
	__fastcall virtual ~TWaveCollectionItem(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	void __fastcall Play(bool Wait);
	void __fastcall Restore(void);
	void __fastcall Stop(void);
	__property int Frequency = {read=FFrequency, write=SetFrequency, nodefault};
	__property bool Initialized = {read=FInitialized, nodefault};
	__property int Pan = {read=FPan, write=SetPan, nodefault};
	__property int Volume = {read=FVolume, write=SetVolume, nodefault};
	__property TWaveCollection* WaveCollection = {read=GetWaveCollection};
	
__published:
	__property bool Looped = {read=FLooped, write=SetLooped, nodefault};
	__property int MaxPlayingCount = {read=FMaxPlayingCount, write=SetMaxPlayingCount, nodefault};
	__property Wave::TWave* Wave = {read=FWave, write=SetWave};
};


class PASCALIMPLEMENTATION TWaveCollection : public Dxclass::THashCollection 
{
	typedef Dxclass::THashCollection inherited;
	
private:
	TCustomDXSound* FDXSound;
	Classes::TPersistent* FOwner;
	HIDESBASE TWaveCollectionItem* __fastcall GetItem(int Index);
	bool __fastcall Initialized(void);
	
protected:
	DYNAMIC Classes::TPersistent* __fastcall GetOwner(void);
	
public:
	__fastcall TWaveCollection(Classes::TPersistent* AOwner);
	TWaveCollectionItem* __fastcall Find(const AnsiString Name);
	void __fastcall Finalize(void);
	void __fastcall Initialize(TCustomDXSound* DXSound);
	void __fastcall Restore(void);
	void __fastcall LoadFromFile(const AnsiString FileName);
	void __fastcall LoadFromStream(Classes::TStream* Stream);
	void __fastcall SaveToFile(const AnsiString FileName);
	void __fastcall SaveToStream(Classes::TStream* Stream);
	__property TCustomDXSound* DXSound = {read=FDXSound};
	__property TWaveCollectionItem* Items[int Index] = {read=GetItem/*, default*/};
public:
	#pragma option push -w-inl
	/* TCollection.Destroy */ inline __fastcall virtual ~TWaveCollection(void) { }
	#pragma option pop
	
};


class DELPHICLASS TCustomDXWaveList;
class PASCALIMPLEMENTATION TCustomDXWaveList : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	TCustomDXSound* FDXSound;
	TWaveCollection* FItems;
	void __fastcall DXSoundNotifyEvent(TCustomDXSound* Sender, TDXSoundNotifyType NotifyType);
	void __fastcall SetDXSound(TCustomDXSound* Value);
	void __fastcall SetItems(TWaveCollection* Value);
	
protected:
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation
		);
	
public:
	__fastcall virtual TCustomDXWaveList(Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomDXWaveList(void);
	__property TCustomDXSound* DXSound = {read=FDXSound, write=SetDXSound};
	__property TWaveCollection* Items = {read=FItems, write=SetItems};
};


class DELPHICLASS TDXWaveList;
class PASCALIMPLEMENTATION TDXWaveList : public TCustomDXWaveList 
{
	typedef TCustomDXWaveList inherited;
	
__published:
	__property DXSound ;
	__property Items ;
public:
	#pragma option push -w-inl
	/* TCustomDXWaveList.Create */ inline __fastcall virtual TDXWaveList(Classes::TComponent* AOwner) : 
		TCustomDXWaveList(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomDXWaveList.Destroy */ inline __fastcall virtual ~TDXWaveList(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Dxsounds */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Dxsounds;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DXSounds
