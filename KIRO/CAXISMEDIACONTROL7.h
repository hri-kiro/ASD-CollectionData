#pragma once

// 머신에서 Microsoft Visual C++를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// 참고: 이 파일의 콘텐츠를 수정하지 마세요. Microsoft Visual C++를 통해 이 클래스가 다시 생성될 경우 
// 수정 내용을 덮어씁니다.

/////////////////////////////////////////////////////////////////////////////

#include "afxwin.h"

class CAXISMEDIACONTROL7 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CAXISMEDIACONTROL7)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= {0x745395c8,0xd0e1,0x4227,{0x85,0x86,0x62,0x4c,0xa9,0xa1,0x0a,0x8d}};
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = nullptr)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID);
	}

	BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
				UINT nID, CFile* pPersist = nullptr, BOOL bStorage = FALSE,
				BSTR bstrLicKey = nullptr)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 특성
public:
enum
{
	AMC_POPUPS_NONE = 0,
	AMC_POPUPS_LOGIN_DIALOG = 1,
	AMC_POPUPS_MESSAGES = 2,
	AMC_POPUPS_NO_VIDEO = 4,
	AMC_POPUPS_SUPPRESS_UNTRUSTED_CERTIFICATE_ALERT = 8
}AMC_POPUPS;

enum
{
	AMC_STATUS_NONE = 0,
	AMC_STATUS_INITIALIZED = 1,
	AMC_STATUS_PLAYING = 2,
	AMC_STATUS_PAUSED = 4,
	AMC_STATUS_RECORDING = 8,
	AMC_STATUS_OPENING = 16,
	AMC_STATUS_RECONNECTING = 32,
	AMC_STATUS_ISSUING_PTZ_COMMAND = 512,
	AMC_STATUS_EXTENDED_TEXT = 1024,
	AMC_STATUS_PTZ_UIMODE_ABS = 2048,
	AMC_STATUS_PTZ_UIMODE_REL = 4096,
	AMC_STATUS_OPENING_RECEIVE_AUDIO = 65536,
	AMC_STATUS_OPENING_TRANSMIT_AUDIO = 131072,
	AMC_STATUS_RECEIVE_AUDIO = 262144,
	AMC_STATUS_TRANSMIT_AUDIO = 524288,
	AMC_STATUS_TRANSMIT_AUDIO_FILE = 1048576,
	AMC_STATUS_RECORDING_AUDIO = 2097152,
	AMC_STATUS_HW_DECODING = 4194304
}AMC_STATUS;

enum
{
	AMC_VIDEO_RENDERER_VMR7 = 0,
	AMC_VIDEO_RENDERER_VMR9 = 4096,
	AMC_VIDEO_RENDERER_EVR = 65536
}AMC_VIDEO_RENDERER;

enum
{
	AMC_VIDEO_DECODE_ONLY_I = 0,
	AMC_VIDEO_DECODE_ONLY_IP = 1,
	AMC_VIDEO_DECODE_ALL_FRAMES = 3,
	AMC_VIDEO_DECODING_QUALITY_LOW = 16,
	AMC_VIDEO_DECODING_QUALITY_MEDIUM = 20,
	AMC_VIDEO_DECODING_QUALITY_HIGH = 24,
	AMC_VIDEO_DECODING_QUALITY_DYNAMIC = 28,
	AMC_VIDEO_NO_FRAME_DROPPING = 32,
	AMC_VIDEO_DEINTERLACE = 65536,
	AMC_VIDEO_DEBLOCK = 131072
}AMC_VIDEO_DECODING_MODE;

enum
{
	AMC_IMAGE_FORMAT_JPEG = 0,
	AMC_IMAGE_FORMAT_BMP = 1
}AMC_IMAGE_FORMAT;

enum
{
	AMC_RECORD_FLAG_NONE = 0,
	AMC_RECORD_FLAG_RECEIVED_AUDIO = 1,
	AMC_RECORD_FLAG_TRANSMITTED_AUDIO = 2,
	AMC_RECORD_FLAG_ENCODED_AUDIO = 4,
	AMC_RECORD_FLAG_VIDEO = 8,
	AMC_RECORD_FLAG_AUDIO_VIDEO = 16
}AMC_RECORD_FLAG;

