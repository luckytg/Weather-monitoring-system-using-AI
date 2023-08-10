#include <Wire.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 5
#define DHTTYPE DHT22
#define seaLevelPressure_hPa 1013.25

SoftwareSerial espSerial(10, 11);

int l; 
int a,h,t;
int p;

String str,temp,humid,press,alt,light;

Adafruit_BMP085 bmp;
DHT dht(DHTPIN, DHTTYPE);
  
void setup() {
  Serial.begin(115200);
  espSerial.begin(115200);

  lcd.init(); // initialize the lcd
  lcd.backlight();
  //humidity
  dht.begin();
  //pressure and temperature
  if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }
}
  
void loop() {
    h = dht.readHumidity();
    t = dht.readTemperature();

    float f = dht.readTemperature(true);
    if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
    }

    if(t>99){
      t=99;
    }
    else if(t<10){
      t=10;
    }
    Serial.print("Temperature = ");
    Serial.print(t);
    Serial.println(" *C");


    if(h>99){
      h=99;
    }
    else if(h<10){
      h=10;
    }
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");


    Serial.print("Pressure = ");
    p=bmp.readPressure()/100;
    if(p>999){
      p=999;
    }
    else if(p<100){
      p=100;
    }
    Serial.print(p);
    Serial.print("hPa\t");


    Serial.print("light intensity=");
    l =analogRead(A0);
    if(l>999){
      l=999;
    }
    else if(l<100){
      l=100;
    }
    Serial.println(l);


    Serial.print("altitude = ");
    a=bmp.readAltitude(seaLevelPressure_hPa * 100);
    if(l>999){
      l=999;
    }
    else if(l<100){
      l=100;
    }
    Serial.print(a);
    Serial.println("meters");

   
    //to sent esp serially
    Serial.println();
    temp=String(t);
    humid=String(h);
    press=String(p);
    light=String(l);
    alt=String(a);
    str=temp+humid+press+light+alt;
    espSerial.println(str);

  // lcd.clear();
  // lcd.setCursor(0, 0);
  // lcd.print("temperature : ");
  // lcd.print(temp);
  // lcd.print("*C");

  // lcd.setCursor(0, 1);
  // lcd.print("humidity : ");
  // lcd.print(humid);
  // lcd.print("%");
  // delay(15000);



  // lcd.setCursor(0, 0);
  // lcd.print("pressure : ");
  // lcd.print(press);
  // lcd.print("hPa");

  // lcd.setCursor(0, 1);
  // lcd.print("light : ");
  // lcd.print(light);
  // lcd.print("lux");
  // delay(15000);

  // lcd.clear();
  // lcd.setCursor(0,0);
  // lcd.print("t:");
  // lcd.print(temp);
  // lcd.print("*c");
  // lcd.setCursor(8,0);
  // lcd.print("h:");
  // lcd.print(humid);
  // lcd.print("%");
  // lcd.setCursor(0, 1);
  // lcd.print("p:");
  // lcd.print(press);
  // lcd.print("hPa");
  // lcd.setCursor(8, 1);
  // lcd.print("l:");
  // lcd.print(light);
  //   //  Serial.println(str);
  //   // espSerial.println(temp);
  //   // espSerial.println(humid);
  //   // espSerial.println(press);
  //   // espSerial.println(light);
  //   // espSerial.println(alt);

    delay(75000);
}