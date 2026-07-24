#ifndef AREA_H_
#define AREA_H_

#include <ctime>
#include <string>
#include <vector>

struct Area {
    std::string id;
    std::string text;

    std::string category;
    std::vector<std::string> resource_ids;

    bool done = false;
    bool archived = false;
    bool updated = false;
    bool deleted = false;

    std::time_t start_at = 0;
    std::time_t due_at = 0;
};

#endif