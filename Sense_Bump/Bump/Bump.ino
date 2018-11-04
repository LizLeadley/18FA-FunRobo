/*
 * Detects bumps and prints out the side and angle the bump came from in the serial monitor
 * 
 * Bumps are when the magnitude of the ax and ay accelerometer values are greater than a specified threshold
 * 
 * Overall objective - to be able to detect bumps from any side of the table with the IMU in any orientation (transform force vector reading from IMU frame to global frame)
 * 
 * Current Progress: Can detect bumps, axes converted to conventional RH axes with positive CCW rotation, matrix math started but unfinished 
 */

// Include Libraries
#include <NineAxesMotion.h>        //Contains the bridge code between the API and the Arduino Environment
#include <Wire.h>
#include <MatrixMath.h>            //Contains code for matrices

// Global Vars - Used for reading/saving IMU dat
NineAxesMotion mySensor;             //Object that for the sensor
unsigned long lastStreamTime = 0;    //To store the last streamed time stamp
const int streamPeriod = 40;         //To stream at 25Hz without using additional timers (time period(ms) =1000/frequency(Hz))
bool updateSensorData = true;        //Flag to update the sensor data. Default is true to perform the first read before the first stream
bool printData = true;               //Flag to print IMU data to serial monitor
const float threshold = 1.5;         //Threshold to classify as bump in m/s^2
float ax,ay,az,rx,ry,rz;             //Variables to save accelerometer and gyro readings

// Matrices
mtx_type A[3];      //Saves accelerometer data
mtx_type R[3];      //Saves gyro data
mtx_type B[3][3];   //TODO: Use this to store rotation matrix

// Functions
float vectorMag();              //Computes the magnitude of a vector in the x-y plane
float computeBumpAngle();       //Computes the angle of a vector in the x-y plane
int classifyBump(float angle);  //Determines which side the bump came from based on angle reading

void setup() //This code is executed once------------------------------------------------
{
  //Peripheral Initialization
  Serial.begin(9600);                               //Initialize the Serial Port to view information on the Serial Monitor
  I2C.begin();                                      //Initialize I2C communication to the let the library communicate with the sensor.
  //Sensor Initialization
  mySensor.initSensor();                            //The I2C Address can be changed here inside this function in the library
  mySensor.setOperationMode(OPERATION_MODE_NDOF);   //Can be configured to other operation modes as desired
  mySensor.setUpdateMode(MANUAL);                   //The default is AUTO. Changing to manual requires calling the relevant update functions prior to calling the read functions
  //Setting to MANUAL requires lesser reads to the sensor
  mySensor.updateAccelConfig();
  updateSensorData = true;
  
  Serial.println();
  Serial.println("Default accelerometer configuration settings...");
  Serial.print("Range: ");
  Serial.println(mySensor.readAccelRange());
  Serial.print("Bandwidth: ");
  Serial.println(mySensor.readAccelBandwidth());
  Serial.print("Power Mode: ");
  Serial.println(mySensor.readAccelPowerMode());
}

void loop() //This code is looped forever-------------------------------------------------
{
  if (updateSensorData)  //Keep the updating of data as a separate task
  {
    mySensor.updateAccel();        //Update the Accelerometer data
    mySensor.updateEuler();        //Update the Euler data into the structure of the object
    mySensor.updateCalibStatus();  //Update the Calibration Status

    ax = -mySensor.readAccelerometer(X_AXIS); //Convert to RH axes
    ay = -mySensor.readAccelerometer(Y_AXIS);
    az = -mySensor.readAccelerometer(Z_AXIS); 
    A[0] = ax;   //Save accelerometer data in A matrix
    A[1] = ay;
    A[2] = az;

    rx = -mySensor.readEulerPitch(); //Convert to RH axes
    ry = -mySensor.readEulerRoll();
    rz = 360-mySensor.readEulerHeading(); 
    R[0] = rx;   //Save orientation data in R matrix
    R[1] = ry;
    R[2] = rz;

    if (vectorMag() > threshold){
      Serial.print("Bump"); //Classify bumps greater in magnitude than the threshold as a bump
      float angle = computeBumpAngle();
      Serial.print(angle);
      int side = classifyBump(angle);
      if (side == 1){
        Serial.print("Front");
      }
      if (side == 2){
        Serial.print("Left");
      }
      if (side == 3){
        Serial.print("Back");
      }
      if (side == 4){
        Serial.print("Right");
      }
      if (side == 0){
        Serial.print("Bump detected, direction unkown");
      }
      delay(2000); // Wait for 2 seconds - prevents multiple bumps from being detected at once
    }
 
    updateSensorData = false;
  }
  if ((millis() - lastStreamTime) >= streamPeriod)
  {
    lastStreamTime = millis();

  if (printData == true)
  {
    Serial.print("Time: ");
    Serial.print(lastStreamTime);
    Serial.print("ms ");

    Serial.print("      aX: ");
    Serial.print(ax); //Accelerometer X-Axis data
    Serial.print("m/s2 ");

    Serial.print(" aY: ");
    Serial.print(ay);  //Accelerometer Y-Axis data
    Serial.print("m/s2 ");

    Serial.print(" aZ: ");
    Serial.print(az);  //Accelerometer Z-Axis data
    Serial.print("m/s2 ");

    Serial.print(" P: ");
    Serial.print(rx); //Pitch data
    Serial.print("deg ");
    
    Serial.print(" R: ");
    Serial.print(ry); //Roll data
    Serial.print("deg");

    Serial.print(" H: ");
    Serial.print(rz); //Heading data
    Serial.print("deg ");

    Serial.print("      C: ");
    Serial.print(mySensor.readAccelCalibStatus());  //Accelerometer Calibration Status (0 - 3)
    Serial.println();
  }

    updateSensorData = true;
  }
}

// Functions----------------------------------------------------------------------------
float vectorMag() 
{
  float mag = sqrt(pow(A[0],2) + pow(A[1],2));
  return mag;
}

float computeBumpAngle()
{
  float angle = 180/PI*atan2(A[0]*PI/180,A[1]*PI/180); // Also convert from degrees to radians
  return angle;
}

int classifyBump(float angle)
{
  // 0 none, 1 front, 2 left, 3 back, 4 right
  if (abs(angle) > 160)
  {
    return 1;
  }
  else if((abs(angle)-90)<20 && angle<0)
  {
    return 2;
  }
  else if(abs(angle<20))
  {
    return 3;
  }
  else if((abs(angle)-90)<20 && angle>0)
  {
    return 4;
  }
  else
  {
    return 0;
  }
}


/*
rotateFrameGlobal(accelArray, rotArray) //- takes array of accelerometer data and array of heading, roll, pitch and modifies array to global frame
 *    xRotMatrix = [] // Pitch - 
 *    yRotMatrix = [] // Roll
 *    zRotMatrix = [] // Heading
 *    
 *    //Order to undo rotation - roll, pitch, heading
 *    //TODO: Need this function
 *    MatrixMult(accelArray, yRotMatrix(rotArray[1]))
 *    MatrixMult(accelArray, xRotMatrix(rotArray[0]))
 *    MatrixMult(accelArray, zRotMatrix(rotArray[2]))
 *    
  */
