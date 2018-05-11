from picamera.array import PiRGBArray
from picamera import PiCamera
from ditCamera import Camera
import numpy as np
import cv2 as cv
import serial
import RPi.GPIO as GPIO
import time
import threading

#Initialize serial
serial_arduino = serial.Serial('/dev/ttyACM0', 9600)

#Initialize camera object
camera = Camera(serial_arduino)

#Initialize threads
camera.processCamera()
