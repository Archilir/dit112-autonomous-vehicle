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

#Initialize serial
try:
    serial_arduino = serial.Serial('/dev/ttyACM0', 9600)
except Exception:
    serial_arduino = serial.Serial('/dev/ttyACM1', 9600)

time.sleep(1)
#Initialize camera object
camera = Camera(serial_arduino)
joystick = Joystick(serial_arduino)

#Initialize threads
camera.start()
joystick.start()
