//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("BioLife.res");
USEFORM("..\BioLife1.cpp", BioLifeForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TBioLifeForm), &BioLifeForm);
                 Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
