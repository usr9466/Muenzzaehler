#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Initialisieren Sie die beiden Timer/Zähler, die zur Durchführung der Gewichts
 * Messungen mit der Waage durchzuführen.
 */
void initTimer();

/**
 * @brief Berechnet die Masse in Milligramm und gibt sie als int
 *
 * @return Die Masse ()
 */
int messeMilligrammEinmalig();

/**
 * @brief Führen Sie eine bestimmte Anzahl von Messungen durch und geben Sie den Durchschnittswert als
 * Milligramm.
 *
 * @return Das durchschnittliche Massenergebnis in Milligramm.
 */
int messeMilligramm();

#endif // MEASUREMENT_H
