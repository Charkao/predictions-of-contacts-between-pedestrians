
const int buttonPin = 3;    //pin associe au bouton
const int ledPin =  2;      //pin de la led
int buttonState = 0;        // statut du bouton

void setup() {

  pinMode(buttonPin, INPUT); // initialise comme une entree
  pinMode(ledPin, OUTPUT); // initialise   comme sortie
}

void loop() {

  buttonState = digitalRead(buttonPin); // lit l'etat du bouton

  // Si bouton enfonce
  if (buttonState == LOW) {
    digitalWrite(ledPin, HIGH); // allume la led
   
  } 
  digitalWrite(ledPin, LOW); // eteint la led
}
