#include "iconotemperatura.h"
#include "iconopresion.h"
#include "iconohumedad.h"
#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "SparkFun_SCD4x_Arduino_Library.h" 

int o = 0;

#define RXD2 16 // To sensor TXD
#define TXD2 17 // To sensor RXD

#define RED2RED 0
#define GREEN2GREEN 1
#define BLUE2BLUE 2
#define BLUE2RED 3
#define GREEN2RED 4
#define RED2GREEN 5
 
#define TFT_GREY 0x2104 // Dark grey 16 bit colour

SCD4x mySensor;
Adafruit_BME280 bme1;


TFT_eSPI tft = TFT_eSPI(); // Invoke custom library with default width and height

int CO2lecture = 0;
int pm25lecture = 0;

int reading = 0; // Value to be displayed
int d = 0;       // Variable used for the sinewave test waveform
boolean range_error = 0;
int8_t ramp = 1;
 
void setup(void)
{
  Serial.begin(9600);
 
  Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Wire.begin(SDA, SCL,100000);
  bme1.begin(0x76); 
  mySensor.begin(0x62);

  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
 
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("Breath", 200, 10, 4);
  //tft.drawString("Weather", 350, 10, 2);
 
  tft.drawString("CO2", 130, 60, 2);
  tft.drawString("PM2.5", 300, 60, 2);

  tft.drawString("Temperatura", 65, 210, 2);
  tft.drawString("Humedad", 190, 210, 2);
  tft.drawString("Presion", 320, 210, 2);
  tft.pushImage(50,230,50,50,iconotemperatura);
  tft.pushImage(180,230,50,50,iconohumedad);
  tft.pushImage(300,230,50,50,iconopresion);

  delay(5000);
}

struct pms5003data {
  uint16_t framelen;
  uint16_t pm10_standard, pm25_standard, pm100_standard;
  uint16_t pm10_env, pm25_env, pm100_env;
  uint16_t particles_03um, particles_05um, particles_10um, particles_25um, particles_50um, particles_100um;
  uint16_t unused;
  uint16_t checksum;
};

struct pms5003data data;

void loop()
{
    readings();
    // Test with a slowly changing value from a Sine function
    d += 4;
    if (d >= 360)
      d = 0;
 
    // Set the the position, gap between meters, and inner radius of the meters
    int xpos = 0, ypos = 5, gap = 4, radius = 40;
 
    xpos = 80, ypos = 80, gap = 50, radius = 60;
 
    //reading = 800 + 150 * sineWave(d + 90);
    xpos = gap + ringMeter(CO2lecture, 0, 2000, xpos, ypos, radius, "ppm", BLUE2RED); // Draw analogue meter
 
    //reading = 15 + 15 * sineWave(d + 150);
    xpos = gap + ringMeter(pm25lecture, 0, 100, xpos, ypos, radius, "ug/m3", GREEN2GREEN); // Draw analogue meter


  
    delay(5000);
}
 
