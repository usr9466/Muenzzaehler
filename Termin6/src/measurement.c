#include "measurement.h"
#include "config.h"
#include "hardware.h"

const unsigned int TC_INIT = 
      TC_CLKS_MCK2              // Timer clock prescaler: Masterclock/2
    | TC_LDBSTOP                // Stop timer when RB loading occurs
    | TC_CAPT                   // Use capture mode
    | TC_LDRA_RISING_EDGE       // Trigger RA on rising edge
    | TC_LDRB_RISING_EDGE;      // Trigger RB on rising edge

void initTimer()
{

    // Disable PIO for Timer pins
    piobaseA->PIO_PDR = 
          (1<<PIOTIOA4)     // Disable TIOA4
        | (1<<PIOTIOA5);    // Disable TIOA5

	// Enable Timer & pio clocks
	pmcbase->PMC_PCER = 
		  (1<<10)   // Enable Timer4 clock
		| (1<<11)   // Enable Timer5 clock
		| (1<<13)   // Enable PIOA clock
		| (1<<14);  // Enable PIOB clock


    tcbase4->TC_CCR = TC_CLKDIS; // Disable timer clock
    tcbase4->TC_CMR = TC_INIT; // Initialize timer config
    tcbase4->TC_CCR = TC_CLKEN; // Enable timer clock

    tcbase5->TC_CCR = TC_CLKDIS; // Disable timer clock
    tcbase5->TC_CMR = TC_INIT; // Initialize timer config
    tcbase5->TC_CCR = TC_CLKEN; // Enable timer clock
}

int messeMilligrammEinmalig()
{
    volatile int capturediff4, capturediff5;
    volatile int stat;

	// Statusregister lesen, um die zuvor beendete Messung zu löschen
    tcbase4->TC_SR;
    tcbase5->TC_SR;
    
	// Starten Sie beide Timer zusammen so nah wie möglich, um Offsets zwischen
	// den Starts der Messungen zu vermeiden
    tcbase4->TC_CCR = TC_SWTRG; // Timer zurücksetzen und neu starten
    tcbase5->TC_CCR = TC_SWTRG; // Timer zurücksetzen und neu starten


	// Warten, bis Timer 4 die Messung beendet hat
    // Capture-Register B wurde geladen => Messung beendet
    while (!( (stat = tcbase4->TC_SR) & TC_LDRBS));

	// Überlauf während der Messung => Messung ist ungültig
    if (stat & TC_COVFS) return -1;

	// Warten, bis Timer 5 die Messung beendet hat
    // Capture-Register B wurde geladen => Messung beendet
    while (!( (stat = tcbase5->TC_SR) & TC_LDRBS));

	// Überlauf während der Messung => Messung ist ungültig
    if (stat & TC_COVFS) return -1;


    // Differenz = MesszeitEnde - MesszeitAnfang
    capturediff4 = tcbase4->TC_RB - tcbase4->TC_RA;

    // Differenz = MesszeitEnde - MesszeitAnfang
    capturediff5 = tcbase5->TC_RB - tcbase5->TC_RA;


    //20 CT
    const uint32_t c1 = 16240;
    const uint32_t c2 = 35;

    // Berechnen Sie die Masse in Milligramm nach der Waagenformel
	int64_t mass64b = ( 
		( 
			(c1*(int64_t)capturediff4*1000u) / capturediff5 
		) - (c1*1000u)
	) - (c2*1000u);

    // Wenn die Masse negativ ist, liegt das wahrscheinlich daran, dass die Skala nahe an 
    // Null ist
    if (mass64b < 0) mass64b = 0;

    // Konvertieren auf 32 Bit
    int mass = (int)mass64b;

    return mass;
}

int messeMilligramm()
{
    // Anzahl der gültigen Messungen
    int validMeasurementsCount = 0;
    // Array zur Aufnahme der Messungen
    int measurements[NUM_MESSUNG];

    int i;
    // Ausführen der eingestellten Anzahl von Messungen
    for (i = 0; i < NUM_MESSUNG; i++)
    {
        int result = messeMilligrammEinmalig();

        // Nur wenn das Ergebnis gültig ist, verwenden Sie es in der Messliste
        if (result >= 0)
        {
            measurements[validMeasurementsCount++] = result;
        }
    }

    // Nur die Hälfte der Messungen hat funktioniert -> Ergebnis ist Bullshit
    if (validMeasurementsCount < NUM_MESSUNG/2) return -1;

    // Index des kleinsten Wertes
    int minIndex = 0;
    // Index des größten Wertes
    int maxIndex = 0;

    // Finden Sie die Min- und Max-Indizes
    for (i = 0; i < validMeasurementsCount; i++)
    {
        if (measurements[i] < measurements[minIndex]) minIndex = i;
        if (measurements[i] >= measurements[maxIndex]) maxIndex = i;
    }

    int sum = 0;
    // Summieren Sie alle gültigen Messungen mit Ausnahme von min und max
    for (i = 0; i < validMeasurementsCount; i++)
    {
        if (i == minIndex || i == maxIndex) continue;

        sum += measurements[i];
    }

    // Berechnen Sie den Durchschnitt
    int average = sum / (validMeasurementsCount-2);

    return average;
}