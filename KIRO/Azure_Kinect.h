#pragma once
#include "k4a/k4a.h"
#include "k4arecord/types.h"
#include "k4arecord/record.h"
#include "k4arecord/playback.hpp"
#include <iostream>
#include <ctime>
#include <thread>

namespace Kinect
{
	class Azure_Kinect
	{
	public:
		static const int32_t defaultExposureAuto = -12;
		static const int32_t defaultGainAuto = -1;

		uint32_t device_count;
		k4a_device_t device;
		k4a_device_configuration_t config_record;
		k4a_device_configuration_t config_viewer;
		k4a_capture_t capture;
		k4a_record_t recording;
		k4a_wait_result_t result;
		int recording_length;

		k4a_image_format_t recording_color_format;
		k4a_image_format_t viewer_color_format;
		k4a_color_resolution_t recording_color_resolution;
		k4a_depth_mode_t recording_depth_mode;
		k4a_fps_t recording_rate;

		bool recording_rate_set;
		bool recording_imu_enabled;
		k4a_wired_sync_mode_t wired_sync_mode ;
		int32_t depth_delay_off_color_usec;
		uint32_t subordinate_delay_off_master_usec;
		int absoluteExposureValue;
		int gain;
		char *recording_filename;
		long total_frame;
		int fps;

		uint8_t device_num;
		char* video_path;
		int32_t timeout_ms;
		char* device_serial;
	
		bool RecordingStart_Flag ;
		bool RecordingEnd_Flag ;



	public:
		Azure_Kinect();
		void set_subordinate(int);
		void set_master();
		void set_standalone();
		void set_video_path(char* path);
		void set_device_num(uint8_t num);
		void get_device_serial();
		int Kinect_Open(uint8_t device_num);
		void Start_Recording();
		void Stop_Recording();
		UINT Camera_On();
		int Kinect_Start();
		int kinect_init();
	};
}


