// @author  Isaac Marquez
// @date    March 4th, 2021
// @details testing prototype of how the embedded
//          microcontroller will respond to our
//          request for sensor data. 


//-------------------------------------------------
//-------------- GLOBAL VARIABLES -----------------
//-------------------------------------------------

// Macros of the command identifiers sending
// and recieving data over the serial port
#define COMMAND_DELIMITER      '$'
#define BRUSH_DATA_ID          "B"
#define SEND_BRUSH_DATA_CMD    "RB"
#define IR_DATA_ID             "I"
#define SEND_IR_DATA_CMD       "RI"
#define DISTANCE_DATA_ID       "D"
#define SEND_DISTANCE_DATA_CMD "RD"

// Macros to define the length of the data arrays
#define IR_LENGTH       5
#define BUMP_LENGTH     3
#define BRUSH_LENGTH    1
#define DISTANCE_LENGTH 4

// Global variables holding the sensor data
// these will be populated and maintained by
// the embedded team
byte irSensor[IR_LENGTH]             = {8,9,10,11,12};
byte bumpSensor[BUMP_LENGTH]         = {1,2,3};
byte brushSensor[BRUSH_LENGTH]       = {35};
byte distanceSensor[DISTANCE_LENGTH] = {4,5,6,7};

//-------------------------------------------------
//------------------- SET UP ----------------------
//-------------------------------------------------

void setup() {
  // Create the serial communcation at a baude rate of 9600
  Serial.begin(9600);
}

//-------------------------------------------------
//-------------------- LOOP -----------------------
//-------------------------------------------------

// Listen for commands comming from navigation
void loop() 
{
  // Don't read if the line is busy
  if (Serial.available() > 0) 
  {
    // Read until you recieve the command delimiter character
    String cmd = Serial.readStringUntil(COMMAND_DELIMITER);

    // Run the command 
    RunCommand(cmd);
  }
}

//-------------------------------------------------
//-------------- HELPER FUNCTIONS -----------------
//-------------------------------------------------

// ---- Run the inputed command ----
void RunCommand(String cmd)
{
  // Run the inputed commands corresponding functions
  if( cmd == SEND_BRUSH_DATA_CMD )
  {
    SendBrush();
  }
  else if( cmd == SEND_IR_DATA_CMD )
  {
    SendIR();
  }
  else if( cmd == SEND_DISTANCE_DATA_CMD )
  {
    SendDistance();
  }
}


// ---- Send the brush data over the serial port ----
void SendBrush() 
{
  // Send brush sensor id
  Serial.println(BRUSH_DATA_ID);

  // Loop through the brush sensor array and
  // send each byte over the serial port
  for(int i=0; i < BRUSH_LENGTH; i++) {
    // Print the current byte of the brushSensor
    Serial.println(brushSensor[i]);
    delay(10);
  }

  // Send the command delimiter
  Serial.println(COMMAND_DELIMITER);
}


// ---- Send the ir sensor data over the serial port ----
void SendIR() 
{
  // Send ir sensor id
  Serial.println(IR_DATA_ID + COMMAND_DELIMITER);

  // Loop through the irSensor array and
  // send each byte over the serial port
  for(int i=0; i < IR_LENGTH; i++) {
    // Print the current byte of the irSensor
    Serial.println(irSensor[i]);
    delay(10);
  }

   // Send the command delimiter
  Serial.println(COMMAND_DELIMITER);
}


// ---- Send the distance data over the serial port ----
void SendDistance() 
{
  // Send distance sensor id
  Serial.println(DISTANCE_DATA_ID);

  // Loop through the distanceSensor array and
  // send each byte over the serial port
  for(int i=0; i < DISTANCE_LENGTH; i++) {
    // Print the current byte of the distanceSensor
    Serial.println(distanceSensor[i]);
    delay(10);
  }

   // Send the command delimiter
  Serial.println(COMMAND_DELIMITER);
}
