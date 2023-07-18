import  time
import os

# Function to gran current time
def get_time():
    return time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime())

# Sleep for 14 seconds to allow for GCS to create data files
#time.sleep(14)
filename = "/home/blainejayotte/data_download/time.txt"
current_time=str(get_time())
# For debugging
print(current_time)
print(current_time[-5:-3])
print(int(current_time[-5:-3])%5)
if int(current_time[-5:-3])%5==0:
	with open(filename, "w") as f:
    		# Write data to file.
    		f.write(current_time)
		f.write("\n")
		f.write("Great Success")
	time.sleep(5)
	os.system("python /home/blainejayotte/data_download/heatmap_generator.py")
