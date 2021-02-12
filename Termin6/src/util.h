#ifndef UTIL_H
#define UTIL_H

/**
 * @brief Nimmt einen Wert und schneidet die angegebene Anzahl von Ziffern ab, während Sie korrekt
 * die letzte Stelle auf- oder abrundet.
 *
 * @param value Der dezimale Festkommawert, der gerundet werden soll.
 *
 * @param digitsAfterComma Die Anzahl der Ziffern, die abgeschnitten und
 * gerundet werden sollen.
 *
 * @Rückgabe Der Eingabewert mit der angegebenen Anzahl von abgeschnittenen und * gerundeten Dezimalstellen.
 *
 */
int roundFixedCommaInt(int value, int digitsAfterComma);

/**
 * @brief Berechnet die Anzahl der Münzen, die mit einem bestimmten Gewicht verbunden ist. Die Funktion
 * rundet korrekt eine Ziffer.
 */
int weightToCoinCount(int weightMg, int coinWeightMg);

/**
 * @brief Konvertiert eine gegebene vorzeichenbehaftete Ganzzahl in eine String-Darstellung.
 * Der Rückgabewert ist ein Zeiger auf einen globalen temporären Puffer, der nur
 * gültig ist, bis die Funktion intToString erneut aufgerufen wird. Mit der
 * postCommaDigits kann ein '.' eingefügt werden, um eine dezimale Festkommazahl darzustellen.
 *
 *
 * @param num Die vorzeichenbehaftete Ganzzahl, die konvertiert werden soll.
 * @param postCommaDigits Ein '.' wird an der angegebenen Position von
 * rechts eingeschoben.
 *
 * @return Ein Zeiger auf den resultierenden nullterminierten String. Der Zeiger wird
 * beim erneuten Aufruf von intToString überschrieben.
 *
 * @example intToString(12345, 2) => "123.45",
 * intToString(12345, 0) => "12345".
 */
char *intToString(int num, int postCommaDigits);

/**
 * @brief die maximale Anzahl von Zeichen, die zur Anzeige eines beliebigen 32-Bit
 * Interger, ohne Nullterminierung.
 *
 * @note
 * −2_147_483_648 => 11 chars.
 *  2_147_483_647 => 10 chars.
 */
#define INT_MAX_CHARCOUNT 11

/**
 * @brief Globaler Puffer zum temporären Speichern einer String-Repräsentation einer 32-Bit
 * Ganzzahl, einschließlich Nullterminierung und Hinzufügen eines zusätzlichen Zeichens für '.'
 * um dezimale Festkommazahlen darzustellen.
 */
extern char sNum[INT_MAX_CHARCOUNT + 1 + 1];

#endif // UTIL_H
