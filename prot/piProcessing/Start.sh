#!/bin/bash

cd /home/pi/Documents/dit112/dit112-autonomous-vehicle/prot/piProcessing
python ditCamera.py &
disown
python ditJoystick.py &
disown
jobs