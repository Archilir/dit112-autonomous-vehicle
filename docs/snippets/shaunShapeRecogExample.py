from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import numpy as np
import cv2 as cv
import serial
import RPi.GPIO as GPIO
import time

#A function to compare contour vertices to recognize the shape
def shape_compare(c):

        #turn curves into lines
        shape = cv.arcLength(c, True)
        #Approximate polygon curves to get better idea on straight lines
        approx = cv.approxPolyDP(c, 0.04 * shape, True)
        
        #Compare vertices of approximated shapes
        if len(approx) == 3:
                return "triangle"

        elif len(approx) == 4:

                (x, y, w, h) = cv.boundingRect(approx)
                ar = w / float(h)

                if ar >= 0.95 and ar <= 1.05:
                        return "square"
                else: 
                        return "rectangle"
        elif len(approx) == 8:
                return "stop sign"
        else:
                return "none"

#Initialize camera
camera = PiCamera()

#Set camera settings
camera.resolution = (320, 240)
camera.framerate = 30

#Use an array of pixels for better performance
camera_array = PiRGBArray(camera, size=(320, 240))

#Allow camera to start
time.sleep(0.1)

#Initialize serial
#ser = serial.Serial('/dev/ttyACM0', 9600, 'N')

#Perform functions for each frame of the camera capture
for frame in camera.capture_continuous(camera_array, format="bgr", use_video_port=True):
        img = frame.array

        #Use greyscale for easier recognition of contours
        gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
        
        #Guassian blur to smooth out the images
        blurred = cv.GaussianBlur(gray, (5, 5), 0)

        #A generic threshold to decide what we consider contours
        thresh = cv.threshold(blurred, 128, 255, cv.THRESH_BINARY_INV)[1]

        #Find these contours based on the threshhold
        _, contours, _ = cv.findContours(thresh.copy(), cv.RETR_TREE,
                cv.CHAIN_APPROX_SIMPLE)
        
        #Draw each contour we find
        for c in contours:
                
                #Calculate center of contours
                moment = cv.moments(c)
                if (moment["m00"] == 0):
                        moment["m00"]=1
                cX = int(moment["m10"] / moment["m00"])
                cY = int(moment["m01"] / moment["m00"])

                #Call the method we made above to decide what the shape of a contour is
                thishape = shape_compare(c)
                if(cv.contourArea(c)>100):
                        cv.drawContours(img, [c], -1, (0, 255, 0), 2)
                
                        cv.putText(img, thishape, (cX - 20, cY - 20),
                                cv.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
                        #if(thishape == "stop sign"):
                                #ser.write("X")
         
                cv.imshow("Image", img)
                cv.imshow("Threshold", thresh)
                cv.waitKey(1)
                #Remove this frame from the array
                camera_array.truncate(0)
