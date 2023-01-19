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

#define Circle 1200 //100의 속도로 양쪽 바퀴가 반대로 돌 때 180도 회전에 걸리는 시간
#define Speed 150 //모터 기본 속도

int is_there_line=1; //선이 있는지 확인하는 변수

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
  
  if(dir_1 == -1){ 
    Serial.print("LEFT ON");
    Serial.print("   ");
  }
  else if(dir_1 == 1){
    Serial.print("LEFT BACK");
    Serial.print("   ");
  }
  else{
    Serial.print("LEFT OFF");
    Serial.print("   ");
  }
  if(dir_r == -1){ 
    Serial.print("RIGHT ON");
    Serial.print("   ");
  }
  else if(dir_r == 1){
    Serial.print("RIGHT BACK");
    Serial.print("   ");
  }
  else{
    Serial.print("RIGHT OFF");
    Serial.print("   ");
  }
  
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
int distance_sense(){ //초음파로 거리 감지 후 모터 제어 함수

  Serial.print(sonar[0].ping_cm()); //시리얼 모니터에 거리 출력
  Serial.print("   ");
  Serial.print(sonar[2].ping_cm());
  Serial.print("   ");
  Serial.print(sonar[1].ping_cm());
  Serial.print("   ");

  if(sonar[0].ping_cm() > 5 &&sonar[0].ping_cm() < 32){ //전방 장애물이 나타났을 경우
    //어느 방향이 더 열려있는지 확인
    if(sonar[2].ping_cm()>0 && sonar[2].ping_cm() < sonar[1].ping_cm()){
      basic(4); //그 방향으로 회전
      delay(500);
    }
    else if(sonar[1].ping_cm()>0 && sonar[1].ping_cm() < sonar[2].ping_cm()){
      basic(3); //그 방향으로 회전
      delay(500);
    }
  }
  else { //전방 장애물이 없을 경우
    if(sonar[2].ping_cm()>0 && sonar[2].ping_cm()< 20) movement(-1,150,-1,100); //왼쪽이 가까우면 속도 변환
    else if(sonar[1].ping_cm()>0 &&sonar[1].ping_cm()< 20)movement(-1,100,-1,150); //오른쪽이 가까우면 속도 변환
  }
  if(analogRead(A0) > 900||analogRead(A1) > 900||analogRead(A2) > 900||
  analogRead(A3) > 900||analogRead(A4) > 900){
    is_there_line = 1; //조건 달성 시 선 따라가기로 변경
    return 0;
  }
  is_there_line = 0;
  return 1;
}


void Line_Tracing(int Value){ //줄 따라가기 이동 단축
  if(Value < 0) movement(0,Speed,-1,-Value*Speed);
  else if(Value > 0) movement(-1,Value*Speed,0,Speed);
  Serial.println("   ");
}

int SenseInfo = 0; //5개 센서 값 저장 변수
int LineReading(){ //줄 따라가는 함수
  if(analogRead(A0) > 900||analogRead(A1) > 900||analogRead(A2) > 900||
  analogRead(A3) > 900||analogRead(A4) > 900){is_there_line = 1;}
  int Line_exist = 0; 
  int LineValue = 0; //선의 위치를 판단하는 변수
  int late = 0;
  for(int i=0;i<5;i++){
    SenseInfo = analogRead(A0+i); //변수에 감지 값 저장
    Serial.print(analogRead(A0+i));
    if(i == 0) if(SenseInfo > 900) LineValue -= 2; //각 센서에 노란색 감지시 값 변화
    if(i == 1) if(SenseInfo > 900) LineValue -= 1;
    if(i == 2) if(SenseInfo > 900) LineValue += 0;
    if(i == 3) if(SenseInfo > 900) LineValue += 1;
    if(i == 4) if(SenseInfo > 900) LineValue += 2;
    if(SenseInfo < 100) Line_exist += 1;
    Serial.print("   ");
  }
  
  Serial.print(LineValue);
  Serial.print("   ");
  if(Line_exist >= 5){ 
    Serial.print("no line");
    Serial.print("   ");
  }
  
  if(Line_exist >= 5) is_there_line = 0;
  else is_there_line = 1;
  if(LineValue != 0){ //(어디에도 선이 감지되지 않거나 가운데에만 선이 있을 경우)<-이것이 아니면
    while(analogRead(A2) < 900){ //가운데에 선이 올 때까지 유지 
      Line_Tracing(LineValue); //줄을 따라가는 함수 실행
      late++;
      if(late>20) break;
    }
  }
  while(sonar[0].ping_cm()<= 15) basic(0);
  return 1;
}
int tracing_line = 0;
int where_is_wall = 0;
void loop() { //메인 반복 함수
  if(is_there_line == 1){
    tracing_line = LineReading(); //노란선 따라가기, 선이 없을 경우 모터제어 없음
    basic(tracing_line);
  }
  else if(is_there_line == 0) {
    where_is_wall = distance_sense(); //초음파로 벽 따라가기
    basic(where_is_wall);
  }
  Serial.print(is_there_line);
  Serial.println(" ");
}
