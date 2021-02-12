#ifndef SERIAL_H
#define SERIAL_H

#include "hardware.h"

/**
 * @brief Initialize the serial port.
 */
void initSerial();

/**
 * @brief Gibt ein einzelnes Zeichen an die serielle Schnittstelle.
 * Diese Funktion blockiert, bis das Zeichen abgesendet wurde.
 *
 * @param c ist das zu sendende Zeichen.
 */
void ausgabeZeichen(char c);

/**
 * @brief Lesen eines Zeichens von der seriellen Schnittstelle.
 * Diese Funktion blockiert (auf unbestimmte Zeit), bis ein Zeichen empfangen wird.
 *
 * @Rückgabe Das von der seriellen Schnittstelle empfangene Zeichen.
 */
char getZeichen();

/**
 * @brief Gibt eine gegebene nullterminierte Zeichenkette an die serielle Schnittstelle.
 * Diese Funktion blockiert, bis die Zeichenkette vollständig ausgeschrieben ist.
 *
 * @param str char-Zeiger auf die nullterminierte Zeichenkette, die gesendet werden soll.
 */
void ausgabeString(char *str);

#endif // SERIAL_H
