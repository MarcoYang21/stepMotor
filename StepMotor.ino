// 此版本是用Arduino Uno R4 WiFi撰寫
// 用物件的寫法來控制步進驗達
// 這個範例只是轉動33度，不間斷往反運動。
#include "StepMotor.h"  // 引入自定義的步進馬達控制頭文件

int rotateTime = 100;    // 旋轉運動時間，單位毫秒
float targetAngle = 33;  // 目標旋轉角度

const int PUL = 11;  // 步進腳位
const int DIR = 12;  // 正反轉控制腳位
const int EN = 13;   // 致能腳位

StepMotor myMotor(DIR, EN, PUL);  // 創建名為 myMotor 的 StepMotor 物件並初始化引腳

void setup() {
  // 執行初始化
  pinMode(PUL, OUTPUT);     // 設定步進腳位為輸出模式
  pinMode(DIR, OUTPUT);     // 設定正反轉控制腳位為輸出模式
  pinMode(EN, OUTPUT);      // 設定致能腳位為輸出模式
  myMotor.enable();         // 最初啟用電機
  Serial.begin(115200);     // 開啟串列通信
  Serial.println("Ready");  // 顯示訊息，表示程式已就緒
}

void loop() {
  myMotor.run();  // 啟動步進馬達運動

  if (myMotor.isFinished()) {
    // 旋轉後到設定位置後，才執行的程式碼
    delay(200);                               // 延遲 200 毫秒
    myMotor.reverseRotation();                // 反轉旋轉方向
    myMotor.rotate(targetAngle, rotateTime);  // 以指定角度和時間旋轉
  }
  // 其它需要一直被執行的工作
}
