{*_* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Author:       François PIETTE
Description:  Example of very basic server object.
              Just returns the input fields converted to uppercase.
              Part of the SrvTst sample application server.
Creation:     February 26, 1998
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
unit SrvObj1;

interface

uses
    SysUtils, Classes, RBroker, RFormat;

type
    TServerObjectUPPER = class(TServerObject)
    public
        procedure   Initialize; override;
        procedure   Execute; override;
    end;

procedure Register;

implementation

{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure Register;
begin
    RegisterComponents('FPiette', [TServerObjectUPPER]);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObjectUPPER.Initialize;
begin
    { Just for demo purpose }
    TriggerDisplay(FFunctionCode + ' is initializing');
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObjectUPPER.Execute;
var
    I    : Integer;
    Data : TMemoryStream;
    Buf  : String;
begin
    { Uncomment the next line to test exceptions behaviour.           }
    { raise Exception.Create('Test failed' + #13#10 + 'Second line'); }

    { The RequestBuffer is positionned on first record on startup }
    while not FRequestBuffer.Eof do begin
        for I := 0 to FRequestBuffer.FieldCount - 1 do
            FResponseBuffer.WriteFields(I = 0,
                                        [UpperCase(FRequestBuffer.Fields[I])]);
        FRequestBuffer.Next;
    end;

    { Demo for stream data field which can send anything ! }
    Data := TMemoryStream.Create;
    Buf := 'A CR/LF pair embeded here after' + #13 + #10 + 'the CR/LF before';
    Data.WriteBuffer(Buf[1], Length(Buf));
    Data.Seek(0, 0);
    FResponseBuffer.WriteStreamField(TRUE, mwString, Data);
    Data.Destroy;

    { Write one more ordinary fields }
    FResponseBuffer.WriteFields(FALSE, ['One more field', 'and another']);

    FResultStatus := 200;
    Finish;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}

end.

