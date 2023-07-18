//Libraries
#include "SparkFun_Si7021_Breakout_Library.h"
#include <Wire.h>
#include <Helium.h>
#include <SoftwareSerial.h>
#include "Arduino.h"
#include "Board.h"
#include "Helium.h"
#include "HeliumUtil.h"

//Definitions - Encoder A and B

//Code for pin names
//First digit: R,L for right and left
//Second digit: F,B for front and back
//Third digit: A,B for encoder A and encoder B
#define RFA 18
#define RFB 19
#define RBA 50
#define RBB 51
#define LFA 2 //LFA PIN CHANGED FROM 42 to 2
#define LFB 3 //LFB PIN CHANGED FROM 43 TO 3
#define LBA 48
#define LBB 49

//Definitions - Enable Pins
#define RFE 11 //RFE PIN CHANGED from 2 TO 11
#define RBE 9 //RBE PIN CHANGED FROM 3 to 9
#define LFE 4
#define LBE 5

//Definitions - Motor Poles
#define RF1 26
#define RF2 27
#define RB1 28
#define RB2 29
#define LF1 7
#define LF2 8
#define LB1 32
#define LB2 33

//Definitions - Encoders
int RFval;
int RBval;
int LFval;
int LBval;
int RFpos = 0;
int RBpos = 0;
int LFpos = 0;
int LBpos = 0;
int RFlast = LOW;
int RBlast = LOW;
int LFlast = LOW;
int LBlast = LOW;
int RFn = LOW;
int RBn = LOW;
int LFn = LOW;
int LBn = LOW;

// wheel information definitions
const int diameter = 70; // in mm
const int pi = 3.141592654;
const int circumference = diameter * pi;
const int tickspercm = 360 / (diameter*pi);

//---------------------------------------

//Setup Serial Communication int
String Direction;           //the direction that the roobt will drive in
String distance;               //the distance you want to travel
String angle;

//Ultrasonic Sensors
const int trigPin1 = 36;
const int echoPin1 = 37;
const int trigPin2 = 38;
const int echoPin2 = 39;
const int trigPin3 = 40;
const int echoPin3 = 41;
// defines variables
long duration1;
int distance1;
long duration2;
int distance2;
long duration3;
int distance3;
int Boundary = 20;

bool first_on = true;
int RF_pos_copy = 0;
int TURNS = 0;

//Setup Software Serial for Sensors
SoftwareSerial pmsSerial(10, 11);
Weather sensor;
//Set initial Float Values
float humidity = 0;
float tempf = 0;

//Helium Channel
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


