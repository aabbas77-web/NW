//---------------------------------------------------------------------------
#ifndef SObjSQLH
#define SObjSQLH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <dbtables.hpp>
#include "RFormat.hpp"
#include "RBroker.hpp"
//---------------------------------------------------------------------------
class TServerObjectSQL : public TServerObject
{
public:
    void __fastcall Execute(void);
    virtual __fastcall TServerObjectSQL(TComponent* Owner);
    __fastcall ~TServerObjectSQL();
protected:
    TQuery *FQuery;
    AnsiString __fastcall GetDatabaseName(void);
    void __fastcall SetDatabaseName(AnsiString newValue);
    void __fastcall CopyFromReference(TServerObject *Reference);
__published:
    __property AnsiString DatabaseName = {read = GetDatabaseName, write = SetDatabaseName};
};
//---------------------------------------------------------------------------
#endif
