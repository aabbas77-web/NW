// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DirectX.pas' rev: 5.00

#ifndef DirectXHPP
#define DirectXHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <MMSystem.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Directx
{
//-- type declarations -------------------------------------------------------
typedef unsigned TDXFileFormat;

typedef unsigned DXFILEFORMAT;

typedef unsigned TDXFileLoadOptions;

typedef unsigned DXFILELOADOPTIONS;

struct TDXFileLoadResource;
typedef TDXFileLoadResource *PDXFileLoadResource;

struct TDXFileLoadResource
{
	Windows::HINST hModule;
	char *lpName;
	char *lpType;
} ;

typedef TDXFileLoadResource  DXFILELOADRESOURCE;

typedef TDXFileLoadResource *LPDXFILELOADRESOURCE;

struct TDXFileLoadMemory;
typedef TDXFileLoadMemory *PDXFileLoadMemory;

struct TDXFileLoadMemory
{
	void *lpMemory;
	unsigned dSize;
} ;

typedef TDXFileLoadMemory  DXFILELOADMEMORY;

typedef TDXFileLoadMemory *LPDXFILELOADMEMORY;

__interface IDirectXFile;
typedef System::DelphiInterface<IDirectXFile> _di_IDirectXFile;
__interface IDirectXFileEnumObject;
typedef System::DelphiInterface<IDirectXFileEnumObject> _di_IDirectXFileEnumObject;
__interface IDirectXFileSaveObject;
typedef System::DelphiInterface<IDirectXFileSaveObject> _di_IDirectXFileSaveObject;
__interface INTERFACE_UUID("{3D82AB40-62DA-11CF-AB39-0020AF71E433}") IDirectXFile  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall CreateEnumObject(void * pvSource, unsigned dwLoadOptions, /* out */ _di_IDirectXFileEnumObject 
		&ppEnumObj) = 0 ;
	virtual HRESULT __stdcall CreateSaveObject(char * szFileName, unsigned dwFileFormat, /* out */ _di_IDirectXFileSaveObject 
		&ppSaveObj) = 0 ;
	virtual HRESULT __stdcall RegisterTemplates(void * pvData, unsigned cbSize) = 0 ;
};

__interface IDirectXFileData;
typedef System::DelphiInterface<IDirectXFileData> _di_IDirectXFileData;
__interface INTERFACE_UUID("{3D82AB41-62DA-11CF-AB39-0020AF71E433}") IDirectXFileEnumObject  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall GetNextDataObject(/* out */ _di_IDirectXFileData &ppDataObj) = 0 ;
	virtual HRESULT __stdcall GetDataObjectById(const GUID &rguid, /* out */ _di_IDirectXFileData &ppDataObj
		) = 0 ;
	virtual HRESULT __stdcall GetDataObjectByName(char * szName, /* out */ _di_IDirectXFileData &ppDataObj
		) = 0 ;
};

__interface INTERFACE_UUID("{3D82AB42-62DA-11CF-AB39-0020AF71E433}") IDirectXFileSaveObject  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall SaveTemplates(unsigned cTemplates, System::PGUID &ppguidTemplates) = 0 ;
	virtual HRESULT __stdcall CreateDataObject(const GUID &rguidTemplate, char * szName, const GUID &pguid
		, unsigned cbSize, void * pvData, /* out */ _di_IDirectXFileData &ppDataObj) = 0 ;
	virtual HRESULT __stdcall SaveData(_di_IDirectXFileData pDataObj) = 0 ;
};

__interface IDirectXFileObject;
typedef System::DelphiInterface<IDirectXFileObject> _di_IDirectXFileObject;
__interface INTERFACE_UUID("{3D82AB43-62DA-11CF-AB39-0020AF71E433}") IDirectXFileObject  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall GetName(char * pstrNameBuf, unsigned &dwBufLen) = 0 ;
	virtual HRESULT __stdcall GetId(GUID &pGuidBuf) = 0 ;
};

__interface INTERFACE_UUID("{3D82AB44-62DA-11CF-AB39-0020AF71E433}") IDirectXFileData  : public IDirectXFileObject 
	
{
	
public:
	virtual HRESULT __stdcall GetData(char * szMember, unsigned &pcbSize, void * &ppvData) = 0 ;
	virtual HRESULT __stdcall GetType(System::PGUID &ppguid) = 0 ;
	virtual HRESULT __stdcall GetNextObject(/* out */ _di_IDirectXFileObject &ppChildObj) = 0 ;
	virtual HRESULT __stdcall AddDataObject(_di_IDirectXFileData pDataObj) = 0 ;
	virtual HRESULT __stdcall AddDataReference(char * szRef, System::PGUID pguidRef) = 0 ;
	virtual HRESULT __stdcall AddBinaryObjec(char * szName, System::PGUID pguid, char * szMimeType, void * 
		pvData, unsigned cbSize) = 0 ;
};

