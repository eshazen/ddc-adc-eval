import serial
import time

port = '/dev/ttyUSB0'
baud = 19200

ser = serial.Serial( port, baud)

if not ser.is_open:
    print("Can't open port")
    exit

while True:
    ser.write( b'l 0\r\n')
    time.sleep(0.1)
    ser.write( b'l 3\r\n')
    time.sleep(0.1)
    
    
