// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'TnOptFrm.pas' rev: 6.00

#ifndef TnOptFrmHPP
#define TnOptFrmHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Buttons.hpp>	// Pascal unit
#include <IniFiles.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Tnoptfrm
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TOptForm;
class PASCALIMPLEMENTATION TOptForm : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TLabel* Label1;
	Stdctrls::TLabel* Label2;
	Stdctrls::TCheckBox* AutoCRCheckBox;
	Stdctrls::TCheckBox* AutoLFCheckBox;
	Stdctrls::TCheckBox* LocalEchoCheckBox;
	Stdctrls::TCheckBox* MonoChromeCheckBox;
	Stdctrls::TEdit* RowsEdit;
	Stdctrls::TEdit* ColsEdit;
	Stdctrls::TButton* OkButton;
	Stdctrls::TButton* CancelButton;
	Stdctrls::TButton* LaboButton;
	Stdctrls::TButton* RDVButton;
	Stdctrls::TButton* USUSButton;
	Stdctrls::TCheckBox* XlatCheckBox;
	Dialogs::TFontDialog* FontDialog1;
	Stdctrls::TButton* FontButton;
	Stdctrls::TEdit* LineHeightEdit;
	Stdctrls::TLabel* Label3;
	Stdctrls::TButton* NamesButton;
	Stdctrls::TCheckBox* UpperLockCheckBox;
	Stdctrls::TButton* A11Button;
	Stdctrls::TGroupBox* GroupBox1;
	Stdctrls::TRadioButton* FKeys1RadioButton;
	Stdctrls::TRadioButton* FKeys2RadioButton;
	Stdctrls::TRadioButton* FKeys3RadioButton;
	Stdctrls::TLabel* Label4;
	Stdctrls::TLabel* Label5;
	Stdctrls::TEdit* LineZoomEdit;
	Stdctrls::TEdit* CharZoomEdit;
	Stdctrls::TCheckBox* GraphicDrawCheckBox;
	void __fastcall OkButtonClick(System::TObject* Sender);
	void __fastcall CancelButtonClick(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall FormClose(System::TObject* Sender, Forms::TCloseAction &Action);
	void __fastcall LaboButtonClick(System::TObject* Sender);
	void __fastcall RDVButtonClick(System::TObject* Sender);
	void __fastcall USUSButtonClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FontButtonClick(System::TObject* Sender);
	void __fastcall NamesButtonClick(System::TObject* Sender);
	void __fastcall A11ButtonClick(System::TObject* Sender);
	
public:
	AnsiString FIniFilename;
	bool FInitialized;
	AnsiString FSectionName;
	AnsiString FKeyName;
	AnsiString FHostName;
	Graphics::TFont* FFont;
	Classes::TNotifyEvent FOnNamesClick;
	bool __fastcall GetLocalEcho(void);
	bool __fastcall GetAutoCr(void);
	bool __fastcall GetAutoLF(void);
	bool __fastcall GetAltKeys(void);
	bool __fastcall GetMonoChrome(void);
	bool __fastcall GetUpperLock(void);
	bool __fastcall GetXlat(void);
	bool __fastcall GetGraphicDraw(void);
	int __fastcall GetRows(void);
	int __fastcall GetCols(void);
	int __fastcall GetLineHeight(void);
	float __fastcall GetLineZoom(void);
	float __fastcall GetCharZoom(void);
	int __fastcall GetFKeys(void);
	void __fastcall SetLocalEcho(bool Value);
	void __fastcall SetAutoCr(bool Value);
	void __fastcall SetAutoLF(bool Value);
	void __fastcall SetAltKeys(bool Value);
	void __fastcall SetMonoChrome(bool Value);
	void __fastcall SetUpperLock(bool Value);
	void __fastcall SetXlat(bool Value);
	void __fastcall SetGraphicDraw(bool Value);
	void __fastcall SetRows(int Value);
	void __fastcall SetCols(int Value);
	void __fastcall SetHostName(AnsiString Value);
	void __fastcall SetLineHeight(int Value);
	void __fastcall SetLineZoom(float Value);
	void __fastcall SetCharZoom(float Value);
	void __fastcall SetFKeys(int Value);
	__property AnsiString IniFilename = {read=FIniFilename, write=FIniFilename};
	__property AnsiString SectionName = {read=FSectionName, write=FSectionName};
	__property AnsiString KeyName = {read=FKeyName, write=FKeyName};
	__property AnsiString HostName = {read=FHostName, write=SetHostName};
	__property bool LocalEcho = {read=GetLocalEcho, write=SetLocalEcho, nodefault};
	__property bool AutoCR = {read=GetAutoCr, write=SetAutoCr, nodefault};
	__property bool AutoLF = {read=GetAutoLF, write=SetAutoLF, nodefault};
	__property bool AltKeys = {read=GetAltKeys, write=SetAltKeys, nodefault};
	__property int FKeys = {read=GetFKeys, write=SetFKeys, nodefault};
	__property bool MonoChrome = {read=GetMonoChrome, write=SetMonoChrome, nodefault};
	__property bool UpperLock = {read=GetUpperLock, write=SetUpperLock, nodefault};
	__property bool Xlat = {read=GetXlat, write=SetXlat, nodefault};
	__property bool GraphicDraw = {read=GetGraphicDraw, write=SetGraphicDraw, nodefault};
	__property int Rows = {read=GetRows, write=SetRows, nodefault};
	__property int Cols = {read=GetCols, write=SetCols, nodefault};
	__property Graphics::TFont* AFont = {read=FFont, write=FFont};
	__property int LineHeight = {read=GetLineHeight, write=SetLineHeight, nodefault};
	__property float LineZoom = {read=GetLineZoom, write=SetLineZoom};
	__property float CharZoom = {read=GetCharZoom, write=SetCharZoom};
	__property Classes::TNotifyEvent OnNamesClick = {read=FOnNamesClick, write=FOnNamesClick};
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TOptForm(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TOptForm(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TOptForm(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TOptForm(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TOptForm* OptForm;

}	/* namespace Tnoptfrm */
using namespace Tnoptfrm;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// TnOptFrm
