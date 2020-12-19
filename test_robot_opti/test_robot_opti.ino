#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C_Hangul.h>
#include <Wire.h>

#define echoPin 6
#define trigPin 7

#define redLed 3
#define greenLed 2
#define yellowLed A2

#define hp 11

#define greenB 0
#define redB 1
#define yellowB 13

#define photoG A0
#define photoD A1

long duration;
long distance;

const int rightBackward = 8;
const int rightForward = 9;
const int leftBackward = 10;
const int leftForward = 12;

SoftwareSerial blth (4, 5);
LiquidCrystal_I2C_Hangul lcd(0x27, 16, 2);
//=============================================================================================
void setup() {
  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);

  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);

  pinMode(hp, INPUT);

  pinMode(greenB, INPUT_PULLUP);
  pinMode(redB, INPUT_PULLUP);
  pinMode(yellowB, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.print("====NewRobot====");
  lcd.setCursor(0, 1);
  lcd.print("================");
    
  Serial.begin(9600);
  blth.begin(9600);
}
//=============================================================================================
void led_welcoming(){
  int k = 0;
  while(k<5){
    digitalWrite(yellowLed, HIGH);
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);
    delay(200);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    delay(200);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    delay(200);
    k++;
    Serial.println(k);
    if(k==5){
      break;
    }
  }
}
//=============================================================================================
void avancer() {
  digitalWrite(rightBackward, LOW); 
  digitalWrite(rightForward, HIGH); 
  digitalWrite(leftBackward, LOW); 
  digitalWrite(leftForward, HIGH); 
}
//=============================================================================================
void reculer(){
  digitalWrite(rightBackward, HIGH); 
  digitalWrite(rightForward, LOW); 
  digitalWrite(leftBackward, HIGH); 
  digitalWrite(leftForward, LOW);
}
//=============================================================================================
void gauche(){
  digitalWrite(rightBackward, LOW); 
  digitalWrite(rightForward, HIGH); 
  digitalWrite(leftBackward, HIGH); 
  digitalWrite(leftForward, LOW);
}
//=============================================================================================
void droite(){
  digitalWrite(rightBackward, HIGH); 
  digitalWrite(rightForward, LOW); 
  digitalWrite(leftBackward, LOW); 
  digitalWrite(leftForward, HIGH);
}
//=============================================================================================
void stopp(){
  digitalWrite(rightBackward, LOW); 
  digitalWrite(rightForward, LOW); 
  digitalWrite(leftBackward, LOW); 
  digitalWrite(leftForward, LOW); 
}
//=============================================================================================
void ultrasonic_radar(){
  long duree, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duree = pulseIn(echoPin, HIGH);
  distance = duree*340/(2*10000);
  Serial.println(distance);
  /*if(distance<20){
    for(int i=0;i<3;i++){
      tone(hp, 100, 80);
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, HIGH);
      delay(100);
      tone(hp, 800, 80);
      digitalWrite(redLed, HIGH);
      digitalWrite(greenLed, LOW);
    } 
  }*/
  delay(100);
}
//=============================================================================================
void autonomous(){ 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;
  delay(10);
  if(distance>19){
    avancer();
  }
  if(distance<18){
    stopp();
    delay(500);
    reculer();
    delay(500);
    stopp();
    delay(100);
    avancer();
  }
}
//=============================================================================================
void blth_command(){
  int recvChar;
  
  int StateGreenB = digitalRead(greenB);
  int StateRedB = digitalRead(redB);
  int StateYellowB = digitalRead(yellowB);
  
  while(1){
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
    }
  }
}
//=============================================================================================
void game(){
  int valG = analogRead(photoG);
  int valD = analogRead(photoD);

  int StateYellowB = digitalRead(yellowB);
  int tamp;

  int tps = 0;

  if(valG < 700 or valD < 700){
    tps = random(500, 800);
    gauche();
    delay(tps);
    stopp();
    valG = analogRead(photoG);
    valD = analogRead(photoD);
    Serial.println(valD);
    if(valG < 700 or valD < 700){
      score++;
      tone(hp, 800, 80);
      lcd.print(score);
      //Serial.println(score);
    }
    if(score==5){
      for(int k = 0; k<5; k++){
        tone(hp, 500, 80);
        delay(100);
        tone(hp, 200, 80);
        delay(100);
      }
      exit(0);
    }
   }  
}
//=============================================================================================
void loop(){
  
  int StateGreenB = digitalRead(greenB);
  int StateRedB = digitalRead(redB);
  int StateYellowB = digitalRead(yellowB);
  
  if(StateGreenB == LOW){
    lcd.clear();
    lcd.print("==blth command==");
    lcd.setCursor(0, 1);
    lcd.print("================");
    blth_command();
    lcd.clear();
  }
  if(StateRedB==LOW){
    for(int i = 0; i < 3; i++){
      tone(hp, 500, 80);
      delay(100);
      tone(hp, 800, 80);
      delay(100);
      tone(hp, 200, 80);
      delay(500);
    }
  } 
  if(StateYellowB==LOW){
    int ValphotoG = analogRead(photoG);
    int ValphotoN = analogRead(photoD);
    while(StateYellowB != LOW){
      if(ValphotoG > 100 and ValphotoD > 100){
        stopp();
        ValPhotoG = analogRead(photoG);
        ValphotoD = analogRead(photoD);
        Serial.println(ValPhotoG);
        Serial.println(ValPhotoD);
        Serial.println("-----------------");
        delay(500);
        if(ValPhotoG < 100 or ValPhotoD < 100){
          tone(hp, 500, 80);
      }
      else{
        break;
      }
    }
    }  
  } 
  Serial.print("PhotoGauche :");
  Serial.println(analogRead(A0));
  Serial.println("///");
  Serial.print("PhotoDroite :");
  Serial.println(analogRead(A1));
  delay(500);
}
