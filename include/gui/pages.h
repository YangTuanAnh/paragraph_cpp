#ifndef PAGES_H_
#define PAGES_H_

#include "core/backend.h"

class IUIPages {
  public:
    static Backend *backend;

    static void draw_page_workspace();
    static void draw_page_tasks();
    static void draw_page_areas();
    static void draw_page_projects();
    static void draw_page_resources();
    static void draw_page_graph();
    static void draw_page_archived();
    static void draw_page_settings();

    static void draw_panel_details();
    static void draw_details_task(bool &dirty);
    static void draw_details_area(bool &dirty);
    static void draw_details_project(bool &dirty);
    static void draw_details_resource(bool &dirty);
};

#endif