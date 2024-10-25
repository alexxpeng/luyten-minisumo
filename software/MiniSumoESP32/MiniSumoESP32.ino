#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A7, OUTPUT);
  pinMode(8, INPUT);
  Serial.begin(9600);
}

int startModule = digitalRead(8);
void loop() {
  
  //if (startModule) {
    //  //digitalWrite(A4, 1);
    // //digitalWrite(A5, 0);
    // //digitalWrite(A6, 1);
    // //digitalWrite(A7, 0);
    // Serial.println("START");
    // delay(1000);
    analogWrite(A4, 70);
    analogWrite(A5, 64);
    analogWrite(A6, 170);
    analogWrite(A7, 64);

    /*
    digitalWrite(A6, 1);
    digitalWrite(A7, 1);
    delay(5000);
    digitalWrite(A6, 1);
    digitalWrite(A7, 0);
    delay(5000);
    */
    //digitalWrite(A6, 1);
    //digitalWrite(A7, 1);
    Serial.println("STOP");
    //delay(2000);
  //} else if (!startModule){
    /*analogWrite(A4, 255);
    analogWrite(A5, 255);
    analogWrite(A6, 255);
    analogWrite(A7, 255);
    Serial.println("STOP");
  //}*/

}
