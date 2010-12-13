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
/// Erzeugt das Handle auf das sqlite3_stmt Statement.
//
ISD::Db::Statement::Handle::Handle(const wchar_t* dbpath)
{
   //sqlite3_prepare16( (dbpath, &m_db);
}

// ============================================================================
/// Finalisiert das sqlite3_stmt Statement.
//
ISD::Db::Statement::Handle::~Handle()
{
   //sqlite3_close(m_db);
}

// ============================================================================
/// Initialisiert die Datenbank.
//
ISD::Db::Statement::Statement(const wchar_t* dbpath) : m_db(new Handle(dbpath))
{
}

// ============================================================================
/// Schliesst die Datenbank.
//
ISD::Db::Statement::~Statement()
{
}
