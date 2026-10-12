#include "DHT.h"

#define DHTPIN 2          // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11     // Change to DHT22 if you're using that

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  delay(2000); // Give the sensor time to stabilize
}

void loop() {
  Serial.println("Reading sensor...");

  float humidity, temperature;
  int attempts = 0;

  // Retry up to 5 times if reading fails
  do {
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
    attempts++;
    delay(100);
  } while ((isnan(humidity) || isnan(temperature)) && attempts < 5);

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C | Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  delay(2000); // Wait 2 seconds between readings
}
