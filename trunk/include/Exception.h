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


namespace ISD{
namespace Db{


// ============================================================================
/// Ausnahmetyp, der bei Misserfolg einer Datenbankoperation standardmaessig
/// geworfen wird.
//
class Exception
{
 public:
   Exception(const wchar_t*);
  ~Exception();

 public:
   virtual const std::wstring& what() const;

 protected:
   std::wstring m_msg;
};


}};
