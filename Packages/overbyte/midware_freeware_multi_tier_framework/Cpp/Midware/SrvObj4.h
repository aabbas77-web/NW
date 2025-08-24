//---------------------------------------------------------------------------
#ifndef SrvObj4H
#define SrvObj4H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "RFormat.hpp"
#include "RBroker.hpp"
//---------------------------------------------------------------------------
class TServerObjectGETCLIENTLIKE : public TServerObject
{
public:
    void __fastcall Execute(void);
    __fastcall TServerObjectGETCLIENTLIKE(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
