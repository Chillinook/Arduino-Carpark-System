#include <LiquidCrystal.h>
#include <Servo.h>

Servo myServo;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int LCDcontrast = 7;
int greLed = 8;
int redLed = 9;
int motorOut = 13;
int button = 41;
int echo = 50;
int trig = 51;

void setup()
{
  pinMode(redLed, OUTPUT);
  pinMode(greLed, OUTPUT);
  pinMode(button, INPUT);
  pinMode(LCDcontrast,OUTPUT);  
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  myServo.attach(motorOut);
  analogWrite(LCDcontrast,75);
  lcd.begin(16, 2);
}

void loop()
{
    digitalWrite(trig,LOW);
    delayMicroseconds(10);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);

    pinMode(echo,INPUT);
    long duration = pulseIn(echo,HIGH);  
    long cm = ( (duration / 2) / 29.1 );

    myServo.write(90);
  
    digitalWrite(redLed,LOW);
    digitalWrite(greLed,LOW);  

    if( (cm<20) && (digitalRead(button)==HIGH) )
    {
          digitalWrite(redLed,HIGH);
          lcd.setCursor(5,1);
          lcd.print("Get ticket");
          delay(4000);
          lcd.clear();

          digitalWrite(redLed,LOW);
          digitalWrite(greLed,HIGH);
          lcd.setCursor(5,1);
          lcd.print("Proceed");
          delay(400);
          for(int i = 90;i <= 180 ;i+=90 )
          {                        
              myServo.write(i);  
              delay(5000);                    
          }            
          for(int i = 180;i >= 90 ;i-=2 )
          {          
              myServo.write(i);  
              delay(200);                    
          }    
          lcd.clear();         
    }
    else if( (cm<20) )
    {
        digitalWrite(redLed,HIGH);
        lcd.setCursor(5,1);
        lcd.print("Welcome");
        delay(3000);
        lcd.clear();
    }
}