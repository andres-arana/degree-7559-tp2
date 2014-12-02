#ifndef __SHARED__DATA_H_INCLUDED__
#define __SHARED__DATA_H_INCLUDED__

#include <vector>
#include <iostream>
#include <utility>

namespace shared {
  struct person {
    unsigned int id;

    static constexpr unsigned int name_length = 61;
    char name[name_length];

    static constexpr unsigned int address_length = 120;
    char address[address_length];

    static constexpr unsigned int phone_length = 13;
    char phone[phone_length];

    void serialize_to(std::ostream &os) const;

    static std::pair<bool, person> deserialize_from(std::istream &is);
  };

  typedef std::vector<person> people;

  struct stats {
    unsigned int record_count;
  };

  namespace msgs {

    constexpr long server_type = 1;
    struct server {
      long type;
      long subtype;

      static constexpr long new_client_subtype = 1;
      static server new_client();
    };

    constexpr long broadcast_type = 2;
    struct broadcast {
      long type;
      long id;

      static broadcast client_id(long id);
    };

    constexpr long client_type_offset = 100;
    struct client {
      long type;
      long subtype;

      union {
        person record;
      } data;

      static constexpr long record_subtype = 1;
      static client record(long client_id, person &p);

      static constexpr long end_of_records_subtype = 2;
      static client end_of_records(long client_id);
    };

  }
}

#endif

