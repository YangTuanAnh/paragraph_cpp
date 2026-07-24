#ifndef NOTE_H_
#define NOTE_H_

#include <string>

struct Note {
    std::string id;
    std::string file_path;

    bool updated = false;
};

#endif