__interface IDirectXFileDataReference;
typedef System::DelphiInterface<IDirectXFileDataReference> _di_IDirectXFileDataReference;
__interface INTERFACE_UUID("{3D82AB45-62DA-11CF-AB39-0020AF71E433}") IDirectXFileDataReference  : public IDirectXFileObject 
	
{
	
public:
	virtual HRESULT __stdcall Resolve(/* out */ _di_IDirectXFileData &ppDataObj) = 0 ;
};

__interface IDirectXFileBinary;
typedef System::DelphiInterface<IDirectXFileBinary> _di_IDirectXFileBinary;
__interface INTERFACE_UUID("{3D82AB46-62DA-11CF-AB39-0020AF71E433}") IDirectXFileBinary  : public IDirectXFileObject 
	
{
	
public:
	virtual HRESULT __stdcall GetSize(unsigned &pcbSize) = 0 ;
	virtual HRESULT __stdcall GetMimeType(char * &pszMimeType) = 0 ;
	virtual HRESULT __stdcall Read(void * pvData, unsigned cbSize, unsigned &pcbRead) = 0 ;
};

struct TDSCaps
{
	unsigned dwSize;
	unsigned dwFlags;
	unsigned dwMinSecondarySampleRate;
	unsigned dwMaxSecondarySampleRate;
	unsigned dwPrimaryBuffers;
	unsigned dwMaxHwMixingAllBuffers;
	unsigned dwMaxHwMixingStaticBuffers;
	unsigned dwMaxHwMixingStreamingBuffers;
	unsigned dwFreeHwMixingAllBuffers;
	unsigned dwFreeHwMixingStaticBuffers;
	unsigned dwFreeHwMixingStreamingBuffers;
	unsigned dwMaxHw3DAllBuffers;
	unsigned dwMaxHw3DStaticBuffers;
	unsigned dwMaxHw3DStreamingBuffers;
	unsigned dwFreeHw3DAllBuffers;
	unsigned dwFreeHw3DStaticBuffers;
	unsigned dwFreeHw3DStreamingBuffers;
	unsigned dwTotalHwMemBytes;
	unsigned dwFreeHwMemBytes;
	unsigned dwMaxContigFreeHwMemBytes;
	unsigned dwUnlockTransferRateHwBuffers;
	unsigned dwPlayCpuOverheadSwBuffers;
	unsigned dwReserved1;
	unsigned dwReserved2;
} ;

typedef TDSCaps *PDSCaps;

typedef TDSCaps  DSCAPS;

typedef TDSCaps *LPDSCAPS;

struct TDSBCaps
{
	unsigned dwSize;
	unsigned dwFlags;
	unsigned dwBufferBytes;
	unsigned dwUnlockTransferRate;
	unsigned dwPlayCpuOverhead;
} ;

typedef TDSBCaps *PDSBCaps;

typedef TDSBCaps  DSBCAPS;

typedef TDSBCaps  LPDSBCAPS;

struct TDSBufferDesc;
typedef TDSBufferDesc *PDSBufferDesc;

struct TDSBufferDesc
{
	unsigned dwSize;
	unsigned dwFlags;
	unsigned dwBufferBytes;
	unsigned dwReserved;
	tWAVEFORMATEX *lpwfxFormat;
} ;

typedef TDSBufferDesc  DSBUFFERDESC;

typedef TDSBufferDesc *LPDSBUFFERDESC;

struct TDSCCaps
{
	unsigned dwSize;
	unsigned dwFlags;
	unsigned dwFormats;
	unsigned dwChannels;
} ;

typedef TDSCCaps *PDSCCaps;

typedef TDSCCaps  DSCCAPS;

typedef TDSCCaps *LPDSCCAPS;

struct TDSCBufferDesc
{
	unsigned dwSize;
	unsigned dwFlags;
	unsigned dwBufferBytes;
	unsigned dwReserved;
	tWAVEFORMATEX *lpwfxFormat;
} ;

typedef TDSCBufferDesc *PDSCBufferDesc;

typedef TDSCBufferDesc  DSCBUFFERDESC;

typedef TDSCBufferDesc *LPDSCBUFFERDESC;

struct TDSCBCaps
{
	unsigned dwSize;
	unsigned dwFlags;
	unsigned dwBufferBytes;
	unsigned dwReserved;
} ;

