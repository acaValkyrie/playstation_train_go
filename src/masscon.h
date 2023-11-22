#ifndef MASSCON_H
#define MASSCON_H

#include <Psx.h>
#include <Wire.h>

#define dataPin 8       //データピン番号
#define cmndPin 9       //コマンドピン番号
#define attPin 11       //アテンションピン番号
#define clockPin 10     //クロックピン番号

void massconSetup();
void updateBrakeAccell();
int getP();
int getB();
void printMassconPropaties();

#endif