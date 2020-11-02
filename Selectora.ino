 #include <Servo.h>
 #include <SoftwareSerial.h>
 
 //
 //Wiring
 //

 //Motors
 const int Motor1Positive = 13;   //L298N IN1
 const int Motor1Negative = 12;   //L298N IN2
 const int Motor2Positive = 11;   //L298N IN3
 const int Motor2Negative = 10;   //L298N IN4
 const int ServoReversePin = 2;

 //End-Stops
 const int Motor1LeftEndStop = 9;
 const int Motor1MiddleEndStop = 8;
 const int Motor1RightEndStop = 7;
 const int Motor2LeftEndStop = 5;
 const int Motor2MiddleEndStop = 4;
 const int Motor2RightEndStop = 3;

 //Push Buttons
 const int ShifterUp = 22;
 const int ShifterDown = 24;
 const int Clutch = 26;

 //Screen
 const int ReverseGearLed = 31; //Blue
 const int NeutralGearLed = 33; //White
 const int FirstGearLed = 35;   //Green
 const int SecondGearLed = 37;  //Green
 const int ThirdGearLed = 39;   //Green
 const int FourthGearLed = 41;  //Green
 const int ErrorLed = 43;       //Red
 const int ClutchLed = 45;      //Green


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
 pinMode (Motor1LeftEndStop, INPUT);
 pinMode (Motor1MiddleEndStop, INPUT);
 pinMode (Motor1RightEndStop, INPUT);
 pinMode (Motor2LeftEndStop, INPUT);
 pinMode (Motor2MiddleEndStop, INPUT);
 pinMode (Motor2RightEndStop, INPUT);
 pinMode (ShifterUp, INPUT);
 pinMode (ShifterDown, INPUT);
 pinMode (Clutch, INPUT);

 //Screen
 pinMode (ReverseGearLed, OUTPUT);
 pinMode (NeutralGearLed, OUTPUT);  
 pinMode (FirstGearLed, OUTPUT);
 pinMode (SecondGearLed, OUTPUT);
 pinMode (ThirdGearLed, OUTPUT);
 pinMode (FourthGearLed, OUTPUT);
 pinMode (ErrorLed, OUTPUT);
 pinMode (ClutchLed, OUTPUT);


 Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}





//
//State
//
void CheckCurrentGear(){
  if(!digitalRead(Motor1LeftEndStop) && 
      digitalRead(Motor1MiddleEndStop) && 
      !digitalRead(Motor1RightEndStop) && 
      !digitalRead(Motor2LeftEndStop) &&
      digitalRead(Motor2MiddleEndStop) && 
      !digitalRead(Motor2RightEndStop) &&
      ServoReverse.read() <= ReverseLeftDegrees){
    
    CurrentGear = 0;
    SetScreen('0');
  }
  else{
    if(digitalRead(Motor1LeftEndStop) && 
    !digitalRead(Motor1MiddleEndStop) && 
    !digitalRead(Motor1RightEndStop) && 
    !digitalRead(Motor2LeftEndStop) &&
    digitalRead(Motor2MiddleEndStop) && 
    !digitalRead(Motor2RightEndStop) &&
    ServoReverse.read() >= ReverseLeftDegrees){
      
    CurrentGear = 1;
    SetScreen('1');
    }
    else{
      if(!digitalRead(Motor1LeftEndStop) && 
        !digitalRead(Motor1MiddleEndStop) && 
        digitalRead(Motor1RightEndStop) && 
        !digitalRead(Motor2LeftEndStop) &&
        digitalRead(Motor2MiddleEndStop) && 
        !digitalRead(Motor2RightEndStop) &&
        ServoReverse.read() >= ReverseLeftDegrees){
      
      CurrentGear = 2;
      SetScreen('2');
      }
      else{
        if(!digitalRead(Motor1LeftEndStop) && 
        digitalRead(Motor1MiddleEndStop) && 
        !digitalRead(Motor1RightEndStop) && 
        digitalRead(Motor2LeftEndStop) &&
        !digitalRead(Motor2MiddleEndStop) && 
        !digitalRead(Motor2RightEndStop) &&
        ServoReverse.read() >= ReverseLeftDegrees){
      
        CurrentGear = 3;
        SetScreen('3');
        }
        else{
          if(!digitalRead(Motor1LeftEndStop) && 
            digitalRead(Motor1MiddleEndStop) && 
            !digitalRead(Motor1RightEndStop) && 
            !digitalRead(Motor2LeftEndStop) &&
            !digitalRead(Motor2MiddleEndStop) && 
            digitalRead(Motor2RightEndStop) &&
            ServoReverse.read() >= ReverseLeftDegrees){
      
          CurrentGear = 4;
          SetScreen('4');
          }
          else{
            if(!digitalRead(Motor1LeftEndStop) && 
              digitalRead(Motor1MiddleEndStop) && 
              !digitalRead(Motor1RightEndStop) && 
              !digitalRead(Motor2LeftEndStop) &&
              digitalRead(Motor2MiddleEndStop) && 
              !digitalRead(Motor2RightEndStop) &&
              ServoReverse.read() <= ReverseLeftDegrees){
      
            CurrentGear = -1;
            SetScreen('R');
            }
            else{
              CurrentGear = -2;
              SetScreen('E');
            }
          }
        }
      }
    }
  }
}

