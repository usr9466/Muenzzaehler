#include <stdbool.h>
#include "util.h"

int roundFixedCommaInt(int value, int digitsAfterComma)
{
    // Cap at 0
    if (digitsAfterComma < 0)
        digitsAfterComma = 0;
    if (digitsAfterComma == 0)
        return value;

    while (digitsAfterComma-- > 1)
    {
        value /= 10;
    }

    // Holt die aktuelle letzte Ziffer
    int lastDigit = value % 10;

    // Abschneiden der aktuellen letzten Stelle
    value = value / 10;

    // Wenn die letzte Ziffer >= 5 war, muss der Wert aufgerundet werden
    if (lastDigit >= 5 || lastDigit <= -5)
    {
        if (value < 0)
            value--;
        else
            value++;
    }

    return value;
}

int weightToCoinCount(int weightMg, int coinWeightMg)
{
    // Wenn das Gewicht negativ ist, wie 0-Münzen behandeln, um ungültige Münze zu verhindern
    // Anzeigen
    if (weightMg < 0)
        return 0;

    // Ermittelt die Münzanzahl*10 (mit einer Stelle mehr Genauigkeit)
    int count = (weightMg * 10) / coinWeightMg;

    // Runden auf die zusätzliche Ziffer
    count = roundFixedCommaInt(count, 1);

    return count;
}

// Initialisieren von dem Puffer mit Nullen
char sNum[INT_MAX_CHARCOUNT + 1 + 1] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

char *intToString(int num, int postCommaDigits)
{
    // Erinnerungs bool, wenn die Zahl negativ ist
    bool neg = num < 0;

    // Schreibens des String von hinten
    int index = (INT_MAX_CHARCOUNT + 1) - 1;

    do
    {
        // Schreiben der letzten Ziffer in den Puffer und ignorieren von negativen
        // Index verringern (im String-Puffer vorwärts gehen)
        sNum[index--] = '0' + (num % 10) * (neg ? -1 : 1);

        // Einfügen eines . an der richtigen Position gemäß postCommaDigits
        if (((INT_MAX_CHARCOUNT + 1) - 1 - index) == postCommaDigits)
        {
            sNum[index--] = '.';
        }

    } // Schleife, solange die Zahl nicht 0 ist, und dividieren durch 10 (Abschneiden der letzten
      // Ziffer abschneiden)
    while (num /= 10);

    // Fügen Sie das Minus vorne an, wenn die Zahl negativ war
    if (neg)
        sNum[index--] = '-';

    // Rückgabe eines Zeigers auf den Anfang der Zahl
    return sNum + index + 1;
}
