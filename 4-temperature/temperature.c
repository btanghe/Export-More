// temperature.c
// Analog ADT7310 - chip select 1
//
// After installing bcm2835, you can build this 
// with something like:
// gcc -o temperature temperature.c -l bcm2835
// sudo ./temperature
//
// Or you can test it before installing with:
// gcc -o temperature -I ../../src ../../src/bcm2835.c temperature.c
// sudo ./temperature
//
// Author: Bart Tanghe
// Based on: Mike McCauley samples
// $Id: RF22.h,v 1.21 2012/05/30 01:51:25 mikem Exp $

/*******************
                        length  command extra   0-rw-register-cr-00
Read the status(0)      2       0x40    ro      0100 0000
read the configur(1)    2       0x48    r       0100 1000
write the confi         2       0x08    w       0000 1000
read the temp(2)        3       0x50    ro      0101 0000
read the id(3)          2       0x58    ro      0101 1000
read the Tcrit(4)       3       0x60    r       0110 0000
write the Tcrit         3       0x20    w       0010 0000
read the Thyst(5)       3       0x68    r       0110 1000                       
write the Thyst         3       0x28    w       0010 1000
read the Thigh(6)       3       0x70    r       0111 0000
write the Thigh         3       0x30    w       0011 0000
read the Tlow(7)        3       0x78    r       0111 1000
write the Tlow          3       0x38    w       0011 1000
********************/


#include <bcm2835.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	if (!bcm2835_init())
	return 1;
	char buffer[4];
	buffer[0] = 50;			
	int i,temp;

	bcm2835_spi_begin();
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE3);				//SCLK rising edge - clock idle state 1
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); 	//set clock frequency
	bcm2835_spi_chipSelect(BCM2835_SPI_CS1);                      	//use chip select 1
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, LOW);      	//chip select 0 to activate


	buffer[0]=buffer[1]=buffer[2]=buffer[3]=0;
	//bcm2835_spi_transfern(buffer,4);

	buffer[0] = 0x58;						//read the id
	bcm2835_spi_transfern(buffer,2);
	printf("id:%02X\n",buffer[1]);
	
	while(1)
	{
		buffer[0] = 0x50;					//read the temp
		bcm2835_spi_transfern(buffer,3);
		printf("status %02X %02X\n",buffer[1],buffer[2]);
		temp = buffer[1]; 
		temp = temp<<8;
                temp = temp + ( buffer[2] & 0xF8);
		printf("status %08x\n",temp);
		temp = temp>>3;
		temp = temp/16;
		printf("temp:%d\n",temp);
		sleep(1);
	}

	bcm2835_spi_end();
	bcm2835_close();
	return 0;
}

