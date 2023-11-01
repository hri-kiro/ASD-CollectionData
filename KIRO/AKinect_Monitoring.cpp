// AKinect_Monitoring.cpp: 구현 파일
//

#include "pch.h"
#include "KIRO.h"
#include "AKinect_Monitoring.h"
#include "afxdialogex.h"

int		RecordDeviceFlag,
RecordDeviceIndex,
RecordFS,
RecordQ,
RecordNumbits,
//RecordNumChannels,
RecordBlockSize,
RecordMaximumSecond,
RecordErr;
char*   wavName;

PaStreamParameters  inputParameters,
outputParameters;
PaStream*           stream;
PaError             err = paNoError;
unsigned            delayCntr;
unsigned            numSamples;
unsigned            numBytes;
paTestData audio_data;
void audio_record_start();
void audio_record_stop();
//#include "pcm2wav.h"
int PCMtoWAV(char* input,
	char* output,
	int   NumChannels,
	int   NumBits,
	int   SamplingRate)
{
	FILE*			fin;
	FILE*			fout;
	size_t			len;
	WAVEHEADER		WaveHeader;
	unsigned int	Data_size;
	char*			char_buf;
	short*			short_buf;
	float*			float_buf;


	fin = fopen(input, "rb");
	fout = fopen(output, "wb");
	Data_size = 0;

	// RIFF
	memcpy(WaveHeader.Riff.ChunkID, "RIFF", 4);
	WaveHeader.Riff.ChunkSize = 0;
	memcpy(WaveHeader.Riff.Format, "WAVE", 4);

	//FMT
	memcpy(WaveHeader.fmt.ChunkID, "fmt ", 4);
	WaveHeader.fmt.ChunkSize = 0x10;
	WaveHeader.fmt.AudioFormat = WAVE_FORMAT_PCM;
	WaveHeader.fmt.NumChannels = NumChannels;
	WaveHeader.fmt.SampleRate = SamplingRate;
	WaveHeader.fmt.ByteRate = NumChannels * SamplingRate * (NumBits / 8);
	WaveHeader.fmt.BlockAlign = NumChannels * (NumBits / 8);
	WaveHeader.fmt.BitsPerSample = NumBits;

	//DATA
	memcpy(WaveHeader.Data.ChunkID, "data", 4);
	WaveHeader.Data.ChunkSize = 0;

	if (fin == NULL) // Failed to open
		return -1;

	if (NumBits == 8)
		while ((len = fread(&char_buf, sizeof(char), 1, fin)) != NULL)
		{
			fwrite(&char_buf, sizeof(char), 1, fout);
			Data_size++;
		}
	else if (NumBits == 16)
		while ((len = fread(&short_buf, sizeof(short), 1, fin)) != NULL)
		{
			fwrite(&short_buf, sizeof(short), 1, fout);
			// Data_size++;
			Data_size += 2;
		}
	else if (NumBits == 32)
		while ((len = fread(&float_buf, sizeof(char), 1, fin)) != NULL)
		{
			fwrite(&float_buf, sizeof(float), 1, fout);
			// Data_size++;
			Data_size += 4;
		}
	else
		return -2;
	fwrite(&WaveHeader, sizeof(WaveHeader), 1, fout);



	WaveHeader.Riff.ChunkSize = Data_size + 44 - 8;
	WaveHeader.Data.ChunkSize = Data_size;

	rewind(fout);
	fwrite(&WaveHeader, sizeof(WaveHeader), 1, fout);

	fclose(fin);
	fclose(fout);

	return 0;
}

static int threadFunctionWriteToRawFile(void* ptr)
{
	paTestData* pData = (paTestData*)ptr;

	/* Mark thread started */
	pData->threadSyncFlag = 0;

	while (1)
	{
		ring_buffer_size_t elementsInBuffer = PaUtil_GetRingBufferReadAvailable(&pData->ringBuffer);
		if ((elementsInBuffer >= pData->ringBuffer.bufferSize / NUM_WRITES_PER_BUFFER) ||
			pData->threadSyncFlag)
		{
			void* ptr[2] = { 0 };
			ring_buffer_size_t sizes[2] = { 0 };

			/* By using PaUtil_GetRingBufferReadRegions, we can read directly from the ring buffer */
			ring_buffer_size_t elementsRead = PaUtil_GetRingBufferReadRegions(&pData->ringBuffer, elementsInBuffer, ptr + 0, sizes + 0, ptr + 1, sizes + 1);
			if (elementsRead > 0)
			{
				int i;
				for (i = 0; i < 2 && ptr[i] != NULL; ++i)
				{
					fwrite(ptr[i], pData->ringBuffer.elementSizeBytes, sizes[i], pData->file);
				}
				PaUtil_AdvanceRingBufferReadIndex(&pData->ringBuffer, elementsRead);
			}

			if (pData->threadSyncFlag)
			{
				break;
			}
		}

		/* Sleep a little while... */
		Pa_Sleep(20);
	}

	pData->threadSyncFlag = 0;

	return 0;
}

typedef int(*ThreadFunctionType)(void*);

/* Start up a new thread in the given function, at the moment only Windows, but should be very easy to extend
to posix type OSs (Linux/Mac) */
static PaError startThread(paTestData* pData, ThreadFunctionType fn)
{
#ifdef _WIN32
	typedef unsigned(__stdcall* WinThreadFunctionType)(void*);
	pData->threadHandle = (void*)_beginthreadex(NULL, 0, (WinThreadFunctionType)fn, pData, CREATE_SUSPENDED, NULL);
	if (pData->threadHandle == NULL) return paUnanticipatedHostError;

	/* Set file thread to a little higher prio than normal */
	SetThreadPriority(pData->threadHandle, THREAD_PRIORITY_ABOVE_NORMAL);

	/* Start it up */
	pData->threadSyncFlag = 1;
	ResumeThread(pData->threadHandle);

#endif

	/* Wait for thread to startup */
	while (pData->threadSyncFlag) {
		Pa_Sleep(10);
	}

	return paNoError;
}

static int stopThread(paTestData* pData)
{
	pData->threadSyncFlag = 1;
	/* Wait for thread to stop */
	while (pData->threadSyncFlag) {
		Pa_Sleep(10);
	}
#ifdef _WIN32
	CloseHandle(pData->threadHandle);
	pData->threadHandle = 0;
#endif

	return paNoError;
}


/* This routine will be called by the PortAudio engine when audio is needed.
** It may be called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
static int recordCallback(const void *inputBuffer, void *outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void *userData)
{
	paTestData *data = (paTestData*)userData;
	ring_buffer_size_t elementsWriteable = PaUtil_GetRingBufferWriteAvailable(&data->ringBuffer);
	// ring_buffer_size_t elementsToWrite = min(elementsWriteable, (ring_buffer_size_t)(framesPerBuffer * NUM_CHANNELS));
	ring_buffer_size_t elementsToWrite = min(elementsWriteable, (ring_buffer_size_t)(framesPerBuffer * RecordNumChannels));
	const SAMPLE *rptr = (const SAMPLE*)inputBuffer;

	(void)outputBuffer; /* Prevent unused variable warnings. */
	(void)timeInfo;
	(void)statusFlags;
	(void)userData;

	data->frameIndex += PaUtil_WriteRingBuffer(&data->ringBuffer, rptr, elementsToWrite);

	return paContinue;
}

static unsigned NextPowerOf2(unsigned val)
{
	val--;
	val = (val >> 1) | val;
	val = (val >> 2) | val;
	val = (val >> 4) | val;
	val = (val >> 8) | val;
	val = (val >> 16) | val;
	return ++val;
}


