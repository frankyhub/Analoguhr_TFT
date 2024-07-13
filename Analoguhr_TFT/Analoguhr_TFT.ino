
/*************************************************************************************************
                                      PROGRAMMINFO
**************************************************************************************************
Funktion: Analog clock for Az-Touch Mod 2.4"-Display

**************************************************************************************************
Version: 13.07.2024
**************************************************************************************************
Board: ESP32 DEV Module
**************************************************************************************************
Libraries:
https://github.com/espressif/arduino-esp32/tree/master/libraries
C:\Users\User\Documents\Arduino
D:\gittemp\Arduino II\A156_Wetterdaten_V3
**************************************************************************************************
C++ Arduino IDE V1.8.19
**************************************************************************************************
Einstellungen:
https://dl.espressif.com/dl/package_esp32_index.json
http://dan.drown.org/stm32duino/package_STM32duino_index.json
http://arduino.esp8266.com/stable/package_esp8266com_index.json




***********************   User_Sertup.h  ****************************************

//                            USER DEFINED SETTINGS
//   Set driver type, fonts to be loaded, pins used and SPI control method etc
//
//   See the User_Setup_Select.h file if you wish to be able to define multiple
//   setups and then easily select which setup file is used by the compiler.
//
//   If this file is edited correctly then all the library example sketches should
//   run without the need to make any more changes for a particular hardware setup!
//   Note that some sketches are designed for a particular TFT pixel width/height


// ##################################################################################
//
// Section 1. Call up the right driver file and any options for it
//
// ##################################################################################

// Define STM32 to invoke optimised processor support (only for STM32)
//#define STM32

// Defining the STM32 board allows the library to optimise the performance
// for UNO compatible "MCUfriend" style shields
//#define NUCLEO_64_TFT
//#define NUCLEO_144_TFT

// STM32 8 bit parallel only:
// If STN32 Port A or B pins 0-7 are used for 8 bit parallel data bus bits 0-7
// then this will improve rendering performance by a factor of ~8x
//#define STM_PORTA_DATA_BUS
//#define STM_PORTA_DATA_BUS

// Tell the library to use 8 bit parallel mode (otherwise SPI is assumed)
//#define TFT_PARALLEL_8_BIT

// Display type -  only define if RPi display
//#define RPI_DISPLAY_TYPE // 20MHz maximum SPI

// Only define one driver, the other ones must be commented out
#define ILI9341_DRIVER
//#define ST7735_DRIVER      // Define additional parameters below for this display
//#define ILI9163_DRIVER     // Define additional parameters below for this display
//#define S6D02A1_DRIVER
//#define RPI_ILI9486_DRIVER // 20MHz maximum SPI
//#define HX8357D_DRIVER
//#define ILI9481_DRIVER
//#define ILI9486_DRIVER
//#define ILI9488_DRIVER     // WARNING: Do not connect ILI9488 display SDO to MISO if other devices share the SPI bus (TFT SDO does NOT tristate when CS is high)
//#define ST7789_DRIVER      // Full configuration option, define additional parameters below for this display
//#define ST7789_2_DRIVER    // Minimal configuration option, define additional parameters below for this display
//#define R61581_DRIVER
//#define RM68140_DRIVER
//#define ST7796_DRIVER
//#define SSD1963_480_DRIVER    // Untested
//#define SSD1963_800_DRIVER    // Untested
//#define SSD1963_800ALT_DRIVER // Untested

// Some displays support SPI reads via the MISO pin, other displays have a single
// bi-directional SDA pin and the library will try to read this via the MOSI line.
// To use the SDA line for reading data from the TFT uncomment the following line:

// #define TFT_SDA_READ      // This option is for ESP32 ONLY, tested with ST7789 display only

// For ST7789 and ILI9341 ONLY, define the colour order IF the blue and red are swapped on your display
// Try ONE option at a time to find the correct colour order for your display

//  #define TFT_RGB_ORDER TFT_RGB  // Colour order Red-Green-Blue
//  #define TFT_RGB_ORDER TFT_BGR  // Colour order Blue-Green-Red

// For M5Stack ESP32 module with integrated ILI9341 display ONLY, remove // in line below

// #define M5STACK

// For ST7789, ST7735 and ILI9163 ONLY, define the pixel width and height in portrait orientation
// #define TFT_WIDTH  80
// #define TFT_WIDTH  128
 #define TFT_WIDTH  240 // ST7789 240 x 240 and 240 x 320
// #define TFT_HEIGHT 160
// #define TFT_HEIGHT 128
// #define TFT_HEIGHT 240 // ST7789 240 x 240
 #define TFT_HEIGHT 320 // ST7789 240 x 320

// For ST7735 ONLY, define the type of display, originally this was based on the
// colour of the tab on the screen protector film but this is not always true, so try
// out the different options below if the screen does not display graphics correctly,
// e.g. colours wrong, mirror images, or tray pixels at the edges.
// Comment out ALL BUT ONE of these options for a ST7735 display driver, save this
// this User_Setup file, then rebuild and upload the sketch to the board again:

// #define ST7735_INITB
// #define ST7735_GREENTAB
// #define ST7735_GREENTAB2
// #define ST7735_GREENTAB3
// #define ST7735_GREENTAB128    // For 128 x 128 display
// #define ST7735_GREENTAB160x80 // For 160 x 80 display (BGR, inverted, 26 offset)
// #define ST7735_REDTAB
// #define ST7735_BLACKTAB
// #define ST7735_REDTAB160x80   // For 160 x 80 display with 24 pixel offset

// If colours are inverted (white shows as black) then uncomment one of the next
// 2 lines try both options, one of the options should correct the inversion.

// #define TFT_INVERSION_ON
// #define TFT_INVERSION_OFF


// ##################################################################################
//
// Section 2. Define the pins that are used to interface with the display here
//
// ##################################################################################

// If a backlight control signal is available then define the TFT_BL pin in Section 2
// below. The backlight will be turned ON when tft.begin() is called, but the library
// needs to know if the LEDs are ON with the pin HIGH or LOW. If the LEDs are to be
// driven with a PWM signal or turned OFF/ON then this must be handled by the user
// sketch. e.g. with digitalWrite(TFT_BL, LOW);

// #define TFT_BL   32            // LED back-light control pin
// #define TFT_BACKLIGHT_ON HIGH  // Level to turn ON back-light (HIGH or LOW)



// We must use hardware SPI, a minimum of 3 GPIO pins is needed.
// Typical setup for ESP8266 NodeMCU ESP-12 is :
//
// Display SDO/MISO  to NodeMCU pin D6 (or leave disconnected if not reading TFT)
// Display LED       to NodeMCU pin VIN (or 5V, see below)
// Display SCK       to NodeMCU pin D5
// Display SDI/MOSI  to NodeMCU pin D7
// Display DC (RS/AO)to NodeMCU pin D3
// Display RESET     to NodeMCU pin D4 (or RST, see below)
// Display CS        to NodeMCU pin D8 (or GND, see below)
// Display GND       to NodeMCU pin GND (0V)
// Display VCC       to NodeMCU 5V or 3.3V
//
// The TFT RESET pin can be connected to the NodeMCU RST pin or 3.3V to free up a control pin
//
// The DC (Data Command) pin may be labeled AO or RS (Register Select)
//
// With some displays such as the ILI9341 the TFT CS pin can be connected to GND if no more
// SPI devices (e.g. an SD Card) are connected, in this case comment out the #define TFT_CS
// line below so it is NOT defined. Other displays such at the ST7735 require the TFT CS pin
// to be toggled during setup, so in these cases the TFT_CS line must be defined and connected.
//
// The NodeMCU D0 pin can be used for RST
//
//
// Note: only some versions of the NodeMCU provide the USB 5V on the VIN pin
// If 5V is not available at a pin you can use 3.3V but backlight brightness
// will be lower.


// ###### EDIT THE PIN NUMBERS IN THE LINES FOLLOWING TO SUIT YOUR ESP8266 SETUP ######

// For NodeMCU - use pin numbers in the form PIN_Dx where Dx is the NodeMCU pin designation
//#define TFT_CS   PIN_D8 // Chip select control pin D8
//#define TFT_DC   PIN_D3 // Data Command control pin
//#define TFT_RST  PIN_D4 // Reset pin (could connect to NodeMCU RST, see next line)
//#define TFT_RST  -1    // Set TFT_RST to -1 if the display RESET is connected to NodeMCU RST or 3.3V

//#define TFT_BL PIN_D1  // LED back-light (only for ST7789 with backlight control pin)

//#define TOUCH_CS PIN_D2  26    // Chip select pin (T_CS) of touch screen

//#define TFT_WR PIN_D2       // Write strobe for modified Raspberry Pi TFT only


// ######  FOR ESP8266 OVERLAP MODE EDIT THE PIN NUMBERS IN THE FOLLOWING LINES  ######

// Overlap mode shares the ESP8266 FLASH SPI bus with the TFT so has a performance impact
// but saves pins for other functions. It is best not to connect MISO as some displays
// do not tristate that line wjen chip select is high!
// On NodeMCU 1.0 SD0=MISO, SD1=MOSI, CLK=SCLK to connect to TFT in overlap mode
// On NodeMCU V3  S0 =MISO, S1 =MOSI, S2 =SCLK
// In ESP8266 overlap mode the following must be defined

//#define TFT_SPI_OVERLAP

// In ESP8266 overlap mode the TFT chip select MUST connect to pin D3
//#define TFT_CS   PIN_D3
//#define TFT_DC   PIN_D5  // Data Command control pin
//#define TFT_RST  PIN_D4  // Reset pin (could connect to NodeMCU RST, see next line)
//#define TFT_RST  -1  // Set TFT_RST to -1 if the display RESET is connected to NodeMCU RST or 3.3V


// ###### EDIT THE PIN NUMBERS IN THE LINES FOLLOWING TO SUIT YOUR ESP32 SETUP   ######

// For ESP32 Dev board (only tested with ILI9341 display)
// The hardware SPI can be mapped to any pins

#define TFT_MISO 19
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   5  // Chip select control pin
#define TFT_DC    4  // Data Command control pin
#define TFT_RST   22  // Reset pin (could connect to RST pin)
//#define TFT_RST  -1  // Set TFT_RST to -1 if display RESET is connected to ESP32 board RST

#define TOUCH_CS 14     // Chip select pin (T_CS) of touch screen

//#define TFT_WR 22    // Write strobe for modified Raspberry Pi TFT only

// For the M5Stack module use these #define lines
//#define TFT_MISO 19
//#define TFT_MOSI 23
//#define TFT_SCLK 18
//#define TFT_CS   14  // Chip select control pin
//#define TFT_DC   27  // Data Command control pin
//#define TFT_RST  33  // Reset pin (could connect to Arduino RESET pin)
//#define TFT_BL   32  // LED back-light (required for M5Stack)

// ######       EDIT THE PINs BELOW TO SUIT YOUR ESP32 PARALLEL TFT SETUP        ######

// The library supports 8 bit parallel TFTs with the ESP32, the pin
// selection below is compatible with ESP32 boards in UNO format.
// Wemos D32 boards need to be modified, see diagram in Tools folder.
// Only ILI9481 and ILI9341 based displays have been tested!

// Parallel bus is only supported for the STM32 and ESP32
// Example below is for ESP32 Parallel interface with UNO displays

// Tell the library to use 8 bit parallel mode (otherwise SPI is assumed)
//#define TFT_PARALLEL_8_BIT

// The ESP32 and TFT the pins used for testing are:
//#define TFT_CS   33  // Chip select control pin (library pulls permanently low
//#define TFT_DC   15  // Data Command control pin - must use a pin in the range 0-31
//#define TFT_RST  32  // Reset pin, toggles on startup
//#define TFT_WR    4  // Write strobe control pin - must use a pin in the range 0-31
//#define TFT_RD    2  // Read strobe control pin

//#define TFT_D0   12  // Must use pins in the range 0-31 for the data bus
//#define TFT_D1   13  // so a single register write sets/clears all bits.
//#define TFT_D2   26  // Pins can be randomly assigned, this does not affect
//#define TFT_D3   25  // TFT screen update performance.
//#define TFT_D4   17
//#define TFT_D5   16
//#define TFT_D6   27
//#define TFT_D7   14

// ######       EDIT THE PINs BELOW TO SUIT YOUR STM32 SPI TFT SETUP        ######

// The TFT can be connected to SPI port 1 or 2
//#define TFT_SPI_PORT 1 // SPI port 1 maximum clock rate is 55MHz
//#define TFT_MOSI PA7
//#define TFT_MISO PA6
//#define TFT_SCLK PA5

//#define TFT_SPI_PORT 2 // SPI port 2 maximum clock rate is 27MHz
//#define TFT_MOSI PB15
//#define TFT_MISO PB14
//#define TFT_SCLK PB13

// Can use Ardiuno pin references, arbitrary allocation, TFT_eSPI controls chip select
//#define TFT_CS   D5 // Chip select control pin to TFT CS
//#define TFT_DC   D6 // Data Command control pin to TFT DC (may be labelled RS = Register Select)
//#define TFT_RST  D7 // Reset pin to TFT RST (or RESET)
// OR alternatively, we can use STM32 port reference names PXnn
//#define TFT_CS   PE11 // Nucleo-F767ZI equivalent of D5
//#define TFT_DC   PE9  // Nucleo-F767ZI equivalent of D6
//#define TFT_RST  PF13 // Nucleo-F767ZI equivalent of D7

//#define TFT_RST  -1   // Set TFT_RST to -1 if the display RESET is connected to processor reset
                        // Use an Arduino pin for initial testing as connecting to processor reset
                        // may not work (pulse too short at power up?)

// ##################################################################################
//
// Section 3. Define the fonts that are to be used here
//
// ##################################################################################

// Comment out the #defines below with // to stop that font being loaded
// The ESP8366 and ESP32 have plenty of memory so commenting out fonts is not
// normally necessary. If all fonts are loaded the extra FLASH space required is
// about 17Kbytes. To save FLASH space only enable the fonts you need!

#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:-.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
//#define LOAD_FONT8N // Font 8. Alternative to Font 8 above, slightly narrower, so 3 digits fit a 160 pixel TFT
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

// Comment out the #define below to stop the SPIFFS filing system and smooth font code being loaded
// this will save ~20kbytes of FLASH
#define SMOOTH_FONT


// ##################################################################################
//
// Section 4. Other options
//
// ##################################################################################

// Define the SPI clock frequency, this affects the graphics rendering speed. Too
// fast and the TFT driver will not keep up and display corruption appears.
// With an ILI9341 display 40MHz works OK, 80MHz sometimes fails
// With a ST7735 display more than 27MHz may not work (spurious pixels and lines)
// With an ILI9163 display 27 MHz works OK.

// #define SPI_FREQUENCY   1000000
// #define SPI_FREQUENCY   5000000
// #define SPI_FREQUENCY  10000000
// #define SPI_FREQUENCY  20000000
#define SPI_FREQUENCY  27000000
// #define SPI_FREQUENCY  40000000
// #define SPI_FREQUENCY  55000000 // STM32 SPI1 only (SPI2 maximum is 27MHz)
// #define SPI_FREQUENCY  80000000

// Optional reduced SPI frequency for reading TFT
#define SPI_READ_FREQUENCY  20000000

// The XPT2046 requires a lower SPI clock rate of 2.5MHz so we define that here:
#define SPI_TOUCH_FREQUENCY  2500000

// The ESP32 has 2 free SPI ports i.e. VSPI and HSPI, the VSPI is the default.
// If the VSPI port is in use and pins are not accessible (e.g. TTGO T-Beam)
// then uncomment the following line:
//#define USE_HSPI_PORT

// Comment out the following #define if "SPI Transactions" do not need to be
// supported. When commented out the code size will be smaller and sketches will
// run slightly faster, so leave it commented out unless you need it!

// Transaction support is needed to work with SD library but not needed with TFT_SdFat
// Transaction support is required if other SPI devices are connected.

// Transactions are automatically enabled by the library for an ESP32 (to use HAL mutex)
// so changing it here has no effect

// #define SUPPORT_TRANSACTIONS

**************************************************************************************************/

