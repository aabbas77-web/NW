//---------------------------------------------------------------------------
#ifndef SrvObj2H
#define SrvObj2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "RFormat.hpp"
#include "RBroker.hpp"
//---------------------------------------------------------------------------
class TLengthyThread : public TThread
{
public:
    TMWBuffer *FResponseBuffer;
    void __fastcall Execute(void);
    __fastcall TLengthyThread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
class TServerObjectTHREAD : public TServerObject
{
private:
    TLengthyThread  *FWorkerThread;
    void __fastcall ThreadJobDone(TObject *Sender);
public:
    void __fastcall Execute(void);
    __fastcall TServerObjectTHREAD(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
