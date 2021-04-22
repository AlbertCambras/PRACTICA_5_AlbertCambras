#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  //sometimes the LCD adress is not 0x3f. Change to 0x27 if it dosn't work.


byte customChar[] = {
  0x00,
  0x00,
  0x10,
  0x19,
  0x1F,
  0x19,
  0x10,
  0x00
};



void setup() {

  lcd.createChar(0, customChar);

  lcd.init();                 //Init the LCD
  lcd.backlight();            //Activate backlight
  
  lcd.clear();
  lcd.setCursor(1,0); 
  lcd.print("PRACTICA 5 ALBERT");
  delay(1000);
  lcd.setCursor(4,1);
  lcd.print("VERSIO 1.0");
  delay(1000);
}

void loop() {
  for(int i=0;i<20;i++){
    for(int j=0;j<4;j++){
      lcd.clear();
      lcd.setCursor(i,j);
      lcd.write(0);
      delay(300);
      i++;
      if(i==19){
        j++;
      }
    }
  }
}