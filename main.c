#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,7,6,5,4);
const int UltrasonikTrig1 = 3;
const int UltrasonikEcho1 = 13;
const int UltrasonikTrig2 = 9;
const int UltrasonikEcho2 = 2;
const int Indikator = 8;

void setup() {
  Serial.begin(9600);
  pinMode(UltrasonikTrig1, OUTPUT);  
  pinMode(UltrasonikEcho1, INPUT);
  pinMode(UltrasonikTrig2, OUTPUT);  
  pinMode(UltrasonikEcho2, INPUT);
  pinMode(Indikator, OUTPUT); 
  lcd.begin(16,2);
}
long duration1,duration2 ; 
long cm1,cm2 ;
 
void loop()
{
  digitalWrite(UltrasonikTrig1, LOW);
  digitalWrite(UltrasonikTrig1, HIGH);
  digitalWrite(UltrasonikTrig2, LOW);
  digitalWrite(UltrasonikTrig2, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(UltrasonikTrig1, LOW);
  duration1 = pulseIn(UltrasonikEcho1, HIGH);
  digitalWrite(UltrasonikTrig2, LOW);
  duration2 = pulseIn(UltrasonikEcho2, HIGH);
  cm1 = microsecondsKeCenti(duration1);
  cm2 = microsecondsKeCenti(duration2);
  Serial.print("Sensor 1 : ");
  Serial.print(cm1);
  Serial.print(" cm");
  Serial.print(" || ");
  Serial.print("Sensor 2 : ");
  Serial.print(cm2);
  Serial.print(" cm");
  Serial.print(" || ");
  // if the distance less than 100 cm / 1 meter
  if (cm1 <= 100) 
	{
//    Serial.print(" 1 too close ");
   	digitalWrite(Indikator, HIGH);
    lcd.setCursor(2,0);
    lcd.print("front side");
    delay(100);
    lcd.clear();
  	}
  else if (cm2 <= 100) 
	{
//    Serial.print(" 2 to close ");
   	digitalWrite(Indikator, HIGH);
    lcd.setCursor(2,0);
    lcd.print("rear side");
    delay(100);
    lcd.clear();
  	}
  else
  	{
    digitalWrite(Indikator, LOW);
  	}
  Serial.println(" || "); 
  delay(100);
}
long microsecondsKeCenti(long microseconds)
{
  return microseconds / 29 / 2;
}