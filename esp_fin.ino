#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

char ssid[] = "xxxxx"; //SSID here
char pass[] = "lucky1221"; // Password here

unsigned long Channel_ID =  2190048; //  Channel ID
const char * myWriteAPIKey = "AC7FZWBSXN50J8P2"; // write API key

int v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13;
int temp=0,pres=0,humid=0,light=0,alt=0;
String value="";
WiFiClient client;

const int Field_Number_1 = 1;
const int Field_Number_2 = 2;
const int Field_Number_3 = 3;
const int Field_Number_4 = 4;
const int Field_Number_5 = 5;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  internet();
}

void loop() {
  internet(); 
  if (Serial.available()) {
    // Serial.write(Serial.read());
    while (Serial.available() > 0) {
      value = Serial.readString();
      v0=value[0];
      v1=value[1];
      v2=value[2];
      v3=value[3];
      v4=value[4];
      v5=value[5];
      v6=value[6];
      v7=value[7];
      v8=value[8];
      v9=value[9];
      v10=value[10];
      v11=value[11];
      v12=value[12];

      humid=((v2-0x30)*10+(v3-0x30));
      pres=((v4-0x30)*100+(v5-0x30)*(10+v6-0x30));
      light=((v7-0x30)*100+(v8-0x30)*10+(v9-0x30));
      alt=((v10-0x30)*100+(v11-0x30)*10+(v12-0x30));
      temp=((v0-0x30)*10+(v1-0x30));

//temp=((v0*10)+v1);
// humid=((v2*10)+v3);
// pres=((v4*100)+(v5*10)+v6);
// light=((v7*100)+(v8*10)+v9);
// alt=((v10*100)+(v11*10)+v12);

      Serial.println(temp);
      Serial.println(humid);
      Serial.println(pres);
      Serial.println(light);
      Serial.println(alt);   

      // Serial.print(v0);
      // Serial.print(v1);
      // Serial.print(v2);
      // Serial.print(v3);
      // Serial.print(v4);
      // Serial.print(v5);
      // Serial.print(v6);
      // Serial.print(v7);
      // Serial.print(v8);
      // Serial.print(v9);
    }

  }
  upload();
}

void internet()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      delay(5000);
    }
  }
}

void upload()
{
  ThingSpeak.writeField(Channel_ID, Field_Number_1, temp, myWriteAPIKey);
  delay(15000);
  ThingSpeak.writeField(Channel_ID, Field_Number_2, humid, myWriteAPIKey);
  delay(15000);
  ThingSpeak.writeField(Channel_ID, Field_Number_3, pres, myWriteAPIKey);
  delay(15000);
  ThingSpeak.writeField(Channel_ID, Field_Number_4, light, myWriteAPIKey);
  delay(15000);
  ThingSpeak.writeField(Channel_ID, Field_Number_5, alt, myWriteAPIKey);
  delay(15000);
  value = "",temp=0;humid=0;pres=0;light=0,alt=0;
}
