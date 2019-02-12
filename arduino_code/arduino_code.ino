#include <MsTimer2.h>

#define MOTOR_1_RPWM    9
#define MOTOR_1_LPWM    10
#define MOTOR_1_ENC_A   2
#define MOTOR_1_ENC_B   7

#define MOTOR_2_RPWM    6
#define MOTOR_2_LPWM    5
#define MOTOR_2_ENC_A   3
#define MOTOR_2_ENC_B   8

volatile int count_m1 = 0;
volatile int count_m2 = 0;
volatile int count_m1_last = 0;
volatile int count_m2_last = 0;
volatile int count = 0;
volatile int count_last = 0;
volatile int cpp = 0;
volatile int cpp_m1 = 0;
volatile int cpp_m2 = 0;
volatile uint8_t flag = 0;
volatile int e0 = 0;
volatile int e1 = 0;
volatile int e2 = 0;
volatile int w = 0;
volatile float u0 = 0;
volatile float u1 = 0;
float d0 = 6.7903;//592.8581;
float d1 = -4.7301;//570.3108;
int t =0;

//String receiveBuffer = "";
volatile bool Flag = false;
int pos = 0;
int z = 0;

void setup() {
  pinMode(MOTOR_1_RPWM,OUTPUT);
  pinMode(MOTOR_1_LPWM,OUTPUT);
  pinMode(MOTOR_2_RPWM,OUTPUT);
  pinMode(MOTOR_2_LPWM,OUTPUT);

  pinMode(MOTOR_1_ENC_A, INPUT);
  pinMode(MOTOR_1_ENC_B, INPUT);
  pinMode(MOTOR_2_ENC_A, INPUT);
  pinMode(MOTOR_2_ENC_B, INPUT);

  Serial.begin(115200);

  MsTimer2::set(10, tim1); // 500ms period
  MsTimer2::start();

  attachInterrupt(digitalPinToInterrupt(MOTOR_1_ENC_A), encoder_m1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MOTOR_2_ENC_A), encoder_m2, CHANGE);

  analogWrite(MOTOR_1_LPWM, 0);
  analogWrite(MOTOR_2_LPWM, 0);
}

void loop() {
  while (!Flag){}
  Flag = false;
  w = Serial.parseFloat();//serialEvent();
  if (w == 0){
    motor_1(0);
    motor_2(0);
  }else{
    e0 = w - cpp_m1;
    u0 = u1 +  12.8968*e0 -12.5*e1;
    e1 = e0;
    u1 = u0;
    //w=15;
    motor_1((int)-u0);
    motor_2((int)-u0);
  }
}

void encoder_m1() {
  if (digitalRead(MOTOR_1_ENC_A) == HIGH) {
    if (digitalRead(MOTOR_1_ENC_B) == HIGH)
      count_m1--;
    else
      count_m1++;
  }
  else
  {
    if (digitalRead(MOTOR_1_ENC_B) == HIGH)
      count_m1++;
    else
      count_m1--;
  }
}

void encoder_m2() {
  if (digitalRead(MOTOR_2_ENC_A) == HIGH) {
    if (digitalRead(MOTOR_2_ENC_B) == HIGH)
      count_m2--;
    else
      count_m2++;
  }
  else
  {
    if (digitalRead(MOTOR_2_ENC_B) == HIGH)
      count_m2++;
    else
      count_m2--;
  }
}

void tim1() {
  cpp_m1 = count_m1 - count_m1_last;
  cpp_m2 = count_m2 - count_m2_last;
  count_m1_last = count_m1;
  count_m2_last = count_m2;
  Flag = true;
}

void motor_1(int duty){
  if (duty < 256 && duty > -256){
    if (duty > 0)
    {
      analogWrite(MOTOR_1_RPWM, duty);
      analogWrite(MOTOR_1_LPWM, 0);
    }else{
      duty = duty * (-1);
      analogWrite(MOTOR_1_RPWM, 0);
      analogWrite(MOTOR_1_LPWM, duty);
    }
  }else if(duty >= 256){
    duty = 255;
    analogWrite(MOTOR_1_RPWM, duty);
    analogWrite(MOTOR_1_LPWM, 0);
  }else if(duty <= -256){
    duty = 255;
    analogWrite(MOTOR_1_RPWM, 0);
    analogWrite(MOTOR_1_LPWM, duty);
  }
}

void motor_2(int duty){
  if (duty < 256 && duty > -256){
    if (duty > 0)
    {
      analogWrite(MOTOR_2_RPWM, duty);
      analogWrite(MOTOR_2_LPWM, 0);
    }else{
      duty = duty * (-1);
      analogWrite(MOTOR_2_RPWM, 0);
      analogWrite(MOTOR_2_LPWM, duty);
    }
  }else if(duty >= 256){
    duty = 255;
    analogWrite(MOTOR_2_RPWM, duty);
    analogWrite(MOTOR_2_LPWM, 0);
  }else if(duty <= -256){
    duty = 255;
    analogWrite(MOTOR_2_RPWM, 0);
    analogWrite(MOTOR_2_LPWM, duty);
  }
}
/*
char* inputString;
bool stringComplete;

void serialEvent() {
  while (Serial.available()) {
   int incomming_byte;
    while ((incomming_byte = Serial.read()) != '\n') {
    if(incomming_byte == 45){
      receiveBuffer += '-';
    }else{
      receiveBuffer += incomming_byte -48;
    }

   }

    w=receiveBuffer.toInt();
   //Serial.println(receiveBuffer);
   receiveBuffer = "";
  }
}*/
