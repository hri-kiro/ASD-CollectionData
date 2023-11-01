// Azure_kinect.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "Azure_Kinect.h"
#include <ctime>


using namespace std;
// TODO: 라이브러리 함수의 예제입니다.
namespace Kinect
{
	Azure_Kinect::Azure_Kinect()
	{
		device = NULL;
		recording_color_format = K4A_IMAGE_FORMAT_COLOR_MJPG;
		viewer_color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
		recording_color_resolution = K4A_COLOR_RESOLUTION_1536P; // FHD 셋팅
		recording_depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
		recording_rate = K4A_FRAMES_PER_SECOND_30;
		recording_rate_set = false;
		recording_imu_enabled = false;
		//wired_sync_mode = K4A_WIRED_SYNC_MODE_STANDALONE;
		depth_delay_off_color_usec = 0;
		subordinate_delay_off_master_usec = 0;
		absoluteExposureValue = defaultExposureAuto;
		gain = defaultGainAuto;
		RecordingStart_Flag = false;
		RecordingEnd_Flag = true;
		total_frame = 0;
		fps = 0;
		device_count = k4a_device_get_installed_count();

		

	}
	void Azure_Kinect::set_standalone()
	{
		config_record = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
		config_record.color_format = recording_color_format;
		config_record.color_resolution = recording_color_resolution;
		config_record.depth_mode = recording_depth_mode;
		config_record.camera_fps = recording_rate;
		config_record.wired_sync_mode = K4A_WIRED_SYNC_MODE_STANDALONE;
		config_record.depth_delay_off_color_usec = depth_delay_off_color_usec;
		config_record.subordinate_delay_off_master_usec = subordinate_delay_off_master_usec;
		//device_count = k4a_device_get_installed_count();
	}
	void Azure_Kinect::set_subordinate(int delay)
	{
		config_record = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
		config_record.color_format = recording_color_format;
		config_record.color_resolution = recording_color_resolution;
		config_record.depth_mode = recording_depth_mode;
		config_record.camera_fps = recording_rate;
		config_record.wired_sync_mode = K4A_WIRED_SYNC_MODE_SUBORDINATE;
		config_record.depth_delay_off_color_usec = depth_delay_off_color_usec;
		config_record.subordinate_delay_off_master_usec = subordinate_delay_off_master_usec;
		//device_count = k4a_device_get_installed_count();
	}
	void Azure_Kinect::set_master()
	{
		config_record = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
		config_record.color_format = recording_color_format;
		config_record.color_resolution = recording_color_resolution;
		config_record.depth_mode = recording_depth_mode;
		config_record.camera_fps = recording_rate;
		config_record.wired_sync_mode = K4A_WIRED_SYNC_MODE_MASTER;
		config_record.depth_delay_off_color_usec = depth_delay_off_color_usec;
		config_record.subordinate_delay_off_master_usec = subordinate_delay_off_master_usec;
		//device_count = k4a_device_get_installed_count();
	}
	void Azure_Kinect::set_video_path(char* path)
	{
		video_path = path;
	}
	void Azure_Kinect::set_device_num(uint8_t num)
	{
		device_num = num;
	}
	void Azure_Kinect::get_device_serial()
	{
		device_serial = NULL;
		size_t serial_number_length = 0;

		if (K4A_BUFFER_RESULT_TOO_SMALL != k4a_device_get_serialnum(device, NULL, &serial_number_length))
		{
			k4a_device_close(device);
			device = NULL;
		}
		device_serial = new char(serial_number_length);


		if (K4A_BUFFER_RESULT_SUCCEEDED != k4a_device_get_serialnum(device, device_serial, &serial_number_length))
		{
			free(device_serial);
			device_serial = NULL;
			k4a_device_close(device);
			device = NULL;
		}
		cout << device_serial << endl;
		k4a_device_close(device);
	}
	int Azure_Kinect::Kinect_Open(uint8_t device_num)
	{
		if (K4A_RESULT_SUCCEEDED != k4a_device_open(device_num, &device))
		{
			cout << "Failed to open device\n";
			if (device != NULL)
			{
				k4a_device_close(device);
				return 0;
			}
		}
		
		return 1;
	}

	int Azure_Kinect::kinect_init()
	{
		if (device_count == 0)
		{
			printf("No K4A devices found\n");
			return 0;
		}

		if (K4A_RESULT_SUCCEEDED != k4a_device_open(device_num, &device))
		{
			printf("Failed to open device\n");
			return 0;
		}

		if (K4A_RESULT_SUCCEEDED != k4a_device_start_cameras(device, &config_record))
		{
			printf("Failed to start device\n");
			k4a_device_close(device);
		}
		k4a_record_create(video_path, device, config_record, &recording);
		return 1;
	}
	int Azure_Kinect::Kinect_Start()
	{
		if (K4A_RESULT_SUCCEEDED != k4a_device_start_cameras(device, &config_record))
		{
			printf("Failed to start device\n");
			k4a_device_close(device);
			return 0;
		}
		//Camera_On();
	}
	void Azure_Kinect::Start_Recording()
	{

		//k4a_record_create(video_path, device, config_record, &recording);
		RecordingStart_Flag = true;
		RecordingEnd_Flag = false;
	}
	void Azure_Kinect::Stop_Recording()
	{
		RecordingStart_Flag = false;
		RecordingEnd_Flag = true;
	}
	UINT Azure_Kinect::Camera_On()
	{

		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.	
		//RecordingEnd_Flag = false;

		//k4a_record_create("Kinect3.mkv", device_3, config_3, &recording_3);
		k4a_record_write_header(recording);

		//Wait for first capture befored starting recording
		int32_t timeout_sec_for_first_capture = 60;

		clock_t first_capture_start = clock();
		result = K4A_WAIT_RESULT_TIMEOUT;

		while ((clock() - first_capture_start) < (CLOCKS_PER_SEC * timeout_sec_for_first_capture))
		{
			result = k4a_device_get_capture(device, &capture, 100);
			if (result == K4A_WAIT_RESULT_SUCCEEDED)
			{
				k4a_capture_release(capture);
				break;
			}
			if (result == K4A_WAIT_RESULT_FAILED)
			{
				std::cerr << "Runtime error: k4a_device_get_capture() returned error: " << result << std::endl;
			}
		}

		timeout_ms = 1000 / 30;
		while (RecordingEnd_Flag == false)
		{
			
			while (RecordingStart_Flag == true)
			{

				//unsigned currentTime = GetTickCount();
				//cout << device_num << " " << start << endl;
				result = k4a_device_get_capture(device, &capture, timeout_ms);

				if (result == K4A_WAIT_RESULT_TIMEOUT)
				{
					continue;
				}
				else if (result != K4A_WAIT_RESULT_SUCCEEDED)
				{
					break;
				}
				
				k4a_record_write_capture(recording, capture);
				k4a_capture_release(capture);
				total_frame++;
				fps++;

			}
			
		}

		k4a_record_flush(recording);
		k4a_record_close(recording);
		return 1;
	}
}

