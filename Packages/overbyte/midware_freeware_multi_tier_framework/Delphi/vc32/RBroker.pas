{*_* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Author:       François PIETTE
Description:  Object Request Broker (ORB) for F. Piette's middleware (MidWare).
              The ORB is one of the two major components for the application
              server (an application server is composed of the application
              server component, the request broker component and several server
              components). The ORB is responsible for dispatching client request
              to server object which knows how to execute the request.
Creation:     February 26, 1998
Version:      1.10
EMail:        francois.piette@overbyte.be   francois.piette@rtfm.be
              http://www.overbyte.be        http://www.rtfm.be/fpiette
              francois.piette@pophost.eunet.be
Support:      Use the mailing list midware@elists.org
              Follow "support" link at http://www.overbyte.be for subscription.
Legal issues: Copyright (C) 1998-2001 by François PIETTE
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

Updates:
Mar 05, 1998  V1.01 TServerObjectUNKNOWN called inherited Execute. Corrected
              call Finish method.
              Created RBrokerVersion constant.
May 23, 1998  V1.02 Renamed procedure Display to TriggerDisplay to be consistent
              with convention used with events management.
              Added comments for methods, properties and events documentation.
Jun 01, 1998  V1.03 Removed beta status. Changed "legal stuff" to prohibe
              commercial applications whithout an agreement.
Jun 21, 1998  V1.04 Adapted for C++Builder V3 (do not support multiple
              constructors).
Jul 08, 1998  V1.05 Adapted for Delphi 4 (added a dummy argument to second
              constructor to remove warning).
Jul 15, 1998  V1.06 Added Tag argument in CrackHeader to help descending
              classes.
Sep 10, 1998  V1.07 Added AppServer to TOrbData
              Added Sender to BrokeRequest function
Jun 06, 1999  V1.08 Set AutoExpand equal to 0 in GiveRequest.
Oct 29, 2001  V1.09 Exposed TServerObject.UserData and ResultStatus as public
              properties
Nov 07, 2001  V1.10 Exposed TServerObject.ORBDataPtr as public property.


 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
unit RBroker;

interface

{$B-}           { Enable partial boolean evaluation   }
{$T-}           { Untyped pointers                    }
{$J+}           { Allow typed constant to be modified }
{$IFDEF VER110} { C++ Builder V3.0                    }
    {$ObjExportAll On}
{$ENDIF}

uses
    WinTypes, WinProcs, SysUtils, StdCtrls, Classes, RFormat;

const
    RBrokerVersion      = 110;
    CopyRight : String  = ' TRequestBroker (c) 1998, 2001 F. Piette V1.10 ';
    ServerObjectVersion = RBrokerVersion;

type
    ERequestBrokerException = class(Exception);
    TRequestBroker          = class;
    TServerObject           = class;
    TServerObjectClass      = class of TServerObject;

    TRequestBrokerOption     = (rboDisplayObjectCount);
    TRequestBrokerOptions    = set of TRequestBrokerOption;

    TDisplayEvent = procedure (Sender : TObject; Msg : String) of object;
    TSendResponseToClient = procedure (Dest     : TObject;
                                       ORB      : TRequestBroker;
                                       Status   : Integer;
                                       Response : PChar;
                                       Len      : Integer) of object;

    TORBData = record
        SendResp  : TSendResponseToClient;
        Tag       : TObject;                     { CliWSocket    }
        Item      : Integer;
        ORB       : TRequestBroker;              { RequestBroker }
        AppServer : TObject;                     { AppServer     }
    end;
    PORBData = ^TORBData;

    {:TServerObject is the ancestor (abstract class) for all object responsible
      for doing the application server work. The ORB create instances of server
      object, pass client request to them and call their Execute method. When
      the server object work is done, it must call the Finish method to send
      the response back to the client. This can be done either from the execute
      method or form any other point later in time. }
    TServerObject = class(TComponent)
    protected
        {:The FunctionCode is used by the ORB to know how to dispatch client
          requests to the various server objects he has in his table. By default
          the FunctionCode is derived from the server object class name and is
          the class name without the leading TServerObject. You can override
          the BuildFunctionCode method to change that behaviour. The function
          code is case insensitive. }
        FFunctionCode   : String;
        {:Where the request comes in. }
        FRequestBuffer  : TMWBuffer;
        {:Where the result goes to. }
        FResponseBuffer : TMWBuffer;
        {:The default response size. }
        FResponseSize   : Integer;
        {:ResultStatus returned to client. Based on the model used by the HTTP
          protocol: 200 means OK, 400 means error. See HTTP protocol reference.
          The server does'nt really use this ResultStatus. It's used by the
          client. The ResultStatus value is returned in the client's
          TAppSrvClient AnswerStatus property as a string. }
        FResultStatus   : Integer;
        {:Reserved for the TServerObject descendent writer. It is generally used
          to pass global data from the application server to the various server
          object. For example TTable or any other global data. Using FUserData
          is far better way of programming than using global variables. }
        FUserData          : LongInt;
        {:To be used for persistent data. }
        FIniFileName       : String;
        {:Data received from the ORB. }
        FORBDataPtr        : PORBData;
        FRequestBroker     : TRequestBroker;
        FServerObjectClass : TServerObjectClass;
        FOnRequestDone     : TNotifyEvent;
        FOnDisplay         : TDisplayEvent;
        {:Triggers the OnDisplay event, if assigned. }
        procedure TriggerDisplay(Msg : String); virtual;
        {:BuildFunctionCode will initialize FFunctionCode with the function
          code handled by the ServerObject. Default to the class name
          without TServerObject. }
        procedure BuildFunctionCode; virtual;
        procedure Loaded; override;
        procedure Notification(AComponent: TComponent; operation: TOperation); override;
        procedure CopyFromReference(Reference : TServerObject); virtual;
{$IFNDEF VER110} { C++Builder do not support multiple constructors }
        {:This constructor is used by the ORB just to get the function code.
          Normally not used outside of the ORB code. }
        constructor CreateForFunctionCode(AOwner : TComponent; Dummy : Integer); virtual;
{$ENDIF}
    public
        constructor Create(AOwner : TComponent); override;
        destructor  Destroy; override; 
        {:The ORB (Object Request Broker, TRequestBroker component) call this
          method to pass a request from the client to the server object. }
        procedure GiveRequest(RqBuffer : PChar; RqLength : Integer); virtual;
        {:The ORB (Object Request Broker, TRequestBroker component) call this
          method when the server object must be initialized. This is done only
          ONCE per server run. This procedure can be overriden to place any
          code needed to initialize global data for the server object. }
        procedure Initialize; virtual;
        {:The ORB (Object Request Broker, TRequestBroker component) call this
          method to make the server object do his work: execute the request
          and produce a response. You MUST override this method and place the
          effective code for the server object work. }
        procedure Execute; virtual;
        {:The server object MUST call this method to signal the ORB (Object
          Request Broker, TRequestBroker component) that the server's object
          work is done and the response is ready to be sent to the client.
          You can call Finish just before returning from the Execute method, or
          at some later moment if the server object continue processing in the
          background after the Execute method has returned control back to the
          ORB (this means you have written an event driven server object or a
          multi-threaded server object). While Execute method code runs, no
          other client is serviced. If the processing is long, you probably
          wants to start a thread to do the processing in the background and
          call Finish method at a later time, or wants to write a fully
          event-driven server object which works by sending messages. }
        procedure Finish; virtual;
        property UserData          : LongInt       read  FUserData
                                                   write FUserData;
        property ResultStatus      : Integer       read  FResultStatus
                                                   write FResultStatus;
        property ORBDataPtr        : PORBData      read  FORBDataPtr
                                                   write FORBDataPtr;
    published
        property RequestBroker : TRequestBroker    read  FRequestBroker
                                                   write FRequestBroker;
    end;

    { This ServerObject is used when the ORB is asked to execute an unknown   }
    { function code.                                                         }
    TServerObjectUNKNOWN = class(TServerObject)
    private
        FFunctionCode : String;
    public
        constructor CreateParam(AOwner : TComponent; FunctionCode : String); virtual;
        procedure   Execute; override;
    end;


    { The RequestBroker maintains a TList with TDispatchObject }
    TDispatchObject = record
        FunctionCode : String;
        Initialized  : Boolean;
        ServerObject : TServerObjectClass;
        Reference    : TServerObject;
    end;
    PDispatchObject = ^TDispatchObject;

    TInstanciationEvent = procedure (Sender : TObject; ServerObject : TServerObject) of object;
    TEnumServerFunctions = function (Sender : TObject; FunctionCode : String) : Boolean of object;

    {:The RequestBroker (ORB) main job is to instanciate objects to satisfy
      client requests, passing to the object the parameters from the request
      and giving the result back to the client when the object has finished.
      A request is made of a function code, a space and some parameters in a
      special format (TMWBuffer).
      The RequestBroker object is linked to the application server object and
      receive client requests from him, brokening those requests and
      dispatching them to server objects for execution. }
    TRequestBroker = class(TComponent)
    protected
        FOptions          : TRequestBrokerOptions;
        FDisplayMemo      : TCustomMemo;
        FObjectCountLabel : TLabel;
        {:List of all TDispatchObject. }
        FObjectList    : TList;
        {:List of all running TServerObject }
        FRunningList   : TList;
        {:Number of instanciated objects. }
        FObjectCount   : Integer;
        {:Just passed to ServerObject instances. }
        FUserData      : LongInt;
        {:Just passed to ServerObject instances. }
        FIniFileName   : String;
        FOnDisplay     : TDisplayEvent;
        {:Triggered when an object has been instanciated. }
        FOnObjCreate   : TInstanciationEvent;
        {:Triggered when an object has been destroyed. }
        FOnObjDestroy  : TInstanciationEvent;
        {:Find a server object by using function code as a key.
          Returns the server object index in the table of object. }
        procedure Notification(AComponent: TComponent; operation: TOperation); override;
        function  FindServerObject(FunctionCode : String) : Integer;
        {:Remove an object from the obejct list. }
        function  RemoveServerObject(FunctionCode : String) : Integer;
        procedure ServerObjectRequestDone(Sender   : TObject);
        {:A client request is constitued of two parts: a function code and
          some parameters. The CrackHeader method is responsible to split both
          parts. By default, it consider the function code to be the first word
          in the data received from the client and the parameter being the
          remaining data after this function code and any trailing spaces.
          You can overrie this method if you like to have a more complex headder
          for example to pass more info from the client to the server. }
        procedure CrackHeader(
            RqBuffer         : PChar;       { Given request buffer       }
            RqLength         : Integer;     { Given request length       }
            Tag              : TObject;     { CliWSocket                 }
            var FunctionCode : String;      { Returned function code     }
            var ParamPtr     : PChar;       { Returned parameters start  }
            var ParamLen     : LongInt      { Returned parameters length }
            ); virtual;
        procedure   TriggerObjCreate(ServerObject : TServerObject); virtual;
        procedure   TriggerObjDestroy(ServerObject : TServerObject); virtual;
        procedure   InternalDisplay(Sender : TObject; Msg : String);
        procedure   Loaded; override;
        function    RemoveRunningObject(ServerObject : TServerObject) : Boolean;
    public
        constructor Create(AOwner : TComponent); override;
        destructor  Destroy; override;
        {:AddServerObject is called from the main application server code, at
          startup to build the request broker object table. This table
          associates objects and request. Each server object has a functions
          code (which default to the server object name without the leading
          TServerObject). Note hat the argument for AddServerObject is an
          object class, not an object instance. }
        procedure   AddServerObject(ServerObjectClass : TServerObjectClass);
        procedure   AddServerObjectWithReference(
                          ServerObjectClass    : TServerObjectClass;
                          ServerObjectInstance : TServerObject);
        {:This method is used to enumerate all server functions. The mains
          purpose is to built some way to display all the server
          functionnalities such as function code list. }
        procedure   EnumServerFunctions(CallBack : TEnumServerFunctions);
        {:BrokeRequest is the ORB main method. This is the method which does
          all the work: creack header, find and instanciate server object,
          execute server object code and send result back to the client. }
        procedure   BrokeRequest(Sender   : TObject;
                                 RqBuffer : PChar;
                                 RqLength : Integer;
                                 Tag      : TObject;
                                 SendResp : TSendResponseToClient);
        {:Number of currently instanciated server objects. }
        property    ObjectCount : Integer           read  FObjectCount;
    published
        {:UserData is not used by the request broker nor the application
          server component. It is there for the application server's writer to
          pass global data between the main application server code and each
          server object, such as TTable of any other data. }
        property UserData    : LongInt              read  FUserData
                                                    write FUserData;
        {:Used to store permanent data. }
        property IniFileName : String               read  FIniFileName
                                                    write FIniFileName;
        property ObjectCountLabel : TLabel          read  FObjectCountLabel
                                                    write FObjectCountLabel;
        property Options : TRequestBrokerOptions    read  FOptions
                                                    write FOptions;
        property DisplayMemo : TCustomMemo          read  FDisplayMemo
                                                    write FDisplayMemo;
        {:Triggered when the component need to display something on the user
          interface such as error or informatinal messages. }
        property OnDisplay   : TDisplayEvent        read  FOnDisplay
                                                    write FOnDisplay;
        {:Triggered when an object has been instanciated. }
        property OnObjCreate  : TInstanciationEvent read  FOnObjCreate
                                                    write FOnObjCreate;
        {:Triggered when an object has been destroyed. }
        property OnObjDestroy : TInstanciationEvent read  FOnObjDestroy
                                                    write FOnObjDestroy;
    end;

procedure Register;

implementation


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure Register;
begin
    RegisterComponents('FPiette', [TRequestBroker, TServerObject]);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
constructor TServerObject.Create(AOwner : TComponent);
begin
    inherited Create(AOwner);
    FResponseSize              := 1024;
    FRequestBuffer             := TMWBuffer.Create(nil);
    FResponseBuffer            := TMWBuffer.Create(nil);
    FResponseBuffer.AutoExpand := 1024;
    FServerObjectClass         := TServerObjectClass(ClassType);
    BuildFunctionCode;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This is just a partial object creation, just enough to get the function   }
{ code created.                                                             }
{ The function code is build from the class name, removing the base class   }
{ name. This behaviour can be overriden in the descendent classes.          }
{$IFNDEF VER110}
constructor TServerObject.CreateForFunctionCode(
    AOwner : TComponent; Dummy : Integer);