// #########################################################################
//  Draw the meter on the screen, returns x coord of righthand side
// #########################################################################
int ringMeter(int value, int vmin, int vmax, int x, int y, int r, const char *units, byte scheme)
{
  // Minimum value of r is about 52 before value text intrudes on ring
  // drawing the text first is an option
 
  x += r;
  y += r; // Calculate coords of centre of ring
 
  int w = r / 3; // Width of outer ring is 1/4 of radius
 
  int angle = 150; // Half the sweep angle of meter (300 degrees)
 
  int v = map(value, vmin, vmax, -angle, angle); // Map the value to an angle v
 
  byte seg = 3; // Segments are 3 degrees wide = 100 segments for 300 degrees
  byte inc = 6; // Draw segments every 3 degrees, increase to 6 for segmented ring
 
  // Variable to save "value" text colour from scheme and set default
  int colour = TFT_BLUE;
 
  // Draw colour blocks every inc degrees
  for (int i = -angle + inc / 2; i < angle - inc / 2; i += inc)
  {
    // Calculate pair of coordinates for segment start
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (r - w) + x;
    uint16_t y0 = sy * (r - w) + y;
    uint16_t x1 = sx * r + x;
    uint16_t y1 = sy * r + y;
 
    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg - 90) * 0.0174532925);
    float sy2 = sin((i + seg - 90) * 0.0174532925);
    int x2 = sx2 * (r - w) + x;
    int y2 = sy2 * (r - w) + y;
    int x3 = sx2 * r + x;
    int y3 = sy2 * r + y;
 
    if (i < v)
    { // Fill in coloured segments with 2 triangles
      switch (scheme)
      {
      case 0:
        colour = TFT_RED;
        break; // Fixed colour
      case 1:
        colour = TFT_GREEN;
        break; // Fixed colour
      case 2:
        colour = TFT_BLUE;
        break; // Fixed colour
      case 3:
        colour = rainbow(map(i, -angle, angle, 0, 127));
        break; // Full spectrum blue to red
      case 4:
        colour = rainbow(map(i, -angle, angle, 70, 127));
        break; // Green to red (high temperature etc)
      case 5:
        colour = rainbow(map(i, -angle, angle, 127, 63));
        break; // Red to green (low battery etc)
      default:
        colour = TFT_BLUE;
        break; // Fixed colour
      }
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, colour);
      //text_colour = colour; // Save the last colour drawn
    }
    else // Fill in blank segments
    {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_GREY);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_GREY);
    }
  }
  // Convert value to a string
  char buf[10];
  byte len = 3;
  if (value > 999)
    len = 5;+
  dtostrf(value, len, 0, buf);
  buf[len] = ' ';
  buf[len + 1] = 0; // Add blanking space and terminator, helps to centre text too!
  // Set the text colour to default
  tft.setTextSize(1);
 
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  // Uncomment next line to set the text colour to the last segment value!
  tft.setTextColor(colour, TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
  // Print value, if the meter is large then use big font 8, othewise use 4
  if (r > 84)
  {
    tft.setTextPadding(55 * 3);   // Allow for 3 digits each 55 pixels wide
    tft.drawString(buf, x, y, 8); // Value in middle
  }
  else
  {
    tft.setTextPadding(3 * 14);   // Allow for 3 digits each 14 pixels wide
    tft.drawString(buf, x, y, 4); // Value in middle
  }
  tft.setTextSize(1);
  tft.setTextPadding(0);
  // Print units, if the meter is large then use big font 4, othewise use 2
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  if (r > 84)
    tft.drawString(units, x, y + 60, 4); // Units display
  else
    tft.drawString(units, x, y + 15, 2); // Units display
 
  // Calculate and return right hand side x coordinate
  return x + r;
}
 
// #########################################################################
// Return a 16 bit rainbow colour
// #########################################################################
unsigned int rainbow(byte value)
{
  // Value is expected to be in range 0-127
  // The value is converted to a spectrum colour from 0 = blue through to 127 = red
 
  byte red = 0;   // Red is the top 5 bits of a 16 bit colour value
  byte green = 0; // Green is the middle 6 bits
  byte blue = 0;  // Blue is the bottom 5 bits
 
  byte quadrant = value / 32;
 
  if (quadrant == 0)
  {
    blue = 31;
    green = 2 * (value % 32);
    red = 0;
  }
  if (quadrant == 1)
  {
    blue = 31 - (value % 32);
    green = 63;
    red = 0;
  }
  if (quadrant == 2)
  {
    blue = 0;
    green = 63;
    red = value % 32;
  }
  if (quadrant == 3)
  {
    blue = 0;
    green = 63 - 2 * (value % 32);
    red = 31;
  }
  return (red << 11) + (green << 5) + blue;
}
 
// #########################################################################
// Return a value in range -1 to +1 for a given phase angle in degrees
// #########################################################################
float sineWave(int phase)
{
  return sin(phase * 0.0174532925);
}
 
//====================================================================================
// This is the function to draw the icon stored as an array in program memory (FLASH)
//====================================================================================
 
// To speed up rendering we use a 64 pixel buffer
#define BUFF_SIZE 64
 
// Draw array "icon" of defined width and height at coordinate x,y
// Maximum icon size is 255x255 pixels to avoid integer overflow
 
