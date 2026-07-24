#ifndef ROUTER_H_
#define ROUTER_H_

#include "core/backend.h"

enum class Page {
    Workspace,
    Graph_View,
    Tasks,
    Projects,
    Areas,
    Resources,
    Archived,
    Settings
};

class Router {
  public:
    static void draw_taskbar(Page &currentPage, Backend &backend);
    static void draw_page(Page &currentPage);
};

#endif