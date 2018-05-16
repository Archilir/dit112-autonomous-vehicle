from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import numpy as np
import cv2 as cv
import time
import threading
import serial
import logging
import multiprocessing as mp

#Initialize camera
camera = PiCamera()

#Set camera settings
camera.resolution = (320, 240)
camera.framerate = 30

#Use an array of pixels for better performance
camera_array = PiRGBArray(camera, size=(320, 240))

#Allow camera to start
time.sleep(0.1)

for frame in camera.capture_continuous(camera_array, format="bgr", use_video_port=True):
    img = frame.array
    img_inv = cv.bitwise_not(img)
    #draw relevant color spaces
    #Use greyscale for easier recognition of contours
    gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
                
    #Guassian blur to smooth out the images
    blurred = cv.GaussianBlur(gray, (5, 5), 0)

    #A generic threshold to decide what we consider contours
    thresh = cv.threshold(blurred, 128, 255, cv.THRESH_BINARY_INV)[1]

    #convert BGR to HSV
    hsv = cv.cvtColor(img, cv.COLOR_BGR2HSV)
    hsv_inv = cv.cvtColor(img_inv, cv.COLOR_BGR2HSV)

      #define range of color
    lower_green = np.array([50, 100, 100])
    upper_green = np.array([70, 255, 255])

    lower_blue = np.array([230, 100, 100])
    upper_blue = np.array([250, 255, 255])

    lower_red = np.array([80, 70, 50])
    upper_red = np.array([100, 255, 255])
                
    #threshhold the hsv image to get only green
    mask_green = cv.inRange(hsv, lower_green, upper_green)
    mask_blue = cv.inRange(hsv, lower_blue, upper_blue)
    mask_red = cv.inRange(hsv_inv, lower_red, upper_red)

    #cv.imshow("Green", mask_green)
    cv.imshow("Blue", mask_blue)
    #cv.imshow("Red", mask_red)
    
    camera_array.truncate(0)
    key = cv.waitKey(1) & 0xFF
    if key==ord("q"):
        break
