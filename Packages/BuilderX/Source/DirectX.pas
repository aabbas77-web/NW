(*==========================================================================;
 *
 *  Copyright (C) 1994-1997 Microsoft Corporation.  All Rights Reserved.
 *
 *  DirectX header version 98.08.07
 *
 *  Present by Hiroyuki Hori.
 *
 *  E-Mail: hori@ingjapan.ne.jp
 *  Homepage: http://www.ingjapan.ne.jp/hori/index-e.html
 *
 *  Present unit:
 *    DirectX.pas    DirectX 6 (DirectX 6 SDK)
 *    DShow.pas      DirectShow (DirectX Media SDK 5.1)
 *    DAnim.pas      DirectAnimation (DirectX Media SDK 5.1)
 *
 ***************************************************************************)

unit DirectX;

interface

{$Z4}
{$A+}
{$WEAKPACKAGEUNIT}

{$IFNDEF DirectX3}
{$IFNDEF DirectX5}
{$IFNDEF DirectX6}
  {$DEFINE DirectX6}
{$ENDIF}
{$ENDIF}
{$ENDIF}

{$IFDEF DirectX3}
  {$UNDEF DirectX1}
  {$UNDEF DirectX2}
  {$UNDEF DirectX4}
  {$UNDEF DirectX5}
  {$UNDEF DirectX6}
  {$DEFINE OlderThanDirectX5}
{$ENDIF}

{$IFDEF DirectX5}
  {$UNDEF DirectX1}
  {$UNDEF DirectX2}
  {$UNDEF DirectX3}
  {$UNDEF DirectX4}
  {$UNDEF DirectX6}
{$ENDIF}

{$IFDEF DirectX6}
  {$UNDEF DirectX1}
  {$UNDEF DirectX2}
  {$UNDEF DirectX3}
  {$UNDEF DirectX4}
  {$UNDEF DirectX5}
{$ENDIF}

uses Windows, MMSystem;

{ DirectDraw Return Codes }

const
  DD_OK                                   = HResult(0);
  DD_FALSE                                = HResult(S_FALSE);
  
(***************************************************************************
 *
 *  Copyright (C) 1998-1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       dxfile.h
 *
 *  Content:    DirectX File public header file
 *
 ***************************************************************************)

{ DirectXFile Object Class Id (for CoCreateInstance()) }

const
  CLSID_CDirectXFile: TGUID = '{4516EC43-8F20-11D0-9B6D-0000C0781BC3}';

{ DirectX File Interface GUIDs. }

  IID_IDirectXFile: TGUID = '{3D82AB40-62DA-11CF-AB39-0020AF71E433}';
  IID_IDirectXFileEnumObject: TGUID = '{3D82AB41-62DA-11CF-AB39-0020AF71E433}';
  IID_IDirectXFileSaveObject: TGUID = '{3D82AB42-62DA-11CF-AB39-0020AF71E433}';
  IID_IDirectXFileObject: TGUID = '{3D82AB43-62DA-11CF-AB39-0020AF71E433}';
  IID_IDirectXFileData: TGUID = '{3D82AB44-62DA-11CF-AB39-0020AF71E433}';
  IID_IDirectXFileDataReference: TGUID = '{3D82AB45-62DA-11CF-AB39-0020AF71E433}';
  IID_IDirectXFileBinary: TGUID = '{3D82AB46-62DA-11CF-AB39-0020AF71E433}';

type
  TDXFileFormat = DWORD;
  DXFILEFORMAT = TDXFileFormat;

const
  DXFILEFORMAT_BINARY     = 0;
  DXFILEFORMAT_TEXT       = 1;
  DXFILEFORMAT_COMPRESSED = 2;

type
  TDXFileLoadOptions = DWORD;
  DXFILELOADOPTIONS = TDXFileLoadOptions;

const
  DXFILELOAD_FROMFILE     = $00;
  DXFILELOAD_FROMRESOURCE = $01;
  DXFILELOAD_FROMMEMORY   = $02;
  DXFILELOAD_FROMSTREAM   = $04;
  DXFILELOAD_FROMURL      = $08;

type
  PDXFileLoadResource = ^TDXFileLoadResource;
  TDXFileLoadResource = record
    hModule: HModule;
    lpName: PChar;
    lpType: PChar;
  end;

  DXFILELOADRESOURCE = TDXFileLoadResource;
  LPDXFILELOADRESOURCE = PDXFileLoadResource;

  PDXFileLoadMemory = ^TDXFileLoadMemory;
  TDXFileLoadMemory = record
    lpMemory: Pointer;
    dSize: DWORD;
  end;

  DXFILELOADMEMORY = TDXFileLoadMemory;
  LPDXFILELOADMEMORY = PDXFileLoadMemory;

{ DirectX File object types. }

type
  IDirectXFile = interface;
  IDirectXFileEnumObject = interface;
  IDirectXFileSaveObject = interface;
  IDirectXFileObject = interface;
  IDirectXFileData = interface;
  IDirectXFileDataReference = interface;
  IDirectXFileBinary = interface;

  IDirectXFile = interface(IUnknown)
    ['{3D82AB40-62DA-11CF-AB39-0020AF71E433}']
    function CreateEnumObject(pvSource: Pointer; dwLoadOptions: TDXFileLoadOptions;
        out ppEnumObj: IDirectXFileEnumObject): HResult; stdcall;
    function CreateSaveObject(szFileName: PChar; dwFileFormat: TDXFileFormat;
        out ppSaveObj: IDirectXFileSaveObject): HResult; stdcall;
    function RegisterTemplates(pvData: Pointer; cbSize: DWORD): HResult; stdcall;
  end;

  IDirectXFileEnumObject = interface(IUnknown)
    ['{3D82AB41-62DA-11CF-AB39-0020AF71E433}']
    function GetNextDataObject(out ppDataObj: IDirectXFileData): HResult; stdcall;
    function GetDataObjectById(const rguid: TGUID; out ppDataObj: IDirectXFileData): HResult; stdcall;
    function GetDataObjectByName(szName: PChar; out ppDataObj: IDirectXFileData): HResult; stdcall;
  end;

  IDirectXFileSaveObject = interface(IUnknown)
    ['{3D82AB42-62DA-11CF-AB39-0020AF71E433}']
    function SaveTemplates(cTemplates: DWORD; var ppguidTemplates: PGUID): HResult; stdcall;
    function CreateDataObject(const rguidTemplate: TGUID; szName: PChar;
        const pguid: TGUID; cbSize: DWORD; pvData: Pointer;
        out ppDataObj: IDirectXFileData): HResult; stdcall;
    function SaveData(pDataObj: IDirectXFileData): HResult; stdcall;
  end;

  IDirectXFileObject = interface(IUnknown)
    ['{3D82AB43-62DA-11CF-AB39-0020AF71E433}']
    function GetName(pstrNameBuf: PChar; var dwBufLen: DWORD): HResult; stdcall;
    function GetId (var pGuidBuf: TGUID): HResult; stdcall;
  end;

  IDirectXFileData = interface(IDirectXFileObject)
    ['{3D82AB44-62DA-11CF-AB39-0020AF71E433}']
    function GetData(szMember: PChar; var pcbSize: DWORD; var ppvData: Pointer): HResult; stdcall;
    function GetType(var ppguid: PGUID): HResult; stdcall;
    function GetNextObject(out ppChildObj: IDirectXFileObject): HResult; stdcall;
    function AddDataObject(pDataObj: IDirectXFileData): HResult; stdcall;
    function AddDataReference(szRef: PChar; pguidRef: PGUID): HResult; stdcall;
    function AddBinaryObjec (szName: PChar; pguid: PGUID; szMimeType: PChar;
        pvData: Pointer; cbSize: DWORD): HResult; stdcall;
  end;

  IDirectXFileDataReference = interface(IDirectXFileObject)
    ['{3D82AB45-62DA-11CF-AB39-0020AF71E433}']
    function Resolve(out ppDataObj: IDirectXFileData): HResult; stdcall;
  end;

  IDirectXFileBinary = interface(IDirectXFileObject)
    ['{3D82AB46-62DA-11CF-AB39-0020AF71E433}']
    function GetSize(var pcbSize: DWORD): HResult; stdcall;
    function GetMimeType(var pszMimeType: PChar): HResult; stdcall;
    function Read(pvData: Pointer; cbSize: DWORD; var pcbRead: DWORD): HResult; stdcall;
  end;

