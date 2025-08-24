{*_* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Author:       François PIETTE
Description:  Example of multi-threaded server object for F. Piette's
              middleware (MidWare). Execute SQL request in a thread.
Creation:     July 04, 1998
Version:      1.04
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
Jul 08, 1998  V1.02 Adapted to Delphi 4
Jul 21, 1998  V1.03 Use a TDatabase component. Create TSession, TDatabase and
              TQuery from within the thread execute method.
              Added properties for TSession and TDatabase components.
Aug 29, 1998  V1.04 Corrrected CopyFromReference to use Fxxx variables
              and FParams.Assign.


 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
unit SObjThrd;

interface

uses
    Windows, Messages, SysUtils, Classes, Db, DBTables, RBroker, RFormat, Forms,
    FileCtrl;

const
    TServerObjectSQLTHREADVersion = 103;
    WM_FINISH                     = WM_USER + 1;

type
    TTriggerDisplay = procedure (Msg : String) of Object;

    TQueryThread = class(TThread)
    protected
        procedure Execute; override;
    private
        MessageText    : String;
        procedure DisplayMessage;
        procedure Display(Msg : String);
    public
        DatabaseName   : String;
        AliasName      : String;
        DriverName     : String;
        Params         : TStrings;
        NetFileDir     : String;
        PrivateDir     : String;
        ThQuery        : TQuery;
        ThSession      : TSession;
        ThDatabase     : TDatabase;
        SQLStatement   : String;
        OwnerHandle    : Integer;
        ResultStatus   : ^Integer;
        ResponseBuffer : TMWBuffer;
        TriggerDisplay : TTriggerDisplay;
    end;

    TServerObjectSQLTHREAD = class(TServerObject)
    private
        FWorkerThread : TQueryThread;
        FDatabaseName : String;
        FNetFileDir   : String;
        FPrivateDir   : String;
        FAliasName    : String;
        FDriverName   : String;
        FParams       : TStrings;
        FWindowHandle : Integer;
        procedure SetAliasName(newValue : String);
        procedure SetDriverName(newValue : String);
        procedure SetDatabaseName(newValue : String);
        procedure SetParams(newValue : TStrings);
        procedure SetPrivateDir(newValue : String);
        procedure WMFinish(var msg: TMessage); message WM_FINISH;
        procedure WndProc(var MsgRec: TMessage); virtual;
    protected
        procedure CopyFromReference(Reference : TServerObject); override;
    public
        constructor Create(AOwner : TComponent); override;
        destructor  Destroy; override;
        procedure   Execute; override;
    published
        // You use either AliasName and leave DatabaseName and DriverName blanks
        // Or you use DatabaseName and DriverName, leaving AliasName blank.
        property AliasName    : String   read FAliasName    write SetAliasName;
        property DatabaseName : String   read FDatabaseName write SetDatabaseName;
        property DriverName   : String   read FDriverName   write SetDriverName;
        // Params must contains the parameters for the database such as user
        // code and password. See Borland help for TDatabase.Params.
        property Params       : TStrings read FParams       write SetParams;
        // NetFileDir is used for Paradox tables. All applications sharing a
        // given paradox table must use the same shared directory
        property NetFileDir   : String   read FNetFileDir   write FNetFileDir;
        // Temporary files needed by BDE are stored in this directory
        property PrivateDir   : String   read FPrivateDir   write SetPrivateDir;
    end;

procedure Register;

implementation

const
    UniqueNumber : Integer = 0;

{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure Register;
begin
    RegisterComponents('FPiette', [TServerObjectSQLTHREAD]);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TQueryThread.DisplayMessage;
begin
     TriggerDisplay(MessageText);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TQueryThread.Display(Msg : String);
begin
    if (not Terminated) and Assigned(TriggerDisplay) then begin
        MessageText := Msg;
        Synchronize(DisplayMessage);
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TQueryThread.Execute;
var
    Fld          : Integer;
    PrivDir      : String;
    SessName     : String;
begin
    try
        // Thread safe incrementation
        InterlockedIncrement(UniqueNumber);
        // Generate unique session name and private directory
        SessName := 'MWSession' + IntToStr(UniqueNumber);
        PrivDir  := PrivateDir + 'Private\'+ SessName;
        ForceDirectories(PrivDir);
//        Sleep(200);

        try
            ThSession := TSession.Create(nil);
            try
                ThSession.SessionName     := SessName;
                ThSession.NetFileDir      := NetFileDir;
                ThSession.PrivateDir      := PrivDir;

                ThDatabase := TDatabase.Create(ThSession);
                try
                    ThDatabase.SessionName      := ThSession.SessionName;
                    ThDatabase.LoginPrompt      := FALSE;
                    ThDatabase.KeepConnection   := ThSession.KeepConnections;
                    if DatabaseName <> '' then begin
                        ThDatabase.DatabaseName := DatabaseName;
                        ThDatabase.DriverName   := DriverName;
                    end
                    else if AliasName <> '' then begin
                        ThDatabase.AliasName    := AliasName;
                        ThDatabase.DatabaseName := 'MiddlewareDb' + IntToStr(UniqueNumber);
                    end;

                    if Params <> nil then
                        ThDatabase.Params       := Params;
                    Display(IntToHex(ThreadID, 8) + ' Open Database');
                    ThDatabase.Open;

                    ThQuery := TQuery.Create(nil);
                    try
                        ThQuery.SessionName   := ThSession.SessionName;
                        ThQuery.DatabaseName  := ThDatabase.DatabaseName;
                        ThQuery.SQL.Clear;
                        ThQuery.SQL.Add(SQLStatement);

                        { Open the query }
                        Display(IntToHex(ThreadID, 8) + ' Query.Open');
                        ThQuery.Open;
                        Display(IntToHex(ThreadID, 8) + ' Query.Opened');
                        { Data found }
                        ResultStatus^ := 200;
                        { Copy all records from the result set to the response }
                        while (not Terminated) and (not ThQuery.Eof) do begin
                            { Copy all fields from the record to the response }
                            for Fld := 0 to ThQuery.FieldCount - 1 do
                                ResponseBuffer.WriteFields(Fld = 0, [ThQuery.Fields[Fld]]);
                            ThQuery.Next;
                        end;
                        ThQuery.Close;
                        ThDatabase.Close;
                        ThSession.Close;
                        if Terminated then begin
                            ResultStatus^ := 401;
                            ResponseBuffer.WriteFields(FALSE, ['Thread has been terminated']);
                            Exit;
                        end;
                    finally
                        ThQuery.Free;
                        ThQuery := nil;
                    end;
                finally
                    ThDatabase.Free;
                    ThDatabase := nil;
                end;
            finally
                ThSession.Free;
                ThSession := nil;
            end;
        finally
            RemoveDir(PrivDir);
        end;
    except
        on E: Exception do begin
            ResultStatus^ := 400;
            ResponseBuffer.WriteFields(FALSE, [E.ClassName + ':' + E.Message]);
        end;
    end;
    PostMessage(OwnerHandle, WM_FINISH, 0, 0);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
constructor TServerObjectSQLTHREAD.Create(AOwner : TComponent);
begin
    inherited Create(AOwner);
    FParams       := TStringList.Create;
    FWindowHandle := AllocateHWnd(WndProc);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
destructor TServerObjectSQLTHREAD.Destroy;
begin
    if Assigned(FParams) then begin
        FParams.Destroy;
        FParams := nil;
    end;
    if FWindowHandle <> 0 then begin
        DeallocateHWnd(FWindowHandle);
        FWindowHandle := 0;
    end;
    inherited Destroy;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObjectSQLTHREAD.CopyFromReference(Reference : TServerObject);
begin
    inherited CopyFromReference(Reference);
    FDatabaseName := TServerObjectSQLTHREAD(Reference).DatabaseName;
    FDriverName   := TServerObjectSQLTHREAD(Reference).DriverName;
    FAliasName    := TServerObjectSQLTHREAD(Reference).AliasName;
    FNetFileDir   := TServerObjectSQLTHREAD(Reference).NetFileDir;
    FPrivateDir   := TServerObjectSQLTHREAD(Reference).PrivateDir;
    FParams.Assign(TServerObjectSQLTHREAD(Reference).Params);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObjectSQLTHREAD.SetAliasName(newValue : String);
begin
    FAliasName    := newValue;
    FDriverName   := '';
    FDatabaseName := '';
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObjectSQLTHREAD.SetDriverName(newValue : String);
begin
    FDriverName := newValue;
    FAliasName  := '';
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObjectSQLTHREAD.SetPrivateDir(newValue : String);
begin
    FPrivateDir := newValue;
    if (Length(FPrivateDir) > 0) and
       (FPrivateDir[Length(FPrivateDir)] <> '\') then
            FPrivateDir := FPrivateDir + '\';
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObjectSQLTHREAD.SetDatabaseName(newValue : String);
begin
    FDatabaseName := newValue;
    FAliasName    := '';
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObjectSQLTHREAD.SetParams(newValue : TStrings);
begin
    FParams.Assign(newValue)
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObjectSQLTHREAD.Execute;
begin
    FWorkerThread                 := TQueryThread.Create(TRUE);
    FWorkerThread.TriggerDisplay  := TriggerDisplay;
    FWorkerThread.ResponseBuffer  := FResponseBuffer;
    FWorkerThread.ResultStatus    := @FResultStatus;
    FWorkerThread.AliasName       := FAliasName;
    FWorkerThread.DatabaseName    := FDatabaseName;
    FWorkerThread.DriverName      := FDriverName;
    FWorkerThread.Params          := FParams;
    FWorkerThread.NetFileDir      := FNetFileDir;
    FWorkerThread.PrivateDir      := FPrivateDir;
    FWorkerThread.SQLStatement    := FRequestBuffer.Fields[0];
    FWorkerThread.OwnerHandle     := FWindowHandle;
    FWorkerThread.FreeOnTerminate := TRUE;
    FWorkerThread.Resume;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObjectSQLTHREAD.WMFinish(var msg: TMessage);
begin
    Finish;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObjectSQLTHREAD.WndProc(var MsgRec: TMessage);
begin
     with MsgRec do begin
         if Msg = WM_FINISH then
             WMFinish(MsgRec)
         else
             Result := DefWindowProc(FWindowHandle, Msg, wParam, lParam);
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}

end.


