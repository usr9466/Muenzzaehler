#include <stdint.h>

#include "measurement.h"
#include "gpio.h"
#include "serial.h"
#include "config.h"
#include "util.h"

void willkommen(void)
{
	ausgabeString("----------------------------------\n");
	ausgabeString("- Herzlich Willkommen Münzuwaage -\n");
	ausgabeString("-   Bitte Behaelter aufstellen   -\n");
	ausgabeString("-       SW 1 zum Taren/Nullen    -\n");
	ausgabeString("----------------------------------\n");
	ausgabeZeichen('\n');
}

int main(void)
{
	int absolutesGewicht; // Absolutes Gewicht auf der Waage in mg
	int leerGewicht;			// Leergewicht in mg
	int deltaGewicht;			// Absolutes Gewicht - Leergewicht auf der Waage in mg
	int münzAnzahl;				// Absolute Münzanzahl

	// Initialisierung der Peripherie
	initPins();
	initTimer();
	initSerial();

loop:

	willkommen();

	// Warten, bis Schalter 1 gedrückt wird
	while (!getSchalter(KEY1))
		;

	// Berechnung des Absoluten Gewichts
	absolutesGewicht = messeMilligramm();

	// Wenn das Gewicht kleiner 0 ist, wird eine Fehlermeldung ausgegeben
	if (absolutesGewicht < 0)
	{
		ausgabeString("Fehler bei der Gewicht berechnung...\n");
		goto loop;
	}

	// Berechne leerGewicht
	leerGewicht = absolutesGewicht;

	deltaGewicht = absolutesGewicht - leerGewicht; // == 0

	// Ausgabe Leergewicht
	ausgabeString("Leergewicht: ");
	ausgabeString(intToString(leerGewicht, 3));
	ausgabeString(" g\n");

	ausgabeString("SW2 betätigen um zu wiegen\n");

	// Warten, bis Schalter 2 gedrückt wird
	while (!getSchalter(KEY2))
		;

	ausgabeString("SW3 betätigen zum stoppen || ausgeben || resetten\n");

	// Zähler zur Erzeugung einer Verzögerung für den Refresh der Ausgabe
	unsigned int counter = 0;

	while (!getSchalter(KEY3))
	{
		// Sofortige Schleife, wenn und nur nach jeweils X Schleifen die Ausgabe aktualisieren
		if (counter++ % 150000 != 0)
			continue;

		//Berechne absolutesGewicht
		absolutesGewicht = messeMilligramm();

		// Wenn das Gewicht < 0 ist, ist die Messung fehlgeschlagen
		if (absolutesGewicht < 0)
		{
			ausgabeString("Wagenfehler...\n");
			goto loop;
		}

		// Delta berechnen
		deltaGewicht = absolutesGewicht - leerGewicht;

		ausgabeString("Gewicht der Muenzen: ");
		ausgabeString(intToString(deltaGewicht, 3));
		ausgabeString(" g\n");

		münzAnzahl = weightTomünzAnzahl(deltaGewicht, CURRENT_COIN_WEIGHT);

		münzAnzahl &= 0xff;

		int i;
		for (i = 0; i < 8; i++)
		{
			// Aktuelles Bit true/false
			bool bit = (münzAnzahl >> (7 - i)) & 1;

			// Aktuelle LED (Offset von LED1 um i) auf Bit gesetzt
			setLED(LED1 << i, bit);
		}
	}

	ausgabeString("Leergewicht: ");
	ausgabeString(intToString(leerGewicht, 3));
	ausgabeString(" g\n");

	ausgabeString("Gewicht der Muenzen: ");
	ausgabeString(intToString(deltaGewicht, 3));
	ausgabeString(" g\n");

	ausgabeString("Gewicht Gesamt: ");
	ausgabeString(intToString(absolutesGewicht, 3));
	ausgabeString(" g\n");

	ausgabeString("Anzahl der Muenzen: ");
	ausgabeString(intToString(münzAnzahl, 0));
	ausgabeString("\n");

	goto loop;

	return 0;
}
