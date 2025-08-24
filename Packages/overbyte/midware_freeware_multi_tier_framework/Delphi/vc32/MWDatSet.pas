{*_* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Author:       François PIETTE
Description:  TMWDataSet component and TMWTable component
EMail:        francois.piette@overbyte.be   francois.piette@rtfm.be
              http://www.overbyte.be        http://www.rtfm.be/fpiette
              francois.piette@pophost.eunet.be
Creation:     March 20, 1998
Version:      1.30
Support:      Use the mailing list midware@elists.org
              Follow "support" link at http://www.overbyte.be for subscription.
Legal issues: Copyright (C) 1997-2001 by François PIETTE
              Rue de Grady 24, 4053 Embourg, Belgium. Fax: +32-4-365.74.56
              <francois.piette@overbyte.be> <francois.piette@pophost.eunet.be>

              This software is provided 'as-is', without any express or
              implied warranty.  In no event will the author be held liable
              for any  damages arising from the use of this software.

              Permission is granted to anyone to use this software and or any
              derived or altered versions for any purpose, excluding commercial
              applications. You can use this software for personal use only.
              You may distribute it freely untouched.
              The following restrictions applies:

              1. The origin of this software must not be misrepresented, you
                 must not claim that you wrote the original software.

              2. If you use this software in a product, an acknowledgment in
                 the product documentation and displayed on screen is required.
                 The text must be: "This product is based on MidWare. Freeware
                 source code is available at http://www.rtfm.be/fpiette."

              3. Altered source versions must be plainly marked as such, and
                 must not be misrepresented as being the original software.

              4. This notice may not be removed or altered from any source
                 distribution and must be added to the product documentation.

Data layout:

    +-----------------------------------------------------------------+
    |          I N T E R N A L   R E C O R D   B U F F E R            |
    +-------------------------------------+----------+-------+--------+
    |   P H Y S I C A L   R E C O R D     |          |       |        |
    +-------------------------------------+          |       |        |
    |                                     |CALCULATED| EXTRA |BOOKMARK|
    |     ACCESSIBLE PHYSICAL FIELDS      |  FIELDS  |RECINFO|  DATA  |
    +-------------------------------------+----------+-------+--------+
          FCalcFieldOffset ----------------^
          FExtraRecInfoOffset ------------------------^
          FBookMarkOffset ------------------------------------^
    <----------- FRecBufSize ----------------------------------------->
    <----------- FRecSize ---------------->

Memo fields are stored in separately allocated memory. The record contains
the pointer to the allocated memory and the length as an integer.


Updates:
Mar 23, 1998 V1.01 Added a byte for the nul terminating byte in each field
May 13, 1998 V1.02 Changed IsSequenced to return FALSE. This solve the scroll
             bar problem in DBGrids.
             Changed GetFieldData to copy just the required number of byte
             regarding the datasize (this bug caused field concatenation).
May 23, 1998 V1.03 Added comments.
Jun 01, 1998 V1.04 Removed beta status. Changed "legal stuff" to prohibe
             commercial applications whithout an agreement.
             Added property editor for FieldLayout.
Jun 14, 1998 V1.05 Moved TFieldLayout in this source file
Jun 20, 1998 V1.06 Implemented field types
Jun 27, 1998 V1.07 Added a notification function
             Added code to protect from FData not assigned
             Added code to check for table active when setting fieldlayout
             Added AppSrvClient, Params and FunctionCode properties to
             allow design time data population. Need an upgraded TWSocket.
Jun 28, 1998 V1.08 Added full parsing for Params property to build a full
             request TWBuffer.
Jul 08, 1998 V1.09 Adapted for Delphi 4
             SetFieldLayout doesn't raise an exception if value not changed
Jul 10, 1998 V1.10 Added memo support
Jul 13, 1998 V1.11 Renamed TMidWareDataSet to TMWDataSet
             Added EMWDataSetException class, TMWTable.ExecuteRequest,
             TMWTable.OnRequestDone, TMWTable.SendRequest
             Added checks for FAppSrvClient being assigned and consistency
             between TMWTable.Data and FAppSrvClient.Answer assignement,
             silently correcting the link when needed.
             Added some comments.
             Added some conditional compile for Delphi2 and BCB1 to be able
             to compile a dummy component.
Jul 17, 1998 V1.12 Added intermediate TMWCustomTable class.
Jul 23, 1998 V1.13 Added DataEvent triggering for blobfields.
Jul 23, 1998 V1.14 Checked for nul length in AppendData
Aug 02, 1998 V1.15 Corrected field len for floats and currency
Aug 19, 1998 V1.16 Added ftBlob and ftGraphic
Aug 20, 1998 V1.17 Corrected a bug ("not Assigned(FData)") in Locate method.
Aug 24, 1998 V1.18 Added FData.Seek in GetRecord
Sep 02, 1998 V1.19 Verify that State in dsWriteModes in SetFieldData
Sep 08, 1998 V1.20 Properly initialize FInternalCurrent in InternalOpen
Sep 27, 1998 V1.21 Added checks in SetFieldData for ReadOnly fields
                   Added a call in SetFieldData to field's Validate.
Oct 17, 1998 V1.22 Adjusted memory allocation in TMWBlobStream.Write
Nov 27, 1998 V1.23 Replaced FieldCount by MWBufferFieldCount because it masked
                   the inherited FieldCount property from TDataSet.
Dec 23, 1998 V1.24 Cleared TWBlobStream buffer content when opened for writing.
                   Optimized TMWBuffer reallocation: reallocate only when
                   buffer is too small.
                   Append data in CopyToCurrentRecord. I'm not sure I must do it
                   like that !
Dec 30, 1998 V1.25 Corrected a bug in date/time handling in SetFieldData
Jan 16, 1999 V1.26 Corrected a bug in ftDate and ftTime field width.
Jan 29, 1999 V1.27 Replaced FloatToStr by FloatToStrEx.
                   Added DoBeforeScroll and DoAfterScroll in Locate.
Jul 21, 1999 V1.27a Corrected CreateBlobStream to set Stream.FModified in
                    write mode
                    Corrected a bug for boolean field in GetFieldData. Thanks
                    to Marchesini Franco <UP@interbusiness.it> for his help.
                    Added ftSmallInt case in GetFieldData.
Sep 15, 2001 V1.30 Added FieldTypeToString function.
                   Removed LoProp and PrmProp uses for Delphi 6 issue.


 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
unit MwDatSet;

interface

{$B-}           { Enable partial boolean evaluation   }
{$T-}           { Untyped pointers                    }
{$J+}           { Allow typed constant to be modified }
{$IFDEF VER110} { C++ Builder V3.0                    }
    {$ObjExportAll On}
{$ENDIF}

{ TMWTable is not compatible with Delphi 2 (VER90) nor BCB 1 (VER93) }
{$IFDEF VER90}
    {$DEFINE NO_TMWTABLE}
{$ENDIF}
{$IFDEF VER93}
    {$DEFINE NO_TMWTABLE}
{$ENDIF}
{$IFNDEF NO_TMWTABLE}

uses
    Windows, Classes, DB, DBConsts, SysUtils, RFormat, ApsCli
    { LOProp, PrmProp };

const
    MWDataSetVersion    = 130;
    CopyRight : String  = ' TMWDataSet (c) 1998-2001 F. Piette V1.30 ';

type
    EMWDataSetException = class(Exception);
    TPosition           = Integer;
    TFieldLayout        = String;
    TRequestParams      = String;

    { Field data record is used to maintains our own field definitions }
    TFieldData = record
        FldOffset : Integer;
        FldName   : String;
        FldType   : TFieldType;
        FldLen    : Integer;
        FldSize   : Integer;
    end;
    PFieldData = ^TFieldData;

    TBookmarkInfo = TPosition;           { TMWBuffer.Tell data type }

    PExtraRecInfo = ^TExtraRecInfo;
    TExtraRecInfo = record
        BookmarkFlag : TBookmarkFlag;    { bfCurrent, bfBOF, bfEOF, bfInserted }
    end;

    TDisplayInfo = procedure (Sender: TObject; const Msg: String) of Object;

    {:TMWDataSet is derived from TDataSet. It had only very few properties,
      methods and events. All inherited properties, methods and events are
      described in Delphi online help under the TDataSet topic. }
    TMWDataSet = class(TDataSet)
    private
        FBookmarkOffset     : LongInt;   { Offset to bookmark data in recbuf  }
        FCalcFieldsOffset   : Word;      { Offset to calculated fields data   }
        FExtraRecInfoOffset : Word;      { Offset to extra rec info in recbuf }
        FCursorOpen         : Boolean;   { True if cursor is open             }
        FInternalCurrent    : TPosition; { Record Pointer                     }
        FRecSize            : Word;      { Physical size of record            }
        FRecBufSize         : Word;      { Total size of recbuf               }
        FData               : TMWBuffer; { Where the data really resides      }
        FFieldLayout        : TFieldLayout; { FIELD1;TYP1;LEN1;FIELD2;...     }
        FFieldData          : TList;     { Decode FieldLayout                 }
        FMWBufferFieldCount : Integer;   { How many fields we have            }
        FOnDisplayInfo      : TDisplayInfo;
    protected
        procedure  Notification(AComponent: TComponent; Operation: TOperation); override;
        { Basic file reading and navigation }
        function  AllocRecordBuffer: PChar; override;
        procedure FreeRecordBuffer(var Buffer: PChar); override;
        function  GetRecord(Buffer: PChar; GetMode: TGetMode; DoCheck: Boolean): TGetResult; override;
        function  GetRecordSize: Word; override;
        procedure InternalClose; override;
        procedure InternalFirst; override;
        procedure InternalLast; override;
        procedure InternalOpen; override;
        procedure InternalRefresh; override;
        function  IsCursorOpen: Boolean; override;
        { Bookmarks }
        procedure GetBookmarkData(Buffer: PChar; Data: Pointer); override;
        function  GetBookmarkFlag(Buffer: PChar): TBookmarkFlag; override;
        procedure SetBookmarkData(Buffer: PChar; Data: Pointer); override;
        procedure SetBookmarkFlag(Buffer: PChar; Value: TBookmarkFlag); override;
        procedure InternalGotoBookmark(Bookmark: Pointer); override;
        procedure InternalSetToRecord(Buffer: PChar); override;
        { Basic file modification }
        procedure InternalInitRecord(Buffer: PChar); override;
        procedure InternalEdit; override;
        procedure InternalDelete; override;
        procedure InternalPost; override;
        { Field component stuff }
        procedure InternalInitFieldDefs; override;
        procedure SetFieldData(Field: TField; Buffer: Pointer); override;
        procedure InternalAddRecord(Buffer: Pointer; Append: Boolean); override;
        { Calculated fields }
        procedure ClearCalcFields(Buffer: PChar); override;
        function  FindRecord(Restart, GoForward: Boolean): Boolean; override;
        function  GetRecordCount: Longint; override;
        function  GetRecNo: Integer; override;
        procedure SetRecNo(Value: Integer); override;
        { Internal things }
        procedure CopyFromCurrentRecord(Dst : PChar);
        procedure CopyToCurrentRecord(Src : PChar);
        procedure AppendData(Src : PChar);
        function  TellText : String;
        procedure CloseBlob(Field: TField); override;
        procedure FreeBlobBuffer(Buffer: PChar);
    public
        function  IsSequenced: Boolean; override;
        function  GetCurrentRecord(Buffer: PChar): Boolean; override;
        function  CreateBlobStream(Field: TField; Mode: TBlobStreamMode): TStream; override;
        function  BookmarkValid(Bookmark: TBookmark): Boolean; override;
        function  CompareBookmarks(Bookmark1, Bookmark2: TBookmark): Integer; override;
        function  GetFieldData(Field: TField; Buffer: Pointer): Boolean; override;
        function  Locate(const KeyFields: String; const KeyValues: Variant;
                         Options: TLocateOptions): Boolean; override;
        function  Lookup(const KeyFields: String;
                         const KeyValues: Variant;
                         const ResultFields: String): Variant; override;
    protected
        { Our own custom stuff }
        FBufferFromInternalSetToRecord: PChar;
        function  GetFieldOffset(FieldNo : Integer) : Integer;
        function  GetFieldLen(FieldNo : Integer) : Integer;
        function  GetFieldType(FieldNo : Integer) : TFieldType;
        procedure TriggerDisplayInfo(const Msg: String); virtual;
        procedure SetFieldLayout(newValue : TFieldLayout);
    public
        constructor Create(AOwner: TComponent); override;
        destructor  Destroy; override;
        {:The data seen thru the component does'nt resides in the component.
          They are actually located in a TMWBuffer component. }
        property    Data : TMWBuffer            read  FData
                                                write FData;
        {:TMWBuffer is organized in records made of fields. There is nothing
          to gives field names, nor field sizes as TMWBuffer is a fully variable
          structure. The component needs something to give a name and a size to
          fields. This is the purpose of the FieldLayout property. This is
          simply a string structured a semicolon separated field names and
          field length like this: FIRSTNAME;20;LASTNAME;20;AGE;3;AMOUNT;8 }
        property    FieldLayout  : TFieldLayout read  FFieldLayout
                                                write SetFieldLayout;
        {:The number of fields. Based on FieldLayout property. }
        property    MWBufferFieldCount : Integer read  FMWBufferFieldCount;
        {:The record size property gives the size of the record. It is a
        readonly computedd value based on the FieldLayout property. Remember
        that the data comes from TMWBuffer component which does'nt have fixed
        record length as each TMWBuffer record can have a variable number of
        fields each one having a variable length. }
        property    RecordSize: Word            read  GetRecordSize;
        {:Event used to display internal info, for debugging purpose. }
        property    OnDisplayInfo: TDisplayInfo read  FOnDisplayInfo
                                                write FOnDisplayInfo;
    end;

  TMWCustomTable = class(TMWDataSet)
    private
        FReadOnly         : Boolean;
        FParams           : TRequestParams;
        FFunctionCode     : String;
        FAppSrvClient     : TAppSrvClient;
        FRequestDoneFlag  : Boolean;
        FRequestError     : Integer;
        FTimeout          : Integer;
        FBusy             : Boolean;
        FOnRequestDone    : TRequestDone;
    protected
        procedure Notification(AComponent: TComponent; Operation: TOperation); override;
        function  GetCanModify: Boolean; override;
        procedure InternalOpen; override;
        procedure AppSrvClientRequestDone(Sender: TObject; Error: Integer); virtual;
        procedure AppSrvClientExecuteRequestDone(Sender: TObject; Error: Integer); virtual;
        procedure SetFunctionCode(newValue : String);
        procedure SetParams(newValue : TRequestParams);
        procedure SetAppSrvClient(newValue : TAppSrvClient);
        procedure SetTimeout(newValue : Integer);
        procedure SendRequest; virtual;
        procedure TriggerRequestDone(Error: Integer); virtual;
    public
        constructor Create(AOwner : TComponent); override;
        procedure DesignTimeRequest; virtual;
        procedure ExecuteRequest; virtual;

        property CanModify: Boolean           read GetCanModify;
        property OnRequestDone   : TRequestDone
                                              read  FOnRequestDone
                                              write FOnRequestDone;
        property Data;
        property FieldLayout;
        property ReadOnly: Boolean            read  FReadOnly
                                              write FReadOnly;
        { Function code used to request data at design time }
        property FunctionCode : String        read  FFunctionCode
                                              write SetFunctionCode;
        { Parameters used to request data at design time }
        property Params : TRequestParams      read  FParams
                                              write SetParams;
        { Component used to request data at design time }
        property AppSrvClient : TAppSrvClient read  FAppSrvClient
                                              write SetAppSrvClient;
        { Timeout waiting for server to reply }
        property Timeout      : Integer       read  FTimeout
                                              write SetTimeout;
  end;

  TMWTable = class(TMWCustomTable)
  published
        property Active;
        property AutoCalcFields;
        property BeforeOpen;
        property AfterOpen;
        property BeforeClose;
        property AfterClose;
        property BeforeInsert;
        property AfterInsert;
        property BeforeEdit;
        property AfterEdit;
        property BeforePost;
        property AfterPost;
        property BeforeCancel;
        property AfterCancel;
        property BeforeDelete;
        property AfterDelete;
        property BeforeScroll;
        property AfterScroll;
        property OnCalcFields;
        property OnDeleteError;
        property OnEditError;
        property OnNewRecord;
        property OnPostError;
        property OnDisplayInfo;
        property OnRequestDone;
        property Data;
        property FieldLayout;
        property ReadOnly;
        property FunctionCode;
        property Params;
        property AppSrvClient;
        property Timeout;
  end;

  // This stream class is designed to be an interface between TDataSet
  // and our datastorage for blobs and memos. There is no real data
  // storage in the object. Data is directly accessed where it is:
  // in the dynamically allocated buffer.
  TMWBlobStream = class(TStream)
      Field     : TField;           // The field it refers to
      pFldData  : PFieldData;       // Pointer to internal infos about field
      Mode      : TBlobStreamMode;  // What operation is intended
      Buffer    : PChar;            // Where the data really is
{$IFDEF VER140}
      FSize     : Int64;            // The data size
{$ELSE}
      FSize     : LongInt;          // The data size
{$ENDIF}
      FCurPos   : LongInt;          // Current position for R/W
      FData     : TMWDataSet;
      FModified : Boolean;
      destructor Destroy; override;
      function  Write(const Value; Count: Longint): Longint; override;
      function  Read(var Value; Count: Longint): Longint; override;
      procedure SetSize(NewSize: Longint); override;
{$IFDEF VER140}
      procedure SetSize64(NewSize: Int64);
      function  GetSize : Int64;
{$ELSE}
      function  GetSize : LongInt;
{$ENDIF}
      function  Seek(Offset: Longint; Origin: Word): Longint; override;
{$IFDEF VER140}
      property  Size read GetSize write SetSize64;
{$ELSE}
      property  Size read GetSize write SetSize;
{$ENDIF}
  end;

function  StringToFieldType(Token : String) : TFieldType;
function  FieldTypeToString(FieldType : TFieldType) : String;
procedure ClearFieldData(FieldData : TList);
function  DecodeLayout(Layout : String; FieldData : TList) : Integer;

procedure Register;

const
  FieldTypesOrdinals : array [0..12] of TFieldType =
     (ftString, ftInteger, ftSmallInt, ftWord,     ftDateTime,
      ftDate,   ftTime,    ftFloat,    ftCurrency, ftBoolean,
      ftBlob,   ftMemo,    ftGraphic);
  FieldTypesNames : array [0..12] of String =
     ('Char', 'Integer', 'SmallInt', 'Word',     'DateTime',
      'Date', 'Time',    'Float',    'Currency', 'Boolean',
      'Blob', 'Memo',    'Graphic');

implementation

uses  Forms;

type
    PPChar   = ^PChar;
    PInteger = ^Integer;

{$IFDEF NEVER}
const
    TraceCount : Integer = 0;

{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure Trace(Msg : String);
begin
    Inc(TraceCount);
    if IsConsole then
        Writeln(TraceCount, ' ', Msg);
end;
{$ENDIF}


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.Notification(AComponent: TComponent; Operation: TOperation);
begin
    inherited Notification(AComponent, Operation);
    if Operation = opRemove then begin
        if AComponent = FData then
            FData := nil;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.TriggerDisplayInfo(const Msg: String);
begin
    if Assigned(FOnDisplayInfo) then
        FOnDisplayInfo(Self, Msg);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
constructor TMWDataSet.Create(AOwner: TComponent);
begin
    inherited Create(AOwner);
    FFieldData       := TList.Create;
    FInternalCurrent := TPosition(-1);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
destructor TMWDataSet.Destroy;
begin
    // We must close the table before destroying because we
    // need some field infos to free ftMemo or ftBlob fields
    Active := FALSE;
    if Assigned(FFieldData) then begin
        ClearFieldData(FFieldData);
        FFieldData.Free;
        FFieldData := nil;
    end;
    inherited Destroy;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWDataSet.AllocRecordBuffer: PChar;
begin
    GetMem(Result, FRecBufSize);
    FillChar(Result^, FRecBufSize, #0);
    TriggerDisplayInfo('AllocRecordBuffer $' + IntToHex(LongInt(Result), 8));
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.FreeRecordBuffer(var Buffer: PChar);
begin
//  writeln('FreeRecordBuffer(' + IntToHex(Integer(Buffer), 8) + ')');
    try
        TriggerDisplayInfo('FreeRecordBuffer $' + IntToHex(LongInt(Buffer), 8));
        // Free the memory allocated for blob fields
        FreeBlobBuffer(Buffer);
        // Free the memory used for the entire record
        FreeMem(Buffer, FRecBufSize);
        Buffer := nil;
    except
        on E:Exception do
            TriggerDisplayInfo('FreeRecordBuffer $' + IntToHex(LongInt(Buffer), 8) +
                               ' exception ' + E.Message);
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This function returns a PChar pointing to blob data                       }
{ Blobs (ftBlob, ftMemo and ftGraphic) are not stored in the record buffer. }
{ The record buffer contains the size and a pointer to dynamically          }
{ allocated memory to hold the blob.                                        }
function GetBlobDataPtr(Buf : PChar; pFldData : PFieldData) : PChar;
begin
    Result := PPChar(Buf + pFldData^.FldOffset)^;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This function set the blob data pointer                                   }
procedure SetBlobDataPtr(Buf : PChar; pFldData : PFieldData; newValue : PChar);
begin
    PPChar(Buf + pFldData^.FldOffset)^ := newValue;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ Retreive the blob field data size                                         }