void SetScreen(char gear){
  Serial.println(gear);
  
  switch (gear){
    case 'R':{
      digitalWrite(ReverseGearLed,HIGH);
      digitalWrite(NeutralGearLed,LOW);
      digitalWrite(FirstGearLed,LOW);
      digitalWrite(SecondGearLed,LOW);
      digitalWrite(ThirdGearLed,LOW);
      digitalWrite(FourthGearLed,LOW);
      digitalWrite(ErrorLed,LOW);
    }
    case '0':{
      digitalWrite(ReverseGearLed,LOW);
      digitalWrite(NeutralGearLed,HIGH);
      digitalWrite(FirstGearLed,LOW);
      digitalWrite(SecondGearLed,LOW);
      digitalWrite(ThirdGearLed,LOW);
      digitalWrite(FourthGearLed,LOW);
      digitalWrite(ErrorLed,LOW);
    }
    case '1':{
      digitalWrite(ReverseGearLed,LOW);
      digitalWrite(NeutralGearLed,LOW);
      digitalWrite(FirstGearLed,HIGH);
      digitalWrite(SecondGearLed,LOW);
      digitalWrite(ThirdGearLed,LOW);
      digitalWrite(FourthGearLed,LOW);
      digitalWrite(ErrorLed,LOW);
    }
    case '2':{
      digitalWrite(ReverseGearLed,LOW);
      digitalWrite(NeutralGearLed,LOW);
      digitalWrite(FirstGearLed,LOW);
      digitalWrite(SecondGearLed,HIGH);
      digitalWrite(ThirdGearLed,LOW);
      digitalWrite(FourthGearLed,LOW);
      digitalWrite(ErrorLed,LOW);
    }
    case '3':{
      digitalWrite(ReverseGearLed,LOW);
      digitalWrite(NeutralGearLed,LOW);
      digitalWrite(FirstGearLed,LOW);
      digitalWrite(SecondGearLed,LOW);
      digitalWrite(ThirdGearLed,HIGH);
      digitalWrite(FourthGearLed,LOW);
      digitalWrite(ErrorLed,LOW);
    }
    case '4':{
      digitalWrite(ReverseGearLed,LOW);
      digitalWrite(NeutralGearLed,LOW);
      digitalWrite(FirstGearLed,LOW);
      digitalWrite(SecondGearLed,LOW);
      digitalWrite(ThirdGearLed,LOW);
      digitalWrite(FourthGearLed,HIGH);
      digitalWrite(ErrorLed,LOW);
    }
    case 'E':{
      digitalWrite(ReverseGearLed,LOW);
      digitalWrite(NeutralGearLed,LOW);
      digitalWrite(FirstGearLed,LOW);
      digitalWrite(SecondGearLed,LOW);
      digitalWrite(ThirdGearLed,LOW);
      digitalWrite(FourthGearLed,LOW);
      digitalWrite(ErrorLed,HIGH);
    }
  }
}

//
//Actions
//
void ShiftUp(){
  Serial.println("Shift UP");
  WaitForClutchPushed();

  switch(CurrentGear){
    case(-1):
      NeutralGear();
    case(0):
      FirstGear();
    case(1):
      SecondGear();
    case(2):
      ThirdGear();
    case(3):
      FourthGear();
  }
}

void ShiftDown(){
  Serial.println("Shift Down");
  WaitForClutchPushed();

  switch(CurrentGear){
    case(4):
      ThirdGear();
    case(3):
      SecondGear();
    case(2):
      FirstGear();
    case(1):
      NeutralGear();
    case(0):
      ReverseGear();
  }
}

void WaitForClutchPushed(){
  while(digitalRead(Clutch)){
    Serial.println("Press clutch");
    digitalWrite(ClutchLed,HIGH);
    delay(50);
  }
  Serial.println("Clutch pressed.");
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
  while(!digitalRead(Motor1LeftEndStop)){
    digitalWrite(Motor1Positive,HIGH);
    digitalWrite(Motor1Negative,LOW);
  }
  digitalWrite(Motor1Positive,LOW);
}

void Motor1Middle(){
//Check position and move motor
}

void Motor1Right(){
  while(!digitalRead(Motor1RightEndStop)){
    digitalWrite(Motor1Positive,LOW);
    digitalWrite(Motor1Negative,HIGH);
  }
  digitalWrite(Motor1Negative,LOW);
}

void Motor2Left(){
  while(!digitalRead(Motor2LeftEndStop)){
    digitalWrite(Motor2Positive,HIGH);
    digitalWrite(Motor2Negative,LOW);
  }
  digitalWrite(Motor2Positive,LOW);
}

void Motor2Middle(){
//Check position and move motor
}

void Motor2Right(){
while(!digitalRead(Motor2RightEndStop)){
    digitalWrite(Motor2Positive,LOW);
    digitalWrite(Motor2Negative,HIGH);
  }
  digitalWrite(Motor2Negative,LOW);
}

void ReverseLeft(){
  ServoReverse.write(ReverseLeftDegrees);
}

void ReverseMiddle(){
  ServoReverse.write(ReverseMiddleDegrees);
}

void loop() {
  CheckCurrentGear();

  if(digitalRead(ShifterUp)==HIGH)
    ShiftUp();

  if(digitalRead(ShifterDown)==HIGH)
    ShiftDown();
  
  delay(50);
}
