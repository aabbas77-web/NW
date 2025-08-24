// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'MSACM.pas' rev: 6.00

#ifndef MSACMHPP
#define MSACMHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <MMSystem.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Msacm
{
//-- type declarations -------------------------------------------------------
struct TWAVEFILTER;
typedef TWAVEFILTER *PWAVEFILTER;

#pragma pack(push, 1)
struct TWAVEFILTER
{
	unsigned cbStruct;
	unsigned dwFilterTag;
	unsigned fdwFilter;
	unsigned dwReserved[6];
} ;
#pragma pack(pop)

typedef unsigned HACMDRIVERID;

typedef unsigned *PHACMDRIVERID;

typedef unsigned HACMDRIVER;

typedef unsigned *PHACMDRIVER;

typedef unsigned HACMSTREAM;

typedef unsigned *PHACMSTREAM;

typedef unsigned HACMOBJ;

typedef unsigned *PHACMOBJ;

typedef BOOL __stdcall (*ACMDRIVERENUMCB)(unsigned hadid, unsigned dwInstance, unsigned fdwSupport);

typedef int __stdcall (*ACMDRIVERPROC)(unsigned _0, unsigned _1, unsigned _2, int _3, int _4);

typedef ACMDRIVERPROC *LPACMDRIVERPROC;

struct TACMDRIVERDETAILSA;
typedef TACMDRIVERDETAILSA *PACMDRIVERDETAILSA;

#pragma pack(push, 1)
struct TACMDRIVERDETAILSA
{
	unsigned cbStruct;
	unsigned fccType;
	unsigned fccComp;
	Word wMid;
	Word wPid;
	unsigned vdwACM;
	unsigned vdwDriver;
	unsigned fdwSupport;
	unsigned cFormatTags;
	unsigned cFilterTags;
	HICON hicon;
	char szShortName[32];
	char szLongName[128];
	char szCopyright[80];
	char szLicensing[128];
	char szFeatures[512];
} ;
#pragma pack(pop)

struct TACMDRIVERDETAILSW;
typedef TACMDRIVERDETAILSW *PACMDRIVERDETAILSW;

#pragma pack(push, 1)
struct TACMDRIVERDETAILSW
{
	unsigned cbStruct;
	unsigned fccType;
	unsigned fccComp;
	Word wMid;
	Word wPid;
	unsigned vdwACM;
	unsigned vdwDriver;
	unsigned fdwSupport;
	unsigned cFormatTags;
	unsigned cFilterTags;
	HICON hicon;
	wchar_t szShortName[32];
	wchar_t szLongName[128];
	wchar_t szCopyright[80];
	wchar_t szLicensing[128];
	wchar_t szFeatures[512];
} ;
#pragma pack(pop)

typedef TACMDRIVERDETAILSA  TACMDRIVERDETAILS;

typedef TACMDRIVERDETAILSA *PACMDRIVERDETAILS;

struct TACMFORMATTAGDETAILSA;
typedef TACMFORMATTAGDETAILSA *PACMFORMATTAGDETAILSA;

#pragma pack(push, 1)
struct TACMFORMATTAGDETAILSA
{
	unsigned cbStruct;
	unsigned dwFormatTagIndex;
	unsigned dwFormatTag;
	unsigned cbFormatSize;
	unsigned fdwSupport;
	unsigned cStandardFormats;
	char szFormatTag[48];
} ;
#pragma pack(pop)

struct TACMFORMATTAGDETAILSW;
typedef TACMFORMATTAGDETAILSW *PACMFORMATTAGDETAILSW;

#pragma pack(push, 1)
struct TACMFORMATTAGDETAILSW
{
	unsigned cbStruct;
	unsigned dwFormatTagIndex;
	unsigned dwFormatTag;
	unsigned cbFormatSize;
	unsigned fdwSupport;
	unsigned cStandardFormats;
	wchar_t szFormatTag[48];
} ;
#pragma pack(pop)

typedef TACMFORMATTAGDETAILSA  TACMFORMATTAGDETAILS;

typedef TACMFORMATTAGDETAILSA *PACMFORMATTAGDETAILS;

typedef BOOL __stdcall (*ACMFORMATTAGENUMCBA)(unsigned hadid, const TACMFORMATTAGDETAILSA &paftd, unsigned dwInstance, unsigned fdwSupport);

typedef BOOL __stdcall (*ACMFORMATTAGENUMCBW)(unsigned hadid, const TACMFORMATTAGDETAILSW &paftd, unsigned dwInstance, unsigned fdwSupport);

typedef BOOL __stdcall (*ACMFORMATTAGENUMCB)(unsigned hadid, const TACMFORMATTAGDETAILSA &paftd, unsigned dwInstance, unsigned fdwSupport);

struct TACMFORMATDETAILSA;
typedef TACMFORMATDETAILSA *PACMFORMATDETAILSA;

#pragma pack(push, 1)
struct TACMFORMATDETAILSA
{
	unsigned cbStruct;
	unsigned dwFormatIndex;
	unsigned dwFormatTag;
	unsigned fdwSupport;
	tWAVEFORMATEX *pwfx;
	unsigned cbwfx;
	char szFormat[128];
} ;
#pragma pack(pop)

struct TACMFORMATDETAILSW;
typedef TACMFORMATDETAILSW *PACMFORMATDETAILSW;

#pragma pack(push, 1)
struct TACMFORMATDETAILSW
{
	unsigned cbStruct;
	unsigned dwFormatIndex;
	unsigned dwFormatTag;
	unsigned fdwSupport;
	tWAVEFORMATEX *pwfx;
	unsigned cbwfx;
	wchar_t szFormat[128];
} ;
#pragma pack(pop)

typedef TACMFORMATDETAILSA *PACMFORMATDETAILS;

typedef TACMFORMATDETAILSA  TACMFORMATDETAILS;

typedef BOOL __stdcall (*ACMFORMATENUMCBA)(unsigned hadid, const TACMFORMATDETAILSA &pafd, unsigned dwInstance, unsigned fdwSupport);

typedef BOOL __stdcall (*ACMFORMATENUMCBW)(unsigned hadid, const TACMFORMATDETAILSW &pafd, unsigned dwInstance, unsigned fdwSupport);

typedef BOOL __stdcall (*ACMFORMATENUMCB)(unsigned hadid, const TACMFORMATDETAILSA &pafd, unsigned dwInstance, unsigned fdwSupport);

typedef unsigned __stdcall (*ACMFORMATCHOOSEHOOKPROCA)(HWND hwnd, unsigned uMsg, int wParam, int lParam);

typedef unsigned __stdcall (*ACMFORMATCHOOSEHOOKPROCW)(HWND hwnd, unsigned uMsg, int wParam, int lParam);

typedef unsigned __stdcall (*ACMFORMATCHOOSEHOOKPROC)(HWND hwnd, unsigned uMsg, int wParam, int lParam);

struct TACMFORMATCHOOSEA;
typedef TACMFORMATCHOOSEA *PACMFORMATCHOOSEA;

#pragma pack(push, 1)
struct TACMFORMATCHOOSEA
{
	unsigned cbStruct;
	unsigned fdwStyle;
	HWND hwndOwner;
	tWAVEFORMATEX *pwfx;
	unsigned cbwfx;
	char *pszTitle;
	char szFormatTag[48];
	char szFormat[128];
	char *pszName;
	unsigned cchName;
	unsigned fdwEnum;
	tWAVEFORMATEX *pwfxEnum;
	unsigned hInstance;
	char *pszTemplateName;
	int lCustData;
	ACMFORMATCHOOSEHOOKPROCA pfnHook;
} ;
#pragma pack(pop)

struct TACMFORMATCHOOSEW;
typedef TACMFORMATCHOOSEW *PACMFORMATCHOOSEW;

#pragma pack(push, 1)
struct TACMFORMATCHOOSEW
{
	unsigned cbStruct;
	unsigned fdwStyle;
	HWND hwndOwner;
	tWAVEFORMATEX *pwfx;
	unsigned cbwfx;
	wchar_t *pszTitle;
	wchar_t szFormatTag[48];
	wchar_t szFormat[128];
	wchar_t *pszName;
	unsigned cchName;
	unsigned fdwEnum;
	tWAVEFORMATEX *pwfxEnum;
	unsigned hInstance;
	wchar_t *pszTemplateName;
	int lCustData;
	ACMFORMATCHOOSEHOOKPROCW pfnHook;
} ;
#pragma pack(pop)

typedef TACMFORMATCHOOSEA  TACMFORMATCHOOSE;

typedef TACMFORMATCHOOSEA *PACMFORMATCHOOSE;

struct TACMFILTERTAGDETAILSA;
typedef TACMFILTERTAGDETAILSA *PACMFILTERTAGDETAILSA;

#pragma pack(push, 1)
struct TACMFILTERTAGDETAILSA
{
	unsigned cbStruct;
	unsigned dwFilterTagIndex;
	unsigned dwFilterTag;
	unsigned cbFilterSize;
	unsigned fdwSupport;
	unsigned cStandardFilters;
	char szFilterTag[48];
} ;
#pragma pack(pop)

struct TACMFILTERTAGDETAILSW;
typedef TACMFILTERTAGDETAILSW *PACMFILTERTAGDETAILSW;

#pragma pack(push, 1)
struct TACMFILTERTAGDETAILSW
{
	unsigned cbStruct;
	unsigned dwFilterTagIndex;
	unsigned dwFilterTag;
	unsigned cbFilterSize;
	unsigned fdwSupport;
	unsigned cStandardFilters;
	wchar_t szFilterTag[48];
} ;
#pragma pack(pop)

typedef TACMFILTERTAGDETAILSA *PACMFILTERTAGDETAILS;

typedef TACMFILTERTAGDETAILSA  TACMFILTERTAGDETAILS;

typedef BOOL __stdcall (*ACMFILTERTAGENUMCBA)(unsigned hadid, const TACMFILTERTAGDETAILSA &paftd, unsigned dwInstance, unsigned fdwSupport);

typedef BOOL __stdcall (*ACMFILTERTAGENUMCBW)(unsigned hadid, const TACMFILTERTAGDETAILSW &paftd, unsigned dwInstance, unsigned fdwSupport);

typedef BOOL __stdcall (*ACMFILTERTAGENUMCB)(unsigned hadid, const TACMFILTERTAGDETAILSA &paftd, unsigned dwInstance, unsigned fdwSupport);

struct TACMFILTERDETAILSA;
typedef TACMFILTERDETAILSA *PACMFILTERDETAILSA;

#pragma pack(push, 1)
struct TACMFILTERDETAILSA
{
	unsigned cbStruct;
	unsigned dwFilterIndex;
	unsigned dwFilterTag;
	unsigned fdwSupport;
	TWAVEFILTER *pwfltr;
	unsigned cbwfltr;
	char szFilter[128];
} ;
#pragma pack(pop)

struct TACMFILTERDETAILSW;
typedef TACMFILTERDETAILSW *PACMFILTERDETAILSW;

#pragma pack(push, 1)
struct TACMFILTERDETAILSW
{
	unsigned cbStruct;
	unsigned dwFilterIndex;
	unsigned dwFilterTag;
	unsigned fdwSupport;
	TWAVEFILTER *pwfltr;
	unsigned cbwfltr;
	wchar_t szFilter[128];
} ;
#pragma pack(pop)

typedef TACMFILTERDETAILSA *PACMFILTERDETAILS;

typedef TACMFILTERDETAILSA  TACMFILTERDETAILS;

typedef BOOL __stdcall (*ACMFILTERENUMCBA)(unsigned hadid, const TACMFILTERDETAILSA &pafd, unsigned dwInstance, unsigned fdwSupport);

typedef BOOL __stdcall (*ACMFILTERENUMCBW)(unsigned hadid, const TACMFILTERDETAILSW &pafd, unsigned dwInstance, unsigned fdwSupport);

typedef BOOL __stdcall (*ACMFILTERENUMCB)(unsigned hadid, const TACMFILTERDETAILSA &pafd, unsigned dwInstance, unsigned fdwSupport);

typedef unsigned __stdcall (*ACMFILTERCHOOSEHOOKPROCA)(HWND hwnd, unsigned uMsg, int wParam, int lParam);

typedef unsigned __stdcall (*ACMFILTERCHOOSEHOOKPROCW)(HWND hwnd, unsigned uMsg, int wParam, int lParam);

typedef unsigned __stdcall (*ACMFILTERCHOOSEHOOKPROC)(HWND hwnd, unsigned uMsg, int wParam, int lParam);

struct TACMFILTERCHOOSEA;
typedef TACMFILTERCHOOSEA *PACMFILTERCHOOSEA;

#pragma pack(push, 1)
struct TACMFILTERCHOOSEA
{
	unsigned cbStruct;
	unsigned fdwStyle;
	HWND hwndOwner;
	TWAVEFILTER *pwfltr;
	unsigned cbwfltr;
	char *pszTitle;
	char szFilterTag[48];
	char szFilter[128];
	char *pszName;
	unsigned cchName;
	unsigned fdwEnum;
	TWAVEFILTER *pwfltrEnum;
	unsigned hInstance;
	char *pszTemplateName;
	int lCustData;
	ACMFILTERCHOOSEHOOKPROCA pfnHook;
} ;
#pragma pack(pop)

struct TACMFILTERCHOOSEW;
typedef TACMFILTERCHOOSEW *PACMFILTERCHOOSEW;

#pragma pack(push, 1)
struct TACMFILTERCHOOSEW
{
	unsigned cbStruct;
	unsigned fdwStyle;
	HWND hwndOwner;
	TWAVEFILTER *pwfltr;
	unsigned cbwfltr;
	wchar_t *pszTitle;
	wchar_t szFilterTag[48];
	wchar_t szFilter[128];
	wchar_t *pszName;
	unsigned cchName;
	unsigned fdwEnum;
	TWAVEFILTER *pwfltrEnum;
	unsigned hInstance;
	wchar_t *pszTemplateName;
	int lCustData;
	ACMFILTERCHOOSEHOOKPROCW pfnHook;
} ;
#pragma pack(pop)

typedef TACMFILTERCHOOSEA *PACMFILTERCHOOSE;

typedef TACMFILTERCHOOSEA  TACMFILTERCHOOSE;

struct TACMSTREAMHEADER;
typedef TACMSTREAMHEADER *PACMSTREAMHEADER;

#pragma pack(push, 1)
struct TACMSTREAMHEADER
{
	unsigned cbStruct;
	unsigned fdwStatus;
	unsigned dwUser;
	Byte *pbSrc;
	unsigned cbSrcLength;
	unsigned cbSrcLengthUsed;
	unsigned dwSrcUser;
	Byte *pbDst;
	unsigned cbDstLength;
	unsigned cbDstLengthUsed;
	unsigned dwDstUser;
	unsigned dwReservedDriver[10];
} ;
#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
static const Shortint WAVE_FILTER_UNKNOWN = 0x0;
static const Word WAVE_FILTER_DEVELOPMENT = 0xffff;
static const Word DRV_MAPPER_PREFERRED_INPUT_GET = 0x4000;
static const Word DRV_MAPPER_PREFERRED_OUTPUT_GET = 0x4002;
static const Word DRVM_MAPPER_STATUS = 0x2000;
static const Word WIDM_MAPPER_STATUS = 0x2000;
static const Shortint WAVEIN_MAPPER_STATUS_DEVICE = 0x0;
static const Shortint WAVEIN_MAPPER_STATUS_MAPPED = 0x1;
static const Shortint WAVEIN_MAPPER_STATUS_FORMAT = 0x2;
static const Word WODM_MAPPER_STATUS = 0x2000;
static const Shortint WAVEOUT_MAPPER_STATUS_DEVICE = 0x0;
static const Shortint WAVEOUT_MAPPER_STATUS_MAPPED = 0x1;
static const Shortint WAVEOUT_MAPPER_STATUS_FORMAT = 0x2;
static const Word ACMERR_BASE = 0x200;
static const Word ACMERR_NOTPOSSIBLE = 0x200;
static const Word ACMERR_BUSY = 0x201;
static const Word ACMERR_UNPREPARED = 0x202;
static const Word ACMERR_CANCELED = 0x203;
static const Word MM_ACM_OPEN = 0x3d4;
static const Word MM_ACM_CLOSE = 0x3d5;
static const Word MM_ACM_DONE = 0x3d6;
static const Shortint ACM_METRIC_COUNT_DRIVERS = 0x1;
static const Shortint ACM_METRIC_COUNT_CODECS = 0x2;
static const Shortint ACM_METRIC_COUNT_CONVERTERS = 0x3;
static const Shortint ACM_METRIC_COUNT_FILTERS = 0x4;
static const Shortint ACM_METRIC_COUNT_DISABLED = 0x5;
static const Shortint ACM_METRIC_COUNT_HARDWARE = 0x6;
static const Shortint ACM_METRIC_COUNT_LOCAL_DRIVERS = 0x14;
static const Shortint ACM_METRIC_COUNT_LOCAL_CODECS = 0x15;
static const Shortint ACM_METRIC_COUNT_LOCAL_CONVERTERS = 0x16;
static const Shortint ACM_METRIC_COUNT_LOCAL_FILTERS = 0x17;
static const Shortint ACM_METRIC_COUNT_LOCAL_DISABLED = 0x18;
static const Shortint ACM_METRIC_HARDWARE_WAVE_INPUT = 0x1e;
static const Shortint ACM_METRIC_HARDWARE_WAVE_OUTPUT = 0x1f;
static const Shortint ACM_METRIC_MAX_SIZE_FORMAT = 0x32;
static const Shortint ACM_METRIC_MAX_SIZE_FILTER = 0x33;
static const Shortint ACM_METRIC_DRIVER_SUPPORT = 0x64;
static const Shortint ACM_METRIC_DRIVER_PRIORITY = 0x65;
static const int ACM_DRIVERENUMF_NOLOCAL = 0x40000000;
static const unsigned ACM_DRIVERENUMF_DISABLED = 0x80000000;
static const Shortint ACM_DRIVERADDF_FUNCTION = 0x3;
static const Shortint ACM_DRIVERADDF_NOTIFYHWND = 0x4;
static const Shortint ACM_DRIVERADDF_TYPEMASK = 0x7;
static const Shortint ACM_DRIVERADDF_LOCAL = 0x0;
static const Shortint ACM_DRIVERADDF_GLOBAL = 0x8;
static const Word ACMDM_USER = 0x4000;
static const Word ACMDM_RESERVED_LOW = 0x6000;
static const Word ACMDM_RESERVED_HIGH = 0x6fff;
static const Word ACMDM_BASE = 0x6000;
static const Word ACMDM_DRIVER_ABOUT = 0x600b;
static const Shortint ACM_DRIVERPRIORITYF_ENABLE = 0x1;
static const Shortint ACM_DRIVERPRIORITYF_DISABLE = 0x2;
static const Shortint ACM_DRIVERPRIORITYF_ABLEMASK = 0x3;
static const int ACM_DRIVERPRIORITYF_BEGIN = 0x10000;
static const int ACM_DRIVERPRIORITYF_END = 0x20000;
static const int ACM_DRIVERPRIORITYF_DEFERMASK = 0x30000;
static const Shortint ACMDRIVERDETAILS_SHORTNAME_CHARS = 0x20;
static const Byte ACMDRIVERDETAILS_LONGNAME_CHARS = 0x80;
static const Shortint ACMDRIVERDETAILS_COPYRIGHT_CHARS = 0x50;
static const Byte ACMDRIVERDETAILS_LICENSING_CHARS = 0x80;
static const Word ACMDRIVERDETAILS_FEATURES_CHARS = 0x200;
static const Shortint ACMDRIVERDETAILS_FCCCOMP_UNDEFINED = 0x0;
static const Shortint ACMDRIVERDETAILS_SUPPORTF_CODEC = 0x1;
static const Shortint ACMDRIVERDETAILS_SUPPORTF_CONVERTER = 0x2;
static const Shortint ACMDRIVERDETAILS_SUPPORTF_FILTER = 0x4;
static const Shortint ACMDRIVERDETAILS_SUPPORTF_HARDWARE = 0x8;
static const Shortint ACMDRIVERDETAILS_SUPPORTF_ASYNC = 0x10;
static const int ACMDRIVERDETAILS_SUPPORTF_LOCAL = 0x40000000;
static const unsigned ACMDRIVERDETAILS_SUPPORTF_DISABLED = 0x80000000;
static const Shortint ACMFORMATTAGDETAILS_FORMATTAG_CHARS = 0x30;
static const Shortint ACM_FORMATTAGDETAILSF_INDEX = 0x0;
static const Shortint ACM_FORMATTAGDETAILSF_FORMATTAG = 0x1;
static const Shortint ACM_FORMATTAGDETAILSF_LARGESTSIZE = 0x2;
static const Shortint ACM_FORMATTAGDETAILSF_QUERYMASK = 0xf;
static const Byte ACMFORMATDETAILS_FORMAT_CHARS = 0x80;
static const Shortint ACM_FORMATDETAILSF_INDEX = 0x0;
static const Shortint ACM_FORMATDETAILSF_FORMAT = 0x1;
static const Shortint ACM_FORMATDETAILSF_QUERYMASK = 0xf;
static const int ACM_FORMATENUMF_WFORMATTAG = 0x10000;
static const int ACM_FORMATENUMF_NCHANNELS = 0x20000;
static const int ACM_FORMATENUMF_NSAMPLESPERSEC = 0x40000;
static const int ACM_FORMATENUMF_WBITSPERSAMPLE = 0x80000;
static const int ACM_FORMATENUMF_CONVERT = 0x100000;
static const int ACM_FORMATENUMF_SUGGEST = 0x200000;
static const int ACM_FORMATENUMF_HARDWARE = 0x400000;
static const int ACM_FORMATENUMF_INPUT = 0x800000;
static const int ACM_FORMATENUMF_OUTPUT = 0x1000000;
static const int ACM_FORMATSUGGESTF_WFORMATTAG = 0x10000;
static const int ACM_FORMATSUGGESTF_NCHANNELS = 0x20000;
static const int ACM_FORMATSUGGESTF_NSAMPLESPERSEC = 0x40000;
static const int ACM_FORMATSUGGESTF_WBITSPERSAMPLE = 0x80000;
static const int ACM_FORMATSUGGESTF_TYPEMASK = 0xff0000;
#define ACMHELPMSGSTRINGA "acmchoose_help"
#define ACMHELPMSGSTRINGW "acmchoose_help"
#define ACMHELPMSGCONTEXTMENUA "acmchoose_contextmenu"
#define ACMHELPMSGCONTEXTMENUW "acmchoose_contextmenu"
#define ACMHELPMSGCONTEXTHELPA "acmchoose_contexthelp"
#define ACMHELPMSGCONTEXTHELPW "acmchoose_contexthelp"
#define ACMHELPMSGSTRING "acmchoose_help"
#define ACMHELPMSGCONTEXTMENU "acmchoose_contextmenu"
#define ACMHELPMSGCONTEXTHELP "acmchoose_contexthelp"
static const Word MM_ACM_FORMATCHOOSE = 0x8000;
static const Shortint FORMATCHOOSE_MESSAGE = 0x0;
static const Shortint FORMATCHOOSE_FORMATTAG_VERIFY = 0x0;
static const Shortint FORMATCHOOSE_FORMAT_VERIFY = 0x1;
static const Shortint FORMATCHOOSE_CUSTOM_VERIFY = 0x2;
static const Shortint ACMFORMATCHOOSE_STYLEF_SHOWHELP = 0x4;
static const Shortint ACMFORMATCHOOSE_STYLEF_ENABLEHOOK = 0x8;
static const Shortint ACMFORMATCHOOSE_STYLEF_ENABLETEMPLATE = 0x10;
static const Shortint ACMFORMATCHOOSE_STYLEF_ENABLETEMPLATEHANDLE = 0x20;
static const Shortint ACMFORMATCHOOSE_STYLEF_INITTOWFXSTRUCT = 0x40;
static const Byte ACMFORMATCHOOSE_STYLEF_CONTEXTHELP = 0x80;
static const Shortint ACMFILTERTAGDETAILS_FILTERTAG_CHARS = 0x30;
static const Shortint ACM_FILTERTAGDETAILSF_INDEX = 0x0;
static const Shortint ACM_FILTERTAGDETAILSF_FILTERTAG = 0x1;
static const Shortint ACM_FILTERTAGDETAILSF_LARGESTSIZE = 0x2;
static const Shortint ACM_FILTERTAGDETAILSF_QUERYMASK = 0xf;
static const Byte ACMFILTERDETAILS_FILTER_CHARS = 0x80;
static const Shortint ACM_FILTERDETAILSF_INDEX = 0x0;
static const Shortint ACM_FILTERDETAILSF_FILTER = 0x1;
static const Shortint ACM_FILTERDETAILSF_QUERYMASK = 0xf;
static const int ACM_FILTERENUMF_DWFILTERTAG = 0x10000;
static const Word MM_ACM_FILTERCHOOSE = 0x8000;
static const Shortint FILTERCHOOSE_MESSAGE = 0x0;
static const Shortint FILTERCHOOSE_FILTERTAG_VERIFY = 0x0;
static const Shortint FILTERCHOOSE_FILTER_VERIFY = 0x1;
static const Shortint FILTERCHOOSE_CUSTOM_VERIFY = 0x2;
static const Shortint ACMFILTERCHOOSE_STYLEF_SHOWHELP = 0x4;
static const Shortint ACMFILTERCHOOSE_STYLEF_ENABLEHOOK = 0x8;
static const Shortint ACMFILTERCHOOSE_STYLEF_ENABLETEMPLATE = 0x10;
static const Shortint ACMFILTERCHOOSE_STYLEF_ENABLETEMPLATEHANDLE = 0x20;
static const Shortint ACMFILTERCHOOSE_STYLEF_INITTOFILTERSTRUCT = 0x40;
static const Byte ACMFILTERCHOOSE_STYLEF_CONTEXTHELP = 0x80;
static const int ACMSTREAMHEADER_STATUSF_DONE = 0x10000;
static const int ACMSTREAMHEADER_STATUSF_PREPARED = 0x20000;
static const int ACMSTREAMHEADER_STATUSF_INQUEUE = 0x100000;
static const Shortint ACM_STREAMOPENF_QUERY = 0x1;
static const Shortint ACM_STREAMOPENF_ASYNC = 0x2;
static const Shortint ACM_STREAMOPENF_NONREALTIME = 0x4;
static const Shortint ACM_STREAMSIZEF_SOURCE = 0x0;
static const Shortint ACM_STREAMSIZEF_DESTINATION = 0x1;
static const Shortint ACM_STREAMSIZEF_QUERYMASK = 0xf;
static const Shortint ACM_STREAMCONVERTF_BLOCKALIGN = 0x4;
static const Shortint ACM_STREAMCONVERTF_START = 0x10;
static const Shortint ACM_STREAMCONVERTF_END = 0x20;
extern "C" unsigned __stdcall acmGetVersion(void);
extern "C" unsigned __stdcall acmMetrics(unsigned hao, unsigned uMetric, void *pMetric);
extern "C" unsigned __stdcall acmDriverEnum(ACMDRIVERENUMCB fnCallback, unsigned dwInstance, unsigned fdwEnum);
extern "C" unsigned __stdcall acmDriverID(unsigned hao, unsigned &phadid, unsigned fdwDriverID);
extern "C" unsigned __stdcall acmDriverAddA(unsigned &phadid, unsigned hinstModule, int lParam, unsigned dwPriority, unsigned fdwAdd);
extern "C" unsigned __stdcall acmDriverAddW(unsigned &phadid, unsigned hinstModule, int lParam, unsigned dwPriority, unsigned fdwAdd);
extern "C" unsigned __stdcall acmDriverAdd(unsigned &phadid, unsigned hinstModule, int lParam, unsigned dwPriority, unsigned fdwAdd);
extern "C" unsigned __stdcall acmDriverRemove(unsigned hadid, unsigned fdwRemove);
extern "C" unsigned __stdcall acmDriverOpen(unsigned &phad, unsigned hadid, unsigned fdwOpen);
extern "C" unsigned __stdcall acmDriverClose(unsigned had, unsigned fdwClose);
extern "C" int __stdcall acmDriverMessage(unsigned had, unsigned uMsg, int lParam1, int lParam2);
extern "C" unsigned __stdcall acmDriverPriority(unsigned hadid, unsigned dwPriority, unsigned fdwPriority);
extern PACKAGE unsigned __fastcall ACMDRIVERDETAILS_FCCTYPE_AUDIOCODE(void);
extern "C" unsigned __stdcall acmDriverDetailsA(unsigned hadid, TACMDRIVERDETAILSA &padd, unsigned fdwDetails);
extern "C" unsigned __stdcall acmDriverDetailsW(unsigned hadid, TACMDRIVERDETAILSW &padd, unsigned fdwDetails);
extern "C" unsigned __stdcall acmDriverDetails(unsigned hadid, TACMDRIVERDETAILSA &padd, unsigned fdwDetails);
extern "C" unsigned __stdcall acmFormatTagDetailsA(unsigned had, TACMFORMATTAGDETAILSA &paftd, unsigned fdwDetails);
extern "C" unsigned __stdcall acmFormatTagDetailsW(unsigned had, TACMFORMATTAGDETAILSW &paftd, unsigned fdwDetails);
extern "C" unsigned __stdcall acmFormatTagDetails(unsigned had, TACMFORMATTAGDETAILSA &paftd, unsigned fdwDetails);
extern "C" unsigned __stdcall acmFormatTagEnumA(unsigned had, TACMFORMATTAGDETAILSA &paftd, ACMFORMATTAGENUMCBA fnCallback, unsigned dwInstance, unsigned fdwEnum);
extern "C" unsigned __stdcall acmFormatTagEnumW(unsigned had, TACMFORMATTAGDETAILSW &paftd, ACMFORMATTAGENUMCBW fnCallback, unsigned dwInstance, unsigned fdwEnum);
extern "C" unsigned __stdcall acmFormatTagEnum(unsigned had, TACMFORMATTAGDETAILSA &paftd, ACMFORMATTAGENUMCBA fnCallback, unsigned dwInstance, unsigned fdwEnum);
extern "C" unsigned __stdcall acmFormatDetailsA(unsigned had, TACMFORMATDETAILSA &pafd, unsigned fdwDetails);
extern "C" unsigned __stdcall acmFormatDetailsW(unsigned had, TACMFORMATDETAILSW &pafd, unsigned fdwDetails);
extern "C" unsigned __stdcall acmFormatDetails(unsigned had, TACMFORMATDETAILSA &pafd, unsigned fdwDetails);
extern "C" unsigned __stdcall acmFormatEnumA(unsigned had, TACMFORMATDETAILSA &pafd, ACMFORMATENUMCBA fnCallback, unsigned dwInstance, unsigned fdwEnum);
extern "C" unsigned __stdcall acmFormatEnumW(unsigned had, TACMFORMATDETAILSW &pafd, ACMFORMATENUMCBW fnCallback, unsigned dwInstance, unsigned fdwEnum);
extern "C" unsigned __stdcall acmFormatEnum(unsigned had, TACMFORMATDETAILSA &pafd, ACMFORMATENUMCBA fnCallback, unsigned dwInstance, unsigned fdwEnum);
extern "C" unsigned __stdcall acmFormatSuggest(unsigned had, const tWAVEFORMATEX &pwfxSrc, tWAVEFORMATEX &pwfxDst, unsigned cbwfxDst, unsigned fdwSuggest);
extern "C" unsigned __stdcall acmFormatChooseA(TACMFORMATCHOOSEA &pafmtc);
extern "C" unsigned __stdcall acmFormatChooseW(TACMFORMATCHOOSEW &pafmtc);
extern "C" unsigned __stdcall acmFormatChoose(TACMFORMATCHOOSEA &pafmtc);
extern "C" unsigned __stdcall acmFilterTagDetailsA(unsigned had, TACMFILTERTAGDETAILSA &paftd, unsigned fdwDetails);
extern "C" unsigned __stdcall acmFilterTagDetailsW(unsigned had, TACMFILTERTAGDETAILSW &paftd, unsigned fdwDetails);
extern "C" unsigned __stdcall acmFilterTagDetails(unsigned had, TACMFILTERTAGDETAILSA &paftd, unsigned fdwDetails);
extern "C" unsigned __stdcall acmFilterTagEnumA(unsigned had, TACMFILTERTAGDETAILSA &paftd, ACMFILTERTAGENUMCBA fnCallback, unsigned dwInstance, unsigned fdwEnum);
extern "C" unsigned __stdcall acmFilterTagEnumW(unsigned had, TACMFILTERTAGDETAILSW &paftd, ACMFILTERTAGENUMCBW fnCallback, unsigned dwInstance, unsigned fdwEnum);
extern "C" unsigned __stdcall acmFilterTagEnum(unsigned had, TACMFILTERTAGDETAILSA &paftd, ACMFILTERTAGENUMCBA fnCallback, unsigned dwInstance, unsigned fdwEnum);
extern "C" unsigned __stdcall acmFilterDetailsA(unsigned had, TACMFILTERDETAILSA &pafd, unsigned fdwDetails);
extern "C" unsigned __stdcall acmFilterDetailsW(unsigned had, TACMFILTERDETAILSW &pafd, unsigned fdwDetails);
extern "C" unsigned __stdcall acmFilterDetails(unsigned had, TACMFILTERDETAILSA &pafd, unsigned fdwDetails);
extern "C" unsigned __stdcall acmFilterEnumA(unsigned had, TACMFILTERDETAILSA &pafd, ACMFILTERENUMCBA fnCallback, unsigned dwInstance, unsigned fdwEnum);
extern "C" unsigned __stdcall acmFilterEnumW(unsigned had, TACMFILTERDETAILSW &pafd, ACMFILTERENUMCBW fnCallback, unsigned dwInstance, unsigned fdwEnum);
extern "C" unsigned __stdcall acmFilterEnum(unsigned had, TACMFILTERDETAILSA &pafd, ACMFILTERENUMCBA fnCallback, unsigned dwInstance, unsigned fdwEnum);
extern "C" unsigned __stdcall acmFilterChooseA(TACMFILTERCHOOSEA &pafltrc);
extern "C" unsigned __stdcall acmFilterChooseW(TACMFILTERCHOOSEW &pafltrc);
extern "C" unsigned __stdcall acmFilterChoose(TACMFILTERCHOOSEA &pafltrc);
extern "C" unsigned __stdcall acmStreamOpen(PHACMSTREAM phas, unsigned had, const tWAVEFORMATEX &pwfxSrc, const tWAVEFORMATEX &pwfxdst, PWAVEFILTER pwfltr, unsigned dwCallback, unsigned dwInstance, unsigned fdwOpen);
extern "C" unsigned __stdcall acmStreamClose(unsigned has, unsigned fdwClose);
extern "C" unsigned __stdcall acmStreamSize(unsigned has, unsigned cbInput, unsigned &pdwOutputByte, unsigned fdwSize);
extern "C" unsigned __stdcall acmStreamReset(unsigned has, unsigned fdwReset);
extern "C" unsigned __stdcall acmStreamMessage(unsigned has, unsigned uMsg, int lParam1, int lParam2);
extern "C" unsigned __stdcall acmStreamConvert(unsigned has, TACMSTREAMHEADER &pash, unsigned fdwConvert);
extern "C" unsigned __stdcall acmStreamPrepareHeader(unsigned has, TACMSTREAMHEADER &pash, unsigned fdwPrepare);
extern "C" unsigned __stdcall acmStreamUnprepareHeader(unsigned has, TACMSTREAMHEADER &pash, unsigned fdwUnprepare);

#if defined(UNICODE)
#pragma option push -w-inl
inline unsigned __stdcall acmDriverAdd(unsigned &phadid, unsigned hinstModule, int lParam, unsigned dwPriority, unsigned fdwAdd)
{
	return acmDriverAddW(phadid, hinstModule, lParam, dwPriority, fdwAdd);
}
#pragma option pop

#else
#pragma option push -w-inl
inline unsigned __stdcall acmDriverAdd(unsigned &phadid, unsigned hinstModule, int lParam, unsigned dwPriority, unsigned fdwAdd)
{
	return acmDriverAddA(phadid, hinstModule, lParam, dwPriority, fdwAdd);
}
#pragma option pop

#endif


#if defined(UNICODE)
#pragma option push -w-inl
inline unsigned __stdcall acmDriverDetails(unsigned hadid, TACMDRIVERDETAILSA &padd, unsigned fdwDetails)
{
	return acmDriverDetailsW(hadid, padd, fdwDetails);
}
#pragma option pop

#else
#pragma option push -w-inl
inline unsigned __stdcall acmDriverDetails(unsigned hadid, TACMDRIVERDETAILSA &padd, unsigned fdwDetails)
{
	return acmDriverDetailsA(hadid, padd, fdwDetails);
}
#pragma option pop

#endif


#if defined(UNICODE)
#pragma option push -w-inl
inline unsigned __stdcall acmFormatTagDetails(unsigned had, TACMFORMATTAGDETAILSA &paftd, unsigned fdwDetails)
{
	return acmFormatTagDetailsW(had, paftd, fdwDetails);
}
#pragma option pop

#else
#pragma option push -w-inl
inline unsigned __stdcall acmFormatTagDetails(unsigned had, TACMFORMATTAGDETAILSA &paftd, unsigned fdwDetails)
{
	return acmFormatTagDetailsA(had, paftd, fdwDetails);
}
#pragma option pop

#endif


#if defined(UNICODE)
#pragma option push -w-inl
inline unsigned __stdcall acmFormatTagEnum(unsigned had, TACMFORMATTAGDETAILSA &paftd, ACMFORMATTAGENUMCBA fnCallback, unsigned dwInstance, unsigned fdwEnum)
{
	return acmFormatTagEnumW(had, paftd, fnCallback, dwInstance, fdwEnum);
}
#pragma option pop

#else
#pragma option push -w-inl
inline unsigned __stdcall acmFormatTagEnum(unsigned had, TACMFORMATTAGDETAILSA &paftd, ACMFORMATTAGENUMCBA fnCallback, unsigned dwInstance, unsigned fdwEnum)
{
	return acmFormatTagEnumA(had, paftd, fnCallback, dwInstance, fdwEnum);
}
#pragma option pop

#endif


#if defined(UNICODE)
#pragma option push -w-inl
inline unsigned __stdcall acmFormatDetails(unsigned had, TACMFORMATDETAILSA &pafd, unsigned fdwDetails)
{
	return acmFormatDetailsW(had, pafd, fdwDetails);
}
#pragma option pop

#else
#pragma option push -w-inl
inline unsigned __stdcall acmFormatDetails(unsigned had, TACMFORMATDETAILSA &pafd, unsigned fdwDetails)
{
	return acmFormatDetailsA(had, pafd, fdwDetails);
}
#pragma option pop

#endif


#if defined(UNICODE)
#pragma option push -w-inl
inline unsigned __stdcall acmFormatEnum(unsigned had, TACMFORMATDETAILSA &pafd, ACMFORMATENUMCBA fnCallback, unsigned dwInstance, unsigned fdwEnum)
{
	return acmFormatEnumW(had, pafd, fnCallback, dwInstance, fdwEnum);
}
#pragma option pop

#else
#pragma option push -w-inl
inline unsigned __stdcall acmFormatEnum(unsigned had, TACMFORMATDETAILSA &pafd, ACMFORMATENUMCBA fnCallback, unsigned dwInstance, unsigned fdwEnum)
{
	return acmFormatEnumA(had, pafd, fnCallback, dwInstance, fdwEnum);
}
#pragma option pop

#endif


#if defined(UNICODE)
#pragma option push -w-inl
inline unsigned __stdcall acmFormatChoose(TACMFORMATCHOOSEA &pafmtc)
{
	return acmFormatChooseW(pafmtc);
}
#pragma option pop

#else
#pragma option push -w-inl
inline unsigned __stdcall acmFormatChoose(TACMFORMATCHOOSEA &pafmtc)
{
	return acmFormatChooseA(pafmtc);
}
#pragma option pop

#endif


#if defined(UNICODE)
#pragma option push -w-inl
inline unsigned __stdcall acmFilterTagDetails(unsigned had, TACMFILTERTAGDETAILSA &paftd, unsigned fdwDetails)
{
	return acmFilterTagDetailsW(had, paftd, fdwDetails);
}
#pragma option pop

#else
#pragma option push -w-inl
inline unsigned __stdcall acmFilterTagDetails(unsigned had, TACMFILTERTAGDETAILSA &paftd, unsigned fdwDetails)
{
	return acmFilterTagDetailsA(had, paftd, fdwDetails);
}
#pragma option pop

#endif


#if defined(UNICODE)
#pragma option push -w-inl
inline unsigned __stdcall acmFilterTagEnum(unsigned had, TACMFILTERTAGDETAILSA &paftd, ACMFILTERTAGENUMCBA fnCallback, unsigned dwInstance, unsigned fdwEnum)
{
	return acmFilterTagEnumW(had, paftd, fnCallback, dwInstance, fdwEnum);
}
#pragma option pop

#else
#pragma option push -w-inl
inline unsigned __stdcall acmFilterTagEnum(unsigned had, TACMFILTERTAGDETAILSA &paftd, ACMFILTERTAGENUMCBA fnCallback, unsigned dwInstance, unsigned fdwEnum)
{
	return acmFilterTagEnumA(had, paftd, fnCallback, dwInstance, fdwEnum);
}
#pragma option pop

#endif


#if defined(UNICODE)
#pragma option push -w-inl
inline unsigned __stdcall acmFilterDetails(unsigned had, TACMFILTERDETAILSA &pafd, unsigned fdwDetails)
{
	return acmFilterDetailsW(had, pafd, fdwDetails);
}
#pragma option pop

#else
#pragma option push -w-inl
inline unsigned __stdcall acmFilterDetails(unsigned had, TACMFILTERDETAILSA &pafd, unsigned fdwDetails)
{
	return acmFilterDetailsA(had, pafd, fdwDetails);
}
#pragma option pop

#endif


#if defined(UNICODE)
#pragma option push -w-inl
inline unsigned __stdcall acmFilterEnum(unsigned had, TACMFILTERDETAILSA &pafd, ACMFILTERENUMCBA fnCallback, unsigned dwInstance, unsigned fdwEnum)
{
	return acmFilterEnumW(had, pafd, fnCallback, dwInstance, fdwEnum);
}
#pragma option pop

#else
#pragma option push -w-inl
inline unsigned __stdcall acmFilterEnum(unsigned had, TACMFILTERDETAILSA &pafd, ACMFILTERENUMCBA fnCallback, unsigned dwInstance, unsigned fdwEnum)
{
	return acmFilterEnumA(had, pafd, fnCallback, dwInstance, fdwEnum);
}
#pragma option pop

#endif


#if defined(UNICODE)
#pragma option push -w-inl
inline unsigned __stdcall acmFilterChoose(TACMFILTERCHOOSEA &pafltrc)
{
	return acmFilterChooseW(pafltrc);
}
#pragma option pop

#else
#pragma option push -w-inl
inline unsigned __stdcall acmFilterChoose(TACMFILTERCHOOSEA &pafltrc)
{
	return acmFilterChooseA(pafltrc);
}
#pragma option pop

#endif


}	/* namespace Msacm */
using namespace Msacm;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// MSACM
