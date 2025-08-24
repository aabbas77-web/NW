//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("MwBcb30.res");
USEPACKAGE("VCL35.bpi");
USEUNIT("ApsCli.pas");
USERES("ApsCli.dcr");
USEPACKAGE("VCLDB35.bpi");
USEUNIT("RFormat.pas");
USERES("RFormat.dcr");
USEUNIT("ApServer.pas");
USERES("ApServer.dcr");
USEUNIT("MWDatSet.pas");
USERES("MWDatSet.dcr");
USEUNIT("ApSrvCli.pas");
USERES("ApSrvCli.dcr");
USEUNIT("RBroker.pas");
USERES("RBroker.dcr");
USEPACKAGE("IcsBcb30.bpi");
USEPACKAGE("VCLX35.bpi");
USEUNIT("..\..\cpp\MidWare\SObjSQL.cpp");
USEUNIT("..\..\cpp\MidWare\SrvObj1.cpp");
USEUNIT("..\..\cpp\MidWare\SObjThrd.cpp");
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