typedef TDSCBCaps *PDSCBCaps;

typedef TDSCBCaps  DSCBCAPS;

typedef TDSCBCaps *LPDSCBCAPS;

struct TDSBPositionNotify;
typedef TDSBPositionNotify *PDSBPositionNotify;

struct TDSBPositionNotify
{
	unsigned dwOffset;
	unsigned hEventNotify;
} ;

typedef TDSBPositionNotify  DSBPOSITIONNOTIFY;

typedef TDSBPositionNotify *LPDSBPOSITIONNOTIFY;

__interface IDirectSound;
typedef System::DelphiInterface<IDirectSound> _di_IDirectSound;
__interface IDirectSoundBuffer;
typedef System::DelphiInterface<IDirectSoundBuffer> _di_IDirectSoundBuffer;
__interface INTERFACE_UUID("{279AFA83-4981-11CE-A521-0020AF0BE560}") IDirectSound  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall CreateSoundBuffer(const TDSBufferDesc &lpDSBufferDesc, /* out */ _di_IDirectSoundBuffer 
		&lplpDirectSoundBuffer, _di_IUnknown pUnkOuter) = 0 ;
	virtual HRESULT __stdcall GetCaps(TDSCaps &lpDSCaps) = 0 ;
	virtual HRESULT __stdcall DuplicateSoundBuffer(_di_IDirectSoundBuffer lpDsbOriginal, /* out */ _di_IDirectSoundBuffer 
		&lpDsbDuplicate) = 0 ;
	virtual HRESULT __stdcall SetCooperativeLevel(HWND hwnd, unsigned dwLevel) = 0 ;
	virtual HRESULT __stdcall Compact(void) = 0 ;
	virtual HRESULT __stdcall GetSpeakerConfig(unsigned &lpdwSpeakerConfig) = 0 ;
	virtual HRESULT __stdcall SetSpeakerConfig(unsigned dwSpeakerConfig) = 0 ;
	virtual HRESULT __stdcall Initialize(System::PGUID lpGuid) = 0 ;
};

__interface INTERFACE_UUID("{279AFA85-4981-11CE-A521-0020AF0BE560}") IDirectSoundBuffer  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall GetCaps(TDSBCaps &lpDSBufferCaps) = 0 ;
	virtual HRESULT __stdcall GetCurrentPosition(unsigned &lpdwCurrentPlayCursor, unsigned &lpdwCurrentWriteCursor
		) = 0 ;
	virtual HRESULT __stdcall GetFormat(tWAVEFORMATEX &lpwfxFormat, unsigned dwSizeAllocated, unsigned 
		&lpdwSizeWritten) = 0 ;
	virtual HRESULT __stdcall GetVolume(int &lplVolume) = 0 ;
	virtual HRESULT __stdcall GetPan(int &lplPan) = 0 ;
	virtual HRESULT __stdcall GetFrequency(unsigned &lpdwFrequency) = 0 ;
	virtual HRESULT __stdcall GetStatus(unsigned &lpdwStatus) = 0 ;
	virtual HRESULT __stdcall Initialize(_di_IDirectSound lpDirectSound, const TDSBufferDesc &lpDSBufferDesc
		) = 0 ;
	virtual HRESULT __stdcall Lock(unsigned dwWriteCursor, unsigned dwWriteBytes, void * &lplpvAudioPtr1
		, unsigned &lpdwAudioBytes1, void * &lplpvAudioPtr2, unsigned &lpdwAudioBytes2, unsigned dwFlags) = 0 
		;
	virtual HRESULT __stdcall Play(unsigned dwReserved1, unsigned dwReserved2, unsigned dwFlags) = 0 ;
	virtual HRESULT __stdcall SetCurrentPosition(unsigned dwNewPosition) = 0 ;
	virtual HRESULT __stdcall SetFormat(const tWAVEFORMATEX &lpfxFormat) = 0 ;
	virtual HRESULT __stdcall SetVolume(int lVolume) = 0 ;
	virtual HRESULT __stdcall SetPan(int lPan) = 0 ;
	virtual HRESULT __stdcall SetFrequency(unsigned dwFrequency) = 0 ;
	virtual HRESULT __stdcall Stop(void) = 0 ;
	virtual HRESULT __stdcall Unlock(void * lpvAudioPtr1, unsigned dwAudioBytes1, void * lpvAudioPtr2, 
		unsigned dwAudioBytes2) = 0 ;
	virtual HRESULT __stdcall Restore(void) = 0 ;
};