begin
    inherited Create(AOwner);
    BuildFunctionCode;
end;
{$ENDIF}


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
destructor TServerObject.Destroy;
begin
    if Assigned(FRequestBuffer) then begin
        FRequestBuffer.Destroy;
        FRequestBuffer := nil;
    end;
    if Assigned(FResponseBuffer) then begin
        FResponseBuffer.Destroy;
        FResponseBuffer := nil;
    end;
    inherited Destroy;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObject.Notification(AComponent: TComponent; operation: TOperation);
begin
    inherited Notification(AComponent, operation);
    if operation = opRemove then begin
        if AComponent = FRequestBroker then
            FRequestBroker := nil;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObject.Loaded;
begin
    inherited Loaded;
    if csDesigning in ComponentState then
        Exit;
    if Assigned(FRequestBroker) and Assigned(FServerObjectClass) then
        FRequestBroker.AddServerObjectWithReference(FServerObjectClass, Self);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObject.CopyFromReference(Reference : TServerObject);
begin
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ Build the function code. The code is based on the classname. For example  }
{ TServerObjectTest will have function code equal to 'TEST'                 }
{ If the classname do not begin by TServerObject, the function code will be }
{ the class name without any leading 'T': TMyObject will gives 'MYOBJECT'.  }
{ This behaviour can be overriden in descendent objects to fit particular   }
{ needs.                                                                    }
procedure TServerObject.BuildFunctionCode;
begin
    FFunctionCode := UpperCase(ClassName);
    if Copy(FFunctionCode, 1, 13) = 'TSERVEROBJECT' then
        FFunctionCode := Copy(FFunctionCode, 14, Length(FFunctionCode))
    else if Copy(FFunctionCode, 1, 5) = 'TSOBJ' then
        FFunctionCode := Copy(FFunctionCode, 6, Length(FFunctionCode))
    else if FFunctionCode[1] = 'T' then
        FFunctionCode := Copy(FFunctionCode, 2, Length(FFunctionCode));
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObject.GiveRequest(RqBuffer : PChar; RqLength : Integer);
begin
    FRequestBuffer.DataBuffer      := RqBuffer;
    FRequestBuffer.DataBufferSize  := RqLength;
    FRequestBuffer.DataBufferCount := RqLength;
    FRequestBuffer.HasData         := TRUE;
    FRequestBuffer.AutoExpand      := 0;          // 06/06/99
    FRequestBuffer.First;
    FResponseBuffer.DataBufferSize := FResponseSize;
    FResponseBuffer.Rewrite;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObject.Initialize;
