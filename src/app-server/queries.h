#ifndef __SERVER__QUERIES_H_INCLUDED__
#define __SERVER__QUERIES_H_INCLUDED__

#include "shared/data.h"
#include <string>

namespace server {
  namespace queries {
    struct by_id {
        const unsigned int id;
        bool operator()(const shared::person &p) const;
    };

    struct by_name {
        const std::string name;
        bool operator()(const shared::person &p) const;
    };

    struct by_phone {
      const std::string tel;
      bool operator()(const shared::person &p) const;
    };
  }
}

#endif
