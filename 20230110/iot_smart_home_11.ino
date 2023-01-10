#include <IRremote.h>

IRrecv ir_recv(10);
decode_results results;

// C++ code
//
void setup()
{
  pinMode(2, OUTPUT);
  ir_recv.enableIRIn(); //적외선 센서 수신 활성화
  Serial.begin(9600);
}

void loop()
{
  int cds_sensor_value = 0;
  
  cds_sensor_value = analogRead(A0);
  //Serial.println(cds_sensor_value);
  
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
}

// 딜레이 = 낮은 전압으로 높은 전압 제어
// 딜레이는 내부의 코일을 이용하여 접점을 움직임
// 기호 : NC = normal close, NO = normal open