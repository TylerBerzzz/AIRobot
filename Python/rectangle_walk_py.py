import os
import serial
import time 
#make sure eto flush serial before writing to it to avoid an issues
#allow time for commands to be sent and processed

sleeptime=7
ser=serial.Serial(port='/dev/ttyACM0',baudrate=9600,parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE,bytesize=serial.EIGHTBITS,timeout=2)
time.sleep(sleeptime)
turn = '-325'
foot = '120'
adjust= '-35'

print("Starting")
for i in range(0,4):
    ser.flushInput() 
    ser.write('m '+foot)
    time.sleep(sleeptime)

ser.flushInput() 
ser.write('t '+turn)
time.sleep(sleeptime)

for i in range(0,4):
    ser.flushInput() 
    ser.write('m '+foot)
    time.sleep(sleeptime)

ser.flushInput() 
ser.write('t '+adjust)
time.sleep(sleeptime)

for i in range(0,3):
    ser.flushInput() #flush or youre fucked
    ser.write('m '+foot)
    time.sleep(sleeptime)
    
ser.flushInput() #flush or youre fucked
ser.write('t '+turn)
time.sleep(sleeptime)

for i in range(0,4):
    ser.flushInput() #flush or youre fucked
    ser.write('m '+foot)
    time.sleep(sleeptime)
    
ser.flushInput()
ser.write('t '+turn)
time.sleep(sleeptime)

for i in range(0,4):
    ser.flushInput() 
    ser.write('m '+foot)
    time.sleep(sleeptime)

ser.flushInput() 
ser.write('t '+adjust)
time.sleep(sleeptime)

for i in range(0,3):
    ser.flushInput() 
    ser.write('m '+foot)
    time.sleep(sleeptime)
    
ser.close()    
print("done")

    
    