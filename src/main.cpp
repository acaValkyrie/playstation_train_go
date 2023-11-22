#include <Psx.h>
#include <Wire.h>
#include <Arduino.h>

#define dataPin 8       //データピン番号
#define cmndPin 9       //コマンドピン番号
#define attPin 11       //アテンションピン番号
#define clockPin 10     //クロックピン番号

#define pwmOutPin 3

Psx MassController;

unsigned int data = 0;
int P,B,S,Pbit,Bbit;
unsigned int Handle[]={15,2062,14,2059,11,2058,13,7,5,14,12,6,4,11,9,3,1,10,8,2,0};  //ハンドルビット判別

float speed;

void setup(){
  MassController = Psx();
  MassController.setupPins(dataPin, cmndPin, attPin, clockPin, 10);
  Serial.begin(9600);
  Wire.begin();

  P = 0;
  B = 0;

  pinMode(pwmOutPin, OUTPUT);
  speed = 0;
}
void loop(){
  data = MassController.read();
  Pbit = data & 2063; //bit処理
  Bbit = data >> 12;

  if((Pbit == (int)Handle[0]) && (Bbit == (int)Handle[6])){  //ニュートラル判定
    P = 0;
    B = 0;
  }else{                                                     //マスコン・ブレーキ判定
    for (int i = 0; i <= 22; i++) {
      if(i <= 5){
        if(Pbit == (int)Handle[i]){
          P = i;
          i = 5;
        }
      }else{
        if(Bbit == (int)Handle[i]){
          B = i - 6;
          i = 22;
        }
      }
    }
  }

  Serial.print("P:");
  Serial.print(P);                //ノッチ表示
  Serial.print(", Bbit:");
  Serial.print(Bbit);             //ブレーキビット表示
  Serial.print(", B:");
  Serial.print(B);                //ブレーキ表示

  speed += P * 0.1 - B * 0.1;
  if(speed > 255){
    speed = 255;
  }else if(speed < 0){
    speed = 0;
  }
  Serial.print(", speed:");
  Serial.println(speed);          //速度表示
  analogWrite(pwmOutPin, (int)speed);
}
