#include "core/backend.h"

#include <algorithm>
#include <iostream>
#include <sqlite3.h>

void Backend::read_stmt_resource(Resource &resource, sqlite3_stmt *stmt) {
    resource.id = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));

    resource.text =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));

    resource.area_id =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));

    resource.source =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));

    resource.archived = sqlite3_column_int(stmt, 5);

    resource.resource_type =
        static_cast<ResourceType>(sqlite3_column_int(stmt, 6));
}

bool Backend::update_resources() {
    const char *sql = "UPDATE RESOURCES "
                      "SET text=?, "
                      "source=?, "
                      "area_id=?, "
                      "archived=?, "
                      "resource_type=?, "
                      "updated_at=CURRENT_TIMESTAMP "
                      "WHERE id=?;";

    sqlite3_stmt *stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << sqlite3_errmsg(db) << '\n';
        return false;
    }

    for (auto &r : curr_resources) {
        if (!r.updated)
            continue;

        sqlite3_reset(stmt);
        sqlite3_clear_bindings(stmt);

        sqlite3_bind_text(stmt, 1, r.text.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, r.source.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, r.area_id.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 4, r.archived);
        sqlite3_bind_int(stmt, 5, static_cast<int>(r.resource_type));
        sqlite3_bind_text(stmt, 6, r.id.c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << sqlite3_errmsg(db) << '\n';
            sqlite3_finalize(stmt);
            return false;
        }

        r.updated = false;
    }

    sqlite3_finalize(stmt);

    return true;
}

bool Backend::add_resource() {
    const char *sql = "INSERT INTO RESOURCES(id) VALUES(?);";

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

    curr_resources.emplace_back();
    Resource &resource = curr_resources.back();
    resource.id = id;

    rebuild_resource_map();

    return true;
}

std::vector<Resource> &Backend::get_resources(int archived) {
    if (queried_resources)
        return curr_resources;

    resource_map.clear();
    curr_resources.clear();

    std::string sql = "SELECT * FROM RESOURCES";

    if (archived != -1)
        sql += " WHERE archived=" + std::to_string(archived);

    sqlite3_stmt *stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << sqlite3_errmsg(db) << '\n';
        return curr_resources;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        curr_resources.emplace_back();
        read_stmt_resource(curr_resources.back(), stmt);
    }

    queried_resources = true;

    sqlite3_finalize(stmt);

    rebuild_resource_map();

    return curr_resources;
}

Resource *Backend::find_resource(std::string id) {
    auto it = resource_map.find(id);
    return it == resource_map.end() ? nullptr : it->second;
}

bool Backend::delete_resources() {
    std::vector<std::string> deleted_ids;

    for (const auto &a : curr_resources)
        if (a.deleted)
            deleted_ids.push_back(a.id);

    if (!deleted_ids.empty()) {
        std::string sql = "DELETE FROM RESOURCES WHERE id IN (";

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

    curr_resources.erase(
        std::remove_if(curr_resources.begin(), curr_resources.end(),
                       [](const Resource &a) { return a.deleted; }),
        curr_resources.end());

    rebuild_resource_map();

    return true;
}

void Backend::rebuild_resource_map() {
    resource_map.clear();
    for (auto &resource : curr_resources)
        resource_map[resource.id] = &resource;
}