__interface IDirectSoundCapture;
typedef System::DelphiInterface<IDirectSoundCapture> _di_IDirectSoundCapture;
__interface IDirectSoundCaptureBuffer;
typedef System::DelphiInterface<IDirectSoundCaptureBuffer> _di_IDirectSoundCaptureBuffer;
__interface INTERFACE_UUID("{B0210781-89CD-11D0-AF08-00A0C925CD16}") IDirectSoundCapture  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall CreateCaptureBuffer(const TDSCBufferDesc &lpDSCBufferDesc, /* out */ _di_IDirectSoundCaptureBuffer 
		&lplpDirectSoundCaptureBuffer, _di_IUnknown pUnkOuter) = 0 ;
	virtual HRESULT __stdcall GetCaps(TDSCCaps &lpDSCCaps) = 0 ;
	virtual HRESULT __stdcall Initialize(System::PGUID lpGuid) = 0 ;
};

__interface INTERFACE_UUID("{B0210782-89CD-11D0-AF08-00A0C925CD16}") IDirectSoundCaptureBuffer  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall GetCaps(TDSCBCaps &lpDSCBCaps) = 0 ;
	virtual HRESULT __stdcall GetCurrentPosition(unsigned &lpdwCapturePosition, unsigned &lpdwReadPosition
		) = 0 ;
	virtual HRESULT __stdcall GetFormat(tWAVEFORMATEX &lpwfxFormat, unsigned dwSizeAllocated, unsigned 
		&lpdwSizeWritten) = 0 ;
	virtual HRESULT __stdcall GetStatus(unsigned &lpdwStatus) = 0 ;
	virtual HRESULT __stdcall Initialize(_di_IDirectSoundCapture lpDirectSoundCapture, const TDSCBufferDesc 
		&lpcDSBufferDesc) = 0 ;
	virtual HRESULT __stdcall Lock(unsigned dwReadCursor, unsigned dwReadBytes, void * &lplpvAudioPtr1, 
		unsigned &lpdwAudioBytes1, void * &lplpvAudioPtr2, unsigned &lpdwAudioBytes2, unsigned dwFlags) = 0 
		;
	virtual HRESULT __stdcall Start(unsigned dwFlags) = 0 ;
	virtual HRESULT __stdcall Stop(void) = 0 ;
	virtual HRESULT __stdcall Unlock(void * lpvAudioPtr1, unsigned dwAudioBytes1, void * lpvAudioPtr2, 
		unsigned dwAudioBytes2) = 0 ;
};

__interface IDirectSoundNotify;
typedef System::DelphiInterface<IDirectSoundNotify> _di_IDirectSoundNotify;
__interface INTERFACE_UUID("{B0210783-89CD-11D0-AF08-00A0C925CD16}") IDirectSoundNotify  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall SetNotificationPositions(unsigned cPositionNotifies, const void *lpcPositionNotifies
		) = 0 ;
};

__interface IKsPropertySet;
typedef System::DelphiInterface<IKsPropertySet> _di_IKsPropertySet;
__interface INTERFACE_UUID("{31EFAC30-515C-11D0-A9AA-00AA0061BE93}") IKsPropertySet  : public IUnknown 
	
{
	
public:
	virtual HRESULT __stdcall GetProperty(const GUID &PropertySetId, unsigned PropertyId, void *pPropertyParams
		, unsigned cbPropertyParams, void *pPropertyData, unsigned cbPropertyData, unsigned &pcbReturnedData
		) = 0 ;
	virtual HRESULT __stdcall SetProperty(const GUID &PropertySetId, unsigned PropertyId, const void *pPropertyParams
		, unsigned cbPropertyParams, const void *pPropertyData, unsigned cbPropertyData) = 0 ;
	virtual HRESULT __stdcall QuerySupport(const GUID &PropertySetId, unsigned PropertyId, unsigned &pSupport
		) = 0 ;
};

typedef BOOL __stdcall (*TDSEnumCallbackW)(System::PGUID lpGuid, wchar_t * lpstrDescription, wchar_t * 
	lpstrModule, void * lpContext);

typedef BOOL __stdcall (*LPDSENUMCALLBACKW)(System::PGUID lpGuid, wchar_t * lpstrDescription, wchar_t * 
	lpstrModule, void * lpContext);

typedef BOOL __stdcall (*TDSEnumCallbackA)(System::PGUID lpGuid, char * lpstrDescription, char * lpstrModule
	, void * lpContext);

typedef BOOL __stdcall (*LPDSENUMCALLBACKA)(System::PGUID lpGuid, char * lpstrDescription, char * lpstrModule
	, void * lpContext);

