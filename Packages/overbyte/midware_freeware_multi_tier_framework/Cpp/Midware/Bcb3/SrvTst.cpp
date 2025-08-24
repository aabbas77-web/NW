//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("SrvTst.res");
USEUNIT("..\SrvObj5.cpp");
USEUNIT("..\SrvObj2.cpp");
USEUNIT("..\SrvObj3.cpp");
USEUNIT("..\SrvObj4.cpp");
USEUNIT("..\SrvObj1.cpp");
USEUNIT("..\cipher.cpp");
USEFORM("SrvTst1.cpp", ServerForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TServerForm), &ServerForm);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
