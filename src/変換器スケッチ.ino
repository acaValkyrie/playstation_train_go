// #include <Psx.h>   
// #include <Wire.h>                                     
                                                         
// #define dataPin 8       //データピン番号
// #define cmndPin 9       //コマンドピン番号
// #define attPin 11       //アテンションピン番号
// #define clockPin 10     //クロックピン番号

// const int EB = 2;         //非常リレーピン番号
// const int Start = 3;      //スタートTRピン番号
// const int sankaku = 4;    //三角TRピン番号
// const int maru = 5;       //丸TRピン番号
// const int batsu = 6;      //バツTRピン番号
// const int shikaku = 7;    //三角TRピン番号
// const int wt = 3000;     //モード選択長押し時間指定

// Psx Psx;                                                

//                                                                                                               //デジポテ情報
// const int OneHan1[] = {127,173,192,211,232,255,89,79,68,57,45,34,23,0,0};                                     //ワンハンドル位置
// const int TwoHan1[] = {127,173,192,211,232,255,170,181,192,203,213,224,235,255,255};                          //ツーハンドル位置
// const int TwoHan2[] = {127,82,67,30,0,0,178,202,227,255,255,255,255,255,255};                                 //ツーハンドル(103系)位置
// const int SousaYT[] = {0,250,1000,0,1000,250};                                                                //以下選択モード用
// const int SousaYS[] = {127,0,0,127,255,255};
// const int SousaXT[] = {0,250,350,500,700,800,1000,0,1000,800,700,500,350,250,0};
// const int SousaXS[] = {127,0,0,0,0,0,0,127,255,255,255,255,255,255,127};

                                             

// unsigned int data = 0;    
// int P,B,S,Pbit,Bbit,BTNbit,i,ii,HSW1val,Mode,ModeST,m,t;
// unsigned int Handle[]={15,2062,14,2059,11,2058,13,7,5,14,12,6,4,11,9,3,1,10,8,2,0};                          //ハンドルビット判別


// void setup()
// {
//   Psx.setupPins(dataPin, cmndPin, attPin, clockPin, 10);                            
//   Serial.begin(9600);
//   Wire.begin();
//   pinMode(EB,OUTPUT);
//   pinMode(Start,OUTPUT);
//   pinMode(sankaku,OUTPUT);
//   pinMode(maru,OUTPUT);
//   pinMode(batsu,OUTPUT);
//   pinMode(shikaku,OUTPUT);

//   Wire.beginTransmission(0x28);       //L側　初期I2C通信
//   Wire.write(byte(0xA9));            
//   Wire.write(127);    
//   Wire.write(127);         
//   Wire.endTransmission(); 

//   Wire.beginTransmission(0x29);       //R側　初期I2C通信
//   Wire.write(byte(0xA9));            
//   Wire.write(127);    
//   Wire.write(127);         
//   Wire.endTransmission();
  
//   P = 0;
//   B = 0;
//   S = 0;
//   Mode = 0;           //モード初期設定は選択モード
//   ModeST = 0;

// }

// void loop()
// {
//   data = Psx.read(); 
//   Pbit = data & 2063;                               //bit処理
//   Bbit = data >> 12;    
//   BTNbit = data & 1936;   
//   BTNbit = BTNbit >> 4;
//   i = 2;          

           

//   if((Pbit == Handle[0]) && (Bbit == Handle[6])){               //ニュートラル判定
//     P = 0;
//     B = 0;
    
//   }else{                                                        //マスコン・ブレーキ判定
//     for (i = 0; i <= 22; i++) {
//       if(i <= 5){
//         if(Pbit == Handle[i]){
//           P = i;
//           i = 5;
//         }
//       }else{
//         if(Bbit == Handle[i]){
//           B = i - 6;
//           i = 22;
//         }
//       }
//     }
//   }



