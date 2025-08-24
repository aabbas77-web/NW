//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("SvrDemo.res");
USEFORM("..\SrvDemo1.cpp", SrvDemoForm);
USEUNIT("..\SObjSQL.cpp");
USEUNIT("..\SrvObj1.cpp");
USEUNIT("..\SObjThrd.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TSrvDemoForm), &SrvDemoForm);
                 Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
