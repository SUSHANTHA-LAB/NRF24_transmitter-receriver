#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define CE_PIN   9
#define CSN_PIN 10

const byte thisSlaveAddress[5] = {'R','x','A','A','A'};

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;

Servo ESC;
Servo d3;
Servo d4;

struct D {
  byte trottle;
  byte Ru;
  byte El;
  };

D tdata;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(19200);
    Serial.println("SimpleRx Starting");
    radio.begin();
    radio.setPALevel(RF24_PA_MIN);
    radio.openReadingPipe(1, thisSlaveAddress);
    radio.startListening();
    ESC.attach(2,1000,2000);
    d3.attach(4);
    d4.attach(5);
    
}

void loop() {
  // put your main code here, to run repeatedly:
  if (radio.available()){
    radio.read(&tdata,sizeof(D));

    lastReceiveTime = millis();
    }

    currentTime = millis();
    if (currentTime - lastReceiveTime > 1000){
      resetData();
      }
   //Serial.print(tdata.trottle);
   Serial.print("\n");
  // Serial.print(tdata.Ru);
      Serial.print("\n");
   Serial.print(tdata.El);
       Serial.print("\n");
   ESC.write(tdata.trottle);
   if(tdata.Ru == 83){
      tdata.Ru = 90;
         d3.write(tdata.Ru);
    }
    else{
   d3.write(tdata.Ru);
    }
    if(tdata.El == 86){
        tdata.El = 90;
           d4.write(tdata.El);
      }
      else{
   d4.write(tdata.El);
      }

}

void resetData(){
  tdata.trottle = 0;
  tdata.Ru = 90;
    tdata.El = 90;
  }
