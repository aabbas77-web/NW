/*---------------------------------------------------------------------------

Author:       François PIETTE
Description:  Helper routines for the MidWare sample client/server demo.
              Those implements very trivial encryption/decryption algorythm.
Creation:     June 21, 1998 (from Delphi version created June 07, 1998)
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

---------------------------------------------------------------------------*/
#include <stdlib.h>
#include <vcl.h>
#pragma hdrstop

#include "cipher.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
void __fastcall Encrypt(
    char *Src, int SrcLen, char **aDst, int *aDstLen, int Key, int Offset)
{
    char *Dst;
    int  Cnt;
    int  I;

    // We need a first pass to know how much bytes must be escaped
    Cnt = 0;
    for (I = 0; I < SrcLen; I++) {
        switch (Src[I] ^ Key) {
        case 0:
        case 4:
        case 10:
        case 13:
            Cnt++;
            break;
        }
    }
    // Allocate memory for the encrypted data
    *aDst = (char *)malloc(SrcLen + Cnt + Cnt + Offset);

    // Encrypt data using the old XOR algorythm
    Dst = *aDst + Offset;
    Cnt = 0;
    for (I = 0; I < SrcLen; I++) {
        *Dst = (char)(Src[I] ^ Key);
        // We must escape some characters because they are used as
        // delimiters in MidWare protocol
        switch (*Dst) {
        case 0:  *Dst++ = 4; Cnt++; *Dst = 7; break;
        case 4:  *Dst++ = 4; Cnt++; *Dst = 4; break;
        case 10: *Dst++ = 4; Cnt++; *Dst = 6; break;
        case 13: *Dst++ = 4; Cnt++; *Dst = 5; break;
        }
        Cnt++;
        Dst++;
    }
    *aDstLen = Cnt + Offset;
}
//---------------------------------------------------------------------------
void __fastcall Decrypt(
    char *CmdBuf, int CmdLen, char *aDst, int *aDstLen)
{
    int  Key;
    int  Cnt;
    char *Src;
    char *Dst;

    // The server used a trivial encryption algorythm for demo purpose.
    // You should design a better algorythm...
    // This algorythm is easy because decrypted data is always smaller
    // than encrypted. So we don't need to play with memory allocation.
    // If you need to allocate memory, use OnAfterProcessReply event to
    // free the allocated memory.
    Key = CmdBuf[1];
    Src = &CmdBuf[2];
    Dst = aDst;
    Cnt = CmdLen - 2;
    while (Cnt > 0) {
        if (*Src != 4)
            *Dst = (char)(*Src ^ Key);
        else {
            Src++;
            Cnt--;
            switch (*Src) {
            case 4 : *Dst = (char)(4  ^ Key); break;
            case 5 : *Dst = (char)(13 ^ Key); break;
            case 6 : *Dst = (char)(10 ^ Key); break;
            case 7 : *Dst = (char)(0  ^ Key); break;
            }
        }
        Dst++;
        Src++;
        Cnt--;
    }
    *aDstLen = Dst - aDst;
}
//---------------------------------------------------------------------------

