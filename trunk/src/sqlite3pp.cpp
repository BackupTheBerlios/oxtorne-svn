#include "sqlite3pp.h"

isd::db::DatabaseHandle::DatabaseHandle(const wchar_t* dbname)
{
   // Lade die Datenbank
   sqlite3_open16(dbname, &m_db);
}

isd::db::DatabaseHandle::~DatabaseHandle()
{
   // Schliesse die Datenbank
   sqlite3_close(m_db);
}
