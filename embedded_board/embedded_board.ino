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
#define COMMAND_DELIMITER  '$'
#define READ_TABLE_CMD     "R"
#define WRITE_TABLE_CMD    "W"
#define TABLE_START        "S"
#define TABLE_END          "E"

// Macros to define the length of the data arrays
#define IR_LENGTH       5
#define BUMP_LENGTH     3
#define BRUSH_LENGTH    3
#define DISTANCE_LENGTH 4

// Global variables holding the sensor data
// these will be populated and maintained by
// the embedded team
byte irSensor[IR_LENGTH]              = {8,9,10,11,12};
byte bumpSensor[BUMP_LENGTH]          = {1,2,3};
byte brushCurrentSensor[BRUSH_LENGTH] = {35, 45, 57};
byte brushTempSensor[BRUSH_LENGTH]    = {42, 25, 12};
byte brushPositionSensor[BRUSH_LENGTH]= {51, 56, 90};
byte distanceSensor[DISTANCE_LENGTH]  = {4,5,6,7};

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
  if( cmd == READ_TABLE_CMD )
  {
    SendTable();
  }
  else if( cmd == WRITE_TABLE_CMD )
  {
    WriteTable();
  }
}

// ---- Write the data from the serial port to teh table ----
void WriteTable() 
{
  // Update all the sensor arrays
  UpdateSensorData(bumpSensor, BUMP_LENGTH);
  UpdateSensorData(irSensor, IR_LENGTH);
  UpdateSensorData(distanceSensor, DISTANCE_LENGTH);
  UpdateSensorData(brushCurrentSensor, BRUSH_LENGTH);
  UpdateSensorData(brushTempSensor, BRUSH_LENGTH);
  UpdateSensorData(brushPositionSensor, BRUSH_LENGTH);
}

// ---- Update the sensor data with new data ----
void UpdateSensorData(byte sensors[], int num_sensors)
{
   // Loop through the sensor array and
   // read in a byte from the serial port 
   // and update the sensor array
  for(int i=0; i < num_sensors; i++) {
    // Read in the current byte
    sensors[i] = Serial.read();
    Serial.println(sensors[i]);
    delay(10);
  }
}

// ---- Send the table data over the serial port ----
void SendTable() 
{
  // Send beginning of table id
  Serial.println(TABLE_START);

  // Send all the sensor data
  SendSensorData(bumpSensor, BUMP_LENGTH);
  SendSensorData(irSensor, IR_LENGTH);
  SendSensorData(distanceSensor, DISTANCE_LENGTH);
  SendSensorData(brushCurrentSensor, BRUSH_LENGTH);
  SendSensorData(brushTempSensor, BRUSH_LENGTH);
  SendSensorData(brushPositionSensor, BRUSH_LENGTH);
}

// ---- Send the sensor data over the serial port ----
void SendSensorData(byte sensors[], int num_sensors)
{
  // Loop through the sensor array and
  // send each byte over the serial port
  for(int i=0; i < num_sensors; i++) {
    // Print the current byte of the bumpSensor
    Serial.println(sensors[i]);
    delay(10);
  }
}
