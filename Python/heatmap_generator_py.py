import numpy as np
import time
import os
import glob
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.path as mpath
import random
import copy as cp

# Remove all old files from VM instance
del_files=glob.glob("/home/blainejayotte/data_download/files/*")
for f in del_files:
	os.remove(f)

# Copy in new files from GCS
os.system("gsutil cp gs://mybuckettest12345/data/* /home/blainejayotte/data_download/files/")
#os.system("gsutil cp gs://mybuckettest12345/saved_data/output2018-07-15T14:35:00.000Z-2018-07-15T14:40:00.000Z-pane-0-last-00-of-01 /home/blainejayotte/data_download/files/")
os.chdir("/home/blainejayotte/data_download/files/")

# Remove all GCS txt files
#os.system("gsutil rm gs://mybuckettest12345/data/*")

# Read each line of the new files
lines=[]
for filename in os.listdir(os.getcwd()):
	new_lines=[line.rstrip('\n') for line in open(filename)]
	for j in range(0,len(new_lines)):
		lines.append(new_lines[j].split(','))

all_data=np.zeros((len(lines),13))
for i in range(0,len(lines)):
	all_data[i][0]=float(lines[i][0])
	all_data[i][1]=float(lines[i][1])
	all_data[i][2]=float(lines[i][2])
	all_data[i][3]=float(lines[i][3])
	all_data[i][4]=float(lines[i][4])
	all_data[i][5]=float(lines[i][5])
	all_data[i][6]=float(lines[i][6])
	all_data[i][7]=float(lines[i][7])
	all_data[i][8]=float(lines[i][7])
	all_data[i][9]=float(lines[i][9])
	all_data[i][10]=float(lines[i][10])
	all_data[i][11]=float(lines[i][11])
	all_data[i][12]=float(lines[i][12])
# Filter data into S1,S2,S3: Array for each sensor
S1=all_data[all_data[:,0] == 1111]
S2=all_data[all_data[:,0] == 2222]
S3=all_data[all_data[:,0] == 3333]

# delete all data before row in S1 with only len=2
append=False
create=True
clean_S1=np.zeros((len(S1),13))
ff=0
for i in range(ff,len(S1)-2):
	if append==True:
		if create==True:
			strt=i
			clean_S1=np.zeros((len(S1)-strt-2,13))
			create=False
		clean_S1[i-strt][0]=S1[i][0]
		clean_S1[i-strt][1]=S1[i][1]
		clean_S1[i-strt][2]=S1[i][2]
		clean_S1[i-strt][3]=S1[i][3]
		clean_S1[i-strt][4]=S1[i][4]
		clean_S1[i-strt][5]=S1[i][5]
		clean_S1[i-strt][6]=S1[i][6]
		clean_S1[i-strt][7]=S1[i][7]
		clean_S1[i-strt][8]=S1[i][8]
		clean_S1[i-strt][9]=S1[i][9]
		clean_S1[i-strt][10]=S1[i][10]
		clean_S1[i-strt][11]=S1[i][11]
		clean_S1[i-strt][12]=S1[i][12]

	if S1[i+2][1]!=0 and append==False:
		append=True

S1_pos=np.zeros((len(clean_S1),2))
# need to clean up encoder and turn information and convert to position
tpf=120
direction=[1,0]
pos=[0,0]
for i in range(1,len(clean_S1)):
	turn=clean_S1[i][12]
	#update position
	pos[0]=pos[0]+direction[0]*(clean_S1[i][11]-clean_S1[i-1][11])/tpf
	pos[1]=pos[1]+direction[1]*(clean_S1[i][11]-clean_S1[i-1][11])/tpf

	S1_pos[i][0]=pos[0]
	S1_pos[i][1]=pos[1]
	#update direction
	if turn==1: #CCW
		if direction==[1,0]:
			direction=[0,1]
		elif direction==[-1,0]:
                        direction=[0,-1]
		elif direction==[0,1]:
                        direction=[-1,0]
		elif direction==[0,-1]:
                        direction=[1,0]
	if turn==-1: #CW
		if direction==[1,0]:
                        direction=[0,-1]
                elif direction==[-1,0]:
                        direction=[0,1]
                elif direction==[0,1]:
                        direction=[1,0]
                elif direction==[0,-1]:
                        direction=[-1,0]

