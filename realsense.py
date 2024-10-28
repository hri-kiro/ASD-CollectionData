import pyrealsense2 as rs
import numpy as np
import cv2

# Configure the pipeline
pipeline = rs.pipeline()
config = rs.config()

# Configure the streams (color + depth)
config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)
config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)

# Start streaming
pipeline.start(config)

# Define video codec and output file
fourcc = cv2.VideoWriter_fourcc(*'XVID')  # 코덱 선택
out = cv2.VideoWriter('realsense_output.avi', fourcc, 30.0, (640, 480)) # 파일 형식 지정

try:
    print("Press 'q' to quit.")
    while True:
        # Wait for a coherent pair of frames: depth and color
        frames = pipeline.wait_for_frames()
        depth_frame = frames.get_depth_frame()
        color_frame = frames.get_color_frame()

        if not depth_frame or not color_frame:
            continue

        # Convert images to numpy arrays
        depth_image = np.asanyarray(depth_frame.get_data())
        color_image = np.asanyarray(color_frame.get_data())

        # 이미지 보기
        cv2.imshow('Realsense Color Stream', color_image)
        # Write the frame to the video output file
        out.write(color_image)

        # 'q'키 입력시 레코딩 멈춤
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

finally:
    # Stop streaming
    pipeline.stop()
    out.release()
    cv2.destroyAllWindows()
