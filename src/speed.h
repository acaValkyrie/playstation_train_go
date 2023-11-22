#ifndef SPEED_H
#define SPEED_H

#include "masscon.h"

#define pwmOutPin 3

void speedSetup();
float calcDeltaSpeed();
void updateSpeed();
float getSpeed();
void printSpeed();

#endif