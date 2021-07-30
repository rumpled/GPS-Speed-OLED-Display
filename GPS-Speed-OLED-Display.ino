#include <NMEAGPS.h>
#include <GPSport.h>
#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

static NMEAGPS gps; // This parses the GPS characters

#define SATFONT           u8g2_font_profont12_mf
#define SATLABEL          "SAT"
#define SATCOUNTPIXELGAP  4
#define SPEEDFONT         u8g2_font_fur42_tn

char satCount[3] = "-";
char gpsSpeed[5] = "--.-";

//#define DEBUG
#ifdef DEBUG
  #define DEBUG_PRINT(x)    Serial.print(x)
  #define DEBUG_PRINTLN(x)  Serial.println(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x) 
#endif

void setup()
{
  #ifdef DEBUG
    Serial.begin(9600);
    DEBUG_PRINTLN( F("Lock & Display started") );
    DEBUG_PRINTLN( F("Looking for GPS device on " GPS_PORT_NAME) );
    Serial.flush();
  #endif

  u8g2.begin();
  u8g2.setFont(SATFONT);
  #define SATFONTHEIGHT u8g2.getMaxCharHeight()
  // and how wide the label is so we can offset the number correctly
  #define SATLABELWIDTH u8g2.getStrWidth(SATLABEL)
  updateDisplay();
  delay(1000);
  gpsPort.begin(9600);
}

static void updateDisplay()
{
  // clear the display buffer for new drawing
  u8g2.clearBuffer();
  
  // sat label (inverted colors)
  u8g2.setFont(SATFONT);
  u8g2.setFontMode(0);
  u8g2.setDrawColor(0);
  u8g2.drawStr(0,SATFONTHEIGHT,SATLABEL);
  u8g2.setFontMode(1);
  u8g2.setDrawColor(2);

  // sat count
  u8g2.drawStr(SATLABELWIDTH+SATCOUNTPIXELGAP,SATFONTHEIGHT,satCount);

  // gps speed
  u8g2.setFont(SPEEDFONT);
  
  // calculate right-alignment offset
  int speedAlignRightOffset = u8g2.getDisplayWidth() - u8g2.getStrWidth(gpsSpeed);

  // and draw it
  u8g2.drawStr(speedAlignRightOffset, 64, gpsSpeed);

  // render everything
  u8g2.sendBuffer();
}

void loop()
{
  // from example sketch, ensures gps is ready
  if (gps.available( gpsPort)) {
    // get the current fix object
    gps_fix fix = gps.read();

    // capture the number of satellites
    itoa(fix.satellites, satCount, 10);

    // and the current speed
    float spd = fix.speed_mph();
    dtostrf(spd, 4, 1, gpsSpeed);
    updateDisplay();

    #ifdef DEBUG
      printDebug(fix);
    #endif
  } // end if gps port available
} // end loop

void printDebug(gps_fix fix) {
  DEBUG_PRINTLN("--------------------");
  DEBUG_PRINT("Status: ");
  switch (fix.status) {
    case 0:
      DEBUG_PRINT(F("STATUS_NONE"));
      break;
    case 1:
      DEBUG_PRINT(F("STATUS_EST"));
      break;
    case 2:
      DEBUG_PRINT(F("STATUS_TIME_ONLY"));
      break;
    case 3:
      DEBUG_PRINT(F("STATUS_STD"));
      break;
    case 4:
      DEBUG_PRINT(F("STATUS_DGPS"));
      break;
    default:
      DEBUG_PRINT(F("Unknown"));
      break;
  }
  DEBUG_PRINT(F(" | Valid: "));
  DEBUG_PRINT(fix.valid.speed);
  DEBUG_PRINT(F(" | Sats: "));
  DEBUG_PRINT(fix.satellites);
  DEBUG_PRINTLN();
  
  DEBUG_PRINT(F("Raw Speed: ["));
  DEBUG_PRINT(spd);
  DEBUG_PRINT("]");
  DEBUG_PRINT(F(" | Formatted Speed: ["));
  DEBUG_PRINT(gpsSpeed);
  DEBUG_PRINTLN(F("]"));
}
