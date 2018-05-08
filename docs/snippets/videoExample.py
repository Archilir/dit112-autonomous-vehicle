#importing packages
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2

#initialize camera, settings and grab reference to raw cam capture
camera = PiCamera()
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

    #drawing a rectangle
    #arguments: image to draw on
    #top left corner
    #bottom right corner
    #color in BGR values
    #thickness

    #top left coordinate is always 0,0
    image = cv2.rectangle(image, (384, 0), (510, 128), (0, 255, 0),3)

    #shows frame
    cv2.imshow("Frame", image)
    key = cv2.waitKey(1) & 0xFF

    #clear stream to prepare for next frame
    #this is always mandatory, throws error otherwise
    rawCapture.truncate(0)

    #press q to quit
    if key==ord("q"):
                break
