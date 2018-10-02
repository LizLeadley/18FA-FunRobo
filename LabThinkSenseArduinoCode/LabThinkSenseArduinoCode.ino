////////////////////////////////////////////////
//Title: Sense Arduino
//Description: Sense Slave Arduino, serially connected (w/ digital pins
////12,13) to Master Arduino Think
//Robot Name?: Boat?
//What does code do: Code will simple serial connect Sense Arduino 
////to Think arduino (not act) sending data and recieving commands
//Hardware Warnings:
//Created by Team Think
////////////////////////////////////////////////

///////////////////////////////
//Libraries
///////////////////////////////
#include <SoftwareSerial.h> //includes software serial library
///////////////////////////////

//Sets up Simple Serial communication
SoftwareSerial senseSerial(12,13); //connects sense arduino to think arduino using pins 12 & 13

void setup() {
  // put your setup code here, to run once:
  senseSerial.begin(9600); //sets baud rate for sense to 9600
  //senseSerial has same name in think and sense arduinos
}

void loop() {
  // put your main code here, to run repeatedly:

  ////////////////////////////////////////
  //Basic softSerial Code
  ////////////////////////////////////////
  if (senseSerial.available()>0) //if any data sent through connection
  {
    senseSerial.read(); //read and return data sent
  }
  senseSerial.println("Message to Think Arduino");//Prints data to the transmit pin of the Sense software serial port
  senseSerial.write("hello think"); //Prints data to the transmit pin of the software serial port as raw bytes.
  ////////////////////////////////////////

  ////////////////////////////////////////
  //Basic Sense Actions Following
  ////////////////////////////////////////

  //read data from think arduino  (probably passive)
  //what data need to be sent to sense arduino?
  //sensor initialization?
  //if sense unusual print specific thing?
  
  //send data to think arduino    (probably active)
  //different data sent for IR sensors and pixy and other
  ////////////////////////////////////////
}
