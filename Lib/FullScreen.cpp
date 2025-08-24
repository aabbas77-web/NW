//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FullScreen.h"
#include "ClientProcess.h"
#include "DataModule.h"
#include "Watch.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormFullScreen *FormFullScreen;
//---------------------------------------------------------------------------
__fastcall TFormFullScreen::TFormFullScreen(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormFullScreen::FormCreate(TObject *Sender)
{
	Left = 0;
    Top = 0;
    Width = Screen->Width;
    Height = Screen->Height;

    nRes = 1;
}
//---------------------------------------------------------------------------
/*
void __fastcall TFormFullScreen::WndProc(Messages::TMessage &Message)
{
    if(DM->ServiceType == stMaintenance)
    {
    	switch(Message.Msg)
        {
			case WM_LBUTTONDBLCLK:
			case WM_LBUTTONDOWN:			case WM_LBUTTONUP:			case WM_MBUTTONDBLCLK:			case WM_MBUTTONDOWN:			case WM_MBUTTONUP:			case WM_MOUSEMOVE:			case WM_MOUSEWHEEL:			case WM_RBUTTONDBLCLK:			case WM_RBUTTONDOWN:			case WM_RBUTTONUP:
            {
				DWORD dwFlag;
				switch(Message.Msg)
			    {
			     	case WM_LBUTTONDOWN:
		    	    {
			        	dwFlag = MOUSEEVENTF_LEFTDOWN;
			         	break;
			        }
			     	case WM_LBUTTONUP:
		    	    {
			        	dwFlag = MOUSEEVENTF_LEFTUP;
			         	break;
			        }
			     	case WM_MBUTTONDOWN:
			        {
			        	dwFlag = MOUSEEVENTF_MIDDLEDOWN;
			         	break;
			        }
			     	case WM_MBUTTONUP:
			        {
			        	dwFlag = MOUSEEVENTF_MIDDLEUP;
			         	break;
			        }
			     	case WM_RBUTTONDOWN:
			        {
		    	    	dwFlag = MOUSEEVENTF_RIGHTDOWN;
			         	break;
			        }
			     	case WM_RBUTTONUP:
			        {
		    	    	dwFlag = MOUSEEVENTF_RIGHTUP;
			         	break;
			        }
                    case WM_MOUSEMOVE:
                    {
                    	X = LOWORD(Message.LParam);
                        Y = HIWORD(Message.LParam);

				    	if((abs(X - nPrevX) <= nRes) && (abs(Y - nPrevY) <= nRes))
						DMClient->SendMouseCommand(MOUSEEVENTF_MOVE,X,Y);
				        nPrevX = X;
				        nPrevY = Y;
						break;
                    }
			    }
        		DMClient->SendMouseCommand(dwFlag,X,Y);
             	break;
            }

			case WM_ACTIVATE:
			case WM_CHAR:			case WM_DEADCHAR:			case WM_GETHOTKEY:			case WM_HOTKEY:			case WM_KEYDOWN:			case WM_KEYUP:			case WM_KILLFOCUS:			case WM_SETFOCUS:			case WM_SETHOTKEY:			case WM_SYSCHAR:			case WM_SYSDEADCHAR:			case WM_SYSKEYDOWN:			case WM_SYSKEYUP:
            {
				DMClient->SendWindowsMessage(Message.Msg,Message.WParam,Message.LParam);
             	break;
            }
        }
    }
	TForm::WndProc(Message);
}
*/
//---------------------------------------------------------------------------
/*
void __fastcall TFormFullScreen::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
	SetCapture(FormFullScreen->Handle);
    ::SetFocus(FormFullScreen->Handle);
    if(DM->ServiceType == stMaintenance)
    {
		DWORD dwFlag;
		switch(Button)
	    {
	     	case mbLeft:
    	    {
	        	dwFlag = MOUSEEVENTF_LEFTDOWN;
	         	break;
	        }
	     	case mbMiddle:
	        {
	        	dwFlag = MOUSEEVENTF_MIDDLEDOWN;
	         	break;
	        }
	     	case mbRight:
	        {
    	    	dwFlag = MOUSEEVENTF_RIGHTDOWN;
	         	break;
	        }
	    }
        DMClient->SendMouseCommand(dwFlag,X,Y);
    }
    else
    if(DM->ServiceType == stWatching)
    {
		DM->AWatchingReportExecute(NULL);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormFullScreen::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    if(DM->ServiceType == stMaintenance)
    {
    	if((abs(X - nPrevX) <= nRes) && (abs(Y - nPrevY) <= nRes))
			DMClient->SendMouseCommand(MOUSEEVENTF_MOVE,X,Y);
        nPrevX = X;
        nPrevY = Y;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormFullScreen::FormMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(DM->ServiceType == stMaintenance)
    {
		DWORD dwFlag;
		switch(Button)
	    {
	     	case mbLeft:
	        {
	        	dwFlag = MOUSEEVENTF_LEFTUP;
	         	break;
	        }
	     	case mbMiddle:
	        {
	        	dwFlag = MOUSEEVENTF_MIDDLEUP;
	         	break;
	        }
	     	case mbRight:
	        {
	        	dwFlag = MOUSEEVENTF_RIGHTUP;
	         	break;
	        }
	    }
        DMClient->SendMouseCommand(dwFlag,X,Y);
    }
}
*/
//---------------------------------------------------------------------------

void __fastcall TFormFullScreen::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    if(DM->ServiceType == stMaintenance)
    {
	    DMClient->SendMouseCommand(MOUSEEVENTF_LEFTUP,0,0);
	    DMClient->SendMouseCommand(MOUSEEVENTF_MIDDLEUP,0,0);
	    DMClient->SendMouseCommand(MOUSEEVENTF_RIGHTUP,0,0);
	    DMClient->SendKeyboardCommand(0,0);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormFullScreen::FormActivate(TObject *Sender)
{
	SetCapture(FormFullScreen->Handle);
    ::SetFocus(FormFullScreen->Handle);
}
//---------------------------------------------------------------------------

void __fastcall TFormFullScreen::FormDeactivate(TObject *Sender)
{
	ReleaseCapture();	
}
//---------------------------------------------------------------------------/*
/*
void __fastcall TFormFullScreen::ApplicationEvents1ShortCut(TWMKey &Msg,
      bool &Handled)
{
	switch(Msg.CharCode)
    {
     	case VK_ESCAPE:
        {
			Close();
         	return;
        }
    }
    if(DM->ServiceType == stMaintenance)
    {
	    DMClient->SendKeyboardCommand(Msg.CharCode);
    }
    Handled = true;
}
*/
//---------------------------------------------------------------------------
/*
void __fastcall TFormFullScreen::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	switch(Key)
    {
     	case VK_ESCAPE:
        {
			Close();
         	return;
        }
    }
    if(DM->ServiceType == stMaintenance)
    {
	    DMClient->SendKeyboardCommand(Key);
    }
}
*/
//---------------------------------------------------------------------------

void __fastcall TFormFullScreen::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
	::SetCapture(FormFullScreen->Handle);
    ::SetFocus(FormFullScreen->Handle);
	::SetActiveWindow(FormFullScreen->Handle);
    if(DM->ServiceType == stMaintenance)
    {
		DWORD dwFlag;
		switch(Button)
	    {
	     	case mbLeft:
    	    {
	        	dwFlag = MOUSEEVENTF_LEFTDOWN;
	         	break;
	        }
	     	case mbMiddle:
	        {
	        	dwFlag = MOUSEEVENTF_MIDDLEDOWN;
	         	break;
	        }
	     	case mbRight:
	        {
    	    	dwFlag = MOUSEEVENTF_RIGHTDOWN;
	         	break;
	        }
	    }
        DMClient->SendMouseCommand(dwFlag,X,Y);
    }
    else
    if(DM->ServiceType == stWatching)
    {
		DM->AWatchingReportExecute(NULL);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormFullScreen::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    if(DM->ServiceType == stMaintenance)
    {
    	if((abs(X - nPrevX) <= nRes) && (abs(Y - nPrevY) <= nRes))
			DMClient->SendMouseCommand(MOUSEEVENTF_MOVE,X,Y);
        nPrevX = X;
        nPrevY = Y;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormFullScreen::FormMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(DM->ServiceType == stMaintenance)
    {
		DWORD dwFlag;
		switch(Button)
	    {
	     	case mbLeft:
	        {
	        	dwFlag = MOUSEEVENTF_LEFTUP;
	         	break;
	        }
	     	case mbMiddle:
	        {
	        	dwFlag = MOUSEEVENTF_MIDDLEUP;
	         	break;
	        }
	     	case mbRight:
	        {
	        	dwFlag = MOUSEEVENTF_RIGHTUP;
	         	break;
	        }
	    }
        DMClient->SendMouseCommand(dwFlag,X,Y);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormFullScreen::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	switch(Key)
    {
     	case VK_ESCAPE:
        {
			Close();
         	return;
        }
    }
    if(DM->ServiceType == stMaintenance)
    {
    	wShift = 0;
    	if(Shift.Contains(ssShift))
        {
        	wShift = 0;
        }
        else
    	if(Shift.Contains(ssAlt))
        {
        	wShift = 1;
        }
        else
    	if(Shift.Contains(ssCtrl))
        {
        	wShift = 2;
        }
        else
    	if(Shift.Contains(ssLeft))
        {
        	wShift = 3;
        }
        else
    	if(Shift.Contains(ssRight))
        {
        	wShift = 4;
        }
        else
    	if(Shift.Contains(ssMiddle))
        {
        	wShift = 5;
        }
        else
    	if(Shift.Contains(ssDouble))
        {
        	wShift = 6;
        }
	    DMClient->SendKeyboardCommand(Key,wShift);
    }
}
//---------------------------------------------------------------------------

