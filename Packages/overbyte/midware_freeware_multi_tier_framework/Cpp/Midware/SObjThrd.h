//---------------------------------------------------------------------------
#ifndef SObjThrdH
#define SObjThrdH
#include <Classes.hpp>
#include <dbtables.hpp>
#include "RFormat.hpp"
#include "RBroker.hpp"
#define WM_FINISH (WM_USER + 1)
typedef void __fastcall (__closure *TTriggerDisplay)(AnsiString Msg);
//---------------------------------------------------------------------------
class TQueryThread : public TThread
{
protected:
    void __fastcall Execute(void);
public:
    virtual __fastcall TQueryThread(BOOL CreateSuspended);
    AnsiString      DatabaseName;
    AnsiString      AliasName;
    AnsiString      DriverName;
    TStrings        *Params;
    AnsiString      NetFileDir;
    AnsiString      PrivateDir;
    TQuery          *ThQuery;
    TSession        *ThSession;
    TDatabase       *ThDatabase;
    AnsiString      SQLStatement;
    HWND            OwnerHandle;
    int             *ResultStatus;
    TMWBuffer       *ResponseBuffer;
    TTriggerDisplay TriggerDisplay;
protected:
    AnsiString      MessageText;
    void __fastcall DisplayMessage(void);
    void __fastcall Display(AnsiString Msg);
};

//---------------------------------------------------------------------------
class TServerObjectSQLTHREAD : public TServerObject
{
public:
    void __fastcall Execute(void);
    virtual __fastcall TServerObjectSQLTHREAD(TComponent* Owner);
    __fastcall ~TServerObjectSQLTHREAD();
protected:
    TQueryThread  *FWorkerThread;
    AnsiString    FDatabaseName;
    AnsiString    FNetFileDir;
    AnsiString    FPrivateDir;
    AnsiString    FAliasName;
    AnsiString    FDriverName;
    TStrings      *FParams;
    HWND          FWindowHandle;
    void __fastcall CopyFromReference(TServerObject *Reference);
    void __fastcall SetAliasName(AnsiString newValue);
    void __fastcall SetDriverName(AnsiString newValue);
    void __fastcall SetDatabaseName(AnsiString newValue);
    void __fastcall SetParams(TStrings *newValue);
    void __fastcall SetPrivateDir(AnsiString newValue);
    virtual void __fastcall WndProc(Messages::TMessage &MsgRec);
    void __fastcall WMFinish(TMessage &Message);
//    BEGIN_MESSAGE_MAP
//        MESSAGE_HANDLER(WM_FINISH, TMessage, WMFinish)
//    END_MESSAGE_MAP(TServerObject)
__published:
    // You use either AliasName and leave DatabaseName and DriverName blanks
    // Or you use DatabaseName and DriverName, leaving AliasName blank.
    __property AnsiString AliasName    = {read = FAliasName,      write = SetAliasName};
    __property AnsiString DatabaseName = {read = FDatabaseName,   write = SetDatabaseName};
    __property AnsiString DriverName   = {read = FDriverName,     write = SetDriverName};
    // Params must contains the parameters for the database such as user
    // code and password. See Borland help for TDatabase.Params.
    __property TStrings *Params        = {read = FParams,         write = SetParams};
    // NetFileDir is used for Paradox tables. All applications sharing a
    // given paradox table must use the same shared directory
    __property AnsiString NetFileDir   = {read = FNetFileDir,     write = FNetFileDir};
    // Temporary files needed by BDE are stored in this directory
    __property AnsiString PrivateDir   = {read = FPrivateDir,     write = SetPrivateDir};
};
//---------------------------------------------------------------------------
#endif
