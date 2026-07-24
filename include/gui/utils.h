#ifndef UTILS_H
#define UTILS_H

#include "IconsFontAwesome6.h"
#include "imgui.h"
#include "imnodes.h"

inline const char *urgency_name(Urgency urgency) {
    switch (urgency) {
    case Urgency::none:
        return "None";
    case Urgency::low:
        return "Low";
    case Urgency::medium:
        return "Medium";
    case Urgency::high:
        return "High";
    }
    return "Unknown";
}

inline const char *urgency_icon(Urgency urgency) {
    switch (urgency) {
    case Urgency::none:
        return ICON_FA_MINUS;
    case Urgency::low:
        return ICON_FA_CHEVRON_DOWN;
    case Urgency::medium:
        return ICON_FA_EQUALS;
    case Urgency::high:
        return ICON_FA_CHEVRON_UP;
    }

    return ICON_FA_QUESTION;
}

inline const char *energy_name(Energy energy) {
    switch (energy) {
    case Energy::none:
        return "None";
    case Energy::trivial:
        return "Trivial - 3m";
    case Energy::easy:
        return "Easy - 1h";
    case Energy::medium:
        return "Medium - 3h";
    case Energy::hard:
        return "Hard - 1d";
    case Energy::challenging:
        return "Challenging - 3d";
    case Energy::breakdown:
        return "Breakdown - 1w";
    case Energy::appointment:
        return "Appointment";
    }

    return "Unknown";
}

inline const char *energy_icon(Energy energy) {
    switch (energy) {
    case Energy::none:
        return ICON_FA_MINUS;
    case Energy::trivial:
        return ICON_FA_FEATHER;
    case Energy::easy:
        return ICON_FA_PERSON_WALKING;
    case Energy::medium:
        return ICON_FA_PERSON_RUNNING;
    case Energy::hard:
        return ICON_FA_DUMBBELL;
    case Energy::challenging:
        return ICON_FA_MOUNTAIN;
    case Energy::breakdown:
        return ICON_FA_LIST_CHECK;
    case Energy::appointment:
        return ICON_FA_CALENDAR_DAY;
    }

    return ICON_FA_QUESTION;
}

inline void cycle_filter(const char *label, int &value) {
    const char *state = value == -1 ? "All" : value == 0 ? "No" : "Yes";

    if (ImGui::SmallButton((std::string(label) + ": " + state).c_str()))
        value = (value + 2) % 3 - 1;
}

#endif