#include <Time.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

// this is for the fsr
#define DELAY 300 // temps entre enregistrement mesures
#define NB_FSR 10 //nombre capteurs de force

int pin_mean[NB_FSR]; // tableau contenant valeurs capteurs
unsigned long actual_time; // temps debut boucle
unsigned long start_time; // temps début acquisition données
unsigned long time_datalog; // temps début acquisition données
String dataString = "";
int pinFsr[] = {0, 1, 2, 7, 8, 10, 5, 4, 11, 3};
//this is for the button and led
const int buttonPin = 3;    //pin associe au bouton
const int ledPin =  2;      //pin de la led
int buttonState = 0;        // statut du bouton


//this is for the SD card 
File myFile; 
const int chipSelect = 17;

/*
    Fonction affichage mesures
*/

void print_data(int fsr) {
  Serial.print(pin_mean[fsr]);
  Serial.print(" ");
}

/**
 * ecrit donnees de chaques capteurs
 */
void display_data(int fsr) { 
  dataString += String(pin_mean[fsr]);
  dataString += " ";
}


/**
 * ecrit temps de chaques donnees
 */
void display_time() {
  dataString += String((actual_time - start_time) / 1000. );
  dataString +=" sec";
  dataString += " ";
}

void setup()
{
  Serial.begin(9600); // initialisation communication serie
  pinMode(buttonPin, INPUT); // initialise comme une entree
  pinMode(ledPin, OUTPUT); // initialise   comme sortie
  while (!Serial) // attend le debut communication serie
  delay(200);
  pinMode(SS, OUTPUT); // sortie

  if (!SD.begin(chipSelect)) {
    Serial.println("SD Card initialization failed!"); // echec communication carte SD
    return;  
  }
  start_time = millis(); // temps debut acquisition
  time_datalog += start_time; // temps enregistrement carte SD
  Serial.println("SD Card OK."); // communication carte SD reussie
  File myFile = SD.open("quatre.txt", FILE_WRITE); // ouvre fichier
  if(myFile){
    dataString = "date leftA leftA leftA Back front front rightA rightA rightA Back";
  }
}

void loop()
{
  delay(500);
  actual_time = millis();
  buttonState = digitalRead(buttonPin); // lit l'etat du bouton

  if (buttonState == LOW) {
    digitalWrite(ledPin, HIGH); // allume la led
       if (actual_time > time_datalog) { // affiche la valeur des capteurs tous les DELAY ms
          dataString = ""; // prochaines donnees a ecrire
          display_time(); // ecrit temps acquisition
          for (int fsr = 0; fsr < NB_FSR; fsr++) { // ecrit le max de chaque capteur depuis delay1
              pin_mean[fsr] = analogRead(fsr);
              display_data(fsr);
              print_data(fsr);
          }
          File myFile = SD.open("quatre.txt", FILE_WRITE); // ouvre fichier
          if (myFile) {
              myFile.println(dataString); // ecrit donnnees
              myFile.close(); // ferme fichier
              Serial.println("writing successfully");
          }
          else{
            Serial.println("writing failed");
          }
       }
       else{
          Serial.println("je suis ici ");
       }
  }
  digitalWrite(ledPin, LOW); // eteint la led
  

  
}
