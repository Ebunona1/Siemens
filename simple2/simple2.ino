// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        2 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 10 // Popular NeoPixel ring size

int green, blue, red;

// 1 - Nitric Oxide effect on Acid Rain
int nitric_size = 24;
int nitric[24] = {6.25, 6.23, 6.36, 6.90, 6.99, 7.21, 9.43, 7.38, 7.65, 8.26, 7.29, 8.03, 8.90, 10.35, 8.90, 7.40, 5.94, 6.43, 5.72, 5.23, 6.07, 5.80, 6.61, 7.76};

// 2 - Relative Humidity effect on Rain Fall Levels
int relative_size = 24;
int relative[24] = {70.73, 71.04, 70.97, 71.31, 71.16, 71.02, 70.70, 70.11, 68.99, 66.97, 64.82, 62.50, 59.12, 56.91, 56.25, 56.49, 56.75, 57.22, 55.98, 58.17, 61.97, 65.20, 67.73, 69.13};

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

#define DELAYVAL 100 // Time (in milliseconds) to pause between pixels
#define SAMPLE_DELAY 3000

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
}

int humidity(int j){

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.

  int rainInc;
  
  if (relative[j] > 68){
    rainInc = 1;
  } 
  else if (relative[j] <= 68 && relative[j] > 64){
    rainInc = 2;
  }
  else if (relative[j] <= 64 && relative[j] > 60){
    rainInc = 3;
  }
  else if (relative[j] <= 60){
    rainInc = 5;
  }
}

void setSeq(int i){
  
  pixels.clear();

        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255 - Here we're using a moderately bright green color:
        pixels.setPixelColor(i, pixels.Color(green, red, blue));
        pixels.setPixelColor((i + 2) % 10, pixels.Color(green, red, blue));
        pixels.setPixelColor((i + 5) % 10, pixels.Color(green, red, blue));
        pixels.setPixelColor((i + 7) % 10, pixels.Color(green, red, blue));
        //pixels.setPixelColor((i + 9) % 10, pixels.Color(green, 0, blue));
    
        pixels.show();   // Send the updated pixel colors to the hardware.
}

void rainfall(int sample_max) {
  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  
  int nitric_counter;
  int rainInc;
  
  int oneInc[5] = {9, 8, 6, 4, 2};
  int twoInc[4] = {9, 7, 4, 1};
  int threeInc[3] = {9, 6, 2};
  int fiveInc[2] = {9, 4};
  
  for (int j = 0; j < nitric_size; j++) {
    
    nitric_counter = 0;
    rainInc = humidity(j);

    // Colour Bands based on Nitric Oxide - Time data
     
    if (nitric[j] < 6.5) {
      blue = 255;
      green = 200;
      red = 50;
    }
    else if (nitric >= 6.5 && nitric[j] < 8){
      blue = 70;
      green = 0;
      red = 255;
    }
    else {
      red = 255;
      blue = 0;
      green = 0;
    }

    while (nitric_counter < sample_max) {

      for(int i = NUMPIXELS - 1; i > 0; i--) { // For each pixel...
        
        
  
        nitric_counter += 1;
    
        delay(DELAYVAL); // Pause before next pass through loop
      }
    }
  }
}

void loop() {

  rainfall(30);
  
}