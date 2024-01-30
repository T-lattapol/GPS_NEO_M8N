#include <TinyGPS++.h>
#include <HardwareSerial.h>
// #include <WiFi.h>
// #include <HTTPClient.h>

#define RXPin (22)
#define TXPin (21)

static const uint32_t GPSBaud = 9600;

// //enter WIFI
// const char* ssid = "iPhone ของ Lattapol";
// const char* password = "bestbest";

// The TinyGPS++ object
TinyGPSPlus gps;

// WiFiServer server(80);
// The serial connection to the GPS device
HardwareSerial ss(2);


void setup()
{
Serial.begin(115200);
ss.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin, false);
Serial.println(TinyGPSPlus::libraryVersion());

// Serial.print("Connecting to ");
    // Serial.println(ssid);

    // // WiFi.begin(ssid, password);
    // while (WiFi.status() != WL_CONNECTED) {
    //     delay(500);
    //     Serial.print(".");
    // // }
    // Serial.println("");
    // Serial.println("WiFi connected");
    // Serial.println("IP address: ");    // this is the address to use for viewing the map
    // Serial.println(WiFi.localIP());
    // server.begin();

}

void loop()
{

while (ss.available() > 0)

if (gps.encode(ss.read()))
displayInfo();

if (millis() > 5000 && gps.charsProcessed() < 10)
{
Serial.println(F("No GPS detected: check wiring."));
while(true);
}
delay(500);
}

void displayInfo()
{
Serial.print(F("Location: "));
if (gps.location.isValid())
{
Serial.print(gps.location.lat(), 8);
Serial.print(F(","));
Serial.println(gps.location.lng(), 8);

Serial.print("Speed in km/h = ");
Serial.println(gps.speed.kmph());

Serial.print("Course in degrees = ");
Serial.println(gps.course.deg());
Serial.println("--------------------------");
}
else
{
Serial.print(F("INVALID"));
}

Serial.println();
}