//   if(B == 0){                                                           //ノッチ情報を単一化・コントローラー未接続処理
//     S = P;
//   }else{
//     if(B >= 9){
//       if(data == 0){
//        S = 0;
//       }else{
//       S = 14;
//       }
//     }else{
//      S = B + 5;
//     }
//   }

  
//    if((ModeST == 1) || (Mode == 0)){
//      digitalWrite(EB, HIGH);
//    }else{
//     if(S < 14 || data == 0){                                                           //EBリレー制御
//       digitalWrite(EB, HIGH);       
//     }else{
//       digitalWrite(EB, LOW);
//     }
//    }
   


//   if (BTNbit & (1<<0)){          //Startボタン
//     digitalWrite(Start, HIGH);      
//     Serial.print("STR");
//    }else{
//     digitalWrite(Start, LOW);
//   }

//   if (BTNbit & (1<<4)){           //△ボタン
//     if(BTNbit & (1<<3)){
//       digitalWrite(sankaku, LOW);
//       }else{
//     digitalWrite(sankaku, HIGH);       
//     Serial.print("sankaku");
//       }
//    }else{
//     digitalWrite(sankaku, LOW);
//   }

//   if (BTNbit & (1<<6)){           //○ボタン
//     digitalWrite(maru, HIGH);    
//     Serial.print("maru");   
//    }else{
//     digitalWrite(maru, LOW);
//   }

//   if (BTNbit & (1<<5)){           //☓ボタン
//     digitalWrite(batsu, HIGH);     
//     Serial.print("batsu");  
//    }else{
//     digitalWrite(batsu, LOW);
//   }
  
//   if (BTNbit & (1<<3) && BTNbit & (1<<4)){      //□ボタン
//     digitalWrite(shikaku, HIGH);   
//     Serial.print("shikaku");    
//    }else{
//     digitalWrite(shikaku, LOW);
//   }


//   if((BTNbit & (1<<3)) && (S == 14)){           //モード変更モードフラグ（非常+SELECT5秒）
//     t = millis();
//     delay(20);
//       do {
//           data = Psx.read();  
//           BTNbit = data & 1936;   
//           BTNbit = BTNbit >> 4;
//           Serial.println(t);
//           delay(20);
//         } while (BTNbit == 8);
//      if(millis()-t > wt){
//         ModeST = 1;
//         t = 0;
//      }
//   }

//   if(ModeST == 1){                                //モード変更モード
//     for (m = 0; m < 6; m++){ 
//       if(BTNbit & (1<<3)){
//          Mode = S;
//          m = 6 ;
//          ModeST = 0;
//       }
//     }
//   }
  
//   if(ModeST == 1){          //モード選択モード時は操作無効
//     Wire.beginTransmission(0x28);       //L側　I2C通信
//     Wire.write(byte(0xA9));            
//     Wire.write(127);    
//     Wire.write(127);         
//     Wire.endTransmission(); 

//     Wire.beginTransmission(0x29);       //R側　I2C通信
//     Wire.write(byte(0xA9));            
//     Wire.write(127);    
//     Wire.write(127);         
//     Wire.endTransmission();
  
//   }else{

//     if( Mode == 0){                       //モード0操作モード
//      if((P == 0) || (B == 0)){
//       Wire.beginTransmission(0x28);       //L側　I2C通信（ニュートラル位置）
//       Wire.write(byte(0xA9));            
//       Wire.write(127);    
//       Wire.write(127);         
//       Wire.endTransmission(); 
//      }else{
//       if((S < 6) || (S == 12 )){

//        Wire.beginTransmission(0x28);       //L側　I2C通信_横軸操作
//        Wire.write(byte(0xA9));            
//        Wire.write(127);    
//        Wire.write(SousaYS[P]);         
//        Wire.endTransmission(); 
//        delay(50);
       
//        Wire.beginTransmission(0x28);       //L側　I2C通信ニュートラル位置）
//        Wire.write(byte(0xA9));            
//        Wire.write(127);    
//        Wire.write(127);         
//        Wire.endTransmission(); 
//        delay(SousaYT[P]);
       
//       }else{
        
