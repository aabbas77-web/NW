//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("ChatCli.res");
USEFORM("..\ChatCli1.cpp", ChatClientForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TChatClientForm), &ChatClientForm);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
