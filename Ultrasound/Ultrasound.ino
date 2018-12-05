#include <LiquidCrystal.h>
#include "Button.h"
#define LCDLight 13
#define rs 12
#define en 11
#define d4 10
#define d5 9
#define d6 8
#define d7 7
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const int trigPin = 4, echoPin = 3;
long duration;
int distanceCm;

int cs=5;
const int contrast = 100;

int h=12;
int m=59;
int s=45;
int flag=1;
int button1;
int button2;
int hs=0;
int ms=3;

const int Time_light=150;
int bl_TO=Time_light;
int bl=10;
const int backlight=120;

static uint32_t last_time, now = 0;

//Buttons
Button S1 (2); //button up
Button S2 (1); //button enter/back
Button S3 (0); //button down

//Outputs
#define D0 3
#define D1 4
#define D2 5


String menuItems[] = {"clock", "sensor"};
int menuPage = 0;
int cursorPosition = 0;
int downCursor = 0;


byte menuCursor[8] = {
  B01000, //  *
  B00100, //   *
  B00010, //    *
  B00001, //     *
  B00010, //    *
  B00100, //   *
  B01000, //  *
  B00000  //
};

byte downArrow[8] = {
  0b01100, //   **
  0b11110, //  ****
  0b11110, // ******
  0b11110, // ******
  0b11110, // ******
  0b01100, //  ****
  0b00000,
  0b01100  //   ** 
};

byte leftArrow[8] = {
  B11000, //**
  B01100, // **
  B00110, //  ** 
  B00011, //   ** 
  B00011, //   **
  B00110, //  **
  B01100, // **
  B11000  //**
};
byte rightArrow[9] = {
  B00011, //   **
  B00110, //  **
  B01100, // **
  B11000, //**
  B11000, //**
  B01100, // **
  B00110, //  **
  B00011  //   **
};

void setup() {

  lcd.begin(16,2);
  pinMode(hs,INPUT_PULLUP);
  pinMode(ms,INPUT_PULLUP);
  analogWrite(cs,contrast);
  analogWrite(bl,backlight);
  now=millis();
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LCDLight, OUTPUT);
  digitalWrite(LCDLight, HIGH);
  
  lcd.begin(16, 2);
  lcd.createChar(0, menuCursor);
  lcd.createChar(1, downArrow);
  lcd.createChar(2, leftArrow);
  lcd.createChar(3, rightArrow);
}

void loop() {
  
mainMenu();
Buttons();
}
void mainMenu() {
if (menuPage == 0) {
  drawCursor();
  lcd.setCursor(1,0);
  lcd.print(menuItems[menuPage]); //sesore
  lcd.setCursor(1,1);
  lcd.print(menuItems[menuPage +1]);//clock
} 
  if (menuPage == 1 ) {
  subMenu1();
  } 
  if (menuPage == 2 ) {   
  subMenu2();
  }
}

void drawCursor() {
  for (int cursorPos = 0; cursorPos < 1; cursorPos++) { // Erases current cursor
    lcd.setCursor(0, cursorPos);
    lcd.print(" ");
  } 
  if(menuPage == 0) {
    if (cursorPosition  == 0) { //shows cursor 1st line
     lcd.setCursor(0,0);
     lcd.write(byte(0));
    }
    if(cursorPosition == 1 ) { //shows cursor 2nd line
      lcd.setCursor(0,1);
      lcd.write(byte(0));
    }
 }
} 
void Buttons() {
  int s1=S1.pressed();
  int s2=S2.pressed();
  int s3=S3.pressed();
  if(menuPage == 0){
    if (cursorPosition == 1 && s1) { 
           lcd.clear();
           cursorPosition --;         
          }
    if (cursorPosition  == 0 && s3) { 
           lcd.clear();
           cursorPosition ++;
          }
  
     if ( s2 && cursorPosition  == 0) {
        lcd.clear();
        menuPage=1; 
        }
     if ( s2 && cursorPosition  == 1) {
        lcd.clear();
        menuPage=2; 
        }

  }else if (menuPage == 1 ){
      if(s2) {
        lcd.clear();
        menuPage=0;
      }
      if(s3){
          h=h+1;
      }
      if(s1){
          m=m+1;  
      }
   }else if (menuPage == 2 ){
      if(s2) {
        lcd.clear();
        menuPage=0;
      }   
}
}

void subMenu1(){ // clock
  
 lcd.begin(16,2);
 lcd.setCursor(0,0);
 lcd.print("Time ");
 if(h<10)lcd.print("0");
 lcd.print(h);
 lcd.print(":");
 if(m<10)lcd.print("0");
 lcd.print(m);
 lcd.print(":");
 if(s<10)lcd.print("0");
 lcd.print(s);
 if(flag==0) lcd.print(" AM");
 if(flag==1) lcd.print(" PM");
 lcd.setCursor(0,1);// for Line 2
 lcd.print("Precision clock");
 if(millis()-last_time>=1000){  
  last_time+=1000;
  s++;
 }
 if(s==60){
  s=0;
  m=m+1;
 }
 if(m==60)
 {
  m=0;
  h=h+1;
 }
 if(h==13)
 {
  h=1;
  flag=flag+1;
  if(flag==2)flag=0;
 }
delay(200);
}
void subMenu2() {  //sensore
  
  delay(100);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Distance: ");
  lcd.print(distanceCm); 
  lcd.print("cm");
  delay(10);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration*0.034/2;
  
  if (distanceCm<=3 ){
        lcd.setCursor(15,0);
        lcd.write(byte (1));
  }
  else if (distanceCm>=3 && distanceCm<=4){
        lcd.setCursor(10,1);
          lcd.write(byte (2));
        lcd.setCursor(6,1);
          lcd.write(byte (3));
            delay(200);
  }
  else if (distanceCm>=5 && distanceCm<=6){
        lcd.setCursor(10,1);
          lcd.write(byte (2));
        lcd.setCursor(6,1);
          lcd.write(byte (3));
            delay(200);
  }
  else if (distanceCm>=7 && distanceCm<=8){
        lcd.setCursor(11,1);
          lcd.write(byte (2));
        lcd.setCursor(5,1);
          lcd.write(byte (3));
            delay(200);

  }
  else if (distanceCm>=9 && distanceCm<=10){
        lcd.setCursor(12,1);
          lcd.write(byte (2));
        lcd.setCursor(4,1);
          lcd.write(byte (3));
            delay(200);

  }
  else if (distanceCm>=11 && distanceCm<=12){
        lcd.setCursor(13,1);
          lcd.write(byte (2));
        lcd.setCursor(3,1);
          lcd.write(byte (3));
            delay(200);

  }
  else if (distanceCm>=13 && distanceCm<=14){
        lcd.setCursor(14,1);
          lcd.write(byte (2));
        lcd.setCursor(2,1);
          lcd.write(byte (3));
            delay(200);

  }
  else if (distanceCm>=15 && distanceCm<=16){
        lcd.setCursor(15,1);
          lcd.write(byte (2));
        lcd.setCursor(1,1);
          lcd.write(byte (3));
            delay(200);

  }
  else if (distanceCm>=17 && distanceCm<=18){
        lcd.setCursor(16,1);
          lcd.write(byte (2));
        lcd.setCursor(0,1);
          lcd.write(byte (3));
            delay(200);

  }
  else if (distanceCm >13){
      lcd.clear();
  }
}
