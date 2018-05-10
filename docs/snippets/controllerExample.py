import serial
import time

ser = serial.Serial('/dev/input/js0', baudrate=9600)
data = []
time0 = time.time()
while (time.time() - time0 < 5):  # Read data for 5 seconds
    data.append(ser.readline())
ser.close()
print(data)
