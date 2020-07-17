DEFINE_GRADIENT_PALETTE(rosso) {            //x
  0, 120,  1,  2,
  127, 179,  1,  3,
  255, 255,  1,  4
};

DEFINE_GRADIENT_PALETTE( verde ) {            // y
  0,    56, 142,  0,
  127,  56, 182,  0,
  255,  56, 200,  0,
  127,  56, 182,  0,
  0,    56, 142,  0
};

DEFINE_GRADIENT_PALETTE( blu ) {           //  scroll
  0,  1,  5,  35,
  45,  3,  7, 50,
  79,   15, 20, 150,
  119,  30, 35, 180,
  158,   15, 20, 150,
  209,   3,  7, 50,
  255,   1,  5,  35
};


DEFINE_GRADIENT_PALETTE(rosa) {        //midi cc1
  0, 247, 79, 17,
  60, 169, 37, 29,
  121, 109, 12, 43,
  188,  55,  9, 41,
  255,  22,  6, 38
};

DEFINE_GRADIENT_PALETTE( giallo ) {       //midi cc3
  0, 215, 97,  1,
  109, 210, 221,  1,
  181, 215, 151,  1,
  232, 232, 239, 32,
  255, 232, 239, 32
};

DEFINE_GRADIENT_PALETTE( smeraldo ) {         //midi cc2
  0,   6, 67, 24,
  53,   4, 37, 13,
  127,   9, 73, 29,
  191,   1, 51, 14,
  255,   2, 37, 12
};


void ledRing() {

  if (mode == 0 && function == 1) {
    currentPalette = rosa;
  }
  else if (mode == 0 && function == 2) {
    currentPalette = smeraldo;
  }
  else if (mode == 0 && function == 3) {
    currentPalette = giallo;
  }
  else if (mode == 1 && function == 1) {
    currentPalette = blu;
  }
  else if (mode == 1 && function == 2) {
    currentPalette = verde;
  }
  else if (mode == 1 && function == 3) {
    currentPalette = rosso;
  }

  currentBlending = LINEARBLEND;
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */

  FillLEDsFromPaletteColors( startIndex);

  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex) {
  uint8_t brightness = 255;
  for ( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}

