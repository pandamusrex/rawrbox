#include "shareablemidi.h"

ShareableMIDI::ShareableMIDI() : midiTransport(Serial1), midiInterface((MidiTransport&)midiTransport) {
}

ShareableMIDI::~ShareableMIDI() {
}

void ShareableMIDI::start_midi() {
  midiInterface.begin();
}

void ShareableMIDI::sendNoteOn(byte note, byte velocity, byte channel) {
  midiInterface.sendNoteOn(note, velocity, channel);
}

void ShareableMIDI::sendNoteOff(byte note, byte velocity, byte channel) {
  midiInterface.sendNoteOff(note, velocity, channel);  
}