/* --- Some color definitions, feel free to change --- */
#define FACE            TFT_ORANGE
#define NUMERIC_POINT   TFT_BLACK
#define BACKGROUND      TFT_WHITE
#define HOURCOLOR       TFT_RED
#define MINUTECOLOR     TFT_BLACK

/* --- Needed libs for this project --- */
#include <SPI.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include <ArduinoJson.h> 
#include <WiFiClientSecure.h>
#include "bitmap.h"   //This is a file in the same dir from this program(!!!)

TFT_eSPI tft = TFT_eSPI();

const char* ssid       = "xxx";  //CHANGE SSID from network
const char* password   = "xxx";  //CHANGE Password from network

/*--- Needed variables for openweathermap.org ---*/
const String apiKey = "b2bc7fc61c4cc3545e6bbf151b58e1dd"; 	//CHANGE API-Key from openweathermap.org
const String location = "Berlin,de"; //CHANGE Location for openweathermap.org e.g. Wiesbaden,de
const char *clientAdress = "api.openweathermap.org";

DynamicJsonDocument jsonDoc(20000); //Var to parse JSON-Data

/*--- Define NTP Client to get time ---*/
const char* ntpServer = "europe.pool.ntp.org";  //Use Europe-NTP-Server
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, 0);
String daysOfTheWeek[7] = {"Sa", "So", "Mo", "Di", "Mi", "Do", "Fr"}; //Will be used on SerialMonitor
unsigned long utcOffsetInSeconds = 7200;


