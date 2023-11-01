#pragma once
#include <string>
#include <k4a\k4a.hpp>
#include <k4arecord\playback.hpp>
#include <k4arecord\record.h>

using namespace std;

class mkv_controller
{
public:
	mkv_controller();
	~mkv_controller();
	void setFilePath(string fileName) { m_fileName = fileName; };
	void openPlayback(string fileName);
	int getFrameCount() { return m_iFrameCount; };
	bool getColorFrame(k4a::image& oImage);
	bool getColorFrame(int frameNumber, k4a::image& oImage);
	bool getDepthFrame(k4a::image& oImage);
	bool getDepthFrame(int frameNumber, k4a::image& oImage);
	bool saveBetweenFrame(int startFrame, int endFrame, string fileName);
	int getTotalFrameCount() { return m_iTotalFrameCount; };
	void FrameRewind();
private:
	void calcTotalFrameCount();
	k4a::playback m_Playback;
	string m_fileName;
	bool m_bOpen;
	int m_iFrameCount;
	int m_iTotalFrameCount;
};

