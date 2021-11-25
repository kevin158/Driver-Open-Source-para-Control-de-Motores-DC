#include <Servo.h>

String command = "";

Servo myservo1;
Servo myservo2;

int posX = 70;
int posY = 0;

void setup() {
  Serial.begin(9600);
  myservo1.attach(9);
  myservo2.attach(11);
  pinMode(2,OUTPUT);
}

bool stringFromSerial() {
  while (Serial.available()) {
    char c = Serial.read();
    command += c;
    if (c == '\n'){
      return true;
    }
  }
  return false;
}

int parseInput(){
  if (stringFromSerial()) {
    if(command.indexOf("right") > -1){
      posX = 120;
      myservo1.write(posX);
      command = "";
      return true;
    } else if(command.indexOf("left") > -1){
      posX = 70;
      myservo1.write(posX);
      command = "";
      return true;
    } else if(command.indexOf("up") > -1){
      posY = 0;
      myservo2.write(posY);
      command = "";
      return true;
    } else if(command.indexOf("down") > -1){
      posY = 90;
      myservo2.write(posY);
      command = "";
      return true;
    } else if(command.indexOf("check") > -1){
      digitalWrite(2, HIGH);
      delay(5000);
      digitalWrite(2,LOW);
      command = "";
      return true;
    } else{
      command = "";
      return true;
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(parseInput()){
    Serial.println("Done");
  }

  

}