begin
    { Just nothing to do in the basic object }
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObject.Execute;
begin
    FResponseBuffer.WriteFields(TRUE, ['Base TServerObject called']);
    FResultStatus := 404;
    Finish;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObject.Finish;
begin
//writeln('Finish');
     if Assigned(FOnRequestDone) then
         FOnRequestDone(Self)
     else begin
         Dispose(FORBDataPtr);
         Destroy;
     end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObject.TriggerDisplay(Msg : String);
begin
    try
        if Assigned(FOndisplay) then
            FOnDisplay(Self, Msg);
    except
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
constructor TServerObjectUNKNOWN.CreateParam(AOwner : TComponent; FunctionCode : String);
begin
    inherited Create(AOwner);
    { We need just a small buffer for this demo }
    FResponseSize := 200;
    FFunctionCode := FunctionCode;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObjectUNKNOWN.Execute;
begin
    FResponseBuffer.WriteFields(TRUE, [FFunctionCode, 'Unknown request']);
    FResultStatus := 401;
    Finish;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
constructor TRequestBroker.Create(AOwner : TComponent);
begin
    inherited Create(AOwner);
    FOptions     := [rboDisplayObjectCount];
    FObjectList  := TList.Create;
    FRunningList := TList.Create;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
destructor TRequestBroker.Destroy;
var
    Dispatch : PDispatchObject;
