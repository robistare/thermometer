#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define MAX_SENSORS 4  // Maximum number of DHT sensors
#define DHTTYPE DHT11   // DHT sensor type

int sensorPins[MAX_SENSORS] = {2, 3, 4, 5};  // Digital pins connected to the DHT sensors
DHT_Unified* dht[MAX_SENSORS];

#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Hello World!");
  delay(1000);
  lcd.clear();
  
  for (int i = 0; i < MAX_SENSORS; i++) {
    dht[i] = new DHT_Unified(sensorPins[i], DHTTYPE);
    dht[i]->begin();
    
    sensor_t sensor;
    dht[i]->temperature().getSensor(&sensor);
    
  }
}

void loop() {
  // Delay between readings
 
  delay(1000);

  
  float avgTemperature = 0;
  float avgHumidity = 0;
  int validReadings = 0;
  bool errorOccurred = false;
  
  for (int i = 0; i < MAX_SENSORS; i++) {
    sensors_event_t event;
    dht[i]->temperature().getEvent(&event);
    
    if (!isnan(event.temperature)) {
      avgTemperature += event.temperature;
      validReadings++;
    }
    else {
      errorOccurred = true;
    }
    
    dht[i]->humidity().getEvent(&event);
    
    if (!isnan(event.relative_humidity)) {
      avgHumidity += event.relative_humidity;
    }
    else {
      errorOccurred = true;
    }
  }
  
  if (!errorOccurred && validReadings > 0) {
    avgTemperature /= validReadings;
    avgHumidity /= MAX_SENSORS;
    
    Serial.print("Average Temperature: ");
    Serial.print(avgTemperature);
    Serial.println(" °C");
    
    Serial.print("Average Humidity: ");
    Serial.print(avgHumidity);
    Serial.println(" %");

    lcd.setCursor(0, 0);
    lcd.print("T: ");
    lcd.print(avgTemperature);
    lcd.print(" C");
    lcd.setCursor(0, 1);
    lcd.print("H: ");
    lcd.print(avgHumidity);
    lcd.print(" %");
  }
  else {
    Serial.println("Error");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error");
  }
}

void cleanup() {
  for (int i = 0; i < MAX_SENSORS; i++) {
    delete dht[i];
  }
}
