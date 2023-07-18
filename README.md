# AIRobot
This robot was developed in 2018 and documentation originally lived on the hackster.io platform, [here](https://www.hackster.io/104667/airobot-320828). It has been transitioned to my github in 2023.

## Overview on the AiRobot System
The AiRobot system comprises of a group of networked sensors and a robot. Every device has sensors that deliver temperature, relative humidity, and air quality measurements to the Google IoT Cloud by using the Helium platform.
The AiRobot is meant for indoor use in homes. AiRobot support sensors are placed a known distance apart and the robot is placed in a calibrated spot. Once the AiRobot is switched on, it will wander between the AiRobot Support Sensors to collect data. The AiRobot knows where it is by using it's motor encoders.

![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/a669fd33-8d36-4374-a992-5a4bb7fdcf45)
![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/0919ab42-bb3b-44db-9400-59ed3cf76e79)


## AiRobot Support Sensors
![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/20bddace-2c83-4da1-a40a-1d98f9fe0eae)

The AiRobot Support Sensors continuously send temperature, humidity, and air quality information to the Google IoT Cloud through Helium. These Support Sensors are fixed at a known location in a room. This is important to building the several heatmaps.

## AiRobot Support Sensor Schematic
![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/5e6c85fd-e8b2-46ad-827a-fd2197b5a678)
The AiRobot Sensor schematic above gives insight on its capabilities. The Sensor has LEDs to help notify the user about programming and power activity. The Plantower (PMS5003) is our air quality sensor and the Si7021 is the RH/Temp sensor. J3 is a barrel jack connector, U3 are power input pins, and both are connected to U11 which is the L7805, which has an voltage input range of 7V-35V.
Note: we designed the board for a different SparkFun RH/temp sensor than what the board above was built for. It was an easy wiring fix.

![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/8953f965-7364-48b3-b32a-a5b9c1343512)
![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/5eb69880-e15c-4abd-9b66-ad03e2935e8e)

## How We Mounted AiRobot Support Sensor
![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/546b1401-9c8f-4f5a-a80c-c1e4ab04686c)
If you look closely on the bottom of the Arduino, we utilize the case with M3 screws to mount. We did not have enough time to 3D print an enclosure, so this was a quick, great, option!

## AiRobot Support Sensor Output & Cloud Data
![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/10e068f6-b50c-46be-8674-36f87f1339f6)

The photo above shows a test example on how data is sent to the cloud. The AiRobot Support Sensor are the lines that start with 2222.
The data is formatted in the following fashion:
SensorName, Temperature, Relative Humidity, PM0.3um, PM0.5um, PM10um, PM25um, PM50um, PM100um, PM1, PM2.5, PM10, nothing, nothing

**What's with all those PM's?**
PM stands for particulate matter. The PM03um, PM0.5um, PM35um, PM50um, PM100um are particle size ranges per 0.1L air.
PM1, PM2.5, PM10 are measurements of particle concentration measured in standard units (ug/m3).

## AiRobot Overview
Below is a picture of an overview of the electronics on AiRobot There is alot of stuff going on, right!?
![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/1fe3f5be-f47a-4543-a200-1d9c1e9b4b6d)

For AiRobot we used an Arduino Mega for data acquisition and movement, Helium for sending data to the google cloud, and the Raspberry Pi to send serial commands to the robot from the google cloud. The picture below shows that process.

![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/6246a750-dec5-4023-a193-62db6cf2c89b)

## AiRobotPower Structure
![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/feff0beb-8908-4c51-b78f-31200b648749)

## AiRobot Wiring Guide
Here's an interior look at the AiRobot. There is so much stuff going on! We did not have enough time to create a custom PCB to avoid wires traveling everywhere, so we used tape, zip ties, and and whatever we could to keep cables from becoming loose.
![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/96a61b8e-026b-484f-8f8a-eab06512823c)

### Motors
![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/633fe175-9019-4458-bcf3-3bcc9205b61f)

### Ultrasonic Sensors
![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/c7650e11-d02e-44a5-a6f3-fc0a8ad125ef)

### Temperature, Relative Humidity, and AIr Quality Sensors
![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/a33e794e-1afb-47ee-a537-586b2e062546)

## AiRobot Hardware
### Mounting and Securing
To mount objects to the chassis, we used several different methods: Tape, Screws, standoffs, 3D prints, and zip ties.

### Standoffs
![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/146c89d8-2545-4aad-bcaa-a405fa850aa1)

Standoffs were used to sandwich the two wooden plates together and secure objects on the platform (as seen in the photo above). We also used standoffs to mount the motor controllers to the AiRobot Chassis

### Zip Ties, 3D Prints, Screws
![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/40c2df57-f653-4882-bf44-f70d7443eb21)

We used zip ties to secure the 12V battery to the AiRobot chassis. The 3D printed parts were used to mount the Ultrasonic Sensors and Temperature/Humidity (SparkFun Si7021) to the chassis. The 3D prints had holes for M3 screws to go through, which were secured using a nut on the opposite side.

### Double Sided Tape
We used double sided tape to mount the PMS5003 (Air Quality) sensor, the Inverter, and the Raspberry Pi.

### Arduino Mega & Helium Mounting
![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/bbe52c97-2ada-4d13-8e72-c7fe64464d3e)

The helium plugs into the Arduino through the pins, which is how it is typically mounted. The Arduino Mega was secured with M3 screws that go through pre drilled through holes on the PCB and case

### Motor Mounting
![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/8b647771-eb90-4fd4-a678-ec079d7dc670)

We mounted the motors by pencil marking the L bracket hole pattern on the robot and drilling holes through. It was secured using a nut.

### AiRobot Drive Train 
![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/af2e7137-6566-4fd1-aeba-7c32148eb122)
![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/a0aa5c3a-627e-4e2b-a1b5-b338d394ed22)

AiRobot was built with 4 wheel drive. We chose 4 wheel drive because we knew that AiRobot would be carrying a heavy payload (>8kg).

All motors are the same model and have the following specs:
**Gear Ratio:** 131:1
**MaxRPM:** 80 RPM
**MaxTorque:** 250 oz-in
**Stall Current:** 5 A

The wheels are 75mm Polyurethane scooter wheels from Pololu. The wheel diameter is small because we wanted to support heavy loads. Scooter wheels works best on hard wood floors and has a disadvantage on carpet.

## Battery Considerations
Knowing the power consumption of all the electrical devices we intended to use was important before we purchased a battery. Before building the robot, we created a Power Consumption Table to figure out what kind of 12V battery Ah we needed. To do these calculations, we just used the power equation: P = IV

## Helium IoT Core
In this project we used the Helium IoT Core to get all of our data up to the cloud. The board was easy to use, and worked great! We won't go be creating a tutorial in this section on how to setup the helium to the google cloud, because they already have fantastic documentation on setup!

Here's the helium setup link: https://www.helium.com/dev/hardware-libraries/arduino

We used 3 Helium Atoms with an Arduino adapter to send to 1 Helium channel. All the data goes to 1 file in 1 bucket every 5 minutes on the google cloud.

## Google Cloud Services Computations
The data was added every 5 minutes to our bucket using a dataflow. The Google Cloud platform was used to create a virtual machine to help process our data. This was immensely helpful and allowed everything to be all in one place without being cluttered.

![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/ec229aa7-0739-43b6-9342-bb3415925219)

Once the data was uploaded to our bucket we used our virtual machine to process it and create heatmaps. Google Cloud Services has excellent tutorials on how to set up everything from virtual machines to Dataflow jobs and I recommend checking their documentation if you experience difficulty. The link to their tutorials page can be found below:

https://cloud.google.com/storage/docs/tutorials

## Heatmap Calculations
After the data was processed and the encoder information was transformed into displacement we needed to calculate the from a few individual points. To create the heatmaps from a bunch of discrete values we used an iterative approach which can be seen in the python code snippet below (for all code see bottom of page).

![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/75fc587a-afa4-4203-985e-f9ab28067431)

Each time through the while loop the unfinished heatmaps for temperature, humidity, and particles are copied. We search through every point in the heatmap array and if there is no value provided either by the robot or the supporting sensors we average the cell's 8 neighbors and set it to that value. If it has no neighbors we ensure to stay inside the while loop. After many iterations the discrete values will be expanded based on averaging and a distribution is created.

## Initial Heatmap Testing
In the heatmap graphs below, the origin of the AiRobot is (0, 0). The entire filled area is the bounds of our defined world. The robot starts of traveling in the positive x direction for 4 units (feet). At location [4, 0] the robot turns 90 degrees and travels to [4, -7]. The robot then finishes the rectangle traveling to [0, -7] and back to [0, 0] in that order. Below are the heatmaps for particles, temperature, and humidity for a sample run.

![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/a886b23a-16b1-4fb8-a107-e8bc42ef527a)
![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/ad9003ec-7c40-42b7-bfc5-80e382a03746)
![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/ee753cd3-2f13-4118-a4d4-640078b484d4)

## Heatmap Verification Testing
We wanted to make sure that our heatmap values made sense, so we placed a vaporizer, heater, and air purifier at different known locations in the room.

![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/8864d624-5ed5-4f4a-b96f-4d7b8f6ec5c0)

** In this picture, the AiRobot has sensors on the left side.

**For this testing we used the sensors at the same height as the robot.

The results of the test were promising and showed our robot was working. The following 3 images are the heatmaps for temperature, particles, and humidity. NOTE: THEY ARE ROTATED 90 DEGREES FROM ABOVE IMAGE

![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/59cc063e-f284-4537-8eee-92af6d8d863c)

The heater is located in the top right corner of this image which lines up well with the region of white denoting a high temperature value.

![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/a618cbd6-42ab-4241-8d40-5f537f8f654b)

The humidifier is located in the bottom right corner of this image which is consistent with our results. We see higher number of particles located in that bottom right corner.

![image](https://github.com/TylerBerzzz/AIRobot/assets/30520534/88db0278-59fe-4679-a241-fb408b1d975a)

The humidity heat map also agrees with our expected results as the humidifier is located in the bottom right corner. There appears to be roughly uniform humidity for the bottom two thirds of the image.

These three images give us stock in AiRobots ability to measure temperature, humidity, and particle distributions through a room.

## Driving to Pollution Source/Region of Interest
With an accurate heatmap the next step is to locate the region of interest and navigate there with the desired appliance. For example, if a region with high concentration of particles was detected an air purifier could be mounted on AiRobot and it would drive to the source. By driving to the source AiRobot is best able to improve air quality or issues. Appliances we used were a humidifier and air purifier. To navigate AiRobot to a spot on the heatmap the distance from Airobot's currently location and the bad spot was calculated. This was calculated on GCS and a txt file of the desired navigation commands was outputted. Our RPi then transferred the commands through serial and directed the robot to its desired location.

## Programming Instructions
Due to the massive amount of information, we struggled providing a step by step tutorial on how to fully build all components of AiRobot. But in this section, we hope to provide you some insight on how the programming works! All of our code is attached to this project as well.

The generic structure is laid out as follows:

1) Arduino Mega wanders around room reading encoders, particles sensor, temperature sensor, and humidity sensor. All this data is continuously streamed to the Google Cloud using helium.

2) After enough data is sent to Google cloud our virtual machine processes encoder information and converts it distance. Heatmaps are created using these distance measurements and the sensor values (temperature, humidity, particle concentration).

