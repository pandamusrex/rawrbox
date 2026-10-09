#include "loop.h"
#include "utils.h"

#include <string.h>

#include "Arduino.h"

Loop::Loop() {
  m_playbackHead = 0;
  m_loopLength = 0;
  strcpy(m_groupName, "");
  strcpy(m_name, "");
}

Loop::~Loop() {
}

void Loop::setGroupName(const char *groupName) {
  strncpy(m_groupName, groupName, MAX_LOOP_GROUP_NAME - 1);
}

void Loop::setName(const char *name) {
  strncpy(m_name, name, MAX_LOOP_NAME - 1);
}

void Loop::getName(char *name, size_t max) {
  strncpy(name, m_name, max - 1);
}

void Loop::addNotesFromString(const char *notes) {
  char workingCopy[MAX_LOOP_NOTES_STRING + 1];
  strncpy(workingCopy, notes, MAX_LOOP_NOTES_STRING);

  char *token = strtok(workingCopy, " ");
  while (token != NULL) {
    unsigned char note = getMIDINote(token);
    if (note > 127) {
      m_notes[m_loopLength] = 0; // TODO Handle legato @ and rest ~ differently
    } else {
      m_notes[m_loopLength] = note;
    }
    m_loopLength++;
    token = strtok(NULL, " ");
  }
}

unsigned char Loop::getNextSixteenth() {
  if (m_loopLength == 0) {
    return 0;
  }

  unsigned char midiNote = m_notes[m_playbackHead];
  m_playbackHead++;
  if (m_playbackHead >= m_loopLength) {
    m_playbackHead = 0;
  }
  return midiNote;
}

bool Loop::isAtBeginningOfLoop() {
    return (m_playbackHead == 0);
}

void Loop::dump() {
  Serial.println("Loop contains:");
  for (unsigned int i=0; i < m_loopLength; i++) {
    Serial.print(m_notes[i], DEC);
    Serial.print(" ");
  }
  Serial.println();
}