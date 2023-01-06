// C++ code
//
void setup()
{
  int waiting=500;
  int i;
  
  for(i=2;i<=8;i++){
  	pinMode(i,OUTPUT);
  }
}

void loop()
{
  int i;
  for(i=2;i<=8;i++){
  	digitalWrite(i, HIGH);
    delay(200);
  }
  
  for(i=2;i<=8;i++){
  	digitalWrite(i, LOW);
  	delay(200);
  }
}



//옴의 법칙 = V = IR
// R = 저항 , V = 전압 , I = 전류