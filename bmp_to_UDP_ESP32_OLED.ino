#include "WiFi.h"
#include "AsyncUDP.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     5 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


const char* ssid     = "wlan";
const char* password = "passwd";
uint8_t heightUDP=0, widthUDP=0;  

AsyncUDP udp;

void setup()
{
    Serial.begin(115200);
    
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
      Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
    }
    display.display();
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Failed");
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 10);
        display.println(F("wifi failed"));
        display.display();
        while(1) {
            delay(1000);
        }
    }
    else{
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 10);
        display.println(ssid);
        display.println(WiFi.localIP());
        display.display();
      }
     
    if(udp.listen(4950)) {
        Serial.print("UDP Listening on IP: ");
        Serial.println(WiFi.localIP());
        udp.onPacket([](AsyncUDPPacket packet) {
            Serial.print("UDP Packet Type: ");
            Serial.print(packet.isBroadcast()?"Broadcast":packet.isMulticast()?"Multicast":"Unicast");
            Serial.print(", From: ");
            Serial.print(packet.remoteIP());
            Serial.print(":");
            Serial.print(packet.remotePort());
            Serial.print(", To: ");
            Serial.print(packet.localIP());
            Serial.print(":");
            Serial.print(packet.localPort());
            Serial.print(", Length: ");
            Serial.print(packet.length());
            Serial.print(", Data: ");
            Serial.write(packet.data(), packet.length());
            Serial.println();
            Serial.print("-->Data in hex first 3 uint8_t: ");
            Serial.print(packet.data()[0],HEX);
            Serial.print(packet.data()[1],HEX);
            Serial.print(packet.data()[2],HEX);
            Serial.println();
            if(packet.data()[0] == 0x87){
              Serial.print("Received size of image packet ");
              heightUDP=packet.data()[1];
              widthUDP=packet.data()[2];
              Serial.print(heightUDP);
              Serial.print("x");
              Serial.print(widthUDP);
              }
              else{
                display.clearDisplay();
                display.drawBitmap(0, 0, packet.data(), heightUDP, widthUDP, 1);
                display.display();
                }
            
            Serial.println();
            
            //reply to the client
            packet.printf("Got %u bytes of data", packet.length());
        });
    }
}

void loop()
{
    delay(1000);
    //Send broadcast
    udp.broadcast("Anyone here?");
}
