#include <QuadMotorShields.h>
#include <ArduinoJson.h>

#include <SPI.h>
#include <Ethernet.h>


QuadMotorShields md;
StaticJsonBuffer<200> jsonBuffer;
StaticJsonBuffer<200> clearJson;
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network.
// gateway and subnet are optional:

byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0x40, 0x9F};

//byte ip[] = {169, 254, 114, 49};
//byte server[] = {169, 254, 114, 221};
//Go to network settings->properties->IpV4-> obtain automatically IP 
// to reset this, otherwise use the address below
byte ip[] = {211, 255, 132, 49};
byte server[] = {211, 255, 132, 121};
int port = 1900;
String s = " ";
String sLast = " ";
EthernetClient client;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
  }

  Ethernet.begin(mac, ip);
  //Ethernet.begin(mac);
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, port)) {
    Serial.println("connected.");
    //print text to the server
    client.println("This is a request from the client.");
  } 
  else {
    if (client.connect(server, port)) {
      Serial.println("connected.");
      //print text to the server
      client.println("This is a request from the client.");
  }
    else { 
      Serial.println("connection failed");
  }
 }
}
int x,y,r,z = 0;
void loop()
{
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    if(c == ' ')
    {
        const int maxCharCount = 100;
        sLast = s;
        s = " ";
        char json[maxCharCount];
        for(int i=0; i<maxCharCount; i++)
        {
          json[i] = sLast[i];
        }
        JsonObject& root = jsonBuffer.parseObject(json);
        x = root["X"];
        y = root["Y"];
        r = root["R"];
        z = root["Z"];
        
        Serial.println(sLast);
        Serial.print("X:");
        Serial.println(x);
        Serial.print("Y:");
        Serial.println(y);
        Serial.print("Z:");
        Serial.println(z);
        Serial.print("R:");
        Serial.println(r);
        jsonBuffer = clearJson;
    }
    else
    {
      s += String(c);
    }
    //if(sLast)
    //jsonString = Json decode sLast
    //Set motorx to jsonString.x
    char sensor = 'a';
    client.println(sensor);
  }
  
}

