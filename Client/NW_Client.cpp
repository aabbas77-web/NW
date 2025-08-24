//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("DataModule.cpp", DM); /* TDataModule: File Type */
USEFORM("Main.cpp", FormMain);
USEFORM("ClientProcess.cpp", DMClient); /* TDataModule: File Type */
USEFORM("..\Lib\Input.cpp", FormInput);
USEFORM("..\Lib\TempExplorer.cpp", FormTempExplorer);
USEFORM("..\Lib\CopyDialog.cpp", FormCopyDialog);
USEFORM("..\Lib\FullScreen.cpp", FormFullScreen);
USEFORM("..\Lib\About.cpp", FormAbout);
USEFORM("Watch.cpp", FormWatch);
USEFORM("..\Lib\Splash.cpp", FormSplash);
USEFORM("Options.cpp", FormOptions);
USEFORM("..\Lib\nw_Messages.cpp", FormMessages);
USEFORM("..\Lib\nw_Message.cpp", FormMessage);
USEFORM("..\Lib\nw_SelectClient.cpp", FormSelectClient);
//---------------------------------------------------------------------------
//#include "Splash.h"
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
//    	FormSplash = new TFormSplash(Application);
//        FormSplash->Show();
//        FormSplash->Update();

		Application->Initialize();
		Application->CreateForm(__classid(TDMClient), &DMClient);
		Application->CreateForm(__classid(TDM), &DM);
		Application->CreateForm(__classid(TFormMain), &FormMain);
		Application->CreateForm(__classid(TFormMessages), &FormMessages);
		Application->CreateForm(__classid(TFormInput), &FormInput);
		Application->CreateForm(__classid(TFormTempExplorer), &FormTempExplorer);
		Application->CreateForm(__classid(TFormCopyDialog), &FormCopyDialog);
		Application->CreateForm(__classid(TFormFullScreen), &FormFullScreen);
		Application->CreateForm(__classid(TFormAbout), &FormAbout);
		Application->CreateForm(__classid(TFormWatch), &FormWatch);
		Application->CreateForm(__classid(TFormOptions), &FormOptions);
		Application->CreateForm(__classid(TFormMessage), &FormMessage);
		Application->CreateForm(__classid(TFormSelectClient), &FormSelectClient);
//		if(FormSplash)
//        {
//        	FormSplash->Close();
//         	delete FormSplash;
//            FormSplash = NULL;
//        }

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

