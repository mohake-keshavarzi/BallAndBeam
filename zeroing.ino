
#include <Wire.h>
#include <Servo.h>



///////////////////////Inputs/outputs///////////////////////
int Analog_in = A0;
Servo myservo;  // create servo object to control a servo, later attatched to D9
///////////////////////////////////////////////////////

int pos = 0; 

void setup() {
  //analogReference(EXTERNAL);
  Serial.begin(9600);  
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(90); //Put the servco at angle 125, so the balance is in the middle
  pinMode(Analog_in,INPUT);  
 
}

void loop() {
    
      myservo.write(90); 
      delay(100);           
    
}