//----audio



CFont g_editFont; // 폰트 저장
// AKinect_Monitoring 대화 상자
extern patient patient_info;
IMPLEMENT_DYNAMIC(AKinect_Monitoring, CDialogEx)

AKinect_Monitoring::AKinect_Monitoring(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RECORD_CAM, pParent)
{
	AfxEnableControlContainer();
}

AKinect_Monitoring::~AKinect_Monitoring()
{
}

void AKinect_Monitoring::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Edit_Timer);
	DDX_Control(pDX, IDC_EDIT_STATUS, m_Edit_Status);
	DDX_Control(pDX, IDC_EDIT2, m_edit_ResearchNumber);
	DDX_Control(pDX, IDC_COMBO1, m_cADOS);
	DDX_Control(pDX, IDC_COMBO2, m_cBedevel);
	DDX_Control(pDX, IDC_AXISMEDIACONTROL1, m_AMC_1);
	DDX_Control(pDX, IDC_AXISMEDIACONTROL2, m_AMC_2);
	DDX_Control(pDX, IDC_AXISMEDIACONTROL3, m_AMC_3);
	DDX_Control(pDX, IDC_AXISMEDIACONTROL4, m_AMC_4);
	DDX_Control(pDX, IDC_AXISMEDIACONTROL5, m_AMC_5);
	DDX_Control(pDX, IDC_AXISMEDIACONTROL6, m_AMC_6);
	DDX_Control(pDX, IDC_AXISMEDIACONTROL7, m_AMC_7);
}


BEGIN_MESSAGE_MAP(AKinect_Monitoring, CDialogEx)
	ON_BN_CLICKED(IDC_CAMON, &AKinect_Monitoring::OnBnClickedCamon)
	ON_BN_CLICKED(IDC_RECORDSTART, &AKinect_Monitoring::OnBnClickedRecordstart)
	ON_BN_CLICKED(IDC_RECORDSTOP, &AKinect_Monitoring::OnBnClickedRecordstop)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_IPCAMON, &AKinect_Monitoring::OnBnClickedIpcamon)
	ON_BN_CLICKED(IDC_AUDIOON, &AKinect_Monitoring::OnBnClickedAudioon)
	ON_BN_CLICKED(IDC_BUTTON3, &AKinect_Monitoring::OnBnClickedButton3)
END_MESSAGE_MAP()


// AKinect_Monitoring 메시지 처리기

