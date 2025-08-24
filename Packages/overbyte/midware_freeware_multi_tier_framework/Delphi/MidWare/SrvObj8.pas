{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Author:       François PIETTE
Description:  Server Object sample
              Show how to store a file sent by the client.
Creation:     Aug 14, 1998
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
unit SrvObj8;

interface

uses
    SysUtils, Classes, RBroker, RFormat, SrvTst2, DB;

const
    VersionServerObjectSENDFILE = 100;

type
    TSObjSENDFILE = class(TServerObject)
    public
        procedure Execute; override;
    end;

implementation

{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TSObjSENDFILE.Execute;
var
    FileName : String;
    Data     : TFileStream;
    FldType  : TMWFieldType;
    DataSize : Integer;
begin
    try
        FileName := FRequestBuffer.Fields[0];
        Data     := TFileStream.Create(FileName, fmCreate);
        try
            FRequestBuffer.GetStreamField(1, Data, FldType);
            DataSize := Data.Size;
        finally
            Data.Destroy;
        end;
        FResultStatus := 200;
        FResponseBuffer.WriteFields(TRUE, [FileName, 'File saved',
                                           DataSize, 'bytes stored']);
    except
        on E:Exception do begin
            FResultStatus := 400;
            FResponseBuffer.Rewrite;
            FResponseBuffer.WriteFields(FALSE, ['Exception', E.Message]);
        end;
    end;

    Finish;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}

end.

