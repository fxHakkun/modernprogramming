#include <SoftwareSerial.h>

//left1,right1 = forward, left2,right2 = backward
const int left1 = 8, left2 = 7, right1 = 4, right2 = 2;
//using pin 6,5 for PWM
const int en1 = 6, en2 = 5;
//input for PWM
int input;
//duration adjustable for turn to right or left
const int tempoh = 500;
SoftwareSerial hc06(10, 11); //Rx,Tx

void setup() {
  
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  Serial.begin(9600);
  hc06.begin(9600);
  input = 255;
  //remove jumper on enable to control PWM, enabling Fast and Slow
  //use jumper for default 5v
  analogWrite(en1, input);
  analogWrite(en2, input);
 
}

void loop() {
int data;

  if (hc06.available()) 
  {
    
    //Serial.print(hc06.read(),char(data));
    data = hc06.read();
    
    if (data == 0x31)
    {
      Forward();
    }
    else if (data == 0x32)
    {
      Backward();
    }
    else if (data == 0x33)
    {
      RightForward();
    }
    else if (data == 0x34)
    {
      LeftForward();
    }
    else if (data == 0x35)
    {
      Stop();
    }
    else if (data == 0x36)
    {
      RotateLeft();
    }
    else if (data == 0x37)
    {
      RotateRight();
    }
    else if (data == 0x38)
    {
      LeftBackward();
    }
    else if (data == 0x39)
    {
      RightBackward();
    }
    else if (data == 0x2B)
    {
      Fast();
    }
    else if (data == 0x2D)
    {
      Slow();
    }
   
  }
}

//setup mode, left1 = left2 or right1 = right2 means Stop
//left1 > left2 and right1 > right2 to move forward

void Forward(){
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);
}

void Backward(){
  digitalWrite(left1, LOW);
  digitalWrite(left2, HIGH);
  digitalWrite(right1, LOW);
  digitalWrite(right2, HIGH);
}

void LeftForward(){
  digitalWrite(left1, LOW);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);
  delay(tempoh);
  Stop();
}

void LeftBackward(){
  digitalWrite(left1, LOW);
  digitalWrite(left2, HIGH);
  digitalWrite(right1, LOW);
  digitalWrite(right2, LOW);
  delay(tempoh);
  Stop();
}

void RightForward(){
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, LOW);
  digitalWrite(right2, LOW);
  delay(tempoh);
  Stop();
}

void RightBackward(){
  digitalWrite(left1, LOW);
  digitalWrite(left2, LOW);
  digitalWrite(right1, LOW);
  digitalWrite(right2, HIGH);
  delay(tempoh);
  Stop();
}

void RotateLeft(){
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, LOW);
  digitalWrite(right2, HIGH);
}

void RotateRight(){
  digitalWrite(left1, LOW);
  digitalWrite(left2, HIGH);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);
}

void Stop(){
  digitalWrite(left1, LOW);
  digitalWrite(left2, LOW);
  digitalWrite(right1, LOW);
  digitalWrite(right2, LOW);
}

void Slow(){
  analogWrite(en1 , input);
  analogWrite(en2 , input);
  input -= 50;
  if (input < 0){
    input = 0;
  }
}

void Fast(){
  analogWrite(en1 , input);
  analogWrite(en2 , input);
  input += 50;
  if (input > 255){
    input = 255;
  }
}
