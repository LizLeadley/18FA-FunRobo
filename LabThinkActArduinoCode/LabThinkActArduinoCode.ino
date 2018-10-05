/////////////////////////////////////////////////////////////////
//Title: Act Arduino
//Description: Act Slave Arduino, serially connected (w/ digital pins
//10,11) to Master Arduino Think
//
//Robot Name: Tugboat
//What does code do: Code will simple serial connect Act Arduino 
//to Think arduino (not sense) sending data and recieving commands
//
//Hardware Warnings:
//Created by Team Think
/////////////////////////////////////////////////////////////////

//Libraries

#include <SoftwareSerial.h> //includes software serial library
#include <Servo.h>

//////////////////////////SETUP///////////////////////////

//Sets up Simple Serial communication
SoftwareSerial senseSerial(10,11); //connects act arduino to think arduino using pins 10 & 11

Servo rudder;
Servo table;
Servo prop;
int rudderPin = 5; //which pin is the rudder plugged into?
int tablePin = 3; // not correct
int propPin = 6; // also not correct yet
int redPin = 7;
int greenPin = 8;
int bluePin = 9;

int angle = 0;
int sign = 0;
int propSpeed = 0;
int tableSpeed = 0;

String data = "";

void setup() 
{
  // put your setup code here, to run once:
  senseSerial.begin(9600); //sets baud rate for act to 9600
  //actSerial has same name in think and act arduinos
  //not attach the servos and motors. the motors act like continuous rotation servos
  Serial.begin(9600);
  //Serial.setTimeout(20);
  rudder.attach(rudderPin);
  table.attach(tablePin);
  prop.attach(propPin);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  

}

////////////////////////MAIN LOOP////////////////////////////

void loop() {
  if (senseSerial.available()>0) //if any data sent through connection
    {
      
      
      Serial.println(senseSerial.read());
    }

    //parse the data from serial into an angle and a speed
    angle = parseAngle(data);
    propSpeed = parseSpeed(data);

    Serial.println(angle);
    //Serial.println(propSpeed);

    //set the motors and servos to match that speed and angle
    //then set the color of the LED
    setActuators(angle, propSpeed);
    setLight(angle);

    //reset data to nothing
}

//////////////////////END OF MAIN LOOP///////////////////////////////////

/////////////////////////FUNCTIONS///////////////////////////////////////

void setActuators(int angle, int propSpeed)
{
  rudder.write(-angle);//the rudders go to the opposite angle from the
  prop.write(propSpeed);
  tableSpeed = angle + 90; //this yields a number from 0 to 180, 
  //which is what the table can take as a speed. A negative angle will 
  //make the motor turn backwards, and vice versa.
  //we may have to divide this to scale it down so the table doesn't 
  //move too fast.
  table.write(tableSpeed);
}

int parseAngle(String data)
{
  
  String signStr = data.substring(0,1); //the first character is the sign of the angle
  String angleStr = data.substring(1,3); //the second and third are the heading angle
  
  //make all those substrings of the input into integers so they can be used
  
  sign = signStr.toInt();
  angle = angleStr.toInt();
  
    if (angle > 90)
    {
      angle = 90; //the servos won't be able to do anything bigger than this
      //the angle 90 may need to change later to be smaller.
    }

    if (!sign) //if the sign character is 0, the angle should be negative
    {
      angle = -angle; //make the angle negative
    }
    
  return angle;
}

int parseSpeed(String data)
{
  String speedStr = data.substring(3); //the last three are the speed from 00 to 99

  //make the substring of the input into an integer so it can be used
  propSpeed = speedStr.toInt();

  return propSpeed;
}

void setLight(int angle)
{
  //first turn all the lights off
  analogWrite(redPin,0);
  analogWrite(greenPin,0);
  analogWrite(bluePin,0);
  if(angle > 0)
  {
    analogWrite(bluePin,255);
  }
  else if(angle < 0)
  {
    analogWrite(greenPin,255);
  }
  //Serial.println("I just set the light");
}
