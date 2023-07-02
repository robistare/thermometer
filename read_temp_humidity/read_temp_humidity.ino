#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT1;
DFRobot_DHT11 DHT2;
#define DHT11_PIN_1 6
#define DHT11_PIN_2 5

#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

void setup() {
  Serial.begin(9500);
  lcd.begin(16, 2);
  lcd.print("Hello World!");
}

void loop() {
  DHT1.read(DHT11_PIN_1);
  DHT2.read(DHT11_PIN_2);

  lcd.clear();

  Serial.print("temp 1: ");
  Serial.print(DHT1.temperature);
  Serial.print("  humi 1: ");
  Serial.println(DHT1.humidity);

  Serial.print("temp 2: ");
  Serial.print(DHT2.temperature);
  Serial.print("  humi 2: ");
  Serial.println(DHT2.humidity);

  float avgTemp = (DHT1.temperature + DHT2.temperature) / 2.0;
  float avgHumidity = (DHT1.humidity + DHT2.humidity) / 2.0;

  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(avgTemp);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("H: ");
  lcd.print(avgHumidity);
  lcd.print(" %");

  delay(1000);
}
