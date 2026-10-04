#ifndef SHAREABLEMIDI_H
#define SHAREABLEMIDI_H

#include <MIDI.h>

class ShareableMIDI {
  public:
    ShareableMIDI();
    ~ShareableMIDI();

    void start_midi();

    void sendNoteOn(byte note, byte velocity, byte channel);
    void sendNoteOff(byte note, byte velocity, byte channel);

  private:
    using MidiTransport = MIDI_NAMESPACE::SerialMIDI<HardwareSerial>;
    using MidiInterface = MIDI_NAMESPACE::MidiInterface<MidiTransport>;

    MidiTransport midiTransport;
    MidiInterface midiInterface;
};

#endif
