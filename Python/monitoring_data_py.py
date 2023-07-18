import numpy as np
import time
import os
import glob
import copy as cp

# Remove all old files from VM instance
remove=True
if remove==True:
        del_files=glob.glob("/home/blainejayotte/data_download/files/*")
        for f in del_files:
                os.remove(f)
# Copy in new files from GCS
os.system("gsutil cp gs://mybuckettest12345/data/* /home/blainejayotte/data_download/files/")
#os.system("gsutil cp gs://mybuckettest12345/saved_data/output2018-07-15T14:35:00.000Z-2018-07-15T14:40:00.000Z-pane-0-last-00-of-01 /home/blainejayotte/data_downl$
os.chdir("/home/blainejayotte/data_download/files/")
# Remove all GCS txt files
#os.system("gsutil rm gs://mybuckettest12345/data/*")
# Read each line of the new files
lines=[]
for filename in os.listdir(os.getcwd()):
        new_lines=[line.rstrip('\n') for line in open(filename)]
        for j in range(0,len(new_lines)):
                lines.append(new_lines[j].split(','))

md=[]
for i in range(0,len(lines)):
        if len(lines[i])==2:
		md.append(str(lines[i][1])+',')

# save the txt file locally then copy to GCS
os.chdir("/home/blainejayotte/data_download/")
f = open('data_monitor.txt','w')
f.writelines(md)
f.close()
#send to cloud
os.system("gsutil cp data_monitor.txt gs://mybuckettest12345/")

