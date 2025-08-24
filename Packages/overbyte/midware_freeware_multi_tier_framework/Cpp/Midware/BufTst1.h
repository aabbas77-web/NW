//---------------------------------------------------------------------------
#ifndef BufTst1H
#define BufTst1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MWDatSet.hpp"
#include "RFormat.hpp"
#include <Db.hpp>
#include <DBGrids.hpp>
#include <DBTables.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "MwDatSet.hpp"
#include <DB.hpp>
//---------------------------------------------------------------------------
class TBufTstForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TLabel *Label1;
    TButton *PriorButton;
    TButton *NextButton;
    TCheckBox *EofCheckBox;
    TCheckBox *BofCheckBox;
    TButton *FirstButton;
    TButton *LastButton;
    TButton *DeleteButton;
    TButton *CreateButton;
    TMemo *Memo1;
    TDBGrid *DBGrid1;
    TTable *Table1;
    TMWBuffer *MWBuffer1;
    TDataSource *DataSource1;
    TMWTable *MWTable1;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall PriorButtonClick(TObject *Sender);
    void __fastcall NextButtonClick(TObject *Sender);
    void __fastcall FirstButtonClick(TObject *Sender);
    void __fastcall LastButtonClick(TObject *Sender);
    void __fastcall DeleteButtonClick(TObject *Sender);
    void __fastcall CreateButtonClick(TObject *Sender);
private:	// User declarations
    bool         FInitialized;
#ifdef TABLE
    TTable       *FData;
#else
    TMWBuffer    *FData;
#endif
    int          FSize;
    char         *FBuffer;
    void __fastcall CreateData(void);
    void __fastcall DisplayData(void);
    void __fastcall ShowCurrent(void);
    AnsiString __fastcall Field(int nIndex);
    AnsiString __fastcall Info(void);
public:		// User declarations
    __fastcall TBufTstForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBufTstForm *BufTstForm;
//---------------------------------------------------------------------------
#endif
