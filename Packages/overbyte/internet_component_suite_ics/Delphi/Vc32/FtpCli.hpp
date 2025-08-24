// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FtpCli.pas' rev: 6.00

#ifndef FtpCliHPP
#define FtpCliHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <WSocket.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Ftpcli
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TFtpOption { ftpAcceptLF, ftpNoAutoResumeAt };
#pragma option pop

typedef Set<TFtpOption, ftpAcceptLF, ftpNoAutoResumeAt>  TFtpOptions;

#pragma option push -b-
enum TFtpState { ftpNotConnected, ftpReady, ftpInternalReady, ftpDnsLookup, ftpConnected, ftpAbort, ftpInternalAbort, ftpWaitingBanner, ftpWaitingResponse };
#pragma option pop

#pragma option push -b-
enum TFtpRequest { ftpNone, ftpOpenAsync, ftpUserAsync, ftpPassAsync, ftpCwdAsync, ftpConnectAsync, ftpReceiveAsync, ftpDirAsync, ftpLsAsync, ftpPortAsync, ftpGetAsync, ftpDirectoryAsync, ftpListAsync, ftpSystemAsync, ftpSystAsync, ftpQuitAsync, ftpAbortXferAsync, ftpSizeAsync, ftpPutAsync, ftpAppendAsync, ftpFileSizeAsync, ftpRqAbort, ftpMkdAsync, ftpRmdAsync, ftpRenameAsync, ftpDeleAsync, ftpRenAsync, ftpRenToAsync, ftpRenFromAsync, ftpDeleteAsync, ftpMkdirAsync, ftpRmdirAsync, ftpPwdAsync, ftpQuoteAsync, ftpCDupAsync, ftpDoQuoteAsync, ftpTransmitAsync, ftpTypeSetAsync, ftpRestAsync, ftpRestGetAsync, ftpRestartGetAsync, ftpRestPutAsync, ftpRestartPutAsync };
#pragma option pop

#pragma option push -b-
enum TFtpFct { ftpFctNone, ftpFctOpen, ftpFctUser, ftpFctPass, ftpFctCwd, ftpFctSize, ftpFctMkd, ftpFctRmd, ftpFctRenFrom, ftpFctRenTo, ftpFctGet, ftpFctDir, ftpFctQuit, ftpFctSyst, ftpFctDele, ftpFctPwd, ftpFctQuote, ftpFctPut, ftpFctTypeSet, ftpFctRest, ftpFctCDup, ftpFctLs, ftpFctAppend, ftpFctPort, ftpFctAbortXfer };
#pragma option pop

typedef Set<TFtpFct, ftpFctNone, ftpFctAbortXfer>  TFtpFctSet;

#pragma option push -b-
enum TFtpShareMode { ftpShareCompat, ftpShareExclusive, ftpShareDenyWrite, ftpShareDenyRead, ftpShareDenyNone };
#pragma option pop

#pragma option push -b-
enum TFtpDisplayFileMode { ftpLineByLine, ftpBinary };
#pragma option pop

#pragma option push -b-
enum TFtpConnectionType { ftpDirect, ftpProxy, ftpSocks4, ftpSocks4A, ftpSocks5 };
#pragma option pop

typedef void __fastcall (__closure *TFtpDisplay)(System::TObject* Sender, AnsiString &Msg);

typedef void __fastcall (__closure *TFtpProgress)(System::TObject* Sender, int Count, bool &Abort);

typedef void __fastcall (__closure *TFtpCommand)(System::TObject* Sender, AnsiString &Cmd);

typedef void __fastcall (__closure *TFtpRequestDone)(System::TObject* Sender, TFtpRequest RqType, Word Error);

typedef void __fastcall (__closure *TFtpReadyToTransmit)(System::TObject* Sender, bool &bCancel);

typedef void __fastcall (__closure *TFtpNextProc)(void);

