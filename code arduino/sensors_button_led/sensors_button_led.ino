#define DELAY 300 // temps entre enregistrement mesures
#define NB_FSR 12 //nombre capteurs de force

int pin_mean[NB_FSR]; // tableau contenant valeurs capteurs
unsigned long prev; 
unsigned long time_loop; // temps debut boucle


const int buttonPin = 3;    //pin associe au bouton
const int ledPin =  2;      //pin de la led
int buttonState = 0;        // statut du bouton


/*
    Fonction affichage mesures
*/

void print_data(int fsr) {
  Serial.print(pin_mean[fsr]);
  Serial.print(" ");
}

void setup()
{
  Serial.begin(9600); // initialisation communication serie
  pinMode(buttonPin, INPUT); // initialise comme une entree
  pinMode(ledPin, OUTPUT); // initialise   comme sortie
  prev = millis();
}

void loop()
{
  time_loop = millis();
  buttonState = digitalRead(buttonPin); // lit l'etat du bouton

  if (buttonState == LOW) {
    digitalWrite(ledPin, HIGH); // allume la led
    if (time_loop - prev > DELAY) { // affiche la valeur des capteurs tous les DELAY ms
        for (int fsr = 0; fsr < NB_FSR; fsr++) {
          pin_mean[fsr] = analogRead(fsr);
          print_data(fsr);
        }
    Serial.println("");
    prev = millis();
   }
  }
 digitalWrite(ledPin, LOW); // eteint la led
  
}
