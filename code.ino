#define motor1pin1 2  // Motor A IN1 pin
#define motor1pin2 3  // Motor A IN2 pin
#define motor2pin1 4  // Motor B IN1 pin
#define motor2pin2 5  // Motor B IN2 pin
// #define EN_A  9  //  Motor A enable pin
// #define EN_B  10 // Motor B enable pin
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
#include <arduino-timer.h>
// #define huskyLens1 0 // huskyLens pin 1
// #define huskyLens2 1 // huskyLens pin 2
auto timer = timer_create_default();
SoftwareSerial mySerial(10, 11);

// char cC = "rock";
int cC;//current choice rock = 1, scissors = 2, paper = 3
HUSKYLENS huskylens;

void printResult(HUSKYLENSResult result){
    if (result.command == COMMAND_RETURN_BLOCK){
        Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
    }
    else if (result.command == COMMAND_RETURN_ARROW){
        Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
    }
    else{
        Serial.println("Object unknown!");
    }
}
int getValue(HUSKYLENSResult result){
  if(result.ID == 1|| result.ID == 4|| result.ID == 7|| result.ID == 10) {
    return 1;
  }
  else if (result.ID == 2 || result.ID == 5 || result.ID == 8 || result.ID == 11) {
    return 2;
  }
  else if (result.ID == 3|| result.ID == 6|| result.ID == 9|| result.ID == 12) {
    return 3;
  }
  else {
    return 4;
  }
}

void sense(HUSKYLENSResult result)
{
  if(getValue(result) == 1){
    if(cC == 1){
      Serial.print("You Tied. \T");
      //white light
    }
    else if(cC == 3){
      //red light
      Serial.print("You Lose Try Again. \T");
    }
    else{
      //green light
      Serial.print("You Won YAY!. \T");
    }

  }
  else if(getValue(result) == 3){
    if(cC == 1){
      //green light
      Serial.print("You Won YAY!. \T");
    }
    else if(cC == 3){
      //white light
      Serial.print("You Tied. \T");
    }
    else{
      //red light
      Serial.print("You Lose Try Again. \T");
    }
  }
  else if (getValue(result) == 2){
    if(cC == 1){
      //red light
      Serial.print("You Lose Try Again. \T");
    }
    else if(cC == 3){
      //green light
      Serial.print("You Won YAY!. \T");
    }
    else{
      //white light
      Serial.print("You Tied. \T");
    }
  }
  
}

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  Serial.println(F("Guten Morgen1"));
  Serial.println(F("Guten Morgen2"));
  while (!huskylens.begin(mySerial)) {
    Serial.println(F("no"));
  }
  Serial.println(F("yes1"));
  Serial.println(F("yes2"));
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  // pinMode(huskyLens1, INPUT);
  // pinMode(huskyLens2, INPUT);
  // pinMode(EN_A, OUTPUT);
  // pinMode(EN_B, OUTPUT);

}

void loop() {

  if (!huskylens.request()) {
      Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    }
    else if(!huskylens.isLearned()){ 
      Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    }
    else if(!huskylens.available()) {
      Serial.println(F("No block or arrow appears on the screen!"));
    }
    
    else
    {
        Serial.println(F("###########"));
        while (huskylens.available())
        {
            HUSKYLENSResult result = huskylens.read();
            printResult(result);
            // sense(result);
            if(getValue(result) == 1){
              Serial.println(F("ROCK"));
            }
            else if(getValue(result) == 2){
              Serial.println(F("SCISSORS"));
            }
            else if(getValue(result) == 3){
              Serial.println(F("PAPER"));
            }
        }    
    }
  long random = randomChoice();
  if (random == 1) {
    rock();
  }
  else if (random == 3) {
    paper();
  }
  else {
    scissors();
  }
  delay(3000);
  stopAllMotors();
  delay(3000);
  rock();
  delay(3000);
  stopAllMotors();
  delay(3000);
}

void stopAllMotors(){
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}

void motor1Forward() {
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  // digitalWrite(EN_A, HIGH);
}

void motor1Backward() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  // digitalWrite(EN_A, HIGH);
}

void motor2Forward() {
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  // digitalWrite(EN_B, HIGH);
}

void motor2Backward() {
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  // digitalWrite(EN_B, HIGH);
}

// Needs hand in Rock position before
void scissors() {
  if (cC == 1) {
    motor1Forward();
  }
  else if (cC == 3) {
    motor2Backward();
  }
  delay(3000);
  cC = 2;
}
// needs hand in paper position before
void rock() {
  if (cC == 3){
    motor1Backward();
    motor2Backward();
  }
  else if (cC == 2) {
    motor1Backward();
  }
  delay(3000);
  cC = 1;
}
// needs hand in rock position before
void paper() {
  if (cC == 1){
    motor1Forward();
    motor2Forward();
  }
  else if (cC == 2) {
    motor2Forward();
  }
  delay(3000);
  cC = 3;
}

long randomChoice() {
  return random(1, 4) ;
}

