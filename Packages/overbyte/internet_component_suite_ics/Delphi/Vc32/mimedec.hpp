// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'MimeDec.pas' rev: 6.00

#ifndef MimeDecHPP
#define MimeDecHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Mimedec
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TMimeDecodePartLine)(System::TObject* Sender, char * Data, int DataLen);

typedef void __fastcall (__closure *TInlineDecodeBegin)(System::TObject* Sender, AnsiString Filename);

typedef void __fastcall (__closure *TInlineDecodeLine)(System::TObject* Sender, char * Line);

typedef void __fastcall (__closure *TInlineDecodeEnd)(System::TObject* Sender, AnsiString Filename);

class DELPHICLASS TMimeDecode;
class PASCALIMPLEMENTATION TMimeDecode : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	AnsiString FFrom;
	AnsiString FDest;
	AnsiString FSubject;
	AnsiString FDate;
	AnsiString FReturnPath;
	AnsiString FEncoding;
	AnsiString FCharSet;
	AnsiString FContentType;
	AnsiString FMimeVersion;
	AnsiString FHeaderName;
	AnsiString FDisposition;
	AnsiString FFileName;
	Classes::TStrings* FHeaderLines;
	bool FIsMultipart;
	bool FEndOfMime;
	AnsiString FPartContentType;
	AnsiString FPartEncoding;
	int FPartNumber;
	bool FPartHeaderBeginSignaled;
	AnsiString FPartName;
	AnsiString FPartDisposition;
	AnsiString FPartContentID;
	AnsiString FPartFileName;
	AnsiString FPartCharset;
	AnsiString FApplicationType;
	bool FPartOpened;
	bool FHeaderFlag;
	int FLineNum;
	char *FBuffer;
	int FBufferSize;
	char *FCurrentData;
	AnsiString FBoundary;
	bool FUUProcessFlag;
	void __fastcall (__closure *FNext)(void);
	Classes::TStream* FDestStream;
	Classes::TNotifyEvent FOnHeaderBegin;
	Classes::TNotifyEvent FOnHeaderLine;
	Classes::TNotifyEvent FOnHeaderEnd;
	Classes::TNotifyEvent FOnPartHeaderBegin;
	Classes::TNotifyEvent FOnPartHeaderLine;
	Classes::TNotifyEvent FOnPartHeaderEnd;
	Classes::TNotifyEvent FOnPartBegin;
	TMimeDecodePartLine FOnPartLine;
	Classes::TNotifyEvent FOnPartEnd;
	Classes::TNotifyEvent FOnMessageEnd;
	AnsiString cUUFilename;
	Classes::TStringList* FEmbeddedBoundary;
	bool cIsEmbedded;
	TInlineDecodeBegin FInlineBegin;
	TInlineDecodeLine FInlineLine;
	TInlineDecodeEnd FInlineEnd;
	virtual void __fastcall TriggerHeaderBegin(void);
	virtual void __fastcall TriggerHeaderLine(void);
	virtual void __fastcall TriggerHeaderEnd(void);
	virtual void __fastcall TriggerPartHeaderBegin(void);
	virtual void __fastcall TriggerPartHeaderLine(void);
	virtual void __fastcall TriggerPartHeaderEnd(void);
	virtual void __fastcall TriggerPartBegin(void);
	virtual void __fastcall TriggerPartLine(char * Data, int DataLen);
	virtual void __fastcall TriggerPartEnd(void);
	virtual void __fastcall TriggerMessageEnd(void);
	void __fastcall ProcessLineUUDecode(void);
	bool __fastcall UUProcessLine(char * FCurrentData);
	void __fastcall ProcessLineQuotedPrintable(void);
	void __fastcall ProcessHeaderLine(void);
	void __fastcall ProcessPartHeaderLine(void);
	void __fastcall ProcessPartLine(void);
	void __fastcall ProcessWaitBoundary(void);
	void __fastcall ProcessMessageLine(void);
	void __fastcall PreparePart(void);
	void __fastcall PrepareNextPart(void);
	void __fastcall ProcessDecodedLine(char * Line, int Len);
	void __fastcall InternalDecodeStream(Classes::TStream* aStream);
	void __fastcall MessageBegin(void);
	void __fastcall MessageEnd(void);
	
