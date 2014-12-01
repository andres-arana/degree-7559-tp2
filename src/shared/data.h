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
}

#endif

