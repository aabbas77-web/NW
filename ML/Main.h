//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>
#include <Menus.hpp>
#include <ActnList.hpp>
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRichEdit *RichEditSource;
	TSplitter *Splitter1;
	TRichEdit *RichEditDest;
	TPanel *Panel2;
	TProgressBar *ProgressBar1;
	TStatusBar *StatusBar1;
	TPanel *Panel3;
	TToolBar *ToolBar1;
	TToolButton *ToolButton1;
	TComboBox *ComboBoxSource;
	TComboBox *ComboBoxDest;
	TPanel *Panel4;
	TPanel *Panel5;
	TCheckBox *CheckBoxRealTime;
	TPopupMenu *PopupMenu;
	TToolButton *ToolButton2;
	TActionList *ActionList1;
	TAction *AAddToDictionary;
	TMenuItem *Addtodictionary1;
	TToolButton *ToolButton3;
	TAction *ATranslate;
	TAction *ADictionary;
	TFormTranslation *FormTranslation1;
	void __fastcall RichEditSourceMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall CheckBoxRealTimeClick(TObject *Sender);
	void __fastcall RichEditSourceMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall AAddToDictionaryExecute(TObject *Sender);
	void __fastcall RichEditSourceMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall ATranslateExecute(TObject *Sender);
	void __fastcall ADictionaryExecute(TObject *Sender);
	void __fastcall RichEditSourceChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);
    POINTL MousePos;
    AnsiString strPrevSelText;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
