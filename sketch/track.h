#ifndef TRACK_H
#define TRACK_H

#include <iostream>
#include <vector>

#include "shareablemidi.h"

#include "loop.h"

class Track{
  public:
    Track();
    ~Track();

    void setTrackNum(unsigned int trackNum);
    void setMIDI(ShareableMIDI *midi);
    void setMIDIChannel(unsigned int midiChannel);

    bool isMuted();
    void mute();
    void unmute();

    void addLoop(const char *groupName, const char *name, const char *notes);
    void getActiveLoopTitle(char *name, size_t max);
    void playNextSixteenth();

    unsigned char getNumLoops();
    void queuePrevLoop();
    void queueNextLoop();
    bool hasQueuedLoop();

  private:
    unsigned int m_trackNum;
  
    ShareableMIDI *m_pMIDI;
    unsigned char m_activeLoopNum;
    unsigned char m_midiChannel;
    bool m_bIsMuted;

    unsigned char m_nextLoopNum;
    unsigned char m_previousMidiNote;

    std::vector<Loop> *m_pLoops;
};

#endif