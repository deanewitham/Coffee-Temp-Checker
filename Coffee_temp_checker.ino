#include <OneWire.h>
#include <DallasTemperature.h>

// DS18b20 stuff
// data wire plugged into port 3 on arduino
#define ONE_WIRE_BUS 3
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

int ledpin = 2;
int dt = 5000;

int buzzpin = 7;
int alarm = 0;

void setup() {
  // Set up pins, the serial monitor, and the sensors
  pinMode(ledpin, OUTPUT);
  pinMode(buzzpin, OUTPUT);
  Serial.begin(115200);
  sensors.begin();
}

void loop() {
  // Get temperature from sensor
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  float tempF = DallasTemperature::toFahrenheit(tempC);
  // If the coffee temperature is under 140F, turn on green LED. If it falls to 135, sound a buzzer once
  if (tempF <=140){
    digitalWrite(ledpin, HIGH);
    if(tempF<=135 && alarm==0){
    digitalWrite(buzzpin, HIGH);
    delay(250);
    digitalWrite(buzzpin, LOW);
    alarm++;
  }
  }
  else{
    digitalWrite(ledpin, LOW);
  }
  
  Serial.println(tempF);
delay(dt);
}
