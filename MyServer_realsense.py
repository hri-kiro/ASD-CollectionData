import socket
import threading
import time
from datetime import datetime
import pyrealsense2 as rs
import numpy as np
import cv2

# RealSense Recorder class
class RealSenseRecorder:
    def __init__(self):
        # Configure the pipeline
        self.pipeline = rs.pipeline()
        self.config = rs.config()

        # Configure the streams (color + depth)
        self.config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)
        self.config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)

        self.is_recording = False
        self.out = None
        self.current_filename = None  # 현재 녹화 중인 파일 이름을 저장할 변수

    def start_recording(self, click_time, message):
        # 파일이름 형식
        filename_time = datetime.strptime(click_time, "%Y-%m-%d %H:%M:%S").strftime("%Y%m%d_%H%M%S")
        new_filename = f"{filename_time}_{message}.avi"
        # 중복 레코딩 방지
        if self.current_filename == new_filename:
            print(f"Skipping recording because filename {new_filename} is already being used.")
            return
        
        print(f"Starting recording with filename: {new_filename}")

        # Define video codec and output file
        fourcc = cv2.VideoWriter_fourcc(*'XVID')
        self.out = cv2.VideoWriter(new_filename, fourcc, 30.0, (640, 480))

        # Start streaming
        self.pipeline.start(self.config)
        self.is_recording = True
        self.current_filename = new_filename  # 현재 파일 이름 저장
        print(f"Recording started. Saving to {new_filename}")
        
        # Start a new thread for continuous recording
        record_thread = threading.Thread(target=self.record)
        record_thread.start()

    def stop_recording(self):
        if self.is_recording:
            print(f"Stopping recording for file: {self.current_filename}")
            self.is_recording = False
            try:
                if self.out:
                    self.out.release()  # 비디오 파일 종료
            except Exception as e:
                print(f"Error closing video file: {e}")
            finally:
                try:
                    self.pipeline.stop()  # 파이프라인 중지
                    print("RealSense pipeline stopped.")
                except Exception as e:
                    print(f"Error stopping pipeline: {e}")
                self.current_filename = None
                print("Recording stopped and saved.")

    def record(self):
        try:
            if not self.is_recording:
                return

            while self.is_recording:
                # Wait for a coherent pair of frames: depth and color
                frames = self.pipeline.wait_for_frames()
                depth_frame = frames.get_depth_frame()
                color_frame = frames.get_color_frame()

                if not depth_frame or not color_frame:
                    continue

                # Convert images to numpy arrays
                color_image = np.asanyarray(color_frame.get_data())

                # Write the frame to the video output file
                self.out.write(color_image)

        except Exception as e:
            print(f"Error during recording: {e}")
            
    

# Client management thread class
class ClientManagerThread(threading.Thread):
    def __init__(self, client_socket, robot_socket, recorder, server_socket):
        threading.Thread.__init__(self)
        self.client_socket = client_socket
        self.robot_socket = robot_socket
        self.recorder = recorder
        self.server_socket = server_socket  # 서버 소켓을 받아와서 재연결 시 서버로 전달

    def run(self):
        try:
            client_address = self.client_socket.getpeername()
            print(f"Client connected. Host: {client_address[0]}, Port: {client_address[1]}")

            while True:
                # 클라이언트로부터 메시지 수신
                data = self.client_socket.recv(1024)
                if not data:
                    break
                # 수신된 데이터를 디코딩
                received_msg = data.decode('utf-8')
                print(f"Received from client: {received_msg}")

                try:
                    received_msg_parts = received_msg.split('>')
                    message = received_msg_parts[0].strip()  # 메시지 부분 추출
                    click_time = received_msg_parts[1].strip()  # 클릭 시간 추출
                    print(f"Message: {message}, Click Time: {click_time}")

                    # 로봇에게 메시지 전송
                    try:
                        if self.robot_socket:
                            self.robot_socket.sendall((message + '\n').encode('utf-8'))
                            print(f"Forwarded to robot: {message}")
                        else:
                            print("Robot is not connected.")
                    except socket.error as e:
                        print(f"Error sending message to robot: {e}")
                        break  # 로봇과 연결이 끊어졌다면 스레드를 종료하고 서버에서 재연결 시도

                    # 녹화 시작
                    if message != "Correct Button" and message != "Wrong Button": # Activity가 클릭되면 녹화 시작
                        print(f"Starting RealSense recording for: {message}")
                        self.recorder.start_recording(click_time, message)
                    else:
                        print(f"Stopping RealSense recording for: {message}") # 판단 버튼이 클릭되면 녹화 중지
                        self.recorder.stop_recording()

                except Exception as e:
                    print(f"Error while handling message: {e}")
                    break
        finally:
            self.client_socket.close()
            
            
# 로봇 연결 처리 함수
def connect_to_robot(server_socket):
    """로봇 연결을 기다리고, 연결되면 소켓을 반환하는 함수"""
    while True:
        try:
            print("Waiting for robot to connect...")
            robot_socket, robot_address = server_socket.accept()  # 서버 소켓을 통해 로봇 연결 수락
            print(f"Robot connected: {robot_address[0]}, Port: {robot_address[1]}")

            # TCP Keep-Alive 설정 추가
            robot_socket.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1)
            return robot_socket
        except Exception as e:
            print(f"Error connecting to robot: {e}")
            time.sleep(5)  # 재연결 시도 간격


def main():
    host = '0.0.0.0'
    port = 8888

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(5)
    print(f"Server listening on {host}:{port}")

    # RealSense Recorder 초기화
    recorder = RealSenseRecorder()

    robot_socket = None

    try:
        while True:
            # 로봇 연결이 없다면 재연결 시도
            if not robot_socket:
                robot_socket = connect_to_robot(server_socket)  # 로봇 연결 대기

            print("Waiting for client to connect...")
            client_socket, client_address = server_socket.accept()  # 클라이언트 연결 대기
            print(f"Client connected: {client_address[0]}, Port: {client_address[1]}")

            # 클라이언트 스레드 생성 및 처리
            client_thread = ClientManagerThread(client_socket, robot_socket, recorder, server_socket)
            client_thread.start()

            # 스레드에서 로봇 소켓이 끊어진 경우, 새로운 연결을 기다림
            client_thread.join()  # 클라이언트 스레드가 끝날 때까지 대기
            robot_socket = None  # 로봇 소켓이 끊어졌다고 가정하고 재연결 대기
            print("Robot socket disconnected, waiting for reconnection...")

    except Exception as e:
        print(f"Error: {e}")
    finally:
        server_socket.close()

if __name__ == "__main__":
    main()