print(S1_pos)

# y,x
S2_loc=[3,5]
S3_loc=[-9,-1]
#Create meshgrid
mesh_square=1 # in ft
# these values need to be rounded to nearest half foot (or foot depends on resolution)
S1xmin=int(round(np.amin(S1_pos[:,0])))
S1xmax=int(round(np.amax(S1_pos[:,0])))
S1ymin=int(round(np.amin(S1_pos[:,1])))
S1ymax=int(round(np.amax(S1_pos[:,1])))
#determine if sensors are mins or maxs compared to robot
xmin=min(S1xmin,S2_loc[1],S3_loc[1])
xmax=max(S1xmax,S2_loc[1],S3_loc[1])
ymin=min(S1ymin,S2_loc[0],S3_loc[0])
ymax=max(S1ymax,S2_loc[0],S3_loc[0])

x=np.arange(int(xmin/mesh_square)-mesh_square,int(xmax/mesh_square)+mesh_square,mesh_square)
y=np.arange(int(ymin/mesh_square)-mesh_square,int(ymax/mesh_square)+mesh_square,mesh_square)
xx,yy=np.meshgrid(x,y)
w,h=xx.shape
# NOTE: heatmap plot cuts off last row and column so ignore it
Z_temp=np.zeros((w, h))
Z_humid=np.zeros((w, h))
Z_particle=np.zeros((w, h))
for i in range(0,len(clean_S1)):
	Z_temp[int(S1_pos[i][1]/mesh_square)-ymin][int(S1_pos[i][0]/mesh_square)-xmin]=clean_S1[i][1]
	Z_humid[int(S1_pos[i][1]/mesh_square)-ymin][int(S1_pos[i][0]/mesh_square)-xmin]=clean_S1[i][2]
	Z_particle[int(S1_pos[i][1]/mesh_square)-ymin][int(S1_pos[i][0]/mesh_square)-xmin]=clean_S1[i][9]

Z_temp[int(S2_loc[0]/mesh_square)-ymin][int(S2_loc[1]/mesh_square)-xmin]=S2[0][1]
Z_temp[int(S3_loc[0]/mesh_square)-ymin][int(S3_loc[1]/mesh_square)-xmin]=S3[0][1]
Z_humid[int(S2_loc[0]/mesh_square)-ymin][int(S2_loc[1]/mesh_square)-xmin]=S2[0][2]
Z_humid[int(S3_loc[0]/mesh_square)-ymin][int(S3_loc[1]/mesh_square)-xmin]=S3[0][2]
Z_particle[int(S2_loc[0]/mesh_square)-ymin][int(S2_loc[1]/mesh_square)-xmin]=S2[0][9]
Z_particle[int(S3_loc[0]/mesh_square)-ymin][int(S3_loc[1]/mesh_square)-xmin]=S3[0][9]
# Filling in all the values

# algorithm goes through all "empty" points and sets equal to average of 8 neighbors or closest value
loop=True
while loop==True:
	loop=False
	Z_copy_temp=cp.deepcopy(Z_temp)
	Z_copy_humid=cp.deepcopy(Z_humid)
	Z_copy_particle=cp.deepcopy(Z_particle)
	for i in range(0,w-1):
		for j in range(0,h-1):
			if Z_copy_temp[i][j]==0:
				#find average of 8 neighbors
				avg_temp=0
				avg_humid=0
				avg_particle=0
				avg_cnt=0
				rng=1
				for row in range(-rng,rng+1):
					for col in range(-rng,rng+1):
						try:
							val=Z_copy_temp[i+row][j+col]
							if val!=0:
								avg_temp+=Z_copy_temp[i+row][j+col]
								avg_humid+=Z_copy_humid[i+row][j+col]
								avg_particle+=Z_copy_particle[i+row][j+col]
								avg_cnt+=1
						except:
							pass

				if avg_cnt==0:
					loop=True
				else:
					Z_temp[i][j]=avg_temp/avg_cnt
					Z_humid[i][j]=avg_humid/avg_cnt
					Z_particle[i][j]=avg_particle/avg_cnt

