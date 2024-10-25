#define LMOTOR1 5
#define LMOTOR2 6
#define RMOTOR1 9
#define RMOTOR2 10
// Start module
#define START 7
// Distance sensors
#define LDIST A4
#define LMDIST A5
#define MDIST A3
#define RMDIST A2
#define RDIST A1
// Line sensors
#define LLS A0
#define RLS A6
// Program select
#define PS1 2
#define PS2 3
#define PS3 4

int lineThreshold = 35;  // Tunable threshold value for line sensors, 40

void setup() {
  // Set motor pins as output
  pinMode(LMOTOR1, OUTPUT);
  pinMode(LMOTOR2, OUTPUT);
  pinMode(RMOTOR1, OUTPUT);
  pinMode(RMOTOR2, OUTPUT);

  // Set sensor pins as input
  pinMode(LDIST, INPUT);
  pinMode(LMDIST, INPUT);
  pinMode(MDIST, INPUT);
  pinMode(RMDIST, INPUT);
  pinMode(RDIST, INPUT);
  pinMode(LLS, INPUT);
  pinMode(RLS, INPUT);
  pinMode(START, INPUT);
  pinMode(PS1, INPUT_PULLUP);
  pinMode(PS2, INPUT_PULLUP);
  pinMode(PS3, INPUT_PULLUP);

  // Initialize serial communication for debug mode
  if (debugMode) {
    Serial.begin(9600);
  }

  // Start with motors off
  stopMotors();
}

void loop() {
  // Read sensor values
  bool leftDist = digitalRead(LDIST);
  bool leftMidDist = digitalRead(LMDIST);
  bool midDist = digitalRead(MDIST);
  bool rightMidDist = digitalRead(RMDIST);
  bool rightDist = digitalRead(RDIST);
  int leftLine = analogRead(LLS);
  int rightLine = analogRead(RLS);
  int progSel = readProgramSelection();

  if (digitalRead(START) == HIGH) {
    switch (progSel) {
      case 0:
        debugMode(leftDist, leftMidDist, midDist, rightMidDist, rightDist, leftLine, rightLine);  // Default program: stop motors
        break;
      case 1:
        defensive(leftDist, leftMidDist, midDist, rightMidDist, rightDist, leftLine, rightLine);
        break;
      case 2:
        attack(leftDist, leftMidDist, midDist, rightMidDist, rightDist, leftLine, rightLine);
        break;
      case 3:
        //programThree();
        break;
      case 4:
        //programFour();
        break;
      case 5:
        //programFive();
        break;
      case 6:
        //programSix();
        break;
      case 7:
        //programSeven();
        break;
      default:
        stopMotors();  // Default to stopping motors if an unknown program is selected
        break;
    }
  } else {
    stopMotors();
  }
}

int readProgramSelection() {
  int ps1 = digitalRead(PS1);
  int ps2 = digitalRead(PS2);
  int ps3 = digitalRead(PS3);

  // Convert binary inputs to a single integer (0-7)
  return (ps1 << 2) | (ps2 << 1) | ps3;
}

void debugMode(bool leftDist, bool leftMidDist, bool midDist, bool rightMidDist, bool rightDist, int leftLine, int rightLine) {
  Serial.print("LDIST: ");
  Serial.print(leftDist);
  Serial.print(" LMDIST: ");
  Serial.print(leftMidDist);
  Serial.print(" MDIST: ");
  Serial.print(midDist);
  Serial.print(" RMDIST: ");
  Serial.print(rightMidDist);
  Serial.print(" RDIST: ");
  Serial.print(rightDist);
  Serial.print(" LLS: ");
  Serial.print(leftLine);
  Serial.print(" RLS: ");
  Serial.print(rightLine);
  Serial.print(" ProgSel: ");
  Serial.println(readProgramSelection());
  delay(100);  // Delay to make it readable
}

