int driverPUL = 7;    // PULse- pin
int driverDIR = 6;    // DIR- pin
 
int pd = 500;       // Pulse Delay period
bool setdir = LOW; // Set Direction
int pot_pin = A0; 
 
void setup() {
 
  pinMode (driverPUL, OUTPUT);
  pinMode (driverDIR, OUTPUT);
  Serial.begin(9600);
}
 
void loop() {
  // Serial.println(analogRead(pot_pin));
  // pd = map((analogRead(pot_pin)),0,1023,2000,50);
  // if
  // digitalWrite(driverDIR,setdir);
  // digitalWrite(driverPUL,HIGH);
  // delayMicroseconds(pd);
  // digitalWrite(driverPUL,LOW);
  // delayMicroseconds(pd);

  Serial.println("Enter data:");
  while (Serial.available() == 0) {}     //wait for data available
  String teststr = Serial.readString();  //read until timeout
  teststr.trim();                        // remove any \r \n whitespace at the end of the String
  // if (teststr == "red") {
  //   Serial.println("A primary color");
  // } else {
  //   Serial.println("Something else");
  // }
  Serial.println(teststr + " test");
 
}