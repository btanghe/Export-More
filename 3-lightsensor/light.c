// light.c
//
// Example program for bcm2835 library
// Tsl2560 light to digital converter
//
// After installing bcm2835, you can build this 
// with something like:
// gcc -o light light.c -l bcm2835
// sudo ./light
//
// Or you can test it before installing with:
// gcc -o light -I ../../src ../../src/bcm2835.c light.c
// sudo ./light
//
// Author: Bart Tanghe
// Based on: Mike McCauley samples
// $Id: RF22.h,v 1.21 2012/05/30 01:51:25 mikem Exp $

#include <bcm2835.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	if (!bcm2835_init())
	   return 1;
	
	char temp[1];				//temporary values
	int ret;
	int ad[2];

	bcm2835_i2c_begin();
	bcm2835_i2c_setSlaveAddress(0x29);      // addr pin attached to ground
	bcm2835_i2c_set_baudrate(1000);         // Default

	temp[0] = 0xa0;				//select the control register
	bcm2835_i2c_write(temp,1);
	temp[0] = 0x03;				//Power up the device
	bcm2835_i2c_write(temp,1);
	bcm2835_delay(500);

	bcm2835_i2c_read(temp,1);
	printf("%x - if 33 the device is turned on\n",temp[0]);

	temp[0] = 0xac;				//Channel 0 lower byte
	bcm2835_i2c_write(temp,1);		
	bcm2835_i2c_read(temp,1);

	ad[1]= (int)temp[0];

	temp[0] = 0xad;				//channel 0 upper byte
	bcm2835_i2c_write(temp,1);
	bcm2835_i2c_read(temp,1); 

	ad[0] = (int)temp[0];
	printf("ad value:%d\n",ad[0]*256+ad[1]);

	bcm2835_i2c_end();
	bcm2835_close();
	
	return 0;
}
