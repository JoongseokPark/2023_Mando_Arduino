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
float R_Sonar_sensor(){ //오른쪽 측면 초음파
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
    float F_sonar_distance = 0.0;
    F_sonar_distance = F_Sonar_sensor();
    float L_sonar_distance = 0.0;
    L_sonar_distance = L_Sonar_sensor();
    float R_sonar_distance = 0.0;
    R_sonar_distance = R_Sonar_sensor();
    
    Serial.print(F_sonar_distance);
    Serial.print("     ");
    Serial.print(R_sonar_distance);
    Serial.print("     ");
    Serial.println(L_sonar_distance);
  
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
