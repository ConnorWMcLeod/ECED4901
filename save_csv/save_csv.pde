 /**
 Saving Values from Arduino to a .csv File Using Processing (Processing is the IDE which runs Java code)
 
  This sketch provides a will read data from Arduino over the serial port and save it to .csv file on your computer.
  The .csv file will be saved in the same folder as your Processing sketch.
  This sketch takes advantage of Processing 2.0's built-in Table class.
  This sketch assumes that values read by Arduino are separated by commas, and each Arduino reading is separated by a newline character.
  Each reading will have it's own row and timestamp in the resulting csv file. This sketch will write a new file a set number of times.  
  
  Based on tutorial By Elaine Laguerta located at http://www.hackerscapes.com/2014/11/how-to-save-data-from-arduino-to-a-csv-file-using-processing/
 
*/
 
import processing.serial.*;
Serial myPort; //creates a software serial port on which you will listen to Arduino
Table table; //table where we will read in and store values. You can name it something more creative!
 
int numReadings = 10; //keeps track of how many readings you'd like to take before writing the file. 
int readingCounter = 0; //counts each reading to compare to numReadings. 
 
String fileName;

// Run once on startup
void setup()
{
  // Find the port with the arduino is 
  String portName = Serial.list()[1]; 
  
  // Setup a UART connection to the port with baud rate 9600
  myPort = new Serial(this, portName, 9600);
  table = new Table(); // Create a table to store data
  table.addColumn("id"); //This column stores a unique identifier for each record. We will just count up from 0 - so your first reading will be ID 0, your second will be ID 1, etc. 
  
  // The following adds columns for time. 
  table.addColumn("year");
  table.addColumn("month");
  table.addColumn("day");
  table.addColumn("hour");
  table.addColumn("minute");
  table.addColumn("second");
  
  // The following are dat columns. The "Result" is the raw adc value (0-2^16), and the Voltage is the converted reading after accounting for the power supply.
  table.addColumn("Result");
  table.addColumn("Voltage");
 
}

// Triggered when data is received over the serial connection
void serialEvent(Serial myPort){
  // Read data from the Arduino until a newline character is reached signifying the end of a record
  String val = myPort.readStringUntil('\n'); 
  if (val!= null) { //We have a reading! Record it.
    val = trim(val); //gets rid of any whitespace or Unicode nonbreakable space
    println(val); //Debugging statement to verify data is being received. 
    float sensorVals[] = float(split(val, ',')); // Data is sent as Comma Seperated values, break the string into each column
    TableRow newRow = table.addRow(); //add a row for this new reading
    newRow.setInt("id", table.lastRowIndex());//record a unique identifier (the row's index)
    
    //record time stamp
    newRow.setInt("year", year());
    newRow.setInt("month", month());
    newRow.setInt("day", day());
    newRow.setInt("hour", hour());
    newRow.setInt("minute", minute());
    newRow.setInt("second", second());
    
    // Record sensor information.
    newRow.setFloat("Result", sensorVals[0]);
    newRow.setFloat("Voltage", sensorVals[1]);
    
    // Counter of how many readings we taken
    readingCounter++;
    
    //saves the table as a csv in the same folder as the sketch every numReadings. 
    if (readingCounter % numReadings ==0)
    {
      fileName = str(year()) + "_" + str(month()) + "_" + str(day()) + "_" + str(table.lastRowIndex()) + ".txt"; //this filename is of the form year+month+day+readingCounter
      saveTable(table, fileName, "csv"); // Save data as CSV
   }
  }
}
