 #include <Servo.h>
 #include <Arduino.h>
 #include <TM1637Display.h>
 
 //
 //Wiring
 //

 //Motors
 const int Motor1Positive = 10;   //L298N IN1
 const int Motor1Negative = 11;   //L298N IN2
 const int Motor2Positive = 12;   //L298N IN3
 const int Motor2Negative = 13;   //L298N IN4
 const int ServoReversePin = 2;

 //End-Stops
 const int ReverseLeftEndStop = 3;
 const int Motor1LeftEndStop = 4;
 const int Motor1MiddleEndStop = 5;
 const int Motor1RightEndStop = 6;
 const int Motor2LeftEndStop = 7;
 const int Motor2MiddleEndStop = 8;
 const int Motor2RightEndStop = 9;

 //Push Buttons
 const int ShifterUp = 22;
 const int ShifterDown = 24;
 const int Clutch = 26;

 //Screen
// #define CLK 52;
// #define DIO 53;
 TM1637Display display(52, 53);
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
 pinMode (ReverseLeftEndStop, INPUT);
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
 display.setBrightness(0x0f);
 display.clear();
 
 pinMode (ReverseGearLed, OUTPUT);
 pinMode (NeutralGearLed, OUTPUT);  
 pinMode (FirstGearLed, OUTPUT);
 pinMode (SecondGearLed, OUTPUT);
 pinMode (ThirdGearLed, OUTPUT);
 pinMode (FourthGearLed, OUTPUT);
 pinMode (ErrorLed, OUTPUT);
 pinMode (ClutchLed, OUTPUT);



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
  
  if(digitalRead(Motor1MiddleEndStop)  
  && digitalRead(Motor2MiddleEndStop)){

      CurrentGear = 0;
      SetScreen('0');

  }
  else{
    if(digitalRead(Motor1LeftEndStop) 
    && digitalRead(Motor2MiddleEndStop)){ 

      CurrentGear = 1;
      SetScreen('1');
    }
    else{
      if(digitalRead(Motor1RightEndStop)  
      && digitalRead(Motor2MiddleEndStop)){

        CurrentGear = 2;
        SetScreen('2');

      }
      else{
        if(digitalRead(Motor1MiddleEndStop) 
        && digitalRead(Motor2LeftEndStop)){

          CurrentGear = 3;
          SetScreen('3');

        }
        else{
          if(digitalRead(Motor1MiddleEndStop)
          && digitalRead(Motor2RightEndStop)){

            CurrentGear = 4;
            SetScreen('4');
            
          }
          else{
            if(digitalRead(Motor1MiddleEndStop) 
            && digitalRead(Motor2MiddleEndStop) 
            && digitalRead(ReverseLeftEndStop)){

              CurrentGear = -1;
              SetScreen('R');
              
            }
            else{

              CurrentGear = 0;
              //SetScreen('E');
            
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
      display.showNumberDec(0, false);  // Expect: ___0
      
      digitalWrite(ReverseGearLed,LOW);
      digitalWrite(NeutralGearLed,HIGH);
      digitalWrite(FirstGearLed,LOW);
      digitalWrite(SecondGearLed,LOW);
      digitalWrite(ThirdGearLed,LOW);
      digitalWrite(FourthGearLed,LOW);
      digitalWrite(ErrorLed,LOW);
    }
    case '1':{
      display.showNumberDec(1, false);
      
      digitalWrite(ReverseGearLed,LOW);
      digitalWrite(NeutralGearLed,LOW);
      digitalWrite(FirstGearLed,HIGH);
      digitalWrite(SecondGearLed,LOW);
      digitalWrite(ThirdGearLed,LOW);
      digitalWrite(FourthGearLed,LOW);
      digitalWrite(ErrorLed,LOW);
    }
    case '2':{
      display.showNumberDec(2, false);
      
      digitalWrite(ReverseGearLed,LOW);
      digitalWrite(NeutralGearLed,LOW);
      digitalWrite(FirstGearLed,LOW);
      digitalWrite(SecondGearLed,HIGH);
      digitalWrite(ThirdGearLed,LOW);
      digitalWrite(FourthGearLed,LOW);
      digitalWrite(ErrorLed,LOW);
    }
    case '3':{
      display.showNumberDec(3, false);

      digitalWrite(ReverseGearLed,LOW);
      digitalWrite(NeutralGearLed,LOW);
      digitalWrite(FirstGearLed,LOW);
      digitalWrite(SecondGearLed,LOW);
      digitalWrite(ThirdGearLed,HIGH);
      digitalWrite(FourthGearLed,LOW);
      digitalWrite(ErrorLed,LOW);
    }
    case '4':{
      display.showNumberDec(4, false);
      
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
    case 'C':{
      digitalWrite(ClutchLed,HIGH);
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

  //Wait for button release
  while(digitalRead(ShifterUp)){
    Serial.println("Release Up Button.");
    delay(50);
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

    //Wait for button release
  while(digitalRead(ShifterDown)){
    Serial.println("Release Down Button.");
    delay(50);
  }
}

void WaitForClutchPushed(){
  while(!digitalRead(Clutch)){
    Serial.println("Press clutch.");
    SetScreen('C');
    digitalWrite(ClutchLed,HIGH);
    delay(100);
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
  while(!digitalRead(Motor1LeftEndStop)){
    digitalWrite(Motor1Positive,HIGH);
    digitalWrite(Motor1Negative,LOW);
  }
  Serial.println("Motor 1 Left.");
  digitalWrite(Motor1Positive,LOW);
  digitalWrite(Motor1Negative,LOW);
}

void Motor1Middle(){
//Check position and move motor
Serial.println("Motor 1 Middle.");
}

void Motor1Right(){
  while(!digitalRead(Motor1RightEndStop)){
    digitalWrite(Motor1Positive,LOW);
    digitalWrite(Motor1Negative,HIGH);
  }
  Serial.println("Motor 1 Right.");
  digitalWrite(Motor1Positive,LOW);
  digitalWrite(Motor1Negative,LOW);
}

void Motor2Left(){
  while(!digitalRead(Motor2LeftEndStop)){
    digitalWrite(Motor2Positive,HIGH);
    digitalWrite(Motor2Negative,LOW);
  }
  Serial.println("Motor 2 Left.");
  digitalWrite(Motor2Positive,LOW);
  digitalWrite(Motor2Negative,LOW);
}

void Motor2Middle(){
Serial.println("Motor 2 Middle.");
//Check posiction and move motor
}

void Motor2Right(){
  while(!digitalRead(Motor2RightEndStop)){
    digitalWrite(Motor2Positive,LOW);
    digitalWrite(Motor2Negative,HIGH);
  }
  Serial.println("Motor 2 Right.");
  digitalWrite(Motor2Positive,LOW);
  digitalWrite(Motor2Negative,LOW);
}

void ReverseLeft(){
  ServoReverse.write(ReverseLeftDegrees);
  Serial.println("Reverse Left.");
}

void ReverseMiddle(){
  ServoReverse.write(ReverseMiddleDegrees);
  Serial.println("Reverse Middle.");
}

void loop() {
  CheckCurrentGear();

  if(digitalRead(ShifterUp))
    ShiftUp();

  if(digitalRead(ShifterDown))
    ShiftDown();
  
  delay(500);
}













//void CheckCurrentGear(){
//   //Serial.print("Reverse: ");
//   //Serial.println(ServoReverse.read());
  
//   if(!digitalRead(Motor1LeftEndStop) && 
//       digitalRead(Motor1MiddleEndStop) && 
//       !digitalRead(Motor1RightEndStop) && 
//       !digitalRead(Motor2LeftEndStop) &&
//       digitalRead(Motor2MiddleEndStop) && 
//       !digitalRead(Motor2RightEndStop) &&
//       //ServoReverse.read() >= ReverseLeftDegrees){
//       !digitalRead(ReverseLeftEndStop)){

//       CurrentGear = 0;
//       SetScreen('0');

//   }
//   else{
//     if(digitalRead(Motor1LeftEndStop) && 
//     !digitalRead(Motor1MiddleEndStop) && 
//     !digitalRead(Motor1RightEndStop) && 
//     !digitalRead(Motor2LeftEndStop) &&
//     digitalRead(Motor2MiddleEndStop) && 
//     !digitalRead(Motor2RightEndStop) &&
//     //ServoReverse.read() >= ReverseLeftDegrees){
//     !digitalRead(ReverseLeftEndStop)){ 

//       CurrentGear = 1;
//       SetScreen('1');
//     }
//     else{
//       if(!digitalRead(Motor1LeftEndStop) && 
//         !digitalRead(Motor1MiddleEndStop) && 
//         digitalRead(Motor1RightEndStop) && 
//         !digitalRead(Motor2LeftEndStop) &&
//         digitalRead(Motor2MiddleEndStop) && 
//         !digitalRead(Motor2RightEndStop) &&
//         //ServoReverse.read() >= ReverseLeftDegrees){
//         !digitalRead(ReverseLeftEndStop)){

//         CurrentGear = 2;
//         SetScreen('2');

//       }
//       else{
//         if(!digitalRead(Motor1LeftEndStop) && 
//         digitalRead(Motor1MiddleEndStop) && 
//         !digitalRead(Motor1RightEndStop) && 
//         digitalRead(Motor2LeftEndStop) &&
//         !digitalRead(Motor2MiddleEndStop) && 
//         !digitalRead(Motor2RightEndStop) &&
//         //ServoReverse.read() >= ReverseLeftDegrees){
//         !digitalRead(ReverseLeftEndStop)){

//           CurrentGear = 3;
//           SetScreen('3');

//         }
//         else{
//           if(!digitalRead(Motor1LeftEndStop) && 
//             digitalRead(Motor1MiddleEndStop) && 
//             !digitalRead(Motor1RightEndStop) && 
//             !digitalRead(Motor2LeftEndStop) &&
//             !digitalRead(Motor2MiddleEndStop) && 
//             digitalRead(Motor2RightEndStop) &&
//             //ServoReverse.read() >= ReverseLeftDegrees){
//             !digitalRead(ReverseLeftEndStop)){

//             CurrentGear = 4;
//             SetScreen('4');
            
//           }
//           else{
//             if(!digitalRead(Motor1LeftEndStop) && 
//               digitalRead(Motor1MiddleEndStop) && 
//               !digitalRead(Motor1RightEndStop) && 
//               !digitalRead(Motor2LeftEndStop) &&
//               digitalRead(Motor2MiddleEndStop) && 
//               !digitalRead(Motor2RightEndStop) &&
//               //ServoReverse.read() <= ReverseLeftDegrees){
//               digitalRead(ReverseLeftEndStop)){

//               CurrentGear = -1;
//               SetScreen('R');
              
//             }
//             else{

//               CurrentGear = 0;
//               SetScreen('E');
            
//             }
//           }
//         }
//       }
//     }
//   }
// }
