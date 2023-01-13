#include <IRremote.h>

#define IN1 2
#define IN2 4
#define ENL 3

#define IN3 7
#define IN4 6
#define ENR 5

#define F_Sonar 8
#define L_Sonar 9
#define R_Sonar 10

#define Obstacle 100

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
float F_Sonar_sensor(){ //전방 초음파
	float duration = 0.0;
  	float distance = 0.0;
  
  	pinMode(F_Sonar, OUTPUT);
  	digitalWrite(F_Sonar,LOW);
  	digitalWrite(F_Sonar,HIGH);
  	delay(10);
  	digitalWrite(F_Sonar,LOW);
  	
  	pinMode(F_Sonar, INPUT);
  	duration = pulseIn(F_Sonar,HIGH);
  
  	distance = (duration*340.0)/2.0/10000.0;
  	return distance;
}
float L_Sonar_sensor(){ //왼쪽 측면 초음파
	float duration = 0.0;
  	float distance = 0.0;
  
  	pinMode(L_Sonar, OUTPUT);
  	digitalWrite(L_Sonar,LOW);
  	digitalWrite(L_Sonar,HIGH);
  	delay(10);
  	digitalWrite(L_Sonar,LOW);
  	
  	pinMode(L_Sonar, INPUT);
  	duration = pulseIn(L_Sonar,HIGH);
  
  	distance = (duration*340.0)/2.0/10000.0;
  	return distance;
}
float R_Sonar_sensor(){ //왼쪽 측면 초음파
	float duration = 0.0;
  	float distance = 0.0;
  
  	pinMode(R_Sonar, OUTPUT);
  	digitalWrite(R_Sonar,LOW);
  	digitalWrite(R_Sonar,HIGH);
  	delay(10);
  	digitalWrite(R_Sonar,LOW);
  	
  	pinMode(R_Sonar, INPUT);
  	duration = pulseIn(R_Sonar,HIGH);
  
  	distance = (duration*340.0)/2.0/10000.0;
  	return distance;
}
void loop()
{
  	float F_sonar_distance = 0.0;
  	F_sonar_distance = F_Sonar_sensor();
  	float L_sonar_distance = 0.0;
  	L_sonar_distance = L_Sonar_sensor();
  	float R_sonar_distance = 0.0;
  	R_sonar_distance = R_Sonar_sensor();
  
  	Serial.print(F_sonar_distance);
  	Serial.print("     ");
  	Serial.print(L_sonar_distance);
  	Serial.print("     ");
  	Serial.println(R_sonar_distance);
  
  	if((L_sonar_distance>Obstacle) //전방에만 장애물이 있을 경우
       &&(F_sonar_distance<=Obstacle)
       &&(R_sonar_distance>Obstacle)){
    	motor_control(-1,50,1,50);
      	delay(1000);
    	motor_control(1,100,1,100);
    }
  	if((L_sonar_distance<=Obstacle) //왼쪽과 전방에 장애물
       &&(F_sonar_distance<=Obstacle)
       &&(R_sonar_distance>Obstacle)){
    	motor_control(1,50,-1,50);
      	delay(1000);
    	motor_control(1,100,1,100);
    }
    if((L_sonar_distance>Obstacle) //오른쪽과 전방에 장애물
       &&(F_sonar_distance<=Obstacle)
       &&(R_sonar_distance<=Obstacle)){
    	motor_control(-1,50,1,50);
      	delay(1000);
    	motor_control(1,100,1,100);
    }
    if((L_sonar_distance<=Obstacle) //삼방향 전부에 장애물
       &&(F_sonar_distance<=Obstacle)
       &&(R_sonar_distance<=Obstacle)){
    	motor_control(-1,50,-1,50);
      	delay(2000);
    	motor_control(-1,50,1,50);
      	delay(1000);
    	motor_control(1,100,1,100);
    }
    else motor_control(1,100,1,100);
    //motor_control(1,100,1,100); 
}