typedef BOOL __stdcall (*TDSEnumCallback)(System::PGUID lpGuid, char * lpstrDescription, char * lpstrModule
	, void * lpContext);

typedef BOOL __stdcall (*LPDSENUMCALLBACK)(System::PGUID lpGuid, char * lpstrDescription, char * lpstrModule
	, void * lpContext);

//-- var, const, procedure ---------------------------------------------------
static const HRESULT DD_OK = 0x0;
static const HRESULT DD_FALSE = 0x1;
extern PACKAGE GUID CLSID_CDirectXFile;
extern PACKAGE GUID IID_IDirectXFile;
extern PACKAGE GUID IID_IDirectXFileEnumObject;
extern PACKAGE GUID IID_IDirectXFileSaveObject;
extern PACKAGE GUID IID_IDirectXFileObject;
extern PACKAGE GUID IID_IDirectXFileData;
extern PACKAGE GUID IID_IDirectXFileDataReference;
extern PACKAGE GUID IID_IDirectXFileBinary;
static const Shortint DXFILEFORMAT_BINARY = 0x0;
static const Shortint DXFILEFORMAT_TEXT = 0x1;
static const Shortint DXFILEFORMAT_COMPRESSED = 0x2;
static const Shortint DXFILELOAD_FROMFILE = 0x0;
static const Shortint DXFILELOAD_FROMRESOURCE = 0x1;
static const Shortint DXFILELOAD_FROMMEMORY = 0x2;
static const Shortint DXFILELOAD_FROMSTREAM = 0x4;
static const Shortint DXFILELOAD_FROMURL = 0x8;
extern PACKAGE GUID TID_DXFILEHeader;
static const HRESULT DXFILE_OK = 0x0;
static const HRESULT DXFILEERR_BADOBJECT = 0x88760352;
static const HRESULT DXFILEERR_BADVALUE = 0x88760353;
static const HRESULT DXFILEERR_BADTYPE = 0x88760354;
static const HRESULT DXFILEERR_BADSTREAMHANDLE = 0x88760355;
static const HRESULT DXFILEERR_BADALLOC = 0x88760356;
static const HRESULT DXFILEERR_NOTFOUND = 0x88760357;
static const HRESULT DXFILEERR_NOTDONEYET = 0x88760358;
static const HRESULT DXFILEERR_FILENOTFOUND = 0x88760359;
static const HRESULT DXFILEERR_RESOURCENOTFOUND = 0x8876035a;
static const HRESULT DXFILEERR_URLNOTFOUND = 0x8876035b;
static const HRESULT DXFILEERR_BADRESOURCE = 0x8876035c;
static const HRESULT DXFILEERR_BADFILETYPE = 0x8876035d;
static const HRESULT DXFILEERR_BADFILEVERSION = 0x8876035e;
static const HRESULT DXFILEERR_BADFILEFLOATSIZE = 0x8876035f;
static const HRESULT DXFILEERR_BADFILECOMPRESSIONTYPE = 0x88760360;
static const HRESULT DXFILEERR_BADFILE = 0x88760361;
static const HRESULT DXFILEERR_PARSEERROR = 0x88760362;
static const HRESULT DXFILEERR_NOTEMPLATE = 0x88760363;
static const HRESULT DXFILEERR_BADARRAYSIZE = 0x88760364;
static const HRESULT DXFILEERR_BADDATAREFERENCE = 0x88760365;
static const HRESULT DXFILEERR_INTERNALERROR = 0x88760366;
static const HRESULT DXFILEERR_NOMOREOBJECTS = 0x88760367;
static const HRESULT DXFILEERR_BADINTRINSICS = 0x88760368;
static const HRESULT DXFILEERR_NOMORESTREAMHANDLES = 0x88760369;
static const HRESULT DXFILEERR_NOMOREDATA = 0x8876036a;
static const HRESULT DXFILEERR_BADCACHEFILE = 0x8876036b;
static const HRESULT DXFILEERR_NOINTERNET = 0x8876036c;
extern PACKAGE GUID TID_D3DRMInfo;
extern PACKAGE GUID TID_D3DRMMesh;
extern PACKAGE GUID TID_D3DRMVector;
extern PACKAGE GUID TID_D3DRMMeshFace;
extern PACKAGE GUID TID_D3DRMMaterial;
extern PACKAGE GUID TID_D3DRMMaterialArray;
extern PACKAGE GUID TID_D3DRMFrame;
extern PACKAGE GUID TID_D3DRMFrameTransformMatrix;
extern PACKAGE GUID TID_D3DRMMeshMaterialList;
extern PACKAGE GUID TID_D3DRMMeshTextureCoords;
extern PACKAGE GUID TID_D3DRMMeshNormals;
extern PACKAGE GUID TID_D3DRMCoords2d;
extern PACKAGE GUID TID_D3DRMMatrix4x4;
extern PACKAGE GUID TID_D3DRMAnimation;
extern PACKAGE GUID TID_D3DRMAnimationSet;
extern PACKAGE GUID TID_D3DRMAnimationKey;
extern PACKAGE GUID TID_D3DRMFloatKeys;
extern PACKAGE GUID TID_D3DRMMaterialAmbientColor;
extern PACKAGE GUID TID_D3DRMMaterialDiffuseColor;
extern PACKAGE GUID TID_D3DRMMaterialSpecularColor;
extern PACKAGE GUID TID_D3DRMMaterialEmissiveColor;
extern PACKAGE GUID TID_D3DRMMaterialPower;
extern PACKAGE GUID TID_D3DRMColorRGBA;
extern PACKAGE GUID TID_D3DRMColorRGB;
extern PACKAGE GUID TID_D3DRMGuid;
extern PACKAGE GUID TID_D3DRMTextureFilename;
extern PACKAGE GUID TID_D3DRMTextureReference;
extern PACKAGE GUID TID_D3DRMIndexedColor;
extern PACKAGE GUID TID_D3DRMMeshVertexColors;
extern PACKAGE GUID TID_D3DRMMaterialWrap;
extern PACKAGE GUID TID_D3DRMBoolean;
extern PACKAGE GUID TID_D3DRMMeshFaceWraps;
extern PACKAGE GUID TID_D3DRMBoolean2d;
extern PACKAGE GUID TID_D3DRMTimedFloatKeys;
extern PACKAGE GUID TID_D3DRMAnimationOptions;
extern PACKAGE GUID TID_D3DRMFramePosition;
extern PACKAGE GUID TID_D3DRMFrameVelocity;
extern PACKAGE GUID TID_D3DRMFrameRotation;
extern PACKAGE GUID TID_D3DRMLight;
extern PACKAGE GUID TID_D3DRMCamera;
extern PACKAGE GUID TID_D3DRMAppData;
extern PACKAGE GUID TID_D3DRMLightUmbra;
extern PACKAGE GUID TID_D3DRMLightRange;
extern PACKAGE GUID TID_D3DRMLightPenumbra;
extern PACKAGE GUID TID_D3DRMLightAttenuation;
extern PACKAGE GUID TID_D3DRMInlineData;
extern PACKAGE GUID TID_D3DRMUrl;
extern PACKAGE GUID TID_D3DRMProgressiveMesh;
extern PACKAGE GUID TID_D3DRMExternalVisual;
extern PACKAGE GUID TID_D3DRMStringProperty;
extern PACKAGE GUID TID_D3DRMPropertyBag;
extern PACKAGE GUID TID_D3DRMRightHanded;
extern PACKAGE Byte D3DRM_XTEMPLATES[3215];
static const Word D3DRM_XTEMPLATE_BYTES = 0xcce;
extern PACKAGE GUID CLSID_DirectSound;
extern PACKAGE GUID CLSID_DirectSoundCapture;
extern PACKAGE GUID IID_IDirectSound;
extern PACKAGE GUID IID_IDirectSoundBuffer;
extern PACKAGE GUID IID_IDirectSound3DListener;
extern PACKAGE GUID IID_IDirectSound3DBuffer;
extern PACKAGE GUID IID_IDirectSoundCapture;
extern PACKAGE GUID IID_IDirectSoundCaptureBuffer;
extern PACKAGE GUID IID_IDirectSoundNotify;
static const Shortint KSPROPERTY_SUPPORT_GET = 0x1;
static const Shortint KSPROPERTY_SUPPORT_SET = 0x2;
extern PACKAGE GUID IID_IKsPropertySet;
static const HRESULT DS_OK = 0x0;
static const HRESULT DSERR_ALLOCATED = 0x8878000a;
static const HRESULT DSERR_CONTROLUNAVAIL = 0x8878001e;
static const HRESULT DSERR_INVALIDPARAM = 0x80070057;
static const HRESULT DSERR_INVALIDCALL = 0x88780032;
static const HRESULT DSERR_GENERIC = 0x80004005;
static const HRESULT DSERR_PRIOLEVELNEEDED = 0x88780046;
static const HRESULT DSERR_OUTOFMEMORY = 0x8007000e;
static const HRESULT DSERR_BADFORMAT = 0x88780064;
static const HRESULT DSERR_UNSUPPORTED = 0x80004001;
static const HRESULT DSERR_NODRIVER = 0x88780078;
static const HRESULT DSERR_ALREADYINITIALIZED = 0x88780082;
static const HRESULT DSERR_NOAGGREGATION = 0x80040110;
static const HRESULT DSERR_BUFFERLOST = 0x88780096;
static const HRESULT DSERR_OTHERAPPHASPRIO = 0x887800a0;
static const HRESULT DSERR_UNINITIALIZED = 0x887800aa;
static const HRESULT DSERR_NOINTERFACE = 0x80004002;
static const Shortint DSCAPS_PRIMARYMONO = 0x1;
static const Shortint DSCAPS_PRIMARYSTEREO = 0x2;
static const Shortint DSCAPS_PRIMARY8BIT = 0x4;
static const Shortint DSCAPS_PRIMARY16BIT = 0x8;
static const Shortint DSCAPS_CONTINUOUSRATE = 0x10;
static const Shortint DSCAPS_EMULDRIVER = 0x20;
static const Shortint DSCAPS_CERTIFIED = 0x40;
static const Word DSCAPS_SECONDARYMONO = 0x100;
static const Word DSCAPS_SECONDARYSTEREO = 0x200;
static const Word DSCAPS_SECONDARY8BIT = 0x400;
static const Word DSCAPS_SECONDARY16BIT = 0x800;
static const Shortint DSBPLAY_LOOPING = 0x1;
static const Shortint DSBSTATUS_PLAYING = 0x1;
static const Shortint DSBSTATUS_BUFFERLOST = 0x2;
static const Shortint DSBSTATUS_LOOPING = 0x4;
static const Shortint DSBLOCK_FROMWRITECURSOR = 0x1;
static const Shortint DSBLOCK_ENTIREBUFFER = 0x2;
static const Shortint DSSCL_NORMAL = 0x1;
static const Shortint DSSCL_PRIORITY = 0x2;
static const Shortint DSSCL_EXCLUSIVE = 0x3;
static const Shortint DSSCL_WRITEPRIMARY = 0x4;
static const Shortint DS3DMODE_NORMAL = 0x0;
static const Shortint DS3DMODE_HEADRELATIVE = 0x1;
static const Shortint DS3DMODE_DISABLE = 0x2;
static const Shortint DS3D_IMMEDIATE = 0x0;
static const Shortint DS3D_DEFERRED = 0x1;
#define DS3D_MINDISTANCEFACTOR  (0.000000E+00)
#define DS3D_MAXDISTANCEFACTOR  (1.000000E+01)
#define DS3D_DEFAULTDISTANCEFACTOR  (1.000000E+00)
#define DS3D_MINROLLOFFFACTOR  (0.000000E+00)
#define DS3D_MAXROLLOFFFACTOR  (1.000000E+01)
#define DS3D_DEFAULTROLLOFFFACTOR  (1.000000E+00)
#define DS3D_MINDOPPLERFACTOR  (0.000000E+00)
#define DS3D_MAXDOPPLERFACTOR  (1.000000E+01)
#define DS3D_DEFAULTDOPPLERFACTOR  (1.000000E+00)
#define DS3D_DEFAULTMINDISTANCE  (1.000000E+00)
#define DS3D_DEFAULTMAXDISTANCE  (1.000000E+09)
static const Shortint DS3D_MINCONEANGLE = 0x0;
static const Word DS3D_MAXCONEANGLE = 0x168;
static const Word DS3D_DEFAULTCONEANGLE = 0x168;
static const Shortint DS3D_DEFAULTCONEOUTSIDEVOLUME = 0x0;
static const Shortint DSBCAPS_PRIMARYBUFFER = 0x1;
static const Shortint DSBCAPS_STATIC = 0x2;
static const Shortint DSBCAPS_LOCHARDWARE = 0x4;
static const Shortint DSBCAPS_LOCSOFTWARE = 0x8;
static const Shortint DSBCAPS_CTRL3D = 0x10;
static const Shortint DSBCAPS_CTRLFREQUENCY = 0x20;
static const Shortint DSBCAPS_CTRLPAN = 0x40;
static const Byte DSBCAPS_CTRLVOLUME = 0x80;
static const Word DSBCAPS_CTRLPOSITIONNOTIFY = 0x100;
static const Byte DSBCAPS_CTRLDEFAULT = 0xe0;
static const Word DSBCAPS_CTRLALL = 0x1f0;
static const Word DSBCAPS_STICKYFOCUS = 0x4000;
static const Word DSBCAPS_GLOBALFOCUS = 0x8000;
static const int DSBCAPS_GETCURRENTPOSITION2 = 0x10000;
static const int DSBCAPS_MUTE3DATMAXDISTANCE = 0x20000;
static const unsigned DSCBCAPS_WAVEMAPPED = 0x80000000;
static const Shortint DSSPEAKER_HEADPHONE = 0x1;
static const Shortint DSSPEAKER_MONO = 0x2;
static const Shortint DSSPEAKER_QUAD = 0x3;
static const Shortint DSSPEAKER_STEREO = 0x4;
static const Shortint DSSPEAKER_SURROUND = 0x5;
static const Shortint DSCCAPS_EMULDRIVER = 0x20;
static const Shortint DSCBLOCK_ENTIREBUFFER = 0x1;
static const Shortint DSCBSTATUS_CAPTURING = 0x1;
static const Shortint DSCBSTATUS_LOOPING = 0x2;
static const Shortint DSCBSTART_LOOPING = 0x1;
static const Shortint DSBFREQUENCY_MIN = 0x64;
static const int DSBFREQUENCY_MAX = 0x186a0;
static const Shortint DSBFREQUENCY_ORIGINAL = 0x0;
static const short DSBPAN_LEFT = 0xffffd8f0;
static const Shortint DSBPAN_CENTER = 0x0;
static const Word DSBPAN_RIGHT = 0x2710;
static const short DSBVOLUME_MIN = 0xffffd8f0;
static const Shortint DSBVOLUME_MAX = 0x0;
static const Shortint DSBSIZE_MIN = 0x4;
static const int DSBSIZE_MAX = 0xfffffff;
static const unsigned DSBPN_OFFSETSTOP = 0xffffffff;
extern PACKAGE unsigned __fastcall DSSPEAKER_COMBINED(Byte c, Byte g);
extern PACKAGE Byte __fastcall DSSPEAKER_CONFIG(unsigned a);
extern PACKAGE Byte __fastcall DSSPEAKER_GEOMETRY(unsigned a);
extern "C" HRESULT __stdcall DirectSoundCreate(System::PGUID lpGUID, /* out */ _di_IDirectSound &lpDS
	, _di_IUnknown pUnkOuter);