void drawIcon(const unsigned short *icon, int16_t x, int16_t y, int8_t width, int8_t height)
{
 
  uint16_t pix_buffer[BUFF_SIZE]; // Pixel buffer (16 bits per pixel)
 
  tft.startWrite();
 
  // Set up a window the right size to stream pixels into
  tft.setAddrWindow(x, y, width, height);
 
  // Work out the number whole buffers to send
  uint16_t nb = ((uint16_t)height * width) / BUFF_SIZE;
 
  // Fill and send "nb" buffers to TFT
  for (int i = 0; i < nb; i++)
  {
    for (int j = 0; j < BUFF_SIZE; j++)
    {
      pix_buffer[j] = pgm_read_word(&icon[i * BUFF_SIZE + j]);
    }
    tft.pushColors(pix_buffer, BUFF_SIZE);
  }
 
  // Work out number of pixels not yet sent
  uint16_t np = ((uint16_t)height * width) % BUFF_SIZE;
 
  // Send any partial buffer left over
  if (np)
  {
    for (int i = 0; i < np; i++)
      pix_buffer[i] = pgm_read_word(&icon[nb * BUFF_SIZE + i]);
    tft.pushColors(pix_buffer, np);
  }
 
  tft.endWrite();
}
 
void readings()
{
  int co2, tscd40, tbme280, hscd40, hbme280, pbme280, pm25um= 0;   
  readPMSdata(&Serial1);
  mySensor.readMeasurement(); 
  
  pm25um = data.pm25_standard;

  co2 = mySensor.getCO2();
  //tscd40 = mySensor.getTemperature();
  tbme280 = bme1.readTemperature();
  //hscd40 = mySensor.getHumidity();
  hbme280 = bme1.readHumidity();
  pbme280 = bme1.readPressure() / 100.0F;

  if(pm25um >100){
    pm25um = 30;
  }
  else if(isnan(pm25um))
  {
    pm25um = 31;
  }

  if(isnan(pbme280)){
    pbme280 = 1006;
  }
  Serial.println();
  Serial.print("CO2(ppm):");
  Serial.print(co2);
  Serial.print("\tPM 2.5:");
  Serial.print(pm25um);
  Serial.print("\tT(C):");
  Serial.print(tbme280);  
  Serial.print("\tH(%RH):");
  Serial.print(hbme280);
  Serial.print("\tP(hPa):");
  Serial.print(pbme280);

  char buffer1[20];
  char buffer2[20];
  char buffer3[20];

  sprintf(buffer1, "%i °C", tbme280);
  sprintf(buffer2, "%i %RH", hbme280);
  sprintf(buffer3, "%i hPa", pbme280);
o = o + 1;
if (o>1){
  tft.drawString(buffer1, 120, 255, 2);
  tft.drawString(buffer2, 255, 255, 2);
  tft.drawString(buffer3, 380, 255, 2);
}
  CO2lecture = (int)co2;
  pm25lecture = (int)pm25um;
}

// PMSSSSSSS
boolean readPMSdata(Stream *s) {
  if (! s->available()) {
    return false;
  }

  // Read a byte at a time until we get to the special '0x42' start-byte
  if (s->peek() != 0x42) {
    s->read();
    return false;
  }

  // Now read all 32 bytes
  if (s->available() < 32) {
    return false;
  }

  uint8_t buffer[32];
  uint16_t sum = 0;
  s->readBytes(buffer, 32);

  // get checksum ready
  for (uint8_t i = 0; i < 30; i++) {
    sum += buffer[i];
  }

  /* debugging
    for (uint8_t i=2; i<32; i++) {
    Serial.print("0x"); Serial.print(buffer[i], HEX); Serial.print(", ");
    }
    Serial.println();
  */

  // The data comes in endian'd, this solves it so it works on all platforms
  uint16_t buffer_u16[15];
  for (uint8_t i = 0; i < 15; i++) {
    buffer_u16[i] = buffer[2 + i * 2 + 1];
    buffer_u16[i] += (buffer[2 + i * 2] << 8);
  }

  // put it into a nice struct :)
  memcpy((void *)&data, (void *)buffer_u16, 30);

  if (sum != data.checksum) {
    Serial.println("Checksum failure");
    return false;
  }
  // success!
  return true;
}
