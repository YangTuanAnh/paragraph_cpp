# Source - https://stackoverflow.com/a/41642102
# Posted by fedepad, modified by community. See post 'Timeline' for change history
# Retrieved 2026-07-19, License - CC BY-SA 4.0

find_package (SQLite3)
if (SQLITE3_FOUND)
  include_directories(${SQLITE3_INCLUDE_DIRS})
  target_link_libraries (${OUT_TARGET} SQLite::SQLite3)
endif (SQLITE3_FOUND)
