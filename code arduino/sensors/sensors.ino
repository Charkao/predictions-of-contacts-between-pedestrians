#define DELAY 300 // temps entre enregistrement mesures
#define NB_FSR 12 //nombre capteurs de force

int pin_mean[NB_FSR]; // tableau contenant valeurs capteurs
unsigned long prev; 
unsigned long time_loop; // temps debut boucle

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
  prev = millis();
}

void loop()
{
  time_loop = millis();
  if (time_loop - prev > DELAY) { // affiche la valeur des capteurs tous les DELAY ms
    for (int fsr = 0; fsr < NB_FSR; fsr++) {
      pin_mean[fsr] = analogRead(fsr);
      print_data(fsr);
    }
    Serial.println("");
    prev = millis();
  }
}
