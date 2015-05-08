#include <QuadMotorShields.h>
#include <ArduinoJson.h>

#include <SPI.h>
#include <Ethernet.h>

QuadMotorShields md;

StaticJsonBuffer<100> jsonBuffer;
StaticJsonBuffer<100> clearJson;

// To obtain server ip: Go to network settings->properties->IpV4 
// Make sure arduino's ip matches for first three numbers or else
// connections will fail.

byte server[] = {211, 255, 132, 121};
//byte server[] = {129, 65, 102, 107};  //TEMPORARY, QUICK-ACCESS ADDRESS
byte ip[] = {211, 255, 132, 49};

byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0x40, 0x9F};
int port = 1900;

int x,y,z,s1,s2;
String s = " ";
EthernetClient client;
int count = 0;

void setup() {
   //ASSIGN DIGITAL PINS
   pinMode(2,OUTPUT);
   pinMode(3,OUTPUT);
   //
   Serial.begin(9600);

   Ethernet.begin(mac, ip);
   delay(1000);

   Serial.println("connecting...");

   // if you get a connection, report back via serial:
   if (client.connect(server, port)) {
      Serial.println("connected.");
      client.println("This is a request from the client."); //print to server
   }
   else {
      if (client.connect(server, port)) {
         Serial.println("connected.");
         client.println("This is a request from the client.");
      }
      else {
          Serial.println("connection failed");
      }
   }
}

/* loop()
 * Reads message from client char by char and saves to a string.
 * This string is parsed into a json object using ArduinoJson.
 * The values for various variables is then obtained from this object. 
 * Using these various variables we control the robot! */

void loop()
{
   digitalWrite(2, LOW);
   digitalWrite(3, LOW);
   count++;
   if (client.available()) {
      char c = client.read();
      if(c == '~') {
	 int maxCommandLength = 70;
         char command[maxCommandLength];
         s.toCharArray(command, maxCommandLength);  
         JsonObject& root = jsonBuffer.parseObject(command);
         //Serial.print("JSON OBJECT: ");
         root.printTo(Serial);
	 x = (int)root["X"];
         y = (int)root["Y"];
         //r = root["R"];
         z = (int)root["Z"];

         md.setM1Speed(x);
         md.setM2Speed(y);
         md.setM3Speed(-z); //THIS IS CAUSING THE CONNECTION TO FAIL
         md.setM4Speed(z);
         //write to the solenoids here
         s1 = (int)root["S1"];
         s2 = (int)root["S2"];
         if(s1>0 or s1<0){
           digitalWrite(2, HIGH); //write to pin(s) controlling s1
         }
         if(s2>0 or s1<0){
           digitalWrite(3, HIGH); //write to pin(s) controlling s2
         }
         //
         if(count%2==0){
           printDebugInfo(x, y, z, s); 
           //client.print(s);
	 }
         jsonBuffer = clearJson;
         s = " ";
      }
      else {
         s += String(c);
      }

   }
  else { //client is no longer available
    client.connect(server, port);
    }
}



void printDebugInfo(int x, int y, int z, String s) {    
   Serial.println(s);
   Serial.print("X:");
   Serial.println(x);
   Serial.print("Y:");
   Serial.println(y);
   Serial.print("Z:");
   Serial.println(z);
}

