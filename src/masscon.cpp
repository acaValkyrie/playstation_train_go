#include "masscon.h"

Psx MassController;

unsigned int data = 0;
int P, B, S,Pbit,Bbit;
unsigned int Handle[]={15,2062,14,2059,11,2058,13,7,5,14,12,6,4,11,9,3,1,10,8,2,0};  //ハンドルビット判別

void massconSetup(){
  MassController = Psx();
  MassController.setupPins(dataPin, cmndPin, attPin, clockPin, 10);
  Serial.begin(9600);
  Wire.begin();

  P = 0;
  B = 0;
}

void updateBrakeAccell(){
  data = MassController.read();
  Pbit = data & 2063; //bit処理
  Bbit = data >> 12;

  if((Pbit == (int)Handle[0]) && (Bbit == (int)Handle[6])){  //ニュートラル判定
    P = 0;
    B = 0;
    return;
  }
  for (int i = 0; i <= 22; i++) {
    if(i <= 5){
      if(Pbit == (int)Handle[i]){
        P = i;
        i = 5;
      }
    }else{
      if(Bbit == (int)Handle[i]){
        B = i - 6;
        return;
      }
    }
  }
}

int getP(){
  return P;
}

int getB(){
  return B;
}

void printMassconPropaties(){
  Serial.print("P:");
  Serial.print(P);                //ノッチ表示
  // Bbitを表示させないとBbitが安定しない
  Serial.print(", Bbit:");
  Serial.print(Bbit);             //ブレーキビット表示
  Serial.print(", B:");
  Serial.print(B);                //ブレーキ表示
}