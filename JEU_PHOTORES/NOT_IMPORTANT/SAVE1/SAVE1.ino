#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C_Hangul.h>
#include <Wire.h>

#define hp 11

#define photoG A0
#define photoD A1

const int rightBackward = 8;
const int rightForward = 9;
const int leftBackward = 10;
const int leftForward = 12;

int score = 0;

LiquidCrystal_I2C_Hangul lcd(0x27, 16, 2);

void setup() {
  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);

  pinMode(hp, INPUT);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
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

void loop(){
  int valG = analogRead(photoG);
  int valD = analogRead(photoD);

  int tps = 0;

  if(valG < 600 or valD < 600){
    tps = random(100, 1000);
    gauche();
    delay(tps);
    stopp();
    valG = analogRead(photoG);
    valD = analogRead(photoD);
    if(valG < 600 or valD < 600){
      score++;
      lcd.print(score);
      Serial.println(score);
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