/*--- Some baisc variables for the code ---*/
int pPrevmin, pPrevhour, pPrevSecond;
String strSunset, strSunrise;
bool bFirstrun, bUpdateSunSetRise;

/*--- Basicparams for clock ---*/
#define Xo 110   // center point in X
#define Yo 120   // center point in Y
#define RADIUS 80  // radius of the clock face

/*
* =================================================================
* Function:     setup   
* Returns:      void
* Description:  Setup display and sensors
* =================================================================
*/
void setup()
{
  bFirstrun = true;
  bUpdateSunSetRise = false;
  bool bTempReturn;
  bool bFail = false;
  pinMode(15, OUTPUT);
  digitalWrite(15, LOW);
  Serial.begin(115200);
  Serial.println("Analog clock");
  Serial.println("For Touch Mod 2.4 and 2.8 -Display");
  randomSeed(analogRead(34));

  /*--- Init TFT and write some text ---*/
  tft.init();
  tft.setRotation(3);
  tft.fillScreen((BACKGROUND));
  tft.setCursor(15, 20, 2);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.println("Analog clock 2.8 TFT");
  tft.setCursor(40, 60, 2);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.print("Display : ");
  tft.setTextColor(TFT_GREEN, TFT_WHITE);
  tft.println("DONE");

  
  /*--- Init WiFi ---*/
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setCursor(40, 100, 2);
  tft.print("WiFi : ");
  WiFi.begin(ssid, password);
  static unsigned long ulSeconds = second();
  while ( WiFi.status() != WL_CONNECTED)
  {
    delay ( 500 );
    Serial.print ( "." );
    if(second() - ulSeconds >= 30)
      break;
  }
  
  if(WiFi.status() == WL_CONNECTED)
  {
    tft.setTextColor(TFT_GREEN, TFT_WHITE);
    tft.println("DONE");
  }
  else
  {
    bFail = true;
    tft.setTextColor(TFT_RED, TFT_WHITE);
    tft.println("FAIL");
  }
      
  /*--- Update needed time and data ---*/
  timeClient.begin();
  if(!bFail)
  {
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.setCursor(40, 140, 2);
    tft.print("Weatherdata : ");
    bTempReturn = UpdateOpenWeatherMapData();
    bFail = bFail || !bTempReturn;
    if(bTempReturn)
    {
      tft.setTextColor(TFT_GREEN, TFT_WHITE);
      tft.println("DONE");
    }
    else
    {
      tft.setTextColor(TFT_RED, TFT_WHITE);
      tft.println("FAIL");
    }
  }
  if(!bFail)
  {
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.setCursor(40, 180, 2);
    tft.print("NTP update : ");
    bTempReturn = UpdateNTPTime();
    bFail = bFail || !bTempReturn;
    if(bTempReturn)
    {
      tft.setTextColor(TFT_GREEN, TFT_WHITE);
      tft.println("DONE");
    }
    else
    {
      tft.setTextColor(TFT_RED, TFT_WHITE);
      tft.println("FAIL");
    }
  }
  ulSeconds = second();
  while(second() - ulSeconds < 5 && !bFail){}
  tft.fillScreen((BACKGROUND));
  /*--- Draw clock and bitmap ---*/
  drawFace();
  tft.drawBitmap(230,20,sunrise,64,64,TFT_BLACK);
  tft.drawBitmap(230,120,sunset,64,64,TFT_BLACK);
  
}

