#include <QuadMotorShields.h>
#include <ArduinoJson.h>

#include <SPI.h>
#include <Ethernet.h>

QuadMotorShields md;

StaticJsonBuffer<200> jsonBuffer;
StaticJsonBuffer<200> clearJson;

// To obtain server ip: Go to network settings->properties->IpV4 
// Make sure arduino's ip matches for first three numbers or else
// connections will fail.

byte server[] = {211, 255, 132, 121};
byte ip[] = {211, 255, 132, 49};

byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0x40, 0x9F};
int port = 1900;
EthernetClient client;

void setup() {
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
   int x,y,r,z = 0;   
   if (client.available()) {
      String s = " ";
      char c = client.read();
      if(c == ' ') {
	 int maxCommandLength = 100;
         char[maxCommandLength] command;
         s.toCharArray(command, maxCommandLength);
             
         JsonObject& root = jsonBuffer.parseObject(command);

	 x = root["X"];
         y = root["Y"];
         r = root["R"];
         z = root["Z"];
         
         printDebugInfo(x, y, z, r, s); 
	 
         jsonBuffer = clearJson;
         s = " ";
      }
      else {
         s += String(c);
      }

      char sensor = 'a';
      client.println(sensor);
   }
}

void printDebugInfo(int x, int y, int z, int r, String s) {    
   Serial.println(s);
   
   Serial.print("X:");
   Serial.println(x);
   Serial.print("Y:");
   Serial.println(y);
   Serial.print("Z:");
   Serial.println(z);
   Serial.print("R:");
   Serial.println(r);
}
