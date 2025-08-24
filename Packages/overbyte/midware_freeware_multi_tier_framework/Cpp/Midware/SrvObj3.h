//---------------------------------------------------------------------------
#ifndef SrvObj3H
#define SrvObj3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "RFormat.hpp"
#include "RBroker.hpp"
//---------------------------------------------------------------------------
class TServerObjectGETCLIENT : public TServerObject
{
public:
    void __fastcall Execute(void);
    __fastcall TServerObjectGETCLIENT(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
