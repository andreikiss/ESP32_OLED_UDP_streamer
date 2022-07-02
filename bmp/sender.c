/*
 * sender.c
 * 
 * Copyright 2022 Andrei Kiss <akiss@BG-NB-0111>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
 typedef struct {
     const uint8_t *data;
     uint16_t width;
     uint16_t height;
     uint8_t dataSize;
     } tImage;
#include "lcd_converter_output.h"


#define SERVERPORT "4950"	// the port users will be connecting to
//#define serverIP "exp"    //or hostname
#define serverIP "192.168.178.100"

int main(int argc, char **argv)
{
	uint8_t sizeUDP[3];
	printf("importing the generated header file of lcd-image-converter\n");
	printf("width: %d\n", singleFrame.width);
	printf("height: %d\n", singleFrame.height);
	sizeUDP[0]=0x87; //recognize this
	sizeUDP[1]=singleFrame.width;
	sizeUDP[2]=singleFrame.height;  
	int how_many_elements = sizeof image_data_singleFrame / sizeof *image_data_singleFrame;

	printf("size: %d\n", how_many_elements);
	for (int i=0; i<how_many_elements; i++)
	{
		printf("0x%02X ", image_data_singleFrame[i]);
		}
		
	
	//send udp
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET; // set to AF_INET to use IPv4
	hints.ai_socktype = SOCK_DGRAM;

	if ((rv = getaddrinfo(serverIP, SERVERPORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// loop through all the results and make a socket
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("talker: socket");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "talker: failed to create socket\n");
		return 2;
	}

	if ((numbytes = sendto(sockfd, &sizeUDP, 3, 0,
			 p->ai_addr, p->ai_addrlen)) == -1) {
		perror("talker: sendto");
		exit(1);
	}
	if ((numbytes = sendto(sockfd, &image_data_singleFrame, how_many_elements, 0,
			 p->ai_addr, p->ai_addrlen)) == -1) {
		perror("talker: sendto");
		exit(1);
	}

	freeaddrinfo(servinfo);

	printf("talker: sent %d bytes to %s\n", numbytes, serverIP);
	close(sockfd);
	
		
		
		
	
	printf("program end2");
	return 0;
}

