/* ----------------------------------------------------------------------------------------------------
 * PARIS <> GENEVE 2016
 * Update: 04/05/16
 *
 * Painting control by the brain through Internet
 *
 * Code get data on url http://one-billion-cat.com/test/openbci/index.php
 * 
 * V1.0
 * Written by Bastien DIDIER
 * more info : http://one-billion-cat.com
 *
 * ----------------------------------------------------------------------------------------------------
 */ 
  
#include <Process.h>
#include <Bridge.h>
#include <Console.h>

#define RELAY_PIN  2
#define   LED_PIN 13

void setup() {
  Bridge.begin();
  Console.begin();
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN,HIGH);
  
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  Process p;
  p.runShellCommand("/usr/bin/curl http://one-billion-cat.com/test/openbci/index.php");
  Serial.println("run curl command");
  
  while (p.running());
    while (p.available()) {
      int result = p.parseInt();
      Serial.println(result);
      
      if (result == 1){
        RelayON();
        digitalWrite(LED_PIN, HIGH);
        delay(60000);
        RelayOFF();
        digitalWrite(LED_PIN, LOW);
      } else {
        RelayOFF();
        digitalWrite(LED_PIN, LOW);
      }
    }
  delay (1000);
}

void RelayON(){
  digitalWrite(RELAY_PIN,LOW);
  //Serial.print('Relay IS ON');
  digitalWrite(LED_PIN,HIGH);
}

void RelayOFF(){
  digitalWrite(RELAY_PIN,HIGH);
  //Serial.print('Relay IS OFF');
  digitalWrite(LED_PIN,LOW);
}
