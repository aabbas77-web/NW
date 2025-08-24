//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("ChatSrv.res");
USEFORM("..\ChatSrv1.cpp", ChatSrvForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TChatSrvForm), &ChatSrvForm);
                 Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
