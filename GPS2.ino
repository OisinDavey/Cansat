#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <math.h>

static const float K1=2,K2=3,K3=7;

static const int RXPin = 10, TXPin = 9;
static const uint32_t GPSBaud = 9600;

float LAT,LNG;
unsigned long lasttime=0;
float temperature,pressure;
int pressureValue;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

float Thermistor(int RawADC) {
  double Temp = RawADC;
  return Temp;
}

float EN(float input){
  if(input>=0)
    return input*input*K1 + input*K2 + K3;
  else 
    return -1*(input*input*K1 + -1*input*K2 + K3);
}

void setup(){
  Serial.begin(9600);
  ss.begin(GPSBaud);
}

void loop(){
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      LAT=gps.location.lat();
      LNG=gps.location.lng();
    }
  }///Calculating temperature
  temperature = Thermistor(analogRead(A0));
  
  ///Calculating pressure
  pressureValue = analogRead (A1);
  pressure = ((pressureValue / 1024.0) + 0.095) / 0.0009;
  
  if(millis()>(lasttime+500)){
    lasttime=millis();
    Serial.print("! -|Summerhill College|-");
    Serial.print("| Encrytion keys: ");
    Serial.print(K1);
    Serial.print(" ");
    Serial.print(K2);
    Serial.print(" ");
    Serial.print(K3);
    Serial.print(" | ");
    Serial.print("Latitude: ");
    Serial.print(EN(LAT),6);
    Serial.print(" | Longditude: ");
    Serial.print(EN(LNG),6);
    Serial.print(" | Pressure: ");
    Serial.print(EN(pressure));
    Serial.print(" | Temperature: ");
    Serial.println(EN(temperature));
  }
}
