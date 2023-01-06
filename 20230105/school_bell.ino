// C++ code
//
int tones[] = {523,587,659,698,784,880,988,1046};
int school_bell_melody[] = { 4,4,5,5,4,4,2,4,4,2,2,1 };
int school_bell_melody2[] = { 4,4,5,5,4,4,2,4,2,1,2,0 };
int school_bell_wait[] = { 300,300,300,300,300,300,600,300,300,300,300,600 };


void setup()
{
  pinMode(13, OUTPUT);
}

void loop()
{
	tone(13,tones[0],500); //13번 핀, 523hz로 500ms동안 연주
  	delay(1000);	  // 1초 지연
  
  for(int i=0;i<8;i++){
  	tone(13,tones[i],200);
    delay(200);
  }
  
  for(int i=0;i<12;i++){
	tone(13,school_bell_melody[i],school_bell_wait[i]);
  }
  delay(1000);
    for(int i=0;i<12;i++){
	tone(13,school_bell_melody2[i],school_bell_wait[i]);
  }
  delay(1000);
}


//피에조 스피커 : 전류를 가하면 진동하며 소리 생성
//헤르츠 상승 = 높은 음