#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

const int channel = 1;

void setup() {
  MIDI.begin();
  pinMode(LED_BUILTIN, OUTPUT); // initialize digital pin LED_BUILTIN as an output
}

void loop() {
  int note;
  for (note=10; note <= 127; note++) {
    MIDI.sendNoteOn(note, 100, channel);
    digitalWrite(LED_BUILTIN, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
    delay(200);
    MIDI.sendNoteOff(note, 100, channel);
    digitalWrite(LED_BUILTIN, LOW);   // change state of the LED by setting the pin to the LOW voltage level
    delay(200);
  }
  delay(2000);
}