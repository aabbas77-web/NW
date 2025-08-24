//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("MwBcb50.res");
USEUNIT("RFormat.pas");
USERES("RFormat.dcr");
USEUNIT("RBroker.pas");
USERES("RBroker.dcr");
USEUNIT("ApSrvCli.pas");
USERES("ApSrvCli.dcr");
USEUNIT("ApServer.pas");
USERES("ApServer.dcr");
USEUNIT("ApsCli.pas");
USERES("ApsCli.dcr");
USEUNIT("MWDatSet.pas");
USERES("MWDatSet.dcr");
USEFORMNS("LOPropIm.pas", Lopropim, ImportForm);
USEFORMNS("LOProp.pas", Loprop, LayoutEditForm);
USEUNIT("..\..\cpp\MidWare\SObjSQL.cpp");
USEUNIT("..\..\cpp\MidWare\SObjThrd.cpp");
USEUNIT("..\..\cpp\MidWare\SrvObj5.cpp");
USEUNIT("..\..\cpp\MidWare\SrvObj2.cpp");
USEUNIT("..\..\cpp\MidWare\SrvObj3.cpp");
USEUNIT("..\..\cpp\MidWare\SrvObj4.cpp");
USEUNIT("..\..\cpp\MidWare\SrvObj1.cpp");
USEPACKAGE("vcl50.bpi");
USEPACKAGE("vcldb50.bpi");
USEPACKAGE("vclbde50.bpi");
USEPACKAGE("vclx50.bpi");
USEPACKAGE("IcsBcb50.bpi");
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
