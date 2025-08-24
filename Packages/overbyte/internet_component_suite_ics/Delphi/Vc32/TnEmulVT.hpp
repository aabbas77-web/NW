// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'TnEmulVT.pas' rev: 6.00

#ifndef TnEmulVTHPP
#define TnEmulVTHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <WSocket.hpp>	// Pascal unit
#include <TnOptFrm.hpp>	// Pascal unit
#include <IniFiles.hpp>	// Pascal unit
#include <TnCnx.hpp>	// Pascal unit
#include <EmulVT.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Tnemulvt
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TTnEmulVTDataAvailable)(System::TObject* Sender, char * Buffer, int &Len);

class DELPHICLASS TTnEmulVT;
class PASCALIMPLEMENTATION TTnEmulVT : public Emulvt::TEmulVT 
{
	typedef Emulvt::TEmulVT inherited;
	
protected:
	Tncnx::TTnCnx* FTnCnx;
	Word FError;
	AnsiString FIniFilename;
	AnsiString FSectionName;
	AnsiString FKeyName;
	AnsiString FHostName;
	AnsiString FPort;
	int FTag;
	bool FUpperLock;
	bool FLocalEcho;
	Classes::TNotifyEvent FOnSessionClosed;
	Classes::TNotifyEvent FOnSessionConnected;
	Classes::TNotifyEvent FOnNamesClick;
	Classes::TNotifyEvent FOnSendLoc;
	Classes::TNotifyEvent FOnTermType;
	Classes::TNotifyEvent FOnLocalEcho;
	TTnEmulVTDataAvailable FOnDataAvailable;
	bool FMouseDown;
	bool FMouseCaptured;
	int FMouseTop;
	int FMouseLeft;
	bool FFocusDrawn;
	#pragma pack(push, 1)
	Types::TRect FFocusRect;
	#pragma pack(pop)
	
	virtual void __fastcall TriggerDataAvailable(char * Buffer, int Len);
	void __fastcall TnCnxDataAvailable(Tncnx::TTnCnx* Sender, char * Buffer, int Len);
	void __fastcall TnCnxSessionClosed(Tncnx::TTnCnx* Sender, Word Erc);
	void __fastcall TnCnxSessionConnected(Tncnx::TTnCnx* Sender, Word Erc);
	void __fastcall TnCnxSendLoc(System::TObject* Sender);
	void __fastcall TnCnxTermType(System::TObject* Sender);
	void __fastcall TnCnxLocalEcho(System::TObject* Sender);
	void __fastcall Display(AnsiString Msg);
	virtual void __fastcall DoKeyBuffer(char * Buffer, int Len);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	void __fastcall SetOnEndOfRecord(Classes::TNotifyEvent Value);
	Classes::TNotifyEvent __fastcall GetOnEndOfRecord();
	void __fastcall SetLocation(AnsiString Value);
	AnsiString __fastcall GetLocation();
	void __fastcall SetHostName(AnsiString newValue);
	
public:
	void __fastcall RequestLocalEcho(bool newValue);
	bool __fastcall GetLocalEcho(void);
	__fastcall virtual TTnEmulVT(Classes::TComponent* AOwner);
	__fastcall virtual ~TTnEmulVT(void);
	void __fastcall Connect(void);
	void __fastcall Disconnect(void);
	void __fastcall EditOptions(void);
	void __fastcall RestoreOptions(void);
	bool __fastcall IsConnected(void);
	int __fastcall Send(void * Data, int Len);
	int __fastcall SendStr(AnsiString Data);
	int __fastcall GetSelTextBuf(char * Buffer, int BufSize);
	DYNAMIC void __fastcall KeyPress(char &Key);
	__property Tncnx::TTnCnx* TnConn = {read=FTnCnx};
	
__published:
	__property AnsiString IniFilename = {read=FIniFilename, write=FIniFilename};
	__property AnsiString SectionName = {read=FSectionName, write=FSectionName};
	__property AnsiString KeyName = {read=FKeyName, write=FKeyName};
	__property Word Error = {read=FError, write=FError, nodefault};
	__property AnsiString HostName = {read=FHostName, write=SetHostName};
	__property AnsiString Port = {read=FPort, write=FPort};
	__property int Tag = {read=FTag, write=FTag, nodefault};
	__property AnsiString Location = {read=GetLocation, write=SetLocation};
	__property bool UpperLock = {read=FUpperLock, write=FUpperLock, nodefault};
	__property bool LocalEcho = {read=FLocalEcho, write=FLocalEcho, nodefault};
	__property OnKeyDown ;
	__property Classes::TNotifyEvent OnSessionClosed = {read=FOnSessionClosed, write=FOnSessionClosed};
	__property Classes::TNotifyEvent OnSessionConnected = {read=FOnSessionConnected, write=FOnSessionConnected};
	__property Classes::TNotifyEvent OnEndOfRecord = {read=GetOnEndOfRecord, write=SetOnEndOfRecord};
	__property Classes::TNotifyEvent OnNamesClick = {read=FOnNamesClick, write=FOnNamesClick};
	__property Classes::TNotifyEvent OnSendLoc = {read=FOnSendLoc, write=FOnSendLoc};
	__property Classes::TNotifyEvent OnTermType = {read=FOnTermType, write=FOnTermType};
	__property Classes::TNotifyEvent OnLocalEcho = {read=FOnLocalEcho, write=FOnLocalEcho};
	__property TTnEmulVTDataAvailable OnDataAvailable = {read=FOnDataAvailable, write=FOnDataAvailable};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TTnEmulVT(HWND ParentWindow) : Emulvt::TEmulVT(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Byte TnEmultVTVersion = 0xd4;
extern PACKAGE AnsiString CopyRight;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Tnemulvt */
using namespace Tnemulvt;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// TnEmulVT
