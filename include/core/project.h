#ifndef PROJECT_H_
#define PROJECT_H_

#include <ctime>
#include <string>
#include <vector>

struct Project {
    std::string id;
    std::string text;

    std::string area_id;
    std::vector<std::string> resource_ids;
    std::vector<std::string> note_ids;

    bool done = false;
    bool archived = false;
    bool updated = false;
    bool deleted = false;

    std::time_t start_at = 0;
    std::time_t due_at = 0;
};

#endif