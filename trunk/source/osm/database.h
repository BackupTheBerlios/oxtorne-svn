#include "sqlite3.h"
#include "stdlib.h"

int db_exec( sqlite3* db, const char* query, ... );
