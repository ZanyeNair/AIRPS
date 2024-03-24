#define IN1_A 5  // Motor A IN1 pin
#define IN2_A 7  // Motor A IN2 pin
#define IN1_B 6  // Motor B IN1 pin
#define IN2_B 8  // Motor B IN2 pin
#define EN_A  9  // Motor A enable pin
#define EN_B  10 // Motor B enable pin
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

char prevChoice = "rock";
int cC = "";//current choice 1&&4 = rock 2 = paper 3 = scisors
HUSKYLENS huskylens;

void setup() {
  pinMode(IN1_A, OUTPUT);
  pinMode(IN2_A, OUTPUT);
  pinMode(IN1_B, OUTPUT);
  pinMode(IN2_B, OUTPUT);
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);

  rock();
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
            sense(result);
        }    
    }
  long random = randomChoice();
  if (random == 1) {
    rock();
    cC = 1;
  }
  else if (random == 2) {
    paper();
    cC = 2;
  }
  else {
    scissors();
    cC = 3;
  }
  

}

void motor1Forward() {
  digitalWrite(IN1_A, HIGH);
  digitalWrite(IN2_A, LOW);
  digitalWrite(EN_A, HIGH);
}

void motor1Backward() {
  digitalWrite(IN1_A, LOW);
  digitalWrite(IN2_A, HIGH);
  digitalWrite(EN_A, HIGH);
}

void motor2Forward() {
  digitalWrite(IN1_B, HIGH);
  digitalWrite(IN2_B, LOW);
  digitalWrite(EN_B, HIGH);
}

void motor2Backward() {
  digitalWrite(IN1_B, LOW);
  digitalWrite(IN2_B, HIGH);
  digitalWrite(EN_B, HIGH);
}

// Needs hand in Rock position before
void scissors() {
  if (prevChoice == "rock") {
    motor1Forward();
  }
  else if (prevChoice == "paper") {
    motor2Backward();
  }
  prevChoice = "scissors";
}
// needs hand in paper position before
void rock() {
  if (prevChoice == "paper"){
    motor1Backward();
    motor2Backward();
  }
  else if (prevChoice == "scissors") {
    motor1Backward();
  }
  prevChoice = "rock";
}
// needs hand in rock position before
void paper() {
  if (prevChoice == "rock"){
    motor1Forward();
    motor2Forward();
  }
  else if (prevChoice == "scissors") {
    motor2Forward();
  }
  prevChoice = "paper";
}

long randomChoice() {
  return random(1, 4) ;
}


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

void sense(HUSKYLENSResult result)
{
  if(result.ID == 1||result.ID == 4){
    if(cC == 1){
      //white light
    }
    else if(cC == 2){
      //red light
    }
    else{
      //green light
    }

  }
  else if(result.ID == 2){
    if(cC == 1){
      //green light
    }
    else if(cC == 2){
      //white light
    }
    else{
      //red light
    }
  }
  else{
    if(cC == 1){
      //red light
    }
    else if(cC == 2){
      //green light
    }
    else{
      //white light
    }
  }
  
}

