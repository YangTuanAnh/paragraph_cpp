#include "core/backend.h"
#include <iostream>
#include "sqlite3.h"
#include <string>
#include <cassert>
#include <vector>

int main()
{
    // g++ para_test.cpp para.cpp -lsqlite3 -o para_test; ./para_test

    Backend backend("data/test.db");
    
    // Check for tables Tasks, Projects, Areas, Resources, Archived after init
    assert(backend.table_exists("tasks"));
    assert(backend.table_exists("projects"));
    assert(backend.table_exists("areas"));
    assert(backend.table_exists("resources"));

    std::cout << "Database initialization test passed." << std::endl;
    
    // Create area "School", check if exists

    // Create project "OOP", check if exists

    // Assign area to project, date, receive updated project

    // Create task "build MVP", check if exists

    // Assign task to project, done, inbox, due date, energy, urgency, receive updated project

    // Create resource "Textbook", check if exists

    // Assign area, project to resource, type, path, url, receive updated project

    // Assign project as archived, receive updated project

    // Unassign project, see updated archived and project csv

    // Assign area as archived, read archived and area to receive updated area

    // Unassign area, see updated archived and area csv

    // Assign resource as archived, save to csv, read resource and resource csvs to receive updated resource

    // Unassign resource, save to csv, read csv to see updated resource and resource csv

    // Write tasks spanning 2 weeks, get tasks that are within the next week

    // Write new area, and project, archive the area, Get all unarchived areas with unarchived projects

    // Get all resources from unarchived area and projects

    // Get tasks with inbox

    // Get all done tasks

    // Write a markdown note, assign to project, check updated for path

    // Delete markdown note, check updated for path
    return 0;
}