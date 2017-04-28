#include "tones.h"

/* Diode pins  */
#define VD1 A0
#define VD2 A1
#define VD3 A2
#define VD4 A3

/* Function for playing melody  */
void play_melody (int);

/* Start diodes lighting  */
void diodes_on();

/* Stop diodes lighting  */
void diodes_off();

/* Play test melody with blinking diodes  */
void play_melody (int);