void defensive(bool leftDist, bool leftMidDist, bool midDist, bool rightMidDist, bool rightDist, int leftLine, int rightLine) {
  if (leftLine < lineThreshold) {
    moveBackward(80);
    delay(160);
    turnRightS(160);
    delay(160);
    //moveForward(40);
    //delay(100);
  } else if (rightLine < lineThreshold){
    moveBackward(80);
    delay(160);
    turnLeftS(160);
    delay(160);
    //moveForward(40);
    //delay(100);
  } else if (midDist) {
    moveForward(125);
  } else if (leftMidDist) {
    turnRight(200);
  } else if (rightMidDist) {
    turnLeft(200);
  } else if (leftDist) {
    turnRightS(200);
  } else if (rightDist) {
    turnLeftS(200);
  } else {
    stopMotors();
  }
}

int midDistCounter = 0; // Initialize a counter for midDist
void attack(bool leftDist, bool leftMidDist, bool midDist, bool rightMidDist, bool rightDist, int leftLine, int rightLine) {  
  if (leftLine < lineThreshold) {
    moveBackward(110);
    delay(180);
    turnRightS(160);
    delay(80);
    midDistCounter = 0; // Reset counter
  } 
  else if (rightLine < lineThreshold) {
    moveBackward(110);
    delay(180);
    turnLeftS(160);
    delay(80);
    midDistCounter = 0; // Reset counter
  } 
  else if (midDist) {
    midDistCounter++; // Increase counter
    moveForward(135 + (midDistCounter * 5)); // Increase speed progressively
  } 
  else if (leftMidDist) {
    turnRight(200);
    midDistCounter = 0; // Reset counter
  } 
  else if (rightMidDist) {
    turnLeft(200);
    midDistCounter = 0; // Reset counter
  } 
  else if (leftDist) {
    turnRightS(200);
    midDistCounter = 0; // Reset counter
  } 
  else if (rightDist) {
    turnLeftS(200);
    midDistCounter = 0; // Reset counter
  } 
  else {
    moveForward(45);
    midDistCounter = 0; // Reset counter
  }
}

void stopMotors() {
  analogWrite(LMOTOR1, 255);
  analogWrite(LMOTOR2, 255);
  analogWrite(RMOTOR1, 255);
  analogWrite(RMOTOR2, 255);
}

void moveForward(int motorSpeed) {
  analogWrite(LMOTOR1, motorSpeed);
  analogWrite(LMOTOR2, 0);
  analogWrite(RMOTOR1, motorSpeed);
  analogWrite(RMOTOR2, 0);
}

void moveBackward(int motorSpeed) {
  analogWrite(LMOTOR1, 0);
  analogWrite(LMOTOR2, motorSpeed);
  analogWrite(RMOTOR1, 0);
  analogWrite(RMOTOR2, motorSpeed);
}

void turnRight(int motorSpeed) {
  analogWrite(LMOTOR1, 255);
  analogWrite(LMOTOR2, 255);
  analogWrite(RMOTOR1, motorSpeed);
  analogWrite(RMOTOR2, 0);
}

void turnLeft(int motorSpeed) {
  analogWrite(LMOTOR1, motorSpeed);
  analogWrite(LMOTOR2, 0);
  analogWrite(RMOTOR1, 255);
  analogWrite(RMOTOR2, 255);
}

void turnRightS(int motorSpeed) {
  analogWrite(LMOTOR1, 0);
  analogWrite(LMOTOR2, motorSpeed);
  analogWrite(RMOTOR1, motorSpeed / 2);
  analogWrite(RMOTOR2, 0);
}

void turnLeftS(int motorSpeed) {
  analogWrite(LMOTOR1, motorSpeed / 2);
  analogWrite(LMOTOR2, 0);
  analogWrite(RMOTOR1, 0);
  analogWrite(RMOTOR2, motorSpeed);
}

bool detectLine(int leftLine, int rightLine) {
  return leftLine < lineThreshold || rightLine < lineThreshold;
}

bool detectObstacle(bool leftDist, bool leftMidDist, bool midDist, bool rightMidDist, bool rightDist) {
  return leftDist || leftMidDist || midDist || rightMidDist || rightDist;
}