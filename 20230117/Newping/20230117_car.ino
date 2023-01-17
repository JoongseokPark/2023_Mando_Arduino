#include <NewPing.h>

#define IN1 2 //왼쪽 모터
#define IN2 3
#define ENL 5
#define IN3 4 //오른쪽 모터
#define IN4 7
#define ENR 6

#define F_Sonar 8
#define L_Sonar 11
#define R_Sonar 10

#define Circle 1400

NewPing sonar[3] = {
  NewPing (F_Sonar, F_Sonar, 500),
  NewPing (R_Sonar, R_Sonar, 500),
  NewPing (L_Sonar, L_Sonar, 500),};
  
void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENL, OUTPUT);
  
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENR, OUTPUT);
  
  pinMode(F_Sonar, OUTPUT);
  pinMode(L_Sonar, OUTPUT);
  pinMode(R_Sonar, OUTPUT);

  Serial.begin(9600);
}

void movement(int dir_1,int speed_1,int dir_r,int speed_r){
  switch(dir_1){ //왼쪽 모터 제어
  case 1: //전진
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    analogWrite(ENL,speed_1);
    break;
  case -1: //후진
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    analogWrite(ENL,speed_1);
    break;
  default: //정지
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    analogWrite(ENL,0);
    break;
  }
  switch(dir_r){ //오른쪽 모터 제어
  case 1: //전진
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    analogWrite(ENR,speed_r);
    break;
  case -1: //후진
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    analogWrite(ENR,speed_r);
    break;
  default: //정지
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
    analogWrite(ENR,0);
    break;
  }
}

void basic(int mode){ //이동 단축
  switch(mode){
    case 1: //전진
      movement(-1,80,-1,80);
      break;
    case 2: //후진
      movement(1,80,1,80);
      break;
    case 3: //좌회전
      movement(1,80,-1,80);
      break;
    case 4: //우회전
      movement(-1,80,1,80);
      break;
    case 0:
      movement(0,0,0,0);
      break;
  }
}
double F_distance =0;
double L_distance =0;
double R_distance =0;

void loop() {
  F_distance = sonar[0].ping_cm() * 10;
  L_distance = sonar[1].ping_cm() * 10;
  R_distance = sonar[2].ping_cm() * 10;
   Serial.print(F_distance);
  Serial.print("     ");
  Serial.print(R_distance);
  Serial.print("     ");
  Serial.println(L_distance);

  if(F_distance!=0&&F_distance<200){
    basic(3);
    delay(Circle);
  }
  if(L_distance!=0&&L_distance<200){
    basic(3);
    delay(Circle/2);
  }
  if(R_distance!=0&&R_distance<200){
    basic(4);
    delay(Circle/2);
  }

  basic(1);
}
