#include <MIDI.h>

#include <SPI.h>
#include <Wire.h>
#include <ILI9341_t3.h>

#include "track.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

const int channel = 1;

Track *pDrums = 0;
Track *pBassLine = 0;
Track *pArpeggio = 0;

unsigned int subBeat = 0;
int previousNote_1 = 0;
int note_1 = 0;
int previousNote_2 = 0;
int note_2 = 0;
int previousNote_3 = 0;
int note_3 = 0;

void setup() {
  Serial.begin(9600);

  // SparkFun SKU COM-28380
  // https://www.sparkfun.com/color-320x240-touchscreen-3-2-inch-ili9341-controller.html
  // TFT VCC   5V
  // TFT GND   GND
  // TFT CS    10
  // TFT RESET 8
  // TFT DC    9
  // TFT MOSI  11
  // TFT SCK   13
  // TFT MISO  12
  #define TFT_RST  8
  #define TFT_DC  9
  #define TFT_CS 10
  ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST);

  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  tft.fillRect(20, 20, 40, 30, ILI9341_RED);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(40, 40);
  tft.println("C4");

  MIDI.begin();
  pinMode(LED_BUILTIN, OUTPUT); 

  pDrums = new Track();
  pDrums->addClip("c1 @ @ ~  c1 @ @ ~  c1 @ @ ~  c1 @ @ ~ ");

  pBassLine = new Track();
  pBassLine->addClip(
    "f#1 f#1 ~ ~  f#1 f#1 ~ ~  f#1 f#1 ~ ~  ~ ~ ~ ~ "
    "f#1 f#1 ~ ~  f#1 f#1 ~ ~  f#1 f#1 ~ ~  ~ ~ ~ ~ "
    "e1 e1 ~ ~    e1 e1 ~ ~    e1 e1 ~ ~    ~ ~ ~ ~ "
    "e1 e1 ~ ~    e1 e1 ~ ~    e1 e1 ~ ~    ~ ~ ~ ~ "
    "f#1 f#1 ~ ~  f#1 f#1 ~ ~  f#1 f#1 ~ ~  ~ ~ ~ ~ "
    "f#1 f#1 ~ ~  f#1 f#1 ~ ~  f#1 f#1 ~ ~  ~ ~ ~ ~ "
    "g1 g1 ~ ~    g1 g1 ~ ~    g1 g1 ~ ~    ~ ~ ~ ~ "
    "g1 g1 ~ ~    g1 g1 ~ ~    g1 g1 ~ ~    ~ ~ ~ ~");

  pArpeggio = new Track();
  pArpeggio->addClip(
    "c#4 @ d4 c#4  c#4 d4 c#4 c#4  d4 c#4 c#4 c#4  c4 c#4 c#4 c#4 "
    "c#4 @ d4 c#4  c#4 d4 c#4 c#4  d4 c#4 c#4 c#4  c4 c#4 c#4 c#4 "
    "b3 @ c4 b3    b3 c4 b3 b3     c4 b3 b3 b3     a#3 b3 b3 b3 "
    "b3 @ c4 b3    b3 c4 b3 b3     c4 b3 b3 b3     a#3 b3 b3 b3");
}

void loop() {

  note_1 = pDrums->getNote();
  if (previousNote_1 != 0) {
    MIDI.sendNoteOff(previousNote_1, 100, 1);
  }
  previousNote_1 = note_1;
  if (note_1 != 0) {
    MIDI.sendNoteOn(note_1, 100, 1);
  }

  /////////////////

  note_2 = pBassLine->getNote();
  if (previousNote_2 != 0) {
    MIDI.sendNoteOff(previousNote_2, 100, 2);
  }
  previousNote_2 = note_2;
  if (note_2 != 0) {
    MIDI.sendNoteOn(note_2, 100, 2);
  }

  ////////////////

  note_3 = pArpeggio->getNote();
  if (previousNote_3 != 0) {
    MIDI.sendNoteOff(previousNote_3, 100, 3);
  }
  previousNote_3 = note_3;
  if (note_3 != 0) {
    MIDI.sendNoteOn(note_3, 100, 3);
  }

  ///////////////

  if (subBeat % 4 == 0) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  subBeat++;
  if (subBeat > 15) {
    subBeat = 0;
  }
  delay(100);
}