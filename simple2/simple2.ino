// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        2 // On Trinket or Gemma, suggest changing this to 1
#define PINTEMP    3
#define PINMOTOR   4

#define SERVOPERIOD 875

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 10 // Popular NeoPixel ring size
#define NUMPIXELSTEMP 28 // Number of pixels in our temp atmosphere

// 1 - Nitric Oxide effect on Acid Rain
int nitric_size = 24;
int nitric[24] = {6.25, 6.23, 6.36, 6.90, 6.99, 7.21, 9.43, 7.38, 7.65, 8.26, 7.29, 8.03, 8.90, 10.35, 8.90, 7.40, 5.94, 6.43, 5.72, 5.23, 6.07, 5.80, 6.61, 7.76};

// 2 - Relative Humidity effect on Rain Fall Levels
int relative_size = 24;
int relative[24] = {70.73, 71.04, 70.97, 71.31, 71.16, 71.02, 70.70, 70.11, 68.99, 66.97, 64.82, 62.50, 59.12, 56.91, 56.25, 56.49, 56.75, 57.22, 55.98, 58.17, 61.97, 65.20, 67.73, 69.13};

// 3 - Temperature effect on Atmosphere
int temp_size = 24;
int temperature[24] = {10.24, 10.00, 9.80, 9.43, 9.25, 9.14, 10.30, 10.36, 10.90, 11.51, 12.29, 13.04, 13.94, 14.64, 15.22, 14.99, 14.44, 14.38, 14.34, 13.55, 12.73, 11.83, 11.06, 10.70};

// 4 - Carbon Monoxide effect on Cloud
int carbon_size = 24;
int carbon[24] = {1439.89, 1172.50, 957.99, 1016.86, 1007.91, 1338.64, 1790.60, 1797.96, 1816.01, 1787.33, 1794.61, 1601.61, 1370.77, 1347.63, 1097.64, 1328.28, 1044.00, 1062.29, 1155.27, 1171.24, 1022.24, 1212.49, 1272.88, 1304.69};

// 5 - Nitrogen Dioxide effect on Growth
int flowers_size = 24;
int flowers[24] = {16.95, 15.35, 13.45, 12.85, 12.27, 12.01, 5.57, 13.52, 12.43, 11.14, 10.05, 10.36, 9.18, 9.57, 12.08, 13.05, 13.42, 14.79, 13.76, 15.78, 19.24, 20.77, 19.69, 18.26};

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel temps(NUMPIXELSTEMP, PINTEMP, NEO_RGB + NEO_KHZ800);

#define DELAYVAL 100 // Time (in milliseconds) to pause between pixels
#define SAMPLE_DELAY 20
#define SAMPLE_DELAY2 5
#define SAMPLE_DELAY3 1
#define PINSERVO 5

Servo flowerServo;

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  temps.begin();
  
  pinMode(13,OUTPUT);
  pinMode(PINMOTOR, OUTPUT);
  digitalWrite(13,HIGH);
}

float nitrOx;



void story(int j, int sample_max) {
  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.

  int rainInc;
  int rgreen, rblue, rred; // rain colour
  int tgreen, tblue, tred; // temperature colour
  int nitric_counter = 0;

  // Colour Bands based on Nitric Oxide and Carbon Monoxide (Rain Acidity and Storm)
  if (nitric[j] < 6.5) {
    rblue = 255;
    rgreen = 200;
    rred = 50;
  }
  else if (nitric[j] >= 6.5 && nitric[j] < 8){
    rblue = 70;
    rgreen = 0;
    rred = 255;
  }
  else {
    rred = 255;
    rblue = 0;
    rgreen = 0;
  }

  // Colour Bands based on Temperature and RH relationship (Rain and Atmosphere)
  
  if (temperature[j] < 11) { // cold
    tblue = 255;
    tgreen = 200;
    tred = 50;
  }
  else if (temperature[j] >= 11 && temperature[j] < 13.5){ // warmer
    tblue = 50;
    tgreen = 255;
    tred = 98;
  }
  else { // hot
    tred = 255;
    tblue = 0;
    tgreen = 50;
  }

  if (relative[j] > 70){
      
      rainInc = 3;
    } 
    else if (relative[j] <= 70 && relative[j] > 60){
      
      rainInc = 5;
    }
    else if (relative[j] <= 60){
      
      rainInc = 7;
    }

  nitrOx = flowers[j];

  while (nitric_counter < sample_max) {

    if (nitrOx < 12.3) {
      flowerServo.detach();
    }
    else {
      flowerServo.attach(PINSERVO);
      flowerServo.write(0);
    }

    for(int i = NUMPIXELS - 1; i > 0; i--) { // For each pixel...
      int ratio = 0;
      ratio = map(carbon[j], 957.99, 1816.01, 70, 255);
      analogWrite(PINMOTOR, ratio);
      
      pixels.clear();

      for (int j = NUMPIXELSTEMP - 1; j > 0; j--){
        temps.setPixelColor(j, temps.Color(tgreen, tred, tblue));
      }

      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255 - Here we're using a moderately bright green color:

      for (int k = 9; k > 0; k -= rainInc) {
        pixels.setPixelColor((i + k) % 10, pixels.Color(rgreen, rred, rblue));
      }

      pixels.show();
      temps.show();
      nitric_counter += 1;

      delay(DELAYVAL); // Pause before next pass through loop
    }
  }
}

void loop() {
  
  // Story for 2s resolution
  for (int j = 0; j < nitric_size; j++){
     story(j, SAMPLE_DELAY);
  }
  /*
  delay(1000);
  
  // Story for 0.5s resolution
  for (int j = 0; j < nitric_size; j++){
     story(j, SAMPLE_DELAY2);
  }

  delay(1000);
  
  // Story for 0.1s resolution
  for (int j = 0; j < nitric_size; j++){
     story(j, SAMPLE_DELAY3);
  }
  */
}
