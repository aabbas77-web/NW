//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("SrvTst.res");
USEFORM("..\SrvTst1.cpp", ServerForm);
USEUNIT("..\cipher.cpp");
USEUNIT("..\SrvObj1.cpp");
USEUNIT("..\SrvObj2.cpp");
USEUNIT("..\SrvObj3.cpp");
USEUNIT("..\SrvObj4.cpp");
USEUNIT("..\SrvObj5.cpp");
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
