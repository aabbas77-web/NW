{*_* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Author:       François PIETTE
Description:  Server Object sample for F. Piette's Middleware (MidWare)
              Show how to use a TQuery and returns the result set.
Creation:     July 01, 1998
Version:      1.00
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


 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
unit SObjSql;

interface

uses
    Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
    RBroker, RFormat, Db, DBTables;

type
    TServerObjectSQL = class(TServerObject)
    protected
        FQuery : TQuery;
        function  GetDatabaseName : String;
        procedure SetDatabaseName(newValue : String);
        procedure CopyFromReference(Reference : TServerObject); override;
    public
        constructor Create(AOwner : TComponent); override;
        Destructor Destroy; override;
        procedure Execute; override;
    published
        property DatabaseName : String read GetDatabaseName write SetDatabaseName;
    end;

procedure Register;

implementation


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure Register;
begin
  RegisterComponents('FPiette', [TServerObjectSQL]);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
constructor TServerObjectSQL.Create(AOwner : TComponent);
begin
    inherited Create(AOwner);
    FQuery := TQuery.Create(Self);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
Destructor TServerObjectSQL.Destroy;
begin
    if Assigned(FQuery) then begin
        FQuery.Free;
        FQuery := nil;
    end;
    inherited Destroy;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObjectSQL.CopyFromReference(Reference : TServerObject);
begin
    inherited CopyFromReference(Reference);
    DatabaseName := TServerObjectSQL(Reference).DatabaseName;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TServerObjectSQL.GetDatabaseName : String;
begin
    if Assigned(FQuery) then
        Result := FQuery.DatabaseName
    else
        Result := '';
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObjectSQL.SetDatabaseName(newValue : String);
begin
    if Assigned(FQuery) then
        FQuery.DatabaseName := Trim(newValue);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObjectSQL.Execute;
var
    Fld          : Integer;
    SQLStatement : String;
begin
    if not Assigned(FQuery) then begin
        FResultStatus := 400;
        FResponseBuffer.Rewrite;
        FResponseBuffer.WriteFields(FALSE, ['No query object at server side']);
        Finish;
        Exit;
    end;

    try
        SQLStatement := FRequestBuffer.Fields[0];
        FQuery.Close;
        FQuery.SQL.Clear;
        FQuery.SQL.Add(SQLStatement);
        FQuery.UniDirectional := TRUE;
        FQuery.Open;
        { Data found }
        FResultStatus := 200;
        { Copy all records from the result set to the response }
        while not FQuery.Eof do begin
            { Copy all fields from the record to the response }
            for Fld := 0 to FQuery.FieldCount - 1 do
                FResponseBuffer.WriteFields(Fld = 0, [FQuery.Fields[Fld]]);
            FQuery.Next;
        end;
        FQuery.Close;
    except
        on E:Exception do begin
            FResultStatus := 400;
            FResponseBuffer.Rewrite;
            FResponseBuffer.WriteFields(FALSE, [E.Message, SQLStatement]);
        end;
    end;

    Finish;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}

end.


