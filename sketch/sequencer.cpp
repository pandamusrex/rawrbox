#include "sequencer.h"

#define TRACK_COUNT 4

Sequencer::Sequencer() : m_pTracks(0) {
  m_pMIDI = new ShareableMIDI();
  m_pMIDI->start_midi();

  m_pTracks = new Track[TRACK_COUNT]();
  for (unsigned int i=0; i < TRACK_COUNT; i++) {
    m_pTracks[i].setTrackNum(i);
    m_pTracks[i].setMIDI(m_pMIDI);
  }
}

Sequencer::~Sequencer() {
  for (int i=0; i < TRACK_COUNT; i++) {
    m_pTracks[i].setMIDI(0);
  }
  delete[] m_pTracks;
  delete m_pMIDI;
}

unsigned char Sequencer::getNumTracks() {
    return TRACK_COUNT;
}

void Sequencer::setMIDIChannelForTrack(unsigned char trackNum, unsigned char midiChannel) {
  if (trackNum >= TRACK_COUNT) {
    return;
  }

  m_pTracks[trackNum].setMIDIChannel(midiChannel);
}

bool Sequencer::isTrackMuted(unsigned char trackNum) {
  if (trackNum >= TRACK_COUNT) {
    return false;
  }

  return m_pTracks[trackNum].isMuted();
}

void Sequencer::muteTrack(unsigned char trackNum) {
  if (trackNum >= TRACK_COUNT) {
    return;
  }

  m_pTracks[trackNum].mute();
}

void Sequencer::unmuteTrack(unsigned char trackNum) {
  if (trackNum >= TRACK_COUNT) {
    return;
  }

  m_pTracks[trackNum].unmute();
}

void Sequencer::toggleMuteForTrack(unsigned char trackNum) {
  if (trackNum >= TRACK_COUNT) {
    return;
  }

  if (m_pTracks[trackNum].isMuted()) {
    m_pTracks[trackNum].unmute();
  } else {
    m_pTracks[trackNum].mute();
  }
}

unsigned char Sequencer::getNumLoopsForTrack(unsigned char trackNum) {
  if (trackNum >= TRACK_COUNT) {
    return 0;
  }

  return m_pTracks[trackNum].getNumLoops();
}

void Sequencer::addLoopToTrack(unsigned char trackNum,
  const char *groupName,
  const char *name,
  const char *notes) {

  if (trackNum >= TRACK_COUNT) {
    return;
  }

  m_pTracks[trackNum].addLoop(groupName, name, notes);
}

void Sequencer::getLoopTitleForTrack(unsigned char trackNum, char *name, size_t max) {
  if (trackNum >= TRACK_COUNT) {
    return;
  }

  m_pTracks[trackNum].getActiveLoopTitle(name, max);
}

void Sequencer::playNextSixteenth() {
  for (unsigned char i = 0; i < TRACK_COUNT; i++) {
    m_pTracks[i].playNextSixteenth();
  }
}

void Sequencer::queuePrevLoopForTrack(unsigned char trackNum) {
  if (trackNum >= TRACK_COUNT) {
    return;
  }

  m_pTracks[trackNum].queuePrevLoop();
}

void Sequencer::queueNextLoopForTrack(unsigned char trackNum) {
  if (trackNum >= TRACK_COUNT) {
    return;
  }

  m_pTracks[trackNum].queueNextLoop();
}

bool Sequencer::hasQueuedLoop(unsigned char trackNum) {
  if (trackNum >= TRACK_COUNT) {
    return;
  }

  return m_pTracks[trackNum].hasQueuedLoop();
}