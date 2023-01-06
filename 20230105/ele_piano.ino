// C++ code
//
int tones[] = {523,587,659,698,784,880,988,1046};
int school_bell_melody[] = { 4,4,5,5,4,4,2,4,4,2,2,1 };
int school_bell_melody2[] = { 4,4,5,5,4,4,2,4,2,1,2,0 };
int school_bell_wait[] = { 300,300,300,300,300,300,600,300,300,300,300,600 };


void setup()
{
  pinMode(13, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  
}

void loop()
{
  int input = 0;
  input = digitalRead(2);
  Serial.println(input);
  
  input = digitalRead(2);
  if(input == HIGH){
  	tone(12,tones[0],500);
    delay(600);
  }  
  
  input = digitalRead(2);
  if(input == HIGH){
  	tone(12,tones[0],500);
    delay(600);
  }
  
  input = digitalRead(3);
  if(input == HIGH){
  	tone(12,tones[1],500);
    delay(600);
  }
  
  input = digitalRead(4);
  if(input == HIGH){
  	tone(12,tones[2],500);
    delay(600);
  }
  
  input = digitalRead(5);
  if(input == HIGH){
  	tone(12,tones[3],500);
    delay(600);
  }
  
  input = digitalRead(6);
  if(input == HIGH){
  	tone(12,tones[4],500);
    delay(600);
  }
  
  input = digitalRead(7);
  if(input == HIGH){
  	tone(12,tones[5],500);
    delay(600);
  }
  
  input = digitalRead(8);
  if(input == HIGH){
  	tone(12,tones[6],500);
    delay(600);
  }
  
  
  
}


//피에조 스피커 : 전류를 가하면 진동하며 소리 생성
//헤르츠 상승 = 높은 음