BOOL AKinect_Monitoring::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	/*m_cADOS.AddString(TEXT("1"));
	m_cADOS.AddString(TEXT("2"));
	m_cADOS.AddString(TEXT("T"));
	m_cBedevel.AddString(TEXT("1"));
	m_cBedevel.AddString(TEXT("2"));
	m_cBedevel.AddString(TEXT("3"));
	m_cBedevel.AddString(TEXT("4"));*/
	SetDlgItemText(IDC_COMBO1, patient_info.Ados_Type);
	SetDlgItemText(IDC_COMBO2, patient_info.Bedevel_Type);
	SetDlgItemText(IDC_EDIT2, patient_info.Research_Number);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	g_editFont.CreatePointFont(180, TEXT("굴림"));
	m_Edit_Timer.SetFont(&g_editFont);
	CString sTime;
	sTime.Format(_T("%d : %02d : %02d"), 0, 0, 0);
	m_Edit_Timer.SetWindowTextA(sTime);
	timer = 0;

	m_ipText_1 = _T("192.168.0.2");//1
	m_ipText_2 = _T("192.168.0.32");
	m_ipText_3 = _T("192.168.0.33");
	m_ipText_4 = _T("192.168.0.25");
	m_ipText_5 = _T("192.168.0.23");//1
	m_ipText_6 = _T("192.168.0.26");
	m_ipText_7 = _T("192.168.0.28");
	m_type = _T("h264");
	//m_type = _T("mpeg4");
	m_user = _T("root");
	m_pass = _T("root");

	m_File_1 = _T("AMC_Recording_1.asf");
	m_File_2 = _T("AMC_Recording_2.asf");
	m_File_3 = _T("AMC_Recording_3.asf");
	m_File_4 = _T("AMC_Recording_4.asf");
	m_File_5 = _T("AMC_Recording_5.asf");
	m_File_6 = _T("AMC_Recording_6.asf");
	m_File_7 = _T("AMC_Recording_7.asf");


	try
	{
		// We set AMC properties here for clarity
		m_AMC_1.put_StretchToFit(TRUE);
		m_AMC_1.put_MaintainAspectRatio(TRUE);
		m_AMC_1.put_ShowStatusBar(TRUE);
		m_AMC_1.put_BackgroundColor(RGB(0, 0, 0)); // black
		m_AMC_1.put_VideoRenderer(AMC_VIDEO_RENDERER_EVR);
		m_AMC_1.put_EnableOverlays(TRUE);

		// Configure context menu
		m_AMC_1.put_EnableContextMenu(TRUE);
		//"-pixcount" to remove pixel counter from context menu
		m_AMC_1.put_ToolbarConfiguration(_T("+play,+fullscreen,-settings"));

		// AMC messaging setting
		m_AMC_1.put_Popups(
			AMC_POPUPS_LOGIN_DIALOG // Allow login dialog and show
			| AMC_POPUPS_NO_VIDEO     // "No Video" message when stopped
			//| AMC_POPUPS_MESSAGES     // Yellow-balloon notification
		);

		m_AMC_1.put_UIMode(_T("digital-zoom"));

	}
	catch (COleDispatchException *e)
	{
		MessageBox(e->m_strDescription);
	}

	try
	{
		// We set AMC properties here for clarity
		m_AMC_2.put_StretchToFit(TRUE);
		m_AMC_2.put_MaintainAspectRatio(TRUE);
		m_AMC_2.put_ShowStatusBar(TRUE);
		m_AMC_2.put_BackgroundColor(RGB(0, 0, 0)); // black
		m_AMC_2.put_VideoRenderer(AMC_VIDEO_RENDERER_EVR);
		m_AMC_2.put_EnableOverlays(TRUE);

		// Configure context menu
		m_AMC_2.put_EnableContextMenu(TRUE);
		//"-pixcount" to remove pixel counter from context menu
		m_AMC_2.put_ToolbarConfiguration(_T("+play,+fullscreen,-settings"));

		// AMC messaging setting
		m_AMC_2.put_Popups(
			AMC_POPUPS_LOGIN_DIALOG // Allow login dialog and show
			| AMC_POPUPS_NO_VIDEO     // "No Video" message when stopped
			//| AMC_POPUPS_MESSAGES     // Yellow-balloon notification
		);

		m_AMC_2.put_UIMode(_T("digital-zoom"));

	}
	catch (COleDispatchException *e)
	{
		MessageBox(e->m_strDescription);
	}

	try
	{
		// We set AMC properties here for clarity
		m_AMC_3.put_StretchToFit(TRUE);
		m_AMC_3.put_MaintainAspectRatio(TRUE);
		m_AMC_3.put_ShowStatusBar(TRUE);
		m_AMC_3.put_BackgroundColor(RGB(0, 0, 0)); // black
		m_AMC_3.put_VideoRenderer(AMC_VIDEO_RENDERER_EVR);
		m_AMC_3.put_EnableOverlays(TRUE);

		// Configure context menu
		m_AMC_3.put_EnableContextMenu(TRUE);
		//"-pixcount" to remove pixel counter from context menu
		m_AMC_3.put_ToolbarConfiguration(_T("+play,+fullscreen,-settings"));

		// AMC messaging setting
		m_AMC_3.put_Popups(
			AMC_POPUPS_LOGIN_DIALOG // Allow login dialog and show
			| AMC_POPUPS_NO_VIDEO     // "No Video" message when stopped
			//| AMC_POPUPS_MESSAGES     // Yellow-balloon notification
		);

		m_AMC_3.put_UIMode(_T("digital-zoom"));

	}
	catch (COleDispatchException *e)
	{
		MessageBox(e->m_strDescription);
	}

	try
	{
		// We set AMC properties here for clarity
		m_AMC_4.put_StretchToFit(TRUE);
		m_AMC_4.put_MaintainAspectRatio(TRUE);
		m_AMC_4.put_ShowStatusBar(TRUE);
		m_AMC_4.put_BackgroundColor(RGB(0, 0, 0)); // black
		m_AMC_4.put_VideoRenderer(AMC_VIDEO_RENDERER_EVR);
		m_AMC_4.put_EnableOverlays(TRUE);

		// Configure context menu
		m_AMC_4.put_EnableContextMenu(TRUE);
		//"-pixcount" to remove pixel counter from context menu
		m_AMC_4.put_ToolbarConfiguration(_T("+play,+fullscreen,-settings"));

		// AMC messaging setting
		m_AMC_4.put_Popups(
			AMC_POPUPS_LOGIN_DIALOG // Allow login dialog and show
			| AMC_POPUPS_NO_VIDEO     // "No Video" message when stopped
			//| AMC_POPUPS_MESSAGES     // Yellow-balloon notification
		);

		m_AMC_4.put_UIMode(_T("digital-zoom"));

	}
	catch (COleDispatchException *e)
	{
		MessageBox(e->m_strDescription);
	}
	try
	{
		// We set AMC properties here for clarity
		m_AMC_5.put_StretchToFit(TRUE);
		m_AMC_5.put_MaintainAspectRatio(TRUE);
		m_AMC_5.put_ShowStatusBar(TRUE);
		m_AMC_5.put_BackgroundColor(RGB(0, 0, 0)); // black
		m_AMC_5.put_VideoRenderer(AMC_VIDEO_RENDERER_EVR);
		m_AMC_5.put_EnableOverlays(TRUE);

		// Configure context menu
		m_AMC_5.put_EnableContextMenu(TRUE);
		//"-pixcount" to remove pixel counter from context menu
		m_AMC_5.put_ToolbarConfiguration(_T("+play,+fullscreen,-settings"));

		// AMC messaging setting
		m_AMC_5.put_Popups(
			AMC_POPUPS_LOGIN_DIALOG // Allow login dialog and show
			| AMC_POPUPS_NO_VIDEO     // "No Video" message when stopped
			//| AMC_POPUPS_MESSAGES     // Yellow-balloon notification
		);

		m_AMC_5.put_UIMode(_T("digital-zoom"));

	}
	catch (COleDispatchException *e)
	{
		MessageBox(e->m_strDescription);
	}
	try
	{
		// We set AMC properties here for clarity
		m_AMC_6.put_StretchToFit(TRUE);
		m_AMC_6.put_MaintainAspectRatio(TRUE);
		m_AMC_6.put_ShowStatusBar(TRUE);
		m_AMC_6.put_BackgroundColor(RGB(0, 0, 0)); // black
		m_AMC_6.put_VideoRenderer(AMC_VIDEO_RENDERER_EVR);
		m_AMC_6.put_EnableOverlays(TRUE);

		// Configure context menu
		m_AMC_6.put_EnableContextMenu(TRUE);
		//"-pixcount" to remove pixel counter from context menu
		m_AMC_6.put_ToolbarConfiguration(_T("+play,+fullscreen,-settings"));

		// AMC messaging setting
		m_AMC_6.put_Popups(
			AMC_POPUPS_LOGIN_DIALOG // Allow login dialog and show
			| AMC_POPUPS_NO_VIDEO     // "No Video" message when stopped
			//| AMC_POPUPS_MESSAGES     // Yellow-balloon notification
		);

		m_AMC_6.put_UIMode(_T("digital-zoom"));

	}
	//audio_data = { 0 };
	catch (COleDispatchException *e)
	{
		MessageBox(e->m_strDescription);
	}
	try
	{
		// We set AMC properties here for clarity
		m_AMC_7.put_StretchToFit(TRUE);
		m_AMC_7.put_MaintainAspectRatio(TRUE);
		m_AMC_7.put_ShowStatusBar(TRUE);
		m_AMC_7.put_BackgroundColor(RGB(0, 0, 0)); // black
		m_AMC_7.put_VideoRenderer(AMC_VIDEO_RENDERER_EVR);
		m_AMC_7.put_EnableOverlays(TRUE);

		// Configure context menu
		m_AMC_7.put_EnableContextMenu(TRUE);
		//"-pixcount" to remove pixel counter from context menu
		m_AMC_7.put_ToolbarConfiguration(_T("+play,+fullscreen,-settings"));

		// AMC messaging setting
		m_AMC_7.put_Popups(
			AMC_POPUPS_LOGIN_DIALOG // Allow login dialog and show
			| AMC_POPUPS_NO_VIDEO     // "No Video" message when stopped
			//| AMC_POPUPS_MESSAGES     // Yellow-balloon notification
		);

		m_AMC_7.put_UIMode(_T("digital-zoom"));

	}
	//audio_data = { 0 };
	catch (COleDispatchException* e)
	{
		MessageBox(e->m_strDescription);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void AKinect_Monitoring::OnBnClickedCamon()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//patient patient_info;
	//GetDlgItemText(IDC_COMBO1, patient_info.Ados_Type);
	//GetDlgItemText(IDC_COMBO2, patient_info.Bedevel_Type);

	for (int i = 0; i < 8; i++)
	{
		CString str;
		str.Format(_T("%d"), i + 1);
		patient_info.video_path[i] = patient_info.folder_path[i] + patient_info.Research_Number + _T("_ADOS_") + patient_info.Ados_Type + _T("_BEDEVEL_") + patient_info.Bedevel_Type + _T("_kinect") + str;// +_T(".mkv");

	}
	m_File_1 = patient_info.folder_path[0] + patient_info.Research_Number + _T("_ADOS_") + patient_info.Ados_Type + _T("_BEDEVEL_") + patient_info.Bedevel_Type + _T("_ipcam_1.asf");
	m_File_2 = patient_info.folder_path[0] + patient_info.Research_Number + _T("_ADOS_") + patient_info.Ados_Type + _T("_BEDEVEL_") + patient_info.Bedevel_Type + _T("_ipcam_2.asf");
	m_File_3 = patient_info.folder_path[0] + patient_info.Research_Number + _T("_ADOS_") + patient_info.Ados_Type + _T("_BEDEVEL_") + patient_info.Bedevel_Type + _T("_ipcam_3.asf");
	m_File_4 = patient_info.folder_path[0] + patient_info.Research_Number + _T("_ADOS_") + patient_info.Ados_Type + _T("_BEDEVEL_") + patient_info.Bedevel_Type + _T("_ipcam_4.asf");
	m_File_5 = patient_info.folder_path[0] + patient_info.Research_Number + _T("_ADOS_") + patient_info.Ados_Type + _T("_BEDEVEL_") + patient_info.Bedevel_Type + _T("_ipcam_5.asf");
	m_File_6 = patient_info.folder_path[0] + patient_info.Research_Number + _T("_ADOS_") + patient_info.Ados_Type + _T("_BEDEVEL_") + patient_info.Bedevel_Type + _T("_ipcam_6.asf");
	m_File_7 = patient_info.folder_path[0] + patient_info.Research_Number + _T("_ADOS_") + patient_info.Ados_Type + _T("_BEDEVEL_") + patient_info.Bedevel_Type + _T("_ipcam_7.asf");

	patient_info.audio_full_path = patient_info.folder_path[0] + patient_info.Research_Number + _T("_ADOS_") + patient_info.Ados_Type + _T("_BEDEVEL_") + patient_info.Bedevel_Type + _T("_audio.pcm");
	/*m_File_1 = patient_info.folder_path[0] + patient_info.Research_Number + _T("_ADOS") + patient_info.Ados_Type + _T("_BEDEVEL") + patient_info.Bedevel_Type + _T("ipcam_1.mp4");
	m_File_2 = patient_info.folder_path[0] + patient_info.Research_Number + _T("_ADOS") + patient_info.Ados_Type + _T("_BEDEVEL") + patient_info.Bedevel_Type + _T("ipcam_2.mp4");
	m_File_3 = patient_info.folder_path[0] + patient_info.Research_Number + _T("_ADOS") + patient_info.Ados_Type + _T("_BEDEVEL") + patient_info.Bedevel_Type + _T("ipcam_3.mp4");
	m_File_4 = patient_info.folder_path[0] + patient_info.Research_Number + _T("_ADOS") + patient_info.Ados_Type + _T("_BEDEVEL") + patient_info.Bedevel_Type + _T("ipcam_4.mp4");
	m_File_5 = patient_info.folder_path[0] + patient_info.Research_Number + _T("_ADOS") + patient_info.Ados_Type + _T("_BEDEVEL") + patient_info.Bedevel_Type + _T("ipcam_5.mp4");
	m_File_6 = patient_info.folder_path[0] + patient_info.Research_Number + _T("_ADOS") + patient_info.Ados_Type + _T("_BEDEVEL") + patient_info.Bedevel_Type + _T("ipcam_6.mp4"); */
	//사용 후, 마지막에 동적할당 된 메모리를 제거해야 합니다.	
	CString v_path1,v_path2,v_path3,v_path4,v_path5,v_path6, v_path7, v_path8;
	CString video_audio_path = patient_info.folder_path[8] + patient_info.Research_Number + _T("_ADOS_") + patient_info.Ados_Type + _T("_BEDEVEL_") + patient_info.Bedevel_Type + _T("_kinect1");
	v_path1 = patient_info.video_path[0] + _T(".mkv");
	kinect1.set_device_num(0);
	kinect1.set_subordinate(720);
	kinect1.set_video_path(LPSTR(LPCTSTR(v_path1))); // "Z:\\v1.mkv" 네트워크드라이브 경로

	v_path2 = patient_info.video_path[1] + _T(".mkv");
	kinect2.set_device_num(1);
	kinect2.set_subordinate(360);
	kinect2.set_video_path(LPSTR(LPCTSTR(v_path2)));

	v_path3 = patient_info.video_path[2] + _T(".mkv");
	kinect3.set_device_num(2);
	kinect3.set_master();
	kinect3.set_video_path(LPSTR(LPCTSTR(v_path3)));

	v_path4 = patient_info.video_path[3] + _T(".mkv");
	kinect4.set_device_num(3);
	kinect4.set_subordinate(540);
	kinect4.set_video_path(LPSTR(LPCTSTR(v_path4)));

	v_path5 = patient_info.video_path[4] + _T(".mkv");
	kinect5.set_device_num(4);
	kinect5.set_subordinate(180);
	kinect5.set_video_path(LPSTR(LPCTSTR(v_path5)));

	v_path6 = patient_info.video_path[5] + _T(".mkv");
	kinect6.set_device_num(5);
	kinect6.set_subordinate(1080);
	kinect6.set_video_path(LPSTR(LPCTSTR(v_path6)));

	v_path7 = patient_info.video_path[6] + _T(".mkv");
	kinect7.set_device_num(6);
	kinect7.set_subordinate(900);
	kinect7.set_video_path(LPSTR(LPCTSTR(v_path7)));

	v_path8 = patient_info.video_path[7] + _T(".mkv");
	kinect8.set_device_num(7);
	kinect8.set_subordinate(1260);
	kinect8.set_video_path(LPSTR(LPCTSTR(v_path8)));

	patient_info.video_full_path[0] = v_path1;
	patient_info.video_full_path[1] = v_path2;
	patient_info.video_full_path[2] = v_path3;
	patient_info.video_full_path[3] = v_path4;
	patient_info.video_full_path[4] = v_path5;
	patient_info.video_full_path[5] = v_path6;
	patient_info.video_full_path[6] = v_path7;
	patient_info.video_full_path[7] = v_path8;
	patient_info.video_full_path[8] = video_audio_path + _T("_audio.mkv");

	int result = 1;
	//kinect1.Kinect_Open(0);
	//kinect1.get_device_serial();
	if (result != kinect1.kinect_init())
	{
		cout << "1번 키넥트 연결 실패" << endl;
	}

	int nLen = m_Edit_Status.GetWindowTextLength();
	m_Edit_Status.SetSel(nLen, nLen);
	m_Edit_Status.SetWindowTextA(TEXT("1번 키넥트 연결 성공\r\n"));

	//kinect2.Kinect_Open(1);
	//kinect2.get_device_serial();
	if (result != kinect2.kinect_init())
	{
		cout << "2번 키넥트 연결 실패" << endl;
	}

	nLen = m_Edit_Status.GetWindowTextLength();
	m_Edit_Status.SetSel(nLen, nLen);
	m_Edit_Status.ReplaceSel(TEXT("2번 키넥트 연결 성공\r\n"));

	//kinect3.Kinect_Open(2);
	//kinect3.get_device_serial();
	if (result != kinect3.kinect_init())
	{
		cout << "3번 키넥트 연결 실패" << endl;
	}

	nLen = m_Edit_Status.GetWindowTextLength();
	m_Edit_Status.SetSel(nLen, nLen);
	m_Edit_Status.ReplaceSel(TEXT("3번 키넥트 연결 성공\r\n"));

	//kinect4.Kinect_Open(3);
	//kinect4.get_device_serial();
	if (result != kinect4.kinect_init())
	{
		cout << "4번 키넥트 연결 실패" << endl;
	}

	nLen = m_Edit_Status.GetWindowTextLength();
	m_Edit_Status.SetSel(nLen, nLen);
	m_Edit_Status.ReplaceSel(TEXT("4번 키넥트 연결 성공\r\n"));

	//kinect5.Kinect_Open(4);
	//kinect5.get_device_serial();
	if (result != kinect5.kinect_init())
	{
		cout << "5번 키넥트 연결 실패" << endl;
	}

	nLen = m_Edit_Status.GetWindowTextLength();
	m_Edit_Status.SetSel(nLen, nLen);
	m_Edit_Status.ReplaceSel(TEXT("5번 키넥트 연결 성공\r\n"));

	//kinect6.Kinect_Open(5);
	//kinect6.get_device_serial();
	if (result != kinect6.kinect_init())
	{
		cout << "6번 키넥트 연결 실패" << endl;
	}

	nLen = m_Edit_Status.GetWindowTextLength();
	m_Edit_Status.SetSel(nLen, nLen);
	m_Edit_Status.ReplaceSel(TEXT("6번 키넥트 연결 성공\r\n"));

	if (result != kinect7.kinect_init())
	{
		cout << "7번 키넥트 연결 실패" << endl;
	}

	nLen = m_Edit_Status.GetWindowTextLength();
	m_Edit_Status.SetSel(nLen, nLen);
	m_Edit_Status.ReplaceSel(TEXT("7번 키넥트 연결 성공\r\n"));

	if (result != kinect8.kinect_init())
	{
		cout << "8번 키넥트 연결 실패" << endl;
	}

	nLen = m_Edit_Status.GetWindowTextLength();
	m_Edit_Status.SetSel(nLen, nLen);
	m_Edit_Status.ReplaceSel(TEXT("8번 키넥트 연결 성공\r\n"));
}


