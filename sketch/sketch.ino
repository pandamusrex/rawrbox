// RAWRBOX
// PANDAMUSREX
// 2026

#include <MIDI.h>
#include "track.h"

#include <SPI.h>
#include <Wire.h>
#include <ILI9341_t3.h>
#include <XPT2046_Touchscreen.h>

// Touch input
#define CS_PIN  8
#define TIRQ_PIN  2
// MOSI=11, MISO=12, SCK=13
XPT2046_Touchscreen ts(CS_PIN, TIRQ_PIN);

// Screen
#define TFT_RST  6
#define TFT_DC  9
#define TFT_CS 10
// MOSI=11, MISO=12, SCK=13
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST);

// MIDI
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

// Sequencer
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
  // Debugging
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); 

  // Screen
  tft.begin();
  tft.setRotation(2);
  tft.fillScreen(ILI9341_BLACK);

  // tft.fillRect(20, 20, 40, 30, ILI9341_RED);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  
  tft.setCursor(10, 10);
  tft.println("1: Drums/Rample 1");
  tft.drawRect(10, 45, 40, 40, ILI9341_WHITE);
  tft.drawRect(70, 45, 40, 40, ILI9341_WHITE);
  tft.drawRect(130, 45, 40, 40, ILI9341_GREEN);
  tft.drawRect(190, 45, 40, 40, ILI9341_WHITE);
  tft.setCursor(10, 90);
  tft.println("2: Bass Synth/Pro-1");
  // tft.fillRect(20, 20, 40, 30, ILI9341_RED);
  tft.setCursor(10, 170);
  tft.println("3: Arp/Rample 2");
  // tft.fillRect(20, 20, 40, 30, ILI9341_RED);
  tft.setCursor(10, 250);
  tft.println("4: Plaits");
  // tft.fillRect(20, 20, 40, 30, ILI9341_RED);

  // Touch
  ts.begin();
  ts.setRotation(2);
  while (!Serial && (millis() <= 1000));

  // MIDI
  MIDI.begin();

  // Sequencer
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

  // Flash the built in LED on the 1st beat

  if (subBeat % 4 == 0) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  subBeat++;
  if (subBeat > 15) {
    subBeat = 0;
  }

  // Handle touches
    if (ts.touched()) {
      TS_Point p = ts.getPoint();
      Serial.print("Pressure = ");
      Serial.print(p.z);
      Serial.print(", x = ");
      Serial.print(p.x);
      Serial.print(", y = ");
      Serial.print(p.y);
      delay(30);
      Serial.println();
  }

  // TODO better tempo management
  delay(100);
}