function GetBlobDataLen(Buf : PChar; pFldData : PFieldData) : Integer;
begin
    Result := PInteger(Buf + pFldData^.FldOffset + SizeOf(PChar))^;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ Set the blob field data size                                              }
procedure SetBlobDataLen(Buf : PChar; pFldData : PFieldData; newValue : Integer);
begin
    PInteger(Buf + pFldData^.FldOffset + SizeOf(PChar))^ := newValue;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ Free memory allocated for all blob fields in a record buffer.             }
{ Blobs (ftBlob, ftMemo and ftGraphic) are not stored in the record buffer. }
{ The record buffer contains the size and a pointer to dynamically          }
{ allocated memory to hold the blob.                                        }
procedure TMWDataSet.FreeBlobBuffer(Buffer: PChar);
var
    FldNo    : Integer;
    pFldData : PFieldData;
    pData    : PChar;
    Len      : Integer;
begin
//  writeln('FreeBlobBuffer(' + IntToHex(Integer(Buffer), 8) + ')');
    for FldNo := 0 to FMWBufferFieldCount - 1 do begin
        pFldData := PFieldData(FFieldData.Items[FldNo]);
        if pFldData^.FldType in [ftMemo, ftBlob, ftGraphic] then begin
            pData := GetBlobDataPtr(Buffer, pFldData);
            Len   := GetBlobDataLen(Buffer, pFldData);
