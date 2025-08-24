//---------------------------------------------------------------------------
#ifndef nw_CopyThreadH
#define nw_CopyThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "CopyDialog.h"
//---------------------------------------------------------------------------
class nw_CopyThread : public TThread
{            
private:
	int 	m_nFilesCount;
	int 	m_nDirsCount;
	__int64 	m_nFilesSize;
	int       	m_nError;

	AnsiString  	m_strSourceFileName;
	AnsiString  	m_strDestFileName;

	TFormCopyDialog *m_pFormCopyDialog;
    bool			m_bFromRemoteToLocal;

protected:
	void __fastcall Execute();
public:
	__fastcall nw_CopyThread(bool CreateSuspended,bool bFromRemoteToLocal = true);
	void __fastcall DoFreeMemory(TObject *Sender);
	void __fastcall UpdateStatus();

	AnsiString  	m_strSourceDirName;
	AnsiString  	m_strDestDirName;
	AnsiString  	m_strCurrDirName;
    AnsiString		m_strTo;
};
//---------------------------------------------------------------------------
#endif
