#ifndef BACKEND_H_
#define BACKEND_H_

#include "area.h"
#include "graph.h"
#include "note.h"
#include "project.h"
#include "resource.h"
#include "task.h"
#include "utils.h"
#include <filesystem>
#include "sqlite3.h"
#include <unordered_map>

enum class SelectionType { None, Area, Project, Task, Resource };

struct Selection {
    SelectionType type = SelectionType::None;
    std::string id;
};

class Backend {
    sqlite3 *db;
    // std::system::path vault_folder = std::system::current_path();

    std::vector<Task> curr_tasks;
    std::vector<Project> curr_projects;
    std::vector<Resource> curr_resources;
    std::vector<Area> curr_areas;
    std::vector<Note> curr_notes;

    std::unordered_map<std::string, Area *> area_map;
    std::unordered_map<std::string, Project *> project_map;
    std::unordered_map<std::string, Task *> task_map;
    std::unordered_map<std::string, Resource *> resource_map;

    bool queried_areas = 0;
    bool queried_projects = 0;
    bool queried_tasks = 0;
    bool queried_resources = 0;

    Selection selection;

    Graph graph;
    bool queried_graph = 0;

    int theme_index = 0;

  public:
    Backend(const std::string& db_name = "data/main.db") { init_db(db_name); }
    ~Backend() { sqlite3_close(db); };

    void init_db(const std::string& db_name);
    bool table_exists(const std::string &table);

    void read_stmt_area(Area &area, sqlite3_stmt *stmt);
    void read_stmt_project(Project &project, sqlite3_stmt *stmt);
    void read_stmt_task(Task &task, sqlite3_stmt *stmt);
    void read_stmt_resource(Resource &resource, sqlite3_stmt *stmt);

    bool update_areas();
    bool update_projects();
    bool update_tasks();
    bool update_resources();

    Area *find_area(std::string id);
    Project *find_project(std::string id);
    Task *find_task(std::string id);
    Resource *find_resource(std::string id);

    bool add_area();
    bool add_project();
    bool add_task();
    bool add_resource();

    bool delete_areas();
    bool delete_projects();
    bool delete_tasks();
    bool delete_resources();

    void rebuild_area_map();
    void rebuild_project_map();
    void rebuild_task_map();
    void rebuild_resource_map();

    std::vector<Task> &get_tasks(int archived = -1);
    std::vector<Project> &get_projects(int archived = -1);
    std::vector<Resource> &get_resources(int archived = -1);
    std::vector<Area> &get_areas(int archived = -1);
    std::vector<Note> &get_notes() { return curr_notes; }

    Graph &get_graph();
    void layout_graph();
    void invalidate_graph() { queried_graph = false; }

    void open_resource(const std::string &id);
    void open_area(const std::string &id);
    void open_project(const std::string &id);
    void open_task(const std::string &id);

    int& get_theme_index() { return theme_index; }

    const Selection &get_selection() const;
};

#endif