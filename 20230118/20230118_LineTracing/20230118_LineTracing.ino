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

#define Line_1 A0
#define Line_2 A1
#define Line_3 A2
#define Line_4 A3
#define Line_5 A4

#define Circle 1400
#define Speed 70

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

  pinMode(Line_1, INPUT);
  pinMode(Line_2, INPUT);
  pinMode(Line_3, INPUT);
  pinMode(Line_4, INPUT);
  pinMode(Line_5, INPUT);

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
      movement(-1,Speed,-1,Speed);
      break;
    case 2: //후진
      movement(1,Speed,1,Speed);
      break;
    case 3: //좌회전
      movement(1,Speed,-1,Speed);
      break;
    case 4: //우회전
      movement(-1,Speed,1,Speed);
      break;
    case 0:
      movement(0,0,0,0);
      break;
  }
}
double F_distance =0;
double L_distance =0;
double R_distance =0;

void distance_sense(){
  F_distance = sonar[0].ping_cm() * 10;
  L_distance = sonar[1].ping_cm() * 10;
  R_distance = sonar[2].ping_cm() * 10;

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
}

void Line_Tracing(int Value){ //줄 따라가기 이동 단축
  if(Value < 0) movement(0,Speed,-1,-Value*Speed);
  else if(Value > 0) movement(-1,Value*Speed,0,Speed);
  else basic(1);
}

int SenseInfo[5] = {0};
void LineReading(){
  int LineValue = 0;
  for(int i=0;i<5;i++){
    SenseInfo[i] = analogRead(A0+i);
    if(i == 0) if(SenseInfo[i] < 100) LineValue -= 2;
    if(i == 1) if(SenseInfo[i] < 100) LineValue -= 1;
    if(i == 2) if(SenseInfo[i] < 100) LineValue += 0;
    if(i == 3) if(SenseInfo[i] < 100) LineValue += 1;
    if(i == 4) if(SenseInfo[i] < 100) LineValue += 2;
    Serial.print(SenseInfo[i]);
    Serial.print("   ");
  }
  Serial.print(LineValue);
  Serial.println("");
  if(LineValue != 0){
    while(analogRead(A2) > 100){
      Line_Tracing(LineValue);
    }
  }
}

void loop() {
  LineReading();
  //distance_sense();
  basic(1);
}
