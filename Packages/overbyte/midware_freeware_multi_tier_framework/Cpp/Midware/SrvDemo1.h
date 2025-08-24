//---------------------------------------------------------------------------
#ifndef SrvDemo1H
#define SrvDemo1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ApServer.hpp"
#include "RBroker.hpp"
#include "SObjSQL.h"
#include "SObjThrd.h"
#include "SrvObj1.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSrvDemoForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *ToolsPanel;
    TLabel *ClientCountLabel;
    TLabel *ObjectCountLabel;
    TLabel *Label1;
    TLabel *Label2;
    TMemo *DisplayMemo;
    TAppServer *AppServer1;
    TRequestBroker *RequestBroker1;
    TServerObjectSQL *ServerObjectSQL1;
    TServerObjectUPPER *ServerObjectUPPER1;
    TServerObjectSQLTHREAD *ServerObjectSQLTHREAD1;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall RequestBroker1Display(TObject *Sender, AnsiString Msg);
private:	// User declarations
public:		// User declarations
    __fastcall TSrvDemoForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSrvDemoForm *SrvDemoForm;
//---------------------------------------------------------------------------
#endif
