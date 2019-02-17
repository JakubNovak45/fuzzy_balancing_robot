#include <MsTimer2.h>

#define MOTOR_1_RPWM    9
#define MOTOR_1_LPWM    10
#define MOTOR_1_ENC_A   2
#define MOTOR_1_ENC_B   7

#define MOTOR_2_RPWM    6
#define MOTOR_2_LPWM    5
#define MOTOR_2_ENC_A   3
#define MOTOR_2_ENC_B   8

float P = 14.5;
float Ti = 0.145;
float Ts = 0.01;

float w = 0;
volatile int count_m1 = 0;
volatile int count = 0;
volatile int count_m1_last = 0;
volatile int cpp_m1 = 0;
volatile int e0 = 0;
volatile float u0 = 0;
volatile float u1 = 0;
volatile int e1 = 0;
volatile bool Flag = false;
//float d0 = 12.8968;
//float d1 = -12.5;

void setup() {
  // put your setup code here, to run once:
  pinMode(MOTOR_1_RPWM, OUTPUT);
  pinMode(MOTOR_1_LPWM, OUTPUT);
  pinMode(MOTOR_2_RPWM, OUTPUT);
  pinMode(MOTOR_2_LPWM, OUTPUT);

  Serial.setTimeout(1000000);
  Serial.begin(115200);

  MsTimer2::set(10, tim1); // 10ms period
  MsTimer2::start();

  attachInterrupt(digitalPinToInterrupt(MOTOR_1_ENC_A), encoder_m1, CHANGE);

  analogWrite(MOTOR_1_LPWM, 0);
  analogWrite(MOTOR_2_LPWM, 0);
}

void loop() {
  while (!Flag) {}
  Flag = false;
  w = Serial.parseFloat();
  if (w != 0)
  {
    e0 = w - cpp_m1;
    u0 = u1 +  (P + (Ts / Ti)) * e0 + (-P) * e1;
    e1 = e0;
    u1 = u0;
    motor((int) u0);
  }
  else
  {
    motor(0); //regulation shutdown (angle out of range +-45°)
  }
}

void tim1() {
  cpp_m1 = count_m1 - count_m1_last;
  count_m1_last = count_m1;
  Flag = true;
}

void encoder_m1() {
  if (digitalRead(MOTOR_1_ENC_A) == HIGH) {
    if (digitalRead(MOTOR_1_ENC_B) == HIGH)
      count--;
    else
      count++;
  }
  else
  {
    if (digitalRead(MOTOR_1_ENC_B) == HIGH)
      count++;
    else
      count--;
  }
}

void motor(int duty) {
  if (duty < 256 && duty > -256) {
    if (duty > 0)
    {
      analogWrite(MOTOR_1_RPWM, duty);
      analogWrite(MOTOR_1_LPWM, 0);
      analogWrite(MOTOR_2_RPWM, duty);
      analogWrite(MOTOR_2_LPWM, 0);
    } else {
      duty = duty * (-1);
      analogWrite(MOTOR_1_RPWM, 0);
      analogWrite(MOTOR_1_LPWM, duty);
      analogWrite(MOTOR_2_RPWM, 0);
      analogWrite(MOTOR_2_LPWM, duty);
    }
  } else if (duty >= 256) {
    duty = 255;
    analogWrite(MOTOR_1_RPWM, duty);
    analogWrite(MOTOR_1_LPWM, 0);
    analogWrite(MOTOR_2_RPWM, duty);
    analogWrite(MOTOR_2_LPWM, 0);
  } else if (duty <= -256) {
    duty = 255;
    analogWrite(MOTOR_1_RPWM, 0);
    analogWrite(MOTOR_1_LPWM, duty);
    analogWrite(MOTOR_2_RPWM, 0);
    analogWrite(MOTOR_2_LPWM, duty);
  }
}
