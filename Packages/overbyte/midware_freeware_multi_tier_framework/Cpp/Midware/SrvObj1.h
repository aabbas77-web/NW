//---------------------------------------------------------------------------
#ifndef SrvObj1H
#define SrvObj1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "RFormat.hpp"
#include "RBroker.hpp"
//---------------------------------------------------------------------------
class TServerObjectUPPER : public TServerObject
{
public:
    void __fastcall Initialize(void);
    void __fastcall Execute(void);
    __fastcall TServerObjectUPPER(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
