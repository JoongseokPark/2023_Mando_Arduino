// C++ code
//
void setup()
{
  pinMode(13, OUTPUT); //13번 핀이 출력
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(13, HIGH); //13번 핀 출력 high
  Serial.println("LED ON");
  delay(3000); // Wait for 1000 millisecond(s)
  
  Serial.println("LED OFF");
  digitalWrite(13, LOW); //13번 핀 출력 low
  delay(3000); // Wait for 1000 millisecond(s)
  
}