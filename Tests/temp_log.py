import serial
import time
import sys
import csv

port = '/dev/ttyUSB0'
baud = 19200

ser = serial.Serial( port, baud)

if not ser.is_open:
    print("Can't open port")
    exit

while True:
    ser.write( b'e\r')
    ser.readline()
    print( ser.readline())
    ser.readline()
    time.sleep(1)
