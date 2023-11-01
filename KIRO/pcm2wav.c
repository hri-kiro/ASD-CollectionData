#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcm2wav.h"

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
	WaveHeader.fmt.ChunkSize	 = 0x10;
	WaveHeader.fmt.AudioFormat	 = WAVE_FORMAT_PCM;
	WaveHeader.fmt.NumChannels	 = NumChannels;
	WaveHeader.fmt.SampleRate	 = SamplingRate;
	WaveHeader.fmt.ByteRate		 = NumChannels * SamplingRate * (NumBits / 8);
	WaveHeader.fmt.BlockAlign	 = NumChannels * (NumBits / 8);
	WaveHeader.fmt.BitsPerSample = NumBits;

	//DATA
	memcpy(WaveHeader.Data.ChunkID, "data", 4);
	WaveHeader.Data.ChunkSize = 0;

	if (fin == NULL) // Failed to open
		return -1;

	if ( NumBits == 8 )
		while ((len = fread(&char_buf, sizeof(char), 1, fin)) != NULL)
		{
			fwrite(&char_buf, sizeof(char), 1, fout);
			Data_size++;
		}
	else if ( NumBits == 16 )
		while ((len = fread(&short_buf, sizeof(short), 1, fin)) != NULL)
		{
			fwrite(&short_buf, sizeof(short), 1, fout);
			// Data_size++;
			Data_size += 2;
		}
	else if ( NumBits == 32 )
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

