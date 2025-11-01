
#include <Wire.h>
#include <Servo.h>



///////////////////////Inputs/outputs///////////////////////
int Analog_in = A0;
Servo myservo;  // create servo object to control a servo, later attatched to D9
///////////////////////////////////////////////////////


////////////////////////Variables///////////////////////
int Read = 0;
double distance = 0.0;
//float elapsedTime;        //Variables for time control
double previous_error, error;
int period = 50;  //Refresh rate period of the loop is 50ms
unsigned long previous_time;
//////////////////////////////////////////////////////

///////////////////PID constants///////////////////////
double kp=2.3; //Mine was 8
double ki=5; //Mine was 0.2
double kd=2; //Mine was 3100
double  distance_setpoint = 15.5;           //Should be the distance from sensor to the middle of the bar in mm
double  integral, derivative, PID_total,PID_i;
///////////////////////////////////////////////////////



void setup() {
  //analogReference(EXTERNAL);
  Serial.begin(9600);  
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(90); //Put the servco at angle 125, so the balance is in the middle
  pinMode(Analog_in,INPUT);  
  previous_time = millis();
}

void loop() {
    unsigned long current_time = millis();
    double time_elapsed = (current_time - previous_time) / 1000.0;
    previous_time = current_time;
    
    distance = get_dist(100);   
    error = distance_setpoint - distance;   
//    Serial.println(error);
    derivative = (error - previous_error) / time_elapsed;
    integral += error * time_elapsed; 
     
    if(-3 < error && error < 3)
    {
      PID_i =(ki * integral);
    }
    else
    {
      PID_i = 0;
    }
  
    PID_total = (kp * error) + (PID_i) + (kd * derivative);
    Serial.println(PID_total);
    PID_total = map(PID_total, -150, 150, 0, 180);
  
    if(PID_total < 0){PID_total = 0;}
    if(PID_total > 170) {PID_total = 170; } 

    
    myservo.write(PID_total);  
    previous_error = error;
    delay(25);
     
}











float get_dist(int n)
{
  long sum=0;
  for(int i=0;i<n;i++)
  {
    sum=sum+analogRead(Analog_in);
  }  
  float adc=sum/n;
  //float volts = analogRead(adc)*0.0048828125;  // value from sensor * (5/1024)
  //float volts = sum*0.003222656;  // value from sensor * (3.3/1024) EXTERNAL analog refference

  float distance_cm = 17569.7 * pow(adc, -1.2062);
  //float distance_cm = 13*pow(volts, -1); 
//  Serial.println(distance_cm);
  return(distance_cm);
}
