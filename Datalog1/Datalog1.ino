/********************************************************************/
// First we include the libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <SPI.h>
#include <SD.h>

// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2 

const int chipSelect = 4;

// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 


// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 
void setup(void) 
{ 
 // start serial port 
 Serial.begin(9600); 
   while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 
 sensors.begin(); 
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
} 
void loop() 
{ 


 Serial.print(" Requesting temperatures..."); 
 sensors.requestTemperatures(); // Send the command to get temperature readings 
 Serial.println("DONE"); 
/********************************************************************/
// AMBIENT TEMP //
 Serial.println("Ambient temp is: "); 
 Serial.println(sensors.getTempFByIndex(0));
 Serial.println();

File dataFile=SD.open("AMB_TEMP.TXT", FILE_WRITE);
 dataFile.println(sensors.getTempFByIndex(0));
 dataFile.close();
/********************************************************************/
// PCM TEMP //
 Serial.println("PCM temp is: ");
 Serial.println(sensors.getTempFByIndex(1));
 Serial.println();

File dataFile2=SD.open("PCM_TEMP.TXT", FILE_WRITE);
 dataFile2.println(sensors.getTempFByIndex(1));
 dataFile2.close();
/********************************************************************/
// VOLTAGE //
 int voltage=analogRead(A0);
 voltage=map(voltage, 0, 1023, 0, 25000);
 Serial.println("voltage (mV): ");
 Serial.println(voltage);
 Serial.println();

File dataFile3=SD.open("VOLTAGE.TXT", FILE_WRITE);
 dataFile3.println(voltage);
 dataFile3.close();

/********************************************************************/
// CURRENT //
 int current=analogRead(A2);
 current=map(current, 102, 921, -5000, 5000);
 Serial.println("Current(mA): ");
 Serial.println(current);
 Serial.println();

 File dataFile4=SD.open("CURRENT.TXT", FILE_WRITE);
 dataFile4.println(current);
 dataFile4.close();
 
/********************************************************************/

 
   delay(5000); 
} 
