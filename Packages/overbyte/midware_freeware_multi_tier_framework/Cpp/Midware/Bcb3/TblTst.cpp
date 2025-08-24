//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("TblTst.res");
USEFORM("..\TblTst1.cpp", TblTstForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TTblTstForm), &TblTstForm);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
