/*Alex Peng
 * MiniSumo Program or something
 */
#include <Arduino.h>
//--------PARAMETERS---------------
#define LINETHRESHOLD 100 //threshold for line sensor analog read
//--------PIN DEFINITIONS----------
#define STARTMODULEPIN 10

#define LEFTLINEPIN    26
#define RIGHTLINEPIN   20

#define LEFTMOTORPIN1  5
#define LEFTMOTORPIN2  6
#define RIGHTMOTORPIN1 9
#define RIGHTMOTORPIN2 10

#define DISTSENSORL    25
#define DISTSENSORLM   24
#define DISTSENSORC    23
#define DISTSENSORRM   22
#define DISTSENSORR    21

#define DIPSWITCH1     5
#define DIPSWITCH2     6
#define DIPSWITCH3     7

//declare vars, included def for readability
int startModule  = digitalRead(STARTMODULEPIN);
int leftLine     = analogRead(LEFTLINEPIN);
int rightLine    = analogRead(RIGHTLINEPIN);
int distSensorL  = digitalRead(DISTSENSORL);
int distSensorLM = digitalRead(DISTSENSORLM);
int distSensorC  = digitalRead(DISTSENSORC);
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
    pinMode(DISTSENSORC, INPUT);
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
     distSensorC  = digitalRead(DISTSENSORC);
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
    //if (startModule){
        analogWrite(5, 120);
        analogWrite(6, 0);
        analogWrite(9, 120);
        analogWrite(10, 0);
      /*
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
      */
    //}
    //else if (!startModule){
    //  stopMoving();
      //debugging
      //Serial.println(progSelect);
      //debugDistSensor(distSensorR);
      //debugLineSensor();
    //}
    //don't care
}

/*
#include <Arduino.h>

#define D5 5
#define D6 6
#define D9 9
#define D10 10

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D9, OUTPUT);
  pinMode(D10, OUTPUT);
}

void loop() {
  analogWrite(D5, 128);
  analogWrite(D6, 255);
  analogWrite(D9, 128);
  analogWrite(D10, 255);
}*/