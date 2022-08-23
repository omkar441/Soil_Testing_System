#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12,11,5,4, 3, 2);
#define SensorPin 0          // the pH meter Analog output is connected with the Arduino’s Analog
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10],temp;
int SensorPin1 = A5;
 
void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  
  lcd.setCursor(2,0);
  lcd.print("pH Value:");
  lcd.setCursor(0,1);
  lcd.print("Moisture %:");
}

void loop()
{
  
  float SensorValue = analogRead(SensorPin1)*0.09775171;   
  float Moistureper = 100-SensorValue; 
  Serial.print(" Moisture % = ");
  Serial.println(Moistureper);  
   lcd.setCursor(12, 1);  
  lcd.print(Moistureper);
  
  for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=3.5*phValue;                      //convert the millivolt into pH value
  Serial.print(" pH = ");
  Serial.println(phValue);
  lcd.setCursor(12, 0);  
  lcd.print(phValue);       
  delay(800);
}