/*
* =================================================================
* Function:     loop   
* Returns:      void
* Description:  Main loop to let program work
* =================================================================
*/
void loop()
{
  DrawTime();
  UpdateOpenWeatherMapData();
  UpdateNTPTime();
  UpdateSunriseSunset();

  //Serial output
  if(pPrevSecond != second() || bFirstrun)
  {
    Serial.print(daysOfTheWeek[weekday()] + "., ");
    Serial.print(GetDigits(hour()) );
    Serial.print(":");
    Serial.print(GetDigits(minute()) );
    Serial.print(":");
    Serial.println(GetDigits(second()) );
    pPrevSecond = second();
  }

  if(bFirstrun)
    bFirstrun = false;
}

/*
* =================================================================
* Function:     UpdateNTPTime   
* Returns:      bool
* Description:  Sync ESP-Time with NTP
* =================================================================
*/
bool UpdateNTPTime()
{
  static bool bUpdateDone;
  if((bFirstrun || (minute() % 15) == 0) && !bUpdateDone)
  {
    bool bUpdate = timeClient.update();
    Serial.print("Update time: ");
    if(bUpdate)
    {
      unsigned long ulNTPTime = timeClient.getEpochTime();
      timeClient.setTimeOffset(utcOffsetInSeconds);
      setTime(timeClient.getEpochTime());
      Serial.println("SUCCESS");
      bUpdateDone = true;
    }
    else
    {
      Serial.println("FAILED");
      bUpdateDone = false;
      return false;
    }
  }
  if((minute() % 2) != 0)
    bUpdateDone = false;
  return true;
}

