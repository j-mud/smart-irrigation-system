#include "arduino_secrets.h"
#include "thingProperties.h"

// PIN CONFIGURATION 
const int moisturePin = A0;        
const int relayPin = 2;            

// THRESHOLD VALUE 
int dryThreshold = 2000;            

void setup() {
  Serial.begin(9600);
  delay(1500); 

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  pinMode(relayPin, OUTPUT);      
  digitalWrite(relayPin, LOW);     

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update(); 

  int moistureValue = analogRead(moisturePin);  
  soilMoisture = map(moistureValue, 3000, 500, 0, 100);      

  Serial.print("Raw Soil Moisture Value: ");
  Serial.println(moistureValue);

  Serial.print("Sending mapped moisture % to cloud: ");
  Serial.println(soilMoisture);

  if (moistureValue > dryThreshold) {
    Serial.println("Dry soil → Turning ON pump 💧");
    digitalWrite(relayPin, HIGH);  
  } else {
    Serial.println("Soil is moist → Turning OFF pump ✅");
    digitalWrite(relayPin, LOW);   
  }

  delay(3000);  
}


