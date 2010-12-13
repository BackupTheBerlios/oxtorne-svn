#include <string>
#include <memory>
#include <exception>

#include <sqlite3/sqlite3.h>


namespace isd{
namespace db{

class DatabaseHandle
{
 friend class Database;

 protected:
   DatabaseHandle(const wchar_t*);
  ~DatabaseHandle();

 protected:
   sqlite3* m_db;
};


class Database
{
 public:
   Database(const wchar_t*);
  ~Database();

 protected:
   std::tr1::shared_ptr<DatabaseHandle> m_db;
};


class Statement
{
 public:
   Statement(const Database&, const wchar_t*);
  ~Statement();
};

}};
