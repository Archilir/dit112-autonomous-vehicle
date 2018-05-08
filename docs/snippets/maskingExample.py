#importing packages
from picamera.array import PiRGBArray
from picamera import PiCamera
import numpy as np
import time
import cv2

#initialize camera, settings and grab reference to raw cam capture
camera = PiCamera()
camera.resolution = (320, 240)
camera.framerate = 32
rawCapture=PiRGBArray(camera, size=(320, 240))

#camera warmup, 0.1sec
time.sleep(0.1)

for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):

    #take frame
    image = frame.array

    #convert BGR to HSV
    hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

    #define range of color
    lower_red = np.array([50, 100, 100])
    upper_red = np.array([70, 255, 255])

    #threshhold the hsv image to get only red
    mask = cv2.inRange(hsv, lower_red, upper_red)
    
    #bitwise-AND mask and original image
    res = cv2.bitwise_and(image, image, mask= mask)

    cv2.imshow("Frame", image)
    cv2.imshow("Mask", mask)
    cv2.imshow("Res", res)

    rawCapture.truncate(0)

    key = cv2.waitKey(1) & 0xFF

    if key==ord("q"):
                break
