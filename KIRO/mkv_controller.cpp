#include "pch.h"
#include "mkv_controller.h"


mkv_controller::mkv_controller()
{
	m_bOpen = false;
	m_iFrameCount = 0;
}


mkv_controller::~mkv_controller()
{
	if (m_bOpen)
		m_Playback.close();
}

void mkv_controller::openPlayback(string fileName)
{
	setFilePath(fileName);
	m_Playback = k4a::playback::open(m_fileName.c_str());
	if(m_Playback)
		m_bOpen = true;
	m_Playback.set_color_conversion(K4A_IMAGE_FORMAT_COLOR_BGRA32);
	calcTotalFrameCount();
	//FrameRewind();
}

bool mkv_controller::getColorFrame(k4a::image& oImage)
{
	bool ret = false;

	if (!m_bOpen)
		return ret;

	k4a::capture* capture = new k4a::capture;
	ret = m_Playback.get_next_capture(capture);
	oImage = capture->get_color_image();
	capture->reset();
	m_iFrameCount++;
	delete capture;

	return ret;
}

bool mkv_controller::getColorFrame(int frameNumber, k4a::image & oImage)
{
	bool ret = false;

	if (!m_bOpen)
		return ret;
	
	k4a::capture* capture = new k4a::capture;
	while (1)
	{
		if (frameNumber > m_iFrameCount)
		{
			ret = m_Playback.get_next_capture(capture);
			m_iFrameCount++;
		}
		else if (frameNumber < m_iFrameCount)
		{
			ret = m_Playback.get_previous_capture(capture);
			m_iFrameCount--;
		}
		else
			break;
	}
	oImage = capture->get_color_image();

	capture->reset();
	delete capture;

	return ret;
}

bool mkv_controller::getDepthFrame(k4a::image & oImage)
{
	bool ret = false;

	if (!m_bOpen)
		return ret;

	k4a::capture* capture = new k4a::capture;
	ret = m_Playback.get_next_capture(capture);
	oImage = capture->get_depth_image();
	capture->reset();
	m_iFrameCount++;
	delete capture;
	
	return ret;
}

bool mkv_controller::getDepthFrame(int frameNumber, k4a::image & oImage)
{
	bool ret = false;

	if (!m_bOpen)
		return ret;

	k4a::capture* capture = new k4a::capture;
	while (1)
	{
		if (frameNumber > m_iFrameCount)
		{
			ret = m_Playback.get_next_capture(capture);
			m_iFrameCount++;
		}
		else if (frameNumber < m_iFrameCount)
		{
			ret = m_Playback.get_previous_capture(capture);
			m_iFrameCount--;
		}
		else
			break;
	}
	oImage = capture->get_depth_image();
	capture->reset();
	delete capture;

	return ret;
}

bool mkv_controller::saveBetweenFrame(int startFrame, int endFrame, string fileName)
{
	bool ret = false;

	if (!m_bOpen)
		return ret;

	m_Playback.set_color_conversion(K4A_IMAGE_FORMAT_COLOR_MJPG); // 추가된 부분
	k4a::capture capture;
	while (1)
	{
		capture.reset();
		if (startFrame > m_iFrameCount)
		{
			ret = m_Playback.get_next_capture(&capture);
			m_iFrameCount++;
		}
		else if (startFrame < m_iFrameCount)
		{
			ret = m_Playback.get_previous_capture(&capture);
			m_iFrameCount--;
		}
		else
			break;
	}
	k4a_device_configuration_t config;
	auto rconfig = m_Playback.get_record_configuration();
	config.camera_fps = rconfig.camera_fps;
	config.color_format = rconfig.color_format;
	config.color_resolution = rconfig.color_resolution;
	config.depth_delay_off_color_usec = rconfig.depth_delay_off_color_usec;
	config.depth_mode = rconfig.depth_mode;
	config.subordinate_delay_off_master_usec = rconfig.subordinate_delay_off_master_usec;
	config.wired_sync_mode = rconfig.wired_sync_mode;

	k4a_record_t recording;
	k4a_record_create(fileName.c_str(), nullptr, config, &recording);
	k4a_record_write_header(recording);
	k4a_record_write_capture(recording, capture.handle());
	capture.reset();
	while (1)
	{
		if (m_iFrameCount < endFrame)
		{
			m_Playback.get_next_capture(&capture);
			m_iFrameCount++;
			k4a_record_write_capture(recording, capture.handle());
			capture.reset();
		}
		else
			break;
	}
	k4a_record_flush(recording);
	k4a_record_close(recording);

	return ret;
}

void mkv_controller::FrameRewind()
{
	if (!m_bOpen)
		return ;

	k4a::capture capture;
	while (m_Playback.get_previous_capture(&capture))
	{
		capture.reset();
		m_iFrameCount--;
	}
}

void mkv_controller::calcTotalFrameCount()
{
	if (!m_bOpen)
		return;
	m_iTotalFrameCount = m_Playback.get_recording_length().count() / 1000000 * 30;
	/*k4a::capture capture;
	while (m_Playback.get_next_capture(&capture))
	{
		capture.reset();
		m_iFrameCount++;
	}
	m_iTotalFrameCount = m_iFrameCount;*/
}
