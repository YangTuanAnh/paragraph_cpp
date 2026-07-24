#ifndef TASK_H_
#define TASK_H_

#include <ctime>
#include <string>

enum class Urgency { none = 0, low = 1, medium = 2, high = 3 };
enum class Energy {
    none = 0,
    trivial = 1,
    easy = 2,
    medium = 3,
    hard = 4,
    challenging = 5,
    breakdown = 6,
    appointment = 7
};

struct Task {
    std::string id;
    std::string text;

    std::string project_id;
    bool done = false;
    bool inbox = false;
    bool archived = false;
    bool updated = false;
    bool deleted = false;

    Urgency urgency = Urgency::none;
    Energy energy = Energy::none;

    std::time_t start_at = 0;
    std::time_t due_at = 0;
};

#endif