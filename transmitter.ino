#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10

const byte thisSlaveAddress[5] = {'R','x','A','A','A'};

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

struct D {
  byte trottle;
  byte Ru;
  byte El;
  };
D tdata;

int pot;
int pot2;
int pot3;

void setup() {
  // put your setup code here, to run once:   
    Serial.begin(19200);
    Serial.println("SimpleTx Starting");
    radio.begin();
    radio.setPALevel(RF24_PA_MIN);
    radio.setRetries(3,5); // delay, count
    radio.openWritingPipe(thisSlaveAddress);
    radio.stopListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  pot = analogRead(A0);
  pot3 = analogRead(A2);
  pot2 = analogRead(A3);
 Serial.print(pot3);
 Serial.print('\n');

  tdata.trottle = map(pot,0,1023,0,180);
  tdata.Ru = map(pot2,0,1023,60,120);
  tdata.El = map(pot3,0,1023,60,120);
  radio.write(&tdata,sizeof(D));
}
