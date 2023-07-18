import os
import numpy as np
import matplotlib.pyplot as plt


os.system("gsutil cp gs://mybuckettest12345/data_monitor.txt /home/pi/Desktop/airobot/")
f=open("data_monitor.txt","r")
line=f.read()
data=line[0:-1].split(',')
x=np.arange(0,len(data))
y=np.zeros((1,len(data)))
for i in range(0,len(data)):
    y[0][i]=int(data[i])

print(x)
print(y)
plt.plot(y)
plt.show()