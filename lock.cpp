#include <Keypad.h>
#include <LiquidCrystal.h> //LCD display
#include <Stepper.h> //LOCK Motor(unipolar stepper motor)

const int stepsPerRevolution = 200; //steps per rev for motor

//initializing pins for motor
Stepper myStepper(stepsPerRevolution, A5,A4,A3,A2);

//initializing LCD display pins
LiquidCrystal lcd(12, 11, 10, 9, 1,0);

//keypad initializing
const byte ROWS=4;
const byte COLS=3;
char keys[ROWS][COLS]={
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS]={8,7,6,5};
byte colPins[COLS]={4,3,2};

char code[4]={'1','2','3','4'};//default passcode
int c=1;//to check passcode
int trial=0;//track number of wrong trials

//keypad constructor
Keypad keypad = Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);

void setup(){
    // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD
  myStepper.setSpeed(60);
}

void loop(){
  /*if(key=='#'){
    //change code
  }
  else{
    key=*/
  lcd.setCursor(0, 1);
  lcd.print("Digital Lock");
  lcd.setCursor(0,0);
   lcd.print("Locked");
   char key=keypad.waitForKey();
   lcd.clear();
   lcd.print(key);
   
   if(key!=code[0]){
     c=c*0;              //c remains 1 if code is right. Else changed to 0
   }
   key=keypad.waitForKey();
   lcd.print(key);
   if(key!=code[1]){
     c=c*0;
   }
   key=keypad.waitForKey();
   lcd.print(key);
   if(key!=code[2]){
     c=c*0;
   }
   key=keypad.waitForKey();
   lcd.print(key);
   delay(500);
   if(key!=code[3]){
     c=c*0;
   }
   
   //checking the code
   if(c==0){
     lcd.clear();
     lcd.print("Try Again ");
     delay(1000);
     lcd.clear();
     c=1;
     trial=trial+1;
     
     //keeps user wait when 3 consecutive trials
     if(trial==3){
       lcd.clear();
       lcd.print("3 wrong-wait 9 s");
       delay(10000);
       lcd.clear();
       lcd.print("hii ");
       trial=0;
     }
   }
   else{
     trial=0;
     lcd.clear();
     lcd.print("open");
     
     //turn lock
     myStepper.step(stepsPerRevolution);
     
     // * for locking , # for password changing
     key=keypad.waitForKey();
     if(key=='#')
       {  
         lcd.clear();
         lcd.print("new code");
         code[0]=keypad.waitForKey();    //saving new code
         lcd.print(code[0]);
         code[1]=keypad.waitForKey();
         lcd.print(code[1]);
         code[2]=keypad.waitForKey();
         lcd.print(code[2]);
         code[3]=keypad.waitForKey();
         lcd.print(code[3]);
         delay(500);
         lcd.clear();
         lcd.print("code changed");
         delay(1000);
         lcd.clear();
         lcd.print("Locked");      //locked after code change
         
       }
     else{
         lcd.clear();
         lcd.print("Locked");
         
     }
   //turn back the lock
   myStepper.step(-stepsPerRevolution);  
   
   }   
  
}