public:
	__fastcall virtual TMimeDecode(Classes::TComponent* AOwner);
	__fastcall virtual ~TMimeDecode(void);
	void __fastcall DecodeFile(AnsiString FileName);
	void __fastcall DecodeStream(Classes::TStream* aStream);
	void __fastcall ProcessLineBase64(void);
	__property AnsiString From = {read=FFrom};
	__property AnsiString Dest = {read=FDest};
	__property AnsiString Subject = {read=FSubject};
	__property AnsiString Date = {read=FDate};
	__property AnsiString ReturnPath = {read=FReturnPath};
	__property AnsiString ContentType = {read=FContentType};
	__property AnsiString Encoding = {read=FEncoding};
	__property AnsiString Charset = {read=FCharSet};
	__property AnsiString MimeVersion = {read=FMimeVersion};
	__property AnsiString HeaderName = {read=FHeaderName};
	__property AnsiString Disposition = {read=FDisposition};
	__property AnsiString FileName = {read=FFileName};
	__property Classes::TStrings* HeaderLines = {read=FHeaderLines};
	__property bool IsMultipart = {read=FIsMultipart, nodefault};
	__property bool EndOfMime = {read=FEndOfMime, nodefault};
	__property AnsiString PartContentType = {read=FPartContentType};
	__property AnsiString PartEncoding = {read=FPartEncoding};
	__property AnsiString PartName = {read=FPartName};
	__property AnsiString PartDisposition = {read=FPartDisposition};
	__property AnsiString PartContentID = {read=FPartContentID};
	__property AnsiString PartFileName = {read=FPartFileName};
	__property AnsiString PartCharset = {read=FPartCharset};
	__property AnsiString ApplicationType = {read=FApplicationType};
	__property int PartNumber = {read=FPartNumber, nodefault};
	__property char * CurrentData = {read=FCurrentData, write=FCurrentData};
	__property Classes::TStream* DestStream = {read=FDestStream, write=FDestStream};
	
__published:
	__property Classes::TNotifyEvent OnHeaderBegin = {read=FOnHeaderBegin, write=FOnHeaderBegin};
	__property Classes::TNotifyEvent OnHeaderLine = {read=FOnHeaderLine, write=FOnHeaderLine};
	__property Classes::TNotifyEvent OnHeaderEnd = {read=FOnHeaderEnd, write=FOnHeaderEnd};
	__property Classes::TNotifyEvent OnPartHeaderBegin = {read=FOnPartHeaderBegin, write=FOnPartHeaderBegin};
	__property Classes::TNotifyEvent OnPartHeaderLine = {read=FOnPartHeaderLine, write=FOnPartHeaderLine};
	__property Classes::TNotifyEvent OnPartHeaderEnd = {read=FOnPartHeaderEnd, write=FOnPartHeaderEnd};
	__property Classes::TNotifyEvent OnPartBegin = {read=FOnPartBegin, write=FOnPartBegin};
	__property TMimeDecodePartLine OnPartLine = {read=FOnPartLine, write=FOnPartLine};
	__property Classes::TNotifyEvent OnPartEnd = {read=FOnPartEnd, write=FOnPartEnd};
	__property Classes::TNotifyEvent OnMessageEnd = {read=FOnMessageEnd, write=FOnMessageEnd};
	__property TInlineDecodeBegin OnInlineDecodeBegin = {read=FInlineBegin, write=FInlineBegin};
	__property TInlineDecodeLine OnInlineDecodeLine = {read=FInlineLine, write=FInlineLine};
	__property TInlineDecodeEnd OnInlineDecodeEnd = {read=FInlineEnd, write=FInlineEnd};
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint MimeDecodeVersion = 0x79;
extern PACKAGE AnsiString CopyRight;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Mimedec */
using namespace Mimedec;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// MimeDec
