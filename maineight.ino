
// This is the code for the fish turning left and turning right and forward
// and the different kinds of motion can be combined with remote controller
// and the concur control of RGB led
// use latest ir code
// and add accelerometer and gyroscope
// and add DHT
// add SD module
/// change memory!!!! test!!!! crazy!!!!



#include <Servo.h>
#include <IRremote.h>
#include "DHT.h"
#define DHTPIN 3     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

//setup for remote controller
int IRpin=6;
IRrecv IR(IRpin);

String myCom;
int IRdelay=1000;

int disable_servo1 = 1;
int disable_servo12 = 1;

//setup for RGB led
int red_light_pin= 2;
int green_light_pin = 3; //useless
int blue_light_pin = 4;

//setup for three servos
float pos1=42;
float pos2=100;
float pos3=96;

int servoPin1=9;
int servoPin2=8;
int servoPin3=7;

int preDelay=10000;

// for forward
int servoDelay=10;
float servoAddTime=0.02;

float ratio1=2./3.;
float ratio2=65./90.*0.9;
float ratio3=64./90.*0.7;

// for turning
float k_turn=1.5;
int servoDelay_t=8;
float servoAddTime_t=0.02;

float ratio1_t=2./3.;
float ratio2_t=65./90.*0.9;
float ratio3_t=64./90.*0.9;

int RGBdelay=200;

float pi=3.14;
float t=0;

Servo Servo1;
Servo Servo2;
Servo Servo3;
bool Warned = 0;
float servoData[5][11]={
      {10,0.02,1.0,0.9,0.7,1.5,8,0.02,1.0,0.9,0.9},
      {25,0.03,1.0,0.7,0.5,1,25,0.03,1.0,0.6,0.6},
      {20,0.025,1.0,0.7,0.5,1.1,20,0.025,1.0,0.7,0.7},
      {15,0.02,1.0,0.8,0.6,1.2,15,0.02,1.0,0.8,0.8},
      {12,0.02,1.0,0.8,0.6,1.3,15,0.02,1.0,0.8,0.8},
      
      };

      
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);

  IR.enableIRIn();
  dht.begin();
  Servo1.attach(servoPin1);
  Servo2.attach(servoPin2);
  Servo3.attach(servoPin3);
  delay(preDelay);

  Serial.println("initinization done");

  RGB_color(255,255,255);
  delay(25000);
  RGB_color(0,0,0);
   
}





