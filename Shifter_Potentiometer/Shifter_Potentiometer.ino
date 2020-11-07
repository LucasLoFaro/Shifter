 #include <Servo.h>
 #include <Arduino.h>
 #include <TM1637Display.h>
 
 //
 //Wiring 
 //

 //Motors
 const int Motor1Positive = 6;   //L298N IN1
 const int Motor1Negative = 7;   //L298N IN2
 const int Motor2Positive = 8;   //L298N IN3
 const int Motor2Negative = 9;   //L298N IN4
 const int ServoReversePin = 5;

 //Push Buttons
 const int ShifterUpButton = 3;
 const int ShifterDownButton = 2;
 const int ClutchButton = 4;

 //Potentiometers
 const int Motor1PosPin = 0;
 const int Motor1LeftPos = 250;
 const int Motor1CenterPos = 500;
 const int Motor1RightPos = 750;
 const int ToleranceMotor1 = 100;

 const int Motor2PosPin = 1;
 const int Motor2LeftPos = 250;
 const int Motor2CenterPos = 500;
 const int Motor2RightPos = 750;
 const int ToleranceMotor2 = 100;

 //Screen
// #define CLK 52;
// #define DIO 53;
 TM1637Display display(52, 53);
 const int ShiftingGearLed = 24; //Green
 const int ReverseGearLed = 31; //Blue
 const int NeutralGearLed = 33; //White
 const int FirstGearLed = 35;   //Green
 const int SecondGearLed = 37;  //Green
 const int ThirdGearLed = 39;   //Green
 const int FourthGearLed = 41;  //Green

 const int ErrorLed = 22;       //Red
 const int ClutchLed = 23;      //Green


 //Variables
 int CurrentGear = 0;
 Servo ServoReverse;
 int ReverseLeftDegrees = 70; //Degrees
 int ReverseMiddleDegrees = 90; //Degrees




void setup() {

  //Motors
 pinMode (Motor1Positive, OUTPUT);
 pinMode (Motor1Negative, OUTPUT);  
 pinMode (Motor2Positive, OUTPUT);
 pinMode (Motor2Negative, OUTPUT);
 ServoReverse.attach(ServoReversePin);
 
 //Endstops and Buttons
 pinMode (ShifterUpButton, INPUT);
 pinMode (ShifterDownButton, INPUT);
 pinMode (ClutchButton, INPUT);

 //Screen
 display.setBrightness(0x0f);
 display.clear();
 
 pinMode (ShiftingGearLed, OUTPUT);
 pinMode (ReverseGearLed, OUTPUT);
 pinMode (NeutralGearLed, OUTPUT);  
 pinMode (FirstGearLed, OUTPUT);
 pinMode (SecondGearLed, OUTPUT);
 pinMode (ThirdGearLed, OUTPUT);
 pinMode (FourthGearLed, OUTPUT);
 pinMode (ErrorLed, OUTPUT);
 pinMode (ClutchLed, OUTPUT);



 digitalWrite(ShiftingGearLed,LOW);
 digitalWrite(ReverseGearLed,LOW);
 digitalWrite(NeutralGearLed,LOW);
 digitalWrite(FirstGearLed,LOW);
 digitalWrite(SecondGearLed,LOW);
 digitalWrite(ThirdGearLed,LOW);
 digitalWrite(FourthGearLed,LOW);
 digitalWrite(ErrorLed,LOW);
 digitalWrite(ClutchLed,LOW);
 


 Serial.begin(9600);

 ReverseMiddle();
  
}





//
//State
//
void CheckCurrentGear(){

  int Motor1Pos = analogRead(Motor1PosPin);
  int Motor2Pos = analogRead(Motor2PosPin);

  if(abs(Motor1Pos - Motor1CenterPos) < ToleranceMotor1 
  && abs(Motor2Pos - Motor2CenterPos) < ToleranceMotor2
  && ServoReverse.read() > ReverseLeftDegrees + 10){
      CurrentGear = 0;
  }
  else{
    if(abs(Motor1Pos - Motor1LeftPos) < ToleranceMotor1 
    && abs(Motor2Pos - Motor2CenterPos) < ToleranceMotor2){ 
      CurrentGear = 1;
    }
    else{
      if(abs(Motor1Pos - Motor1RightPos) < ToleranceMotor1 
      && abs(Motor2Pos - Motor2CenterPos) < ToleranceMotor2){
        CurrentGear = 2;
      }
      else{
        if(abs(Motor1Pos - Motor1CenterPos) < ToleranceMotor1 
        && abs(Motor2Pos - Motor2LeftPos) < ToleranceMotor2){
          CurrentGear = 3;
        }
        else{
          if(abs(Motor1Pos - Motor1CenterPos) < ToleranceMotor1 
          && abs(Motor2Pos - Motor2RightPos) < ToleranceMotor2){
            CurrentGear = 4; 
          }
          else{
            if(abs(Motor1Pos - Motor1CenterPos) < ToleranceMotor1 
            && abs(Motor2Pos - Motor2CenterPos) < ToleranceMotor2
            && ServoReverse.read() <= ReverseLeftDegrees ){
              CurrentGear = -1; 
            }
            else{
            //Falta reversa
              CurrentGear = 999;
            }
          }
        }
      }
    }
  }
  SetScreen(CurrentGear);

  Serial.print("Current Gear: ");
  Serial.println(CurrentGear);
}

