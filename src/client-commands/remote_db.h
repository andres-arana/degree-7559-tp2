#ifndef __CLIENT__COMMANDS__REMOTE_DB_H_INCLUDED__
#define __CLIENT__COMMANDS__REMOTE_DB_H_INCLUDED__

#include "client/context.h"
#include "shared/data.h"
#include <string>

namespace client {
  namespace commands {
    class remote_db {
      public:
        remote_db(context &c);

        shared::people upsert(const shared::person &p);

        shared::people query_all();

        shared::people query_by_id(const unsigned int person_id);

        shared::people query_by_name(const std::string &name);

      private:
        context &c;
    };
  }
}

#endif