//        Wire.beginTransmission(0x28);       //L側　I2C通信_縦軸操作
//        Wire.write(byte(0xA9));            
//        Wire.write(SousaXS[B]);    
//        Wire.write(127);         
//        Wire.endTransmission(); 
//        delay(50); 
       
//        Wire.beginTransmission(0x28);       //L側　I2C通信（ニュートラル位置）
//        Wire.write(byte(0xA9));            
//        Wire.write(127);    
//        Wire.write(127);         
//        Wire.endTransmission(); 
//        delay(SousaXT[B]);
//       }
//      }

//     Wire.beginTransmission(0x29);       //R側　I2C通信（ニュートラル位置）
//     Wire.write(byte(0xA9));            
//     Wire.write(127);    
//     Wire.write(127);         
//     Wire.endTransmission();
//     }
    
//     if( Mode == 1){                  //モード1ワンハンドルモード
//     Wire.beginTransmission(0x28);       //L側　I2C通信
//     Wire.write(byte(0xA9));            
//     Wire.write(127);    
//     Wire.write(OneHan1[S]);         
//     Wire.endTransmission(); 

//     Wire.beginTransmission(0x29);       //R側　I2C通信
//     Wire.write(byte(0xA9));            
//     Wire.write(127);    
//     Wire.write(127);         
//     Wire.endTransmission();
//    }
   

//    if( Mode == 2){                  //モード2ツーハンドル
//     if(S < 6){
//     Wire.beginTransmission(0x28);      //L側　I2C通信
//     Wire.write(byte(0xA9));            
//     Wire.write(127);    
//     Wire.write(TwoHan1[S]);         
//     Wire.endTransmission(); 

//     Wire.beginTransmission(0x29);     //R側　I2C通信
//     Wire.write(byte(0xA9));            
//     Wire.write(127);    
//     Wire.write(127);         
//     Wire.endTransmission(); 
//      }else{
//     Wire.beginTransmission(0x28);     //L側　I2C通信
//     Wire.write(byte(0xA9));            
//     Wire.write(127);    
//     Wire.write(127);         
//     Wire.endTransmission(); 
    
//     Wire.beginTransmission(0x29);     //R側　I2C通信
//     Wire.write(byte(0xA9));            
//     Wire.write(TwoHan1[S]);    
//     Wire.write(127);         
//     Wire.endTransmission();  
//       }
//     }
//    if( Mode == 3){                  //モード3ツーハンドル(103系)
//     if(S < 6){
//     Wire.beginTransmission(0x28);      //L側　I2C通信
//     Wire.write(byte(0xA9));            
//     Wire.write(TwoHan2[S]);    
//     Wire.write(127);         
//     Wire.endTransmission(); 

//     Wire.beginTransmission(0x29);     //R側　I2C通信
//     Wire.write(byte(0xA9));            
//     Wire.write(127);    
//     Wire.write(127);         
//     Wire.endTransmission(); 
//      }else{
//     Wire.beginTransmission(0x28);     //L側　I2C通信
//     Wire.write(byte(0xA9));            
//     Wire.write(127);    
//     Wire.write(127);         
//     Wire.endTransmission(); 
    
//     Wire.beginTransmission(0x29);     //R側　I2C通信
//     Wire.write(byte(0xA9));            
//     Wire.write(TwoHan2[S]);    
//     Wire.write(127);         
//     Wire.endTransmission();  
//       }
//     }
//   } 
//   Serial.print(P);                //ノッチ表示
//   Serial.print(',');
//   Serial.print(B);                //ブレーキ表示
//   Serial.print(',');
//   Serial.print(Pbit);             //
//   Serial.print(',');
//   Serial.print(Bbit); 
//   Serial.print(',');  
//   Serial.print(BTNbit); 
//   Serial.print(',');
//   Serial.print(data);
//   Serial.print(',');
//   Serial.print(S);
//   Serial.print(',');
//   Serial.print(Mode);
//   Serial.print(',');
//   Serial.print(ModeST);
//   Serial.print(',');
//   Serial.print(t);
//   Serial.print(',');
//   Serial.println(millis());

// }