class DELPHICLASS FtpException;
class PASCALIMPLEMENTATION FtpException : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall FtpException(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall FtpException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall FtpException(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall FtpException(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall FtpException(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall FtpException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall FtpException(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall FtpException(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~FtpException(void) { }
	#pragma option pop
	
};


class DELPHICLASS TCustomFtpCli;
class PASCALIMPLEMENTATION TCustomFtpCli : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
protected:
	HWND FWindowHandle;
	AnsiString FHostName;
	AnsiString FPort;
	AnsiString FLocalAddr;
	AnsiString FUserName;
	AnsiString FPassWord;
	AnsiString FLocalFileName;
	AnsiString FHostFileName;
	AnsiString FHostDirName;
	AnsiString FDnsResult;
	char FType;
	Word FShareMode;
	TFtpDisplayFileMode FDisplayFileMode;
	TFtpConnectionType FConnectionType;
	AnsiString FProxyServer;
	AnsiString FProxyPort;
	bool FAppendFlag;
	bool FDisplayFileFlag;
	Wsocket::TWSocket* FControlSocket;
	Wsocket::TWSocket* FDataSocket;
	int FStartTime;
	int FStopTime;
	TFtpState FState;
	int FStatusCode;
	int FRequestResult;
	TFtpFctSet FFctSet;
	TFtpFct FFctPrv;
	int FHighLevelResult;
	bool FHighLevelFlag;
	bool FRestartFlag;
	TFtpOptions FOptions;
	TFtpDisplay FOnDisplay;
	TFtpDisplay FOnDisplayFile;
	TFtpDisplay FOnError;
	TFtpCommand FOnCommand;
	Classes::TNotifyEvent FOnResponse;
	Wsocket::TSessionConnected FOnSessionConnected;
	Wsocket::TSessionClosed FOnSessionClosed;
	Classes::TNotifyEvent FOnStateChange;
	TFtpRequestDone FOnRequestDone;
	TFtpProgress FOnProgress;
	TFtpReadyToTransmit FOnReadyToTransmit;
	Wsocket::TBgExceptionEvent FOnBgException;
	Classes::TStream* FLocalStream;
	TFtpRequest FRequestType;
	bool FRequestDoneFlag;
	char FReceiveBuffer[4096];
	int FReceiveLen;
	AnsiString FLastResponse;
	AnsiString FLastResponseSave;
	AnsiString FPasvResponse;
	int FStatusCodeSave;
	AnsiString FErrorMessage;
	Word FError;
	AnsiString FGetCommand;
	bool FConnected;
	char FSendBuffer[1460];
	int FByteCount;
	int FSizeResult;
	AnsiString FDirResult;
	int FResumeAt;
	TFtpNextProc FNext;
	TFtpNextProc FWhenConnected;
	TFtpNextProc FDoneAsync;
	int FOkResponses[16];
	TFtpNextProc FNextRequest;
	bool FServerSaidDone;
	bool FFileReceived;
	bool FFileSent;
	bool FPassive;
	bool FEofFlag;
	bool FStorAnswerRcvd;
	bool FPutSessionOpened;
	bool FStreamFlag;
	void __fastcall SetErrorMessage(void);
	void __fastcall DataSocketGetDataAvailable(System::TObject* Sender, Word Error);
	void __fastcall DataSocketGetSessionConnected(System::TObject* Sender, Word Error);
	void __fastcall DataSocketPutSessionConnected(System::TObject* Sender, Word Error);
	void __fastcall DataSocketGetSessionAvailable(System::TObject* Sender, Word Error);
	void __fastcall DataSocketGetSessionClosed(System::TObject* Sender, Word Error);
	void __fastcall DataSocketPutDataAvailable(System::TObject* Sender, Word Error);
	void __fastcall DataSocketPutDataSent(System::TObject* Sender, Word Error);
	void __fastcall DataSocketPutSessionAvailable(System::TObject* Sender, Word Error);
	void __fastcall DataSocketPutSessionClosed(System::TObject* Sender, Word Error);
	virtual void __fastcall SendCommand(AnsiString Cmd);
	virtual void __fastcall TriggerDisplay(AnsiString Msg);
	virtual void __fastcall TriggerReadyToTransmit(bool &bCancel);
	virtual void __fastcall TriggerDisplayFile(AnsiString Msg);
	virtual void __fastcall TriggerError(AnsiString Msg);
	void __fastcall DisplayLastResponse(void);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	virtual bool __fastcall Progress(void);
	void __fastcall ControlSocketDnsLookupDone(System::TObject* Sender, Word Error);
	void __fastcall ControlSocketSessionConnected(System::TObject* Sender, Word Error);
	void __fastcall ControlSocketDataAvailable(System::TObject* Sender, Word Error);
	void __fastcall ControlSocketSessionClosed(System::TObject* Sender, Word Error);
	void __fastcall TriggerRequestDone(Word Error);
	void __fastcall TriggerStateChange(void);
	void __fastcall StateChange(TFtpState NewState);
	virtual void __fastcall PortAsync(void);
	void __fastcall DoneQuitAsync(void);
	void __fastcall ExecAsync(TFtpRequest RqType, AnsiString Cmd, const Word * OkResponses, const int OkResponses_Size, TFtpNextProc DoneAsync);
	void __fastcall NextExecAsync(void);
	void __fastcall DoGetAsync(TFtpRequest RqType);
	void __fastcall Next1GetAsync(void);
	void __fastcall Next2GetAsync(void);
	void __fastcall Next3GetAsync(void);
	void __fastcall Next1PutAsync(void);
	void __fastcall Next2PutAsync(void);
	void __fastcall Next3PutAsync(void);
	void __fastcall DoHighLevelAsync(void);
	void __fastcall DoPutAppendAsync(void);
	void __fastcall HighLevelAsync(TFtpRequest RqType, TFtpFctSet Fcts);
	void __fastcall HandleError(const AnsiString Msg);
	bool __fastcall CheckReady(void);
	virtual void __fastcall TransfertStats(void);
	void __fastcall ExtractMoreResults(void);
	void __fastcall SetBinary(bool Value);
	bool __fastcall GetBinary(void);
	bool __fastcall GetConnected(void);
	void __fastcall SetShareMode(TFtpShareMode newValue);
	TFtpShareMode __fastcall GetShareMode(void);
	void __fastcall SetDisplayFileMode(TFtpDisplayFileMode NewValue);
	TFtpDisplayFileMode __fastcall GetDisplayFileMode(void);
	void __fastcall SetConnectionType(TFtpConnectionType NewValue);
	TFtpConnectionType __fastcall GetConnectionType(void);
	void __fastcall SetSocksPassword(AnsiString NewValue);
	AnsiString __fastcall GetSocksPassword();
	void __fastcall SetSocksPort(AnsiString NewValue);
	AnsiString __fastcall GetSocksPort();
	void __fastcall SetSocksServer(AnsiString NewValue);
	AnsiString __fastcall GetSocksServer();
	void __fastcall SetSocksUserCode(AnsiString NewValue);
	AnsiString __fastcall GetSocksUserCode();
	void __fastcall SetPassive(bool NewValue);
	virtual void __fastcall WndProc(Messages::TMessage &MsgRec);
	virtual HWND __fastcall FtpCliAllocateHWnd(Wsocket::TWndMethod Method);
	virtual void __fastcall FtpCliDeallocateHWnd(HWND WHandle);
	virtual void __fastcall HandleBackGroundException(Sysutils::Exception* E);
	MESSAGE void __fastcall WMFtpRequestDone(Messages::TMessage &msg);
	MESSAGE void __fastcall WMFtpSendData(Messages::TMessage &msg);
	void __fastcall DestroyLocalStream(void);
	void __fastcall SetLocalStream(Classes::TStream* Stream);
	void __fastcall SetLocalFileName(AnsiString FileName);
	
public:
	__fastcall virtual TCustomFtpCli(Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomFtpCli(void);
	virtual void __fastcall OpenAsync(void);
	virtual void __fastcall UserAsync(void);
	virtual void __fastcall PassAsync(void);
	virtual void __fastcall ConnectAsync(void);
	virtual void __fastcall QuitAsync(void);
	virtual void __fastcall AbortAsync(void);
	virtual void __fastcall GetAsync(void);
	virtual void __fastcall ExecGetAsync(void);
	virtual void __fastcall ReceiveAsync(void);
	virtual void __fastcall PutAsync(void);
	virtual void __fastcall ExecPutAsync(void);
	virtual void __fastcall TransmitAsync(void);
	virtual void __fastcall AppendAsync(void);
	virtual void __fastcall ExecAppendAsync(void);
	virtual void __fastcall AppendFileAsync(void);
	virtual void __fastcall ExecDirAsync(void);
	virtual void __fastcall DirAsync(void);
	virtual void __fastcall ExecLsAsync(void);
	virtual void __fastcall LsAsync(void);
	virtual void __fastcall TypeSetAsync(void);
	virtual void __fastcall TypeBinaryAsync(void);
	virtual void __fastcall TypeAsciiAsync(void);
	virtual void __fastcall PwdAsync(void);
	virtual void __fastcall CwdAsync(void);
	virtual void __fastcall CDupAsync(void);
	virtual void __fastcall DirectoryAsync(void);
	virtual void __fastcall ListAsync(void);
	virtual void __fastcall SystAsync(void);
	virtual void __fastcall SystemAsync(void);
	virtual void __fastcall SizeAsync(void);
	virtual void __fastcall FileSizeAsync(void);
	virtual void __fastcall MkdAsync(void);
	virtual void __fastcall MkdirAsync(void);
	virtual void __fastcall RmdAsync(void);
	virtual void __fastcall RmdirAsync(void);
	virtual void __fastcall DeleAsync(void);
	virtual void __fastcall DeleteAsync(void);
	virtual void __fastcall RenFromAsync(void);
	virtual void __fastcall RenToAsync(void);
	virtual void __fastcall RenAsync(void);
	virtual void __fastcall RenameAsync(void);
	virtual void __fastcall QuoteAsync(void);
	virtual void __fastcall DoQuoteAsync(void);
	virtual void __fastcall AbortXferAsync(void);
	virtual void __fastcall RestAsync(void);
	virtual void __fastcall RestGetAsync(void);
	virtual void __fastcall RestartGetAsync(void);
	virtual void __fastcall RestPutAsync(void);
	virtual void __fastcall RestartPutAsync(void);
	__property HWND Handle = {read=FWindowHandle, nodefault};
	__property AnsiString LastResponse = {read=FLastResponse};
	__property AnsiString ErrorMessage = {read=FErrorMessage};
	__property AnsiString DnsResult = {read=FDnsResult};
	__property int SizeResult = {read=FSizeResult, nodefault};
	__property AnsiString DirResult = {read=FDirResult};
	__property Wsocket::TWSocket* ControlSocket = {read=FControlSocket};
	__property Wsocket::TWSocket* DataSocket = {read=FDataSocket};
	__property bool Connected = {read=GetConnected, nodefault};
	__property int StatusCode = {read=FStatusCode, nodefault};
	__property int ByteCount = {read=FByteCount, nodefault};
	__property TFtpState State = {read=FState, nodefault};
	__property TFtpRequest RequestType = {read=FRequestType, nodefault};
	__property TFtpOptions Options = {read=FOptions, write=FOptions, nodefault};
	__property Classes::TStream* LocalStream = {read=FLocalStream, write=SetLocalStream};
	__property int ResumeAt = {read=FResumeAt, write=FResumeAt, nodefault};
	__property AnsiString HostName = {read=FHostName, write=FHostName};
	__property AnsiString Port = {read=FPort, write=FPort};
	__property AnsiString LocalAddr = {read=FLocalAddr, write=FLocalAddr};
	__property AnsiString UserName = {read=FUserName, write=FUserName};
	__property AnsiString PassWord = {read=FPassWord, write=FPassWord};
	__property AnsiString HostDirName = {read=FHostDirName, write=FHostDirName};
	__property AnsiString HostFileName = {read=FHostFileName, write=FHostFileName};
	__property AnsiString LocalFileName = {read=FLocalFileName, write=SetLocalFileName};
	__property bool DisplayFileFlag = {read=FDisplayFileFlag, write=FDisplayFileFlag, nodefault};
	__property bool Binary = {read=GetBinary, write=SetBinary, nodefault};
	__property bool Passive = {read=FPassive, write=SetPassive, nodefault};
	__property TFtpShareMode ShareMode = {read=GetShareMode, write=SetShareMode, nodefault};
	__property TFtpDisplayFileMode DisplayFileMode = {read=GetDisplayFileMode, write=SetDisplayFileMode, nodefault};
	__property TFtpConnectionType ConnectionType = {read=GetConnectionType, write=SetConnectionType, nodefault};
	__property AnsiString ProxyServer = {read=FProxyServer, write=FProxyServer};
	__property AnsiString ProxyPort = {read=FProxyPort, write=FProxyPort};
	__property AnsiString SocksPassword = {read=GetSocksPassword, write=SetSocksPassword};
	__property AnsiString SocksPort = {read=GetSocksPort, write=SetSocksPort};
	__property AnsiString SocksServer = {read=GetSocksServer, write=SetSocksServer};
	__property AnsiString SocksUserCode = {read=GetSocksUserCode, write=SetSocksUserCode};
	__property TFtpDisplay OnDisplay = {read=FOnDisplay, write=FOnDisplay};
	__property TFtpDisplay OnDisplayFile = {read=FOnDisplayFile, write=FOnDisplayFile};
	__property TFtpDisplay OnError = {read=FOnError, write=FOnError};
	__property TFtpCommand OnCommand = {read=FOnCommand, write=FOnCommand};
	__property Classes::TNotifyEvent OnResponse = {read=FOnResponse, write=FOnResponse};
	__property TFtpProgress OnProgress = {read=FOnProgress, write=FOnProgress};
	__property Wsocket::TSessionConnected OnSessionConnected = {read=FOnSessionConnected, write=FOnSessionConnected};
	__property Wsocket::TSessionClosed OnSessionClosed = {read=FOnSessionClosed, write=FOnSessionClosed};
	__property TFtpRequestDone OnRequestDone = {read=FOnRequestDone, write=FOnRequestDone};
	__property Classes::TNotifyEvent OnStateChange = {read=FOnStateChange, write=FOnStateChange};
	__property TFtpReadyToTransmit OnReadyToTransmit = {read=FOnReadyToTransmit, write=FOnReadyToTransmit};
	__property Wsocket::TBgExceptionEvent OnBgException = {read=FOnBgException, write=FOnBgException};
};


class DELPHICLASS TFtpClient;
class PASCALIMPLEMENTATION TFtpClient : public TCustomFtpCli 
{
	typedef TCustomFtpCli inherited;
	
protected:
	int FTimeout;
	int FTimeStop;
	bool FMultiThreaded;
	bool FTerminated;
	Classes::TNotifyEvent FOnMessagePump;
	virtual bool __fastcall Progress(void);
	virtual bool __fastcall Synchronize(TFtpNextProc Proc);
	virtual bool __fastcall WaitUntilReady(void);
	
public:
	__fastcall virtual TFtpClient(Classes::TComponent* AOwner);
	void __fastcall MessagePump(void);
	bool __fastcall Open(void);
	bool __fastcall User(void);
	bool __fastcall Pass(void);
	bool __fastcall Connect(void);
	bool __fastcall Cwd(void);
	bool __fastcall Pwd(void);
	bool __fastcall CDup(void);
	bool __fastcall TypeSet(void);
	bool __fastcall TypeBinary(void);
	bool __fastcall TypeAscii(void);
	bool __fastcall Get(void);
	bool __fastcall Put(void);
	bool __fastcall RestPut(void);
	bool __fastcall RestartPut(void);
	bool __fastcall Quit(void);
	bool __fastcall Abort(void);
	bool __fastcall Receive(void);
	bool __fastcall Transmit(void);
	bool __fastcall Append(void);
	bool __fastcall AppendFile(void);
	bool __fastcall Dir(void);
	bool __fastcall Directory(void);
	bool __fastcall Ls(void);
	bool __fastcall List(void);
	bool __fastcall Mkd(void);
	bool __fastcall Mkdir(void);
	bool __fastcall Ren(void);
	bool __fastcall Rename(void);
	bool __fastcall Dele(void);
	bool __fastcall Delete(void);
	bool __fastcall Rmd(void);
	bool __fastcall Rmdir(void);
	bool __fastcall Syst(void);
	bool __fastcall System(void);
	bool __fastcall Size(void);
	bool __fastcall FileSize(void);
	bool __fastcall Quote(void);
	bool __fastcall DoQuote(void);
	bool __fastcall AbortXfer(void);
	bool __fastcall RestGet(void);
	bool __fastcall RestartGet(void);
	
__published:
	__property int Timeout = {read=FTimeout, write=FTimeout, nodefault};
	__property bool MultiThreaded = {read=FMultiThreaded, write=FMultiThreaded, nodefault};
	__property HostName ;
	__property Port ;
	__property LocalAddr ;
	__property UserName ;
	__property PassWord ;
	__property HostDirName ;
	__property HostFileName ;
	__property LocalFileName ;
	__property DisplayFileFlag ;
	__property Binary ;
	__property ErrorMessage ;
	__property ShareMode ;
	__property Options ;
	__property ConnectionType ;
	__property ProxyServer ;
	__property SocksPassword ;
	__property SocksPort ;
	__property SocksServer ;
	__property SocksUserCode ;
	__property OnDisplay ;
	__property OnDisplayFile ;
	__property OnCommand ;
	__property OnResponse ;
	__property OnProgress ;
	__property OnSessionConnected ;
	__property OnSessionClosed ;
	__property OnRequestDone ;
	__property OnStateChange ;
	__property OnReadyToTransmit ;
	__property OnBgException ;
public:
	#pragma option push -w-inl
	/* TCustomFtpCli.Destroy */ inline __fastcall virtual ~TFtpClient(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Word FtpCliVersion = 0x118;
extern PACKAGE AnsiString CopyRight;
static const Word BLOCK_SIZE = 0x5b4;
static const Word WM_FTP_REQUEST_DONE = 0x401;
static const Word WM_FTP_SENDDATA = 0x402;
static const Word FTP_RCV_BUF_SIZE = 0x1000;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Ftpcli */
using namespace Ftpcli;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FtpCli