os.chdir("/home/blainejayotte/data_download/heatmaps/")

fig_temp=plt.figure()
ax_temp=fig_temp.add_subplot(111)
pc_temp=ax_temp.pcolormesh(xx,yy,Z_temp,cmap='hot')
fig_temp.colorbar(pc_temp)
ax_temp.set_title('Temperature Heatmap')
plt.show()

timestr = time.strftime("%Y_%m_%d_%H_%M_%S")
heatmap_name_temp='heatmap_temp_'+timestr
plt.savefig(heatmap_name_temp)

fig_humid=plt.figure()
ax_humid=fig_humid.add_subplot(111)
pc_humid=ax_humid.pcolormesh(xx,yy,Z_humid,cmap='hot')
fig_humid.colorbar(pc_humid)
ax_humid.set_title('Humidity Heatmap')
plt.show()
heatmap_name_humid='heatmap_humid_'+timestr
plt.savefig(heatmap_name_humid)

fig_particle=plt.figure()
ax_particle=fig_particle.add_subplot(111)
pc_particle=ax_particle.pcolormesh(xx,yy,Z_particle,cmap='hot')
fig_particle.colorbar(pc_particle)
ax_particle.set_title('Particle Heatmap')
plt.show()
heatmap_name_particle='heatmap_particle_'+timestr
plt.savefig(heatmap_name_particle)

os.system("gsutil cp "+heatmap_name_temp+".png gs://mybuckettest12345/")
os.system("gsutil cp "+heatmap_name_humid+".png gs://mybuckettest12345/")
os.system("gsutil cp "+heatmap_name_particle+".png gs://mybuckettest12345/")

# time to locate and travel to problem area
# using particle sensor


max_val=np.amax(Z_particle)
for i in range(0,int(xmax-xmin+1)):
	for j in range(0,int(ymax-ymin+1)):
		if Z_particle[j][i]==max_val:
			particle_loc=[i+xmin,j+ymin]
			print(i,j)
			print(xmin,ymin)
			i=int(xmax-xmin+1)
			j=int(ymax-ymin+1)

#print(Z_particle[0][0],Z_particle[0][1],Z_particle[1][0])
#print(xmin,ymin)
#print(Z_particle)
#print(np.amax(Z_particle))
current_loc=[S1_pos[len(S1_pos)-1][0],S1_pos[len(S1_pos)-1][1]]
print(current_loc)
print(particle_loc)

commands=[]
d=[0,0]
d[0]=particle_loc[0]-current_loc[0]
d[1]=particle_loc[1]-current_loc[1]
# first go to desired x location
if d[0]>0:
	commands.append('t1,')
if d[0]<0:
	commands.append('t3,')
	d[0]=-d[0]
for i in range(0,int(d[0]+1)):
	commands.append('m1,')

# second go to desired y location
if d[1]>0:
        commands.append('t3,')
if d[1]<0:
        commands.append('t1,')
	d[1]=-d[1]
for i in range(0,int(d[1]+1)):
        commands.append('m1,')

print(commands)

# save the txt file locally then copy to GCS
os.chdir("/home/blainejayotte/data_download/")
f = open('commands.txt','w')
f.writelines(commands)
f.close()
#send to cloud
os.system("gsutil cp commands.txt gs://mybuckettest12345/")