/*
* =================================================================
* Function:     UpdateOpenWeatherMapData   
* Returns:      bool
* Description:  Update OpenWeathermap data
* =================================================================
*/
bool UpdateOpenWeatherMapData()
{
  static bool bUpdateDone;
  if((bFirstrun || (minute() % 30) == 0) && !bUpdateDone)
  {
    jsonDoc.clear();  //Normally not needed, but sometimes new data will not stored
    String strRequestData = RequestData(); //Get JSON as RAW string
    Serial.println("Received data: " + strRequestData);
    //Only do an update, if we got valid data
    if(strRequestData != "")  //Only do an update, if we got valid data
    {
      DeserializationError error = deserializeJson(jsonDoc, strRequestData); //Deserialize string to AJSON-doc
      if (error)
      {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        return false;
      }
      //Save data to global var
      static unsigned long timeZone = jsonDoc["timezone"];  //Get latest timezone
      //Print to Serial Monitor
      time_t ttSunrise, ttSunset;
      ttSunrise  = jsonDoc["sys"]["sunrise"].as<time_t>();  //Convert seconds to time_t
      ttSunset   = jsonDoc["sys"]["sunset"].as<time_t>();   //Convert seconds to time_t
      Serial.println("SunRise: " + String(hour(ttSunrise+utcOffsetInSeconds)) + ":" + String(minute(ttSunrise+utcOffsetInSeconds)) );
      Serial.println("SunSet: " + String(hour(ttSunset+utcOffsetInSeconds)) + ":" + String(minute(ttSunset+utcOffsetInSeconds)) );
      //Check if sunset or sunrise has changed
      if(strSunset != String(GetDigits(hour(ttSunset+utcOffsetInSeconds))) + ":" + String(GetDigits(minute(ttSunset+utcOffsetInSeconds))) )
      {
        strSunset = String(GetDigits(hour(ttSunset+utcOffsetInSeconds))) + ":" + String(GetDigits(minute(ttSunset+utcOffsetInSeconds)));
        bUpdateSunSetRise = true;
      }
      if(strSunrise != String(GetDigits(hour(ttSunrise+utcOffsetInSeconds))) + ":" + String(GetDigits(minute(ttSunrise+utcOffsetInSeconds))) )
      {
        strSunrise = String(GetDigits(hour(ttSunrise+utcOffsetInSeconds))) + ":" + String(GetDigits(minute(ttSunrise+utcOffsetInSeconds)));
        bUpdateSunSetRise = true;
      }
      /*--- Update timezone ---*/
      if(timeZone != utcOffsetInSeconds)
      {
        utcOffsetInSeconds = timeZone;
        timeClient.setTimeOffset(utcOffsetInSeconds);
      }
      bUpdateDone = true;
    }
    else
      return false;
    }
  if((minute() % 2) != 0)
   bUpdateDone = false;
 return true;
}

