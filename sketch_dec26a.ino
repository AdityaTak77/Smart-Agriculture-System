#include "DHT.h"
#define DHTPIN 2     
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);
#include <Wire.h>               
#include <LiquidCrystal.h>  

LiquidCrystal lcd(7,8,9,10,11,12);
                                  
const int analogInPin = A5; //variable declare kiya jo a5 se connected h
int sensorValue = 0; 

#define SensorPin A0          
unsigned long int avgValue; 
float b;
int buf[10],temp;

void setup() {
  pinMode(13,OUTPUT);  
  lcd.begin(16, 2);
  Serial.begin(9600); 
  
              
  dht.begin();
}

void loop() {
   //////DHT sensor
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  lcd.setCursor(0,0);            
  lcd.print("H: ");
  lcd.print(h); 
  lcd.setCursor(0,1);
  lcd.print("T: ");
  
  lcd.print(t);
  lcd.print(" *C ");
  ///////soil moisture sensor
  delay(1000);
  
  delay(100);
  lcd.clear();
  lcd.print("Soil Moisture:");
  sensorValue = analogRead(analogInPin); 
  lcd.setCursor(0, 1); //lcd m kitni jgh par dhikhana h
  lcd.print(sensorValue);
  
  //Serial.println("\t");
  delay(1000);
  
  ////////ph sensor
  delay(1000);
  for(int i=0;i<10;i++) 
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
        // Serial.println(temp);
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; 
  phValue=3.5*phValue; 
  lcd.clear();                     
  lcd.print("pH:"); 
  //lcd.setCursor(8, 0);
  lcd.print(phValue);
  Serial.println(h);
  Serial.print("\t\t");
  Serial.print(phValue);
  Serial.print("\t");
  Serial.println(t);
  Serial.println("\t");
  Serial.println(sensorValue);
  delay(1000);
  Serial.print("\t");
  ///////
}