void loop(){

  
  RGB_color(0, 0, 0);
  
              float h = dht.readHumidity();
//            Serial.print("% Humidity: ");
//            Serial.println(h);

            if(h>40 and h<50 and Warned == 0)
            {
                RGB_color(255,0,0);
                delay(200);
                RGB_color(0,0,0);
                delay(200);
                RGB_color(255,0,255);
                delay(200); 
                RGB_color(255,0,0);
                delay(200);
                RGB_color(0,0,0);
                delay(200);
                RGB_color(255,0,255);
                delay(200); 
                Warned = 1;               
            }

            while(h>50)
            {
                RGB_color(0,0,0);
                RGB_color(255,0,0);
                delay(200);
                RGB_color(0,0,0);
                RGB_color(255,0,255);
                delay(200);     
                RGB_color(0,0,0);           
                RGB_color(0,0,255);
                delay(200);
            }

  if (IR.decode()){ 
    IR.resume();
    //Serial.println(IR.decodedIRData.decodedRawData,HEX);
    delay(IRdelay);

//    
//    if (IR.decodedIRData.decodedRawData==3125149440){
//    //myFile.println("End Test");
//    myFile.close();
//    //Serial.println("File closed.");
//    }

    if(IR.decodedIRData.decodedRawData==3175284480) // num 7
    {
      disable_servo1 = 0;
      RGB_color(255,0,0);
      delay(100);
      RGB_color(0,0,0);
      delay(100);
      RGB_color(255,0,0);
      delay(100); 
      RGB_color(0,0,0);
      delay(100);
      RGB_color(255,0,0);
      delay(500);
      RGB_color(0,0,0);
    }
    if(IR.decodedIRData.decodedRawData==2907897600) // num 8
    {
      disable_servo12 = 0;
      RGB_color(255,0,0);
      delay(500);
      RGB_color(0,0,0);
      delay(100);
      RGB_color(255,0,0);
      delay(100); 
      RGB_color(0,0,0);
      delay(100);
      RGB_color(255,0,0);
      delay(100);
      RGB_color(0,0,0);
    }
    if(IR.decodedIRData.decodedRawData==3041591040) // num 9
    {
      disable_servo1 = 1;
      disable_servo12 = 1;
      RGB_color(255,0,0);
      delay(200);
      RGB_color(0,0,0);
      delay(100);
      RGB_color(0,0,255);
      delay(200); 
      RGB_color(0,0,0);
      delay(100);
      RGB_color(255,0,255);
      delay(200);
      RGB_color(0,0,0);
    }

    if(IR.decodedIRData.decodedRawData==3810328320 or IR.decodedIRData.decodedRawData==2774204160) // num 5 or 6
    {
        RGB_color(255,0,255);
        delay(200);
        RGB_color(0,0,0);
        delay(200);
        RGB_color(255,0,255);
        delay(200);
        RGB_color(0,0,0);
        delay(200);
        RGB_color(255,0,255);
        delay(200);
        RGB_color(0,0,0);
        delay(200);
        RGB_color(255,0,255);
        delay(200);
        RGB_color(0,0,0);
        for(int i=1;i<=300;i++)
        {
          turn(0);        
        }
        if(IR.decodedIRData.decodedRawData==3810328320)
          for(int i=1;i<=300;i++)
          {
            turn(1);        
          }
        else
          for(int i=1;i<=300;i++)
          {
            turn(2);        
          }        


        Serial.println("go and turn");
    }


    int sc=-1;
    if(IR.decodedIRData.decodedRawData==4077715200)sc=1;
    if(IR.decodedIRData.decodedRawData==3877175040)sc=2;
    if(IR.decodedIRData.decodedRawData==2707357440)sc=3;
    if(IR.decodedIRData.decodedRawData==4144561920)sc=4;   
    if(IR.decodedIRData.decodedRawData==3910598400)sc=0;
    if (IR.decodedIRData.decodedRawData==3125149440) 
    {
                // Stop = 1;   
                RGB_color(255,0,0);
                delay(200);
                RGB_color(0,0,0);
                delay(200);
                RGB_color(255,0,0);
                delay(200);
                RGB_color(0,0,0);
                delay(200);
                RGB_color(255,0,0);
                delay(200);
                RGB_color(0,0,0);
                delay(200);            
                Serial.println("close file");
                   
    }

    if(sc!=-1)
    {     
      // for forward
      servoDelay=servoData[sc][0];
      servoAddTime=servoData[sc][1];

      ratio1=2./3.*servoData[sc][2];
      ratio2=65./90.*servoData[sc][3];
      ratio3=64./90.*servoData[sc][4];

      // for turning
      k_turn=servoData[sc][5];
      servoDelay_t=servoData[sc][6];
      servoAddTime_t=servoData[sc][7];

      ratio1_t=2./3.*servoData[sc][8];
      ratio2_t=65./90.*servoData[sc][9];
      ratio3_t=64./90.*servoData[sc][10];
   
      Serial.print("Change mode: speed ");
      Serial.println(sc);

      speed_light();
    }  


    bool Stop = 0;


    int mc = -1;
    String Com[3] = {"Go Forward","Turn Left","Turn Right"};
    
    if(IR.decodedIRData.decodedRawData==3141861120) mc=1; //left
    if(IR.decodedIRData.decodedRawData==3158572800) mc=2; //right
    if(IR.decodedIRData.decodedRawData==3208707840) mc=0; //forward

    if(mc!=-1)
    {
      
        myCom = Com[mc];
        //myFile.println("L");
        Serial.println(myCom); 
        while(1)
        {
    
            if(Stop==1)
            {
              if((mc==1 or mc==2) and abs(pos3-96)<5 and abs(pos2-100)<10)
              break;
              if(mc==0 and (abs(pos2-100)<5))
              break;
            }
    
            turn(mc);
            float h = dht.readHumidity();
//            Serial.print("% Humidity: ");
//            Serial.println(h);

            if(h>40 and h<50 and Warned == 0)
            {
                RGB_color(255,0,0);
                delay(200);
                RGB_color(0,0,0);
                delay(200);
                RGB_color(255,0,255);
                delay(200); 
                RGB_color(255,0,0);
                delay(200);
                RGB_color(0,0,0);
                delay(200);
                RGB_color(255,0,255);
                delay(200); 
                Warned = 1;               
            }

            while(h>50)
            {
                RGB_color(0,0,0);
                RGB_color(255,0,0);
                delay(200);
                RGB_color(0,0,0);
                RGB_color(255,0,255);
                delay(200);     
                RGB_color(0,0,0);           
                RGB_color(0,0,255);
                delay(200);
            }
    
        
            if (IR.decode() ) {
              IR.resume(); 
              if (IR.decodedIRData.decodedRawData==3927310080) {
                Stop = 1;               
                Serial.println("stop");
                   
              }

             }
        }

    }
    
    }

  delay(IRdelay);


  
}