/*
* =================================================================
* Function:     RequestData   
* Returns:      String
* Description:  Request to openWeathermap.org to get latest data
* =================================================================
*/
String RequestData()
{
  WiFiClientSecure client;
  client.setInsecure();
  if(!client.connect(clientAdress,443)){
    Serial.println("Failed to connect");
    return "";
  }
  /*
   * path as followed, see documentation:
   * /data/2.5/weather? <- static url-path
   * q="location"       <- given location to get weatherforecast
   * &lang=de           <- german description for weather
   * &units=metric      <- metric value in Celcius and hPa
   * appid="apiKey"     <- API-Key from user-account
   */
  String path = "/data/2.5/weather?q=" + location + "&lang=de&units=metric&appid=" + apiKey;

  //Send request to openweathermap.org
  client.print(
    "GET " + path + " HTTP/1.1\r\n" + 
    "Host: " + clientAdress + "\r\n" + 
    "Connection: close\r\n" + 
    "Pragma: no-cache\r\n" + 
    "Cache-Control: no-cache\r\n" + 
    "User-Agent: ESP32\r\n" + 
    "Accept: text/html,application/json\r\n\r\n");

  //Wait for the answer, max 2 sec.
  uint64_t startMillis = millis();
  while (client.available() == 0) {
    if (millis() - startMillis > 2000) {
      Serial.println("Client timeout");
      client.stop();
      return "";
    }
  }

  //If there is an answer, parse answer from openweathermap.org
  String resHeader = "", resBody = "";
  bool receivingHeader = true;
  while(client.available()) {
    String line = client.readStringUntil('\r');
    if (line.length() == 1 && resBody.length() == 0) {
      receivingHeader = false;
      continue;
    }
    if (receivingHeader) {
      resHeader += line;
    }
    else {
      resBody += line;
    }
  }
  
  client.stop(); //Need to stop, otherwise NodeMCU will crash after a while
  return resBody;
}

