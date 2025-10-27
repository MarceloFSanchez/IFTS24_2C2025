#include "lora1.h"
#include <SerialRAM.h> 

#define LED_PIN       12

SerialRAM ram;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  Serial.begin(115200);
  ram.begin();

  digitalWrite(LED_PIN, LOW);
  delay(300);
  digitalWrite(LED_PIN, HIGH);
  delay(300);
  digitalWrite(LED_PIN, LOW);
  delay(300);
  digitalWrite(LED_PIN, HIGH);
  delay(300);
  digitalWrite(LED_PIN, LOW);
  delay(300);
  digitalWrite(LED_PIN, HIGH);
 
  delay(8000); 
  digitalWrite(LED_PIN, LOW);
  
  Serial.println();
  Serial.println("*******************");
  Serial.println("*   EESA-IOT V2   *");
  Serial.println("*******************");
  Serial.println();
  
  LORA1_init();

  if (!ram.getAutoStore()) {
    ram.setAutoStore(true);
    ram.write(0x0100, 0);
    Serial.println("Autostore enabled!");
  }
  else
    Serial.println("Autostore already enabled!");

  digitalWrite(LED_PIN, HIGH);
  delay(2000); 
}

void loop()
{
  uint8_t x = 0;
  char s[30]; 
  
  Serial.println("");
  Serial.println("---------------------- EESA-IOT V2 LoRa SAMR34 ------------");
  LORA1_command((const char*)"sys get ver", 10000);
  LORA1_command("sys get hweui", 1000);
  Serial.println("");

  delay(2000);
  
  Serial.println("---------------------- EESA-IOT V2 EERAM 47L16 ------------");
  x = ram.read(0x0100);
  sprintf(s, "EERAM read: %d", x);
  Serial.println(s);
  ram.write(0x0100, x + 1);
  Serial.println(""); 

  delay(2000);
}
