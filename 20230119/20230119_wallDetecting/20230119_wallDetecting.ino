#include <NewPing.h>

#define IN1 2 //왼쪽 모터
#define IN2 3
#define ENL 5
#define IN3 4 //오른쪽 모터
#define IN4 7
#define ENR 6

#define F_Sonar 8  //전방 초음파
#define L_Sonar 11 //좌측 초음파
#define R_Sonar 10 //우측 초음파

#define Line_1 A0 //가장 왼쪽 선 센서
#define Line_2 A1
#define Line_3 A2
#define Line_4 A3
#define Line_5 A4 //가장 오른쪽 선 센서

#define Circle 1400 //100의 속도로 양쪽 바퀴가 반대로 돌 때 180도 회전에 걸리는 시간
#define Speed 100 //모터 기본 속도

NewPing sonar[3] = { //전좌후 초음파 센서 선언
  NewPing (F_Sonar, F_Sonar, 500),
  NewPing (R_Sonar, R_Sonar, 500),
  NewPing (L_Sonar, L_Sonar, 500),};
  
void setup()
{
  pinMode(IN1, OUTPUT); //왼쪽 모터 포트 선언
  pinMode(IN2, OUTPUT);
  pinMode(ENL, OUTPUT);
  
  pinMode(IN3, OUTPUT); //오른쪽 모터 포트 선언
  pinMode(IN4, OUTPUT);
  pinMode(ENR, OUTPUT);
  
  pinMode(F_Sonar, OUTPUT); //초음파 센서 포트 선언
  pinMode(L_Sonar, OUTPUT);
  pinMode(R_Sonar, OUTPUT);

  pinMode(Line_1, INPUT); //선 센서 포트 선언
  pinMode(Line_2, INPUT);
  pinMode(Line_3, INPUT);
  pinMode(Line_4, INPUT);
  pinMode(Line_5, INPUT);

  Serial.begin(9600);
}

void movement(int dir_1,int speed_1,int dir_r,int speed_r){ //모터 제어 함수
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

void basic(int mode){ //모터 제어 단축 함수
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

double F_distance =0; //삼방향 초음파 변수 선언
double L_distance =0;
double R_distance =0;

void turningObstacle(){ //선 위에서 장애물을 만났을 때 회피하는 함수
  while((L_distance = sonar[2].ping_cm() * 10) > 170) movement(-1,100,1,100);
  while((L_distance = sonar[2].ping_cm() * 10) < 200) basic(1);
  basic(3); delay(Circle/2);
  while((L_distance = sonar[2].ping_cm() * 10)>200) basic(1);
  while((L_distance = sonar[2].ping_cm() * 10)<300) basic(1);
  basic(3); delay(Circle/2);
  while(analogRead(A0)<600&&analogRead(A1)<600&&analogRead(A2)<600
        &&analogRead(A3)<600&&analogRead(A4)<600) basic(1);  
}

void distance_sense(){ //초음파로 거리 감지 후 모터 제어 함수
  F_distance = sonar[0].ping_cm() * 10; //전방
  R_distance = sonar[1].ping_cm() * 10; //우측
  L_distance = sonar[2].ping_cm() * 10; //좌측

  Serial.print(F_distance); //시리얼 모니터에 거리 출력
  Serial.print("   ");
  Serial.print(L_distance);
  Serial.print("   ");
  Serial.println(R_distance);

  if(F_distance!=0 && F_distance < 300){ //전방 장애물이 나타났을 경우
    basic(0);
    if(L_distance!=0 && L_distance < 300){ //좌측에도 장애물이 있는지 확인
      if(R_distance!=0 && R_distance < 300) basic(2); //우측 확인 후 장애물이 있다면 후진
      else while(sonar[2].ping_cm() * 10 < 350) basic(4); //좌측 센서에 감지될 때까지 우회전한다
    }
    else if(R_distance!=0 && R_distance < 300){ //좌측에 없다면 우측에는 장애물이 있는지 확인
      if(L_distance!=0 && L_distance < 300) basic(2); //우측 확인 후 장애물이 있다면 후진
      else while(sonar[1].ping_cm() * 10 < 350) basic(3); //우측 센서에 감지될 때까지 좌회전
    }
  }
  else { //전방 장애물이 없을 경우
    if(L_distance != 0 && L_distance < 600){ //왼쪽이 감지 범위 이내인지
      if(R_distance != 0 && R_distance < 600){ //그리고 오른쪽도 그런지 확인
        if(R_distance > L_distance) basic(4);
        else if(L_distance > R_distance) basic(3);
      }
    }
  }
  //선 위에서 장애물을 만났을 경우 정지한다
  if(analogRead(A2)>600 && F_distance < 150)basic(0); 

}

void Line_Tracing(int Value){ //줄 따라가기 이동 단축
  if(Value < 0) movement(0,Speed,-1,-Value*Speed);
  else if(Value > 0) movement(-1,Value*Speed,0,Speed);
  else basic(1);
}

int SenseInfo = 0; //5개 센서 값 저장 변수
void LineReading(){ //줄 따라가는 함수
  int LineValue = 0; //선의 위치를 판단하는 변수
  for(int i=0;i<5;i++){
    SenseInfo = analogRead(A0+i); //변수에 감지 값 저장
    if(i == 0) if(SenseInfo > 900) LineValue -= 2; //각 센서에 노란색 감지시 값 변화
    if(i == 1) if(SenseInfo > 900) LineValue -= 1;
    if(i == 2) if(SenseInfo > 900) LineValue += 0;
    if(i == 3) if(SenseInfo > 900) LineValue += 1;
    if(i == 4) if(SenseInfo > 900) LineValue += 2;
  }
  Serial.print(LineValue);
  Serial.print("   ");
  if(LineValue != 0){ //(어디에도 선이 감지되지 않거나 가운데에만 선이 있을 경우)<-이것이 아니면
    while(analogRead(A2) < 900){ //가운데에 선이 올 때까지 유지
      Line_Tracing(LineValue); //줄을 따라가는 함수 실행
    }
  }
  else if(LineValue == 0) basic(1);
}

void loop() { //메인 반복 함수
  LineReading(); //노란선 따라가기, 선이 없을 경우 모터제어 없음
  distance_sense(); //초음파로 벽 따라가기
}
