#include <DHT.h>

#define DHTPIN 6      // Pin where the DHT22 is connected
#define DHTTYPE DHT11 // Type of DHT sensor

// Soil Moisture Sensor Variables
int soilMoistureValue;
const int soilMoistureThreshold = 500; // Soil moisture threshold for pump control

// Pump control pin
#define PUMP_PIN 2 // Replace with the actual pin connected to the pump relay

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

void setup() {
  // Open Serial Monitor
  Serial.begin(9600);

  // Set ADC to use 3.3-volt AREF input
  analogReference(EXTERNAL);

  // Initialize pump pin as an output
  pinMode(PUMP_PIN, OUTPUT);
  // Turn off the pump initially
  digitalWrite(PUMP_PIN, LOW);

  // Initialize DHT sensor
  dht.begin();
}

void loop() {
  // Read soil moisture value
  soilMoistureValue = analogRead(A0); // Update this with the correct pin for your soil moisture sensor

  // Map the raw soil moisture value to a percentage (0-100%)
  int soilMoisturePercentage = map(soilMoistureValue, 0, 1023, 0, 100);

  // Read temperature and humidity from the DHT22 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Print soil moisture value as a percentage, temperature, and humidity to Serial Monitor
  Serial.print("Soil Moisture: ");
  Serial.print(soilMoisturePercentage);
  Serial.println(" %");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C | Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Check if soil moisture value is greater than the threshold
  if (soilMoistureValue > soilMoistureThreshold) {
    // Turn on the pump
    digitalWrite(PUMP_PIN, HIGH);
  } else {
    // Turn off the pump
    digitalWrite(PUMP_PIN, LOW);
  }

  // Add additional conditions for controlling the pump based on temperature and humidity
  if (temperature > 25.0 || humidity > 60.0) {
    // Turn on the pump when conditions are met
    digitalWrite(PUMP_PIN, HIGH);
  } else {
    // Deactivate the pump when conditions are not met
    digitalWrite(PUMP_PIN, LOW);
  }

  delay(1000);
}