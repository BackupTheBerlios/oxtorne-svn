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


// ============================================================================
/// Forward Declaration des sqlite3_stmt structs.
//
typedef struct sqlite3_stmt sqlite3_stmt;


namespace ISD{
namespace Db{


// ============================================================================
/// Statementklasse fuer die Kapselung eines Prepared Statements.
//
class Statement
{
 protected:
   // =========================================================================
   /// Hilfsklasse verpackt sqlite3_stmt, damit diese wiederum in einem
   /// shared_ptr verpackt werden kann und das Statement im Falle der Loeschung
   /// finalisiert wird.
   //
   class Handle
   {
    public:
      Handle(const wchar_t*) throw();
     ~Handle();
      sqlite3_stmt* m_db;
   };

 public:
   Statement(const wchar_t*) throw();
   virtual ~Statement();

 protected:
   std::tr1::shared_ptr<Handle> m_stmt;
};


}};
