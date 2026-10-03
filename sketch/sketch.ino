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
Sequencer seq = Sequencer(MIDI);
#define DRUM_TRACK 0
#define BASS_SYNTH_TRACK 1
#define ARP_TRACK 2
#define PLAITS_TRACK 3

// UI
unsigned int subBeat = 0;
bool inTouch = false;

void setup() {
  // Debugging
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); 

  // Screen
  tft.begin();
  tft.setRotation(2);
  tft.fillScreen(ILI9341_BLACK);

  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  
  // TODO SHOW MUTE/UNMUTE
  // TODO DISABLE PREV NEXT "BUTTONS" IF < 2 LOOPS ON A TRACK

  tft.drawRect(5, 5, 50, 70, ILI9341_WHITE);
  tft.setCursor(60, 10);
  tft.println("1: Drums/Rample 1"); // TODO READ FROM TRACK
  tft.drawRect(180, 5, 50, 70, ILI9341_WHITE);

  tft.drawRect(5, 85, 50, 70, ILI9341_WHITE);
  tft.setCursor(60, 90);
  tft.println("2: Bass Synth/Pro-1"); // TODO READ FROM TRACK
  tft.drawRect(180, 85, 50, 70, ILI9341_WHITE);

  tft.drawRect(180, 165, 50, 70, ILI9341_WHITE);
  tft.setCursor(60, 170);
  tft.println("3: Arp/Rample 2"); // TODO READ FROM TRACK
  tft.drawRect(180, 165, 50, 70, ILI9341_WHITE);

  tft.drawRect(180, 245, 50, 70, ILI9341_WHITE);
  tft.setCursor(60, 250);
  tft.println("4: Plaits"); // TODO READ FROM TRACK
  tft.drawRect(180, 245, 50, 70, ILI9341_WHITE);

  // Touch
  ts.begin();
  ts.setRotation(2);
  while (!Serial && (millis() <= 1000));

  // MIDI
  MIDI.begin();

  // C0:24, C1:36, C2:48, C3:60, C4:72
  seq.setMIDIChannelForTrack(DRUM_TRACK, 1);
  seq.setMIDIChannelForTrack(1, 2);
  seq.setMIDIChannelForTrack(2, 3);
  seq.setMIDIChannelForTrack(3, 4);

  // Sequencer
  sequencer.addLoopToTrack(DRUM_TRACK,
    "Knight Rider",
    "4 on the Floor",
    "c1 @ @ ~  c1 @ @ ~  c1 @ @ ~  c1 @ @ ~"
  );

  sequencer.addLoopToTrack(DRUM_TRACK,
    "Blue Monday",
    "Drums",
    "c1 @ @ ~  c1 @ @ ~  c1 c1 c1 c1  c1 c1 c1 c1 "
    "c1 @ @ ~  c1 @ @ ~  c1 @ @ ~     c1 @ @ ~"
  );

  sequencer.addLoopToTrack(DRUM_TRACK,
    "Sweet Dreams",
    "4 on the Floor",
    "c1 @ @ ~  c1 @ @ ~  c1 @ @ ~  c1 @ @ ~"
  );

  sequencer.addLoopToTrack(BASS_SYNTH_TRACK,
    "Knight Rider",
    "Bass Line",
    "f#1 f#1 ~ ~  f#1 f#1 ~ ~  f#1 f#1 ~ ~  ~ ~ ~ ~ "
    "f#1 f#1 ~ ~  f#1 f#1 ~ ~  f#1 f#1 ~ ~  ~ ~ ~ ~ "
    "e1 e1 ~ ~    e1 e1 ~ ~    e1 e1 ~ ~    ~ ~ ~ ~ "
    "e1 e1 ~ ~    e1 e1 ~ ~    e1 e1 ~ ~    ~ ~ ~ ~ "
    "f#1 f#1 ~ ~  f#1 f#1 ~ ~  f#1 f#1 ~ ~  ~ ~ ~ ~ "
    "f#1 f#1 ~ ~  f#1 f#1 ~ ~  f#1 f#1 ~ ~  ~ ~ ~ ~ "
    "g1 g1 ~ ~    g1 g1 ~ ~    g1 g1 ~ ~    ~ ~ ~ ~ "
    "g1 g1 ~ ~    g1 g1 ~ ~    g1 g1 ~ ~    ~ ~ ~ ~"
  );

  sequencer.addLoopToTrack(BASS_SYNTH_TRACK,
    "Blue Monday",
    "Bass",
    "f1 @ f2 @  f1 @ f2 @  c1 @ c2 @  c1 @ c2 @ "
    "d1 @ d2 @  d1 @ d2 @  d1 @ d2 @  d1 @ d2 @ "
    "g1 @ g2 @  g1 @ g2 @  c1 @ c2 @  c1 @ c2 @ "
    "d1 @ d2 @  d1 @ d2 @  d1 @ d2 @  d1 @ d2 @"
  )

  sequencer.addLoopToTrack(BASS_SYNTH_TRACK,
    "Sweet Dreams",
    "Bass",
    "c1 @ c1 @  ~ ~ ~ ~  ~ ~ ~ ~  ~ ~ ~ ~ "
    "~ ~ ~ ~    ~ ~ ~ ~  ~ ~ ~ ~  ~ ~ ~ ~ "
  )

  sequencer.addLoop(ARP_TRACK,
    "Knight Rider",
    "Arp",
    "c#4 @ d4 c#4  c#4 d4 c#4 c#4  d4 c#4 c#4 c#4  c4 c#4 c#4 c#4 "
    "c#4 @ d4 c#4  c#4 d4 c#4 c#4  d4 c#4 c#4 c#4  c4 c#4 c#4 c#4 "
    "b3 @ c4 b3    b3 c4 b3 b3     c4 b3 b3 b3     a#3 b3 b3 b3 "
    "b3 @ c4 b3    b3 c4 b3 b3     c4 b3 b3 b3     a#3 b3 b3 b3"
  );

  sequencer.addLoop(ARP_TRACK, "Blue Monday", "Mid Motif",
    "f3 @ f3 @  f3 @ g3 @  c3 @ c3 @  c3 @ d3 @ "
    "d3 @ @ @   d3 @ d3 @  @ @ d3 @   d3 @ @ @ "
    "f3 @ f3 @  f3 @ g3 @  c3 @ c3 @  c3 @ d3 @ "
    "d3 @ @ @   d3 @ d3 @  @ @ d3 @   d3 @ @ @"
  );

  sequencer.addLoop(ARP_TRACK, "Sweet Dreams", "Mid Motif",
    "c2 @ c2 @    c3 @ c4 @   eb3 @ eb4 @  c3 @ c4 @ "
    "ab3 @ ab3 @  ab4 @ c4 @  g2 @ g2 @    g3 @ c4 @"
  );
}

void loop() {
  sequencer.playNextSixteenth();

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
  if (ts.touched()) { // if screen is being touched
    if (!inTouch) { // if we haven't already processed this touch
      inTouch = true;

      TS_Point p = ts.getPoint();
      if (p.z > 1500) {
        unsigned char track;
        unsigned char position;

        track = p.y / 800;
        if (track > 3) {
          track = 3;
        } // TODO TRACK_COUNT

        if (p.x < 1000) { // LEFT OF TRACK == QUEUE PREVIOUS LOOP
          seq.queuePrevLoopForTrack(trackNum);
        } else if (p.x > 2000) { // RIGHT OF TRACK == QUEUE NEXT LOOP
          seq.queueNextLoopForTrack(trackNum);
        } else { // CENTER OF TRACK == TOGGLE MUTE
          seq.toggleMuteForTrack(trackNum);
        }
      }
      //Serial.print("Pressure = ");
      //Serial.print(p.z);
      //Serial.print(", x = ");
      //Serial.print(p.x);
      //Serial.print(", y = ");
      //Serial.print(p.y);
      //delay(30);
      //Serial.println();
    }
  } else {
    inTouch = false;
  }

  // TODO tempo management
  delay(100);
}