3) Point of interest is calculated from the heatmaps and serial directions on how to navigate there are calculated from virtual machine and uploaded to Google Cloud.

4) RPi copies directions from Google Cloud and transmits it to arduino through serial. This directs AiRobot to its final position where it stays and runs the desired appliance.

5) Lastly code runs on the virtual machine tracks sensor measurements in AiRobots location to monitor progress of cleaning the polluted area.

## Obstacles we encountered
This project was not easy. We encountered obstacles all along the way. Thanks to all nighters and never giving up, we overcame them.

Some problems we encountered were:

**1. Time.** This project was an enormous amount of work that was done in a short period of time. We are only a team of 2!

**2.Sleep.** Towards the submission date, we pulled several all nighters to work hard and overcome all obstacles we had to.

**3. PartSelection.** Given the time constraints and the complexity of this project, we were forced to make quick decisions about parts

**3.a Motor Selection.** When choosing the motors to use, we had to theoretically make sure that it was in the spec to carry our intended load. This load is based on alot of things, since we have alot of parts.

**4.PowerConsumption.** Depending on the appliance you wanted to put on the AiRobot platform, the weight of the unit and the total power consumption increases. When the power consumption increases, it changes our required lead acid battery size, which means much larger % changes in weight. Lead acid batteries are HEAVY!

**5.Robot Positioning.** We tried GPS - it was not good enough. We tried an accelerometer - it was not good enough. Signal Strength was not good enough. We had too little time to learn IR pattern recognition with a camera. This was an extremely tough obstacle, so we just relied on encoders.

**6.Encoders.** We had trouble reading all values of the encoders at the same time. This was a very annoying problem. We were forced to rely on encoder data from one wheel.

**7. Monitoringand controlling SO MANY THINGS.** Very stressful, very difficult. So much code that needed to be written for only 2 people in a incredibly constrained timeframe.

## Possible Future Improvements to AiRobot
We didn't have alot of time on this project, so we could not make AiRobot perfect. We're very satisfied with the work we completed though! Some future improvements:

**1.Moreaccurate Positioning.** We believe that this is the hardest part of this entire project. We believe that the IR method that Broomba's use might by the best chance to get this to work.

**2.Wander mode.** Once we have more accurate positioning, AiRobot can start from anywhere without being calibrated. It can truely walk randomly within a room.

**3.AiRobotAppliances.** If we were to hack or build the appliances we put on the AiRobot platform, we could customly modify the environment based on the data we receive without having to touch a button.
