// License: CC0
//

#include <Adafruit_NeoPixel.h>
#define LED_PIN    6

#define LED_COUNT 19

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

// mapping
// 0 moon
// 1 left star
// 2 left upper middle eye
// 3 right upper middle eye
// 4 right star
// 5 right eye
// 6 middle eye
// 7 left eye
// 8 left left upper ray
// 9 left lower middle eye
// 10 right lower middle eye
// 11 right right upper ray
// 12 right right lower ray
// 13 rigtht lower ray
// 14 right upper ray
// 15 middle ray
// 16 left top ray
// 17 left bottom ray
// 18 left left bottom ray

enum pos{
  MOON = 0,
  STAR_LEFT,
  EYE_LEFT_UPPER,
  EYE_RIGHT_UPPER,
  STAR_RIGHT,
  EYE_RIGHT,
  EYE_MIDDLE,
  EYE_LEFT,
  RAYLL_UPPER,
  EYE_LEFT_LOWER,
  EYE_RIGHT_LOWER,
  RAYRR_UPPER,
  RAYRR_LOWER,
  RAYR_LOWER,
  RAYR_UPPER,
  RAY,
  RAYL_UPPER,
  RAYL_LOWER,
  RAYLL_LOWER
};

uint8_t _lin(int16_t _imin, int16_t _imax, int16_t _icur, uint8_t _omin, uint8_t _omax) {
  int32_t t;
  if (_icur <= _imin) { return _omin; }
  if (_icur >= _imax) { return _omax; }

  t = (_omax - _omin);
  t *= (_icur - _imin);
  t /= (_imax - _imin);

  if (t > 255) { return 255; }
  return (uint8_t)t;
}

void fade(uint16_t hue, int16_t _t, int *pos, int npos) {
  int16_t _mid = _t/2;
  for (int16_t it=0; it<_t; it++) {
    strip.clear();
    for (int i=0; i<npos; i++) {
      uint8_t v = 0;
      if (it < _mid)  { v = _lin(0, _mid, it, 0, 255); }
      else            { v = _lin(0, _mid, _t - it, 0, 255); }   
      uint32_t _c = strip.ColorHSV(hue, 255, v);
      strip.setPixelColor(pos[i], strip.gamma32(_c));
    }
    strip.show();
  }
}

void burstv(uint16_t hue, uint16_t d, int *_s, int _sn, int *_e, int _en) {
  int16_t T = 102, dt = 1, pt = 12, w=50;
  uint8_t p0, p1;

  int b;

  for (int16_t t=0; t<(T+pt); t+=dt) {
    p0 = _lin(0, w, t, 0, 255);
    if (t>(T-w)) { p0 = _lin(0, w, T - t, 0, 255); }
    p1 = _lin(0, w, t-pt, 0, 255);
    if ((t-pt)>(T-w)) { p1 = _lin(0, w, T - t + pt, 0, 255); }

    b = p0;
    strip.clear();
    for (int i=0; i<_sn; i++) {
      strip.setPixelColor(_s[i], strip.gamma32(strip.ColorHSV(hue, 255, b)));
    }

    b = p1;
    for (int i=0; i<_en; i++) {
      strip.setPixelColor(_e[i], strip.gamma32(strip.ColorHSV(hue, 255, b)));
    }
    strip.show();
    delay(d);
  }
  
}


void burstvi(uint16_t hue0, uint16_t hue1, uint16_t d, int *_s, int _sn, int *_e, int _en) {
  int16_t T = 102, dt = 1, pt = 22, w=45;
  uint8_t p0, p1;

  int b;

  int32_t _a = (int32_t)((int32_t)hue1 - (int32_t)hue0);
  int32_t _b = (int32_t)((int32_t)hue0 + 65536 - (int32_t)hue1);

  int32_t hue_step = 0;
  if (abs(_a) < abs(_b)) {
    hue_step = _a / (T+pt);
  }
  else {
    hue_step = - _b / (T+pt);
  }

  int32_t hue=hue0;
  

  for (int16_t t=0; t<(T+pt); t+=dt) {
    p0 = _lin(0, w, t, 0, 255);
    if (t>(T-w)) { p0 = _lin(0, w, T - t, 0, 255); }
    p1 = _lin(0, w, t-pt, 0, 255);
    if ((t-pt)>(T-w)) { p1 = _lin(0, w, T - t + pt, 0, 255); }

    b = p0;
    strip.clear();
    for (int i=0; i<_sn; i++) {
      strip.setPixelColor(_s[i], strip.gamma32(strip.ColorHSV(hue, 255, b)));
    }

    b = p1;
    for (int i=0; i<_en; i++) {
      strip.setPixelColor(_e[i], strip.gamma32(strip.ColorHSV(hue, 255, b)));
    }
    strip.show();
    delay(d);
    hue += hue_step;
    hue += 65536;
    hue %= 65536;
  }
  
}

