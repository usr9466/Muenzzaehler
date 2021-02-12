#include "gpio.h"

void initPins()
{
	// Peripherietakt für PIOB freigeben
	// (PCER = Peripheral Clock Enable Register)
	pmcbase->PMC_PCER = (1 << 14);

	// Initialisieren der LED-Pins

	// PIO für alle LEDs freigeben (PER = PIO-Enable-Register)
	piobaseB->PIO_PER = ALL_LEDS;
	// Datenrichtung (Ausgang) für alle LEDs einstellen (OER = Output enable register)
	piobaseB->PIO_OER = ALL_LEDS;

	// Tastenpins initialisieren
	// PIO für die ersten drei Schalter freigeben
	piobaseB->PIO_PER = KEY1 | KEY2 | KEY3;
	// Datenrichtung (Eingang) für die ersten drei Schalter einstellen
	piobaseB->PIO_ODR = KEY1 | KEY2 | KEY3;
}

void setPin(uint16_t pin, bool state)
{
	if (state)
	{
		piobaseB->PIO_SODR = pin; // PIN on
	}
	else
	{
		piobaseB->PIO_CODR = pin; // PIN off
	}
}

bool getPin(uint16_t pin)
{
	return (piobaseB->PIO_PDSR & pin);
}

bool getSchalter(uint16_t pin)
{
	// Die Schalter sind low-aktiv geschaltet, so dass sie den invertierten Pin-Zustand erhalten
	return !getPin(pin);
}

void setLED(uint16_t pin, bool on)
{
	// Die LEDs sind low-aktiv geschaltet, also low setzen, um die Leds zu aktivieren
	setPin(pin, !on);
}
