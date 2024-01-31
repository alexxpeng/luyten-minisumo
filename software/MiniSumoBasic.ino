/*Alex Peng
 * MiniSumo Program or something
 */
//--------PARAMETERS---------------
#define LINETHRESHOLD 100 //threshold for line sensor analog read
//--------PIN DEFINITIONS----------
#define STARTMODULEPIN 13

#define LEFTLINEPIN    20
#define RIGHTLINEPIN   21

#define LEFTMOTORPIN1  23
#define LEFTMOTORPIN2  22
#define RIGHTMOTORPIN1 18
#define RIGHTMOTORPIN2 19

#define DISTSENSORL    38
#define DISTSENSORLM   40
#define DISTSENSORRM   11
#define DISTSENSORR    9

#define DIPSWITCH1     24
#define DIPSWITCH2     25
#define DIPSWITCH3     26

//declare vars, included def for readability
int startModule  = digitalRead(STARTMODULEPIN);
int leftLine     = analogRead(LEFTLINEPIN);
int rightLine    = analogRead(RIGHTLINEPIN);
int distSensorL  = digitalRead(DISTSENSORL);
int distSensorLM = digitalRead(DISTSENSORLM);
int distSensorRM = digitalRead(DISTSENSORRM);
int distSensorR  = digitalRead(DISTSENSORR);
int progSelect   = digitalRead(DIPSWITCH3) << 2 | (digitalRead(DIPSWITCH2) << 1 | digitalRead(DIPSWITCH1));

void setup() {
    Serial.begin(115200);

    //initialize motor pins
    pinMode(LEFTMOTORPIN1, OUTPUT);
    pinMode(LEFTMOTORPIN2, OUTPUT);
    pinMode(RIGHTMOTORPIN1, OUTPUT);
    pinMode(RIGHTMOTORPIN2, OUTPUT);

    //initialize Start Module pin
    pinMode(STARTMODULEPIN, INPUT);

    //initialize distance sensors
    pinMode(DISTSENSORR, INPUT);
    pinMode(DISTSENSORRM, INPUT);
    pinMode(DISTSENSORLM, INPUT);
    pinMode(DISTSENSORL, INPUT);

    //initialize line sensors
    pinMode(LEFTLINEPIN, INPUT);
    pinMode(RIGHTLINEPIN, INPUT);

    //initialize dip switch inputs (active low due to internal pullup)
    pinMode(DIPSWITCH1, INPUT_PULLUP);
    pinMode(DIPSWITCH2, INPUT_PULLUP);
    pinMode(DIPSWITCH3, INPUT_PULLUP);
    
}

void forward(){
    //FORWARD
    //left forward
    digitalWrite(LEFTMOTORPIN1, HIGH);
    digitalWrite(LEFTMOTORPIN2, LOW);
    //right forward
    digitalWrite(RIGHTMOTORPIN1, HIGH);
    digitalWrite(RIGHTMOTORPIN2, LOW);
}

void backward(){
    //BACKWARD
    //left back
    digitalWrite(LEFTMOTORPIN1, LOW);
    digitalWrite(LEFTMOTORPIN2, HIGH);
    //right back
    digitalWrite(RIGHTMOTORPIN1, LOW);
    digitalWrite(RIGHTMOTORPIN2, HIGH);
}

void rightTurn(){
    //RIGHT
    //left forward
    digitalWrite(LEFTMOTORPIN1, HIGH);
    digitalWrite(LEFTMOTORPIN2, LOW);
    //right back
    digitalWrite(RIGHTMOTORPIN1, HIGH);
    digitalWrite(RIGHTMOTORPIN2, HIGH);
}

void leftTurn(){
    //LEFT
    //left back
    digitalWrite(LEFTMOTORPIN1, HIGH);
    digitalWrite(LEFTMOTORPIN2, HIGH);
    //right forward
    digitalWrite(RIGHTMOTORPIN1, HIGH);
    digitalWrite(RIGHTMOTORPIN2, LOW);
}

void stopMoving(){
    digitalWrite(LEFTMOTORPIN1, LOW);
    digitalWrite(LEFTMOTORPIN2, LOW);
    digitalWrite(RIGHTMOTORPIN1, LOW);
    digitalWrite(RIGHTMOTORPIN2, LOW);
}

void debugLineSensor(){
    //print left and right line sensor readings
    Serial.print("LEFT LS: ");
    Serial.println(leftLine);
    Serial.print("RIGHT LS: ");
    Serial.println(rightLine);
}

void debugDistSensor(int distSense){
    //print dist sensor reading passed in
    Serial.print("DIST SENSOR: ");
    Serial.println(distSense);
}

void loop() {
     //update vars
     startModule  = digitalRead(STARTMODULEPIN);
     leftLine     = analogRead(LEFTLINEPIN);
     rightLine    = analogRead(RIGHTLINEPIN);
     progSelect   = digitalRead(DIPSWITCH3) << 2 | (digitalRead(DIPSWITCH2) << 1 | digitalRead(DIPSWITCH1));
     distSensorL  = digitalRead(DISTSENSORL);
     distSensorLM = digitalRead(DISTSENSORLM);
     distSensorRM = digitalRead(DISTSENSORRM);
     distSensorR  = digitalRead(DISTSENSORR);

  
    //wait for start module signal
    
    //program 0 basic test
    /*if (startModule){
      switch (progSelect){
          case 0: { 
              forward();
              if (leftLine < LINETHRESHOLD) {
                  //if left line sensor triggered back and turn right
                  backward();
                  delay(200);
                  rightTurn();
                  delay(200);
              }else if (rightLine < LINETHRESHOLD) {
                  //if right line sensor triggered back and turn left
                  backward();
                  delay(200);
                  leftTurn();
                  delay(200);
              }
          }

          case 1: {
              backward();
          }

          case 2: {
          
          
      }

          
    }
    */
    if (startModule){
              if (distSensorLM) {
                  forward();
              }
              if (distSensorL && !distSensorLM) {
                  leftTurn();
                  delay(50);
              }
              if (distSensorR && !distSensorLM) {
                  rightTurn();
                  delay(50);
              }
              if (leftLine < LINETHRESHOLD) {
                  //if left line sensor triggered back and turn right
                  backward();
                  delay(200);
                  rightTurn();
                  delay(200);
              }else if (rightLine < LINETHRESHOLD) {
                  //if right line sensor triggered back and turn left
                  backward();
                  delay(200);
                  leftTurn();
                  delay(200);
              }
    }
    else if (!startModule){
      stopMoving();
      //debugging
      //Serial.println(progSelect);
      //debugDistSensor(distSensorR);
      //debugLineSensor();
    }
    //don't care
}
