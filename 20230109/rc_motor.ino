#include <Servo.h>

Servo servo;

void setup()
{
  servo.attach(2);
  Serial.begin(9600);
}

void loop()
{
  int ad_in = 0;
  int anlge = 0;
  ad_in = analogRead(A0);
  
  Serial.println(ad_in);
  
  anlge = map(ad_in,0,1023,0,180);
  servo.write(anlge);
  delay(1500); 
}


/*
	작동기는 모터와 같이 전기적 신호를 
    사용하여 기계를 움직이는 장치

*/