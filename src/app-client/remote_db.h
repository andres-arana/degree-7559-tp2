#ifndef __CLIENT__REMOTE_DB_H_INCLUDED__
#define __CLIENT__REMOTE_DB_H_INCLUDED__

#include "app-client/context.h"
#include "shared/data.h"
#include <string>

namespace client {
  class remote_db {
    public:
      remote_db(context &c);

      shared::person upsert(const shared::person &p);

      shared::people query_all();

      shared::person query_by_id(const unsigned int person_id);

      shared::people query_by_name(const std::string &name);

    private:
      context &c;
  };
}

#endif
