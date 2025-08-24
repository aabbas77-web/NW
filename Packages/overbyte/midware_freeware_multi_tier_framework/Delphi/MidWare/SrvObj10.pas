{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Author:       François PIETTE
Description:  Server Object sample.
              Show how to use CgiGate and IsaGate gateway interface between
              a webserver and a application server.
              This demo just get all infos from webserver, format it as HTML
              and return it as result. In a real program, you use the infos
              to fetch some data and do some processing to produce HTML
              result.
              CgiGate or IsaGate send info as follow:
              Record 1:
                  Two fields with major and minor version number
                  A field with program name.
              Record 2:
                  A single field containing all data from web page
              Record 3:
                  A single field with Cgi/IsaGate executable
              Record 4:
                  Complete environment string for CgiGate or variables for
                  IsaGate. Each field has the form NAME=VALUE.
              The server objet must produce valid output for webserver. Each
              record in result set will be transformed to a line to form the
              answer for the webserver. Each field is concatenated and a CR/LF
              is appended at the end of the record, except last record.
Creation:     April 25, 1999
Version:      1.00
EMail:        francois.piette@overbyte.be   francois.piette@rtfm.be
              http://www.overbyte.be        http://www.rtfm.be/fpiette
              francois.piette@pophost.eunet.be
Support:      Use the mailing list midware@elists.org
              Follow "support" link at http://www.overbyte.be for subscription.
Legal issues: Copyright (C) 1997-2001 by François PIETTE
              Rue de Grady 24, 4053 Embourg, Belgium. Fax: +32-4-365.74.56
              <francois.piette@overbyte.be> <francois.piette@pophost.eunet.be>

              This software is provided 'as-is', without any express or
              implied warranty. In no event will the author be held liable
              for any damages arising from the use of this software.

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
unit SrvObj10;

interface

uses
    SysUtils, Classes, RBroker, RFormat;

type
    TSObjCgiIsaGate = class(TServerObject)
    public
        procedure   Execute; override;
    end;
    TSObjIsaGate = class(TSObjCgiIsaGate)
    end;
    TSObjCgiGate = class(TSObjCgiIsaGate)
    end;

procedure Register;

implementation

{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure Register;
begin
    RegisterComponents('FPiette', [TSObjCgiGate, TSObjIsaGate]);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TSObjCgiIsaGate.Execute;
var
    ExeName  : String;
    DataIn   : String;
    Version  : String;
    EnvVar   : String;
    Fld      : Integer;
begin
    Version  := FRequestBuffer.Fields[2] + ' V' +
                FRequestBuffer.Fields[0] + '.' + FRequestBuffer.Fields[1];
    FRequestBuffer.Next;
    DataIn   := FRequestBuffer.Fields[0];
    FRequestBuffer.Next;
    ExeName  := FRequestBuffer.Fields[0];
    FRequestBuffer.Next;

    FResultStatus := 200;
    FResponseBuffer.Rewrite;
    FResponseBuffer.WriteFields(FALSE, [
        'Content-type: text/html' + #13#10#13#10 +
        '<HTML>' + #13#10 +
        '<HEAD>' + #13#10 +
        '<TITLE>Cgi/Isa Gateway Result</TITLE>' + #13#10 +
        '</HEAD>' + #13#10 +
        '<BODY>' + #13#10 +
        '<H3>Version:</H3>' + #13#10 +
        Version + '<BR><BR>' + #13#10 +
        '<H3>DataIn:</H3>' + #13#10 +
        DataIn + '<BR><BR>' + #13#10 +
        '<H3>ExeName:</H3>' + #13#10 +
        ExeName + '<BR><BR>' + #13#10 +
        '<H3>Environment:</H3>' + #13#10]);
    Fld := 0;
    while TRUE do begin
        EnvVar := FRequestBuffer.Fields[Fld];
        if Length(EnvVar) = 0 then
            break;
        FResponseBuffer.WriteFields(FALSE, [EnvVar, '<BR>']);
        Inc(Fld);
    end;

    FResponseBuffer.WriteFields(FALSE, [
        '</BODY>' + #13#10 +
        '</HTML>']);

    Finish;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}

end.

