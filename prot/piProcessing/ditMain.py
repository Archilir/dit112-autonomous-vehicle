from picamera.array import PiRGBArray
from picamera import PiCamera
from ditCamera import Camera
from ditJoystick import Joystick
import numpy as np
import cv2 as cv
import serial
import RPi.GPIO as GPIO
import time
import threading
import multiprocessing as mp

if __name__ == "__main__":
#Initialize serial
    try:
        serial_arduino = serial.Serial('/dev/ttyAMA0', 9600)
    except Exception:
        serial_arduino = serial.Serial('/dev/ttyACM1', 9600)
    time.sleep(1)
    #Initialize camera object
    camera = Camera(serial_arduino)
    joystick = Joystick(serial_arduino)

    #Initialize threads
    camera.start()
    joystick.start()

    #Initialize processes

    #with mp.Pool(2) as p:
    #    p.apply_async(camera.processCamera())
    #    p.apply_async(joystick.processJoystick())

    #mp.Process(target=camera.processCamera()).start()
    #mp.Process(target=joystick.processJoystick()).start()
