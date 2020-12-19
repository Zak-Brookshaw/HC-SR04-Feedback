int trigPin = 4;
int echoPin = 3;
int readPin = A0;



unsigned long timer = 0;
unsigned long timer_o = 0;
unsigned long limit = 2*1000;  // miliseconds between trigger pull
unsigned long wait_limit = 3*1000;
unsigned long wait_time = 0;
bool doit = false;
int trys = 0;

volatile unsigned long count = 0;
volatile unsigned long count_o = 0;



void setup() {
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(readPin, INPUT);
  Serial.begin(9600);
//  attachInterrupt(digitalPinToInterrupt(echoPin), start, RISING);
//  attachInterrupt(digitalPinToInterrupt(echoPin), ending, FALLING);
}

void loop() {
  
  timer = millis() - timer_o;
  
  if (timer > limit){
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    count = 0;
  }
  
  while(trys < 1000){
    if (digitalRead(echoPin)){
      count_o = micros();
      while(digitalRead(echoPin)){
      }
      count = micros() - count_o;
      break;
    }
    trys+=1;
  }

  Serial.println((float)count/58.0);
  trys = 0;
}

void start(){
  doit = true;
}
