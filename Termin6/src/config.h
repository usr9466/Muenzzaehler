#ifndef CONFIG_H
#define CONFIG_H

/////////////////////////
// Münzzähler Config //
/////////////////////////

// Münzgewichte (CW) in Milligramm

/** @brief 1 ct weight in mg */
#define CW_1CT 2300
/** @brief 2 ct weight in mg */
#define CW_2CT 3060
/** @brief 5 ct weight in mg */
#define CW_5CT 3920
/** @brief 10 ct weight in mg */
#define CW_10CT 4100
/** @brief 20 ct weight in mg */
#define CW_20CT 5740
/** @brief 50 ct weight in mg */
#define CW_50CT 7800
/** @brief 1 € weight in mg */
#define CW_1EU 7500
/** @brief 2 € weight in mg */
#define CW_2EU 8500

/**
 * @brief Das Münzgewicht, das zur Berechnung der Münzanzahl verwendet wird
 */
// #define CURRENT_COIN_WEIGHT CW_20CT
#define CURRENT_COIN_WEIGHT CW_20CT

//////////////////////////////////
// Messparameter Config //
//////////////////////////////////

/**
 * @brief Anzahl der Messungen, die für ein Ergebnis durchgeführt werden müssen.
 * Der höchste und der niedrigste Werte werden entfernt und der Rest der Werte wird zu einem Durchschnitt
 */
#define NUM_MESSUNG 12

////////////////////////
// Serial Port Config //
////////////////////////

/**
 * @brief Ziel BAUD Rate
 */
//#define DEFAULT_BAUD 38400

// 2 CT
// #define DEFAULT_BAUD 57600

// 20 CT
#define DEFAULT_BAUD 115200

/**
 * @brief The master clock speed (cpu clock)
 */
#define M_CLOCK_SPEED 25000000

/**
 * @brief The clock divider that is calculated from masterclock and the target
 * baudrate.
 *
 * @warning This currently has to be calculated manually.
 *
 * @note Calculation: US_CD = M_CLOCK_SPEED / (16*DEFAULT_BAUD)
 */

// #define US_CD 41

// BAUD 57600 / 2 Ct
// #define US_CD 27 // 27.1

// BAUD 115200 / 20 Ct
#define US_CD 14 // 13.5

#endif // CONFIG_H