void AKinect_Monitoring::OnBnClickedRecordstart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	kinect3.Start_Recording();
	kinect2.Start_Recording();
	kinect1.Start_Recording();
	kinect4.Start_Recording();
	kinect5.Start_Recording();
	kinect6.Start_Recording();
	kinect7.Start_Recording();
	kinect8.Start_Recording();
	m_Threadcam1 = true;
	m_Threadcam2 = true;
	m_Threadcam3 = true;
	m_Threadcam4 = true;
	m_Threadcam5 = true;
	m_Threadcam6 = true;
	m_Threadcam7 = true;
	m_Threadcam8 = true;
	CWinThread *pThreadcam1 = ::AfxBeginThread(threadCAM1, this);
	CWinThread *pThreadcam2 = ::AfxBeginThread(threadCAM2, this);
	CWinThread *pThreadcam3 = ::AfxBeginThread(threadCAM3, this);
	CWinThread *pThreadcam4 = ::AfxBeginThread(threadCAM4, this);
	CWinThread *pThreadcam5 = ::AfxBeginThread(threadCAM5, this);
	CWinThread *pThreadcam6 = ::AfxBeginThread(threadCAM6, this);
	CWinThread* pThreadcam7 = ::AfxBeginThread(threadCAM7, this);
	CWinThread* pThreadcam8 = ::AfxBeginThread(threadCAM8, this);
	int nLen = m_Edit_Status.GetWindowTextLength();
	m_Edit_Status.SetSel(nLen, nLen);
	m_Edit_Status.SetWindowTextA(TEXT("녹화시작\r\n"));
	SetTimer(FRAME_CNT, 1000, 0);

	this->UpdateData(true);

	int	aRecMode = AMC_RECORD_FLAG_AUDIO_VIDEO;
	if (m_type.CompareNoCase((CString)"mjpeg") == 0)
	{
		// Audio recording is not supported for Motion JPEG over HTTP
		aRecMode = AMC_RECORD_FLAG_VIDEO;
	}

	try
	{
		// Starts to record to the specified file.
		m_AMC_1.StartRecordMedia(m_File_1, aRecMode, (CString)"");
	}
	catch (COleDispatchException *e)
	{
		if (e->m_scError == E_INVALIDARG)
		{
			MessageBox((CString)"Invalid parameters.");
		}
		else if (e->m_scError == E_ACCESSDENIED)
		{
			MessageBox((CString)"Access denied.");
		}
		else
		{
			MessageBox(e->m_strDescription);
		}
	}

	try
	{
		// Starts to record to the specified file.
		m_AMC_2.StartRecordMedia(m_File_2, aRecMode, (CString)"");
	}
	catch (COleDispatchException *e)
	{
		if (e->m_scError == E_INVALIDARG)
		{
			MessageBox((CString)"Invalid parameters.");
		}
		else if (e->m_scError == E_ACCESSDENIED)
		{
			MessageBox((CString)"Access denied.");
		}
		else
		{
			MessageBox(e->m_strDescription);
		}
	}

	try
	{
		// Starts to record to the specified file.
		m_AMC_3.StartRecordMedia(m_File_3, aRecMode, (CString)"");
	}
	catch (COleDispatchException *e)
	{
		if (e->m_scError == E_INVALIDARG)
		{
			MessageBox((CString)"Invalid parameters.");
		}
		else if (e->m_scError == E_ACCESSDENIED)
		{
			MessageBox((CString)"Access denied.");
		}
		else
		{
			MessageBox(e->m_strDescription);
		}
	}

	try
	{
		// Starts to record to the specified file.
		m_AMC_4.StartRecordMedia(m_File_4, aRecMode, (CString)"");
	}
	catch (COleDispatchException *e)
	{
		if (e->m_scError == E_INVALIDARG)
		{
			MessageBox((CString)"Invalid parameters.");
		}
		else if (e->m_scError == E_ACCESSDENIED)
		{
			MessageBox((CString)"Access denied.");
		}
		else
		{
			MessageBox(e->m_strDescription);
		}
	}
	try
	{
		// Starts to record to the specified file.
		m_AMC_5.StartRecordMedia(m_File_5, aRecMode, (CString)"");
	}
	catch (COleDispatchException *e)
	{
		if (e->m_scError == E_INVALIDARG)
		{
			MessageBox((CString)"Invalid parameters.");
		}
		else if (e->m_scError == E_ACCESSDENIED)
		{
			MessageBox((CString)"Access denied.");
		}
		else
		{
			MessageBox(e->m_strDescription);
		}
	}
	try
	{
		// Starts to record to the specified file.
		m_AMC_6.StartRecordMedia(m_File_6, aRecMode, (CString)"");
	}
	catch (COleDispatchException *e)
	{
		if (e->m_scError == E_INVALIDARG)
		{
			MessageBox((CString)"Invalid parameters.");
		}
		else if (e->m_scError == E_ACCESSDENIED)
		{
			MessageBox((CString)"Access denied.");
		}
		else
		{
			MessageBox(e->m_strDescription);
		}
	}
	try
	{
		// Starts to record to the specified file.
		m_AMC_7.StartRecordMedia(m_File_7, aRecMode, (CString)"");
	}
	catch (COleDispatchException* e)
	{
		if (e->m_scError == E_INVALIDARG)
		{
			MessageBox((CString)"Invalid parameters.");
		}
		else if (e->m_scError == E_ACCESSDENIED)
		{
			MessageBox((CString)"Access denied.");
		}
		else
		{
			MessageBox(e->m_strDescription);
		}
	}
	nLen = m_Edit_Status.GetWindowTextLength();
	m_Edit_Status.SetSel(nLen, nLen);
	m_Edit_Status.SetWindowTextA(TEXT("녹화시작\r\n"));

	audio_record_start();
}


