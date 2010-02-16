#include "sqlite3.h"
#include "stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif

int db_prepare( sqlite3*, sqlite3_stmt**, const char*, ... );
int db_step( sqlite3_stmt* );
int db_finalize( sqlite3_stmt* );

int db_exec( sqlite3*, const char*, ... );

#ifdef __cplusplus
}
#endif
