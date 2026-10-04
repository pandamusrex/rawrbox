#ifndef LOOP_H
#define LOOP_H

#include <iostream>
#include <vector>

#define MAX_LOOP_GROUP_NAME 32
#define MAX_LOOP_NAME 32
#define MAX_LOOP_NOTES_STRING 512
#define MAX_LOOP_NOTES 128 // 8 bars of 16th notes

class Loop {
  public:
    Loop();
    ~Loop();

    void setGroupName(const char *groupName);
    void setName(const char *name);
    void addNotesFromString(const char *notes);

    unsigned char getNextSixteenth();

    bool isAtBeginningOfLoop();

    void dump();

  private:
    char m_groupName[MAX_LOOP_GROUP_NAME];
    char m_name[MAX_LOOP_NAME];

    unsigned int m_loopLength;
    unsigned int m_playbackHead;
    unsigned char m_notes[MAX_LOOP_NOTES];
};

#endif