import os
import serial
import time
import numpy as np 

os.system("gsutil cp gs://mybuckettest12345/commands.txt /home/pi/Desktop/airobot/")
f=open("commands.txt","r")
line=f.read()
commands=line[0:-1].split(',')
print(commands)

sleeptime=5
ser=serial.Serial(port='/dev/ttyACM0',baudrate=9600,parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE,bytesize=serial.EIGHTBITS,timeout=2)
time.sleep(sleeptime)
turn = '-325'
foot = '122'

print("Starting")
ser.flushInput()
ser.write('r 0')
time.sleep(sleeptime)

fc=0
for i in range(0,len(commands)):
    ser.flushInput() #flush or youre fucked
    if commands[i]=='t1':
        com='t '+turn
        print('turn')
    if commands[i]=='m1':
        com='m '+foot
        print('forward')
        fc+=1
        
    ser.write(com)
    time.sleep(sleeptime)
    if fc==3:
        ser.flushInput()
        ser.write('t -15')
        time.sleep(sleeptime)
        fc=0
        
        

ser.flushInput()
ser.write('r 3')
print("At particle heavy location!")
print("Absorbing ...")