void SetScreen(int gear){
  
  switch (gear){
    case -1:{
      const uint8_t rev[] = {
        SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G
        };
      display.setSegments(rev);

      digitalWrite(ReverseGearLed,HIGH);
      digitalWrite(NeutralGearLed,LOW);
      digitalWrite(FirstGearLed,LOW);
      digitalWrite(SecondGearLed,LOW);
      digitalWrite(ThirdGearLed,LOW);
      digitalWrite(FourthGearLed,LOW);
      digitalWrite(ErrorLed,LOW);
      break;
    }
    case 0:{
      display.showNumberDec(0, false);  // Expect: ___0
      
      digitalWrite(ReverseGearLed,LOW);
      digitalWrite(NeutralGearLed,HIGH);
      digitalWrite(FirstGearLed,LOW);
      digitalWrite(SecondGearLed,LOW);
      digitalWrite(ThirdGearLed,LOW);
      digitalWrite(FourthGearLed,LOW);
      digitalWrite(ErrorLed,LOW);
      break;
    }
    case 1:{
      display.showNumberDec(1, false);
      
      digitalWrite(ReverseGearLed,LOW);
      digitalWrite(NeutralGearLed,LOW);
      digitalWrite(FirstGearLed,HIGH);
      digitalWrite(SecondGearLed,LOW);
      digitalWrite(ThirdGearLed,LOW);
      digitalWrite(FourthGearLed,LOW);
      digitalWrite(ErrorLed,LOW);
      break;
    }
    case 2:{
      display.showNumberDec(2, false);
      
      digitalWrite(ReverseGearLed,LOW);
      digitalWrite(NeutralGearLed,LOW);
      digitalWrite(FirstGearLed,LOW);
      digitalWrite(SecondGearLed,HIGH);
      digitalWrite(ThirdGearLed,LOW);
      digitalWrite(FourthGearLed,LOW);
      digitalWrite(ErrorLed,LOW);
      break;
    }
    case 3:{
      display.showNumberDec(3, false);

      digitalWrite(ReverseGearLed,LOW);
      digitalWrite(NeutralGearLed,LOW);
      digitalWrite(FirstGearLed,LOW);
      digitalWrite(SecondGearLed,LOW);
      digitalWrite(ThirdGearLed,HIGH);
      digitalWrite(FourthGearLed,LOW);
      digitalWrite(ErrorLed,LOW);
      break;
    }
    case 4:{
      display.showNumberDec(4, false);
      
      digitalWrite(ReverseGearLed,LOW);
      digitalWrite(NeutralGearLed,LOW);
      digitalWrite(FirstGearLed,LOW);
      digitalWrite(SecondGearLed,LOW);
      digitalWrite(ThirdGearLed,LOW);
      digitalWrite(FourthGearLed,HIGH);
      digitalWrite(ErrorLed,LOW);
      break;
    }
    default:{
      const uint8_t error[] = {
        SEG_G,SEG_G,SEG_G,SEG_G
        };
      display.setSegments(error);
      
      digitalWrite(ReverseGearLed,LOW);
      digitalWrite(NeutralGearLed,LOW);
      digitalWrite(FirstGearLed,LOW);
      digitalWrite(SecondGearLed,LOW);
      digitalWrite(ThirdGearLed,LOW);
      digitalWrite(FourthGearLed,LOW);
      digitalWrite(ErrorLed,HIGH);
      break;
    }
  }
}

//
//Actions
//
void ShiftUp(){
  Serial.println("Shift UP");
  WaitForClutchPushed();
  digitalWrite(ShiftingGearLed,HIGH);

  switch(CurrentGear){
    case -1: {
      NeutralGear();
      break;
    }
      
    case 0: {
      FirstGear();
      break;
    }
    case 1: {
      SecondGear();
      break;
    }
    
    case 2: {
      ThirdGear();
      break;
    }
      
    case 3: {
      FourthGear();
      break;
    }
      
  }

  //Wait for button release
  while(digitalRead(ShifterUpButton)){
    Serial.println("Release Up Button.");
  }
  digitalWrite(ShiftingGearLed,LOW);
}