void AKinect_Monitoring::OnBnClickedRecordstop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	kinect1.Stop_Recording();
	kinect2.Stop_Recording();
	kinect3.Stop_Recording();
	kinect4.Stop_Recording();
	kinect5.Stop_Recording();
	kinect6.Stop_Recording();
	kinect7.Stop_Recording();
	kinect8.Stop_Recording();
	cout << "종료" << endl;
	KillTimer(FRAME_CNT);
	KillTimer(CLOCK_CNT);
	cout << "kinect1 total frame : " << kinect1.total_frame << endl;
	cout << "kinect2 total frame : " << kinect2.total_frame << endl;
	cout << "kinect3 total frame : " << kinect3.total_frame << endl;
	cout << "kinect4 total frame : " << kinect4.total_frame << endl;
	cout << "kinect5 total frame : " << kinect5.total_frame << endl;
	cout << "kinect6 total frame : " << kinect6.total_frame << endl;
	cout << "kinect7 total frame : " << kinect6.total_frame << endl;
	cout << "kinect8 total frame : " << kinect6.total_frame << endl;

	int nLen = m_Edit_Status.GetWindowTextLength();
	m_Edit_Status.SetSel(nLen, nLen);
	m_Edit_Status.SetWindowTextA(TEXT("녹화종료\r\n"));
	m_AMC_1.StopRecordMedia();
	m_AMC_2.StopRecordMedia();
	m_AMC_3.StopRecordMedia();
	m_AMC_4.StopRecordMedia();
	m_AMC_5.StopRecordMedia();
	m_AMC_6.StopRecordMedia();
	m_AMC_7.StopRecordMedia();
	nLen = m_Edit_Status.GetWindowTextLength();
	m_Edit_Status.SetSel(nLen, nLen);
	m_Edit_Status.SetWindowTextA(TEXT("ip카메라 녹화종료\r\n"));

	audio_record_stop();
	m_Edit_Status.SetSel(nLen, nLen);
	m_Edit_Status.SetWindowTextA(TEXT("음성 녹음종료\r\n"));

	

}

