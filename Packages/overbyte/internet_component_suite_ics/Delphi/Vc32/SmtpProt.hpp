// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'SmtpProt.pas' rev: 6.00

#ifndef SmtpProtHPP
#define SmtpProtHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <MD5.hpp>	// Pascal unit
#include <WinSock.hpp>	// Pascal unit
#include <WSocket.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Smtpprot
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS SmtpException;
class PASCALIMPLEMENTATION SmtpException : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall SmtpException(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall SmtpException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall SmtpException(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall SmtpException(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall SmtpException(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall SmtpException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall SmtpException(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall SmtpException(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~SmtpException(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TSmtpState { smtpReady, smtpDnsLookup, smtpConnecting, smtpConnected, smtpInternalReady, smtpWaitingBanner, smtpWaitingResponse, smtpAbort };
#pragma option pop

#pragma option push -b-
enum TSmtpRequest { smtpConnect, smtpHelo, smtpMailFrom, smtpVrfy, smtpRcptTo, smtpData, smtpQuit, smtpRset, smtpOpen, smtpMail, smtpEhlo, smtpAuth, smtpCustom };
#pragma option pop

#pragma option push -b-
enum TSmtpFct { smtpFctNone, smtpFctHelo, smtpFctConnect, smtpFctMailFrom, smtpFctRcptTo, smtpFctData, smtpFctVrfy, smtpFctQuit, smtpFctRset, smtpFctEhlo, smtpFctAuth };
#pragma option pop

typedef Set<TSmtpFct, smtpFctNone, smtpFctAuth>  TSmtpFctSet;

#pragma option push -b-
enum TSmtpContentType { smtpHTML, smtpPlainText };
#pragma option pop

#pragma option push -b-
enum TSmtpAuthType { smtpAuthNone, smtpAuthPlain, smtpAuthLogin, smtpAuthCramMD5 };
#pragma option pop

typedef void __fastcall (__closure *TSmtpDisplay)(System::TObject* Sender, AnsiString Msg);

typedef void __fastcall (__closure *TSmtpHeaderLineEvent)(System::TObject* Sender, char * Msg, int Size);

typedef void __fastcall (__closure *TSmtpProcessHeaderEvent)(System::TObject* Sender, Classes::TStrings* HdrLines);

typedef void __fastcall (__closure *TSmtpGetDataEvent)(System::TObject* Sender, int LineNum, char * MsgLine, int MaxLen, bool &More);

typedef void __fastcall (__closure *TSmtpRequestDone)(System::TObject* Sender, TSmtpRequest RqType, Word Error);

typedef void __fastcall (__closure *TSmtpAttachmentContentType)(System::TObject* Sender, int FileNumber, AnsiString &FileName, AnsiString &ContentType);

typedef void __fastcall (__closure *TSmtpAttachHeader)(System::TObject* Sender, int FileNumber, AnsiString FileName, Classes::TStrings* HdrLines);

typedef void __fastcall (__closure *TSmtpNextProc)(void);

class DELPHICLASS TCustomSmtpClient;
class PASCALIMPLEMENTATION TCustomSmtpClient : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	HWND __fastcall SmtpClientAllocateHWnd(Wsocket::TWndMethod Method);
	void __fastcall SmtpClientDeallocateHWnd(HWND WHandle);
	
protected:
	Wsocket::TWSocket* FWSocket;
	AnsiString FHost;
	AnsiString FLocalAddr;
	AnsiString FPort;
	AnsiString FSignOn;
	AnsiString FUsername;
	AnsiString FPassword;
	TSmtpAuthType FAuthType;
	AnsiString FFromName;
	Classes::TStrings* FRcptName;
	Classes::TStrings* FMailMessage;
	AnsiString FHdrFrom;
	AnsiString FHdrTo;
	AnsiString FHdrReplyTo;
	AnsiString FHdrReturnPath;
	AnsiString FHdrSubject;
	AnsiString FHdrSender;
	TSmtpState FState;
	AnsiString FCharSet;
	TSmtpContentType FContentType;
	AnsiString FContentTypeStr;
	AnsiString FLastResponse;
	AnsiString FErrorMessage;
	int FTag;
	bool FConnected;
	bool FESmtpSupported;
	TSmtpRequest FRequestType;
	bool FRequestDoneFlag;
	int FReceiveLen;
	int FRequestResult;
	int FStatusCode;
	char FReceiveBuffer[4096];
	TSmtpNextProc FNext;
	TSmtpNextProc FWhenConnected;
	TSmtpFctSet FFctSet;
	TSmtpFct FFctPrv;
	int FHighLevelResult;
	bool FHighLevelFlag;
	TSmtpNextProc FNextRequest;
	AnsiString FLastResponseSave;
	int FStatusCodeSave;
	bool FRestartFlag;
	int FOkResponses[16];
	TSmtpNextProc FDoneAsync;
	HWND FWindowHandle;
	int FItemCount;
	Classes::TStrings* FHdrLines;
	int FLineNum;
	bool FMoreLines;
	bool FOwnHeaders;
	TSmtpDisplay FOnDisplay;
	TSmtpDisplay FOnCommand;
	TSmtpDisplay FOnResponse;
	TSmtpGetDataEvent FOnGetData;
	TSmtpHeaderLineEvent FOnHeaderLine;
	TSmtpProcessHeaderEvent FOnProcessHeader;
	TSmtpRequestDone FOnRequestDone;
	Classes::TNotifyEvent FOnStateChange;
	Wsocket::TSessionConnected FOnSessionConnected;
	Wsocket::TSessionClosed FOnSessionClosed;
	virtual void __fastcall TriggerDisplay(AnsiString Msg);
	virtual void __fastcall TriggerCommand(AnsiString Msg);
	virtual void __fastcall TriggerResponse(AnsiString Msg);
	virtual void __fastcall TriggerRequestDone(Word Error);
	virtual void __fastcall TriggerStateChange(void);
	virtual void __fastcall TriggerGetData(int LineNum, char * MsgLine, int MaxLen, bool &More);
	virtual void __fastcall TriggerHeaderLine(char * Line, int Size);
	virtual void __fastcall TriggerProcessHeader(Classes::TStrings* HdrLines);
	virtual void __fastcall TriggerSessionConnected(Word Error);
	virtual void __fastcall TriggerSessionClosed(Word Error);
	void __fastcall ClearErrorMessage(void);
	void __fastcall SetErrorMessage(void);
	void __fastcall StateChange(TSmtpState NewState);
	virtual void __fastcall SendCommand(AnsiString Cmd);
	void __fastcall SetRcptName(Classes::TStrings* newValue);
	void __fastcall SetMailMessage(Classes::TStrings* newValue);
	virtual void __fastcall InitUUEncode(file &hFile, AnsiString sFile);
	virtual void __fastcall DoUUEncode(file &hFile, AnsiString &sLine, bool &More);
	virtual void __fastcall EndUUEncode(file &hFile);
	void __fastcall CheckReady(void);
	void __fastcall WSocketDnsLookupDone(System::TObject* Sender, Word Error);
	void __fastcall WSocketSessionConnected(System::TObject* Sender, Word Error);
	void __fastcall WSocketDataAvailable(System::TObject* Sender, Word Error);
	void __fastcall WSocketDataSent(System::TObject* Sender, Word Error);
	void __fastcall WSocketSessionClosed(System::TObject* Sender, Word Error);
	void __fastcall DisplayLastResponse(void);
	void __fastcall DoHighLevelAsync(void);
	void __fastcall ExecAsync(TSmtpRequest RqType, AnsiString Cmd, const Word * OkResponses, const int OkResponses_Size, TSmtpNextProc DoneAsync);
	void __fastcall NextExecAsync(void);
	void __fastcall EhloNext(void);
	void __fastcall AuthNextLogin(void);
	void __fastcall AuthNextLoginNext(void);
	void __fastcall AuthNextCramMD5(void);
	void __fastcall RcptToNext(void);
	void __fastcall RcptToDone(void);
	void __fastcall DataNext(void);
	virtual void __fastcall WndProc(Messages::TMessage &MsgRec);
	MESSAGE void __fastcall WMSmtpRequestDone(Messages::TMessage &msg);
	
public:
	__fastcall virtual TCustomSmtpClient(Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomSmtpClient(void);
	virtual void __fastcall Connect(void);
	virtual void __fastcall Helo(void);
	virtual void __fastcall Ehlo(void);
	virtual void __fastcall Auth(void);
	virtual void __fastcall Vrfy(void);
	virtual void __fastcall MailFrom(void);
	virtual void __fastcall RcptTo(void);
	virtual void __fastcall Data(void);
	virtual void __fastcall Quit(void);
	virtual void __fastcall Rset(void);
	virtual void __fastcall Abort(void);
	virtual void __fastcall Open(void);
	virtual void __fastcall Mail(void);
	__property Wsocket::TWSocket* CtrlSocket = {read=FWSocket};
	__property HWND Handle = {read=FWindowHandle, nodefault};
	__property bool Connected = {read=FConnected, nodefault};
	void __fastcall HighLevelAsync(TSmtpRequest RqType, TSmtpFctSet Fcts);
	void __fastcall SetContentType(TSmtpContentType newValue);
	
protected:
	__property AnsiString Host = {read=FHost, write=FHost};
	__property AnsiString LocalAddr = {read=FLocalAddr, write=FLocalAddr};
	__property AnsiString Port = {read=FPort, write=FPort};
	__property AnsiString SignOn = {read=FSignOn, write=FSignOn};
	__property AnsiString Username = {read=FUsername, write=FUsername};
	__property AnsiString Password = {read=FPassword, write=FPassword};
	__property TSmtpAuthType AuthType = {read=FAuthType, write=FAuthType, nodefault};
	__property AnsiString FromName = {read=FFromName, write=FFromName};
	__property Classes::TStrings* RcptName = {read=FRcptName, write=SetRcptName};
	__property Classes::TStrings* MailMessage = {read=FMailMessage, write=SetMailMessage};
	__property AnsiString HdrFrom = {read=FHdrFrom, write=FHdrFrom};
	__property AnsiString HdrTo = {read=FHdrTo, write=FHdrTo};
	__property AnsiString HdrReplyTo = {read=FHdrReplyTo, write=FHdrReplyTo};
	__property AnsiString HdrReturnPath = {read=FHdrReturnPath, write=FHdrReturnPath};
	__property AnsiString HdrSubject = {read=FHdrSubject, write=FHdrSubject};
	__property AnsiString HdrSender = {read=FHdrSender, write=FHdrSender};
	__property AnsiString CharSet = {read=FCharSet, write=FCharSet};
	__property TSmtpContentType ContentType = {read=FContentType, write=SetContentType, nodefault};
	__property AnsiString ErrorMessage = {read=FErrorMessage};
	__property AnsiString LastResponse = {read=FLastResponse};
	__property TSmtpState State = {read=FState, nodefault};
	__property int Tag = {read=FTag, write=FTag, nodefault};
	__property bool OwnHeaders = {read=FOwnHeaders, write=FOwnHeaders, nodefault};
	__property TSmtpDisplay OnDisplay = {read=FOnDisplay, write=FOnDisplay};
	__property TSmtpDisplay OnCommand = {read=FOnCommand, write=FOnCommand};
	__property TSmtpDisplay OnResponse = {read=FOnResponse, write=FOnResponse};
	__property TSmtpGetDataEvent OnGetData = {read=FOnGetData, write=FOnGetData};
	__property TSmtpHeaderLineEvent OnHeaderLine = {read=FOnHeaderLine, write=FOnHeaderLine};
	__property TSmtpProcessHeaderEvent OnProcessHeader = {read=FOnProcessHeader, write=FOnProcessHeader};
	__property TSmtpRequestDone OnRequestDone = {read=FOnRequestDone, write=FOnRequestDone};
	__property Classes::TNotifyEvent OnStateChange = {read=FOnStateChange, write=FOnStateChange};
	__property Wsocket::TSessionConnected OnSessionConnected = {read=FOnSessionConnected, write=FOnSessionConnected};
	__property Wsocket::TSessionClosed OnSessionClosed = {read=FOnSessionClosed, write=FOnSessionClosed};
};


class DELPHICLASS TSmtpCli;
class PASCALIMPLEMENTATION TSmtpCli : public TCustomSmtpClient 
{
	typedef TCustomSmtpClient inherited;
	
protected:
	Classes::TStrings* FEmailBody;
	Classes::TStrings* FEmailFiles;
	int FCurrentFile;
	AnsiString FMimeBoundary;
	file FFile;
	bool FFileStarted;
	bool FBodyFlag;
	int FBodyLine;
	TSmtpAttachmentContentType FOnAttachContentType;
	TSmtpAttachHeader FOnAttachHeader;
	virtual void __fastcall TriggerAttachContentType(int FileNumber, AnsiString &FileName, AnsiString &ContentType);
	virtual void __fastcall TriggerAttachHeader(int FileNumber, AnsiString FileName, Classes::TStrings* HdrLines);
	virtual void __fastcall TriggerGetData(int LineNum, char * MsgLine, int MaxLen, bool &More);
	virtual void __fastcall TriggerHeaderLine(char * Line, int Size);
	void __fastcall SetEMailFiles(Classes::TStrings* newValue);
	void __fastcall PrepareEMail(void);
	
public:
	__fastcall virtual TSmtpCli(Classes::TComponent* AOwner);
	__fastcall virtual ~TSmtpCli(void);
	virtual void __fastcall Data(void);
	
__published:
	__property Host ;
	__property LocalAddr ;
	__property Port ;
	__property SignOn ;
	__property Username ;
	__property Password ;
	__property AuthType ;
	__property FromName ;
	__property RcptName ;
	__property MailMessage ;
	__property HdrFrom ;
	__property HdrTo ;
	__property HdrReplyTo ;
	__property HdrReturnPath ;
	__property HdrSubject ;
	__property HdrSender ;
	__property State ;
	__property CharSet ;
	__property ContentType ;
	__property ErrorMessage ;
	__property LastResponse ;
	__property Tag ;
	__property OwnHeaders ;
	__property OnDisplay ;
	__property OnCommand ;
	__property OnResponse ;
	__property OnGetData ;
	__property OnHeaderLine ;
	__property OnProcessHeader ;
	__property OnRequestDone ;
	__property OnSessionConnected ;
	__property OnSessionClosed ;
	__property Classes::TStrings* EmailFiles = {read=FEmailFiles, write=SetEMailFiles};
	__property TSmtpAttachmentContentType OnAttachContentType = {read=FOnAttachContentType, write=FOnAttachContentType};
	__property TSmtpAttachHeader OnAttachHeader = {read=FOnAttachHeader, write=FOnAttachHeader};
};


class DELPHICLASS TSyncSmtpCli;
class PASCALIMPLEMENTATION TSyncSmtpCli : public TSmtpCli 
{
	typedef TSmtpCli inherited;
	
protected:
	int FTimeout;
	int FTimeStop;
	bool FMultiThreaded;
	virtual bool __fastcall WaitUntilReady(void);
	bool __fastcall Synchronize(TSmtpNextProc Proc);
	virtual void __fastcall TriggerGetData(int LineNum, char * MsgLine, int MaxLen, bool &More);
	
public:
	__fastcall virtual TSyncSmtpCli(Classes::TComponent* AOwner);
	virtual bool __fastcall ConnectSync(void);
	virtual bool __fastcall HeloSync(void);
	virtual bool __fastcall EhloSync(void);
	virtual bool __fastcall AuthSync(void);
	virtual bool __fastcall VrfySync(void);
	virtual bool __fastcall MailFromSync(void);
	virtual bool __fastcall RcptToSync(void);
	virtual bool __fastcall DataSync(void);
	virtual bool __fastcall QuitSync(void);
	virtual bool __fastcall RsetSync(void);
	virtual bool __fastcall AbortSync(void);
	virtual bool __fastcall OpenSync(void);
	virtual bool __fastcall MailSync(void);
	
__published:
	__property int Timeout = {read=FTimeout, write=FTimeout, nodefault};
	__property bool MultiThreaded = {read=FMultiThreaded, write=FMultiThreaded, nodefault};
public:
	#pragma option push -w-inl
	/* TSmtpCli.Destroy */ inline __fastcall virtual ~TSyncSmtpCli(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Byte SmtpCliVersion = 0xe0;
extern PACKAGE AnsiString CopyRight;
static const Word SMTP_RCV_BUF_SIZE = 0x1000;
static const Word WM_SMTP_REQUEST_DONE = 0x401;
extern PACKAGE AnsiString __fastcall Rfc822DateTime(System::TDateTime t);
extern PACKAGE void __fastcall Register(void);

}	/* namespace Smtpprot */
using namespace Smtpprot;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// SmtpProt