begin
    if Assigned(FObjectList) then begin
        { Free every item in the list }
        while FObjectList.Count > 0 do begin
            Dispatch := FObjectList.Items[0];
            if Dispatch <> nil then
                Dispose(Dispatch);
            FObjectList.Delete(0);
        end;

        { Free the list object }
        FObjectList.Destroy;
        FObjectList := nil;
    end;

    if Assigned(FRunningList) then begin
        { Should we destroy the object still in the list here ? }
        FRunningList.Destroy;
        FRunningList := nil;
    end;

    inherited Destroy;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TRequestBroker.RemoveRunningObject(
    ServerObject : TServerObject) : Boolean;
var
    I : Integer;
begin
    if Assigned(FRunningList) then begin
        for I := 0 to FRunningList.Count - 1 do begin
            if ServerObject = FRunningList.Items[I] then begin
//writeln('Remove TServerObject from running list');
                FRunningList.Delete(I);
                Result := TRUE;
                exit;
            end;
        end;
    end;
    Result := FALSE;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TRequestBroker.Notification(AComponent: TComponent; operation: TOperation);
begin
    inherited Notification(AComponent, operation);
    if operation = opRemove then begin
        if AComponent = FObjectCountLabel then
            FObjectCountLabel := nil
        else if AComponent = FDisplayMemo then
            FDisplayMemo := nil
        else if AComponent is TServerObject then
            RemoveRunningObject(TServerObject(AComponent));
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TRequestBroker.Loaded;
begin
    inherited Loaded;
    if csDesigning in ComponentState then
        Exit;
    if (rboDisplayObjectCount in FOptions) and Assigned(FObjectCountLabel) then
        FObjectCountLabel.Caption := '0';
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TRequestBroker.InternalDisplay(Sender : TObject; Msg : String);
begin
    try
        if Assigned(FDisplayMemo) then
            FDisplayMemo.Lines.Add(Msg);
    except
    end;
    try
        if Assigned(FOnDisplay) then
            FOnDisplay(Sender, Msg);
    except
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ Find a FunctionCode in the FObjectList and return the item index or -1    }
{ if function code not found.                                               }
function TRequestBroker.FindServerObject(FunctionCode : String) : Integer;
var
    Dispatch : PDispatchObject;
