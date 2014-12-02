#ifndef __CLIENT__REMOTE_DB_H_INCLUDED__
#define __CLIENT__REMOTE_DB_H_INCLUDED__

#include "app-client/context.h"
#include "shared/data.h"

namespace client {
  class remote_db {
    public:
      remote_db(context &c);

      shared::person upsert(const shared::person &p);

      shared::people query_all();

    private:
      context &c;
  };
}

#endif
