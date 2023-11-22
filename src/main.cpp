#include <Psx.h>
#include <Wire.h>
#include <Arduino.h>

#define dataPin 8       //データピン番号
#define cmndPin 9       //コマンドピン番号
#define attPin 11       //アテンションピン番号
#define clockPin 10     //クロックピン番号

const int EB = 2;         //非常リレーピン番号
const int Start = 3;      //スタートTRピン番号
const int sankaku = 4;    //三角TRピン番号
const int maru = 5;       //丸TRピン番号
const int batsu = 6;      //バツTRピン番号
const int shikaku = 7;    //三角TRピン番号
const int wt = 3000;     //モード選択長押し時間指定

Psx MassController;
                                                                                     //デジポテ情報
const int OneHan1[] = {127,173,192,211,232,255,89,79,68,57,45,34,23,0,0};            //ワンハンドル位置
const int TwoHan1[] = {127,173,192,211,232,255,170,181,192,203,213,224,235,255,255}; //ツーハンドル位置
const int TwoHan2[] = {127,82,67,30,0,0,178,202,227,255,255,255,255,255,255};        //ツーハンドル(103系)位置
const int SousaYT[] = {0,250,1000,0,1000,250};                                       //以下選択モード用
const int SousaYS[] = {127,0,0,127,255,255};
const int SousaXT[] = {0,250,350,500,700,800,1000,0,1000,800,700,500,350,250,0};
const int SousaXS[] = {127,0,0,0,0,0,0,127,255,255,255,255,255,255,127};

unsigned int data = 0;
int P,B,S,Pbit,Bbit,BTNbit,i,ii,HSW1val,Mode,ModeST,m,t;
unsigned int Handle[]={15,2062,14,2059,11,2058,13,7,5,14,12,6,4,11,9,3,1,10,8,2,0};  //ハンドルビット判別

void setup(){
  MassController = Psx();
  MassController.setupPins(dataPin, cmndPin, attPin, clockPin, 10);
  Serial.begin(9600);
  Wire.begin();

  P = 0;
  B = 0;
}
void loop(){
  data = MassController.read();
  Pbit = data & 2063; //bit処理
  Bbit = data >> 12;
  i = 2;

  if((Pbit == (int)Handle[0]) && (Bbit == (int)Handle[6])){  //ニュートラル判定
    P = 0;
    B = 0;
  }else{                                                     //マスコン・ブレーキ判定
    for (i = 0; i <= 22; i++) {
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
  Serial.println();
}
