#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.




#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원
#include <afxdisp.h>

enum AMC_POPUPS
{
	/// AMC will not show any Popups.
	AMC_POPUPS_NONE = 0L,

	/// AMC will show a Login Dialog if the username or password is incorrect.
	AMC_POPUPS_LOGIN_DIALOG = 1L,

	/// All messages are shown as Popups.
	AMC_POPUPS_MESSAGES = 2L,

	/// "No Video" overlay is shown when the stream is stopped.
	AMC_POPUPS_NO_VIDEO = 4L,

	/// Untrusted certificates will be rejected without prompting the user.
	AMC_POPUPS_SUPPRESS_UNTRUSTED_CERTIFICATE_ALERT = 8L,
};

enum AMC_STATUS
{
	/// AMC is uninitialized
	AMC_STATUS_NONE = 0L,

	/// AMC is initialized and ready.
	AMC_STATUS_INITIALIZED = 1L,

	/// A media stream/file is playing.
	AMC_STATUS_PLAYING = 2L,

	/// Playing of a media stream/file is paused.
	AMC_STATUS_PAUSED = 4L,

	/// A media stream/file is being recorded.
	AMC_STATUS_RECORDING = 8L,

	/// AMC is opening a media stream/file.
	AMC_STATUS_OPENING = 16L,

	/// AMC is performing reconnection.
	AMC_STATUS_RECONNECTING = 32L,

	/// Issuing a Pan, Tilt, Zoom command to the device.
	AMC_STATUS_ISSUING_PTZ_COMMAND = 512L,

	/// An extended text/message is displayed in the status bar.
	AMC_STATUS_EXTENDED_TEXT = 1024L,

	/// UIMode is set to ptz-absolute.
	AMC_STATUS_PTZ_UIMODE_ABS = 2048L,

	/// UIMode is set to ptz-relative or ptz-relative-no-cross.
	AMC_STATUS_PTZ_UIMODE_REL = 4096L,

	/// The stream for receiveing audio is being opened.
	AMC_STATUS_OPENING_RECEIVE_AUDIO = 65536L,

	/// AMC is opening the stream for transmitting audio.
	AMC_STATUS_OPENING_TRANSMIT_AUDIO = 131072L,

	/// Receiving audio.
	AMC_STATUS_RECEIVE_AUDIO = 262144L,

	/// Transmitting audio.
	AMC_STATUS_TRANSMIT_AUDIO = 524288L,

	/// An audio file is being transmitted.
	AMC_STATUS_TRANSMIT_AUDIO_FILE = 1048576L,

	/// Recording audio.
	AMC_STATUS_RECORDING_AUDIO = 2097152L
};

enum AMC_VIDEO_RENDERER
{
	/// Video Mixing Renderer 7
	AMC_VIDEO_RENDERER_VMR7 = 0x00000,

	/// Video Mixing Renderer 9
	AMC_VIDEO_RENDERER_VMR9 = 0x01000,

	/// Enhanced Video Renderer
	AMC_VIDEO_RENDERER_EVR = 0x10000
};

/// Option flags for StartRecordMedia
enum AMC_RECORD_FLAG
{
	AMC_RECORD_FLAG_NONE = 0,

	// Record received audio samples
	AMC_RECORD_FLAG_RECEIVED_AUDIO = 1,

	// Record transmitted audio samples
	AMC_RECORD_FLAG_TRANSMITTED_AUDIO = 2,

	// If set, audio should be saved in its encoded form. Otherwise in wav(pcm)-format.
	AMC_RECORD_FLAG_ENCODED_AUDIO = 4,

	// Record video only
	AMC_RECORD_FLAG_VIDEO = 8,

	// Record both video and audio
	AMC_RECORD_FLAG_AUDIO_VIDEO = 16
};





#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif










