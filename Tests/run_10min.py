import serial
import time
import sys
import csv

port = '/dev/ttyUSB0'
baud = 19200

gain = -1

script = sys.argv[0]

if len(sys.argv) > 3:
    gain = int(sys.argv[1])
    nsamp = int(sys.argv[2])
    ofile = sys.argv[3]
else:
    print("usage: ", script, " <gain> <nsamp> <file>")
    exit(1);

ser = serial.Serial( port, baud, timeout=2)

if not ser.is_open:
    print("Can't open port")
    exit

fp = open( ofile, "w")

# initialize
ser.write( b'\r')
time.sleep( 2)
ser.reset_input_buffer()

ser.write( b'c 0\r')
gset = "g %d\r" % gain
ser.write( gset.encode("utf-8"))
ser.write( b'a\r')

samp = 0

while samp < nsamp:
    data = ser.readline().decode('utf-8')
    cols = data.split(',')
    if len(cols) > 2:
        samp = int(cols[0])
        ch2 = int(cols[1])
        ch1 = int(cols[2])
        print( samp, ch1)
        fp.write( data)
        fp.flush()
        
