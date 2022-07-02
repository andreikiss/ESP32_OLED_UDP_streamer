# ESP32_OLED_UDP_streamer
Stream images over UDP to ESP32 and display on OLED SSD1306 


This project is based on lcd-image-converter:
https://lcd-image-converter.riuson.com/en/docs/others/command-line/convert-image/

How it works:
 - the screen is captured with imagemagick - ```sudo apt-get install imagemagick``` 
 - the lcd-image-converter generates the Monochrome C file for data
 - this output file is compiled and sent over UDP(first the size HeightxWidth, then the data)
 - the ESP32 receives the data over UDP
 - ESP32 sends the data to OLED SSD1306 128x64 display
 
 It works, it's not optimized and with my learning programming know-how it just just existing pieces put together
 
 Utility - just for fun
 Use at your own risk :)
 
 How to use:
  - compile the lcd-image-converter - you will need qtcreator and some additional libraries
  - take the binary and put it where you also put the_rundown.sh
  - adapt
  ```#define serverIP "192.168.178.100"```   in sender.c with your ESP32 ip address
  - adapt the Arduino .ino file with your wlan information
  - chmod +x the_rundown.sh
  - ./the_rundown.sh  and hold on to your pants cuz this will write files and open sockets for every frame :D - don't worry they are also closed...if everything goes well :)
  
  
import -monochrome -window root -resize 128x64 test.bmp
here maybe check for the display you want to stream ? Imagemagick tutorial
//convert -threshold 80 test.bmp out_black.bmp
convert -alpha off -auto-level -threshold 50% -background Black test.bmp out_black.bmp 

https://medium.com/sysf/bits-to-bitmaps-a-simple-walkthrough-of-bmp-image-format-765dc6857393
https://www.metadata2go.com
https://diyusthad.com/image2cpp
https://beej.us/guide/bgc/html/index-wide.html#arrays-and-pointers
https://beej.us/guide/bgnet/html/index-wide.html#sendtorecv

Hexedit Hex Editor
xxd

https://lcd-image-converter.riuson.com/en/docs/others/command-line/convert-image/
./lcd-image-converter -m convert-image --doc-name=uga --preset-name=Monochrome --input=./real_128.bmp --output=./box.c


sudo apt-get install git
sudo apt-get install qtcreator
sudo apt-get install libqt5xmlpatterns5-dev
sudo apt-get install  qtdeclarative5-dev
sudo apt-get install libqt5svg5-dev


https://github.com/espressif/arduino-esp32/blob/master/libraries/AsyncUDP/src/AsyncUDP.cpp
