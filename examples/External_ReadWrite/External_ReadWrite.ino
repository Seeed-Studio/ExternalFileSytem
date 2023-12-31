#include <Adafruit_LittleFS.h>
#include <ExternalFileSystem.h>
#include <Adafruit_TinyUSB.h> // for Serial

using namespace Adafruit_LittleFS_Namespace;

#define FILENAME    "/adafruit.txt"
#define CONTENTS    "Adafruit Little File System test file contents"

File file(ExternalFS);

// the setup function runs once when you press reset or power the board
void setup() 
{
  Serial.begin(115200);
  while ( !Serial ) delay(10);   // for nrf52840 with native usb

  Serial.println("External Read Write File Example");
  Serial.println();

  // Wait for user input to run. Otherwise the code will 
  // always run immediately after flash and create the FILENAME in advance
  Serial.print("Enter to any keys to continue:");
  while ( !Serial.available() )
  {
    delay(1);
  }
  Serial.println();
  Serial.println();

  // Initialize External File System
  ExternalFS.begin();

  file.open(FILENAME, FILE_O_READ);

  // file existed
  if ( file )
  {
    Serial.println(FILENAME " file exists");
    
    uint32_t readlen;
    char buffer[64] = { 0 };
    readlen = file.read(buffer, sizeof(buffer));

    buffer[readlen] = 0;
    Serial.println(buffer);
    file.close();
  }else
  {
    Serial.print("Open " FILENAME " file to write ... ");

    if( file.open(FILENAME, FILE_O_WRITE) )
    {
      Serial.println("OK");
      file.write(CONTENTS, strlen(CONTENTS));
      file.close();
    }else
    {
      Serial.println("Failed!");
    }
  }

  Serial.println("Done");
}

// the loop function runs over and over again forever
void loop() 
{
}
