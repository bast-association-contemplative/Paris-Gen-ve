// définition des broches utilisées
#define  RELAIS_PIN   2
#define     LED_PIN  13

volatile char inChar;
boolean LIGHT = false;

void setup() {
  // initialize serial:
  Serial.begin(115200);
  
  pinMode(RELAIS_PIN, OUTPUT);
  digitalWrite(RELAIS_PIN,HIGH);
  
  pinMode(   LED_PIN, OUTPUT);

  // print help
  Serial.println("LIGHT Controller: starting..."); 
  Serial.println("Help Commands: ");
  Serial.println("    'P' = ON the light");
  Serial.println("    '0' = OFF the light");
  
  Serial.println("Waiting for Alpha Brainwaves...");
}

void loop() {
  
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = Serial.read();
    Serial.print("Received :");
    Serial.println(inChar);

    if( inChar == 'P' ){
        LightON();
        digitalWrite(LED_PIN, HIGH);
        delay(60000);
        LightOFF();
        digitalWrite(LED_PIN, LOW);
    } else if( inChar == '0' ) {
      LightOFF();
      digitalWrite(LED_PIN, LOW);
    }
  }
}

void LightON(){
  //ETAT ON
   digitalWrite(RELAIS_PIN,LOW);
   //Serial.print('LIGHT IS ON');
   digitalWrite(LED_PIN,HIGH);
}

void LightOFF(){
  //ETAT OFF
   digitalWrite(RELAIS_PIN,HIGH);
   //Serial.print('LIGHT IS OFF');
   digitalWrite(LED_PIN,LOW);
}