void setup() {
  Serial.begin(9600);
  //HELIUM Initialization
  // Begin communication with the Helium Atom
    // The baud rate differs per supported board
    // and is configured in Board.h
    helium.begin(HELIUM_BAUD_RATE);

    // Connect the Atom to the Helium Network
    Serial.print("Connecting - ");
    int status = helium.connect();
    int8_t result;
    Serial.print("Creating Channel - ");
    status = channel.begin("env-hub", &result);
    
    // Print status and result
    report_status_result(status, result);

    //PMS5003 Baud Rate is 9600
    pmsSerial.begin(9600);
  //Initialize the Si7021 and ping it
    sensor.begin();
    
  //Set Outputs
  pinMode(RFA, INPUT); pinMode(RFB, INPUT);
  pinMode(RBA, INPUT); pinMode(RBB, INPUT);
  pinMode(LFA, INPUT); pinMode(LFB, INPUT);
  pinMode(LBA, INPUT); pinMode(LBB, INPUT);

  pinMode(RFE, OUTPUT); pinMode(RBE, OUTPUT);
  pinMode(LFE, OUTPUT); pinMode(LBE, OUTPUT);

  pinMode(RF1, OUTPUT); pinMode(RF2, OUTPUT);
  pinMode(RB1, OUTPUT); pinMode(RB2, OUTPUT);
  pinMode(LF1, OUTPUT); pinMode(LF2, OUTPUT);
  pinMode(LB1, OUTPUT); pinMode(LB2, OUTPUT);

  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin3, INPUT); // Sets the echoPin as an Input

  //Motor Related Initilizations
  digitalWrite(RFA, LOW); digitalWrite(RFB, LOW);
  digitalWrite(RBA, LOW); digitalWrite(RBB, LOW);
  digitalWrite(LFA, LOW); digitalWrite(LFB, LOW);
  digitalWrite(LBA, LOW); digitalWrite(LBB, LOW);

  digitalWrite(RFE, LOW); digitalWrite(RBE, LOW);
  digitalWrite(LFE, LOW); digitalWrite(LBE, LOW);

  digitalWrite(RF1, LOW); digitalWrite(RF2, LOW);
  digitalWrite(RB1, LOW); digitalWrite(RB2, LOW);
  digitalWrite(LF1, LOW); digitalWrite(LF2, LOW);
  digitalWrite(LB1, LOW); digitalWrite(LB2, LOW);

  //Initialize the Si7021
  //sensor.begin(); //WE CHANGED THIS AND WE NEED TO GET IT RUNNING

  
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
  if (Serial.available() > 0)                         //if the user has sent a command
  {
    Direction = Serial.readStringUntil(' ');       //read the characters in the command until you reach the first space
    distance = Serial.readStringUntil(' ');           //read the characters in the command until you reach the second space
    angle = Serial.readStringUntil(' ');
    //print the command that was just received in the serial monitor
    Serial.print(Direction);
    Serial.print(" ");
    Serial.println(distance.toInt());

    if (Direction == "m")                         //if the entered direction is forward
    {
      Move(distance.toInt());
    }
    if (Direction == "t")                         //if the entered direction is forward
     {
      Turn(distance.toInt());
    }
    if (Direction == "r")                         //if the entered direction is forward
    {
      if (distance.toInt()==0){
        //monitor serial for movement commands
        //once at desired location then run r 1,2,3 depending on desired sensor
        Serial.println("waiting for commands")
        while (true) {
            if (Serial.available() > 0)                         //if the user has sent a command
  {
    Direction = Serial.readStringUntil(' ');       //read the characters in the command until you reach the first space
    distance = Serial.readStringUntil(' ');           //read the characters in the command until you reach the second space
    angle = Serial.readStringUntil(' ');
    //print the command that was just received in the serial monitor
    Serial.print(Direction);
    Serial.print(" ");
    Serial.println(distance.toInt());

    if (Direction == "m")                         //if the entered direction is forward
    {
      Move(distance.toInt());
    }
    if (Direction == "t")                         //if the entered direction is forward
     {
      Turn(distance.toInt());
    }
    if (Direction == "r")                         //if the entered direction is forward
    {
      if (distance.toInt()>0){


    if (distance.toInt()==1){
        char buffer[10];
        while (true){
          tempf = sensor.getTempF();
          String T = dtostrf(tempf, 0, 2, buffer);
            int8_t result;
            
            String HeliumData="1111,"+ T;
            const char * Data = HeliumData.c_str();
            Serial.println(Data); //Test Diagnostic
            int status = channel.send(Data, strlen(Data), &result);
          }
      }
      
      if (distance.toInt()==2){
        char buffer[10];
        while (true){
          humidity = sensor.getRH();
          String H = dtostrf(humidity, 0, 2, buffer);
            int8_t result;
            
            String HeliumData="1111,"+ H;
            const char * Data = HeliumData.c_str();
            Serial.println(Data); //Test Diagnostic
            int status = channel.send(Data, strlen(Data), &result);
          }
      }

      if (distance.toInt()==3){
        char buffer[10];
        while (true){
          
          if (readPMSdata(&pmsSerial)) {
   /*       
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
  */
  
  // Concentration Units (standard)
  // PM 1.0
  //String PM1 = dtostrf(data.pm10_standard, 0, 0, buffer);
  // PM 2.5
  String PM2p5 = dtostrf(data.pm25_standard, 0, 0, buffer);
  // PM 10
  //String PM10 = dtostrf(data.pm100_standard, 0, 0, buffer);

            int8_t result;
            
            String HeliumData="1111,"+ PM2p5;
            const char * Data = HeliumData.c_str();
            Serial.println(Data); //Test Diagnostic
            int status = channel.send(Data, strlen(Data), &result);
          }
          }
      }
      
    }
          }
      }
      }
      }
  }
  }
  else
  {
    //blah                               //turn the motors
  }
  if (readPMSdata(&pmsSerial)) {
    humidity = sensor.getRH();
    tempf = sensor.getTempF();
    
    
//----------------------------------------------------------
// String Section
  String SensorName = "1111"; //2222,3333,etc.
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
  if (first_on==true){
    first_on=false;
    String HeliumData="1111,-9999,0,0,0,0,0,0,0,0,0,0,0";
    const char * Data = HeliumData.c_str();
    Serial.println(Data); //Test Diagnostic
    delay(1);
    int status = channel.send(Data, strlen(Data), &result);
    }
  String HeliumData = SensorName + "," + Tempf + "," + Humidity + PM_03um + "," + PM_05um + "," + PM_10um + "," + PM_25um + "," + PM_50um + "," + PM_100um + "," + PM1 + "," + PM2p5 + "," + PM10 + ","+String(RF_pos_copy)+","+String(TURNS);
  const char * Data = HeliumData.c_str(); 
  Serial.println(Data); //Test Diagnostic
  Serial.println(RF_pos_copy);
  Serial.println(TURNS);
  //after turns gets uploaded set back to 0
  TURNS=0;
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
    //Serial.println("Checksum failure");
    return false;
  }
  return true;
}
//
void Move(int distance)                       //function for driving the right motor
{
  digitalWrite(RFE, HIGH); digitalWrite(RBE, HIGH);
  digitalWrite(LFE, HIGH); digitalWrite(LBE, HIGH);
  if (distance > 0) {
    while (RFpos < distance) {
      RFn = digitalRead(RFA);
      if ((RFlast == LOW) && (RFn == HIGH)) {
        if (digitalRead(RFB) == LOW) {
          RFpos--;
          RF_pos_copy--;
        }
        else {
          RFpos++;
          RF_pos_copy++;
        }
        if((distance2<Boundary and distance2>0) or (distance1<Boundary and distance1>0) or (distance3<Boundary and distance3>0)){ //or distance1<Boundary or distance3<Boundary
          Serial.print(distance2);
          Serial.println(",OBJECT!");
          RFpos=0;
          distance2=0;
          Stop();
          break;
        }
        Serial.println(RFpos);
        Serial.println(RF_pos_copy);
        
//        Serial.print(",");
//        Serial.print(distance1);
//        Serial.print(",");
//        Serial.print(distance2);
//        Serial.print(",");
//        Serial.println(distance3);
        
      }
      RFlast = RFn;

      digitalWrite(RF1, HIGH);
      digitalWrite(RB2, HIGH);
      digitalWrite(LF1, HIGH);
      digitalWrite(LB2, HIGH);

      digitalWrite(LF2, LOW);
      digitalWrite(LB1, LOW);
      digitalWrite(RF2, LOW);
      digitalWrite(RB1, LOW);
    }
    RFpos = 0;
    Stop();
  }
  if (distance < 0) {
//    analogWrite(RFE, 215); analogWrite(RBE, 215);
//    analogWrite(LFE, 215); analogWrite(LBE, 215);
    while (RFpos > distance) {
      RFn = digitalRead(RFA);
      if ((RFlast == LOW) && (RFn == HIGH)) {
        if (digitalRead(RFB) == LOW) {
          RFpos--;
          RF_pos_copy--;
        }
        else {
          RFpos++;
          RF_pos_copy++;
        }
        Serial.println(RFpos);
      }
      RFlast = RFn;
      
          digitalWrite(RF1, LOW);
          digitalWrite(RB2, LOW);
          digitalWrite(LF1, LOW);
          digitalWrite(LB2, LOW);

          digitalWrite(LF2, HIGH);
          digitalWrite(LB1, HIGH);
          digitalWrite(RF2, HIGH);
          digitalWrite(RB1, HIGH);
    }
  RFpos = 0;
  Stop();
  }
}
void Turn(int angle) {
  digitalWrite(RFE, HIGH); digitalWrite(RBE, HIGH);
  digitalWrite(LFE, HIGH); digitalWrite(LBE, HIGH);
  if (angle > 0) {
    while (RFpos < angle) {
      RFn = digitalRead(RFA);
      if ((RFlast == LOW) && (RFn == HIGH)) {
        if (digitalRead(RFB) == LOW) {
          RFpos--;
        }
        else {
          RFpos++;
        }
        
        Serial.println(RFpos);
        //Serial.print(",");
      }

      RFlast = RFn;

      digitalWrite(RF2, LOW);
      digitalWrite(RB1, LOW);
      digitalWrite(LF1, LOW);
      digitalWrite(LB2, LOW);

      digitalWrite(RF1, HIGH);
      digitalWrite(RB2, HIGH);
      digitalWrite(LF2, HIGH);
      digitalWrite(LB1, HIGH);
    }
          if (RFpos>90){
          TURNS=1;}
          if (RFpos<-90) {TURNS=-1;}
    RFpos = 0;
    Stop();
  }
  if (angle < 0) {
    while (RFpos > angle) {
      RFn = digitalRead(RFA);
      if ((RFlast == LOW) && (RFn == HIGH)) {
        if (digitalRead(RFB) == LOW) {
          RFpos--;
        }
        else {
          RFpos++;
        }

        Serial.println(RFpos);
      }

      RFlast = RFn;

      digitalWrite(RF1, LOW);
      digitalWrite(RB2, LOW);
      digitalWrite(LF2, LOW);
      digitalWrite(LB1, LOW);

      digitalWrite(RF2, HIGH);
      digitalWrite(RB1, HIGH);
      digitalWrite(LF1, HIGH);
      digitalWrite(LB2, HIGH);
    }
          if (RFpos>90){
          TURNS=1;}
          if  (RFpos<-90){TURNS=-1;}
    RFpos = 0;
    Stop();
  }
}
void Stop() {
  digitalWrite(LF2, LOW);
  digitalWrite(LB1, LOW);
  digitalWrite(RF2, LOW);
  digitalWrite(RB1, LOW);
  digitalWrite(RF1, LOW);
  digitalWrite(RB2, LOW);
  digitalWrite(LF1, LOW);
  digitalWrite(LB2, LOW);
  delay(250);

}
int Ultrasonic() {
  // Clears the trigPin
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);
  // Calculating the distance
  distance1 = duration1 * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance1: ");
  //Serial.print(distance1);
  //Serial.print(",");
  delay(10);

  // Clears the trigPin
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance2: ");
  //Serial.print(distance2);
  //Serial.print(",");
  delay(10);

  // Clears the trigPin
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration3 = pulseIn(echoPin3, HIGH);
  // Calculating the distance
  distance3 = duration3 * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance3: ");
  //Serial.println(distance3);
  delay(10);

}

