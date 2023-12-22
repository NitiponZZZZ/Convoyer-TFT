TaskHandle_t Task1;
TaskHandle_t Task2;
#include <ESP32Servo.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#define pin_Motor_A 12
#define pin_Motor_B 14
#define PWM1_Ch 6
#define PWM1_Res 8
#define PWM1_Freq 1000
#define pin_Motor_C 27
#define pin_Motor_D 26
#define PWM2_Ch 14
#define PWM2_Res 8
#define PWM2_Freq 1000
#define pin_Motor_E 25
#define pin_Motor_F 4
#define pin_Motor_G 21
#define PWM3_Ch 7
#define PWM3_Res 8
#define PWM3_Freq 1000
#define pin_Sensor1 39
#define pin_Sensor4 36
#define pin_Limit1 34
#define pin_Limit2 35
#define pin_Servo1 32
#define pin_Servo2 22
#define pin_Servo3 13
#define pin_Servo4 33
#define pin_Commu 15
const int minUs = 1000, maxUs = 2000, led1 = 2, led2 = 4;
bool val_sensor1, val_sensor4, val_limit1, val_limit2;
uint8_t Finished_product = 0, Workin_processt = 0, Assemble_parts = 0, Defective_part = 0, page;
uint8_t stateN = 0, StageStop = 1;
Servo Servo1, Servo2, Servo3, Servo4;
TFT_eSPI tft = TFT_eSPI();
TFT_eSPI_Button key[3];
ESP32PWM pwm;

void setup() {
  Serial.begin(115200);
  ESP32PWM::allocateTimer(0), ESP32PWM::allocateTimer(1), ESP32PWM::allocateTimer(2), ESP32PWM::allocateTimer(3);
  Servo1.setPeriodHertz(50), Servo2.setPeriodHertz(50), Servo3.setPeriodHertz(50), Servo4.setPeriodHertz(50);
  pinMode(led1, OUTPUT), pinMode(led2, OUTPUT);
  Servo1.attach(pin_Servo1, minUs, maxUs), Servo2.attach(pin_Servo2, minUs, maxUs), Servo3.attach(pin_Servo3, minUs, maxUs), Servo4.attach(pin_Servo4, minUs, maxUs);
  pinMode(pin_Motor_A, OUTPUT);
  pinMode(pin_Motor_B, OUTPUT);
  pinMode(pin_Motor_C, OUTPUT);
  pinMode(pin_Motor_D, OUTPUT);
  pinMode(pin_Motor_E, OUTPUT);
  pinMode(pin_Motor_F, OUTPUT);
  pinMode(pin_Motor_G, OUTPUT);
  //pinMode(pin_Commu, OUTPUT);
  pinMode(pin_Sensor1, INPUT_PULLUP);
  pinMode(pin_Sensor4, INPUT_PULLUP);
  pinMode(pin_Limit1, INPUT_PULLUP);
  pinMode(pin_Limit2, INPUT_PULLUP);

  ledcAttachPin(pin_Motor_A, PWM1_Ch), ledcSetup(PWM1_Ch, PWM1_Freq, PWM1_Res), ledcAttachPin(pin_Motor_C, PWM2_Ch);
  ledcSetup(PWM2_Ch, PWM2_Freq, PWM2_Res), ledcAttachPin(pin_Motor_E, PWM3_Ch), ledcSetup(PWM3_Ch, PWM3_Freq, PWM3_Res);
  tft.init();
  tft.setRotation(3);
  uint16_t calData[5] = { 282, 3573, 204, 3562, 7 };
  tft.setTouch(calData);
  main_page();
  xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 1, &Task1, 0);
  delay(500);
  xTaskCreatePinnedToCore(Task2code, "Task2", 10000, NULL, 1, &Task2, 1);
  delay(500);

  bridge(0);
  Servo3.write(180);  //Up Griper
  delay(250);
  Servo2.write(95);  //Open Gripper
  delay(250);
  Servo2.write(170);  //Close Gripper
  delay_N(250);
  Servo2.write(95);  //Open Gripper
  delay_N(250);
  Servo4.write(180);  //Open gate 2
  delay_N(250);
  Servo1.write(180);  //Open gate 1
  int testCartesian = 0;

  while (testCartesian == 0) {
    if (val_limit1) {
      bridge(0);
      testCartesian = 1;
      break;
    } else {
      bridge(80);
    }
  }
  while (testCartesian == 1) {
    if (val_limit2) {
      break;
    } else {
      bridge(-80);
    }
  }
}

void loop() {
}