enum
{
	AMC_USER_WINDOW_PROPERTY_NONE = 0,
	AMC_USER_WINDOW_PROPERTY_RESIZEABLE = 1,
	AMC_USER_WINDOW_PROPERTY_MOVABLE = 2,
	AMC_USER_WINDOW_PROPERTY_FILLED = 4,
	AMC_USER_WINDOW_PROPERTY_MAINTAIN_ASPECT_RATIO = 8,
	AMC_USER_WINDOW_PROPERTY_NOT_SELECTABLE = 16,
	AMC_USER_WINDOW_PROPERTY_SHOW_DIMENSIONS = 32,
	AMC_USER_WINDOW_PROPERTY_NO_HEADER_LINE = 64,
	AMC_USER_WINDOW_PROPERTY_SELECT = 128,
	AMC_USER_WINDOW_PROPERTY_NO_SHADOW = 256,
	AMC_USER_WINDOW_PROPERTY_CONTENT_TEXT = 512,
	AMC_USER_WINDOW_PROPERTY_NO_HEADER_DELIMITER = 1024
}AMC_USER_WINDOW_PROPERTY;

enum
{
	AMC_USER_WINDOW_STATE_NONE = 0,
	AMC_USER_WINDOW_STATE_SELECTED = 1,
	AMC_USER_WINDOW_STATE_USER_INTERACTION = 2
}AMC_USER_WINDOW_STATE;

enum
{
	AMC_USER_OBJECT_TYPE_POLYLINE = 1,
	AMC_USER_OBJECT_TYPE_POLYGON = 2,
	AMC_USER_OBJECT_TYPE_RECTANGLE = 3,
	AMC_USER_OBJECT_TYPE_ELLIPS = 4,
	AMC_USER_OBJECT_TYPE_DIRECTIONAL_LINE = 10,
	AMC_USER_OBJECT_TYPE_DISTANCE_ELLIPSE = 11
}AMC_USER_OBJECT_TYPE;

enum
{
	AMC_USER_OBJECT_PROPERTY_NONE = 0,
	AMC_USER_OBJECT_PROPERTY_MOVABLE = 1,
	AMC_USER_OBJECT_PROPERTY_CHANGEABLE = 2,
	AMC_USER_OBJECT_PROPERTY_FILL = 4,
	AMC_USER_OBJECT_PROPERTY_HIDDEN = 8,
	AMC_USER_OBJECT_PROPERTY_TOPMOST = 16,
	AMC_USER_OBJECT_PROPERTY_SELECT = 32,
	AMC_USER_OBJECT_PROPERTY_SHADOW = 64,
	AMC_USER_OBJECT_PROPERTY_SHOW_NAME = 128,
	AMC_USER_OBJECT_PROPERTY_TRANSPARENCY = 256,
	AMC_USER_OBJECT_PROPERTY_FILL_CROSS = 512,
	AMC_USER_OBJECT_PROPERTY_MAINTAIN_AR = 1024,
	AMC_USER_OBJECT_PROPERTY_THICK_LINE = 2048
}AMC_USER_OBJECT_PROPERTY;

enum
{
	AMC_USER_OBJECT_STATE_NONE = 0,
	AMC_USER_OBJECT_STATE_CREATED = 1,
	AMC_USER_OBJECT_STATE_SELECTED = 2,
	AMC_USER_OBJECT_STATE_USER_INTERACTION = 4,
	AMC_USER_OBJECT_STATE_MODIFIED = 8,
	AMC_USER_OBJECT_STATE_REMOVED = 16
}AMC_USER_OBJECT_STATE;

enum
{
	AMC_PM_AUTO = 0,
	AMC_PM_LIVE = 1,
	AMC_PM_RECORDING = 2
}AMC_PLAYBACK_MODE;

