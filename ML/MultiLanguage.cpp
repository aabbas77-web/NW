//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Main.cpp", FormMain);
USEFORM("Splash.cpp", FormSplash);
USEFORM("AddNewPhrase.cpp", FormAddNewPhrase);
USEFORM("Lib\ML_DataModule.cpp", DM_ML); /* TDataModule: File Type */
USEFORM("Dictionary.cpp", FormDictionary);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TDM_ML), &DM_ML);
		Application->CreateForm(__classid(TFormMain), &FormMain);
		Application->CreateForm(__classid(TFormAddNewPhrase), &FormAddNewPhrase);
		Application->CreateForm(__classid(TFormDictionary), &FormDictionary);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
