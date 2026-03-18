//Task: 7-segment
const int segmentA = 3;
const int segmentB = 2;
const int segmentC = 8;
const int segmentD = 7;
const int segmentE = 6;
const int segmentF = 4;
const int segmentG = 5;

const int PushBut1 = 11;
const int PushBut2 = 12;

int PB1Count = 0;
int PB1State = 0;
int LastPB1State = 0;

int PB2Count = 0;
int PB2State = 0;
int LastPB2State = 0;

void setup(){
  Serial.begin(9600);

  pinMode(PushBut1, INPUT_PULLUP);
  pinMode(PushBut2, INPUT_PULLUP);

  pinMode(segmentA, OUTPUT);
  pinMode(segmentB, OUTPUT);
  pinMode(segmentC, OUTPUT);
  pinMode(segmentD, OUTPUT);
  pinMode(segmentE, OUTPUT);
  pinMode(segmentF, OUTPUT);
  pinMode(segmentG, OUTPUT);

  digitalWrite(segmentA, HIGH);
  digitalWrite(segmentB, HIGH);
  digitalWrite(segmentC, HIGH);
  digitalWrite(segmentD, HIGH);
  digitalWrite(segmentE, HIGH);
  digitalWrite(segmentF, HIGH);
  digitalWrite(segmentG, HIGH);
}

void loop(){
  Serial.println(PB1Count);
  delay(1000);

  PB1State = digitalRead(PushBut1);
  PB2State = digitalRead(PushBut2);

  if(PB1State != LastPB1State){
    if(PB1State == LOW){
      PB1Count++;
    }
    delay(50);
  }

  if(PB2State != LastPB2State){
    if(PB2State == LOW){
      PB1Count = 0;
    }
    delay(50);
  }

  LastPB1State = PB1State;
  LastPB2State = PB2State;

  if(PB1Count == 0){
    r();
    seg0();
  }

  if(PB1Count == 1){
    r();
    seg1();
  }

  if(PB1Count == 2){
    r();
    seg2();
  }

  if(PB1Count == 3){
    r();
    seg3();
  }

  if(PB1Count == 4){
    r();
    seg4();
  }

  if(PB1Count == 5){
    r();
    seg5();
  }

  if(PB1Count == 6){
    r();
    seg6();
  }

  if(PB1Count == 7){
    r();
    seg7();
  }

  if(PB1Count == 8){
    r();
    seg8();
  }

  if(PB1Count == 9){
    r();
    seg9();
  }
}

void r(){
  digitalWrite(segmentA, HIGH);
  digitalWrite(segmentB, HIGH);
  digitalWrite(segmentC, HIGH);
  digitalWrite(segmentD, HIGH);
  digitalWrite(segmentE, HIGH);
  digitalWrite(segmentF, HIGH);
  digitalWrite(segmentG, HIGH);
}

void seg0(){
  //0
  digitalWrite(segmentA, LOW);
  digitalWrite(segmentB, LOW);
  digitalWrite(segmentC, LOW);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, LOW);
}

void seg1(){
  //1
  digitalWrite(segmentB, LOW);
  digitalWrite(segmentC, LOW);
}

void seg2(){
  //2
  digitalWrite(segmentA, LOW);
  digitalWrite(segmentB, LOW);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentG, LOW);
}

void seg3(){
  //3
  digitalWrite(segmentA, LOW);
  digitalWrite(segmentB, LOW);
  digitalWrite(segmentC, LOW);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentG, LOW);
}

void seg4(){
  //4
  digitalWrite(segmentB, LOW);
  digitalWrite(segmentC, LOW);
  digitalWrite(segmentF, LOW);
  digitalWrite(segmentG, LOW);
}

void seg5(){
  //5
  digitalWrite(segmentA, LOW);
  digitalWrite(segmentC, LOW);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentF, LOW);
  digitalWrite(segmentG, LOW);
}

void seg6(){
  //6
  digitalWrite(segmentA, LOW);
  digitalWrite(segmentC, LOW);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, LOW);
  digitalWrite(segmentG, LOW);
}

void seg7(){
  //7
  digitalWrite(segmentA, LOW);
  digitalWrite(segmentC, LOW);
}

void seg8(){
  //8
  digitalWrite(segmentA, LOW);
  digitalWrite(segmentB, LOW);
  digitalWrite(segmentC, LOW);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, LOW);
  digitalWrite(segmentG, LOW);
}

void seg9(){
  //9
  digitalWrite(segmentA, LOW);
  digitalWrite(segmentC, LOW);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, LOW);
  digitalWrite(segmentG, LOW);
}
