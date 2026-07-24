#include "core/backend.h"
#include <algorithm>
#include <iostream>
#include <sqlite3.h>
#include <string>

void Backend::read_stmt_project(Project &project, sqlite3_stmt *stmt) {
    project.id = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));

    project.text = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));

    project.area_id =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));

    project.done = sqlite3_column_int(stmt, 4);
    project.archived = sqlite3_column_int(stmt, 5);
    project.start_at = sqlite3_column_int64(stmt, 8);
    project.due_at = sqlite3_column_int64(stmt, 9);
}

bool Backend::update_projects() {
    const char *sql = "UPDATE PROJECTS "
                      "SET text=?, "
                      "area_id=?, "
                      "done=?, "
                      "archived=?, "
                      "start_at=?, "
                      "due_at=?, "
                      "updated_at=CURRENT_TIMESTAMP "
                      "WHERE id=?;";

    sqlite3_stmt *stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << sqlite3_errmsg(db) << '\n';
        return false;
    }

    for (auto &p : curr_projects) {
        if (!p.updated)
            continue;

        sqlite3_reset(stmt);
        sqlite3_clear_bindings(stmt);

        sqlite3_bind_text(stmt, 1, p.text.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, p.area_id.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 3, p.done);
        sqlite3_bind_int(stmt, 4, p.archived);
        sqlite3_bind_int64(stmt, 5, p.start_at);
        sqlite3_bind_int64(stmt, 6, p.due_at);
        sqlite3_bind_text(stmt, 7, p.id.c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << sqlite3_errmsg(db) << '\n';
            sqlite3_finalize(stmt);
            return false;
        }

        p.updated = false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool Backend::add_project() {
    char *error = nullptr;
    const char *sql = "INSERT INTO PROJECTS ('id') VALUES (?)";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    std::string new_id = get_uuid();
    sqlite3_bind_text(stmt, 1, new_id.c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (rc != SQLITE_DONE) {
        std::cerr << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    curr_projects.emplace_back();
    Project &project = curr_projects.back();
    project.id = new_id;

    rebuild_project_map();

    return true;
}

std::vector<Project> &Backend::get_projects(int archived) {
    if (queried_projects)
        return curr_projects;

    curr_projects.clear();
    sqlite3_stmt *stmt;
    std::string sql = "SELECT * FROM PROJECTS";
    if (archived != -1)
        sql += " WHERE ARCHIVED = " + std::to_string(archived);
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    ;
    if (rc != SQLITE_OK) {
        std::cerr << "Error fetching projects: " << sqlite3_errmsg(db)
                  << std::endl;
        sqlite3_close(db);
        sqlite3_finalize(stmt);
        return curr_projects;
    }

    while (!queried_projects) {
        switch (sqlite3_step(stmt)) {
        case SQLITE_ROW:
            curr_projects.emplace_back();
            read_stmt_project(curr_projects.back(), stmt);
            break;
        case SQLITE_DONE:
            queried_projects = true;
            break;
        default:
            fprintf(stderr, "Failed.\n");
            break;
        }
    }

    sqlite3_finalize(stmt);

    rebuild_project_map();

    return curr_projects;
}

Project *Backend::find_project(std::string id) {
    auto it = project_map.find(id);
    return (it != project_map.end()) ? it->second : nullptr;
};

bool Backend::delete_projects() {
    std::vector<std::string> deleted_ids;

    for (const auto &a : curr_projects)
        if (a.deleted)
            deleted_ids.push_back(a.id);

    if (!deleted_ids.empty()) {
        std::string sql = "DELETE FROM PROJECTS WHERE id IN (";

        for (int i = 0; i < deleted_ids.size(); ++i)
            sql += (i == 0 ? "?" : ",?");

        sql += ");";

        sqlite3_stmt *stmt = nullptr;

        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) !=
            SQLITE_OK) {
            std::cerr << sqlite3_errmsg(db) << '\n';
            return false;
        }

        for (int i = 0; i < deleted_ids.size(); ++i)
            sqlite3_bind_text(stmt, static_cast<int>(i + 1),
                              deleted_ids[i].c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << sqlite3_errmsg(db) << '\n';
            sqlite3_finalize(stmt);
            return false;
        }

        sqlite3_finalize(stmt);
    }

    curr_projects.erase(
        std::remove_if(curr_projects.begin(), curr_projects.end(),
                       [](const Project &a) { return a.deleted; }),
        curr_projects.end());

    rebuild_project_map();

    return true;
}

void Backend::rebuild_project_map() {
    project_map.clear();
    for (auto &project : curr_projects)
        project_map[project.id] = &project;
}