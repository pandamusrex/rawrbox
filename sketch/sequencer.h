#ifndef SEQUENCER_H
#define SEQUENCER_H

#include "track.h"
#include "shareablemidi.h"

class Sequencer{
  public:
    Sequencer();
    ~Sequencer();

    unsigned char getNumTracks();

    void setMIDIChannelForTrack(unsigned char trackNum, unsigned char midiChannel);

    bool isTrackMuted(unsigned char trackNum);
    void muteTrack(unsigned char trackNum);
    void unmuteTrack(unsigned char trackNum);
    void toggleMuteForTrack(unsigned char trackNum);

    unsigned char getNumLoopsForTrack(unsigned char trackNum);

    void addLoopToTrack(unsigned char trackNum,
        const char *groupName,
        const char *name,
        const char *notes);

    void queuePrevLoopForTrack(unsigned char trackNum);
    void queueNextLoopForTrack(unsigned char trackNum);

    //void getCurrentTrackLoop(unsigned char trackNum,
    //  unsigned char loopNum,
    //  unsigned char *loopLength,
    //  unsigned char *loopAt
    //);
    
    //unsigned char getTrackLoopDetails(unsigned char trackNum,
    //    unsigned char loopNum,
    //    char *loopGroupName,
    //    char *loopName
    //);

    //void setNextTrackLoop(unsigned char trackNum,
    //    unsigned char loopNum);

    void playNextSixteenth();

  private:
    ShareableMIDI *m_pMIDI;
    Track *m_pTracks;
};

#endif