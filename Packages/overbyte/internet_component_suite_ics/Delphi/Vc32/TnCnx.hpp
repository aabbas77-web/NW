// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'TnCnx.pas' rev: 6.00

#ifndef TnCnxHPP
#define TnCnxHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <WinSock.hpp>	// Pascal unit
#include <WSocket.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Tncnx
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TTnCnx;
typedef void __fastcall (__closure *TTnSessionConnected)(TTnCnx* Sender, Word Error);

typedef void __fastcall (__closure *TTnSessionClosed)(TTnCnx* Sender, Word Error);

typedef void __fastcall (__closure *TTnDataAvailable)(TTnCnx* Sender, char * Buffer, int Len);

typedef void __fastcall (__closure *TTnDisplay)(TTnCnx* Sender, AnsiString Str);

class PASCALIMPLEMENTATION TTnCnx : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
public:
	Wsocket::TWSocket* Socket;
	
private:
	AnsiString FPort;
	AnsiString FHost;
	AnsiString FLocation;
	AnsiString FTermType;
	bool RemoteBinMode;
	bool LocalBinMode;
	bool FLocalEcho;
	bool Spga;
	bool FTType;
	char FBuffer[2049];
	int FBufferCnt;
	HWND FWindowHandle;
	TTnSessionConnected FOnSessionConnected;
	TTnSessionClosed FOnSessionClosed;
	TTnDataAvailable FOnDataAvailable;
	TTnDisplay FOnDisplay;
	Classes::TNotifyEvent FOnEOR;
	Classes::TNotifyEvent FOnSendLoc;
	Classes::TNotifyEvent FOnTermType;
	Classes::TNotifyEvent FOnLocalEcho;
	void __fastcall WndProc(Messages::TMessage &MsgRec);
	void __fastcall SocketSessionConnected(System::TObject* Sender, Word Error);
	void __fastcall SocketSessionClosed(System::TObject* Sender, Word Error);
	void __fastcall SocketDataAvailable(System::TObject* Sender, Word Error);
	void __fastcall Display(AnsiString Str);
	void __fastcall AddChar(char Ch);
	void __fastcall ReceiveChar(char Ch);
	void __fastcall Answer(char chAns, char chOption);
	void __fastcall NegociateSubOption(AnsiString strSubOption);
	void __fastcall NegociateOption(char chAction, char chOption);
	void __fastcall FlushBuffer(void);
	Wsocket::TSocketState __fastcall GetState(void);
	
public:
	__fastcall virtual TTnCnx(Classes::TComponent* AOwner);
	__fastcall virtual ~TTnCnx(void);
	int __fastcall Send(void * Data, int Len);
	int __fastcall SendStr(AnsiString Data);
	void __fastcall Connect(void);
	bool __fastcall IsConnected(void);
	void __fastcall WillOption(char chOption);
	void __fastcall WontOption(char chOption);
	void __fastcall DontOption(char chOption);
	void __fastcall DoOption(char chOption);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	void __fastcall Close(void);
	void __fastcall Pause(void);
	void __fastcall Resume(void);
	__property Wsocket::TSocketState State = {read=GetState, nodefault};
	__property HWND Handle = {read=FWindowHandle, nodefault};
	
__published:
	__property AnsiString Port = {read=FPort, write=FPort};
	__property AnsiString Host = {read=FHost, write=FHost};
	__property AnsiString Location = {read=FLocation, write=FLocation};
	__property AnsiString TermType = {read=FTermType, write=FTermType};
	__property bool LocalEcho = {read=FLocalEcho, write=FLocalEcho, nodefault};
	__property TTnSessionConnected OnSessionConnected = {read=FOnSessionConnected, write=FOnSessionConnected};
	__property TTnSessionClosed OnSessionClosed = {read=FOnSessionClosed, write=FOnSessionClosed};
	__property TTnDataAvailable OnDataAvailable = {read=FOnDataAvailable, write=FOnDataAvailable};
	__property TTnDisplay OnDisplay = {read=FOnDisplay, write=FOnDisplay};
	__property Classes::TNotifyEvent OnEndOfRecord = {read=FOnEOR, write=FOnEOR};
	__property Classes::TNotifyEvent OnSendLoc = {read=FOnSendLoc, write=FOnSendLoc};
	__property Classes::TNotifyEvent OnTermType = {read=FOnTermType, write=FOnTermType};
	__property Classes::TNotifyEvent OnLocalEcho = {read=FOnLocalEcho, write=FOnLocalEcho};
};


//-- var, const, procedure ---------------------------------------------------
static const Byte TnCnxVersion = 0xd0;
extern PACKAGE AnsiString CopyRight;
static const char TNCH_EOR = '\xef';
static const char TNCH_SE = '\xf0';
static const char TNCH_NOP = '\xf1';
static const char TNCH_DATA_MARK = '\xf2';
static const char TNCH_BREAK = '\xf3';
static const char TNCH_IP = '\xf4';
static const char TNCH_AO = '\xf5';
static const char TNCH_AYT = '\xf6';
static const char TNCH_EC = '\xf7';
static const char TNCH_EL = '\xf8';
static const char TNCH_GA = '\xf9';
static const char TNCH_SB = '\xfa';
static const char TNCH_WILL = '\xfb';
static const char TNCH_WONT = '\xfc';
static const char TNCH_DO = '\xfd';
static const char TNCH_DONT = '\xfe';
static const char TNCH_IAC = '\xff';
static const char TN_TRANSMIT_BINARY = '\x0';
static const char TN_ECHO = '\x1';
static const char TN_RECONNECTION = '\x2';
static const char TN_SUPPRESS_GA = '\x3';
static const char TN_MSG_SZ_NEGOC = '\x4';
static const char TN_STATUS = '\x5';
static const char TN_TIMING_MARK = '\x6';
static const char TN_NOPTIONS = '\x6';
static const char TN_DET = '\x14';
static const char TN_SEND_LOC = '\x17';
static const char TN_TERMTYPE = '\x18';
static const char TN_EOR = '\x19';
static const char TN_NAWS = '\x1f';
static const char TN_TERMSPEED = '\x20';
static const char TN_TFC = '\x21';
static const char TN_XDISPLOC = '\x23';
static const char TN_EXOPL = '\xff';
static const char TN_TTYPE_SEND = '\x1';
static const char TN_TTYPE_IS = '\x0';
extern PACKAGE void __fastcall Register(void);

}	/* namespace Tncnx */
using namespace Tncnx;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// TnCnx
