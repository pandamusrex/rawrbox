#ifndef SEQUENCER_H
#define SEQUENCER_H

#include <MIDI.h>
#include "track.h"

class Sequencer{
  public:
    Sequencer(MIDI &midi);
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
    MIDI &m_midi;
    Track *m_pTracks;
    // int getMIDINote(const char *note);
    // unsigned int m_playbackHead;
    // std::vector<char> *m_pNotes;
};

#endif