void turn(int dir)
{

  int tur;
  if(dir==1)tur=1; else tur=-1;
  if(dir==1 or dir==2) //left
  {
    pos1=tur * atan(k_turn*(11*sin(2*pi/9+pi*t)/50+67./300.))/pi*180*ratio1_t*disable_servo1*disable_servo12+42;
    pos2=tur * atan(k_turn*(22*sin(4*pi/9+pi*t)/25+67./75.))/pi*180*ratio2_t*disable_servo12+100;
    pos3=tur * atan(k_turn*(99*sin(2*pi/3+pi*t)/50+201./100.))/pi*180*ratio3_t+96;
  }

  if(dir==0) //forward
  {
    pos1=atan(2*sin(2*pi/9+pi*t)/3)/pi*180*ratio1*disable_servo1*disable_servo12+42;
    pos2=atan(8*sin(4*pi/9+pi*t)/3)/pi*180*ratio2*disable_servo12+100;
    pos3=atan(6*sin(2*pi/3+pi*t))/pi*180*ratio3+96;
  }
  
  Servo1.write(pos1);
  Servo2.write(pos2);
  Servo3.write(pos3);

  int RGB[3][2] = {{0,255},{255,0},{255,255}};
  RGB_color(RGB[dir][0],0,RGB[dir][1]);  
  delay(servoDelay_t);
  t=t+servoAddTime_t;
}


void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  digitalWrite(red_light_pin, red_light_value);
  digitalWrite(green_light_pin, green_light_value);
  digitalWrite(blue_light_pin, blue_light_value);
}


void speed_light(){
    RGB_color(0, 0, 255);
    delay(RGBdelay);
    RGB_color(0, 0, 0);
    delay(RGBdelay);
    RGB_color(0, 0, 255);
    delay(RGBdelay);
    RGB_color(0, 0, 0); 
    delay(RGBdelay);
}




//void Store_SD(){
//
//  sensors_event_t a, g, temp;
//  mpu.getEvent(&a, &g, &temp); 
//  float h = dht.readHumidity();
//  
//  myFile.print("% Humidity: ");
//  myFile.println(h);
  
//  myFile.print("Acceleration X: ");
//  myFile.print(a.acceleration.x);
//  myFile.print(", Y: ");
//  myFile.print(a.acceleration.y);
//  myFile.print(", Z: ");
//  myFile.print(a.acceleration.z);
//  myFile.println(" m/s^2");
//
//  myFile.print("Rotation X: ");
//  myFile.print(g.gyro.x);
//  myFile.print(", Y: ");
//  myFile.print(g.gyro.y);
//  myFile.print(", Z: ");
//  myFile.print(g.gyro.z);
//  myFile.println(" rad/s");
//
//  myFile.print("Temperature: ");
//  myFile.print(temp.temperature);
//  myFile.println(" degC");

  
//}