begin
    { The list should be sorted to find faster... }
    FunctionCode := UpperCase(Trim(FunctionCode));
    for Result := 0 to FObjectList.Count - 1 do begin
        Dispatch := FObjectList.Items[Result];
        if Dispatch.FunctionCode = FunctionCode then
            Exit;
    end;
    Result := -1;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ Remove a FunctionCode from FObjectList. Return 0 if Ok, -1 if not found   }
function TRequestBroker.RemoveServerObject(FunctionCode : String) : Integer;
var
    Dispatch : PDispatchObject;
begin
    FunctionCode := UpperCase(Trim(FunctionCode));
    Result := FindServerObject(FunctionCode);
    if Result < 0 then
        Exit;

    Dispatch := FObjectList.Items[Result];
    if Dispatch <> nil then
        Dispose(Dispatch);


    FObjectList.Delete(Result);
    Result := 0;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TRequestBroker.AddServerObject(
    ServerObjectClass : TServerObjectClass);
begin
    AddServerObjectWithReference(ServerObjectClass, nil);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TRequestBroker.AddServerObjectWithReference(
    ServerObjectClass    : TServerObjectClass;
    ServerObjectInstance : TServerObject);
var
    Dispatch     : PDispatchObject;
    Item         : Integer;
    FunctionCode : String;
    ServerObject : TServerObject;
