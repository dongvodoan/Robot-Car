#include <Servo.h>
String data;

// Enable Motor
int Motor_Enable = 2;

// Motor A
int Motor_A_Reverse = 10; 
int Motor_A_Forward = 11; 

// Motor B
int Motor_B_Reverse = 12;   
int Motor_B_Forward = 13;

// Pin Led
int Pin_Led = 8;

// Servo control hand shift Left or Right 
Servo servo1;

// Servo control hand shift Up or Down
Servo servo2;

Servo servo;

//Set start degrees of servo 1
int i=90;

// Set start degrees of serrvo 2
int j=90;

int Degrees;

// Servo 1 Pin Init
int servo_Pin_1 = 6;

// Servo 2 Pin Init
int servo_Pin_2 = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(Motor_Enable, OUTPUT);
  pinMode(Motor_A_Forward, OUTPUT);
  pinMode(Motor_A_Reverse, OUTPUT);

  pinMode(Motor_B_Forward, OUTPUT);
  pinMode(Motor_B_Reverse, OUTPUT);

  pinMode(Pin_Led, OUTPUT);

  servo1.attach(servo_Pin_1);

  servo2.attach(servo_Pin_2);
}

// Function stop car
void Stop(){
        analogWrite(Motor_Enable, 0); 
        digitalWrite(Motor_A_Reverse, LOW);
        digitalWrite(Motor_A_Forward, LOW);
        digitalWrite(Motor_B_Reverse, LOW);
        digitalWrite(Motor_B_Forward, LOW);
  }

// Function Forward car
void Forward(){
        analogWrite(Motor_Enable,200); 
        digitalWrite(Motor_A_Reverse, LOW);
        digitalWrite(Motor_A_Forward, HIGH); 
        digitalWrite(Motor_B_Reverse, LOW);
        digitalWrite(Motor_B_Forward, HIGH);
  }

// Function Reverse car
void Reverse(){
        analogWrite(Motor_Enable, 150);
        digitalWrite(Motor_A_Reverse, HIGH);
        digitalWrite(Motor_A_Forward, LOW);
        digitalWrite(Motor_B_Reverse, HIGH);
        digitalWrite(Motor_B_Forward, LOW);
  }
  
// Function turnleft car
void turnLeft(){
        analogWrite(Motor_Enable, 150);
        digitalWrite(Motor_A_Reverse, LOW);
        digitalWrite(Motor_A_Forward, HIGH);
        digitalWrite(Motor_B_Reverse, HIGH);
        digitalWrite(Motor_B_Forward, LOW);
  }

// Function turnright car 
void turnRight(){
        analogWrite(Motor_Enable, 150);
        digitalWrite(Motor_A_Reverse, HIGH);
        digitalWrite(Motor_A_Forward, LOW);
        digitalWrite(Motor_B_Reverse, LOW);
        digitalWrite(Motor_B_Forward, HIGH);
  }

// Function turn on light
void turnOn(){
  digitalWrite(Pin_Led, HIGH);
  }

// Function turn off light
void turnOff(){
  digitalWrite(Pin_Led, LOW);
  }

//count up from Degrees->max
void countUp(int max){
  while(Degrees<max){
  Degrees++;
  servo.write(Degrees);
  Serial.print(Degrees);
  delay(75);
  char c = Serial.read();
  if(c=='S') break;
  }
}

//count down from Degrees->min
void countDown(int min){
  while(Degrees>min){
  Degrees--;
  servo.write(Degrees);
  Serial.print(Degrees);
  delay(75);
  char c = Serial.read();
  if(c=='S') break;
  }
}

// Function Shift right the Hand
void Left(){
  Degrees=i;
  servo=servo1;
  countUp(180);
  i=Degrees;
}

// Function Shift left the Hand
void Right(){
  Degrees=i;
  servo=servo1;
  countDown(0);
  i=Degrees;
}

// Function Shift Up the hand
void Up(){
  n=j;
  servo=servo2;
  countUp(110);
  j=n;
}

// Function Shift Down the hand
void Down(){
  n=j;
  servo=servo2;
  countDown(55);
  j=n;
}

// Function handle command
void handleCommand(String command){
  // Control lights
  if(command=="On"){     
      turnOn();                                     // Turn on Lights
  }
  else if(command=="Off"){
      turnOff();                                    // Turn off Lights
  }
  
  // Drive Car
  if(command=="Forward"){
      Forward();                                    // go to Forward
  }
  else if(command=="Backward"){
      Reverse();                                    // go to Backward
  }
  else if(command=="TLeft"){
     turnLeft();                                    // go to Forward Left
  }
  else if(command=="TRight"){
     turnRight();                                   // go to Forward Left
  }
  // Control Hand
  else if(command=="Left"){                         // shift left
    Left();
    }
  else if(command=="Right"){                        // shift right
    Right();
    }
  else if(command=="Up"){                           // shift up
    Up();
    }
  else if(command=="Down"){                         // shift down
    Down();
    }
  else if(command=="Stop"){                         // Stop working
    Stop();                                    
    }
}  
  
void loop() {
    while(Serial.available())
    { 
      char c = Serial.read();                       // listeing data send to
      data+=c;                                      // add string
      delay(2);                                     // delay 2ms
    }
    if(data.length()>0){
      Serial.println(data);
      handleCommand(data);                          // run function handle command
      }
      data="";                                      // clear string
}
