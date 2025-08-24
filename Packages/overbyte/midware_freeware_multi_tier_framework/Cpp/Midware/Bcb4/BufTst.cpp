//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("BufTst.res");
USEFORM("..\BufTst1.cpp", BufTstForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TBufTstForm), &BufTstForm);
                 Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
