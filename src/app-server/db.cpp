#include "app-server/db.h"
#include "app-server/queries.h"
#include <algorithm>
#include <iterator>
#include <fstream>

using namespace std;
using namespace server;

namespace {
  unsigned int generate_id(const shared::people &data) {
    unsigned int maximum = 0;
    for (shared::people::const_iterator it = data.begin(); it != data.end(); it++) {
      if (it->id > maximum) {
        maximum = it->id;
      }
    }

    return maximum + 1;
  }
};

db::db() {
  ifstream file("people.db", ifstream::binary);

  if (file) {
    auto p = shared::person::deserialize_from(file);
    while (p.first) {
      data.push_back(p.second);
      p = shared::person::deserialize_from(file);
    }
  }
}

const shared::people db::all() const {
  return data;
}

const shared::stats db::stats() const {
  shared::stats result;
  result.record_count = data.size();

  return result;
}

void db::upsert(const shared::person &person) {
  auto record = find_if(
      data.begin(),
      data.end(),
      queries::by_id { person.id });

  if (record != data.end()) {
    *record = person;
  } else {
    shared::person record = person;
    record.id = generate_id(data);
    data.push_back(record);
  }
}

db::~db() {
  ofstream file("people.db", ofstream::trunc | ofstream::binary);
  for (shared::people::const_iterator it = data.begin(); it != data.end(); it++) {
    it->serialize_to(file);
  }
}
