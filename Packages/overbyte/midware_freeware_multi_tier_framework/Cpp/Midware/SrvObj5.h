//---------------------------------------------------------------------------
#ifndef SrvObj5H
#define SrvObj5H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "RFormat.hpp"
#include "RBroker.hpp"
//---------------------------------------------------------------------------
class TServerObjectGETFILE : public TServerObject
{
public:
    void __fastcall Execute(void);
    __fastcall TServerObjectGETFILE(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