void burst(uint16_t hue) {
  char _s[] = { RAYLL_UPPER, RAYL_UPPER, RAY, RAYR_UPPER, RAYRR_UPPER };
  char _e[] = { RAYLL_LOWER, RAYL_LOWER, RAYR_LOWER, RAYRR_LOWER };
  int _sn = 5, _en=4;

  int16_t T = 102, dt = 1, pt = 12, w=50;
  uint8_t p0, p1;

  uint32_t d=20;

  for (int16_t t=0; t<(T+pt); t+=dt) {
    p0 = _lin(0, w, t, 0, 255);
    if (t>(T-w)) { p0 = _lin(0, w, T - t, 0, 255); }
    p1 = _lin(0, w, t-pt, 0, 255);
    if ((t-pt)>(T-w)) { p1 = _lin(0, w, T - t + pt, 0, 255); }

    int b = strip.gamma8(p0);
    b = p0;
    strip.clear();
    for (int i=0; i<_sn; i++) {
      strip.setPixelColor(_s[i], strip.gamma32(strip.ColorHSV(hue, 255, b)));
    }

    b = strip.gamma8(p1);
    b = p1;
    for (int i=0; i<_en; i++) {
      strip.setPixelColor(_e[i], strip.gamma32(strip.ColorHSV(hue, 255, b)));
    }
    strip.show();
    delay(d);
  }

}



void loop() {
  int x[] = { MOON };
  int y[] = { STAR_LEFT, STAR_RIGHT };
  int z[] = { EYE_LEFT, EYE_LEFT_UPPER, EYE_RIGHT_UPPER, EYE_RIGHT, EYE_LEFT_LOWER, EYE_RIGHT_LOWER, EYE_MIDDLE};

  int a[] = { EYE_LEFT, EYE_LEFT_UPPER, EYE_RIGHT_UPPER, EYE_RIGHT, EYE_LEFT_LOWER, EYE_RIGHT_LOWER, EYE_MIDDLE,
              RAYRR_UPPER, RAYR_UPPER, RAY, RAYL_UPPER, RAYLL_UPPER };
  int b[] = { MOON, STAR_LEFT, STAR_RIGHT, RAYRR_LOWER, RAYR_LOWER, RAYL_LOWER, RAYLL_LOWER };

  uint32_t  purple = (300*65536)/360,
            red = 0,
            green = (120*65536)/360,
            blue = (240*65536)/360;
  

//  burstv(purple, 35, a, 12, b ,7);
  burstvi(red, purple, 35, a, 12, b ,7);
  return;


  for (uint32_t i=0; i<65536; i+=1024*8) {
    burstv((uint16_t)i, 20, a, 12, b, 7);
  }
return;
  fade(55000, 1500, x, 1);
  fade(60600, 1500, y, 2);
  fade(48000, 1500, z, 7);
  burst(65000);
  burstv(10000, 20, a, 12, b, 7);
  
  delay(500);
  return;
  
  // Fill along the length of the strip in various colors...
  //
  colorWipe(strip.Color(255,   0,   0), 50); // Red
  colorWipe(strip.Color(  0, 255,   0), 50); // Green
  colorWipe(strip.Color(  0,   0, 255), 50); // Blue

  // Do a theater marquee effect in various colors...
  //
  theaterChase(strip.Color(127, 127, 127), 50); // White, half brightness
  theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
  theaterChase(strip.Color(  0,   0, 127), 50); // Blue, half brightness

  rainbow(10);
  theaterChaseRainbow(50);
}

void test_mapping() {
  strip.clear();
  uint32_t color = strip.Color(255,0,0);
  for(int i=0; i<strip.numPixels(); i++) {
    strip.clear();
    strip.setPixelColor(i, color); // Set pixel 'c' to value 'color'
    strip.show();
    delay(1000);
  }

  strip.clear();
  strip.setPixelColor(MOON, color);
  strip.show();
  delay(1000);

  strip.clear();
  strip.setPixelColor(STAR_LEFT, color);
  strip.show();
  delay(1000);

  strip.clear();
  strip.setPixelColor(EYE_LEFT_UPPER, color);
  strip.show();
  delay(1000);

  strip.clear();
  strip.setPixelColor(EYE_RIGHT_UPPER, color);
  strip.show();
  delay(1000);

  strip.clear();
  strip.setPixelColor(STAR_RIGHT, color);
  strip.show();
  delay(1000);

  strip.clear();
  strip.setPixelColor(EYE_RIGHT, color);
  strip.show();
  delay(1000);

  strip.clear();
  strip.setPixelColor(EYE_MIDDLE, color);
  strip.show();
  delay(1000);

  strip.clear();
  strip.setPixelColor(EYE_LEFT, color);
  strip.show();
  delay(1000);

  strip.clear();
  strip.setPixelColor(RAYLL_UPPER, color);
  strip.show();
  delay(1000);

  strip.clear();
  strip.setPixelColor(EYE_LEFT_LOWER, color);
  strip.show();
  delay(1000);

  strip.clear();
  strip.setPixelColor(EYE_RIGHT_LOWER, color);
  strip.show();
  delay(1000);

  strip.clear();
  strip.setPixelColor(RAYRR_UPPER, color);
  strip.show();
  delay(1000);

  strip.clear();
  strip.setPixelColor(RAYRR_LOWER, color);
  strip.show();
  delay(1000);

  strip.clear();
  strip.setPixelColor(RAYR_LOWER, color);
  strip.show();
  delay(1000);

  strip.clear();
  strip.setPixelColor(RAYR_UPPER, color);
  strip.show();
  delay(1000);

  strip.clear();
  strip.setPixelColor(RAY, color);
  strip.show();
  delay(1000);

  strip.clear();
  strip.setPixelColor(RAYL_UPPER, color);
  strip.show();
  delay(1000);

  strip.clear();
  strip.setPixelColor(RAYL_LOWER, color);
  strip.show();
  delay(1000);

  strip.clear();
  strip.setPixelColor(RAYLL_LOWER, color);
  strip.show();
  delay(1000);

  
  strip.show(); // Update strip with new contents
}

// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
