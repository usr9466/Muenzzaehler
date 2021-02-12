#ifndef _HARDWARE_H
#define _HARDWARE_H

#include "../h/aic.h"
#include "../h/pmc.h"
#include "../h/pio.h"
#include "../h/tc.h"
#include "../h/usart.h"

extern StructPMC* pmcbase;

extern StructPIO* piobaseA;
extern StructPIO* piobaseB;

extern StructTC* tcbase4;
extern StructTC* tcbase5;

extern StructUSART* usartbase0;

#endif // _HARDWARE_H