void ShiftDown(){
  Serial.println("Shift Down");
  WaitForClutchPushed();
  digitalWrite(ShiftingGearLed,HIGH);

  switch(CurrentGear){
    case(4): {
      ThirdGear();
      break;
    }
    case(3):{
      SecondGear();
      break;
    }
    case(2):{
      FirstGear();
      break;
    }
    case(1):{
      NeutralGear();
      break;
    }
    case(0):{
      ReverseGear();
      break;
    }
  }

    //Wait for button release
  while(digitalRead(ShifterDownButton)){
    Serial.println("Release Down Button.");
  }
  digitalWrite(ShiftingGearLed,LOW);
}

void WaitForClutchPushed(){
  while(!digitalRead(ClutchButton)){
    Serial.println("Press clutch.");
    digitalWrite(ClutchLed,HIGH);
  }
  Serial.println("Release Clutch.");
  digitalWrite(ClutchLed,LOW);
}

//
//Gears
//
void FirstGear(){
  Motor2Middle();
  ReverseMiddle();
  Motor1Left();
}

void SecondGear(){
  Motor2Middle();
  ReverseMiddle();
  Motor1Right();
}

void ThirdGear(){
  Motor1Middle();
  ReverseMiddle();
  Motor2Left();
}

void FourthGear(){
  Motor1Middle();
  ReverseMiddle();
  Motor2Right();
}

void NeutralGear(){
  Motor1Middle();
  Motor2Middle();
  ReverseMiddle();
}

void ReverseGear(){
  Motor1Middle();
  Motor2Middle();
  ReverseLeft();
}

//
//Motors Control
//

void Motor1Left(){
  Serial.println("Motor 1 Left.");
  int Motor1Pos = analogRead(Motor1PosPin);
  while(abs(analogRead(Motor1PosPin) - Motor1LeftPos) > ToleranceMotor1 ){
    Serial.print("Motor 1 Left. Remaining: ");
    Serial.println(abs(analogRead(Motor1PosPin) - Motor1LeftPos));
    digitalWrite(Motor1Positive,HIGH);
    digitalWrite(Motor1Negative,LOW);
  }
  digitalWrite(Motor1Positive,LOW);
  digitalWrite(Motor1Negative,LOW);
}

void Motor1Middle(){
//Check position and move motor
Serial.println("Motor 1 Middle.");
}

void Motor1Right(){
  Serial.println("Motor 1 Right.");
  int Motor1Pos = analogRead(Motor1PosPin);
  while(abs(analogRead(Motor1PosPin) - Motor1RightPos) > ToleranceMotor1 ){
    Serial.print("Motor 1 Right. Remaining: ");
    Serial.println(abs(analogRead(Motor1PosPin) - Motor1RightPos));
    digitalWrite(Motor1Positive,LOW);
    digitalWrite(Motor1Negative,HIGH);
  }
  digitalWrite(Motor1Positive,LOW);
  digitalWrite(Motor1Negative,LOW);
}

void Motor2Left(){
  Serial.println("Motor 2 Left.");
  int Motor2Pos = analogRead(Motor2PosPin);
  while(abs(analogRead(Motor2PosPin) - Motor2LeftPos) > ToleranceMotor2 ){
    Serial.print("Motor 2 Left. Remaining: ");
    Serial.println(abs(analogRead(Motor2PosPin) - Motor2LeftPos));
    digitalWrite(Motor2Positive,HIGH);
    digitalWrite(Motor2Negative,LOW);
  }
  digitalWrite(Motor2Positive,LOW);
  digitalWrite(Motor2Negative,LOW);
}

void Motor2Middle(){
Serial.println("Motor 2 Middle.");
//Check posiction and move motor
}

void Motor2Right(){
  Serial.println("Motor 2 Right.");
  int Motor2Pos = analogRead(Motor2PosPin);
  while(abs(analogRead(Motor2PosPin) - Motor2RightPos) > ToleranceMotor2 ){
    Serial.print("Motor 2 Right. Remaining: ");
    Serial.println(abs(analogRead(Motor2PosPin) - Motor2RightPos));
    digitalWrite(Motor2Positive,LOW);
    digitalWrite(Motor2Negative,HIGH);
  }
  digitalWrite(Motor2Positive,LOW);
  digitalWrite(Motor2Negative,LOW);
}

void ReverseLeft(){
  Serial.println("Reverse Left.");
  ServoReverse.write(ReverseLeftDegrees);
}

void ReverseMiddle(){
  Serial.println("Reverse Middle.");
  ServoReverse.write(ReverseMiddleDegrees);
}

void loop() {
  CheckCurrentGear();

  if(digitalRead(ShifterUpButton))
    ShiftUp();

  if(digitalRead(ShifterDownButton))
    ShiftDown();
  
  
  //delay(250);
}