/*
* =================================================================
* Function:     UpdateSunriseSunset   
* Returns:      String
* Description:  Update displayed text for sunset and sunrise
* =================================================================
*/
void UpdateSunriseSunset()
{
  if(bUpdateSunSetRise)
  {
    tft.setTextSize(2);
    tft.setTextColor(TFT_BLACK);
    tft.fillRect(230,75,64,30,TFT_WHITE);
    tft.setCursor(230,75);
    tft.print(strSunrise);
    tft.fillRect(230,175,64,30,TFT_WHITE);
    tft.setCursor(230,175);
    tft.print(strSunset);
    bUpdateSunSetRise = false;
  }
}

/*
* =================================================================
* Function:     GetDigits   
* Returns:      String
* Description:  If the value is less than 10, a "0" is placed in front
* =================================================================
*/
String GetDigits(int iValue)
{
  String rValue = "";
  if(iValue < 10)
    rValue += "0";
  rValue += iValue;
  return rValue;
}

/*
* =================================================================
* Function:     drawFace   
* Returns:      String
* Description:  Draw clock face
* =================================================================
*/
void drawFace()
{
  int i = 0, angle = 0;
  float x, y;

  // Draw outer frame
  tft.drawCircle(Xo, Yo, RADIUS + 21, FACE);
  tft.drawCircle(Xo, Yo, RADIUS + 20, FACE);

  // Draw inner frame
  tft.drawCircle(Xo, Yo, RADIUS + 12, FACE);
  tft.drawCircle(Xo, Yo, RADIUS + 11, FACE);
  tft.drawCircle(Xo, Yo, RADIUS + 10, FACE);

  //Draw Numeric point

  for (i = 0; i <= 12; i++)
  {
    x = Xo + round(RADIUS * cos(angle * M_PI / 180) );
    y = Yo + round(RADIUS * sin(angle * M_PI / 180) );
    tft.drawCircle(x, y, 2, NUMERIC_POINT);
    angle += 30;
  }

  for (i = 0; i < 360; i += 6)
    tft.drawPixel(Xo + round(RADIUS * cos(i * M_PI / 180)), Yo + round(RADIUS * sin(i * M_PI / 180)), NUMERIC_POINT);
}