enum
{
	AMC_FW_DISABLED = 0,
	AMC_FW_NORMAL = 1,
	AMC_FW_PERSISTENT = 2
}AMC_FOCUS_WINDOW_MODE;

enum
{
	AMC_OVERLAY_CROSSHAIR = 1,
	AMC_OVERLAY_VECTOR = 2,
	AMC_OVERLAY_ZOOM = 4
}AMC_OVERLAY;

enum
{
	AMC_TILT_ORIENTATION_UNDEF = 0,
	AMC_TILT_ORIENTATION_WALL = 1,
	AMC_TILT_ORIENTATION_CEILING = 2,
	AMC_TILT_ORIENTATION_DESK = 3
}AMC_TILT_ORIENTATION;

enum
{
	AXIS_E_NET_PROBLEMS = -2147220992,
	AXIS_E_NO_MORE_STREAM = -2147220991,
	AXIS_E_NO_UDP_VIDEO_STREAM_STARTED = -2147220990,
	AXIS_E_HTTP_NOT_FOUND = -2147220989,
	AXIS_E_CONNECT_SOURCE = -2147220988,
	AXIS_E_CONNECT_SOURCE_ALL = -2147220987,
	AXIS_E_MPEG4_OLD_VERSION = -2147220985,
	AXIS_E_DECODER_MISSING = -2147220984,
	AXIS_E_MEDIA_FAIL = -2147220976,
	AXIS_E_NO_AUDIO_HW = -2147220975,
	AXIS_E_MEDIA_ABORT = -2147220974,
	AXIS_E_NO_PTZ_CONTROL_URL = -2147220944,
	AXIS_E_PTZ_FAIL = -2147220943,
	AXIS_E_AACDMO_NOT_FOUND = -2147220942,
	AXIS_E_CONTENT_TYPE = -2147220928,
	AXIS_E_UNTRUSTED_CA = -2147220927,
	AXIS_E_BASIC_AUTH_NOT_ALLOWED = -2147220926,
	AXIS_E_INIT_UNEXPECTED = -2147220736,
	AXIS_E_INIT_ACCESSDENIED = -2147220735,
	AXIS_E_INIT_COMPONENT_MISSING = -2147220734,
	AXIS_E_INIT_COMPONENT_OLD = -2147220733,
	AXIS_E_INIT_NO_JPEG_ENCODER = -2147220732,
	AXIS_E_MISSING_SNAPSHOT_FOLDER = -2147220731,
	AXIS_E_NO_MPEG4_SNAPSHOT = -2147220730,
	AXIS_E_SHUTTING_DOWN = -2147220729,
	AXIS_E_MISSING_RECORDING_FOLDER = -2147220728,
	AXIS_E_WRONG_MEDIA_TYPE = -2147220727,
	AXIS_E_NO_PROTOCOL = -2147220720,
	AXIS_E_DIRECTX_VERSION = -2147220719,
	AXIS_E_SNAPSHOT = -2147220718,
	AXIS_E_AUDIO_NET_PROBLEMS = -2147220480,
	AXIS_E_AUDIO_MAX_CLIENTS = -2147220479,
	AXIS_E_AUDIO_CLOSE_RECEIVE = -2147220478,
	AXIS_E_AUDIO_CLOSE_TRANSMIT = -2147220477,
	AXIS_E_AUDIO_CLIENT = -2147220476,
	AXIS_E_AUDIO_PROXY = -2147220475,
	AXIS_E_AUDIO_MAX_REC_CLIENTS = -2147220474,
	AXIS_E_AUDIO_TRANSMIT = -2147220473,
	AXIS_E_AUDIO_FILE = -2147220472,
	AXIS_E_AUDIO_NO_MORE_STREAM = -2147220400,
	AXIS_U_AUDIO_STREAM = -2147220399,
	AXIS_U_AUDIO_RESTART_TRANSMIT = -2147220398,
	AXIS_U_AUDIO_MODE_RECONFIG = -2147220397,
	AXIS_U_AUDIO_TRANSMIT_FILE_DONE = -2147220395,
	AXIS_E_AUDIO_COMPONENT_MISSING = -2147220394,
	AXIS_E_RECORDING_COMPONENT_MISSING = -2147220384,
	AXIS_E_RECORDING_NO_STREAM = -2147220383,
	AXIS_E_RECORDING_STOP_FAILED = -2147220382,
	AXIS_E_WMF_MISSING = -2147220223,
	AXIS_E_FILE_ACCESS_DENIED = -2147220222,
	AXIS_E_OPERATION_CANCELLED = -2147220221,
	AXIS_N_NEW_ASPECT_RATIO = -2147219968,
	AXIS_N_RESTART = -2147219967,
	AXIS_N_VIDEO_RENDER_CHANGED = -2147219966,
	AXIS_N_STREAM_INFO = -2147219965,
	AXIS_E_LOGIN_FAILED = -2147219191,
	AXIS_E_NOT_ENOUGH_SPACE = -2147219184
}AXIS_ERROR;