UINT AKinect_Monitoring::threadCAM1(LPVOID pParam)
{
	AKinect_Monitoring* pDlg = ((AKinect_Monitoring*)pParam);
	UINT Retval = pDlg->kinect1.Camera_On();
	SetEvent(pDlg->m_ThreadCAM1);
	return Retval;
}
UINT AKinect_Monitoring::threadCAM2(LPVOID pParam)
{
	AKinect_Monitoring* pDlg = ((AKinect_Monitoring*)pParam);
	UINT Retval = pDlg->kinect2.Camera_On();
	SetEvent(pDlg->m_ThreadCAM2);
	return Retval;
}
UINT AKinect_Monitoring::threadCAM3(LPVOID pParam)
{
	AKinect_Monitoring* pDlg = ((AKinect_Monitoring*)pParam);
	UINT Retval = pDlg->kinect3.Camera_On();
	SetEvent(pDlg->m_ThreadCAM3);
	return Retval;
}
UINT AKinect_Monitoring::threadCAM4(LPVOID pParam)
{
	AKinect_Monitoring* pDlg = ((AKinect_Monitoring*)pParam);
	UINT Retval = pDlg->kinect4.Camera_On();
	SetEvent(pDlg->m_ThreadCAM4);
	return Retval;
}
UINT AKinect_Monitoring::threadCAM5(LPVOID pParam)
{
	AKinect_Monitoring* pDlg = ((AKinect_Monitoring*)pParam);
	UINT Retval = pDlg->kinect5.Camera_On();
	SetEvent(pDlg->m_ThreadCAM5);
	return Retval;
}
UINT AKinect_Monitoring::threadCAM6(LPVOID pParam)
{
	AKinect_Monitoring* pDlg = ((AKinect_Monitoring*)pParam);
	UINT Retval = pDlg->kinect6.Camera_On();
	SetEvent(pDlg->m_ThreadCAM6);
	return Retval;
}
UINT AKinect_Monitoring::threadCAM7(LPVOID pParam)
{
	AKinect_Monitoring* pDlg = ((AKinect_Monitoring*)pParam);
	UINT Retval = pDlg->kinect7.Camera_On();
	SetEvent(pDlg->m_ThreadCAM7);
	return Retval;
}
UINT AKinect_Monitoring::threadCAM8(LPVOID pParam)
{
	AKinect_Monitoring* pDlg = ((AKinect_Monitoring*)pParam);
	UINT Retval = pDlg->kinect8.Camera_On();
	SetEvent(pDlg->m_ThreadCAM6);
	return Retval;
}
void AKinect_Monitoring::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nIDEvent)
	{
	case FRAME_CNT:
		/*cout << "kinect1 : " << kinect1.fps << endl;
		cout << "kinect2 : " << kinect2.fps << endl;
		cout << "kinect3 : " << kinect3.fps << endl;
		cout << "kinect4 : " << kinect4.fps << endl;
		cout << "kinect5 : " << kinect5.fps << endl;
		cout << "kinect6 : " << kinect6.fps << endl;*/
		kinect1.fps = 0;
		kinect2.fps = 0;
		kinect3.fps = 0;
		kinect4.fps = 0;
		kinect5.fps = 0;
		kinect6.fps = 0;
		kinect7.fps = 0;
		kinect8.fps = 0;
		timer++;
		CString sTime;
		sTime.Format(_T("%d : %02d : %02d"), (timer / 3600), (timer / 60) % 60, timer % 60);
		m_Edit_Timer.SetWindowTextA(sTime);
		break;

	}
	CDialogEx::OnTimer(nIDEvent);
}


