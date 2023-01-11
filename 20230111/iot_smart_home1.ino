#include <IRremote.h>

IRrecv ir_recv(10);
decode_results results;

// C++ code
//
void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);
  ir_recv.enableIRIn(); //적외선 센서 수신 활성화
  Serial.begin(9600);
}

void loop()
{
  int cds_sensor_value = 0;
  int PIR_sensor_value = 0;
  int temp_sensor_value = 0;
  int gas_sensor_value = 0;
  float temp = 0.0;
  
  cds_sensor_value = analogRead(A0);
  temp_sensor_value = analogRead(A1);
  gas_sensor_value = analogRead(A2);
  PIR_sensor_value = digitalRead(4);
  
  temp = temp_sensor_value*5.0/1024.0;
  temp = (temp-0.5)*100.0;
  
  //Serial.println(PIR_sensor_value);
  //Serial.println(temp);
  Serial.println(gas_sensor_value);
  if(gas_sensor_value > 80){
  	tone(5,600,1000);
    delay(1000);
  }
  else noTone(5);
  
  if(PIR_sensor_value == 1)digitalWrite(2,HIGH);
  if(PIR_sensor_value == 0)digitalWrite(2,LOW);
  
  if(temp <= 10)digitalWrite(3,HIGH);
  else digitalWrite(3,LOW);
  /*
  if(ir_recv.decode(&results)){
  	Serial.println(results.value);
    delay(30);
    ir_recv.resume();
  }
  
  if(results.value == 16593103){ //0 입력
    digitalWrite(2,HIGH);
    delay(1000);
  }  
  if(results.value == 16615543){ //2 입력
    digitalWrite(2,LOW);
    delay(2000);
  }
  
  
  if( cds_sensor_value < 200){ //밝기 수신에 따라 키고 끔
  	 digitalWrite(2, HIGH);
  	 delay(1000); // Wait for 1000 millisecond(s)
  }
  else {
  	digitalWrite(2, LOW);
    delay(1000); // Wait for 1000 millisecond(s)
  }	
  */
}

// 딜레이 = 낮은 전압으로 높은 전압 제어
// 딜레이는 내부의 코일을 이용하여 접점을 움직임
// 기호 : NC = normal close, NO = normal open

// PIR 센서 : 움직임을 적외선으로 감지

// 온도 센서 : -40~125도까지 측정 가능 
// 온도에 따른 전압 변화를 통해 측정 
