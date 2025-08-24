{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Author:       François Piette
Description:  TTrackDataSet keep track of TDataSet insert, delete and update.
              See Quick Referece below.
Creation:     April 1, 1999
Version:      1.01
EMail:        francois.piette@overbyte.be   francois.piette@rtfm.be
              http://www.overbyte.be        http://www.rtfm.be/fpiette
              francois.piette@pophost.eunet.be
Support:      Use the mailing list midware@elists.org
              Follow "support" link at http://www.overbyte.be for subscription.
Legal issues: Copyright (C) 1999-2001 by François PIETTE
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

Quick Reference:
    TTrackDataSet component is use to track changes (edit, insert, delete)
    made in a TDataSet (TTable, TQuery or any other TDataSet descendent).
    It does it by installing event handler to the TDataSet to be informed
    about changes. Event handled are BeforeDelete, BeforeEdit, BeforeInsert,
    AfterDelete and AfterPost. Those event once captured by TTrackDataSet
    can still be used because the component relay them to other events.

    TTrackDataSet component use a TTrackData object to hold fields content
    and definition. TTrackData object mainly consist of a TList used to hold
    a list of all data fields from TDataSet. Elements of the list are pointers
    to TTrackDataField.

    Before any change is made to a TDataSet, TTrackDataSet component record
    all field values into a TTrackData, accessible thru DataBefore property.
    After any changes are posted, TTrackDataSet component record new values
    into a second TTrackData, accessible thru DataAfter property. And then fire
    the OnDataChanged event. Operation done is saved in Operation property.

    From the OnDataChanged event, the programmer can get the operation done
    (insert, delete or update) in the Operation property, the data
    before the operation in DataBefore property and data after the operation in
    DataAfter property. At that point, those informations may be save to build
    a log file to later undo the changes, or apply them again (to implement
    brielcase model for example).

Updates:
Sep 15, 2001 V1.01 Delphi 6


 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
unit TrackDs;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  db;

const
    AppSrvClientVersion = 101;
    CopyRight : String  = ' TTrackData (c) 1999-2001 F. Piette V1.01 ';

type
  TTrackDataSetOperation = (tdsoNone, tdsoInsert, tdsoDelete, tdsoUpdate);
const
  TrackDataSetOperationName : array [TTrackDataSetOperation] of String =
      ('tdsoNone', 'tdsoInsert', 'tdsoDelete', 'tdsoUpdate');
type
  ETrackDataSetException   = class(EXception);
  TTrackDataSetNotifyEvent = procedure (Sender : TObject; DataSet : TDataSet) of object;

  // TTrackDataField is used to hold all informations from a dataset field
  TTrackDataField = class(TObject)
    Data      : PChar;       // Pointer to buffer holding data
    DataSize  : Integer;     // Size of data buffer
    DataType  : TFieldType;  // Field datatype
    FieldName : String;      // Field name
    Changed   : Boolean;     // Changed flag, updated by compare method
    function  AsString : String;
  end;
  TTrackDataFieldClass = class of TTrackDataField;

  // TTrackDataItem is an enuùeration of all items that can be included in
  // convertion from TTrackDataField to string (AsString method).
  TTrackDataItem  = (tdiData,      tdiDataSize, tdiDataType,
                     tdiFieldName, tdiChanged);
  TTrackDataItems = set of TTrackDataItem;

  // TTrackData is an object used to hold data fields from a dataset record
  // It is a kind of record duplicate, but no tied to any database system
  TTrackData = class(TObject)
  protected
    FFieldClass : TTrackDataFieldClass;  // Class to be used for fields
    FFields     : TList;                 // A list for all TTrackDataField
    function GetFieldCount : Integer;
    function GetField(nIndex : Integer) : TTrackDataField;
  public
    constructor Create; virtual;
    destructor  Destroy; override;
    // Clear the list, freeing memory
    procedure   Clear;
    // Add a field to the list. Data is copied to a TTrackDataField
    function    Add(DataSetField : TField) : Integer;
    // Delete a field from list, releasing used memory
    procedure   Delete(Index : Integer);
    // Convert to string representation, with a set of items to take care of
    function    AsString(How : TTrackDataItems) : String;
    // Find a field by name
    function    FieldByName(const FieldName : String) : TTrackDataField;
    // Compare this TTrackData with an other one, updating both Changed flags
    // Returns TRUE if both are excatly matching.
    function    Compare(Other : TTrackData) : Boolean;
    // Returns the number of field added to the list
    property    FieldCount : Integer read GetFieldCount;
    // Give access to a field (TTrackDataField) from the list
    property    Fields[nIndex : Integer] : TTrackDataField read GetField;
  end;

  TCustomTrackDataSet = class(TComponent)
  protected
    FDataSet        : TDataSet;
    FOperation      : TTrackDataSetOperation;
    FDataBefore     : TTrackData;
    FDataAfter      : TTrackData;
    FBeforeDelete   : TTrackDataSetNotifyEvent;
    FBeforeEdit     : TTrackDataSetNotifyEvent;
    FBeforeInsert   : TTrackDataSetNotifyEvent;
    FAfterDelete    : TTrackDataSetNotifyEvent;
    FAfterPost      : TTrackDataSetNotifyEvent;
    FAfterCancel    : TTrackDataSetNotifyEvent;
    FOnDataChanging : TNotifyEvent;
    FOnDataChanged  : TNotifyEvent;
    procedure   Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure   TriggerBeforeDelete(DataSet: TDataSet); virtual;
    procedure   TriggerBeforeEdit(DataSet: TDataSet); virtual;
    procedure   TriggerBeforeInsert(DataSet: TDataSet); virtual;
    procedure   TriggerAfterDelete(DataSet: TDataSet); virtual;
    procedure   TriggerAfterPost(DataSet: TDataSet); virtual;
    procedure   TriggerAfterCancel(DataSet: TDataSet); virtual;
    procedure   TriggerDataChanging; virtual;
    procedure   TriggerDataChanged; virtual;
    procedure   DataSetBeforeDelete(DataSet: TDataSet); virtual;
    procedure   DataSetBeforeEdit(DataSet: TDataSet); virtual;
    procedure   DataSetBeforeInsert(DataSet: TDataSet); virtual;
    procedure   DataSetAfterDelete(DataSet: TDataSet); virtual;
    procedure   DataSetAfterPost(DataSet: TDataSet); virtual;
    procedure   DataSetAfterCancel(DataSet: TDataSet); virtual;
    procedure   SetDataSet(NewValue : TDataSet); virtual;
    function    GetTracking : Boolean; virtual;
    procedure   SetTracking(NewValue : Boolean);
    procedure   SaveRecord(Dst : TTrackData); virtual;
  public
    constructor Create(AOwner : TComponent); override;
    destructor  Destroy; override;
    // Start tracking data set. It attach event handlers to TDataSet, deleting
    // existing event handlers.
    procedure TrackOn; virtual;
    // Stop tracking data set. Remove all event handlers from TDataSet. Do
    // not restore event handlers that was installed before TrackOn call.
    procedure TrackOff; virtual;
    // Detach a TTrackData (such as DataBefore or DataAfter) from the
    // component. Programmer then becomes responsible for freeing it when is
    // is no more needed or he will experience memory leaks.
    procedure Detach(TrackData : TTrackData); virtual;

    // Check or set component tracking activity
    property  Active : Boolean                          read  GetTracking
                                                        write SetTracking;
    // Current operation
    property  Operation  : TTrackDataSetOperation       read  FOperation;
    // Data before the operation
    property  DataBefore : TTrackData                   read  FDataBefore;
    // Data after the operation
    property  DataAfter  : TTrackData                   read  FDataAfter;

    // Tracket TDataSet (TTable, TQuery or any other TDataSet)
    property DataSet : TDataSet                         read  FDataSet
                                                        write SetDataSet;
    // OnDataChanging is fired when change are about to be made
    property OnDataChanging : TNotifyEvent              read  FOnDataChanging
                                                        write FOnDataChanging;
    // OnDataChanged is fired when an operation is done (insert, delete, update)
    property OnDataChanged : TNotifyEvent               read  FOnDataChanged
                                                        write FOnDataChanged;
    // Event triggered when TDataSet.BeforeDelete is triggered
    property BeforeDelete: TTrackDataSetNotifyEvent     read  FBeforeDelete
                                                        write FBeforeDelete;
    // Event triggered when TDataSet.BeforeEdit is triggered
    property BeforeEdit: TTrackDataSetNotifyEvent       read  FBeforeEdit
                                                        write FBeforeEdit;
    // Event triggered when TDataSet.BeforeInsert is triggered
    property BeforeInsert: TTrackDataSetNotifyEvent     read  FBeforeInsert
                                                        write FBeforeInsert;
    // Event triggered when TDataSet.AfterDelete is triggered
    property AfterDelete: TTrackDataSetNotifyEvent      read  FAfterDelete
                                                        write FAfterDelete;
    // Event triggered when TDataSet.AfterPost is triggered
    property AfterPost: TTrackDataSetNotifyEvent        read  FAfterPost
                                                        write FAfterPost;
    // Event triggered when TDataSet.AfterCancel is triggered
    property AfterCancel: TTrackDataSetNotifyEvent      read  FAfterCancel
                                                        write FAfterCancel;
  end;

  TTrackDataSet = class(TCustomTrackDataSet)
  published
    property DataSet;
    property OnDataChanging;
    property OnDataChanged;
    property BeforeDelete;
    property BeforeEdit;
    property BeforeInsert;
    property AfterDelete;
    property AfterPost;
    property AfterCancel;
  end;


procedure Register;

implementation

function DoubleQuote(Value : String) : String; forward;



{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TTrackDataField.AsString : String;
var
    J, N : Integer;
const
    HexDigit : array [0..15] of char =
        ('0', '1', '2', '3', '4', '5', '6', '7',
         '8', '9', 'A', 'B', 'C', 'D', 'E', 'F');
    BooleanToStr : array [Boolean] of string = ('FALSE', 'TRUE');
type
    PDateTimeRec = ^TDateTimeRec;
    PDateTime    = ^TDateTime;
begin
    case DataType of
    ftString :
        Result := '''' + DoubleQuote(Data) + '''';
    ftInteger:
        Result := IntToStr(PInteger(Data)^);
    ftBoolean:
        Result := BooleanToStr[Data^ <> #0];
    ftFloat, ftCurrency:
        Result := FloatToStr(PDouble(Data)^);
    ftDate:
        Result := FormatDateTime('YYYYMMDD',
                  PDateTimeRec(Data)^.Date - DateDelta);
    ftTime:
        Result := FormatDateTime('HHNNSS',
                  PDateTimeRec(Data)^.Time / MSecsPerDay);
    ftDateTime :
        if PDateTime(Data)^ = 0 then
            Result := '00000000 000000'
        else
            Result := FormatDateTime('YYYYMMDD HHNNSS',
                      (PDateTimeRec(Data)^.DateTime / MSecsPerDay) - DateDelta);
    ftBlob, ftMemo, ftGraphic :
        begin
           // We have binary data. Every control code if outputed like
           // an hex number, including quote and dollars sign
           // We will do a first pass to now how many hex char we have
           // Two passes are needed because long string handling is very
           // slow if adding one char at a time
           N := 0;
           for J := 0 to DataSize - 1 do begin
               if Data[J] in [#0..#31, '$', ''''] then
                   Inc(N);
           end;
           // Now we can adjust result size
           SetLength(Result, 2 + DataSize + N + N);
           // And do the second pass to set result value
           Result[1] := '''';
           N := 2;
           for J := 0 to DataSize - 1 do begin
               if Data[J] in [#0..#31, '$', ''''] then begin
                   Result[N] := '$';
                   Inc(N);
                   Result[N] := HexDigit[Ord(Data[J]) shr 4];
                   Inc(N);
                   Result[N] := HexDigit[Ord(Data[J]) and 15];
               end
               else
                   Result[N] := Data[J];
               Inc(N);
           end;
           Result[N] := '''';
        end;
    else
        raise ETrackDataSetException.Create(
                'TTrackDataField.AsString: ' +
                'unsupported field type for field ''' +
                FieldName + '''');
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
constructor TTrackData.Create;
begin
    inherited Create;
    FFieldClass := TTrackDataField;
    FFields     := TList.Create;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
destructor TTrackData.Destroy;
begin
    if Assigned(FFields) then begin
        FFields.Clear;
        // Delete the list
        FFields.Destroy;
        FFields := nil;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTrackData.Clear;
var
    Index : Integer;
begin
    // Delete all items from the list
    for Index := FieldCount - 1 downto 0 do
        Delete(Index);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TTrackData.GetFieldCount : Integer;
begin
    if Assigned(FFields) then
        Result := FFields.Count
    else
        Result := 0;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TTrackData.GetField(nIndex : Integer) : TTrackDataField;
begin
    if (nIndex < 0) or (nIndex >= FieldCount) then
        raise ETrackDataSetException.Create('TTrackData.GetField: Index out of range');
    Result := FFields.Items[nIndex];
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TTrackData.FieldByName(const FieldName : String) : TTrackDataField;
var
    Index : Integer;
begin
    for Index := FieldCount - 1 downto 0 do begin
        Result := FFields.Items[Index];
        if CompareText(Result.FieldName, FieldName) = 0 then
            Exit;
    end;
    raise ETrackDataSetException.Create('TTrackData.FieldByName: Field ''' +
                                        FieldName + ''' doesn''t exists.');
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TTrackData.AsString(How : TTrackDataItems) : String;
var
    Index : Integer;
    Field : TTrackDataField;
    Count : Integer;
    I     : Integer;
const
    HexDigit : array [0..15] of char =
        ('0', '1', '2', '3', '4', '5', '6', '7',
         '8', '9', 'A', 'B', 'C', 'D', 'E', 'F');
    BooleanToStr : array [Boolean] of string = ('FALSE', 'TRUE');
type
    PDateTimeRec = ^TDateTimeRec;
begin
    // Empty How means all informations
    if How = [] then
        How := [tdiData, tdiDataSize, tdiDataType, tdiFieldName];
    Result := '';
    I      := 0;
    Count  := FieldCount - 1;
    for Index := 0 to Count do begin
        Field := Fields[Index];
        if (tdiChanged in How) and (not Field.Changed) then
            continue;
        if I > 0 then
            Result := Result + ';';
        if tdiFieldName in How then
            Result := Result + Field.FieldName + ':';
        if tdiDataSize in How then
            Result := Result + IntToStr(Field.DataSize) + ':';
        if tdiDataType in How then
            Result := Result + IntToStr(Ord(Field.DataType)) + ':';
        if tdiData in How then
            Result := Result + Field.AsString;
        Inc(I);
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
// Update Changed flag by comparing with other TTrackData
// Returns TRUE if ALL fields are the same
// If field counts are not equals, return FALSE and flag all fields
// as changed.
// Do not check field names (speed !). They should not change anyway.
function TTrackData.Compare(Other : TTrackData) : Boolean;
var
    Index  : Integer;
    Field1 : TTrackDataField;
    Field2 : TTrackDataField;
    Count  : Integer;
    I      : Integer;
    P, Q   : PChar;
begin
    Count := FieldCount - 1;
    if Count <> (Other.FieldCount - 1) then begin
        Result := FALSE;
        for Index := 0 to Count do
            Fields[Index].Changed := TRUE;
        Exit;
    end;
    Result := TRUE;
    for Index := 0 to Count do begin
        Field1         := Fields[Index];
        Field2         := Other.Fields[Index];
        Field1.Changed := FALSE;
        Field2.Changed := FALSE;
        if (Field1.DataSize <> Field2.DataSize) or
           (Field1.DataType <> Field2.DataType) then begin
           // Size or type not the same, consider as changed
           Field1.Changed := TRUE;
           Field2.Changed := TRUE;
           Result         := FALSE;
        end
        else begin
           // Size and type are the same, compare data (binary compare)
           P := Field1.Data;
           Q := Field2.Data;
           I := 0;
           while I < Field1.DataSize do begin
               if P^ <> Q^ then begin
                   Field1.Changed := TRUE;
                   Field2.Changed := TRUE;
                   Result         := FALSE;
                   break;
               end;
               Inc(P);
               Inc(Q);
               Inc(I);
           end;
        end;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TTrackData.Add(DataSetField : TField) : Integer;
var
    Field      : TTrackDataField;
    BlobStream : TStream;
begin
    if not Assigned(DataSetField) then
        raise ETrackDataSetException.Create('TTrackData.Add: Field not assigned');

    // Allocate a new data record
    Field := FFieldClass.Create;

    // Append the record to the list
    Result := FFields.Add(Field);

    // Copy data from field to allocated record
    Field.DataType  := DataSetField.DataType;
    Field.FieldName := DataSetField.FieldName;
    Field.Changed   := FALSE;
    if DataSetField.IsBlob then begin
        BlobStream := DataSetField.DataSet.CreateBlobStream(DataSetField, bmRead);
        try
            Field.DataSize := BlobStream.Size;
            if Field.DataSize > 0 then begin
                // Allocate memory to hold data
                Field.Data := AllocMem(Field.DataSize);
                // Get data into allocated memory
                BlobStream.ReadBuffer(Field.Data^, Field.DataSize);
            end;
        finally
            BlobStream.Free;
        end;
    end
    else begin
        // Copy field info and data to record
        Field.DataSize  := DataSetField.DataSize;
        if Field.DataSize > 0 then begin
            // Allocate memory to hold data
            Field.Data := AllocMem(Field.DataSize);
            // Get data into allocated memory
            DataSetField.GetData(Field.data);
        end;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTrackData.Delete(Index : Integer);
var
    Field : TTrackDataField;
begin
    if (Index < 0) or (Index >= FFields.Count) then
        raise ETrackDataSetException.Create('TTrackData.Delete: Index out of range');
    Field := FFields.Items[Index];
    if Field.DataSize > 0 then
        FreeMem(Field.Data);
    Field.Destroy;
    FFields.Delete(Index);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
constructor TCustomTrackDataSet.Create(AOwner : TComponent);
begin
    inherited Create(AOwner);
    FDataBefore := TTrackData.Create;
    FDataAfter  := TTrackData.Create;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
destructor TCustomTrackDataSet.Destroy;
begin
    if Assigned(FDataBefore) then begin
        FDataBefore.Destroy;
        FDataBefore := nil;
    end;
    if Assigned(FDataAfter) then begin
        FDataAfter.Destroy;
        FDataAfter := nil;
    end;
    inherited Destroy;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TCustomTrackDataSet.SetDataSet(NewValue : TDataSet);
begin
    if NewValue = FDataSet then
        Exit;
    TrackOff;
    FDataSet := NewValue;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TCustomTrackDataSet.GetTracking : Boolean;
var
    Temp : TDataSetNotifyEvent;
begin
    if not Assigned(FDataSet) then
        Result := FALSE
    else begin
        Temp   := DataSetBeforeDelete;
        Result := (@FDataSet.BeforeDelete = @Temp);
        if Result then begin
            Temp   := DataSetBeforeInsert;
            Result := (@FDataSet.BeforeInsert = @Temp);
        end
        else if Result then begin
            Temp   := DataSetBeforeEdit;
            Result := (@FDataSet.BeforeEdit = @Temp);
        end
        else if Result then begin
            Temp   := DataSetAfterDelete;
            Result := (@FDataSet.AfterDelete = @Temp);
        end
        else if Result then begin
            Temp   := DataSetAfterPost;
            Result := (@FDataSet.AfterPost = @Temp);
        end
        else if Result then begin
            Temp   := DataSetAfterCancel;
            Result := (@FDataSet.AfterCancel = @Temp);
        end;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TCustomTrackDataSet.SetTracking(NewValue : Boolean);
begin
    if NewValue then
        TrackOn
    else
        TrackOff;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TCustomTrackDataSet.Detach(TrackData : TTrackData);
begin
    if TrackData = FDataBefore then
        FDataBefore := nil
    else if TrackData = FDataAfter then
        FDataAfter := nil;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TCustomTrackDataSet.TrackOn;
begin
    if not Assigned(FDataSet) then
        raise ETrackDataSetException.Create(
                 'TrackOn failed: Dataset property is unassigned');
    FDataSet.BeforeDelete  := DataSetBeforeDelete;
    FDataSet.BeforeEdit    := DataSetBeforeEdit;
    FDataSet.BeforeInsert  := DataSetBeforeInsert;
    FDataSet.AfterDelete   := DataSetAfterDelete;
    FDataSet.AfterPost     := DataSetAfterPost;
    FDataSet.AfterCancel   := DataSetAfterCancel;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TCustomTrackDataSet.TrackOff;
begin
    FOperation := tdsoNone;
    if not Assigned(FDataSet) then
        Exit;
    FDataSet.BeforeDelete  := nil;
    FDataSet.BeforeEdit    := nil;
    FDataSet.BeforeInsert  := nil;
    FDataSet.AfterDelete   := nil;
    FDataSet.AfterPost     := nil;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TCustomTrackDataSet.TriggerBeforeDelete(DataSet: TDataSet);
begin
    if Assigned(FBeforeDelete) then
        FBeforeDelete(Self, DataSet);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TCustomTrackDataSet.TriggerBeforeEdit(DataSet: TDataSet);
begin
    if Assigned(FBeforeEdit) then
        FBeforeEdit(Self, DataSet);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TCustomTrackDataSet.TriggerBeforeInsert(DataSet: TDataSet);
begin
    if Assigned(FBeforeInsert) then
        FBeforeInsert(Self, DataSet);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TCustomTrackDataSet.TriggerAfterDelete(DataSet: TDataSet);
begin
    if Assigned(FAfterDelete) then
        FAfterDelete(Self, DataSet);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TCustomTrackDataSet.TriggerAfterCancel(DataSet: TDataSet);
begin
    if Assigned(FAfterCancel) then
        FAfterCancel(Self, DataSet);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TCustomTrackDataSet.TriggerAfterPost(DataSet: TDataSet);
begin
    if Assigned(FAfterPost) then
        FAfterPost(Self, DataSet);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TCustomTrackDataSet.TriggerDataChanging;
begin
    if Assigned(FOnDataChanging) then
        FOnDataChanging(Self);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TCustomTrackDataSet.TriggerDataChanged;
begin
    if Assigned(FOnDataChanged) then
        FOnDataChanged(Self);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TCustomTrackDataSet.DataSetBeforeDelete(DataSet: TDataSet);
begin
    TriggerBeforeDelete(DataSet);
    TriggerDataChanging;
    FOperation := tdsoDelete;
    SaveRecord(FDataBefore);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TCustomTrackDataSet.DataSetBeforeEdit(DataSet: TDataSet);
begin
    TriggerBeforeEdit(DataSet);
    TriggerDataChanging;
    FOperation := tdsoUpdate;
    SaveRecord(FDataBefore);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TCustomTrackDataSet.DataSetBeforeInsert(DataSet: TDataSet);
begin
    TriggerBeforeInsert(DataSet);
    TriggerDataChanging;
    FOperation := tdsoInsert;
    FDataBefore.Clear;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TCustomTrackDataSet.DataSetAfterDelete(DataSet: TDataSet);
begin
    FDataAfter.Clear;
    TriggerDataChanged;
    TriggerAfterDelete(DataSet);
    FOperation := tdsoNone;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TCustomTrackDataSet.DataSetAfterPost(DataSet: TDataSet);
begin
    SaveRecord(FDataAfter);
    TriggerDataChanged;
    TriggerAfterPost(DataSet);
    FOperation := tdsoNone;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TCustomTrackDataSet.DataSetAfterCancel(DataSet: TDataSet);
begin
    FDataBefore.Clear;
    TriggerAfterCancel(DataSet);
    FOperation := tdsoNone;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TCustomTrackDataSet.SaveRecord(Dst : TTrackData);
var
    Index : Integer;
begin
    if not Assigned(Dst) then
        Exit;
    Dst.Clear;
    for Index := 0 to FDataSet.FieldCount - 1 do
        Dst.Add(FDataSet.Fields[Index]);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TCustomTrackDataSet.Notification(AComponent: TComponent; Operation: TOperation);
begin
    inherited Notification(AComponent, Operation);
    if Operation = opRemove then begin
        if AComponent = FDataSet then begin
            FDataSet := nil;
            TrackOff;
        end;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function  DoubleQuote(Value : String) : String;
var
    I : Integer;
begin
    Result := '';
    for I := 1 to Length(Value) do begin
        if Value[I] = '''' then
            Result := Result + ''''''
        else
            Result := Result + Value[I];
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure Register;
begin
  RegisterComponents('FPiette', [TTrackDataSet]);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}

end.
