#include <WiFiClientSecure.h>   // Include the HTTPS library
#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266WiFiMulti.h>   // Include the Wi-Fi-Multi library
#include "Arduino.h"
#include <EMailSender.h>
ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'
uint8_t connection_state = 0;
uint16_t reconnect_interval = 10000;
WiFiClient  client;
String data1="";
String data2="cmd";
String data=" MESSAGE";
EMailSender emailSend("sivaprasadpilla7@gmail.com", "tvgcjlhvnpdetvvq");
void gmail()
{
  EMailSender::EMailMessage message;
    
    message.subject = "SOLAR_MONI_SYSTEM"+data1;
    message.message = "This_is_Mail_From_ESP8266:"+data1;

    EMailSender::Response resp = emailSend.send("bashettyrishika@gmail.com", message);

    Serial.println("Sending status: ");

    Serial.println(resp.status);
    Serial.println(resp.code);
    Serial.println(resp.desc);  
}
void upload()
{
const char* server4 = "api.thingspeak.com";
const char* _getLink4 = "https://api.thingspeak.com/update?api_key=91SHW5GUCCRO6Y5M&field1="; // Thingspeak.com
//const char* _getLink4 = "https://api.thingspeak.com/update?api_key=CND8HFA3ARVFXXW8&field1="; // Thingspeak.com

 // Serial.println("data uploading");delay(1000);  
  client.connect(server4,80);
 if (client.connect(server4,80))     // "184.106.153.149" or api.thingspeak.com  https://api.thingspeak.com/apps/thinghttp/send_request?api_key=CT9B331KB5PLM1G5
  { 
    String getStr4 = _getLink4;
    client.print("GET "+getStr4+data1+"\n");
    client.print("HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n\n\n");
  }
  client.stop();

}

void readdata()
{
  data1="";delay(1000);
const char* server4 = "api.thingspeak.com";
const char* _getLink4 = " https://api.thingspeak.com/channels/562742/fields/1/last.txt"; // Thingspeak.com


  //Serial.println("data uploading");delay(1000);  
  client.connect(server4,80);
 if (client.connect(server4,80))     // "184.106.153.149" or api.thingspeak.com  https://api.thingspeak.com/apps/thinghttp/send_request?api_key=CT9B331KB5PLM1G5
  { 
    String getStr4 = _getLink4;
    client.print("GET "+getStr4+"\n");
    client.print("HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n\n\n");
    client.available();
    data1=client.readString();delay(1000);
    //Serial.println(data1);delay(1000);

if(data1[0]=='*')
{
  if(data2==data1)
  {
    
  }
  else
  {
  Serial.println(data1);upload();
  }
  data2=data1;
}
/*

 if((data1=="light1on")||(data1=="light1off")||(data1=="light2on")||(data1=="light2off")||(data1=="fan1on")||(data1=="fan1off")||(data1=="fan2on")||(data1=="fan2off"))
{
  Serial.print(data1);delay(1000);upload();
}
  
    if(data1[0]=='*')
    {
   Serial.println(data1);delay(10000);upload();
    }
    if((data1=="1")||(data1=="2")||(data1=="3")||(data1=="4")||(data1=="0"))
    {
   Serial.print(data1);delay(10000);
      }
      */
  }
  client.stop();
}



void setup()
{
  Serial.begin(9600);         // Start the Serial communication to send messages to the computer
  delay(10);
  //Serial.println('\n');

  wifiMulti.addAP("consciencetechnologies", "484conscience777");   // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("sivaji", "sivaji.123");
  wifiMulti.addAP("ZTE-sUQdqa", "5hjgxyh9");
  wifiMulti.addAP("project", "project.123");
  wifiMulti.addAP("iphone", "ily092111");

  //Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    //Serial.print('.');
  }
  //Serial.println('\n');
  //Serial.print("Connected to ");
  //Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  //Serial.print("IP address:\t");
 Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer
  //Serial.println('\n');

  //readdata();
//gmail();
}


void loop() 
{

while(1)
{
 // readdata();
  
 while(Serial.available())
 {
  data1=Serial.readString();delay(1000);
  upload();
gmail();
  
 }
 
}

}
