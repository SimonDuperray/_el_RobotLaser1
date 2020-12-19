#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C_Hangul.h>
#include <Wire.h>

#define hp 11

#define photoG A0
#define photoD A1

#define yellowB 13

const int rightBackward = 8;
const int rightForward = 9;
const int leftBackward = 10;
const int leftForward = 12;

int score = 0;

unsigned long MS;
unsigned long start;

LiquidCrystal_I2C_Hangul lcd(0x27, 16, 2);

void setup() {
  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);

  pinMode(yellowB, INPUT_PULLUP);

  pinMode(hp, INPUT);

  lcd.init();
  lcd.backlight();

  start = millis();

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

void game(){
  int valG = analogRead(photoG);
  int valD = analogRead(photoD);
  
  int tps = 0;
    
  if(valG < 100 or valD < 100){
    while(1){
      MS=millis()-start;
      Serial.print ((MS / 1000) / 60);      // minutes
      Serial.print ("' ");
      Serial.print ((MS / 1000) % 60);      // secondes
      Serial.print ("'' ");
      Serial.println (MS % 1000);           // millièmes 
      valG = analogRead(photoG);
      valD = analogRead(photoD);
      if(valG < 100 or valD < 100){
        tps = random(800, 2000);
        gauche();
        delay(tps);
        stopp();
        score++;
        tone(hp, 800, 80);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("====");
        lcd.setCursor(4, 0);
        lcd.print("score :");
        lcd.setCursor(11, 0);
        lcd.print(score);
        lcd.setCursor(12, 0);
        lcd.print("====");
        lcd.setCursor(0, 1);
        lcd.print("================");
      }
      if(((MS / 1000) % 60)==20){
        for(int k = 0; k<5; k++){
          tone(hp, 500, 80);
          delay(100);
          tone(hp, 200, 80);
          delay(100);
        }
      exit(0);
      }
      if(score==5){
        for(int j = 0;j<5;j++){
          tone(hp, 500, 80);
          delay(100);
          tone(hp, 800, 80);
          delay(100);
        }
      exit(0);
      }
    }
  }
}
 
void loop(){
  game(); 
}
