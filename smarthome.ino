#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 6, 5, 4, 3);


int redLed = 13;
int alarm = 8;
int sensor = A0;
int pir=7;
int lamp=10;
int uSonic = 9;
int temp = A1;

//values

//gas threshold
int starter = 400;
//pir
int motion=0;

long duration, inches, cm;

void setup()
{
  lcd.begin(16, 2);
  pinMode(redLed, OUTPUT);
  pinMode(alarm, OUTPUT);
  pinMode(lamp, OUTPUT);
  pinMode(pir, INPUT);
  pinMode(sensor, INPUT);
  pinMode(temp, INPUT);
  pinMode(2, INPUT);
  digitalWrite(lamp, HIGH);
  
  attachInterrupt(0, safetyButton, RISING);
  
  Serial.begin(9600);
  
}

void loop()
{
  
 
  pinMode(uSonic, OUTPUT);
  digitalWrite(uSonic, LOW);
  delayMicroseconds(2);
  digitalWrite(uSonic, HIGH);
  delayMicroseconds(2);
 
  digitalWrite(uSonic, LOW);
 
  pinMode(uSonic, INPUT);
  duration = pulseIn(uSonic, HIGH);
 
  cm = microsecondsToCentimeters(duration);
  cm = cm +2;

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  if(cm<50){
    lcd.setCursor(0,0);
    lcd.print("             ");
    lcd.setCursor(0,0);
    lcd.print("at the door");
  }else{
    lcd.setCursor(0,0);
    lcd.print("           ");
  }
  //smoke detector
  int gasValue = analogRead(sensor);
  //motion deecotr
  motion = digitalRead(pir);
  //temperature seneor
  float tempValue = ((analogRead(temp)*(5.0/1024))-0.5)/0.01;
  Serial.println(tempValue);
  lcd.setCursor(0,1);
  lcd.print(tempValue);
  delay(500);
  if(gasValue>starter)
  {
    digitalWrite(redLed,HIGH);
    tone(alarm,1000,10000);
    delay(1000);
  }
  else{
    digitalWrite(redLed,LOW);
    noTone(alarm);
    delay(1000);
  
}if(motion==HIGH)
  {
    digitalWrite(lamp, LOW);
    delay(5000);
  }
  else{
    digitalWrite(lamp,HIGH);
  }
}
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
void safetyButton(){
  	lcd.clear();
    digitalWrite(redLed,HIGH);
    tone(alarm,100000,10000);
  	lcd.print("fire detected");
    delay(7000);
  }