// 작업
public:
// _IAxisMediaControlEvents

// 함수
//

	void OnError(long theErrorCode, LPCTSTR theErrorInfo)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theErrorCode, theErrorInfo);
	}
	void OnNewImage()
	{
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void OnClick(long X, long Y)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X, Y);
	}
	void OnDoubleClick(long nButton, long nShiftState, long fX, long fY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, nButton, nShiftState, fX, fY);
	}
	void OnMouseDown(long nButton, long nShiftState, long fX, long fY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, nButton, nShiftState, fX, fY);
	}
	void OnMouseUp(long nButton, long nShiftState, long fX, long fY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, nButton, nShiftState, fX, fY);
	}
	void OnMouseMove(long nButton, long nShiftState, long fX, long fY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, nButton, nShiftState, fX, fY);
	}
	void OnStatusChange(long theNewStatus, long theOldStatus)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theNewStatus, theOldStatus);
	}
	void OnJoyDown(long nButton)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, nButton);
	}
	void OnJoyUp(long nButton)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xA, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, nButton);
	}
	void OnMouseWheel(long nShiftState, long Delta, long fX, long fY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0xB, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, nShiftState, Delta, fX, fY);
	}
	void OnUserWindowChanged(short theID, long theXPos, long theYPos, long theWidth, long theHeight, long theState, BOOL isForced)
	{
		static BYTE parms[] = VTS_I2 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL;
		InvokeHelper(0xC, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theID, theXPos, theYPos, theWidth, theHeight, theState, isForced);
	}
	void OnUserObjectChanged(long theID, long theType, LPCTSTR theData, LPCTSTR theName, long theColor1, long theColor2, long theFlags, long theState, BOOL isForced)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL;
		InvokeHelper(0xD, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theID, theType, theData, theName, theColor1, theColor2, theFlags, theState, isForced);
	}
	void OnKeyDown(unsigned long KeyCode, long Flags, BOOL * Handled)
	{
		static BYTE parms[] = VTS_UNKNOWN VTS_I4 VTS_UNKNOWN;
		InvokeHelper(0xE, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, KeyCode, Flags, Handled);
	}
	void OnKeyUp(unsigned long KeyCode, long Flags, BOOL * Handled)
	{
		static BYTE parms[] = VTS_UNKNOWN VTS_I4 VTS_UNKNOWN;
		InvokeHelper(0xF, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, KeyCode, Flags, Handled);
	}
	void OnNewVideoSize(long theWidth, long theHeight)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theWidth, theHeight);
	}
	void OnEndOfStream(long theFlags)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theFlags);
	}
	void OnStreamInfo(__int64 theTimestamp, __int64 theHoldTime, __int64 theRenderMargin)
	{
		static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_UNKNOWN;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theTimestamp, theHoldTime, theRenderMargin);
	}

// 속성
//

// IAxisMediaControl

