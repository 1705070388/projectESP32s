#include <BluetoothSerial.h>
#include "DHT.h"

#define dhtPin 2
#define DHTTYPE DHT11

DHT dht(dhtPin, DHTTYPE);
BluetoothSerial SerialBT; 

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT_Server"); // Set a name for Bluetooth server
  dht.begin();
}

void loop() {
 
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);


   if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

    SerialBT.print(F("Humidity: "));
SerialBT.print(h);
SerialBT.print(F("%  Temperature: "));
SerialBT.print(t);
SerialBT.print(F("°C "));
SerialBT.print(f);
SerialBT.print(F("°F  Heat index: "));
SerialBT.print(hic);
SerialBT.print(F("°C "));
SerialBT.print(hif);
SerialBT.println(F("°F"));
     delay(2000);
}