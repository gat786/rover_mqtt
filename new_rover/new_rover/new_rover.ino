const int APositive=11;
const int ANegative=12;
const int BPositive=8;
const int BNegative=13;

int const Trigpin = 10;
int const Echopin = 9;
int const Buzzpin = 2;

void setup() {
  Serial.begin(9600);
  pinMode(APositive,OUTPUT);
  pinMode(ANegative,OUTPUT);

  
  pinMode(BPositive,OUTPUT);
  pinMode(BNegative,OUTPUT);
  
  pinMode(Trigpin,OUTPUT);
  pinMode(Echopin,INPUT);
  pinMode(Buzzpin,OUTPUT);
}

int recieved=0;

void loop() {
  buzzer();
}

void getAhead(){
  moveForward();
  delay(500);
  stopMoving();
}


void getBack(){
  moveBackward();
  delay(500);
  stopMoving();
}

void moveForward(){
  //first wheel
  digitalWrite(APositive,HIGH);
  digitalWrite(ANegative,LOW);

  //second wheel
  digitalWrite(BPositive,HIGH);
  digitalWrite(BNegative,LOW);
}

void moveBackward(){
  //first wheel
  digitalWrite(APositive,LOW);
  digitalWrite(ANegative,HIGH);

  //second wheel
  digitalWrite(BPositive,LOW);
  digitalWrite(BNegative,HIGH);
}

void stopMoving(){
  //first wheel
  digitalWrite(APositive,LOW);
  digitalWrite(ANegative,LOW);
  //second wheel
  digitalWrite(BPositive,LOW);
  digitalWrite(BNegative,LOW);
}

void buzzer()
{
  // Duration will be the input pulse width and distance will be the distance to the obstacle in centimeters
  int duration, distance;
  // Output pulse with 1ms width on Trigpin
  digitalWrite(Trigpin, HIGH);
  delay(1);
  digitalWrite(Trigpin, LOW);
  // Measure the pulse input in echo pin
  duration = pulseIn(Echopin, HIGH);
  // Distance is half the duration devided by 29.1 (from datasheet)
  distance = (duration/2) / 29.1;
  
  // if distance less than 0.5 meter and more than 0 (0 or less means over range)
  if (distance <= 20 && distance >= 0) {
    // Buzz
    digitalWrite(Buzzpin, LOW);
    Serial.write("yes \n");
    moveBackward();
    delay(50);
  } 
  else 
  {
    stopMoving();

    // Don't buzz
    while(Serial.available()>0){
      recieved = Serial.read();
      Serial.write(recieved);
      switch(recieved){
        case '1':
          getAhead();
          break;
        case '2':
          getBack();
          break;
        default:{
          break;
        }
      }
    }
    digitalWrite(Buzzpin, HIGH);
  }
    // Waiting 60 ms won't hurt any one
    delay(50);
}
