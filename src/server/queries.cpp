#include "server/queries.h"

using namespace server::queries;

bool by_id::operator()(const shared::person &p) const {
  return p.id == id;
}

bool by_name::operator()(const shared::person &p) const {
  return std::string(p.name) == name;
}

