/*
 * 
 *        IRC readout for KSM microscope
 *        
 *        
                     Mighty 1284p    
                      +---\/---+
           (D 0) PB0 1|        |40 PA0 (AI 0 / D24)
           (D 1) PB1 2|        |39 PA1 (AI 1 / D25)
      INT2 (D 2) PB2 3|        |38 PA2 (AI 2 / D26)
       PWM (D 3) PB3 4|        |37 PA3 (AI 3 / D27)
    PWM/SS (D 4) PB4 5|        |36 PA4 (AI 4 / D28)
      MOSI (D 5) PB5 6|        |35 PA5 (AI 5 / D29)
  PWM/MISO (D 6) PB6 7|        |34 PA6 (AI 6 / D30)
   PWM/SCK (D 7) PB7 8|        |33 PA7 (AI 7 / D31)
                 RST 9|        |32 AREF
                VCC 10|        |31 GND
                GND 11|        |30 AVCC
              XTAL2 12|        |29 PC7 (D 23)
              XTAL1 13|        |28 PC6 (D 22)
      RX0 (D 8) PD0 14|        |27 PC5 (D 21) TDI
      TX0 (D 9) PD1 15|        |26 PC4 (D 20) TDO
RX1/INT0 (D 10) PD2 16|        |25 PC3 (D 19) TMS
TX1/INT1 (D 11) PD3 17|        |24 PC2 (D 18) TCK
     PWM (D 12) PD4 18|        |23 PC1 (D 17) SDA
     PWM (D 13) PD5 19|        |22 PC0 (D 16) SCL
     PWM (D 14) PD6 20|        |21 PD7 (D 15) PWM
                      +--------+
*/

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define F1  2
#define F2  25
#define LED 20  

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

void setup()
{
  pinMode(F1, INPUT);  // Set the IRC phases as input
  pinMode(F2, INPUT);  
  
  pinMode(LED, OUTPUT);  
  
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  //lcd.setCursor(0,0);
  //lcd.print("Hello, world!");
  //lcd.setCursor(0,1);
  //lcd.print("KSM");
  //delay(1000);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("KSM"); 

  attachInterrupt(F1, interrupt, FALLING); 
}

long axis = 0;
boolean oldPhase = digitalRead(F1);
boolean phase = digitalRead(F1); 

void loop()
{
  lcd.setCursor(2,1);  
  if (axis<0)
  {
    lcd.setCursor(2,1);  
  }
  else
  {
    lcd.setCursor(2,1);  
    lcd.print('+');
  }
  lcd.print(axis);
  lcd.print(" ");

  while (digitalRead(F1));
  while (!digitalRead(F1));
}

void interrupt()
{
  if(digitalRead(F2))
  {
    axis++;
  }
  else
  {
    axis--;
  }  
}
