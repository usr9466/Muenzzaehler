#ifndef _GPIO_H
#define _GPIO_H

#include <stdint.h>
#include <stdbool.h>
#include "hardware.h"

/**
 * @brief Initialize the pins used in the program.
 */
void initPins();

/**
 * @brief Setzt den angegebenen Pin auf den angegebenen Zustand.
 *
 * @param pins Die Bitmaske für die Pins. Zum Beispiel (LED1 | LED2) zum Setzen des
 * Zustands sind für die Pins LED1 und LED2 gleichzeitig zu setzen.
 *
 * @param state Wenn true, wird der Pin auf high gesetzt. Andernfalls wird der Pin auf
 * low gesetzt.
 */
void setPin(uint16_t pins, bool state);

/**
 * @brief Holt den Zustand des angegebenen Pins.
 *
 * @param pin Die Pin-Bitmaske für nur 1 Pin, der getestet werden soll.
 *
 * @return True, wenn der Zustand des Pins High ist, sonst false.
 */
bool getPin(uint16_t pin);

/**
 * @brief Holt den Zustand des angegebenen Schalterpins. Dies unterscheidet sich von getPin
 * weil der Rückgabewert invertiert ist, da die Schalter low aktiv sind.
 *
 * @param pin Die Pin-Bitmaske für nur 1 Pin (Schalter), der getestet werden soll.
 *
 * @return True, wenn der Schalter gedrückt ist, sonst false.
 */
bool getSchalter(uint16_t pin);

/**
 * @brief Setzt die angegebenen LEDs am Pin auf den angegebenen Zustand.
		Die LEDs sind low aktiv, daher wird der
 * Zustand einfach invertiert.
 *
 * @param pins Die Bitmaske für die Pins. Zum Beispiel (LED1 | LED2) zum Setzen des
 * Zustand für die Pins LED1 und LED2 gleichzeitig zu setzen.
 *
 * @param state Wenn true, wird die LED eingeschaltet, sonst wird die LED
 * aus.
 */
void setLED(uint16_t pin, bool on);

#endif // _GPIO_H
