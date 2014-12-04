#include "client-commands/map.h"

using namespace std;
using namespace client;
using namespace client::commands;

void commands::map::assoc(const string &name, command *c) {
  auto pair = std::make_pair(name, unique_ptr<command>(c));
  commands.insert(std::move(pair));
}

commands::map::map_type::iterator commands::map::find(const string &key) {
  return commands.find(key);
}

commands::map::map_type::const_iterator commands::map::find(const string &key) const {
  return commands.find(key);
}

commands::map::map_type::iterator commands::map::begin() {
  return commands.begin();
}

commands::map::map_type::const_iterator commands::map::begin() const {
  return commands.begin();
}

commands::map::map_type::iterator commands::map::end() {
  return commands.end();
}

commands::map::map_type::const_iterator commands::map::end() const {
  return commands.end();
}

