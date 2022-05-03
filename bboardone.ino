#include <TinyMPU6050.h>
#include <SPI.h>
#include <SD.h>
#include <IRremote.h>
File myFile;
MPU6050 mpu (Wire);
#define IRpin 6
IRrecv IR(IRpin);
long randNumber;
String filename;



void setup() 
{ 
  Serial.begin(9600);
  randomSeed(analogRead(0));
  SD.begin(10);

  randNumber = random(3000);
  filename=String(randNumber)+".txt";
  Serial.println(filename);


  
  myFile = SD.open(filename, FILE_WRITE);
  
  
  mpu.Initialize();
  mpu.Calibrate();
  IR.enableIRIn(); 
  delay(1000);
  Serial.println('d');
}

void loop() 
{
  if (IR.decode())
  { 
    IR.resume();
    bool Stop=0;
    if (IR.decodedIRData.decodedRawData==3141861120 or IR.decodedIRData.decodedRawData==3208707840 or IR.decodedIRData.decodedRawData==3158572800){//left forw right
      Serial.println('j');
      if (IR.decodedIRData.decodedRawData==3141861120){
      myFile.println('l');
      }
      if (IR.decodedIRData.decodedRawData==3208707840){
      myFile.println('f');
      }
      if (IR.decodedIRData.decodedRawData==3158572800){
      myFile.println('r');
      }
      
      while(1)
      {
        mpu.Execute();
        delay(1000);
        if (IR.decode() ) {
          IR.resume(); 
          if (IR.decodedIRData.decodedRawData==3927310080) {
          Stop = 1;            
          Serial.println('o');  
          break;               
          }
        }         
          myFile.println("AX   AY   AZ   GX   GY   GZ");
          myFile.print(mpu.GetAccX());
          myFile.print(" ");
          myFile.print(mpu.GetAccY());
          myFile.print(" ");
          myFile.print(mpu.GetAccZ());
          myFile.print(" ");
          myFile.print(mpu.GetGyroX());
          myFile.print(" ");
          myFile.print(mpu.GetGyroY());
          myFile.print(" ");
          myFile.println(mpu.GetGyroZ());
          myFile.println(" ");
 
      }
      }
      if (IR.decodedIRData.decodedRawData==3125149440) {
        myFile.close();
        
        Serial.println('c');  
        randNumber = randNumber+1;
        filename=String(randNumber)+".txt";
        Serial.println(filename);
        myFile = SD.open(filename, FILE_WRITE);
           
      }    
  }
}
