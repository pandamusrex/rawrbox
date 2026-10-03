#ifndef LOOP_H
#define LOOP_H

#include <iostream>
#include <vector>

#define MAX_LOOP_GROUP_NAME 32
#define MAX_LOOP_NAME 32
#define MAX_LOOP_NOTES_STRING 512

class Loop {
  public:
    Loop();
    ~Loop();

    void setGroupName(const char *groupName);
    void setName(const char *name);
    void addNotesFromString(const char *notes);

    char getNextSixteenth();

    bool isAtBeginningOfLoop();

  private:
    char m_groupName[MAX_LOOP_GROUP_NAME];
    char m_name[MAX_LOOP_NAME];

    unsigned int m_playbackHead;

    std::vector<char> *m_pMIDINotes;
};

#endif