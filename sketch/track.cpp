#include "track.h"
#include "loop.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

Track::Track(MIDI &midi) : m_midi(midi), m_midiChannel(0),
  m_bIsMuted(false), m_activeLoopNum(0), m_previousMidiNote(0), m_nextLoopNum(0) {
  m_pLoops = new std::vector<Loop>;
}

Track::~Track() {
  delete m_pLoops;
}

void Track::setMIDIChannel(unsigned int midiChannel) {
  m_midiChannel = midiChannel;
}

bool Track::isMuted() {
  return m_bIsMuted;
}

void Track::mute() {
  m_bIsMuted = true;
}

void Track::unmute() {
  m_bIsMuted = false;
}

unsigned char Track::getNumLoops() {
  return m_pLoops->size();
}

void Track::addLoop(const char *groupName, const char *name, const char *notes) {
  Loop loop;

  loop.setGroupName(groupName);
  loop.setName(name);
  loop.addNotesFromString(notes);

  m_pLoops->push_back(loop);
}

void Track::playNextSixteenth() {
  if (m_pLoops->empty()) {
    return;
  }

  if (m_previousMidiNote != 0) {
    m_midi.sendNoteOff(m_previousMidiNote, 100, m_midiChannel);
  }

  char nextMidiNote = m_pLoops[m_activeLoopNum].getNextSixteenth();
  m_previousMidiNote = nextMidiNote;

  if (!m_bIsMuted) {
    if (nextMidiNote != 0) {
      MIDI.sendNoteOn(nextMidiNote, 100, m_midiChannel);
    }
  }

  if (m_nextLoopNum != m_activeLoopNum) {
    if (m_pLoops[m_activeLoopNum].isAtBeginningOfLoop()) {
      m_activeLoopNum = m_nextLoopNum;
    }
  }
}

void Track::queuePrevLoop() {
  if (m_pLoops->size() <= 1) {
    return;
  }

  m_nextLoopNum = m_activeLoopNum;
  if (m_nextLoopNum == 0) {
    m_nextLoopNum = m_pLoops->size() - 1;
  } else {
    m_nextLoopNum--;
  }
}

void Track::queueNextLoop() {
  if (m_pLoops->size() <= 1) {
    return;
  }

  m_nextLoopNum = m_activeLoopNum;
  m_nextLoopNum++;
  if (m_nextLoopNum > m_pLoops->size() - 1) {
    m_nextLoopNum = 0;
  }
}