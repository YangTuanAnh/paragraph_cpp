#include "core/backend.h"
#include <algorithm>
#include <iostream>
#include "sqlite3.h"
#include <string>

void Backend::read_stmt_area(Area &area, sqlite3_stmt *stmt) {
    area.id = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));

    area.text = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));

    area.category =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));

    area.done = sqlite3_column_int(stmt, 4);
    area.archived = sqlite3_column_int(stmt, 5);
    area.start_at = sqlite3_column_int64(stmt, 8);
    area.due_at = sqlite3_column_int64(stmt, 9);
}

bool Backend::update_areas() {
    const char *sql = "UPDATE AREAS "
                      "SET text=?, "
                      "category=?, "
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

    for (auto &a : curr_areas) {
        if (!a.updated)
            continue;

        sqlite3_reset(stmt);
        sqlite3_clear_bindings(stmt);

        sqlite3_bind_text(stmt, 1, a.text.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, a.category.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 3, a.done);
        sqlite3_bind_int(stmt, 4, a.archived);
        sqlite3_bind_int64(stmt, 5, a.start_at);
        sqlite3_bind_int64(stmt, 6, a.due_at);
        sqlite3_bind_text(stmt, 7, a.id.c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << sqlite3_errmsg(db) << '\n';
            sqlite3_finalize(stmt);
            return false;
        }

        a.updated = false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool Backend::add_area() {
    char *error = nullptr;
    const char *sql = "INSERT INTO AREAS ('id') VALUES (?)";
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

    curr_areas.emplace_back();
    Area &area = curr_areas.back();
    area.id = new_id;

    rebuild_area_map();

    return true;
}

std::vector<Area> &Backend::get_areas(int archived) {
    if (queried_areas)
        return curr_areas;

    area_map.clear();
    curr_areas.clear();
    sqlite3_stmt *stmt;
    std::string sql = "SELECT * FROM AREAS";
    if (archived != -1)
        sql += " WHERE ARCHIVED = " + std::to_string(archived);
    int rc = sqlite3_prepare(db, sql.c_str(), sizeof(sql), &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Error fetching areas: " << sqlite3_errmsg(db)
                  << std::endl;
        sqlite3_close(db);
        sqlite3_finalize(stmt);
        return curr_areas;
    }

    while (!queried_areas) {
        switch (sqlite3_step(stmt)) {
        case SQLITE_ROW:
            curr_areas.emplace_back();
            read_stmt_area(curr_areas.back(), stmt);
            break;
        case SQLITE_DONE:
            queried_areas = true;
            break;
        default:
            fprintf(stderr, "Failed.\n");
            break;
        }
    }

    sqlite3_finalize(stmt);

    rebuild_area_map();

    return curr_areas;
}

Area *Backend::find_area(std::string id) {
    auto it = area_map.find(id);
    return (it != area_map.end()) ? it->second : nullptr;
};

bool Backend::delete_areas() {
    std::vector<std::string> deleted_ids;

    for (const auto &a : curr_areas)
        if (a.deleted)
            deleted_ids.push_back(a.id);

    if (!deleted_ids.empty()) {
        std::string sql = "DELETE FROM AREAS WHERE id IN (";

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

    curr_areas.erase(std::remove_if(curr_areas.begin(), curr_areas.end(),
                                    [](const Area &a) { return a.deleted; }),
                     curr_areas.end());

    rebuild_area_map();

    return true;
}

void Backend::rebuild_area_map() {
    area_map.clear();
    for (auto &area : curr_areas)
        area_map[area.id] = &area;
}