//          writeln('  pData =' + IntToHex(Integer(pData), 8));
//          writeln('  Len   =' + IntToStr(Len));
            if pData <> nil then begin
                FreeMem(pData, Len + 1);
                SetBlobDataPtr(Buffer, pFldData, nil);
                SetBlobDataLen(Buffer, pFldData, 0);
            end;
        end;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.InternalInitRecord(Buffer: PChar);
begin
//  writeln('InternalInitRecord(' + IntToHex(Integer(Buffer), 8) + ')');
    TriggerDisplayInfo('InternalInitRecord $' + IntToHex(LongInt(Buffer), 8));
    FreeBlobBuffer(Buffer);
    FillChar(Buffer^, FRecBufSize, #0);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWDataSet.TellText : String;
begin
    Result := 'Tell = ' + IntToStr(FData.Tell) +
              '  DataBufferCount = ' + IntToStr(FData.DataBufferCount);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.InternalOpen;
begin
    TriggerDisplayInfo('InternalOpen');
    if Assigned(FData) then begin
        FData.First;
        TriggerDisplayInfo(TellText);
    end;
    FInternalCurrent := TPosition(-1);   { 08/09/98 }
    FCursorOpen := True;
    InternalInitFieldDefs;      { Populate FieldDefs from external dict }
    if DefaultFields then
        CreateFields;           { Populate Fields from FieldDefs        }
    BindFields(True);

    { Compute offsets to various record buffer segments }
    BookmarkSize        := SizeOf(TBookmarkInfo);
    FCalcFieldsOffset   := FRecSize;
    FExtraRecInfoOffset := FCalcFieldsOffset + CalcFieldsSize;
    FBookmarkOffset     := FExtraRecInfoOffset + SizeOf(TExtraRecInfo);
    FRecBufSize         := FBookmarkOffset + BookmarkSize;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.InternalClose;
begin
    TriggerDisplayInfo('InternalClose');
    { Destroy the TField components if no persistent fields }
    if DefaultFields then
        DestroyFields;

    { InternalClose is called by the Fields Editor in design mode, so }
    { the actual table may not be open.                               }
    FCursorOpen := False;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWDataSet.GetFieldOffset(FieldNo : Integer) : Integer;
begin
    Result := PFieldData(FFieldData.Items[FieldNo])^.FldOffset;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWDataSet.GetFieldLen(FieldNo : Integer) : Integer;
begin
    Result := PFieldData(FFieldData.Items[FieldNo])^.FldLen;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWDataSet.GetFieldType(FieldNo : Integer) : TFieldType;
begin
    Result := PFieldData(FFieldData.Items[FieldNo])^.FldType;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure ClearFieldData(FieldData : TList);
var
    I : Integer;
begin
    for I := 0 to FieldData.Count - 1 do
        Dispose(PFieldData(FieldData.Items[I]));
    FieldData.Clear;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function stpblk(PValue : PChar) : PChar;
begin
    Result := PValue;
    while Result^ in [' ', #9, #10, #13] do
        Inc(Result);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function atof(value : string) : Extended;
begin
    if Value = '' then
        Result := 0
    else begin
        try
            Result := StrToFloat(Value);
        except
            Result := 0;
        end;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function atoi(value : string) : Integer;
var
    i    : Integer;
    Sign : Char;
begin
    Result := 0;
    Sign   := '+';
    i      := 1;
    while (i <= Length(Value)) and (Value[i] = ' ') do
        i := i + 1;
    if (i <= Length(Value)) and (Value[i] in ['+', '-']) then begin
        Sign := Value[i];
        Inc(i);
    end;
    while (i <= Length(Value)) and (Value[i] >= '0') and (Value[i] <= '9')do begin
        Result := Result * 10 + ord(Value[i]) - ord('0');
        i := i + 1;
    end;
    if Sign = '-' then
        Result := -Result;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function GetToken(Src : PChar; var Dst : String; var Delim : Char) : PChar;
begin
    Result := StpBlk(Src);
    Dst    := '';
    while TRUE do begin
        Delim := Result^;
        if Delim in [';', #0] then
            break;
        Dst := Dst + UpperCase(Result^);
        Inc(Result);
    end;
    if Delim <> #0 then
        Inc(Result);
    Result := stpblk(Result);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function  FieldTypeToString(FieldType : TFieldType) : String;
var
    I : Integer;
begin
    for I := Low(FieldTypesNames) to High(FieldTypesNames) do begin
        if FieldTypesOrdinals[I] = FieldType then begin
            Result := FieldTypesNames[I];
            Exit;
        end;
    end;
    raise EMWDataSetException.Create(
              'FieldTypeToString: Unsupported field type');
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function StringToFieldType(Token : String) : TFieldType;
var
    I : Integer;
begin
    Token  := Trim(Token);
    Result := ftUnknown;
    if Token > '' then begin
        if Length(Token) = 1 then begin
            // Support old code !
            case UpperCase(Token)[1] of
            'C': Result := ftString;
            'D': Result := ftDateTime;
            'N': Result := ftInteger;
            'F': Result := ftFloat;
            'L': Result := ftBoolean;
            end;
        end
        else begin
            for I := Low(FieldTypesNames) to High(FieldTypesNames) do begin
                if StrIComp(PChar(Token), PChar(FieldTypesNames[I])) = 0 then begin
                    Result := FieldTypesOrdinals[I];
                    Exit;
                end;
            end;
        end;
    end;
//  ftWord, ftCurrency, ftBCD, ftDate, ftTime, ftDateTime,
//  ftBytes, ftVarBytes, ftAutoInc, ftBlob, ftMemo, ftGraphic,
//  ftFmtMemo, ftParadoxOle, ftDBaseOle, ftTypedBinary, ftCursor
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ Parse a FieldLayout string and build a field structure list.              }
function DecodeLayout(Layout : String; FieldData : TList) : Integer;
type
    fdState = (fdName, fdType, fdSize);
var
    FldNo   : Integer;
    p       : PChar;
    Token   : String;
    Delim   : Char;
    State   : fdState;
    FldName : String;
    FldType : TFieldType;
    FldLen  : Integer;
    FldSize : Integer;
    pData   : PFieldData;
begin
    // Free all existing data definition
    ClearFieldData(FieldData);

    State       := fdName;
    FldNo       := 1;
    Result      := 0;
    FldType     := ftUnknown;
    FldSize     := 0;
    p           := PChar(Layout);
    while (p <> nil) and (p^ <> #0) do begin
        p := GetToken(p, Token, Delim);
        case State of
        fdName:
            begin
                if Token = '' then
                    FldName := 'FIELD' + IntToStr(FldNo)
                else
                    FldName := Token;
                FldSize := 0;
                State   := fdType;
            end;
        fdType:
            begin
                FldType := StringToFieldType(Token);
                State   := fdSize;
            end;
        fdSize:
            begin
                // We need a field length
                FldLen := atoi(Token);
                if FldLen <= 0 then
                    FldLen := 10;

                if FldType = ftString then
                    FldSize := FldLen
                else if FldType in [ftDateTime, ftTime, ftDate] then  // 16/01/99
                    FldLen := 20
                else if FldType = ftInteger then
                    FldLen := 11
                else if FldType = ftFloat then
                    FldLen := 20
                else if FldType = ftCurrency then
                    FldLen := 20
                else if FldType = ftBoolean then
                    FldLen := 2
                else if FldType in [ftMemo, ftBlob, ftGraphic] then
                    FldLen := SizeOf(Pointer) + SizeOf(Integer);

                New(pData);
                FieldData.Add(pData);
                pData.FldLen    := FldLen;
                pData.FldSize   := FldSize;
                pData.FldType   := FldType;
                pData.FldName   := FldName;
                pData.FldOffset := Result;

                Result := Result + FldLen + 1;       { compute our record size }
                                                     { +1 is for NUL byte      }
                Inc(FldNo);
                State := fdName;
            end;
        end;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.InternalInitFieldDefs;
var
    FldNo   : Integer;
    pData   : PFieldData;
{$IFDEF VER110}
    Field   : TFieldDef;
{$ENDIF}
begin
    TriggerDisplayInfo('InternalInitFieldDefs');
    FieldDefs.Clear;
    FRecSize            := DecodeLayout(FFieldLayout, FFieldData);
    FMWBufferFieldCount := FFieldData.Count;

    for FldNo := 1 to FFieldData.Count do begin
        pData := PFieldData(FFieldData.Items[FldNo - 1]);
{$IFDEF VER110}
        FieldDefs.BeginUpdate;
        try
            Field                   := FieldDefs.AddFieldDef;
            Field.Name              := pData.FldName;
            Field.DataType          := pData.FldType;
            Field.Size              := pData.FldSize;
            Field.Required          := FALSE;  // FP nov 11, 1998
            Field.InternalCalcField := FALSE;
        finally
            FieldDefs.EndUpdate;
        end;
{$ELSE}
        TFieldDef.Create(FieldDefs, pData.FldName, pData.FldType,
                         pData.FldSize, FALSE, FldNo);  // FP nov 11, 1998
{$ENDIF}
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ Position BEFORE the very first record (there will be a get next)          }
procedure TMWDataSet.InternalFirst;
begin
    TriggerDisplayInfo('InternalFirst');
    if Assigned(FData) then
        FData.First;
    FInternalCurrent := TPosition(-1);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ Position AFTER the very last record (there will be a get prior)           }
procedure TMWDataSet.InternalLast;
begin
    TriggerDisplayInfo('InternalLast');
    if Assigned(FData) then
        FData.Last;
    FInternalCurrent := TPosition(-2);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.AppendData(Src : PChar);
var
    FldNo    : Integer;
    p        : PChar;
    pFldData : PFieldData;
    pData    : PChar;
    Len      : Integer;
    Value    : String;
begin
    if not Assigned(FData) then
        Exit;

//    for FldNo := 0 to FMWBufferFieldCount - 1 do begin
//        p := Src + GetFieldOffset(FldNo);
//        FData.WriteFields(FldNo = 0, [p]);
//    end;

    for FldNo := 0 to FMWBufferFieldCount - 1 do begin
        pFldData := PFieldData(FFieldData.Items[FldNo]);
        if pFldData^.FldType in [ftMemo, ftBlob, ftGraphic] then begin
            pData := GetBlobDataPtr(Src, pFldData);
            Len   := GetBlobDataLen(Src, pFldData);
            SetLength(Value, Len);
            if Len > 0 then
                Move(pData^, Value[1], Len);
            FData.WriteFields(FldNo = 0, [Value]);
        end
        else begin
            p := Src + pFldData^.FldOffset;
            FData.WriteFields(FldNo = 0, [p]);
        end;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ Copy data from the TMWBuffer current record to some TDataSet internal     }
{ buffer.                                                                   }
procedure TMWDataSet.CopyFromCurrentRecord(Dst : PChar);
var
    FldNo    : Integer;
    pFldData : PFieldData;
    pData    : PChar;
    Len      : Integer;
