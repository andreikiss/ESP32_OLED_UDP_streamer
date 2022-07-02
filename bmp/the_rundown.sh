#/bin/sh

echo "Sending UDP while doing mad things with sockets"

while :
do
	echo "infinite loops [ hit CTRL+C to stop]"
	import -monochrome -window root -resize 128x64 test.bmp
	echo "lcd-image-converter/release/linux/output/lcd-image-converter"
	./lcd-image-converter -m convert-image --doc-name=singleFrame --preset-name=Monochrome --input=./test.bmp --output=./lcd_converter_output.h
	gcc -Wall -o "sender" "sender.c"
	./sender
done

