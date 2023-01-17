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

void loop() {
  basic(1);
  delay(Circle);
  basic(2);
  delay(Circle);
  basic(3);
  delay(Circle/2);
  basic(4);
  delay(Circle/2);
  basic(5);
  delay(Circle);
}
