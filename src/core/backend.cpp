#include "core/backend.h"
#include <fstream>
#include <iostream>
#include <sqlite3.h>
#include <string>

std::string get_sql(const std::string file_path) {
    std::ifstream file(file_path);

    std::string line, sql;
    while (std::getline(file, line))
        sql += line + '\n';

    return sql;
}

void Backend::init_db(const std::string& db_name) {
    sqlite3 *db;
    sqlite3_open(db_name.c_str(), &db);
    this->db = db;

    char *error = nullptr;
    std::string sql = get_sql("data/migrations/001_db_init.sql");

    int rc = sqlite3_exec(this->db, sql.c_str(), 0, 0, &error);
    if (rc != SQLITE_OK) {
        std::cerr << "DB error: " << error << std::endl;
        sqlite3_free(error);
    }
}

bool Backend::table_exists(const std::string& table) {
    static constexpr const char* sql =
        "SELECT 1 "
        "FROM sqlite_master "
        "WHERE type='table' AND name=?;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_text(stmt, 1, table.c_str(), -1, SQLITE_TRANSIENT);
    bool exists = (sqlite3_step(stmt) == SQLITE_ROW);
    sqlite3_finalize(stmt);

    return exists;
}

void Backend::open_resource(const std::string &id) {
    selection.type = SelectionType::Resource;
    selection.id = id;
}

void Backend::open_area(const std::string &id) {
    selection.type = SelectionType::Area;
    selection.id = id;
}

void Backend::open_project(const std::string &id) {
    selection.type = SelectionType::Project;
    selection.id = id;
}

void Backend::open_task(const std::string &id) {
    selection.type = SelectionType::Task;
    selection.id = id;
}

const Selection &Backend::get_selection() const { return selection; }