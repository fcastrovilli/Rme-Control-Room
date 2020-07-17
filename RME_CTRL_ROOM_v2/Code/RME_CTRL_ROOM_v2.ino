//LED

#include <FastLED.h>

#define LED_PIN     14
#define NUM_LEDS    16
#define BRIGHTNESS  200
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 40

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

//MIDI

#include <MIDI.h>
#if defined(USBCON)
#include <midi_UsbTransport.h>
static const unsigned sUsbTransportBufferSize = 16;
typedef midi::UsbTransport<sUsbTransportBufferSize> UsbTransport;
UsbTransport sUsbTransport;
MIDI_CREATE_INSTANCE(UsbTransport, sUsbTransport, MIDI);
//#else // No USB available, fallback to Serial
//MIDI_CREATE_DEFAULT_INSTANCE();
#endif


#include "ClickButton.h"
#include <ClickEncoder.h>
#include <TimerOne.h>
#include "Mouse.h"

ClickEncoder *encoder;
int16_t last, value;

void timerIsr() {
  encoder->service();
}

bool mode = 0;                  /////////////////////////////////////////////////
int function = 1;               /////////////////////////////////////////////////
int masterVol = 0;               /////////////////////////////////////////////////
int hp1Vol = 0;               /////////////////////////////////////////////////
int hp2Vol = 0;               /////////////////////////////////////////////////

int mouseMovement = 0;
float multiplierX = 1;
float multiplierY = 1;

//Button
const int buttonPin1 = 3;
ClickButton button1(buttonPin1, LOW, CLICKBTN_PULLUP);

//TIMERS
#include <elapsedMillis.h>
elapsedMillis encTimer;
elapsedMillis relTimer;

#define  ENC_TIME 150                 //Tempo di rilascio dopo il click !!!PARAMETRO
#define  CLICK_TIME 250              //Tempo di azzeramento dopo il movimento dell'encoder !!!PARAMETRO


void setup() {
  //Serial.begin(9600);
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  MIDI.begin();
  Mouse.begin();
  //////////////////////////////////////////////////////////////////////////////
  button1.debounceTime   = 20;   // Debounce timer in ms
  button1.multiclickTime = 250;  // Time limit for multi clicks
  button1.longClickTime  = 1000; // time until "held-down clicks" register
  //////////////////////////////////////////////////////////////////////////////
  encoder = new ClickEncoder(A3, A1, 0);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);
  last = -1;
  //////////////////////////////////////////////////////////////////////////////

}

void loop() {
  button();
  encFunz();
  ledRing();
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
  MidiUSB.flush();
}
