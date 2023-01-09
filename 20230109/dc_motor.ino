// C++ code
//
void setup()
{
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

}

void loop()
{
  digitalWrite(4, LOW); //LOW와 HIGH를 바꾸어 모터 방향 조정
  digitalWrite(5, HIGH);
  analogWrite(3,100); //0~255 값으로 속도 조절
  
  delay(1500);
  
  
}

/*

	직류모터
    전류의 방향에 따라 정방향 구동, 역방향 구동이 바뀐다.
    -> +와 -의 방향이 바뀜

*/