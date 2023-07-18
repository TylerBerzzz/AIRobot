# AIRobot
A self-driving robot with networked environmental sensors that maps and controls its environment.

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

<More to be done

