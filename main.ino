#include <LiquidCrystal.h>
#include <dht11.h>
#include <SimpleDHT.h>
#define dirPin 4
#define stepPin 5
#include <AccelStepper.h>
#define motorInterfaceType 1

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);
int pinDHT11 = 2;
SimpleDHT11 dht11;
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void setup()
{
  Serial.begin(9600);
 lcd.begin(16,2);
  pinMode(3, OUTPUT); //connect relay to digital pin three 
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  stepper.setMaxSpeed(100);
  stepper.setAcceleration(50);
}

void loop()
{
  Serial.println("=================================");
  Serial.println("DHT11 readings...");
  
byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;

  //This bit will tell our Arduino what to do if there is some sort of an error at getting readings from our sensor
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) 
  {
    Serial.print("No reading , err="); Serial.println(err);
    delay(1000);
    return;
  }
  Serial.print("Readings: ");
  Serial.print((int)temperature); Serial.print(" Celcius, ");
  Serial.print((int)humidity); Serial.println(" %");
 
  //Telling our lcd to refresh itself every 0.75 seconds
  lcd.clear();
 
  //Choosing the first line and row
  lcd.setCursor(0,0);  //Typing Temp: to the first line starting from the first row
  lcd.print("Temp: ");  //Typing the temperature readings after "Temp: " 
  lcd.print((int)temperature);  //Choosing the second line and first row
  lcd.setCursor(0,1);  //Typing Humidity(%): to the second line starting from the first row
  lcd.print("Humidity(%): ");  //Typing the humidity readings after "Humidity(%): "
  lcd.print((int)humidity);  

  // LCD and DHT11 verification
  
  // Set the target position:
  stepper.moveTo(400);
  // Run to target position with set speed and acceleration/deceleration:
  stepper.runToPosition();

  delay(1000);

  // Move back to zero:
  stepper.moveTo(0);
  stepper.runToPosition();

  delay(1000);
  //stepper motor 

   if (((int)temperature) >= 20)
 { digitalWrite(3, HIGH); // turn relay ON, NO pin is on )
 delay(6000);}
  else
 { digitalWrite(3, LOW); 
 delay(6000); }// turn relay OFF  

}
