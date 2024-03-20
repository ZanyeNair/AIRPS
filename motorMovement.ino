#define IN1_A 5  // Motor A IN1 pin
#define IN2_A 7  // Motor A IN2 pin
#define IN1_B 6  // Motor B IN1 pin
#define IN2_B 8  // Motor B IN2 pin
#define EN_A  9  // Motor A enable pin
#define EN_B  10 // Motor B enable pin

char prevChoice = "rock";
char currentChoice = "";

void setup() {
  pinMode(IN1_A, OUTPUT);
  pinMode(IN2_A, OUTPUT);
  pinMode(IN1_B, OUTPUT);
  pinMode(IN2_B, OUTPUT);
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);

  rock()
}

void loop() {
  long random = randomChoice();
  if (random == 1) {
    rock();
    currentChoice = "rock";
  }
  else if (random == 2) {
    paper();
    currentChoice = "paper";
  }
  else {
    scissors();
    currentChoice = "scissors";
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
  return random(1, 4) 
}
