#include "core/backend.h"
#include <algorithm>
#include <iostream>
#include <sqlite3.h>
#include <string>

void Backend::read_stmt_task(Task &task, sqlite3_stmt *stmt) {
    task.id = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));

    task.text = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));

    task.project_id =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));

    task.done = sqlite3_column_int(stmt, 4);
    task.inbox = sqlite3_column_int(stmt, 5);
    task.archived = sqlite3_column_int(stmt, 6);

    task.urgency = static_cast<Urgency>(sqlite3_column_int(stmt, 7));
    task.energy = static_cast<Energy>(sqlite3_column_int(stmt, 8));

    task.start_at = sqlite3_column_int64(stmt, 11);
    task.due_at = sqlite3_column_int64(stmt, 12);
}

bool Backend::update_tasks() {
    const char *sql = "UPDATE TASKS "
                      "SET text=?, "
                      "project_id=?, "
                      "done=?, "
                      "inbox=?, "
                      "archived=?, "
                      "urgency=?, "
                      "energy=?, "
                      "start_at=?, "
                      "due_at=?, "
                      "updated_at=CURRENT_TIMESTAMP "
                      "WHERE id=?;";

    sqlite3_stmt *stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << sqlite3_errmsg(db) << '\n';
        return false;
    }

    for (auto &t : curr_tasks) {
        if (!t.updated)
            continue;

        sqlite3_reset(stmt);
        sqlite3_clear_bindings(stmt);

        sqlite3_bind_text(stmt, 1, t.text.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, t.project_id.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 3, t.done);
        sqlite3_bind_int(stmt, 4, t.inbox);
        sqlite3_bind_int(stmt, 5, t.archived);
        sqlite3_bind_int(stmt, 6, (int)t.urgency);
        sqlite3_bind_int(stmt, 7, (int)t.energy);
        sqlite3_bind_int64(stmt, 8, t.start_at);
        sqlite3_bind_int64(stmt, 9, t.due_at);
        sqlite3_bind_text(stmt, 10, t.id.c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << sqlite3_errmsg(db) << '\n';
            sqlite3_finalize(stmt);
            return false;
        }

        t.updated = false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool Backend::add_task() {
    const char *sql = "INSERT INTO TASKS(id) VALUES(?);";

    sqlite3_stmt *stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << sqlite3_errmsg(db) << '\n';
        return false;
    }

    std::string id = get_uuid();

    sqlite3_bind_text(stmt, 1, id.c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    if (rc != SQLITE_DONE) {
        std::cerr << sqlite3_errmsg(db) << '\n';
        return false;
    }

    curr_tasks.emplace_back();
    Task &task = curr_tasks.back();
    task.id = id;

    rebuild_task_map();

    return true;
}

std::vector<Task> &Backend::get_tasks(int archived) {
    if (queried_tasks)
        return curr_tasks;

    curr_tasks.clear();

    std::string sql = "SELECT * FROM TASKS";

    // if (archived != -1)
    //     sql += " WHERE archived=" + std::to_string(archived);

    sqlite3_stmt *stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << sqlite3_errmsg(db) << '\n';
        return curr_tasks;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        curr_tasks.emplace_back();
        read_stmt_task(curr_tasks.back(), stmt);
    }

    queried_tasks = true;

    sqlite3_finalize(stmt);

    rebuild_task_map();

    return curr_tasks;
}

Task *Backend::find_task(std::string id) {
    auto it = task_map.find(id);
    return (it != task_map.end()) ? it->second : nullptr;
};

bool Backend::delete_tasks() {
    std::vector<std::string> deleted_ids;

    for (const auto &a : curr_tasks)
        if (a.deleted)
            deleted_ids.push_back(a.id);

    if (!deleted_ids.empty()) {
        std::string sql = "DELETE FROM TASKS WHERE id IN (";

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

    curr_tasks.erase(std::remove_if(curr_tasks.begin(), curr_tasks.end(),
                                    [](const Task &a) { return a.deleted; }),
                     curr_tasks.end());

    rebuild_task_map();

    return true;
}

void Backend::rebuild_task_map() {
    task_map.clear();
    for (auto &task : curr_tasks)
        task_map[task.id] = &task;
}