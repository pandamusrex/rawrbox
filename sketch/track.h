#ifndef TRACK_H
#define TRACK_H

#include <iostream>
#include <vector>

class Track{
  public:
    Track();
    ~Track();

    void addClip(const char *str);
    char getNote();

  private:
    int getMIDINote(const char *note);
    unsigned int m_playbackHead;
    std::vector<char> *m_pNotes;
};

#endif