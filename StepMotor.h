#ifndef StepMotor_h
#define StepMotor_h

#include <Arduino.h>  // 引入 Arduino 標準庫

class StepMotor {
public:
  StepMotor(int dirPin, int enaPin, int stpPin);  // 類別建構函數，用於初始化步進馬達的引腳

  void setDirection(int dir);                              // 設定步進馬達的運動方向
  void enable();                                           // 啟用步進馬達
  void disable();                                          // 停用步進馬達
  void rotate(float degrees, unsigned long rotationTime);  // 控制步進馬達旋轉到指定角度和時間
  void reverseRotation();                                  // 反轉步進馬達的運動方向
  bool isFinished();                                       // 檢查步進馬達是否已完成運動
  void run();                                              // 開始步進馬達的運動

private:
  int directionPin;       // 步進馬達的方向控制引腳
  int enablePin;          // 步進馬達的啟用/停用控制引腳
  int stepPin;            // 步進馬達的步進引腳
  int stepsPerRev;        // 一個完整旋轉（360度）所需的步數
  int targetSteps;        // 目標步數
  int currentStep;        // 目前的步數
  int stepDelay;          // 步進間的時間延遲
  int lastStepTime;       // 最後一次輸出步進脈衝的時間
  int rotationDirection;  // 1 表示正向旋轉，-1 表示反向旋轉
  bool pulseDirection;    // 控制步進脈衝方向
  bool isRunning;         // 步進馬達是否正在運行
};

#endif