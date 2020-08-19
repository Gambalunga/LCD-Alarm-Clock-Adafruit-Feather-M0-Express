/*

  Audio player, non blocking.
  read 8bit mono .wav file, up to 4 channels
  use Audacity to convert your audio file
  Author : AloyseTech with subsequent modifications by various people including,Hydronics and Gambalunga

  03/17/19: https://github.com/hydronics2/SamdAudio
    updated to work with Adafruit Qaud Flash memory boards.
    This will work with any SAMD21 chip using SPI flash with a little tinkering
     - itsyBitsy M0 Express, 
     - Feather M0 Express, 

   23/07/2020:
    updated to work with the current version of the Adafruit_SPIFlash library.
    Not tested but could probably be modified to function with an SD card.
    For use with an SD card refer to https://github.com/hydronics2/SamdAudio
    
     - Will not work with Adafruit Feather M4 Express and other boards with the SAMD51 processor 

    Read this great description in the Adafruit tutorial for getting the WAV files onto your Adafruit M0 Express board
    https://learn.adafruit.com/introducing-itsy-bitsy-m0?view=all#using-spi-flash
    Thanks to Tondy Dicola and Adafruit for making this so easy!

*/

#include <SPI.h>
#include <SdFat.h>
#include <Adafruit_SPIFlash.h>
#include <Audio_FeatherM0.h> // 

// On-board external flash (QSPI or SPI) macros should already
// defined in your board variant if supported
// - EXTERNAL_FLASH_USE_QSPI
// - EXTERNAL_FLASH_USE_CS/EXTERNAL_FLASH_USE_SPI
#if defined(EXTERNAL_FLASH_USE_QSPI)
  Adafruit_FlashTransport_QSPI flashTransport;

#elif defined(EXTERNAL_FLASH_USE_SPI)
  Adafruit_FlashTransport_SPI flashTransport(EXTERNAL_FLASH_USE_CS, EXTERNAL_FLASH_USE_SPI);

#else
  #error No QSPI/SPI flash are defined on your board variant.h !
#endif

Adafruit_SPIFlash flash(&flashTransport);

// file system object from SdFat
FatFileSystem fatfs;

SamdAudio AudioPlayer; 

#define NUM_AUDIO_CHANNELS 4 //could be 1,2 or 4 for sound

#define AUDIO_BUFFER_SIZE 1024 //512 works fine for 22.05kh, use 1024 for 32khz and 44.1khz

//indicate sample rate here (use audacity to convert your wav)
const unsigned int sampleRate = 32000; //hz

//your wav file
const char *filename0 = "sfx1_8bit_22khz.wav";
const char *filename1 = "sfx1_8bit_32khz.wav";
const char *filename2 = "sfx2_8bit_22khz.wav";
const char *filename3 = "sfx2_8bit_32khz.wav";
const char *filename4 = "sfx4_8bit_32khz.wav";

void setup()
{
  delay(10);
  Serial.begin(115200);
  while (!Serial); // open the serial to start!

 // Initialize flash library and check its chip ID.
  if (!flash.begin()) {
    Serial.println("Error, failed to initialize flash chip!");
    while(1);
  }
  Serial.print("Flash chip JEDEC ID: 0x"); Serial.println(flash.getJEDECID(), HEX);

  // First call begin to mount the filesystem.  Check that it returns true
  // to make sure the filesystem was mounted.
  if (!fatfs.begin(&flash)) {
    Serial.println("Failed to mount filesystem!");
    Serial.println("Was CircuitPython loaded on the board first to create the filesystem?");
    while(1);
  }
  Serial.println("Mounted filesystem!");

  
  Serial.print("Initializing Audio Player...");
  if (AudioPlayer.begin(sampleRate, NUM_AUDIO_CHANNELS, AUDIO_BUFFER_SIZE) == -1) 
  {
    Serial.println(" failed!");
    return;
  }
  Serial.println(" done.");

  AudioPlayer.play(filename0, 1);

  Serial.println("Playing file.....");
}


void loop()
{
  if (Serial.available()) 
  {
    char c = Serial.read();
    Serial.println(c); //for debug

    if ( c == 'o') 
    {
      AudioPlayer.play(filename1, 0); //playing file on channel 0
      Serial.println("playing audio file on channel 0");
    }
    if ( c == 'p') 
    {
      AudioPlayer.play(filename2, 1); //playing file  on channel 1
      Serial.println("playing audio file on channel 1");
    }
      if ( c == 'k') 
    {
      AudioPlayer.play(filename3, 2); //playing file on channel 2
      Serial.println("playing audio file on channel 2");
    }
      if ( c == 'l') 
    {
      AudioPlayer.play(filename4, 3); //playing file on channel 3
      Serial.println("playing audio file on channel 3");
    }    
  } 
}