HBRUSH AKinect_Monitoring::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	switch (nCtlColor)
	{
	case CTLCOLOR_EDIT:
	{
		if (pWnd->GetDlgCtrlID() == IDC_EDIT1)
		{
			pDC->SetTextColor(RGB(255, 0, 0));
		}
	}
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void AKinect_Monitoring::OnBnClickedIpcamon()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString anURL_1 = m_ipText_1;
	CString anURL_2 = m_ipText_2;
	CString anURL_3 = m_ipText_3;
	CString anURL_4 = m_ipText_4;
	CString anURL_5 = m_ipText_5;
	CString anURL_6 = m_ipText_6;
	CString anURL_7 = m_ipText_7;

	// Determine protocol to use if not set
	if (m_ipText_1.Find((CString)"://") == -1)
	{
		if (m_type.CompareNoCase((CString)"mpeg4") == 0 || m_type.CompareNoCase((CString)"h264") == 0 ||
			m_type.CompareNoCase((CString)"h265") == 0)
		{
			anURL_1 = (CString)"axrtsphttp://" + m_ipText_1;
		}
		else
		{
			anURL_1 = (CString)"http://" + m_ipText_1;
		}
	}

	// complete URL
	if (!(anURL_1[anURL_1.GetLength() - 1] == '/'))
	{
		anURL_1 += (CString)"/";
	}

	if (m_type.CompareNoCase((CString)"mjpeg") == 0)
	{
		anURL_1 = anURL_1 + (CString)"axis-cgi/mjpg/video.cgi";
	}
	else if (m_type.CompareNoCase((CString)"mpeg4") == 0)
	{
		anURL_1 = anURL_1 + (CString)"mpeg4/media.amp";
	}
	else if (m_type.CompareNoCase((CString)"h264") == 0)
	{
		anURL_1 = anURL_1 + (CString)"axis-media/media.amp?videocodec=h264";
	}
	else if (m_type.CompareNoCase((CString)"h265") == 0)
	{
		anURL_1 = anURL_1 + (CString)"axis-media/media.amp?videocodec=h265";
	}

	//Stop possible streams
	m_AMC_1.Stop();

	// Set username and password
	m_AMC_1.put_MediaUsername(m_user);
	m_AMC_1.put_MediaPassword(m_pass);

	// Set the media URL and the media type
	m_AMC_1.put_MediaURL(anURL_1);

	// Starts the download of the mpeg4 stream from the Axis camera/video server
	m_AMC_1.Play();

	// check for stream errors in OnError event


		// Determine protocol to use if not set
	if (m_ipText_2.Find((CString)"://") == -1)
	{
		if (m_type.CompareNoCase((CString)"mpeg4") == 0 || m_type.CompareNoCase((CString)"h264") == 0 ||
			m_type.CompareNoCase((CString)"h265") == 0)
		{
			anURL_2 = (CString)"axrtsphttp://" + m_ipText_2;
		}
		else
		{
			anURL_2 = (CString)"http://" + m_ipText_2;
		}
	}

	// complete URL
	if (!(anURL_2[anURL_2.GetLength() - 1] == '/'))
	{
		anURL_2 += (CString)"/";
	}

	if (m_type.CompareNoCase((CString)"mjpeg") == 0)
	{
		anURL_2 = anURL_2 + (CString)"axis-cgi/mjpg/video.cgi";
	}
	else if (m_type.CompareNoCase((CString)"mpeg4") == 0)
	{
		anURL_2 = anURL_2 + (CString)"mpeg4/media.amp";
	}
	else if (m_type.CompareNoCase((CString)"h264") == 0)
	{
		anURL_2 = anURL_2 + (CString)"axis-media/media.amp?videocodec=h264";
	}
	else if (m_type.CompareNoCase((CString)"h265") == 0)
	{
		anURL_2 = anURL_2 + (CString)"axis-media/media.amp?videocodec=h265";
	}

	//Stop possible streams
	m_AMC_2.Stop();

	// Set username and password
	m_AMC_2.put_MediaUsername(m_user);
	m_AMC_2.put_MediaPassword(m_pass);

	// Set the media URL and the media type
	m_AMC_2.put_MediaURL(anURL_2);

	// Starts the download of the mpeg4 stream from the Axis camera/video server
	m_AMC_2.Play();

	// check for stream errors in OnError event



	// Determine protocol to use if not set
	if (m_ipText_3.Find((CString)"://") == -1)
	{
		if (m_type.CompareNoCase((CString)"mpeg4") == 0 || m_type.CompareNoCase((CString)"h264") == 0 ||
			m_type.CompareNoCase((CString)"h265") == 0)
		{
			anURL_3 = (CString)"axrtsphttp://" + m_ipText_3;
		}
		else
		{
			anURL_3 = (CString)"http://" + m_ipText_3;
		}
	}

	// complete URL
	if (!(anURL_3[anURL_3.GetLength() - 1] == '/'))
	{
		anURL_3 += (CString)"/";
	}

	if (m_type.CompareNoCase((CString)"mjpeg") == 0)
	{
		anURL_3 = anURL_3 + (CString)"axis-cgi/mjpg/video.cgi";
	}
	else if (m_type.CompareNoCase((CString)"mpeg4") == 0)
	{
		anURL_3 = anURL_3 + (CString)"mpeg4/media.amp";
	}
	else if (m_type.CompareNoCase((CString)"h264") == 0)
	{
		anURL_3 = anURL_3 + (CString)"axis-media/media.amp?videocodec=h264";
	}
	else if (m_type.CompareNoCase((CString)"h265") == 0)
	{
		anURL_3 = anURL_3 + (CString)"axis-media/media.amp?videocodec=h265";
	}

	//Stop possible streams
	m_AMC_3.Stop();

	// Set username and password
	m_AMC_3.put_MediaUsername(m_user);
	m_AMC_3.put_MediaPassword(m_pass);

	// Set the media URL and the media type
	m_AMC_3.put_MediaURL(anURL_3);

	// Starts the download of the mpeg4 stream from the Axis camera/video server
	m_AMC_3.Play();

	// check for stream errors in OnError event

	// Determine protocol to use if not set
	if (m_ipText_4.Find((CString)"://") == -1)
	{
		if (m_type.CompareNoCase((CString)"mpeg4") == 0 || m_type.CompareNoCase((CString)"h264") == 0 ||
			m_type.CompareNoCase((CString)"h265") == 0)
		{
			anURL_4 = (CString)"axrtsphttp://" + m_ipText_4;
		}
		else
		{
			anURL_4 = (CString)"http://" + m_ipText_4;
		}
	}

	// complete URL
	if (!(anURL_4[anURL_4.GetLength() - 1] == '/'))
	{
		anURL_4 += (CString)"/";
	}

	if (m_type.CompareNoCase((CString)"mjpeg") == 0)
	{
		anURL_4 = anURL_4 + (CString)"axis-cgi/mjpg/video.cgi";
	}
	else if (m_type.CompareNoCase((CString)"mpeg4") == 0)
	{
		anURL_4 = anURL_4 + (CString)"mpeg4/media.amp";
	}
	else if (m_type.CompareNoCase((CString)"h264") == 0)
	{
		anURL_4 = anURL_4 + (CString)"axis-media/media.amp?videocodec=h264";
	}
	else if (m_type.CompareNoCase((CString)"h265") == 0)
	{
		anURL_4 = anURL_4 + (CString)"axis-media/media.amp?videocodec=h265";
	}

	//Stop possible streams
	m_AMC_4.Stop();

	// Set username and password
	m_AMC_4.put_MediaUsername(m_user);
	m_AMC_4.put_MediaPassword(m_pass);

	// Set the media URL and the media type
	m_AMC_4.put_MediaURL(anURL_4);

	// Starts the download of the mpeg4 stream from the Axis camera/video server
	m_AMC_4.Play();

	if (m_ipText_5.Find((CString)"://") == -1)
	{
		if (m_type.CompareNoCase((CString)"mpeg4") == 0 || m_type.CompareNoCase((CString)"h264") == 0 ||
			m_type.CompareNoCase((CString)"h265") == 0)
		{
			anURL_5 = (CString)"axrtsphttp://" + m_ipText_5;
		}
		else
		{
			anURL_5 = (CString)"http://" + m_ipText_5;
		}
	}

	// complete URL
	if (!(anURL_5[anURL_5.GetLength() - 1] == '/'))
	{
		anURL_5 += (CString)"/";
	}

	if (m_type.CompareNoCase((CString)"mjpeg") == 0)
	{
		anURL_5 = anURL_5 + (CString)"axis-cgi/mjpg/video.cgi";
	}
	else if (m_type.CompareNoCase((CString)"mpeg4") == 0)
	{
		anURL_5 = anURL_5 + (CString)"mpeg4/media.amp";
	}
	else if (m_type.CompareNoCase((CString)"h264") == 0)
	{
		anURL_5 = anURL_5 + (CString)"axis-media/media.amp?videocodec=h264";
	}
	else if (m_type.CompareNoCase((CString)"h265") == 0)
	{
		anURL_5 = anURL_5 + (CString)"axis-media/media.amp?videocodec=h265";
	}

	//Stop possible streams
	m_AMC_5.Stop();

	// Set username and password
	m_AMC_5.put_MediaUsername(m_user);
	m_AMC_5.put_MediaPassword(m_pass);

	// Set the media URL and the media type
	m_AMC_5.put_MediaURL(anURL_5);

	// Starts the download of the mpeg4 stream from the Axis camera/video server
	m_AMC_5.Play();

	if (m_ipText_6.Find((CString)"://") == -1)
	{
		if (m_type.CompareNoCase((CString)"mpeg4") == 0 || m_type.CompareNoCase((CString)"h264") == 0 ||
			m_type.CompareNoCase((CString)"h265") == 0)
		{
			anURL_6 = (CString)"axrtsphttp://" + m_ipText_6;
		}
		else
		{
			anURL_6 = (CString)"http://" + m_ipText_6;
		}
	}

	// complete URL
	if (!(anURL_6[anURL_6.GetLength() - 1] == '/'))
	{
		anURL_6 += (CString)"/";
	}

	if (m_type.CompareNoCase((CString)"mjpeg") == 0)
	{
		anURL_6 = anURL_6 + (CString)"axis-cgi/mjpg/video.cgi";
	}
	else if (m_type.CompareNoCase((CString)"mpeg4") == 0)
	{
		anURL_6 = anURL_6 + (CString)"mpeg4/media.amp";
	}
	else if (m_type.CompareNoCase((CString)"h264") == 0)
	{
		anURL_6 = anURL_6 + (CString)"axis-media/media.amp?videocodec=h264";
	}
	else if (m_type.CompareNoCase((CString)"h265") == 0)
	{
		anURL_6 = anURL_6 + (CString)"axis-media/media.amp?videocodec=h265";
	}

	//Stop possible streams
	m_AMC_6.Stop();

	// Set username and password
	m_AMC_6.put_MediaUsername(m_user);
	m_AMC_6.put_MediaPassword(m_pass);

	// Set the media URL and the media type
	m_AMC_6.put_MediaURL(anURL_6);

	// Starts the download of the mpeg4 stream from the Axis camera/video server
	m_AMC_6.Play();

	if (m_ipText_7.Find((CString)"://") == -1)
	{
		if (m_type.CompareNoCase((CString)"mpeg4") == 0 || m_type.CompareNoCase((CString)"h264") == 0 ||
			m_type.CompareNoCase((CString)"h265") == 0)
		{
			anURL_7 = (CString)"axrtsphttp://" + m_ipText_7;
		}
		else
		{
			anURL_7 = (CString)"http://" + m_ipText_7;
		}
	}

	// complete URL
	if (!(anURL_7[anURL_7.GetLength() - 1] == '/'))
	{
		anURL_7 += (CString)"/";
	}

	if (m_type.CompareNoCase((CString)"mjpeg") == 0)
	{
		anURL_7 = anURL_7 + (CString)"axis-cgi/mjpg/video.cgi";
	}
	else if (m_type.CompareNoCase((CString)"mpeg4") == 0)
	{
		anURL_7 = anURL_7 + (CString)"mpeg4/media.amp";
	}
	else if (m_type.CompareNoCase((CString)"h264") == 0)
	{
		anURL_7 = anURL_7 + (CString)"axis-media/media.amp?videocodec=h264";
	}
	else if (m_type.CompareNoCase((CString)"h265") == 0)
	{
		anURL_7 = anURL_7 + (CString)"axis-media/media.amp?videocodec=h265";
	}

	//Stop possible streams
	m_AMC_7.Stop();

	// Set username and password
	m_AMC_7.put_MediaUsername(m_user);
	m_AMC_7.put_MediaPassword(m_pass);
		  
	// Set7the media URL and the media type
	m_AMC_7.put_MediaURL(anURL_7);
		  
	// Sta7ts the download of the mpeg4 stream from the Axis camera/video server
	m_AMC_7.Play();
}
void audio_record_start()
{
	RecordDeviceFlag = 1;
	RecordDeviceIndex = 3;// 마이크 배열 3 사용(2~9로 인덱스상태)
	RecordFS = 48000;
	RecordQ = paInt16;
	RecordNumChannels = NUM_CHANNELS;
	RecordBlockSize = FRAMES_PER_BUFFER;
	RecordMaximumSecond = NUM_SECONDS;
	RecordNumbits = NUM_BITS;

	numSamples = NextPowerOf2((unsigned)(RecordFS * 0.5 * RecordNumChannels));
	numBytes = numSamples * sizeof(SAMPLE);
	audio_data.ringBufferData = (SAMPLE *)PaUtil_AllocateMemory(numBytes);
	if (audio_data.ringBufferData == NULL)
	{
		printf("Could not allocate ring buffer data.\n");
	}

	if (PaUtil_InitializeRingBuffer(&audio_data.ringBuffer, sizeof(SAMPLE), numSamples, audio_data.ringBufferData) < 0)
	{
		printf("Failed to initialize ring buffer. Size is not power of 2 ??\n");
	}
	err = Pa_Initialize();
	if (RecordDeviceFlag == 1)
		inputParameters.device = RecordDeviceIndex;
	else
	{
		inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
		const PaDeviceInfo *deviceInfo;
		deviceInfo = Pa_GetDeviceInfo(inputParameters.device);
		printf("[%d] %s is selected as input device.\n", inputParameters.device, deviceInfo->name);
	}
	

	//deviceInfo = Pa_GetDeviceInfo(inputParameters.device);
	//printf("[%d] %s is selected as input device.\n", inputParameters.device, deviceInfo->name);
	inputParameters.channelCount = RecordNumChannels;
	inputParameters.sampleFormat = RecordQ;
	inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
	inputParameters.hostApiSpecificStreamInfo = NULL;

	err = Pa_OpenStream(
		&stream,
		&inputParameters,
		NULL,                  /* &outputParameters, */
		RecordFS,
		RecordBlockSize,
		paNoFlag,
		recordCallback,
		&audio_data);
	/* Open the raw audio 'cache' file... */
	audio_data.file = fopen(LPSTR(LPCTSTR(patient_info.audio_full_path)), "wb");

	/* Start the file writing thread */
	err = startThread(&audio_data, threadFunctionWriteToRawFile);

	err = Pa_StartStream(stream);
}
void audio_record_stop()
{
	err = Pa_CloseStream(stream);

	/* Stop the thread */
	err = stopThread(&audio_data);

	/* Close file */
	fclose(audio_data.file);
	audio_data.file = 0;

	wavName = (char*)malloc(strlen(LPSTR(LPCTSTR(patient_info.audio_full_path))) * sizeof(char) + 1);
	strcpy(wavName, LPSTR(LPCTSTR(patient_info.audio_full_path)));
	memcpy(wavName + strlen(LPSTR(LPCTSTR(patient_info.audio_full_path))) - 4, ".wav", 4);
	
	RecordErr = PCMtoWAV(LPSTR(LPCTSTR(patient_info.audio_full_path)), wavName, RecordNumChannels, RecordNumbits, RecordFS);
	strcpy(LPSTR(LPCTSTR(patient_info.audio_full_path)), wavName);
	printf("\n=== Convert '%s' to '%s' !! Please check wav file. ===\n", LPSTR(LPCTSTR(patient_info.audio_full_path)), wavName); fflush(stdout);

	free(wavName);
}
void audio_list() //kinect 마이크는 2번째꺼로 (1~8중에)
{
	RecordDeviceFlag = 0;
	RecordDeviceIndex = 8;
	RecordFS = 48000;
	RecordQ = paInt16;
	RecordNumChannels = NUM_CHANNELS;
	RecordBlockSize = FRAMES_PER_BUFFER;
	RecordMaximumSecond = NUM_SECONDS;
	RecordNumbits = NUM_BITS;

	numSamples = NextPowerOf2((unsigned)(RecordFS * 0.5 * RecordNumChannels));
	numBytes = numSamples * sizeof(SAMPLE);
	audio_data.ringBufferData = (SAMPLE *)PaUtil_AllocateMemory(numBytes);
	if (audio_data.ringBufferData == NULL)
	{
		printf("Could not allocate ring buffer data.\n");
	}

	if (PaUtil_InitializeRingBuffer(&audio_data.ringBuffer, sizeof(SAMPLE), numSamples, audio_data.ringBufferData) < 0)
	{
		printf("Failed to initialize ring buffer. Size is not power of 2 ??\n");
	}
	err = Pa_Initialize();
	inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */

		int numDevices;
		const PaDeviceInfo *deviceInfo;

		numDevices = Pa_GetDeviceCount();
		for (int i = 0; i < numDevices; i++)
		{
			deviceInfo = Pa_GetDeviceInfo(i);
			printf("[%d] Input device name: %s\n", i, deviceInfo->name);
		}

}

void AKinect_Monitoring::OnBnClickedAudioon()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	printf("ddd\n");
	audio_list();
}


void AKinect_Monitoring::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString cmdLine;
	cmdLine = "mkvmerge -o " + patient_info.video_full_path[8] + " " + patient_info.video_full_path[0] + " " + patient_info.audio_full_path; // 확인필요
	system(cmdLine);
	cout << "병합완료" << endl;
	/*cmdLine = "del " + patient_info.video_full_path[0];
	system(cmdLine);*/
	/*cmdLine = "move " + patient_info.video_path[0] + "_audio.mkv "+ patient_info.video_full_path[0];
	system(cmdLine);*/
}
