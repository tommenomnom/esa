#include <FastLED.h>

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

int vib = 6;               // the PWM pin the Vibration motor is attached to
unsigned long vib_intensity = 0;
unsigned long intensity = 0;         // how bright the LED is
int intensityAmount1 = 255/36;   // Intensity motor increase by points
int intensityAmount2 = 255/18;   // Intensity motor decrease by points
unsigned long timer;
unsigned long x;
bool first_timer_is_set = false;
bool second_timer_is_set = false;
bool third_timer_is_set = false;
bool fourth_timer_is_set = false;
bool vibrate = false;
unsigned long start_time;
#define DATA_PIN    3
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    88
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

void setup() {
  //delay(3000); // 3 second delay for recovery
  Serial.begin(9600);
  start_time = millis();
  Serial.println("runvideo");
  //tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); 

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {sinelon_oneway};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void loop()
{


  if (millis() - start_time < 12000){
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
  }

if (millis() - start_time >= 12000 && millis() - start_time < 22000) {
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(4000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  //EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
  }

    if (millis() - start_time >= 22000 && millis() - start_time < 40000) {
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(2000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  //EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
  }

      if (millis() - start_time >= 40000 && millis() - start_time < 52000) {
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  //EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
  }

    else if (millis() - start_time >= 52000) {
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    //start_time = millis();   
    FastLED.show();
  }


  if (millis() - start_time >= 7000 && millis() - start_time < 8000) {
    if (fourth_timer_is_set == false) {
       x = 0;
      timer = millis();
      fourth_timer_is_set = true;
      Serial.println("runvideo");
      PulsateVibration(40, 100, false);
      //Serial.write("Reset");
    }
  }


  
   if (millis() - start_time >= 12000 && millis() - start_time < 52000) {
    if (first_timer_is_set == false) {
       x = 0;
      timer = millis();
      first_timer_is_set = true;
      //Serial.write("Reset"); 
    }

    if (millis() > timer + x) {
      //Serial.write("MOET GVD WERKEN");
      PulsateVibration(50, 80, true);
      x = x + 3000;  
    }
    //delay(1200);
  }

  // if (millis() - start_time >= 13000 && millis() - start_time < 48000) {
  //   if (second_timer_is_set == false) {
  //      x = 0;
  //     timer = millis();
  //     second_timer_is_set = true;
  //     //Serial.write("Reset");
  //   }

  //   if (millis() > timer + x) {
  //     //Serial.write("MOET GVD WERKEN");
  //     PulsateVibration(90, 110, true);
  //     x = x + 900;  
  //   }
  //   //delay(1200);
  // }

  // if (millis() - start_time >= 28500 && millis() - start_time < 48000) {
  //   if (third_timer_is_set == false) {
  //      x = 0;
  //     timer = millis();
  //     third_timer_is_set = true; 
  //     //Serial.write("Reset");
  //   }

  //   if (millis() > timer + x) {
  //     //Serial.write("MOET GVD WERKEN");
  //     PulsateVibration(100, 120, true);
  //     x = x + 600;
  //   }
  //   //delay(1200);
  // }

  if (millis() - start_time >= 52000 && millis() - start_time < 60000) {
    //Serial.write("stop");
    analogWrite(vib, 0);
  }


}

void PulsateVibration(int vib_int_min, int vib_int_max, bool light) {
  unsigned long vib_start_time = millis();
  unsigned long vib_passed_time = 0;
  unsigned long vib_time_step = 100;
  unsigned long delay = 100;
  unsigned long delay_timer = 0;
  bool vibrate_up = true;
  bool vibrate_down = false;
  vib_intensity = vib_int_min;
  int vib_step = (vib_int_max - vib_int_min) / 3;

  while (vibrate_up == true) {

      if (millis() - start_time >= 12000 && millis() - start_time < 22000) {
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(4000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  //EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
  }

    if (millis() - start_time >= 22000 && millis() - start_time < 40000) {
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(2000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  //EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
  }

      if (millis() - start_time >= 40000 && millis() - start_time < 52000) {
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  //EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
  }

    if (millis() > vib_start_time + delay_timer) {
      analogWrite(vib, vib_intensity);
      vib_intensity = vib_intensity + vib_step;       
      delay_timer = delay_timer + delay;
    }
    if (delay_timer > 300) {
      vibrate_up = false;
      vibrate_down = true;
    }
  }

  while (vibrate_down == true) {

      if (millis() - start_time >= 12000 && millis() - start_time < 22000) {
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(4000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  //EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
  }

    if (millis() - start_time >= 22000 && millis() - start_time < 40000) {
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(2000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  //EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
  }

      if (millis() - start_time >= 40000 && millis() - start_time < 52000) {
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  //EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
  }

    if (millis() > vib_start_time + delay_timer) {
      analogWrite(vib, vib_intensity);
      vib_intensity = vib_intensity - vib_step;       
      delay_timer = delay_timer + delay;
    }
    if (delay_timer > 610) {
      vibrate_up = true;
      vibrate_down = false;
      analogWrite(vib, 0);
    }
  }
  //Serial.write("stop nou eens");
  analogWrite(vib, 0);
  vibrate = false;
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))


void sinelon_oneway()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy(leds, NUM_LEDS, 20);
  static int pos = 0; // declare a static variable to remember the last position

  // increment or decrement the position depending on the direction
  if (pos == NUM_LEDS - 1) {
    pos = 0; // start from the beginning when it reaches the end
  } else {
    pos++;
  }

  // add the color to the new position
    leds[pos] += CHSV(128, 255, 224);
}




