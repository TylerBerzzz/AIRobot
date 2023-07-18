#include <Helium.h>
#include "SparkFun_Si7021_Breakout_Library.h"
#include <SoftwareSerial.h>
#include <Wire.h>
#include "Arduino.h"
#include "Board.h"
#include "Helium.h"
#include "HeliumUtil.h"

//for uno
SoftwareSerial pmsSerial(2, 3);
//for mega only
//SoftwareSerial pmsSerial(10, 11);

 //Create Instance of HTU21D or SI7021 temp and humidity sensor and MPL3115A2 barrometric sensor
Weather sensor;

//Set initial Float Values
float humidity = 0;
float tempf = 0;

// NOTE:

Helium  helium(&atom_serial);
Channel channel(&helium);

void report_status(int status)
{
    if (helium_status_OK == status)
    {
        Serial.println("Succeeded");
    }
    else
    {
        Serial.println("Failed");
    }
}

void report_status_result(int status, int result)
{
    if (helium_status_OK == status)
    {
        if (result == 0)
        {
            Serial.println("Succeeded");
        }
        else {
            Serial.print("Failed - ");
            Serial.println(result);
        }
    }
    else
    {
        Serial.println("Failed");
    }
}

void
setup()
{
    Serial.begin(9600);
    Serial.println("Starting");

    // Begin communication with the Helium Atom
    // The baud rate differs per supported board
    // and is configured in Board.h
    helium.begin(HELIUM_BAUD_RATE);

    // Connect the Atom to the Helium Network
    Serial.print("Connecting - ");
    int status = helium.connect();
    // Print status
    //report_status(status);

    // Begin communicating with the channel. This should only need to
    // be done once.
    //
    // NOTE: Please ensure you've created a channel called "Helium
    // Cloud MQTT" called in the Helium Dashboard.
    int8_t result;
    Serial.print("Creating Channel - ");
    status = channel.begin("env-hub", &result);
    // Print status and result
    report_status_result(status, result);
 
  //PMS5003 Baud Rate is 9600
    pmsSerial.begin(9600);
  //Initialize the Si7021 and ping it
    sensor.begin();
}
 
struct pms5003data {
  uint16_t framelen;
  uint16_t pm10_standard, pm25_standard, pm100_standard;
  uint16_t pm10_env, pm25_env, pm100_env;
  uint16_t particles_03um, particles_05um, particles_10um, particles_25um, particles_50um, particles_100um;
  uint16_t unused;
  uint16_t checksum;
};
 
struct pms5003data data;

 
void loop() {
  //Serial.println("hi");
  
  if (readPMSdata(&pmsSerial)) {
    humidity = sensor.getRH();
    tempf = sensor.getTempF();
    
    
//----------------------------------------------------------
// String Section
  String SensorName = "3333"; // 1111 for robot and 2222 for other sensor
  char buffer[10];
  // Size ranges of particles - Good for histogram plot
  // Particles > 0.3um / 0.1L air
  String PM_03um = dtostrf(data.particles_03um, 0, 0, buffer);
  //Particles > 0.5um / 0.1L air
  String PM_05um = dtostrf(data.particles_05um, 0, 0, buffer);
  //Particles > 1.0um / 0.1L air
  String PM_10um = dtostrf(data.particles_10um, 0, 0, buffer);
  //Particles > 2.5um / 0.1L air
  String PM_25um = dtostrf(data.particles_25um, 0, 0, buffer);
  //Particles > 5.0um / 0.1L air
  String PM_50um = dtostrf(data.particles_50um, 0, 0, buffer);
  //Particles > 50 um / 0.1L air
  String PM_100um = dtostrf(data.particles_100um, 0, 0, buffer);

  // Concentration Units (standard)
  // PM 1.0
  String PM1 = dtostrf(data.pm10_standard, 0, 0, buffer);
  // PM 2.5
  String PM2p5 = dtostrf(data.pm25_standard, 0, 0, buffer);
  // PM 10
  String PM10 = dtostrf(data.pm100_standard, 0, 0, buffer);
  
  //Temperature RH
  String Tempf = dtostrf(tempf, 0, 2, buffer);
  String Humidity = dtostrf(humidity, 0, 2, buffer);
  
  //Convert all strings into One String to rule them all. **********USE THIS STRING TO SEND TO HELIUM!***********
  int8_t result;
  String HeliumData = SensorName + "," + Tempf + "," + Humidity + PM_03um + "," + PM_05um + "," + PM_10um + "," + PM_25um + "," + PM_50um + "," + PM_100um + "," + PM1 + "," + PM2p5 + "," + PM10+","+String(0)+","+String(0);
  const char * Data = HeliumData.c_str(); 
  Serial.println(Data); //Test Diagnostic
  // Send data to channel
  //const char * SendData = HeliumData;
  int status = channel.send(Data, strlen(Data), &result);
  //report_status_result(status, result);
  }
}
 
boolean readPMSdata(Stream *s) {
  if (! s->available()) {
    return false;
  }
  
  // Read a byte at a time until we get the'0x42' start-byte
  if (s->peek() != 0x42) {
    s->read();
    return false;
  }
 
  if (s->available() < 32) {
    return false;
  }
    
  uint8_t buffer[32];    
  uint16_t sum = 0;
  s->readBytes(buffer, 32);
 
  // get checksum ready
  for (uint8_t i=0; i<30; i++) {
    sum += buffer[i];
  }
  uint16_t buffer_u16[15];
  for (uint8_t i=0; i<15; i++) {
    buffer_u16[i] = buffer[2 + i*2 + 1];
    buffer_u16[i] += (buffer[2 + i*2] << 8);
  }
  memcpy((void *)&data, (void *)buffer_u16, 30);
 
  if (sum != data.checksum) {
    Serial.println("Checksum failure");
    return false;
  }
  return true;
}

