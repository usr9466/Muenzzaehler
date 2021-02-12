#include <stdbool.h>
#include "serial.h"
#include "config.h"

void initSerial()
{
	// Takt für US0 freigeben
	pmcbase->PMC_PCER = PMC_US0;

	// PIO für Pins für US0 TxD (Senden) und RxD (Empfangen) deaktivieren (P15, P16)
	// Dadurch können die Pins vom US0 verwendet werden
	piobaseA->PIO_PDR = (1 << 15) | (1 << 16);

	// Deaktivieren Sie TxD und RxD zur Konfiguration der seriellen Schnittstelle
	usartbase0->US_CR = US_TXDIS | US_RXDIS;

	// Baudrate durch Setzen des Frequenzteilers einstellen
	// Baudratengenerator-Register (CD = Clock Divider)
	usartbase0->US_BRGR = US_CD;

	// UART (Universal asynchronous receiver transmitter) einstellen
	// Params: keine Parität, 8b Daten, 1 Stop (8N1)
	// und Masterclock als Baseclock für USART

	//usartbase0->US_MR = US_CHRL_8 | US_NBSTOP_1 | US_PAR_NO | US_CLKS_MCK;
	usartbase0->US_MR = US_CHRL_7 | US_NBSTOP_1 | US_PAR_NO | US_CLKS_MCK;

	// TxD und RxD wieder freigeben
	usartbase0->US_CR = US_TXEN | US_RXEN;
}

void ausgabeZeichen(char c)
{
	// Schleife, solange TX nicht bereit ist (nicht sendetauglich)
	while (!(usartbase0->US_CSR & US_TXRDY))
		;

	// Schreiben der Zeichen in den Ausgang (damit wird das Zeichen gesendet)
	usartbase0->US_THR = c;
}

char getZeichen()
{
	char c;

	// Schleife solange RX nicht bereit ist (noch keine Daten empfangen)
	while (!(usartbase0->US_CSR & US_RXRDY))
		;

	// Lesen Sie das empfangene Zeichen
	c = usartbase0->US_RHR;

	return c;
}

void ausgabeString(char *str)
{
	int i = 0;

	// Do solange das Ende des Strings (Nullterminierung) nicht erreicht ist
	while (str[i] != 0)
	{
		// Serielle Terminals wollen \r\n für neue Zeile, also fügen Sie \r vor \n ein
		if (str[i] == '\n')
			ausgabeZeichen('\r');

		// Ausgeben des aktuellen Zeichens
		ausgabeZeichen(str[i]);

		// Gehe zum nächsten Zeichen
		i++;
	}
}
