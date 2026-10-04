#include "loop.h"
#include "utils.h"

#include <string.h>

Loop::Loop() : m_playbackHead(0) {
  m_pMIDINotes = new std::vector<char>;
  strcpy(m_groupName, "");
  strcpy(m_name, "");
}

Loop::~Loop() {
  delete m_pMIDINotes;
}

void Loop::setGroupName(const char *groupName) {
  strncpy(m_groupName, groupName, MAX_LOOP_GROUP_NAME - 1);
}

void Loop::setName(const char *name) {
  strncpy(m_name, name, MAX_LOOP_NAME - 1);
}

void Loop::addNotesFromString(const char *notes) {
  char workingCopy[MAX_LOOP_NOTES_STRING + 1];
  strncpy(workingCopy, notes, MAX_LOOP_NOTES_STRING);

  char *token = strtok(workingCopy, " ");
  while (token != NULL) {
    unsigned char note = getMIDINote(token);
    if (note > 127) {
      m_pMIDINotes->push_back(0); // TODO Handle legato @ and rest ~ differently
    } else {
      m_pMIDINotes->push_back((char) note);
    }
    token = strtok(NULL, " ");
  }
}

char Loop::getNextSixteenth() {
  if (m_pMIDINotes->empty()) {
    return 0;
  }

  char midiNote = m_pMIDINotes->at(m_playbackHead);
  m_playbackHead++;
  if (m_playbackHead >= m_pMIDINotes->size()) {
    m_playbackHead = 0;
  }
  return midiNote;
}

bool Loop::isAtBeginningOfLoop() {
    return (m_playbackHead == 0);
}