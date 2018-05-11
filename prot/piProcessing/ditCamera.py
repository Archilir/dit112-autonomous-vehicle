from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import numpy as np
import cv2 as cv
import time

class Camera:
    #Initialize camera
    camera = PiCamera()

    #Set camera settings
    camera.resolution = (320, 240)
    camera.framerate = 30

    #Use an array of pixels for better performance
    camera_array = PiRGBArray(camera, size=(320, 240))
    
    def __init__(self, serial):
        self.serial = serial
        #Allow camera to start
        time.sleep(0.1)

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


    #Function to detect shapes in real time
    def detectShapes(frame, cont):
        for c in cont:
            #Calculate center of contours
            moment = cv.moments(c)
            if (moment["m00"] == 0):
                moment["m00"]=1
            cX = int(moment["m10"] / moment["m00"])
            cY = int(moment["m01"] / moment["m00"])

            #Call the method we made above to decide what the shape of a contour is
            thishape = shape_compare(c)
            if(cv.contourArea(c)>100):
                cv.drawContours(frame, [c], -1, (0, 255, 0), 2)
                        
                cv.putText(frame, thishape, (cX - 20, cY - 20),
                cv.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
                if(thishape == "stop sign"):
                    return True
        return False
    def detectColor(mask):
        color = cv.countNonZero(mask)
        if(color > 100):
            return True
        return False

    def detectSign(shape, color, serial):
        if(shape and color):
            serial.write('X')

    def processCamera():
        #Perform functions for each frame of the camera capture
        for frame in camera.capture_continuous(camera_array, format="bgr", use_video_port=True):
                img = frame.array

                #draw relevant color spaces
                #Use greyscale for easier recognition of contours
                gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
                
                #Guassian blur to smooth out the images
                blurred = cv.GaussianBlur(gray, (5, 5), 0)

                #A generic threshold to decide what we consider contours
                thresh = cv.threshold(blurred, 128, 255, cv.THRESH_BINARY_INV)[1]

                #convert BGR to HSV
                hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

                #
                #Find these contours based on the threshhold
                _, contours, _ = cv.findContours(thresh.copy(), cv.RETR_TREE,
                        cv.CHAIN_APPROX_SIMPLE)
                #
                #check color
                #define range of color
                lower_green = np.array([50, 100, 100])
                upper_green = np.array([70, 255, 255])
                
                #threshhold the hsv image to get only red
                mask = cv2.inRange(hsv, lower_green, upper_green)
            
                #bitwise-AND mask and original image
                res = cv2.bitwise_and(image, image, mask= mask)

                #
                #checks whether a stop sign and a color are detected. If they are, writes to serial.
                detectSign(detectColor(mask), detectShapes(img, contours), self.serial)
                #
                #draw images & contours
                cv.imshow("Image", frame)
                cv.imshow("Mask", res)
                cv.imshow("Threshold", thresh)

                camera_array.truncate(0)
        
