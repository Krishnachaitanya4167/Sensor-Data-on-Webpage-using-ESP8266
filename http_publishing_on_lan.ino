#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DHT.h>//dht 11 library for wifi module
#define DHTTYPE DHT11
#define DHTPIN  2
const char *ssid = "your network name";
const char *password = "your password";
ESP8266WebServer server(80);//server and port
 DHT dht(DHTPIN, DHTTYPE, 11);//defining  dht11 sensor type and pinn for library
 float humidity, temp_f;  
String te="";     
 String hu="";
 
 
 void handle_root() {
  dht.begin();        //initialize the sensor
  humidity = dht.readHumidity();          //reading humidity from sensor
  temp_f = dht.readTemperature(false);   //reading temp from sensor---when false value will be in form of centigrade or else it is farenheit
     te="Temperature is: "+String((int)temp_f)+"c";
    hu="Humidity: "+String((int)humidity)+"%";
   server.send(200, "text/plain", te+" and "+hu);//sending data to webpage
   }

void setup(void)
{
  Serial.begin(115200);  //setting baudrate for serial communication
  WiFi.begin(ssid, password);//connect to wifi
  Serial.print("\n\r \n\rWorking to connect");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("DHT Weather Reading Server");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");//ipadress of wifi
  Serial.println(WiFi.localIP());
    server.on("/", handle_root);//handling the server(on)
    server.begin();
  Serial.println("HTTP server started");
}
 void loop(void)
{  server.handleClient();
}

