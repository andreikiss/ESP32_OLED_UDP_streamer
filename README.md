# ESP32_OLED_UDP_streamer
Stream images over UDP to ESP32 and display on OLED SSD1306 

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

Image.c si box.c sunt identice acum


import -monochrome -window root -resize 128x64 test.bmp
./lcd-image-converter -m convert-image --doc-name=uga --preset-name=Monochrome --input=./my_screen_capture.bmp --output=./my_header.h
gcc -Wall -o "sender" "sender.c" (in directory: /home/akiss/ssd1306/bmp)

sudo apt-get install git
sudo apt-get install qtcreator
sudo apt-get install libqt5xmlpatterns5-dev
sudo apt-get install  qtdeclarative5-dev
sudo apt-get install libqt5svg5-dev


https://github.com/espressif/arduino-esp32/blob/master/libraries/AsyncUDP/src/AsyncUDP.cpp
