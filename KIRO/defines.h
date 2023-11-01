#pragma once

#include <afxdb.h>
#include <vector>
#include <string>
#include <utility>
#include <thread>
#include "Azure_Kinect.h"
#include "Monitoring.h"
#include "TabDlg1.h"
#include "TabDlg2.h"
#include "AKinect_Monitoring.h"
#include "Patient_Info.h"
#include "VideoTagging.h"

#include "portaudio.h"
#include "pa_ringbuffer.h"
#include "pa_util.h"


#define FRAME_CNT 1000
#define CLOCK_CNT 100
#define DBOPEN "DSN=Autism_db;SERVER=192.168.0.3;UID=kiro;PWD=fhqhtNAS021!;DATABASE=Autism_db;"
//#define DBOPEN "DSN=Autism_db;SERVER=127.0.0.1;UID=root;PWD=root;DATABASE=Autism_db;"

//#define TEST

using namespace std;

struct patient
{
	CString Research_Number;
	CString Date;
	CString Ados_Type;
	CString Bedevel_Type;
	CString video_path[8];
	CString folder_path[9]; // 음성 영상 병합 마지막에 추가
	CString folder_tagging_path[8];
	CString Age;
	CString video_full_path[9];// 음성 영상 병합 마지막에 추가
	CString audio_full_path;
	CString video_audio_path;
};

struct VideoIndex
{
	int StartIndex;
	int EndIndex;
};

struct xlContainer
{
	CString contents;
	CString time;
	CString score;
};

#define SAMPLE_RATE  (16000)
#define FRAMES_PER_BUFFER (512)
#define NUM_SECONDS     (10)
#define NUM_CHANNELS    (1)
#define NUM_BITS		(16)
#define NUM_WRITES_PER_BUFFER   (4)
/* #define DITHER_FLAG     (paDitherOff) */
#define DITHER_FLAG     (0) /**/

static int RecordNumChannels;

/* Select sample format. */
#if 0
#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#elif 1
#define PA_SAMPLE_TYPE  paInt16
typedef short SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt8
typedef char SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#else
#define PA_SAMPLE_TYPE  paUInt8
typedef unsigned char SAMPLE;
#define SAMPLE_SILENCE  (128)
#define PRINTF_S_FORMAT "%d"
#endif

typedef struct
{
	unsigned            frameIndex;
	int                 threadSyncFlag;
	SAMPLE             *ringBufferData;
	PaUtilRingBuffer    ringBuffer;
	FILE               *file;
	void               *threadHandle;
}
paTestData;


#define WAVE_FORMAT_UNKNOWN        0x0000;
#define WAVE_FORMAT_PCM            0x0001;
#define WAVE_FORMAT_MS_ADPCM       0x0002;
#define WAVE_FORMAT_IEEE_FLOAT     0x0003;
#define WAVE_FORMAT_ALAW           0x0006;
#define WAVE_FORMAT_MULAW          0x0007;
#define WAVE_FORMAT_IMA_ADPCM      0x0011;
#define WAVE_FORMAT_YAMAHA_ADPCM   0x0016;
#define WAVE_FORMAT_GSM            0x0031;
#define WAVE_FORMAT_ITU_ADPCM      0x0040;
#define WAVE_FORMAT_MPEG           0x0050;
#define WAVE_FORMAT_EXTENSIBLE     0XFFFE;


typedef struct
{
	unsigned char ChunkID[4];  // RIFF
	unsigned int ChunkSize;    // Filesize
	unsigned char Format[4];   // WAVE
} RIFF;

typedef struct
{
	unsigned char ChunkID[4];  // fmt 
	unsigned int ChunkSize;    // 16
	unsigned short AudioFormat; // WAVE_FORMAT_PCM
	unsigned short NumChannels;
	unsigned int SampleRate;
	unsigned int ByteRate; // ch * smapleRate * Bits/8
	unsigned short BlockAlign; // ch *bits/8
	unsigned short BitsPerSample; // bits
} FMT;

typedef struct
{
	unsigned char ChunkID[4]; //data
	unsigned int ChunkSize; // Raw data size
} DATA;

typedef struct
{
	RIFF Riff;
	FMT fmt;
	DATA Data;
} WAVEHEADER;

