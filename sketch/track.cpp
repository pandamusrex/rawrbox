#include "track.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

Track::Track() : m_playbackHead(0) {
  m_pNotes = new std::vector<char>;
}

Track::~Track() {
  delete m_pNotes;
}

void Track::addClip(const char *str) {
  char workingCopy[1024];
  strcpy(workingCopy, str);

  char *token = strtok(workingCopy, " ");
  while (token != NULL) {
    int note = this->getMIDINote(token);
    if (note == -1) {
      m_pNotes->push_back(0);
    } else {
      m_pNotes->push_back((char) note);
    }
    token = strtok(NULL, " ");
  }
}

char Track::getNote() {
  if (m_pNotes->empty()) {
    return 72; // C4
  }

  char note = m_pNotes->at(m_playbackHead);
  m_playbackHead++;
  if (m_playbackHead > m_pNotes->size() - 1) {
    m_playbackHead = 0;
  }
  return note;
}

int Track::getMIDINote(const char *note) {
  if (!note || strlen(note) < 2 || strlen(note) > 4) {
      return -1; // Invalid length
  }

  // Map note letters to semitone offsets from C
  int semitoneMap[7] = {9, 11, 0, 2, 4, 5, 7}; // A B C D E F G

  char letter = toupper(note[0]);
  if (letter < 'A' || letter > 'G') {
      return -1; // Invalid note letter
  }

  int semitone = semitoneMap[letter - 'A'];

  int idx = 1;
  // Handle optional sharp (#) or flat (b)
  if (note[idx] == '#' || note[idx] == 'b' || note[idx] == 'B') {
      if (note[idx] == '#') semitone += 1;
      else semitone -= 1;
      idx++;
  }

  // Parse octave number
  int octave = 0;
  int sign = 1;
  if (note[idx] == '-') { // Negative octave
      sign = -1;
      idx++;
  }
  if (!isdigit(note[idx])) {
      return -1; // Missing octave digit
  }
  while (isdigit(note[idx])) {
      octave = octave * 10 + (note[idx] - '0');
      idx++;
  }
  octave *= sign;

  // MIDI note number formula: C0 = 24, so:
  int midiNumber = (octave + 2) * 12 + semitone;

  // Validate range
  if (midiNumber < 0 || midiNumber > 127) {
      return -1;
  }

  return midiNumber;
}