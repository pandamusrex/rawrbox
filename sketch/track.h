#ifndef TRACK_H
#define TRACK_H

#include <iostream>
#include <vector>

#include <MIDI.h>

#include "loop.h"

class Track{
  public:
    Track(MIDI &midi);
    ~Track();

    void setMIDIChannel(unsigned int midiChannel);

    bool isMuted();
    void mute();
    void unmute();

    void addLoop(const char *groupName, const char *name, const char *notes);
    void playNextSixteenth();

    unsigned char getNumLoops();
    void queuePrevLoop();
    void queueNextLoop();

  private:
    MIDI &m_midi;
    unsigned char m_activeLoopNum;
    unsigned char m_midiChannel;
    bool m_bIsMuted;

    unsigned char m_nextLoopNum;

    unsigned char m_previousMidiNote;

    std::vector<Loop> *m_pLoops;
};

#endif