  #include <DHT.h>
  #include <DHT_U.h>
  #include "DHT.h"
  #define DHT_A 2
  #define DHTTYPE DHT22
  float h;
  float t;
  float hic;
  const int A2pin = 2;
  DHT dht(A2, DHTTYPE);
  
void setup() {
  // put your setup code here, to run once:  
  Serial.begin(9600);
  pinMode(A2pin, INPUT);
  dht.begin();
}
void loop(){   
  sensorHumedad();  
  Serial.print(t);
  delay(100);
  Serial.print(h);
  delay(100);
}

void sensorHumedad(){
  h = dht.readHumidity();
  t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
   //Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  hic = dht.computeHeatIndex(t, h, false);

}
