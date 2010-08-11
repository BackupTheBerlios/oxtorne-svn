#include "sqlite3/sqlite3.h"
#include "stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif

int opt_prepare( sqlite3*, sqlite3_stmt**, const char*, ... );

#ifdef __cplusplus
}
#endif
