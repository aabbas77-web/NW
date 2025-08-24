//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("MwBcb40.res");
USEPACKAGE("vcl40.bpi");
USEUNIT("RFormat.pas");
USERES("RFormat.dcr");
USEPACKAGE("VCLDB40.bpi");
USEUNIT("RBroker.pas");
USERES("RBroker.dcr");
USEUNIT("ApSrvCli.pas");
USERES("ApSrvCli.dcr");
USEUNIT("ApServer.pas");
USERES("ApServer.dcr");
USEUNIT("ApsCli.pas");
USERES("ApsCli.dcr");
USEPACKAGE("Icsbcb40.bpi");
USEUNIT("MWDatSet.pas");
USERES("MWDatSet.dcr");
USEFORMNS("LOPropIm.pas", Lopropim, ImportForm);
USEFORMNS("LOProp.pas", Loprop, LayoutEditForm);
USEUNIT("..\..\cpp\MidWare\SObjSQL.cpp");
USEUNIT("..\..\cpp\MidWare\SObjThrd.cpp");
USEPACKAGE("VCLX40.bpi");
USEUNIT("..\..\cpp\MidWare\SrvObj5.cpp");
USEUNIT("..\..\cpp\MidWare\SrvObj2.cpp");
USEUNIT("..\..\cpp\MidWare\SrvObj3.cpp");
USEUNIT("..\..\cpp\MidWare\SrvObj4.cpp");
USEUNIT("..\..\cpp\MidWare\SrvObj1.cpp");
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//   Package source.
//---------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
        return 1;
}
//---------------------------------------------------------------------------