begin
    for FldNo := 0 to FMWBufferFieldCount - 1 do begin
        pFldData := PFieldData(FFieldData.Items[FldNo]);
        if pFldData^.FldType in [ftMemo, ftBlob, ftGraphic] then begin
//          writeln('CopyFromCurrentRecord(' + IntToHex(Integer(Dst), 8) + ')');
            // Memo fields are stored in separate dynamically allocated
            // memory. The TDataSet buffer contains only the pointer to this
            // allocated memory and the field size.
            Len   := FData.FieldSize[FldNo];
            pData := GetBlobDataPtr(Dst, pFldData);
//          writeln('  Len      =' + IntToStr(Len));
//          writeln('  Old Len  =' + IntToStr(GetBlobDataLen(Dst, pFldData)));
//          writeln('  Old pData=' + IntToHex(Integer(pData), 8));
            ReallocMem(pData, Len + 1);
//          writeln('  New pData=' + IntToHex(Integer(pData), 8));
            SetBlobDataPtr(Dst, pFldData, pData);
            SetBlobDataLen(Dst, pFldData, Len);
            TriggerDisplayInfo('Memo in record $' + IntToHex(Integer(Dst), 8));
            Move(PChar(FData.Fields[FldNo])^, pData^, Len);
            pData[Len] := #0;
        end
        else begin
            // Any other field type is directly stored in the buffer
            StrLCopy(Dst + pFldData^.FldOffset,
                     PChar(FData.Fields[FldNo]),
                     pFldData^.FldLen + 1);
        end;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.CopyToCurrentRecord(Src : PChar);
