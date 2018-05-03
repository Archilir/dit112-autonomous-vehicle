#importing packages
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2

#initialize camera, settings and grab reference to raw cam capture
camera = PiCamera()
camera.color_effects = (128,128)
camera.resolution = (320, 240)
camera.framerate = 32
rawCapture=PiRGBArray(camera, size=(320, 240))

#camera warmup, 0.1sec
time.sleep(0.1)

#capture frames from camera

for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
    #not sure what exactly this does so I'll just copy the comments
    #grabs the raw NumPy array representing image, then initializes timestamp
    #and occupied/unoccupied text
    #frame.array returns an image object in openCV terms
    image = frame.array
    #img_grey = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    
    ret,thresh1 = cv2.threshold(image,127,255,cv2.THRESH_BINARY)
    #thresh2 = cv2.adaptiveThreshold(image,255,cv2.ADAPTIVE_THRESH_MEAN_C,\
    #        cv2.THRESH_BINARY,11,2)
    ret,thresh3 = cv2.threshold(image, 127, 255, cv2.THRESH_TOZERO)
    
    #shows frame
    cv2.imshow("Frame", image)
    cv2.imshow("Threshold", thresh1)
    #cv2.imshow("Threshold2", thresh2)
    cv2.imshow("Threshold3", thresh3)
    key = cv2.waitKey(1) & 0xFF

    #clear stream to prepare for next frame
    #this is always mandatory, throws error otherwise
    rawCapture.truncate(0)

    #press q to quit
    if key==ord("q"):
                break
