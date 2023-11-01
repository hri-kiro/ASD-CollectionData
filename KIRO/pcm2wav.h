#pragma once

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

int PCMtoWAV(char* input,
	         char* output,
	         int   NumChannels,
	         int   NumBits,
	         int   SamplingRate);