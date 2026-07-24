#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <string>

enum class ResourceType {
    none = 0,
    file = 1,
    folder = 2,
    url = 3,
    article = 4,
    video = 5,
    book = 6,
    document = 7,
    other = 8
};

struct Resource {
    std::string id;
    std::string text;
    std::string source;

    std::string area_id;

    bool archived = false;
    bool updated = false;
    bool deleted = false;

    ResourceType resource_type = ResourceType::none;
};

#endif