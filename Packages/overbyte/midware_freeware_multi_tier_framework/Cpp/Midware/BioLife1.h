//---------------------------------------------------------------------------
#ifndef BioLife1H
#define BioLife1H
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
#include <ExtCtrls.hpp>
#include "MwDatSet.hpp"
#include <DB.hpp>
//---------------------------------------------------------------------------
class TBioLifeForm : public TForm
{
__published:	// IDE-managed Components
    TSplitter *Splitter1;
    TPanel *Panel1;
    TDBNavigator *DBNavigator1;
    TButton *RequestButton;
    TPanel *LeftPanel;
    TDBMemo *DBMemo1;
    TPanel *Panel4;
    TDBText *DBText1;
    TPanel *RightPanel;
    TDBImage *DBImage1;
    TPanel *Panel2;
    TLabel *Label1;
    TEdit *WhereEdit;
    TStatusBar *StatusBar1;
    TAppSrvClient *AppSrvClient1;
    TMWTable *MWTable1;
    TStringField *MWTable1COMMONNAME;
    TMemoField *MWTable1NOTES;
    TGraphicField *MWTable1GRAPHIC;
    TMWBuffer *MWBuffer1;
    TDataSource *DataSource1;
    void __fastcall RequestButtonClick(TObject *Sender);
    void __fastcall MWTable1RequestDone(TObject *Sender, int Error);
private:	// User declarations
public:		// User declarations
    __fastcall TBioLifeForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBioLifeForm *BioLifeForm;
//---------------------------------------------------------------------------
#endif
