import os
import serial
import time 

ser=serial.Serial(port='/dev/ttyACM0',baudrate=9600)
time.sleep(5)

while True:
    command=raw_input("Enter command: ")
    ser.flushInput() 
    ser.write(command)