{ DirectX File Header template's GUID. }

const
  TID_DXFILEHeader: TGUID = '{3D82AB43-62DA-11CF-AB39-0020AF71E433}';

{ DirectX File errors. }

const
  DXFILE_OK                         = HResult(0);

  DXFILEERR_BADOBJECT               = HResult($88760000 + 850);
  DXFILEERR_BADVALUE                = HResult($88760000 + 851);
  DXFILEERR_BADTYPE                 = HResult($88760000 + 852);
  DXFILEERR_BADSTREAMHANDLE         = HResult($88760000 + 853);
  DXFILEERR_BADALLOC                = HResult($88760000 + 854);
  DXFILEERR_NOTFOUND                = HResult($88760000 + 855);
  DXFILEERR_NOTDONEYET              = HResult($88760000 + 856);
  DXFILEERR_FILENOTFOUND            = HResult($88760000 + 857);
  DXFILEERR_RESOURCENOTFOUND        = HResult($88760000 + 858);
  DXFILEERR_URLNOTFOUND             = HResult($88760000 + 859);
  DXFILEERR_BADRESOURCE             = HResult($88760000 + 860);
  DXFILEERR_BADFILETYPE             = HResult($88760000 + 861);
  DXFILEERR_BADFILEVERSION          = HResult($88760000 + 862);
  DXFILEERR_BADFILEFLOATSIZE        = HResult($88760000 + 863);
  DXFILEERR_BADFILECOMPRESSIONTYPE  = HResult($88760000 + 864);
  DXFILEERR_BADFILE                 = HResult($88760000 + 865);
  DXFILEERR_PARSEERROR              = HResult($88760000 + 866);
  DXFILEERR_NOTEMPLATE              = HResult($88760000 + 867);
  DXFILEERR_BADARRAYSIZE            = HResult($88760000 + 868);
  DXFILEERR_BADDATAREFERENCE        = HResult($88760000 + 869);
  DXFILEERR_INTERNALERROR           = HResult($88760000 + 870);
  DXFILEERR_NOMOREOBJECTS           = HResult($88760000 + 871);
  DXFILEERR_BADINTRINSICS           = HResult($88760000 + 872);
  DXFILEERR_NOMORESTREAMHANDLES     = HResult($88760000 + 873);
  DXFILEERR_NOMOREDATA              = HResult($88760000 + 874);
  DXFILEERR_BADCACHEFILE            = HResult($88760000 + 875);
  DXFILEERR_NOINTERNET              = HResult($88760000 + 876);

(***************************************************************************
 *
 *  Copyright (C) 1998-1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       rmxfguid.h
 *
 *  Content:    Defines GUIDs of D3DRM's templates.
 *
 ***************************************************************************)

const
  TID_D3DRMInfo: TGUID = '{2B957100-9E9A-11cf-AB39-0020AF71E433}';
  TID_D3DRMMesh: TGUID = '{3D82AB44-62DA-11cf-AB39-0020AF71E433}';
  TID_D3DRMVector: TGUID = '{3D82AB5E-62DA-11cf-AB39-0020AF71E433}';
  TID_D3DRMMeshFace: TGUID = '{3D82AB5F-62DA-11cf-AB39-0020AF71E433}';
  TID_D3DRMMaterial: TGUID = '{3D82AB4D-62DA-11cf-AB39-0020AF71E433}';
  TID_D3DRMMaterialArray: TGUID = '{35FF44E1-6C7C-11cf-8F52-0040333594A3}';
  TID_D3DRMFrame: TGUID = '{3D82AB46-62DA-11cf-AB39-0020AF71E433}';
  TID_D3DRMFrameTransformMatrix: TGUID = '{F6F23F41-7686-11cf-8F52-0040333594A3}';
  TID_D3DRMMeshMaterialList: TGUID = '{F6F23F42-7686-11cf-8F52-0040333594A3}';
  TID_D3DRMMeshTextureCoords: TGUID = '{F6F23F40-7686-11cf-8F52-0040333594A3}';
  TID_D3DRMMeshNormals: TGUID = '{F6F23F43-7686-11cf-8F52-0040333594A3}';
  TID_D3DRMCoords2d: TGUID = '{F6F23F44-7686-11cf-8F52-0040333594A3}';
  TID_D3DRMMatrix4x4: TGUID = '{F6F23F45-7686-11cf-8F52-0040333594A3}';
  TID_D3DRMAnimation: TGUID = '{3D82AB4F-62DA-11cf-AB39-0020AF71E433}';
  TID_D3DRMAnimationSet: TGUID = '{3D82AB50-62DA-11cf-AB39-0020AF71E433}';
  TID_D3DRMAnimationKey: TGUID = '{10DD46A8-775B-11cf-8F52-0040333594A3}';
  TID_D3DRMFloatKeys: TGUID = '{10DD46A9-775B-11cf-8F52-0040333594A3}';
  TID_D3DRMMaterialAmbientColor: TGUID = '{01411840-7786-11cf-8F52-0040333594A3}';
  TID_D3DRMMaterialDiffuseColor: TGUID = '{01411841-7786-11cf-8F52-0040333594A3}';
  TID_D3DRMMaterialSpecularColor: TGUID = '{01411842-7786-11cf-8F52-0040333594A3}';
  TID_D3DRMMaterialEmissiveColor: TGUID = '{D3E16E80-7835-11cf-8F52-0040333594A3}';
  TID_D3DRMMaterialPower: TGUID = '{01411843-7786-11cf-8F52-0040333594A3}';
  TID_D3DRMColorRGBA: TGUID = '{35FF44E0-6C7C-11cf-8F52-0040333594A3}';
  TID_D3DRMColorRGB: TGUID = '{D3E16E81-7835-11cf-8F52-0040333594A3}';
  TID_D3DRMGuid: TGUID = '{A42790E0-7810-11cf-8F52-0040333594A3}';
  TID_D3DRMTextureFilename: TGUID = '{A42790E1-7810-11cf-8F52-0040333594A3}';
  TID_D3DRMTextureReference: TGUID = '{A42790E2-7810-11cf-8F52-0040333594A3}';
  TID_D3DRMIndexedColor: TGUID = '{1630B820-7842-11cf-8F52-0040333594A3}';
  TID_D3DRMMeshVertexColors: TGUID = '{1630B821-7842-11cf-8F52-0040333594A3}';
  TID_D3DRMMaterialWrap: TGUID = '{4885AE60-78E8-11cf-8F52-0040333594A3}';
  TID_D3DRMBoolean: TGUID = '{537DA6A0-CA37-11d0-941C-0080C80CFA7B}';
  TID_D3DRMMeshFaceWraps: TGUID = '{ED1EC5C0-C0A8-11d0-941C-0080C80CFA7B}';
  TID_D3DRMBoolean2d: TGUID = '{4885AE63-78E8-11cf-8F52-0040333594A3}';
  TID_D3DRMTimedFloatKeys: TGUID = '{F406B180-7B3B-11cf-8F52-0040333594A3}';
  TID_D3DRMAnimationOptions: TGUID = '{E2BF56C0-840F-11cf-8F52-0040333594A3}';
  TID_D3DRMFramePosition: TGUID = '{E2BF56C1-840F-11cf-8F52-0040333594A3}';
  TID_D3DRMFrameVelocity: TGUID = '{E2BF56C2-840F-11cf-8F52-0040333594A3}';
  TID_D3DRMFrameRotation: TGUID = '{E2BF56C3-840F-11cf-8F52-0040333594A3}';
  TID_D3DRMLight: TGUID = '{3D82AB4A-62DA-11cf-AB39-0020AF71E433}';
  TID_D3DRMCamera: TGUID = '{3D82AB51-62DA-11cf-AB39-0020AF71E433}';
  TID_D3DRMAppData: TGUID = '{E5745280-B24F-11cf-9DD5-00AA00A71A2F}';
  TID_D3DRMLightUmbra: TGUID = '{AED22740-B31F-11cf-9DD5-00AA00A71A2F}';
  TID_D3DRMLightRange: TGUID = '{AED22742-B31F-11cf-9DD5-00AA00A71A2F}';
  TID_D3DRMLightPenumbra: TGUID = '{AED22741-B31F-11cf-9DD5-00AA00A71A2F}';
  TID_D3DRMLightAttenuation: TGUID = '{A8A98BA0-C5E5-11cf-B941-0080C80CFA7B}';
  TID_D3DRMInlineData: TGUID = '{3A23EEA0-94B1-11d0-AB39-0020AF71E433}';
  TID_D3DRMUrl: TGUID = '{3A23EEA1-94B1-11d0-AB39-0020AF71E433}';

  TID_D3DRMProgressiveMesh: TGUID = '{8A63C360-997D-11d0-941C-0080C80CFA7B}';
  TID_D3DRMExternalVisual: TGUID = '{98116AA0-BDBA-11d1-82C0-00A0C9697271}';
  TID_D3DRMStringProperty: TGUID = '{7F0F21E0-BFE1-11d1-82C0-00A0C9697271}';
  TID_D3DRMPropertyBag: TGUID = '{7F0F21E1-BFE1-11d1-82C0-00A0C9697271}';
  TID_D3DRMRightHanded: TGUID = '{7F5D5EA0-D53A-11d1-82C0-00A0C9697271}';

(***************************************************************************
 *
 *  Copyright (C) 1998-1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       rmxftmpl.h
 *
 *  Content:    D3DRM XFile templates in binary form.
 *
 ***************************************************************************)

const
  D3DRM_XTEMPLATES: array [0..3214] of byte = (
        $78, $6f, $66, $20, $30, $33, $30, $32, $62,
        $69, $6e, $20, $30, $30, $36, $34, $1f, 0, $1,
        0, $6, 0, 0, 0, $48, $65, $61, $64, $65,
        $72, $a, 0, $5, 0, $43, $ab, $82, $3d, $da,
        $62, $cf, $11, $ab, $39, 0, $20, $af, $71, $e4,
        $33, $28, 0, $1, 0, $5, 0, 0, 0, $6d,
        $61, $6a, $6f, $72, $14, 0, $28, 0, $1, 0,
        $5, 0, 0, 0, $6d, $69, $6e, $6f, $72, $14,
        0, $29, 0, $1, 0, $5, 0, 0, 0, $66,
        $6c, $61, $67, $73, $14, 0, $b, 0, $1f, 0,
        $1, 0, $6, 0, 0, 0, $56, $65, $63, $74,
        $6f, $72, $a, 0, $5, 0, $5e, $ab, $82, $3d,
        $da, $62, $cf, $11, $ab, $39, 0, $20, $af, $71,
        $e4, $33, $2a, 0, $1, 0, $1, 0, 0, 0,
        $78, $14, 0, $2a, 0, $1, 0, $1, 0, 0,
        0, $79, $14, 0, $2a, 0, $1, 0, $1, 0,
        0, 0, $7a, $14, 0, $b, 0, $1f, 0, $1,
        0, $8, 0, 0, 0, $43, $6f, $6f, $72, $64,
        $73, $32, $64, $a, 0, $5, 0, $44, $3f, $f2,
        $f6, $86, $76, $cf, $11, $8f, $52, 0, $40, $33,
        $35, $94, $a3, $2a, 0, $1, 0, $1, 0, 0,
        0, $75, $14, 0, $2a, 0, $1, 0, $1, 0,
        0, 0, $76, $14, 0, $b, 0, $1f, 0, $1,
        0, $9, 0, 0, 0, $4d, $61, $74, $72, $69,
        $78, $34, $78, $34, $a, 0, $5, 0, $45, $3f,
        $f2, $f6, $86, $76, $cf, $11, $8f, $52, 0, $40,
        $33, $35, $94, $a3, $34, 0, $2a, 0, $1, 0,
        $6, 0, 0, 0, $6d, $61, $74, $72, $69, $78,
        $e, 0, $3, 0, $10, 0, 0, 0, $f, 0,
        $14, 0, $b, 0, $1f, 0, $1, 0, $9, 0,
        0, 0, $43, $6f, $6c, $6f, $72, $52, $47, $42,
        $41, $a, 0, $5, 0, $e0, $44, $ff, $35, $7c,
        $6c, $cf, $11, $8f, $52, 0, $40, $33, $35, $94,
        $a3, $2a, 0, $1, 0, $3, 0, 0, 0, $72,
        $65, $64, $14, 0, $2a, 0, $1, 0, $5, 0,
        0, 0, $67, $72, $65, $65, $6e, $14, 0, $2a,
        0, $1, 0, $4, 0, 0, 0, $62, $6c, $75,
        $65, $14, 0, $2a, 0, $1, 0, $5, 0, 0,
        0, $61, $6c, $70, $68, $61, $14, 0, $b, 0,
        $1f, 0, $1, 0, $8, 0, 0, 0, $43, $6f,
        $6c, $6f, $72, $52, $47, $42, $a, 0, $5, 0,
        $81, $6e, $e1, $d3, $35, $78, $cf, $11, $8f, $52,
        0, $40, $33, $35, $94, $a3, $2a, 0, $1, 0,
        $3, 0, 0, 0, $72, $65, $64, $14, 0, $2a,
        0, $1, 0, $5, 0, 0, 0, $67, $72, $65,
        $65, $6e, $14, 0, $2a, 0, $1, 0, $4, 0,
        0, 0, $62, $6c, $75, $65, $14, 0, $b, 0,
        $1f, 0, $1, 0, $c, 0, 0, 0, $49, $6e,
        $64, $65, $78, $65, $64, $43, $6f, $6c, $6f, $72,
        $a, 0, $5, 0, $20, $b8, $30, $16, $42, $78,
        $cf, $11, $8f, $52, 0, $40, $33, $35, $94, $a3,
        $29, 0, $1, 0, $5, 0, 0, 0, $69, $6e,
        $64, $65, $78, $14, 0, $1, 0, $9, 0, 0,
        0, $43, $6f, $6c, $6f, $72, $52, $47, $42, $41,
        $1, 0, $a, 0, 0, 0, $69, $6e, $64, $65,
        $78, $43, $6f, $6c, $6f, $72, $14, 0, $b, 0,
        $1f, 0, $1, 0, $7, 0, 0, 0, $42, $6f,
        $6f, $6c, $65, $61, $6e, $a, 0, $5, 0, $a0,
        $a6, $7d, $53, $37, $ca, $d0, $11, $94, $1c, 0,
        $80, $c8, $c, $fa, $7b, $29, 0, $1, 0, $9,
        0, 0, 0, $74, $72, $75, $65, $66, $61, $6c,
        $73, $65, $14, 0, $b, 0, $1f, 0, $1, 0,
        $9, 0, 0, 0, $42, $6f, $6f, $6c, $65, $61,
        $6e, $32, $64, $a, 0, $5, 0, $63, $ae, $85,
        $48, $e8, $78, $cf, $11, $8f, $52, 0, $40, $33,
        $35, $94, $a3, $1, 0, $7, 0, 0, 0, $42,
        $6f, $6f, $6c, $65, $61, $6e, $1, 0, $1, 0,
        0, 0, $75, $14, 0, $1, 0, $7, 0, 0,
        0, $42, $6f, $6f, $6c, $65, $61, $6e, $1, 0,
        $1, 0, 0, 0, $76, $14, 0, $b, 0, $1f,
        0, $1, 0, $c, 0, 0, 0, $4d, $61, $74,
        $65, $72, $69, $61, $6c, $57, $72, $61, $70, $a,
        0, $5, 0, $60, $ae, $85, $48, $e8, $78, $cf,
        $11, $8f, $52, 0, $40, $33, $35, $94, $a3, $1,
        0, $7, 0, 0, 0, $42, $6f, $6f, $6c, $65,
        $61, $6e, $1, 0, $1, 0, 0, 0, $75, $14,
        0, $1, 0, $7, 0, 0, 0, $42, $6f, $6f,
        $6c, $65, $61, $6e, $1, 0, $1, 0, 0, 0,
        $76, $14, 0, $b, 0, $1f, 0, $1, 0, $f,
        0, 0, 0, $54, $65, $78, $74, $75, $72, $65,
        $46, $69, $6c, $65, $6e, $61, $6d, $65, $a, 0,
        $5, 0, $e1, $90, $27, $a4, $10, $78, $cf, $11,
        $8f, $52, 0, $40, $33, $35, $94, $a3, $31, 0,
        $1, 0, $8, 0, 0, 0, $66, $69, $6c, $65,
        $6e, $61, $6d, $65, $14, 0, $b, 0, $1f, 0,
        $1, 0, $8, 0, 0, 0, $4d, $61, $74, $65,
        $72, $69, $61, $6c, $a, 0, $5, 0, $4d, $ab,
        $82, $3d, $da, $62, $cf, $11, $ab, $39, 0, $20,
        $af, $71, $e4, $33, $1, 0, $9, 0, 0, 0,
        $43, $6f, $6c, $6f, $72, $52, $47, $42, $41, $1,
        0, $9, 0, 0, 0, $66, $61, $63, $65, $43,
        $6f, $6c, $6f, $72, $14, 0, $2a, 0, $1, 0,
        $5, 0, 0, 0, $70, $6f, $77, $65, $72, $14,
        0, $1, 0, $8, 0, 0, 0, $43, $6f, $6c,
        $6f, $72, $52, $47, $42, $1, 0, $d, 0, 0,
        0, $73, $70, $65, $63, $75, $6c, $61, $72, $43,
        $6f, $6c, $6f, $72, $14, 0, $1, 0, $8, 0,
        0, 0, $43, $6f, $6c, $6f, $72, $52, $47, $42,
        $1, 0, $d, 0, 0, 0, $65, $6d, $69, $73,
        $73, $69, $76, $65, $43, $6f, $6c, $6f, $72, $14,
        0, $e, 0, $12, 0, $12, 0, $12, 0, $f,
        0, $b, 0, $1f, 0, $1, 0, $8, 0, 0,
        0, $4d, $65, $73, $68, $46, $61, $63, $65, $a,
        0, $5, 0, $5f, $ab, $82, $3d, $da, $62, $cf,
        $11, $ab, $39, 0, $20, $af, $71, $e4, $33, $29,
        0, $1, 0, $12, 0, 0, 0, $6e, $46, $61,
        $63, $65, $56, $65, $72, $74, $65, $78, $49, $6e,
        $64, $69, $63, $65, $73, $14, 0, $34, 0, $29,
        0, $1, 0, $11, 0, 0, 0, $66, $61, $63,
        $65, $56, $65, $72, $74, $65, $78, $49, $6e, $64,
        $69, $63, $65, $73, $e, 0, $1, 0, $12, 0,
        0, 0, $6e, $46, $61, $63, $65, $56, $65, $72,
        $74, $65, $78, $49, $6e, $64, $69, $63, $65, $73,
        $f, 0, $14, 0, $b, 0, $1f, 0, $1, 0,
        $d, 0, 0, 0, $4d, $65, $73, $68, $46, $61,
        $63, $65, $57, $72, $61, $70, $73, $a, 0, $5,
        0, $c0, $c5, $1e, $ed, $a8, $c0, $d0, $11, $94,
        $1c, 0, $80, $c8, $c, $fa, $7b, $29, 0, $1,
        0, $f, 0, 0, 0, $6e, $46, $61, $63, $65,
        $57, $72, $61, $70, $56, $61, $6c, $75, $65, $73,
        $14, 0, $34, 0, $1, 0, $9, 0, 0, 0,
        $42, $6f, $6f, $6c, $65, $61, $6e, $32, $64, $1,
        0, $e, 0, 0, 0, $66, $61, $63, $65, $57,
        $72, $61, $70, $56, $61, $6c, $75, $65, $73, $e,
        0, $1, 0, $f, 0, 0, 0, $6e, $46, $61,
        $63, $65, $57, $72, $61, $70, $56, $61, $6c, $75,
        $65, $73, $f, 0, $14, 0, $b, 0, $1f, 0,
        $1, 0, $11, 0, 0, 0, $4d, $65, $73, $68,
        $54, $65, $78, $74, $75, $72, $65, $43, $6f, $6f,
        $72, $64, $73, $a, 0, $5, 0, $40, $3f, $f2,
        $f6, $86, $76, $cf, $11, $8f, $52, 0, $40, $33,
        $35, $94, $a3, $29, 0, $1, 0, $e, 0, 0,
        0, $6e, $54, $65, $78, $74, $75, $72, $65, $43,
        $6f, $6f, $72, $64, $73, $14, 0, $34, 0, $1,
        0, $8, 0, 0, 0, $43, $6f, $6f, $72, $64,
        $73, $32, $64, $1, 0, $d, 0, 0, 0, $74,
        $65, $78, $74, $75, $72, $65, $43, $6f, $6f, $72,
        $64, $73, $e, 0, $1, 0, $e, 0, 0, 0,
        $6e, $54, $65, $78, $74, $75, $72, $65, $43, $6f,
        $6f, $72, $64, $73, $f, 0, $14, 0, $b, 0,
        $1f, 0, $1, 0, $10, 0, 0, 0, $4d, $65,
        $73, $68, $4d, $61, $74, $65, $72, $69, $61, $6c,
        $4c, $69, $73, $74, $a, 0, $5, 0, $42, $3f,
        $f2, $f6, $86, $76, $cf, $11, $8f, $52, 0, $40,
        $33, $35, $94, $a3, $29, 0, $1, 0, $a, 0,
        0, 0, $6e, $4d, $61, $74, $65, $72, $69, $61,
        $6c, $73, $14, 0, $29, 0, $1, 0, $c, 0,
        0, 0, $6e, $46, $61, $63, $65, $49, $6e, $64,
        $65, $78, $65, $73, $14, 0, $34, 0, $29, 0,
        $1, 0, $b, 0, 0, 0, $66, $61, $63, $65,
        $49, $6e, $64, $65, $78, $65, $73, $e, 0, $1,
        0, $c, 0, 0, 0, $6e, $46, $61, $63, $65,
        $49, $6e, $64, $65, $78, $65, $73, $f, 0, $14,
        0, $e, 0, $1, 0, $8, 0, 0, 0, $4d,
        $61, $74, $65, $72, $69, $61, $6c, $f, 0, $b,
        0, $1f, 0, $1, 0, $b, 0, 0, 0, $4d,
        $65, $73, $68, $4e, $6f, $72, $6d, $61, $6c, $73,
        $a, 0, $5, 0, $43, $3f, $f2, $f6, $86, $76,
        $cf, $11, $8f, $52, 0, $40, $33, $35, $94, $a3,
        $29, 0, $1, 0, $8, 0, 0, 0, $6e, $4e,
        $6f, $72, $6d, $61, $6c, $73, $14, 0, $34, 0,
        $1, 0, $6, 0, 0, 0, $56, $65, $63, $74,
        $6f, $72, $1, 0, $7, 0, 0, 0, $6e, $6f,
        $72, $6d, $61, $6c, $73, $e, 0, $1, 0, $8,
        0, 0, 0, $6e, $4e, $6f, $72, $6d, $61, $6c,
        $73, $f, 0, $14, 0, $29, 0, $1, 0, $c,
        0, 0, 0, $6e, $46, $61, $63, $65, $4e, $6f,
        $72, $6d, $61, $6c, $73, $14, 0, $34, 0, $1,
        0, $8, 0, 0, 0, $4d, $65, $73, $68, $46,
        $61, $63, $65, $1, 0, $b, 0, 0, 0, $66,
        $61, $63, $65, $4e, $6f, $72, $6d, $61, $6c, $73,
        $e, 0, $1, 0, $c, 0, 0, 0, $6e, $46,
        $61, $63, $65, $4e, $6f, $72, $6d, $61, $6c, $73,
        $f, 0, $14, 0, $b, 0, $1f, 0, $1, 0,
        $10, 0, 0, 0, $4d, $65, $73, $68, $56, $65,
        $72, $74, $65, $78, $43, $6f, $6c, $6f, $72, $73,
        $a, 0, $5, 0, $21, $b8, $30, $16, $42, $78,
        $cf, $11, $8f, $52, 0, $40, $33, $35, $94, $a3,
        $29, 0, $1, 0, $d, 0, 0, 0, $6e, $56,
        $65, $72, $74, $65, $78, $43, $6f, $6c, $6f, $72,
        $73, $14, 0, $34, 0, $1, 0, $c, 0, 0,
        0, $49, $6e, $64, $65, $78, $65, $64, $43, $6f,
        $6c, $6f, $72, $1, 0, $c, 0, 0, 0, $76,
        $65, $72, $74, $65, $78, $43, $6f, $6c, $6f, $72,
        $73, $e, 0, $1, 0, $d, 0, 0, 0, $6e,
        $56, $65, $72, $74, $65, $78, $43, $6f, $6c, $6f,
        $72, $73, $f, 0, $14, 0, $b, 0, $1f, 0,
        $1, 0, $4, 0, 0, 0, $4d, $65, $73, $68,
        $a, 0, $5, 0, $44, $ab, $82, $3d, $da, $62,
        $cf, $11, $ab, $39, 0, $20, $af, $71, $e4, $33,
        $29, 0, $1, 0, $9, 0, 0, 0, $6e, $56,
        $65, $72, $74, $69, $63, $65, $73, $14, 0, $34,
        0, $1, 0, $6, 0, 0, 0, $56, $65, $63,
        $74, $6f, $72, $1, 0, $8, 0, 0, 0, $76,
        $65, $72, $74, $69, $63, $65, $73, $e, 0, $1,
        0, $9, 0, 0, 0, $6e, $56, $65, $72, $74,
        $69, $63, $65, $73, $f, 0, $14, 0, $29, 0,
        $1, 0, $6, 0, 0, 0, $6e, $46, $61, $63,
        $65, $73, $14, 0, $34, 0, $1, 0, $8, 0,
        0, 0, $4d, $65, $73, $68, $46, $61, $63, $65,
        $1, 0, $5, 0, 0, 0, $66, $61, $63, $65,
        $73, $e, 0, $1, 0, $6, 0, 0, 0, $6e,
        $46, $61, $63, $65, $73, $f, 0, $14, 0, $e,
        0, $12, 0, $12, 0, $12, 0, $f, 0, $b,
        0, $1f, 0, $1, 0, $14, 0, 0, 0, $46,
        $72, $61, $6d, $65, $54, $72, $61, $6e, $73, $66,
        $6f, $72, $6d, $4d, $61, $74, $72, $69, $78, $a,
        0, $5, 0, $41, $3f, $f2, $f6, $86, $76, $cf,
        $11, $8f, $52, 0, $40, $33, $35, $94, $a3, $1,
        0, $9, 0, 0, 0, $4d, $61, $74, $72, $69,
        $78, $34, $78, $34, $1, 0, $b, 0, 0, 0,
        $66, $72, $61, $6d, $65, $4d, $61, $74, $72, $69,
        $78, $14, 0, $b, 0, $1f, 0, $1, 0, $5,
        0, 0, 0, $46, $72, $61, $6d, $65, $a, 0,
        $5, 0, $46, $ab, $82, $3d, $da, $62, $cf, $11,
        $ab, $39, 0, $20, $af, $71, $e4, $33, $e, 0,
        $12, 0, $12, 0, $12, 0, $f, 0, $b, 0,
        $1f, 0, $1, 0, $9, 0, 0, 0, $46, $6c,
        $6f, $61, $74, $4b, $65, $79, $73, $a, 0, $5,
        0, $a9, $46, $dd, $10, $5b, $77, $cf, $11, $8f,
        $52, 0, $40, $33, $35, $94, $a3, $29, 0, $1,
        0, $7, 0, 0, 0, $6e, $56, $61, $6c, $75,
        $65, $73, $14, 0, $34, 0, $2a, 0, $1, 0,
        $6, 0, 0, 0, $76, $61, $6c, $75, $65, $73,
        $e, 0, $1, 0, $7, 0, 0, 0, $6e, $56,
        $61, $6c, $75, $65, $73, $f, 0, $14, 0, $b,
        0, $1f, 0, $1, 0, $e, 0, 0, 0, $54,
        $69, $6d, $65, $64, $46, $6c, $6f, $61, $74, $4b,
        $65, $79, $73, $a, 0, $5, 0, $80, $b1, $6,
        $f4, $3b, $7b, $cf, $11, $8f, $52, 0, $40, $33,
        $35, $94, $a3, $29, 0, $1, 0, $4, 0, 0,
        0, $74, $69, $6d, $65, $14, 0, $1, 0, $9,
        0, 0, 0, $46, $6c, $6f, $61, $74, $4b, $65,
        $79, $73, $1, 0, $6, 0, 0, 0, $74, $66,
        $6b, $65, $79, $73, $14, 0, $b, 0, $1f, 0,
        $1, 0, $c, 0, 0, 0, $41, $6e, $69, $6d,
        $61, $74, $69, $6f, $6e, $4b, $65, $79, $a, 0,
        $5, 0, $a8, $46, $dd, $10, $5b, $77, $cf, $11,
        $8f, $52, 0, $40, $33, $35, $94, $a3, $29, 0,
        $1, 0, $7, 0, 0, 0, $6b, $65, $79, $54,
        $79, $70, $65, $14, 0, $29, 0, $1, 0, $5,
        0, 0, 0, $6e, $4b, $65, $79, $73, $14, 0,
        $34, 0, $1, 0, $e, 0, 0, 0, $54, $69,
        $6d, $65, $64, $46, $6c, $6f, $61, $74, $4b, $65,
        $79, $73, $1, 0, $4, 0, 0, 0, $6b, $65,
        $79, $73, $e, 0, $1, 0, $5, 0, 0, 0,
        $6e, $4b, $65, $79, $73, $f, 0, $14, 0, $b,
        0, $1f, 0, $1, 0, $10, 0, 0, 0, $41,
        $6e, $69, $6d, $61, $74, $69, $6f, $6e, $4f, $70,
        $74, $69, $6f, $6e, $73, $a, 0, $5, 0, $c0,
        $56, $bf, $e2, $f, $84, $cf, $11, $8f, $52, 0,
        $40, $33, $35, $94, $a3, $29, 0, $1, 0, $a,
        0, 0, 0, $6f, $70, $65, $6e, $63, $6c, $6f,
        $73, $65, $64, $14, 0, $29, 0, $1, 0, $f,
        0, 0, 0, $70, $6f, $73, $69, $74, $69, $6f,
        $6e, $71, $75, $61, $6c, $69, $74, $79, $14, 0,
        $b, 0, $1f, 0, $1, 0, $9, 0, 0, 0,
        $41, $6e, $69, $6d, $61, $74, $69, $6f, $6e, $a,
        0, $5, 0, $4f, $ab, $82, $3d, $da, $62, $cf,
        $11, $ab, $39, 0, $20, $af, $71, $e4, $33, $e,
        0, $12, 0, $12, 0, $12, 0, $f, 0, $b,
        0, $1f, 0, $1, 0, $c, 0, 0, 0, $41,
        $6e, $69, $6d, $61, $74, $69, $6f, $6e, $53, $65,
        $74, $a, 0, $5, 0, $50, $ab, $82, $3d, $da,
        $62, $cf, $11, $ab, $39, 0, $20, $af, $71, $e4,
        $33, $e, 0, $1, 0, $9, 0, 0, 0, $41,
        $6e, $69, $6d, $61, $74, $69, $6f, $6e, $f, 0,
        $b, 0, $1f, 0, $1, 0, $a, 0, 0, 0,
        $49, $6e, $6c, $69, $6e, $65, $44, $61, $74, $61,
        $a, 0, $5, 0, $a0, $ee, $23, $3a, $b1, $94,
        $d0, $11, $ab, $39, 0, $20, $af, $71, $e4, $33,
        $e, 0, $1, 0, $6, 0, 0, 0, $42, $49,
        $4e, $41, $52, $59, $f, 0, $b, 0, $1f, 0,
        $1, 0, $3, 0, 0, 0, $55, $72, $6c, $a,
        0, $5, 0, $a1, $ee, $23, $3a, $b1, $94, $d0,
        $11, $ab, $39, 0, $20, $af, $71, $e4, $33, $29,
        0, $1, 0, $5, 0, 0, 0, $6e, $55, $72,
        $6c, $73, $14, 0, $34, 0, $31, 0, $1, 0,
        $4, 0, 0, 0, $75, $72, $6c, $73, $e, 0,
        $1, 0, $5, 0, 0, 0, $6e, $55, $72, $6c,
        $73, $f, 0, $14, 0, $b, 0, $1f, 0, $1,
        0, $f, 0, 0, 0, $50, $72, $6f, $67, $72,
        $65, $73, $73, $69, $76, $65, $4d, $65, $73, $68,
        $a, 0, $5, 0, $60, $c3, $63, $8a, $7d, $99,
        $d0, $11, $94, $1c, 0, $80, $c8, $c, $fa, $7b,
        $e, 0, $1, 0, $3, 0, 0, 0, $55, $72,
        $6c, $13, 0, $1, 0, $a, 0, 0, 0, $49,
        $6e, $6c, $69, $6e, $65, $44, $61, $74, $61, $f,
        0, $b, 0, $1f, 0, $1, 0, $4, 0, 0,
        0, $47, $75, $69, $64, $a, 0, $5, 0, $e0,
        $90, $27, $a4, $10, $78, $cf, $11, $8f, $52, 0,
        $40, $33, $35, $94, $a3, $29, 0, $1, 0, $5,
        0, 0, 0, $64, $61, $74, $61, $31, $14, 0,
        $28, 0, $1, 0, $5, 0, 0, 0, $64, $61,
        $74, $61, $32, $14, 0, $28, 0, $1, 0, $5,
        0, 0, 0, $64, $61, $74, $61, $33, $14, 0,
        $34, 0, $2d, 0, $1, 0, $5, 0, 0, 0,
        $64, $61, $74, $61, $34, $e, 0, $3, 0, $8,
        0, 0, 0, $f, 0, $14, 0, $b, 0, $1f,
        0, $1, 0, $e, 0, 0, 0, $53, $74, $72,
        $69, $6e, $67, $50, $72, $6f, $70, $65, $72, $74,
        $79, $a, 0, $5, 0, $e0, $21, $f, $7f, $e1,
        $bf, $d1, $11, $82, $c0, 0, $a0, $c9, $69, $72,
        $71, $31, 0, $1, 0, $3, 0, 0, 0, $6b,
        $65, $79, $14, 0, $31, 0, $1, 0, $5, 0,
        0, 0, $76, $61, $6c, $75, $65, $14, 0, $b,
        0, $1f, 0, $1, 0, $b, 0, 0, 0, $50,
        $72, $6f, $70, $65, $72, $74, $79, $42, $61, $67,
        $a, 0, $5, 0, $e1, $21, $f, $7f, $e1, $bf,
        $d1, $11, $82, $c0, 0, $a0, $c9, $69, $72, $71,
        $e, 0, $1, 0, $e, 0, 0, 0, $53, $74,
        $72, $69, $6e, $67, $50, $72, $6f, $70, $65, $72,
        $74, $79, $f, 0, $b, 0, $1f, 0, $1, 0,
        $e, 0, 0, 0, $45, $78, $74, $65, $72, $6e,
        $61, $6c, $56, $69, $73, $75, $61, $6c, $a, 0,
        $5, 0, $a0, $6a, $11, $98, $ba, $bd, $d1, $11,
        $82, $c0, 0, $a0, $c9, $69, $72, $71, $1, 0,
        $4, 0, 0, 0, $47, $75, $69, $64, $1, 0,
        $12, 0, 0, 0, $67, $75, $69, $64, $45, $78,
        $74, $65, $72, $6e, $61, $6c, $56, $69, $73, $75,
        $61, $6c, $14, 0, $e, 0, $12, 0, $12, 0,
        $12, 0, $f, 0, $b, 0);

  D3DRM_XTEMPLATE_BYTES = 3278;

(*==========================================================================;
 *
 *  Copyright (C) 1995,1996 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       dsound.h
 *  Content:    DirectSound include file
 *
 **************************************************************************)

{ GUIDS used by DirectDraw objects }

const
  CLSID_DirectSound: TGUID = '{47D4D946-62E8-11cf-93BC-444553540000}';
  CLSID_DirectSoundCapture: TGUID = '{B0210780-89CD-11d0-AF08-00A0C925CD16}';

  IID_IDirectSound: TGUID = '{279AFA83-4981-11CE-A521-0020AF0BE560}';
  IID_IDirectSoundBuffer: TGUID = '{279AFA85-4981-11CE-A521-0020AF0BE560}';
  IID_IDirectSound3DListener: TGUID = '{279AFA84-4981-11CE-A521-0020AF0BE560}';
  IID_IDirectSound3DBuffer: TGUID = '{279AFA86-4981-11CE-A521-0020AF0BE560}';
  IID_IDirectSoundCapture: TGUID = '{B0210781-89CD-11D0-AF08-00A0C925CD16}';
  IID_IDirectSoundCaptureBuffer: TGUID = '{B0210782-89CD-11D0-AF08-00A0C925CD16}';

  IID_IDirectSoundNotify: TGUID = '{B0210783-89CD-11D0-AF08-00A0C925CD16}';

{ DirectSound Structures }

type
  IDirectSound = interface;
  IDirectSoundBuffer = interface;
  IDirectSoundCapture = interface;
  IDirectSoundCaptureBuffer = interface;
  IDirectSoundNotify = interface;

{ TDSCaps }

  PDSCaps = ^TDSCaps;
  TDSCaps = record
    dwSize: DWORD;
    dwFlags: DWORD;
    dwMinSecondarySampleRate: DWORD;
    dwMaxSecondarySampleRate: DWORD;
    dwPrimaryBuffers: DWORD;
    dwMaxHwMixingAllBuffers: DWORD;
    dwMaxHwMixingStaticBuffers: DWORD;
    dwMaxHwMixingStreamingBuffers: DWORD;
    dwFreeHwMixingAllBuffers: DWORD;
    dwFreeHwMixingStaticBuffers: DWORD;
    dwFreeHwMixingStreamingBuffers: DWORD;
    dwMaxHw3DAllBuffers: DWORD;
    dwMaxHw3DStaticBuffers: DWORD;
    dwMaxHw3DStreamingBuffers: DWORD;
    dwFreeHw3DAllBuffers: DWORD;
    dwFreeHw3DStaticBuffers: DWORD;
    dwFreeHw3DStreamingBuffers: DWORD;
    dwTotalHwMemBytes: DWORD;
    dwFreeHwMemBytes: DWORD;
    dwMaxContigFreeHwMemBytes: DWORD;
    dwUnlockTransferRateHwBuffers: DWORD;
    dwPlayCpuOverheadSwBuffers: DWORD;
    dwReserved1: DWORD;
    dwReserved2: DWORD;
  end;

  DSCAPS = TDSCaps;
  LPDSCAPS = PDSCaps;

{ TDSBCaps }

  PDSBCaps = ^TDSBCaps;
  TDSBCaps = record
    dwSize: DWORD;
    dwFlags: DWORD;
    dwBufferBytes: DWORD;
    dwUnlockTransferRate: DWORD;
    dwPlayCpuOverhead: DWORD;
  end;

  DSBCAPS = TDSBCaps;
  LPDSBCAPS = DSBCAPS;

{ TDSBufferDesc }

  PDSBufferDesc = ^TDSBufferDesc;
  TDSBufferDesc = record
    dwSize: DWORD;
    dwFlags: DWORD;
    dwBufferBytes: DWORD;
    dwReserved: DWORD;
    lpwfxFormat: PWaveFormatEx;
  end;

  DSBUFFERDESC = TDSBufferDesc;
  LPDSBUFFERDESC = PDSBufferDesc;

{ TDSCCaps }

  PDSCCaps = ^TDSCCaps;
  TDSCCaps = record
    dwSize: DWORD;
    dwFlags: DWORD;
    dwFormats: DWORD;
    dwChannels: DWORD;
  end;

  DSCCAPS = TDSCCaps;
  LPDSCCAPS = PDSCCaps;

{ TDSCBufferDesc }

  PDSCBufferDesc = ^TDSCBufferDesc;
  TDSCBufferDesc = record
    dwSize: DWORD;
    dwFlags: DWORD;
    dwBufferBytes: DWORD;
    dwReserved: DWORD;
    lpwfxFormat: PWaveFormatEx;
  end;

  DSCBUFFERDESC = TDSCBufferDesc;
  LPDSCBUFFERDESC = PDSCBufferDesc;

{ TDSCBCaps }

  PDSCBCaps = ^TDSCBCaps;
  TDSCBCaps = record
    dwSize: DWORD;
    dwFlags: DWORD;
    dwBufferBytes: DWORD;
    dwReserved: DWORD;
  end;

  DSCBCAPS = TDSCBCaps;
  LPDSCBCAPS = PDSCBCaps;

{ TDSBPositionNotify }

  PDSBPositionNotify = ^TDSBPositionNotify;
  TDSBPositionNotify = record
    dwOffset: DWORD;
    hEventNotify: THandle;
  end;

  DSBPOSITIONNOTIFY = TDSBPositionNotify;
  LPDSBPOSITIONNOTIFY = PDSBPositionNotify;

{ IDirectSound }

  IDirectSound = interface(IUnknown)
    ['{279AFA83-4981-11CE-A521-0020AF0BE560}']
    // IDirectSound methods
    function CreateSoundBuffer(const lpDSBufferDesc: TDSBufferDesc;
        out lplpDirectSoundBuffer: IDirectSoundBuffer;
        pUnkOuter: IUnknown): HResult; stdcall;
    function GetCaps(var lpDSCaps: TDSCaps): HResult; stdcall;
    function DuplicateSoundBuffer(lpDsbOriginal: IDirectSoundBuffer;
        out lpDsbDuplicate: IDirectSoundBuffer): HResult; stdcall;
    function SetCooperativeLevel(hwnd: HWND; dwLevel: DWORD): HResult; stdcall;
    function Compact: HResult; stdcall;
    function GetSpeakerConfig(var lpdwSpeakerConfig: DWORD): HResult; stdcall;
    function SetSpeakerConfig(dwSpeakerConfig: DWORD): HResult; stdcall;
    function Initialize(lpGuid: PGUID): HResult; stdcall;
  end;

{ IDirectSoundBuffer }

  IDirectSoundBuffer = interface(IUnknown)
    ['{279AFA85-4981-11CE-A521-0020AF0BE560}']
    // IDirectSoundBuffer methods
    function GetCaps(var lpDSBufferCaps: TDSBCaps): HResult; stdcall;
    function GetCurrentPosition(var lpdwCurrentPlayCursor,
        lpdwCurrentWriteCursor: DWORD): HResult; stdcall;
    function GetFormat(var lpwfxFormat: TWaveFormatEx; dwSizeAllocated: DWORD;
        var lpdwSizeWritten: DWORD): HResult; stdcall;
    function GetVolume(var lplVolume: Longint): HResult; stdcall;
    function GetPan(var lplPan: Longint): HResult; stdcall;
    function GetFrequency(var lpdwFrequency: DWORD): HResult; stdcall;
    function GetStatus(var lpdwStatus: DWORD): HResult; stdcall;
    function Initialize(lpDirectSound: IDirectSound; const
        lpDSBufferDesc: TDSBufferDesc): HResult; stdcall;
    function Lock(dwWriteCursor: DWORD; dwWriteBytes: DWORD;
        var lplpvAudioPtr1: Pointer; var lpdwAudioBytes1: DWORD;
        var lplpvAudioPtr2: Pointer; var lpdwAudioBytes2: DWORD;
        dwFlags: DWORD): HResult; stdcall;
    function Play(dwReserved1, dwReserved2: DWORD; dwFlags: DWORD): HResult; stdcall;
    function SetCurrentPosition(dwNewPosition: DWORD): HResult; stdcall;
    function SetFormat(const lpfxFormat: TWaveFormatEx): HResult; stdcall;
    function SetVolume(lVolume: Longint): HResult; stdcall;
    function SetPan(lPan: Longint): HResult; stdcall;
    function SetFrequency(dwFrequency: DWORD): HResult; stdcall;
    function Stop: HResult; stdcall;
    function Unlock(lpvAudioPtr1: Pointer; dwAudioBytes1: DWORD;
        lpvAudioPtr2: Pointer; dwAudioBytes2: DWORD): HResult; stdcall;
    function Restore: HResult; stdcall;
  end;

{ IDirectSoundCapture }

  IDirectSoundCapture = interface(IUnknown)
    ['{B0210781-89CD-11D0-AF08-00A0C925CD16}']
    // IDirectSoundCapture methods
    function CreateCaptureBuffer(const lpDSCBufferDesc: TDSCBufferDesc;
        out lplpDirectSoundCaptureBuffer: IDirectSoundCaptureBuffer;
        pUnkOuter: IUnknown): HResult; stdcall;
    function GetCaps(var lpDSCCaps: TDSCCaps): HResult; stdcall;
    function Initialize(lpGuid: PGUID): HResult; stdcall;
  end;

{ IDirectSoundCaptureBuffer }

  IDirectSoundCaptureBuffer = interface(IUnknown)
    ['{B0210782-89CD-11D0-AF08-00A0C925CD16}']
    // IDirectSoundCaptureBuffer methods
    function GetCaps(var lpDSCBCaps: TDSCBCaps): HResult; stdcall;
    function GetCurrentPosition(var lpdwCapturePosition,
        lpdwReadPosition: DWORD): HResult; stdcall;
    function GetFormat(var lpwfxFormat: TWaveFormatEx; dwSizeAllocated: DWORD;
        var lpdwSizeWritten: DWORD): HResult; stdcall;
    function GetStatus(var lpdwStatus: DWORD): HResult; stdcall;
    function Initialize(lpDirectSoundCapture: IDirectSoundCapture;
        const lpcDSBufferDesc: TDSCBufferDesc): HResult; stdcall;
    function Lock(dwReadCursor: DWORD; dwReadBytes: DWORD;
        var lplpvAudioPtr1: Pointer; var lpdwAudioBytes1: DWORD;
        var lplpvAudioPtr2: Pointer; var lpdwAudioBytes2: DWORD;
        dwFlags: DWORD): HResult; stdcall;
    function Start(dwFlags: DWORD): HResult; stdcall;
    function Stop: HResult; stdcall;
    function Unlock(lpvAudioPtr1: Pointer; dwAudioBytes1: DWORD;
        lpvAudioPtr2: Pointer; dwAudioBytes2: DWORD): HResult; stdcall;
  end;

{ IDirectSoundNotify }

  IDirectSoundNotify = interface(IUnknown)
    ['{B0210783-89CD-11D0-AF08-00A0C925CD16}']
    // IDirectSoundNotify methods
    function SetNotificationPositions(cPositionNotifies: DWORD;
        const lpcPositionNotifies): HResult; stdcall;
  end;

{ IKsPropertySet }

const
  KSPROPERTY_SUPPORT_GET = $00000001;
  KSPROPERTY_SUPPORT_SET = $00000002;

  IID_IKsPropertySet: TGUID = (D1:$31efac30;D2:$515c;D3:$11d0;D4:($a9,$aa,$00,$aa,$00,$61,$be,$93));

type
  IKsPropertySet = interface;

  IKsPropertySet = interface(IUnknown)
    ['{31EFAC30-515C-11D0-A9AA-00AA0061BE93}']
    // IKsPropertySet methods
    function GetProperty(const PropertySetId: TGUID; PropertyId: DWORD;
        var pPropertyParams; cbPropertyParams: DWORD;
        var pPropertyData; cbPropertyData: DWORD;
        var pcbReturnedData: ULONG): HResult; stdcall;
    function SetProperty(const PropertySetId: TGUID; PropertyId: DWORD;
        const pPropertyParams; cbPropertyParams: DWORD;
        const pPropertyData; cbPropertyData: DWORD): HResult; stdcall;
    function QuerySupport(const PropertySetId: TGUID; PropertyId: DWORD;
        var pSupport: ULONG): HResult; stdcall;
  end;

{ Return Codes }

const
  DS_OK                         = HResult(0);
  DSERR_ALLOCATED               = HResult($88780000 + 10);
  DSERR_CONTROLUNAVAIL          = HResult($88780000 + 30);
  DSERR_INVALIDPARAM            = HResult(E_INVALIDARG);
  DSERR_INVALIDCALL             = HResult($88780000 + 50);
  DSERR_GENERIC                 = HResult(E_FAIL);
  DSERR_PRIOLEVELNEEDED         = HResult($88780000 + 70);
  DSERR_OUTOFMEMORY             = HResult(E_OUTOFMEMORY);
  DSERR_BADFORMAT               = HResult($88780000 + 100);
  DSERR_UNSUPPORTED             = HResult(E_NOTIMPL);
  DSERR_NODRIVER                = HResult($88780000 + 120);
  DSERR_ALREADYINITIALIZED      = HResult($88780000 + 130);
  DSERR_NOAGGREGATION           = HResult(CLASS_E_NOAGGREGATION);
  DSERR_BUFFERLOST              = HResult($88780000 + 150);
  DSERR_OTHERAPPHASPRIO         = HResult($88780000 + 160);
  DSERR_UNINITIALIZED           = HResult($88780000 + 170);
  DSERR_NOINTERFACE             = HResult(E_NOINTERFACE);

{ Flags }

  DSCAPS_PRIMARYMONO      = $00000001;
  DSCAPS_PRIMARYSTEREO    = $00000002;
  DSCAPS_PRIMARY8BIT      = $00000004;
  DSCAPS_PRIMARY16BIT     = $00000008;
  DSCAPS_CONTINUOUSRATE   = $00000010;
  DSCAPS_EMULDRIVER       = $00000020;
  DSCAPS_CERTIFIED        = $00000040;
  DSCAPS_SECONDARYMONO    = $00000100;
  DSCAPS_SECONDARYSTEREO  = $00000200;
  DSCAPS_SECONDARY8BIT    = $00000400;
  DSCAPS_SECONDARY16BIT   = $00000800;

  DSBPLAY_LOOPING         = $00000001;

  DSBSTATUS_PLAYING       = $00000001;
  DSBSTATUS_BUFFERLOST    = $00000002;
  DSBSTATUS_LOOPING       = $00000004;

  DSBLOCK_FROMWRITECURSOR = $00000001;
  DSBLOCK_ENTIREBUFFER    = $00000002;

  DSSCL_NORMAL            = $00000001;
  DSSCL_PRIORITY          = $00000002;
  DSSCL_EXCLUSIVE         = $00000003;
  DSSCL_WRITEPRIMARY      = $00000004;

  DS3DMODE_NORMAL         = $00000000;
  DS3DMODE_HEADRELATIVE   = $00000001;
  DS3DMODE_DISABLE        = $00000002;

  DS3D_IMMEDIATE          = $00000000;
  DS3D_DEFERRED           = $00000001;

  DS3D_MINDISTANCEFACTOR     = 0.0;
  DS3D_MAXDISTANCEFACTOR     = 10.0;
  DS3D_DEFAULTDISTANCEFACTOR = 1.0;

  DS3D_MINROLLOFFFACTOR      = 0.0;
  DS3D_MAXROLLOFFFACTOR      = 10.0;
  DS3D_DEFAULTROLLOFFFACTOR  = 1.0;

  DS3D_MINDOPPLERFACTOR      = 0.0;
  DS3D_MAXDOPPLERFACTOR      = 10.0;
  DS3D_DEFAULTDOPPLERFACTOR  = 1.0;

  DS3D_DEFAULTMINDISTANCE    = 1.0;
  DS3D_DEFAULTMAXDISTANCE    = 1000000000.0;

  DS3D_MINCONEANGLE          = 0;
  DS3D_MAXCONEANGLE          = 360;
  DS3D_DEFAULTCONEANGLE      = 360;

  DS3D_DEFAULTCONEOUTSIDEVOLUME = 0;

  DSBCAPS_PRIMARYBUFFER       = $00000001;
  DSBCAPS_STATIC              = $00000002;
  DSBCAPS_LOCHARDWARE         = $00000004;
  DSBCAPS_LOCSOFTWARE         = $00000008;
  DSBCAPS_CTRL3D              = $00000010;
  DSBCAPS_CTRLFREQUENCY       = $00000020;
  DSBCAPS_CTRLPAN             = $00000040;
  DSBCAPS_CTRLVOLUME          = $00000080;
  DSBCAPS_CTRLPOSITIONNOTIFY  = $00000100;
  DSBCAPS_CTRLDEFAULT         = $000000E0;
  DSBCAPS_CTRLALL             = $000001F0;
  DSBCAPS_STICKYFOCUS         = $00004000;
  DSBCAPS_GLOBALFOCUS         = $00008000;
  DSBCAPS_GETCURRENTPOSITION2 = $00010000;
  DSBCAPS_MUTE3DATMAXDISTANCE = $00020000;

  DSCBCAPS_WAVEMAPPED = $80000000;

  DSSPEAKER_HEADPHONE = $00000001;
  DSSPEAKER_MONO      = $00000002;
  DSSPEAKER_QUAD      = $00000003;
  DSSPEAKER_STEREO    = $00000004;
  DSSPEAKER_SURROUND  = $00000005;

function DSSPEAKER_COMBINED(c, g: Byte): DWORD;
function DSSPEAKER_CONFIG(a: DWORD): Byte;
function DSSPEAKER_GEOMETRY(a: DWORD): Byte;

const
  DSCCAPS_EMULDRIVER    = $00000020;

  DSCBLOCK_ENTIREBUFFER = $00000001;

  DSCBSTATUS_CAPTURING  = $00000001;
  DSCBSTATUS_LOOPING    = $00000002;

  DSCBSTART_LOOPING     = $00000001;

  DSBFREQUENCY_MIN      = 100;
  DSBFREQUENCY_MAX      = 100000;
  DSBFREQUENCY_ORIGINAL = 0;

  DSBPAN_LEFT   = -10000;
  DSBPAN_CENTER = 0;
  DSBPAN_RIGHT  = 10000;

  DSBVOLUME_MIN = -10000;
  DSBVOLUME_MAX = 0;

  DSBSIZE_MIN = 4;
  DSBSIZE_MAX = $0FFFFFFF;

  DSBPN_OFFSETSTOP = $FFFFFFFF;

{ DirectSound API }

type
  TDSEnumCallbackW = function(lpGuid: PGUID; lpstrDescription: LPCWSTR;
    lpstrModule: LPCWSTR; lpContext: Pointer): BOOL; stdcall;
  LPDSENUMCALLBACKW = TDSEnumCallbackW;

  TDSEnumCallbackA = function(lpGuid: PGUID; lpstrDescription: LPCSTR;
    lpstrModule: LPCSTR; lpContext: Pointer): BOOL; stdcall;
  LPDSENUMCALLBACKA = TDSEnumCallbackA;

  TDSEnumCallback = TDSEnumCallbackA;
  LPDSENUMCALLBACK = TDSEnumCallback;

function DirectSoundCreate(lpGUID: PGUID; out lpDS: IDirectSound; pUnkOuter: IUnknown): HResult; stdcall;
function DirectSoundEnumerateA(lpDSEnumCallback: TDSEnumCallbackA; lpContext: Pointer): HResult; stdcall;
function DirectSoundEnumerateW(lpDSEnumCallback: TDSEnumCallbackW; lpContext: Pointer): HResult; stdcall;
function DirectSoundEnumerate(lpDSEnumCallback: TDSEnumCallbackA; lpContext: Pointer): HResult; stdcall;

function DirectSoundCaptureCreate(lpGUID: PGUID; out lplpDSC: IDirectSoundCapture; pUnkOuter: IUnknown): HResult; stdcall;
function DirectSoundCaptureEnumerateA(lpDSEnumCallback: TDSEnumCallbackA; lpContext: Pointer): HResult; stdcall;
function DirectSoundCaptureEnumerateW(lpDSEnumCallback: TDSEnumCallbackW; lpContext: Pointer): HResult; stdcall;
function DirectSoundCaptureEnumerate(lpDSEnumCallback: TDSEnumCallbackA; lpContext: Pointer): HResult; stdcall;

implementation

const
  DSoundLib = 'DSound.dll';


{ DirectSound }

function DSSPEAKER_COMBINED(c, g: Byte): DWORD;
begin
  Result := c or (g shl 16);
end;

function DSSPEAKER_CONFIG(a: DWORD): Byte;
begin
  Result := a;
end;

function DSSPEAKER_GEOMETRY(a: DWORD): Byte;
begin
  Result := a shr 16;
end;

function DirectSoundCreate; external DSoundLib;
function DirectSoundEnumerateA; external DSoundLib;
function DirectSoundEnumerateW; external DSoundLib;
function DirectSoundEnumerate; external DSoundLib name 'DirectSoundEnumerateA';

function DirectSoundCaptureCreate; external DSoundLib;
function DirectSoundCaptureEnumerateA; external DSoundLib;
function DirectSoundCaptureEnumerateW; external DSoundLib;
function DirectSoundCaptureEnumerate; external DSoundLib name 'DirectSoundCaptureEnumerateA';

end.

