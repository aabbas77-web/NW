//---------------------------------------------------------------------------
#ifndef TblTst1H
#define TblTst1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ApsCli.hpp"
#include "MWDatSet.hpp"
#include "RFormat.hpp"
#include <ComCtrls.hpp>
#include <Db.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "MwDatSet.hpp"
#include <DB.hpp>
//---------------------------------------------------------------------------
class TTblTstForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TDBNavigator *DBNavigator1;
    TEdit *KeyEdit;
    TButton *RequestButton;
    TButton *Button1;
    TDBGrid *DBGrid1;
    TStatusBar *StatusBar1;
    TMWBuffer *MWBuffer1;
    TMWTable *MWTable1;
    TDataSource *DataSource1;
    TAppSrvClient *AppSrvClient1;
    void __fastcall RequestButtonClick(TObject *Sender);
    void __fastcall AppSrvClient1RequestDone(TObject *Sender, int Error);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall AppSrvClient1SessionConnected(TObject *Sender,
          WORD Error);
    void __fastcall AppSrvClient1SessionClosed(TObject *Sender,
          WORD Error);
private:	// User declarations
public:		// User declarations
    __fastcall TTblTstForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTblTstForm *TblTstForm;
//---------------------------------------------------------------------------
#endif