extern "C" HRESULT __stdcall DirectSoundEnumerateA(TDSEnumCallbackA lpDSEnumCallback, void * lpContext
	);
extern "C" HRESULT __stdcall DirectSoundEnumerateW(TDSEnumCallbackW lpDSEnumCallback, void * lpContext
	);
extern "C" HRESULT __stdcall DirectSoundEnumerate(TDSEnumCallbackA lpDSEnumCallback, void * lpContext
	);
extern "C" HRESULT __stdcall DirectSoundCaptureCreate(System::PGUID lpGUID, /* out */ _di_IDirectSoundCapture 
	&lplpDSC, _di_IUnknown pUnkOuter);
extern "C" HRESULT __stdcall DirectSoundCaptureEnumerateA(TDSEnumCallbackA lpDSEnumCallback, void * 
	lpContext);
extern "C" HRESULT __stdcall DirectSoundCaptureEnumerateW(TDSEnumCallbackW lpDSEnumCallback, void * 
	lpContext);
extern "C" HRESULT __stdcall DirectSoundCaptureEnumerate(TDSEnumCallbackA lpDSEnumCallback, void * lpContext
	);

#if defined(UNICODE)
#pragma option push -w-inl
inline HRESULT __stdcall DirectSoundEnumerate(TDSEnumCallbackA lpDSEnumCallback, void * lpContext)
{
	return DirectSoundEnumerateW(lpDSEnumCallback, lpContext);
}
#pragma option pop

#else
#pragma option push -w-inl
inline HRESULT __stdcall DirectSoundEnumerate(TDSEnumCallbackA lpDSEnumCallback, void * lpContext)
{
	return DirectSoundEnumerateA(lpDSEnumCallback, lpContext);
}
#pragma option pop

#endif


#if defined(UNICODE)
#pragma option push -w-inl
inline HRESULT __stdcall DirectSoundCaptureEnumerate(TDSEnumCallbackA lpDSEnumCallback, void * lpContext
	)
{
	return DirectSoundCaptureEnumerateW(lpDSEnumCallback, lpContext);
}
#pragma option pop

#else
#pragma option push -w-inl
inline HRESULT __stdcall DirectSoundCaptureEnumerate(TDSEnumCallbackA lpDSEnumCallback, void * lpContext
	)
{
	return DirectSoundCaptureEnumerateA(lpDSEnumCallback, lpContext);
}
#pragma option pop

#endif


}	/* namespace Directx */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Directx;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DirectX
