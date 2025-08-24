//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("CliTst.res");
USEFORM("..\CliTst1.cpp", TestClientForm);
USEUNIT("..\cipher.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TTestClientForm), &TestClientForm);
                 Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
