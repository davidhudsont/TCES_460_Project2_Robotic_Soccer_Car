import serial
import time

ser = serial.Serial('/dev/ttyACM0',115200)

while True:
	print(ser.readline())
	print(1)
	time.sleep(1)
	
