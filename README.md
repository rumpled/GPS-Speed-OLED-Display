# GPS Speed OLED Display

Display a count of satellites for a gps fix and the current speed on a small OLED display

### Libraries:

- u8g2 - https://github.com/olikraus/u8g2
- NeoGPS - https://github.com/SlashDevin/NeoGPS



### References:

- RobotZero - https://robotzero.one/arduino-neo-gps-oled/



### Hardware:

- Moteino USB - https://lowpowerlab.com/shop/moteinousb
- GY-GPS6MV2 - GPS Module
- Heltec 0.49" OLED - https://heltec.org/project/049-oled/



### Things learned:

- A bit about how GPS modules work



### Config files for NeoGPS:

These are known-working files that you have to place into the NeoGPS src folder wherever your Arduino libraries are stored.

- NMEAGPS_cfg.h
- GPSfix_cfg.h
- GPSport.h



### Notes:

You have to disconnect the Serial RX port when programming or data from the GPS module will interfere.