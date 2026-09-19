#include <MIDI.h>

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