// blink.c
//
// Example program for bcm2835 library
// Blinks the status of 1 of the 8 leds every 0.5 secs
//
// After installing bcm2835, you can build this 
// with something like:
// gcc -o blink blink.c -l bcm2835
// sudo ./blink
//
// Or you can test it before installing with:
// gcc -o blink -I ../../src ../../src/bcm2835.c blink.c
// sudo ./blink
//
// Author: Bart Tanghe
// Based on: Mike McCauley samples
// $Id: RF22.h,v 1.21 2012/05/30 01:51:25 mikem Exp $

#include <bcm2835.h>

//define the 8 leds

#define PIN0 RPI_V2_GPIO_P1_07      //4
#define PIN1 RPI_V2_GPIO_P1_08      //14
#define PIN2 RPI_V2_GPIO_P1_18      //24
#define PIN3 RPI_V2_GPIO_P1_16      //23
#define PIN4 RPI_V2_GPIO_P1_15      //22
#define PIN5 RPI_V2_GPIO_P1_13      //27
#define PIN6 RPI_V2_GPIO_P1_12      //18
#define PIN7 RPI_V2_GPIO_P1_11      //17

int main(int argc, char **argv)
{
	int i;

	if (!bcm2835_init())
		return 1;

	// Set the pins to be an output
	bcm2835_gpio_fsel(PIN0, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(PIN1, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(PIN2, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(PIN3, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(PIN4, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(PIN5, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(PIN6, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(PIN7, BCM2835_GPIO_FSEL_OUTP);

	while(1)
	{
		bcm2835_gpio_set(PIN0);
		bcm2835_delay(500);
		bcm2835_gpio_clr(PIN0);
		bcm2835_delay(500);

		bcm2835_gpio_set(PIN1);
		bcm2835_delay(500);
		bcm2835_gpio_clr(PIN1);
		bcm2835_delay(500);
		bcm2835_gpio_set(PIN2);
		bcm2835_delay(500);
		bcm2835_gpio_clr(PIN2);
		bcm2835_delay(500);

		bcm2835_gpio_set(PIN3);
		bcm2835_delay(500);
		bcm2835_gpio_clr(PIN3);
		bcm2835_delay(500);

		bcm2835_gpio_set(PIN4);
		bcm2835_delay(500);
		bcm2835_gpio_clr(PIN4);
		bcm2835_delay(500);

		bcm2835_gpio_set(PIN5);
		bcm2835_delay(500);
		bcm2835_gpio_clr(PIN5);
		bcm2835_delay(500);

		bcm2835_gpio_set(PIN6);
		bcm2835_delay(500);
		bcm2835_gpio_clr(PIN6);
		bcm2835_delay(500);

		bcm2835_gpio_set(PIN7);
		bcm2835_delay(500);
		bcm2835_gpio_clr(PIN7);
		bcm2835_delay(500);
	}

	bcm2835_close();
	return 0;
}