var
    FldNo    : Integer;
    Value    : String;
    pFldData : PFieldData;
    pData    : PChar;
    Len      : Integer;
begin
//Trace('CopyToCurrentRecord ' + IntToHex(Integer(Src), 8));
//    if not FData.HasData then begin         // 24/12/98 Create all fields
//        for FldNo := 0 to FMWBufferFieldCount - 1 do
//             FData.WriteFields(FldNo = 0, ['']);
//        FData.First;
//    end;
    for FldNo := 0 to FMWBufferFieldCount - 1 do begin
//        if not FData.IsValidFields(FldNo) then
//             FData.WriteFields(FALSE, ['']);

        pFldData := PFieldData(FFieldData.Items[FldNo]);
        if pFldData^.FldType in [ftMemo, ftBlob, ftGraphic] then begin
            pData := GetBlobDataPtr(Src, pFldData);
            Len   := GetBlobDataLen(Src, pFldData);
            SetLength(Value, Len);
            if Len > 0 then
                Move(pData^, Value[1], Len);
        end
        else
            Value := StrPas(Src + pFldData^.FldOffset);

        FData.Fields[FldNo] := Value;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWDataSet.GetRecord(
    Buffer  : PChar;
    GetMode : TGetMode;
    DoCheck : Boolean): TGetResult;
begin
    Result := grOk;
    case GetMode of
    gmCurrent:
        begin
            TriggerDisplayInfo('GetRecord Current into buffer $' +
                               IntToHex(Integer(Buffer), 8));
            if (not Assigned(FData)) or                  // No data
               (FInternalCurrent = TPosition(-1)) or     // First
               (FInternalCurrent = TPosition(-2)) then   // Last
                Result := grError
            else begin
                FInternalCurrent := FData.Tell;
                TriggerDisplayInfo(TellText);
                CopyFromCurrentRecord(Buffer);
            end;
        end;
    gmNext:
        begin
            TriggerDisplayInfo('GetRecord Next  buffer ' + IntToHex(LongInt(Buffer), 8));
            if (not Assigned(FData)) or             // No data
               (FInternalCurrent = TPosition(-2)) then  // On the last
                Result := grEof
            else begin
                if FInternalCurrent <> TPosition(-1) then begin
                    FData.Seek(FInternalCurrent);  // 24/08/98
                    FData.Next;
                end;

                if FData.Eof then begin
                    FInternalCurrent := TPosition(-2);
                    Result := grEof;
                end
                else begin
                    FInternalCurrent := FData.Tell;
                    TriggerDisplayInfo(TellText);
                    CopyFromCurrentRecord(Buffer);
                end;
            end;
        end;
    gmPrior:
        begin
            TriggerDisplayInfo('GetRecord Prior  buffer ' + IntToHex(LongInt(Buffer), 8));
            if (not Assigned(FData)) or                 // No Data
               (FInternalCurrent = TPosition(-1)) then  // On the first
                Result := grBof
            else begin
                if FInternalCurrent <> TPosition(-2) then begin
                    FData.Seek(FInternalCurrent);  // 24/08/98
                    FData.Prior;
                end;

                if FData.Bof then begin
                    FInternalCurrent := TPosition(-1);
                    Result := grBof
                end
                else begin
                    FInternalCurrent := FData.Tell;
                    TriggerDisplayInfo(TellText);
                    CopyFromCurrentRecord(Buffer);
                end;
            end;
        end;
    else
        Result := grError;
    end;

    if Result <> grOk then begin
        TriggerDisplayInfo('GetRecord Result <> grOk');
        InternalInitRecord(Buffer);
    end;

    if Result = grOk then begin
        GetCalcFields(Buffer);
        with PExtraRecInfo(Buffer + FExtraRecInfoOffset)^ do begin
            BookmarkFlag := bfCurrent;
            SetBookmarkData(Buffer, @FInternalCurrent);
        end;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ Get the data for the given field from the active buffer and stick it      }
{ in the given buffer.  Return False if the field value is null; otherwise  }
{ return True. Buffer may be nil if TDataSet is checking for null only.     }
function TMWDataSet.GetFieldData(Field: TField; Buffer: Pointer): Boolean;
var
    Offset    : Integer;
    DataSize  : Integer;
    TimeStamp : TTimeStamp;  { TTimeStamp declared in SysUtils }
    RecBuf    : PChar;
    I         : Integer;
    Buf       : String;
