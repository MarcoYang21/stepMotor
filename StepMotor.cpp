#include "StepMotor.h"

#include <Arduino.h>
StepMotor::StepMotor(int dirPin, int enaPin, int stpPin) {
  directionPin = dirPin;  // 設定方向控制腳的引腳
  enablePin = enaPin;     // 設定啟用/停用控制腳的引腳
  stepPin = stpPin;       // 設定步進腳的引腳
  isRunning = false;      // 初始化為非運行狀態
  rotationDirection = 1;  // 初始為正向旋轉
  stepsPerRev = 1600;     // 一個完整旋轉（360度）所需的步數
  pulseDirection = true;  // 起始脈衝方向為真（正向）

  pinMode(directionPin, OUTPUT);  // 設定方向控制腳為輸出模式
  pinMode(enablePin, OUTPUT);     // 設定啟用/停用控制腳為輸出模式
  pinMode(stepPin, OUTPUT);       // 設定步進腳為輸出模式
}

void StepMotor::setDirection(int dir) {
  digitalWrite(directionPin, dir);             // 設定方向控制腳的電位高低
  rotationDirection = (dir == HIGH) ? 1 : -1;  // 根據電位高低設定旋轉方向
}

void StepMotor::enable() {
  digitalWrite(enablePin, LOW);  // 啟用馬達
}

void StepMotor::disable() {
  digitalWrite(enablePin, HIGH);  // 停用馬達
}

void StepMotor::rotate(float degrees, unsigned long rotationTime) {
  targetSteps = int((degrees / 360.0) * stepsPerRev);                  // 計算所需的步數
  stepDelay = static_cast<double>(rotationTime) / targetSteps * 1000;  // 計算每步之間的時間延遲
  currentStep = 0;                                                     // 初始化當前步數
  isRunning = true;                                                    // 設定為運行狀態
  enable();                                                            // 啟用馬達
}

void StepMotor::reverseRotation() {
  rotationDirection = -rotationDirection;                             // 反轉旋轉方向
  digitalWrite(directionPin, (rotationDirection == 1) ? HIGH : LOW);  // 根據反轉方向設定方向控制腳
}

bool StepMotor::isFinished() {
  return !isRunning;  // 檢查是否完成運行
}

void StepMotor::run() {
  if (isRunning) {
    unsigned long currentTime = micros();  // 取得當前時間（微秒）
    if (currentStep > targetSteps) {
      isRunning = false;  // 如果已完成所有步數，則設定為非運行狀態
    } else {
      if (currentTime - lastStepTime >= stepDelay) {
        digitalWrite(enablePin, LOW);           // 啟用馬達
        digitalWrite(stepPin, pulseDirection);  // 輸出步進脈衝
        pulseDirection = !pulseDirection;       // 切換脈衝方向
        currentStep++;                          // 增加當前步數
        lastStepTime = currentTime;             // 更新最後一次輸出脈衝的時間
      }
    }
  }
}