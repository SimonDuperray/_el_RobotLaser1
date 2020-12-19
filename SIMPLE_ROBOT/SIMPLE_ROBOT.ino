#include <SoftwareSerial.h>
//#include <PCM.h>

#define echoPin 5
#define trigPin 4

long duration;
long distance;

const int rightBackward = 8;
const int rightForward = 9;
const int leftBackward = 10;
const int leftForward = 12;

char buz = 11;

SoftwareSerial blth (2, 3);

void setup() {
  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);

  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  Serial.begin(9600);
  blth.begin(9600);
}

void avancer() {
  digitalWrite(rightBackward, LOW); 
  digitalWrite(rightForward, HIGH); 
  digitalWrite(leftBackward, LOW); 
  digitalWrite(leftForward, HIGH); 
}

void reculer(){
  digitalWrite(rightBackward, HIGH); 
  digitalWrite(rightForward, LOW); 
  digitalWrite(leftBackward, HIGH); 
  digitalWrite(leftForward, LOW);
}

void gauche(){
  digitalWrite(rightBackward, LOW); 
  digitalWrite(rightForward, HIGH); 
  digitalWrite(leftBackward, HIGH); 
  digitalWrite(leftForward, LOW);
}

void droite(){
  digitalWrite(rightBackward, HIGH); 
  digitalWrite(rightForward, LOW); 
  digitalWrite(leftBackward, LOW); 
  digitalWrite(leftForward, HIGH);
}

void stopp(){
  digitalWrite(rightBackward, LOW); 
  digitalWrite(rightForward, LOW); 
  digitalWrite(leftBackward, LOW); 
  digitalWrite(leftForward, LOW); 
}

void loop() {
  long duree, distance;
  int recvChar;
  while(1){
    digitalWrite(trigPin, LOW);  
    delayMicroseconds(2); 
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duree = pulseIn(echoPin, HIGH);
    distance = duree*340/(2*10000);
    Serial.println(distance);
    delay(50);
    if(distance<20){
        tone(11, 500, 80);
        delay(100);
      }
    if(blth.available()){
      recvChar = blth.read();
      Serial.println(recvChar);
      if(recvChar==0){
        stopp();
      }
      if(recvChar==1){
        avancer();
      }
      if(recvChar==2){
        reculer();
      }
      if(recvChar==3){
        gauche();
      }
      if(recvChar==4){
        droite();
      }
      if(recvChar==5){
        for(int i = 0; i<3; i++){
          tone(buz, 800, 500);
          delay(1000);
        }
      }
      if(recvChar==6){
        //startPlayback(sample, sizeof(sample));
      }
    }
  }
}