/*
* =================================================================
* Function:     DrawMinuteHand   
* Returns:      void
* Description:  Draw minute hand on clock face
* =================================================================
*/
void DrawMinuteHand(int m, int color)
{
  float angle=-90;
  float Xa, Ya;
  Xa=Xo+(RADIUS-20)*cos((angle+m*6)*M_PI/180);
  Ya=Yo+(RADIUS-20)*sin((angle+m*6)*M_PI/180);
  for(int iCnt = -1; iCnt <= 1; iCnt++)
    tft.drawLine(Xo, Yo+iCnt, Xa, Ya+iCnt, color);
}

/*
* =================================================================
* Function:     DrawHourHand   
* Returns:      void
* Description:  Draw hour hand on clock face
* =================================================================
*/
void DrawHourHand(int h, int m, int color)
{
  float angle=-90;
  float Xa, Ya;
  Xa=Xo+(RADIUS-(RADIUS/2))*cos((angle+h*30+(m*30/60))*M_PI/180);
  Ya=Yo+(RADIUS-(RADIUS/2))*sin((angle+h*30+(m*30/60))*M_PI/180);
  for(int iCnt = -1; iCnt <= 1; iCnt++)
   tft.drawLine(Xo, Yo+iCnt, Xa, Ya+iCnt, color);
}

/*
* =================================================================
* Function:     DrawCenterPoint   
* Returns:      void
* Description:  Draw centerpoint on clock face
* =================================================================
*/
void DrawCenterPoint()
{
  tft.fillCircle(Xo, Yo, 3, NUMERIC_POINT);
}

/*
* =================================================================
* Function:     DrawTime   
* Returns:      void
* Description:  Basefunction to draw hour and minute hands
* =================================================================
*/
void DrawTime()
{
  if(pPrevmin != minute() || pPrevhour != hour() || bFirstrun)
  {
    if(!bFirstrun)  //Only needed, cause otherwise esp crashs
    {
      DrawMinuteHand(pPrevmin, BACKGROUND);
      DrawHourHand(pPrevhour, pPrevmin, BACKGROUND);
    }
    DrawMinuteHand(minute(), MINUTECOLOR);
    DrawHourHand(hour(), minute(), HOURCOLOR);
    DrawCenterPoint();
    pPrevmin = minute();
    pPrevhour = hour();  
  }
}