begin
    { Create an object instance, just to get the object FunctionCode }
{$IFNDEF VER110}
    { We use another constructor which is faster because it does'nt create }
    { TMWBuffers.                                                          }
    ServerObject := ServerObjectClass.CreateForFunctionCode(Self, 0);
{$ELSE}
    { But C++Builder do not support multiple constructors, so we use the   }
    { normal constructor.                                                  }
    ServerObject := ServerObjectClass.Create(Self);
{$ENDIF}
    ServerObject.FOnDisplay := InternalDisplay;
    FunctionCode := ServerObject.FFunctionCode;
    ServerObject.Destroy;

    Item := FindServerObject(FunctionCode);
    if Item >= 0 then
        { FunctionCode already exist, replace existing }
        Dispatch := FObjectList.Items[Item]
    else begin
        { FunctionCode does'nt exist, create an new item }
        New(Dispatch);
        FObjectList.Add(Dispatch);
        Dispatch.FunctionCode := FunctionCode;
        { I should sort the list to be able to find faster }
    end;

    Dispatch.Initialized  := FALSE;
    Dispatch.ServerObject := ServerObjectClass;
    Dispatch.Reference    := ServerObjectInstance;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TRequestBroker.EnumServerFunctions(CallBack : TEnumServerFunctions);
var
    Item     : Integer;
    Dispatch : PDispatchObject;
begin
    if not Assigned(CallBack) then
        Exit;
    Item := 0;
    while Item < FObjectList.Count do begin
        Dispatch := FObjectList.Items[Item];
        if not CallBack(Self, Dispatch.FunctionCode) then
            break;
        Inc(Item);
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TRequestBroker.TriggerObjCreate(ServerObject : TServerObject);
begin
    if (rboDisplayObjectCount in FOptions) and Assigned(FObjectCountLabel) then
        FObjectCountLabel.Caption := IntToStr(ObjectCount);
    if Assigned(FOnObjCreate) then
        FOnObjCreate(Self, ServerObject);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TRequestBroker.TriggerObjDestroy(ServerObject : TServerObject);
begin
    if (rboDisplayObjectCount in FOptions) and Assigned(FObjectCountLabel) then
        FObjectCountLabel.Caption := IntToStr(ObjectCount - 1);
    if Assigned(FOnObjDestroy) then
         FOnObjDestroy(Self, ServerObject);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TRequestBroker.ServerObjectRequestDone(Sender : TObject);
var
    ServerObject : TServerObject;
    ORBDataPtr   : PORBData;
begin
    ServerObject := Sender as TServerObject;
    TriggerObjDestroy(ServerObject);
    ORBDataPtr := ServerObject.FORBDataPtr;
    if Assigned(ORBDataPtr.SendResp) then begin
        ORBDataPtr.SendResp(ORBDataPtr.Tag,
                            ORBDataPtr.ORB,
                            ServerObject.FResultStatus,
                            ServerObject.FResponseBuffer.DataBuffer,
                            ServerObject.FResponseBuffer.DataBufferCount);
    end;
    Dispose(ORBDataPtr);
    Dec(FObjectCount);
    ServerObject.Free;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ Extract the function code and separate parameters from header             }
procedure TRequestBroker.CrackHeader(
    RqBuffer         : PChar;       { Given request buffer       }
    RqLength         : Integer;     { Given request length       }
    Tag              : TObject;     { CliWSocket                 }
    var FunctionCode : String;      { Returned function code     }
    var ParamPtr     : PChar;       { Returned parameters start  }
    var ParamLen     : LongInt);    { Returned parameters length }
var
    I : LongInt;
begin
    { The first word is the object name }
    I := 0;
    while (I < RqLength) and (RqBuffer[I] <> ' ') do
        Inc(I);
    SetLength(FunctionCode, I);
    Move(RqBuffer^, FunctionCode[1], I);

    { Skip spaces }
    while (I < RqLength) and (RqBuffer[I] = ' ') do
        Inc(I);

    { Parameters follows }
    ParamPtr := RqBuffer + I;
    ParamLen := RqLength - I;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TRequestBroker.BrokeRequest(
    Sender   : TObject;                 { TAppServer }
    RqBuffer : PChar;
    RqLength : Integer;
    Tag      : TObject;                 { CliWSocket }
    SendResp : TSendResponseToClient);
var
    Item         : Integer;
    FunctionCode : String;
    ParamPtr     : PChar;
    ParamLen     : LongInt;
    Dispatch     : PDispatchObject;
    ServerObject : TServerObject;
    ORBDataPtr   : PORBData;
begin
    { Extract the function code and separate parameters from header }
    CrackHeader(RqBuffer, RqLength, Tag,            { Inputs  }
                FunctionCode, ParamPtr, ParamLen);  { Outputs }

    Item := FindServerObject(FunctionCode);
    if Item < 0 then begin
        ServerObject := TServerObjectUNKNOWN.CreateParam(Self, FunctionCode);
        Item         := FRunningList.Add(ServerObject);
        Dispatch     := nil;
    end
    else begin
        Dispatch     := FObjectList.Items[Item];
        ServerObject := Dispatch.ServerObject.Create(Self);
        FRunningList.Add(ServerObject);
        if Assigned(Dispatch.Reference) then
            ServerObject.CopyFromReference(Dispatch.Reference);
    end;

    Inc(FObjectCount);
    TriggerObjCreate(ServerObject);

    try
        New(ORBDataPtr);
        try
            ORBDataPtr.SendResp         := SendResp;
            ORBDataPtr.Tag              := Tag;        { CliWSocket }
            ORBDataPtr.Item             := Item;
            ORBDataPtr.ORB              := Self;
            ORBDataPtr.AppServer        := Sender;

            ServerObject.FOnDisplay     := InternalDisplay;
            ServerObject.FOnRequestDone := ServerObjectRequestDone;
            ServerObject.FORBDataPtr    := ORBDataPtr;
            ServerObject.FResultStatus  := 400;
            ServerObject.FUserData      := FUserData;
            ServerObject.FIniFileName   := FIniFileName;
            ServerObject.GiveRequest(ParamPtr, ParamLen);
            { Call the Initialize procedure if it is the first instanciation }
            if (Dispatch <> nil) and (not Dispatch.Initialized) then begin
                ServerObject.Initialize;
                Dispatch.Initialized := TRUE;
            end;
            ServerObject.Execute;
        except
            Dispose(ORBDataPtr);
            raise;
        end;
    except
        { In case of error, delete the ServerObject instance }
        TriggerObjDestroy(ServerObject);
        ServerObject.Destroy;
        Dec(FObjectCount);
        raise;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}

end.

