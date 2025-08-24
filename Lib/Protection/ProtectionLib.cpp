//---------------------------------------------------------------------------
#include <string.h>
#include <registry.hpp>
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "ProtectionLib.h"
#include "skeydrv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#ifdef _DEFAULT_
// Default
const AnsiString c_strLabel = "¨≤æ≠´¥∫¶";// "SMARTKEY"
const AnsiString c_strPassword = "∫™´≠∞±";// "EUTRON"
const AnsiString c_strDungleData = "¨∫º™≠∂´¶ﬂªæ´æ";// "SECURITY DATA"
const AnsiString c_strDungleScramplingData = " d£73≠€≤";
const AnsiString c_strExecutionCountKeyExt = "\\0";// ALL
#endif
//---------------------------------------------------------------------------
#ifdef _ALL_
// All (0)
const AnsiString c_strLabel = "®®Ø´º†æ≥≥†≥æΩ∫≥†Œ";// "WWPTC_ALL_LABEL_1";
const AnsiString c_strPassword = "æ≥≥†Øæ¨¨®∞≠ª†Œ";// "ALL_PASSWORD_1";
const AnsiString c_strDungleData = "æ≥≥†ªæ´æ†Œ";// "ALL_DATA_1";
const AnsiString c_strDungleScramplingData = " d£73≠€≤";
const AnsiString c_strExecutionCountKeyExt = "\\0";// ALL
#endif
//---------------------------------------------------------------------------
#ifdef _NETWATCHER_
// NetWatcher (A)
const AnsiString c_strLabel = "®®Ø´º†±®†≥æΩ∫≥†Œ";// "WWPTC_NW_LABEL_1";
const AnsiString c_strPassword = "±®†Øæ¨¨®∞≠ª†Œ";// "NW_PASSWORD_1";
const AnsiString c_strDungleData = "±®†ªæ´æ†Œ";// "NW_DATA_1";
const AnsiString c_strDungleScramplingData = " d£73≠€≤";
const AnsiString c_strExecutionCountKeyExt = "\\A";// NetWatcher
#endif
//---------------------------------------------------------------------------
#ifdef _CHILED_CLINIC_
// Chiled Clinic (B)
const AnsiString c_strLabel = "®®Ø´º†ºº†≥æΩ∫≥†Œ";// "WWPTC_CC_LABEL_1";
const AnsiString c_strPassword = "ºº†Øæ¨¨®∞≠ª†Œ";// "CC_PASSWORD_1";
const AnsiString c_strDungleData = "ºº†ªæ´æ†Œ";// "CC_DATA_1";
const AnsiString c_strDungleScramplingData = " d£73≠€≤";
const AnsiString c_strExecutionCountKeyExt = "\\B";// Chiled Clinic
#endif
//---------------------------------------------------------------------------
#ifdef _PUBLIC_CLINIC_
// Public Clinic (C)
const AnsiString c_strLabel = "®®Ø´º†Øº†≥æΩ∫≥†Œ";// "WWPTC_PC_LABEL_1";
const AnsiString c_strPassword = "Øº†Øæ¨¨®∞≠ª†Œ";// "PC_PASSWORD_1";
const AnsiString c_strDungleData = "Øº†ªæ´æ†Œ";// "PC_DATA_1";
const AnsiString c_strDungleScramplingData = " d£73≠€≤";
const AnsiString c_strExecutionCountKeyExt = "\\C";// Public Clinic
#endif
//---------------------------------------------------------------------------
#ifdef _SKIN_CLINIC_
// Skin Clinic (D)
const AnsiString c_strLabel = "®®Ø´º†¨º†≥æΩ∫≥†Œ";// "WWPTC_SC_LABEL_1";
const AnsiString c_strPassword = "¨º†Øæ¨¨®∞≠ª†Œ";// "SC_PASSWORD_1";
const AnsiString c_strDungleData = "¨º†ªæ´æ†Œ";// "SC_DATA_1";
const AnsiString c_strDungleScramplingData = " d£73≠€≤";
const AnsiString c_strExecutionCountKeyExt = "\\D";// Skin Clinic
#endif
//---------------------------------------------------------------------------
#ifdef _FEMAIL_CLINIC_
// Femail Clinic (E)
const AnsiString c_strLabel = "®®Ø´º†πº†≥æΩ∫≥†Œ";// "WWPTC_FC_LABEL_1";
const AnsiString c_strPassword = "πº†Øæ¨¨®∞≠ª†Œ";// "FC_PASSWORD_1";
const AnsiString c_strDungleData = "πº†ªæ´æ†Œ";// "FC_DATA_1";
const AnsiString c_strDungleScramplingData = " d£73≠€≤";
const AnsiString c_strExecutionCountKeyExt = "\\E";// Femail Clinic
#endif
//---------------------------------------------------------------------------
#ifdef _ATTENDANCE_
// Attendance (F)
const AnsiString c_strLabel = "®®Ø´º†æ†≥æΩ∫≥†Œ";// "WWPTC_A_LABEL_1";
const AnsiString c_strPassword = "æ†Øæ¨¨®∞≠ª†Œ";// "A_PASSWORD_1";
const AnsiString c_strDungleData = "æ†ªæ´æ†Œ";// "A_DATA_1";
const AnsiString c_strDungleScramplingData = " d£73≠€≤";
const AnsiString c_strExecutionCountKeyExt = "\\F";// Attendance
#endif
//---------------------------------------------------------------------------
#ifdef _CENTRAL_
// Central (G)
const AnsiString c_strLabel = "®®Ø´º†º†≥æΩ∫≥†Œ";// "WWPTC_C_LABEL_1";
const AnsiString c_strPassword = "º†Øæ¨¨®∞≠ª†Œ";// "C_PASSWORD_1";
const AnsiString c_strDungleData = "º†ªæ´æ†Œ";// "C_DATA_1";
const AnsiString c_strDungleScramplingData = " d£73≠€≤";
const AnsiString c_strExecutionCountKeyExt = "\\G";// Central
#endif
//---------------------------------------------------------------------------
#ifdef _DIALER_NET_
// Dialer Net (H)
const AnsiString c_strLabel = "®®Ø´º†ª±†≥æΩ∫≥†Œ";// "WWPTC_DN_LABEL_1";
const AnsiString c_strPassword = "ª±†Øæ¨¨®∞≠ª†Œ";// "DN_PASSWORD_1";
const AnsiString c_strDungleData = "ª±†ªæ´æ†Œ";// "DN_DATA_1";
const AnsiString c_strDungleScramplingData = " d£73≠€≤";
const AnsiString c_strExecutionCountKeyExt = "\\H";// Dialer Net
#endif
//---------------------------------------------------------------------------
#ifdef _DIALER_LOCAL_
// Dialer Local (I)
const AnsiString c_strLabel = "®®Ø´º†ª≥†≥æΩ∫≥†Œ";// "WWPTC_DL_LABEL_1";
const AnsiString c_strPassword = "ª≥†Øæ¨¨®∞≠ª†Œ";// "DL_PASSWORD_1";
const AnsiString c_strDungleData = "ª≥†ªæ´æ†Œ";// "DL_DATA_1";
const AnsiString c_strDungleScramplingData = " d£73≠€≤";
const AnsiString c_strExecutionCountKeyExt = "\\I";// Dialer Local
#endif
//---------------------------------------------------------------------------
#ifdef _EMBROIDERY_
// Embroidery (J)
const AnsiString c_strLabel = "®®Ø´º†∫≤Ω†≥æΩ∫≥†Œ";// "WWPTC_EMB_LABEL_1";
const AnsiString c_strPassword = "∫≤Ω†Øæ¨¨®∞≠ª†Œ";// "EMB_PASSWORD_1";
const AnsiString c_strDungleData = "∫≤Ω†ªæ´æ†Œ";// "EMB_DATA_1";
const AnsiString c_strDungleScramplingData = " d£73≠€≤";
const AnsiString c_strExecutionCountKeyExt = "\\J";// Embroidery
#endif
//---------------------------------------------------------------------------
#ifdef _GL_ACCOUNT_
// Embroidery (J)
const AnsiString c_strLabel = "®®Ø´º†∫≤Ω†≥æΩ∫≥†Œ";// "WWPTC_GL_LABEL_1";
const AnsiString c_strPassword = "∫≤Ω†Øæ¨¨®∞≠ª†Œ";// "GL_PASSWORD_1";
const AnsiString c_strDungleData = "∫≤Ω†ªæ´æ†Œ";// "GL_DATA_1";
const AnsiString c_strDungleScramplingData = " d£73≠€≤";
const AnsiString c_strExecutionCountKeyExt = "\\G";// GL
#endif
//---------------------------------------------------------------------------
const AnsiString c_strDungleNotExists = "«·ﬁ›· «·≈·ﬂ —Ê‰Ì €Ì— „ÊÃÊœ";
const AnsiString c_strDebuggerPresent = "Ì—ÃÏ ≈€·«ﬁ «·„‰ﬁÕ ﬁ»·  ‰›Ì– «·»—‰«„Ã";
const AnsiString c_strTheEvaluationTimeReached = "≈‰ Â  «·› —… «· Ã—Ì»Ì… ··»—‰«„Ã";
//---------------------------------------------------------------------------
const AnsiString c_strExecutionCountName = "V";
const AnsiString c_strExecutionCountKey = "£¨êôãàûçö£≤ñúçêåêôã£®ñëõêàå£ºäççöëã©öçåñêë£ª≤¨£©©";
const int	c_nExecutionCount = 100;
//---------------------------------------------------------------------------
#ifdef _TEST_
void status_error(int err);
#endif
void pro_Initialize();
void pro_Finalize();
//---------------------------------------------------------------------------
//-----------------------System Utilities------------------------------------
//---------------------------------------------------------------------------
bool IsWinNT()
{
	OSVERSIONINFO VersionInfo;
    VersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&VersionInfo);
    return (VersionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT);
}
//---------------------------------------------------------------------------
bool IsWin9x()
{
 	OSVERSIONINFO VersionInfo;
    VersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&VersionInfo);
    return (VersionInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS);
}
//---------------------------------------------------------------------------
bool IsWin3_11()
{
 	OSVERSIONINFO VersionInfo;
    VersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&VersionInfo);
    return (VersionInfo.dwPlatformId == VER_PLATFORM_WIN32s);
}
//---------------------------------------------------------------------------
// Return Values:
//      VER_PLATFORM_WIN32s          'Win16 running Win32s';
//      VER_PLATFORM_WIN32_WINDOWS   'Win32 Windows, probably Win95';
//      VER_PLATFORM_WIN32_NT        'WinNT, full 32-bit';
//---------------------------------------------------------------------------
DWORD GetSystemVersion()
{
 	OSVERSIONINFO VersionInfo;
    VersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&VersionInfo);
    return VersionInfo.dwPlatformId;
}
//---------------------------------------------------------------------------
//-----------------------Demo routines---------------------------------------
//---------------------------------------------------------------------------
AnsiString EncodeString(AnsiString strText)
{
	AnsiString strResult="";
	for(int i=1;i<=strText.Length();i++)
    {
		strResult+=char(255-Byte(strText[i]));
    }
    return strResult;
}
//---------------------------------------------------------------------------
void InitCheckExecutionCount()
{
  	TRegistry *Registry = new TRegistry();
  	try
  	{
    	Registry->RootKey = HKEY_LOCAL_MACHINE;
/*
        try
        {
	    	if(Registry->OpenKey(EncodeString(c_strExecutionCountKey)+c_strExecutionCountKeyExt,false))
    	    {
        	    Registry->CloseKey();
	        }
	        else
	        {
		    	if(Registry->OpenKey(EncodeString(c_strExecutionCountKey)+c_strExecutionCountKeyExt,true))
	    	    {
	    			int nExecutionCount = 0;
	                Registry->WriteString(c_strExecutionCountName,EncodeString(IntToStr(nExecutionCount)));
	            	Registry->CloseKey();
	            }
	        }
        }
        catch(...)
        {
        	if(Registry->OpenKey(EncodeString(c_strExecutionCountKey)+c_strExecutionCountKeyExt,true))
            {
            	int nExecutionCount = 0;
                Registry->WriteString(c_strExecutionCountName,EncodeString(IntToStr(nExecutionCount)));
                Registry->CloseKey();
            }
        }
*/
    	if(Registry->OpenKey(EncodeString(c_strExecutionCountKey)+c_strExecutionCountKeyExt,false))
        {
        	AnsiString strExecutionCount;
            try
            {
    			int nExecutionCount;
                strExecutionCount = EncodeString(Registry->ReadString(c_strExecutionCountName));
	    		nExecutionCount = StrToInt(strExecutionCount);
                if(nExecutionCount >= c_nExecutionCount)
                {
    				#ifdef _TEST_
    				MessageDlg(c_strTheEvaluationTimeReached,mtInformation,TMsgDlgButtons()<<mbOK,0);
        			#else
    				FatalAppExit(0,c_strTheEvaluationTimeReached.c_str());
        			#endif
                }
                else
                {
                	nExecutionCount++;
      				Registry->WriteString(c_strExecutionCountName,EncodeString(IntToStr(nExecutionCount)));
                }
            }
            catch(...)
            {
            	#ifdef _TEST_
                MessageDlg(c_strTheEvaluationTimeReached,mtInformation,TMsgDlgButtons()<<mbOK,0);
                #else
                FatalAppExit(0,c_strTheEvaluationTimeReached.c_str());
                #endif
            }
            Registry->CloseKey();
        }
        else
        {
        	#ifdef _TEST_
            MessageDlg(c_strTheEvaluationTimeReached,mtInformation,TMsgDlgButtons()<<mbOK,0);
            #else
            FatalAppExit(0,c_strTheEvaluationTimeReached.c_str());
            #endif
        }
    	delete Registry;
  	}
  	catch(...)
  	{
    	delete Registry;

        #ifdef _TEST_
        MessageDlg(c_strTheEvaluationTimeReached,mtInformation,TMsgDlgButtons()<<mbOK,0);
        #else
        FatalAppExit(0,c_strTheEvaluationTimeReached.c_str());
        #endif
  	}
}
//---------------------------------------------------------------------------
void CheckExecutionCount()
{
  	TRegistry *Registry = new TRegistry();
  	try
  	{
    	Registry->RootKey = HKEY_LOCAL_MACHINE;
    	if(Registry->OpenKey(EncodeString(c_strExecutionCountKey)+c_strExecutionCountKeyExt,false))
        {
        	AnsiString strExecutionCount;
            try
            {
    			int nExecutionCount;
                strExecutionCount = EncodeString(Registry->ReadString(c_strExecutionCountName));
	    		nExecutionCount = StrToInt(strExecutionCount);
                if(nExecutionCount >= c_nExecutionCount)
                {
    				#ifdef _TEST_
    				MessageDlg(c_strTheEvaluationTimeReached,mtInformation,TMsgDlgButtons()<<mbOK,0);
        			#else
    				FatalAppExit(0,c_strTheEvaluationTimeReached.c_str());
        			#endif
                }
            }
            catch(...)
            {
            	#ifdef _TEST_
                MessageDlg(c_strTheEvaluationTimeReached,mtInformation,TMsgDlgButtons()<<mbOK,0);
                #else
                FatalAppExit(0,c_strTheEvaluationTimeReached.c_str());
                #endif
            }
            Registry->CloseKey();
        }
        else
        {
        	#ifdef _TEST_
            MessageDlg(c_strTheEvaluationTimeReached,mtInformation,TMsgDlgButtons()<<mbOK,0);
            #else
            FatalAppExit(0,c_strTheEvaluationTimeReached.c_str());
            #endif
        }
    	delete Registry;
  	}
  	catch(...)
  	{
    	delete Registry;

        #ifdef _TEST_
        MessageDlg(c_strTheEvaluationTimeReached,mtInformation,TMsgDlgButtons()<<mbOK,0);
        #else
        FatalAppExit(0,c_strTheEvaluationTimeReached.c_str());
        #endif
  	}
}
//---------------------------------------------------------------------------
bool IsInvalidExecutionCount()
{
  	TRegistry *Registry = new TRegistry();
  	try
  	{
    	Registry->RootKey = HKEY_LOCAL_MACHINE;
    	if(Registry->OpenKey(EncodeString(c_strExecutionCountKey)+c_strExecutionCountKeyExt,false))
        {
        	AnsiString strExecutionCount;
            try
            {
    			int nExecutionCount;
                strExecutionCount = EncodeString(Registry->ReadString(c_strExecutionCountName));
	    		nExecutionCount = StrToInt(strExecutionCount);
                if(nExecutionCount >= c_nExecutionCount)
                {
					return true;
                }
            }
            catch(...)
            {
            	return true;
            }
            Registry->CloseKey();
        }
        else
        {
        	return true;
        }
    	delete Registry;
  	}
  	catch(...)
  	{
    	delete Registry;

        return true;
  	}
    return false;
}
//---------------------------------------------------------------------------
//-----------------------AntiDebugging routines------------------------------
//---------------------------------------------------------------------------
void pro_DebuggerCheck()
{
	if(IsWinNT())
    {
	 	if(IsDebuggerPresent())
	    {
	    	#ifdef _TEST_
	   		status_error(-100);
	        #else
	    	FatalAppExit(0,c_strDebuggerPresent.c_str());
	        #endif
	    }
    }
}
//---------------------------------------------------------------------------
bool pro_IsDebuggerLoaded()
{
	if(IsWinNT())
	 	return IsDebuggerPresent();
    else
    	return false;
}
//---------------------------------------------------------------------------
bool pro_IsSoftIce95Loaded()
{
	HANDLE hFile;
  	bool bResult = false;
  	hFile = CreateFileA("\\\\.\\SICE", GENERIC_READ | GENERIC_WRITE,
    					FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
    					FILE_ATTRIBUTE_NORMAL, 0);
  	if( hFile != INVALID_HANDLE_VALUE )
    {
    	CloseHandle(hFile);
    	bResult = true;
  	}
    return bResult;
}
//---------------------------------------------------------------------------
void pro_SoftIce95Check()
{
	HANDLE hFile;
  	bool bResult = false;
  	hFile = CreateFileA("\\\\.\\SICE", GENERIC_READ | GENERIC_WRITE,
    					FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
    					FILE_ATTRIBUTE_NORMAL, 0);
  	if( hFile != INVALID_HANDLE_VALUE )
    {
    	CloseHandle(hFile);
    	bResult = true;
  	}

    if(bResult)
    {
    	#ifdef _TEST_
   		status_error(-101);
        #else
    	FatalAppExit(0,c_strDebuggerPresent.c_str());
        #endif
    }
}
//---------------------------------------------------------------------------
bool pro_IsSoftIceNTLoaded()
{
	HANDLE hFile;
  	bool bResult = false;
  	hFile = CreateFileA("\\\\.\\NTICE", GENERIC_READ | GENERIC_WRITE,
    					FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
    					FILE_ATTRIBUTE_NORMAL, 0);
  	if( hFile != INVALID_HANDLE_VALUE )
    {
    	CloseHandle(hFile);
    	bResult = true;
  	}
    return bResult;
}
//---------------------------------------------------------------------------
void pro_SoftIceNTCheck()
{
	HANDLE hFile;
  	bool bResult = false;
  	hFile = CreateFileA("\\\\.\\NTICE", GENERIC_READ | GENERIC_WRITE,
    					FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
    					FILE_ATTRIBUTE_NORMAL, 0);
  	if( hFile != INVALID_HANDLE_VALUE )
    {
    	CloseHandle(hFile);
    	bResult = true;
  	}

    if(bResult)
    {
    	#ifdef _TEST_
   		status_error(-101);
        #else
    	FatalAppExit(0,c_strDebuggerPresent.c_str());
        #endif
    }
}
//---------------------------------------------------------------------------
void pro_SoftIceCheck()
{
	if(IsWinNT())
	    pro_SoftIceNTCheck();
    else
		pro_SoftIce95Check();
}
//---------------------------------------------------------------------------
bool pro_IsSoftIceLoaded()
{
	if(IsWinNT())
		return pro_IsSoftIceNTLoaded();
    else
		return pro_IsSoftIce95Loaded();
}
//---------------------------------------------------------------------------
//-----------------------Dungle routines-------------------------------------
//---------------------------------------------------------------------------
void pro_Check()
{
	static SKEY_DATA key;               

	/* Locating Mode */

	key.command = (int) 'L';
	memset (key.label,'\0',LABEL_LENGTH);
	memset (key.password,'\0',PASSWORD_LENGTH);
	memset (key.data,'\0',DATA_LENGTH);
	lstrcpy((char *)key.label, EncodeString(c_strLabel).c_str());

	msclink (&key);

  	if ( key.status != ST_OK )
  	{
    	#ifdef _TEST_
   		status_error(key.status);
        #else
    	FatalAppExit(0,c_strDungleNotExists.c_str());
        #endif
  	}

	/* Comparing Mode */

	key.command = (int) 'C';
	memset ((char *)key.label,'\0',LABEL_LENGTH);
	memset ((char *)key.password,'\0',PASSWORD_LENGTH);
	memset ((char *)key.data,'\0',DATA_LENGTH);
	lstrcpy((char *)key.label, EncodeString(c_strLabel).c_str());
	lstrcpy((char *)key.password, EncodeString(c_strPassword).c_str());
	lstrcpy((char *)key.data, EncodeString(c_strDungleData).c_str());

	msclink (&key);

  	if ( key.status < ST_OK )
  	{
    	#ifdef _TEST_
   		status_error(key.status);
        #else
    	FatalAppExit(0,c_strDungleNotExists.c_str());
        #endif
  	}
}
//---------------------------------------------------------------------------
void pro_Scrambling()
{
	/* Scrambling Mode */
/*
	key.command = (int) 'S';
	memset ((char *)key.label,'\0',LABEL_LENGTH);
	lstrcpy((char *)key.label, EncodeString(c_strLabel).c_str());
	lstrcpy((char *)key.data, "12345678");

	msclink (&key);
/*
	if ( key.status < 0 )
		ErrorKey(hWnd, key.status);
	else
    {
		sprintf(key_mess2, "Original    Data   : 0x31 0x32 0x33 0x34 0x35 0x36 0x37 0x38");
		SetEditText(hMess2,(LPSTR)key_mess2);
		sprintf(key_mess3, "Scrambled Data : 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x",
					key.data[0], key.data[1],
					key.data[2], key.data[3],
					key.data[4], key.data[5],
					key.data[6], key.data[7] );
		SetEditText(hMess3,(LPSTR)key_mess3);
	}
*/
/*
	pro_Initialize();

  	//ACCESS MODE: SCRAMBLING
	KEY_NET	  user_key;
    ZeroMemory(&user_key,sizeof(user_key));
  	strcpy(user_key.label,EncodeString(c_strLabel).c_str());
  	strcpy(user_key.password,EncodeString(c_strPassword).c_str());
  	strcpy(user_key.data,EncodeString(c_strDungleData).c_str());
  	user_key.net_command = NET_KEY_ACCESS;
  	user_key.command = SCRAMBLING_MODE;

  	//SmartKey calling
  	_smartlink(&user_key);

  	//convert error in string
  	if ( user_key.status != ST_OK )
  	{
    	#ifdef _TEST_
   		status_error(user_key.status);
        #else
    	FatalAppExit(0,c_strDungleNotExists.c_str());
        #endif
  	}
  	else
  	{
     	if(AnsiString((char *)user_key.data) != c_strDungleScramplingData)
        {
	    	#ifdef _TEST_
	   		status_error(user_key.status);
	        #else
	    	FatalAppExit(0,c_strDungleNotExists.c_str());
	        #endif
        }
  	}

    pro_Finalize();
*/    
}
//---------------------------------------------------------------------------
#ifdef _TEST_
void status_error(int err)
{
/*
  	switch (err)
  	{
     	case -100:
        	ShowMessage("Debugger Present!");
        break;
     	case -101:
        	ShowMessage("SoftIce Present!");
        break;
     	case ST_NONE_KEY:
        	ShowMessage("No SmartKey Found!");
        break;
     	case ST_SYNT_ERR:
        	ShowMessage("Syntax error!");
        break;
     	case ST_PW_DATA_FAILED:
        	ShowMessage("Uncorrect password or Data!");
        break;
     	case ST_EXEC_ERROR:
        	ShowMessage("Number of executions excedeed");
        break;
     	case ST_HW_FAILURE:
        	ShowMessage("Hardware failure! Check yours SmartKey!");
        break;
     	default:
        	ShowMessage("Unrecognized error!");
        break;
  	}
*/    
}
#endif
//---------------------------------------------------------------------------

