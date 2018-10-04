/**********************************************************************************
 * 
 * Title: 18FA FunRobo Serial Experiment
 * Description:
 *    *Practicing communication between c++ and arduino
 * Robot or hardware: Arduino Uno
 * This code will do the following:
 *    *Blink the light at c++ terminal's command
 * Hardware notes and warnings:
 *    *Don't use a VM
 * Created by: Liz Leadley
 * Edited by:
 * Conventions:
 *    *Strict camelCase naming without underscores
 * 
 *********************************************************************************/
 
 
char incomingByte = 0;   // for incoming serial data
int bright;


void setup()
{
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  pinMode(LED_BUILTIN, OUTPUT);

}

void
loop()
{

  // send data only when you receive data:
  if (Serial.available() > 0)
    {
      // read the incoming byte:
      incomingByte = Serial.read();

      digitalWrite(LED_BUILTIN, HIGH);
      delay(incomingByte*500);
      digitalWrite(LED_BUILTIN, LOW);
//      delay(incomingByte*500);
//
//      switch (incomingByte)
//        {
//      case '1':
//          digitalWrite(LED_BUILTIN, HIGH);
//          delay(1000);
//          digitalWrite(LED_BUILTIN, LOW);
//          delay(1000);   
//      case '2':
//        bright = 50;
//        break;
//      case '3':
//        bright = 255;
//        break;
//
//      default:
//        bright = 0;
//        break;
//        }

      Serial.println(incomingByte);
    }
}
