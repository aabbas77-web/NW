//---------------------------------------------------------------------------
#ifndef cipherH
#define cipherH
extern void __fastcall Encrypt(
    char *Src, int SrcLen, char **aDst, int *aDstLen, int Key, int Offset);
extern void __fastcall Decrypt(
    char *CmdBuf, int CmdLen, char *aDst, int *aDstLen);
//---------------------------------------------------------------------------
#endif
