#include <Servo.h>
#include <ezButton.h>
const int servo_pin = 6;

enum class States{
  reloading,  // Winding arm back
  reloading2,  // Winding arm back
  loaded, // Waiting to receive command to slap
  slap, // Self-explanatory :)
};

const char* state_names[] = {"reloading", "reloading2", "loaded", "slap"};

States state = States::reloading;  // Reloads upon startup

// Logs a state change
void changeState(States target_state){
  Serial.print(millis());
  Serial.print(" | Switching state from ");
  Serial.print(state_names[(int)state]);
  Serial.print(" to ");
  state = target_state;
  Serial.println(state_names[(int)state]);
}

// Pin Config
ezButton lim(7);  // Limit switch at port 7
Servo motor; 
int pot_pin = A0; 
int speed;

void setup() {
  motor.attach(6, 1000, 2000);
  Serial.begin(9600);
  motor.write(0);
  delay(5000);  // Gives servo enough time to receive low signal
  speed = 10;
  while(!Serial.available()) delay(10);
  Serial.println("STARTING!");
}
 
void loop() {
  lim.loop();
  Serial.print(millis());
  Serial.print(" | ");
  Serial.println(state_names[(int)state]);
  // Serial.println(lim.getState());

  switch(state){
    case States::loaded:
      motor.write(1);
      if(Serial.available()){
        String teststr = Serial.readString();  //read until timeout
        teststr.trim();
        if(teststr == "hello") changeState(States::slap);
      }
      break;
    case States::reloading:
      motor.write(15);
      delay(500);
      Serial.println("SLOW DOWN**********");
      changeState(States::loaded);
      break;
    
    case States::reloading2:
      motor.write(7);
      if(lim.isPressed()) changeState(States::loaded);
      break;

    case States::slap:
      motor.write(speed);
      delay(1000); // wait for arm to reset
      changeState(States::reloading);
      break;   

  }
  // Serial.println(analogRead(pot_pin));
  // speed = map((analogRead(pot_pin)),0,1023, 0, 180);
  // motor.write(speed);

  // Serial.println("Enter data:");
  // while (Serial.available() == 0) {}     //wait for data available
  // String teststr = Serial.readString();  //read until timeout
  // teststr.trim();                        // remove any \r \n whitespace at the end of the String
  // if (teststr == "red") {
  //   Serial.println("A primary color");
  // } else {
  //   Serial.println("Something else");
  // }
  // Serial.println(teststr + " test");
 
}