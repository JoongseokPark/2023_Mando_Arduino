#include <IRremote.h>

#define IN1 2
#define IN2 4
#define ENL 9

#define IN3 7
#define IN4 6
#define ENR 5

IRrecv ir_recv(10); //적외선 센서 핀 번호
decode_results results; //수신된 적외선 신호 저장 변수

void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENL, OUTPUT);
  
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENR, OUTPUT);
  ir_recv.enableIRIn();
  Serial.begin(9600);
}

void motor_control(int dir_1,int speed_1,int dir_r,int speed_r){
  //왼쪽 모터 제어
  if(dir_1 == 1){
  	digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    analogWrite(ENL,speed_1);
  }
  else if(dir_1 == -1){
 	digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    analogWrite(ENL,speed_1);
  }
  else{
  	digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    analogWrite(ENL,0);
  }
  //오른쪽 모터 제어
  if(dir_r == 1){
  	digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    analogWrite(ENR,speed_r);
  }
  else if(dir_r == -1){
 	digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    analogWrite(ENR,speed_r);
  }
  else{
  	digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
    analogWrite(ENR,0);
  }
}

void loop()
{
  if(ir_recv.decode(&results)){
  	Serial.println(results.value);
    delay(30);
    ir_recv.resume();
    if(results.value == 16593103 ){ //0번 전진
    	motor_control(1,100,1,100);
    }
    else if(results.value == 16623703){ //5번 중지
    	motor_control(0,100,0,100); 
    }
    else if(results.value == 16603303){ //9번 후진
    	motor_control(-1,100,-1,100); 
    }
    else if(results.value == 16591063){ //4번 시계방향
    	motor_control(-1,50,1,50); 
    }
    else if(results.value == 16607383){ //6번 반시계방향
    	motor_control(1,50,-1,50); 
    }
    else motor_control(0,100,0,100);
  }
}