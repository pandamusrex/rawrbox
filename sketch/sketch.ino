/*
 ____                 _                           ____           
|  _ \ __ _ _ __   __| | __ _ _ __ ___  _   _ ___|  _ \ _____  __
| |_) / _` | '_ \ / _` |/ _` | '_ ` _ \| | | / __| |_) / _ \ \/ /
|  __/ (_| | | | | (_| | (_| | | | | | | |_| \__ \  _ <  __/>  < 
|_|   \__,_|_| |_|\__,_|\__,_|_| |_| |_|\__,_|___/_| \_\___/_/\_\

RAWRBOX
2026
*/

#include "sequencer.h"

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

// Sequencer
Sequencer seq = Sequencer();
#define DRUM_TRACK_0 0
#define BASS_SYNTH_TRACK_1 1
#define ARP_TRACK_2 2
#define PLAITS_TRACK_3 3

// UI
unsigned int subBeat = 0;
bool inTouch = false;

void preloadSequencer() {
  // C0:24, C1:36, C2:48, C3:60, C4:72
  seq.setMIDIChannelForTrack(DRUM_TRACK_0, 1);
  seq.setMIDIChannelForTrack(BASS_SYNTH_TRACK_1, 2);
  seq.setMIDIChannelForTrack(ARP_TRACK_2, 3);
  seq.setMIDIChannelForTrack(PLAITS_TRACK_3, 4);

  // Sequencer
  seq.addLoopToTrack(DRUM_TRACK_0,
    "Knight Rider",
    "4 on the Floor",
    "c1 @ @ ~  c1 @ @ ~  c1 @ @ ~  c1 @ @ ~"
  );

  seq.addLoopToTrack(DRUM_TRACK_0,
    "Blue Monday",
    "Drums",
    "c1 @ @ ~  c1 @ @ ~  c1 c1 c1 c1  c1 c1 c1 c1 "
    "c1 @ @ ~  c1 @ @ ~  c1 @ @ ~     c1 @ @ ~"
  );

  seq.addLoopToTrack(DRUM_TRACK_0,
    "Sweet Dreams",
    "4 on the Floor",
    "c1 @ @ ~  c1 @ @ ~  c1 @ @ ~  c1 @ @ ~"
  );

  seq.addLoopToTrack(BASS_SYNTH_TRACK_1,
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

  seq.addLoopToTrack(BASS_SYNTH_TRACK_1,
    "Blue Monday",
    "Bass",
    "f1 @ f2 @  f1 @ f2 @  c1 @ c2 @  c1 @ c2 @ "
    "d1 @ d2 @  d1 @ d2 @  d1 @ d2 @  d1 @ d2 @ "
    "g1 @ g2 @  g1 @ g2 @  c1 @ c2 @  c1 @ c2 @ "
    "d1 @ d2 @  d1 @ d2 @  d1 @ d2 @  d1 @ d2 @"
  );

  seq.addLoopToTrack(BASS_SYNTH_TRACK_1,
    "Sweet Dreams",
    "Bass",
    "c1 @ c1 @  ~ ~ ~ ~  ~ ~ ~ ~  ~ ~ ~ ~ "
    "~ ~ ~ ~    ~ ~ ~ ~  ~ ~ ~ ~  ~ ~ ~ ~ "
  );

  seq.addLoopToTrack(ARP_TRACK_2,
    "Knight Rider",
    "Arp",
    "c#4 @ d4 c#4  c#4 d4 c#4 c#4  d4 c#4 c#4 c#4  c4 c#4 c#4 c#4 "
    "c#4 @ d4 c#4  c#4 d4 c#4 c#4  d4 c#4 c#4 c#4  c4 c#4 c#4 c#4 "
    "b3 @ c4 b3    b3 c4 b3 b3     c4 b3 b3 b3     a#3 b3 b3 b3 "
    "b3 @ c4 b3    b3 c4 b3 b3     c4 b3 b3 b3     a#3 b3 b3 b3"
  );

  seq.addLoopToTrack(ARP_TRACK_2,
    "Blue Monday",
    "Mid Motif",
    "f3 @ f3 @  f3 @ g3 @  c3 @ c3 @  c3 @ d3 @ "
    "d3 @ @ @   d3 @ d3 @  @ @ d3 @   d3 @ @ @ "
    "f3 @ f3 @  f3 @ g3 @  c3 @ c3 @  c3 @ d3 @ "
    "d3 @ @ @   d3 @ d3 @  @ @ d3 @   d3 @ @ @"
  );

  seq.addLoopToTrack(ARP_TRACK_2,
    "Sweet Dreams",
    "Mid Motif",
    "c2 @ c2 @    c3 @ c4 @   eb3 @ eb4 @  c3 @ c4 @ "
    "ab3 @ ab3 @  ab4 @ c4 @  g2 @ g2 @    g3 @ c4 @"
  );
}

#define MAX_TRACK_TITLE 32

void updateUI() {  
  // TODO SHOW MUTE/UNMUTE
  // TODO DISABLE PREV NEXT "BUTTONS" IF < 2 LOOPS ON A TRACK

  int loopCount = 0;
  char trackTitle[MAX_TRACK_TITLE] = "NO TITLE";
  bool isMuted = false;
  bool hasQueuedLoop = false;

  uint16_t trackTitleColor = ILI9341_CYAN;
  uint16_t trackControlsColor = ILI9341_LIGHTGREY;

  int16_t yOffset = 0;

  uint16_t titleWidth = 0;
  uint16_t titleHeight = 0;

  int16_t xTitle = 0;
  int16_t yTitle = 0;

  for (int track = 0; track < 4; track++) {
    yOffset = track * 64;

    loopCount = seq.getNumLoopsForTrack(track);
    seq.getLoopTitleForTrack(track, trackTitle, MAX_TRACK_TITLE - 1);
    isMuted = seq.isTrackMuted(track);
    hasQueuedLoop = seq.hasQueuedLoop(track);

    if (loopCount == 0) {
      trackTitleColor = ILI9341_DARKGREY;
    } else if (isMuted) {
      trackTitleColor = ILI9341_DARKCYAN;
    } else {
      trackTitleColor = hasQueuedLoop ? ILI9341_MAGENTA : ILI9341_CYAN;
    }

    trackControlsColor = (loopCount > 0) ? ILI9341_LIGHTGREY : ILI9341_DARKGREY;

    // Left triangle
    tft.fillTriangle(16, yOffset + 32,
                     32, yOffset + 24,
                     32, yOffset + 40,
                     trackControlsColor);
    // Title
    tft.setTextSize(2);
    titleWidth = tft.measureTextWidth(trackTitle);
    titleHeight = tft.measureTextHeight(trackTitle);
    xTitle = 120 - titleWidth / 2;
    yTitle = yOffset + 32 - titleHeight / 2;
    tft.setCursor(xTitle, yTitle);
    tft.setTextColor(trackTitleColor);
    tft.println(trackTitle);

    // Right triangle
    tft.fillTriangle(224, yOffset + 32,
                     208, yOffset + 24,
                     208, yOffset + 40,
                     trackControlsColor);

  }
}

void setup() {
  // Debugging using VCP and built-in LED
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); 

  // Load tracks
  preloadSequencer();

  // Setup Screen
  tft.begin();
  tft.setRotation(2);
  tft.fillScreen(ILI9341_BLACK);

  // Setup Touch
  ts.begin();
  ts.setRotation(2);
  while (!Serial && (millis() <= 1000)); // Wait for USB VCP to come on line

  // Draw the UI for the first time
  updateUI();
}

void loop() {
  seq.playNextSixteenth();

  ///////////////
  // Flash the built in LED on the beats

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
      Serial.println(p.y);
      if (p.z > 1500) {
        unsigned char track;

        track = p.y / 800;
        if (track > 3) {
          track = 3;
        } // TODO TRACK_COUNT

        if (p.x < 1000) { // LEFT OF TRACK == QUEUE PREVIOUS LOOP
          seq.queuePrevLoopForTrack(track);
        } else if (p.x > 2000) { // RIGHT OF TRACK == QUEUE NEXT LOOP
          seq.queueNextLoopForTrack(track);
        } else { // CENTER OF TRACK == TOGGLE MUTE
          seq.toggleMuteForTrack(track);
        }
      }
      updateUI(); // If we start showing loop position, we may need to move this out?
    }
  } else {
    inTouch = false;
  }

  // TODO tempo management
  delay(110);
}