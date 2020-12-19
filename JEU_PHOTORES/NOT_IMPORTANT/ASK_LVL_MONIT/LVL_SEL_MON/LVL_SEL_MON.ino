#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C_Hangul.h>
#include <Wire.h>

#define hp 11

#define photoG A0
#define photoD A1

#define redLed 3
#define greenLed 2
#define yellowLed A2

const int rightBackward = 8;
const int rightForward = 9;
const int leftBackward = 10;
const int leftForward = 12;

int score = 0;
int tps = 0;
int ask_level;
int time_limit = 0;
int lvl;

unsigned long MS;
unsigned long start;

LiquidCrystal_I2C_Hangul lcd(0x27, 16, 2);

void setup(){
  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);

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

int flvl(){
  tps = random(200, 1000);
  time_limit = 25;
  lvl = 1;
}

int slvl(){
  tps = random(750, 1350);
  time_limit = 20;  
  lvl = 2;
}

int tlvl(){
  tps = random(1100, 1900);
  time_limit = 15;  
  lvl = 3;
}

void game(){
  int valG = analogRead(photoG);
  int valD = analogRead(photoD);
  
  lcd.setCursor(3, 0);
  lcd.print("Get Ready !");
  lcd.setCursor(4, 1);
  lcd.print("Level :");
  lcd.setCursor(11, 1);
  lcd.print(lvl);
        
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
        digitalWrite(yellowLed, HIGH);
      }
      if(((MS / 1000) % 60)==time_limit){
        for(int k = 0; k<5; k++){
          tone(hp, 500, 80);
          digitalWrite(redLed, HIGH);
          delay(100);
          tone(hp, 200, 80);
          digitalWrite(redLed, LOW);
          delay(100);
        }
      digitalWrite(yellowLed, LOW);  
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("Perdu...");
      exit(0);
      }
      if(score==5){
        for(int j = 0;j<5;j++){
          tone(hp, 500, 80);
          digitalWrite(greenLed, HIGH);
          delay(100);
          tone(hp, 800, 80);
          digitalWrite(greenLed, LOW);
          delay(100);
        }
      digitalWrite(yellowLed, LOW);  
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("Gagne !");
      exit(0);
      }
    }
  }
}

void loop(){
  if(Serial.available()){
    ask_level = Serial.read();
    Serial.println(ask_level);
  }
  if(ask_level==49){
    flvl();
  }
  if(ask_level==50){
    slvl();
  }
  if(ask_level==51){
    tlvl();
  }
  game();
}
