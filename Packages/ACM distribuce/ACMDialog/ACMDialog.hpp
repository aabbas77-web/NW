// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ACMDialog.pas' rev: 6.00

#ifndef ACMDialogHPP
#define ACMDialogHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Dialogs.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <MMSystem.hpp>	// Pascal unit
#include <MSACM.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Acmdialog
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TACMDialog;
class PASCALIMPLEMENTATION TACMDialog : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
public:
	void * __fastcall OpenDialog(void);
public:
	#pragma option push -w-inl
	/* TComponent.Create */ inline __fastcall virtual TACMDialog(Classes::TComponent* AOwner) : Classes::TComponent(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TComponent.Destroy */ inline __fastcall virtual ~TACMDialog(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE Msacm::TACMFORMATCHOOSEA fc;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Acmdialog */
using namespace Acmdialog;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ACMDialog
