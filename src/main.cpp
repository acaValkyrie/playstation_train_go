#include <Arduino.h>
#include "masscon.h"
#include "speed.h"

void setup(){
  massconSetup();
  speedSetup();
}

void loop(){
  // マスコンの現在のレバーの位置を取得する。
  updateBrakeAccell();

  // マスコンの現在のレバーの位置に応じて、モーターの回転速度の変化量を決定する。
  updateSpeed();
  // モーターの回転速度の変化量に応じて、モーターの回転速度を変化させる。
  int speed = (int)getSpeed();

  // モーターの回転速度を変化させる。
  analogWrite(pwmOutPin, (int)speed);

  // デバッグ用のプリント
  printMassconPropaties();
  printSpeed();
}
