#include<Servo.h>
#include<SoftwareSerial.h>

const int trigPin = 10;
const int echoPin = 9;
const int buzzPin = 2;

Servo servo;

int input;

const int A1P = 11;//define pin 2 for A1P
const int A1N = 12;//define pin 3 for A1N

//const int B1P = 11;//define pin 8 for B1P
//const int B1N = 12;//define pin 9 for B1N

int angle;

void setup() {
  Serial.begin(9600);
  servo.attach(9);
  
  pinMode(trigPin, OUTPUT);//Ultra
  pinMode(echoPin, INPUT);//Ultra
  pinMode(buzzPin, OUTPUT); // buzz pin is output to control buzzering
  
}


void loop() {
  motorForward();
 
//  input = getInput
  
//  int distance = getDistanceInCM();
//  if(checkObstacle(distance))
//  {
//    executeCommand(input);
//  }

//  buZul();
}

int getInput()//get input From serial port
{
  int recieved;
  if(Serial.available())
  {
     recieved = Serial.read();
  }
  return recieved;

  
}

//bool checkObstacle(int distance)//check if there is an obstacle in between
//{
//  if(distance < 20)
//  {
//    return true;
//  }
//  return false;
//}
//
//int getDistanceInCM()//get distance from ultrasonic sensor
//{
//  digitalWrite(trigPin, LOW); 
//  delayMicroseconds(2); 
//
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10); 
// 
//  digitalWrite(trigPin, LOW);
//  int duration = pulseIn(echoPin, HIGH);
// 
//  int distance = duration/58.2; //Calc distance (in cm) 
//
//  return distance;
//}

int executeCommand(int command)
{ 
  switch (command)
  {
    case '1': 
      motorForward(); //start both motors A and B
      delay(500);
      motorStop();
      break;

    case '2':  
      motorBackward();
      delay(500);
      motorStop();
      break;


   case '3': 
      servo.write(45);//right
      break;
    
    case '4':  
      servo.write(90);//go straight
      break;
      
    case '5':  
      servo.write(135);//move right
      break;
      
    default:{
      break;
      }
  }
  return 0;
}


void motorForward()// Forward direction
{
    digitalWrite(A1P,LOW);
    digitalWrite(A1N,HIGH);
    //digitalWrite(B1P,LOW);
    //digitalWrite(B1N,HIGH);
}   
  

void motorBackward()// Backward direction
{
    digitalWrite(A1P,HIGH);
    digitalWrite(A1N,LOW);
   // digitalWrite(B1P,HIGH);
   // digitalWrite(B1N,LOW);    
}


void motorStop()// Stop
{
    digitalWrite(A1P,LOW);
    digitalWrite(A1N,LOW);
   // digitalWrite(B1P,LOW);
   // digitalWrite(B1N,LOW);
}


//--------------------------------------
void buZul(){
  long duration, inches, cm, distance;
// Duration will be the input pulse width and distance will be the distance to the obstacle in centimeters

// Output pulse with 1ms width on trigPin
digitalWrite(trigPin, HIGH);
delay(1);
digitalWrite(trigPin, LOW);
// Measure the pulse input in echo pin
duration = pulseIn(echoPin, HIGH);
// Distance is half the duration devided by 29.1 (from datasheet)
distance = (duration/2) / 29.1;
// if distance less than 0.5 meter and more than 0 (0 or less means over range)
if (distance <= 30 && distance >= 0) {
// Buzz
digitalWrite(buzzPin, LOW);
Serial.print("Danger");} else {
// Don't buzz
digitalWrite(buzzPin, HIGH);

}
pinMode(trigPin,OUTPUT);
pinMode(echoPin, INPUT);
  
cm = microsecondsToCentimeters(duration);

Serial.print(cm);
Serial.print("cm");
Serial.println();
// Waiting 60 ms won't hurt any one
delay(60);
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
