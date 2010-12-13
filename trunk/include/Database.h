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
#include <string>
#include <memory>

#include "Exception.h"


// ============================================================================
/// Forward Declaration des sqlite3 structs.
//
typedef struct sqlite3 sqlite3;


namespace ISD{
namespace Db{


// ============================================================================
/// Datenbankklasse fuer die Kapselung einer Datenbank.
//
class Database
{
 protected:
   // =========================================================================
   /// Hilfsklasse verpackt sqlite3, damit diese wiederum in einem shared_ptr
   /// verpackt werden kann und die Datenbank im Falle der Loeschung schliesst.
   //
   class Handle
   {
    public:
      Handle(const wchar_t*) throw();
     ~Handle();
      sqlite3* m_db;
   };

 public:
   Database(const wchar_t*) throw();
  ~Database();

 protected:
   std::tr1::shared_ptr<Handle> m_db;
};


}};
