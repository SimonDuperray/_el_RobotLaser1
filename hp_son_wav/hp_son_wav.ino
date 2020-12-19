#include <SPI.h>
#include <SD.h> // Inclure la librairie SD
#define SDPIN 10 // Chip Select du lecteur SD
#include <TMRpcm.h> 

File myFile;
TMRpcm tmrpcm;

char caractere; // Définition du caractère pour la gestion dans le moniteur série

void setup(){
  Serial.begin(9600); // début de la communication série
  tmrpcm.speakerPin = 9; // Speaker sur la pin 9
  tmrpcm.setVolume(4); // gestion du volume de 0 à 7
  tmrpcm.quality(1); // qualitée audio 0 ou 1
  
  // Initialisation de la carte SD
  if (!SD.begin(SDPIN)) { 
    Serial.println("initialization failed!"); //  S'il y a un soucis "initialization failed!" s'affichera au moniteur
    return;
  }
  
  

}

void loop(){
      //tone(9, 500, 80);
      //delay(100);
      tmrpcm.play("test.wav"); // Joue le son "son8bit.wav"
 
}
