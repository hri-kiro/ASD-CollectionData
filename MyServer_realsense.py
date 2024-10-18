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

    def start_recording(self, click_time):
        # Format the click_time into a valid filename
        filename_time = datetime.strptime(click_time, "%Y-%m-%d %H:%M:%S").strftime("%Y%m%d_%H%M%S")
        filename = f"realsense_recording_{filename_time}.avi"

        # Define video codec and output file
        fourcc = cv2.VideoWriter_fourcc(*'XVID')
        self.out = cv2.VideoWriter(filename, fourcc, 30.0, (640, 480))

        # Start streaming
        self.pipeline.start(self.config)
        self.is_recording = True
        print(f"Recording started. Saving to {filename}")

    def stop_recording(self):
        if self.is_recording:
            self.is_recording = False
            self.pipeline.stop()
            if self.out:
                self.out.release()
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
    def __init__(self, client_socket, recorder):
        threading.Thread.__init__(self)
        self.client_socket = client_socket
        self.recorder = recorder

    def run(self):
        try:
            client_address = self.client_socket.getpeername()
            print(f"Client connected. Host: {client_address[0]}, Port: {client_address[1]}")

            while True:
                # Continuously handle communication with the client (e.g., receive messages)
                data = self.client_socket.recv(1024)
                if not data:
                    break
                # Decode the received data to a string
                received_msg = data.decode('utf-8')
                print(f"Received from client: {received_msg}")

                try:
                    received_msg_parts = received_msg.split('>')

                    message = received_msg_parts[0].strip()  # Strip any extra spaces from the message
                    click_time = received_msg_parts[1].strip()  # Strip any extra spaces from the click time

                    print(f"Message: {message}, Click Time: {click_time}")
                    
                    # Stop recording if "Wrong Button" or "Correct Button" is received
                    if message == "Wrong Button" or message == "Correct Button":
                        print(f"Stopping RealSense recording with message: {message}")
                        self.recorder.stop_recording()

                    # Start recording for any other message
                    else:
                        print("Starting RealSense recording...")
                        self.recorder.start_recording(click_time)  # Pass click time for the filename
                        # Start a thread to record frames in the background
                        threading.Thread(target=self.recorder.record).start()
                        
                except ValueError:
                    print("Received data in unexpected format")

        finally:
            self.client_socket.close()

# Main server setup
def main():
    host = '0.0.0.0'
    port = 8888
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(5)
    print(f"Server listening on {host}:{port}")

    # Initialize the RealSense recorder
    recorder = RealSenseRecorder()

    try:
        while True:
            client_socket, client_address = server_socket.accept()
            print(f"Client connected: Host: {client_address[0]}, Port: {client_address[1]}")

            # Create a new thread for handling the client
            client_thread = ClientManagerThread(client_socket, recorder)
            client_thread.start()

    except Exception as e:
        print(f"Error: {e}")
    finally:
        server_socket.close()

if __name__ == "__main__":
    main()
