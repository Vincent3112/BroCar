from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2


class Camera(object):
    '''
    Camera class handles all the actions relative
    to the camera and images taken from it.
    '''
    def __init__(self, resolution=(640,480), framerate=32):
        self.camera = PiCamera()
        self.camera.resolution = resolution
        self.camera.framerate = framerate
        self.rawCapture = PiRGBArray(self.camera, size=resolution)

        # allow the camera to warmup
        time.sleep(0.1)
 
    def run(self):
        # capture frames from the camera
        for frame in self.camera.capture_continuous(self.rawCapture, format="bgr", use_video_port=True):
            # grab the raw NumPy array representing the image, then initialize the timestamp
            # and occupied/unoccupied text
            image = frame.array

            # show the frame
            cv2.imshow("Brocar camera", image)
            key = cv2.waitKey(1) & 0xFF

            # clear the stream in preparation for the next frame
            self.rawCapture.truncate(0)

            # if the `q` key was pressed, break from the loop
            if key == ord("q"):
                break

