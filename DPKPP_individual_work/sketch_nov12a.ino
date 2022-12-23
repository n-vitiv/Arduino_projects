#include "DHT.h"
#include "Wire.h" 
#include "LiquidCrystal_I2C.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
#define BUZZERPIN 7

//setup DHT component
DHT dht(DHTPIN, DHTTYPE);
// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27,20,4);

void setup() {
    pinMode(BUZZERPIN, OUTPUT);//initialize the buzzer pin as an output
    lcd.init();                      // initialize the lcd 
    dht.begin();
    Serial.begin(57600);
}

void loop() {
    delay(2000);
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float humidity = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float Ctemperature = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(humidity) || isnan(Ctemperature)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }

    // Print a message to the LCD.
    char temperature_string[16] = {0};
    char humidity_string[16] = {0};
    float x = 3.1415;
    sprintf(temperature_string, "Temp: ");
    sprintf(humidity_string, "Hum:  ");
    lcd.backlight();
    lcd.setCursor(1,0);
    lcd.print(temperature_string);
    lcd.print(Ctemperature, 2);
    lcd.print(" C");
    lcd.setCursor(1,1);
    lcd.print(humidity_string);
    lcd.print(humidity, 2);
    lcd.print(" ");
    lcd.print((char)37);
    if(humidity > 60)
    {
        for (int i = 0; i < 200; ++i)
        {
            digitalWrite(BUZZERPIN,HIGH);
            delay(2);
            digitalWrite(BUZZERPIN,LOW);
            delay(2);
        }
    }
    else
    {
        digitalWrite(BUZZERPIN,LOW);
    }
}
