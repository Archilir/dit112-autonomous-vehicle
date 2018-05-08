#import necessary packages
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2

#initializing camera and grabbing reference to raw camera capture
camera = PiCamera()
rawCapture = PiRGBArray(camera)

#allow the camera to warmup(??)
time.sleep(0.1)

#grab image from camera
camera.capture(rawCapture, format="bgr")
image = rawCapture.array

#display image until a key is pressed
cv2.imshow("Image", image)
cv2.waitKey(0)