begin
//Trace('TMWDataSet.GetFieldData ' + IntToHex(LongInt(ActiveBuffer), 8));
    RecBuf := ActiveBuffer;
    if State = dsCalcFields then
        RecBuf := CalcBuffer;

    if Field.FieldNo <> -1 then begin   { a physical field }
        { Check for a null value }
        Result := TRUE; { no null value }

        { If value is not null }
        if Result and Assigned(Buffer) then begin
            FillChar(Buffer^, Field.DataSize, 0);
            Offset   := GetFieldOffset(Field.FieldNo - 1);
            DataSize := Field.DataSize;

            if Field.DataType in [ftDateTime, ftDate, ftTime] then
                TimeStamp := TimeStampFromMWFormat(StrPas(RecBuf + OffSet));

            case Field.DataType of
            ftDate:     TDateTimeRec(Buffer^).Date     := TimeStamp.Date;
            ftTime:     TDateTimeRec(Buffer^).Time     := TimeStamp.Time;
            ftDateTime: TDateTimeRec(Buffer^).DateTime := TimeStampToMSecs(TimeStamp);
            ftInteger:  Integer(Buffer^)  := atoi(RecBuf + Offset);
            ftSmallInt: SmallInt(Buffer^) := atoi(RecBuf + Offset);
            ftFloat:    Double(Buffer^)   := atof(RecBuf + Offset);
            ftCurrency: Double(Buffer^)   := atof(RecBuf + Offset);
            ftString:   StrLCopy(Buffer, RecBuf + OffSet, DataSize - 1);
            ftBoolean:  Boolean(Buffer^)  := ((RecBuf[Offset] = 'T') or (RecBuf[Offset] = '1'));
            ftMemo, ftBlob, ftGraphic:
                        raise Exception.Create('GetFieldData: program error');
            else
                raise EDatabaseError.Create('unsupported data type');
            end;
{$IFDEF NEVER}
            { Special handing for date/time fields }
            { TMWBuffer store datatime as TTimeStamp structure converted to }
            { two ascii integers                                            }
            if Field.DataType in [ftDateTime, ftDate, ftTime] then begin
                TimeStamp := TimeStampFromMWFormat(StrPas(RecBuf + OffSet));
                case Field.DataType of
                    ftDate: TDateTimeRec(Buffer^).Date := TimeStamp.Date;
                    ftTime: TDateTimeRec(Buffer^).Time := TimeStamp.Time;
                else
                    TDateTimeRec(Buffer^).DateTime := TimeStampToMSecs(TimeStamp);
                end;
            end
            else if Field.DataType = ftInteger then begin
                Integer(Buffer^) := StrToInt(RecBuf + Offset);
            end
            else if Field.DataType = ftString then begin
                // Standard null terminated strings
                StrLCopy(Buffer, RecBuf + OffSet, DataSize - 1);
            end
            else begin
                Move(RecBuf[Offset], Buffer^, DataSize);
            end;
{$ENDIF}
        end;
    end
    else begin   { a calculated field }
        Offset := FCalcFieldsOffset + Field.Offset;
        Result := not Boolean(RecBuf[Offset]);
        if Result and Assigned(Buffer) then
            Move(RecBuf[Offset + 1], Buffer^, Field.DataSize);
    end;

    Buf := '';
    for I := 0 to 19 do begin
        if (Buffer <> nil) and (Pchar(Buffer)[I] >= ' ') then
            Buf := Buf + Pchar(Buffer)[I]
    end;

    TriggerDisplayInfo('GetFieldData ' + IntToStr(Field.FieldNo) +
                       ' from ActiveBuffer $' + IntToHex(Integer(ActiveBuffer), 8) +
                       ' ''' + Buf + '''');
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWBlobStream.Read(var Value; Count: Longint): Longint;
var
    pData     : PChar;
    Len       : Integer;
begin
//  Trace('TMWBlobStream.Read ' + IntToHex(LongInt(Buffer), 8));
//  Writeln('TMWBlobStream.Read Count=', Count);
    if Count < 0 then
        raise Exception.Create('TMWBlobStream.Read can''t read negative byte count');

    if Count = 0 then begin
        Result := 0;
        Exit;
    end;

    // Get data length
    Len := GetBlobDataLen(Buffer, pFldData);
    if Len <= 0 then begin
        Result := 0;
        Exit;
    end;

    // Get data pointer
    pData := GetBlobDataPtr(Buffer, pFldData);

    // Adjust count to not read more than available data
    if (FCurPos + Count) > Len then
        Count := Len - FCurPos;

    // Check if some more data to read
    if Count <= 0 then begin
        Result := 0;
        Exit;
    end;

    // Copy data
    Move(pData[FCurPos], Value, Count);

    // Update current position
    FCurPos   := FCurPos + Count;

    // Return byte count
    Result    := Count;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWBlobStream.Write(const Value; Count: Longint): Longint;
var
    pData     : PChar;
    Len       : LongInt;
begin
//  Trace('TMWBlobStream.Write ' + IntToHex(LongInt(Buffer), 8));
//  writeln('TMWBlobStream.Write Count=', Count, ' Buffer=', IntToHex(Integer(Buffer), 8));
    if Count < 0 then
        raise Exception.Create('TMWBlobStream.Write can''t write negative byte count');

    if Count = 0 then begin
        Result := 0;
        Exit;
    end;

    // Get data pointer and data length
    pData := GetBlobDataPtr(Buffer, pFldData);
    Len   := GetBlobDataLen(Buffer, pFldData);   // 23/12/98

    if Len < (FCurPos + Count) then begin        // 23/12/98
        // Adjust allocated memory  (17/10/98)
        ReallocMem(pData, FCurPos + Count + 1);
        SetBlobDataPtr(Buffer, pFldData, pData);
        SetBlobDataLen(Buffer, pFldData, FCurPos + Count);
    end;

    // Copy data to internal buffer
    Move(Value, pData[FCurPos], Count);

    // Update current position
    FCurPos := FCurPos + Count;
{
    // If in edit or insert mode, copy data to TMWBuffer
    if FData.State = dsEdit then   // 24/12/98
        FData.CopyToCurrentRecord(Buffer)
    else if FData.State = dsInsert then   // 23/12/98
        FData.AppendData(Buffer);
}
    Result    := Count;
    FModified := TRUE;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWBlobStream.SetSize(NewSize: Longint);
begin
    FSize := NewSize;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{$IFDEF VER140}
procedure TMWBlobStream.SetSize64(NewSize: Int64);
begin
    FSize := NewSize;
end;
{$ENDIF}


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function  TMWBlobStream.GetSize : {$IFDEF VER140} Int64; {$ELSE} LongInt; {$ENDIF}
begin
    Result := FSize;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWBlobStream.Seek(Offset: Longint; Origin: Word): Longint;
begin
    case Origin of
    soFromBeginning: Result := Offset;
    soFromCurrent:   Result := FCurPos + Offset;
    soFromEnd:       Result := FSize - Offset;
    else
         raise Exception.Create('TMWBlobStream.Seek invalid origin');
    end;
    FCurPos := Result;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
destructor TMWBlobStream.Destroy;
begin
//  writeln('TMWBlobStream.Destroy');
    if FModified then begin
        if Field is TBlobField then
            TBlobField(Field).Modified := True;
        try
            FData.DataEvent(deFieldChange, Longint(Field));
        except
            Application.HandleException(Self);
        end;
    end;
    inherited Destroy;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWDataSet.CreateBlobStream(
    Field: TField; Mode: TBlobStreamMode): TStream;
var
    Stream    : TMWBlobStream;
    pFldData  : PFieldData;
    pData     : PChar;
begin
    pFldData        := PFieldData(FFieldData.Items[Field.FieldNo - 1]);
    Stream          := TMWBlobStream.Create;
    Stream.Field    := Field;
    Stream.Mode     := Mode;
    Stream.pFldData := pFldData;
    Stream.Buffer   := ActiveBuffer;
    Stream.FData    := Self;
    if (Mode = bmRead) {and FData.HasData} and (ActiveBuffer <> nil) then
        Stream.SetSize(GetBlobDataLen(ActiveBuffer, pFldData));
    // 23/12/98
    if (Mode = bmWrite) {and FData.HasData }and (ActiveBuffer <> nil) then begin
        // Clear any data already into buffer
        pData := GetBlobDataPtr(ActiveBuffer, pFldData);
        ReallocMem(pData, 1);
        SetBlobDataPtr(ActiveBuffer, pFldData, pData);
        SetBlobDataLen(ActiveBuffer, pFldData, 0);
        Stream.FModified := TRUE;
    end;
    Result := Stream;
//  writeln('CreateBlobStream Fld=', Field.FieldNo, ' Mode=', ord(Mode), ' Buffer=', IntToHex(Integer(Stream.Buffer), 8), ' Size=', Stream.Size);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.CloseBlob(Field: TField);
begin
    inherited CloseBlob(Field);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.ClearCalcFields(Buffer: PChar);
begin
    FillChar(Buffer[FCalcFieldsOffset], CalcFieldsSize, 0);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWDataSet.GetCurrentRecord(Buffer: PChar): Boolean;
begin
    TriggerDisplayInfo('GetCurrentRecord');
    Result := False;
    if not IsEmpty then begin
        Result := True;
        Move(ActiveBuffer^, Buffer^, FRecSize);  {not sure here, buffer may contain internal data}
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWDataSet.GetRecordSize: Word;
begin
    TriggerDisplayInfo('GetRecordSize');
    Result := FRecSize;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.InternalGotoBookmark(Bookmark: Pointer);
begin
    FInternalCurrent := TBookmarkInfo(Bookmark^);
    if Assigned(FData) then begin
        if FInternalCurrent = TPosition(-1) then
            FData.First
        else if FInternalCurrent = TPosition(-2) then begin
            FData.Last;
            FData.Next;
        end
        else
            FData.Seek(FInternalCurrent);
    end;
    TriggerDisplayInfo('InternalGotoBookmark ' +
                       IntToStr(FInternalCurrent));
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.InternalSetToRecord(Buffer: PChar);
begin
    TriggerDisplayInfo('InternalSetToRecord from buffer ' +
                       IntToHex(LongInt(Buffer), 8));
    FBufferFromInternalSetToRecord := Buffer;
    InternalGotoBookmark(Buffer + FBookmarkOffset);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.GetBookmarkData(Buffer: PChar; Data: Pointer);
begin
    Move(Buffer[FBookmarkOffset], Data^, BookmarkSize);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.SetBookmarkData(Buffer: PChar; Data: Pointer);
begin
    Move(Data^, Buffer[FBookmarkOffset], BookmarkSize);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWDataSet.GetBookmarkFlag(Buffer: PChar): TBookmarkFlag;
begin
    Result := PExtraRecInfo(Buffer + FExtraRecInfoOffset).BookmarkFlag;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.SetBookmarkFlag(Buffer: PChar; Value: TBookmarkFlag);
begin
  PExtraRecInfo(Buffer + FExtraRecInfoOffset).BookmarkFlag := Value;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWDataSet.BookmarkValid(Bookmark: TBookmark): Boolean;
var
    RecordPointer : TPosition;
begin
    RecordPointer := TBookmarkInfo(Bookmark^);
    TriggerDisplayInfo('BookmarkValid ' + IntToHex(LongInt(RecordPointer), 8));
    Result := Assigned(FData);
    if Result then begin
        CursorPosChanged;  { physical position no longer matches logical position }
        try
            FData.Seek(RecordPointer);
            { check for a deleted record }
            Result := TRUE;
        except
          Result := False;
        end;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWDataSet.CompareBookmarks(Bookmark1, Bookmark2: TBookmark): Integer;
begin
    TriggerDisplayInfo('CompareBookmarks');
  { bookmarks are equal if they are both nil or they both have the same value }
  if Bookmark1 = Bookmark2 then
    Result := 0
  else begin
    Result := 1;
    if Assigned(Bookmark1) and Assigned(Bookmark2) then
      if TBookmarkInfo(Bookmark1^) = TBookmarkInfo(Bookmark2^) then
        Result := 0;
  end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.SetFieldLayout(newValue : TFieldLayout);
begin
    if FFieldLayout = Trim(newValue) then
        Exit;

    if Active then
        raise EMWDataSetException.Create('Can''t change FieldLayout while table is active');
    FFieldLayout := Trim(newValue);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.InternalAddRecord(Buffer: Pointer; Append: Boolean);
begin
//Trace('InternalAddRecord');
    TriggerDisplayInfo('InternalAddRecord');
    { In our case, is doesn't matter if the record is being appended, }
    { inserts and appends both get written to the end of the file.    }
//    Move(Buffer^, MyData[FInternalCurrent], FRecSize);
    AppendData(Buffer);
    CursorPosChanged;
    Resync([rmExact, rmCenter]);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.InternalDelete;
begin
    TriggerDisplayInfo('InternalDelete ');
    if Assigned(FData) then begin
        FData.Seek(FInternalCurrent);
        FData.Delete;
    end;

    // Physical position no longer matches logical position
    CursorPosChanged;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.InternalEdit;
begin
    TriggerDisplayInfo('InternalEdit');
    { Refresh the current record }
    if Assigned(FData) then begin
        FData.Seek(FInternalCurrent);
        CopyFromCurrentRecord(ActiveBuffer);
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.InternalPost;
begin
//Trace('InternalPost ' + IntToHex(LongInt(ActiveBuffer), 8));
    if not Assigned(FData) then
        Exit;

    case State of
    dsEdit:
        begin
            TriggerDisplayInfo('InternalPost dsEdit');
            FData.Seek(FInternalCurrent);
            CopyToCurrentRecord(ActiveBuffer);
        end;
    dsInsert:
        begin
            TriggerDisplayInfo('InternalPost dsInsert');
            AppendData(ActiveBuffer);
            FData.Last;
            FInternalCurrent := FData.Tell;
            CursorPosChanged;
        end;
    else
        TriggerDisplayInfo('InternalPost Unknown');
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.InternalRefresh;
begin
    TriggerDisplayInfo('InternalRefresh');
    { This is where we would refresh any buffers we are using  }
    { between the data and TDataSet's internal record buffers. }
    Close;
    Open;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWDataSet.IsCursorOpen: Boolean;
begin
    Result := FCursorOpen;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ Copy data from a TField internal storage to our internal storage          }
procedure TMWDataSet.SetFieldData(Field: TField; Buffer: Pointer);
var
    Offset    : Integer;
    DataSize  : Integer;
    DataLen   : Integer;
    Value     : String;
    TimeStamp : TTimeStamp;
begin
//  Trace('TMWDataSet.SetFieldData ' + IntToHex(LongInt(Buffer), 8));
//  writeln('TMWDataSet.SetFieldData');
    TriggerDisplayInfo('SetFieldData ' + IntToStr(Field.FieldNo));
    if not (State in dsWriteModes) then
        DatabaseError(SNotEditing);         { 02/09/98 }

    if Field.FieldNo <> -1 then begin   { a physical field }
        { Cannot set fields while in OnCalcFields handler }
        if State = dsCalcFields then
            DatabaseError(SNotEditing);

        { 27/09/98 }
        if Field.ReadOnly and not (State in [dsSetKey, dsFilter]) then
            DatabaseErrorFmt(SFieldReadOnly, [Field.DisplayName]);
        Field.Validate(Buffer);

        { Offset is the position in our internal storage }
        Offset    := GetFieldOffset(Field.FieldNo - 1);
        { DataLen is our internal (ascii) storage length }
        DataLen   := GetFieldLen(Field.FieldNo - 1);
        { DataSize is TField internal (binary) storage size }
        DataSize  := Field.DataSize;

        if not Assigned(Buffer) then
            { If setting field to null, clear the field data }
            { Should I handle Memo, Blob and graphic ??      }
            FillChar(ActiveBuffer[Offset], DataSize, #0)
        else begin
            case Field.DataType of
            ftString:
                StrLCopy(ActiveBuffer + Offset, Buffer, DataSize);
            ftMemo, ftBlob, ftGraphic:
                raise Exception.Create('SetFieldData: program error');
            ftDate:
                begin
                    TimeStamp.Date := TDateTimeRec(Buffer^).Date;  // 30/12/98
                    TimeStamp.Time := 0;
                    Value          := TimeStampToMWFormat(TimeStamp);
                    StrLCopy(ActiveBuffer + Offset, @Value[1], DataLen);
                end;
            ftTime:
                begin
                    TimeStamp.Time := TDateTimeRec(Buffer^).Time; // 30/12/98
                    TimeStamp.Date := 0;
                    Value          := TimeStampToMWFormat(TimeStamp);
                    StrLCopy(ActiveBuffer + Offset, @Value[1], DataLen);
                end;
            ftDateTime:
                begin
                    TimeStamp := MSecsToTimeStamp(TDateTimeRec(Buffer^).DateTime);
                    Value     := TimeStampToMWFormat(TimeStamp);
                    StrLCopy(ActiveBuffer + Offset, @Value[1], DataLen);
                end;
            ftInteger:
                begin
                    Value := IntToStr(Integer(Buffer^));
                    StrLCopy(ActiveBuffer + Offset, @Value[1], DataLen);
                end;
            ftFloat:
                begin
                    Value := FloatToStrEx(Double(Buffer^)); // 29/01/99
                    StrLCopy(ActiveBuffer + Offset, @Value[1], DataLen);
                end;
            ftCurrency:
                begin
                    Value := FloatToStrEx(Double(Buffer^));  // 29/01/99
                    StrLCopy(ActiveBuffer + Offset, @Value[1], DataLen);
                end;
            ftBoolean:
                begin
                    if Boolean(Buffer^) then
                        Value := 'T'
                    else
                        Value := 'F';
                    StrLCopy(ActiveBuffer + Offset, @Value[1], DataLen);
                end;
            else
                raise EDatabaseError.Create('unsupported field type');
            end;
        end;
    end
    else begin   { a calculated field }
        Offset := FCalcFieldsOffset + Field.Offset;
        if Assigned(Buffer) then
            Move(Buffer^, CalcBuffer[Offset + 1], Field.DataSize);
    end;

    if not (State in [dsCalcFields]) then
        DataEvent(deFieldChange, Longint(Field));
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWDataSet.Locate(
    const KeyFields: string;           // Field list, separated by semi-colon
    const KeyValues: Variant;
    Options: TLocateOptions): Boolean;
var
    p        : PChar;
    FldName  : String;
    FldNum   : Integer;
    Delim    : Char;
    FldArray : String;
begin
    DoBeforeScroll;   // 29/01/99
    // Physical position no longer matches logical position
    CursorPosChanged;

    // Convert KeyFields which are fields names separated by semicolon to
    // an field number list consisting of a string where each field is
    // given by his number (starting from 1) expressed as a char
    // (Meaning that Ord(FldArray[I]) - 1 gives the field number
    // The 1 offset is there for proper string termination
    FldArray := '';
    p        := PChar(KeyFields);
    while (p <> nil) and (p^ <> #0) do begin
        p      := GetToken(p, FldName, Delim);
        FldNum := FieldDefs.IndexOf(FldName) + 1; // Zero based
        FldArray := FldArray + Chr(FldNum);
        if Delim <> ';' then
            break;
    end;

    if not Assigned(FData) then begin
        Result:= FALSE;
        Exit;
    end;

    Result := FData.Locate(FldArray, KeyValues, Options);

    if FData.Eof then
        FInternalCurrent := TPosition(-2)
    else if FData.Bof then
        FInternalCurrent := TPosition(-1)
    else
        FInternalCurrent := FData.Tell;

    if Result then
        Resync([rmExact, rmCenter]);

    DoAfterScroll;    // 29/01/99
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWDataSet.Lookup(
    const KeyFields: String;
    const KeyValues: Variant;
    const ResultFields: String): Variant;
begin
//    Result := False;
    raise EMWDataSetException.Create('TMWDataSet.Lookup not implemented');
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWDataSet.FindRecord(Restart, GoForward: Boolean): Boolean;
begin
    raise EMWDataSetException.Create('TMWDataSet.FindRecord not implemented');
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWDataSet.GetRecordCount: Longint;
begin
    Result := -1;        // Sequenced, no record count
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWDataSet.GetRecNo: Integer;
begin
    Result := -1;        // Sequenced, no record number
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWDataSet.SetRecNo(Value: Integer);
begin
    // Sequenced, no record number
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWDataSet.IsSequenced: Boolean;
begin
    // We use a sequenced data storage (TMWBuffer). It means that there
    // is no record number.
    Result := False;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
constructor TMWCustomTable.Create(AOwner : TComponent);
begin
    inherited Create(AOwner);
    FTimeout     := 10;
    FFieldLayout := 'FIELD1;C;10;FIELD2;C;15';
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWCustomTable.Notification(AComponent: TComponent; Operation: TOperation);
begin
    inherited Notification(AComponent, Operation);
    if Operation = opRemove then begin
        if AComponent = FAppSrvClient then
            AppSrvClient := nil;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TMWCustomTable.GetCanModify: Boolean;
begin
    Result := not FReadOnly;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWCustomTable.SetFunctionCode(newValue : String);
begin
    newValue := Trim(newValue);
    if newValue = FFunctionCode then
        Exit;
    if Active then
        raise EMWDataSetException.Create('Can''t change FunctionCode while table is active');
    FFunctionCode := newValue;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWCustomTable.SetParams(newValue : TRequestParams);
begin
    newValue := Trim(newValue);
    if newValue = FParams then
        Exit;

    if Active then
        raise EMWDataSetException.Create('Can''t change Params while table is active');
    FParams := newValue;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWCustomTable.SetAppSrvClient(newValue : TAppSrvClient);
begin
    if newValue = FAppSrvClient then
        Exit;

    if newValue = nil then
        Active := FALSE;
    if Active then
        raise EMWDataSetException.Create('Can''t change AppSrvClient while table is active');
    FAppSrvClient := newValue;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWCustomTable.SetTimeout(newValue : Integer);
begin
    if newValue <= 0 then
        FTimeout := 10
    else
        FTimeout := newValue;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ SendRequest is here just to be able to override it in descending          }
{ component to allow something to be done before actually sending a request }
procedure TMWCustomTable.SendRequest;
begin
    FAppSrvClient.Send;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This event handler is called because DesignTimeRequest was called.        }
procedure TMWCustomTable.AppSrvClientRequestDone(
    Sender: TObject;
    Error: Integer);
begin
    FRequestDoneFlag := TRUE;
    FRequestError    := Error;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TMWCustomTable.TriggerRequestDone(Error: Integer);
begin
    if Assigned(FOnRequestDone) then
        FOnRequestDone(Self, Error);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This event handler is called because ExecuteRequest was called.           }
procedure TMWCustomTable.AppSrvClientExecuteRequestDone(
    Sender: TObject;
    Error: Integer);
begin
    FRequestDoneFlag := TRUE;
    FRequestError    := Error;
    if (Error = 0) and (FAppSrvClient.AnswerStatus = '200') then
        Active := TRUE;
    TriggerRequestDone(Error);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ ExecuteRequest ask the AppSrvClient object to execute the same request as }
{ it is done at design time.                                                }
{ Be aware that AppSrvClient properties are modified by this call.          }
procedure TMWCustomTable.ExecuteRequest;
begin
    // Check for missing properties
    if not Assigned(FAppSrvClient) then
        raise EMWDataSetException.Create('TMWCustomTable.AppSrvClient not assigned');
    if not (Assigned(Data) or Assigned(FAppSrvClient.Answer)) then
        raise EMWDataSetException.Create('TMWCustomTable.Data not assigned');
    if Trim(FFunctionCode) = '' then
        raise EMWDataSetException.Create('TMWCustomTable.FunctionCode not assigned');

    Active := FALSE;
    FAppSrvClient.Request.Rewrite;

    // Parse the FParams string to build the request parameters TMWBuffer
    FAppSrvClient.Request.StringToRecords(FParams);

    FAppSrvClient.FunctionCode  := Trim(FFunctionCode);
    FRequestDoneFlag            := FALSE;
    FRequestError               := 0;
    FAppSrvClient.OnRequestDone := AppSrvClientExecuteRequestDone;
    if Assigned(Data) then
        FAppSrvClient.Answer    := Data
    else
        Data                    := FAppSrvClient.Answer;
    SendRequest;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This procedure is called at design time to populate the dataware controls.}
{ To execute the same request at runtime, you should use ExecuteRequest.    }
procedure TMWCustomTable.DesignTimeRequest;
var
    Timeout          : Integer;
    OldFunctionCode  : String;
    OldOnRequestDone : TRequestDone;
    ErrMsg           : String;
begin
    if FBusy then
        Exit;
    Active           := FALSE;
    OldFunctionCode  := FAppSrvClient.FunctionCode;
    OldOnRequestDone := FAppSrvClient.OnRequestDone;
    try
        FBusy := TRUE;
        FAppSrvClient.Request.Rewrite;

        // Parse the FParams string to build the request parameters TMWBuffer
        FAppSrvClient.Request.StringToRecords(FParams);

        FAppSrvClient.FunctionCode  := Trim(FFunctionCode);
        FRequestDoneFlag            := FALSE;
        FRequestError               := 0;
        FAppSrvClient.OnRequestDone := AppSrvClientRequestDone;
        if Assigned(Data) then
            FAppSrvClient.Answer    := Data
        else
            Data                    := FAppSrvClient.Answer;
        SendRequest;
        { SendRequest is asynchronous, so we must wait until the request }
        { is executed in the background or some timeout elapsed.         }
        { This is bad code, but I don't know how to do it otherwise.     }
        Timeout := Integer(GetTickCount) + FTimeout * 1000;
        while (not FRequestDoneFlag) and (Timeout > Integer(GetTickCount)) do begin
            Application.ProcessMessages;
            Sleep(0);
        end;
        if not FRequestDoneFlag then
            ErrMsg := 'Timeout executing request'
        else if FRequestError <> 0 then
            ErrMsg := 'Can''t execute request, error #' +
                                   IntToStr(FRequestError)
        else if (FAppSrvClient.AnswerStatus <> '200') and
                (FAppSrvClient.AnswerStatus <> 'OK')  then
            { By convention, we suppose the server either return 'OK' if }
            { successfull, or FTP like result code, '200' meaning OK.    }
            ErrMsg := 'Server reported error #' +
                      FAppSrvClient.AnswerStatus +
                      ' while executing request: ' +
                      FAppSrvClient.Answer.RecordToString
        else
            ErrMsg := '';

        if ErrMsg <> '' then begin
            if csDesigning in ComponentState then
                FAppSrvClient.Answer.Rewrite
            else
                raise EMWDataSetException.Create(ErrMsg);
        end;
    finally
        FBusy                       := FALSE;
        FAppSrvClient.FunctionCode  := OldFunctionCode;
        FAppSrvClient.OnRequestDone := OldOnRequestDone;
        FAppSrvClient.Close;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ We override the InternalOpen method to be able to populate data-aware     }
{ components at run-time.                                                   }
procedure TMWCustomTable.InternalOpen;
begin
    if (Assigned(FAppSrvClient) and (Trim(FFunctionCode) > '') and
       (csDesigning in ComponentState)) and
       (not (csLoading in ComponentState)) then
        DesignTimeRequest;
    inherited InternalOpen;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure Register;
begin
    RegisterComponents('FPiette', [TMWTable]);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{$ELSE}
{ TMWCustomTable is not compatible with Delphi 2 nor BCB 1 }
{ Declare and implement a dummy component.           }
uses Windows, Classes;
type TMWCustomTable = class(TComponent);
procedure Register;
implementation
procedure Register;
begin RegisterComponents('FPiette', [TMWTable]); end;
{$ENDIF}

end.