// 함수
//

	void Play()
	{
		InvokeHelper(0x65, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void Stop()
	{
		InvokeHelper(0x66, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void TogglePause()
	{
		InvokeHelper(0x67, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void StartRecord(LPCTSTR theFile)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x68, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theFile);
	}
	void StopRecord()
	{
		InvokeHelper(0x69, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void GetCurrentImage(long theFormat, VARIANT * theBuffer, long * theBufferSize)
	{
		static BYTE parms[] = VTS_I4 VTS_UNKNOWN VTS_UNKNOWN;
		InvokeHelper(0x6E, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theFormat, theBuffer, theBufferSize);
	}
	void SaveCurrentImage(long theFormat, LPCTSTR theFile)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR;
		InvokeHelper(0x6F, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theFormat, theFile);
	}
	long get_MPEG4VideoDecodingMode()
	{
		long result;
		InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_MPEG4VideoDecodingMode(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x70, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_DisplayMessages()
	{
		BOOL result;
		InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_DisplayMessages(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x71, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_MPEG4VideoRenderer()
	{
		long result;
		InvokeHelper(0x72, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_MPEG4VideoRenderer(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x72, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_EnableContextMenu()
	{
		BOOL result;
		InvokeHelper(0x73, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_EnableContextMenu(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x73, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_EnableRecording()
	{
		long result;
		InvokeHelper(0x74, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_EnableRecording(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x74, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_EnableReconnect()
	{
		BOOL result;
		InvokeHelper(0x75, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_EnableReconnect(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x75, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void AudioTransmitStart()
	{
		InvokeHelper(0x76, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void AudioReceiveStart()
	{
		InvokeHelper(0x77, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void AudioReceiveStop()
	{
		InvokeHelper(0x78, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void AudioTransmitStop()
	{
		InvokeHelper(0x79, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	CString get_MediaURL()
	{
		CString result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_MediaURL(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_AutoStart()
	{
		BOOL result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_AutoStart(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_UIMode()
	{
		CString result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_UIMode(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_Mute()
	{
		BOOL result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Mute(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Volume()
	{
		long result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Volume(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_MediaUsername()
	{
		CString result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_MediaUsername(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_MediaPassword()
	{
		CString result;
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_MediaPassword(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_NetworkTimeout()
	{
		long result;
		InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_NetworkTimeout(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_MediaType()
	{
		CString result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_MediaType(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_FullScreen()
	{
		BOOL result;
		InvokeHelper(0xA, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_FullScreen(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xA, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_MediaFile()
	{
		CString result;
		InvokeHelper(0xB, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_MediaFile(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xB, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_CurrentPosition()
	{
		long result;
		InvokeHelper(0xC, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_CurrentPosition(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xC, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Duration()
	{
		long result;
		InvokeHelper(0xD, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_FramesDrawn()
	{
		long result;
		InvokeHelper(0xE, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_Status()
	{
		long result;
		InvokeHelper(0xF, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	BOOL get_StretchToFit()
	{
		BOOL result;
		InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_StretchToFit(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_ShowToolbar()
	{
		BOOL result;
		InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ShowToolbar(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_ShowStatusBar()
	{
		BOOL result;
		InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ShowStatusBar(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_ToolbarConfiguration()
	{
		CString result;
		InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_ToolbarConfiguration(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_PTZControlURL()
	{
		CString result;
		InvokeHelper(0x1E, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_PTZControlURL(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x1E, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_MPEG2VideoDecodingMode()
	{
		long result;
		InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_MPEG2VideoDecodingMode(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x28, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_MotionConfigURL()
	{
		CString result;
		InvokeHelper(0x32, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_MotionConfigURL(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x32, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_MotionDataURL()
	{
		CString result;
		InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_MotionDataURL(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x33, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_AudioConfigURL()
	{
		CString result;
		InvokeHelper(0x3C, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_AudioConfigURL(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x3C, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_AudioReceiveURL()
	{
		CString result;
		InvokeHelper(0x3D, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_AudioReceiveURL(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x3D, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_AudioTransmitURL()
	{
		CString result;
		InvokeHelper(0x3E, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_AudioTransmitURL(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x3E, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_AudioFile()
	{
		CString result;
		InvokeHelper(0x3F, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_AudioFile(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x3F, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_AudioTransmitMute()
	{
		BOOL result;
		InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_AudioTransmitMute(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x40, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_AudioTransmitVolume()
	{
		long result;
		InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_AudioTransmitVolume(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x41, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_ClarifyEnabled()
	{
		BOOL result;
		InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ClarifyEnabled(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x50, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_ClarifyLevel()
	{
		long result;
		InvokeHelper(0x51, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_ClarifyLevel(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x51, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_ClarifyLicenseFile()
	{
		CString result;
		InvokeHelper(0x52, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_ClarifyLicenseFile(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x52, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_ClarifyValidatorsLocation()
	{
		CString result;
		InvokeHelper(0x53, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_ClarifyValidatorsLocation(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x53, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void StartRecordMedia(LPCTSTR theFile, long theFlags, LPCTSTR theMediaTypes)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR;
		InvokeHelper(0x7A, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theFile, theFlags, theMediaTypes);
	}
	void StopRecordMedia()
	{
		InvokeHelper(0x7B, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void StartTransmitMedia(LPCTSTR theFile, long theFlags)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4;
		InvokeHelper(0x7C, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theFile, theFlags);
	}
	void StopTransmitMedia()
	{
		InvokeHelper(0x7D, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	CString get_SvgDataUrl()
	{
		CString result;
		InvokeHelper(0x7E, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_SvgDataUrl(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x7E, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_JoystickConnected()
	{
		BOOL result;
		InvokeHelper(0x7F, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void SetImage(VARIANT * theImage, long * theSize)
	{
		static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN;
		InvokeHelper(0x80, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theImage, theSize);
	}
	void SetReconnectionStrategy(long theDuration1, long theConnectionInterval1, long theDuration2, long theConnectionInterval2, long theDuration3, long theConnectionInterval3, BOOL infiniteMode)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL;
		InvokeHelper(0x81, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theDuration1, theConnectionInterval1, theDuration2, theConnectionInterval2, theDuration3, theConnectionInterval3, infiniteMode);
	}
	BOOL get_EnableJoystick()
	{
		BOOL result;
		InvokeHelper(0x82, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_EnableJoystick(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x82, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_EnableAreaZoom()
	{
		BOOL result;
		InvokeHelper(0x83, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_EnableAreaZoom(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x83, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_ClientOverlay()
	{
		long result;
		InvokeHelper(0x84, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_ClientOverlay(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x84, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void put_Popups(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x85, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Popups()
	{
		long result;
		InvokeHelper(0x85, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_H264VideoDecodingMode()
	{
		long result;
		InvokeHelper(0x86, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_H264VideoDecodingMode(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x86, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_H264VideoRenderer()
	{
		long result;
		InvokeHelper(0x87, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_H264VideoRenderer(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x87, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	unsigned long get_ButtonColor()
	{
		unsigned long result;
		InvokeHelper(0x88, DISPATCH_PROPERTYGET, UNSIGNED LONG, (void*)&result, nullptr);
		return result;
	}
	void put_ButtonColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UNKNOWN;
		InvokeHelper(0x88, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void GetVersion(LPCTSTR theClsId, long * major, long * minor, long * build, long * revision)
	{
		static BYTE parms[] = VTS_BSTR VTS_UNKNOWN VTS_UNKNOWN VTS_UNKNOWN VTS_UNKNOWN;
		InvokeHelper(0x89, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theClsId, major, minor, build, revision);
	}
	BOOL get_OneClickZoom()
	{
		BOOL result;
		InvokeHelper(0x8A, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_OneClickZoom(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x8A, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void SetUserWindow(short theID, LPCTSTR theName, long theXPos, long theYPos, long theWidth, long theHeight, long theColor, long theOpacity, long theFlags)
	{
		static BYTE parms[] = VTS_I2 VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x8B, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theID, theName, theXPos, theYPos, theWidth, theHeight, theColor, theOpacity, theFlags);
	}
	void GetUserWindow(short theID)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0x8C, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theID);
	}
	void RemoveUserWindow(short theID)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0x8D, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theID);
	}
	long GetVersionPart(LPCTSTR theClsId, long thePartIndex)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4;
		InvokeHelper(0x8E, DISPATCH_METHOD, VT_I4, (void*)&result, parms, theClsId, thePartIndex);
		return result;
	}
	void put_MaintainAspectRatio(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x8F, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_MaintainAspectRatio()
	{
		BOOL result;
		InvokeHelper(0x8F, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	long get_MPEG4RTPDelay()
	{
		long result;
		InvokeHelper(0x90, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_MPEG4RTPDelay(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x90, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_MPEG4RTPDelayAudio()
	{
		long result;
		InvokeHelper(0x91, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_MPEG4RTPDelayAudio(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x91, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_H264RTPDelay()
	{
		long result;
		InvokeHelper(0x92, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_H264RTPDelay(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x92, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_H264RTPDelayAudio()
	{
		long result;
		InvokeHelper(0x93, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_H264RTPDelayAudio(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x93, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_BackgroundColor()
	{
		long result;
		InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_BackgroundColor(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x94, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_MJPEGVideoRenderer()
	{
		long result;
		InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_MJPEGVideoRenderer(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x95, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_MJPEGRTPDelay()
	{
		long result;
		InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_MJPEGRTPDelay(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x96, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_MJPEGRTPDelayAudio()
	{
		long result;
		InvokeHelper(0x97, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_MJPEGRTPDelayAudio(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x97, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_SynchronizeUsingRTCP()
	{
		BOOL result;
		InvokeHelper(0x98, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_SynchronizeUsingRTCP(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x98, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void BeginUserObject(long theID, long theType, LPCTSTR theName, long theColor1, long theColor2, long theNumPointsLimit, long theFlags)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x99, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theID, theType, theName, theColor1, theColor2, theNumPointsLimit, theFlags);
	}
	void EndUserObject(long theID)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x9A, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theID);
	}
	void SetUserObject(long theID, long theType, LPCTSTR theData, LPCTSTR theName, long theColor1, long theColor2, long theNumPointsLimit, long theFlags)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x9B, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theID, theType, theData, theName, theColor1, theColor2, theNumPointsLimit, theFlags);
	}
	void GetUserObject(long theID)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x9C, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theID);
	}
	void RemoveUserObject(long theID)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x9D, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theID);
	}
	void SetAdditionalMediaSource(LPCTSTR theURL, LPCTSTR theMediaUsername, LPCTSTR theMediaPassword, long theIndex, long theHttpPort)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4;
		InvokeHelper(0x9E, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theURL, theMediaUsername, theMediaPassword, theIndex, theHttpPort);
	}
	unsigned __int64 get_CurrentPosition64()
	{
		unsigned __int64 result;
		InvokeHelper(0x9F, DISPATCH_PROPERTYGET, UNSIGNED __INT64, (void*)&result, nullptr);
		return result;
	}
	void put_CurrentPosition64(unsigned __int64 newValue)
	{
		static BYTE parms[] = VTS_UNKNOWN;
		InvokeHelper(0x9F, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	unsigned __int64 get_StartPosition64()
	{
		unsigned __int64 result;
		InvokeHelper(0xA0, DISPATCH_PROPERTYGET, UNSIGNED __INT64, (void*)&result, nullptr);
		return result;
	}
	void put_StartPosition64(unsigned __int64 newValue)
	{
		static BYTE parms[] = VTS_UNKNOWN;
		InvokeHelper(0xA0, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	unsigned __int64 get_StopPosition64()
	{
		unsigned __int64 result;
		InvokeHelper(0xA1, DISPATCH_PROPERTYGET, UNSIGNED __INT64, (void*)&result, nullptr);
		return result;
	}
	void put_StopPosition64(unsigned __int64 newValue)
	{
		static BYTE parms[] = VTS_UNKNOWN;
		InvokeHelper(0xA1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void SetPositions32(long theCurrentPositionLow, long theCurrentPositionHigh, long theStartPositionLow, long theStartPositionHigh, long theStopPositionLow, long theStopPositionHigh)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0xA2, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theCurrentPositionLow, theCurrentPositionHigh, theStartPositionLow, theStartPositionHigh, theStopPositionLow, theStopPositionHigh);
	}
	long get_AudioOnlyRTPDelay()
	{
		long result;
		InvokeHelper(0xA3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_AudioOnlyRTPDelay(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xA3, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_EnableOverlays()
	{
		BOOL result;
		InvokeHelper(0xA4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_EnableOverlays(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xA4, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_PlaybackRate()
	{
		double result;
		InvokeHelper(0xA5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_PlaybackRate(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0xA5, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	unsigned __int64 get_Duration64()
	{
		unsigned __int64 result;
		InvokeHelper(0xA6, DISPATCH_PROPERTYGET, UNSIGNED __INT64, (void*)&result, nullptr);
		return result;
	}
	long get_VideoRenderer()
	{
		long result;
		InvokeHelper(0xA7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_VideoRenderer(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xA7, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_PTZPresetURL()
	{
		CString result;
		InvokeHelper(0xA8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_PTZPresetURL(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xA8, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_Language()
	{
		CString result;
		InvokeHelper(0xA9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_Language(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xA9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_PTZMapURL()
	{
		CString result;
		InvokeHelper(0xAA, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_PTZMapURL(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xAA, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_PlaybackMode()
	{
		long result;
		InvokeHelper(0xAB, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_PlaybackMode(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xAB, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_FocusWindowMode()
	{
		long result;
		InvokeHelper(0xAC, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_FocusWindowMode(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xAC, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_FocusWindowURL()
	{
		CString result;
		InvokeHelper(0xAD, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_FocusWindowURL(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xAD, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void FrameStep(long theStepLength)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xAE, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theStepLength);
	}
	void SetProxy(LPCTSTR theHost, LPCTSTR theUsername, LPCTSTR thePassword)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR;
		InvokeHelper(0xAF, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theHost, theUsername, thePassword);
	}
	BOOL get_H264EnableHWDecoding()
	{
		BOOL result;
		InvokeHelper(0xB0, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_H264EnableHWDecoding(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xB0, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void H264AssignHWDecodingAdaptor(long theAdaptor, long theAdaptorIndex)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0xB1, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theAdaptor, theAdaptorIndex);
	}
	void SetFullScreenPlacement(long theIndex, long theTotal, long theOptions)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0xB2, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theIndex, theTotal, theOptions);
	}
	long get_DewarpTiltOrientation()
	{
		long result;
		InvokeHelper(0xB3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_DewarpTiltOrientation(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xB3, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_DewarpLensProfile()
	{
		CString result;
		InvokeHelper(0xB4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_DewarpLensProfile(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xB4, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_DisableRTPBuffering()
	{
		BOOL result;
		InvokeHelper(0xB5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_DisableRTPBuffering(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xB5, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_H265VideoDecodingMode()
	{
		long result;
		InvokeHelper(0xB6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_H265VideoDecodingMode(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xB6, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_H265RTPDelay()
	{
		long result;
		InvokeHelper(0xB7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_H265RTPDelay(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xB7, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_H265RTPDelayAudio()
	{
		long result;
		InvokeHelper(0xB8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_H265RTPDelayAudio(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xB8, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_H265EnableHWDecoding()
	{
		BOOL result;
		InvokeHelper(0xB9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_H265EnableHWDecoding(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xB9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void H265AssignHWDecodingAdaptor(long theAdaptor, long theAdaptorIndex)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0xBA, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, theAdaptor, theAdaptorIndex);
	}
	double get_AudioGain()
	{
		double result;
		InvokeHelper(0xBB, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_AudioGain(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0xBB, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_EnableStreamInfo()
	{
		BOOL result;
		InvokeHelper(0xBC, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_EnableStreamInfo(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xBC, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

// 속성
//



};
