//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("BuilderXPk5.res");
USEPACKAGE("vcl50.bpi");
USEUNIT("DirectX.pas");
USERES("DirectX.dcr");
USEUNIT("DXClass.pas");
USEUNIT("DXConsts.pas");
USEUNIT("DXReg.pas");
USEUNIT("DXSounds.pas");
USEUNIT("DXWaveEdit.pas");
USEUNIT("Wave.pas");
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Package source.
//---------------------------------------------------------------------------

#pragma argsused
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
	return 1;
}
//---------------------------------------------------------------------------
