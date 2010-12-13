//#############################################################################
//##                                                                         ##
//##        Product:   HiCAD / HeLIOS                                        ##
//##        Copyright: by ISD Software & Systeme GmbH                        ##
//##        Address:   Hauert 4                                              ##
//##                   44227 Dortmund                                        ##
//##                   Germany                                               ##
//##        Phone:     (+49) 231 97 93 0                                     ##
//##        E-Mail:    info@isdgroup.de                                      ##
//##                                                                         ##
//#############################################################################
#include "Database.h"

#include <sqlite3/sqlite3.h>


// ============================================================================
/// Erzeugt das Handle auf die Datenbank und initialisiert sofort das sqlite3
/// handle.
//
ISD::Db::Database::Handle::Handle(const wchar_t* dbpath)
{
   sqlite3_open16(dbpath, &m_db);
}

// ============================================================================
/// Schliesst die sqlite3 Datenbank.
//
ISD::Db::Database::Handle::~Handle()
{
   sqlite3_close(m_db);
}

// ============================================================================
/// Initialisiert die Datenbank.
//
ISD::Db::Database::Database(const wchar_t* dbpath) : m_db(new Handle(dbpath))
{
}

// ============================================================================
/// Schliesst die Datenbank.
//
ISD::Db::Database::~Database()
{
}
