{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Author:       François PIETTE
Description:  Helper routines for the MidWare sample client/server demo.
              Those implements very trivial encryption/decryption algorythm.
Creation:     June 07, 1998
Version:      1.00
EMail:        francois.piette@pophost.eunet.be    
              francois.piette@rtfm.be             http://www.rtfm.be/fpiette
Support:      Use the mailing list midware@rtfm.be See website for details.
Legal issues: Copyright (C) 1998 by François PIETTE
              Rue de Grady 24, 4053 Embourg, Belgium. Fax: +32-4-365.74.56
              <francois.piette@pophost.eunet.be>

              This software is provided 'as-is', without any express or
              implied warranty.  In no event will the author be held liable
              for any  damages arising from the use of this software.

              Permission is granted to anyone to use this software and or any
              derived or altered versions for any purpose, excluding commercial
              applications. You can use this software for personal or internal
              use only. You may distribute it freely untouched.
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

{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
unit Cipher;

interface

procedure Encrypt(
    Src         : PChar;
    SrcLen      : Integer;
    var aDst    : PChar;
    var aDstLen : Integer;
    Key         : Integer;
    Offset      : Integer);

procedure Decrypt(
    CmdBuf      : PChar;
    CmdLen      : Integer;
    aDst        : PChar;
    var aDstLen : Integer);
    
implementation


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure Encrypt(
    Src         : PChar;
    SrcLen      : Integer;
    var aDst    : PChar;
    var aDstLen : Integer;
    Key         : Integer;
    Offset      : Integer);
var
    Dst : PChar;
    Cnt : Integer;
    I   : Integer;
begin
    { We need a first pass to know how much bytes must be escaped }
    Cnt := 0;
    for I := 0 to SrcLen - 1 do begin
        if Chr(Ord(Src[I]) xor Key) in [#0, #4, #10, #13] then
            Inc(Cnt);
    end;
    { Allocate memory for the encrypted data }
    GetMem(aDst, SrcLen + Cnt + Cnt + Offset);

    { Encrypt data using the old XOR algorythm                }
    Dst := aDst + Offset;
    Cnt := 0;
    for I := 0 to SrcLen - 1 do begin
        Dst^ := Chr(Ord(Src[I]) xor Key);
        { We must escape some characters because they are used as }
        { delimiters in application server protocol               }
        case Dst^ of
        #0:  begin
                 Dst^ := #4;
                 Inc(Dst);
                 Inc(Cnt);
                 Dst^ := #7;
             end;
        #4:  begin
                 Dst^ := #4;
                 Inc(Dst);
                 Inc(Cnt);
                 Dst^ := #4;
             end;
        #10: begin
                 Dst^ := #4;
                 Inc(Dst);
                 Inc(Cnt);
                 Dst^ := #6;
             end;
        #13: begin
                 Dst^ := #4;
                 Inc(Dst);
                 Inc(Cnt);
                 Dst^ := #5;
             end;
        end;
        Inc(Cnt);
        Inc(Dst);
    end;
    aDstLen := Cnt + Offset;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure Decrypt(
    CmdBuf      : PChar;
    CmdLen      : Integer;
    aDst        : PChar;
    var aDstLen : Integer);
var
    Key : Integer;
    Cnt : Integer;
    Src : PChar;
    Dst : PChar;
begin
    { The server used a trivial encryption algorythm for demo purpose. }
    { You should design a better algorythm...                          }
    { This algorythm is easy because decrypted data is always smaller  }
    { than encrypted. So we don't need to play with memory allocation. }
    { If you need to allocate memory, use OnAfterProcessReply event to }
    { free the allocated memory.                                       }
    Key := Ord(CmdBuf[1]);
    Src := @CmdBuf[2];
    Dst := aDst;
    Cnt := CmdLen - 2;
    while Cnt > 0 do begin
        if Src^ <> #4 then
            Dst^ := Chr(Ord(Src^) xor Key)
        else begin
            Inc(Src);
            Dec(Cnt);
            case Src^ of
            #4 : Dst^ := Chr(4  xor Key);
            #5 : Dst^ := Chr(13 xor Key);
            #6 : Dst^ := Chr(10 xor Key);
            #7 : Dst^ := Chr(0  xor Key);
            end;
        end;
        Inc(Dst);
        Inc(Src);
        Dec(Cnt);
    end;
    aDstLen := Dst - aDst;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}

end.


